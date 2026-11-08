"""Import reviewed GPT Image atlases and pack their native RGB565 frames."""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import struct
import zlib
from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
COLOR = ROOT / 'assets/color'
LIBRARY = ROOT / 'assets/library'


def read_catalog():
    return json.loads((COLOR/'catalog.json').read_text(encoding='utf-8'))


def write_catalog(data):
    (COLOR/'catalog.json').write_text(json.dumps(data, ensure_ascii=False, indent=2)+'\n',
                                     encoding='utf-8', newline='\n')


def import_atlas(slug, source):
    catalog = read_catalog()
    batch = next(b for b in catalog['batches'] if b['id'] == slug)
    destination = COLOR/'generated'/f'{slug}.png'
    if source.resolve() != destination.resolve():
        shutil.copy2(source, destination)
    master = Image.open(destination).convert('RGB')
    reference_width, reference_height = batch['canvas']
    ratio_error = abs((master.width/master.height)/(reference_width/reference_height)-1)
    if ratio_error > .015:
        raise ValueError(f'Atlas aspect ratio changed: {slug}: {master.size}')
    unique = {entry['key']: entry for entry in catalog['unique']}
    # Cropping and native-size conversion are deterministic import operations;
    # illustration/color work is performed by GPT Image, not by this tool.
    row_bounds = None
    if slug == 'status-controls':
        # The generator preserved both strips but shifted them a few pixels.
        # Find the two continuous full-width bands, avoiding a cropped border.
        active = []
        for y in range(master.height):
            count = sum(min(master.getpixel((x,y))) < 210
                        for x in range(0, master.width, 4))
            if count > (master.width/4)*.35:
                active.append(y)
        components = []
        for y in active:
            if not components or y > components[-1][-1]+1:
                components.append([y])
            else:
                components[-1].append(y)
        spans = [(rows[0],rows[-1]+1) for rows in components if len(rows)>20]
        if len(spans) == 2:
            row_bounds = spans
    imported = {}
    for index,item in enumerate(batch['items']):
        original = unique[item['key']]
        left,top,right,bottom = item['box']
        box = (round(left*master.width/reference_width),
               round(top*master.height/reference_height),
               round(right*master.width/reference_width),
               round(bottom*master.height/reference_height))
        if row_bounds is not None:
            box = (0,row_bounds[index][0],master.width,row_bounds[index][1])
        native = master.crop(box).resize(tuple(original['size']), Image.Resampling.LANCZOS)
        # Every alias gets a semantically named RGB PNG. The original LIB mask
        # remains the authoritative transparent/opaque geometry at runtime.
        for frame in catalog['frames']:
            if frame['source_rgba_sha256'] == item['key']:
                output = COLOR/'library'/frame['source']
                output.parent.mkdir(parents=True, exist_ok=True)
                native.save(output)
                frame['color'] = output.resolve().relative_to(COLOR.resolve()).as_posix()
                frame['batch'] = slug
                frame['color_sha256'] = hashlib.sha256(output.read_bytes()).hexdigest()
                imported[frame['source']] = frame['color']
    batch.update(status='imported',master='generated/'+slug+'.png',
                 master_size=list(master.size),
                 master_sha256=hashlib.sha256(destination.read_bytes()).hexdigest(),
                 imported_frames=len(imported))
    write_catalog(catalog)
    print(json.dumps({'batch':slug,'frames':len(imported),'master_size':list(master.size)}))


def rgb565(image):
    pixels = image.convert('RGB').get_flattened_data()
    return b''.join(struct.pack('<H', ((r>>3)<<11)|((g>>2)<<5)|(b>>3))
                    for r,g,b in pixels)


def build(output, allow_partial=False):
    catalog = read_catalog()
    if not allow_partial and any('color' not in f for f in catalog['frames']):
        raise ValueError('Color atlas imports incomplete')
    if __package__:
        from .sango_lib import pack
    else:
        from sango_lib import pack
    library = pack(LIBRARY)
    manifest = json.loads((LIBRARY/'manifest.json').read_text(encoding='utf-8'))
    resources = {e['id']:e for e in [*manifest['records'],*manifest['supplements']]}
    entries = []
    payloads = {}
    for frame in catalog['frames']:
        if 'color' not in frame:
            continue
        resource = resources[frame['resource']]
        spec = resource['images'][frame['image']] if 'images' in resource else resource['image']
        width,height = frame['size']
        planes = 2 if spec['flags'] & 1 else 1
        row_bytes = (width+3)//4
        record_offset = struct.unpack_from('<I',library,(frame['resource']-1)*4)[0]
        source_offset = record_offset+spec.get('offset',12)+6+frame['frame']*row_bytes*height*planes
        path = COLOR/frame['color']
        image = Image.open(path)
        if image.size != (width,height):
            raise ValueError('Native frame dimensions changed: '+frame['color'])
        encoded = rgb565(image)
        digest = hashlib.sha256(encoded).hexdigest()
        payloads.setdefault(digest, encoded)
        entries.append((source_offset,width,height,spec['flags'],digest))
    entries.sort()
    if len({e[0] for e in entries}) != len(entries):
        raise ValueError('Duplicate original frame offsets')
    start = 32+len(entries)*16
    positions = {}; data = bytearray()
    for digest,pixels in payloads.items():
        positions[digest] = start+len(data); data.extend(pixels)
    index = b''.join(struct.pack('<IIHHI',offset,positions[digest],width,height,flags)
                     for offset,width,height,flags,digest in entries)
    header = struct.pack('<8sIIIIII',b'SGCOLOR1',start+len(data),len(entries),32,start,
                         len(library),zlib.crc32(library))
    result = header+index+data
    output.parent.mkdir(parents=True,exist_ok=True); output.write_bytes(result)
    info = {'schema':1,'complete':not any('color' not in f for f in catalog['frames']),'frames':len(entries),'unique_rgb_frames':len(payloads),
            'bytes':len(result),'sha256':hashlib.sha256(result).hexdigest(),
            'library_sha256':hashlib.sha256(library).hexdigest(),
            'library_crc32':f'{zlib.crc32(library):08x}',
            'format':'SGCOLOR1: 32-byte header, sorted <IIHHI> source-offset index, RGB565 LE pixels; masks stay in sango.lib'}
    (output.parent/'color-build.json').write_text(json.dumps(info,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(info))
    return info



def refresh():
    """Record hashes after deliberately editing the native color PNG files."""
    catalog=read_catalog()
    for frame in catalog['frames']:
        if 'color' not in frame:raise ValueError('Color atlas imports incomplete')
        path=COLOR/frame['color']
        with Image.open(path) as image:
            if image.size!=tuple(frame['size']):
                raise ValueError('Native frame dimensions changed: '+frame['color'])
        frame['color_sha256']=hashlib.sha256(path.read_bytes()).hexdigest()
    write_catalog(catalog)
    print(json.dumps({'refreshed_frames':len(catalog['frames'])}))


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    actions=parser.add_subparsers(dest='command',required=True)
    ingest=actions.add_parser('import');ingest.add_argument('batch');ingest.add_argument('source',type=Path)
    package=actions.add_parser('build');package.add_argument('--allow-partial',action='store_true');package.add_argument('-o','--output',type=Path,default=ROOT/'build/sango.clr')
    actions.add_parser('refresh')
    status=actions.add_parser('status')
    args=parser.parse_args()
    if args.command=='import':import_atlas(args.batch,args.source)
    elif args.command=='build':build(args.output,args.allow_partial)
    elif args.command=='refresh':refresh()
    else:
        c=read_catalog();print(json.dumps({'frames':len(c['frames']),
            'colored':sum('color' in f for f in c['frames']),
            'batches':{b['id']:b['status'] for b in c['batches']}}))


if __name__=='__main__':
    main()

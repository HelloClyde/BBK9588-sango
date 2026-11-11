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
    if batch.get('composition') == 'native-pixel-font':
        raise ValueError('Use tools/compose_battle_ui.py to preserve the 1:1 glyph grid')
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
        sampling = Image.Resampling.NEAREST if batch.get('resample') == 'nearest' else Image.Resampling.LANCZOS
        crop = master.crop(box)
        native = (resize_alpha_sprite(crop, tuple(original['size']), batch['alpha_import'])
                  if batch.get('alpha_import') else crop.resize(tuple(original['size']), sampling))
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
                if batch.get('alpha_import'):
                    frame['transparency'] = {
                        'mode': 'image-alpha', 'threshold': 128,
                        'reason': 'Atlas matte removed before premultiplied downsampling; preserve pale interior wood and lettering.'}
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



# Index-only extension. The original LIB flags and bitmap bytes stay intact.
TRANSPARENT_ZERO=0x100


def transparent_background(image, policy):
    """Decode explicit sprite alpha or an exterior white atlas matte.

    Only edge-connected near-white pixels are transparent. Enclosed white
    windows/roof details remain opaque. This is resource alpha metadata,
    independent of illustration generation and the original LIB mask planes.
    """
    if not policy:return set()
    if policy.get('mode') == 'image-alpha':
        if 'A' not in image.getbands():
            raise ValueError('Explicit image-alpha policy needs an alpha channel')
        return {i for i,a in enumerate(image.getchannel('A').get_flattened_data())
                if a < policy.get('threshold',128)}
    if policy.get('mode') not in ('edge-connected-white','all-near-white'):
        raise ValueError('Unsupported color transparency policy')
    width,height=image.size
    pixels=list(image.convert('RGB').get_flattened_data())
    minimum=policy['minimum_channel'];chroma=policy['maximum_chroma']
    def background(index):
        color=pixels[index]
        return min(color)>=minimum and max(color)-min(color)<=chroma
    if policy['mode']=='all-near-white':
        return {index for index in range(width*height) if background(index)}
    pending=[x for x in range(width)]+[(height-1)*width+x for x in range(width)]
    pending += [y*width for y in range(height)]+[y*width+width-1 for y in range(height)]
    seen=set();transparent=set()
    while pending:
        index=pending.pop()
        if index in seen:continue
        seen.add(index)
        if not background(index):continue
        transparent.add(index)
        x,y=index%width,index//width
        if x:pending.append(index-1)
        if x+1<width:pending.append(index+1)
        if y:pending.append(index-width)
        if y+1<height:pending.append(index+width)
    return transparent


def resize_alpha_sprite(image, size, policy):
    """Decode the source atlas matte before reducing to the device pixel grid.

    Pillow resizes RGBA through premultiplied RGBa, so transparent white cannot
    contaminate opaque edge colors. The device uses a binary transparent key.
    Enclosed pale panels/glyphs never join the outer matte component.
    """
    transparent=transparent_background(image,policy)
    rgba=image.convert('RGBA')
    alpha=Image.new('L',image.size,255)
    alpha.putdata([0 if i in transparent else 255 for i in range(image.width*image.height)])
    rgba.putalpha(alpha)
    native=rgba.resize(size,Image.Resampling.LANCZOS)
    native.putalpha(native.getchannel('A').point(lambda a:255 if a>=128 else 0))
    return native


def encode_frame(image, frame):
    if frame.get('geometry') == 'original-river-plane':
        if __package__:
            from .river_geometry import encode
        else:
            from river_geometry import encode
        return encode(frame),frame['flags']
    encoded=bytearray(rgb565(image));flags=frame['flags']
    policy=frame.get('transparency')
    if policy and policy.get('mode')=='original-color-plane':
        # Resource 056 has an intact 4-gray upward arrow but a corrupt LIB
        # mask. Recover its exact original pixel geometry, not the clipped
        # generated silhouette. This is a native resource palette/mask decode;
        # both reference PNGs and the original LIB remain unchanged.
        original=Image.open(LIBRARY/frame['source']).convert('RGB')
        if original.size!=image.size:
            raise ValueError('Original cursor plane dimensions changed')
        palette=policy['palette_rgb'];encoded=bytearray()
        for red,green,blue in original.get_flattened_data():
            if red!=green or red!=blue or str(red) not in palette:
                raise ValueError('Expected the original four-gray cursor plane')
            color=palette[str(red)]
            if color is None:
                value=0
            else:
                red,green,blue=color
                value=(((red>>3)<<11)|((green>>2)<<5)|(blue>>3)) or 1
            encoded.extend(struct.pack('<H',value))
        return bytes(encoded),flags|TRANSPARENT_ZERO
    if policy:
        transparent=transparent_background(image,policy)
        for index in range(image.width*image.height):
            value=struct.unpack_from('<H',encoded,index*2)[0]
            struct.pack_into('<H',encoded,index*2,0 if index in transparent else value or 1)
        flags |= TRANSPARENT_ZERO
    return bytes(encoded),flags


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
        encoded, flags = encode_frame(image, frame)
        digest = hashlib.sha256(encoded).hexdigest()
        payloads.setdefault(digest, encoded)
        entries.append((source_offset,width,height,flags,digest))
    entries.sort()
    if len({e[0] for e in entries}) != len(entries):
        raise ValueError('Duplicate original frame offsets')
    start = 32+len(entries)*16
    positions = {}; data = bytearray()
    for digest,pixels in payloads.items():
        positions[digest] = start+len(data); data.extend(pixels)
    index = b''.join(struct.pack('<IIHHI',offset,positions[digest],width,height,flags)
                     for offset,width,height,flags,digest in entries)
    native_status = catalog.get('native_status_image')
    if catalog.get('native_weather_images') and not native_status:
        raise ValueError('Native weather requires the native status trailer')
    if native_status:
        image = Image.open(COLOR/native_status['path']).convert('RGB')
        if image.size != (240,24):
            raise ValueError('Native status image must be exactly 240x24')
        resource = resources[native_status['source_resource']]
        source = struct.unpack_from('<I',library,(native_status['source_resource']-1)*4)[0]+resource['images'][0].get('offset',12)+6
        if any(e[0]==source for e in entries):
            weather=catalog.get('native_weather_images')
            if weather:
                if weather['size']!=[18,18] or len(weather['frames'])!=5:
                    raise ValueError('Native weather must contain five 18x18 images')
                weather_pixels=bytearray()
                for path in weather['frames']:
                    icon=Image.open(COLOR/path).convert('RGBA')
                    if icon.size!=(18,18):raise ValueError('Native weather size changed')
                    for red,green,blue,alpha in icon.get_flattened_data():
                        if alpha not in (0,255):raise ValueError('Native weather alpha must be binary')
                        value=(((red>>3)<<11)|((green>>2)<<5)|(blue>>3)) or 1
                        weather_pixels.extend(struct.pack('<H',value if alpha else 0))
                weather_source=struct.unpack_from('<I',library,(weather['source_resource']-1)*4)[0]+6+resources[weather['source_resource']]['images'][0].get('offset',12)
                weather_offset=start+len(data);data.extend(weather_pixels)
                data.extend(struct.pack('<8sIIIIII',b'SGWTH01\0',weather_offset,len(weather_pixels),18,18,weather_source,zlib.crc32(weather_pixels)))
            pixels = rgb565(image)
            offset = start+len(data)
            data.extend(pixels)
            data.extend(struct.pack('<8sIIIIII',b'SGHUD01\0',offset,len(pixels),240,24,source,zlib.crc32(pixels)))
    header = struct.pack('<8sIIIIII',b'SGCOLOR1',start+len(data),len(entries),32,start,
                         len(library),zlib.crc32(library))
    result = header+index+data
    output.parent.mkdir(parents=True,exist_ok=True); output.write_bytes(result)
    info = {'schema':1,'complete':not any('color' not in f for f in catalog['frames']),'frames':len(entries),'unique_rgb_frames':len(payloads),
            'bytes':len(result),'sha256':hashlib.sha256(result).hexdigest(),
            'library_sha256':hashlib.sha256(library).hexdigest(),
            'library_crc32':f'{zlib.crc32(library):08x}',
            'format':'SGCOLOR1: 32-byte header, sorted <IIHHI> source-offset index, RGB565 LE pixels; masks stay in sango.lib'}
    if native_status:
        info['native_status_size']=[240,24]
        info['format'] += '; optional SGHUD01 native image trailer'
    if catalog.get('native_weather_images'):
        info['native_weather_size']=[18,18]
        info['native_weather_frames']=5
        info['format'] += '; optional SGWTH01 five-frame native weather block'
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

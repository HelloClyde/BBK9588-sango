"""Lossless unpack/edit/repack of Sango's indexed 2bpp resource library."""
from __future__ import annotations
import argparse,hashlib,json,struct
from pathlib import Path
from PIL import Image

ANIMATIONS={3,6,19,20,21,22,23,24,25,27,35,36,37,38,39,40,41,42,43}
ROOT=Path(__file__).resolve().parents[1]
DEFAULT=ROOT/'assets/library'
LEVELS=(255,170,85,0)

def sha(data):return hashlib.sha256(data).hexdigest()
def write_json(path,value):
    path.parent.mkdir(parents=True,exist_ok=True)
    path.write_text(json.dumps(value,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
def asset(root,name):
    path=(root/name).resolve()
    if not path.is_relative_to(root.parent.resolve()):raise ValueError('Asset path escapes assets directory')
    return path

def catalog(data):
    candidates=[]
    for index in range(min(4096,len(data)//4)):
        offset=struct.unpack_from('<I',data,index*4)[0]
        if offset+12<=len(data):
            size,rid,count,stride,encoding=struct.unpack_from('<IHHHH',data,offset)
            if rid==index+1 and size>=12 and offset+size<=len(data):candidates.append(offset)
    if not candidates:raise ValueError('No valid resource index')
    index_bytes=min(candidates)
    if index_bytes%4:raise ValueError('Unaligned index table')
    slots=index_bytes//4;records=[]
    for rid in range(1,slots+1):
        offset=struct.unpack_from('<I',data,(rid-1)*4)[0]
        if offset in (0,0xffffffff):continue
        if offset<index_bytes or offset+12>len(data):raise ValueError(f'Invalid resource {rid} offset')
        size,actual,count,stride,encoding=struct.unpack_from('<IHHHH',data,offset)
        if actual!=rid or size<12 or offset+size>len(data):raise ValueError(f'Invalid resource {rid} header')
        records.append({'id':rid,'offset':offset,'bytes':size,'count':count,'stride':stride,'encoding':encoding})
    cursor=index_bytes
    for r in sorted(records,key=lambda r:r['offset']):
        if r['offset']<cursor:raise ValueError('Overlapping resource records')
        cursor=r['offset']+r['bytes']
    return slots,records

def bitmap(data,offset,end):
    if offset+6>end:return None
    w,h,frames,flags=struct.unpack_from('<HHBB',data,offset)
    size=6+((w+3)//4)*h*frames*(1+(flags&1))
    if not (0<w<=480 and 0<h<=480 and frames and flags in (0,1,32,33) and offset+size<=end):return None
    return {'width':w,'height':h,'frames':frames,'flags':flags,'offset':offset,'bytes':size}

def export_bitmap(data,spec,folder,stem,root):
    w,h=spec['width'],spec['height'];stride=(w+3)//4;plane=stride*h
    files=[]
    for frame in range(spec['frames']):
        start=spec['offset']+6+frame*plane*(1+(spec['flags']&1));colors=start+plane*(spec['flags']&1)
        pixels=bytearray()
        for y in range(h):
            for x in range(w):
                i=y*stride+x//4;s=6-(x%4)*2;v=LEVELS[(data[colors+i]>>s)&3]
                alpha=0 if spec['flags']&1 and (data[start+i]>>s)&1 else 255
                pixels.extend((v,v,v,alpha))
        path=folder/f'{stem}-frame-{frame:03d}.png'
        Image.frombytes('RGBA',(w,h),bytes(pixels)).save(path)
        files.append(path.relative_to(root).as_posix())
    return {**spec,'pngs':files}

def unpack(data,root):
    if root.exists():raise ValueError('Output already exists; unpack into a new directory')
    root.mkdir(parents=True);slots,records=catalog(data);layout=[];entries=[];cursor=slots*4;png_count=0
    for r in sorted(records,key=lambda r:r['offset']):
        if cursor<r['offset']:
            padding=data[cursor:r['offset']]
            if len(set(padding))==1:layout.append({'padding_bytes':len(padding),'fill':padding[0]})
            else:
                path=root/'padding'/f'{cursor:08x}.bin';path.parent.mkdir(exist_ok=True);path.write_bytes(padding)
                layout.append({'padding_file':path.relative_to(root).as_posix()})
        raw=data[r['offset']:r['offset']+r['bytes']];folder=root/f"r{r['id']:04d}";folder.mkdir()
        (folder/'record.bin').write_bytes(raw)
        entry={'id':r['id'],'kind':'raw','record':(folder/'record.bin').relative_to(root).as_posix(),
            'original_offset':r['offset'],'original_bytes':len(raw),'original_sha256':sha(raw)}
        if r['id'] in ANIMATIONS and not r['encoding']:
            commands,images=raw[14:16];start=18+commands*5;specs=[]
            for i in range(images):
                spec=bitmap(raw,start,len(raw))
                if not spec or spec['frames']!=1:raise ValueError(f"Invalid animation {r['id']} image {i}")
                specs.append(export_bitmap(raw,spec,folder,f'image-{i:03d}',root));start+=spec['bytes']
            if start!=len(raw):raise ValueError('Unexpected animation suffix')
            timeline={'commands':[list(raw[18+i*5:23+i*5]) for i in range(commands)]}
            write_json(folder/'timeline.json',timeline)
            entry.update(kind='animation',images=specs,timeline=(folder/'timeline.json').relative_to(root).as_posix())
        elif not r['encoding'] and r['count']==1:
            w,h=struct.unpack_from('<HH',raw,12)
            # Map headers can resemble four-frame bitmaps. Check their complete
            # tile-array length before interpreting the six-byte image header.
            if r['id']>=100 and w and h and 28+w*h==len(raw):
                grid={'width':w,'height':h,'tiles':[list(raw[28+y*w:28+(y+1)*w]) for y in range(h)]}
                write_json(folder/'map.json',grid);entry.update(kind='map',map=(folder/'map.json').relative_to(root).as_posix())
            else:
                spec=bitmap(raw,12,len(raw))
                if spec and 12+spec['bytes']==len(raw):
                    entry.update(kind='bitmap',images=[export_bitmap(raw,spec,folder,'image',root)])
        png_count+=sum(len(i['pngs']) for i in entry.get('images',[]))
        entries.append(entry);layout.append({'resource':r['id']});cursor=r['offset']+r['bytes']
    if cursor<len(data):
        (root/'trailer.bin').write_bytes(data[cursor:]);layout.append({'padding_file':'trailer.bin'})
    manifest={'schema':1,'format':'Sango 9588 indexed 2bpp library','index_slots':slots,
        'original_bytes':len(data),'original_sha256':sha(data),'original_index':list(struct.unpack_from(f'<{slots}I',data)),
        'png_frames':png_count,'records':sorted(entries,key=lambda r:r['id']),'layout':layout,'supplements':[]}
    write_json(root/'manifest.json',manifest)
    return manifest

def encode_bitmap(root,spec,seed=b''):
    w,h=spec['width'],spec['height'];frames=spec['frames'];flags=spec['flags']
    if not (0<w<=480 and 0<h<=480 and 0<frames<=255 and flags in (0,1,32,33)):raise ValueError('Invalid bitmap geometry or flags')
    if len(spec['pngs'])!=frames:raise ValueError('Bitmap frame count mismatch')
    stride=(w+3)//4;plane=stride*h;size=6+plane*frames*(1+(flags&1))
    out=bytearray(seed if len(seed)==size else bytes(size));struct.pack_into('<HHBB',out,0,w,h,frames,flags)
    for frame,name in enumerate(spec['pngs']):
        image=Image.open(asset(root,name)).convert('RGBA')
        if image.size!=(w,h):raise ValueError(f'PNG size mismatch: {name}')
        rgba=image.tobytes();start=6+frame*plane*(1+(flags&1));colors=start+plane*(flags&1)
        for y in range(h):
            for x in range(w):
                at=(y*w+x)*4;r,g,b,a=rgba[at:at+4]
                if r!=g or g!=b or r not in LEVELS:raise ValueError(f'PNG must use the four original gray levels: {name}')
                if not flags&1 and a!=255:raise ValueError(f'Opaque image contains transparency: {name}')
                if a not in (0,255):raise ValueError(f'Only binary alpha is supported: {name}')
                i=y*stride+x//4;shift=6-(x%4)*2;bits=3<<shift
                out[colors+i]=(out[colors+i]&~bits)|((3-r//85)<<shift)
                if flags&1:
                    # Preserve the unused high mask bit and row-end padding.
                    out[start+i]=(out[start+i]&~(1<<shift))|((a==0)<<shift)
    return bytes(out)

def encode_record(root,entry):
    raw=asset(root,entry['record']).read_bytes();size,rid,count,stride,encoding=struct.unpack_from('<IHHHH',raw)
    if rid!=entry['id'] or size!=len(raw):raise ValueError('Resource header/manifest mismatch')
    if entry['kind']=='bitmap':
        spec=entry['images'][0];begin=spec['offset'];end=begin+spec['bytes']
        result=raw[:begin]+encode_bitmap(root,spec,raw[begin:end])+raw[end:]
    elif entry['kind']=='animation':
        commands=json.loads(asset(root,entry['timeline']).read_text(encoding='utf-8'))['commands']
        if len(commands)>255 or len(entry['images'])>255:raise ValueError('Too many animation frames')
        if any(len(c)!=5 or any(type(v)!=int or not 0<=v<=255 for v in c) for c in commands):raise ValueError('Invalid animation command')
        prefix=bytearray(raw[:18]);prefix[14]=len(commands);prefix[15]=len(entry['images'])
        result=bytes(prefix)+b''.join(bytes(c) for c in commands)
        for spec in entry['images']:
            start=spec['offset'];result+=encode_bitmap(root,spec,raw[start:start+spec['bytes']])
    elif entry['kind']=='map':
        grid=json.loads(asset(root,entry['map']).read_text(encoding='utf-8'));w,h=grid['width'],grid['height'];rows=grid['tiles']
        if not (0<w<=255 and 0<h<=255) or len(rows)!=h or any(len(row)!=w for row in rows):raise ValueError('Invalid map dimensions')
        if any(type(v)!=int or not 0<=v<=255 for row in rows for v in row):raise ValueError('Invalid map tile')
        prefix=bytearray(raw[:28]);struct.pack_into('<HH',prefix,12,w,h)
        result=bytes(prefix)+b''.join(bytes(row) for row in rows)
    elif entry['kind']=='raw':result=raw
    else:raise ValueError('Unknown resource kind')
    result=bytearray(result);struct.pack_into('<I',result,0,len(result));return bytes(result)

def pack(root,include_supplements=True):
    manifest=json.loads((root/'manifest.json').read_text(encoding='utf-8'))
    if manifest['schema']!=1:raise ValueError('Unsupported resource manifest')
    slots=manifest['index_slots'];index=list(manifest['original_index'])
    if len(index)!=slots:raise ValueError('Index size mismatch')
    records={}
    for entry in manifest['records']:
        rid=entry['id']
        if rid in records or not 1<=rid<=slots:raise ValueError('Duplicate/out-of-range resource ID')
        records[rid]=encode_record(root,entry)
    result=bytearray(slots*4);placed=set()
    for part in manifest['layout']:
        if 'resource' in part:
            rid=part['resource']
            if rid in placed:raise ValueError('Duplicate resource layout entry')
            index[rid-1]=len(result);result.extend(records[rid]);placed.add(rid)
        elif 'padding_bytes' in part:result.extend(bytes([part['fill']])*part['padding_bytes'])
        else:result.extend(asset(root,part['padding_file']).read_bytes())
    if placed!=set(records):raise ValueError('Resource missing from physical layout')
    if include_supplements:
        for entry in manifest.get('supplements',[]):
            rid=entry['id']
            if not 1<=rid<=slots or rid in records or index[rid-1] not in (0,0xffffffff):raise ValueError('Supplement overwrites existing resource')
            payload=encode_bitmap(root,entry['image']);record=struct.pack('<IHHHH',12+len(payload),rid,1,0,0)+payload
            index[rid-1]=len(result);result.extend(record);records[rid]=record
    struct.pack_into(f'<{slots}I',result,0,*index)
    catalog(bytes(result))
    return bytes(result)

def generate_includes(root,include_dir):
    """Use the same supplemental PNGs for the existing embedded C fallback."""
    manifest=json.loads((root/'manifest.json').read_text(encoding='utf-8'))
    for entry in manifest.get('supplements',[]):
        payload=encode_bitmap(root,entry['image'])
        for name in entry.get('c_includes',[]):
            if Path(name).name!=name or not name.endswith('.inc'):
                raise ValueError('Invalid generated C include filename')
            text='/* Generated from assets/library/manifest.json by tools/sango_lib.py. */\n'
            text+='\n'.join('  '+','.join(f'0x{v:02x}' for v in payload[i:i+16])+',' for i in range(0,len(payload),16))+'\n'
            path=include_dir/name
            # Avoid unnecessary rewrites; output contains no machine paths/date.
            if not path.exists() or path.read_text(encoding='ascii')!=text:
                path.write_text(text,encoding='ascii',newline='\n')

def verify_original(root):
    manifest=json.loads((root/'manifest.json').read_text(encoding='utf-8'))
    data=pack(root,False)
    if len(data)!=manifest['original_bytes'] or sha(data)!=manifest['original_sha256']:
        raise ValueError('Edited resources differ from the original library')
    return data

def main():
    parser=argparse.ArgumentParser(description=__doc__);sub=parser.add_subparsers(dest='op',required=True)
    u=sub.add_parser('unpack');u.add_argument('input',type=Path);u.add_argument('-o','--output',type=Path,required=True)
    p=sub.add_parser('pack');p.add_argument('source',type=Path,nargs='?',default=DEFAULT);p.add_argument('-o','--output',type=Path,default=ROOT/'build/sango.lib');p.add_argument('--original-only',action='store_true')
    i=sub.add_parser('inspect');i.add_argument('input',type=Path)
    args=parser.parse_args()
    if args.op=='unpack':
        m=unpack(args.input.read_bytes(),args.output);print(json.dumps({'records':len(m['records']),'png_frames':m['png_frames'],'original_sha256':m['original_sha256']}))
    elif args.op=='pack':
        data=pack(args.source,not args.original_only);args.output.parent.mkdir(parents=True,exist_ok=True);args.output.write_bytes(data)
        print(json.dumps({'output':str(args.output),'bytes':len(data),'sha256':sha(data)}))
    else:
        data=args.input.read_bytes();slots,records=catalog(data);print(json.dumps({'index_slots':slots,'records':records,'bytes':len(data),'sha256':sha(data)},indent=2))

if __name__=='__main__':main()

"""Exercise the compiled RGB565 loader, index and rasterizers in MIPS.

No firmware needed. Only SDK file/allocation/pixel boundaries are modeled.
The real C CRC, parsing, binary lookup, clipping and original masks execute.
"""
from __future__ import annotations
import hashlib,json,struct,zlib
from pathlib import Path
from PIL import Image
from test_control_flow import Machine,STATE,ROOT,BUFFER
from color_assets import read_catalog,rgb565,encode_frame,TRANSPARENT_ZERO

LIB_ADDRESS=0x81000000
COLOR_ADDRESS=0x81200000
CONTEXT=0x81600000


def machine(library,color=None):
    m=Machine((ROOT/'build/sango.elf').read_bytes())
    m.write(LIB_ADDRESS,library)
    m.word(STATE['g_resource_package_address'],LIB_ADDRESS)
    m.word(STATE['g_draw_context'],CONTEXT)
    m.word(STATE['g_message_context'],CONTEXT+4)
    m.word(STATE['g_game_context'],CONTEXT+8)
    m.pixels=[];m.guards=[]
    m.texts=[]
    m.intercept('sango_color_sdk_text',5,lambda a:m.texts.append([*a[:4],m.text(a[4])]))
    m.intercept('sango_color_sdk_pixel',4,lambda a:m.pixels.append(tuple(a)))
    m.intercept('sango_color_sdk_guard',1,lambda a:m.guards.append(a[0]))
    if color is not None:
        m.write(COLOR_ADDRESS,color)
        assert m.call('sango_color_use_buffer',COLOR_ADDRESS,len(color),len(library),
                      instruction_limit=80_000_000)==1
    return m


def mini():
    # Width5 has a partially used final byte; mask has both bit patterns1/3.
    lib=b'LIB!'+bytes((0x10,0xc0,0x00,0x00,0x1b,0x40,0xe4,0x80))
    values=(0,0xf800,0x07e0,0x001f,0xffff,0x2222,0x1234,0x4321,0xabcd,0xdddd)
    colors=struct.pack('<8sIIIIII',b'SGCOLOR1',68,1,32,48,len(lib),zlib.crc32(lib))
    return lib,colors+struct.pack('<IIHHI',4,48,5,2,1)+struct.pack('<10H',*values)


def expected_pixels(library,colors,entry,x,y,target):
    offset,payload,w,h,flags=entry
    values=struct.unpack_from('<'+'H'*(w*h),colors,payload)
    expected=[]
    for row in range(h):
        for col in range(w):
            sx=((x+col+32768)%65536)-32768;sy=y+row
            if not(0<=sx<240 and 0<=sy<320):continue
            if flags&1 and not flags&TRANSPARENT_ZERO and (library[offset+row*((w+3)//4)+col//4]>>(6-(col%4)*2))&1:continue
            if flags&TRANSPARENT_ZERO and not values[row*w+col]:continue
            expected.append((target,sx,sy,values[row*w+col] or 1))
    return expected


def main():
    count=0
    lib=(ROOT/'build/sango.lib').read_bytes();colors=(ROOT/'build/sango.clr').read_bytes()
    header=struct.unpack_from('<8sIIIIII',colors)
    assert header[:1]==(b'SGCOLOR1',) and header[1]==len(colors) and header[5:]==(len(lib),zlib.crc32(lib))
    entries=[struct.unpack_from('<IIHHI',colors,32+i*16) for i in range(header[2])]
    catalog=read_catalog();assert len(entries)==len(catalog['frames'])==1204
    assert all(b['status']=='imported' for b in catalog['batches'])
    m=machine(lib,colors)
    by_offset={e[0]:e for e in entries}
    manifest=json.loads((ROOT/'assets/library/manifest.json').read_text(encoding='utf-8'))
    records={r['id']:r for r in manifest['records']+manifest['supplements']}
    frame_entries={}
    for f in catalog['frames']:
        r=records[f['resource']];spec=r['images'][f['image']] if 'images' in r else r['image']
        w,h=f['size'];stride=((w+3)//4)*h*(2 if spec['flags']&1 else 1)
        offset=struct.unpack_from('<I',lib,(f['resource']-1)*4)[0]+spec.get('offset',12)+6+f['frame']*stride
        entry=by_offset[offset];assert entry[2:4]==(w,h) and entry[4]&~TRANSPARENT_ZERO==spec['flags']
        png=ROOT/'assets/color'/f['color'];image=Image.open(png)
        assert image.size==(w,h) and hashlib.sha256(png.read_bytes()).hexdigest()==f['color_sha256']
        encoded,flags=encode_frame(image,f)
        assert entry[4]==flags and colors[entry[1]:entry[1]+w*h*2]==encoded
        assert m.call('sango_color_pixels',LIB_ADDRESS+offset,w,h,spec['flags']&1)==COLOR_ADDRESS+entry[1]
        assert m.call('sango_color_pixels',LIB_ADDRESS+offset,w+1,h,spec['flags']&1)==0
        assert m.call('sango_color_pixels',LIB_ADDRESS+offset,w,h,not(spec['flags']&1))==0
        frame_entries[(f['resource'],f['image'],f['frame'])]=entry
        count+=3
    count+=1
    # Source contours and native extents, RGB565 (including opaque black), all
    # four legacy raster entry points, screen presentation and clipping.
    presents=[]
    m.intercept('sango_display_present_context',2,lambda a:presents.append(a))
    for key in [(3,0,0),(44,0,0),(18,0,0),(17,0,0),(4,0,16),(5,0,0),(19,1,0),(38,0,0),(48,0,0),(9,0,0),(33,0,0)]:
        e=frame_entries[key];offset,p,w,h,flags=e
        for x,y in [(0,0),(65533,-2),(234,314)]:
            m.pixels.clear();m.guards.clear()
            assert m.call('sango_color_draw_raster',x,y,w,h,LIB_ADDRESS+offset,CONTEXT+8,flags&1,
                          instruction_limit=25_000_000)==1
            assert m.pixels==expected_pixels(lib,colors,e,x,y,CONTEXT+8),key
            assert m.guards==[]
            count+=1
    # Every original combat sprite goes through the actual colored mask loop.
    battle_resources=set(range(19,26))|{27}|set(range(35,44))
    combat_frames=0
    for f in catalog['frames']:
        if f['resource'] not in battle_resources:continue
        e=frame_entries[(f['resource'],f['image'],f['frame'])]
        off,p,w,h,flags=e;m.pixels.clear()
        assert m.call('sango_color_draw_raster',20,30,w,h,LIB_ADDRESS+off,CONTEXT+8,flags&1,
                      instruction_limit=20_000_000)==1
        assert m.pixels==expected_pixels(lib,colors,e,20,30,CONTEXT+8)
        combat_frames+=1;count+=1
    for masked in (0,1):
        e=frame_entries[(5,0,0) if masked else (17,0,0)]
        off,p,w,h,flags=e
        for screen in (0,1):
            name=('sango_raster_draw_masked_screen' if masked else 'sango_raster_draw_screen') if screen else ('sango_raster_draw_masked' if masked else 'sango_raster_draw_opaque')
            m.pixels.clear();m.guards.clear();presents.clear()
            args=(4,5,w,h,LIB_ADDRESS+off) if screen else (4,5,w,h,LIB_ADDRESS+off,CONTEXT+8)
            m.call(name,*args,instruction_limit=20_000_000)
            target=(CONTEXT if masked else CONTEXT+4) if screen else CONTEXT+8
            assert m.pixels==expected_pixels(lib,colors,e,4,5,target),name
            if screen and not masked:assert presents==[[CONTEXT+4,0],[0,CONTEXT+4]]
            if screen and masked:assert m.guards==[1,0]
            count+=1
    # Actual supplemental toolbar/credits dispatch retains native dimensions.
    m.intercept('sango_render_clear_rectangle',5,lambda a:None)
    m.intercept('sango_render_present',1,lambda a:None)
    for name,rid,y in [('sango_statusbar_draw',17,232),('sango_battle_toolbar_draw',17,232),('sango_credits_draw',18,0)]:
        m.pixels.clear();m.texts.clear();m.call(name,CONTEXT+8,instruction_limit=25_000_000)
        expected=expected_pixels(lib,colors,frame_entries[(rid,0,0)],0,y,CONTEXT+8)
        assert m.pixels==expected
        count+=1
    # Small valid package allows hostile headers/index entries to exercise real
    # CRC/validation without repeating a half-megabyte CRC for every mutation.
    small_lib,small=mini()
    malformed=[(0,ord('X'),1),(8,len(small)+1,4),(12,4097,4),(12,0,4),(16,16,4),(20,32,4),
               (24,len(small_lib)+1,4),(28,0,4),(32,len(small_lib),4),(36,49,4),
               (36,46,4),(36,len(small),4),(40,0,2),(40,321,2),(42,0,2),(44,2,4)]
    n=machine(small_lib)
    for pos,value,size in malformed:
        damaged=bytearray(small);damaged[pos:pos+size]=value.to_bytes(size,'little')
        n.write(COLOR_ADDRESS,damaged)
        assert n.call('sango_color_use_buffer',COLOR_ADDRESS,len(damaged),len(small_lib))==0,(pos,value)
        assert n.call('sango_color_pixels',LIB_ADDRESS+4,5,2,1)==0
        count+=1
    n.write(COLOR_ADDRESS,small)
    assert n.call('sango_color_use_buffer',COLOR_ADDRESS,len(small),len(small_lib))==1
    n.call('sango_color_draw_raster',0,0,5,2,LIB_ADDRESS+4,CONTEXT,1)
    assert n.pixels==expected_pixels(small_lib,small,(4,48,5,2,1),0,0,CONTEXT)
    assert n.pixels[0][-1]==1 # Opaque black cannot become copy-key transparency.
    count+=1
    n.call('sango_color_unload');n.pixels.clear()
    assert n.call('sango_color_draw_raster',0,0,5,2,LIB_ADDRESS+4,CONTEXT,1)==0 and not n.pixels
    count+=1
    # File loader/ownership: missing, short/oversized, allocation failure,
    # short reads, wrong LIB, good load, and cleanup of only owned buffers.
    for case in ['missing','short','large','oom','short-read','wrong-lib','valid']:
        n=machine(small_lib);frees=[];closed=[];opened=[]
        data=(b'bad' if case=='short' else small)
        if case=='wrong-lib':data=small[:28]+bytes(4)+small[32:]
        n.write(BUFFER,b'A:\\app\\sango.LIB\0')
        n.intercept('bbk_strlen',1,lambda a:len(n.text(a[0])))
        n.intercept('bbk_memcpy',3,lambda a:n.write(a[0],n.read(a[1],a[2])))
        def fopen(a):
            opened.append(n.text(a[0]));return 0 if case=='missing' else 7
        n.intercept('bbk_fopen',2,fopen)
        n.intercept('bbk_fseek',3,lambda a:0)
        n.intercept('bbk_ftell',1,lambda a:17*1024*1024 if case=='large' else len(data))
        n.intercept('bbk_alloc',1,lambda a:0 if case=='oom' else COLOR_ADDRESS)
        def fread(a):
            assert a[1:]==[len(data),1,7]
            n.write(a[0],data);return 0 if case=='short-read' else 1
        n.intercept('bbk_fread',4,fread)
        n.intercept('bbk_fclose',1,lambda a:closed.append(a[0]))
        n.intercept('bbk_free_if_nonnull',1,lambda a:frees.append(a[0]))
        n.call('sango_color_load',BUFFER,len(small_lib))
        assert opened==[b'A:\\app\\sango.clr']
        got=n.call('sango_color_pixels',LIB_ADDRESS+4,5,2,1)
        assert bool(got)==(case=='valid'),case
        n.call('sango_color_unload')
        assert frees==([COLOR_ADDRESS] if case in ['short-read','wrong-lib','valid'] else []),(case,frees)
        assert closed==([] if case=='missing' else [7]),case
        count+=1
    report={'passed':count,'failed':0,'frames':1204,'unique_rgb_frames':len({e[1] for e in entries}),'combat_frames':combat_frames,
            'bda_sha256':hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),
            'color_sha256':hashlib.sha256(colors).hexdigest(),
            'scope':'Real compiled MIPS CRC32, header/index validation, all 1204 source-offset lookups and native PNG/RGB565 byte equivalence, original masks, four raster entry points, clipping and screen/context selection, opaque-black copy key, supplemental dispatch and optional SDK file lifecycle. SDK pixels/files/allocations modeled; native rendering separately verified.'}
    (ROOT/'build/color-mips-validation.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(report))

if __name__=='__main__':main()

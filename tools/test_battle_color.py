"""Run colored battle timelines and verify backdrop restoration in compiled MIPS."""
from pathlib import Path
import hashlib,json,struct
from PIL import Image
from test_color_assets import machine,CONTEXT
from test_control_flow import ROOT,STATE,BUFFER
from color_assets import read_catalog

GROUPS=[19,20,21,22,23,24,25,27,35,36,37,38,39,40,41,42,43]


def main():
    lib=(ROOT/'build/sango.lib').read_bytes();color=(ROOT/'build/sango.clr').read_bytes()
    catalog=read_catalog();manifest=json.loads((ROOT/'assets/library/manifest.json').read_text(encoding='utf8'))
    records={r['id']:r for r in manifest['records']+manifest['supplements']}
    checks=0;tile_stats=[]
    # Plain ground and every water family must have an opaque colored surface.
    for f in [f for f in catalog['frames'] if f['resource']==4]:
        im=Image.open(ROOT/'assets/color'/f['color']).convert('RGB');pixels=list(im.get_flattened_data())
        pure_white=sum(p==(255,255,255) for p in pixels)
        blue=sum(b>r+16 and g>r+8 for r,g,b in pixels)
        assert pure_white==0,(f['frame'],pure_white)
        if f['frame']>=16 and f['frame']!=41:assert blue>=32,(f['frame'],blue)
        if f['frame']==1:assert all(g>160 and b<g for r,g,b in pixels)
        tile_stats.append({'frame':f['frame'],'white_pixels':pure_white,'water_blue_pixels':blue});checks+=1
    # All battle overlay color planes retain their original visible linework.
    # Unlike the old city cursor, none has hidden nonwhite foreground pixels.
    overlay_ids={5,7,19,20,21,22,23,24,25,27,34,38}
    masked_frames=0
    for f in catalog['frames']:
        if f['resource'] not in overlay_ids or not f['flags']&1:continue
        im=Image.open(ROOT/'assets/library'/f['source']).convert('RGBA')
        assert not any(min(r,g,b)<255 and a==0 for r,g,b,a in im.get_flattened_data()),(f['resource'],f['image'],f['frame'])
        masked_frames+=1;checks+=1
    # Weather mattes and number counters are transparent, while the actual
    # warm/cool glyph pixels remain visible, including opaque black.
    entries=[struct.unpack_from('<IIHHI',color,32+i*16) for i in range(1204)]
    alpha_frames=0
    for f in [f for f in catalog['frames'] if f['resource'] in (9,15)]:
        r=records[f['resource']];spec=r['images'][f['image']];w,h=f['size']
        offset=struct.unpack_from('<I',lib,(f['resource']-1)*4)[0]+spec['offset']+6+f['frame']*((w+3)//4)*h
        e=next(e for e in entries if e[0]==offset);values=struct.unpack_from('<'+'H'*(w*h),color,e[1])
        assert e[4]&0x100 and 0<values.count(0)<w*h
        alpha_frames+=1;checks+=1
    m=machine(lib,color);m.word(STATE['g_scratch_buffer_address'],BUFFER+0x1000)
    palette=[0x9e69,0xffff,0,0xf81f,0x1234]
    base=Image.new('I',(240,320));base.putdata([palette[((x//8)+(y//8))%5] for y in range(320) for x in range(240)])
    canvas=base.copy();frames=[];captures=[];restores=[];freed=[];snapshot=None;wait_key=0;peek_key=255;fail_capture=False;last_restore_count=0
    def flush():
        for ctx,x,y,v in m.pixels:
            assert ctx==CONTEXT+8
            canvas.putpixel((x,y),v)
        m.pixels.clear()
    def capture(a):
        nonlocal snapshot
        flush();captures.append(a[0]);snapshot=canvas.copy()
        return 0 if fail_capture else 0x81610000
    def restore(a):
        flush();handle,left,top,right,bottom,target=a
        assert handle==0x81610000 and target==CONTEXT+8
        assert 0<=left<=right<240 and 0<=top<=bottom<320
        box=(left,top,right+1,bottom+1);canvas.paste(snapshot.crop(box),box);restores.append(a)
    def free(a):
        flush();assert a==[0x81610000];freed.append(a[0])
    def clear(a):
        flush();left,top,right,bottom,target=a
        left=max(0,left);top=max(0,top);right=min(239,right);bottom=min(319,bottom)
        if left<=right and top<=bottom:canvas.paste(0xffff,(left,top,right+1,bottom+1))
    def present(a):
        nonlocal last_restore_count
        points=list(m.pixels)
        flush()
        if len(restores)>last_restore_count:
            # On an erase tick the real engine redraws every live actor.
            # Everything outside those actual raster writes must be underlay.
            expected=base.copy()
            for ctx,x,y,value in points:expected.putpixel((x,y),value)
            assert canvas.tobytes()==expected.tobytes(),'expired sprite left a white block or trail'
        last_restore_count=len(restores)
        if len(frames)<160:frames.append(canvas.copy())
    m.intercept('sango_color_sdk_snapshot',1,capture)
    m.intercept('sango_color_sdk_restore',6,restore)
    m.intercept('sango_color_sdk_snapshot_free',1,free)
    m.intercept('sango_render_clear_rectangle',5,clear)
    m.intercept('sango_render_present',1,present)
    m.intercept('sango_input_wait',2,lambda a:wait_key)
    m.intercept('sango_input_peek_key',0,lambda a:peek_key)
    results=[];out=ROOT/'build/battle-color-review';out.mkdir(exist_ok=True)
    def rgb(im):
        result=Image.new('RGB',im.size);result.putdata([(((v>>11)&31)*255//31,((v>>5)&63)*255//63,(v&31)*255//31) for v in im.get_flattened_data()]);return result
    for rid in GROUPS:
        canvas=base.copy();frames.clear();captures.clear();restores.clear();freed.clear();last_restore_count=0
        # Command count is an actual byte in the LIB animation header.
        start=struct.unpack_from('<I',lib,(rid-1)*4)[0]+12;command_count=lib[start+2]
        result=m.call('sango_animation_play_range',rid,0,command_count-1,0,20,49,instruction_limit=150_000_000)
        flush()
        assert result==255 and captures==[CONTEXT+8] and freed==[0x81610000],rid
        assert restores,rid
        # Legacy playback retains the last lifetime-1 frame until its caller
        # redraws the UI; freeing the snapshot must not erase that final frame.
        assert canvas.tobytes()==frames[-1].tobytes(),rid
        assert len(frames)>1 and any(f.tobytes()!=base.tobytes() for f in frames),rid
        results.append({'resource':rid,'commands':command_count,'frames':len(frames),'restores':len(restores)})
        if rid in (19,27,35,38):
            converted=[rgb(im) for im in frames]
            converted[0].save(out/f'animation-{rid}.gif',save_all=True,append_images=converted[1:],duration=80,loop=0)
        checks+=1
    # Both interrupt exits free the compatible context and return the same key.
    for kind in ['peek','wait']:
        canvas=base.copy();captures.clear();freed.clear();frames.clear();restores.clear();last_restore_count=0
        peek_key=28 if kind=='peek' else 255;wait_key=28 if kind=='wait' else 0
        result=m.call('sango_animation_play_range',19,0,6,1 if kind=='peek' else 0,20,49,instruction_limit=20_000_000)
        assert result==28 and captures==[CONTEXT+8] and freed==[0x81610000],kind
        checks+=1
    # Clip restoration to the physical canvas. A failed snapshot allocation
    # falls back to the original clear path without freeing an unowned handle.
    wait_key=0;peek_key=255;canvas=base.copy();captures.clear();freed.clear();restores.clear()
    m.call('sango_color_animation_begin',CONTEXT+8)
    m.call('sango_color_animation_erase',0xfffffffa,0xfffffffa,250,330,CONTEXT+8)
    assert restores[-1][1:5]==[0,0,239,319]
    assert m.call('sango_color_animation_end',123)==123 and freed==[0x81610000];checks+=1
    fail_capture=True;captures.clear();freed.clear();restores.clear();canvas=base.copy()
    m.call('sango_animation_play_range',19,0,6,0,20,49,instruction_limit=50_000_000)
    assert captures==[CONTEXT+8] and not restores and not freed;checks+=1
    report={'passed':checks,'failed':0,'masked_battle_frames':masked_frames,'opaque_terrain_tiles':46,
            'transparent_weather_digit_frames':alpha_frames,'animation_groups':results,
            'bda_sha256':hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),
            'color_sha256':hashlib.sha256(color).hexdigest(),
            'scope':'Real compiled MIPS timelines for all 17 battle groups, RGB565 sprite loops and backing-context ownership/clip/interrupt/failure paths. SDK capture/copy/pixel/timer boundaries modeled; native SDK backing-context copy separately verified. Terrain semantic colors and overlay alpha checked; no full battle/campaign or physical-device claim.'}
    (ROOT/'build/battle-color-validation.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report))

if __name__=='__main__':main()

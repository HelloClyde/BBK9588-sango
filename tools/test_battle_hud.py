"""Check the compiled 240-pixel battle footer against the 9288S reference.

Real MIPS resource decoding, scaling, HUD dispatch and text preparation run in
Unicorn. SDK pixel/text boundaries are recorded; native font pixels require the
separate firmware check. No original executable or private firmware is needed.
"""
from __future__ import annotations
import hashlib,json,struct
from pathlib import Path
from PIL import Image
from test_control_flow import Machine,STATE,ROOT,BUFFER

TOP=240
TOOLBAR_TOP=264
CONTEXT=0x81300100
GRAY=(255,170,85,0)


def machine():
    m=Machine((ROOT/'build/sango.elf').read_bytes())
    m.write(0x81000000,(ROOT/'build/sango.lib').read_bytes())
    m.word(STATE['g_resource_package_address'],0x81000000)
    m.word(STATE['g_game_context'],CONTEXT)
    image=Image.new('L',(240,320),85)
    text=[];fonts=[];clears=[]
    def pixel(args):
        x,y,gray,target=args
        assert target==CONTEXT and 0<=x<240 and 240<=y<300,(x,y,gray,target)
        image.putpixel((x,y),GRAY[gray])
    def clear(args):
        left,top,right,bottom,target=args
        assert target in (0,CONTEXT)
        clears.append(args)
        image.paste(255,(left,top,right+1,bottom+1))
    m.intercept('sango_display_put_gray_pixel',4,pixel)
    m.intercept('sango_render_clear_rectangle',5,clear)
    m.intercept('sango_display_select_font',2,lambda args:fonts.append(args))
    m.intercept('sango_text_draw_native',4,
        lambda args:text.append([args[0],args[1],m.text(args[2]).hex(),args[3]]))
    return m,image,text,fonts,clears


def weather_image(frame):
    manifest=json.loads((ROOT/'assets/library/manifest.json').read_text(encoding='utf-8'))
    entry=next(row for row in manifest['records'] if row['id']==9)
    return Image.open(ROOT/'assets/library'/entry['images'][0]['pngs'][frame]).convert('L')


def scale_reference(image):
    # Integer stages avoid floating-point tie drift at a direct 1.5x resize.
    width,height=image.size
    return image.resize((width*3,height*3),Image.Resampling.NEAREST).resize(
        (width*3//2,height*3//2),Image.Resampling.NEAREST)


def main():
    reference=Image.open(ROOT/'assets/battle-toolbar/status-row-9288s-reference.png').convert('L')
    assert reference.size==(160,16)
    expected_row=scale_reference(reference)
    toolbar=Image.open(ROOT/'assets/battle-toolbar/toolbar-240x36.png').convert('L')
    count=0
    for food in (0,1,9,10,9999,65535):
        for weather in range(1,6):
            m,image,text,fonts,clears=machine()
            m.write(STATE['g_battle_attacker_food'],struct.pack('<H',food))
            m.write(STATE['g_battle_weather'],bytes((weather,)))
            m.call('sango_battle_status_draw')
            expected=expected_row.copy()
            expected.paste(scale_reference(weather_image(weather-1)),(112,3))
            assert image.crop((0,TOP,240,TOOLBAR_TOP)).tobytes()==expected.tobytes(),(food,weather)
            assert image.crop((0,TOOLBAR_TOP,240,300)).tobytes()==toolbar.tobytes()
            assert image.crop((0,300,240,320)).getextrema()==(255,255)
            assert clears==[[0,TOOLBAR_TOP,239,319,CONTEXT]],clears
            assert text==[[21,244,str(food).encode().hex(),CONTEXT]],text
            assert fonts==[[3,CONTEXT],[0,CONTEXT]],fonts
            count+=1
    for target in (0,CONTEXT):
        for value in ('森林','司马懿','夏侯惇','无法到达','没有目标','命令无效','诸葛亮孔明'):
            m,image,text,fonts,clears=machine()
            encoded=value.encode('gbk')
            m.write(BUFFER,encoded+b'\0')
            m.call('sango_battle_status_draw_description',BUFFER,target)
            # Real names/errors fit four GBK characters; a fifth is truncated.
            # Skill-menu errors draw directly to the screen, map labels to context.
            assert text==[[159,244,encoded[:8].hex(),target]],text
            assert clears==[[159,242,237,261,target]],clears
            assert fonts==[[3,target],[0,target]],fonts
            count+=1
    for x,y,expected in ((60,266,1),(113,297,1),(128,266,2),(181,297,2),
                          (85,265,0),(85,298,0),(85,260,0),(85,300,0),
                          (59,282,0),(114,282,0),(127,282,0),(182,282,0),
                          (356,282,0),(85,538,0)):
        m=Machine((ROOT/'build/sango.elf').read_bytes())
        assert m.call('sango_battle_toolbar_hit',x,y)==expected,(x,y)
        count+=1
    report={'passed':count,'failed':0,'status_rectangle':[0,240,240,24],
            'toolbar_rectangle':[0,264,240,36],'text_font_logical_id':3,
            'reference_status_sha256':hashlib.sha256((ROOT/'assets/battle-toolbar/status-row-9288s-reference.png').read_bytes()).hexdigest(),
            'bda_sha256':hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),
            'scope':'Compiled MIPS HUD/scaling/text preparation; SDK pixel/text boundaries modeled. '
                    'Compares original 9288S status bitmap, all five weather frames, six food values, '
                    'GBK names/errors on screen/context and full-width touch boundaries. Native fonts checked separately.'}
    path=ROOT/'build/battle-hud-validation.json'
    path.write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps(report))


if __name__=='__main__':
    main()

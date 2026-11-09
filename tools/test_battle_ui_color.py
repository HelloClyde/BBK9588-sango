"""Exercise native-size color HUD text, the original detail switch and combat origins.

The production MIPS prepares strings, coordinates and dispatch. Only SDK text
pixels and selected gameplay inputs are modeled; native font transparency is
checked separately in C200 firmware.
"""
import hashlib,json,struct
from PIL import Image
import test_color_assets as color
import test_control_flow as control
from test_control_flow import ROOT,STATE,BUFFER


def main():
    lib=(ROOT/'build/sango.lib').read_bytes();clr=(ROOT/'build/sango.clr').read_bytes()
    m=color.machine(lib,clr);count=0
    unit=255;terrain=0;name='司马懿'
    m.intercept('sango_battle_find_unit_at',2,lambda a:unit)
    m.intercept('sango_battle_terrain_at',2,lambda a:terrain)
    m.write(STATE['g_battle_roster_first'],b'\x0d')
    m.intercept('sango_load_named_text',2,lambda a:m.write(a[1],name.encode('gbk')+b'\0'))
    m.intercept('sango_render_clear_rectangle',5,lambda a:(_ for _ in ()).throw(AssertionError('Color HUD used white clear')))
    # The footer intentionally clears only the unchanged strategy summary.
    m.intercept('sango_battle_toolbar_draw',1,lambda a:None)
    m.intercept('sango_battle_summary_draw',1,lambda a:None)
    names=[]
    for terrain in range(8):
        for unit in (255,0):
            m.texts.clear();m.pixels.clear()
            m.call('sango_battle_draw_cursor_description',instruction_limit=5_000_000)
            assert len(m.texts)==1 and m.texts[0][1:4]==[3,159,212]
            label=m.texts[0][4].decode('gbk')
            if unit==255:assert len(label)==2;names.append(label)
            else:assert label==name
            count+=1
    assert len(set(names))==8
    for food in (0,1,10,9999,65535):
        for weather in range(1,6):
            m.write(STATE['g_battle_attacker_food'],struct.pack('<H',food))
            m.write(STATE['g_battle_weather'],bytes([weather]))
            m.texts.clear();m.pixels.clear();m.call('sango_battle_status_draw',instruction_limit=15_000_000)
            assert m.texts==[[color.CONTEXT+8,3,21,212,str(food).encode()]]
            canvas=Image.new('I',(240,320))
            for ctx,x,y,v in m.pixels:canvas.putpixel((x,y),v)
            assert 0xffff not in canvas.crop((21,212,69,228)).get_flattened_data()
            assert 0xffff not in canvas.crop((159,212,237,228)).get_flattened_data()
            count+=1
    # Error text shares the original single-line field and stays inside it.
    for value in ['没有目标','无法到达','诸葛亮孔明','司马懿仲达的一段长名字']:
        m.texts.clear();m.pixels.clear();m.write(BUFFER,value.encode('gbk')+b'\0')
        m.call('sango_battle_status_draw_description',BUFFER,0,instruction_limit=5_000_000)
        assert m.texts[0][:4]==[0,3,159,212] and len(m.texts[0][4])<=9
        m.texts[0][4].decode('gbk')
        assert all(x>=159 and 208<=y<232 for _,x,y,v in m.pixels);count+=1
    left=m.call('sango_battle_animation_left');top=m.call('sango_battle_animation_top')
    start=struct.unpack_from('<I',lib,15*4)[0]+12
    width,height=struct.unpack_from('<HH',lib,start)
    assert left*2+width==240 and top*2+height==208
    assert (left,top)==(55,72);count+=1
    # The real skill dispatcher must apply the same translation to backgrounds,
    # relative effect offsets, text and damage values. Compare all 30 skills to
    # a companion-disabled execution of the SAME ELF, including state/results.
    original_machine=control.Machine
    old_address=color.COLOR_ADDRESS;color.COLOR_ADDRESS=0x81800000
    def translated_machine(image):
        candidate=color.machine(lib,clr)
        for key in ['g_draw_context','g_message_context','g_game_context']:candidate.word(STATE[key],0)
        return candidate
    try:
        image=(ROOT/'build/sango.elf').read_bytes()
        for skill in range(1,31):
            control.Machine=original_machine
            before=control.run_skill(image,skill,1,2,0,0,0)
            control.Machine=translated_machine
            after=control.run_skill(image,skill,1,2,0,0,0)
            normalized=[]
            for event in after[1]:
                e=list(event)
                if e[0] in ('sango_bitmap_draw_resource','sango_animation_play_range','sango_battle_draw_damage_digits'):
                    e[1]=list(e[1])
                    x,y={'sango_bitmap_draw_resource':(2,3),'sango_animation_play_range':(4,5),'sango_battle_draw_damage_digits':(0,1)}[e[0]]
                    e[1][x]-=35;e[1][y]-=23
                if e[0]=='text':e[1]-=35;e[2]-=23
                normalized.append(e)
            assert before==(after[0],normalized,*after[2:]),skill
            count+=1
    finally:control.Machine=original_machine;color.COLOR_ADDRESS=old_address
    # Normal attacks use the same centered frame and translated damage origin.
    m=color.machine(lib,clr);draws=[];timelines=[];digits=[]
    m.intercept('sango_bitmap_draw_resource',5,lambda a:draws.append(a))
    m.intercept('sango_animation_play_range',6,lambda a:timelines.append(a))
    m.intercept('sango_battle_draw_damage_digits',3,lambda a:digits.append(a))
    m.intercept('sango_battle_roll_attack_damage',0,lambda a:123)
    m.intercept('sango_battle_damage_feedback',1,lambda a:7)
    m.intercept('sango_input_wait',2,lambda a:0)
    m.word(STATE['g_attacker_level_address'],BUFFER+16);m.word(STATE['g_defender_level_address'],BUFFER+16)
    m.word(STATE['g_defender_troops_address'],BUFFER+32)
    m.write(BUFFER+16,b'\1');m.write(STATE['g_battle_show_animations'],b'\1')
    for attacker in range(6):
        for defender in range(6):
            draws.clear();timelines.clear();digits.clear();m.write(BUFFER+32,struct.pack('<H',500))
            m.write(STATE['g_attacker_troop_type'],bytes([attacker]));m.write(STATE['g_defender_troop_type'],bytes([defender]))
            assert m.call('sango_battle_execute_normal_attack',10,instruction_limit=5_000_000)==7
            assert draws==[[16,1,55,72,0]] and timelines[0][-2:]==[55,72] and digits==[[95,112,123]]
            count+=1
    gray=color.machine(lib)
    assert gray.call('sango_battle_animation_left')==20 and gray.call('sango_battle_animation_top')==49;count+=1
    report={'passed':count,'failed':0,'bda_sha256':hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),
            'color_sha256':hashlib.sha256(clr).hexdigest(),'status_field':{'switch':'unit name or empty-tile terrain','rectangle':[159,212,78,16]},
            'animation_frame':[left,top,width,height],
            'scope':'Real compiled MIPS image-based HUD, dynamic transparent text/terrain decoding, food/weather limits, complete GBK clipping, empty/occupied tiles, one-line name/terrain switch; all 30 skill and 36 normal attack dispatches retain gameplay state/results and relative coordinates while centering the modal. SDK font pixels modeled; native sharp/transparent font pixels separately checked.'}
    (ROOT/'build/battle-ui-color-validation.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report))


if __name__=='__main__':main()

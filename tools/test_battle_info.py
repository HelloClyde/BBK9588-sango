"""Execute the production 240x320 info sheet and native weather path in MIPS.

Only SDK canvas/font/present boundaries and derived combat stats are modeled.
The real renderer, field selection, wrapping, resource strings and parser run.
"""
import hashlib,json,struct
from PIL import Image
from test_control_flow import Machine,ROOT,STATE,BUFFER
from test_color_assets import machine,CONTEXT,LIB_ADDRESS,COLOR_ADDRESS
from audit_resource_usage import record,text_items

IMAGE=(ROOT/'build/sango.elf').read_bytes()
PAGE=0x81300400

def info_machine(unit=0,terrain=0,level=7,troop=0,status=0,owned=False,fail=False):
    m=Machine(IMAGE);trace=[];texts=[]
    lib=(ROOT/'build/sango.lib').read_bytes();m.write(LIB_ADDRESS,lib)
    m.word(STATE['g_resource_package_address'],LIB_ADDRESS)
    m.word(STATE['g_character_table_address'],BUFFER+1024)
    m.write(BUFFER+1024,struct.pack('<10BH4B',0,1,level,87,91,80,0,99,70,troop,65535,0,0,30,0))
    m.write(0x81c2b280,bytes((2,3,100,80,5,0,status)))
    m.write(STATE['g_scenario_id_view2'],b'\1')
    m.word(STATE['g_game_context'],CONTEXT)
    m.word(STATE['g_message_context'],0 if owned else PAGE)
    m.intercept('sango_battle_find_unit_at',2,lambda a:unit)
    m.intercept('sango_battle_resolve_character',1,lambda a:0)
    m.intercept('sango_battle_terrain_at',2,lambda a:terrain)
    m.intercept('sango_load_named_text',2,lambda a:m.write(a[1],'司马懿'.encode('gbk')+b'\0'))
    def combat(a):
        m.write(STATE['g_attacker_level_address'],bytes([0xa5])*20)
        m.write(STATE['g_attacker_attack_view2'],struct.pack('<HH',4321,9876))
    m.intercept('sango_battle_prepare_combatant',2,combat)
    m.intercept('sango_battle_info_prepare_canvas',1,lambda a:trace.append(('canvas',a[0])))
    def text(a):
        value=m.text(a[4]);value.decode('gbk')
        assert a[0]==PAGE and a[1]==3 and 12<=a[2] and a[2]+len(value)*8<=228
        assert 12<=a[3] and a[3]+16<=315
        texts.append((a[2],a[3],value));trace.append(('text',a[0]))
    m.intercept('sango_color_sdk_text',5,text)
    m.intercept('sango_bitmap_draw_frame',7,lambda a:trace.append(('portrait',*a)))
    m.intercept('sango_render_present',1,lambda a:trace.append(('present',a[0])))
    def wait(a):
        assert a==[0,1] and trace[-1]==('present',PAGE)
        trace.append(('wait',))
        return 254
    m.intercept('sango_input_wait',2,wait)
    m.intercept('bbk_compatible_context_create',0,lambda a:0 if fail else PAGE)
    m.intercept('bbk_compatible_context_free',1,lambda a:trace.append(('free',a[0])) or 1)
    before=m.read(0x81c2b0d0,0x9a1)
    m.call('sango_battle_show_cursor_info',instruction_limit=8_000_000)
    assert m.read(0x81c2b0d0,0x9a1)==before,'Info changed game state'
    if fail:assert not trace;return texts,trace
    assert [x for x in trace if x[0]=='present']==[('present',PAGE),('present',CONTEXT)]
    assert trace[0]==('canvas',PAGE)
    assert len([x for x in trace if x[0]=='wait'])==1
    assert bool([x for x in trace if x[0]=='free'])==owned
    return texts,trace

def main():
    count=0
    for level,troop,status in [(7,0,0),(20,5,7),(255,255,255)]:
        texts,trace=info_machine(level=level,troop=troop,status=status)
        fields={(x,y):v for x,y,v in texts}
        assert fields[(12,44)]=='司马懿'.encode('gbk')
        for pos,value in [((60,118),b'87'),((172,118),b'91'),((60,146),b'100'),
                          ((172,146),b'80'),((60,174),b'4321'),((172,174),b'9876'),
                          ((60,202),b'65535'),((172,202),b'99')]:assert fields[pos]==value
        assert fields[(60,90)]==(str(level).encode() if level<20 else b'MAX')
        assert trace[-1]==('present',CONTEXT);count+=1
    manifest=json.loads((ROOT/'assets/library/manifest.json').read_text(encoding='utf8'))
    descriptions=text_items(record(manifest,1))[13:21]
    for terrain in range(8):
        texts,trace=info_machine(unit=255,terrain=terrain)
        paragraph=b''.join(v for x,y,v in texts if 90<=y<=258)
        assert paragraph==descriptions[terrain].split('：',1)[1].encode('gbk')
        assert (12,44,descriptions[terrain].split('：',1)[0].encode('gbk')) in texts
        assert all(not v.decode('gbk').startswith(tuple('。，、；：！？')) for x,y,v in texts if 90<=y<=258)
        assert not [x for x in trace if x[0]=='portrait'];count+=1
    texts,trace=info_machine(owned=True);assert trace[-1]==('free',PAGE);count+=1
    info_machine(owned=True,fail=True);count+=1

    lib=(ROOT/'build/sango.lib').read_bytes();clr=(ROOT/'build/sango.clr').read_bytes()
    _,status_offset,_,_,_,_,_=struct.unpack_from('<8sIIIIII',clr,len(clr)-32)
    tag,offset,size,width,height,source,crc=struct.unpack_from('<8sIIIIII',clr,status_offset-32)
    assert (tag,size,width,height)==(b'SGWTH01\0',3240,18,18)
    m=machine(lib,clr)
    for frame in range(5):
        assert m.call('sango_color_native_weather',LIB_ADDRESS+source,frame)==COLOR_ADDRESS+offset+frame*648
        image=Image.open(ROOT/f'assets/color/battle-ui/weather/weather-{frame+1:02}-18x18.png').convert('RGBA')
        values=struct.unpack_from('<324H',clr,offset+frame*648)
        for (r,g,b,a),value in zip(image.get_flattened_data(),values):
            assert value==(((((r>>3)<<11)|((g>>2)<<5)|(b>>3)) or 1) if a else 0)
        m.pixels.clear();m.write(STATE['g_battle_weather'],bytes([frame+1]))
        m.call('sango_battle_status_draw_weather',CONTEXT+8,instruction_limit=10_000_000)
        # The first432 pixels restore the18x24 background; remaining pixels
        # are copied from the18x18 sprite without resampling, skipping alpha0.
        expected=[(CONTEXT+8,112+x,211+y,values[y*18+x]) for y in range(18) for x in range(18) if values[y*18+x]]
        assert m.pixels[432:]==expected;count+=1
    for original,frame in [(LIB_ADDRESS+source+1,0),(LIB_ADDRESS+source,5)]:
        assert m.call('sango_color_native_weather',original,frame)==0;count+=1
    for field,value in [(8,offset+1),(8,32),(12,3238),(16,17),(20,19),(24,source+1),(28,crc^1)]:
        bad=bytearray(clr);struct.pack_into('<I',bad,status_offset-32+field,value)
        m.write(COLOR_ADDRESS,bad)
        assert m.call('sango_color_use_buffer',COLOR_ADDRESS,len(bad),len(lib),instruction_limit=80_000_000)==0
        assert m.call('sango_color_native_weather',LIB_ADDRESS+source,0)==0;count+=1
    report={'passed':count,'failed':0,'bda_sha256':hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),
            'color_sha256':hashlib.sha256(clr).hexdigest(),'weather_frames':5,'weather_native_size':[18,18],
            'info_font':16,'info_presentation':'One completed off-screen page, then explicit dismissal and battlefield restore.',
            'scope':'Real compiled MIPS info sheet fields/resources/GBK wrapping, MAX/invalid values, ownership failure and combat-state restoration; actual native-weather parser/CRC/bounds/source/alpha and18x18 pixel copying. SDK canvas/font/present boundaries and derived combat stats modeled; native C200 separately tested.'}
    (ROOT/'build/battle-info-validation.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps(report))

if __name__=='__main__':main()

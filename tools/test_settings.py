"""Execute settings, persistence and music controls in production MIPS."""
from pathlib import Path
import hashlib,json,struct
from test_control_flow import Machine,ROOT,BUFFER,STATE
from test_touch_input import event,install_events
from test_music import Player,wave_fixture

IMAGE=(ROOT/'build/sango.elf').read_bytes()
cases=[]
def check(name,ok):
    assert ok,name
    cases.append({'name':name,'passed':True})

def controller(events):
    m=Machine(IMAGE);draws=[];credits=[];writes=[]
    m.intercept('sango_settings_draw',1,lambda a:draws.append(a[0]))
    m.intercept('sango_menu_show_credits',0,lambda a:credits.append(1))
    m.intercept('sango_settings_sdk_read',2,lambda a:0)
    m.intercept('sango_settings_sdk_write',2,lambda a:writes.append(m.read(a[0],a[1])) or a[1])
    m.intercept('sango_touch_cancel',0,lambda a:None)
    m.write(BUFFER,b'A:\\games\\sango.lib\0');m.call('sango_settings_load',BUFFER)
    pending=install_events(m,events)
    m.call('sango_settings_show')
    assert not pending
    return m,draws,credits,writes

def main():
    m,draws,credits,writes=controller([event(5,key=1)])
    check('Escape returns without changing or writing preferences',not writes and m.call('sango_music_is_enabled')==1 and m.call('sango_music_get_volume')==8)
    m,_,_,writes=controller([event(11,100,90),event(11,190,175),event(11,120,280)])
    check('Touch toggle and plus apply before returning',m.call('sango_music_is_enabled')==0 and m.call('sango_music_get_volume')==9)
    check('Settings persist a versioned checksummed record',writes==[b'SGS\1\0\11\0\xac'])
    saved=writes[0]
    fresh=Machine(IMAGE)
    fresh.write(BUFFER,b'B:/games/sango.lib\0')
    fresh.intercept('sango_settings_sdk_read',2,lambda a:fresh.write(a[0],saved) or len(saved))
    fresh.call('sango_settings_load',BUFFER)
    check('A new application instance restores off and90percent',fresh.call('sango_music_is_enabled')==0 and fresh.call('sango_music_get_volume')==9)
    for pos in (0,3,4,5,6,7):
        bad=bytearray(saved);bad[pos]^=128
        test=Machine(IMAGE);test.write(BUFFER,b'sango.lib\0')
        test.intercept('sango_settings_sdk_read',2,lambda a:test.write(a[0],bad) or len(bad))
        test.call('sango_settings_load',BUFFER)
        check(f'Corrupt settings byte{pos} cannot change defaults',test.call('sango_music_is_enabled')==1 and test.call('sango_music_get_volume')==8)
    for keys,enabled,volume in [([0x1c],0,8),([0x6c,0x6a],1,9),([0x6c]+[0x69]*12,1,0),([0x6c]+[0x6a]*12,1,10)]:
        m,_,_,_=controller([*[event(5,key=k) for k in keys],event(5,key=1)])
        check(f'Keyboard actions{keys} respect music and volume bounds',m.call('sango_music_is_enabled')==enabled and m.call('sango_music_get_volume')==volume)
    m,draws,credits,writes=controller([event(5,key=0x6c),event(5,key=0x6c),event(5,key=0x1c),event(5,key=1)])
    check('Keyboard credits returns to the same settings page',len(credits)==1 and draws[-1]==2 and not writes)
    m,_,credits,_=controller([event(11,100,230),event(5,key=1)])
    check('Touch credits is the secondary credits entry',credits==[1])
    for ev in [event(11,0,90),event(11,120,175),event(11,90,260),event(12,100,90,key=1),event(13,100,90)]:
        m,_,credits,writes=controller([ev,event(5,key=1)])
        check(f'Outside and drag event{ev} never activate a control',not credits and not writes)

    # Actual paint controller: native-font strings are dynamic state only.
    for level,wanted in [(0,b'0%'),(1,b'10%'),(8,b'80%'),(10,b'100%')]:
        m=Machine(IMAGE);texts=[];resources=[]
        m.call('sango_music_set_volume',level)
        for name,count in [('sango_ui_paint_begin',0),('sango_ui_paint_end',0),('sango_display_draw_rectangle',7)]:m.intercept(name,count,lambda a:None)
        m.intercept('sango_bitmap_draw_resource',5,lambda a:resources.append(a[0]))
        m.intercept('sango_ruler_sdk_text',4,lambda a:texts.append(m.text(a[2])))
        m.call('sango_settings_draw',1)
        check(f'Paint uses native settings resource and exact percentage{wanted}',resources==[78] and texts==['开'.encode('gbk'),wanted])

    raw=(ROOT/'assets/music/runtime/menu.wav').read_bytes();wav=wave_fixture(raw)
    p=Player({'menu.wav':wav,'strategy.wav':wav,'battle.wav':wav})
    p.m.intercept('sango_music_sdk_audio_volume',1,lambda a:p.log.append(('volume',a[0])))
    p.scene(1);check('Music initially streams with the existing default',bool(p.handles) and bool(p.output))
    p.m.call('sango_music_set_enabled',0);at=len(p.output)
    p.scene(3)
    for _ in range(5):p.poll()
    check('Disabled music stops file decoder timer and writes across scene changes',not p.handles and len(p.output)==at and p.log[-1][0]=='close')
    p.m.call('sango_music_set_enabled',1)
    check('Enable resumes the most recently requested scene',bool(p.handles) and any(x==('open','battle.wav') for x in p.log))
    p.m.call('sango_music_set_volume',10)
    check('Live volume changes reach the SDK stream',('volume',10) in p.log)
    p.m.call('sango_music_set_volume',0);at=len(p.output)
    for _ in range(3):p.poll()
    check('Zero volume suspends decoding instead of silently consuming CPU',not p.handles and len(p.output)==at)
    p.m.call('sango_music_set_volume',8)
    check('Raising zero volume resumes the requested battle track',bool(p.handles))
    p.stop()
    # Original save-initialized bytes are independent of all preferences.
    import io
    from elftools.elf.elffile import ELFFile
    data=ELFFile(io.BytesIO(IMAGE)).get_section_by_name('.sango_data').data()
    check('Original initialized/save data remains exact',hashlib.sha256(data).hexdigest()=='970e2121b60aa27d340563a249d63df2c67ce7a006ee8cb4c6cddd0cf0f3301f')
    report={'passed':len(cases),'failed':0,'bda_sha256':hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),
            'scope':'Actual compiled MIPS settings UI, preference encode/validation/reload, keyboard/touch/drag boundaries and full streaming lifecycle. SDK file/audio/font/input boundaries modeled; native UI checked separately.','cases':cases}
    (ROOT/'build/settings-validation.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in report.items() if k!='cases'}))

if __name__=='__main__':main()

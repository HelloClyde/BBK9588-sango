"""Exercise production MIPS gestures and touch-enabled menu/map controllers."""
from pathlib import Path
import hashlib,json,struct
from elftools.elf.elffile import ELFFile
from test_control_flow import Machine,ROOT,STATE,BUFFER,run_battle_input,run_number_selection,run_list_selection

IMAGE=(ROOT/'build/sango.elf').read_bytes()

def event(kind,x=0,y=0,key=0):
    return (kind,key&0xffffffff,x&0xffff,y&0xffff)

def install_events(m,events,name='sango_input_next_event'):
    pending=list(events)
    def next_event(args):
        assert pending,'Controller consumed all input without completing'
        m.write(args[0],struct.pack('<IIHH',*pending.pop(0)))
        return 1
    m.intercept(name,1,next_event)
    return pending

def main():
    checks=0;m=Machine(IMAGE);sample=[0,0];reads=[];clock=[0]
    m.intercept('sango_touch_sdk_ticks',0,lambda a:clock[0])
    timer_calls=[];m.intercept('sango_touch_sdk_timer',1,lambda a:timer_calls.append(a[0]))
    def position(args):
        reads.append(tuple(sample));m.write(args[0],struct.pack('<H',sample[0]&65535));m.write(args[1],struct.pack('<H',sample[1]&65535))
    m.intercept('sango_touch_sdk_position',2,position)
    def raw(kind,x=0,y=0):
        if kind in (1,2):sample[:]=[x,y]
        m.write(BUFFER,struct.pack('<IIHH',*event(kind,x,y)))
        emitted=m.call('sango_touch_process',BUFFER)
        return emitted,struct.unpack('<IIHH',m.read(BUFFER,12))
    def tap(x,y):
        assert raw(1,x,y)[0]==0
        emitted,packet=raw(2,x,y);assert emitted==1 and packet[0]==11
        return packet
    # Real window callback consumes coordinates before firmware default key synthesis.
    for kind in (1,2):
        assert m.call('sango_window_proc',123,kind,0,319<<16|239)==1
        assert struct.unpack('<I',m.read(STATE['g_native_event_data'],4))[0]==319<<16|239
        checks+=1
    for x,y in [(0,0),(239,319),(120,255),(120,256),(57,49),(182,290)]:
        packet=tap(x,y);assert packet[2:]==(x,y);checks+=1
    assert raw(2,120,100)[0]==0;checks+=1
    for invalid in [(-1,100),(240,100),(100,-1),(100,320)]:
        raw(1,*invalid);assert raw(2,*invalid)[0]==0;checks+=1
    raw(1,100,100);assert raw(1,107,107)[0]==0
    assert raw(2,107,107)[1][0]==11;checks+=1
    raw(1,100,100);assert raw(1,108,100)[1][0]==12
    assert raw(2,100,100)[1][0]==13;checks+=1
    raw(1,100,100);raw(1,-1,100);raw(1,100,100)
    assert raw(2,100,100)[0]==0;checks+=1
    before=len(reads);assert raw(0x144)[0]==0 and len(reads)==before;checks+=1
    raw(1,80,80);sample[:]=[80,80]
    for _ in range(12):assert raw(0x144)[0]==0
    assert raw(2,80,80)[1][0]==11;checks+=1
    raw(1,80,80);clock[0]+=32
    assert raw(2,80,80)[1][0]==14;checks+=1
    raw(1,100,100);sample[:]=[110,100]
    assert raw(0x144)[1][0]==12
    assert raw(2,110,100)[1][0]==13;checks+=1
    raw(1,100,100);m.call('sango_touch_cancel');assert raw(2,100,100)[0]==0;checks+=1
    raw(1,200,100);sample[:]=[80,100]
    m.write(BUFFER,struct.pack('<IIHH',*event(2,200,100)))
    assert m.call('sango_touch_process',BUFFER)==1
    coalesced=struct.unpack('<IIHH',m.read(BUFFER,12))
    assert coalesced[0]==13 and coalesced[2:]==(80,100)
    assert coalesced[1]&65535==(-120)&65535;checks+=1
    assert timer_calls.count(1)==timer_calls.count(0);checks+=1
    # Native event adapter returns a single release action, preserves full Y,
    # and keeps queued keyboard events and the legacy map-width slot intact.
    m.write(STATE['g_battle_map_width_aux_view2'],b'\x26')
    native_queue=install_events(m,[event(1,239,319),event(2,239,319)],'sango_input_poll_native_event')
    sample[:]=[239,319]
    m.call('sango_input_next_event',BUFFER);assert struct.unpack('<IIHH',m.read(BUFFER,12))[::2]==(11,239)
    assert m.read(STATE['g_battle_map_width_aux_view2'],1)==b'\x26';checks+=1
    native_queue.extend([event(1,60,70),event(0x10,key=0x67),event(1,65,70),event(2,60,70),event(0x10,key=0x1c)])
    m.call('sango_input_next_event',BUFFER);assert struct.unpack('<II',m.read(BUFFER,8))==(5,0x67)
    m.call('sango_input_next_event',BUFFER);assert struct.unpack('<II',m.read(BUFFER,8))==(5,0x1c);checks+=1
    native_queue.extend([event(0x144,key=2),event(0x144,key=1)])
    m.call('sango_input_next_event',BUFFER)
    assert struct.unpack('<II',m.read(BUFFER,8))==(6,0) and not native_queue;checks+=1
    # Four main/scenario image rectangles: all corners and inactive gutters.
    for bg,left,width,tops in [(44,57,126,[49,111,173,234]),(45,42,157,[49,110,171,232])]:
        for row,top in enumerate(tops):
            for x,y in [(left,top),(left+width-1,top+56),(left+width//2,top+28)]:
                m.write(BUFFER,struct.pack('<IIHH',*event(11,x,y)))
                assert m.call('sango_touch_menu_row',bg,BUFFER)==row;checks+=1
        for x,y in [(left-1,80),(left+width,80),(left,48),(left,319)]:
            m.write(BUFFER,struct.pack('<IIHH',*event(11,x,y)))
            assert m.call('sango_touch_menu_row',bg,BUFFER)==0xffffffff;checks+=1
    # A real animated menu also handles taps returned through its animation wait.
    for bg,x,tops in [(44,120,[49,111,173,234]),(45,120,[49,110,171,232])]:
        for row,top in enumerate(tops):
            mm=Machine(IMAGE);mm.record('sango_bitmap_draw_resource',5)
            install_events(mm,[event(11,x,top+20)])
            assert mm.call('sango_menu_select_animated',bg,100 if bg==44 else 104)==row;checks+=1
    for row,top in enumerate([49,111,173,234]):
        mm=Machine(IMAGE);mm.record('sango_bitmap_draw_resource',5)
        mm.intercept('sango_touch_sdk_ticks',0,lambda a:0)
        mm.intercept('sango_touch_sdk_timer',1,lambda a:None)
        mm.intercept('sango_touch_sdk_position',2,lambda a:mm.write(a[0],struct.pack('<H',120)) or mm.write(a[1],struct.pack('<H',top+20)))
        mm.write(BUFFER,struct.pack('<IIHH',*event(1,120,top+20)));mm.call('sango_touch_process',BUFFER)
        mm.write(BUFFER,struct.pack('<IIHH',*event(2,120,top+20)));mm.call('sango_touch_process',BUFFER)
        install_events(mm,[event(6)])
        mm.intercept('sango_animation_play_resource',1,lambda a:254)
        assert mm.call('sango_menu_select_animated',44,100)==row;checks+=1
    # Real option panel, including scrolled row indexing, blank rows, cancellation.
    for selected,top,point,result in [(0,40,(30,41),0),(0,40,(30,65),2),(5,40,(30,41),4),(0,270,(30,283),1),(0,40,(0,0),255)]:
        mm=Machine(IMAGE);mm.write(BUFFER,struct.pack('<4H',20,top,44,top+36))
        mm.write(BUFFER+100,b'AAAABBBBCCCCDDDDEEEEFFFFGGGG\0')
        mm.intercept('bbk_strlen',1,lambda a:len(mm.text(a[0])))
        for fn,n in [('sango_display_fill_gray_rectangle',6),('sango_display_fill_rectangle',6),('sango_display_draw_rectangle',7),('sango_text_draw_legacy',3),('sango_display_invert_rectangle',5),('sango_display_put_gray_pixel',4)]:mm.record(fn,n)
        install_events(mm,[event(11,*point)])
        assert mm.call('sango_ui_choose_option',BUFFER,selected,BUFFER+100)==result;checks+=1
    # Strategy painter models only drawing; production hit transforms, loops,
    # keyboard and selection return paths execute, in gray and RGB layouts.
    for color in (0,1):
        width,height=(240,232) if color else (224,224)
        for x,y in [(0,0),(width-1,height-1),(width//2,height//2)]:
            mm=Machine(IMAGE);mm.write(BUFFER,bytes([2,1,4,3]));draws=[]
            mm.intercept('sango_color_is_loaded',0,lambda a:color)
            def draw(a):
                state=list(mm.read(a[0],4));draws.append(state);return 7 if len(draws)>1 else 0
            mm.intercept('sango_strategy_draw_map',2,draw);mm.record('sango_render_clear_rectangle',5)
            install_events(mm,[event(11,x,y)])
            assert mm.call('sango_strategy_select_city',BUFFER)==6
            assert draws[-1][2:]==[2+x*7//width,1+y*7//height];checks+=1
    for color in (0,1):
        mm=Machine(IMAGE);mm.write(BUFFER,bytes([0,0,3,3]));draws=[]
        mm.intercept('sango_color_is_loaded',0,lambda a:color)
        mm.intercept('sango_strategy_draw_map',2,lambda a:draws.append(list(mm.read(a[0],4))) or 7)
        mm.record('sango_render_clear_rectangle',5)
        pending=install_events(mm,[event(12,30,100,key=(-100)&65535),event(13,30,100),event(5,key=1)])
        assert mm.call('sango_strategy_select_city',BUFFER)==255 and not pending
        assert draws[-1][0]==(700//(240 if color else 224));checks+=1
    # Direct battle taps select a unit/destination/target through the original
    # command paths; none of these tests bypasses the production input loop.
    for mode in (1,2,3):
        for x,y in [(0,0),(239,207),(120,112)]:
            events=[event(11,x,y)]
            result,trace,state,pending=run_battle_input(IMAGE,mode,(7,7),events,None)
            assert result==0 and pending==0
            assert state[STATE['g_battle_cursor_x']-0x81c2b0e4]==x//16
            assert state[STATE['g_battle_cursor_y']-0x81c2b0e4]==y//16;checks+=1
    for mode in (1,2,3):
        result,trace,state,pending=run_battle_input(IMAGE,mode,(7,7),[event(12,40,80,key=(-64)&65535),event(13,40,80),event(11,16,16)],None)
        assert result==0 and pending==0
        assert state[STATE['g_battle_viewport_x']-0x81c2b0e4]==1
        assert state[STATE['g_battle_cursor_x']-0x81c2b0e4]==2;checks+=1
    # Panning never emits confirmation and cannot start in footer/summary.
    for world,grid,screen in [((12,9),(7,7),(240,232)),((12,9),(7,7),(224,224)),((30,30),(15,13),(240,208))]:
        for dx,dy in [(-120,0),(120,0),(0,-100),(0,100),(-80,-80)]:
            m.call('sango_touch_cancel');raw(2,0,0);raw(1,120,110);emit,p=raw(1,120+dx,110+dy)
            if not emit:
                assert raw(2,120+dx,110+dy)[0]==0
                checks+=1
                continue
            m.write(BUFFER+40,bytes([0,0,3,3]));m.write(BUFFER+48,bytes(12));m.write(BUFFER,struct.pack('<IIHH',*p))
            m.call('sango_touch_pan_map',BUFFER,BUFFER+40,*world,*grid,*screen,BUFFER+48)
            state=list(m.read(BUFFER+40,4))
            assert 0<=state[0]<=world[0]-grid[0] and 0<=state[1]<=world[1]-grid[1]
            assert state[0]<=state[2]<state[0]+grid[0] and state[1]<=state[3]<state[1]+grid[1]
            assert raw(2,120+dx,110+dy)[1][0]==13;checks+=1
    # An empty edge tap moves only the cursor, never the viewport.
    for color in (0,1):
        mm=Machine(IMAGE);mm.write(BUFFER,bytes([2,1,4,3]));draws=[]
        mm.intercept('sango_color_is_loaded',0,lambda a:color)
        mm.intercept('sango_strategy_draw_map',2,lambda a:draws.append(list(mm.read(a[0],4))) or 0)
        mm.record('sango_render_clear_rectangle',5)
        width,height=(240,232) if color else (224,224)
        pending=install_events(mm,[event(11,width-1,height//2),event(5,key=1)])
        assert mm.call('sango_strategy_select_city',BUFFER)==255 and not pending
        assert list(mm.read(BUFFER,4))==[2,1,8,4];checks+=1
    # Exact numeric values match keyboard entry, with touch digit selection,
    # plus/minus/confirm/cancel and upper/lower bounds.
    for initial,maximum,events,expected in [(10,99,[event(11,100,192),event(11,140,192)],11),(0,99,[event(11,50,192),event(11,140,192)],0),(99,99,[event(11,100,192),event(11,140,192)],99),(10,99,[event(11,126,159),event(11,100,192),event(11,140,192)],20),(10,99,[event(11,182,192)],65535)]:
        # Original key model already has deterministic text/format SDK boundaries;
        # the new controls are a separate native render surface.
        result,_,pending=run_number_selection(IMAGE,initial,maximum,events)
        assert result==expected and pending==0;checks+=1
    for kind in ('item','character'):
        for row in range(4):
            result,*_=run_list_selection(IMAGE,kind,6,(10,10,180,100),[event(11,30,23+row*12)],2)
            assert result==row;checks+=1
    for mode in (0,1):
        for row in range(3):
            mm=Machine(IMAGE);mm.record('sango_save_draw_slots',0);mm.record('sango_display_invert_rectangle',5)
            requests=[]
            mm.intercept('sango_save_write_slot' if mode==0 else 'sango_save_load_slot',1,lambda a:requests.append(a[0]) or 1)
            install_events(mm,[event(11,100,102+row*27+5)])
            assert mm.call('sango_save_choose_slot',mode)==row and requests==[row];checks+=1
    with (ROOT/'build/sango.elf').open('rb') as f:
        elf=ELFFile(f);data=elf.get_section_by_name('.sango_data').data();extension=elf.get_section_by_name('.sango_touch')
        assert len(data)==45536 and hashlib.sha256(data).hexdigest()=='970e2121b60aa27d340563a249d63df2c67ce7a006ee8cb4c6cddd0cf0f3301f'
        assert extension['sh_addr']>=0x81c2ba71 and extension['sh_addr']+extension['sh_size']<=0x81c30000;checks+=1
    report={'passed':checks,'failed':0,'bda_sha256':hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),'scope':'Actual compiled MIPS window callback, gesture recognizer, event normalization, full 16-bit coordinates, duplicate/up/cancel/bounds/timer sampling, image menu hitboxes/controllers, popup rows, strategy clicks, battle mode1/2/3 taps, drag clamps, numeric and roster selection. SDK queue/coordinate/pixel boundaries modeled. Initialized legacy/save data unchanged; touch extension outside legacy state. Native firmware tested separately.'}
    (ROOT/'build/touch-input-validation.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report))

if __name__=='__main__':main()

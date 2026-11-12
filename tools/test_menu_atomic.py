"""Verify the first visible popup contains its frame and every content row.

Run actual MIPS controllers. Model only drawing/input/SDK surface boundaries;
assert every draw (including the outer rectangle) precedes the first publish
on the compatible canvas, and input is never awaited while paint is active.
"""
import hashlib,json,struct
from test_control_flow import Machine,ROOT,STATE,BUFFER
from test_menu_input import IMAGE,WINDOW,CANVAS,context,surfaces,drawing,input_queue
from test_touch_input import event


def exercise(image,kind):
    m=Machine(image);trace=surfaces(m);drawing(m,trace)
    m.intercept('sango_resource_read_text',3,lambda a:m.write(a[2],b'TEXT\0'))
    m.intercept('sango_load_named_text',2,lambda a:m.write(a[1],b'NAME\0'))
    m.intercept('sango_city_read_name',2,lambda a:m.write(a[1],b'CITY\0'))
    m.intercept('bbk_strcat',2,lambda a:m.write(a[0],m.text(a[0])+m.text(a[1])+b'\0') or a[0])
    m.intercept('sango_bitmap_draw_frame_screen',6,lambda a:trace.append(('picture',context(m),a)))
    m.intercept('sango_text_draw_native',4,lambda a:trace.append(('text',context(m),a[:2],m.text(a[2]))))
    def wait(a):
        assert context(m)==WINDOW,'Dialog waits with an unpublished canvas'
        trace.append(('wait',))
    m.intercept('sango_input_wait',2,wait)
    if kind in ('character','item'):
        m.write(BUFFER,bytes(range(20)))
        for suffix,n in [('header',4),('row',5)]:
            def draw(a,suffix=suffix):
                trace.append((suffix,context(m),a));return a[0]+2 if suffix=='header' else 0
            m.intercept(f'sango_ui_draw_{kind}_{suffix}',n,draw)
        input_queue(m,trace,[event(5,key=1)])
        m.call(f'sango_ui_select_{kind}',BUFFER,20,4,2,235,181)
    elif kind in ('food','money','troop'):
        m.intercept('sango_touch_draw_number_controls',0,lambda a:trace.append(('controls',context(m))))
        input_queue(m,trace,[event(5,key=1)])
        m.call(f'sango_ui_input_{kind}_amount',123,9999)
    elif kind=='city-details':
        m.intercept('sango_city_format_attribute',4,lambda a:m.write(a[2],b'VALUE\0'))
        input_queue(m,trace,[event(5,key=1)])
        m.call('sango_ui_show_city_details',0)
    elif kind=='message':
        m.write(BUFFER,b'FULL MESSAGE\0');m.call('sango_ui_show_message',BUFFER,1)
    else:
        m.word(STATE['g_scratch_buffer_address'],BUFFER+1024)
        m.intercept('sango_resource_item',3,lambda a:BUFFER+4096)
        m.intercept('sango_render_present',1,lambda a:None)
        m.intercept('sango_text_draw_wrapped_box',3,lambda a:trace.append(('wrapped',context(m))))
        m.intercept('sango_text_draw_centered',3,lambda a:trace.append(('text',context(m),a[:2],m.text(a[2]))))
        m.intercept('sango_render_clear_rectangle',5,lambda a:None)
        m.intercept('sango_text_draw_context',4,lambda a:None)
        if kind=='character-message':
            m.write(BUFFER,b'MESSAGE\0');m.call('sango_ui_show_character_message',0,BUFFER)
        elif kind=='city-event':
            m.write(STATE['g_first_city_governor'],b'\x01')
            m.intercept('sango_city_format_status',4,lambda a:m.write(a[1],b'STATUS\0'))
            m.call('sango_ui_show_city_event',0,0,0,0)
        else:
            m.call('sango_strategy_show_'+kind.replace('-','_'),0,0)
    return m,trace


def complete(trace):
    draws=[t for t in trace if t[0] not in ('snapshot','present','free','input','wait','sango_display_invert_rectangle')]
    return bool(draws) and all(t[1]==CANVAS for t in draws) and sum(t[0]=='present' for t in trace)==1


def main():
    cases=[]
    def check(name,ok):
        assert ok,name;cases.append({'name':name,'passed':True})
    kinds=['character','item','food','money','troop','city-details','message','character-message','city-event','army-attack','armies-engage','battle-victory','battle-defeat']
    # Roster and numeric entry must include the outer frame, not just text.
    for kind in kinds:
        m,trace=exercise(IMAGE,kind)
        check(kind+': frame and all content are offscreen until one publish',complete(trace))
        check(kind+': no pending paint or redirected context after input',context(m)==WINDOW and m.call('sango_ui_paint_active')==0)
        if kind in ('food','money','troop'):
            first=next(i for i,t in enumerate(trace) if t[0]=='present')
            check(kind+': first publish contains buttons and initial digits',any(t[0]=='controls' for t in trace[:first]) and any(t[0]=='text' and t[-1]==b'0123' for t in trace[:first]))
    # Exercise the real SDK guard/redraw wrappers, rather than mocking these
    # above the point at which C200 used to reveal the unfinished rectangle.
    m=Machine(IMAGE);trace=surfaces(m);native=[]
    m.symbols=dict(m.symbols)
    table=BUFFER+0x8000
    m.word(0x81c00004,table)
    for offset,name,count in [(0x74,'native_guard',1),(0xe0,'native_redraw',3)]:
        address=BUFFER+0x9000+offset
        m.word(table+offset,address);m.symbols[name]=address
        m.intercept(name,count,lambda a,name=name:native.append((name,a)))
    def flush():
        m.call('sango_ui_paint_guard',1);m.call('sango_ui_paint_redraw');m.call('sango_ui_paint_guard',0)
    flush();check('Outside a modal, SDK guard/redraw still reach firmware',len(native)==3)
    m.word(STATE['g_aux_context'],CANVAS)
    copies=[]
    m.intercept('sango_color_sdk_restore',6,lambda a:copies.append(a))
    m.call('sango_ui_paint_begin');m.call('sango_ui_paint_begin')
    flush();check('Offscreen nested paint suppresses every intermediate firmware flush',len(native)==3)
    check('Auxiliary canvas is reused without allocating a snapshot',not trace and copies==[[WINDOW,0,0,239,319,CANVAS]])
    m.call('sango_ui_paint_end');flush()
    check('Inner scope cannot reenable window refresh',len(native)==3 and not trace)
    m.call('sango_ui_paint_end')
    check('Borrowed canvas is published once and never freed',trace==[('present',)] and context(m)==WINDOW)
    flush();check('Closing the complete popup restores normal firmware flushing',len(native)==6)
    for conflict in ('g_game_context','g_message_context'):
        m=Machine(IMAGE);trace=surfaces(m)
        m.word(STATE['g_aux_context'],CANVAS);m.word(STATE[conflict],CANVAS)
        m.call('sango_ui_paint_begin');m.call('sango_ui_paint_end')
        check('Auxiliary alias with '+conflict+' cannot overwrite backing storage',trace==[('snapshot',),('present',),('free',)])
    before=ROOT/'build/menu-atomic-native/before.elf'
    if before.exists():
        for kind in ('character','item','food','city-details','message'):
            _,trace=exercise(before.read_bytes(),kind)
            check('Pre-fix '+kind+': reproduces drawing frame before complete popup',not complete(trace))
    report={'passed':len(cases),'failed':0,'bda_sha256':hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),'scope':'Actual compiled MIPS modal controllers; all frame/content draws must target compatible canvas before a single publish and before input. Native physical LCD sampled separately. Optional old ELF reproduces early-frame defect. No physical-device latency claim.','cases':cases}
    (ROOT/'build/menu-atomic-validation.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps({k:v for k,v in report.items() if k!='cases'}))

if __name__=='__main__':main()

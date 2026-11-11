"""Execute first-frame, first-input and incremental faction-page regressions."""
import hashlib,json,struct
from test_control_flow import ROOT,STATE,BUFFER
from test_color_assets import machine,CONTEXT
from test_touch_input import event,install_events

LIB=(ROOT/'build/sango.lib').read_bytes();CLR=(ROOT/'build/sango.clr').read_bytes()
WINDOW=CONTEXT;AUX=CONTEXT+12;ALLOC=CONTEXT+16

def setup(events,aux=AUX,message=CONTEXT+4,allocation=ALLOC):
    m=machine(LIB,CLR);ops=[];pictures=[];texts=[];presents=[];allocations=[];frees=[];guards=[]
    m.word(STATE['g_aux_context'],aux);m.word(STATE['g_message_context'],message)
    m.word(STATE['g_character_table_address'],0x81100000)
    m.word(STATE['g_scratch_buffer_address'],BUFFER+4096)
    m.word(STATE['g_army_slot_used_address'],BUFFER+8000)
    m.word(STATE['g_order_queue_address'],BUFFER+9000)
    m.word(STATE['g_move_costs_address'],BUFFER+1024)
    m.word(STATE['g_temp_character_ids_address'],BUFFER+1536)
    count=m.call('sango_scenario_load',1,BUFFER+1536)
    def picture(a):pictures.append(a);ops.append(('picture',a))
    def text(a):texts.append([*a[:3],m.text(a[3]),a[4]]);ops.append(('text',a))
    def present(a):
        presents.append(a);ops.append(('present',a))
        if len(presents)==1:
            assert len(texts)>=11,'First frame published before names and selected name'
            assert {tuple(p[3:5]) for p in pictures}>={(240,320),(84,64),(48,48),(56,18)}
        assert a[0]!=WINDOW or not allocation,'Expected explicit borrowed canvas'
    m.intercept('sango_ruler_sdk_picture',6,picture)
    m.intercept('sango_ruler_sdk_text_at',5,text)
    m.intercept('sango_ruler_sdk_present',5,present)
    m.intercept('sango_color_sdk_restore',6,lambda a:ops.append(('restore',a)))
    m.intercept('sango_color_sdk_snapshot',1,lambda a:allocations.append(a) or allocation)
    m.intercept('sango_color_sdk_snapshot_free',1,lambda a:frees.append(a[0]))
    m.intercept('sango_color_sdk_guard',1,lambda a:guards.append(a[0]))
    pending=list(events)
    def input(a):
        assert presents,'Input waited before a complete first frame'
        assert m.read(STATE['g_draw_context'],4)==struct.pack('<I',WINDOW),'Window handle changed while waiting'
        assert pending,'Unexpected delay/input consumption'
        m.write(a[0],struct.pack('<IIHH',*pending.pop(0)))
        ops.append(('input',))
    m.intercept('sango_input_next_event',1,input)
    return m,count,pending,ops,pictures,texts,presents,allocations,frees,guards

def main():
    cases=[]
    def check(name,ok):assert ok,name;cases.append({'name':name,'passed':True})
    key=lambda k:event(5,key=k)
    # No synthetic warm-up event: the first real tap must already work.
    for action,wanted in [(event(11,170,280),5),(event(11,60,280),255),(key(0x1c),5),(key(1),255)]:
        m,count,pending,ops,pictures,texts,presents,allocs,frees,guards=setup([action])
        result=m.call('sango_menu_choose_ruler',count,instruction_limit=3_000_000)
        check(f'First input{action} immediately returns correct result',result==wanted and not pending)
        check(f'First input{action} sees exactly one complete first commit',len(presents)==1 and presents[0][2]&1)
        check(f'First input{action} renders only to borrowed offscreen surfaces',all(p[0]!=WINDOW for p in pictures) and all(t[0]!=WINDOW for t in texts))
        check(f'First input{action} allocates and frees no page snapshots',not allocs and not frees)
    m,count,pending,ops,pictures,texts,presents,allocs,frees,guards=setup([event(11,40,141),event(11,170,280)])
    wanted=m.read(BUFFER+1536+4,1)[0]
    check('First immediate name tap previews row4 and next tap confirms it',m.call('sango_menu_choose_ruler',count)==wanted and len(presents)==2)
    check('Row preview never repaints the full static background',sum(p[3:5]==[240,320] for p in pictures)==1)
    check('First preview uses one dirty transaction, preserving old frame until ready',not(presents[1][2]&1) and presents[1][2]==14)
    # Adjacent list updates copy two18px rows, map and two preview rectangles.
    m,count,pending,ops,pictures,texts,presents,allocs,frees,guards=setup([key(0x6c),key(0x1c)])
    m.call('sango_menu_choose_ruler',count)
    update=presents[1]
    pixels=56*(update[4]-update[3]+1)+84*64+63*55+113*20
    check('Adjacent preview submits exactly the two affected rows',update[3:5]==[64,99])
    check('Adjacent window copy budget is13117pixels instead of76800',pixels==13117)
    check('Switching adds no whole-window snapshots or per-pixel image drawing',not allocs and not frees and not m.pixels)
    check('Bulk picture calls stay bounded to static art plus highlight and portrait',len(pictures)==6)
    m,count,pending,ops,pictures,texts,presents,allocs,frees,guards=setup([key(0x6c)]*12+[key(1)])
    m.call('sango_menu_choose_ruler',count)
    check('Scroll never submits a full-window redraw after the first frame',len(presents)==13 and all(not(p[2]&1) for p in presents[1:]))
    check('Scroll only refreshes the fixed ten-row list bounds',all(64<=p[3]<=p[4]<=243 for p in presents[1:]))
    m,count,pending,ops,pictures,texts,presents,allocs,frees,guards=setup([event(6),event(6),key(1)])
    m.call('sango_menu_choose_ruler',count)
    check('Blink publishes only the84x64 map twice',len(presents)==3 and [p[2] for p in presents[1:]]==[4,4])
    check('Blink does not render text, portraits or the full background again',len(pictures)==4 and len(texts)==12)
    check('Blink markers are drawn only on the offscreen canvas',bool(m.pixels) and all(p[0]==AUX for p in m.pixels))
    # App-owned canvas shortages keep confirm/cancel functional and bounded.
    for aux,message,allocation,owned in [(0,CONTEXT+4,ALLOC,False),(0,0,ALLOC,True),(0,0,0,False)]:
        m,count,pending,ops,pictures,texts,presents,allocs,frees,guards=setup([key(1)],aux,message,allocation)
        result=m.call('sango_menu_choose_ruler',count)
        check(f'Canvas fallback{aux,message,allocation} can cancel immediately',result==255 and not pending)
        check(f'Canvas fallback{aux,message,allocation} frees only owned memory',frees==([ALLOC] if owned else []))
    report={'passed':len(cases),'failed':0,'bda_sha256':hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),
            'adjacent_preview_window_pixels':13117,'previous_full_window_pixels':76800,
            'scope':'Actual compiled MIPS faction controller and compositor. Native SDK picture/text/copy/present boundaries modeled; first real input, complete initial commit, explicit contexts, no per-selection allocation/per-pixel image calls, dirty areas, scrolling, blink and canvas fallbacks checked. Native visuals/response separately tested; no physical latency claim.','cases':cases}
    (ROOT/'build/ruler-response-validation.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in report.items() if k!='cases'}))

if __name__=='__main__':main()

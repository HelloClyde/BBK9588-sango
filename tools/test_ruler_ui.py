"""Exercise faction-page previews, actual scenario identities and touch confirmation."""
import hashlib
import json
import struct

from test_control_flow import Machine, ROOT, STATE, BUFFER
from test_touch_input import event, install_events
from test_color_assets import machine, expected_pixels, CONTEXT, LIB_ADDRESS

IMAGE = (ROOT/'build/sango.elf').read_bytes()
LIB = (ROOT/'build/sango.lib').read_bytes()
CLR = (ROOT/'build/sango.clr').read_bytes()


def controller(count, events):
    m = Machine(IMAGE); trace=[]
    m.word(STATE['g_move_costs_address'], BUFFER+1024)
    m.word(STATE['g_temp_character_ids_address'], BUFFER+1536)
    m.write(BUFFER+1024,b'X'*250+b'\xa5\0')
    m.write(BUFFER+1536,bytes(range(41)))
    m.write(BUFFER+2048,bytes(range(80)))
    m.intercept('sango_load_named_text',2,lambda a:m.write(a[1],b'Name\0'))
    m.intercept('sango_resource_item',3,lambda a:BUFFER+2048)
    m.intercept('sango_ruler_begin',1,lambda a:trace.append(('begin',a)))
    m.intercept('sango_ruler_select',4,lambda a:trace.append(('select',a)))
    m.intercept('sango_ruler_draw_names',1,lambda a:trace.append(('names',a)))
    m.intercept('sango_ruler_end',1,lambda a:trace.append(('end',a)) or a[0])
    m.intercept('sango_display_invert_rectangle',5,lambda a:trace.append(('marker',a)))
    def cities(a):m.write(a[1],b'\x00\x01');return 2
    m.intercept('sango_faction_list_cities',2,cities)
    pending=install_events(m,events)
    result=m.call('sango_menu_choose_ruler',count)
    assert not pending and m.read(BUFFER+1274,2)==b'\xa5\0'
    return result,trace,m.read(BUFFER+1024,250)


def main():
    cases=[]
    def check(name,ok):
        assert ok,name
        cases.append({'name':name,'passed':True})
    key=lambda k:event(5,key=k)
    for count in (0,1,18,41,86):
        result,trace,names=controller(count,[] if not count else [key(0x1c)])
        check(f'{count} rulers retain bounded names and confirm/cancel result',
              result==(255 if not count else 0) and (not count or names[min(count,41)*6]==0))
        check(f'{count} rulers release the page on confirm',
              (not trace if not count else trace[-1]==('end',[0])))
    for delta in (0,1,28):
        events=[event(11,40,64+3*18+5,key=delta),event(11,170,280,key=1)]
        result,trace,_=controller(18,events)
        check(f'Touch delta {delta}: preview row3 then explicit Confirm returns row3',result==3)
        check(f'Touch delta {delta}: row3 preview occurred before leaving',
              [t for t in trace if t[0]=='select'][-1][1]==[0,0,3,0])
    for x,y in [(24,267),(104,294),(60,280)]:
        result,trace,_=controller(18,[event(11,40,120),event(11,x,y)])
        check(f'Return button corner {x},{y} cancels and frees the page',result==255 and trace[-1]==('end',[255]))
    for x,y in [(136,267),(218,294),(170,280)]:
        result,_,_=controller(18,[key(0x6c),event(11,x,y)])
        check(f'Confirm button corner {x},{y} uses current selection',result==1)
    for x,y in [(23,280),(105,280),(135,280),(219,280),(170,266),(170,295)]:
        result,trace,_=controller(18,[event(11,x,y),key(1)])
        check(f'Outside button point {x},{y} does not activate a button',result==255)
    result,trace,_=controller(41,[key(0x6c)]*30+[key(0x1c)])
    check('Ten visible rows scroll to keep row30 previewed',
          result==30 and [t for t in trace if t[0]=='select'][-1][1]==[29,20,30,21])
    result,trace,_=controller(4,[event(6),event(11,230,200),event(12,80,60),key(1)])
    markers=[t[1] for t in trace if t[0]=='marker']
    check('Map flashing uses translated map coordinates only',
          result==255 and len(markers)==2 and markers[0][:4]==[121,74,122,75])
    result,trace,_=controller(1,[event(11,40,230),key(0x1c)])
    check('Blank rows do not preview nonexistent rulers',result==0 and len([t for t in trace if t[0]=='select'])==1)

    # Real scenario loader and real picture renderer. Only native pixel/text/
    # snapshot SDK boundaries are modeled, not the identity or lookup logic.
    cat=json.loads((ROOT/'assets/color/catalog.json').read_text(encoding='utf8'))
    manifest=json.loads((ROOT/'assets/library/manifest.json').read_text(encoding='utf8'))
    resources={r['id']:r for r in manifest['records']+manifest['supplements']}
    entries={e[0]:e for e in [struct.unpack_from('<IIHHI',CLR,32+i*16)
                            for i in range(struct.unpack_from('<I',CLR,12)[0])]}
    source=json.loads((ROOT/'assets/ruler/provenance.json').read_text(encoding='utf8'))
    m=machine(LIB,CLR);m.word(STATE['g_character_table_address'],0x81100000)
    m.word(STATE['g_scratch_buffer_address'],BUFFER+4096)
    m.word(STATE['g_army_slot_used_address'],BUFFER+8000)
    m.word(STATE['g_order_queue_address'],BUFFER+9000)
    texts=[];snapshots=[];freed=[];restores=[]
    m.intercept('sango_ruler_sdk_text',4,lambda a:texts.append([*a[:2],m.text(a[2]),a[3]]))
    m.intercept('sango_color_sdk_snapshot',1,lambda a:snapshots.append(a[0]) or 0x81610000)
    m.intercept('sango_color_sdk_snapshot_free',1,lambda a:freed.append(a[0]))
    m.intercept('sango_color_sdk_restore',6,lambda a:restores.append(a))
    for scenario in source['scenarios']:
        sid=scenario['scenario'];count=m.call('sango_scenario_load',sid,BUFFER+1536)
        actual=list(m.read(BUFFER+1536,count))
        check(f'Scenario{sid}: preview candidates match the actual game loader',actual==[r['character_id'] for r in scenario['rulers']])
        for row in scenario['rulers']:
            cid=row['character_id'];frame=row['deck_frame'];m.pixels.clear();texts.clear()
            m.call('sango_ruler_update',cid,instruction_limit=2_000_000)
            record=resources[53];spec=record['image']
            offset=struct.unpack_from('<I',LIB,(53-1)*4)[0]+18+frame*((48+3)//4)*48
            check(f'Scenario{sid} ruler{cid}: correct48px portrait frame at133,168',
                  m.pixels==expected_pixels(LIB,CLR,entries[offset],133,168,CONTEXT))
            # Names independently decoded from the corresponding scenario table.
            textid={1:62,2:70,3:71,4:72}[sid]
            at=struct.unpack_from('<I',LIB,(textid-1)*4)[0];encoding=struct.unpack_from('<H',LIB,at+10)[0]
            name=bytes((v-encoding)&255 for v in LIB[at+12+cid*8:at+12+(cid+1)*8]).split(b'\0')[0]
            check(f'Scenario{sid} ruler{cid}: displayed name uses the same characterID',
                  texts==[[157-len(name)*4,232,name,0]])
    # The page borrows the existing game canvas; it must not free that owner.
    m.pixels.clear();m.call('sango_ruler_begin',18,instruction_limit=30_000_000)
    check('Page background/map are colored rather than white',len(m.pixels)>80000)
    check('Existing game canvas is reused without another page allocation',
          m.call('sango_ruler_end',255)==255 and not snapshots and not freed)
    m.call('sango_ruler_end',255)
    check('Repeated page cleanup never frees the application canvas',not freed)

    report={'passed':len(cases),'failed':0,'bda_sha256':hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),
            'library_sha256':hashlib.sha256(LIB).hexdigest(),'color_sha256':hashlib.sha256(CLR).hexdigest(),
            'scope':'Actual MIPS faction controller, scenario loader and portrait renderer; all50 original scenario rulers use matching portrait/name IDs. Touch previews, explicit buttons, scrolling, bounds and borrowed-canvas ownership checked. SDK pixels/text/context boundaries modeled; native page/font checked separately.','cases':cases}
    (ROOT/'build/ruler-ui-validation.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps({k:v for k,v in report.items() if k!='cases'}))


if __name__=='__main__':main()

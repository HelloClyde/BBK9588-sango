"""Check actual save-slot rendering/selection against the resource046 grid."""
from pathlib import Path
import hashlib,io,json,struct
from elftools.elf.elffile import ELFFile
from PIL import Image
from test_control_flow import Machine,ROOT,STATE,BUFFER
from test_touch_input import event,install_events

LIBRARY=(ROOT/'build/sango.lib').read_bytes()
IMAGE=(ROOT/'build/sango.elf').read_bytes()
LIB_ADDRESS=0x81000000

def ruled_cells(path):
    image=Image.open(path).convert('RGB');lines=[]
    for y in range(88,290):
        dark=sum(max(image.getpixel((x,y)))-min(image.getpixel((x,y)))<130 and
                 sum(image.getpixel((x,y)))<600 for x in range(24,215))
        if dark>170:
            if lines and y==lines[-1][1]+1:lines[-1][1]=y
            else:lines.append([y,y])
    assert len(lines)==8,path
    return [(lines[i][1]+1,lines[i+1][0]-1) for i in range(3)]

def draw_slots(image,files):
    m=Machine(image);m.write(LIB_ADDRESS,LIBRARY);m.word(STATE['g_resource_package_address'],LIB_ADDRESS)
    m.write(STATE['g_scenario_id_view2'],b'\x03');handles={};texts=[];backgrounds=[];closed=[]
    def open_file(a):
        name=m.text(a[0]).split(b'\\')[-1].decode('ascii')
        if name not in files:return 0
        handle=100+len(closed)+len(handles);handles[handle]=[files[name],0];return handle
    def read(a):
        data,pos=handles[a[3]];take=min(a[1]*a[2],len(data)-pos)
        m.write(a[0],data[pos:pos+take]);handles[a[3]][1]+=take
        return take//a[1] if a[1] else 0
    def close(a):closed.append(a[0]);del handles[a[0]]
    m.intercept('bbk_fopen',2,open_file);m.intercept('bbk_fread',4,read);m.intercept('bbk_fclose',1,close)
    # The unity compiler can inline bbk_fopen down to a local SDK wrapper;
    # each translation unit can contain a different symbol with that name.
    for symbol in ELFFile(io.BytesIO(image)).get_section_by_name('.symtab').iter_symbols():
        if symbol.name=='bda_fs_fopen_raw':
            name='_save_open_'+str(symbol['st_value']);m.symbols[name]=int(symbol['st_value'])
            m.intercept(name,2,open_file)
    names=['刘备','曹操','孙权']
    m.intercept('sango_load_named_text',2,lambda a:m.write(a[1],names[a[0]%3].encode('gbk')+b'\0'))
    m.intercept('sango_format_integer',3,lambda a:m.write(a[1],str(a[0]).encode()+b'\0'))
    m.intercept('bbk_strlen',1,lambda a:len(m.text(a[0])))
    m.intercept('sango_bitmap_draw_resource',5,lambda a:backgrounds.append(a))
    m.intercept('sango_text_draw_legacy',3,lambda a:texts.append((a[0],a[1],m.text(a[2]))))
    m.call('sango_save_draw_slots')
    assert backgrounds==[[46,1,0,0,1]] and not handles
    assert m.read(STATE['g_scenario_id_view2'],1)==b'\x03'
    return texts,closed

def choose(mode,events,result=1):
    m=Machine(IMAGE);rects=[];requests=[];draws=[]
    m.intercept('sango_save_draw_slots',0,lambda a:draws.append(1))
    m.intercept('sango_display_invert_rectangle',5,lambda a:rects.append(tuple(a)))
    def io(a):requests.append(a[0]);return result
    m.intercept('sango_save_write_slot' if mode==0 else 'sango_save_load_slot',1,io)
    pending=install_events(m,events)
    answer=m.call('sango_save_choose_slot',mode)
    assert not pending
    return answer,requests,rects,draws

def main():
    cases=[]
    def check(name,ok):
        assert ok,name
        cases.append({'name':name,'passed':True})
    sources=[ROOT/'assets'/folder/'界面/存读档列表底图_资源046/存读档列表底图.png'
             for folder in ['library','color/library']]
    cells=[ruled_cells(path) for path in sources]
    full={}
    for slot in range(3):
        full[f'sango{slot*2}.sav']=struct.pack('<BBH',slot+1,slot,190+slot)
        full[f'sango{slot*2+1}.sav']=b'commands'
    for label,files in [('empty',{}),('full',full),('primary-only',{'sango0.sav':full['sango0.sav']}),
                        ('secondary-only',{'sango1.sav':b'commands'}),
                        ('mixed',{k:v for k,v in full.items() if k not in ('sango2.sav','sango3.sav')})]:
        texts,_=draw_slots(IMAGE,files)
        for source,bands in zip(sources,cells):
            check(label+' text fits '+source.parent.name,len(texts)==3 and all(
                x==40 and top<=y and y+11<=bottom for (x,y,_),(top,bottom) in zip(texts,bands)))
        if label=='full':check('Existing metadata/name/year remain in original slot order',all(name.encode('gbk') in text and str(190+i).encode() in text for i,((_,_,text),name) in enumerate(zip(texts,['刘备','曹操','孙权']))))
        if label in ('empty','primary-only','secondary-only'):check(label+' displays original empty marker',all(t[2]=='空'.encode('gbk') for t in texts))
    for mode in (0,1):
        for row,(top,bottom) in enumerate(cells[1]):
            for y in (top,(top+bottom)//2,bottom):
                for x in (24,100,215):
                    answer,requests,_,_=choose(mode,[event(11,x,y)])
                    check(f'Mode{mode} row{row} touch({x},{y}) uses that save slot',answer==row and requests==[row])
        for keys,wanted in [([],0),([0x6c],1),([0x6c,0x6c],2),([0x6c]*3,0),([0x67],2),([0x67]*2,1),([0x67]*3,0)]:
            answer,requests,rects,_=choose(mode,[event(5,key=k) for k in keys+[0x1c]])
            check(f'Mode{mode} keyboard{keys} selects{wanted}',answer==wanted and requests==[wanted])
            check(f'Mode{mode} keyboard{keys} highlight fits ruled cell',all(
                left==24 and right==215 and context==0 and any(top<=y and y2<=bottom for top,bottom in cells[1])
                for left,y,right,y2,context in rects))
        for x,y in [(23,108),(216,108),(100,94),(100,176)]:
            answer,requests,_,_=choose(mode,[event(11,x,y),event(5,key=1)])
            check(f'Mode{mode} outside touch({x},{y}) cannot overwrite/load a slot',answer==255 and not requests)
    baseline=ROOT/'build/music-performance-D2/sango.elf'
    if baseline.exists():
        old,_=draw_slots(baseline.read_bytes(),{})
        check('Pre-fix executable reproduces divider overlap',any(not(top<=y and y+11<=bottom) for (_,y,_),(top,bottom) in zip(old,cells[1])))
    report={'passed':len(cases),'failed':0,'bda_sha256':hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),
            'colored_cells':cells[1],'glyph_height':12,'text_tops':[102,129,156],
            'scope':'Actual compiled MIPS slot list with modeled file metadata/name/number and text output boundaries. Actual save/load controller and touch row logic, empty/full/incomplete pairs, ruler/year assembly, scenario restoration, file closure, all three slots, keyboard wrapping and outside touches. Read/write payload code and save format unchanged. Native font screenshot checked separately.',
            'cases':cases}
    (ROOT/'build/save-layout-validation.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in report.items() if k!='cases'}))

if __name__=='__main__':main()

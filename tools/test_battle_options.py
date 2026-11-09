"""Exercise all battle options through real MIPS menu/text/dispatch code."""
from pathlib import Path
import argparse,hashlib,json,struct
from test_control_flow import Machine,ROOT,STATE

FLAGS=['g_battle_render_enabled_view2','g_battle_show_animations_view2','g_battle_animate_movement_view2']
PARENT='回合结束敌军移动战斗动画移动速度全军撤退'.encode('gbk')
VIEW='不看观看'.encode('gbk');SPEED='快速慢速'.encode('gbk')
def tap(x,y):return (11,0,x,y)
def key(code):return (5,code,0,0)
def select(row,mode):return [tap(20,14+12*row)] if mode=='touch' else [key(0x6c)]*row+[key(0x1c)]


def run(image,events):
    m=Machine(image);m.write(0x81000000,(ROOT/'build/sango.lib').read_bytes())
    m.word(STATE['g_resource_package_address'],0x81000000)
    m.word(STATE['g_game_context'],0x81600008)
    for name in FLAGS:m.write(STATE[name],b'\1')
    m.write(STATE['g_battle_result_view2'],b'\0')
    pending=list(events);texts=[];presents=[]
    def next_event(args):
        assert pending,'Option consumed unexpected extra input/submenu'
        m.write(args[0],struct.pack('<IIHH',*pending.pop(0)))
    m.intercept('sango_input_next_event',1,next_event)
    m.intercept('bbk_strlen',1,lambda a:len(m.text(a[0])))
    m.intercept('sango_text_draw_legacy',3,lambda a:texts.append(m.text(a[2])))
    m.intercept('sango_render_present',1,lambda a:presents.append(a[0]))
    for fn,n in [('sango_display_fill_gray_rectangle',6),('sango_display_fill_rectangle',6),
                 ('sango_display_draw_rectangle',7),('sango_display_invert_rectangle',5),
                 ('sango_display_put_gray_pixel',4)]:m.record(fn,n)
    result=m.call('sango_battle_show_options')
    return {'returned':result,'result':m.read(STATE['g_battle_result_view2'],1)[0],
            'flags':[m.read(STATE[n],1)[0] for n in FLAGS],'pending':len(pending),
            'texts':texts,'presents':presents}


def main():
    parser=argparse.ArgumentParser();parser.add_argument('--baseline',type=Path);args=parser.parse_args()
    image=(ROOT/'build/sango.elf').read_bytes();cases=[]
    def check(name,events,returned,battle_result,flags,texts):
        state=run(image,events)
        assert state['returned']==returned and state['result']==battle_result,(name,state)
        assert state['flags']==flags and state['pending']==0,(name,state)
        assert state['texts']==texts and state['presents'] and set(state['presents'])=={0x81600008},(name,state)
        cases.append({'name':name,'passed':True})
    for mode in ['touch','key']:
        for row in [0,4]:
            check(f'{mode}: row{row} ends turn/retreats without view submenu',select(row,mode),255,2 if row==4 else 0,[1,1,1],[PARENT])
        for row in [1,2,3]:
            for value in [0,1]:
                submenu=[tap(116,153+12*value)] if mode=='touch' else ([key(0x67)] if value==0 else [])+[key(0x1c)]
                flags=[1,1,1];flags[row-1]=value
                check(f'{mode}: row{row} changes only setting{row-1} to{value}',select(row,mode)+submenu+[key(1)],1,0,flags,[PARENT,SPEED if row==3 else VIEW,PARENT])
            cancel=[tap(239,319)] if mode=='touch' else [key(1)]
            check(f'{mode}: row{row} submenu cancel preserves battle/settings',select(row,mode)+cancel+[key(1)],1,0,[1,1,1],[PARENT,SPEED if row==3 else VIEW,PARENT])
        check(f'{mode}: close parent preserves battle/settings',[tap(239,319)] if mode=='touch' else [key(1)],1,0,[1,1,1],[PARENT])
    events=[]
    for row in [1,2,3]:events+=select(row,'touch')+[tap(116,153)]
    check('Multiple settings then retreat dispatch each visible row correctly',events+select(4,'touch'),255,2,[0,0,0],[PARENT,VIEW,PARENT,VIEW,PARENT,SPEED,PARENT])
    check('Touch setting then physical keys can retreat',select(1,'touch')+[tap(116,153)]+[key(0x6c)]*3+[key(0x1c)],255,2,[0,1,1],[PARENT,VIEW,PARENT])
    baseline=None
    if args.baseline:
        old=args.baseline.read_bytes()
        enemy=run(old,select(1,'touch'))
        retreat=run(old,select(4,'touch')+[tap(116,153),key(1)])
        assert enemy['result']==2 and enemy['returned']==255
        assert retreat['result']==0 and retreat['flags']==[0,1,1] and VIEW in retreat['texts']
        baseline={'elf_sha256':hashlib.sha256(old).hexdigest(),'enemy_movement_wrongly_retreats':True,'retreat_wrongly_changes_view_flag':True}
    report={'passed':len(cases),'failed':0,'bda_sha256':hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),
            'scope':'Real compiled MIPS sango_battle_show_options, resource001 text decode and sango_ui_choose_option; touch row hit-testing and keyboard events execute. SDK draw/present/input boundaries modeled. No new confirmation is added: row4 directly sets result2, matching reviewed9288S code.',
            'cases':cases}
    (ROOT/'build/battle-options-validation.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf8',newline='\n')
    if baseline:(ROOT/'build/battle-options-baseline.json').write_text(json.dumps(baseline,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps({'passed':len(cases),'failed':0,'baseline_reproduced':bool(baseline)}))


if __name__=='__main__':main()

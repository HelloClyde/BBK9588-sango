"""Record the reviewed original 9288S/9588 battle-menu reference.

Requires user-supplied original files; neither original executable is shipped.
Branch meanings are annotations from inspected original disassembly, not an
automated decompiler or a claim of native9288S menu execution.
"""
from pathlib import Path
import argparse,hashlib,json,struct


def text(package,item):
    offset=struct.unpack_from('<I',package,0)[0]
    _,rid,count,stride,encoding=struct.unpack_from('<IHHHH',package,offset)
    assert rid==1 and count>=item and stride==0
    relative,length=struct.unpack_from('<HH',package,offset+12+(item-1)*4)
    return bytes((b-(encoding&255))&255 for b in package[offset+relative:offset+relative+length]).decode('gbk')


def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe9288s',type=Path,required=True);p.add_argument('--bda9588',type=Path,required=True);p.add_argument('--lib9588',type=Path,required=True);p.add_argument('--output',type=Path,default=Path('build/battle-options-reference.json'));a=p.parse_args()
    exe=a.exe9288s.read_bytes();bda=a.bda9588.read_bytes();library=a.lib9588.read_bytes()
    assert hashlib.sha256(exe).hexdigest()=='4eafbd3c59b64bf56fb810e47de43cb9d1075530801a8f991cf007f510954f9c'
    assert hashlib.sha256(bda).hexdigest()=='38f3740af4d21ea3108e964b2824b518b1b5cc837e81fcb9b3cfefced7ff8ac6'
    offset=struct.unpack_from('<I',exe,8)[0];assert struct.unpack_from('<I',exe,len(exe)-4)[0]==offset
    package=exe[offset:-4]
    texts={str(i):text(package,i) for i in [9,10,11]}
    assert texts=={str(i):text(library,i) for i in [9,10,11]}
    assert texts=={'9':'回合结束敌军移动战斗动画移动速度全军撤退','10':'不看观看','11':'快速慢速'}
    rows=[{'row':i,'label':texts['9'][i*4:i*4+4],'9288s_action':action,'9588_original_action':old} for i,action,old in [
        (0,'End player turn, return255; battle result unchanged','same'),
        (1,'Choose resource001/10 and update enemy-movement view flag','Set battle result2 and return255: wrongly retreats'),
        (2,'Choose resource001/10 and update combat-animation flag','same'),
        (3,'Choose resource001/11 and update movement-speed flag','same'),
        (4,'Set battle result2 and return255; no view submenu','Choose resource001/10 and update enemy-movement view flag: wrong submenu')]]
    report={'date':'2026-11-10','evidence_kind':'Reviewed original static S1C33/MIPS disassembly plus decoded original text records; not native9288S execution.',
        '9288s_exe_sha256':hashlib.sha256(exe).hexdigest(),'9588_original_bda_sha256':hashlib.sha256(bda).hexdigest(),
        'text_records':texts,'same_decoded_menu_text':True,'rows':rows,
        '9288s_menu_file_range':['0x782e','0x7910'],'9288s_menu_code_sha256':hashlib.sha256(exe[0x782e:0x7910]).hexdigest(),
        '9288s_branch_evidence':{'row4_result2_store':['0x7886','0x789a'],'row1_view_flag_pointer':['0x7880','0x78d8'],'row2_animation_flag_pointer':['0x7872','0x78c6'],'row3_speed_flag_pointer':['0x788a','0x78d0'],'view_flag':'0x027126fa','animation_flag':'0x027126fb','movement_flag':'0x027126fc','battle_result':'0x027126f6'},
        '9588_original_menu_virtual_range':['0x81c06440','0x81c065c4'],
        '9588_original_branch_evidence':{'row1_wrong_retreat':['0x81c064e8','0x81c06530'],'row4_wrong_view_flag':['0x81c06568','0x81c065b0']},
        'finding':'9588 original port swapped rows1 and4 while retaining the9288S text order. The reconstructed C preserved that port bug; correction follows original9288S action mapping, without changing text or adding a confirmation.'}
    a.output.parent.mkdir(parents=True,exist_ok=True);a.output.write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps({'menus_match':True,'swapped_rows':[1,4],'output':str(a.output)}))


if __name__=='__main__':main()

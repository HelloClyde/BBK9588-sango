"""Resource purposes established from callers, selectors and decoded tables.

No drawing-content guesses belong here. Frame numbers without a code-derived
meaning deliberately remain numbered. audit_resource_usage.py checks the cited
source expressions and reconstructs the skill/resource and city/map selectors.
"""
from copy import deepcopy
try:
    from .source_map import resolve_reference
except ImportError:
    from source_map import resolve_reference

def ref(function,expression,source='src/sango_game.c'):
    return resolve_reference(function,expression,source)

def rule(category,name,reason,*evidence,status='confirmed'):
    return {'category':category,'name':name,'usage_status':status,
            'naming_evidence':reason,'code_evidence':list(evidence)}

RULES={
1:rule('文字','战斗提示与存读档文字','文字读取器以资源1和条目号读取；覆盖战斗提示、战场菜单与存读档路径。',
       ref('FUN_81c0666c','FUN_81c154d8(1,'),ref('FUN_81c164c8',"FUN_81c154d8(1,0x40,")),
2:rule('数据','战斗与战略界面规则子表','15个子表的使用点包含移动范围、技能列表、经验、地形修正、初始站位、城市坐标、列表列宽、行动消耗和城市战场类型。',
       ref('FUN_81c02524',"in_t0 = 2;"),ref('FUN_81c12e18',"FUN_81c152f0(2,'\\x0e',"),ref('FUN_81c10394','FUN_81c154d8(2,0xf,')),
3:rule('界面','启动片头动画','资源加载后、建立新会话前，生命周期函数播放资源3。',ref('sango_game_lifecycle','FUN_81c162e0(3);')),
4:rule('战斗','战场地形图块','战场初始化将图集ID设为4；地图渲染按tile ID取64字节的16x16图块；地形类型由FUN_81c0620c确定。',
       ref('FUN_81c03c98','DAT_81c2b13e = 4;'),ref('FUN_81c04b9c','FUN_81c04f40((uint)DAT_81c2b13e,'),ref('FUN_81c0620c','bVar1 != 0x29')),
5:rule('战斗','部队兵种与状态小图','FUN_81c06838按部队组、兵种、水域和混乱/石阵状态选择帧；FUN_81c04630加交替相位后绘制。',
       ref('FUN_81c06838','uVar3 = 0xe;'),ref('FUN_81c06838','uVar3 = 0xc;'),ref('FUN_81c04630','FUN_81c04fb4(5,')),
6:rule('历史界面','原版制作群组动画','原版制作群组入口播放资源6；当前入口已调用竖屏C素材，保留原资源供回包。',
       ref('FUN_81c15e44','FUN_81c162e0(6);','docs/original-credits-call.c.txt'),
       ref('FUN_81c15e44','sango_credits_draw(credits_draw_target);'),status='historical'),
7:rule('战斗','移动范围与目标光标','移动范围绘制直接使用帧0；选目标使用第2项（帧1），当前战场光标使用第5项（帧4）。其他帧未定位调用。',
       ref('FUN_81c027f0',"FUN_81c152f0(7,'\\x01',"),ref('FUN_81c0343c','FUN_81c04fb4(7,2,'),ref('FUN_81c03c20','FUN_81c04fb4(7,5,')),
8:rule('战斗','战斗状态行底图','战斗HUD把资源8按9288S的160像素逻辑宽度放大为240x24，在y=224绘制，再填粮草、天气和目标姓名/地形。9588资源右侧追加的空白列不参与缩放。',
       ref('sango_battle_status_draw','sango_resource_item(8, 1, g_resource_package_address)','src/sango_battle_ui.c'),
       ref('sango_battle_status_draw_description','draw_status_text(STATUS_DESCRIPTION_X, text, target);','src/sango_battle_ui.c')),
9:rule('天气','战斗天气状态图标','天气状态值为1到5；绘制前转零基帧号，并按3:2放大到18x18。未找到代码内的逐状态中文天气名，保留状态编号。',
       ref('FUN_81c06384','uVar1 = (int)uVar1 % 5 + 1;'),
       ref('sango_battle_status_draw_weather','sango_resource_item(9, 1, g_resource_package_address)','src/sango_battle_ui.c'),
       ref('sango_battle_status_draw_weather','g_battle_weather - 1','src/sango_battle_ui.c')),
10:rule('数据','战斗计谋参数','计谋ID减1后按34字节记录定位；使用者据此消耗技力、选择状态、伤害及目标条件。',
       ref('FUN_81c062d0',"FUN_81c152f0(10,'\\x01',"),ref('FUN_81c062d0','* 0x22'),ref('FUN_81c058b8','pcVar4 = (char *)FUN_81c062d0(uVar8);')),
11:rule('文字','战斗计谋名称','计谋列表与执行提示均按计谋ID读取资源11的名称。',
       ref('FUN_81c021d4','FUN_81c154d8(0xb,'),ref('FUN_81c058b8','FUN_81c154d8(0xb,uVar8,')),
12:rule('调用待确认','技能说明文本_调用待确认','解码后的内容是30项计谋说明，但未在当前读取器调用中定位资源12；不声称已接入说明界面。',status='unresolved'),
13:rule('数据','计谋目标范围矩阵','FUN_81c02524的计谋分支用资源13，并按81字节取9x9范围模板。',
        ref('FUN_81c02524','in_t0 = 0xd;'),ref('FUN_81c02524','* 0x51'),ref('FUN_81c02524','unaff_s1 = 9;')),
14:rule('剧本数据','各剧本武将初始特技','按剧本读取200字节表，按武将ID取特技并合入当前可用计谋列表。',
        ref('FUN_81c0205c','FUN_81c152f0(0xe,DAT_81c2b161,')),
15:rule('战斗','战斗伤害数字字形','数值绘制器将十进制字符减0x30，作为资源15的零基帧号。',
        ref('FUN_81c05f7c',"FUN_81c152f0(0xf,'\\x01',"),ref('FUN_81c05f7c','cVar3 - 0x30')),
16:rule('战斗','战斗演出背景框','普通攻击演出前绘制；计谋演出依初始化数据中的背景框标记决定是否绘制。',
        ref('FUN_81c05e0c',"FUN_81c077bc(0x10,1,0x14,0x31,'\\0');"),ref('FUN_81c058b8','(&DAT_81c201ac)[uVar5]')),
17:rule('补充界面','信息查找补充底栏','LIB补充条目和当前战略/战斗C内嵌位图共用240x36目标PNG；战斗显示时按240x36原尺寸绘制；战场显示15列14行，底部保留36行势力摘要。当前C并不从LIB的17号条目读取。',
        ref('sango_statusbar_draw','toolbar_bitmap','src/sango_statusbar.c'),ref('sango_battle_toolbar_draw','battle_toolbar_bitmap','src/sango_statusbar.c')),
18:rule('补充界面','制作群组补充竖屏页','LIB补充条目和当前C制作群组页共用目标PNG；制作群组入口调用C位图。',
        ref('sango_credits_draw','credits_bitmap','src/sango_credits.c'),ref('FUN_81c15e44','sango_credits_draw(')),
**{rid:rule('战斗动画',troop+'攻击演出','普通攻击通过攻击方兵种+19选择图集；另核对计谋到资源和时间轴区间的初始化表。单个精灵不凭外观指定攻击/受击角色。',
            ref('FUN_81c05e0c','uVar5 = DAT_81c2b237 + 0x13;'),ref('FUN_81c01278','(&DAT_81c2b237)[iVar6] = bVar1;'),
            ref('FUN_81c058b8','&DAT_81c20110 + uVar5 * 2'))
   for rid,troop in enumerate(['骑兵','步兵','弓兵','水军','极兵','玄兵'],19)},
25:rule('战斗动画','水域目标普通攻击演出','普通攻击默认选资源25；仅当目标地形不是7（河流）时改为按攻击方兵种选19到24。',
        ref('FUN_81c05e0c','uVar5 = 0x19;'),ref('FUN_81c05e0c',"DAT_81c2b249 != '\\a'"),ref('FUN_81c0620c','uVar3 = 7;')),
26:rule('战斗','战斗短消息底图','FUN_81c07bc0读取资源26，绘制文本、按参数等待；用于计谋名和失败等战斗短消息。',
        ref('FUN_81c07bc0',"FUN_81c152f0(0x1a,'\\x01',"),ref('FUN_81c058b8','FUN_81c07bc0(acStack_48,')),
27:rule('战斗动画','升级退场与行动特效','FUN_81c04920将0到5用于升级、6到11用于兵力/生命耗尽退场；FUN_81c02f4c将12到17用于攻击或计谋指令。',
        ref('FUN_81c04920','FUN_81c04ae8(0,5,'),ref('FUN_81c04920','FUN_81c04ae8(6,0xb,'),ref('FUN_81c02f4c','FUN_81c06a70(0x1b,0xc,0x11,')),
**{rid:rule('天气',f'天气状态{rid-27:02d}演出背景','资源ID=天气状态+27；代码只确认状态1到5的对应关系，未提供逐状态中文天气名。',
            ref('FUN_81c06384',"FUN_81c077bc((uVar1 & 0xff) + 0x1b,")) for rid in range(28,33)},
33:rule('战斗','战斗天数弹窗','实际天数弹窗绘制函数读取资源33，并在中央空位绘制传入天数。',
        ref('sango_battle_day_popup_draw','FUN_81c152f0(33,1,','src/sango_battle_ui.c')),
34:rule('战斗','禁咒与定身状态标记','部队状态2（禁咒）选零基帧2/3，状态3（定身）选帧4/5；帧0/1未定位使用。',
        ref('FUN_81c04630',"cVar1 == '\\x02'"),ref('FUN_81c04630','iVar4 = 4,'),ref('FUN_81c04630','FUN_81c04fb4(0x22,')),
35:rule('计谋动画','火攻火箭烈火演出','初始化表将计谋5火攻、11火箭、18烈火指向资源35。',ref('FUN_81c058b8','&DAT_81c20110 + uVar5 * 2')),
36:rule('计谋动画','水淹海啸演出','初始化表将计谋12水淹、19海啸指向资源36。',ref('FUN_81c058b8','&DAT_81c20110 + uVar5 * 2')),
37:rule('计谋动画','滚木落石演出','初始化表将计谋6滚木、7落石指向资源37；两者选取不同的指令区间。',ref('FUN_81c058b8','&DAT_81c20110 + uVar5 * 2')),
38:rule('计谋动画','撞击演出','初始化表将计谋13撞击指向资源38。',ref('FUN_81c058b8','&DAT_81c20110 + uVar5 * 2')),
39:rule('计谋动画','咒封定身奇门演出','初始化表将计谋14咒封、15定身、20奇门指向资源39。',ref('FUN_81c058b8','&DAT_81c20110 + uVar5 * 2')),
40:rule('计谋动画','流言演出','初始化表将计谋16流言指向资源40。',ref('FUN_81c058b8','&DAT_81c20110 + uVar5 * 2')),
41:rule('计谋动画','援兵援军演出','初始化表将计谋17援兵、29援军指向资源41。',ref('FUN_81c058b8','&DAT_81c20110 + uVar5 * 2')),
42:rule('计谋动画','石阵演出','初始化表将计谋23石阵指向资源42。',ref('FUN_81c058b8','&DAT_81c20110 + uVar5 * 2')),
43:rule('计谋动画','陷阱演出','初始化表将计谋24陷阱指向资源43。',ref('FUN_81c058b8','&DAT_81c20110 + uVar5 * 2')),
44:rule('界面','主菜单静态底图','会话入口以资源44作菜单底图，选项动画基ID为100。',ref('sango_select_session','FUN_81c15d18(0x2c,100)')),
45:rule('界面','剧本菜单静态底图','新会话选择以资源45作底图，选项动画基ID为104，选中项+1作为剧本ID。',
        ref('sango_select_session','FUN_81c15d18(0x2d,0x68)'),ref('sango_select_session',"FUN_81c1b91c((char)uVar2 + '\\x01'")),
46:rule('界面','存读档列表底图','FUN_81c164c8读取资源46后依次检查三组存档文件、绘制君主名和年月；同一列表用于存档和读档。',
        ref('FUN_81c164c8','FUN_81c077bc(0x2e,1,'),ref('FUN_81c16330','FUN_81c164c8();')),
47:rule('战略地图','君主选择势力图','君主选择器绘制资源47，并依据城市坐标和所选君主控制的城市闪烁标记。',
        ref('FUN_81c15e6c','FUN_81c077bc(0x2f,1,'),ref('FUN_81c15e6c','FUN_81c161c4(')),
**{rid:rule('武将头像',f'剧本{rid-47:02d}武将头像','头像ID=剧本+47，头像帧号与同剧本姓名表使用同一武将索引。',
            ref('FUN_81c055b0','FUN_81c152f0(DAT_81c2b161 + 0x2f,'),ref('FUN_81c055b0','FUN_81c14fb8(0xc3,10,'),
            ref('sango_load_named_text',f'in_a3 = {textid:#x};')) for rid,textid in zip(range(48,52),[62,70,71,72])},
54:rule('战略地图','战略大地图拼块','战略绘制器按(row*12+column)*256读取资源54的32x32块，帧索引对应12列9行。',
        ref('FUN_81c12e18',"FUN_81c152f0(0x36,'\\x01',"),ref('FUN_81c12e18','* 0xc + (uint)*param_1) * 0x100')),
55:rule('战略地图','城市归属图标','战略城市叠加层按归属选择零基帧0无归属、7其他势力、8当前玩家。帧1到6和9未定位调用。',
        ref('FUN_81c12e18',"FUN_81c152f0(0x37,'\\x01',"),ref('FUN_81c12e18','bVar7 = 8;'),ref('FUN_81c12e18','bVar7 = 7,')),
56:rule('战略地图','当前城市选择标记','战略地图绘制器在当前选中的地图格坐标上叠加资源56。',ref('FUN_81c12e18',"FUN_81c152f0(0x38,'\\x01',")),
57:rule('剧本数据','各剧本城市初始状态','场景初始化读取资源57的31字节城市记录，写入城市状态数组并读取初始年份。',ref('FUN_81c1add4','FUN_81c152f0(0x39,param_1,')),
58:rule('文字','城市名称','城市名读取包装器以城市ID+1读取资源58。',ref('FUN_81c1971c','FUN_81c154d8(0x3a,')),
59:rule('数据','城市相邻关系表','路线距离和相邻城选择函数读取资源59，每城16字节并扫描相邻城列表。',
        ref('FUN_81c136a0',"FUN_81c152f0(0x3b,'\\x01',"),ref('FUN_81c128b4',"FUN_81c152f0(0x3b,'\\x01',")),
60:rule('调用待确认','原始数据表_用途待确认','未定位当前代码对资源60的读取；不再因长度接近城市表而推定其用途。',status='unresolved'),
61:rule('剧本数据','各剧本武将初始属性','场景初始化从资源61按15字节读取200项属性。',ref('FUN_81c1add4','FUN_81c152f0(0x3d,param_1,')),
**{rid:rule('文字',f'剧本{scenario:02d}武将姓名','姓名读取函数按剧本选择资源，再按武将ID+1读取。',ref('sango_load_named_text',f'in_a3 = {rid:#x};'))
   for scenario,rid in enumerate([62,70,71,72],1)},
63:rule('剧本数据','各剧本武将出生年与登场城市','年度更新比较出生年+16与当前年份，随后把尚未出现的武将加入指定城市。此表不是武将命令表。',
        ref('FUN_81c17734','FUN_81c152f0(0x3f,DAT_81c2b161,'),ref('FUN_81c17734','+ 0x10) == DAT_81c2b140'),ref('FUN_81c17734','FUN_81c134b8(uVar5,(byte)uVar7)')),
64:rule('文字','战略指令属性与事件文字','城市/武将/宝物属性列、战略指令、事件和胜负提示均按条目号读取资源64。',
        ref('FUN_81c19748','FUN_81c154d8(0x40,'),ref('FUN_81c12058','FUN_81c154d8(0x40,0x5b,')),
65:rule('剧本数据','各剧本城市武将排列索引','初始化将200项复制到城市武将索引数组，城市记录的起点和数量用于取其中的武将ID。',
        ref('FUN_81c1add4','FUN_81c152f0(0x41,param_1,'),ref('FUN_81c13870','DAT_81c2b310')),
66:rule('数据','宝物与道具属性','66字节记录描述宝物效果，装备/卸下时按武力、智力和兵种效果字段更新武将。',
        ref('FUN_81c17a08',"FUN_81c152f0(0x42,'\\x01',"),ref('FUN_81c17eb4','0x3e'),ref('FUN_81c185cc','0x41')),
67:rule('剧本数据','各剧本宝物登场年份与城市','资源67的三字节记录用于判断年份，并调用城市宝物插入函数；不是势力辅助表。',
        ref('FUN_81c17e18','FUN_81c152f0(0x43,DAT_81c2b161,'),ref('FUN_81c17e18','FUN_81c135a8('),ref('FUN_81c135a8','param_2 < 0x21')),
68:rule('剧本数据','各剧本城市宝物排列索引','初始化将33项复制到宝物索引数组，城市宝物插入/移除函数操作同一数组；不是君主列表。',
        ref('FUN_81c1add4','FUN_81c152f0(0x44,param_1,'),ref('FUN_81c135a8','DAT_81c2b3e0'),ref('FUN_81c12504','DAT_81c2b3e0')),
69:rule('战略地图','城市数与武将数图标','战略状态区帧1旁写玩家城市数量，帧0旁写FUN_81c17b3c返回的玩家武将总数。战斗底部重现最后一次战略摘要，并沿用这两帧图标。',
        ref('FUN_81c12e18',"FUN_81c152f0(0x45,'\\x01',"),ref('FUN_81c12e18','FUN_81c15070(0x35,0x10f,7,9,1,'),ref('FUN_81c17b3c','FUN_81c13ab8('),
        ref('sango_battle_summary_draw','sango_resource_item(69, 1, g_resource_package_address)','src/sango_battle_ui.c')),
73:rule('文字','宝物与道具名称','宝物名称包装器按宝物ID+1读取资源73。',ref('FUN_81c18c80','FUN_81c154d8(0x49,')),
74:rule('调用待确认','宝物说明文本_调用待确认','解码文本为各宝物说明；当前接口只按资源66显示属性，尚未定位读取资源74的调用点。',status='unresolved'),
75:rule('战略地图','查找城市连接图','战略地图的查找键/触摸分支读取并居中显示资源75。',ref('FUN_81c12b18',"FUN_81c152f0(0x4b,'\\x01',")),
76:rule('事件插图','进攻交战与胜负提示插图','四个事件函数分别绘制帧0到3，并组合资源64的军队进攻、军vs军、战斗胜利和战斗失败提示。',
        *[ref(fn,f'FUN_81c14fb8(0x4d,0x77,0x54,0x40,{frame},') for frame,fn in enumerate(['FUN_81c11d98','FUN_81c11f18','FUN_81c12058','FUN_81c12188'])]),
**{rid:rule('菜单动画',label+'选中动画','菜单底图44以100为动画基ID，当前选项为0到3；会话入口对应开始新局、读档、制作群组、退出。',
            ref('sango_select_session','FUN_81c15d18(0x2c,100)'),ref('FUN_81c15d18','FUN_81c162e0(param_2 + (short)uVar2)'))
   for rid,label in enumerate(['开始新局','读取存档','制作群组','退出游戏'],100)},
**{rid:rule('菜单动画',f'剧本{rid-103:02d}选中动画','剧本菜单底图45以104为动画基ID；选中序号+1传给剧本初始化。',
            ref('sango_select_session','FUN_81c15d18(0x2d,0x68)'),ref('FUN_81c15d18','FUN_81c162e0(param_2 + (short)uVar2)')) for rid in range(104,108)},
**{rid:rule('战场地图',f'城池战场_类型{rid-110:02d}','城市ID索引资源2第15子表，所得类型加110作为战场资源ID；不推定历史战役名称。',
            ref('FUN_81c10394','FUN_81c154d8(2,0xf,'),ref('FUN_81c10394','DAT_81c2b262 = pbVar7[uVar13] + 0x6e;'),
            ref('FUN_81c04c60','FUN_81c04f40((uint)DAT_81c2b262,')) for rid in range(110,117)},
}

EVENT76_FRAMES=[
    {'frame':0,'name':'军队进攻','caller':'FUN_81c11d98','text_resource':64,'text_entries':[97,98],'message':'我方或君主名 + 军队进攻 + 城市名'},
    {'frame':1,'name':'双方交战','caller':'FUN_81c11f18','text_resource':64,'text_entries':[104,105],'message':'君主甲 + 军 vs + 君主乙 + 军'},
    {'frame':2,'name':'战斗胜利','caller':'FUN_81c12058','text_resource':64,'text_entries':[91,98],'message':'我方或君主名 + 战斗胜利'},
    {'frame':3,'name':'战斗失败','caller':'FUN_81c12188','text_resource':64,'text_entries':[92,98],'message':'我方 + 战斗失败'},
]

def identity(rid):
    result=deepcopy(RULES.get(rid,rule('调用待确认',f'用途待确认资源{rid:03d}','尚无代码读取路径依据。',status='unresolved')))
    if rid==76:result['frame_usage']=deepcopy(EVENT76_FRAMES)
    return result

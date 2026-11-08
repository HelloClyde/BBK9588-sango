"""Human-readable names based on the recovered callers and the actual artwork.

Names describe visible content/use. Unresolved variants keep their frame index;
they are not assigned invented historical events or specific character identities.
"""
from __future__ import annotations
import re,struct

# Resource ID: category, name, evidence/qualification.
RESOURCES={
    1:('文字','战斗提示与存读档文字','FUN_81c154d8: record text bytes subtract the header encoding value.'),
    2:('数据','战斗界面与规则配置','Shared subtables used by range, terrain, selection and UI code.'),
    3:('界面','三国霸业片头画面','Animation invoked by the intro; title artwork.'),
    4:('战斗','战场地形图块','16x16 terrain artwork; keep transition variants separate.'),
    5:('战斗','兵种与粮草小图标','Two visual sets of units, supplies and defeat markers.'),
    6:('界面','原版横屏制作群组','Original 320x240 animation; supplemented by portrait resource 18.'),
    7:('界面','战场光标与操作标记','Movement-range rasterizer and visible cursor artwork.'),
    8:('界面','粮草天数姓名状态行','Visible 粮/天 labels and name field.'),
    9:('天气','天气状态小图标','FUN_81c06384 selects by weather index; preserve state order.'),
    10:('数据','战斗技能参数','FUN_81c062d0 selects 34-byte records by skill ID.'),
    11:('文字','战斗技能名称','Decoded text contains 践踏/冲锋/突击/火攻 etc.'),
    12:('文字','战斗技能说明','Decoded text describes cavalry, archery and other skills.'),
    13:('数据','技能作用范围模板','FUN_81c02524 uses 9x9 range templates.'),
    14:('数据','各剧本武将初始特技','FUN_81c0205c selects scenario and character skill.'),
    15:('界面','战斗数字字形','Visible digits 0 through 9.'),
    16:('界面','武将与技能说明窗框','FUN_81c058b8/FUN_81c05e0c; decorative dialog border.'),
    17:('界面','信息查找补充底栏','Supplemental shared strategy/battle toolbar.'),
    18:('界面','制作群组补充竖屏页','Supplemental 240x320 portrait credits page.'),
    19:('战斗动画','骑兵攻击与受击','Unit order follows the decoded troop-name list and visible sprites.'),
    20:('战斗动画','步兵攻击与受击','Unit order follows the decoded troop-name list and visible sprites.'),
    21:('战斗动画','弓兵攻击与受击','Includes two arrow projectiles after the shared target sprites.'),
    22:('战斗动画','水军攻击与受击','Unit order follows the decoded troop-name list and visible sprites.'),
    23:('战斗动画','极兵攻击与受击','Uses the original troop label 极兵, not an inferred replacement.'),
    24:('战斗动画','玄兵攻击与受击','Uses the original troop label 玄兵.'),
    25:('战斗动画','船只与飞行物特效','Visible ship/supply silhouette and small flying objects; exact skill unresolved.'),
    26:('界面','战斗短提示窗框','120x24 empty decorative message border.'),
    27:('战斗动画','状态与投射物特效','Status markers, skull/flame artwork and projectiles; retain timeline order.'),
    28:('天气','晴天战场背景','Visible clear sky and sun.'),
    29:('天气','阴天战场背景','Visible cloud cover.'),
    30:('天气','大风战场背景','Visible wind strokes.'),
    31:('天气','雨天战场背景','Visible raindrops.'),
    32:('天气','雪天战场背景','Visible snowflakes.'),
    33:('界面','第几天天数弹窗','sango_battle_day_popup_draw uses resource 33.'),
    34:('界面','方向与返回小图标','Visible directional pointers and return arrows; variants retain indices.'),
    35:('计谋动画','火焰燃烧','Visible flames in two animation images.'),
    36:('计谋动画','滚木下落','Visible log rolling down a hillside.'),
    37:('计谋动画','落石下落','Visible rocks falling down a hillside.'),
    38:('计谋动画','船只撞击','Two ship images and two impact flashes.'),
    39:('计谋动画','人物施计','Visible character performing an action; exact skill not asserted.'),
    40:('计谋动画','人物对话','Visible 在那/河边 dialogue artwork; exact skill not asserted.'),
    41:('计谋动画','骑兵行进','Visible riding troops; exact event not asserted.'),
    42:('计谋动画','城池人物事件','Visible person at a city wall; exact event not asserted.'),
    43:('计谋动画','树林人物事件','Visible person among trees; exact event not asserted.'),
    44:('界面','主菜单','Visible 新君登陆/重返沙场/制作群组/卸甲归田.'),
    45:('界面','剧本选择菜单','Visible 董卓弄权/曹操崛起/赤壁之战/三国鼎立.'),
    46:('界面','君主与存档选择底图','FUN_81c164c8 draws resource 46; empty ruled list background.'),
    47:('战略地图','势力形势小地图','FUN_81c15e6c draws the territorial overview.'),
    48:('武将头像','董卓弄权武将头像','Portrait resource = scenario + 47; names from resource 62.'),
    49:('武将头像','曹操崛起武将头像','Portrait resource = scenario + 47; names from resource 70.'),
    50:('武将头像','赤壁之战武将头像','Portrait resource = scenario + 47; names from resource 71.'),
    51:('武将头像','三国鼎立武将头像','Portrait resource = scenario + 47; names from resource 72.'),
    54:('战略地图','战略大地图拼块','FUN_81c12e18 addresses (row*12+column)*256 and renders the 12-column strategy map.'),
    55:('战略地图','城池营寨与阵营标记','FUN_81c12e18 overlays these sprites on the strategy map.'),
    56:('战略地图','战略地图光标','Visible selection marker used with map overlays.'),
    57:('剧本数据','各剧本城市初始状态','FUN_81c1add4 loads four scenario city-state tables.'),
    58:('文字','城市名称','Decoded city-name table: 西凉/北平/襄平 etc.'),
    59:('数据','城市邻接与路线','FUN_81c136a0 searches eight neighboring-city slots per city.'),
    60:('数据','城市路线辅助表','Same 38x16 shape as the adjacency table; individual fields unresolved.'),
    61:('剧本数据','各剧本武将初始属性','FUN_81c1add4 loads 200 characters, 15 bytes per entry, for each scenario.'),
    62:('文字','董卓弄权武将姓名','sango_load_named_text selects resource 62 for scenario 1.'),
    63:('剧本数据','各剧本武将命令数据','FUN_81c0b6f0 uses scenario-specific 600-byte character-command data.'),
    64:('文字','内政外交军备与事件文字','Decoded command labels, stats, dialog and event text.'),
    65:('剧本数据','各剧本城市武将索引','FUN_81c1add4 copies 200 character IDs into the city roster buffer.'),
    66:('数据','宝物与道具属性','66-byte item records accessed by item index throughout the game.'),
    67:('剧本数据','各剧本势力辅助数据','Scenario-specific 99-byte tables; field meanings remain partially unresolved.'),
    68:('剧本数据','各剧本君主列表','FUN_81c1add4 copies 33-byte ruler-selection lists.'),
    69:('战略地图','战略小旗与人物标记','Two small overlay markers used by strategy rendering.'),
    70:('文字','曹操崛起武将姓名','sango_load_named_text selects resource 70 for scenario 2.'),
    71:('文字','赤壁之战武将姓名','sango_load_named_text selects resource 71 for scenario 3.'),
    72:('文字','三国鼎立武将姓名','sango_load_named_text selects resource 72 for scenario 4.'),
    73:('文字','宝物与道具名称','Decoded names include 方天画戟/七星刀/六韬/赤兔.'),
    74:('文字','宝物与道具说明','Decoded text describes item effects and provenance.'),
    75:('战略地图','城市连接线路图','Find command route-map artwork, checked against rendered output.'),
    76:('事件插图','进攻交战与胜负提示插图','已核对四个调用函数和资源064的提示文字：帧0军队进攻，帧1双方交战，帧2战斗胜利，帧3战斗失败。'),
    **{rid:('地图数据',f'旧格式地图{rid-99:02d}','Original packed layout retained; geographic name not identified.') for rid in range(100,108)},
    **{rid:('战场地图',f'战场地图{rid-109:02d}','32x32 tile map; no historical battle name stored in the resource.') for rid in range(110,117)},
}
TROOPS=['骑兵','步兵','弓兵','水军','极兵','玄兵']
EVENT76_FRAMES=[
    {'frame':0,'name':'军队进攻','caller':'FUN_81c11d98','text_resource':64,'text_entries':[97,98],
     'message':'我方或君主名 + 军队进攻 + 城市名'},
    {'frame':1,'name':'双方交战','caller':'FUN_81c11f18','text_resource':64,'text_entries':[104,105],
     'message':'君主甲 + 军 vs + 君主乙 + 军'},
    {'frame':2,'name':'战斗胜利','caller':'FUN_81c12058','text_resource':64,'text_entries':[91,98],
     'message':'我方或君主名 + 战斗胜利'},
    {'frame':3,'name':'战斗失败','caller':'FUN_81c12188','text_resource':64,'text_entries':[92,98],
     'message':'我方 + 战斗失败'},
]

def identity(rid):
    category,name,evidence=RESOURCES.get(rid,('未识别资源',f'用途待确认资源{rid:03d}','No verified semantic mapping.'))
    result={'category':category,'name':name,'naming_evidence':evidence}
    if rid==76:result['frame_usage']=[dict(frame) for frame in EVENT76_FRAMES]
    return result

def folder_name(rid):
    info=identity(rid)
    return f"{info['category']}/{info['name']}_资源{rid:03d}"

def clean_name(name):
    return re.sub(r'[<>:"/\\|?*\x00-\x1f]', '_',name).strip(' .') or '未命名'

def character_name(raw):
    """Decode GBK but retain nonstandard game character codes explicitly."""
    raw=raw.split(b'\0')[0];parts=[];i=0
    while i<len(raw):
        size=1 if raw[i]<128 else 2;part=raw[i:i+size]
        try:parts.append(part.decode('gbk'))
        except UnicodeDecodeError:parts.append('_字码'+part.hex().upper())
        i+=size
    return clean_name(''.join(parts)) if parts else '空白姓名'

def portrait_names(data,rid):
    text_id={48:62,49:70,50:71,51:72}[rid]
    offset=struct.unpack_from('<I',data,(text_id-1)*4)[0]
    if offset in (0,0xffffffff) or offset+12>len(data):return []
    size,actual,count,stride,encoding=struct.unpack_from('<IHHHH',data,offset)
    if actual!=text_id or stride!=8 or offset+size>len(data):return []
    return [character_name(bytes((v-encoding)&255 for v in data[start:start+stride]))
            for start in range(offset+12,offset+size,stride)]

def bitmap_name(rid,frame,total,names=()):
    name=identity(rid)['name']
    if 48<=rid<=51:
        person=names[frame] if frame<len(names) else '姓名待确认'
        return f'武将{frame:03d}_{person}_头像'
    if rid==54:return f'战略地图_第{frame//12+1:02d}行_第{frame%12+1:02d}列_拼块{frame:03d}'
    if rid==15:return f'数字_{frame}'
    if rid==5:
        subjects=TROOPS+['粮草','战败标记'];subject=subjects[(frame%16)//2]
        return f'样式{frame//16+1}_{subject}_姿态{frame%2+1:02d}_帧{frame:03d}'
    if rid==4:
        labels=['空白边框','空白平地','草地','营寨','城池','森林']
        label=labels[frame] if frame<6 else '山地过渡' if frame<16 else '水岸过渡'
        return f'{label}_图块{frame:03d}'
    if rid==7:
        label=['移动范围标记','目标十字标记','手形指针','箭头指针','向上箭头','返回箭头'][frame] if frame<6 else name
        return f'{label}_帧{frame:03d}'
    if rid==55:
        label='营寨' if frame==0 else '城门' if frame<7 else '城池标记'
        # FUN_81c12e18 selects 0 for unowned, 7 for enemies, 8 for player.
        if frame==0:label='无归属城池或营寨'
        if frame==7:label='敌方城池'
        if frame==8:label='我方城池'
        if frame==9:label='城池备用样式'
        return f'{label}_帧{frame:03d}'
    if rid==76:return EVENT76_FRAMES[frame]['name'] if frame<4 else f'{name}_帧{frame:03d}'
    return name if total==1 else f'{name}_帧{frame:03d}'

def animation_name(rid,image):
    name=identity(rid)['name']
    attacks={19:7,20:4,21:4,22:6,23:7,24:6}
    if rid in attacks:
        first=attacks[rid];troop=TROOPS[rid-19]
        if image<first:return f'{troop}_攻击动作{image+1:02d}_精灵{image:03d}'
        if image<first+12:
            i=image-first
            return f'受击对象_{TROOPS[i//2]}_姿态{i%2+1:02d}_精灵{image:03d}'
        return f'{troop}_投射物{image-first-11:02d}_精灵{image:03d}'
    if rid==38:
        return ['船只姿态01','船只姿态02','小型撞击闪光','大型撞击闪光'][image] if image<4 else f'撞击特效{image:03d}'
    return name if rid in (3,6) else f'{name}_动作{image+1:02d}'

def image_filename(rid,image,frame,total,animation=False,names=()):
    stem=animation_name(rid,image) if animation else bitmap_name(rid,frame,total,names)
    if animation and total>1:stem+=f'_帧{frame:03d}'
    return clean_name(stem)+'.png'

"""Human-readable names based on the recovered callers and the actual artwork.

Purposes come from the code-usage audit. Unresolved variants keep their frame
index; no image-only interpretations are used.
"""
from __future__ import annotations
import re,struct

try:
    from .sango_resource_usage import identity,EVENT76_FRAMES
except ImportError:
    from sango_resource_usage import identity,EVENT76_FRAMES

TROOPS=['骑兵','步兵','弓兵','水军','极兵','玄兵']

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
        group='前十部队' if frame<16 else '后十部队'
        item=frame%16
        if item<12:subject=TROOPS[item//2]
        elif item<14:subject='河流地形部队'
        else:subject='混乱或石阵状态部队'
        return f'{group}_{subject}_交替帧{frame%2}_帧{frame:03d}'
    if rid==4:
        terrain=1 if frame<2 else 0 if frame==2 else 5 if frame==3 else 4 if frame==4 else 3 if frame==5 else 2 if frame<16 else 6 if frame==41 else 7
        label=['草地','平原','山地','森林','村庄','城池','营寨','河流'][terrain]
        return f'{label}_图块{frame:03d}'
    if rid==7:
        label={0:'可移动范围标记',1:'目标位置标记',4:'当前战场光标'}.get(frame,'未定位调用_帧义待确认')
        return f'{label}_帧{frame:03d}'
    if rid==9:return f'天气状态{frame+1:02d}_图标'
    if rid==34:
        label='禁咒标记' if frame in (2,3) else '定身标记' if frame in (4,5) else '未定位调用_帧义待确认'
        return f'{label}_帧{frame:03d}'
    if rid==55:
        label={0:'无归属城市',7:'其他势力城市',8:'当前玩家城市'}.get(frame,'未定位调用_帧义待确认')
        return f'{label}_帧{frame:03d}'
    if rid==69:return '武将数量图标' if frame==0 else '城市数量图标' if frame==1 else f'帧义待确认{frame:03d}'
    if rid==76:return EVENT76_FRAMES[frame]['name'] if frame<4 else f'{name}_帧{frame:03d}'
    return name if total==1 else f'{name}_帧{frame:03d}'

def animation_name(rid,image):
    name=identity(rid)['name']
    # Image roles are not uniquely determined by their appearance or ordinal.
    # The audited group name gives the actual use; keep exact sprite indices.
    return name if rid in (3,6) else f'{name}_精灵{image:03d}'


def image_filename(rid,image,frame,total,animation=False,names=()):
    stem=animation_name(rid,image) if animation else bitmap_name(rid,frame,total,names)
    if animation and total>1:stem+=f'_帧{frame:03d}'
    return clean_name(stem)+'.png'

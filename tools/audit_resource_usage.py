"""Check resource names against code selectors and produce an auditable index."""
from __future__ import annotations
import argparse,hashlib,json,re,struct
from pathlib import Path
import sango_lib as lib
import sango_resource_names as names
from sango_resource_usage import RULES
from source_map import parse_functions,contains_expression,FUNCTION_NAMES,MAPPING

ROOT=Path(__file__).resolve().parents[1]
LIBRARY=ROOT/'assets/library'

def functions(path):
    return parse_functions(path)

def initialized_data():
    text=(ROOT/'src/sango_data.c').read_text(encoding='utf-8')
    values=re.findall(r'0x([0-9a-fA-F]{2})\b',text[text.index('{'):text.index('};')])
    data=bytes(int(value,16) for value in values)
    if len(data)!=45536:raise ValueError('Original initialized-data length changed')
    return data

def record(manifest,rid):
    entry=next(entry for entry in manifest['records'] if entry['id']==rid)
    return lib.asset(LIBRARY,entry['record']).read_bytes()

def subtable(raw,index):
    count,stride=struct.unpack_from('<HH',raw,6)
    if stride:return raw[12+(index-1)*stride:12+index*stride]
    offset,length=struct.unpack_from('<HH',raw,12+(index-1)*4)
    return raw[offset:offset+length]

def text_items(raw):
    size,rid,count,stride,encoding=struct.unpack_from('<IHHHH',raw)
    count=(len(raw)-12)//stride if stride else count
    return [bytes((v-encoding)&255 for v in subtable(raw,i+1)).split(b'\0')[0].decode('gbk',errors='replace') for i in range(count)]

def selectors(manifest):
    data=initialized_data()
    def at(address,length):return data[address-0x81c1fef0:address-0x81c1fef0+length]
    skill_names=text_items(record(manifest,11));skills=[]
    for i,label in enumerate(skill_names):
        rid=struct.unpack_from('<H',at(0x81c20110,64),i*2)[0]
        skills.append({'skill_id':i+1,'name':label,'resource':rid,
            'first_command':at(0x81c2014c,32)[i],'last_command':at(0x81c2016c,32)[i],
            'x_offset':at(0x81c2018c,32)[i],'draw_background_frame':bool(at(0x81c201ac,32)[i])})
    expected={19:[1,2,3,4],20:[8],21:[9,10],35:[5,11,18],36:[12,19],37:[6,7],
              38:[13],39:[14,15,20],40:[16],41:[17,29],42:[23],43:[24]}
    for rid,ids in expected.items():
        if [row['skill_id'] for row in skills if row['resource']==rid]!=ids:
            raise ValueError(f'Skill animation selector changed for resource {rid}; review names')
    terrain_text=text_items(record(manifest,1))[6]
    if terrain_text!='草地平原山地森林村庄城池营寨河流':raise ValueError('Terrain labels changed')
    troop_text=text_items(record(manifest,1))[11]
    if troop_text!='骑兵步兵弓兵水军极兵玄兵':raise ValueError('Troop labels changed')
    cities=text_items(record(manifest,58));types=subtable(record(manifest,2),15)
    if len(types)!=38 or len(cities)!=38 or any(v>6 for v in types):raise ValueError('City battle-map selector changed')
    return {'skills':skills,'ordinary_attack_command_strides':list(at(0x81c201d4,6)),
            'city_maps':[{'city_id':i,'city':city,'map_type':kind,'resource':110+kind} for i,(city,kind) in enumerate(zip(cities,types))]}

def animation_uses(entry,selection):
    rid=entry['id'];timeline=json.loads(lib.asset(LIBRARY,entry['timeline']).read_text(encoding='utf-8'))['commands']
    intervals=[]
    for skill in selection['skills']:
        if skill['resource']==rid:
            intervals.append({'use':'计谋'+skill['name'],'first':skill['first_command'],'last':skill['last_command']})
    if 19<=rid<=24:
        stride=selection['ordinary_attack_command_strides'][rid-19]
        for i,troop in enumerate(names.TROOPS):
            intervals.append({'use':'普通攻击_目标兵种'+troop,'first':stride*i,'last':stride*(i+1)-1})
    elif rid==25:intervals.append({'use':'普通攻击_目标地形为河流','first':0,'last':4})
    elif rid==27:
        intervals.extend([{'use':'武将升级','first':0,'last':5},
                          {'use':'部队生命或兵力耗尽退场','first':6,'last':11},
                          {'use':'攻击或计谋指令目标特效','first':12,'last':17}])
    elif rid in [3,6,*range(100,108)]:
        raw=lib.asset(LIBRARY,entry['record']).read_bytes()
        intervals.append({'use':entry['name'],'first':0,'last':raw[17]})
    for interval in intervals:
        if not 0<=interval['first']<=interval['last']<len(timeline):
            raise ValueError(f'Animation command range out of bounds: {rid} {interval}')
    images=[]
    for i,spec in enumerate(entry['images']):
        commands=[n for n,command in enumerate(timeline) if command[4]==i]
        uses=[interval['use'] for interval in intervals if any(interval['first']<=n<=interval['last'] for n in commands)]
        images.append({'image':i,'pngs':spec['pngs'],'command_indices':commands,
                       'uses':uses,'role':'由时间轴指令引用；不凭画面指定精灵角色'})
    return {'intervals':intervals,'images':images}

def audit(manifest):
    entries=[*manifest['records'],*manifest.get('supplements',[])]
    if {e['id'] for e in entries}!=set(RULES):raise ValueError('Every original/supplemental resource must have a reviewed rule')
    source_cache={};proofs=[];selection=selectors(manifest)
    source_paths={'src/sango_data.c'}
    for entry in entries:
        rid=entry['id'];identity=names.identity(rid);evidence=[]
        for citation in identity['code_evidence']:
            source=citation['source'];source_paths.add(source)
            if source not in source_cache:source_cache[source]=functions(ROOT/source)
            function=source_cache[source].get(citation['function'])
            if not function or not contains_expression(function['source'],citation['expression']):
                raise ValueError(f'Code evidence no longer matches resource {rid}: {citation}')
            evidence.append({**citation,'line':function['line']})
        if not evidence and identity['usage_status']!='unresolved':raise ValueError(f'Missing code evidence for {rid}')
        for key in ['category','name','usage_status','naming_evidence','code_evidence']:
            if entry.get(key)!=identity[key]:raise ValueError(f'Manifest naming rule differs for {rid}: {key}')
        if entry.get('kind'):
            if Path(entry['record']).parent.as_posix()!=names.folder_name(rid):raise ValueError(f'Noncanonical directory for {rid}')
            people=()
            if 48<=rid<=51:
                raw=record(manifest,{48:62,49:70,50:71,51:72}[rid]);encoding=struct.unpack_from('<H',raw,10)[0]
                people=[names.character_name(bytes((v-encoding)&255 for v in raw[i:i+8])) for i in range(12,len(raw),8)]
            for image,spec in enumerate(entry.get('images',[])):
                for frame,png in enumerate(spec['pngs']):
                    expected=names.image_filename(rid,image,frame,spec['frames'],entry['kind']=='animation',people)
                    if Path(png).name!=expected or not lib.asset(LIBRARY,png).is_file():raise ValueError(f'Unreviewed filename for {rid}: {png}')
        proof={'id':rid,**identity,'code_evidence':evidence}
        if rid in (12,74):proof['decoded_text_preview']=text_items(record(manifest,rid))[:3]
        if entry.get('kind')=='animation':proof['animation_usage']=animation_uses(entry,selection)
        if 110<=rid<=116:proof['cities']=[row for row in selection['city_maps'] if row['resource']==rid]
        proofs.append(proof)
    # These helpers are the complete current routes into the library. Record
    # variable arguments too: absence of a literal does not prove dead data.
    unresolved=[]
    helper_names=[FUNCTION_NAMES.get(name,name) for name in ['FUN_81c152f0','FUN_81c04f40','FUN_81c154d8','FUN_81c077bc','FUN_81c06a70','FUN_81c162e0','FUN_81c04fb4']]
    game={}
    for module in MAPPING['modules']:
        source_paths.add(module['file'])
        game.update(functions(ROOT/module['file']))
    for function,body in game.items():
        for text in body['source'].splitlines():
            if any(helper+'(' in text for helper in helper_names) and not text.startswith(('int ','uint ','void ','undefined4 ')):
                unresolved.append({'function':function,'line':text.strip()})
    return {'schema':1,'reviewed_resources':len(entries),
            'source_sha256_lf':{path:lib.sha((ROOT/path).read_text(encoding='utf-8').encode('utf-8')) for path in sorted(source_paths)},
            'resources':proofs,'selectors':selection,'resource_calls_reviewed':unresolved,
            'limits':'12、60、74未定位当前读取路径；未命名的具体天气、未引用帧和精灵角色保留编号，不把静态检查当作完整战役运行验证。'}

def markdown(report):
    lines=['# 资源代码用途核对','',
        '命名依据为读取路径、状态/菜单分支、初始化数据选择表及时间轴引用。图片外观不作为用途证据。',
        '所有帧号从0计数。`已确认`只表示所述用途有代码依据，不代表全部战役已运行验证。','',
        '| ID | 素材 | 核对状态 | 代码依据 |','| --- | --- | --- | --- |']
    statuses={'confirmed':'已确认','historical':'历史调用，当前已替代','unresolved':'调用/用途待确认'}
    for entry in report['resources']:
        refs=[]
        for ref in entry['code_evidence']:
            link=f"../../{ref['source']}#L{ref['line']}";label=ref['function']
            if f'[{label}]({link})' not in refs:refs.append(f'[{label}]({link})')
        lines.append(f"| {entry['id']:03d} | {entry['name']} | {statuses[entry['usage_status']]} | {'、'.join(refs) or '未定位，保留待确认标记'} |")
    lines.extend(['','## 计谋动画选择表','',
        '从 `src/sango_data.c` 原初始化区 0x81c20110、0x81c2014c、0x81c2016c 读取，名称从资源011解码。',
        '`sango_battle_execute_skill` 实际用这些值选择动画及指令区间。零资源和特殊处理分支不推定为动画。','',
        '| 计谋ID | 原名称 | 资源ID | 指令范围 |','| --- | --- | --- | --- |'])
    for row in report['selectors']['skills']:
        if row['resource']:lines.append(f"| {row['skill_id']} | {row['name']} | {row['resource']:03d} | {row['first_command']}～{row['last_command']} |")
    lines.extend(['','## 城市战场选择','',
        '`sango_strategy_resolve_attack` 读取资源002第15子表：战场ID=城市对应类型+110。城市名由资源058解码。','',
        '| 战场资源 | 适用城市 |','| --- | --- |'])
    for rid in range(110,117):
        cities='、'.join(row['city'] for row in report['selectors']['city_maps'] if row['resource']==rid)
        lines.append(f'| {rid} | {cities} |')
    lines.extend(['','## 逐项依据',''])
    for entry in report['resources']:
        lines.extend([f"### {entry['id']:03d} {entry['name']}",'',entry['naming_evidence'],''])
        for citation in entry['code_evidence']:
            lines.append(f"- `{citation['function']}`：`{citation['expression']}`")
        if entry.get('animation_usage'):
            lines.extend(['','已确认的播放区间：'])
            for interval in entry['animation_usage']['intervals']:
                lines.append(f"- 指令{interval['first']}～{interval['last']}：{interval['use']}")
            lines.extend(['','每个精灵被哪些指令/用途引用，见同目录 `code-usage.json` 的 `animation_usage.images`。'])
        lines.append('')
    lines.extend(['## 边界','',report['limits'],''])
    return '\n'.join(lines)

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--check',action='store_true');args=parser.parse_args()
    manifest=json.loads((LIBRARY/'manifest.json').read_text(encoding='utf-8'));report=audit(manifest)
    text=markdown(report);json_text=json.dumps(report,ensure_ascii=False,indent=2)+'\n'
    outputs={LIBRARY/'代码用途核对.md':text,LIBRARY/'code-usage.json':json_text}
    for path,value in outputs.items():
        if args.check:
            if not path.is_file() or path.read_text(encoding='utf-8')!=value:raise ValueError(f'Outdated resource audit: {path.name}')
        else:path.write_text(value,encoding='utf-8',newline='\n')
    print(json.dumps({'passed':True,'reviewed_resources':report['reviewed_resources'],
        'unresolved':[entry['id'] for entry in report['resources'] if entry['usage_status']=='unresolved'],
        'skill_animation_table_checked':True,'city_map_selector_checked':True},ensure_ascii=False))

if __name__=='__main__':main()

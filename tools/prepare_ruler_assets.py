"""Import the wood faction page and crop existing GPT Image ruler portraits.

No generation service is called. Portrait identities come from actual scenario
city owners and same-scenario portrait IDs, not visual guesses. Normal builds
pack the committed files; rerun this only when deliberately importing new art.
"""
from pathlib import Path
import hashlib
import json
import struct
from PIL import Image
import sango_lib as lib
from sango_resource_usage import identity

ROOT = Path(__file__).resolve().parents[1]
COLOR = ROOT/'assets/color'
GRAY = ROOT/'assets/ruler'


def save_json(path, value):
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2)+'\n', encoding='utf8')


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def gray4(image):
    # Container encoding conversion only; the visual work is from GPT Image.
    return image.convert('L').point(lambda v: min(3, (v+42)//85)*85).convert('RGB')


def main():
    GRAY.mkdir(exist_ok=True)
    manifest = json.loads((ROOT/'assets/library/manifest.json').read_text(encoding='utf8'))
    catalog = json.loads((COLOR/'catalog.json').read_text(encoding='utf8'))
    catalog['frames'] = [f for f in catalog['frames'] if f['resource'] not in (52, 53, 77)]
    catalog['batches'] = [b for b in catalog['batches'] if b['id'] not in ('ruler-page', 'ruler-portraits', 'ruler-highlight')]
    originals = {r['id']:r for r in manifest['records']}
    city_records = lib.asset(ROOT/'assets/library', originals[57]['record']).read_bytes()
    stride = struct.unpack_from('<H', city_records, 8)[0]
    portraits, by_key, scenarios = [], {}, []
    mapping = [[255]*19 for _ in range(4)]
    for scenario in range(1, 5):
        cities = city_records[12+(scenario-1)*stride:12+scenario*stride]
        rulers = list(dict.fromkeys(cities[i*31+1]-1 for i in range(38) if cities[i*31+1]))
        uses = []
        for character in rulers:
            source = next(f for f in catalog['frames'] if f['resource']==47+scenario and f['frame']==character)
            key = source['source_rgba_sha256']
            if key not in by_key:
                batch = next(b for b in catalog['batches'] if b['id']==source['batch'])
                item = next(i for i in batch['items'] if i['key']==key)
                master = Image.open(COLOR/batch['master']).convert('RGB')
                rw, rh = batch['canvas']
                box = tuple(round(v*(master.width/rw if n%2==0 else master.height/rh))
                            for n,v in enumerate(item['box']))
                portrait = master.crop(box).resize((48,48), Image.Resampling.LANCZOS)
                name = Path(source['source']).stem.split('_',1)[1].rsplit('_头像',1)[0]
                by_key[key] = len(portraits)
                portraits.append({'image':portrait,'name':name,'source':source,'master':batch['master'],'box':list(box)})
            index = by_key[key]
            assert character < 19
            mapping[scenario-1][character] = index
            uses.append({'character_id':character,'source_portrait_resource':47+scenario,
                         'source_portrait_frame':character,'deck_frame':index,
                         'source_name':source['source']})
        scenarios.append({'scenario':scenario,'rulers':uses})
    assert len(portraits)==33

    groups = {
        52: [('势力选择木质底图', Image.open(COLOR/'generated/wood-ui-ruler-background.png').convert('RGB').resize((240,320),Image.Resampling.LANCZOS))],
        53: [(f'君主{index:03d}_{p["name"]}_预览头像',p['image']) for index,p in enumerate(portraits)],
        77: [('势力选择选中木纹条', Image.open(COLOR/'generated/wood-ui-menu-states.png').convert('RGB').crop((200,24,360,74)).resize((56,18),Image.Resampling.LANCZOS))],
    }
    manifest['supplements'] = [e for e in manifest['supplements'] if e['id'] not in groups]
    for rid, images in groups.items():
        role = identity(rid)
        folder = f'{role["category"]}/{role["name"]}_资源{rid:03d}'
        names = []
        items = []
        atlas = Image.new('RGB',(images[0][1].width*min(8,len(images)),
                                images[0][1].height*((len(images)+7)//8)), 'white')
        batch_id = {52:'ruler-page',53:'ruler-portraits',77:'ruler-highlight'}[rid]
        for frame,(name, image) in enumerate(images):
            original = GRAY/f'{name}.png';gray4(image).save(original)
            destination = COLOR/'library'/folder/f'{name}.png'
            destination.parent.mkdir(parents=True,exist_ok=True);image.save(destination)
            original_name = '../ruler/'+original.name; names.append(original_name)
            key = hashlib.sha256(Image.open(original).convert('RGBA').tobytes()).hexdigest()
            f = {'resource':rid,'name':role['name'],'image':0,'frame':frame,'source':original_name,
                 'size':list(image.size),'source_rgba_sha256':key,'flags':32,
                 'color':destination.relative_to(COLOR).as_posix(),'batch':batch_id,'color_sha256':sha(destination)}
            catalog['frames'].append(f)
            if not any(u['key']==key for u in catalog['unique']):
                catalog['unique'].append({'key':key,'source':original_name,'size':list(image.size),'flags':32})
            x=(frame%8)*image.width;y=(frame//8)*image.height
            atlas.paste(image,(x,y));items.append({'key':key,'box':[x,y,x+image.width,y+image.height]})
        master = COLOR/'generated'/f'{batch_id}-import.png';atlas.save(master)
        catalog['batches'].append({'id':batch_id,'canvas':list(atlas.size),'items':items,
                                  'status':'imported','master':master.relative_to(COLOR).as_posix(),
                                  'master_size':list(atlas.size),'master_sha256':sha(master),
                                  'imported_frames':len(images),'composition':'Existing GPT Image art, crop/resize/encoding only'})
        manifest['supplements'].append({'id':rid,**role,'image':{'width':images[0][1].width,
                   'height':images[0][1].height,'frames':len(images),'flags':32,'pngs':names},'c_includes':[]})
    for entry in manifest['records'] + manifest['supplements']:
        entry.update(identity(entry['id']))
    save_json(ROOT/'assets/library/manifest.json',manifest)
    save_json(COLOR/'catalog.json',catalog)
    header = '/* Generated by tools/prepare_ruler_assets.py from actual scenario owners. */\n'
    header += 'static const unsigned char ruler_portrait_frames[4][19] = {\n'
    header += ''.join('    {'+','.join(str(v) for v in row)+'},\n' for row in mapping)+'};\n'
    (ROOT/'include/sango_ruler_portraits.inc').write_text(header,encoding='ascii')
    save_json(GRAY/'provenance.json',{'generator':'Built-in GPT Image background; existing GPT Image portrait masters',
          'background_master':'../color/generated/wood-ui-ruler-background.png',
          'background_prompt':'../color/prompts/wood-ui-ruler-background.txt',
          'layout_followup_prompt':'../color/prompts/wood-ui-ruler-background-layout.txt',
          'portraits':[{'frame':i,'name':p['name'],'source':p['source']['source'],'master':p['master'],
                       'crop':p['box']} for i,p in enumerate(portraits)],'scenarios':scenarios,
          'portrait_size':[48,48],'portrait_source':'Cropped from the corresponding original GPT Image master, not enlarged24px PNGs',
          'highlight_source':{'master':'../color/generated/wood-ui-menu-states.png','crop':[200,24,360,74],'size':[56,18]}})
    lib.write_resource_index(ROOT/'assets/library',manifest)
    print(json.dumps({'added_resources':[52,53,77],'ruler_faces':len(portraits),'total_color_frames':len(catalog['frames'])}))


if __name__=='__main__':
    main()

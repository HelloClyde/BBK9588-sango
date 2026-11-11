"""Deterministically import reviewed GPT Image wood/settings assets.

This tool only packs/crops/resizes existing generated masters and encodes the
new fallback bitmap. It never calls a generator or repaints source artwork.
"""
from pathlib import Path
import hashlib,json,shutil
from PIL import Image
import color_assets as color
import sango_lib as library
from sango_resource_usage import identity

ROOT=Path(__file__).resolve().parents[1]
COLOR=ROOT/'assets/color'

def save(path,data):
    path.write_text(json.dumps(data,ensure_ascii=False,indent=2)+'\n',encoding='utf8',newline='\n')

def main():
    catalog=color.read_catalog()
    selected=[f for f in catalog['frames'] if f['resource'] in (18,44,45,46,102,104,105,106,107)]
    archive=COLOR/'variants/before-wood-settings'
    if not (archive/'frames.json').exists():
        for f in selected:
            dest=archive/f['color'];dest.parent.mkdir(parents=True,exist_ok=True)
            shutil.copy2(COLOR/f['color'],dest)
        save(archive/'frames.json',selected)
    imports=[]
    for rid,slug,reference in [
        (18,'wood-ui-credits-author','generated/wood-ui-credits.png'),
        (44,'wood-ui-main-menu-settings','generated/wood-ui-main-menu.png'),
        (45,'wood-ui-scenario-page','generated/page-045.png'),
        (46,'wood-ui-save-list','generated/page-046.png')]:
        frame=next(f for f in catalog['frames'] if f['resource']==rid)
        imports.append({'id':slug,'reference':reference,'canvas':[1086,1448],
                        'items':[{'key':frame['source_rgba_sha256'],'box':[0,0,1086,1448]}]})
    # The generator retained the white gutters but shifted their boundaries.
    # Use the actual reviewed rectangle bounds, not the reference-grid guesses.
    frames=sorted((f for f in catalog['frames'] if f['resource'] in (104,105,106,107)),key=lambda f:(f['resource'],f['image']))
    master=Image.open(COLOR/'generated/wood-ui-scenario-states.png').convert('RGB')
    spans=[]
    for y in range(master.height):
        active=sum(min(master.getpixel((x,y)))<230 for x in range(master.width))>master.width*.6
        if active:
            if spans and y==spans[-1][1]:spans[-1][1]=y+1
            else:spans.append([y,y+1])
    spans=[s for s in spans if s[1]-s[0]>master.height/10]
    assert len(spans)==4,spans
    items=[]
    for index,frame in enumerate(frames):
        top,bottom=spans[index//2];half=index%2
        xs=[x for x in range(half*master.width//2,(half+1)*master.width//2)
            if min(master.getpixel((x,(top+bottom)//2)))<230]
        items.append({'key':frame['source_rgba_sha256'],'box':[min(xs),top,max(xs)+1,bottom]})
    imports.append({'id':'wood-ui-scenario-states','reference':'references/wood-ui-scenario-states.png',
                    'canvas':list(master.size),'items':items})
    frames=sorted((f for f in catalog['frames'] if f['resource']==102),key=lambda f:f['image'])
    states=Image.open(COLOR/'generated/wood-ui-settings-menu-states.png').convert('RGB')
    bands=[]
    for y in range(states.height):
        if sum(min(states.getpixel((x,y)))<230 for x in range(states.width))>states.width*.6:
            if bands and y==bands[-1][1]:bands[-1][1]=y+1
            else:bands.append([y,y+1])
    bands=[b for b in bands if b[1]-b[0]>states.height/10]
    assert len(bands)==4,bands
    top,bottom=bands[2];state_items=[]
    for i,frame in enumerate(frames):
        xs=[x for x in range(i*states.width//2,(i+1)*states.width//2)
            if any(min(states.getpixel((x,y)))<230 for y in range(top,bottom))]
        state_items.append({'key':frame['source_rgba_sha256'],'box':[min(xs),top,max(xs)+1,bottom]})
    imports.append({'id':'wood-ui-settings-menu-states','reference':'generated/wood-ui-menu-states.png',
                    'canvas':list(states.size),'items':state_items})
    for batch in imports:
        batch.update(status='reviewed',prompt='prompts/'+batch['id']+'.txt')
        if batch['id']=='wood-ui-settings-menu-states':
            batch['alpha_import']={'mode':'edge-connected-white','minimum_channel':200,'maximum_chroma':40}
        catalog['batches']=[b for b in catalog['batches'] if b['id']!=batch['id']]+[batch]
    color.write_catalog(catalog)
    for batch in imports:
        color.import_atlas(batch['id'],COLOR/'generated'/(batch['id']+'.png'))

    # Settings uses an unused LIB slot. Original87 records/offsets stay intact.
    catalog=color.read_catalog()
    manifest=json.loads((ROOT/'assets/library/manifest.json').read_text(encoding='utf8'))
    gray_dir=ROOT/'assets/settings';gray_dir.mkdir(exist_ok=True)
    native=Image.open(COLOR/'generated/wood-ui-settings-page.png').convert('RGB').resize((240,320),Image.Resampling.LANCZOS)
    native_path=COLOR/'library/补充界面/游戏设置木质底图_资源078/游戏设置木质底图.png'
    native_path.parent.mkdir(parents=True,exist_ok=True);native.save(native_path)
    gray=native.convert('L').point(lambda v:min(3,(v+42)//85)*85).convert('RGB')
    gray_path=gray_dir/'游戏设置木质底图.png';gray.save(gray_path)
    key=hashlib.sha256(gray.convert('RGBA').tobytes()).hexdigest()
    frame={'resource':78,'name':'游戏设置木质底图','image':0,'frame':0,
           'source':'../settings/游戏设置木质底图.png','size':[240,320],
           'source_rgba_sha256':key,'flags':32,'color':native_path.relative_to(COLOR).as_posix(),
           'batch':'wood-ui-settings-page','color_sha256':hashlib.sha256(native_path.read_bytes()).hexdigest()}
    catalog['frames']=[f for f in catalog['frames'] if f['resource']!=78]+[frame]
    if not any(u['key']==key for u in catalog['unique']):
        catalog['unique'].append({'key':key,'source':frame['source'],'size':[240,320],'flags':32})
    batch={'id':'wood-ui-settings-page','reference':'references/wood-ui-settings-layout.png',
           'canvas':[1086,1448],'items':[{'key':key,'box':[0,0,1086,1448]}],
           'status':'imported','master':'generated/wood-ui-settings-page.png',
           'prompt':'prompts/wood-ui-settings-page.txt','imported_frames':1}
    catalog['batches']=[b for b in catalog['batches'] if b['id']!=batch['id']]+[batch]
    catalog['native_frames']=len(catalog['frames']);catalog['unique_frames']=len(catalog['unique'])
    color.write_catalog(catalog)
    manifest['supplements']=[s for s in manifest['supplements'] if s['id']!=78]+[{
        'id':78,**identity(78),
        'image':{'width':240,'height':320,'frames':1,'flags':32,'pngs':[frame['source']]},'c_includes':[]}]
    save(ROOT/'assets/library/manifest.json',manifest)
    library.write_resource_index(ROOT/'assets/library',manifest)
    save(COLOR/'wood-settings-provenance.json',{
        'generator':'built-in GPT Image','date':'2026-11-12','mode':'edit and reference-based generation',
        'changed_resources':[18,44,45,46,102,104,105,106,107],'added_resource':78,
        'previous_native_assets':'variants/before-wood-settings','author_line':'优化作者 HelloClyde',
        'assets':[{'master':'generated/'+b['id']+'.png','prompt':b['prompt'],
                   'master_sha256':hashlib.sha256((COLOR/'generated'/(b['id']+'.png')).read_bytes()).hexdigest(),
                   'items':b['items']} for b in imports+[batch]]})
    print(json.dumps({'changed_native_frames':len(selected),'added_resource':78,'total_frames':len(catalog['frames'])}))

if __name__=='__main__':main()

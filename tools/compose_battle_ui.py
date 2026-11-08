"""Bake fixed 16x16 glyph masks into final-size images, with no glyph resizing.

GPT Image supplies the artwork. This deterministic asset-authoring step crops
the art and places checked-in single-bit typography on the final LCD grid.
It is not a runtime drawing system and needs no installed font to reproduce.
"""
from pathlib import Path
import hashlib,json
from PIL import Image
from color_assets import COLOR,read_catalog,write_catalog

INK=(24,20,8)

def compose():
    root=COLOR/'battle-ui';root.mkdir(exist_ok=True)
    master_path=COLOR/'generated/gold-ui-battle-hud-background.png'
    master=Image.open(master_path).convert('RGB')
    def crop(box,size):
        box=tuple(round(v*(master.width/960 if i%2==0 else master.height/384)) for i,v in enumerate(box))
        return master.crop(box).resize(size,Image.Resampling.LANCZOS)
    legacy=crop((0,80,960,144),(240,16))
    status=Image.new('RGB',(240,24))
    # The original 3:2 layout is baked ONCE into art, without any text in it.
    for y in range(24):
        for x in range(240):status.putpixel((x,y),legacy.getpixel((239 if x==239 else (x*2+1)//3,(y*2+1)//3)))
    toolbar=crop((0,200,960,344),(240,36))
    status.save(root/'status-background-240x24.png')
    toolbar.save(root/'toolbar-background-240x36.png')
    placements=[]
    def text(image,value,left,top,output):
        for i,char in enumerate(value):
            path=root/'glyphs'/f'{char}_16x16.png'
            mask=Image.open(path).convert('RGBA').getchannel('A')
            assert mask.size==(16,16) and set(mask.get_flattened_data())=={0,255}
            image.paste(INK,(left+i*16,top,left+(i+1)*16,top+16),mask)
            placements.append({'character':char,'mask':f'glyphs/{char}_16x16.png','target':output,'rectangle':[left+i*16,top,16,16],'scale':[1,1]})
    text(status,'粮',4,4,'status-row-240x24.png')
    text(status,'天',82,4,'status-row-240x24.png')
    text(toolbar,'信息',71,10,'toolbar-240x36.png')
    text(toolbar,'查找',139,10,'toolbar-240x36.png')
    status.save(root/'status-row-240x24.png')
    toolbar.save(COLOR/'statusbar/toolbar-240x36.png')
    catalog=read_catalog();frame=next(f for f in catalog['frames'] if f['resource']==17)
    frame.update(batch='battle-hud-pixel-grid',color_sha256=hashlib.sha256((COLOR/frame['color']).read_bytes()).hexdigest())
    batch={'id':'battle-hud-pixel-grid','composition':'native-pixel-font','reference':'references/battle-hud-sharp.png','canvas':[960,384],
           'master':master_path.relative_to(COLOR).as_posix(),'master_size':list(master.size),'master_sha256':hashlib.sha256(master_path.read_bytes()).hexdigest(),
           'prompt':'prompts/gold-ui-battle-hud-background.txt','items':[{'key':frame['source_rgba_sha256'],'box':[0,200,960,344]}],
           'status':'imported','imported_frames':1,'font_grid':[16,16],'font_scale':[1,1]}
    catalog['batches']=[b for b in catalog['batches'] if b['id']!=batch['id']]+[batch]
    catalog['native_status_image']={'path':'battle-ui/status-row-240x24.png','source_resource':8,'size':[240,24],
        'sha256':hashlib.sha256((root/'status-row-240x24.png').read_bytes()).hexdigest()}
    write_catalog(catalog)
    (root/'provenance.json').write_text(json.dumps({'artwork_generator':'built-in GPT Image','font_masks':'glyphs/provenance.json',
        'master':batch['master'],'master_sha256':batch['master_sha256'],'prompt':batch['prompt'],'ink_rgb':INK,
        'runtime_scale':[1,1],'placements':placements},ensure_ascii=False,indent=2)+'\n',encoding='utf8')
    print('Baked 240x24 status and 240x36 toolbar; all six glyph masks copied at 1:1.')

if __name__=='__main__':compose()

"""Reimport the eight menu sprites with source-matte-aware downsampling.

No illustrations are regenerated. The reviewed GPT Image masters and crop
rectangles remain unchanged; only alpha decoding/resampling is corrected.
"""
from pathlib import Path
import hashlib,json,shutil
from color_assets import COLOR,read_catalog,write_catalog,import_atlas

def main():
    catalog=read_catalog()
    frames=[f for f in catalog['frames'] if 100<=f['resource']<=103]
    archive=COLOR/'variants/menu-white-matte'
    if not (archive/'frames.json').exists():
        for f in frames:
            dest=archive/f['color'];dest.parent.mkdir(parents=True,exist_ok=True)
            shutil.copy2(COLOR/f['color'],dest)
        (archive/'frames.json').write_text(json.dumps(frames,ensure_ascii=False,indent=2)+'\n',encoding='utf8')
    batches=['wood-ui-menu-states','wood-ui-settings-menu-states']
    for b in catalog['batches']:
        if b['id'] in batches:
            b['alpha_import']={'mode':'edge-connected-white','minimum_channel':200,'maximum_chroma':40}
    write_catalog(catalog)
    for batch in batches:
        import_atlas(batch,COLOR/'generated'/(batch+'.png'))
    c=read_catalog()
    report={'source':'Existing reviewed GPT Image wood menu masters',
            'correction':'Decode edge-connected white source matte, resize premultiplied RGBA, encode binary RGB565 transparent key',
            'previous_assets':'variants/menu-white-matte','changed_frames':[
                {'resource':f['resource'],'image':f['image'],'path':f['color'],'sha256':f['color_sha256']}
                for f in c['frames'] if 100<=f['resource']<=103]}
    (COLOR/'menu-alpha-provenance.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf8')
    print(json.dumps({'reimported_sprites':len(report['changed_frames']),'artwork_regenerated':False}))

if __name__=='__main__':main()

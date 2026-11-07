"""Regenerate the four native-size icon PNGs from the saved GPT Image master."""
from pathlib import Path
import hashlib,json,sys
from PIL import Image
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'sdk'))
from bda_packer.vx_icon import ICON_SPECS,make_vx,rgb565_bytes
def main():
    assets=ROOT/'assets/app-icon';master=Image.open(assets/'icon-gpt-image-master.png').convert('RGB')
    records=[]
    for i,(w,h) in enumerate(ICON_SPECS):
        icon=master.resize((w,h),Image.Resampling.LANCZOS);icon.save(assets/f'icon-{i}-{w}x{h}.png')
        raw=make_vx(w,h,rgb565_bytes([(*p,255) for p in icon.getdata()],(255,255,255),transparent_key=None))
        records.append({'index':i,'size':[w,h],'bytes':len(raw),'vx_sha256':hashlib.sha256(raw).hexdigest()})
    provenance=json.loads((assets/'provenance.json').read_text(encoding='utf-8'));provenance['icons']=records
    provenance['master_sha256']=hashlib.sha256((assets/'icon-gpt-image-master.png').read_bytes()).hexdigest()
    (assets/'provenance.json').write_text(json.dumps(provenance,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
if __name__=='__main__':main()

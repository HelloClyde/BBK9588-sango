"""Export reviewed GPT Image weather art once at the final 18-pixel LCD size."""
from pathlib import Path
import hashlib,json
from PIL import Image
from color_assets import COLOR,read_catalog,write_catalog

def main():
    master=COLOR/'generated/weather-native-sharp.png'
    image=Image.open(master).convert('RGBA')
    assert image.size==(1024,1536)
    out=COLOR/'battle-ui/weather';out.mkdir(parents=True,exist_ok=True)
    frames=[]
    for frame in range(5):
        x,y=(frame%2)*512,(frame//2)*512
        cell=image.crop((x,y,x+512,y+512))
        solid=cell.getchannel('A').point(lambda a:255 if a>=192 else 0)
        bounds=solid.getbbox();assert bounds
        glyph=cell.crop(bounds);alpha=solid.crop(bounds)
        scale=min(16/glyph.width,16/glyph.height)
        size=(max(1,round(glyph.width*scale)),max(1,round(glyph.height*scale)))
        # Quantization/export only. All illustration/color comes from GPT Image.
        rgb=glyph.convert('RGB').quantize(colors=4,dither=Image.Dither.NONE).convert('RGB')
        rgb=rgb.resize(size,Image.Resampling.NEAREST)
        alpha=alpha.resize(size,Image.Resampling.NEAREST)
        target=Image.new('RGBA',(18,18),(0,0,0,0));rgb.putalpha(alpha)
        target.alpha_composite(rgb,((18-size[0])//2,(18-size[1])//2))
        path=out/f'weather-{frame+1:02}-18x18.png';target.save(path)
        frames.append({'frame':frame,'path':path.relative_to(COLOR).as_posix(),
                       'source_cell':[x,y,512,512],'crop':list(bounds),'size':[18,18],
                       'sha256':hashlib.sha256(path.read_bytes()).hexdigest()})
    catalog=read_catalog();catalog['native_weather_images']={
        'source_resource':9,'size':[18,18],'frames':[f['path'] for f in frames]}
    write_catalog(catalog)
    (out/'provenance.json').write_text(json.dumps({
        'generator':'built-in GPT Image','master':master.relative_to(COLOR).as_posix(),
        'master_sha256':hashlib.sha256(master.read_bytes()).hexdigest(),
        'reference':'references/weather-original-five.png','prompt':'prompts/weather-native-sharp.txt',
        'original_order_and_motifs_preserved':True,'runtime_scale':[1,1],
        'export':'Final-size nearest sampling, four RGB colors, binary alpha. Original generated master retained.',
        'frames':frames},ensure_ascii=False,indent=2)+'\n',encoding='utf8',newline='\n')
    print('Exported five original weather motifs at native 18x18; no runtime resizing.')

if __name__=='__main__':main()

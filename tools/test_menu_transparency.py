"""Check white-matte removal and eight real-MIPS menu sprite composites."""
from pathlib import Path
import hashlib,json,struct
from PIL import Image
from color_assets import COLOR,read_catalog,resize_alpha_sprite
from test_color_assets import machine,CONTEXT,LIB_ADDRESS
from test_control_flow import ROOT

def main():
    cases=[]
    def check(name,ok):
        assert ok,name
        cases.append({'name':name,'passed':True})
    # A closed white interior is useful artwork, while outer white is matte.
    fixture=Image.new('RGB',(20,20),'white')
    for y in range(3,17):
        for x in range(3,17):fixture.putpixel((x,y),(90,50,20))
    for y in range(7,13):
        for x in range(7,13):fixture.putpixel((x,y),(255,255,255))
    native=resize_alpha_sprite(fixture,(10,10),{'mode':'edge-connected-white','minimum_channel':200,'maximum_chroma':40})
    check('Outer atlas matte becomes transparent before reduction',native.getpixel((0,0))[3]==0)
    check('Enclosed pale lettering/panel stays opaque',native.getpixel((5,5))[3]==255 and min(native.getpixel((5,5))[:3])>240)
    lib=(ROOT/'build/sango.lib').read_bytes();clr=(ROOT/'build/sango.clr').read_bytes()
    entries={e[0]:e for e in (struct.unpack_from('<IIHHI',clr,32+i*16) for i in range(struct.unpack_from('<I',clr,12)[0]))}
    manifest=json.loads((ROOT/'assets/library/manifest.json').read_text(encoding='utf8'))
    records={r['id']:r for r in manifest['records']};frames=[f for f in read_catalog()['frames'] if 100<=f['resource']<=103]
    m=machine(lib,clr);m.intercept('sango_display_present_context',2,lambda a:None)
    for f in frames:
        rid,img=f['resource'],f['image'];w,h=f['size'];picture=Image.open(COLOR/f['color']).convert('RGBA')
        source=struct.unpack_from('<I',lib,(rid-1)*4)[0]+records[rid]['images'][img]['offset']+6
        _,payload,_,_,flags=entries[source];values=struct.unpack_from('<'+'H'*(w*h),clr,payload)
        white=[]
        for y in range(h):
            for x in range(w):
                q=values[y*w+x]
                if q and (y<2 or y>=h-2 or x<2 or x>=w-2):
                    rgb=((q>>11)*255//31,((q>>5)&63)*255//63,(q&31)*255//31)
                    if min(rgb)>210 and max(rgb)-min(rgb)<35:white.append((x,y))
        check(f'Resource{rid}/{img} has no opaque neutral white edge',not white)
        check(f'Resource{rid}/{img} has declared binary alpha',f['transparency']['mode']=='image-alpha' and set(picture.getchannel('A').get_flattened_data())=={0,255})
        m.pixels.clear();m.call('sango_color_draw_raster',57,49,w,h,LIB_ADDRESS+source,CONTEXT+8,0,instruction_limit=25_000_000)
        actual={(p[1]-57,p[2]-49):p[3] for p in m.pixels}
        expected={(x,y):values[y*w+x] for y in range(h) for x in range(w) if values[y*w+x]}
        check(f'Resource{rid}/{img} real MIPS leaves every alpha-zero pixel untouched',actual==expected)
        # The central ink field is never the connected exterior background.
        check(f'Resource{rid}/{img} keeps the complete lettering field opaque',all(picture.getpixel((x,y))[3]==255 for y in range(14,43) for x in range(15,111)))
    report={'passed':len(cases),'failed':0,'bda_sha256':hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),
            'color_sha256':hashlib.sha256(clr).hexdigest(),'scope':'Source-matte decoding retains enclosed whites; all eight actual packed menu sprites have no neutral-white outer ring. Real compiled MIPS raster leaves alpha-zero pixels unchanged and preserves complete lettering fields. Native compositing checked separately.','cases':cases}
    (ROOT/'build/menu-transparency-validation.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in report.items() if k!='cases'}))

if __name__=='__main__':main()

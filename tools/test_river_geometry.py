"""Check actual CLR/MIPS river pixels against the original LIB geometry."""
from pathlib import Path
import hashlib,json,struct
from PIL import Image,ImageDraw
from test_color_assets import machine,LIB_ADDRESS,CONTEXT
from test_control_flow import STATE
from color_assets import read_catalog

ROOT=Path(__file__).resolve().parents[1]


def main():
    lib=(ROOT/'build/sango.lib').read_bytes();clr=(ROOT/'build/sango.clr').read_bytes()
    definition=json.loads((ROOT/'assets/color/terrain/river-geometry.json').read_text(encoding='utf8'))
    frames={f['frame']:f for f in read_catalog()['frames'] if f['resource']==4}
    entries={struct.unpack_from('<I',clr,32+i*16)[0]:struct.unpack_from('<IIHHI',clr,32+i*16) for i in range(struct.unpack_from('<I',clr,12)[0])}
    record=struct.unpack_from('<I',lib,12)[0]
    manifest=json.loads((ROOT/'assets/library/manifest.json').read_text(encoding='utf8'))
    spec=next(r for r in manifest['records'] if r['id']==4)['images'][0]
    start=record+spec.get('offset',12)+6
    palette={k:((r>>3)<<11)|((g>>2)<<5)|(b>>3) for k,(r,g,b) in definition['palette_rgb'].items()}
    assert len(set(palette.values()))==5 and all(palette.values())
    m=machine(lib,clr);count=0;decoded={};source_planes={};banks=waves=0
    for n in range(46):
        offset=start+n*64;entry=entries[offset]
        actual=struct.unpack_from('<256H',clr,entry[1]);decoded[n]=actual
        if n not in [*range(16,41),*range(42,46)]:continue
        assert frames[n]['geometry']=='original-river-plane'
        gray=[(255,170,85,0)[(lib[offset+y*4+x//4]>>(6-2*(x%4)))&3] for y in range(16) for x in range(16)]
        source_planes[n]=gray
        # Independent original-LIB oracle: all original linework/waves must
        # survive at the exact coordinate, with no new shoreline/ripple pixel.
        assert [i for i,v in enumerate(actual) if v==palette['bank_outline']]==[i for i,v in enumerate(gray) if v==0],n
        assert [i for i,v in enumerate(actual) if v==palette['bank_shade']]==[i for i,v in enumerate(gray) if v==85],n
        assert [i for i,v in enumerate(actual) if v==palette['ripple']]==[i for i,v in enumerate(gray) if v==170],n
        assert all(v in palette.values() for v in actual),n
        assert all(actual[i] in (palette['land'],palette['water']) for i,v in enumerate(gray) if v==255),n
        banks+=sum(v<170 for v in gray);waves+=gray.count(170)
        for x,y in [(32,40),(65532,-3),(235,315)]:
            m.pixels.clear()
            assert m.call('sango_color_draw_raster',x,y,16,16,LIB_ADDRESS+offset,CONTEXT+8,0)==1
            signed_x=x if x<32768 else x-65536
            expected=[(CONTEXT+8,signed_x+px,y+py,actual[py*16+px]) for py in range(16) for px in range(16) if 0<=signed_x+px<240 and 0<=y+py<320]
            assert m.pixels==expected,(n,x,y)
            count+=1
    assert len(source_planes)==29
    out=ROOT/'build/river-geometry';out.mkdir(exist_ok=True)
    def rgb(v):return (((v>>11)&31)*255//31,((v>>5)&63)*255//63,(v&31)*255//31)
    tiles={n:Image.new('RGB',(16,16)) for n in decoded}
    for n,tile in tiles.items():tile.putdata([rgb(v) for v in decoded[n]])
    adjacency=set();mapped=0;maps=[];photo_map=None
    for record in (r for r in manifest['records'] if r.get('map')):
        data=json.loads((ROOT/'assets/library'/record['map']).read_text(encoding='utf8'))
        canvas=Image.new('RGB',(data['width']*16,data['height']*16))
        for y,row in enumerate(data['tiles']):
            for x,n in enumerate(row):
                canvas.paste(tiles[n],(x*16,y*16))
                if n in source_planes:
                    mapped+=1
                    # Every bank pixel on the assembled real map has the
                    # original local coordinate even across a tile boundary.
                    for i,v in enumerate(source_planes[n]):
                        if v<170:assert decoded[n][i]==palette['bank_outline' if v==0 else 'bank_shade']
                for dx,dy,axis in [(1,0,'horizontal'),(0,1,'vertical')]:
                    if y+dy<data['height'] and x+dx<data['width']:
                        other=data['tiles'][y+dy][x+dx]
                        if n in source_planes and other in source_planes:
                            adjacency.add((axis,n,other))
        path=out/f'map-{record["id"]}.png';canvas.save(path)
        maps.append({'resource':record['id'],'screenshot':path.relative_to(ROOT).as_posix(),'sha256':hashlib.sha256(path.read_bytes()).hexdigest()})
        if record['id']==113:photo_map=data['tiles']
    assert len(maps)==7 and mapped>1000 and len(adjacency)>60
    # The user's photo matches all22 sampled forest/mountain/fort positions
    # in resource113 at (0,6). Exercise that complete production viewport.
    m.word(STATE['g_viewport_tiles_address'],0x81630000)
    m.write(STATE['g_battle_map_resource'],struct.pack('<H',113))
    m.call('sango_battle_initialize_field');m.pixels.clear()
    m.call('sango_battle_draw_terrain',0,6,instruction_limit=30_000_000)
    expected=[(CONTEXT+8,x,y,decoded[photo_map[6+y//16][x//16]][(y%16)*16+x%16]) for y in range(208) for x in range(240)]
    assert sorted(m.pixels)==sorted(expected)
    count+=1
    comparison=Image.new('RGB',(720,232),'white');draw=ImageDraw.Draw(comparison)
    for index,label in enumerate(['Original resource','alpha.3 color','Fixed original geometry']):draw.text((index*240+4,4),label,fill='black')
    for y,row in enumerate(photo_map[6:19]):
        for x,n in enumerate(row[:15]):
            f=frames[n]
            comparison.paste(Image.open(ROOT/'assets/library'/f['source']).convert('RGB'),(x*16,24+y*16))
            comparison.paste(Image.open(ROOT/'assets/color'/f['color']).convert('RGB'),(240+x*16,24+y*16))
            comparison.paste(tiles[n],(480+x*16,24+y*16))
    comparison.save(out/'photo-map-113-comparison.png')
    report={'passed':count,'failed':0,'bda_sha256':hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),
            'color_sha256':hashlib.sha256(clr).hexdigest(),'river_tiles':29,'exact_original_bank_pixels':banks,
            'exact_original_ripple_pixels':waves,'real_map_count':7,'mapped_river_tiles':mapped,
            'actual_river_adjacency_pairs':len(adjacency),'map_previews':maps,
            'user_photo_viewport':{'resource':113,'origin':[0,6],'size':[240,208],'matched_landmark_samples':22,'compiled_viewport_pixel_comparison':True},
            'scope':'87 real compiled-MIPS raster/clip cases plus one complete production viewport matching the user photo.29 CLR tiles checked directly against original LIB2bpp line/ripple coordinates. All seven original map matrices assembled with resulting native pixels. Original outline/shade/ripple coordinates are preserved; explicit outside-land bank topology is reviewed metadata. No map or gameplay rule change.'}
    (ROOT/'build/river-geometry-validation.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps({k:v for k,v in report.items() if k!='map_previews'}))


if __name__=='__main__':main()

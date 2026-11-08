"""Verify city matte transparency and the compiled 240x232 strategy painter.

Actual MIPS lookup, color raster/scaling, map tile/city/cursor selection execute;
SDK pixels/strings and footer text boundaries are deterministic host models.
"""
from pathlib import Path
import hashlib,json,struct
from PIL import Image
from color_assets import transparent_background,encode_frame,TRANSPARENT_ZERO,read_catalog
from test_color_assets import machine,expected_pixels,LIB_ADDRESS,COLOR_ADDRESS,CONTEXT
from test_control_flow import ROOT,STATE,BUFFER


def main():
    checks=0
    policy={'mode':'edge-connected-white','minimum_channel':224,'maximum_chroma':20}
    test=Image.new('RGB',(7,7),'white')
    # Closed dark outline with a real white window inside, colored wall detail
    # and opaque black. Only the outside white matte may disappear.
    for x in range(1,6):test.putpixel((x,1),(0,0,0));test.putpixel((x,5),(0,0,0))
    for y in range(1,6):test.putpixel((1,y),(0,0,0));test.putpixel((5,y),(0,0,0))
    test.putpixel((3,2),(250,230,180))
    alpha=transparent_background(test,policy)
    assert alpha=={y*7+x for y in range(7) for x in range(7) if x in (0,6) or y in (0,6)}
    encoded,flags=encode_frame(test,{'flags':0,'transparency':policy})
    assert flags==TRANSPARENT_ZERO and struct.unpack_from('<H',encoded,(3*7+3)*2)[0]==0xffff
    assert struct.unpack_from('<H',encoded,(1*7+1)*2)[0]==1
    checks+=1
    lib=(ROOT/'build/sango.lib').read_bytes();colors=(ROOT/'build/sango.clr').read_bytes()
    count=struct.unpack_from('<I',colors,12)[0]
    entries={e[0]:e for e in (struct.unpack_from('<IIHHI',colors,32+i*16) for i in range(count))}
    catalog=read_catalog();manifest=json.loads((ROOT/'assets/library/manifest.json').read_text(encoding='utf8'))
    city=next(r for r in manifest['records'] if r['id']==55);spec=city['images'][0]
    record=struct.unpack_from('<I',lib,54*4)[0]
    m=machine(lib,colors)
    # All ten ownership frames receive per-frame key metadata; white enclosed
    # architectural details remain real RGB pixels, not a global white key.
    transparent_counts=[]
    for f in [f for f in catalog['frames'] if f['resource']==55]:
        offset=record+spec['offset']+6+f['frame']*64;e=entries[offset]
        assert e[4]&TRANSPARENT_ZERO
        m.pixels.clear()
        m.call('sango_bitmap_draw_frame',40,40,16,16,f['frame'],LIB_ADDRESS+record+spec['offset'],CONTEXT+8)
        assert m.pixels==expected_pixels(lib,colors,e,40,40,CONTEXT+8)
        values=struct.unpack_from('<256H',colors,e[1]);transparent_counts.append(values.count(0))
        assert 0<values.count(0)<256
        assert len(m.pixels)==256-values.count(0)
        checks+=1
    m.word(STATE['g_scratch_buffer_address'],BUFFER+0x1000)
    m.write(STATE['g_scenario_id_view2'],b'\1');m.write(STATE['g_player_character'],b'\0')
    m.write(STATE['g_current_year'],struct.pack('<H',190));m.write(STATE['g_current_month'],b'\1')
    for city in range(38):m.write(STATE['g_first_city_owner']+36*city,bytes([city%3]))
    m.intercept('bbk_memcpy',3,lambda a:m.write(a[0],m.read(a[1],a[2])))
    m.intercept('bbk_strcat',2,lambda a:m.write(a[0],m.text(a[0])+m.text(a[1])+b'\0') or a[0])
    m.intercept('sango_text_draw_context',4,lambda a:None)
    m.intercept('sango_faction_count_characters',1,lambda a:9)
    m.intercept('sango_render_present',1,lambda a:None)
    m.intercept('sango_display_present_context',2,lambda a:None)
    clears=[]
    m.intercept('sango_render_clear_rectangle',5,lambda a:clears.append(a))
    # Exercise all legal camera positions, including final world row/column.
    # Every physical map pixel is painted, and only the footer is cleared.
    for vy in range(3):
        for vx in range(6):
            m.write(BUFFER,bytes([vx,vy,vx+3,vy+3]));m.pixels.clear();clears.clear()
            result=m.call('sango_strategy_draw_map',BUFFER,0,instruction_limit=40_000_000)
            mapped={(x,y) for ctx,x,y,value in m.pixels if y<232}
            assert len(mapped)==240*232,(vx,vy,len(mapped))
            assert clears==[[0,232,239,319,CONTEXT+8]],clears
            assert m.read(BUFFER,4)==bytes([vx,vy,vx+3,vy+3])
            assert 0<=result<=38
            # Scoping must end before the footer and all subsequent painters.
            m.pixels.clear();m.call('sango_color_put_pixel',100,100,0x1234,CONTEXT+8)
            assert m.pixels==[(CONTEXT+8,100,100,0x1234)]
            checks+=1
    # Incremental cursor redraws use the same global pixel boundaries as a full
    # repaint. The displayed map must be identical after each directional move.
    for key,delta,mode in [('up',(0,-1),1),('left',(-1,0),2),('down',(0,1),3),('right',(1,0),4)]:
        state=(1,1,4,4);m.write(BUFFER,bytes(state));m.pixels.clear()
        m.call('sango_strategy_draw_map',BUFFER,0,instruction_limit=40_000_000)
        pixels={(x,y):v for ctx,x,y,v in m.pixels if y<232}
        new=(1,1,4+delta[0],4+delta[1]);m.write(BUFFER,bytes(new));m.pixels.clear()
        m.call('sango_strategy_draw_map',BUFFER,mode,instruction_limit=10_000_000)
        pixels.update({(x,y):v for ctx,x,y,v in m.pixels if y<232})
        m.pixels.clear();m.call('sango_strategy_draw_map',BUFFER,0,instruction_limit=40_000_000)
        full={(x,y):v for ctx,x,y,v in m.pixels if y<232}
        assert pixels==full,key
        checks+=1
    # Missing CLR keeps the original gray-only layout rather than resizing a
    # mixture of old and new raster paths.
    m.call('sango_color_unload');assert m.call('sango_color_strategy_map_begin',CONTEXT+8)==0
    m.pixels.clear();m.call('sango_color_put_pixel',100,100,0x1234,CONTEXT+8)
    assert m.pixels==[(CONTEXT+8,100,100,0x1234)];checks+=1
    report={'passed':checks,'failed':0,'map_rectangle':[0,0,240,232],'logical_tiles':[7,7],
            'viewports':18,'city_frames':10,'city_transparent_pixels':transparent_counts,
            'bda_sha256':hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),
            'color_sha256':hashlib.sha256(colors).hexdigest(),
            'scope':'Real compiled strategy painter, all camera bounds, all ten city frames, white-detail preservation, full map pixel coverage, incremental/full redraw equality, scope and gray fallback. SDK pixels/strings, footer text/count boundaries modeled; native firmware separately checked.'}
    (ROOT/'build/strategy-color-validation.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report))

if __name__=='__main__':main()

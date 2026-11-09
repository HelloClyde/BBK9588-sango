"""Check baked glyph pixels and the optional native HUD image in real MIPS."""
import hashlib,json,struct,zlib
from PIL import Image
from color_assets import COLOR,rgb565
from test_color_assets import machine,CONTEXT,LIB_ADDRESS,COLOR_ADDRESS
from test_control_flow import ROOT,STATE,BUFFER

def main():
    lib=(ROOT/'build/sango.lib').read_bytes();clr=(ROOT/'build/sango.clr').read_bytes();count=0
    tag,offset,size,w,h,source,crc=struct.unpack_from('<8sIIIIII',clr,len(clr)-32)
    assert (tag,size,w,h)==(b'SGHUD01\0',11520,240,24)
    assert offset+size+32==len(clr) and zlib.crc32(clr[offset:offset+size])==crc
    status=Image.open(COLOR/'battle-ui/status-row-240x24.png').convert('RGB')
    assert clr[offset:offset+size]==rgb565(status);count+=1
    provenance=json.loads((COLOR/'battle-ui/provenance.json').read_text(encoding='utf8'))
    ink=tuple(provenance['ink_rgb'])
    for item in provenance['placements']:
        assert item['scale']==[1,1]
        mask=Image.open(COLOR/'battle-ui'/item['mask']).convert('RGBA').getchannel('A')
        assert mask.size==(16,16) and set(mask.get_flattened_data())=={0,255}
        target=status if item['target'].startswith('status-row') else Image.open(COLOR/'statusbar/toolbar-240x36.png').convert('RGB')
        background=Image.open(COLOR/'battle-ui'/('status-background-240x24.png' if item['target'].startswith('status-row') else 'toolbar-background-240x36.png')).convert('RGB')
        left,top,width,height=item['rectangle'];assert (width,height)==(16,16)
        for y in range(16):
            for x in range(16):assert target.getpixel((left+x,top+y))==(ink if mask.getpixel((x,y)) else background.getpixel((left+x,top+y)))
        count+=1
    m=machine(lib,clr)
    assert m.call('sango_color_native_status',LIB_ADDRESS+source)==COLOR_ADDRESS+offset
    assert m.call('sango_color_native_status',LIB_ADDRESS+source+1)==0;count+=1
    m.intercept('sango_battle_toolbar_draw',1,lambda a:None)
    m.intercept('sango_battle_summary_draw',1,lambda a:None)
    m.write(STATE['g_battle_weather'],b'\0')
    m.call('sango_battle_status_draw',instruction_limit=20_000_000)
    pixels=struct.unpack('<5760H',clr[offset:offset+size])
    expected=[(CONTEXT+8,x,208+y,pixels[y*240+x] or 1) for y in range(24) for x in range(240)]
    assert m.pixels==expected,'Native status was scaled or sampled instead of copied 1:1';count+=1
    # Restoration must copy the same native image's field, including its art.
    m.pixels.clear();m.write(BUFFER,'平原'.encode('gbk')+b'\0')
    m.call('sango_battle_status_draw_description',BUFFER,CONTEXT+8,instruction_limit=10_000_000)
    assert m.pixels==[p for p in expected if 159<=p[1]<238];count+=1
    # Backward compatibility: SGCOLOR1 files without the optional image remain valid.
    legacy=bytearray(clr[:offset]);struct.pack_into('<I',legacy,8,len(legacy))
    m.write(COLOR_ADDRESS,legacy)
    assert m.call('sango_color_use_buffer',COLOR_ADDRESS,len(legacy),len(lib),instruction_limit=80_000_000)==1
    assert m.call('sango_color_native_status',LIB_ADDRESS+source)==0;count+=1
    # A damaged recognized trailer must reject the complete allocation, not
    # publish an unbounded or checksum-invalid native pointer.
    for pos,value in [(8,offset+1),(8,32),(8,len(clr)),(12,size-2),(16,239),(20,23),(24,source+1),(28,crc^1)]:
        damaged=bytearray(clr);struct.pack_into('<I',damaged,len(clr)-32+pos,value)
        m.write(COLOR_ADDRESS,damaged)
        assert m.call('sango_color_use_buffer',COLOR_ADDRESS,len(damaged),len(lib),instruction_limit=80_000_000)==0,(pos,value)
        assert m.call('sango_color_native_status',LIB_ADDRESS+source)==0;count+=1
    damaged=bytearray(clr);damaged[offset]^=1;m.write(COLOR_ADDRESS,damaged)
    assert m.call('sango_color_use_buffer',COLOR_ADDRESS,len(damaged),len(lib),instruction_limit=80_000_000)==0;count+=1
    m.write(COLOR_ADDRESS,clr)
    assert m.call('sango_color_use_buffer',COLOR_ADDRESS,len(clr),len(lib),instruction_limit=80_000_000)==1
    m.call('sango_color_unload');assert m.call('sango_color_native_status',LIB_ADDRESS+source)==0;count+=1
    report={'passed':count,'failed':0,'native_image':[240,24],'glyph_cell':[16,16],'glyph_scale':[1,1],
            'rendered_status_pixels_compared':5760,'fixed_characters':'粮天?信息查找',
            'bda_sha256':hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),
            'color_sha256':hashlib.sha256(clr).hexdigest(),
            'scope':'Seven baked single-bit glyph masks match final PNG pixels exactly at integer positions; compiled MIPS copies all 5760 native HUD pixels without scaling, restores the same image region, checks SGHUD01 trailer bounds/CRC/source, legacy compatibility and unload. SDK pixel/text boundaries modeled; native firmware separately checked.'}
    (ROOT/'build/battle-pixel-grid-validation.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report))

if __name__=='__main__':main()

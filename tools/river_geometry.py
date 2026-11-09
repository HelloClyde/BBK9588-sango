"""Decode original 2bpp river geometry with colors from the reviewed atlas.

Generated color PNGs remain palette references. Bank/ripple coordinates and
the water openings are authoritative in the original resource004 planes.
This resource conversion runs at pack time; the game renderer is unchanged.
"""
from pathlib import Path
import hashlib
import json
import struct
from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
COLOR = ROOT / 'assets/color'
DEFINITION = COLOR / 'terrain/river-geometry.json'


def land_pixels(original, sides, corners):
    """White pixels outside each explicitly reviewed original bank side."""
    land = set()
    for side in sides:
        for along in range(16):
            line = [(along, depth) if side == 'N' else
                    (along, 15-depth) if side == 'S' else
                    (depth, along) if side == 'W' else
                    (15-depth, along) for depth in range(4)]
            for point in line:
                if original.getpixel(point) != 255:
                    break
                land.add(point)
    for corner in corners:
        start = (0 if 'W' in corner else 15, 0 if 'N' in corner else 15)
        pending = [start]
        seen = set()
        while pending:
            x, y = pending.pop()
            if (x, y) in seen or not (0 <= x < 16 and 0 <= y < 16):
                continue
            seen.add((x, y))
            if abs(x-start[0]) > 3 or abs(y-start[1]) > 3:
                continue
            if original.getpixel((x, y)) != 255:
                continue
            land.add((x, y))
            pending.extend([(x-1,y),(x+1,y),(x,y-1),(x,y+1)])
    return land


def encode(frame, definition=None):
    definition = definition or json.loads(DEFINITION.read_text(encoding='utf8'))
    if (frame['resource'], frame['image'], frame['size'], frame['flags']) != (4, 0, [16,16], 32):
        raise ValueError('Original river policy requires opaque resource004 16x16 tiles')
    rule = definition['frames'][str(frame['frame'])]
    source = ROOT / 'assets/library' / frame['source']
    if hashlib.sha256(source.read_bytes()).hexdigest() != rule['source_png_sha256']:
        raise ValueError('Original river source changed: '+frame['source'])
    original = Image.open(source).convert('L')
    if set(original.get_flattened_data()) - {0,85,170,255}:
        raise ValueError('Original river source is not four-gray')
    land = land_pixels(original, rule['bank_sides'], rule['land_corners'])
    palette = definition['palette_rgb']
    values = []
    for y in range(16):
        for x in range(16):
            shade = original.getpixel((x,y))
            key = {0:'bank_outline',85:'bank_shade',170:'ripple',255:'water'}[shade]
            if (x,y) in land:
                key = 'land'
            red,green,blue = palette[key]
            values.append(((red>>3)<<11)|((green>>2)<<5)|(blue>>3))
    return struct.pack('<256H',*values)


def main():
    """Refresh source checksums only after reviewing original bank topology."""
    catalog = json.loads((COLOR/'catalog.json').read_text(encoding='utf8'))
    topology = {16:('NS',[]),17:('WE',[]),18:('NW',[]),19:('NE',[]),
                20:('NW',['SE']),21:('SE',['NW']),22:('',[]),23:('SW',['NE']),
                24:('NE',['SW']),25:('NWE',[]),26:('SWE',[]),
                27:('N',['SW','SE']),28:('S',['NW','NE']),29:('SW',[]),
                30:('SE',[]),31:('N',[]),32:('S',[]),33:('W',[]),34:('E',[]),
                35:('', ['NW']),36:('', ['SE']),37:('', ['NW','SE']),
                38:('', ['NE','SW']),39:('', ['NE']),40:('', ['SW']),
                42:('', ['SW','SE']),43:('', ['NW','NE']),44:('NSW',[]),45:('NSE',[])}
    # Exact swatches from existing GPT Image outputs. This changes palette
    # assignment only: no generated geometry or resampling enters the CLR.
    samples = {'land':(1,8,8),'water':(22,8,8),'ripple':(22,6,1),
               'bank_outline':(31,2,0),'bank_shade':(31,1,1)}
    frames = {f['frame']:f for f in catalog['frames'] if f['resource']==4}
    palette = {}; provenance = {}
    for name,(number,x,y) in samples.items():
        path = COLOR/frames[number]['color']
        palette[name] = list(Image.open(path).convert('RGB').getpixel((x,y)))
        provenance[name] = {'path':frames[number]['color'],'pixel':[x,y],
                            'sha256':hashlib.sha256(path.read_bytes()).hexdigest()}
    rules = {}
    for number,(sides,corners) in topology.items():
        frame = frames[number]
        source = ROOT/'assets/library'/frame['source']
        rules[str(number)] = {'bank_sides':list(sides),'land_corners':corners,
                             'source_png_sha256':hashlib.sha256(source.read_bytes()).hexdigest()}
        frame['geometry'] = 'original-river-plane'
    definition = {'schema':1,'source_resource':4,'size':[16,16],
                  'geometry':'Original 2bpp plane: 0=outline,85=bank shade,170=ripple,255=water or outside land. All nonwhite pixels retain exact original coordinates. Outside white land is bounded by reviewed bank sides/corners.',
                  'palette_rgb':palette,'palette_samples':provenance,'frames':rules}
    DEFINITION.parent.mkdir(exist_ok=True)
    DEFINITION.write_text(json.dumps(definition,ensure_ascii=False,indent=2)+'\n',encoding='utf8',newline='\n')
    (COLOR/'catalog.json').write_text(json.dumps(catalog,ensure_ascii=False,indent=2)+'\n',encoding='utf8',newline='\n')
    print('Locked29 river tiles to original resource004 pixel geometry.')


if __name__ == '__main__':
    main()

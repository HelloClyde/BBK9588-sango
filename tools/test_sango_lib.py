"""Resource-codec regression checks; needs no original BDA, LIB or firmware."""
from __future__ import annotations
import copy,json,re,struct,tempfile,unittest
from pathlib import Path
from PIL import Image
import sango_lib as lib

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'assets/library'
ORIGINAL_SHA='42920210b5a130781ed1f1cce4bdaca3fc1bb95f14fac8d88d170a9ad77490a5'

class LibraryTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.manifest=json.loads((SOURCE/'manifest.json').read_text(encoding='utf-8'))
        cls.original=lib.verify_original(SOURCE)
        cls.packed=lib.pack(SOURCE)

    def test_lossless_original(self):
        self.assertEqual(lib.sha(self.original),ORIGINAL_SHA)
        self.assertEqual(len(self.original),439720)
        slots,records=lib.catalog(self.original)
        self.assertEqual((slots,len(records)),(116,87))

    def test_original_records_and_unused_slots(self):
        slots,records=lib.catalog(self.packed)
        self.assertEqual((slots,len(records)),(116,89))
        before={r['id']:r for r in lib.catalog(self.original)[1]}
        for record in records:
            if record['id'] in before:
                old=before[record['id']]
                self.assertEqual(record,old)
                a,b=record['offset'],old['offset']
                self.assertEqual(self.packed[a:a+record['bytes']],self.original[b:b+old['bytes']])
        for rid in range(1,117):
            if rid not in (17,18):
                self.assertEqual(self.packed[(rid-1)*4:rid*4],self.original[(rid-1)*4:rid*4])
        self.assertEqual(len(self.packed),461116)

    def test_maps_are_not_misread_as_images(self):
        maps=[r for r in self.manifest['records'] if r['kind']=='map']
        self.assertEqual([r['id'] for r in maps],list(range(110,117)))
        self.assertEqual(self.manifest['png_frames'],1186)
        for r in maps:
            grid=json.loads((SOURCE/r['map']).read_text(encoding='utf-8'))
            self.assertEqual((grid['width'],grid['height']),(32,32))

    def test_extended_library_can_be_unpacked_and_repacked(self):
        with tempfile.TemporaryDirectory(prefix='sango-roundtrip-') as name:
            root=Path(name)/'assets/library'
            result=lib.unpack(self.packed,root)
            self.assertEqual(len(result['records']),89)
            self.assertEqual(lib.pack(root),self.packed)

    def test_c_fallbacks_and_library_use_identical_pixels(self):
        with tempfile.TemporaryDirectory(prefix='sango-includes-') as name:
            target=Path(name);lib.generate_includes(SOURCE,target)
            for entry in self.manifest['supplements']:
                payload=lib.encode_bitmap(SOURCE,entry['image'])
                for filename in entry['c_includes']:
                    for path in [target/filename,ROOT/'include'/filename]:
                        encoded=bytes(int(x,16) for x in re.findall(r'0x([0-9a-f]{2})',path.read_text()))
                        self.assertEqual(encoded,payload)
                offset=struct.unpack_from('<I',self.packed,(entry['id']-1)*4)[0]
                self.assertEqual(self.packed[offset+12:offset+12+len(payload)],payload)
        # These two reviewed art sources currently share the same bitmap.
        for name in ['statusbar','battle-toolbar']:
            with Image.open(ROOT/f'assets/{name}/toolbar-240x36.png') as image:
                if name=='statusbar':first=image.convert('RGBA').tobytes()
                else:self.assertEqual(image.convert('RGBA').tobytes(),first)

    def test_mask_hidden_pixels_and_unaligned_row_padding(self):
        # Two five-pixel frames: exercise mask polarity, hidden RGB, unused high
        # mask bits, row padding and all four gray levels without image loss.
        raw=struct.pack('<HHBB',5,2,2,33)+bytes((i*73+39)%256 for i in range(16))
        spec=lib.bitmap(raw,0,len(raw))
        self.assertIsNotNone(spec)
        with tempfile.TemporaryDirectory(prefix='sango-mask-') as name:
            root=Path(name)
            exported=lib.export_bitmap(raw,spec,root,'test',root)
            self.assertEqual(lib.encode_bitmap(root,exported,raw),raw)
            path=root/exported['pngs'][0]
            with Image.open(path) as image:
                image=image.convert('RGBA');image.putpixel((0,0),(0,0,0,255));image.save(path)
            edited=lib.encode_bitmap(root,exported,raw)
            self.assertEqual((edited[6]>>6)&1,0)  # opaque mask low bit
            self.assertEqual((edited[10]>>6)&3,3)  # black color plane
            self.assertEqual(edited[6]&0xbf,raw[6]&0xbf)  # other bits retained
            self.assertEqual(edited[14:],raw[14:])  # second frame untouched

    def test_animation_timeline_is_editable(self):
        entry=next(r for r in self.manifest['records'] if r['kind']=='animation')
        with tempfile.TemporaryDirectory(prefix='sango-timeline-') as name:
            root=Path(name)
            record=(SOURCE/entry['record']).read_bytes()
            (root/'record.bin').write_bytes(record)
            commands=json.loads((SOURCE/entry['timeline']).read_text(encoding='utf-8'))
            commands['commands'][0][0]^=1
            lib.write_json(root/'timeline.json',commands)
            revised=copy.deepcopy(entry);revised['record']='record.bin';revised['timeline']='timeline.json'
            for spec in revised['images']:
                for i,path in enumerate(spec['pngs']):
                    target=f"{spec['offset']}-{i}.png";(root/target).write_bytes((SOURCE/path).read_bytes());spec['pngs'][i]=target
            encoded=lib.encode_record(root,revised)
            self.assertEqual(encoded[:18],record[:18])
            self.assertEqual(encoded[18],record[18]^1)
            self.assertEqual(encoded[19:],record[19:])

    def test_map_tile_is_editable(self):
        entry=next(r for r in self.manifest['records'] if r['kind']=='map')
        with tempfile.TemporaryDirectory(prefix='sango-map-') as name:
            root=Path(name);record=(SOURCE/entry['record']).read_bytes()
            (root/'record.bin').write_bytes(record)
            grid=json.loads((SOURCE/entry['map']).read_text(encoding='utf-8'));grid['tiles'][0][0]^=1
            lib.write_json(root/'map.json',grid)
            encoded=lib.encode_record(root,{**entry,'record':'record.bin','map':'map.json'})
            self.assertEqual(encoded[:28],record[:28]);self.assertEqual(encoded[28],record[28]^1)
            self.assertEqual(encoded[29:],record[29:])

    def test_invalid_png_and_escaping_path_are_rejected(self):
        with tempfile.TemporaryDirectory(prefix='sango-invalid-') as name:
            root=Path(name)/'assets/library';root.mkdir(parents=True)
            spec={'width':5,'height':2,'frames':1,'flags':32,'pngs':['image.png']}
            Image.new('RGBA',(4,2),'white').save(root/'image.png')
            with self.assertRaisesRegex(ValueError,'size mismatch'):lib.encode_bitmap(root,spec)
            Image.new('RGBA',(5,2),'red').save(root/'image.png')
            with self.assertRaisesRegex(ValueError,'gray levels'):lib.encode_bitmap(root,spec)
            Image.new('RGBA',(5,2),(0,0,0,0)).save(root/'image.png')
            with self.assertRaisesRegex(ValueError,'transparency'):lib.encode_bitmap(root,spec)
            with self.assertRaisesRegex(ValueError,'escapes'):lib.asset(root,'../../outside.png')

    def test_overlapping_index_is_rejected(self):
        data=bytearray(self.original)
        struct.pack_into('<I',data,4,struct.unpack_from('<I',data,0)[0])
        with self.assertRaises(ValueError):lib.catalog(data)

if __name__=='__main__':unittest.main(verbosity=2)

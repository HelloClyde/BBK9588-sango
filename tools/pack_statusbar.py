"""Pack the GPT Image toolbar master into the game's two-bit LCD format.

Only regenerating the asset needs Pillow; the C build consumes the checked-in
include directly and does not need an image service or Python image library.
"""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct

from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
ASSETS = ROOT / 'assets/statusbar'


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def main() -> None:
    master_path = ASSETS / 'toolbar-gpt-image-master.png'
    master = Image.open(master_path).convert('L')
    # Fixed, reviewed crop of this generated master; no run-time heuristics.
    crop = (0, 203, 2172, 521)
    if master.size != (2172, 724):
        raise ValueError('A different master requires reviewing the crop first')
    target = master.crop(crop).resize((240, 36), Image.Resampling.LANCZOS)
    target = target.point([min(3, (value + 42) // 85) * 85 for value in range(256)])
    target.save(ASSETS / 'toolbar-240x36.png')
    pixels = target.tobytes()
    packed = bytearray(struct.pack('<HHBB', 240, 36, 1, 32))
    for index in range(0, len(pixels), 4):
        packed.append(sum((3 - pixels[index + i] // 85) << (6 - i * 2) for i in range(4)))
    (ASSETS / 'toolbar-240x36.bin').write_bytes(packed)
    include = '/* GPT Image restoration; packed by tools/pack_statusbar.py. */\n'
    include += '\n'.join('  ' + ','.join(f'0x{value:02x}' for value in packed[index:index + 16]) + ','
                         for index in range(0, len(packed), 16)) + '\n'
    (ROOT / 'include/sango_statusbar_bitmap.inc').write_text(include, encoding='ascii')
    provenance = {
        'generator': 'built-in image_gen (GPT Image)',
        'edit_reference': 'toolbar-9288s-reference.png',
        'prompt': 'imagegen-prompt.txt',
        'master': master_path.name, 'master_size': list(master.size),
        'master_sha256': sha(master_path.read_bytes()), 'crop_box': list(crop),
        'target': 'toolbar-240x36.png', 'target_size': [240, 36],
        'target_sha256': sha((ASSETS / 'toolbar-240x36.png').read_bytes()),
        'levels': [0, 85, 170, 255], 'dithering': False,
        'packed_bytes': len(packed), 'packed_sha256': sha(packed),
        'game_palette': '0=white, 1=light gray, 2=dark gray, 3=black; MSB first',
        'display_rectangle': [0, 232, 240, 36],
        'purpose': 'Restore the omitted 9288S Information/Find toolbar in the 9588 C rebuild',
    }
    (ASSETS / 'provenance.json').write_text(json.dumps(provenance, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(provenance, ensure_ascii=False))


if __name__ == '__main__':
    main()

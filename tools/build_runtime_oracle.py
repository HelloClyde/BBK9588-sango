"""Link otherwise discarded formatter code for MIPS differential tests.

This creates an ELF test image only. It never produces an installable BDA.
--source-root may point to a previous checkout or a saved src/include/map tree.
"""
from __future__ import annotations
import argparse
import json
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from build import compiler


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source-root', type=Path, default=ROOT)
    parser.add_argument('--cc')
    parser.add_argument('--output', type=Path, default=ROOT / 'build/runtime-oracle/sango.elf')
    args = parser.parse_args()
    source = args.source_root.resolve()
    output = args.output.resolve()
    output.parent.mkdir(parents=True, exist_ok=True)
    cc = compiler(args.cc)
    mapping = json.loads((source / 'source-map.json').read_text(encoding='utf-8'))
    unity = output.parent / 'engine.c'
    unity.write_text(''.join('#include "' + (source / module['file']).as_posix() + '"\n'
                             for module in mapping['modules']), encoding='utf-8')
    flags = ['-std=gnu99', '-EL', '-march=mips32', '-mabi=32', '-msoft-float',
             '-mno-abicalls', '-G0', '-fno-pic', '-ffreestanding', '-fno-builtin',
             '-fno-strict-aliasing', '-fwrapv', '-Os', '-ffunction-sections', '-fdata-sections',
             '-Wno-incompatible-pointer-types', '-Wno-int-conversion',
             '-I', str(source / 'include'), '-I', str(ROOT / 'sdk/sdk/include')]
    files = [unity, *[source / 'src' / (name + '.c') for name in
                     ('sango_data', 'sango_entry', 'sango_statusbar', 'sango_credits', 'sango_battle_ui')]]
    objects = []
    for index, path in enumerate(files):
        obj = output.parent / f'unit-{index}.o'
        subprocess.run([str(cc), *flags, '-c', str(path), '-o', str(obj)], check=True)
        objects.append(str(obj))
    # Retained runtime code may exceed the production text slot. Test it in a
    # separate region, keeping the legacy initialized-data/state addresses.
    script = output.parent / 'oracle.ld'
    script.write_text('''ENTRY(bda_main)
SECTIONS {
 . = 0x81400000; .text : { *(.text.entry) *(.text*) }
 .rodata : { *(.rodata*) }
 .data : { *(.data*) *(.sdata*) *(.bss*) *(COMMON) }
 ASSERT(. < 0x81500000, "Runtime oracle overlaps test buffers")
 . = 0x81c1fef0; .sango_data : { KEEP(*(.sango_data)) }
 . = 0x81c2b0d0; .sango_bss (NOLOAD) : { . += 0x9a1; }
 /DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.comment) *(.gnu.attributes) }
}
''', encoding='ascii')
    retain = [row['name'] for row in mapping['functions'] if row['original_address'] in
              (0x81c1bd50, 0x81c1c48c, 0x81c1c6d0, 0x81c1ba04)]
    subprocess.run([str(cc), '-EL', '-march=mips32', '-mabi=32', '-msoft-float',
                    '-mno-abicalls', '-fno-pic', '-nostdlib', '-Wl,--gc-sections',
                    '-Wl,--build-id=none', *['-Wl,--undefined=' + name for name in retain],
                    '-Wl,-T,' + str(script), *objects, '-lgcc', '-o', str(output)], check=True)
    print('Linked runtime oracle ELF:', output)


if __name__ == '__main__':
    main()

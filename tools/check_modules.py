"""Compile each engine module alone to reject leaked declarations/macros."""
from __future__ import annotations

import argparse
import json
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from build import compiler
from tools.source_index import validate_layout
from tools.source_map import MAPPING


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--cc')
    args = parser.parse_args()
    validate_layout()
    flags = ['-std=gnu99', '-EL', '-march=mips32', '-mabi=32', '-msoft-float',
             '-mno-abicalls', '-G0', '-fno-pic', '-ffreestanding', '-fno-builtin',
             '-fno-strict-aliasing', '-fwrapv', '-Os', '-Wno-incompatible-pointer-types',
             '-Wno-int-conversion', '-I', str(ROOT / 'include'),
             '-I', str(ROOT / 'sdk/sdk/include'), '-fsyntax-only']
    cc = compiler(args.cc)
    for module in MAPPING['modules']:
        subprocess.run([str(cc), *flags, str(ROOT / module['file'])], check=True)
    print(json.dumps({'passed': len(MAPPING['modules']), 'failed': 0,
                      'scope': 'Each source module compiles independently; not a runtime test.'}))


if __name__ == '__main__':
    main()

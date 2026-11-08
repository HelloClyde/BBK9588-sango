"""Check the modular source layout and generate its searchable function index."""
from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

try:
    from .source_map import MAPPING, ROOT, parse_functions
except ImportError:
    from source_map import MAPPING, ROOT, parse_functions

INDEX = ROOT / 'docs/FUNCTION_INDEX.md'


def validate_layout():
    """Reject missing, duplicated, reordered or unmapped function definitions."""
    definitions = {}
    ordered_names = []
    module_paths = []
    for module in MAPPING['modules']:
        relative = module['file']
        path = (ROOT / relative).resolve()
        if not path.is_relative_to((ROOT / 'src').resolve()) or not path.is_file():
            raise ValueError('Invalid source module: ' + relative)
        module_paths.append(relative)
        functions = parse_functions(path)
        if len(functions) != module['functions']:
            raise ValueError('Module function count differs: ' + relative)
        text = path.read_text(encoding='utf-8')
        # Address comments and historical labels remain useful for tracing.
        # Opaque recovered function/global/type identifiers do not belong in C.
        if re.search(r'\b(?:FUN_[0-9a-fA-F]+|DAT_[0-9a-fA-F]+|undefined[1248]?)\b', text):
            raise ValueError('Unmigrated recovered identifier: ' + relative)
        for name, definition in functions.items():
            if name in definitions:
                raise ValueError('Duplicate definition: ' + name)
            definitions[name] = {**definition, 'file': relative}
            ordered_names.append(name)
    if len(module_paths) != len(set(module_paths)):
        raise ValueError('Duplicate module path')
    if ordered_names != [row['name'] for row in MAPPING['functions']]:
        raise ValueError('Function order differs from source-map.json')
    for row in MAPPING['functions']:
        if definitions[row['name']]['file'] != row['file']:
            raise ValueError('Function mapped to the wrong module: ' + row['name'])
    actual_paths = {
        path.relative_to(ROOT).as_posix()
        for directory in {Path(path).parts[1] for path in module_paths}
        for path in (ROOT / 'src' / directory).glob('*.c')
    }
    if actual_paths != set(module_paths):
        raise ValueError('An engine source is missing from the build map')
    aliases = [view['alias'] for view in MAPPING['memory_views']]
    if len(aliases) != len(set(aliases)):
        raise ValueError('Duplicate legacy-memory alias')
    return definitions


def render(definitions):
    lines = [
        '# 函数索引', '',
        '由 `python tools/source_index.py` 生成；手工阅读入口见 [源码导航](SOURCE_GUIDE.md)。',
        '原地址用于对照恢复记录，不代表重新链接后的函数地址。未确认的兼容空入口保留 `stub` 名称。', '',
    ]
    for module in MAPPING['modules']:
        path = module['file']
        lines.extend([f"## {path}", '', module['description'] + '。', '',
                      '| 原地址 | 当前函数／源码位置 |', '| --- | --- |'])
        for row in MAPPING['functions']:
            if row['file'] == path:
                line = definitions[row['name']]['line']
                lines.append(f"| `0x{row['original_address']:08x}` | "
                             f"[`{row['name']}`](../{path}#L{line}) |")
        lines.append('')
    return '\n'.join(lines)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true', help='Fail if the checked-in index is stale')
    parser.add_argument('--find', metavar='NAME_OR_ADDRESS', help='Find a current/legacy name or original address')
    args = parser.parse_args()
    definitions = validate_layout()
    if args.find:
        query = args.find.lower().removeprefix('0x')
        matches = [row for row in MAPPING['functions'] if
                   query in row['name'].lower() or query in row['legacy_name'].lower() or
                   query in f"{row['original_address']:08x}"]
        for row in matches:
            print(f"{row['file']}:{definitions[row['name']]['line']}  {row['signature']}  "
                  f"[original 0x{row['original_address']:08x}]")
        if not matches:
            raise SystemExit('No matching function')
        return
    text = render(definitions)
    if args.check:
        if not INDEX.is_file() or INDEX.read_text(encoding='utf-8') != text:
            raise ValueError('Stale function index; run python tools/source_index.py')
    else:
        INDEX.write_text(text, encoding='utf-8', newline='\n')
    print(json.dumps({'modules': len(MAPPING['modules']), 'functions': len(definitions),
                      'index_current': True}))


if __name__ == '__main__':
    main()

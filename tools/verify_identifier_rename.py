"""Verify a naming-only edit against a saved modular source/ELF baseline.

Uses the historical-to-current local mappings in source-map.json. Function
definitions must match token for token after identifier substitution, including
operators, constants, types, declarations and control flow. Comments and layout
are ignored. Also requires identical production BDA and LIB bytes.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import re

from source_map import ROOT, MAPPING, RECOVERED_LOCAL, c_tokens, code_only, parse_functions, translate


def without_comments(text):
    # Preserve string/character literals: their contents affect behavior.
    return re.sub(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*[\s\S]*?\*/|//[^\n]*',
                  lambda m:' ' if m[0].startswith(('/*','//')) else m[0],text)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--baseline',required=True,type=Path,
                        help='Contains src/, source-map.json, sango.elf, 三国霸业.bda and sango.lib')
    parser.add_argument('--report',type=Path,default=ROOT/'build/identifier-rename-validation.json')
    args=parser.parse_args()
    baseline=json.loads((args.baseline/'source-map.json').read_text(encoding='utf-8'))
    previous={row['legacy_name']:row for row in baseline['functions']}
    if set(previous)!={row['legacy_name'] for row in MAPPING['functions']}:
        raise ValueError('Function set changed')
    before={};after={}
    for module in baseline['modules']:
        before.update(parse_functions(args.baseline/module['file']))
    for module in MAPPING['modules']:
        after.update(parse_functions(ROOT/module['file']))
    changed=[];identifier_count=label_count=0
    for row in MAPPING['functions']:
        old=previous[row['legacy_name']]
        source=before[old['name']]['source']
        candidate=after[row['name']]['source']
        identifiers=set(re.findall(r'\b[A-Za-z_]\w*\b',code_only(source)))
        renames={}
        for historical,current in row['locals'].items():
            prior=old['locals'].get(historical,historical)
            if prior not in identifiers or prior==current:
                continue
            if prior in renames and renames[prior]!=current:
                raise ValueError('Ambiguous rename: '+row['name']+': '+prior)
            renames[prior]=current
        expected=translate(source,renames)
        if c_tokens(without_comments(expected))!=c_tokens(without_comments(candidate)):
            raise ValueError('Non-naming change: '+row['name'])
        if RECOVERED_LOCAL.search(code_only(candidate)):
            raise ValueError('Opaque name remains: '+row['name'])
        if renames:
            changed.append(row['name'])
            labels=set(re.findall(r'(?m)^\s*([A-Za-z_]\w*):',code_only(source)))
            label_count+=sum(name in labels for name in renames)
            identifier_count+=sum(name not in labels for name in renames)
    artifacts={}
    for name in ('三国霸业.bda','sango.lib'):
        left=(args.baseline/name).read_bytes();right=(ROOT/'build'/name).read_bytes()
        if left!=right:
            raise ValueError('Production artifact changed: '+name)
        artifacts[name]={'bytes':len(right),'sha256':sha(right),'byte_identical':True}
    report={'passed':True,'functions_checked':len(previous),'functions_renamed':len(changed),
            'variables_or_parameters_renamed':identifier_count,'labels_renamed':label_count,
            'remaining_recovered_locals_or_labels':0,'artifacts':artifacts,
            'baseline_elf_sha256':sha((args.baseline/'sango.elf').read_bytes()),
            'candidate_elf_sha256':sha((ROOT/'build/sango.elf').read_bytes()),
            'source_sha256_lf':{module['file']:sha((ROOT/module['file']).read_text(encoding='utf-8').encode('utf-8'))
                                for module in MAPPING['modules']},
            'changed_functions':changed,
            'scope':'All mapped function tokens match after local identifier substitution; production '
                    'BDA and library bytes are identical. This does not extend prior gameplay coverage '
                    'or establish a stronger meaning for unresolved legacy arguments.'}
    args.report.parent.mkdir(parents=True,exist_ok=True)
    args.report.write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({key:value for key,value in report.items() if key not in ('source_sha256_lf','changed_functions')},ensure_ascii=False))


if __name__=='__main__':
    main()

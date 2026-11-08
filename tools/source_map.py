"""Shared navigation and identifier migration for the modular C sources."""
from __future__ import annotations
import json,re
from pathlib import Path

ROOT=Path(__file__).resolve().parents[1]
MAPPING=json.loads((ROOT/'source-map.json').read_text(encoding='utf-8'))
FUNCTIONS={row['legacy_name']:row for row in MAPPING['functions']}
FUNCTION_NAMES={old:row['name'] for old,row in FUNCTIONS.items()}
TOKEN=re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|\b[A-Za-z_]\w*\b')

def translate(text,identifiers):
    return TOKEN.sub(lambda m:m[0] if m[0][0] in '\"\'' else identifiers.get(m[0],m[0]),text)

def resolve_reference(function,expression,source):
    if source.startswith('docs/original-'):
        return {'source':source,'function':function,'expression':expression}
    row=FUNCTIONS.get(function)
    identifiers={**MAPPING['type_names'],**FUNCTION_NAMES}
    if row and source=='src/sango_game.c':
        source=row['file']
        identifiers.update(row['globals']);identifiers.update(row['locals'])
    return {'source':source,'function':FUNCTION_NAMES.get(function,function),
            'expression':translate(expression,identifiers)}

def parse_functions(path):
    """Find top-level definitions, preserving offsets and ignoring comments/literals."""
    text=path.read_text(encoding='utf-8')
    pattern=r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*[\s\S]*?\*/|//[^\n]*'
    masked=re.sub(pattern,lambda m:re.sub(r'[^\n]',' ',m[0]),text)
    header=re.compile(r'(?m)^(?:[A-Za-z_]\w*[\s*]+)+?([A-Za-z_]\w*)\(')
    result={}
    for match in header.finditer(masked):
        pos=match.end();depth=1
        while depth:
            if masked[pos]=='(':depth+=1
            elif masked[pos]==')':depth-=1
            pos+=1
        while pos<len(masked) and masked[pos].isspace():pos+=1
        if pos>=len(masked) or masked[pos]!='{':continue
        end=pos+1;depth=1
        while depth:
            if masked[end]=='{':depth+=1
            elif masked[end]=='}':depth-=1
            end+=1
        result[match[1]]={'source':text[match.start():end],
            'line':text.count('\n',0,match.start())+1,'start':match.start(),'end':end}
    return result

def c_tokens(text):
    return tuple(re.findall(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[A-Za-z_]\w*|0[xX][0-9a-fA-F]+[uUlL]*|\d+[uUlL]*|[^\s]',text))

def contains_expression(source,expression):
    body=c_tokens(source);part=c_tokens(expression)
    return any(body[i:i+len(part)]==part for i in range(len(body)-len(part)+1))

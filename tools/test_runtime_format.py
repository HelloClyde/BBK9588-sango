"""Compare the actual retained MIPS formatters with the pre-refactor version."""
import argparse
import itertools
import json
import hashlib
from pathlib import Path
import struct

from test_control_flow import Machine, BUFFER, ROOT


def run(image, format_string, words, alignment):
    machine = Machine(image)
    machine.write(BUFFER, format_string + b'\0')
    machine.write(BUFFER + 0x400, b'example\0')
    machine.write(BUFFER + 0x420, b'\xd6\xd0\xce\xc4\0')
    machine.word(BUFFER + 0x700, 0xa5a5a5a5)
    argument_address = BUFFER + 0x300 + alignment
    aligned = (argument_address + 3) & ~3
    for index, word in enumerate(words):
        machine.word(aligned + index * 4, word)
    machine.word(BUFFER + 0x800, BUFFER + 0x900)
    result = machine.call('sango_crt_vformat', BUFFER, argument_address,
                          machine.symbols['sango_crt_append_character'], BUFFER + 0x800)
    end = struct.unpack('<I', machine.read(BUFFER + 0x800, 4))[0]
    assert BUFFER + 0x900 <= end < BUFFER + 0x1900
    return result, machine.read(BUFFER + 0x900, end - BUFFER - 0x900), machine.read(BUFFER + 0x700, 4)


def cases():
    for conversion in ('d', 'i', 'u', 'o', 'x', 'X', 'D', 'U', 'O', 'p'):
        for flags in ('', '#', '+', ' ', '-', '0', '#0', '+0', '-+', '#-'):
            for width in ('', '1', '4', '12'):
                for precision in ('', '.0', '.1', '.8'):
                    for value in (0, 1, 15, 16, 127, 255, 32768, 0x80000000, 0xffffffff):
                        yield ('[' + '%' + flags + width + precision + conversion + ']').encode(), [value]
    for length in ('h', 'l', 'L', 'hl', 'lh'):
        for conversion in ('d', 'u', 'x', 'n'):
            for value in (0, 255, 32767, 32768, 65535, 0xffffffff):
                yield ('%' + length + conversion).encode(), [BUFFER + 0x700 if conversion == 'n' else value]
    for precision, width, value in itertools.product((-2, -1, 0, 3, 12), (-12, -1, 0, 1, 12), (0, 15, 0xffffffff)):
        yield b'%#0*.*x', [width, precision, value]
    for pointer in (0, BUFFER + 0x400, BUFFER + 0x420):
        for spec in (b'%s', b'%12s', b'%-12s', b'%.0s', b'%.3s', b'%012.3s'):
            yield spec, [pointer]
    for value in (0, 10, 65, 128, 255):
        yield b'%8c', [value]
    for text in (b'', b'plain', b'a\nb', b'%%', b'%q', b'%\n', b'prefix%', b'%.',
                 b'%#.0X %x %X', b'abc%n%d%hn', b'%+06d\n%#x!'):
        if b'%n' in text:
            yield text, [BUFFER + 0x700, 12, BUFFER + 0x700]
        else:
            yield text, [0, 10, 15]


def run_strtol(image, text, base):
    machine = Machine(image)
    machine.write(BUFFER, text + b'\0')
    machine.word(BUFFER + 0x700, 0)
    result = machine.call('sango_crt_strtol', BUFFER, BUFFER + 0x700, base)
    return result, machine.read(BUFFER + 0x700, 4), machine.read(0x81c2b198, 4)


def strtol_cases():
    texts = [b'', b' ', b'\t\r\n-42x', b'+', b'-', b'0', b'00', b'09', b'0x', b'0xFF',
             b'-0X80000000', b'2147483646', b'2147483647', b'2147483648', b'4294967295',
             b'123abc', b'xyz', b'777777777777777777777', b'\xff123']
    texts += [str(value).encode() for value in (-2147483648, -32768, -1, 1, 8, 9, 16, 32767, 2147483647)]
    for text, base in itertools.product(texts, (0, 2, 8, 10, 11, 16, 36)):
        yield text, base


def run_field_formatter(image, format_string, words):
    machine = Machine(image)
    machine.write(BUFFER, format_string + b'\0')
    machine.write(BUFFER + 0x400, b'example\0')
    for index, word in enumerate(words):
        machine.word(BUFFER + 0x300 + index * 4, word)
    function = ('sango_crt_format_words' if 'sango_crt_format_words' in machine.symbols
                else 'sango_crt_format_integer_words')
    result = machine.call(function, 0x4d, BUFFER + 0x900, BUFFER, BUFFER + 0x300)
    assert 0 <= result < 4096
    return result, machine.read(BUFFER + 0x900, result)


def field_cases():
    for conversion in ('d', 'i', 'u', 'o', 'x', 'X'):
        for flags, width, precision, value in itertools.product(
                ('', '#', '+', '-', '0', '#0', '+0'), ('', '8'), ('', '.0', '.4'),
                (0, 1, 255, 0x80000000, 0xffffffff)):
            yield ('%' + flags + width + precision + conversion).encode(), [value]
    for value in (0.0, 1.0, 1.2345, -3.125, 0.00001, 1234567.0, float('inf'), float('nan')):
        words = list(struct.unpack('<II', struct.pack('<d', value)))
        for spec in (b'%f', b'%e', b'%.0f', b'%.3f', b'%12.5e', b'%+012.3f'):
            yield spec, words
    for spec in (b'%s', b'%12s', b'%-12.3s', b'%%', b'%q', b'plain'):
        yield spec, [BUFFER + 0x400]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--baseline', required=True, type=Path)
    parser.add_argument('--candidate', required=True, type=Path)
    parser.add_argument('--report', type=Path, default=ROOT / 'build/runtime-format-validation.json')
    parser.add_argument('--only', choices=('vformat', 'fields', 'strtol'))
    args = parser.parse_args()
    before, after = args.baseline.read_bytes(), args.candidate.read_bytes()
    count = 0
    groups = {}
    if args.only in (None, 'vformat'):
        for format_string, words in cases():
            for alignment in (0, 1, 2, 3):
                left, right = run(before, format_string, words, alignment), run(after, format_string, words, alignment)
                if left != right:
                    raise AssertionError((format_string, words, alignment, left, right))
                count += 1
            if count % 2000 == 0:
                print(f'Runtime formatter cases: {count}, failed: 0', flush=True)
        groups['vformat'] = count
    for name, cases_function, run_function in [('fields', field_cases, run_field_formatter),
                                               ('strtol', strtol_cases, run_strtol)]:
        if args.only and args.only != name:
            continue
        passed = 0
        for case in cases_function():
            left, right = run_function(before, *case), run_function(after, *case)
            if left != right:
                raise AssertionError((name, case, left, right))
            passed += 1
        groups[name] = passed
    report = {'passed': sum(groups.values()), 'failed': 0, 'groups': groups,
              'baseline_elf_sha256': hashlib.sha256(before).hexdigest(),
              'candidate_elf_sha256': hashlib.sha256(after).hexdigest(),
              'scope': 'The reported groups execute retained MIPS runtime code in a separate ELF. '
                       'vformat compares counts, emitted bytes, %n writes and O32 alignment; fields '
                       'compares integer/float/string conversion; strtol compares value, end pointer and errno. '
                       'Legacy quirks are preserved. vformat itself is discarded from the production BDA. '
                       'This is a host CPU model, not firmware or hardware validation.'}
    args.report.parent.mkdir(parents=True, exist_ok=True)
    args.report.write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(report))


if __name__ == '__main__':
    main()

"""Run compiled menu/table paint scopes and ruler input on modeled SDK surfaces."""
import hashlib
import json
import struct

from test_control_flow import Machine, ROOT, STATE, BUFFER
from test_touch_input import event

IMAGE = (ROOT / 'build/sango.elf').read_bytes()
WINDOW, CANVAS = 0x81600000, 0x81600004


def context(m):
    return struct.unpack('<I', m.read(STATE['g_draw_context'], 4))[0]


def surfaces(m, fail=False):
    trace = []
    m.word(STATE['g_draw_context'], WINDOW)

    def snapshot(a):
        assert a == [WINDOW] and context(m) == WINDOW
        trace.append(('snapshot',))
        return 0 if fail else CANVAS

    def present(a):
        assert a == [CANVAS, WINDOW] and context(m) == WINDOW
        trace.append(('present',))

    def free(a):
        assert a == [CANVAS] and context(m) == WINDOW
        trace.append(('free',))

    m.intercept('sango_color_sdk_snapshot', 1, snapshot)
    if 'sango_ui_paint_sdk_present' in m.symbols:
        m.intercept('sango_ui_paint_sdk_present', 2, present)
    m.intercept('sango_color_sdk_snapshot_free', 1, free)
    return trace


def drawing(m, trace):
    m.intercept('bbk_strlen', 1, lambda a: len(m.text(a[0])))
    for name, count in [('sango_display_fill_gray_rectangle', 6),
                        ('sango_display_fill_rectangle', 6),
                        ('sango_display_draw_rectangle', 7),
                        ('sango_display_invert_rectangle', 5),
                        ('sango_bitmap_draw_resource', 5),
                        ('sango_display_put_gray_pixel', 4)]:
        m.intercept(name, count,
                    lambda a, name=name: trace.append((name, context(m), a)))
    m.intercept('sango_text_draw_legacy', 3,
                lambda a: trace.append(('text', context(m), a[:2], m.text(a[2]))))


def input_queue(m, trace, events):
    pending = list(events)

    def read(a):
        assert context(m) == WINDOW, 'Input waited with the window context redirected'
        assert pending, 'Controller consumed all events without returning'
        trace.append(('input',))
        m.write(a[0], struct.pack('<IIHH', *pending.pop(0)))

    m.intercept('sango_input_next_event', 1, read)
    return pending


def ruler(image, count, events, fail=False):
    m = Machine(image)
    trace = surfaces(m, fail)
    drawing(m, trace)
    names, ids, positions = BUFFER + 1024, BUFFER + 1536, BUFFER + 2048
    m.word(STATE['g_move_costs_address'], names)
    m.word(STATE['g_temp_character_ids_address'], ids)
    # Uninitialized heap contents used to survive the final padded name.
    m.write(names, b'X' * 250 + b'\xa5\0')
    m.write(ids, bytes(range(50, 136)))
    m.write(positions, bytes(range(80)))
    m.intercept('sango_load_named_text', 2,
                lambda a: m.write(a[1], ('刘备' if a[0] % 2 else '诸葛亮').encode('gbk') + b'\0'))
    m.intercept('sango_resource_read_text', 3,
                lambda a: m.write(a[2], '选择势力'.encode('gbk') + b'\0'))
    m.intercept('sango_resource_item', 3, lambda a: positions)

    def cities(a):
        trace.append(('cities', a[0]))
        m.write(a[1], b'\x00\x01')
        return 2

    m.intercept('sango_faction_list_cities', 2, cities)
    pending = input_queue(m, trace, events)
    result = m.call('sango_menu_choose_ruler', count)
    assert not pending and context(m) == WINDOW
    assert m.read(names + 250, 2) == b'\xa5\0', 'Name buffer overflow'
    return result, trace, m.read(names, 250)


def main():
    cases = []

    def check(name, ok):
        assert ok, name
        cases.append({'name': name, 'passed': True})

    m = Machine(IMAGE)
    trace = surfaces(m)
    m.call('sango_ui_paint_end')
    check('Unmatched end does not publish/free a surface', not trace)
    m.call('sango_ui_paint_begin')
    m.call('sango_ui_paint_begin')
    check('Nested begin reuses one compatible surface', context(m) == CANVAS and len(trace) == 1)
    m.call('sango_ui_paint_end')
    check('Nested end leaves content offscreen', context(m) == CANVAS and len(trace) == 1)
    m.call('sango_ui_paint_end')
    check('Outermost end restores context, publishes once, then frees',
          context(m) == WINDOW and trace == [('snapshot',), ('present',), ('free',)])
    for _ in range(2):
        m.call('sango_ui_paint_begin')
        m.call('sango_ui_paint_end')
    check('Subsequent redraw scopes allocate and free independently', len(trace) == 9)
    for available in (0, WINDOW):
        m = Machine(IMAGE)
        trace = surfaces(m, fail=True)
        m.word(STATE['g_draw_context'], available)
        m.call('sango_ui_paint_begin')
        m.call('sango_ui_paint_begin')
        m.call('sango_ui_paint_end')
        m.call('sango_ui_paint_end')
        check(f'Unavailable canvas/context {available:x} safely falls back without leaking',
              context(m) == available and not any(t[0] in ('present', 'free') for t in trace))

    key = lambda code: event(5, key=code)
    for keys, answer, repaints in [([key(0x1c)], 0, 1), ([key(1)], 255, 1),
                                  ([key(0x6c), key(0x1c)], 1, 1),
                                  ([key(0x6c)] * 4 + [key(0x1c)], 4, 3)]:
        m = Machine(IMAGE)
        trace = surfaces(m)
        drawing(m, trace)
        m.write(BUFFER, struct.pack('<4H', 20, 40, 44, 76))
        m.write(BUFFER + 100, b'AAAABBBBCCCCDDDDEEEEFFFFGGGG\0')
        pending = input_queue(m, trace, keys)
        result = m.call('sango_ui_choose_option', BUFFER, 0, BUFFER + 100)
        check(f'Option menu result {answer} retains navigation/confirm/cancel', result == answer and not pending)
        check(f'Option menu {answer} publishes initial/scroll text in complete scopes',
              sum(t[0] == 'present' for t in trace) == repaints and
              all(t[1] == CANVAS for t in trace if t[0] == 'text'))
        check(f'Option menu {answer} uses the window for native selection inversion',
              all(t[1] == WINDOW for t in trace if t[0] == 'sango_display_invert_rectangle'))

    for kind in ('character', 'item'):
        for keys, answer in [([key(0x1c)], 0), ([key(1)], 255),
                             ([key(0x6c)] * 5 + [key(0x1c)], 5),
                             ([key(0x6a), key(0x1c)], 0)]:
            m = Machine(IMAGE)
            trace = surfaces(m)
            drawing(m, trace)
            m.write(BUFFER, bytes(range(20)))
            for suffix, n in [('header', 4), ('row', 5)]:
                def draw(a, suffix=suffix):
                    trace.append((suffix, context(m), a))
                    return a[0] + 2 if suffix == 'header' else 0
                m.intercept(f'sango_ui_draw_{kind}_{suffix}', n, draw)
            pending = input_queue(m, trace, keys)
            result = m.call(f'sango_ui_select_{kind}', BUFFER, 20, 4, 2, 235, 61)
            check(f'{kind} roster {answer}/{keys[0][1]} preserves input result', result == answer and not pending)
            check(f'{kind} roster {answer}/{keys[0][1]} batches headers and all rows',
                  all(t[1] == CANVAS for t in trace if t[0] in ('header', 'row')) and
                  any(t[0] == 'present' for t in trace))
            check(f'{kind} roster {answer}/{keys[0][1]} inverts only the native window',
                  all(t[1] == WINDOW for t in trace if t[0] == 'sango_display_invert_rectangle'))

    # The redesigned faction page has dedicated rendering/input coverage in test_ruler_ui.py.
    baseline = ROOT / 'build/save-layout-D3/sango.elf'
    if baseline.exists():
        _, before, old_names = ruler(baseline.read_bytes(), 4, [key(0x1c)])
        check('Pre-fix D3 reproduces reading stale bytes past the padded ruler list',
              old_names[24] != 0 and any(t[0] == 'text' and b'X' in t[3] for t in before))

    # Preserve the initialized legacy data and the fixed save/global addresses.
    from elftools.elf.elffile import ELFFile
    import io
    data = ELFFile(io.BytesIO(IMAGE)).get_section_by_name('.sango_data').data()
    check('Original initialized/save data stays byte-identical', hashlib.sha256(data).hexdigest() ==
          '970e2121b60aa27d340563a249d63df2c67ce7a006ee8cb4c6cddd0cf0f3301f')
    report = {'passed': len(cases), 'failed': 0,
              'bda_sha256': hashlib.sha256((ROOT / 'build/三国霸业.bda').read_bytes()).hexdigest(),
              'scope': 'Compiled MIPS paint scopes and complete popup/roster controllers; '
                       'the redesigned faction page has separate ruler-ui validation. '
                       'SDK surfaces and input queues modeled; native font/presentation checked separately. '
                       'No physical latency claim.', 'cases': cases}
    (ROOT / 'build/menu-input-validation.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps({k: v for k, v in report.items() if k != 'cases'}))


if __name__ == '__main__':
    main()

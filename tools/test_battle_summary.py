"""Verify the compiled battle summary snapshot without private firmware."""
from __future__ import annotations
import hashlib
import json
import struct
from pathlib import Path
from test_control_flow import Machine, ROOT, STATE, BUFFER
from audit_resource_usage import record, text_items

CONTEXT = 0x81300100
PACKAGE = 0x81000000


def setup():
    m = Machine((ROOT / 'build/sango.elf').read_bytes())
    m.write(PACKAGE, (ROOT / 'build/sango.lib').read_bytes())
    m.word(STATE['g_resource_package_address'], PACKAGE)
    m.word(STATE['g_game_context'], CONTEXT)
    m.word(STATE['g_scratch_buffer_address'], BUFFER)
    m.write(BUFFER, bytes([0xa5]) * 256)
    text, bitmaps = [], []
    m.intercept('sango_display_put_gray_pixel', 4, lambda args: 0)
    m.intercept('sango_render_clear_rectangle', 5, lambda args: 0)
    m.intercept('sango_display_select_font', 2, lambda args: 0)
    m.intercept('sango_text_draw_native', 4,
                lambda args: text.append((args[0], args[1], m.text(args[2]), args[3])))
    m.intercept('sango_bitmap_draw_frame', 7, lambda args: bitmaps.append(args))
    return m, text, bitmaps


def main():
    manifest = json.loads((ROOT / 'assets/library/manifest.json').read_text(encoding='utf-8'))
    cities = text_items(record(manifest, 58))
    labels = text_items(record(manifest, 64))
    m, text, bitmaps = setup()
    m.call('sango_battle_status_draw')
    assert not [row for row in bitmaps if row[1] >= 284] and not [entry for entry in text if entry[1] >= 284]
    count = 1
    for scenario in range(1, 5):
        for ruler, year, month, city_count, people_count, city in (
                (0, 190, 1, 3, 9, 4), (199, 65535, 12, 38, 200, 0)):
            m, text, bitmaps = setup()
            for name, value in [('g_player_character', ruler), ('g_scenario_id_view2', scenario),
                                ('g_current_month', month)]:
                m.write(STATE[name], bytes([value]))
            m.write(STATE['g_current_year'], struct.pack('<H', year))
            m.call('sango_battle_summary_remember', city_count, people_count, city)
            # Battle redraws retain the last strategic summary, even if live
            # values change. Neither old state nor shared text scratch is changed.
            m.write(STATE['g_current_year'], b'\x01\x00')
            m.write(STATE['g_current_month'], b'\x02')
            m.write(STATE['g_player_character'], bytes([(ruler + 1) % 200]))
            m.write(STATE['g_scenario_id_view2'], bytes([5 - scenario]))
            state = m.read(0x81c2b0d0, 0x9a1)
            m.call('sango_battle_status_draw')
            bitmaps = [row for row in bitmaps if row[1] >= 284]
            expected = [(94, 289, str(city_count).encode(), CONTEXT),
                        (94, 303, str(people_count).encode(), CONTEXT),
                        (123, 289, (str(year) + labels[62]).encode('gbk'), CONTEXT),
                        (123, 303, (str(month) + labels[63]).encode('gbk'), CONTEXT)]
            if city:
                expected.append((180, 296, cities[city - 1].encode('gbk'), CONTEXT))
            assert [entry for entry in text if entry[1] >= 284] == expected, text
            assert [row[:5] for row in bitmaps] == [
                [31, 290, 24, 24, ruler], [79, 290, 7, 9, 1], [79, 305, 7, 9, 0]], bitmaps
            for row in bitmaps:
                assert row[6] == CONTEXT
            # Header of the first frame must come from the snapshotted scenario.
            offset = struct.unpack_from('<I', (ROOT / 'build/sango.lib').read_bytes(),
                                        (scenario + 46) * 4)[0]
            assert bitmaps[0][5] == PACKAGE + offset + 12
            assert m.read(0x81c2b0d0, 0x9a1) == state
            assert m.read(BUFFER, 256) == bytes([0xa5]) * 256
            count += 1
    report = {'passed': count, 'failed': 0, 'bda_sha256': hashlib.sha256(
        (ROOT / 'build/三国霸业.bda').read_bytes()).hexdigest(),
        'summary_rectangle': [0, 284, 240, 36],
        'scope': 'Compiled MIPS caches last strategic ruler/scenario/counts/date/city; validates '
                 'portrait resource/frame, two native text rows, empty city, redraw stability and '
                 'unchanged legacy state/shared scratch. SDK text/bitmap boundaries modeled; '
                 'native appearance checked separately.'}
    (ROOT / 'build/battle-summary-validation.json').write_text(
        json.dumps(report, indent=2) + '\n', encoding='utf-8', newline='\n')
    print(json.dumps(report))


if __name__ == '__main__':
    main()

"""Check the 15-column/14-row display viewport against all seven real maps.

Runs compiled MIPS copy/scroll/painters. SDK drawing boundaries are recorded;
movement/AI windows remain 15x15 and are not resized by these display checks.
"""
from __future__ import annotations
import hashlib
import json
import struct
from test_control_flow import Machine, ROOT, STATE, BUFFER

PACKAGE = 0x81000000
CONTEXT = 0x81300100
COLS, ROWS, TILE = 15, 14, 16


def machine(resource):
    m = Machine((ROOT / 'build/sango.elf').read_bytes())
    m.write(PACKAGE, (ROOT / 'build/sango.lib').read_bytes())
    m.word(STATE['g_resource_package_address'], PACKAGE)
    m.word(STATE['g_viewport_tiles_address'], BUFFER)
    m.word(STATE['g_game_context'], CONTEXT)
    m.write(STATE['g_battle_map_resource'], struct.pack('<H', resource))
    m.write(STATE['g_battle_tileset_resource'], struct.pack('<H', 4))
    address = m.call('sango_resource_item', resource, 1, PACKAGE)
    width, height = struct.unpack('<HH', m.read(address, 4))
    m.write(STATE['g_battle_map_width'], bytes([width]))
    m.write(STATE['g_battle_map_height'], bytes([height]))
    calls = []
    m.intercept('sango_raster_draw_opaque', 6, lambda args: calls.append(args))
    m.intercept('sango_battle_status_draw', 0, lambda args: 0)
    m.intercept('sango_battle_draw_cursor_description', 0, lambda args: 0)
    return m, address, width, height, calls


def main():
    count = 0
    for resource in range(110, 117):
        m, address, width, height, draws = machine(resource)
        for requested_x, requested_y in ((0, 0), (width-COLS, height-ROWS),
                                         (width-1, height-1), (65535, 65535)):
            m.write(BUFFER, bytes([0xa5]) * 225)
            m.call('sango_battle_copy_viewport_tiles', requested_x, requested_y)
            left, top = min(requested_x, width-COLS), min(requested_y, height-ROWS)
            expected = b''.join(m.read(address+16+(top+row)*width+left, COLS)
                                for row in range(ROWS))
            assert m.read(STATE['g_battle_viewport_x'], 1) == bytes([left])
            assert m.read(STATE['g_battle_viewport_y'], 1) == bytes([top])
            assert m.read(BUFFER, COLS*ROWS) == expected
            assert m.read(BUFFER+COLS*ROWS, 15) == bytes([0xa5])*15
            count += 1
        for left, top in ((0, 0), (width-COLS, height-ROWS)):
            draws.clear()
            m.call('sango_battle_draw_terrain', left, top)
            assert len(draws) == COLS*ROWS
            for index, args in enumerate(draws):
                assert args[:4] == [(index % COLS)*TILE, (index//COLS)*TILE, TILE, TILE]
                assert args[5] == CONTEXT and args[1]+args[3] <= 224
            count += 1
        # Traverse every row down and back up: the last map row stays reachable.
        m.write(STATE['g_battle_viewport_x'], b'\0')
        m.write(STATE['g_battle_viewport_y'], b'\0')
        m.write(STATE['g_battle_cursor_x'], b'\0')
        top = 0
        for row in [*range(height), *range(height-1, -1, -1)]:
            m.write(STATE['g_battle_cursor_y'], bytes([row]))
            m.call('sango_battle_scroll_viewport', 0)
            if row < top:
                top -= 1
            elif row >= top+ROWS:
                top += 1
            actual = m.read(STATE['g_battle_viewport_y'], 1)[0]
            assert actual == top and actual <= row < actual+ROWS
            assert 0 <= actual <= height-ROWS
            count += 1
        assert top == 0
    # Movement overlays still iterate the original 225-cell rule window;
    # only the visible 210 cells may paint into the map area.
    m, _, _, _, _ = machine(110)
    marks = []
    m.word(STATE['g_move_costs_address'], BUFFER+512)
    m.write(BUFFER+512, bytes([1])*225)
    m.intercept('sango_raster_draw_masked', 6, lambda args: marks.append(args))
    m.call('sango_battle_draw_move_range')
    assert len(marks) == 210 and all(row[1]+row[3] <= 224 for row in marks)
    assert m.read(BUFFER+512, 225) == bytes([1])*225
    count += 1
    # Blinking/restoring an offscreen tile must not read stale cache rows or
    # paint the status row, for either screen or back-buffer targets.
    m, _, _, _, tiles = machine(110)
    m.call('sango_battle_copy_viewport_tiles', 0, 0)
    m.intercept('sango_raster_draw_screen', 5, lambda args: tiles.append(args))
    for target in (0, 1):
        for column, row, visible in ((0, 13, True), (14, 13, True),
                                      (0, 14, False), (15, 0, False)):
            tiles.clear()
            m.call('sango_battle_draw_tile', column, row, target)
            assert bool(tiles) == visible, (column, row, target, tiles)
            count += 1
    # Map sprites/effects cannot paint over the footer's first row.
    m, _, _, _, _ = machine(110)
    sprites, effects = [], []
    m.intercept('sango_bitmap_draw_resource', 5, lambda args: sprites.append(args))
    m.intercept('sango_animation_play_range', 6, lambda args: effects.append(args))
    for x, y, visible in ((0, 208, True), (224, 208, True), (0, 224, False),
                           (240, 0, False), (0, 65535, False)):
        sprites.clear()
        m.call('sango_battle_draw_bitmap', 7, 5, x, y)
        assert bool(sprites) == visible, (x, y, sprites)
        count += 1
    for row, visible in ((13, True), (14, False), (15, False)):
        sprites.clear()
        if row == 13:
            m.intercept('sango_battle_present', 0, lambda args: 0)
        m.write(STATE['g_battle_cursor_y'], bytes([row]))
        m.call('sango_battle_draw_cursor')
        assert bool(sprites) == visible
        effects.clear()
        m.call('sango_battle_play_unit_effect', 0, 5, 0, row)
        assert bool(effects) == visible
        count += 1
    report = {'passed': count, 'failed': 0, 'viewport_tiles': [15, 14],
              'map_rectangle': [0, 0, 240, 224], 'rules_window_unchanged': [15, 15],
              'resources_checked': list(range(110, 117)),
              'bda_sha256': hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),
              'scope': 'Compiled MIPS real-map viewport copies, edge clamps, 210-tile painting, '
                       'top-to-bottom scrolling/reachability, overlays and sprite/effect clipping; '
                       'SDK rendering boundaries modeled. Not complete battle or hardware proof.'}
    (ROOT/'build/battle-viewport-validation.json').write_text(
        json.dumps(report, indent=2)+'\n', encoding='utf-8', newline='\n')
    print(json.dumps(report))


if __name__ == '__main__':
    main()

"""Compare compiled control-flow changes with a previously built ELF.

Runs real MIPS instructions with deterministic boundaries around modal input
and rendering. Requires pyelftools and Unicorn; no firmware or original BDA.
Keep the baseline ELF from before editing and pass it with --baseline.
"""
from __future__ import annotations

import argparse
import hashlib
import io
import itertools
import json
from pathlib import Path
import struct
import random
from functools import lru_cache

from elftools.elf.elffile import ELFFile
from unicorn import Uc, UC_ARCH_MIPS, UC_MODE_MIPS32, UC_MODE_LITTLE_ENDIAN, UC_HOOK_CODE
from unicorn.mips_const import (
    UC_MIPS_REG_PC, UC_MIPS_REG_SP, UC_MIPS_REG_RA, UC_MIPS_REG_V0, UC_MIPS_REG_V1,
    UC_MIPS_REG_A0, UC_MIPS_REG_A1, UC_MIPS_REG_A2, UC_MIPS_REG_A3,
    UC_MIPS_REG_CP0_STATUS,
)
from unicorn import mips_const

ROOT = Path(__file__).resolve().parents[1]
STACK = 0x81bff000
BUFFER = 0x81500000
STOP = 0x81700000
ARGUMENTS = (UC_MIPS_REG_A0, UC_MIPS_REG_A1, UC_MIPS_REG_A2, UC_MIPS_REG_A3)
STATE = {row['alias']: row['address'] for row in
         json.loads((ROOT / 'source-map.json').read_text(encoding='utf-8'))['memory_views']}


@lru_cache(maxsize=2)
def decode_image(image):
    elf = ELFFile(io.BytesIO(image))
    symbols = {symbol.name: int(symbol['st_value'])
               for symbol in elf.get_section_by_name('.symtab').iter_symbols()}
    segments = [(int(segment['p_vaddr']), segment.data()) for segment in elf.iter_segments()
                if segment['p_type'] == 'PT_LOAD']
    return symbols, segments


class Machine:
    def __init__(self, image):
        self.u = Uc(UC_ARCH_MIPS, UC_MODE_MIPS32 | UC_MODE_LITTLE_ENDIAN)
        self.u.mem_map(0, 0x02000000)
        self.u.reg_write(UC_MIPS_REG_CP0_STATUS, 0x10000000)
        self.symbols, segments = decode_image(image)
        for address, data in segments:
            self.write(address, data)
        self.trace = []

    def read(self, address, size):
        return bytes(self.u.mem_read(address & 0x1fffffff, size))

    def write(self, address, data):
        self.u.mem_write(address & 0x1fffffff, bytes(data))

    def word(self, address, value):
        self.write(address, struct.pack('<I', value & 0xffffffff))

    def text(self, address):
        data = bytearray()
        for offset in range(256):
            byte = self.read(address + offset, 1)
            if byte == b'\0':
                return bytes(data)
            data.extend(byte)
        raise AssertionError('Unterminated modeled text')

    def arguments(self, count):
        values = [self.u.reg_read(register) & 0xffffffff for register in ARGUMENTS]
        stack = self.u.reg_read(UC_MIPS_REG_SP)
        return (values + [struct.unpack('<I', self.read(stack + 16 + 4 * index, 4))[0]
                          for index in range(max(0, count - 4))])[:count]

    def intercept(self, name, count, callback):
        address = self.symbols[name]

        def hook(uc, pc, size, user):
            value = callback(self.arguments(count))
            uc.reg_write(UC_MIPS_REG_V0, (value or 0) & 0xffffffff)
            uc.reg_write(UC_MIPS_REG_PC, uc.reg_read(UC_MIPS_REG_RA))

        self.u.hook_add(UC_HOOK_CODE, hook, begin=address, end=address)

    def record(self, name, count):
        self.intercept(name, count, lambda args: self.trace.append([name, args]))

    def call(self, name, *values, instruction_limit=2000000):
        for index, register in enumerate(ARGUMENTS):
            self.u.reg_write(register, values[index] if index < len(values) else 0)
        for index, value in enumerate(values[4:]):
            self.word(STACK + 16 + 4 * index, value)
        self.u.reg_write(UC_MIPS_REG_SP, STACK)
        self.u.reg_write(UC_MIPS_REG_RA, STOP)
        self.u.emu_start(self.symbols[name], STOP, count=instruction_limit)
        if self.u.reg_read(UC_MIPS_REG_PC) != STOP:
            raise AssertionError('Input loop did not terminate: ' + name)
        return self.u.reg_read(UC_MIPS_REG_V0)


def run_city_selection(image, state, events, selected_city):
    machine = Machine(image)
    machine.write(BUFFER, bytes(state))
    pending = list(events)

    def input_event(args):
        if not pending:
            raise AssertionError('Input sequence exhausted without returning')
        event = pending.pop(0)
        machine.trace.append(['input', list(event)])
        machine.write(args[0], struct.pack('<IIHH', *event))

    def draw_map(args):
        machine.trace.append(['draw_map', list(machine.read(args[0], 4)), args[1]])
        return selected_city

    # The route bitmap is still read by the actual resource decoder.
    library = (ROOT / 'build/sango.lib').read_bytes()
    machine.write(0x81000000, library)
    machine.word(0x81c2b154, 0x81000000)
    machine.intercept('sango_input_next_event', 1, input_event)
    machine.intercept('sango_strategy_draw_map', 2, draw_map)
    machine.intercept('bbk_memcpy', 3,
                      lambda args: machine.write(args[0], machine.read(args[1], args[2])))
    machine.record('sango_render_clear_rectangle', 5)
    machine.record('sango_display_fill_rectangle', 6)
    machine.record('sango_ui_show_message', 2)
    machine.record('sango_render_present', 1)
    machine.record('sango_bitmap_draw_frame_screen', 6)
    result = machine.call('sango_strategy_select_city', BUFFER)
    return result, machine.read(BUFFER, 4), machine.trace, len(pending)


def city_cases():
    key = lambda value: (5, value, 0, 0)
    cancel = key(1)
    # Every valid viewport/cursor combination, at each directional boundary.
    for viewport_x, viewport_y in itertools.product(range(6), range(3)):
        for cursor_x in range(viewport_x, min(viewport_x + 7, 12)):
            for cursor_y in range(viewport_y, min(viewport_y + 7, 9)):
                state = (viewport_x, viewport_y, cursor_x, cursor_y)
                for direction in (0x67, 0x69, 0x6a, 0x6c):
                    yield state, [key(direction), cancel], 0
    for city in (0, 1, 38, 255):
        for dismiss in (key(1), key(0x1c), (11, 0, 85, 250)):
            for trigger in (key(0x1f), (11, 0, 155, 260)):
                yield (0, 0, 0, 0), [trigger, (6, 0, 0, 0), dismiss, key(0x1c), cancel], city
        yield (0, 0, 0, 0), [key(0x1c), cancel], city
    for event in ((5, 0x23, 0, 0), (5, 0x68, 0, 0), (5, 0xffffffff, 0, 0),
                  (11, 0, 85, 260), (11, 0, 155, 300), (11, 0, 65535, 65535),
                  (4, 1, 0, 0), (6, 0, 0, 0)):
        yield (2, 1, 6, 4), [event, cancel], 1
    yield (0, 0, 0, 0), [key(0x6a)] * 15 + [key(0x6c)] * 12 + [
        key(0x69)] * 15 + [key(0x67)] * 12 + [cancel], 1


def run_number_selection(image, initial, maximum, events):
    machine = Machine(image)
    pending = list(events)

    def input_event(args):
        if not pending:
            raise AssertionError('Number input consumed all events')
        event = pending.pop(0)
        machine.trace.append(['input', list(event)])
        machine.write(args[0], struct.pack('<IIHH', *event))

    def read_text(args):
        machine.write(args[2], b'MAX=' if args[1] == 0x2d else b'VALUE\0')

    def format_integer(args):
        machine.write(args[1], str(args[0]).encode('ascii') + b'\0')
        return args[1]

    def draw_text(args):
        machine.trace.append(['text', args[:2], machine.text(args[2]).hex()])

    machine.intercept('sango_input_next_event', 1, input_event)
    machine.intercept('sango_resource_read_text', 3, read_text)
    machine.intercept('sango_format_integer', 3, format_integer)
    machine.intercept('bbk_strlen', 1, lambda args: len(machine.text(args[0])))
    machine.intercept('sango_text_draw_legacy', 3, draw_text)
    machine.record('sango_display_invert_rectangle', 5)
    result = machine.call('sango_ui_select_number', initial, maximum)
    return result, machine.trace, len(pending)


def number_cases():
    key = lambda code: (5, code, 0, 0)
    sequences = [[], [0x67], [0x6c], [0x69, 0x67], [0x6a, 0x67],
                 [0x69] * 5 + [0x67] * 3 + [0x6a] * 5 + [0x6c] * 3,
                 [0x67, 0x67, 0x69, 0x67, 0x6c, 0x6a, 0x6c, 0x68]]
    for maximum in (0, 1, 9, 10, 99, 100, 999, 1000, 9999, 10000, 65535, 0xffffffff):
        for initial in sorted({0, 1, max(0, maximum - 1), maximum, (maximum + 1) & 0xffffffff, 65535}):
            for sequence in sequences:
                yield initial, maximum, [(6, 0, 0, 0), *map(key, sequence), key(0x1c)]
            yield initial, maximum, [key(1)]


def run_animation(image, animation, first, last, flags, key_after, wait_after):
    machine = Machine(image)
    machine.write(BUFFER, animation)
    machine.word(0x81c2b0f0, 0x81200000)  # scratch buffer, fixed old-state layout
    machine.word(0x81c2b128, 0x81300000)
    ticks = {'peek': 0, 'wait': 0}

    def input_boundary(kind, after, result):
        def callback(args):
            ticks[kind] += 1
            machine.trace.append([kind, args])
            return result if after is not None and ticks[kind] >= after else (255 if kind == 'peek' else 0)
        return callback

    machine.intercept('sango_resource_item', 3, lambda args: BUFFER)
    machine.intercept('sango_input_peek_key', 0, input_boundary('peek', key_after, 28))
    machine.intercept('sango_input_wait', 2, input_boundary('wait', wait_after, 1))
    for name, count in [('sango_render_clear_rectangle', 5), ('sango_render_present', 1),
                        ('sango_raster_draw_opaque', 6), ('sango_raster_draw_masked', 6)]:
        machine.record(name, count)
    result = machine.call('sango_animation_play_range', 19, first, last, flags, 7, 13)
    # Sprite pointers and remaining counters are observable working data too.
    return result, machine.trace, machine.read(0x81200000, 600)


def animation_cases():
    for delays in itertools.product((0, 1, 2, 3), repeat=3):
        for lifetime in (0, 1, 2, 5):
            commands = b''.join(bytes((index, index + 1, lifetime, delay, 0))
                                for index, delay in enumerate(delays))
            for masked in (False, True):
                bitmap = struct.pack('<HHBB', 4, 1, 1, int(masked)) + bytes(1 + masked)
                animation = bytes((0, 0, 3, 1, 0, 0)) + commands + bitmap
                yield animation, 0, 2, 0, None, None
    commands = bytes((1, 1, 5, 3, 0, 2, 2, 5, 2, 0, 3, 3, 2, 1, 0))
    animation = bytes((0, 0, 3, 1, 0, 0)) + commands + struct.pack('<HHBB', 4, 1, 1, 0) + b'\0'
    for first, last, flags in itertools.product((0, 1, 2), (0, 1, 2), (0, 1, 2, 3)):
        if first <= last:
            for key_after, wait_after in ((None, None), (1, None), (2, None), (None, 1)):
                yield animation, first, last, flags, key_after, wait_after


def run_list_selection(image, kind, count, bounds, events, column_stride):
    machine = Machine(image)
    machine.write(BUFFER, bytes(range(200)) + b'\xfd' * 256)
    pending = list(events)

    def input_event(args):
        if not pending:
            raise AssertionError('List input consumed all events')
        event = pending.pop(0)
        machine.trace.append(['input', list(event)])
        machine.write(args[0], struct.pack('<IIHH', *event))

    def header(args):
        machine.trace.append(['header', args])
        return args[0] + column_stride

    machine.intercept('sango_input_next_event', 1, input_event)
    machine.intercept(f'sango_ui_draw_{kind}_header', 4, header)
    machine.record(f'sango_ui_draw_{kind}_row', 5)
    machine.record('sango_display_draw_rectangle', 7)
    machine.record('sango_display_fill_rectangle', 6)
    machine.record('sango_display_invert_rectangle', 5)
    result = machine.call(f'sango_ui_select_{kind}', BUFFER, count, *bounds)
    return result, machine.trace, len(pending)


def list_cases():
    key = lambda code: (5, code, 0, 0)
    sequences = list(itertools.product((0x67, 0x6c, 0x69, 0x6a, 0x68, 0x6d), repeat=3))
    sequences += [(0x6c,) * 25 + (0x67,) * 25, (0x6a,) * 10 + (0x69,) * 10]
    for kind in ('item', 'character'):
        for count in (0, 1, 2, 3, 4, 8, 19, 200):
            for bounds in ((4, 2, 235, 61), (4, 20, 235, 180), (12, 130, 210, 230)):
                for sequence in sequences:
                    yield kind, count, bounds, [(6, 0, 0, 0), *map(key, sequence), key(0x1c)], 2
                yield kind, count, bounds, [key(1)], 4


def run_search(image, seed, owner, intelligence, available_count, required_discoverer):
    machine = Machine(image)
    library = bytearray((ROOT / 'build/sango.lib').read_bytes())
    for resource in (63, 67):
        offset = struct.unpack_from('<I', library, (resource - 1) * 4)[0]
        stride = struct.unpack_from('<H', library, offset + 8)[0]
        if stride:
            item_offset = offset + 12
        else:
            item_offset = offset + struct.unpack_from('<H', library, offset + 12)[0]
        for candidate in (2, 4, 5, 6, 7, 9):
            library[item_offset + candidate * 3 + 1] = required_discoverer
    machine.write(0x81000000, library)
    machine.word(STATE['g_resource_package_address'], 0x81000000)
    machine.word(STATE['g_character_table_address'], 0x81100000)
    machine.word(STATE['g_scratch_buffer_address'], 0x81200000)
    machine.word(STATE['g_random_seed'], seed)
    machine.write(STATE['g_scenario_id'], b'\x01')
    machine.write(STATE['g_player_character'], b'\0')
    machine.write(BUFFER, bytes((3, 3, 7, 0)) + bytes(8))
    for character in range(200):
        machine.write(0x81100000 + character * 16, bytes((0, 0, 1, 50, intelligence, 50)) + bytes(10))
    machine.write(0x81100000 + 3 * 16 + 1, bytes((owner,)))
    machine.write(0x81c2b9a4, bytes((0, 8)))
    machine.write(STATE['g_city_item_roster'], bytes(range(8)))

    def available(args):
        candidates = bytes((5, 7, 9)[:available_count])
        machine.write(args[1], candidates)
        machine.trace.append(['characters', args[0], list(candidates)])
        return available_count

    def items(args):
        candidates = bytes((2, 4, 6)[:available_count])
        machine.write(args[1], candidates)
        machine.trace.append(['items', args[0], list(candidates)])
        return available_count

    def message(args):
        machine.trace.append(['message', args[0], machine.text(args[1]).hex()])

    machine.intercept('sango_city_list_available_characters', 2, available)
    machine.intercept('sango_city_find_item', 2, items)
    machine.intercept('sango_ui_show_character_message', 2, message)
    machine.record('sango_render_present', 1)
    machine.record('sango_city_add_character', 2)
    result = machine.call('sango_strategy_resolve_search', BUFFER)
    return (result, machine.trace, machine.read(0x81100000, 3200),
            machine.read(0x81c2b0e4, 0x98d), machine.read(0x81200000, 600))


def search_cases():
    for seed, owner, intelligence, count, discoverer in itertools.product(
            range(64), (1, 2), (1, 70, 150), (0, 3), (0, 4, 199)):
        yield seed, owner, intelligence, count, discoverer


def run_battle_input(image, mode, cursor, events, register_seed):
    machine = Machine(image)
    if register_seed is not None:
        for index in range(1, 29):
            machine.u.reg_write(getattr(mips_const, f'UC_MIPS_REG_{index}'),
                                (register_seed + index * 0x10203) & 0xffffffff)
    machine.write(STATE['g_battle_cursor_x'], bytes((cursor[0],)))
    machine.write(STATE['g_battle_cursor_y'], bytes((cursor[1],)))
    machine.write(STATE['g_battle_map_width'], b'\x10')
    machine.write(STATE['g_battle_map_height'], b'\x10')
    pending = list(events)

    def input_event(args):
        if not pending:
            raise AssertionError('Battle input did not return')
        event = pending.pop(0)
        machine.trace.append(['input', list(event)])
        machine.write(args[0], struct.pack('<IIHH', *event))

    machine.intercept('sango_input_next_event', 1, input_event)
    for name, count in [('sango_battle_draw_tile', 3), ('sango_battle_show_overview', 0),
                        ('sango_battle_draw_hud', 0), ('sango_battle_show_cursor_info', 0),
                        ('sango_battle_draw_units', 1), ('sango_battle_draw_target_markers', 0),
                        ('sango_battle_draw_move_range', 0), ('sango_battle_scroll_viewport', 1),
                        ('sango_battle_draw_cursor', 0)]:
        if name == 'sango_battle_draw_hud' and name not in machine.symbols:
            # The layout wrapper is inlined; compare its shared HUD boundary.
            machine.intercept('sango_battle_status_draw', 0,
                lambda args: machine.trace.append(['sango_battle_draw_hud', []]))
        else:
            machine.record(name, count)
    # GCC outlines the hint==0 branch when the small preview wrappers are
    # reused. It has no argument; compare it with the same scroll boundary.
    if 'sango_battle_scroll_viewport.part.0' in machine.symbols:
        machine.intercept('sango_battle_scroll_viewport.part.0', 0,
            lambda args: machine.trace.append(['sango_battle_scroll_viewport', [0]]))
    unused_arguments = () if register_seed is None else tuple(
        (register_seed + register * 0x10203) & 0xffffffff for register in (5, 6, 7))
    result = machine.call('sango_battle_poll_map_action', mode, *unused_arguments)
    return result, machine.trace, machine.read(0x81c2b0e4, 0x98d), len(pending)


def battle_input_cases():
    key = lambda code: (5, code, 0, 0)
    for mode, cursor, seed in itertools.product((0, 1, 2, 3, 255),
            ((0, 0), (7, 7), (15, 15)), (None, 0, 0x11223344, 0xffffffff)):
        for count in (0, 1, 9, 10, 11, 19, 20, 21, 255, 256):
            yield mode, cursor, [(6, 0, 0, 0)] * count + [key(1)], seed
        for code in (0x67, 0x69, 0x6a, 0x6c, 0x1f, 0x23, 0x68):
            yield mode, cursor, [key(code), (6, 0, 0, 0), key(0x1c)], seed
        for x, y in ((85, 277), (155, 277), (85, 300), (65535, 65535)):
            yield mode, cursor, [(11, 0, x, y), key(1)], seed


def run_skill(image, skill, animations, profile, status, actor, random_roll):
    machine = Machine(image)
    machine.write(0x81000000, (ROOT / 'build/sango.lib').read_bytes())
    machine.word(STATE['g_resource_package_address'], 0x81000000)
    machine.word(STATE['g_character_table_address'], 0x81100000)
    machine.word(STATE['g_scratch_buffer_address'], 0x81200000)
    machine.word(STATE['g_defender_troops_address'], 0x81300000)
    machine.write(STATE['g_scenario_id'], b'\x01')
    machine.write(STATE['g_battle_roster_first'], bytes(range(1, 21)))
    machine.write(STATE['g_attacker_initiative'], b'\x02')
    machine.write(STATE['g_defender_initiative'], b'\x14')
    machine.write(STATE['g_battle_show_animations'], bytes((animations,)))
    machine.write(STATE['g_first_unit_energy'] + actor * 7, b'\x02')
    for name in ('g_battle_attacker_food', 'g_battle_defender_food'):
        machine.write(STATE[name], struct.pack('<H', 123))
    machine.write(0x81300000, struct.pack('<H', 123))
    # Use the actual library decoder, then vary only the documented fields.
    parameters = machine.call('sango_battle_skill_parameters', skill)
    machine.write(parameters, bytes((profile == 3, status)))
    machine.write(parameters + 6, b'\x05')
    machine.write(BUFFER, bytes((1, skill, actor, 19 - actor)))

    def compute_effect(args):
        machine.trace.append(['compute_effect', machine.read(args[0], 34).hex()])
        machine.write(args[1], struct.pack('<H', (0, 0, 600, 600)[profile]))
        machine.write(args[2], struct.pack('<3H', (0, 600, 0, 0)[profile], 0, 0))

    def short_message(args):
        machine.trace.append(['short_message', machine.text(args[0]).hex(), *args[1:]])

    def message(args):
        machine.trace.append(['message', machine.text(args[0]).hex(), args[1]])

    def character_message(args):
        machine.trace.append(['character_message', args[0], machine.text(args[1]).hex()])

    machine.intercept('crt_rand', 0,
                      lambda args: machine.trace.append(['rand', random_roll]) or random_roll)
    machine.intercept('sango_battle_compute_skill_effect', 3, compute_effect)
    machine.intercept('sango_battle_show_short_message', 3, short_message)
    machine.intercept('sango_ui_show_message', 2, message)
    machine.intercept('sango_ui_show_character_message', 2, character_message)
    machine.intercept('sango_text_draw_legacy', 3,
        lambda args: machine.trace.append(['text', *args[:2], machine.text(args[2]).hex()]))
    machine.intercept('sango_character_troop_capacity', 1, lambda args: 500)
    machine.intercept('sango_battle_damage_feedback', 1,
        lambda args: machine.trace.append(['feedback', *args]) or 7)
    machine.intercept('sango_battle_execute_surround_attack', 1,
        lambda args: machine.trace.append(['surround', *args]) or 9)
    for name, count in [('sango_battle_change_weather', 0),
                        ('sango_battle_prepare_combatant', 2), ('sango_render_present', 1),
                        ('sango_bitmap_draw_resource', 5), ('sango_animation_play_range', 6),
                        ('sango_battle_draw_unit_damage', 3), ('sango_battle_draw_damage_digits', 3),
                        ('sango_input_wait', 2)]:
        machine.record(name, count)
    result = machine.call('sango_battle_execute_skill', BUFFER)
    return (result, machine.trace, machine.read(0x81c2b0e4, 0x98d),
            machine.read(0x81300000, 2), machine.read(0x81200000, 128))


def skill_cases():
    yield from itertools.product(range(1, 31), (0, 1), range(4), (0, 3, 4), (0, 19), (0, 39))


def run_attack(image, attacker, defender, count, troop_profile, selection_count):
    machine = Machine(image)
    machine.write(0x81000000, (ROOT / 'build/sango.lib').read_bytes())
    for name, address in [('g_resource_package_address', 0x81000000),
                          ('g_character_table_address', 0x81100000),
                          ('g_scratch_buffer_address', 0x81200000),
                          ('g_army_rosters_address', 0x81300000),
                          ('g_army_slot_used_address', 0x81301000)]:
        machine.word(STATE[name], address)
    machine.write(STATE['g_player_character'], b'\0')
    machine.write(STATE['g_first_city_owner'] + 3 * 36, bytes((defender,)))
    machine.write(STATE['g_first_city_food'] + 3 * 36, struct.pack('<H', 456))
    machine.write(0x81300000, bytes((5, 6, 0, 8, 0, 10, 0, 0, 0, 0)))
    machine.write(0x81100000 + 4 * 16 + 1, bytes((attacker,)))
    for index in range(40):
        troops = ((index * 173) % 1000, 0, 1000 - index * 7)[troop_profile]
        machine.write(0x81100000 + index * 16 + 10, struct.pack('<H', troops))
    machine.write(BUFFER, bytes((8, 0, 1, 3, 0, 0)) + struct.pack('<H', 789) + bytes(4))
    selected = []

    def idle(args):
        roster = list(range(20, 20 + count))
        roster = [value for value in roster if value not in selected]
        machine.write(args[1], bytes(roster))
        machine.trace.append(['idle', args[0], roster])
        return len(roster)

    def choose(args):
        roster = list(machine.read(args[0], args[1]))
        choice = 0 if roster and len(selected) < selection_count else 255
        machine.trace.append(['choose', roster, choice, *args[2:]])
        return choice

    def remove(args):
        selected.append(args[1])
        machine.trace.append(['remove', *args])

    def battle(args):
        machine.trace.append(['battle'])
        machine.write(STATE['g_battle_result'], b'\x02')

    machine.intercept('sango_city_list_idle_characters', 2, idle)
    machine.intercept('sango_ui_select_character', 6, choose)
    machine.intercept('sango_city_remove_character', 2, remove)
    machine.intercept('sango_city_neighbor_direction', 2, lambda args: 2)
    machine.intercept('sango_battle_run', 0, battle)
    machine.intercept('bbk_memcpy', 3,
                      lambda args: machine.write(args[0], machine.read(args[1], args[2])))
    for name, arity in [('sango_city_add_character', 2), ('sango_render_present', 1),
                        ('sango_strategy_show_army_attack', 2), ('sango_strategy_finish_battle', 2),
                        ('sango_strategy_show_battle_victory', 1), ('sango_strategy_show_armies_engage', 2)]:
        machine.record(name, arity)
    result = machine.call('sango_strategy_resolve_attack', BUFFER)
    return (result, machine.trace, machine.read(0x81c2b0e4, 0x98d),
            machine.read(0x81200000, 600), machine.read(0x81301000, 10))


def attack_cases():
    yield from itertools.product((1, 2, 3), (0, 1, 2, 3), (0, 1, 2, 5, 12), range(3), (0, 2, 10))


def run_float(image, case):
    machine = Machine(image)
    kind, function, *values = case
    if kind == 'pack':
        classification, sign, exponent, significand = values
        machine.write(BUFFER, struct.pack('<6I', classification, sign, exponent & 0xffffffff,
                                         0, significand & 0xffffffff, significand >> 32))
        result = machine.call(function, BUFFER)
    elif kind == 'f32':
        result = machine.call(function, *values)
    else:
        left, right = values
        result = machine.call(function, left & 0xffffffff, left >> 32,
                              right & 0xffffffff, right >> 32)
    return result, machine.u.reg_read(UC_MIPS_REG_V1) if kind != 'f32' else 0


def float_cases():
    edge32 = (0, 0x80000000, 1, 0x7fffff, 0x800000, 0x3f000000, 0x3f7fffff,
              0x3f800000, 0x3f800001, 0x40000000, 0x7f7fffff, 0x7f800000,
              0xff800000, 0x7f800001, 0x7fc00000)
    edge64 = (0, 0x8000000000000000, 1, 0xfffffffffffff, 0x10000000000000,
              0x3fefffffffffffff, 0x3ff0000000000000, 0x3ff0000000000001,
              0x7fefffffffffffff, 0x7ff0000000000000, 0xfff0000000000000,
              0x7ff0000000000001, 0x7ff8000000000000)
    generator = random.Random(0x5a71)
    for function in ('soft_float_add', 'soft_float_mul', 'soft_float_div'):
        for left, right in itertools.product(edge32, repeat=2):
            yield ('f32', function, left, right),
        for _ in range(512):
            yield ('f32', function, generator.getrandbits(32), generator.getrandbits(32)),
    for function in ('sango_soft_sub_f64', 'sango_soft_mul_f64', 'sango_soft_div_f64'):
        for left, right in itertools.product(edge64, repeat=2):
            yield ('f64', function, left, right),
        for _ in range(512):
            yield ('f64', function, generator.getrandbits(64), generator.getrandbits(64)),
    for classification, sign, exponent, significand in itertools.product(
            (0, 1, 2, 3, 4), (0, 1), (-1075, -1074, -1023, -1022, -1, 0, 1023, 1024),
            (0, 1, 0x7f, 0x80, 0xff, 0x100, 0x180, 1 << 60, (1 << 61) - 1)):
        yield ('pack', 'sango_soft_pack_f64', classification, sign, exponent, significand),


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--baseline', required=True, type=Path)
    parser.add_argument('--candidate', type=Path, default=ROOT / 'build/sango.elf')
    parser.add_argument('--report', type=Path, default=ROOT / 'build/control-flow-validation.json')
    parser.add_argument('--only', choices=('city', 'number', 'animation', 'lists', 'search', 'battle', 'skill', 'attack', 'float'))
    args = parser.parse_args()
    before = args.baseline.read_bytes()
    after = args.candidate.read_bytes()
    counts = {}
    groups = [('city', city_cases, run_city_selection), ('number', number_cases, run_number_selection),
              ('animation', animation_cases, run_animation), ('lists', list_cases, run_list_selection),
              ('search', search_cases, run_search), ('battle', battle_input_cases, run_battle_input),
              ('skill', skill_cases, run_skill), ('attack', attack_cases, run_attack),
              ('float', float_cases, run_float)]
    for name, cases, run in groups:
        if args.only and args.only != name:
            continue
        count = 0
        for case in cases():
            left, right = run(before, *case), run(after, *case)
            if left != right:
                raise AssertionError({'group': name, 'case': repr(case),
                                      'baseline': repr(left), 'candidate': repr(right)})
            count += 1
            if count % 500 == 0:
                print(f'{name} cases: {count}, failed: 0', flush=True)
        counts[name] = count
    report = {'passed': sum(counts.values()), 'failed': 0, 'groups': counts,
              'baseline_elf_sha256': hashlib.sha256(before).hexdigest(),
              'candidate_elf_sha256': hashlib.sha256(after).hexdigest(),
              'bda_sha256': hashlib.sha256((ROOT / 'build/三国霸业.bda').read_bytes()).hexdigest(),
              'scope': 'The reported groups execute actual MIPS functions against the provided baseline ELF: '
                       'city/battle input, decimal input, pagination, animation timing, search outcomes, '
                       'skill dispatch, attack preparation and soft-float boundary/random cases. '
                       'Compares return, observable state, input consumption and rendering calls. '
                       'Rendering/modal boundaries are deterministic models; not native firmware or hardware.'}
    args.report.parent.mkdir(parents=True, exist_ok=True)
    args.report.write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(json.dumps(report), flush=True)


if __name__ == '__main__':
    main()

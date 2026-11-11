"""Verify actual MIPS sliding-leaf geometry, frame timing, skip and cleanup."""
import hashlib
import json
import struct

from test_control_flow import Machine, ROOT, STATE, BUFFER
from test_touch_input import event, install_events

IMAGE = (ROOT / 'build/sango.elf').read_bytes()
MENU, CANVAS, DOOR = 0x81600008, 0x81600004, 0x81610000


def main():
    cases = []

    def check(name, ok):
        assert ok, name
        cases.append({'name': name, 'passed': True})

    # Production compose function runs; only named SDK copy/present boundaries
    # are modeled. Every source rectangle must stay within its own leaf.
    m = Machine(IMAGE)
    copies, presents = [], []
    m.intercept('sango_intro_sdk_copy', 5, lambda a: copies.append(a))
    m.intercept('sango_render_present', 1, lambda a: presents.append(a[0]))
    for distance in (0, 1, 6, 30, 60, 114, 119, 120, 121, 1000):
        copies.clear(); presents.clear()
        m.call('sango_intro_compose', DOOR, MENU, CANVAS, distance)
        expected = [[MENU, 0, 240, CANVAS, 0]]
        if distance < 120:
            expected += [[DOOR, distance, 120-distance, CANVAS, 0],
                         [DOOR, 120, 120-distance, CANVAS, 120+distance]]
        check(f'Distance {distance} uses the proper moving halves and menu background', copies == expected)
        check(f'Distance {distance} presents one complete offscreen frame', presents == [CANVAS])

    # Raw timer1/2/audio wakeups must never turn the20-frame effect into a flash.
    for skip in ('none', 'key', 'tap', 'hold', 'drag'):
        m = Machine(IMAGE)
        m.word(STATE['g_game_context'], MENU)
        m.word(STATE['g_message_context'], CANVAS)
        snapshots, timers, freed, distances, final = [], [], [], [], []
        m.intercept('sango_color_sdk_snapshot', 1, lambda a: snapshots.append(a[0]) or DOOR)
        m.intercept('sango_color_sdk_snapshot_free', 1, lambda a: freed.append(a[0]))
        m.intercept('sango_intro_sdk_timer', 1, lambda a: timers.append(a[0]))
        m.intercept('sango_intro_compose', 4, lambda a: distances.append(a[3]))
        m.intercept('sango_render_present', 1, lambda a: final.append(a[0]))
        backgrounds = []
        m.intercept('sango_bitmap_draw_resource', 5, lambda a: backgrounds.append(a))
        clock = [0]
        m.intercept('sango_touch_sdk_ticks', 0, lambda a: clock[0])
        m.intercept('sango_touch_sdk_timer', 1, lambda a: 0)
        sample = [120, 100]
        def position(a):
            m.write(a[0], struct.pack('<H', sample[0]))
            m.write(a[1], struct.pack('<H', sample[1]))
        m.intercept('sango_touch_sdk_position', 2, position)
        queued = []
        if skip == 'key': queued = [event(0x10, key=0x1c)]
        if skip in ('tap', 'hold', 'drag'):
            queued = [event(1, 120, 100)]
            if skip == 'drag': queued.append(event(1, 140, 100)); sample[0] = 140
            queued.append(event(2, *sample))
        for _ in range(20):
            queued += [event(0x144, key=1), event(0x144, key=2), event(0), event(0x144, key=4)]
        def raw(a):
            assert queued, 'Intro did not return after20 frame events'
            packet = queued.pop(0)
            if skip == 'hold' and packet[0] == 2: clock[0] = 32
            m.write(a[0], struct.pack('<IIHH', *packet))
            return 1
        m.intercept('sango_input_poll_native_event', 1, raw)
        m.call('sango_intro_open_menu')
        wanted = [] if skip in ('key', 'tap', 'hold') else list(range(6, 121, 6))
        check(f'{skip}: only dedicated timer4 advances the intended frames', distances == wanted)
        check(f'{skip}: stop timer and free one captured gate on every exit',
              snapshots == [MENU] and timers == [1, 0] and freed == [DOOR])
        check(f'{skip}: leave a complete menu ready for normal input',
              backgrounds == [[44, 1, 0, 0, 0]] and final == [MENU])

    for missing in ('allocation', 'canvas'):
        m = Machine(IMAGE)
        m.word(STATE['g_game_context'], MENU)
        m.word(STATE['g_message_context'], 0 if missing == 'canvas' else CANVAS)
        m.intercept('sango_color_sdk_snapshot', 1, lambda a: 0)
        m.record('sango_bitmap_draw_resource', 5)
        m.record('sango_render_present', 1)
        m.intercept('sango_intro_sdk_timer', 1, lambda a: (_ for _ in ()).throw(AssertionError('Started timer without canvas')))
        m.call('sango_intro_open_menu')
        check(f'Missing {missing}: safely show the final menu without waiting',
              m.trace == [['sango_bitmap_draw_resource', [44, 1, 0, 0, 0]],
                          ['sango_render_present', [MENU]]])

    # The new effect is actually wired to startup, not just reachable in a fixture.
    for result in (255, 28, 1, 254):
        m = Machine(IMAGE)
        called = []
        for name, count, answer in [('graphics_init_stub', 0, 1),
                                    ('sango_load_package_and_buffers', 0, 0),
                                    ('sango_allocate_session_state', 0, 0),
                                    ('sango_select_session', 0, 0),
                                    ('sango_release_package_and_buffers', 0, 0),
                                    ('sango_music_shutdown', 0, 0)]:
            if name in m.symbols: m.intercept(name, count, lambda a, answer=answer: answer)
        m.intercept('sango_animation_play_resource', 1, lambda a: result)
        m.intercept('sango_intro_open_menu', 0, lambda a: called.append(1))
        m.call('sango_game_lifecycle')
        check(f'Startup result {result}: normal completion opens; explicit skip bypasses', called == ([1] if result == 255 else []))

    report = {'passed': len(cases), 'failed': 0,
              'bda_sha256': hashlib.sha256((ROOT/'build/三国霸业.bda').read_bytes()).hexdigest(),
              'scope': 'Compiled MIPS leaf composition, timer isolation, real touch recognizer, '
                       'skip/drag/failure/cleanup and actual startup wiring. SDK copies/input modeled; '
                       'native moving-frame screenshots checked separately.', 'cases': cases}
    (ROOT/'build/intro-validation.json').write_text(json.dumps(report, indent=2)+'\n')
    print(json.dumps({k:v for k,v in report.items() if k != 'cases'}))


if __name__ == '__main__':
    main()

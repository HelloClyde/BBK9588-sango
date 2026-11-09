#include "sango_internal.h"

/* Gesture state belongs to input/UI only; none of it is part of a saved game.
 * Window messages own the contact lifetime. The SDK position getter is sampled
 * only while that contact is down; the global raw-input queue is never consumed. */
static struct
{
    int down, moved, cancelled, ignore_until_release;
    int origin_x, origin_y, previous_x, previous_y;
    int last_tap_x, last_tap_y;
    uint32_t started_tick, sequence;
} contact;

static int magnitude(int value)
{
    return value < 0 ? -value : value;
}

static int clamp(int value, int minimum, int maximum)
{
    return value < minimum ? minimum : value > maximum ? maximum : value;
}

/* Keep the SDK boundary separate from the deterministic gesture recognizer. */
__attribute__((noinline)) void sango_touch_sdk_position(uint16_t *x, uint16_t *y)
{
    bda_gui_touch_position(x, y);
}

__attribute__((noinline)) uint32_t sango_touch_sdk_ticks(void)
{
    return (uint32_t)bda_gui_tick_count_25ms();
}

__attribute__((noinline)) void sango_touch_sdk_timer(int active)
{
    /* Independent of the game's 500 ms blink timer and animation timer resets. */
    if (active)
        bda_gui_window_timer_start((bda_handle_t)g_app_frame, SANGO_TOUCH_TIMER_ID, 20);
    else
        bda_gui_window_timer_stop((bda_handle_t)g_app_frame, SANGO_TOUCH_TIMER_ID);
}

int sango_touch_x(const int *event)
{
    return (int16_t)((uint32_t)event[2] & 0xffffu);
}

int sango_touch_y(const int *event)
{
    return (int16_t)((uint32_t)event[2] >> 16);
}

void sango_touch_cancel(void)
{
    if (contact.down)
    {
        sango_touch_sdk_timer(0);
        contact.ignore_until_release = 1;
    }
    contact.down = 0;
    contact.moved = 0;
    contact.cancelled = 0;
}

int sango_touch_process(int *event)
{
    int message = event[0], x, y, dx, dy;
    if (message == 0x144)
    {
        uint16_t sample_x, sample_y;
        if (!contact.down)
            return 0;
        sango_touch_sdk_position(&sample_x, &sample_y);
        event[2] = (int)((uint32_t)sample_x | (uint32_t)sample_y << 16);
    }
    else if (message != BDA_MSG_TOUCH_COORDINATE && message != BDA_MSG_TOUCH_RELEASE)
        return 0;

    if (contact.ignore_until_release)
    {
        if (message == BDA_MSG_TOUCH_RELEASE)
            contact.ignore_until_release = 0;
        return 0;
    }

    if (message == BDA_MSG_TOUCH_RELEASE && contact.down)
    {
        uint16_t release_x, release_y;
        /* The release message can retain the last queued coordinate. The
         * calibrated getter supplies the final point of a coalesced drag. */
        sango_touch_sdk_position(&release_x, &release_y);
        event[2] = (int)((uint32_t)release_x | (uint32_t)release_y << 16);
    }

    x = sango_touch_x(event);
    y = sango_touch_y(event);
    if (message == BDA_MSG_TOUCH_COORDINATE && !contact.down)
    {
        contact.down = 1;
        contact.moved = 0;
        contact.cancelled = 0;
        contact.started_tick = sango_touch_sdk_ticks();
        ++contact.sequence;
        contact.origin_x = contact.previous_x = x;
        contact.origin_y = contact.previous_y = y;
        sango_touch_sdk_timer(1);
    }
    if (!contact.down)
        return 0;
    if (x < 0 || x >= 240 || y < 0 || y >= 320)
        contact.cancelled = 1;
    if (contact.cancelled)
    {
        if (message == BDA_MSG_TOUCH_RELEASE)
        {
            sango_touch_cancel();
            contact.ignore_until_release = 0;
        }
        return 0;
    }
    if (magnitude(x - contact.origin_x) >= 8 || magnitude(y - contact.origin_y) >= 8)
        contact.moved = 1;
    dx = x - contact.previous_x;
    dy = y - contact.previous_y;
    if (message == BDA_MSG_TOUCH_RELEASE)
    {
        sango_touch_sdk_timer(0);
        event[0] = contact.moved ? SANGO_TOUCH_PAN_END
                   : (uint32_t)(sango_touch_sdk_ticks() - contact.started_tick) >= 32
                       ? SANGO_TOUCH_HOLD
                       : SANGO_TOUCH_TAP;
        contact.down = 0;
        if (!contact.moved)
        {
            contact.last_tap_x = x;
            contact.last_tap_y = y;
        }
    }
    else
    {
        if (!contact.moved || (dx == 0 && dy == 0))
            return 0;
        event[0] = SANGO_TOUCH_PAN;
    }
    event[1] = (int)((uint32_t)(uint16_t)dx | (uint32_t)(uint16_t)dy << 16);
    contact.previous_x = x;
    contact.previous_y = y;
    return 1;
}

int sango_touch_menu_row(unsigned int background, const int *event)
{
    static const uint16_t main_tops[4] = {49, 111, 173, 234};
    static const uint16_t scenario_tops[4] = {49, 110, 171, 232};
    int x = sango_touch_x(event), y = sango_touch_y(event), row;
    const uint16_t *tops = background == 44 ? main_tops : scenario_tops;
    int left = background == 44 ? 57 : 42, width = background == 44 ? 126 : 157;
    if (x < left || x >= left + width || (background != 44 && background != 45))
        return -1;
    for (row = 0; row < 4; ++row)
        if (y >= tops[row] && y < tops[row] + 57)
            return row;
    return -1;
}

int sango_touch_last_menu_row(unsigned int background)
{
    int event[3] = {SANGO_TOUCH_TAP, 0,
                    (int)((uint32_t)contact.last_tap_x | (uint32_t)contact.last_tap_y << 16)};
    return sango_touch_menu_row(background, event);
}

int sango_touch_choose_row(const int *event, int left, int top, int right, int row_height,
                           unsigned int visible, unsigned int first, unsigned int total)
{
    int x = sango_touch_x(event), y = sango_touch_y(event);
    unsigned int row;
    if ((event[0] != SANGO_TOUCH_TAP && event[0] != SANGO_TOUCH_HOLD) || row_height <= 0 ||
        x < left || x > right || y < top)
        return -1;
    row = (unsigned int)(y - top) / (unsigned int)row_height;
    return row < visible && first + row < total ? (int)(first + row) : -1;
}

int sango_touch_swipe_key(const int *event)
{
    int dx, dy;
    if (event[0] != SANGO_TOUCH_PAN_END)
        return 0;
    dx = sango_touch_x(event) - contact.origin_x;
    dy = sango_touch_y(event) - contact.origin_y;
    if (magnitude(dy) >= magnitude(dx))
        return dy <= -8 ? BDA_KEY_DOWN : dy >= 8 ? BDA_KEY_UP : 0;
    return dx <= -8 ? BDA_KEY_RIGHT : dx >= 8 ? BDA_KEY_LEFT : 0;
}

int sango_touch_map_point(const int *event, uint8_t *state, int columns, int rows, int screen_width,
                          int screen_height)
{
    int x = sango_touch_x(event), y = sango_touch_y(event);
    if (event[0] != SANGO_TOUCH_TAP || x < 0 || x >= screen_width || y < 0 || y >= screen_height)
        return 0;
    state[2] = state[0] + x * columns / screen_width;
    state[3] = state[1] + y * rows / screen_height;
    return 1;
}

int sango_touch_pan_map(const int *event, uint8_t *state, int world_width, int world_height,
                        int columns, int rows, int screen_width, int screen_height, int *remainder)
{
    int dx, dy, next_x, next_y, changed;
    if ((event[0] != SANGO_TOUCH_PAN && event[0] != SANGO_TOUCH_PAN_END) || contact.origin_x < 0 ||
        contact.origin_x >= screen_width || contact.origin_y < 0 ||
        contact.origin_y >= screen_height)
        return 0;
    dx = (int16_t)((uint32_t)event[1] & 0xffffu);
    dy = (int16_t)((uint32_t)event[1] >> 16);
    if ((unsigned int)remainder[2] != contact.sequence)
    {
        remainder[0] = remainder[1] = 0;
        remainder[2] = (int)contact.sequence;
    }
    remainder[0] -= dx * columns;
    remainder[1] -= dy * rows;
    next_x = clamp(state[0] + remainder[0] / screen_width, 0,
                   world_width > columns ? world_width - columns : 0);
    next_y = clamp(state[1] + remainder[1] / screen_height, 0,
                   world_height > rows ? world_height - rows : 0);
    remainder[0] %= screen_width;
    remainder[1] %= screen_height;
    if (event[0] == SANGO_TOUCH_PAN_END)
        remainder[0] = remainder[1] = 0;
    changed = next_x != state[0] || next_y != state[1];
    state[0] = (uint8_t)next_x;
    state[1] = (uint8_t)next_y;
    state[2] = (uint8_t)clamp(state[2], next_x, next_x + columns - 1);
    state[3] = (uint8_t)clamp(state[3], next_y, next_y + rows - 1);
    return changed;
}

void sango_touch_draw_number_controls(void)
{
    static const char *const labels[4] = {"\xbc\xf5\xc9\xd9", "\xd4\xf6\xbc\xd3",
                                          "\xc8\xb7\xb6\xa8", "\xb7\xb5\xbb\xd8"};
    int button;
    for (button = 0; button < 4; ++button)
    {
        int left = 40 + button * 42;
        sango_display_fill_gray_rectangle(left, 183, left + 37, 205, 0, 0);
        sango_display_draw_rectangle(left, 183, left + 37, 205, 3, 0, 0);
        sango_text_draw_native(left + 3, 188, (char *)labels[button], 0);
    }
}

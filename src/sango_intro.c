#include "sango_internal.h"

enum
{
    INTRO_TIMER = 4,
    FRAME_MS = 30,
    HALF_WIDTH = 120,
    DOOR_STEP = 6
};

/* Copy every RGB565 color, including both possible transparency keys. */
__attribute__((noinline)) void sango_intro_sdk_copy(unsigned int source, int source_x, int width,
                                                    unsigned int target, int target_x)
{
    bda_gui_context_copy((bda_handle_t)source, source_x, 0, width, 320, (bda_handle_t)target,
                         target_x, 0, 0);
    bda_gui_context_copy((bda_handle_t)source, source_x, 0, width, 320, (bda_handle_t)target,
                         target_x, 0, 0xffff);
}

/* Both leaves move offscreen; the center progressively reveals the menu.
 * Prepare on the existing message surface so no partially moved frame is shown. */
void sango_intro_compose(unsigned int door, unsigned int menu, unsigned int canvas,
                         unsigned int distance)
{
    sango_intro_sdk_copy(menu, 0, 240, canvas, 0);
    if (distance < HALF_WIDTH)
    {
        sango_intro_sdk_copy(door, distance, HALF_WIDTH - distance, canvas, 0);
        sango_intro_sdk_copy(door, HALF_WIDTH, HALF_WIDTH - distance, canvas,
                             HALF_WIDTH + distance);
    }
    sango_render_present(canvas);
}

__attribute__((noinline)) void sango_intro_sdk_timer(int active)
{
    if (active)
        bda_gui_window_timer_start((bda_handle_t)g_app_frame, INTRO_TIMER, FRAME_MS);
    else
        bda_gui_window_timer_stop((bda_handle_t)g_app_frame, INTRO_TIMER);
}

/* Only the intro's timer advances its frames. Legacy, touch and audio timers
 * retain their own cadence; polling also continues to service the music queue. */
int sango_intro_wait_frame(void)
{
    int event[3];
    while (true)
    {
        if (!sango_input_poll_native_event((uint32_t *)event))
            continue;
        if (sango_touch_process(event))
        {
            if (event[0] == SANGO_TOUCH_TAP || event[0] == SANGO_TOUCH_HOLD)
                return 1;
            continue;
        }
        if (event[0] == 0x10)
        {
            sango_touch_cancel();
            return 1;
        }
        if (event[0] == BDA_MSG_WINDOW_TIMER && event[1] == INTRO_TIMER)
            return 0;
    }
}

void sango_intro_open_menu(void)
{
    unsigned int door = 0;
    if (g_game_context && g_message_context)
        door = sango_color_sdk_snapshot(g_game_context);
    sango_bitmap_draw_resource(44, 1, 0, 0, 0);
    if (door)
    {
        sango_intro_sdk_timer(1);
        for (unsigned int distance = DOOR_STEP; distance <= HALF_WIDTH; distance += DOOR_STEP)
        {
            if (sango_intro_wait_frame())
                break;
            sango_intro_compose(door, g_game_context, (unsigned int)g_message_context, distance);
        }
        sango_intro_sdk_timer(0);
        sango_color_sdk_snapshot_free(door);
    }
    /* Allocation failure or an explicit skip still ends on the complete menu. */
    sango_render_present(g_game_context);
}

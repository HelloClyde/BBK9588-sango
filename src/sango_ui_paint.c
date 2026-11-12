#include "sango_internal.h"

/* Prepare every part of a modal before publishing. The application's auxiliary
 * surface is idle while these dialogs run; reuse it instead of allocating a
 * full-screen snapshot for every menu. None of this state is saved game data. */
static unsigned int paint_depth, window_context, paint_context, paint_owned;

int sango_ui_paint_active(void)
{
    return paint_depth != 0;
}

void sango_ui_paint_guard(unsigned int enabled)
{
    if (!paint_depth || !paint_context)
        bda_sango_gui_draw_guard(enabled);
}

void sango_ui_paint_redraw(void)
{
    if (!paint_depth || !paint_context)
        bda_sango_gui_request_redraw(g_app_frame, 0, 0);
}

/* Keep the native presentation boundary measurable in UI regression tests. */
__attribute__((noinline)) void sango_ui_paint_sdk_present(unsigned int canvas,
                                                          unsigned int window)
{
    sango_color_sdk_guard(1);
    sango_color_sdk_restore(canvas, 0, 0, 239, 319, window);
    sango_color_sdk_guard(0);
    bda_sango_gui_request_redraw(g_app_frame, 0, 0);
}

void sango_ui_paint_begin(void)
{
    if (paint_depth++ != 0 || !g_draw_context)
        return;
    window_context = g_draw_context;
    paint_context = g_aux_context;
    if (paint_context == window_context || paint_context == g_game_context ||
        paint_context == (unsigned int)g_message_context)
        paint_context = 0;
    if (paint_context)
        sango_color_sdk_restore(window_context, 0, 0, 239, 319, paint_context);
    else
    {
        paint_context = sango_color_sdk_snapshot(window_context);
        paint_owned = paint_context != 0;
    }
    if (paint_context)
        g_draw_context = paint_context;
}

void sango_ui_paint_end(void)
{
    if (!paint_depth || --paint_depth != 0)
        return;
    if (paint_context)
    {
        g_draw_context = window_context;
        sango_ui_paint_sdk_present(paint_context, window_context);
        if (paint_owned)
            sango_color_sdk_snapshot_free(paint_context);
    }
    paint_context = window_context = paint_owned = 0;
}

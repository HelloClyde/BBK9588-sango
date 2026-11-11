#include "sango_internal.h"

/* A menu is prepared on a compatible surface, then copied to the window once.
 * Keep this state outside the recovered globals/save region. Drawing does not
 * pump events, so the window retains its real context until this scope ends. */
static unsigned int paint_depth, window_context, paint_context;

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
    paint_context = sango_color_sdk_snapshot(window_context);
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
        sango_color_sdk_snapshot_free(paint_context);
    }
    paint_context = window_context = 0;
}

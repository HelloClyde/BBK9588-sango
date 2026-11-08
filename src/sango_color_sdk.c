#include "sango_internal.h"

/* Keep native calls in a small adapter separate from color-file parsing and
 * raster logic. The project never indexes firmware GUI tables here. */
void sango_color_sdk_pixel(uint32_t context, int x, int y, uint16_t color)
{
    bda_gui_put_pixel((bda_handle_t)context, x, y, color);
}

void sango_color_sdk_guard(int enabled)
{
    bda_sango_gui_draw_guard(enabled);
}

/* The verified SDK copy always skips one color key. Two passes with distinct
 * keys copy every RGB565 value opaquely, including black, white and magenta. */
static void copy_opaque(uint32_t source, int left, int top, int width, int height, uint32_t target)
{
    bda_gui_context_copy((bda_handle_t)source, left, top, width, height, (bda_handle_t)target, left,
                         top, 0);
    bda_gui_context_copy((bda_handle_t)source, left, top, width, height, (bda_handle_t)target, left,
                         top, 0xffff);
}

uint32_t sango_color_sdk_snapshot(uint32_t source)
{
    bda_handle_t snapshot = bda_gui_compatible_context_create((bda_handle_t)g_draw_context);
    if (snapshot)
        copy_opaque(source, 0, 0, 240, 320, (uint32_t)snapshot);
    return (uint32_t)snapshot;
}

void sango_color_sdk_restore(uint32_t snapshot, short left, short top, short right, short bottom,
                             uint32_t target)
{
    copy_opaque(snapshot, left, top, right - left + 1, bottom - top + 1, target);
}

void sango_color_sdk_snapshot_free(uint32_t snapshot)
{
    bda_gui_compatible_context_free((bda_handle_t)snapshot);
}

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

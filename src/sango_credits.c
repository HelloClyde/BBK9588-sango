#include "sango_internal.h"
#include "sango_credits.h"

static const unsigned char credits_bitmap[] = {
#include "sango_credits_bitmap.inc"
};

void sango_credits_draw(unsigned int target)
{
    if (!sango_color_draw_resource(18, 0, 0, target))
        sango_bitmap_draw_frame(0, 0, 240, 320, 0, (uint8_t *)credits_bitmap, target);
    sango_render_present(target);
}

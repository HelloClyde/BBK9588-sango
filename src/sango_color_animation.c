#include "sango_internal.h"

/* Animation rectangles must restore the pixels under the expiring sprite.
 * The old white clear was correct only for monochrome white backgrounds. */
static uint32_t animation_background;
static uint32_t animation_target;

uint32_t sango_color_animation_end(uint32_t result)
{
    if (animation_background)
        sango_color_sdk_snapshot_free(animation_background);
    animation_background = animation_target = 0;
    return result;
}

void sango_color_animation_begin(uint32_t target)
{
    sango_color_animation_end(0);
    if (sango_color_is_loaded() && target)
    {
        animation_background = sango_color_sdk_snapshot(target);
        animation_target = animation_background ? target : 0;
    }
}

void sango_color_animation_erase(short left, short top, short right, short bottom, uint32_t target)
{
    if (!animation_background || target != animation_target)
    {
        sango_render_clear_rectangle(left, top, right, bottom, target);
        return;
    }
    if (left < 0)
        left = 0;
    if (top < 0)
        top = 0;
    if (right > 239)
        right = 239;
    if (bottom > 319)
        bottom = 319;
    if (left <= right && top <= bottom)
        sango_color_sdk_restore(animation_background, left, top, right, bottom, target);
}

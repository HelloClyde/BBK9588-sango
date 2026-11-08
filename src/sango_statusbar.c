#include "sango_internal.h"
#include "sango_statusbar.h"

static const unsigned char toolbar_bitmap[] = {
#include "sango_statusbar_bitmap.inc"
};

static const unsigned char battle_toolbar_bitmap[] = {
#include "sango_battle_toolbar_bitmap.inc"
};

void sango_statusbar_draw(unsigned int target)
{
    /* Use the recovered rasterizer and its existing SDK drawing bindings. */
    sango_bitmap_draw_frame(0, SANGO_STATUSBAR_TOP, SANGO_STATUSBAR_WIDTH, SANGO_STATUSBAR_HEIGHT,
                            0, (uint8_t *)toolbar_bitmap, target);
}

enum SangoStatusbarAction sango_statusbar_hit(unsigned int x, unsigned int y)
{
    if (y < SANGO_STATUSBAR_TOP + 2 || y >= SANGO_STATUSBAR_TOP + SANGO_STATUSBAR_HEIGHT - 2)
        return SANGO_STATUSBAR_NONE;
    /* Interior rectangles of the generated, reviewed button frames. */
    if (x >= 60 && x < 114)
        return SANGO_STATUSBAR_INFO;
    if (x >= 128 && x < 182)
        return SANGO_STATUSBAR_FIND;
    return SANGO_STATUSBAR_NONE;
}

void sango_battle_toolbar_draw(unsigned int target)
{
    /* Fit the original order: status, controls, then the two-row summary.
       Keep the reviewed source bitmap; sample its 36 rows into 24 screen rows. */
    unsigned int x, y;
    sango_render_clear_rectangle(0, SANGO_BATTLE_TOOLBAR_TOP, 239, 319, target);
    for (y = 0; y < SANGO_BATTLE_TOOLBAR_HEIGHT; ++y)
    {
        unsigned int source_y = y * 3 / 2;
        for (x = 0; x < SANGO_STATUSBAR_WIDTH; ++x)
        {
            unsigned int color =
                battle_toolbar_bitmap[6 + source_y * (SANGO_STATUSBAR_WIDTH / 4) + x / 4];
            color = (color >> (6 - (x % 4) * 2)) & 3;
            sango_display_put_gray_pixel(x, SANGO_BATTLE_TOOLBAR_TOP + y, color, target);
        }
    }
}

enum SangoBattleToolbarAction sango_battle_toolbar_hit(unsigned int x, unsigned int y)
{
    if (y < SANGO_BATTLE_TOOLBAR_TOP + 2 ||
        y >= SANGO_BATTLE_TOOLBAR_TOP + SANGO_BATTLE_TOOLBAR_HEIGHT - 2)
        return SANGO_BATTLE_TOOLBAR_NONE;
    if (x >= 60 && x < 114)
        return SANGO_BATTLE_TOOLBAR_INFO;
    if (x >= 128 && x < 182)
        return SANGO_BATTLE_TOOLBAR_OVERVIEW;
    return SANGO_BATTLE_TOOLBAR_NONE;
}

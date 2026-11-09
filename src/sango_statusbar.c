#include "sango_internal.h"
#include "sango_statusbar.h"

/* Both scenes share the same native-size toolbar and screen baseline. */
_Static_assert(SANGO_BATTLE_STATUS_TOP + SANGO_BATTLE_STATUS_HEIGHT == SANGO_BATTLE_TOOLBAR_TOP,
               "Battle terrain and status must end at the shared toolbar");

static const unsigned char toolbar_bitmap[] = {
#include "sango_statusbar_bitmap.inc"
};

static const unsigned char battle_toolbar_bitmap[] = {
#include "sango_battle_toolbar_bitmap.inc"
};

void sango_statusbar_draw(unsigned int target)
{
    if (sango_color_draw_resource(17, 0, SANGO_STATUSBAR_TOP, target))
        return;
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
    /* Render the reviewed artwork at its native size; do not squeeze its glyphs. */
    sango_render_clear_rectangle(0, SANGO_BATTLE_TOOLBAR_TOP, 239, 319, target);
    if (sango_color_draw_resource(17, 0, SANGO_BATTLE_TOOLBAR_TOP, target))
        return;
    sango_bitmap_draw_frame(0, SANGO_BATTLE_TOOLBAR_TOP, SANGO_STATUSBAR_WIDTH,
                            SANGO_BATTLE_TOOLBAR_HEIGHT, 0, (uint8_t *)battle_toolbar_bitmap,
                            target);
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

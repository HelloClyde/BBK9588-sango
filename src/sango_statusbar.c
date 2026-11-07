#include "sango_recovered.h"
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
    FUN_81c15070(0, SANGO_STATUSBAR_TOP, SANGO_STATUSBAR_WIDTH,
                 SANGO_STATUSBAR_HEIGHT, 0, (byte *)toolbar_bitmap, target);
}

enum SangoStatusbarAction sango_statusbar_hit(unsigned int x, unsigned int y)
{
    if (y < SANGO_STATUSBAR_TOP + 2 ||
        y >= SANGO_STATUSBAR_TOP + SANGO_STATUSBAR_HEIGHT - 2)
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
    /* 9288S stacks its 16-pixel status row directly above the toolbar.
       Clear the remaining footer so strategy UI and old button rows cannot
       survive below the relocated battle controls. */
    FUN_81c15210(0,SANGO_BATTLE_TOOLBAR_TOP,239,319,target);
    FUN_81c15070(0,SANGO_BATTLE_TOOLBAR_TOP,SANGO_STATUSBAR_WIDTH,
                 SANGO_STATUSBAR_HEIGHT,0,(byte *)battle_toolbar_bitmap,target);
}

enum SangoBattleToolbarAction sango_battle_toolbar_hit(unsigned int x, unsigned int y)
{
    if (y < SANGO_BATTLE_TOOLBAR_TOP + 2 ||
        y >= SANGO_BATTLE_TOOLBAR_TOP + SANGO_STATUSBAR_HEIGHT - 2)
        return SANGO_BATTLE_TOOLBAR_NONE;
    if (x >= 60 && x < 114)
        return SANGO_BATTLE_TOOLBAR_INFO;
    if (x >= 128 && x < 182)
        return SANGO_BATTLE_TOOLBAR_OVERVIEW;
    return SANGO_BATTLE_TOOLBAR_NONE;
}

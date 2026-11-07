#ifndef SANGO_STATUSBAR_H
#define SANGO_STATUSBAR_H

enum SangoStatusbarAction {
    SANGO_STATUSBAR_NONE,
    SANGO_STATUSBAR_INFO,
    SANGO_STATUSBAR_FIND
};

enum SangoBattleToolbarAction {
    SANGO_BATTLE_TOOLBAR_NONE,
    SANGO_BATTLE_TOOLBAR_INFO,
    SANGO_BATTLE_TOOLBAR_OVERVIEW
};

enum {
    SANGO_STATUSBAR_TOP = 232,
    SANGO_STATUSBAR_WIDTH = 240,
    SANGO_STATUSBAR_HEIGHT = 36,
    SANGO_BATTLE_STATUS_TOP = 241,
    SANGO_BATTLE_STATUS_HEIGHT = 16,
    SANGO_BATTLE_TOOLBAR_TOP = SANGO_BATTLE_STATUS_TOP + SANGO_BATTLE_STATUS_HEIGHT
};

void sango_statusbar_draw(unsigned int target);
enum SangoStatusbarAction sango_statusbar_hit(unsigned int x, unsigned int y);
void sango_battle_toolbar_draw(unsigned int target);
enum SangoBattleToolbarAction sango_battle_toolbar_hit(unsigned int x, unsigned int y);

#endif

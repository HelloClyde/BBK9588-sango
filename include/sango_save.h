#ifndef SANGO_SAVE_H
#define SANGO_SAVE_H
#include "sango_types.h"

/* Resource046 is a240x320 ruled page. Keep text/highlight/touch on the same
 * three27px rows;12px glyphs must stay clear of y121/148/175 separators. */
enum
{
    SANGO_SAVE_SLOT_COUNT = 3,
    SANGO_SAVE_ROW_TOP = 95,
    SANGO_SAVE_ROW_HEIGHT = 27,
    SANGO_SAVE_TEXT_LEFT = 40,
    SANGO_SAVE_TEXT_TOP = 102,
    SANGO_SAVE_TEXT_HEIGHT = 12,
    SANGO_SAVE_ROW_LEFT = 24,
    SANGO_SAVE_ROW_RIGHT = 215
};

uint32_t sango_save_choose_slot(char load_mode);
void sango_save_draw_slots(void);
uint32_t sango_save_load_slot(char slot);
uint32_t sango_save_write_slot(char slot);

#endif

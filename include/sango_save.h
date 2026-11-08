#ifndef SANGO_SAVE_H
#define SANGO_SAVE_H
#include "sango_types.h"

uint32_t sango_save_choose_slot(char load_mode);
void sango_save_draw_slots(void);
uint32_t sango_save_load_slot(char slot);
uint32_t sango_save_write_slot(char slot);

#endif

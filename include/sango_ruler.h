#ifndef SANGO_RULER_H
#define SANGO_RULER_H
void sango_ruler_sdk_text(int x, int y, const char *text, int selected);
void sango_ruler_sdk_text_at(unsigned int target, int x, int y, const char *text, int selected);
void sango_ruler_sdk_picture(unsigned int target, int x, int y, unsigned int width,
                             unsigned int height, const uint16_t *pixels);
void sango_ruler_sdk_present(unsigned int canvas, unsigned int window, unsigned int dirty,
                             int list_top, int list_bottom);
#include "sango_types.h"

enum
{
    SANGO_RULER_ROWS = 10,
    SANGO_RULER_LIST_LEFT = 28,
    SANGO_RULER_LIST_RIGHT = 84,
    SANGO_RULER_LIST_TOP = 64,
    SANGO_RULER_ROW_HEIGHT = 18,
    SANGO_RULER_MAP_X = 118,
    SANGO_RULER_MAP_Y = 64
};
void sango_ruler_begin(unsigned int count);
void sango_ruler_present(void);
void sango_ruler_flash_cities(unsigned int count, const uint8_t *cities, int positions);
void sango_ruler_draw_names(unsigned int first);
void sango_ruler_select(unsigned int previous, unsigned int previous_first, unsigned int selected,
                        unsigned int first);
unsigned int sango_ruler_end(unsigned int result);
int sango_ruler_touch_button(const int *event);
#endif

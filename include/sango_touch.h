#ifndef SANGO_TOUCH_H
#define SANGO_TOUCH_H
#include "sango_types.h"

enum
{
    SANGO_TOUCH_TAP = 11,
    SANGO_TOUCH_PAN = 12,
    SANGO_TOUCH_PAN_END = 13,
    SANGO_TOUCH_HOLD = 14,
    SANGO_TOUCH_TIMER_ID = 2,
    SANGO_TOUCH_ANIMATION_KEY = 0xfe
};

/* Event ABI stays three words: kind, key/delta, packed signed-16-bit x/y. */
int sango_touch_process(int *event);
void sango_touch_cancel(void);
void sango_touch_sdk_position(uint16_t *x, uint16_t *y);
uint32_t sango_touch_sdk_ticks(void);
void sango_touch_sdk_timer(int active);
int sango_touch_x(const int *event);
int sango_touch_y(const int *event);
int sango_touch_last_menu_row(unsigned int background);
int sango_touch_menu_row(unsigned int background, const int *event);
int sango_touch_choose_row(const int *event, int left, int top, int right, int row_height,
                           unsigned int visible, unsigned int first, unsigned int total);
int sango_touch_swipe_key(const int *event);
int sango_touch_map_point(const int *event, uint8_t *state, int columns, int rows, int screen_width,
                          int screen_height);
int sango_touch_pan_map(const int *event, uint8_t *state, int world_width, int world_height,
                        int columns, int rows, int screen_width, int screen_height, int *remainder);
void sango_touch_draw_number_controls(void);
#endif

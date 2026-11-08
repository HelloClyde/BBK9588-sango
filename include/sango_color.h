#ifndef SANGO_COLOR_H
#define SANGO_COLOR_H
#include "sango_types.h"
void sango_color_load(const char *library_path, uint32_t library_bytes);
void sango_color_unload(void);
int sango_color_use_buffer(void *buffer, uint32_t bytes, uint32_t library_bytes);
const uint16_t *sango_color_pixels(uint32_t original_pixels, uint32_t width, uint32_t height,
                                   int masked);
int sango_color_draw_raster(uint32_t x, short y, uint32_t width, uint32_t height,
                            uint32_t original_pixels, uint32_t target, int masked);
int sango_color_draw_resource(unsigned int resource, int x, short y, unsigned int target);
void sango_color_put_pixel(short x, short y, uint16_t color, unsigned int target);
void sango_color_sdk_pixel(uint32_t context, int x, int y, uint16_t color);
void sango_color_sdk_guard(int enabled);
#endif

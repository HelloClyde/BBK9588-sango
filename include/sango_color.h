#ifndef SANGO_COLOR_H
#define SANGO_COLOR_H
#include "sango_types.h"
#define SANGO_COLOR_TRANSPARENT_ZERO 0x100u
int sango_color_strategy_map_begin(uint32_t target);
void sango_color_strategy_map_end(void);
void sango_color_load(const char *library_path, uint32_t library_bytes);
void sango_color_unload(void);
int sango_color_is_loaded(void);
uint32_t sango_color_frame_flags(uint32_t original_pixels, uint32_t width, uint32_t height,
                                 int masked);
void sango_color_animation_begin(uint32_t target);
uint32_t sango_color_animation_end(uint32_t result);
void sango_color_animation_erase(short left, short top, short right, short bottom, uint32_t target);
uint32_t sango_color_sdk_snapshot(uint32_t source);
void sango_color_sdk_restore(uint32_t snapshot, short left, short top, short right, short bottom,
                             uint32_t target);
void sango_color_sdk_snapshot_free(uint32_t snapshot);
int sango_color_use_buffer(void *buffer, uint32_t bytes, uint32_t library_bytes);
const uint16_t *sango_color_pixels(uint32_t original_pixels, uint32_t width, uint32_t height,
                                   int masked);
int sango_color_draw_raster(uint32_t x, short y, uint32_t width, uint32_t height,
                            uint32_t original_pixels, uint32_t target, int masked);
int sango_color_draw_resource(unsigned int resource, int x, short y, unsigned int target);
void sango_color_put_pixel(short x, short y, uint16_t color, unsigned int target);
void sango_color_sdk_pixel(uint32_t context, int x, int y, uint16_t color);
void sango_color_sdk_guard(int enabled);
void sango_color_sdk_text(unsigned int target, int font, int x, int y, const char *text);
#endif

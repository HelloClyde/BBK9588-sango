#ifndef SANGO_RENDER_H
#define SANGO_RENDER_H
#include "sango_types.h"

uint32_t sango_animation_play_range(uint32_t resource_id, uint32_t first_command, uint32_t last_command, uint32_t play_flags, uint16_t origin_x, short origin_y);
void sango_raster_draw_screen(uint32_t param_1, short param_2, uint32_t param_3, uint32_t param_4, int param_5);
void sango_raster_draw_opaque(uint32_t param_1, short param_2, uint32_t param_3, uint32_t param_4, int param_5, uint32_t param_6);
void sango_raster_draw_masked(uint32_t param_1, short param_2, uint32_t param_3, uint32_t param_4, int param_5, uint32_t param_6);
void sango_raster_draw_masked_screen(uint32_t param_1, short param_2, uint32_t param_3, uint32_t param_4, int param_5);
void sango_text_draw_legacy(uint16_t x, uint16_t y, char *text);
void sango_font_load_glyph(uint32_t param_1, int param_2);
int sango_font_glyph_offset(uint32_t param_1);
void sango_ui_show_message(char *param_1, uint32_t param_2);
void sango_render_present(uint32_t param_1);
void sango_bitmap_draw_frame_screen(uint16_t x, short y, uint16_t width, uint16_t height, uint8_t frame, uint8_t *bitmap);
void sango_bitmap_draw_frame(uint16_t x, short y, uint16_t width, uint16_t height, uint8_t frame, uint8_t *bitmap, uint32_t target);
void sango_text_draw_context(short x, short y, char *text, uint32_t target);
void sango_text_reset_clip_bounds(void);
void sango_text_draw_character(uint8_t param_1, uint8_t param_2, uint8_t param_3);
void sango_render_clear_rectangle(short left, short top, short right, short bottom, uint32_t target);
int sango_bitmap_rectangle_byte_count(int param_1, int param_2, int param_3, int param_4);

#endif

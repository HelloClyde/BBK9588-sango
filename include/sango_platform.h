#ifndef SANGO_PLATFORM_H
#define SANGO_PLATFORM_H
#include "sango_types.h"

uint32_t sango_window_proc(uint32_t handle, int message, uint32_t wparam, uint32_t lparam);
void sango_display_copy_and_refresh(short param_1, short param_2, uint32_t param_3,
                                    uint32_t param_4);
void sango_display_fill_rectangle(short left, short top, short right, short bottom, uint32_t color,
                                  uint32_t target);
void sango_display_blit_palette_bitmap(short param_1, short param_2, short param_3, short param_4,
                                       short param_5, short param_6, int param_7, uint32_t param_8,
                                       uint32_t param_9, uint32_t param_10, int param_11);
void sango_display_capture_bitmap(short param_1, short param_2, short param_3, short param_4,
                                  short param_5, short param_6, uint16_t *param_7, int param_8,
                                  uint32_t param_9, int param_10, int param_11);
void sango_display_put_gray_pixel(short param_1, short param_2, uint32_t param_3, uint32_t param_4);
void sango_display_draw_line(short param_1, short param_2, short param_3, short param_4,
                             uint32_t param_5, uint32_t param_6, uint32_t param_7);
void sango_display_draw_rectangle(short param_1, short param_2, short param_3, short param_4,
                                  uint32_t param_5, uint32_t param_6, int param_7);
void sango_display_draw_circle(short param_1, short param_2, int param_3, uint32_t param_4,
                               uint32_t param_5, int param_6);
void sango_display_draw_polyline(short param_1, short param_2, int param_3, uint32_t param_4,
                                 int param_5);
void sango_display_set_brush(int param_1, uint32_t param_2);
void sango_display_set_text_color(int param_1, uint32_t param_2);
uint32_t sango_display_select_font(uint8_t param_1, uint32_t param_2);
uint16_t *sango_bitmap_open_embedded_entry(uint32_t *param_1, uint32_t param_2, int param_3,
                                           int param_4);
uint32_t sango_input_key_is_down(uint32_t param_1);
void sango_input_decode_key_packet(short param_1, short param_2, short param_3, short param_4,
                                   int param_5);
uint32_t sango_text_input_proc(uint32_t handle, int message, uint32_t wparam, uint32_t lparam);
uint32_t sango_text_input_dialog(uint32_t param_1, uint8_t *param_2, uint32_t param_3);
void sango_display_render_bitmap_region(short param_1, short param_2, int param_3, uint32_t param_4,
                                        int param_5, int param_6);
void sango_platform_window_auxiliary(uint32_t param_1, uint32_t param_2);
int sango_create_app_frame(void);
uint32_t sango_platform_allocate_zeroed_buffer(void);
int sango_run_event_loop_and_close(void);
void sango_platform_init_window_descriptor(uint32_t *param_1);
uint32_t sango_input_poll_native_event(uint32_t *param_1);
int bbk_post_message(uint32_t message, uint32_t wparam, uint32_t lparam);
void *bbk_alloc(uint32_t size);
void bbk_free_if_nonnull(void *ptr);
char *bbk_strcat(char *destination, char *source);
uint32_t bbk_strlen(char *text);
void *bbk_memcpy(void *dst, void *src, uint32_t size);
void sango_memory_fill(void *destination, int value, uint32_t bytes);
uint8_t *sango_format_integer(int param_1, uint8_t *param_2, int param_3);
void bbk_zero_time_stub(uint16_t *time_fields);
void bbk_srand(uint32_t seed);
uint32_t bbk_rand(void);
uint32_t sango_timer_start(uint32_t param_1, uint32_t param_2);
uint32_t sango_timer_stop(uint32_t param_1);
void *bbk_compatible_context_create(void);
int bbk_compatible_context_free(void *context);
void sango_display_present_context(uint32_t param_1, uint32_t param_2);
void sango_display_noop(void);
void sango_display_invert_rectangle(short param_1, short param_2, short param_3, short param_4,
                                    uint32_t param_5);
int sango_platform_noop(uint8_t *param_1);
uint32_t sango_bitmap_query_dimensions(uint16_t *param_1, uint32_t param_2, uint32_t param_3,
                                       uint32_t *param_4, uint32_t *param_5);
void sango_display_fill_gray_rectangle(short param_1, short param_2, short param_3, short param_4,
                                       uint32_t param_5, uint32_t param_6);
void sango_text_get_font_metrics(uint16_t *param_1, uint32_t param_2);
void sango_text_draw_native(short param_1, short param_2, char *param_3, uint32_t param_4);
void bbk_clearerr(void *file);
int bbk_ferror(void *file);
int bbk_fclose(void *file);
int bbk_feof(void *file);
uint32_t sango_platform_stub_0af50(void);
uint32_t sango_platform_stub_0af58(void);
void *bbk_fopen(char *path, char *mode);
uint32_t sango_platform_stub_0af88(void);
uint32_t sango_platform_stub_0af90(void);
uint32_t bbk_fread(void *buffer, uint32_t size, uint32_t count, void *file);
int bbk_fseek(void *file, int offset, int whence);
int bbk_ftell(void *file);
uint32_t bbk_fwrite(void *param_1, uint32_t param_2, uint32_t param_3, void *param_4);
uint32_t sango_platform_stub_0b070(void);
uint32_t sango_platform_stub_0b078(void);
uint32_t sango_platform_stub_0b080(void);
uint32_t sango_platform_stub_0b088(void);
uint32_t sango_platform_stub_0b090(void);
int bbk_rename(char *old_path, char *new_path);
void sango_platform_stub_0b0c0(void);
void *bbk_load_file_with_progress(char *path);
uint32_t sango_platform_stub_0b2c4(void);
uint32_t sango_platform_stub_0b2cc(void);
uint32_t sango_platform_stub_0b2d4(void);
void sango_input_dispatch_pending_events(uint32_t param_1);
int graphics_init_stub(void);
uint32_t sango_platform_stub_0b508(void);
int bbk_message_box(char *message, char *title, uint32_t flags);
uint32_t sango_input_next_event(int *event);
uint32_t sango_input_wait(short ticks, char allow_key);
uint32_t sango_input_peek_key(void);
void sango_runtime_noop_a(void);
void sango_runtime_noop_b(void);
uint32_t sango_runtime_read_tick_counter(uint32_t *param_1);

#endif

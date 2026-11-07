#ifndef BDA_SANGO_COMPAT_H
#define BDA_SANGO_COMPAT_H
#include <bda_sdk.h>
#include "sango_sdk_bindings.h"
/* Project-local compatibility extension. The unsupported legacy
 * APIs are kept here, using the SDK loader-table accessors and the
 * original observed O32 ABI. Application C has only named calls. */
static inline int bda_sango_gui_event_poll(void * a0, unsigned int a1) {
#ifdef SANGO_BIND_GUI_EVENT_POLL
    return (int)SANGO_BIND_GUI_EVENT_POLL(a0, a1);
#else
    typedef int (*entry_t)(void *, unsigned int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x030u);
    return (int)entry(a0, a1);
#endif
}
static inline int bda_sango_gui_post_message(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3) {
#ifdef SANGO_BIND_GUI_POST_MESSAGE
    return (int)SANGO_BIND_GUI_POST_MESSAGE(a0, a1, a2, a3);
#else
    typedef int (*entry_t)(unsigned int, unsigned int, unsigned int, unsigned int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x03cu);
    return (int)entry(a0, a1, a2, a3);
#endif
}
static inline int bda_sango_gui_send_message(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3) {
#ifdef SANGO_BIND_GUI_SEND_MESSAGE
    return (int)SANGO_BIND_GUI_SEND_MESSAGE(a0, a1, a2, a3);
#else
    return (int)bda_control_send((bda_handle_t)a0, (u32)a1, (u32)a2, (u32)a3);
#endif
}
static inline int bda_sango_gui_frame_release(unsigned int a0) {
#ifdef SANGO_BIND_GUI_FRAME_RELEASE
    return (int)SANGO_BIND_GUI_FRAME_RELEASE(a0);
#else
    return (int)bda_gui_frame_release((bda_handle_t)a0);
#endif
}
static inline int bda_sango_gui_event_step(void * a0) {
#ifdef SANGO_BIND_GUI_EVENT_STEP
    return (int)SANGO_BIND_GUI_EVENT_STEP(a0);
#else
    typedef int (*entry_t)(void *);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x050u);
    return (int)entry(a0);
#endif
}
static inline int bda_sango_gui_event_dispatch(void * a0) {
#ifdef SANGO_BIND_GUI_EVENT_DISPATCH
    return (int)SANGO_BIND_GUI_EVENT_DISPATCH(a0);
#else
    typedef int (*entry_t)(void *);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x054u);
    return (int)entry(a0);
#endif
}
static inline int bda_sango_gui_draw_guard(unsigned int a0) {
#ifdef SANGO_BIND_GUI_DRAW_GUARD
    return (int)SANGO_BIND_GUI_DRAW_GUARD(a0);
#else
    typedef int (*entry_t)(unsigned int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x074u);
    return (int)entry(a0);
#endif
}
static inline int bda_sango_gui_register_frame(void * a0) {
#ifdef SANGO_BIND_GUI_REGISTER_FRAME
    return (int)SANGO_BIND_GUI_REGISTER_FRAME(a0);
#else
    return (int)bda_gui_register_frame_desc((bda_frame_desc_t *)a0);
#endif
}
static inline int bda_sango_gui_frame_stop(unsigned int a0) {
#ifdef SANGO_BIND_GUI_FRAME_STOP
    return (int)SANGO_BIND_GUI_FRAME_STOP(a0);
#else
    return (int)bda_gui_frame_stop((bda_handle_t)a0);
#endif
}
static inline int bda_sango_gui_default_proc(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3) {
#ifdef SANGO_BIND_GUI_DEFAULT_PROC
    return (int)SANGO_BIND_GUI_DEFAULT_PROC(a0, a1, a2, a3);
#else
    return (int)bda_gui_default_proc((bda_handle_t)a0, (u32)a1, (u32)a2, (u32)a3);
#endif
}
static inline int bda_sango_gui_request_redraw(unsigned int a0, unsigned int a1, unsigned int a2) {
#ifdef SANGO_BIND_GUI_REQUEST_REDRAW
    return (int)SANGO_BIND_GUI_REQUEST_REDRAW(a0, a1, a2);
#else
    typedef int (*entry_t)(unsigned int, unsigned int, unsigned int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x0e0u);
    return (int)entry(a0, a1, a2);
#endif
}
static inline unsigned int bda_sango_gui_object_draw_begin(unsigned int a0) {
#ifdef SANGO_BIND_GUI_OBJECT_DRAW_BEGIN
    return (unsigned int)SANGO_BIND_GUI_OBJECT_DRAW_BEGIN(a0);
#else
    return (unsigned int)bda_gui_object_draw_begin((bda_handle_t)a0);
#endif
}
static inline void bda_sango_gui_object_draw_end(unsigned int a0, unsigned int a1) {
#ifdef SANGO_BIND_GUI_OBJECT_DRAW_END
    (void)SANGO_BIND_GUI_OBJECT_DRAW_END(a0, a1);
#else
    (void)bda_gui_object_draw_end((bda_handle_t)a0, (bda_handle_t)a1);
#endif
}
static inline int bda_sango_gui_set_active(unsigned int a0) {
#ifdef SANGO_BIND_GUI_SET_ACTIVE
    return (int)SANGO_BIND_GUI_SET_ACTIVE(a0);
#else
    return (int)bda_control_set_active((bda_handle_t)a0);
#endif
}
static inline void bda_sango_gui_close_frame(unsigned int a0) {
#ifdef SANGO_BIND_GUI_CLOSE_FRAME
    (void)SANGO_BIND_GUI_CLOSE_FRAME(a0);
#else
    (void)bda_gui_close_frame((bda_handle_t)a0);
#endif
}
static inline unsigned int bda_sango_gui_control_create(const char * a0, const char * a1, unsigned int a2, unsigned int a3, unsigned int a4, int a5, int a6, int a7, int a8, unsigned int a9, unsigned int a10) {
#ifdef SANGO_BIND_GUI_CONTROL_CREATE
    return (unsigned int)SANGO_BIND_GUI_CONTROL_CREATE(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
#else
    typedef unsigned int (*entry_t)(const char *, const char *, unsigned int, unsigned int, unsigned int, int, int, int, int, unsigned int, unsigned int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x1a4u);
    return (unsigned int)entry(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
#endif
}
static inline int bda_sango_gui_control_destroy(unsigned int a0) {
#ifdef SANGO_BIND_GUI_CONTROL_DESTROY
    return (int)SANGO_BIND_GUI_CONTROL_DESTROY(a0);
#else
    return (int)bda_control_destroy((bda_handle_t)a0);
#endif
}
static inline int bda_sango_gui_timer_start(unsigned int a0, unsigned int a1, unsigned int a2) {
#ifdef SANGO_BIND_GUI_TIMER_START
    return (int)SANGO_BIND_GUI_TIMER_START(a0, a1, a2);
#else
    return (int)bda_gui_window_timer_start((bda_handle_t)a0, (u32)a1, (u32)a2);
#endif
}
static inline int bda_sango_gui_timer_stop(unsigned int a0, unsigned int a1) {
#ifdef SANGO_BIND_GUI_TIMER_STOP
    return (int)SANGO_BIND_GUI_TIMER_STOP(a0, a1);
#else
    return (int)bda_gui_window_timer_stop((bda_handle_t)a0, (u32)a1);
#endif
}
static inline int bda_sango_gui_message_box(unsigned int a0, const char * a1, const char * a2, unsigned int a3) {
#ifdef SANGO_BIND_GUI_MESSAGE_BOX
    return (int)SANGO_BIND_GUI_MESSAGE_BOX(a0, a1, a2, a3);
#else
    return (int)bda_msgbox_ex((bda_handle_t)a0, (const char *)a2, (const char *)a1, (u32)a3);
#endif
}
static inline void * bda_sango_gui_draw_object(unsigned int a0) {
#ifdef SANGO_BIND_GUI_DRAW_OBJECT
    return (void *)SANGO_BIND_GUI_DRAW_OBJECT(a0);
#else
    return (void *)bda_gui_draw_object_create((u32)a0);
#endif
}
static inline int bda_sango_gui_display_metric(unsigned int a0, unsigned int a1) {
#ifdef SANGO_BIND_GUI_DISPLAY_METRIC
    return (int)SANGO_BIND_GUI_DISPLAY_METRIC(a0, a1);
#else
    typedef int (*entry_t)(unsigned int, unsigned int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x300u);
    return (int)entry(a0, a1);
#endif
}
static inline unsigned int bda_sango_gui_current_draw(unsigned int a0) {
#ifdef SANGO_BIND_GUI_CURRENT_DRAW
    return (unsigned int)SANGO_BIND_GUI_CURRENT_DRAW(a0);
#else
    return (unsigned int)bda_gui_current_draw((bda_handle_t)a0);
#endif
}
static inline void bda_sango_gui_end_draw(unsigned int a0) {
#ifdef SANGO_BIND_GUI_END_DRAW
    (void)SANGO_BIND_GUI_END_DRAW(a0);
#else
    (void)bda_gui_end_draw((bda_handle_t)a0);
#endif
}
static inline void * bda_sango_gui_compatible_create(unsigned int a0) {
#ifdef SANGO_BIND_GUI_COMPATIBLE_CREATE
    return (void *)SANGO_BIND_GUI_COMPATIBLE_CREATE(a0);
#else
    return (void *)bda_gui_compatible_context_create((bda_handle_t)a0);
#endif
}
static inline void bda_sango_gui_compatible_free(void * a0) {
#ifdef SANGO_BIND_GUI_COMPATIBLE_FREE
    (void)SANGO_BIND_GUI_COMPATIBLE_FREE(a0);
#else
    (void)bda_gui_compatible_context_free((bda_handle_t)a0);
#endif
}
static inline unsigned int bda_sango_gui_set_fill_object(unsigned int a0, unsigned int a1) {
#ifdef SANGO_BIND_GUI_SET_FILL_OBJECT
    return (unsigned int)SANGO_BIND_GUI_SET_FILL_OBJECT(a0, a1);
#else
    typedef unsigned int (*entry_t)(unsigned int, unsigned int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x334u);
    return (unsigned int)entry(a0, a1);
#endif
}
static inline int bda_sango_gui_set_text_mode(unsigned int a0, unsigned int a1) {
#ifdef SANGO_BIND_GUI_SET_TEXT_MODE
    return (int)SANGO_BIND_GUI_SET_TEXT_MODE(a0, a1);
#else
    return (int)bda_gui_set_text_mode((bda_handle_t)a0, (u32)a1);
#endif
}
static inline int bda_sango_gui_set_text_color(unsigned int a0, unsigned int a1) {
#ifdef SANGO_BIND_GUI_SET_TEXT_COLOR
    return (int)SANGO_BIND_GUI_SET_TEXT_COLOR(a0, a1);
#else
    return (int)bda_gui_set_text_color((bda_handle_t)a0, (u32)a1);
#endif
}
static inline void * bda_sango_gui_select_draw_object(unsigned int a0, void * a1) {
#ifdef SANGO_BIND_GUI_SELECT_DRAW_OBJECT
    return (void *)SANGO_BIND_GUI_SELECT_DRAW_OBJECT(a0, a1);
#else
    return (void *)bda_gui_select_draw_object((bda_handle_t)a0, (void *)a1);
#endif
}
static inline unsigned int bda_sango_gui_bind_image_resource(unsigned int a0, unsigned int a1) {
#ifdef SANGO_BIND_GUI_BIND_IMAGE_RESOURCE
    return (unsigned int)SANGO_BIND_GUI_BIND_IMAGE_RESOURCE(a0, a1);
#else
    typedef unsigned int (*entry_t)(unsigned int, unsigned int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x35cu);
    return (unsigned int)entry(a0, a1);
#endif
}
static inline int bda_sango_gui_put_pixel(unsigned int a0, int a1, int a2, unsigned int a3) {
#ifdef SANGO_BIND_GUI_PUT_PIXEL
    return (int)SANGO_BIND_GUI_PUT_PIXEL(a0, a1, a2, a3);
#else
    return (int)bda_gui_put_pixel((bda_handle_t)a0, (s32)a1, (s32)a2, (u32)a3);
#endif
}
static inline int bda_sango_gui_rgb(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3) {
#ifdef SANGO_BIND_GUI_RGB
    return (int)SANGO_BIND_GUI_RGB(a0, a1, a2, a3);
#else
    return (int)bda_gui_rgb((bda_handle_t)a0, (u32)a1, (u32)a2, (u32)a3);
#endif
}
static inline void bda_sango_gui_line_to(unsigned int a0, int a1, int a2) {
#ifdef SANGO_BIND_GUI_LINE_TO
    (void)SANGO_BIND_GUI_LINE_TO(a0, a1, a2);
#else
    (void)bda_gui_line_to((bda_handle_t)a0, (s32)a1, (s32)a2);
#endif
}
static inline void bda_sango_gui_move_to(unsigned int a0, int a1, int a2) {
#ifdef SANGO_BIND_GUI_MOVE_TO
    (void)SANGO_BIND_GUI_MOVE_TO(a0, a1, a2);
#else
    (void)bda_gui_move_to((bda_handle_t)a0, (s32)a1, (s32)a2);
#endif
}
static inline void bda_sango_gui_circle(unsigned int a0, int a1, int a2, int a3) {
#ifdef SANGO_BIND_GUI_CIRCLE
    (void)SANGO_BIND_GUI_CIRCLE(a0, a1, a2, a3);
#else
    (void)bda_gui_circle((bda_handle_t)a0, (s32)a1, (s32)a2, (s32)a3);
#endif
}
static inline void bda_sango_gui_rectangle(unsigned int a0, int a1, int a2, int a3, int a4) {
#ifdef SANGO_BIND_GUI_RECTANGLE
    (void)SANGO_BIND_GUI_RECTANGLE(a0, a1, a2, a3, a4);
#else
    (void)bda_gui_rectangle((bda_handle_t)a0, (s32)a1, (s32)a2, (s32)a3, (s32)a4);
#endif
}
static inline int bda_sango_gui_capture_region(int a0, int a1, int a2, int a3, void * a4) {
#ifdef SANGO_BIND_GUI_CAPTURE_REGION
    return (int)SANGO_BIND_GUI_CAPTURE_REGION(a0, a1, a2, a3, a4);
#else
    typedef int (*entry_t)(int, int, int, int, void *);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x3f8u);
    return (int)entry(a0, a1, a2, a3, a4);
#endif
}
static inline int bda_sango_gui_restore_region(int a0, int a1, int a2, int a3, const void * a4) {
#ifdef SANGO_BIND_GUI_RESTORE_REGION
    return (int)SANGO_BIND_GUI_RESTORE_REGION(a0, a1, a2, a3, a4);
#else
    typedef int (*entry_t)(int, int, int, int, const void *);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x400u);
    return (int)entry(a0, a1, a2, a3, a4);
#endif
}
static inline int bda_sango_gui_fill_region(unsigned int a0, int a1, int a2, int a3, int a4) {
#ifdef SANGO_BIND_GUI_FILL_REGION
    return (int)SANGO_BIND_GUI_FILL_REGION(a0, a1, a2, a3, a4);
#else
    typedef int (*entry_t)(unsigned int, int, int, int, int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x40cu);
    return (int)entry(a0, a1, a2, a3, a4);
#endif
}
static inline int bda_sango_gui_render_region(unsigned int a0, int a1, int a2, int a3, int a4, int a5, int a6, void * a7, int a8, int a9) {
#ifdef SANGO_BIND_GUI_RENDER_REGION
    return (int)SANGO_BIND_GUI_RENDER_REGION(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
#else
    typedef int (*entry_t)(unsigned int, int, int, int, int, int, int, void *, int, int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x414u);
    return (int)entry(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
#endif
}
static inline int bda_sango_gui_context_copy(unsigned int a0, int a1, int a2, int a3, int a4, unsigned int a5, int a6, int a7, unsigned int a8) {
#ifdef SANGO_BIND_GUI_CONTEXT_COPY
    return (int)SANGO_BIND_GUI_CONTEXT_COPY(a0, a1, a2, a3, a4, a5, a6, a7, a8);
#else
    return (int)bda_gui_context_copy((bda_handle_t)a0, (s32)a1, (s32)a2, (s32)a3, (s32)a4, (bda_handle_t)a5, (s32)a6, (s32)a7, (u32)a8);
#endif
}
static inline void * bda_sango_gui_current_font(unsigned int a0) {
#ifdef SANGO_BIND_GUI_CURRENT_FONT
    return (void *)SANGO_BIND_GUI_CURRENT_FONT(a0);
#else
    typedef void * (*entry_t)(unsigned int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x4a4u);
    return (void *)entry(a0);
#endif
}
static inline int bda_sango_gui_font_cell_width(unsigned int a0) {
#ifdef SANGO_BIND_GUI_FONT_CELL_WIDTH
    return (int)SANGO_BIND_GUI_FONT_CELL_WIDTH(a0);
#else
    typedef int (*entry_t)(unsigned int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x4d0u);
    return (int)entry(a0);
#endif
}
static inline int bda_sango_gui_font_cell_height(unsigned int a0) {
#ifdef SANGO_BIND_GUI_FONT_CELL_HEIGHT
    return (int)SANGO_BIND_GUI_FONT_CELL_HEIGHT(a0);
#else
    typedef int (*entry_t)(unsigned int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x4d4u);
    return (int)entry(a0);
#endif
}
static inline int bda_sango_gui_draw_text(unsigned int a0, int a1, int a2, const char * a3, int a4) {
#ifdef SANGO_BIND_GUI_DRAW_TEXT
    return (int)SANGO_BIND_GUI_DRAW_TEXT(a0, a1, a2, a3, a4);
#else
    return (int)bda_gui_draw_text((bda_handle_t)a0, (s32)a1, (s32)a2, (const char *)a3, (s32)a4);
#endif
}
static inline int bda_sango_gui_select_font(unsigned int a0, unsigned int a1) {
#ifdef SANGO_BIND_GUI_SELECT_FONT
    return (int)SANGO_BIND_GUI_SELECT_FONT(a0, a1);
#else
    typedef int (*entry_t)(unsigned int, unsigned int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x544u);
    return (int)entry(a0, a1);
#endif
}
static inline void bda_sango_gui_edit_finish(void) {
#ifdef SANGO_BIND_GUI_EDIT_FINISH
    (void)SANGO_BIND_GUI_EDIT_FINISH();
#else
    typedef void (*entry_t)(void);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x558u);
    (void)entry();
#endif
}
static inline int bda_sango_gui_bitmap_buffer(int a0, int a1, int a2, int a3, const void * a4, void * a5, unsigned int a6) {
#ifdef SANGO_BIND_GUI_BITMAP_BUFFER
    return (int)SANGO_BIND_GUI_BITMAP_BUFFER(a0, a1, a2, a3, a4, a5, a6);
#else
    typedef int (*entry_t)(int, int, int, int, const void *, void *, unsigned int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x578u);
    return (int)entry(a0, a1, a2, a3, a4, a5, a6);
#endif
}
static inline int bda_sango_gui_bitmap_context(unsigned int a0, int a1, int a2, int a3, int a4, const void * a5, unsigned int a6) {
#ifdef SANGO_BIND_GUI_BITMAP_CONTEXT
    return (int)SANGO_BIND_GUI_BITMAP_CONTEXT(a0, a1, a2, a3, a4, a5, a6);
#else
    typedef int (*entry_t)(unsigned int, int, int, int, int, const void *, unsigned int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x57cu);
    return (int)entry(a0, a1, a2, a3, a4, a5, a6);
#endif
}
static inline int bda_sango_gui_bitmap_crop(int a0, int a1, int a2, int a3, int a4, int a5, const void * a6, void * a7) {
#ifdef SANGO_BIND_GUI_BITMAP_CROP
    return (int)SANGO_BIND_GUI_BITMAP_CROP(a0, a1, a2, a3, a4, a5, a6, a7);
#else
    typedef int (*entry_t)(int, int, int, int, int, int, const void *, void *);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x584u);
    return (int)entry(a0, a1, a2, a3, a4, a5, a6, a7);
#endif
}
static inline int bda_sango_gui_draw_aux_rectangle(unsigned int a0, int a1, int a2, int a3, int a4) {
#ifdef SANGO_BIND_GUI_DRAW_AUX_RECTANGLE
    return (int)SANGO_BIND_GUI_DRAW_AUX_RECTANGLE(a0, a1, a2, a3, a4);
#else
    typedef int (*entry_t)(unsigned int, int, int, int, int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x5ccu);
    return (int)entry(a0, a1, a2, a3, a4);
#endif
}
static inline int bda_sango_gui_input_packet(void * a0) {
#ifdef SANGO_BIND_GUI_INPUT_PACKET
    return (int)SANGO_BIND_GUI_INPUT_PACKET(a0);
#else
    return (int)bda_gui_input_packet((bda_gui_input_packet_t *)a0);
#endif
}
static inline int bda_sango_gui_shell_open(unsigned int a0) {
#ifdef SANGO_BIND_GUI_SHELL_OPEN
    return (int)SANGO_BIND_GUI_SHELL_OPEN(a0);
#else
    typedef int (*entry_t)(unsigned int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x6a8u);
    return (int)entry(a0);
#endif
}
static inline int bda_sango_gui_window_aux_a(unsigned int a0, unsigned int a1, unsigned int a2) {
#ifdef SANGO_BIND_GUI_WINDOW_AUX_A
    return (int)SANGO_BIND_GUI_WINDOW_AUX_A(a0, a1, a2);
#else
    typedef int (*entry_t)(unsigned int, unsigned int, unsigned int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x7e0u);
    return (int)entry(a0, a1, a2);
#endif
}
static inline int bda_sango_gui_window_aux_b(unsigned int a0, unsigned int a1, unsigned int a2) {
#ifdef SANGO_BIND_GUI_WINDOW_AUX_B
    return (int)SANGO_BIND_GUI_WINDOW_AUX_B(a0, a1, a2);
#else
    typedef int (*entry_t)(unsigned int, unsigned int, unsigned int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_gui(), 0x7e4u);
    return (int)entry(a0, a1, a2);
#endif
}
static inline void * bda_sango_fs_fopen(const char * a0, const char * a1) {
#ifdef SANGO_BIND_FS_FOPEN
    return (void *)SANGO_BIND_FS_FOPEN(a0, a1);
#else
    return (void *)bda_fs_fopen_raw((const char *)a0, (const char *)a1);
#endif
}
static inline int bda_sango_fs_fclose(void * a0) {
#ifdef SANGO_BIND_FS_FCLOSE
    return (int)SANGO_BIND_FS_FCLOSE(a0);
#else
    return (int)bda_fs_close_raw((int)a0);
#endif
}
static inline unsigned int bda_sango_fs_fread(void * a0, unsigned int a1, unsigned int a2, void * a3) {
#ifdef SANGO_BIND_FS_FREAD
    return (unsigned int)SANGO_BIND_FS_FREAD(a0, a1, a2, a3);
#else
    return (unsigned int)bda_fs_fread_raw((void *)a0, (bda_size_t)a1, (bda_size_t)a2, (int)a3);
#endif
}
static inline unsigned int bda_sango_fs_fwrite(const void * a0, unsigned int a1, unsigned int a2, void * a3) {
#ifdef SANGO_BIND_FS_FWRITE
    return (unsigned int)SANGO_BIND_FS_FWRITE(a0, a1, a2, a3);
#else
    return (unsigned int)bda_fs_fwrite_raw((const void *)a0, (bda_size_t)a1, (bda_size_t)a2, (int)a3);
#endif
}
static inline int bda_sango_fs_fseek(void * a0, int a1, int a2) {
#ifdef SANGO_BIND_FS_FSEEK
    return (int)SANGO_BIND_FS_FSEEK(a0, a1, a2);
#else
    return (int)bda_fs_seek_raw((int)a0, (s32)a1, (int)a2);
#endif
}
static inline int bda_sango_fs_ftell(void * a0) {
#ifdef SANGO_BIND_FS_FTELL
    return (int)SANGO_BIND_FS_FTELL(a0);
#else
    return (int)bda_fs_tell_raw((int)a0);
#endif
}
static inline int bda_sango_fs_feof(void * a0) {
#ifdef SANGO_BIND_FS_FEOF
    return (int)SANGO_BIND_FS_FEOF(a0);
#else
    typedef int (*entry_t)(void *);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_fs(), 0x018u);
    return (int)entry(a0);
#endif
}
static inline int bda_sango_fs_ferror(void * a0) {
#ifdef SANGO_BIND_FS_FERROR
    return (int)SANGO_BIND_FS_FERROR(a0);
#else
    return (int)bda_fs_error((int)a0);
#endif
}
static inline void bda_sango_fs_clearerr(void * a0) {
#ifdef SANGO_BIND_FS_CLEARERR
    (void)SANGO_BIND_FS_CLEARERR(a0);
#else
    typedef void (*entry_t)(void *);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_fs(), 0x020u);
    (void)entry(a0);
#endif
}
static inline int bda_sango_fs_rename(const char * a0, const char * a1) {
#ifdef SANGO_BIND_FS_RENAME
    return (int)SANGO_BIND_FS_RENAME(a0, a1);
#else
    return (int)bda_fs_rename((const char *)a0, (const char *)a1);
#endif
}
static inline int bda_sango_fs_mkdir(const char * a0) {
#ifdef SANGO_BIND_FS_MKDIR
    return (int)SANGO_BIND_FS_MKDIR(a0);
#else
    return (int)bda_fs_mkdir((const char *)a0);
#endif
}
static inline unsigned int bda_sango_fs_read_at(void * a0, unsigned int a1, unsigned int a2, void * a3) {
#ifdef SANGO_BIND_FS_READ_AT
    return (unsigned int)SANGO_BIND_FS_READ_AT(a0, a1, a2, a3);
#else
    typedef unsigned int (*entry_t)(void *, unsigned int, unsigned int, void *);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_fs(), 0x068u);
    return (unsigned int)entry(a0, a1, a2, a3);
#endif
}
static inline int bda_sango_fs_access(const char * a0, int a1) {
#ifdef SANGO_BIND_FS_ACCESS
    return (int)SANGO_BIND_FS_ACCESS(a0, a1);
#else
    typedef int (*entry_t)(const char *, int);
    entry_t entry = (entry_t)bda_sdk_internal_api(bda_sdk_internal_fs(), 0x06cu);
    return (int)entry(a0, a1);
#endif
}
static inline void * bda_sango_mem_alloc(unsigned int a0) {
#ifdef SANGO_BIND_MEM_ALLOC
    return (void *)SANGO_BIND_MEM_ALLOC(a0);
#else
    return (void *)bda_alloc((bda_size_t)a0);
#endif
}
static inline void bda_sango_mem_free(void * a0) {
#ifdef SANGO_BIND_MEM_FREE
    (void)SANGO_BIND_MEM_FREE(a0);
#else
    (void)bda_free((void *)a0);
#endif
}
#endif

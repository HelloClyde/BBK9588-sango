#include "sango_internal.h"

/* 应用窗口、计时、内存、文件和消息框适配。 */

/* 原函数 0x81c0a330 */
int sango_create_app_frame(void)
{
    unsigned char abi_storage[68] __attribute__((aligned(8)));
#define frame_internal28 (*(uint32_t *)(abi_storage + 4))
#define frame_title (*(char **)(abi_storage + 8))
#define frame_internal44 (*(uint32_t *)(abi_storage + 12))
#define frame_internal48 (*(uint32_t *)(abi_storage + 16))
#define frame_helper_arg14 (*(uint32_t *)(abi_storage + 20))
#define frame_callback (*(SangoLegacyCode **)(abi_storage + 24))
#define frame_x (*(uint32_t *)(abi_storage + 28))
#define frame_y (*(uint32_t *)(abi_storage + 32))
#define frame_native_height (*(uint32_t *)(abi_storage + 36))
#define frame_native_width (*(uint32_t *)(abi_storage + 40))
#define frame_surface (*(void **)(abi_storage + 44))
#define frame_aux30 (*(uint32_t *)(abi_storage + 48))
#define frame_style (*(uint32_t *)(abi_storage + 0))

    int register_result;
    int creation_result;

    g_frame_buffer = bda_sango_mem_alloc(0x4b20);
    creation_result = -1;
    if (g_frame_buffer != 0)
    {
        crt_memset(g_frame_buffer, 0xff, 0x4b00);
        frame_style = 0x8000000;
        frame_title = g_legacy_data_81c20210;
        frame_callback = sango_window_proc;
        frame_native_height = 0xf0;
        frame_native_width = 0x140;
        frame_internal28 = 0;
        frame_internal44 = 0;
        frame_internal48 = 0;
        frame_x = 0;
        frame_y = 0;
        frame_surface = bda_sango_gui_draw_object(0xf);
        frame_aux30 = 0;
        frame_helper_arg14 = 0;
        register_result = bda_sango_gui_register_frame(&frame_style);
        creation_result = -1;
        if (register_result != -1)
        {
            sango_display_set_brush(0, 0);
            sango_display_set_text_color(3, 0);
            bda_sango_gui_set_text_mode(g_draw_context, 0);
            g_legacy_data_81c2b20c = 0;
            creation_result = 0;
        }
    }
    return creation_result;
}
#undef frame_internal28
#undef frame_title
#undef frame_internal44
#undef frame_internal48
#undef frame_helper_arg14
#undef frame_callback
#undef frame_x
#undef frame_y
#undef frame_native_height
#undef frame_native_width
#undef frame_surface
#undef frame_aux30
#undef frame_style

/* 原函数 0x81c0a44c */
uint32_t sango_platform_allocate_zeroed_buffer(void)
{
    bool allocated;

    g_frame_buffer = bda_sango_mem_alloc(0x4b20);
    allocated = g_frame_buffer != 0;
    if (allocated)
    {
        crt_memset(g_frame_buffer, 0xff, 0x4b00);
    }
    return (uint32_t)allocated;
}

/* 原函数 0x81c0a4a4 */
int sango_run_event_loop_and_close(void)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define native_event (*(uint8_t(*)[32])(abi_storage + 0))

    int event_available;

    bda_sango_gui_post_message(g_app_frame, 0x66, 0, 0);
    while (true)
    {
        event_available = bda_sango_gui_event_poll(native_event, 0);
        if (event_available == 0)
            break;
        bda_sango_gui_event_step(native_event);
        bda_sango_gui_event_dispatch(native_event);
    }
    bda_sango_gui_close_frame(g_app_frame);
    if (g_frame_buffer != 0)
    {
        bda_sango_mem_free((void *)g_frame_buffer);
    }
    return 1;
}
#undef native_event

/* 原函数 0x81c0a578 */
void sango_platform_init_window_descriptor(uint32_t *descriptor)
{
    void *background_object;

    *descriptor = 0x8000000;
    descriptor[2] = g_legacy_data_81c20210;
    descriptor[6] = sango_window_proc;
    descriptor[9] = 0xf0;
    descriptor[10] = 0x140;
    descriptor[1] = 0;
    descriptor[3] = 0;
    descriptor[4] = 0;
    descriptor[7] = 0;
    descriptor[8] = 0;
    background_object = bda_sango_gui_draw_object(0xf);
    descriptor[0xb] = background_object;
    descriptor[5] = 0;
    descriptor[0xc] = 0;
    return;
}

/* 原函数 0x81c0a5fc */
uint32_t sango_input_poll_native_event(uint32_t *event_result)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define native_event (*(uint8_t(*)[32])(abi_storage + 0))

    int event_available;

    event_available = bda_sango_gui_event_poll(native_event, 0);
    if (event_available != 0)
    {
        bda_sango_gui_event_step(native_event);
        bda_sango_gui_event_dispatch(native_event);
        *event_result = g_native_event_kind_view2;
        event_result[1] = g_native_event_key;
        event_result[2] = g_native_event_data;
        g_native_event_kind_view2 = 0;
    }
    return (uint32_t)(event_available != 0);
}
#undef native_event

/* 原函数 0x81c0a6a0 */
int bbk_post_message(uint32_t message, uint32_t wparam, uint32_t lparam)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define stored_message (*(uint32_t *)(abi_storage + 4))
#define stored_wparam (*(uint32_t *)(abi_storage + 8))
#define stored_lparam (*(uint32_t *)(abi_storage + 12))
#define message_storage (*(uint8_t(*)[4])(abi_storage + 0))

    crt_memset(message_storage, 0, 0x1c);
    stored_message = message;
    stored_wparam = wparam;
    stored_lparam = lparam;
    bda_sango_gui_post_message(g_app_frame, message, wparam, lparam);
    return 1;
}
#undef stored_message
#undef stored_wparam
#undef stored_lparam
#undef message_storage

/* 原函数 0x81c0a704 */
void *bbk_alloc(uint32_t size)
{
    void *allocation;

    allocation = bda_sango_mem_alloc(size);
    return allocation;
}

/* 原函数 0x81c0a72c */
void bbk_free_if_nonnull(void *ptr)
{
    if (ptr != 0)
    {
        bda_sango_mem_free(ptr);
    }
    return;
}

/* 原函数 0x81c0a774 */
char *bbk_strcat(char *destination, char *source)
{
    char *concatenated_text;

    concatenated_text = sango_crt_strcat(destination, source);
    return concatenated_text;
}

/* 原函数 0x81c0a790 */
uint32_t bbk_strlen(char *text)
{
    uint32_t length;

    length = sango_crt_strlen(text);
    return length;
}

/* 原函数 0x81c0a7ac */
void *bbk_memcpy(void *dst, void *src, uint32_t size)
{
    void *copied_destination;

    copied_destination = crt_memcpy(dst, src, size);
    return copied_destination;
}

/* 原函数 0x81c0a7c8 */
void sango_memory_fill(void *destination, int value, uint32_t bytes)
{
    crt_memset(destination, value, bytes);
    return;
}

/* 原函数 0x81c0a7e4 */
uint8_t *sango_format_integer(int value, uint8_t *destination, int radix)
{
    int supported_radix;
    uint8_t *format_text;

    format_text = &g_legacy_data_81c20254;
    if (radix != 10)
    {
        if (radix < 0xb)
        {
            format_text = &g_legacy_data_81c20258;
            supported_radix = 8;
        }
        else
        {
            format_text = (uint8_t *)0x81c2025c;
            supported_radix = 0x10;
        }
        if (radix != supported_radix)
        {
            return format_text;
        }
    }
    sango_crt_format_entry(destination, format_text, value, radix);
    return format_text;
}

/* 原函数 0x81c0a86c */
void bbk_zero_time_stub(uint16_t *time_fields)
{
    time_fields[7] = 0;
    *time_fields = 0;
    time_fields[1] = 0;
    time_fields[2] = 0;
    time_fields[5] = 0;
    time_fields[3] = 0;
    time_fields[6] = 0;
    time_fields[4] = 0;
    return;
}

/* 原函数 0x81c0a890 */
void bbk_srand(uint32_t seed)
{
    crt_srand(seed);
    return;
}

/* 原函数 0x81c0a8ac */
uint32_t bbk_rand(void)
{
    uint32_t random_value;

    random_value = crt_rand();
    return random_value;
}

/* 原函数 0x81c0a8c8 */
uint32_t sango_timer_start(uint32_t timer_id, uint32_t interval)
{
    bda_sango_gui_timer_start(g_app_frame, timer_id, interval);
    return 1;
}

/* 原函数 0x81c0a904 */
uint32_t sango_timer_stop(uint32_t timer_id)
{
    bda_sango_gui_timer_stop(g_app_frame, timer_id);
    return 1;
}

/* 原函数 0x81c0a938 */
void *bbk_compatible_context_create(void)
{
    void *context;

    context = bda_sango_gui_compatible_create(g_draw_context);
    return context;
}

/* 原函数 0x81c0a964 */
int bbk_compatible_context_free(void *context)
{
    bda_sango_gui_compatible_free(context);
    return 1;
}

/* 原函数 0x81c0a990 */
void sango_display_present_context(uint32_t destination_context, uint32_t source_context)
{

    if (destination_context == 0)
    {
        if (source_context != 0)
        {
            bda_sango_gui_draw_guard(1);
            bda_sango_gui_context_copy(source_context, 0, 0, 0xf0, 0x140, g_draw_context, 0, 0,
                                       0xf81f);
            bda_sango_gui_request_redraw(g_app_frame, 0, 0);
            bda_sango_gui_draw_guard(0);
        }
    }
    else
    {
        if (source_context == 0)
        {
            source_context = g_draw_context;
        }
        else
        {
        }
        bda_sango_gui_context_copy(source_context, 0, 0, 0xf0, 0x140, destination_context, 0, 0,
                                   0xf81f);
    }
    return;
}

/* 原函数 0x81c0aadc */
void sango_display_noop(void)
{
    return;
}

/* 原函数 0x81c0aae4 */
void sango_display_invert_rectangle(short left, short top, short right, short bottom,
                                    uint32_t context)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(uint32_t *)(abi_storage + 0)) = context;
#define context (*(uint32_t *)(abi_storage + 0))

    int origin_y;
    int origin_x;

    origin_x = (int)left;
    origin_y = (int)top;
    if (context == 0)
    {
        bda_sango_gui_draw_guard(1);
        bda_sango_gui_draw_aux_rectangle(g_draw_context, origin_x, origin_y, right - origin_x,
                                         bottom - origin_y);
        bda_sango_gui_draw_guard(0);
    }
    else
    {
        bda_sango_gui_draw_aux_rectangle(context, origin_x, origin_y, right - origin_x,
                                         bottom - origin_y);
    }
    return;
}
#undef context

/* 原函数 0x81c0abcc */
int sango_platform_noop(uint8_t *little_endian_bytes)
{
    return (((uint32_t)little_endian_bytes[3] * 0x100 + (uint32_t)little_endian_bytes[2]) * 0x100 +
            (uint32_t)little_endian_bytes[1]) *
               0x100 +
           (uint32_t)*little_endian_bytes;
}

/* 原函数 0x81c0ac00 */
uint32_t sango_bitmap_query_dimensions(uint16_t *bitmap, uint32_t unused_a1, uint32_t unused_a2,
                                       uint32_t *width, uint32_t *height)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(uint32_t **)(abi_storage + 0)) = height;
#define height (*(uint32_t **)(abi_storage + 0))

    uint32_t queried;

    queried = 0;
    if (((bitmap != (uint16_t *)0x0) && (width != (uint32_t *)0x0)) && (height != (uint32_t *)0x0))
    {
        queried = 1;
        *width = (uint32_t)*bitmap;
        *height = (uint32_t)bitmap[1];
    }
    return queried;
}
#undef height

/* 原函数 0x81c0ac48 */
void sango_display_fill_gray_rectangle(short left, short top, short right, short bottom,
                                       uint32_t gray, uint32_t context)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
    (*(uint32_t *)(abi_storage + 0)) = gray;
    (*(uint32_t *)(abi_storage + 4)) = context;
#define gray (*(uint32_t *)(abi_storage + 0))
#define context (*(uint32_t *)(abi_storage + 4))

    sango_display_fill_rectangle(left, top, right, bottom, gray, context);
    return;
}
#undef gray
#undef context

/* 原函数 0x81c0ad1c */
void sango_text_get_font_metrics(uint16_t *cell_dimensions, uint32_t font_id)
{
    int cell_size;

    bda_sango_gui_current_font(font_id);
    bda_sango_gui_select_font(g_draw_context, font_id & 0xff);
    cell_size = bda_sango_gui_font_cell_width(g_draw_context);
    cell_dimensions[1] = (short)cell_size;
    cell_size = bda_sango_gui_font_cell_height(g_draw_context);
    *cell_dimensions = (short)cell_size;
    bda_sango_gui_select_font(g_draw_context, (uint32_t)g_legacy_data_81c2b210);
    return;
}

/* 原函数 0x81c0addc */
void sango_text_draw_native(short x, short y, char *text, uint32_t context)
{
    if (context == 0)
    {
        bda_sango_gui_draw_guard(1);
        bda_sango_gui_draw_text(g_draw_context, (int)x, (int)y, text, -1);
        bda_sango_gui_draw_guard(0);
    }
    else
    {
        bda_sango_gui_draw_text(context, (int)x, (int)y, text, -1);
    }
    return;
}

/* 原函数 0x81c0aeb0 */
void bbk_clearerr(void *file)
{
    bda_sango_fs_clearerr(file);
    return;
}

/* 原函数 0x81c0aed8 */
int bbk_ferror(void *file)
{
    int result;

    result = bda_sango_fs_ferror(file);
    return result;
}

/* 原函数 0x81c0af00 */
int bbk_fclose(void *file)
{
    int result;

    result = bda_sango_fs_fclose(file);
    return result;
}

/* 原函数 0x81c0af28 */
int bbk_feof(void *file)
{
    int result;

    result = bda_sango_fs_feof(file);
    return result;
}

/* 原函数 0x81c0af50 */
uint32_t sango_platform_stub_0af50(void)
{
    return 0;
}

/* 原函数 0x81c0af58 */
uint32_t sango_platform_stub_0af58(void)
{
    return 0;
}

/* 原函数 0x81c0af60 */
void *bbk_fopen(char *path, char *mode)
{
    void *file_handle;

    file_handle = bda_sango_fs_fopen(path, mode);
    return file_handle;
}

/* 原函数 0x81c0af88 */
uint32_t sango_platform_stub_0af88(void)
{
    return 0;
}

/* 原函数 0x81c0af90 */
uint32_t sango_platform_stub_0af90(void)
{
    return 0;
}

/* 原函数 0x81c0af98 */
uint32_t bbk_fread(void *buffer, uint32_t size, uint32_t count, void *file)
{
    if ((size != 0) && (count != 0))
    {
        count = bda_sango_fs_fread(buffer, size, count, file);
    }
    return count;
}

/* 原函数 0x81c0afdc */
int bbk_fseek(void *file, int offset, int whence)
{
    int result;

    result = bda_sango_fs_fseek(file, offset, whence);
    return result;
}

/* 原函数 0x81c0b004 */
int bbk_ftell(void *file)
{
    int result;

    result = bda_sango_fs_ftell(file);
    return result;
}

/* 原函数 0x81c0b02c */
uint32_t bbk_fwrite(void *buffer, uint32_t element_size, uint32_t element_count, void *file)
{
    if ((element_size != 0) && (element_count != 0))
    {
        element_count = bda_sango_fs_fwrite(buffer, element_size, element_count, file);
    }
    return element_count;
}

/* 原函数 0x81c0b070 */
uint32_t sango_platform_stub_0b070(void)
{
    return 0;
}

/* 原函数 0x81c0b078 */
uint32_t sango_platform_stub_0b078(void)
{
    return 0;
}

/* 原函数 0x81c0b080 */
uint32_t sango_platform_stub_0b080(void)
{
    return 0;
}

/* 原函数 0x81c0b088 */
uint32_t sango_platform_stub_0b088(void)
{
    return 0;
}

/* 原函数 0x81c0b090 */
uint32_t sango_platform_stub_0b090(void)
{
    return 0;
}

/* 原函数 0x81c0b098 */
int bbk_rename(char *old_path, char *new_path)
{
    int result;

    result = bda_sango_fs_rename(old_path, new_path);
    return result;
}

/* 原函数 0x81c0b0c0 */
void sango_platform_stub_0b0c0(void)
{
    return;
}

/* 原函数 0x81c0b0c8 */
void *bbk_load_file_with_progress(char *path)
{
    short progress_x;
    uint32_t chunk_bytes;
    void *file_handle;
    int file_bytes;
    void *allocated_buffer;
    void *loaded_buffer;
    uint32_t offset_or_progress_color;
    uint32_t percent_loaded;

    file_handle = bda_sango_fs_fopen(path, (char *)0x81c20260);
    loaded_buffer = (void *)0x0;
    if (file_handle != 0)
    {
        bda_sango_fs_fseek(file_handle, 0, 2);
        file_bytes = bda_sango_fs_ftell(file_handle);
        chunk_bytes = file_bytes / 100;
        allocated_buffer = bda_sango_mem_alloc(file_bytes + 1);
        loaded_buffer = (void *)0x0;
        if (allocated_buffer != 0)
        {
            percent_loaded = 0;
            bda_sango_fs_fseek(file_handle, 0, 0);
            sango_display_fill_rectangle(0x12, 0x118, 0xde, 0x124, 0, 0);
            offset_or_progress_color = 0;
            do
            {
                bda_sango_fs_read_at((void *)((int)allocated_buffer + offset_or_progress_color),
                                     offset_or_progress_color, chunk_bytes, file_handle);
                offset_or_progress_color = bda_sango_gui_rgb(g_draw_context, 0x1f, 0x78, 0xa5);
                progress_x = (short)percent_loaded * 2;
                sango_display_fill_rectangle(progress_x + 0x14, 0x11a, progress_x + 0x16, 0x122,
                                             offset_or_progress_color, 0);
                percent_loaded = percent_loaded + 1 & 0xff;
                offset_or_progress_color = percent_loaded * chunk_bytes;
            } while (percent_loaded < 100);
            bda_sango_fs_fread((void *)((int)allocated_buffer + chunk_bytes * 100),
                               file_bytes % 100, 1, file_handle);
            bda_sango_fs_fclose(file_handle);
            loaded_buffer = allocated_buffer;
        }
    }
    return loaded_buffer;
}

/* 原函数 0x81c0b2c4 */
uint32_t sango_platform_stub_0b2c4(void)
{
    return 1;
}

/* 原函数 0x81c0b2cc */
uint32_t sango_platform_stub_0b2cc(void)
{
    return 1;
}

/* 原函数 0x81c0b2d4 */
uint32_t sango_platform_stub_0b2d4(void)
{
    return 1;
}

/* 原函数 0x81c0b404 */
void sango_input_dispatch_pending_events(uint32_t duration)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define native_event (*(uint8_t(*)[32])(abi_storage + 0))

    bool keep_polling;
    int event_available_or_kind;
    uint32_t timer_events;

    timer_events = 0;
    keep_polling = true;
    do
    {
        event_available_or_kind = bda_sango_gui_event_poll(native_event, 0);
        if (event_available_or_kind != 0)
        {
            bda_sango_gui_event_step(native_event);
            bda_sango_gui_event_dispatch(native_event);
            event_available_or_kind = g_native_event_kind;
            g_native_event_kind = 0;
            if (event_available_or_kind == 0x144)
            {
                timer_events = timer_events + 1;
            }
            if (event_available_or_kind == 0x10)
            {
                keep_polling = false;
            }
            if (duration / 0x2a <= timer_events)
            {
                keep_polling = false;
            }
        }
    } while (keep_polling);
    return;
}
#undef native_event

/* 原函数 0x81c0b500 */
int graphics_init_stub(void)
{
    return 1;
}

/* 原函数 0x81c0b508 */
uint32_t sango_platform_stub_0b508(void)
{
    return 1;
}

/* 原函数 0x81c0b510 */
int bbk_message_box(char *message, char *title, uint32_t flags)
{
    void *saved_screen_context;
    int dialog_result;

    saved_screen_context = bda_sango_gui_compatible_create(g_draw_context);
    dialog_result = -1;
    if (saved_screen_context != 0)
    {
        bda_sango_gui_context_copy(g_draw_context, 0, 0, 0xf0, 0x140,
                                   (uint32_t)saved_screen_context, 0, 0, 0xf81f);
        dialog_result = bda_sango_gui_message_box(0, message, title, flags);
        bda_sango_gui_draw_guard(1);
        bda_sango_gui_context_copy((uint32_t)saved_screen_context, 0, 0, 0xf0, 0x140,
                                   g_draw_context, 0, 0, 0xf81f);
        bda_sango_gui_request_redraw(g_app_frame, 0, 0);
        bda_sango_gui_draw_guard(0);
        bda_sango_gui_compatible_free(saved_screen_context);
    }
    return dialog_result;
}

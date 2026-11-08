#include "sango_internal.h"

/* 按键数据与文本输入对话框。 */

/* 原函数 0x81c097f4 */
uint16_t *sango_bitmap_open_embedded_entry(uint32_t *entry_state, uint32_t access_mode,
                                           int entry_index, int container_address)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define entry_offset (*(int(*)[2])(abi_storage + 0))

    uint16_t width;
    uint16_t height;
    uint16_t *bitmap;

    if (2 < access_mode)
    {
        return (uint16_t *)0x0;
    }
    crt_memcpy(entry_offset, (void *)(container_address + entry_index * 4), 4);
    bitmap = (uint16_t *)(container_address + entry_offset[0]);
    if (access_mode == 1)
    {
        *entry_state = bitmap;
    }
    else
    {
        if (access_mode != 0)
        {
            if (access_mode == 2)
            {
                width = *bitmap;
                height = bitmap[1];
                entry_state[1] = bitmap;
                *entry_state =
                    (uint16_t *)(((int)(width + 3) >> 2) * (uint32_t)height + (int)bitmap);
            }
            goto store_access_mode;
        }
        *entry_state = 0;
    }
    entry_state[1] = 0;
store_access_mode:
    entry_state[2] = access_mode;
    return bitmap;
}
#undef entry_offset

/* 原函数 0x81c098b4 */
uint32_t sango_input_key_is_down(uint32_t key_code)
{
    unsigned char abi_storage[22] __attribute__((aligned(8)));
#define key_packet (*(char(*)[6])(abi_storage + 0))
    crt_memset(key_packet, 0, 6);
    bda_sango_gui_input_packet(key_packet);
    /* SDK的六字节状态顺序：右、左、下、上、返回、确定。 */
    switch (key_code)
    {
    case 0x67:
        return (uint32_t)(key_packet[3] == '\x01');
    case 0x69:
        return (uint32_t)(key_packet[1] == '\x01');
    case 0x6a:
        return (uint32_t)(key_packet[0] == '\x01');
    case 0x6c:
        return (uint32_t)(key_packet[2] == '\x01');
    case 1:
        return (uint32_t)(key_packet[4] == '\x01');
    case 0x1c:
        return (uint32_t)(key_packet[5] == '\x01');
    default:
        return 0;
    }
}
#undef key_packet

/* 原函数 0x81c09990 */
void sango_raster_invert_packed_rectangle(short x1, short y1, short x2, short y2, int pixel_address)
{
    unsigned char abi_storage[52] __attribute__((aligned(8)));
    (*(int *)(abi_storage + 32)) = pixel_address;
#define pixel_address (*(int *)(abi_storage + 32))
#define left_edge_masks (*(uint32_t(*)[2])(abi_storage + 0))
#define right_edge_masks (*(uint32_t(*)[2])(abi_storage + 8))

    int left = (int)x1;
    int top = (int)y1;
    int right = (int)x2;
    int bottom = (int)y2;
    left_edge_masks[0] = g_legacy_data_81c20244;
    right_edge_masks[0] = g_legacy_data_81c20248;
    if (left >= 240 || top >= 320 || right < 0 || bottom < 0)
        return;
    if (left < 0)
        left = 0;
    if (top < 0)
        top = 0;
    if (right > 239)
        right = 239;
    if (bottom > 319)
        bottom = 319;

    /* 2bpp帧缓冲每行60字节。首尾字节按掩码取反，中间字节整体取反。 */
    int rounded_right = right + 3;
    if (-1 < right)
        rounded_right = right;
    int rounded_left = left + 3;
    if (-1 < left)
        rounded_left = left;
    int left_remainder = (left + (rounded_left >> 2) * -4) * 0x10000 >> 0x10;
    int right_remainder = (right + (rounded_right >> 2) * -4) * 0x10000 >> 0x10;
    int horizontal_span = (right - right_remainder) + (left_remainder - left);
    int row_bytes = horizontal_span + 4;
    if (row_bytes < 0)
        row_bytes = horizontal_span + 7;
    row_bytes = row_bytes >> 2;

    int row_index = 0;
    if (-1 < bottom - top)
    {
        int first_row_address = pixel_address + (int)(short)(rounded_left >> 2) + top * 60;
        int row_word_offset = 0;
        int row_byte_offset = 0;
        do
        {
            uint8_t pixel_byte = *(uint8_t *)(row_byte_offset + first_row_address);
            uint8_t edge_mask = *(uint8_t *)((int)left_edge_masks + left_remainder);
            int last_byte_address = row_byte_offset + first_row_address + row_bytes - 1;
            *(uint8_t *)(row_byte_offset + first_row_address) =
                ~pixel_byte & edge_mask | pixel_byte & ~edge_mask;
            pixel_byte = *(uint8_t *)last_byte_address;
            edge_mask = *(uint8_t *)((int)right_edge_masks + right_remainder);
            *(uint8_t *)last_byte_address = ~pixel_byte & edge_mask | pixel_byte & ~edge_mask;
            /* 首尾可能是同一字节，保留原先两次掩码操作的顺序。 */
            if ((2 < row_bytes) && (0 < row_bytes - 2))
            {
                uint8_t *interior_cursor = (uint8_t *)(row_word_offset * 4 + first_row_address);
                int interior_bytes = row_bytes - 2;
                do
                {
                    interior_cursor = interior_cursor + 1;
                    interior_bytes = interior_bytes - 1;
                    *interior_cursor = ~*interior_cursor;
                } while (interior_bytes != 0);
            }
            row_index = row_index + 1;
            row_byte_offset = row_byte_offset + 60;
            row_word_offset = row_word_offset + 15;
        } while (row_index <= bottom - top);
    }
}
#undef pixel_address
#undef left_edge_masks
#undef right_edge_masks

/* 原函数 0x81c09b6c */
uint32_t sango_text_input_proc(uint32_t handle, int message, uint32_t wparam, uint32_t lparam)
{
    uint32_t message_result;

    if (message == 0x66)
    {
        bda_sango_gui_edit_finish();
        bda_sango_gui_control_destroy(g_platform_state_104);
        bda_sango_gui_frame_stop(handle);
        bda_sango_gui_frame_release(handle);
        message_result = 0;
    }
    else
    {
        if (message < 0x67)
        {
            if (message == 0x12)
            {
                if ((wparam & 0xffff) == 0x1c)
                {
                    bda_sango_gui_send_message(g_platform_state_104, 0x133, g_text_input_frame,
                                               g_legacy_data_81c2b10c);
                    bda_sango_gui_post_message(handle, 0x66, 0, 0);
                    g_platform_state_108 = 0;
                }
                else if ((wparam & 0xffff) == 1)
                {
                    bda_sango_gui_post_message(handle, 0x66, 0, 0);
                }
            }
            else if (message == 0x60)
            {
                g_platform_state_108 = 1;
                g_platform_state_104 = bda_sango_gui_control_create(
                    (char *)0x81c2024c, (char *)0x0, 0x48410000, 0, 0, 6, 8, 0x78, 0x18, handle, 0);
                bda_sango_gui_send_message(g_platform_state_104, 0xf0c5, g_text_input_frame,
                                           g_legacy_data_81c2b10c);
                bda_sango_gui_set_active(g_platform_state_104);
            }
        }
        message_result = bda_sango_gui_default_proc(handle, message, wparam, lparam);
    }
    return message_result;
}

/* 原函数 0x81c09d90 */
uint32_t sango_text_input_dialog(uint32_t title_address, uint8_t *output_text,
                                 uint32_t edit_argument)
{
    unsigned char abi_storage[104] __attribute__((aligned(8)));
#define frame_proc (*(SangoLegacyCode **)(abi_storage + 24))
#define frame_x (*(uint32_t *)(abi_storage + 28))
#define frame_y (*(uint32_t *)(abi_storage + 32))
#define frame_height (*(uint32_t *)(abi_storage + 36))
#define frame_width (*(uint32_t *)(abi_storage + 40))
#define frame_surface (*(void **)(abi_storage + 44))
#define frame_aux30 (*(uint32_t *)(abi_storage + 48))
#define event_packet (*(uint8_t(*)[32])(abi_storage + 56))
#define frame_style (*(uint32_t *)(abi_storage + 0))
#define frame_internal28 (*(uint32_t *)(abi_storage + 4))
#define frame_title (*(uint32_t *)(abi_storage + 8))
#define frame_internal44 (*(uint32_t *)(abi_storage + 12))
#define frame_internal48 (*(uint32_t *)(abi_storage + 16))
#define frame_helper_arg14 (*(uint32_t *)(abi_storage + 20))

    int event_or_display_metric;
    uint32_t frame_handle;
    uint32_t dialog_result;

    *output_text = 0;
    frame_style = 0x28400000;
    frame_proc = sango_text_input_proc;
    frame_x = 0x5a;
    frame_height = 0xe6;
    frame_y = 0x50;
    frame_width = 0x8c;
    frame_internal28 = 0;
    frame_internal44 = 0;
    frame_internal48 = 0;
    g_text_input_frame = edit_argument;
    g_legacy_data_81c2b10c_view2 = output_text;
    frame_title = title_address;
    frame_surface = bda_sango_gui_draw_object(8);
    frame_aux30 = 0;
    frame_helper_arg14 = 0;
    event_or_display_metric = bda_sango_gui_display_metric(0, 6);
    g_input_dialog_backing = bda_sango_mem_alloc(event_or_display_metric * 0x3200 + 10);
    if (g_input_dialog_backing != 0)
    {
        bda_sango_gui_capture_region(0, 200, 0x140, 0x28, g_input_dialog_backing);
    }
    frame_handle = bda_sango_gui_register_frame(&frame_style);
    if (frame_handle == 0xffffffff)
    {
        bda_sango_mem_free(g_input_dialog_backing);
        dialog_result = 1;
    }
    else
    {
        while (event_or_display_metric = bda_sango_gui_event_poll(event_packet, 0),
               event_or_display_metric != 0)
        {
            bda_sango_gui_event_step(event_packet);
            bda_sango_gui_event_dispatch(event_packet);
        }
        bda_sango_gui_close_frame(frame_handle);
        dialog_result = g_platform_state_108;
        if (g_input_dialog_backing != 0)
        {
            bda_sango_gui_restore_region(0, 200, 0xf0, 0x28, g_input_dialog_backing);
            bda_sango_mem_free(g_input_dialog_backing);
            dialog_result = g_platform_state_108;
        }
    }
    return dialog_result;
}
#undef frame_proc
#undef frame_x
#undef frame_y
#undef frame_height
#undef frame_width
#undef frame_surface
#undef frame_aux30
#undef event_packet
#undef frame_style
#undef frame_internal28
#undef frame_title
#undef frame_internal44
#undef frame_internal48
#undef frame_helper_arg14

/* 原函数 0x81c09fb0 */
void sango_display_render_bitmap_region(short x, short y, int entry_index, uint32_t draw_context,
                                        int transparency_mode, int container_address)
{
    unsigned char abi_storage[120] __attribute__((aligned(8)));
    (*(int *)(abi_storage + 96)) = transparency_mode;
    (*(int *)(abi_storage + 100)) = container_address;
#define transparency_mode (*(int *)(abi_storage + 96))
#define container_address (*(int *)(abi_storage + 100))
#define entry_state (*(int(*)[4])(abi_storage + 0))
#define descriptor_flags (*(uint32_t *)(abi_storage + 16))
#define bitmap_width (*(int *)(abi_storage + 20))
#define bitmap_height (*(int *)(abi_storage + 24))
#define descriptor_aux (*(uint32_t *)(abi_storage + 28))
#define pixel_format (*(uint8_t *)(abi_storage + 32))
#define pixel_bits (*(uint8_t *)(abi_storage + 33))
#define pixel_address (*(int *)(abi_storage + 36))
#define transparent_color (*(int *)(abi_storage + 40))
#define height_byte0 (*(uint8_t *)(abi_storage + 48))
#define height_byte1 (*(uint8_t *)(abi_storage + 49))
#define height_byte2 (*(uint8_t *)(abi_storage + 50))
#define height_byte3 (*(uint8_t *)(abi_storage + 51))

    uint32_t active_draw_context;
    int screen_x;
    int screen_y;

    screen_y = (int)y;
    screen_x = (int)x;
    sango_bitmap_open_embedded_entry(entry_state, 1, entry_index, container_address);
    descriptor_flags = 0;
    bitmap_width = (((uint32_t) * (uint8_t *)(entry_state[0] + 7) * 0x100 +
                     (uint32_t) * (uint8_t *)(entry_state[0] + 6)) *
                        0x100 +
                    (uint32_t) * (uint8_t *)(entry_state[0] + 5)) *
                       0x100 +
                   (uint32_t) * (uint8_t *)(entry_state[0] + 4);
    height_byte0 = *(uint8_t *)(entry_state[0] + 8);
    height_byte1 = *(uint8_t *)(entry_state[0] + 9);
    height_byte2 = *(uint8_t *)(entry_state[0] + 10);
    height_byte3 = *(uint8_t *)(entry_state[0] + 0xb);
    descriptor_aux = 0;
    bitmap_height = (((uint32_t)height_byte3 * 0x100 + (uint32_t)height_byte2) * 0x100 +
                     (uint32_t)height_byte1) *
                        0x100 +
                    (uint32_t)height_byte0;
    pixel_format = *(uint8_t *)(entry_state[0] + 0x10);
    pixel_address = entry_state[0] + 0x16;
    pixel_bits = 0x10;
    transparent_color = -1;
    if (transparency_mode == 0)
    {
        if (draw_context != 0)
        {
            bda_sango_gui_render_region(draw_context, screen_x, screen_y, bitmap_width,
                                        bitmap_height, bitmap_width, bitmap_height,
                                        &descriptor_flags, 0, 0);
            return;
        }
        bda_sango_gui_draw_guard(1);
        active_draw_context = bda_sango_gui_object_draw_begin(g_app_frame);
        bda_sango_gui_render_region(active_draw_context, screen_x, screen_y, bitmap_width,
                                    bitmap_height, bitmap_width, bitmap_height, &descriptor_flags,
                                    0, 0);
    }
    else
    {
        if (transparency_mode != 1)
        {
            return;
        }
        if (draw_context != 0)
        {
            transparent_color = bda_sango_gui_rgb(draw_context, 0xff, 0, 0xff);
            bda_sango_gui_render_region(draw_context, screen_x, screen_y, bitmap_width,
                                        bitmap_height, bitmap_width, bitmap_height,
                                        &descriptor_flags, 0, 0);
            return;
        }
        bda_sango_gui_draw_guard(1);
        active_draw_context = bda_sango_gui_object_draw_begin(g_app_frame);
        transparent_color = bda_sango_gui_rgb(active_draw_context, 0xff, 0, 0xff);
        bda_sango_gui_render_region(active_draw_context, screen_x, screen_y, bitmap_width,
                                    bitmap_height, bitmap_width, bitmap_height, &descriptor_flags,
                                    0, 0);
    }
    bda_sango_gui_object_draw_end(g_app_frame, active_draw_context);
    bda_sango_gui_draw_guard(0);
    return;
}
#undef transparency_mode
#undef container_address
#undef entry_state
#undef descriptor_flags
#undef bitmap_width
#undef bitmap_height
#undef descriptor_aux
#undef pixel_format
#undef pixel_bits
#undef pixel_address
#undef transparent_color
#undef height_byte0
#undef height_byte1
#undef height_byte2
#undef height_byte3

/* 原函数 0x81c0a2c0 */
void sango_platform_window_auxiliary(uint32_t argument0, uint32_t argument1)
{
    bda_sango_gui_window_aux_a(g_app_frame, argument0, argument1);
    return;
}

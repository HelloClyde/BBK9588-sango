#include "sango_internal.h"

/* SDK窗口消息及基础绘图适配。 */

/* 原函数 0x81c07e70 */
uint32_t sango_window_proc(uint32_t handle, int message, uint32_t wparam, uint32_t lparam)
{
    uint32_t message_result;

    g_native_event_kind = message;
    if (message < 0x13)
    {
        if (0xf < message)
        {
            g_native_event_key = wparam & 0xffff;
            g_native_event_data = lparam;
            return 0;
        }
        if ((message == 1) || (message == 2))
        {
            g_native_event_key = wparam & 0xffff;
            g_native_event_data = lparam;
            /* Consumed touch must not reach the firmware default procedure,
             * which can turn the same gesture into a second key/ESC action. */
            return 1;
        }
    }
    else
    {
        if (message == 0x66)
        {
            bda_sango_gui_end_draw(g_draw_context);
            bda_sango_gui_frame_stop(g_app_frame);
            bda_sango_gui_frame_release(g_app_frame);
            return 0;
        }
        if ((message < 0x67) && (message == 0x60))
        {
            g_app_frame = handle;
            g_draw_context = bda_sango_gui_current_draw(handle);
        }
    }
    if (message == BDA_MSG_WINDOW_TIMER)
    {
        g_native_event_key = wparam;
        g_native_event_data = lparam;
    }
    message_result = bda_sango_gui_default_proc(handle, message, wparam, lparam);
    return message_result;
}

/* 原函数 0x81c07fd4 */
void sango_display_copy_and_refresh(short source_x, short source_y, uint32_t target_context,
                                    uint32_t source_context)
{
    int copy_x;
    int copy_y;

    copy_x = (int)source_x;
    copy_y = (int)source_y;
    if (((copy_x + 0xefU & 0xffff) < 0x1df) && ((copy_y + 0x13fU & 0xffff) < 0x27f))
    {
        if (target_context == 0)
        {
            if (source_context != 0)
            {
                bda_sango_gui_context_copy(0, 0, 0, 0xf0, 0x140, g_draw_context, copy_x, copy_y, 0);
                bda_sango_gui_request_redraw(g_app_frame, 0, 0);
            }
        }
        else
        {
            if (source_context == 0)
            {
                source_context = 0;
                target_context = g_draw_context;
            }
            bda_sango_gui_context_copy(target_context, 0, 0, 0xf0, 0x140, source_context, copy_x,
                                       copy_y, 0);
        }
    }
    return;
}

/* 原函数 0x81c08100 */
void sango_display_fill_rectangle(short left, short top, short right, short bottom, uint32_t color,
                                  uint32_t target)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
    (*(uint32_t *)(abi_storage + 0)) = color;
    (*(uint32_t *)(abi_storage + 4)) = target;
#define color (*(uint32_t *)(abi_storage + 0))
#define target (*(uint32_t *)(abi_storage + 4))

    int width;
    int height;
    int screen_x;
    int screen_y;
    uint32_t brush_kind;

    screen_y = (unsigned short)top;
    screen_x = (unsigned short)left;
    height = (unsigned short)(bottom - top + 1);
    width = (unsigned short)(right - left + 1);
    if (color == 1)
    {
        brush_kind = 8;
    }
    else if (color == 0)
    {
        brush_kind = 0xf;
    }
    else if (color == 2)
    {
        brush_kind = 7;
    }
    else
    {
        brush_kind = 0x10;
    }
    if (color <= 3)
        color = (uint32_t)bda_sango_gui_draw_object(brush_kind);
    if (target == 0)
    {
        bda_sango_gui_draw_guard(1);
        bda_sango_gui_bind_image_resource(g_draw_context, color);
        bda_sango_gui_fill_region(g_draw_context, screen_x, screen_y, width, height);
        bda_sango_gui_request_redraw(g_app_frame, 0, 0);
        bda_sango_gui_draw_guard(0);
    }
    else
    {
        bda_sango_gui_bind_image_resource(g_draw_context, color);
        bda_sango_gui_fill_region(g_draw_context, screen_x, screen_y, width, height);
        bda_sango_gui_bind_image_resource(target, color);
        bda_sango_gui_fill_region(target, screen_x, screen_y, width, height);
    }
    return;
}
#undef color
#undef target

/* 原函数 0x81c082fc */
void sango_display_blit_palette_bitmap(short x, short y, short width, short height, short source_x,
                                       short source_y, int bitmap_address,
                                       uint32_t ignored_argument8, uint32_t ignored_argument9,
                                       uint32_t draw_context, int transparency_mode)
{
    unsigned char abi_storage[132] __attribute__((aligned(8)));
    (*(short *)(abi_storage + 88)) = source_x;
    (*(short *)(abi_storage + 92)) = source_y;
    (*(int *)(abi_storage + 96)) = bitmap_address;
    (*(uint32_t *)(abi_storage + 100)) = ignored_argument8;
    (*(uint32_t *)(abi_storage + 104)) = ignored_argument9;
    (*(uint32_t *)(abi_storage + 108)) = draw_context;
    (*(int *)(abi_storage + 112)) = transparency_mode;
#define source_x (*(short *)(abi_storage + 88))
#define descriptor_flags (*(uint32_t *)(abi_storage + 0))
#define source_y (*(short *)(abi_storage + 92))
#define bitmap_width (*(int *)(abi_storage + 4))
#define bitmap_address (*(int *)(abi_storage + 96))
#define bitmap_height (*(int *)(abi_storage + 8))
#define ignored_argument8 (*(uint32_t *)(abi_storage + 100))
#define descriptor_aux (*(uint32_t *)(abi_storage + 12))
#define ignored_argument9 (*(uint32_t *)(abi_storage + 104))
#define pixel_format (*(uint8_t *)(abi_storage + 16))
#define draw_context (*(uint32_t *)(abi_storage + 108))
#define pixel_bits (*(uint8_t *)(abi_storage + 17))
#define transparency_mode (*(int *)(abi_storage + 112))
#define pixel_address (*(int *)(abi_storage + 20))
#define transparent_color (*(int *)(abi_storage + 24))
#define height_byte0 (*(uint8_t *)(abi_storage + 32))
#define height_byte1 (*(uint8_t *)(abi_storage + 33))
#define height_byte2 (*(uint8_t *)(abi_storage + 34))
#define height_byte3 (*(uint8_t *)(abi_storage + 35))

    uint32_t active_draw_context;
    int draw_height;
    int crop_x;
    int crop_y;
    int screen_x;
    int screen_y;
    int draw_width;

    descriptor_flags = 0;
    screen_x = (int)x;
    screen_y = (int)y;
    bitmap_width = (((uint32_t) * (uint8_t *)(bitmap_address + 7) * 0x100 +
                     (uint32_t) * (uint8_t *)(bitmap_address + 6)) *
                        0x100 +
                    (uint32_t) * (uint8_t *)(bitmap_address + 5)) *
                       0x100 +
                   (uint32_t) * (uint8_t *)(bitmap_address + 4);
    height_byte0 = *(uint8_t *)(bitmap_address + 8);
    draw_width = (int)width;
    draw_height = (int)height;
    height_byte1 = *(uint8_t *)(bitmap_address + 9);
    height_byte2 = *(uint8_t *)(bitmap_address + 10);
    height_byte3 = *(uint8_t *)(bitmap_address + 0xb);
    descriptor_aux = 0;
    bitmap_height = (((uint32_t)height_byte3 * 0x100 + (uint32_t)height_byte2) * 0x100 +
                     (uint32_t)height_byte1) *
                        0x100 +
                    (uint32_t)height_byte0;
    pixel_format = *(uint8_t *)(bitmap_address + 0x10);
    pixel_address = bitmap_address + 0x16;
    pixel_bits = 0x10;
    transparent_color = -1;
    crop_x = (int)source_x;
    crop_y = (int)source_y;
    if (transparency_mode == 0)
    {
        if (draw_context != 0)
        {
            bda_sango_gui_render_region(draw_context, screen_x, screen_y, draw_width, draw_height,
                                        bitmap_width, bitmap_height, &descriptor_flags, crop_x,
                                        crop_y);
            return;
        }
        bda_sango_gui_draw_guard(1);
        active_draw_context = bda_sango_gui_object_draw_begin(g_app_frame);
        bda_sango_gui_render_region(active_draw_context, screen_x, screen_y, draw_width,
                                    draw_height, bitmap_width, bitmap_height, &descriptor_flags,
                                    crop_x, crop_y);
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
            bda_sango_gui_render_region(draw_context, screen_x, screen_y, draw_width, draw_height,
                                        bitmap_width, bitmap_height, &descriptor_flags, crop_x,
                                        crop_y);
            return;
        }
        bda_sango_gui_draw_guard(1);
        active_draw_context = bda_sango_gui_object_draw_begin(g_app_frame);
        transparent_color = bda_sango_gui_rgb(active_draw_context, 0xff, 0, 0xff);
        bda_sango_gui_render_region(active_draw_context, screen_x, screen_y, draw_width,
                                    draw_height, bitmap_width, bitmap_height, &descriptor_flags,
                                    crop_x, crop_y);
    }
    bda_sango_gui_object_draw_end(g_app_frame, active_draw_context);
    bda_sango_gui_draw_guard(0);
    return;
}
#undef source_x
#undef descriptor_flags
#undef source_y
#undef bitmap_width
#undef bitmap_address
#undef bitmap_height
#undef ignored_argument8
#undef descriptor_aux
#undef ignored_argument9
#undef pixel_format
#undef draw_context
#undef pixel_bits
#undef transparency_mode
#undef pixel_address
#undef transparent_color
#undef height_byte0
#undef height_byte1
#undef height_byte2
#undef height_byte3

/* 原函数 0x81c0863c */
void sango_display_capture_bitmap(short x, short y, short width, short height, short source_x,
                                  short source_y, uint16_t *dimensions, int bitmap_address,
                                  uint32_t ignored_argument9, int draw_mode, int pixel_mode)
{
    unsigned char abi_storage[44] __attribute__((aligned(8)));
    (*(short *)(abi_storage + 0)) = source_x;
    (*(short *)(abi_storage + 4)) = source_y;
    (*(uint16_t **)(abi_storage + 8)) = dimensions;
    (*(int *)(abi_storage + 12)) = bitmap_address;
    (*(uint32_t *)(abi_storage + 16)) = ignored_argument9;
    (*(int *)(abi_storage + 20)) = draw_mode;
    (*(int *)(abi_storage + 24)) = pixel_mode;
#define source_x (*(short *)(abi_storage + 0))
#define source_y (*(short *)(abi_storage + 4))
#define dimensions (*(uint16_t **)(abi_storage + 8))
#define bitmap_address (*(int *)(abi_storage + 12))
#define ignored_argument9 (*(uint32_t *)(abi_storage + 16))
#define draw_mode (*(int *)(abi_storage + 20))
#define pixel_mode (*(int *)(abi_storage + 24))

    uint16_t source_height;
    uint16_t source_width;
    void *cropped_pixels;
    int rounded_width;
    int crop_x_or_result;
    int crop_y;
    uint32_t draw_width;
    uint32_t draw_height;
    uint32_t copy_mode;
    void *pixel_data;

    draw_width = (uint32_t)width;
    draw_height = (uint32_t)height;
    crop_x_or_result = (int)source_x;
    crop_y = (int)source_y;
    if (pixel_mode == 1)
    {
        copy_mode = 1;
    }
    else if (pixel_mode == 2)
    {
        copy_mode = 2;
    }
    if (1 < (copy_mode - 1 & 0xff))
    {
        return;
    }
    if (dimensions == (uint16_t *)0x0)
    {
        return;
    }
    source_height = dimensions[1];
    source_width = *dimensions;
    pixel_data = (void *)(bitmap_address + 0xc);
    if ((((crop_x_or_result != 0) || (crop_y != 0)) || (source_width != draw_width)) ||
        (source_height != draw_height))
    {
        rounded_width = draw_width + 3;
        if ((int)(draw_width + 3) < 0)
        {
            rounded_width = draw_width + 6;
        }
        cropped_pixels = bda_sango_mem_alloc((rounded_width >> 2) * draw_height + 0x20);
        if (cropped_pixels == 0)
        {
            return;
        }
        crop_x_or_result =
            bda_sango_gui_bitmap_crop((uint32_t)source_width, (uint32_t)source_height,
                                      crop_x_or_result, crop_y, crop_x_or_result + draw_width + -1,
                                      crop_y + draw_height + -1, pixel_data, cropped_pixels);
        pixel_data = cropped_pixels;
        if (crop_x_or_result == 0)
            goto release_pixel_data;
    }
    if (draw_mode == 0)
    {
        bda_sango_gui_bitmap_context(g_draw_context, (int)x, (int)y, draw_width, draw_height,
                                     pixel_data, copy_mode);
        bda_sango_gui_bitmap_buffer((int)x, (int)y, draw_width, draw_height, pixel_data,
                                    g_frame_buffer, copy_mode);
        bda_sango_gui_request_redraw(g_app_frame, 0, 0);
    }
release_pixel_data:
    if (pixel_data != 0)
    {
        bda_sango_mem_free(pixel_data);
    }
    return;
}
#undef source_x
#undef source_y
#undef dimensions
#undef bitmap_address
#undef ignored_argument9
#undef draw_mode
#undef pixel_mode

/* 原函数 0x81c0886c */
void sango_display_put_gray_pixel(short x, short y, uint32_t gray_level, uint32_t draw_context)
{
    uint32_t brush_kind;
    int screen_x;
    int screen_y;
    void *brush_object;

    screen_x = (int)x;
    screen_y = (int)y;
    if (screen_x < 0)
    {
        return;
    }
    if (screen_y < 0)
    {
        return;
    }
    if (0xef < screen_x)
    {
        return;
    }
    if (0x13f < screen_y)
    {
        return;
    }
    if (3 < gray_level)
    {
        return;
    }
    if (gray_level == 1)
    {
        brush_kind = 8;
    }
    else if (gray_level == 0)
    {
        brush_kind = 0xf;
    }
    else if (gray_level == 2)
    {
        brush_kind = 7;
    }
    else
    {
        brush_kind = 0x10;
    }
    brush_object = bda_sango_gui_draw_object(brush_kind);
    if (draw_context == 0)
    {
        bda_sango_gui_draw_guard(1);
        bda_sango_gui_put_pixel(g_draw_context, screen_x, screen_y, (uint32_t)brush_object);
        bda_sango_gui_request_redraw(g_app_frame, 0, 0);
        bda_sango_gui_draw_guard(0);
    }
    else
    {
        bda_sango_gui_put_pixel(draw_context, screen_x, screen_y, (uint32_t)brush_object);
    }
    return;
}

/* 原函数 0x81c089c4 */
void sango_display_draw_line(short start_x, short start_y, short end_x, short end_y,
                             uint32_t gray_level, uint32_t ignored_style, uint32_t target_context)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
    (*(uint32_t *)(abi_storage + 0)) = gray_level;
    (*(uint32_t *)(abi_storage + 4)) = ignored_style;
    (*(uint32_t *)(abi_storage + 8)) = target_context;
#define gray_level (*(uint32_t *)(abi_storage + 0))
#define ignored_style (*(uint32_t *)(abi_storage + 4))
#define target_context (*(uint32_t *)(abi_storage + 8))

    short delta_x_short;
    short delta_y_short;
    int abs_delta_x;
    int abs_delta_y;
    void *previous_pen;
    int slope_sign;
    uint32_t pen_kind;
    void *pen_object;
    int x_work;
    int clipped_start_x;
    int y_work;
    int clipped_start_y;
    int clipped_end_x;
    int clipped_end_y;
    int delta_y;
    int delta_x;

    x_work = (int)start_x;
    y_work = (int)start_y;
    clipped_end_x = (int)end_x;
    clipped_end_y = (int)end_y;
    if ((x_work < 0) && (clipped_end_x < 0))
    {
        return;
    }
    if ((y_work < 0) && (clipped_end_y < 0))
    {
        return;
    }
    if ((0xef < x_work) && (0xef < clipped_end_x))
    {
        return;
    }
    if ((0x13f < y_work) && (0x13f < clipped_end_y))
    {
        return;
    }
    clipped_start_x = x_work;
    if (x_work < 0)
    {
        clipped_start_x = 0;
    }
    if (clipped_end_x < 0)
    {
        clipped_end_x = 0;
    }
    clipped_start_y = y_work;
    if (y_work < 0)
    {
        clipped_start_y = 0;
    }
    if (clipped_end_y < 0)
    {
        clipped_end_y = 0;
    }
    if (0xef < clipped_end_x)
    {
        clipped_end_x = 0xef;
    }
    if (0x13f < clipped_end_y)
    {
        clipped_end_y = 0x13f;
    }
    if (0xef < x_work)
    {
        clipped_start_x = 0xef;
    }
    if (0x13f < y_work)
    {
        clipped_start_y = 0x13f;
    }
    if (3 < gray_level)
    {
        return;
    }
    if (gray_level == 1)
    {
        pen_kind = 8;
    }
    else if (gray_level == 0)
    {
        pen_kind = 0xf;
    }
    else if (gray_level == 2)
    {
        pen_kind = 7;
    }
    else
    {
        pen_kind = 0x10;
    }
    pen_object = bda_sango_gui_draw_object(pen_kind);
    if (target_context == 0)
    {
        previous_pen = bda_sango_gui_select_draw_object(g_draw_context, pen_object);
        bda_sango_gui_draw_guard(1);
        bda_sango_gui_move_to(g_draw_context, clipped_start_x, clipped_start_y);
        bda_sango_gui_line_to(g_draw_context, clipped_end_x, clipped_end_y);
        bda_sango_gui_request_redraw(g_app_frame, 0, 0);
        bda_sango_gui_select_draw_object(g_draw_context, previous_pen);
        bda_sango_gui_draw_guard(0);
    }
    else if ((clipped_start_x == clipped_end_x) || (clipped_start_y == clipped_end_y))
    {
        x_work = clipped_start_x;
        if (clipped_end_x < clipped_start_x)
        {
            x_work = clipped_end_x;
            clipped_end_x = clipped_start_x;
        }
        y_work = clipped_start_y;
        if (clipped_end_y < clipped_start_y)
        {
            y_work = clipped_end_y;
            clipped_end_y = clipped_start_y;
        }
        sango_display_fill_rectangle((short)x_work, (short)y_work, (short)clipped_end_x,
                                     (short)clipped_end_y, gray_level, target_context);
    }
    else
    {
        x_work = (clipped_end_x - clipped_start_x) * 0x10000;
        y_work = (clipped_end_y - clipped_start_y) * 0x10000;
        delta_x = x_work >> 0x10;
        delta_y = y_work >> 0x10;
        slope_sign = 1;
        if (delta_x * delta_y < 0)
        {
            slope_sign = -1;
        }
        abs_delta_x = sango_crt_abs(delta_x);
        abs_delta_y = sango_crt_abs(delta_y);
        delta_x_short = (short)((uint32_t)x_work >> 0x10);
        delta_y_short = (short)((uint32_t)y_work >> 0x10);
        if (abs_delta_y < abs_delta_x)
        {
            x_work = clipped_start_x;
            if (delta_x < 0)
            {
                delta_x = (int)-delta_x_short;
                delta_y = (int)-delta_y_short;
                x_work = clipped_end_x;
                clipped_start_y = clipped_end_y;
                clipped_end_x = clipped_start_x;
            }
            clipped_end_y = delta_y * 2 - delta_x;
            sango_display_put_gray_pixel((short)x_work, (short)clipped_start_y, gray_level,
                                         target_context);
            while (x_work < clipped_end_x)
            {
                clipped_end_y = clipped_end_y * 0x10000 >> 0x10;
                clipped_start_x = (x_work + 1) * 0x10000;
                x_work = clipped_start_x >> 0x10;
                y_work = delta_y << 0x11;
                if (-1 < clipped_end_y)
                {
                    clipped_start_y = (clipped_start_y + slope_sign) * 0x10000 >> 0x10;
                    y_work = (delta_y - delta_x) * 0x20000;
                }
                clipped_end_y = clipped_end_y + (y_work >> 0x10);
                sango_display_put_gray_pixel((short)((uint32_t)clipped_start_x >> 0x10),
                                             (short)clipped_start_y, gray_level, target_context);
            }
        }
        else
        {
            x_work = clipped_start_y;
            if (delta_y < 0)
            {
                delta_x = (int)-delta_x_short;
                delta_y = (int)-delta_y_short;
                clipped_start_x = clipped_end_x;
                x_work = clipped_end_y;
                clipped_end_y = clipped_start_y;
            }
            clipped_end_x = delta_x * 2 - delta_y;
            sango_display_put_gray_pixel((short)clipped_start_x, (short)x_work, gray_level,
                                         target_context);
            while (x_work < clipped_end_y)
            {
                clipped_end_x = clipped_end_x * 0x10000 >> 0x10;
                clipped_start_y = (x_work + 1) * 0x10000;
                x_work = clipped_start_y >> 0x10;
                y_work = delta_x << 0x11;
                if (-1 < clipped_end_x)
                {
                    clipped_start_x = (clipped_start_x + slope_sign) * 0x10000 >> 0x10;
                    y_work = (delta_x - delta_y) * 0x20000;
                }
                clipped_end_x = clipped_end_x + (y_work >> 0x10);
                sango_display_put_gray_pixel((short)clipped_start_x,
                                             (short)((uint32_t)clipped_start_y >> 0x10), gray_level,
                                             target_context);
            }
        }
    }
    return;
}
#undef gray_level
#undef ignored_style
#undef target_context

/* 原函数 0x81c08e7c */
void sango_display_draw_rectangle(short x1, short y1, short x2, short y2, uint32_t gray,
                                  uint32_t line_style, int context)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
    (*(uint32_t *)(abi_storage + 0)) = gray;
    (*(uint32_t *)(abi_storage + 4)) = line_style;
    (*(int *)(abi_storage + 8)) = context;
#define gray (*(uint32_t *)(abi_storage + 0))
#define line_style (*(uint32_t *)(abi_storage + 4))
#define context (*(int *)(abi_storage + 8))

    void *previous_draw_object;
    short edge_left;
    uint32_t draw_object_id;
    short edge_y;
    short edge_right;
    short edge_bottom;
    int normalized_bottom;
    int normalized_right;
    int original_bottom;
    int normalized_top;
    int normalized_left;
    void *draw_object;

    normalized_left = (int)x1;
    normalized_top = (int)y1;
    normalized_bottom = (int)x2;
    original_bottom = (int)y2;
    if (3 < gray)
    {
        return;
    }
    normalized_right = normalized_bottom;
    if (normalized_bottom < normalized_left)
    {
        normalized_right = normalized_left;
        normalized_left = normalized_bottom;
    }
    normalized_bottom = original_bottom;
    if (original_bottom < normalized_top)
    {
        normalized_bottom = normalized_top;
        normalized_top = original_bottom;
    }
    draw_object_id = 8;
    if (gray != 1)
    {
        if (gray == 0)
        {
            draw_object_id = 0xf;
        }
        else if (gray == 2)
        {
            draw_object_id = 7;
        }
        else
        {
            draw_object_id = 0x10;
            if (gray != 3)
                goto draw_rectangle_edges;
        }
    }
    draw_object = bda_sango_gui_draw_object(draw_object_id);
draw_rectangle_edges:
    if (context == 0)
    {
        previous_draw_object = bda_sango_gui_select_draw_object(g_draw_context, draw_object);
        bda_sango_gui_draw_guard(1);
        bda_sango_gui_rectangle(g_draw_context, normalized_left, normalized_top,
                                normalized_right + 1, normalized_bottom + 1);
        bda_sango_gui_draw_guard(0);
        bda_sango_gui_request_redraw(g_app_frame, 0, 0);
        bda_sango_gui_select_draw_object(g_draw_context, previous_draw_object);
    }
    edge_left = (short)normalized_left;
    edge_y = (short)normalized_top;
    edge_right = (short)normalized_right;
    sango_display_draw_line(edge_left, edge_y, edge_right, edge_y, gray, line_style, context);
    edge_bottom = (short)normalized_bottom;
    sango_display_draw_line(edge_right, edge_y, edge_right, edge_bottom, gray, line_style, context);
    sango_display_draw_line(edge_left, edge_bottom, edge_right, edge_bottom, gray, line_style,
                            context);
    sango_display_draw_line(edge_left, edge_y, edge_left, edge_bottom, gray, line_style, context);
    return;
}
#undef gray
#undef line_style
#undef context

/* 原函数 0x81c090c4 */
void sango_display_draw_circle(short center_x, short center_y, int radius, uint32_t gray_level,
                               uint32_t ignored_style, int draw_context)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
    (*(uint32_t *)(abi_storage + 0)) = ignored_style;
    (*(int *)(abi_storage + 4)) = draw_context;
#define ignored_style (*(uint32_t *)(abi_storage + 0))
#define draw_context (*(int *)(abi_storage + 4))

    int offset_difference;
    void *previous_pen;
    int decision_error;
    short point_x_positive;
    short point_x_negative;
    int origin_x;
    uint32_t pen_kind;
    short point_y;
    void *pen_object;
    int offset_y;
    int offset_x;
    int previous_error;
    int origin_y;

    origin_x = (int)center_x;
    origin_y = (int)center_y;
    if (radius == 0)
    {
        return;
    }
    if (3 < gray_level)
    {
        return;
    }
    if (gray_level == 1)
    {
        pen_kind = 8;
    }
    else if (gray_level == 0)
    {
        pen_kind = 0xf;
    }
    else if (gray_level == 2)
    {
        pen_kind = 7;
    }
    else
    {
        pen_kind = 0x10;
        if (gray_level != 3)
            goto draw_circle;
    }
    pen_object = bda_sango_gui_draw_object(pen_kind);
draw_circle:
    if (draw_context == 0)
    {
        previous_pen = bda_sango_gui_select_draw_object(g_draw_context, pen_object);
        bda_sango_gui_circle(g_draw_context, origin_x, origin_y, radius);
        bda_sango_gui_request_redraw(g_app_frame, 0, 0);
        bda_sango_gui_select_draw_object(g_draw_context, previous_pen);
    }
    decision_error = radius * -2 + 3;
    offset_y = (int)(short)radius;
    offset_x = 0;
    if (-1 < offset_y)
    {
        do
        {
            previous_error = decision_error * 0x10000 >> 0x10;
            point_x_positive = (short)((uint32_t)((origin_x + offset_x) * 0x10000) >> 0x10);
            point_y = (short)((uint32_t)((origin_y + offset_y) * 0x10000) >> 0x10);
            sango_display_put_gray_pixel(point_x_positive, point_y, gray_level, draw_context);
            point_x_negative = (short)((uint32_t)((origin_x - offset_x) * 0x10000) >> 0x10);
            sango_display_put_gray_pixel(point_x_negative, point_y, gray_level, draw_context);
            point_y = (short)((uint32_t)((origin_y - offset_y) * 0x10000) >> 0x10);
            sango_display_put_gray_pixel(point_x_positive, point_y, gray_level, draw_context);
            sango_display_put_gray_pixel(point_x_negative, point_y, gray_level, draw_context);
            point_x_positive = (short)((uint32_t)((origin_x + offset_y) * 0x10000) >> 0x10);
            point_y = (short)((uint32_t)((origin_y + offset_x) * 0x10000) >> 0x10);
            sango_display_put_gray_pixel(point_x_positive, point_y, gray_level, draw_context);
            point_x_negative = (short)((uint32_t)((origin_x - offset_y) * 0x10000) >> 0x10);
            sango_display_put_gray_pixel(point_x_negative, point_y, gray_level, draw_context);
            point_y = (short)((uint32_t)((origin_y - offset_x) * 0x10000) >> 0x10);
            sango_display_put_gray_pixel(point_x_positive, point_y, gray_level, draw_context);
            sango_display_put_gray_pixel(point_x_negative, point_y, gray_level, draw_context);
            offset_difference = offset_x - offset_y;
            decision_error = previous_error + offset_x * 4 + 6;
            if (-1 < previous_error)
            {
                offset_y = (offset_y + -1) * 0x10000 >> 0x10;
                decision_error = previous_error + offset_difference * 4 + 10;
            }
            offset_x = (offset_x + 1) * 0x10000 >> 0x10;
        } while (offset_x <= offset_y);
    }
    return;
}
#undef ignored_style
#undef draw_context

/* 原函数 0x81c093c0 */
void sango_display_draw_polyline(short center_x, short center_y, int radius, uint32_t gray,
                                 int context)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(int *)(abi_storage + 0)) = context;
#define context (*(int *)(abi_storage + 0))

    int coordinate_difference;
    int decision_accumulator;
    short inner_right;
    short outer_right_or_row;
    short inner_row;
    short inner_left;
    short outer_left;
    int radius_y;
    int radius_x;
    int origin_y;
    int origin_x;
    int decision_value;

    origin_x = (int)center_x;
    origin_y = (int)center_y;
    if (((radius != 0) && (gray < 4)) && (context != 0))
    {
        decision_accumulator = radius * -2 + 3;
        radius_y = (int)(short)radius;
        radius_x = 0;
        if (-1 < radius_y)
        {
            do
            {
                decision_value = decision_accumulator * 0x10000 >> 0x10;
                inner_right = (short)((uint32_t)((origin_x + radius_x) * 0x10000) >> 0x10);
                outer_right_or_row = (short)((uint32_t)((origin_y + radius_y) * 0x10000) >> 0x10);
                inner_left = (short)((uint32_t)((origin_x - radius_x) * 0x10000) >> 0x10);
                sango_display_draw_line(inner_right, outer_right_or_row, inner_left,
                                        outer_right_or_row, gray, 0, context);
                outer_right_or_row = (short)((uint32_t)((origin_x + radius_y) * 0x10000) >> 0x10);
                inner_row = (short)((uint32_t)((origin_y + radius_x) * 0x10000) >> 0x10);
                outer_left = (short)((uint32_t)((origin_x - radius_y) * 0x10000) >> 0x10);
                sango_display_draw_line(outer_right_or_row, inner_row, outer_left, inner_row, gray,
                                        0, context);
                inner_row = (short)((uint32_t)((origin_y - radius_x) * 0x10000) >> 0x10);
                sango_display_draw_line(outer_right_or_row, inner_row, outer_left, inner_row, gray,
                                        0, context);
                outer_right_or_row = (short)((uint32_t)((origin_y - radius_y) * 0x10000) >> 0x10);
                sango_display_draw_line(inner_right, outer_right_or_row, inner_left,
                                        outer_right_or_row, gray, 0, context);
                coordinate_difference = radius_x - radius_y;
                decision_accumulator = decision_value + radius_x * 4 + 6;
                if (-1 < decision_value)
                {
                    radius_y = (radius_y + -1) * 0x10000 >> 0x10;
                    decision_accumulator = decision_value + coordinate_difference * 4 + 10;
                }
                radius_x = (radius_x + 1) * 0x10000 >> 0x10;
            } while (radius_x <= radius_y);
        }
    }
    return;
}
#undef context

/* 原函数 0x81c095b4 */
void sango_display_set_brush(int gray, uint32_t context)
{
    void *draw_object;
    uint32_t draw_object_id;

    if (gray == 1)
    {
        draw_object_id = 8;
    }
    else if (gray == 0)
    {
        draw_object_id = 0xf;
    }
    else if (gray == 2)
    {
        draw_object_id = 7;
    }
    else
    {
        if (gray != 3)
        {
            return;
        }
        draw_object_id = 0x10;
    }
    draw_object = bda_sango_gui_draw_object(draw_object_id);
    if (context == 0)
    {
        bda_sango_gui_set_fill_object(g_draw_context, (uint32_t)draw_object);
        g_legacy_data_81c2b204 = draw_object;
    }
    else
    {
        bda_sango_gui_set_fill_object(context, (uint32_t)draw_object);
    }
    return;
}

/* 原函数 0x81c09680 */
void sango_display_set_text_color(int gray, uint32_t context)
{
    void *draw_object;
    uint32_t draw_object_id;

    if (gray == 1)
    {
        draw_object_id = 8;
    }
    else if (gray == 0)
    {
        draw_object_id = 0xf;
    }
    else if (gray == 2)
    {
        draw_object_id = 7;
    }
    else
    {
        if (gray != 3)
        {
            return;
        }
        draw_object_id = 0x10;
    }
    draw_object = bda_sango_gui_draw_object(draw_object_id);
    if (context == 0)
    {
        bda_sango_gui_set_text_color(g_draw_context, (uint32_t)draw_object);
        g_legacy_data_81c2b208 = draw_object;
    }
    else
    {
        bda_sango_gui_set_text_color(context, (uint32_t)draw_object);
    }
    return;
}

/* 原函数 0x81c0974c */
uint32_t sango_display_select_font(uint8_t font_id, uint32_t context)
{
    uint32_t selected;
    uint8_t native_font_id;

    selected = 0;
    switch (font_id)
    {
    case 0:
    case 1:
    case 2:
        native_font_id = 0;
        break;
    case 3:
    case 4:
    case 5:
        native_font_id = 4;
        break;
    case 6:
    case 7:
    case 8:
        native_font_id = 8;
        break;
    default:
        goto return_selection_result;
    }
    if (context == 0)
    {
        bda_sango_gui_select_font(g_draw_context, (uint32_t)native_font_id);
        selected = 1;
        g_legacy_data_81c2b210 = native_font_id;
    }
    else
    {
        bda_sango_gui_select_font(context, (uint32_t)native_font_id);
        selected = 1;
    }
return_selection_result:
    return selected;
}

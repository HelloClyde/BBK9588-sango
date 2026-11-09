#include "sango_internal.h"

/* 四灰度位图、遮罩、文字及上下文呈现。 */

/* 原函数 0x81c14350 */
void sango_raster_draw_screen(uint32_t x, short y, uint32_t width, uint32_t height,
                              int pixel_data_address)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(int *)(abi_storage + 0)) = pixel_data_address;
#define pixel_data_address (*(int *)(abi_storage + 0))

    int byte_count_or_offset;
    uint32_t aligned_width_or_plane_bytes;
    uint32_t pixel_value;
    uint32_t gray;
    uint32_t pixel_x;
    uint32_t pixel_shift;
    uint32_t origin_x;

    origin_x = x & 0xffff;
    sango_display_present_context(g_message_context_view2, 0);
    if (sango_color_draw_raster(x, y, width, height, pixel_data_address, g_message_context_view2,
                                0))
    {
        sango_display_present_context(0, g_message_context_view2);
        sango_display_noop();
        return;
    }
    aligned_width_or_plane_bytes = width & 0xffff;
    /* Two-bit pixels occupy four pixels per uint8_t, as in the image header's
          frame stride. Rounding to eight pixels overreads 84-pixel-wide maps. */
    if ((width & 3) != 0)
    {
        aligned_width_or_plane_bytes = (width & 0xfffc) + 4;
    }
    byte_count_or_offset = aligned_width_or_plane_bytes * (height & 0xffff);
    if (byte_count_or_offset < 0)
    {
        byte_count_or_offset = byte_count_or_offset + 3;
    }
    aligned_width_or_plane_bytes = byte_count_or_offset >> 2 & 0xffff;
    byte_count_or_offset = 0;
    if (aligned_width_or_plane_bytes != 0)
    {
        pixel_x = origin_x;
        do
        {
            pixel_shift = 6;
            do
            {
                pixel_value =
                    (int)(uint32_t) * (uint8_t *)(pixel_data_address + byte_count_or_offset) >>
                        (pixel_shift & 0x1f) &
                    3;
                gray = 3;
                if ((((pixel_value == 3) || (gray = 2, pixel_value == 2)) ||
                     (gray = 1, pixel_value == 1)) ||
                    (gray = 0, pixel_value == 0))
                {
                    sango_display_put_gray_pixel((short)pixel_x, y, gray, g_message_context_view2);
                }
                pixel_x = pixel_x + 1 & 0xffff;
                pixel_shift = pixel_shift - 2;
                if ((int)(origin_x + (width & 0xffff) + -1) < (int)pixel_x)
                {
                    y = y + 1;
                    if ((y & 7) == 0)
                        sango_music_poll();
                    pixel_x = origin_x;
                    break;
                }
            } while (-1 < (int)pixel_shift);
            byte_count_or_offset = byte_count_or_offset + 1;
        } while (byte_count_or_offset < (int)aligned_width_or_plane_bytes);
    }
    sango_display_present_context(0, g_message_context_view2);
    sango_display_noop();
    return;
}
#undef pixel_data_address

/* 原函数 0x81c14504 */
void sango_raster_draw_opaque(uint32_t x, short y, uint32_t width, uint32_t height,
                              int pixel_data_address, uint32_t context)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
    (*(int *)(abi_storage + 0)) = pixel_data_address;
    (*(uint32_t *)(abi_storage + 4)) = context;
#define pixel_data_address (*(int *)(abi_storage + 0))
#define context (*(uint32_t *)(abi_storage + 4))

    int byte_count_or_offset;
    uint32_t pixel_value;
    uint32_t gray;
    uint32_t pixel_x;
    uint32_t pixel_shift;
    uint32_t aligned_width_or_plane_bytes;
    uint32_t origin_x;

    if (sango_color_draw_raster(x, y, width, height, pixel_data_address, context, 0))
        return;
    origin_x = x & 0xffff;
    aligned_width_or_plane_bytes = width & 0xffff;
    if ((width & 3) != 0)
    {
        aligned_width_or_plane_bytes = (width & 0xfffc) + 4;
    }
    byte_count_or_offset = aligned_width_or_plane_bytes * (height & 0xffff);
    if (byte_count_or_offset < 0)
    {
        byte_count_or_offset = byte_count_or_offset + 3;
    }
    aligned_width_or_plane_bytes = byte_count_or_offset >> 2 & 0xffff;
    byte_count_or_offset = 0;
    if (aligned_width_or_plane_bytes != 0)
    {
        pixel_x = origin_x;
        do
        {
            pixel_shift = 6;
            do
            {
                pixel_value =
                    (int)(uint32_t) * (uint8_t *)(pixel_data_address + byte_count_or_offset) >>
                        (pixel_shift & 0x1f) &
                    3;
                gray = 3;
                if ((((pixel_value == 3) || (gray = 2, pixel_value == 2)) ||
                     (gray = 1, pixel_value == 1)) ||
                    (gray = 0, pixel_value == 0))
                {
                    sango_display_put_gray_pixel((short)pixel_x, y, gray, context);
                }
                pixel_x = pixel_x + 1 & 0xffff;
                pixel_shift = pixel_shift - 2;
                if ((int)(origin_x + (width & 0xffff) + -1) < (int)pixel_x)
                {
                    y = y + 1;
                    if ((y & 7) == 0)
                        sango_music_poll();
                    pixel_x = origin_x;
                    break;
                }
            } while (-1 < (int)pixel_shift);
            byte_count_or_offset = byte_count_or_offset + 1;
        } while (byte_count_or_offset < (int)aligned_width_or_plane_bytes);
    }
    return;
}
#undef pixel_data_address
#undef context

/* 原函数 0x81c14690 */
void sango_raster_draw_masked(uint32_t x, short y, uint32_t width, uint32_t height,
                              int pixel_data_address, uint32_t context)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
    (*(int *)(abi_storage + 0)) = pixel_data_address;
    (*(uint32_t *)(abi_storage + 4)) = context;
#define pixel_data_address (*(int *)(abi_storage + 0))
#define context (*(uint32_t *)(abi_storage + 4))

    int byte_count_or_offset;
    uint32_t gray;
    uint32_t pixel_x;
    uint32_t pixel_shift;
    uint32_t aligned_width_or_plane_bytes;
    uint32_t origin_x;

    if (sango_color_draw_raster(x, y, width, height, pixel_data_address, context, 1))
        return;
    origin_x = x & 0xffff;
    aligned_width_or_plane_bytes = width & 0xffff;
    if ((width & 3) != 0)
    {
        aligned_width_or_plane_bytes = (width & 0xfffc) + 4;
    }
    byte_count_or_offset = aligned_width_or_plane_bytes * (height & 0xffff);
    if (byte_count_or_offset < 0)
    {
        byte_count_or_offset = byte_count_or_offset + 3;
    }
    aligned_width_or_plane_bytes = byte_count_or_offset >> 2 & 0xffff;
    byte_count_or_offset = 0;
    if (aligned_width_or_plane_bytes != 0)
    {
        pixel_x = origin_x;
        do
        {
            pixel_shift = 6;
            do
            {
                if (((int)(uint32_t) * (uint8_t *)(pixel_data_address + byte_count_or_offset) >>
                         (pixel_shift & 0x1f) &
                     1U) == 0)
                {
                    gray = (int)(uint32_t)((
                               uint8_t *)(pixel_data_address +
                                          byte_count_or_offset))[aligned_width_or_plane_bytes] >>
                               (pixel_shift & 0x1f) &
                           3;
                    if (gray == 3)
                    {
                        gray = 3;
                    }
                    else if (gray == 2)
                    {
                        gray = 2;
                    }
                    else if (gray == 1)
                    {
                        gray = 1;
                    }
                    else
                    {
                        if (gray != 0)
                            goto next_pixel;
                        gray = 0;
                    }
                    sango_display_put_gray_pixel((short)pixel_x, y, gray, context);
                }
            next_pixel:
                pixel_x = pixel_x + 1 & 0xffff;
                pixel_shift = pixel_shift - 2;
                if ((int)(origin_x + (width & 0xffff) + -1) < (int)pixel_x)
                {
                    y = y + 1;
                    if ((y & 7) == 0)
                        sango_music_poll();
                    pixel_x = origin_x;
                    break;
                }
            } while (-1 < (int)pixel_shift);
            byte_count_or_offset = byte_count_or_offset + 1;
        } while (byte_count_or_offset < (int)aligned_width_or_plane_bytes);
    }
    return;
}
#undef pixel_data_address
#undef context

/* 原函数 0x81c14838 */
void sango_raster_draw_masked_screen(uint32_t x, short y, uint32_t width, uint32_t height,
                                     int pixel_data_address)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(int *)(abi_storage + 0)) = pixel_data_address;
#define pixel_data_address (*(int *)(abi_storage + 0))

    int byte_count_or_offset;
    uint32_t gray;
    uint32_t pixel_x;
    uint32_t pixel_shift;
    uint32_t aligned_width_or_plane_bytes;
    uint32_t origin_x;

    if (sango_color_draw_raster(x, y, width, height, pixel_data_address, 0, 1))
        return;
    origin_x = x & 0xffff;
    aligned_width_or_plane_bytes = width & 0xffff;
    if ((width & 3) != 0)
    {
        aligned_width_or_plane_bytes = (width & 0xfffc) + 4;
    }
    byte_count_or_offset = aligned_width_or_plane_bytes * (height & 0xffff);
    if (byte_count_or_offset < 0)
    {
        byte_count_or_offset = byte_count_or_offset + 3;
    }
    aligned_width_or_plane_bytes = byte_count_or_offset >> 2 & 0xffff;
    byte_count_or_offset = 0;
    if (aligned_width_or_plane_bytes != 0)
    {
        pixel_x = origin_x;
        do
        {
            pixel_shift = 6;
            do
            {
                if (((int)(uint32_t) * (uint8_t *)(pixel_data_address + byte_count_or_offset) >>
                         (pixel_shift & 0x1f) &
                     1U) == 0)
                {
                    gray = (int)(uint32_t)((
                               uint8_t *)(pixel_data_address +
                                          byte_count_or_offset))[aligned_width_or_plane_bytes] >>
                               (pixel_shift & 0x1f) &
                           3;
                    if (gray == 3)
                    {
                        gray = 3;
                    }
                    else if (gray == 2)
                    {
                        gray = 2;
                    }
                    else if (gray == 1)
                    {
                        gray = 1;
                    }
                    else
                    {
                        if (gray != 0)
                            goto next_pixel;
                        gray = 0;
                    }
                    sango_display_put_gray_pixel((short)pixel_x, y, gray, 0);
                }
            next_pixel:
                pixel_x = pixel_x + 1 & 0xffff;
                pixel_shift = pixel_shift - 2;
                if ((int)(origin_x + (width & 0xffff) + -1) < (int)pixel_x)
                {
                    y = y + 1;
                    if ((y & 7) == 0)
                        sango_music_poll();
                    pixel_x = origin_x;
                    break;
                }
            } while (-1 < (int)pixel_shift);
            byte_count_or_offset = byte_count_or_offset + 1;
        } while (byte_count_or_offset < (int)aligned_width_or_plane_bytes);
    }
    return;
}
#undef pixel_data_address

/* 原函数 0x81c149dc */
void sango_text_draw_legacy(uint16_t x, uint16_t y, char *text)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define lines_written (*(int *)(abi_storage + 4))
#define source_offset (*(int *)(abi_storage + 8))

    uint32_t original_y;
    uint16_t clip_bottom;
    int line_stride;
    void *wrapped_buffer;
    char *scanned_character;
    uint32_t characters_per_row;
    int scan_offset;
    uint8_t *line_terminator;
    int last_byte_offset;
    uint32_t wrapped_text_bytes;
    int line_end_offset;
    bool split_multibyte_character;
    int buffer_offset;
    int row_y_offset;

    clip_bottom = g_text_bottom;
    original_y = (uint32_t)y;
    uint32_t clipped_left = (uint32_t)x;
    if ((uint32_t)x < (uint32_t)g_text_left)
    {
        clipped_left = (uint32_t)g_text_left;
    }
    if (original_y < g_text_top)
    {
        y = g_text_top;
    }
    characters_per_row = (int)(g_text_right - clipped_left) / 6;
    source_offset = 0;
    lines_written = 0;
    int text_bytes = sango_crt_strlen(text);
    if (characters_per_row == 0)
    {
        sango_legacy_trap(7);
    }
    wrapped_text_bytes = text_bytes + text_bytes / (int)characters_per_row;
    if ((int)wrapped_text_bytes < (int)characters_per_row)
    {
        characters_per_row = wrapped_text_bytes;
    }
    wrapped_buffer = bbk_alloc(wrapped_text_bytes + 0x230);
    line_stride = characters_per_row + 1;
    sango_memory_fill(wrapped_buffer, 0, wrapped_text_bytes + 0x230);
    if (line_stride == 0)
    {
        sango_legacy_trap(7);
    }
    if (-1 < (int)wrapped_text_bytes / line_stride)
    {
        row_y_offset = 0;
        buffer_offset = 0;
        do
        {
            split_multibyte_character = false;
            line_end_offset = buffer_offset + characters_per_row;
            bbk_memcpy((void *)((int)wrapped_buffer + buffer_offset), text + source_offset,
                       characters_per_row);
            line_terminator = (uint8_t *)((int)wrapped_buffer + line_end_offset);
            source_offset = source_offset + characters_per_row;
            if ((0x80 < (uint8_t)line_terminator[-1]) &&
                (last_byte_offset = line_end_offset + -1, scan_offset = last_byte_offset,
                 buffer_offset <= last_byte_offset))
            {
                do
                {
                    scanned_character = (char *)((int)wrapped_buffer + scan_offset);
                    scan_offset = scan_offset + -1;
                    if (-1 < *scanned_character)
                        break;
                    split_multibyte_character = (bool)(split_multibyte_character ^ 1);
                } while (buffer_offset <= scan_offset);
                if (split_multibyte_character)
                {
                    line_terminator = (uint8_t *)((int)wrapped_buffer + last_byte_offset);
                    source_offset = source_offset + -1;
                    line_end_offset = last_byte_offset;
                }
            }
            *line_terminator = 0;
            if (((int)(wrapped_text_bytes - buffer_offset) < (int)characters_per_row) ||
                ((int)((uint32_t)clip_bottom - (uint32_t)y) <= row_y_offset))
                break;
            sango_display_select_font(0, 0);
            sango_text_draw_native(x, (short)((original_y + row_y_offset) * 0x10000 >> 0x10),
                                   (char *)((int)wrapped_buffer + buffer_offset), 0);
            lines_written = lines_written + 1;
            row_y_offset = row_y_offset + 0xc;
            if (line_stride == 0)
            {
                sango_legacy_trap(7);
            }
            buffer_offset = line_end_offset + 1;
        } while (lines_written <= (int)wrapped_text_bytes / line_stride);
    }
    if (g_text_auto_clip_view2 != '\0')
    {
        g_text_right = 0xef;
        g_text_bottom = 0x140;
        g_text_left = 0;
        g_text_top = 0;
    }
    bbk_free_if_nonnull(wrapped_buffer);
    return;
}
#undef lines_written
#undef source_offset

/* 原函数 0x81c14cac */
void sango_font_load_glyph(uint32_t character_code, int glyph_buffer_address)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define packed_glyph (*(uint8_t(*)[24])(abi_storage + 0))

    uint8_t third_byte;
    uint8_t second_byte;
    uint8_t first_byte;
    int offset;
    uint32_t source_offset_or_row;
    uint8_t *expanded_row;
    uint32_t row_index;

    if ((character_code & 0xffff) >> 8 < 0xa1)
    {
        sango_memory_fill((void *)glyph_buffer_address, 0, 0x18);
    }
    else
    {
        offset = sango_font_glyph_offset(character_code & 0xffff);
        bbk_fseek(g_font_file, offset, 0);
        bbk_fread(packed_glyph, 1, 0x12, g_font_file);
        row_index = 0;
        do
        {
            source_offset_or_row = row_index * 3 & 0xff;
            third_byte = packed_glyph[source_offset_or_row + 2];
            second_byte = packed_glyph[source_offset_or_row + 1];
            first_byte = packed_glyph[source_offset_or_row];
            source_offset_or_row = row_index & 0x3f;
            row_index = row_index + 1 & 0xff;
            expanded_row = (uint8_t *)(glyph_buffer_address + source_offset_or_row * 4);
            expanded_row[3] = third_byte << 4;
            *expanded_row = first_byte;
            expanded_row[1] = second_byte & 0xf0;
            expanded_row[2] = second_byte * '\x10' + (char)((int)(third_byte & 0xf0) >> 4);
        } while (row_index < 6);
    }
    return;
}
#undef packed_glyph

/* 原函数 0x81c14d98 */
int sango_font_glyph_offset(uint32_t character_code)
{
    return ((((character_code & 0xffff) >> 8) - 0xa1) * 0x5e + (character_code & 0xff) + -0xa1) *
           0x12;
}

/* 原函数 0x81c14dd8 */
void sango_ui_show_message(char *text, uint32_t wait_units)
{
    uint32_t text_length_or_lines;

    g_text_right_view2 = 0xeb;
    g_text_left = 5;
    text_length_or_lines = bbk_strlen(text);
    text_length_or_lines = (text_length_or_lines & 0xff) / 0x25 + 1;
    g_text_top = (uint16_t)((int)(text_length_or_lines * -0xc + 0x13f) >> 1);
    g_text_bottom_view2 = g_text_top + (short)text_length_or_lines * 0xc;
    if (0x19 < text_length_or_lines)
    {
        g_text_bottom_view2 = 0x13a;
        g_text_top = 5;
    }
    sango_display_fill_gray_rectangle(g_text_left - 3, g_text_top - 3, g_text_right_view2 + 3,
                                      g_text_bottom_view2 + 2, 0, 0);
    sango_display_draw_rectangle(g_text_left - 3, g_text_top - 3, g_text_right_view2 + 3,
                                 g_text_bottom_view2 + 2, 3, 0, 0);
    sango_text_draw_legacy(g_text_left, g_text_top, text);
    if ((wait_units & 0xff) != 0)
    {
        sango_input_wait((short)(wait_units & 0xff) * 0x28, '\x01');
    }
    return;
}

/* 原函数 0x81c14f98 */
void sango_render_present(uint32_t context)
{
    sango_music_poll();
    sango_display_present_context(0, context);
    return;
}

/* 原函数 0x81c14fb8 */
void sango_bitmap_draw_frame_screen(uint16_t x, short y, uint16_t width, uint16_t height,
                                    uint8_t frame, uint8_t *bitmap)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
    (*(uint8_t *)(abi_storage + 0)) = frame;
    (*(uint8_t **)(abi_storage + 4)) = bitmap;
#define frame (*(uint8_t *)(abi_storage + 0))
#define bitmap (*(uint8_t **)(abi_storage + 4))

    if ((bitmap[5] & 1) == 1)
    {
        sango_raster_draw_masked_screen(
            (uint32_t)x, y, (uint32_t)width, (uint32_t)height,
            (int)(bitmap +
                  (((int)(((uint32_t)bitmap[1] * 0x100 + (uint32_t)*bitmap & 0xffff) + 3) >> 2) *
                       ((uint32_t)bitmap[3] * 0x100 + (uint32_t)bitmap[2] & 0xffff)
                   << (bitmap[5] & 1)) *
                      (uint32_t)frame +
                  6));
    }
    else
    {
        sango_raster_draw_screen(
            (uint32_t)x, y, (uint32_t)width, (uint32_t)height,
            (int)(bitmap +
                  (((int)(((uint32_t)bitmap[1] * 0x100 + (uint32_t)*bitmap & 0xffff) + 3) >> 2) *
                       ((uint32_t)bitmap[3] * 0x100 + (uint32_t)bitmap[2] & 0xffff)
                   << (bitmap[5] & 1)) *
                      (uint32_t)frame +
                  6));
    }
    return;
}
#undef frame
#undef bitmap

/* 原函数 0x81c15070 */
void sango_bitmap_draw_frame(uint16_t x, short y, uint16_t width, uint16_t height, uint8_t frame,
                             uint8_t *bitmap, uint32_t target)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
    (*(uint8_t **)(abi_storage + 4)) = bitmap;
    (*(uint32_t *)(abi_storage + 8)) = target;
    (*(uint8_t *)(abi_storage + 0)) = frame;
#define bitmap (*(uint8_t **)(abi_storage + 4))
#define target (*(uint32_t *)(abi_storage + 8))
#define frame (*(uint8_t *)(abi_storage + 0))

    if ((bitmap[5] & 1) == 1)
    {
        sango_raster_draw_masked(
            (uint32_t)x, y, (uint32_t)width, (uint32_t)height,
            (int)(bitmap +
                  (((int)(((uint32_t)bitmap[1] * 0x100 + (uint32_t)*bitmap & 0xffff) + 3) >> 2) *
                       ((uint32_t)bitmap[3] * 0x100 + (uint32_t)bitmap[2] & 0xffff)
                   << (bitmap[5] & 1)) *
                      (uint32_t)frame +
                  6),
            target);
    }
    else
    {
        sango_raster_draw_opaque(
            (uint32_t)x, y, (uint32_t)width, (uint32_t)height,
            (int)(bitmap +
                  (((int)(((uint32_t)bitmap[1] * 0x100 + (uint32_t)*bitmap & 0xffff) + 3) >> 2) *
                       ((uint32_t)bitmap[3] * 0x100 + (uint32_t)bitmap[2] & 0xffff)
                   << (bitmap[5] & 1)) *
                      (uint32_t)frame +
                  6),
            target);
    }
    return;
}
#undef bitmap
#undef target
#undef frame

/* 原函数 0x81c15134 */
void sango_text_draw_context(short x, short y, char *text, uint32_t target)
{
    sango_display_select_font(0, target);
    sango_text_draw_native(x, y, text, target);
    return;
}

/* 原函数 0x81c151a8 */
void sango_text_reset_clip_bounds(void)
{
    if (g_text_auto_clip_view2 != '\0')
    {
        g_text_right = 0xef;
        g_text_bottom = 0x140;
        g_text_left = 0;
        g_text_top = 0;
    }
    return;
}

/* 原函数 0x81c151e4 */
void sango_text_draw_character(uint8_t x, uint8_t y, uint8_t legacy_text_byte)
{
    g_legacy_data_81c2b158 = 0;
    sango_text_draw_legacy((uint16_t)x, (uint16_t)y, (char *)(uint32_t)legacy_text_byte);
    return;
}

/* 原函数 0x81c15210 */
void sango_render_clear_rectangle(short left, short top, short right, short bottom, uint32_t target)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(uint32_t *)(abi_storage + 0)) = target;
#define target (*(uint32_t *)(abi_storage + 0))

    sango_display_fill_rectangle(left, top, right, bottom, 0, target);
    return;
}
#undef target

/* 原函数 0x81c152a4 */
int sango_bitmap_rectangle_byte_count(int left, int top, int right, int bottom)
{
    uint32_t rounded_width;
    uint32_t width;
    int row_bytes;

    width = (right - left) + 1;
    rounded_width = (right - left) + 4;
    if (-1 < (int)width)
    {
        rounded_width = width;
    }
    row_bytes = (int)rounded_width >> 2;
    if ((width & 3) != 0)
    {
        row_bytes = row_bytes + 1;
    }
    return (bottom - top) * row_bytes + row_bytes;
}

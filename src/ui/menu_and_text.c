#include "sango_internal.h"

/* 选项菜单、位图控件、文本布局与数值提示。 */

/* 原函数 0x81c07068 */
uint32_t sango_ui_choose_option(uint16_t *bounds, uint32_t initial_selection, char *menu_text)
{
    unsigned char abi_storage[68] __attribute__((aligned(8)));
#define event_kind (*(int *)(abi_storage + 0))
#define key_code (*(int *)(abi_storage + 4))
#define characters_per_row (*(uint32_t *)(abi_storage + 32))
#define option_count (*(uint32_t *)(abi_storage + 36))
#define top_option (*(uint32_t *)(abi_storage + 40))
#define visible_rows (*(uint32_t *)(abi_storage + 44))
#define text_offset (*(uint32_t *)(abi_storage + 48))

    bool has_scrollbar;
    bool repaint_started = false;
    bool thumb_changed;
    short previous_thumb_top;
    uint32_t thumb_y;
    uint32_t float_operand;
    short thumb_bottom;
    uint32_t track_top;
    uint32_t highlight_top;
    int highlight_bottom;
    int visible_selection_row;
    uint32_t selected_option;

    g_text_auto_clip = 0;
    g_text_bottom = bounds[3];
    g_text_top = bounds[1];
    g_text_left = *bounds;
    g_text_right = bounds[2];
    selected_option = initial_selection & 0xff;
    visible_rows = (int)((uint32_t)g_text_bottom - (uint32_t)g_text_top) / 0xc & 0xff;
    characters_per_row = (int)((uint32_t)g_text_right - (uint32_t)g_text_left) / 6 & 0xff;
    uint32_t text_bytes = bbk_strlen(menu_text);
    if (characters_per_row == 0)
    {
        sango_legacy_trap(7);
    }
    option_count = text_bytes / characters_per_row & 0xff;
    sango_ui_paint_begin();
    sango_display_fill_gray_rectangle(g_text_left - 3, g_text_top - 3, g_text_right + 2,
                                      g_text_bottom + 2, 0, 0);
    has_scrollbar = visible_rows < option_count;
    top_option = selected_option;
    if (!has_scrollbar)
    {
        top_option = 0;
    }
    sango_display_draw_rectangle(g_text_left - 3, g_text_top - 3, g_text_right + 2,
                                 g_text_bottom + 2, 3, 0, 0);
    if (has_scrollbar)
    {
        sango_display_fill_gray_rectangle(g_text_right + 2, g_text_top - 3, g_text_right + 6,
                                          g_text_bottom + 2, 0, 0);
        sango_display_draw_rectangle(g_text_right + 2, g_text_top - 3, g_text_right + 6,
                                     g_text_bottom + 2, 3, 0, 0);
        sango_display_draw_rectangle(g_text_right + 2, g_text_top - 1, g_text_right + 6,
                                     g_text_bottom, 3, 0, 0);
        if ((int)option_count < (int)(top_option + visible_rows))
        {
            top_option = option_count - visible_rows & 0xff;
        }
    }
    text_offset = top_option * characters_per_row;
    thumb_changed = true;
    visible_selection_row = selected_option - top_option;
    sango_text_draw_legacy(g_text_left, g_text_top, menu_text + text_offset);
    highlight_top = (uint32_t)(uint8_t)g_text_top + visible_selection_row * 0xc & 0xff;
    highlight_bottom = highlight_top + 0xc;
    sango_ui_paint_end();
    sango_display_invert_rectangle(g_text_left, (short)highlight_top, g_text_right,
                                   (short)highlight_bottom, 0);
    thumb_y = (uint32_t)(uint8_t)g_text_top;
    do
    {
        do
        {
            if (has_scrollbar)
            {
                previous_thumb_top = (short)thumb_y;
                thumb_bottom = previous_thumb_top + 2;
                if (thumb_changed)
                {
                    sango_display_draw_rectangle(g_text_right + 3, previous_thumb_top,
                                                 g_text_right + 5, thumb_bottom, 0, 0, 0);
                    sango_display_put_gray_pixel(g_text_right + 4, previous_thumb_top + 1, 0,
                                                 0);
                    sango_display_put_gray_pixel(g_text_right + 4, previous_thumb_top + 1, 0,
                                                 0);
                    uint32_t float_bits = sango_soft_int_to_f32((int)(char)selected_option);
                    if ((char)selected_option < 0)
                    {
                        float_bits = soft_float_add(float_bits, g_legacy_data_81c20c4c);
                    }
                    thumb_changed = false;
                    float_operand = sango_soft_int_to_f32(option_count - 1);
                    float_bits = soft_float_div(float_bits, float_operand);
                    track_top = (uint32_t)g_text_top;
                    float_operand = sango_soft_int_to_f32((g_text_bottom - track_top) - 3);
                    float_bits = soft_float_mul(float_bits, float_operand);
                    float_operand = sango_soft_int_to_f32(track_top);
                    float_bits = soft_float_add(float_bits, float_operand);
                    float_bits = sango_soft_f32_to_int(float_bits);
                    thumb_y = float_bits & 0xff;
                    thumb_bottom = (short)thumb_y + 2;
                    sango_display_draw_rectangle(g_text_right + 3, (short)thumb_y,
                                                 g_text_right + 5, thumb_bottom, 3, 0, 0);
                }
                sango_display_invert_rectangle(g_text_right + 3, (short)thumb_y,
                                               g_text_right + 5, thumb_bottom, 0);
            }
            sango_input_next_event(&event_kind);
            if (event_kind == SANGO_TOUCH_TAP || event_kind == SANGO_TOUCH_HOLD)
            {
                int tapped =
                    sango_touch_choose_row(&event_kind, g_text_left, g_text_top, g_text_right,
                                           12, visible_rows, top_option, option_count);
                if (tapped >= 0)
                {
                    selected_option = (uint32_t)tapped;
                    event_kind = 5;
                    key_code = BDA_KEY_ENTER;
                }
                else if (sango_touch_x(&event_kind) < g_text_left - 3 ||
                         sango_touch_x(&event_kind) > g_text_right + 6 ||
                         sango_touch_y(&event_kind) < g_text_top - 3 ||
                         sango_touch_y(&event_kind) > g_text_bottom + 2)
                {
                    event_kind = 5;
                    key_code = BDA_KEY_ESCAPE;
                }
            }
            else if (event_kind == SANGO_TOUCH_PAN_END)
            {
                key_code = sango_touch_swipe_key(&event_kind);
                if (key_code)
                    event_kind = 5;
            }
        } while (event_kind != 5);
        sango_display_invert_rectangle(g_text_left, (short)highlight_top, g_text_right,
                                       (short)highlight_bottom, 0);
        if (key_code == 0x1c)
        {
            g_text_left = 0;
            g_text_auto_clip = 1;
            g_text_bottom = 0x140;
            g_text_top = 0;
            g_text_right = 0xef;
            return selected_option;
        }
        if (key_code < 0x1d)
        {
            if (key_code == 1)
            {
                g_text_auto_clip = 1;
                g_text_bottom = 0x140;
                g_text_right = 0xef;
                g_text_left = 0;
                g_text_top = 0;
                return 0xff;
            }
        }
        else
        {
            if (key_code == 0x67)
            {
                if (selected_option == 0)
                {
                    thumb_changed = true;
                    top_option = option_count - visible_rows & 0xff;
                    text_offset = top_option * characters_per_row;
                    selected_option = option_count - 1 & 0xff;
                    visible_selection_row = selected_option - top_option;
                }
                else
                {
                    selected_option = selected_option - 1 & 0xff;
                    thumb_changed = true;
                    visible_selection_row = selected_option - top_option;
                    if (top_option <= selected_option)
                        goto update_selection_highlight;
                    top_option = top_option - 1 & 0xff;
                    text_offset = text_offset - characters_per_row & 0xffff;
                    visible_selection_row = selected_option - top_option;
                }
            }
            else
            {
                if (key_code != 0x6c)
                    goto update_selection_highlight;
                if (selected_option == option_count - 1)
                {
                    selected_option = 0;
                    thumb_changed = true;
                    visible_selection_row = 0;
                    top_option = 0;
                    text_offset = 0;
                }
                else
                {
                    if ((int)selected_option < (int)(option_count - 1))
                    {
                        selected_option = selected_option + 1 & 0xff;
                        thumb_changed = true;
                        visible_selection_row = selected_option - top_option;
                    }
                    if (visible_selection_row < (int)visible_rows)
                        goto update_selection_highlight;
                    top_option = top_option + 1 & 0xff;
                    text_offset = text_offset + characters_per_row & 0xffff;
                    visible_selection_row = selected_option - top_option;
                }
            }
            sango_ui_paint_begin();
            repaint_started = true;
            sango_text_draw_legacy(g_text_left, g_text_top, menu_text + text_offset);
        }
    update_selection_highlight:
        highlight_top = (uint32_t)(uint8_t)g_text_top + visible_selection_row * 0xc & 0xff;
        highlight_bottom = highlight_top + 0xc;
        if (repaint_started)
        {
            sango_ui_paint_end();
            repaint_started = false;
        }
        sango_display_invert_rectangle(g_text_left, (short)highlight_top, g_text_right,
                                      (short)highlight_bottom, 0);
    } while (true);
}
#undef event_kind
#undef key_code
#undef characters_per_row
#undef option_count
#undef top_option
#undef visible_rows
#undef text_offset

/* 原函数 0x81c077bc */
void sango_bitmap_draw_resource(uint32_t resource_id, uint32_t frame_number, uint32_t x,
                                short y, char draw_to_screen)
{
    unsigned char abi_storage[17] __attribute__((aligned(8)));
    (*(char *)(abi_storage + 0)) = draw_to_screen;
#define draw_to_screen (*(char *)(abi_storage + 0))

    uint8_t flags;
    uint8_t *bitmap;
    uint32_t dimension;
    uint32_t row_bytes;
    uint32_t width;
    uint32_t screen_x;

    screen_x = x & 0xffff;
    bitmap = (uint8_t *)sango_resource_item(resource_id & 0xffff, '\x01',
                                            g_resource_package_address);
    if ((bitmap != (uint8_t *)0x0) && ((frame_number & 0xff) <= (uint32_t)bitmap[4]))
    {
        dimension = (uint32_t)*bitmap + (uint32_t)bitmap[1] * 0x100;
        width = dimension & 0xffff;
        row_bytes = width >> 2;
        if ((dimension & 3) != 0)
        {
            row_bytes = (width >> 2) + 1;
        }
        dimension = (uint32_t)bitmap[2] + (uint32_t)bitmap[3] * 0x100 & 0xffff;
        flags = bitmap[5];
        bitmap =
            bitmap +
            (((row_bytes * dimension & 0xffff) << (flags & 1)) * ((frame_number & 0xff) - 1) &
             0xffff) +
            6;
        if (draw_to_screen == '\0')
        {
            if ((flags & 1) == 0)
            {
                sango_raster_draw_opaque(screen_x, y, width, dimension, (int)bitmap,
                                         g_game_context);
            }
            else
            {
                sango_raster_draw_masked(screen_x, y, width, dimension, (int)bitmap,
                                         g_game_context);
            }
        }
        else if ((flags & 1) == 0)
        {
            sango_raster_draw_screen(screen_x, y, width, dimension, (int)bitmap);
        }
        else
        {
            sango_raster_draw_masked_screen(screen_x, y, width, dimension, (int)bitmap);
        }
    }
    return;
}
#undef draw_to_screen

/* 原函数 0x81c0791c */
void sango_text_draw_wrapped_box(uint16_t *outer_bounds, uint16_t *inner_bounds, char *text)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define region_right (*(uint16_t(*)[4])(abi_storage + 16))
#define region_bottom (*(uint16_t(*)[4])(abi_storage + 24))
#define region_left (*(uint16_t(*)[4])(abi_storage + 0))
#define region_top (*(uint16_t(*)[4])(abi_storage + 8))

    int region_offset;
    uint32_t region_index;

    region_left[0] = *outer_bounds;
    region_top[1] = inner_bounds[1];
    region_top[3] = inner_bounds[3];
    region_right[0] = outer_bounds[2];
    region_bottom[3] = outer_bounds[3];
    region_top[0] = outer_bounds[1];
    region_right[1] = *inner_bounds;
    region_left[2] = inner_bounds[2];
    region_index = 0;
    region_left[1] = region_left[0];
    region_left[3] = region_left[0];
    region_top[2] = region_top[1];
    region_right[2] = region_right[0];
    region_right[3] = region_right[0];
    region_bottom[0] = region_top[1];
    region_bottom[1] = region_top[3];
    region_bottom[2] = region_top[3];
    sango_crt_strlen(text);
    region_offset = 0;
    do
    {
        text = sango_text_wrap_lines(*(uint16_t *)((int)region_left + region_offset),
                                     *(uint16_t *)((int)region_top + region_offset),
                                     *(uint16_t *)((int)region_right + region_offset),
                                     *(uint16_t *)((int)region_bottom + region_offset), text);
        region_index = region_index + 1 & 0xff;
        if (text == (char *)0x0)
        {
            return;
        }
        region_offset = region_index << 1;
    } while (region_index < 4);
    return;
}
#undef region_right
#undef region_bottom
#undef region_left
#undef region_top

/* 原函数 0x81c079fc */
char *sango_text_wrap_lines(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom,
                            char *text)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(char **)(abi_storage + 0)) = text;
#define text (*(char **)(abi_storage + 0))

    uint32_t text_length;
    uint32_t region_capacity;
    char *remaining_text;

    remaining_text = (char *)0x0;
    region_capacity = ((int)((uint32_t)right - (uint32_t)left) / 6) *
                          ((int)((uint32_t)bottom - (uint32_t)top) / 0xc) &
                      0xff;
    text_length = sango_crt_strlen(text);
    if (region_capacity <= text_length)
    {
        remaining_text = sango_text_find_line_end((int)text, region_capacity, '|');
        if (remaining_text == (char *)0x0)
        {
            remaining_text = text + region_capacity;
            if (region_capacity == 0)
            {
                return text;
            }
        }
        else
        {
            *remaining_text = '\0';
            remaining_text = remaining_text + 1;
        }
    }
    g_text_left = left;
    g_text_bottom = bottom;
    g_text_top = top;
    g_text_right = right;
    sango_text_draw_legacy(left, top, text);
    return remaining_text;
}
#undef text

/* 原函数 0x81c07b20 */
char *sango_text_find_line_end(int text_address, uint32_t max_length, char delimiter)
{
    char *delimiter_position;
    uint32_t scan_offset;

    scan_offset = max_length & 0xff;
    do
    {
        if (scan_offset == 0)
        {
            return (char *)0x0;
        }
        delimiter_position = (char *)(text_address + scan_offset);
        scan_offset = scan_offset - 1 & 0xff;
    } while (*delimiter_position != delimiter);
    return delimiter_position;
}

/* 原函数 0x81c07b58 */
void sango_text_draw_centered(short center_x, uint16_t y, char *text)
{
    uint32_t text_length;

    text_length = bbk_strlen(text);
    sango_text_draw_legacy(center_x - ((short)text_length * 3 & 0x7fU), y, text);
    return;
}

/* 原函数 0x81c07bc0 */
void sango_battle_show_short_message(char *text, uint16_t wait_units, uint16_t row_or_center)
{
    uint16_t screen_y;
    uint8_t *background_bitmap;
    uint32_t screen_x;

    background_bitmap =
        (uint8_t *)sango_resource_item(0x1a, '\x01', g_resource_package_address);
    screen_y = (row_or_center & 0xff) * 0xc;
    screen_x = (int)(0xef - (uint32_t)*background_bitmap) >> 1 & 0xff;
    if ((row_or_center & 0xff) == 0xff)
    {
        screen_y = (uint16_t)((int)(0x13f - (uint32_t)background_bitmap[2]) >> 1);
    }
    sango_raster_draw_screen(screen_x, screen_y & 0xff, (uint32_t)*background_bitmap,
                             (uint32_t)background_bitmap[2], (int)(background_bitmap + 6));
    sango_text_draw_legacy((short)screen_x + 10, (screen_y & 0xff) + 6, text);
    sango_input_wait((wait_units & 0xff) * 100, '\x01');
    return;
}

/* 原函数 0x81c07cac */
uint32_t sango_math_sqrt_step_search(uint16_t value)
{
    uint32_t candidate;
    uint32_t step;
    uint32_t previous;

    step = 10;
    candidate = 0;
    while (true)
    {
        previous = candidate;
        candidate = previous + step & 0xff;
        if (step == 0)
            break;
        if ((uint32_t)value <= candidate * candidate)
        {
            step = step - 1 & 0xff;
            candidate = previous;
        }
    }
    return previous;
}

/* 原函数 0x81c07cf0 */
void sango_text_draw_padded_number(uint16_t x, uint16_t y, uint32_t value, uint32_t field_width,
                                   int context)
{
    unsigned char abi_storage[108] __attribute__((aligned(8)));
    (*(int *)(abi_storage + 88)) = context;
#define context (*(int *)(abi_storage + 88))
#define padded_text (*(char(*)[16])(abi_storage + 0))
#define number_text (*(char(*)[16])(abi_storage + 16))

    uint32_t digit_count;
    uint32_t decimal_modulus;
    uint32_t width;
    char *dst;

    dst = padded_text;
    width = field_width & 0xff;
    sango_memory_fill(dst, 0x30, 0xc);
    decimal_modulus = *(uint32_t *)(&g_legacy_data_81c201e0 + width * 4);
    if (decimal_modulus == 0)
    {
        sango_legacy_trap(7);
    }
    sango_format_integer(value % decimal_modulus, number_text, 10);
    digit_count = sango_crt_strlen(number_text);
    digit_count = digit_count & 0xff;
    if ((digit_count <= width) && (decimal_modulus <= value))
    {
        dst = dst + (width - digit_count);
    }
    bbk_memcpy(dst, number_text, digit_count + 1);
    if (context == 0)
    {
        sango_text_draw_legacy(x, y, padded_text);
    }
    else
    {
        sango_text_draw_context(x, y, padded_text, context);
    }
    return;
}
#undef context
#undef padded_text
#undef number_text

/* 原函数 0x81c07e10 */
int sango_character_troop_capacity(uint32_t character_id)
{
    int character;

    character = g_character_table_address + (character_id & 0xff) * 0x10;
    return ((uint32_t) * (uint8_t *)(character + 3) + (uint32_t) * (uint8_t *)(character + 4)) *
               10 +
           (uint32_t) * (uint8_t *)(character + 2) * 100;
}

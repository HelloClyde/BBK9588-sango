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
                    sango_display_put_gray_pixel(g_text_right + 4, previous_thumb_top + 1, 0, 0);
                    sango_display_put_gray_pixel(g_text_right + 4, previous_thumb_top + 1, 0, 0);
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
                    sango_display_draw_rectangle(g_text_right + 3, (short)thumb_y, g_text_right + 5,
                                                 thumb_bottom, 3, 0, 0);
                }
                sango_display_invert_rectangle(g_text_right + 3, (short)thumb_y, g_text_right + 5,
                                               thumb_bottom, 0);
            }
            sango_input_next_event(&event_kind);
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
            sango_text_draw_legacy(g_text_left, g_text_top, menu_text + text_offset);
        }
    update_selection_highlight:
        highlight_top = (uint32_t)(uint8_t)g_text_top + visible_selection_row * 0xc & 0xff;
        highlight_bottom = highlight_top + 0xc;
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
void sango_bitmap_draw_resource(uint32_t resource_id, uint32_t frame_number, uint32_t x, short y,
                                char draw_to_screen)
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
    bitmap =
        (uint8_t *)sango_resource_item(resource_id & 0xffff, '\x01', g_resource_package_address);
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
        bitmap = bitmap +
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
void sango_text_draw_wrapped_box(uint16_t *param_1, uint16_t *param_2, char *param_3)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define local_20 (*(uint16_t(*)[4])(abi_storage + 16))
#define local_18 (*(uint16_t(*)[4])(abi_storage + 24))
#define local_30 (*(uint16_t(*)[4])(abi_storage + 0))
#define local_28 (*(uint16_t(*)[4])(abi_storage + 8))

    int iVar1;
    uint32_t uVar2;

    local_30[0] = *param_1;
    local_28[1] = param_2[1];
    local_28[3] = param_2[3];
    local_20[0] = param_1[2];
    local_18[3] = param_1[3];
    local_28[0] = param_1[1];
    local_20[1] = *param_2;
    local_30[2] = param_2[2];
    uVar2 = 0;
    local_30[1] = local_30[0];
    local_30[3] = local_30[0];
    local_28[2] = local_28[1];
    local_20[2] = local_20[0];
    local_20[3] = local_20[0];
    local_18[0] = local_28[1];
    local_18[1] = local_28[3];
    local_18[2] = local_28[3];
    sango_crt_strlen(param_3);
    iVar1 = 0;
    do
    {
        param_3 = sango_text_wrap_lines(
            *(uint16_t *)((int)local_30 + iVar1), *(uint16_t *)((int)local_28 + iVar1),
            *(uint16_t *)((int)local_20 + iVar1), *(uint16_t *)((int)local_18 + iVar1), param_3);
        uVar2 = uVar2 + 1 & 0xff;
        if (param_3 == (char *)0x0)
        {
            return;
        }
        iVar1 = uVar2 << 1;
    } while (uVar2 < 4);
    return;
}
#undef local_20
#undef local_18
#undef local_30
#undef local_28

/* 原函数 0x81c079fc */
char *sango_text_wrap_lines(uint16_t param_1, uint16_t param_2, uint16_t param_3, uint16_t param_4,
                            char *param_5)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(char **)(abi_storage + 0)) = param_5;
#define param_5 (*(char **)(abi_storage + 0))

    uint32_t uVar1;
    uint32_t uVar2;
    char *pcVar3;

    pcVar3 = (char *)0x0;
    uVar2 = ((int)((uint32_t)param_3 - (uint32_t)param_1) / 6) *
                ((int)((uint32_t)param_4 - (uint32_t)param_2) / 0xc) &
            0xff;
    uVar1 = sango_crt_strlen(param_5);
    if (uVar2 <= uVar1)
    {
        pcVar3 = sango_text_find_line_end((int)param_5, uVar2, '|');
        if (pcVar3 == (char *)0x0)
        {
            pcVar3 = param_5 + uVar2;
            if (uVar2 == 0)
            {
                return param_5;
            }
        }
        else
        {
            *pcVar3 = '\0';
            pcVar3 = pcVar3 + 1;
        }
    }
    g_text_left = param_1;
    g_text_bottom = param_4;
    g_text_top = param_2;
    g_text_right = param_3;
    sango_text_draw_legacy(param_1, param_2, param_5);
    return pcVar3;
}
#undef param_5

/* 原函数 0x81c07b20 */
char *sango_text_find_line_end(int param_1, uint32_t param_2, char param_3)
{
    char *pcVar1;
    uint32_t uVar2;

    uVar2 = param_2 & 0xff;
    do
    {
        if (uVar2 == 0)
        {
            return (char *)0x0;
        }
        pcVar1 = (char *)(param_1 + uVar2);
        uVar2 = uVar2 - 1 & 0xff;
    } while (*pcVar1 != param_3);
    return pcVar1;
}

/* 原函数 0x81c07b58 */
void sango_text_draw_centered(short param_1, uint16_t param_2, char *param_3)
{
    uint32_t uVar1;

    uVar1 = bbk_strlen(param_3);
    sango_text_draw_legacy(param_1 - ((short)uVar1 * 3 & 0x7fU), param_2, param_3);
    return;
}

/* 原函数 0x81c07bc0 */
void sango_battle_show_short_message(char *param_1, uint16_t param_2, uint16_t param_3)
{
    uint16_t uVar1;
    uint8_t *pbVar2;
    uint32_t uVar3;

    pbVar2 = (uint8_t *)sango_resource_item(0x1a, '\x01', g_resource_package_address);
    uVar1 = (param_3 & 0xff) * 0xc;
    uVar3 = (int)(0xef - (uint32_t)*pbVar2) >> 1 & 0xff;
    if ((param_3 & 0xff) == 0xff)
    {
        uVar1 = (uint16_t)((int)(0x13f - (uint32_t)pbVar2[2]) >> 1);
    }
    sango_raster_draw_screen(uVar3, uVar1 & 0xff, (uint32_t)*pbVar2, (uint32_t)pbVar2[2],
                             (int)(pbVar2 + 6));
    sango_text_draw_legacy((short)uVar3 + 10, (uVar1 & 0xff) + 6, param_1);
    sango_input_wait((param_2 & 0xff) * 100, '\x01');
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
void sango_text_draw_padded_number(uint16_t param_1, uint16_t param_2, uint32_t param_3,
                                   uint32_t param_4, int param_5)
{
    unsigned char abi_storage[108] __attribute__((aligned(8)));
    (*(int *)(abi_storage + 88)) = param_5;
#define param_5 (*(int *)(abi_storage + 88))
#define acStack_48 (*(char(*)[16])(abi_storage + 0))
#define acStack_38 (*(char(*)[16])(abi_storage + 16))

    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    char *dst;

    dst = acStack_48;
    uVar3 = param_4 & 0xff;
    sango_memory_fill(dst, 0x30, 0xc);
    uVar2 = *(uint32_t *)(&g_legacy_data_81c201e0 + uVar3 * 4);
    if (uVar2 == 0)
    {
        sango_legacy_trap(7);
    }
    sango_format_integer(param_3 % uVar2, acStack_38, 10);
    uVar1 = sango_crt_strlen(acStack_38);
    uVar1 = uVar1 & 0xff;
    if ((uVar1 <= uVar3) && (uVar2 <= param_3))
    {
        dst = dst + (uVar3 - uVar1);
    }
    bbk_memcpy(dst, acStack_38, uVar1 + 1);
    if (param_5 == 0)
    {
        sango_text_draw_legacy(param_1, param_2, acStack_48);
    }
    else
    {
        sango_text_draw_context(param_1, param_2, acStack_48, param_5);
    }
    return;
}
#undef param_5
#undef acStack_48
#undef acStack_38

/* 原函数 0x81c07e10 */
int sango_character_troop_capacity(uint32_t character_id)
{
    int character;

    character = g_character_table_address + (character_id & 0xff) * 0x10;
    return ((uint32_t) * (uint8_t *)(character + 3) + (uint32_t) * (uint8_t *)(character + 4)) *
               10 +
           (uint32_t) * (uint8_t *)(character + 2) * 100;
}

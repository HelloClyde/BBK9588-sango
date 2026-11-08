#include "sango_internal.h"

/* 可移动区域及战场形势信息。 */

/* 原函数 0x81c027f0 */
void sango_battle_draw_move_range(void)
{
    uint32_t window_left;
    uint32_t window_top;
    uint32_t source_y;
    int marker_bitmap_address;
    uint32_t viewport_row;
    uint32_t source_x;
    uint32_t viewport_y;
    uint32_t viewport_x;
    uint32_t window_row;
    uint32_t window_column;
    uint32_t viewport_column;

    window_left = (uint32_t)g_move_window_left;
    viewport_x = (uint32_t)g_battle_viewport_x;
    viewport_y = (uint32_t)g_battle_viewport_y;
    source_x = (uint32_t)g_move_source_x;
    window_top = (uint32_t)g_move_window_top;
    source_y = (uint32_t)g_move_source_y;
    marker_bitmap_address = sango_resource_item(7, '\x01', g_resource_package_address);
    for (window_column = (uint32_t)g_move_window_left; window_column < 0xf;
         window_column = window_column + 1 & 0xff)
    {
        window_row = (uint32_t)g_move_window_top;
        if (window_row < 0xf)
        {
            viewport_column = window_column - ((viewport_x + window_left) - source_x & 0xff);
            do
            {
                viewport_row = window_row - ((viewport_y + window_top) - source_y & 0xff);
                if (((viewport_column & 0xff) < 0xf) &&
                    ((viewport_row & 0xff) < SANGO_BATTLE_VIEW_ROWS))
                {
                    if ('\0' < *(char *)(g_move_costs_address + window_row * 0xf + window_column))
                    {
                        sango_raster_draw_masked((viewport_column & 0xf) << 4,
                                                 (short)((viewport_row & 0xf) << 4), 0x10, 0x10,
                                                 marker_bitmap_address + 6, g_game_context);
                    }
                }
                window_row = window_row + 1 & 0xff;
            } while (window_row < 0xf);
        }
    }
    return;
}

/* 原函数 0x81c02954 */
void sango_battle_show_overview(void)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define overview_text (*(char(*)[24])(abi_storage + 0))

    int unit_offset;
    uint32_t marker_color;
    uint32_t exit_key;
    char visible_side;
    uint32_t input_or_count;
    uint32_t map_left;
    uint32_t map_top;
    uint32_t first_unit;
    uint32_t selected_side;

    sango_display_fill_gray_rectangle(0, 0, 0xef, 0x13f, 0, 0);
    map_left = (int)(0x78 - (uint32_t)g_battle_map_width) / 2 & 0xff;
    map_top = (int)(0x140 - (uint32_t)g_battle_map_height) / 2 + 0x14U & 0xff;
    sango_battle_load_overview_text(0x31, overview_text);
    sango_text_draw_legacy(5, 3, overview_text);
    sango_battle_load_overview_text(0x30, overview_text);
    sango_format_integer((uint32_t)g_battle_day, overview_text + 3, 10);
    uint32_t text_length = bbk_strlen(overview_text);
    overview_text[text_length] = ' ';
    sango_text_draw_legacy(5, 0x11, overview_text);
    sango_battle_load_overview_text(0x36, overview_text);
    sango_text_draw_legacy(0x24, (short)map_top - 0xf, overview_text);
    sango_battle_draw_overview_rows('\x01', 0);
    marker_color = 3;
    sango_display_draw_rectangle((short)map_left + -1, (short)map_top + -1,
                                 (short)((g_battle_map_width + map_left) * 0x10000 >> 0x10),
                                 (short)((g_battle_map_height + map_top) * 0x10000 >> 0x10), 3, 0,
                                 0);
    selected_side = 1;
    first_unit = 0;
    do
    {
        do
        {
            input_or_count = 0;
            do
            {
                unit_offset = input_or_count * 7;
                if ((&g_first_unit_status)[unit_offset] != '\b')
                {
                    sango_display_put_gray_pixel(
                        (short)(((uint8_t)(&g_first_unit_x)[unit_offset] + map_left) * 0x10000 >>
                                0x10),
                        (short)(((uint8_t)(&g_first_unit_y)[unit_offset] + map_top) * 0x10000 >>
                                0x10),
                        marker_color, 0);
                    sango_display_put_gray_pixel(
                        (short)(((uint8_t)(&g_first_unit_x)[unit_offset] + map_left) * 0x10000 >>
                                0x10),
                        (short)(((uint8_t)(&g_first_unit_y)[unit_offset] + map_top) * 0x10000 >>
                                0x10),
                        marker_color, 0);
                }
                input_or_count = input_or_count + 1 & 0xff;
            } while (input_or_count < 0x14);
            if (marker_color != 3)
            {
                marker_color = 0;
            }
            input_or_count = sango_input_wait(0x32, '\x01');
        } while (input_or_count == 0);
        visible_side = (char)selected_side;
        if (input_or_count == 0x67)
        {
            input_or_count = first_unit - 0x18;
            if (first_unit == 0)
                goto draw_unit_list;
        change_list_offset:
            first_unit = input_or_count & 0xff;
        refresh_selected_side:
            visible_side = (char)selected_side;
        }
        else
        {
            if ((int)input_or_count < 0x68)
            {
                if (input_or_count != 0xb)
                {
                    exit_key = 0x1c;
                    if ((int)input_or_count < 0xc)
                    {
                        exit_key = 1;
                    }
                    if (input_or_count != exit_key)
                        goto refresh_selected_side;
                }
                return;
            }
            if (0x68 < (int)input_or_count)
            {
                if ((int)input_or_count < 0x6b)
                {
                    selected_side = (uint32_t)(selected_side == 0);
                    first_unit = 0;
                    goto refresh_selected_side;
                }
                if (((input_or_count == 0x6c) &&
                     (input_or_count = sango_battle_count_active_units(selected_side),
                      0x17 < input_or_count)) &&
                    (input_or_count = sango_battle_count_active_units(selected_side),
                     (int)first_unit < (int)(input_or_count - 0x18)))
                {
                    input_or_count = first_unit + 0x18;
                    goto change_list_offset;
                }
            }
        }
    draw_unit_list:
        sango_battle_draw_overview_rows(visible_side, first_unit);
    } while (true);
}
#undef overview_text

/* 原函数 0x81c02c4c */
void sango_battle_draw_overview_rows(char side, uint32_t first_row)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define message_start (*(char(*)[5])(abi_storage + 0))
#define food_text_start (*(uint8_t(*)[3])(abi_storage + 5))
#define troop_text_start (*(uint8_t(*)[16])(abi_storage + 8))

    uint16_t troops;
    uint8_t index;
    uint32_t character_or_text_value;
    char *message_suffix;
    uint32_t visible_row;
    uint32_t first_unit;
    uint32_t side_begin;

    side_begin = (uint32_t)(uint8_t)side * 10 & 0xff;
    sango_display_fill_gray_rectangle(0x78, 0, 0xef, 0x13f, 0, 0);
    sango_display_draw_rectangle(0x78, 0, 0xef, 0x13f, 3, 0, 0);
    sango_display_draw_line(0x78, 0xe, 0xef, 0xe, 3, 0, 0);
    sango_display_draw_line(0x78, 0x1c, 0xef, 0x1c, 3, 0, 0);
    character_or_text_value = sango_battle_is_player_unit(side_begin);
    sango_load_named_text(
        *(char *)(character_or_text_value * 0x10 + g_character_table_address + 1) + 0xff,
        message_start);
    character_or_text_value = bbk_strlen(message_start);
    message_suffix = message_start + (character_or_text_value & 0xff);
    *message_suffix = ' ';
    sango_battle_load_overview_text(0x32, message_suffix);
    sango_text_draw_legacy((short)(character_or_text_value & 0xff) * -3 - 0x52U & 0xff, 2,
                           message_start);
    sango_battle_load_overview_text(0x34, message_start);
    if (side == '\0')
    {
        character_or_text_value = (uint32_t)g_battle_attacker_food;
    }
    else
    {
        character_or_text_value = (uint32_t)g_battle_recon_food;
        if (character_or_text_value == 0)
        {
            sango_battle_load_overview_text(0x35, food_text_start);
            goto draw_food_and_units;
        }
    }
    sango_format_integer(character_or_text_value, food_text_start, 10);
draw_food_and_units:
    sango_text_draw_legacy(0x7b, 0x10, message_start);
    first_unit = (first_row & 0xff) + side_begin & 0xff;
    visible_row = 0;
    character_or_text_value = first_unit;
    while (true)
    {
        if (10 < (int)((character_or_text_value & 0xff) - side_begin))
        {
            return;
        }
        index = (&g_battle_roster_first)[character_or_text_value & 0xff] - 1;
        if ((&g_battle_roster_first)[character_or_text_value & 0xff] == '\0')
            break;
        troops = *(uint16_t *)((uint32_t)index * 0x10 + g_character_table_address + 10);
        sango_load_named_text(index, message_start);
        character_or_text_value = bbk_strlen(message_start);
        sango_memory_fill(message_start + (character_or_text_value & 0xff), 0x20,
                          0x14 - (character_or_text_value & 0xff));
        sango_format_integer((uint32_t)troops, troop_text_start, 10);
        sango_text_draw_legacy(0x7b, (short)visible_row * 0xc + 0x1e, message_start);
        visible_row = visible_row + 1 & 0xff;
        character_or_text_value = visible_row + first_unit;
        if (0x17 < visible_row)
        {
            return;
        }
    }
    return;
}
#undef message_start
#undef food_text_start
#undef troop_text_start

/* 原函数 0x81c02ec0 */
uint32_t sango_battle_count_active_units(uint32_t side)
{
    uint32_t unit_count;

    unit_count = 0;
    do
    {
        if ((&g_battle_roster_first)[unit_count + ((side & 0xff) * 10 & 0xff)] == '\0')
        {
            return unit_count;
        }
        unit_count = unit_count + 1 & 0xff;
    } while (unit_count < 10);
    return unit_count;
}

/* 原函数 0x81c02f08 */
void sango_battle_load_overview_text(uint32_t text_id, void *destination)
{
    sango_resource_read_text(1, text_id & 0xff, destination);
    return;
}

/* 原函数 0x81c02f30 */
uint32_t sango_battle_is_player_unit(uint32_t unit_id)
{
    return (uint8_t)(&g_battle_roster_first)[unit_id & 0xff] - 1 & 0xff;
}

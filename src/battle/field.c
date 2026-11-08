#include "sango_internal.h"

/* 战场初始化、日更新与地图绘制。 */

/* 原函数 0x81c03c98 */
uint32_t sango_battle_initialize_field(void)
{
    int unit_offset;
    char defense_origin_y;
    char defense_origin_x;
    uint8_t *map;
    uint32_t scan_width_or_second_formation;
    uint32_t spawn_x;
    uint32_t spawn_y;
    uint32_t load_failed;
    char *first_formation_entry;
    char *second_formation_entry;
    uint32_t tile_index;
    int formation_entry_offset;
    char second_side_y;
    char second_side_x;
    char first_side_y;
    char first_side_x;

    map = (uint8_t *)sango_battle_resource_item((uint32_t)g_battle_map_resource, '\x01');
    if (map == (uint8_t *)0x0)
    {
        g_battle_load_failed = 1;
        load_failed = 1;
    }
    else
    {
        g_battle_map_width = *map;
        g_battle_map_height = map[2];
        g_battle_tileset_resource = 4;
        tile_index = 0;
        if (map[0x10] != 3)
        {
            scan_width_or_second_formation = 1;
            do
            {
                tile_index = scan_width_or_second_formation & 0xffff;
                scan_width_or_second_formation = tile_index + 1;
            } while ((map + 0x10)[tile_index] != 3);
        }
        scan_width_or_second_formation = (uint32_t)g_battle_map_width;
        if (scan_width_or_second_formation == 0)
        {
            sango_legacy_trap(7);
        }
        g_battle_spawn_x_view2 = (char)(tile_index % scan_width_or_second_formation);
        defense_origin_x = g_battle_spawn_x_view2 + -2;
        g_battle_spawn_y_view2 = (char)(tile_index / scan_width_or_second_formation);
        defense_origin_y = g_battle_spawn_y_view2 + -2;
        spawn_x = sango_battle_spawn_origin('x');
        spawn_y = sango_battle_spawn_origin('y');
        tile_index = 8;
        scan_width_or_second_formation = (uint32_t)g_battle_entry_direction;
        first_side_x = defense_origin_x;
        first_side_y = defense_origin_y;
        second_side_x = (char)spawn_x;
        second_side_y = (char)spawn_y;
        if (g_battle_control_mode == '\x01')
        {
            scan_width_or_second_formation = 8;
            tile_index = (uint32_t)g_battle_entry_direction;
            first_side_x = (char)spawn_x;
            first_side_y = (char)spawn_y;
            second_side_x = defense_origin_x;
            second_side_y = defense_origin_y;
        }
        spawn_x = sango_battle_resource_item(2, '\x05');
        spawn_y = 0;
        do
        {
            formation_entry_offset = (spawn_y & 0x7f) * 2;
            first_formation_entry = (char *)(spawn_x + tile_index * 0x14 + formation_entry_offset);
            unit_offset = spawn_y * 7;
            (&g_first_unit_x)[unit_offset] = *first_formation_entry + first_side_x;
            second_formation_entry =
                (char *)(spawn_x + scan_width_or_second_formation * 0x14 + formation_entry_offset);
            (&g_first_unit_y)[unit_offset] = first_formation_entry[1] + first_side_y;
            spawn_y = spawn_y + 1 & 0xff;
            (&g_second_side_first_x)[unit_offset] = second_side_x + *second_formation_entry;
            (&g_second_side_first_y)[unit_offset] = second_side_y + second_formation_entry[1];
        } while (spawn_y < 10);
        load_failed = 0;
    }
    return load_failed;
}

/* 原函数 0x81c03ea8 */
uint32_t sango_battle_spawn_origin(char axis)
{
    uint32_t origin_x;
    uint32_t origin_y;

    origin_x = g_battle_map_width - 5 & 0xff;
    origin_y = g_battle_map_height - 5 & 0xff;
    switch (g_battle_entry_direction)
    {
    case 0:
        origin_x = (g_battle_map_width >> 1) - 2 & 0xff;
        goto use_top_edge;
    case 1:
        origin_y = 2;
        break;
    case 2:
        origin_y = (g_battle_map_height >> 1) - 2 & 0xff;
        break;
    case 4:
        origin_x = (g_battle_map_width >> 1) - 2 & 0xff;
        break;
    case 6:
        origin_y = (g_battle_map_height >> 1) - 2 & 0xff;
    case 5:
        origin_x = 2;
        break;
    case 7:
        origin_x = 0;
    use_top_edge:
        origin_y = 0;
    }
    if (axis != 'x')
    {
        origin_x = origin_y;
    }
    return origin_x;
}

/* 原函数 0x81c03f6c */
void sango_battle_draw_hud(void)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define food_text (*(char(*)[16])(abi_storage + 0))

    uint32_t digit_count;

    sango_battle_draw_bitmap(8, 1, 0, 0xf1);
    sango_format_integer((uint32_t)g_battle_attacker_food, food_text, 10);
    digit_count = sango_crt_strlen(food_text);
    sango_text_draw_padded_number(0xe, 0xf4, (uint32_t)g_battle_attacker_food, digit_count & 0xff,
                                  g_game_context_view2);
    sango_battle_draw_bitmap(9, (uint32_t)g_battle_weather, 0x4b, 0xf3);
    sango_battle_toolbar_draw(g_game_context_view2);
    return;
}
#undef food_text

/* 原函数 0x81c03ff8 */
uint32_t sango_battle_target_side_allowed(void)
{
    uint32_t template_x;
    uint32_t template_width;
    uint32_t template_y;
    uint32_t inside_template;

    inside_template = 0;
    template_width = (uint32_t)*g_temp_character_ids_address;
    template_y = (uint32_t)g_battle_cursor_y - (uint32_t)g_temp_character_ids_address[2] & 0xff;
    template_x = (uint32_t)g_battle_cursor_x - (uint32_t)g_temp_character_ids_address[1] & 0xff;
    if ((template_y < template_width) && (template_x < template_width))
    {
        inside_template =
            (uint32_t)(g_temp_character_ids_address[template_x + template_y * template_width + 3] ==
                       1);
    }
    return inside_template;
}

/* 原函数 0x81c04064 */
/* 推进战斗天数，处理粮草/状态及已修复的居中弹窗。 */
void sango_battle_advance_day(void)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define food_exhausted_text (*(char(*)[32])(abi_storage + 8))

    int unit_stride_base;
    uint32_t unit_or_food_text_id;

    g_battle_day = g_battle_day + 1;
    g_battle_recon_food = 0;
    unit_or_food_text_id = 0;
    if (g_battle_day < 0x1f)
    {
        unit_stride_base = 0;
        do
        {
            unit_stride_base = unit_stride_base - unit_or_food_text_id;
            unit_or_food_text_id = unit_or_food_text_id + 1 & 0xff;
            (&g_first_unit_has_acted)[unit_stride_base] = 0;
            unit_stride_base = unit_or_food_text_id << 3;
        } while (unit_or_food_text_id < 0x14);
        sango_battle_change_weather();
        sango_battle_day_popup_draw((uint32_t)g_battle_day);
        sango_input_wait(0x32, '\0');
        if (g_battle_defender_food_view2 == 0)
        {
            g_battle_result = '\x01';
            unit_or_food_text_id = 0x26;
        }
        if (g_battle_attacker_food_view2 == 0)
        {
            g_battle_result = '\x02';
            unit_or_food_text_id = 0x25;
        }
        if (g_battle_result != '\0')
        {
            sango_battle_load_text(unit_or_food_text_id, food_exhausted_text);
            sango_ui_show_message(food_exhausted_text, 1);
        }
        sango_battle_tick_unit_statuses();
    }
    else if (g_battle_control_mode == '\x01')
    {
        g_battle_result = '\x02';
    }
    else
    {
        g_battle_result = '\x01';
    }
    return;
}
#undef food_exhausted_text

/* 原函数 0x81c041f8 */
void sango_battle_scroll_viewport(char suppress_scroll)
{
    uint8_t next_viewport_x;
    uint8_t next_viewport_y;

    if (suppress_scroll != '\0')
    {
        return;
    }
    next_viewport_x = g_battle_viewport_x - 1;
    next_viewport_y = g_battle_viewport_y;
    if ((uint32_t)g_battle_viewport_x <= (uint32_t)g_battle_cursor_x)
    {
        if ((uint32_t)g_battle_cursor_y < (uint32_t)g_battle_viewport_y)
        {
            next_viewport_x = g_battle_viewport_x;
            next_viewport_y = g_battle_viewport_y - 1;
        }
        else
        {
            next_viewport_x = g_battle_viewport_x + 1;
            if (((uint32_t)g_battle_cursor_x < g_battle_viewport_x + 0xf) &&
                (next_viewport_x = g_battle_viewport_x, next_viewport_y = g_battle_viewport_y + 1,
                 (uint32_t)g_battle_cursor_y < g_battle_viewport_y + 0xf))
                goto redraw_status;
        }
    }
    g_battle_viewport_y = next_viewport_y;
    g_battle_viewport_x = next_viewport_x;
    sango_battle_draw_terrain((uint32_t)g_battle_viewport_x, (uint32_t)g_battle_viewport_y);
redraw_status:
    sango_battle_draw_hud();
    sango_battle_draw_cursor_description();
    return;
}

/* 原函数 0x81c042c4 */
void sango_battle_tick_unit_statuses(void)
{
    bool recovery_roll_passed;
    bool status_changed;
    uint32_t character_or_random_roll;
    uint32_t unit_index;
    char unit_status;
    int character_address;
    uint16_t remaining_troops;
    int unit_stride_base;
    uint32_t troops_lost;

    if (g_battle_result != '\0')
    {
        return;
    }
    unit_index = 0;
    unit_stride_base = 0;
check_unit_status:
    unit_status = (&g_first_unit_status)[unit_stride_base - unit_index];
    if (unit_status != '\b')
    {
        character_or_random_roll = sango_battle_unit_character(unit_index);
        troops_lost = 0;
        character_address = g_character_table_address + character_or_random_roll * 0x10;
        character_or_random_roll = bbk_rand();
        remaining_troops = *(uint16_t *)(character_address + 10);
        status_changed = false;
        recovery_roll_passed = (int)character_or_random_roll % 0x3c <
                               (int)(uint32_t)(*(uint8_t *)(character_address + 4) >> 1);
        switch (unit_status)
        {
        default:
            break;
        case '\x01':
        case '\x02':
        case '\x03':
            goto check_status_recovery;
        case '\x04':
        case '\a':
            if (!recovery_roll_passed)
                goto clear_unit_status;
            goto next_unit;
        case '\x06':
            goto apply_troop_attrition;
        }
    }
advance_unchanged_unit:
next_unit:
    unit_index = unit_index + 1 & 0xff;
    unit_stride_base = unit_index << 3;
    if (0x13 < unit_index)
    {
        return;
    }
    goto check_unit_status;
apply_troop_attrition:
    troops_lost = (uint32_t)(remaining_troops >> 3);
    remaining_troops = remaining_troops - (remaining_troops >> 3);
check_status_recovery:
    if (recovery_roll_passed)
    {
        sango_battle_remove_unit_status(unit_index);
    clear_unit_status:
        unit_status = '\0';
        status_changed = true;
    }
    if (troops_lost != 0)
    {
        sango_battle_redraw_field(unit_index);
        sango_battle_show_unit_delta('-', unit_index, troops_lost);
        *(uint16_t *)(character_address + 10) = remaining_troops;
    }
    if (!status_changed)
        goto advance_unchanged_unit;
    (&g_first_unit_status)[unit_stride_base - unit_index] = unit_status;
    sango_battle_redraw_field(unit_index);
    sango_battle_blink_unit(unit_index, 4);
    goto next_unit;
}

/* 原函数 0x81c04468 */
void sango_battle_redraw_field(uint32_t unit_id)
{
    int unit_offset;
    uint32_t viewport_x;
    uint32_t viewport_y;

    unit_offset = (unit_id & 0xff) * 7;
    g_battle_cursor_x = (&g_first_unit_x)[unit_offset];
    g_battle_cursor_y = (&g_first_unit_y)[unit_offset];
    viewport_x = 0;
    if (6 < g_battle_cursor_x)
    {
        viewport_x = g_battle_cursor_x - 7 & 0xffff;
    }
    viewport_y = 0;
    if (4 < g_battle_cursor_y)
    {
        viewport_y = g_battle_cursor_y - 5 & 0xffff;
    }
    sango_battle_draw_terrain(viewport_x, viewport_y);
    sango_battle_draw_units(0);
    sango_battle_draw_cursor_description();
    sango_battle_present();
    return;
}

/* 原函数 0x81c044f8 */
void sango_battle_show_unit_delta(char sign, uint32_t unit_id, uint32_t amount)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define amount_text (*(uint8_t(*)[15])(abi_storage + 1))
#define message_sign (*(char *)(abi_storage + 0))

    int unit_offset;

    message_sign = sign;
    sango_format_integer(amount & 0xffff, amount_text, 10);
    unit_offset = (unit_id & 0xff) * 7;
    sango_text_draw_legacy(
        ((uint16_t)(uint8_t)(&g_first_unit_x)[unit_offset] - (uint16_t)g_battle_viewport_x) * 0x10 &
            0xff,
        ((uint16_t)(uint8_t)(&g_first_unit_y)[unit_offset] - (uint16_t)g_battle_viewport_y) * 0x10 &
            0xff,
        &message_sign);
    sango_input_wait(0x32, '\0');
    return;
}
#undef amount_text
#undef message_sign

/* 原函数 0x81c04590 */
void sango_battle_blink_unit(uint32_t unit_id, uint8_t blink_count)
{
    int unit_offset;
    uint8_t blink_index;

    sango_battle_draw_units(0);
    unit_offset = (unit_id & 0xff) * 7;
    blink_index = 1;
    while (true)
    {
        sango_battle_present();
        if (blink_count < blink_index)
            break;
        sango_input_wait(10, '\0');
        sango_battle_draw_tile((uint32_t)(uint8_t)(&g_first_unit_x)[unit_offset],
                               (uint32_t)(uint8_t)(&g_first_unit_y)[unit_offset], '\x01');
        sango_input_wait(10, '\0');
        blink_index = blink_index + 1;
    }
    return;
}

/* 原函数 0x81c04630 */
void sango_battle_draw_units(uint32_t animation_phase)
{
    char unit_status;
    uint8_t map_y;
    uint32_t sprite_frame;
    int unit_offset_or_status_frame;
    short screen_y;
    uint32_t screen_x;
    uint32_t map_x;
    uint32_t unit_index;
    uint32_t unit_y;

    unit_index = 0;
    do
    {
        unit_offset_or_status_frame = unit_index * 7;
        unit_status = (&g_first_unit_status)[unit_offset_or_status_frame];
        if (unit_status != '\b')
        {
            map_x = (uint32_t)(uint8_t)(&g_first_unit_x)[unit_offset_or_status_frame];
            map_y = (&g_first_unit_y)[unit_offset_or_status_frame];
            unit_y = (uint32_t)map_y;
            if ((((g_battle_viewport_x <= map_x) && (map_x < g_battle_viewport_x + 0xf)) &&
                 (g_battle_viewport_y <= unit_y)) &&
                (unit_y < g_battle_viewport_y + 0xf))
            {
                sprite_frame = sango_battle_unit_sprite_frame(unit_index);
                if ((&g_first_unit_has_acted)[unit_offset_or_status_frame] == '\0')
                {
                    sprite_frame = sprite_frame + (animation_phase & 0xff) & 0xff;
                }
                screen_y = ((uint16_t)map_y - (uint16_t)g_battle_viewport_y) * 0x10;
                screen_x = (map_x - g_battle_viewport_x) * 0x10 & 0xffff;
                sango_battle_draw_tile(map_x, unit_y, '\0');
                sango_battle_draw_bitmap(5, sprite_frame + 1 & 0xff, screen_x, screen_y);
                unit_offset_or_status_frame = 2;
                if ((unit_status == '\x02') ||
                    (unit_offset_or_status_frame = 4, unit_status == '\x03'))
                {
                    sango_battle_draw_bitmap(
                        0x22, unit_offset_or_status_frame + (animation_phase & 0xff) + 1 & 0xff,
                        screen_x, screen_y);
                }
            }
        }
        unit_index = unit_index + 1 & 0xff;
    } while (unit_index < 0x14);
    return;
}

/* 原函数 0x81c047bc */
void sango_battle_draw_tile(uint32_t map_x, uint32_t map_y, char draw_to_screen)
{
    uint8_t tile_id;
    uint32_t tileset_address;
    int pixel_data_address;
    uint16_t screen_y;
    uint32_t screen_x;

    tile_id =
        *(uint8_t *)(g_viewport_tiles_address +
                     ((((map_y & 0xff) - (uint32_t)g_battle_viewport_y) * 0xf + (map_x & 0xff)) -
                          (uint32_t)g_battle_viewport_x &
                      0xff));
    tileset_address = sango_battle_resource_item((uint32_t)g_battle_tileset_resource, '\x01');
    screen_x = ((map_x & 0xff) - (uint32_t)g_battle_viewport_x) * 0x10 & 0xff;
    screen_y = ((short)(map_y & 0xff) - (uint16_t)g_battle_viewport_y) * 0x10 & 0xff;
    pixel_data_address = tileset_address + (uint32_t)tile_id * 0x40 + 6;
    if (draw_to_screen == '\0')
    {
        sango_raster_draw_opaque(screen_x, screen_y, 0x10, 0x10, pixel_data_address,
                                 g_game_context);
    }
    else
    {
        sango_raster_draw_screen(screen_x, screen_y, 0x10, 0x10, pixel_data_address);
    }
    return;
}

/* 原函数 0x81c048bc */
void sango_battle_show_action_message(uint32_t experience_gain)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define message (*(char(*)[24])(abi_storage + 0))
#define amount_text (*(char(*)[8])(abi_storage + 24))

    sango_battle_load_text(0x16, message);
    sango_format_integer(experience_gain & 0xff, amount_text, 10);
    sango_crt_strcat(message, amount_text);
    sango_battle_show_short_message(message, 1, 0xff);
    return;
}
#undef message
#undef amount_text

/* 原函数 0x81c04920 */
void sango_battle_check_level_and_retreat(void)
{
    uint8_t unit_x;
    uint8_t unit_y;
    char unit_life;
    int unit_offset;
    char *message;
    uint8_t new_level;
    uint32_t character_id;
    uint32_t message_variant;
    int character_address;
    uint32_t unit_index;

    message = g_scratch_buffer_address;
    unit_index = 0;
    do
    {
        unit_offset = unit_index * 7;
        if ((&g_first_unit_status)[unit_offset] != '\b')
        {
            character_id = sango_battle_unit_character(unit_index);
            unit_x = (&g_first_unit_x)[unit_offset];
            unit_y = (&g_first_unit_y)[unit_offset];
            character_address = g_character_table_address + character_id * 0x10;
            message_variant = bbk_rand();
            message_variant = (int)message_variant % 3 & 0xff;
            if (*(uint8_t *)(character_address + 7) < 100)
            {
                unit_life = (&g_first_unit_life)[unit_offset];
            }
            else
            {
                sango_battle_redraw_field(unit_index);
                new_level = *(char *)(character_address + 2) + 1;
                *(char *)(character_address + 7) = *(char *)(character_address + 7) + -100;
                *(uint8_t *)(character_address + 2) = new_level;
                if (0x14 < new_level)
                {
                    *(uint8_t *)(character_address + 2) = 0x14;
                }
                sango_battle_play_unit_effect(0, 5, (uint16_t)unit_x, (uint16_t)unit_y);
                sango_battle_load_text(message_variant + 0x27 & 0xff, message);
                sango_ui_show_character_message((uint8_t)character_id, message);
                unit_life = (&g_first_unit_life)[unit_offset];
            }
            if ((unit_life == '\0') || (*(short *)(character_address + 10) == 0))
            {
                sango_battle_redraw_field(unit_index);
                (&g_first_unit_status)[unit_offset] = 8;
                sango_battle_play_unit_effect(6, 0xb, (uint16_t)unit_x, (uint16_t)unit_y);
                sango_battle_load_text(message_variant + 0x2a & 0xff, message);
                sango_ui_show_character_message((uint8_t)character_id, message);
            }
        }
        unit_index = unit_index + 1 & 0xff;
    } while (unit_index < 0x14);
    return;
}

/* 原函数 0x81c04ae8 */
void sango_battle_play_unit_effect(uint32_t first_command, uint32_t last_command, uint16_t map_x,
                                   uint16_t map_y)
{
    uint16_t viewport_x;
    uint16_t viewport_y;

    viewport_x = (uint16_t)g_battle_viewport_x;
    if ((viewport_x <= map_x) && (map_x < (uint16_t)(viewport_x + 0xf)))
    {
        viewport_y = (uint16_t)g_battle_viewport_y;
        if (viewport_y <= map_y)
        {
            if (map_y < (uint16_t)(viewport_y + 0xf))
            {
                sango_animation_play_range(0x1b, first_command & 0xff, last_command & 0xff, 0,
                                           (map_x - viewport_x) * 0x10,
                                           (map_y - viewport_y) * 0x10);
            }
        }
    }
    return;
}

/* 原函数 0x81c04b9c */
void sango_battle_draw_terrain(uint32_t view_x, uint32_t view_y)
{
    uint32_t tileset;
    uint32_t tile_index;
    uint32_t row_product;

    sango_battle_copy_viewport_tiles(view_x & 0xffff, view_y & 0xffff);
    tileset = sango_battle_resource_item((uint32_t)g_battle_tileset_resource, '\x01');
    tile_index = 0;
    row_product = 0;
    do
    {
        sango_raster_draw_opaque(
            (tile_index + (row_product >> 3) * -0xf) * 0x10 & 0xffff,
            (short)(row_product >> 3) * 0x10, 0x10, 0x10,
            tileset + 6 + (uint32_t) * (uint8_t *)(g_viewport_tiles_address + tile_index) * 0x40,
            g_game_context);
        tile_index = tile_index + 1 & 0xffff;
        row_product = (uint32_t)((uint64_t)tile_index * 0x88888889 >> 0x20);
    } while (tile_index < 0xe1);
    return;
}

/* 原函数 0x81c04c60 */
void sango_battle_copy_viewport_tiles(uint32_t requested_x, uint32_t requested_y)
{
    uint32_t map;
    uint8_t row;
    void *source_row;
    void *target_row;
    uint32_t view_y;
    uint32_t view_x;

    view_x = requested_x & 0xffff;
    view_y = requested_y & 0xffff;
    if ((uint32_t)g_battle_map_width < view_x + 0xf)
    {
        view_x = g_battle_map_width - 0xf & 0xffff;
    }
    if ((uint32_t)g_battle_map_height < view_y + 0xf)
    {
        view_y = g_battle_map_height - 0xf & 0xffff;
    }
    g_battle_viewport_y = (uint8_t)view_y;
    g_battle_viewport_x = (uint8_t)view_x;
    map = sango_battle_resource_item((uint32_t)g_battle_map_resource, '\x01');
    row = 0;
    source_row = (void *)(view_y * g_battle_map_width + map + 0x10 + view_x);
    target_row = g_viewport_tiles_address_view2;
    do
    {
        bbk_memcpy(target_row, source_row, 0xf);
        row = row + 1;
        source_row = (void *)((int)source_row + (uint32_t)g_battle_map_width);
        target_row = (void *)((int)target_row + 0xf);
    } while (row < 0xf);
    return;
}

/* 原函数 0x81c04d58 */
void sango_battle_draw_cursor_description(void)
{
    unsigned char abi_storage[61] __attribute__((aligned(8)));
#define terrain_names (*(uint8_t(*)[40])(abi_storage + 0))
#define description (*(char(*)[4])(abi_storage + 40))
#define terminator (*(uint8_t *)(abi_storage + 44))

    uint32_t unit_or_terrain;

    sango_render_clear_rectangle(0x6a, 0xf3, 0x9a, 0xff, g_game_context);
    unit_or_terrain =
        sango_battle_find_unit_at((uint16_t)g_battle_cursor_x, (uint16_t)g_battle_cursor_y);
    if (unit_or_terrain == 0xff)
    {
        unit_or_terrain =
            sango_battle_terrain_at((uint32_t)g_battle_cursor_x, (uint32_t)g_battle_cursor_y);
        sango_battle_load_text(7, terrain_names);
        bbk_memcpy(description, terrain_names + (unit_or_terrain & 0x3f) * 4, 4);
        terminator = 0;
    }
    else
    {
        unit_or_terrain = sango_battle_unit_character(unit_or_terrain);
        sango_load_named_text((uint8_t)unit_or_terrain, description);
    }
    sango_battle_draw_text(0x6a, 0xf3, description);
    return;
}
#undef terrain_names
#undef description
#undef terminator

/* 原函数 0x81c04e34 */
void sango_battle_check_finish(char active_side)
{
    int unit_offset;
    uint32_t unit_index;

    if (g_battle_result == '\0')
    {
        if ((&g_first_unit_status)[(uint32_t)g_battle_player_unit_begin * 7] == '\b')
        {
            g_battle_result = 1;
            if (g_battle_player_unit_begin != 10)
            {
                g_battle_result = 2;
            }
            return;
        }
        if (active_side == '\0')
        {
            g_battle_result = '\x01';
            unit_index = 10;
        }
        else
        {
            unit_index = 0;
            g_battle_result = '\x02';
        }
        if (unit_index < 0x14)
        {
            while (true)
            {
                unit_offset = unit_index * 7;
                unit_index = unit_index + 1 & 0xff;
                if ((&g_first_unit_status)[unit_offset] != '\b')
                    break;
                if (0x13 < unit_index)
                {
                    return;
                }
            }
            g_battle_result = '\0';
        }
    }
    return;
}

/* 原函数 0x81c04efc */
uint32_t sango_battle_unit_character(uint32_t unit_id)
{
    return (uint8_t)(&g_battle_roster_first)[unit_id & 0xff] - 1 & 0xff;
}

/* 原函数 0x81c04f18 */
void sango_battle_load_text(uint32_t text_id, void *output)
{
    sango_resource_read_text(1, text_id & 0xff, output);
    return;
}

/* 原函数 0x81c04f40 */
uint32_t sango_battle_resource_item(uint32_t resource_id, char item_number)
{
    uint32_t address;

    address = sango_resource_item(resource_id & 0xffff, item_number, g_resource_package_address);
    return address;
}

/* 原函数 0x81c04f68 */
void sango_battle_present(void)
{
    sango_render_present(g_game_context);
    return;
}

/* 原函数 0x81c04f8c */
void sango_battle_draw_text(short x, short y, char *text)
{
    sango_text_draw_context(x, y, text, g_game_context);
    return;
}

/* 原函数 0x81c04fb4 */
void sango_battle_draw_bitmap(uint32_t resource_id, uint32_t frame_number, uint32_t x, short y)
{
    sango_bitmap_draw_resource(resource_id & 0xffff, frame_number & 0xff, x & 0xffff, y, '\0');
    return;
}

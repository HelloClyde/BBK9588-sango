#include "sango_internal.h"

/* 战略地图、城市选择和归属查询。 */

/* 原函数 0x81c12b18 */
/* 战略城市选择循环；map_state包含视口与当前光标，城市返回值为0基索引。 */
uint32_t sango_strategy_select_city(uint8_t *map_state)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define event_kind (*(int *)(abi_storage + 0))
#define key_code (*(int *)(abi_storage + 4))

    bool redraw_map = true;
    bool showing_find_map = false;
    uint8_t scroll_mode = 0;
    uint32_t selected_city_plus_one;

    sango_render_clear_rectangle(0, 0, 0xef, 0x13f, g_game_context);
    while (true)
    {
        if (redraw_map && !showing_find_map)
        {
            selected_city_plus_one = sango_strategy_draw_map(map_state, scroll_mode);
            redraw_map = false;
            scroll_mode = 0;
        }

        sango_input_next_event(&event_kind);
        if ((event_kind != 5) && (event_kind != 0xb))
            continue;

        /* 任意按键或触摸先关闭查找图，不同时执行该输入的地图命令。 */
        if (showing_find_map)
        {
            showing_find_map = false;
            redraw_map = true;
            continue;
        }

        bool open_find_map = event_kind == 5 && key_code == 0x1f;
        if (event_kind == 0xb)
        {
            /* 直接读取完整16位坐标，旧全局坐标会把255之后的行截断。 */
            enum SangoStatusbarAction action = sango_statusbar_hit(*(uint16_t *)(abi_storage + 8),
                                                                   *(uint16_t *)(abi_storage + 10));
            if (action == SANGO_STATUSBAR_INFO)
            {
                sango_ui_show_message(&g_legacy_data_81c20570, 2);
                sango_strategy_present();
            }
            if (action != SANGO_STATUSBAR_FIND)
                continue;
            open_find_map = true;
        }

        if (open_find_map)
        {
            sango_display_fill_gray_rectangle(0, 0, 0xef, 0x13f, 0, 0);
            uint8_t *find_map =
                (uint8_t *)sango_resource_item(0x4b, '\x01', g_resource_package_address);
            showing_find_map = true;
            /* 9588查找图为84×64，按资源描述居中，不套用9288S的160×160。 */
            uint16_t map_width = (uint16_t)(find_map[0] | (find_map[1] << 8));
            uint16_t map_height = (uint16_t)(find_map[2] | (find_map[3] << 8));
            sango_bitmap_draw_frame_screen((240 - map_width) / 2, (320 - map_height) / 2, map_width,
                                           map_height, 0, find_map);
            continue;
        }

        uint8_t previous_coordinate;
        switch (key_code)
        {
        case 1:
            return 0xff;
        case 0x1c:
            if (selected_city_plus_one != 0)
                return selected_city_plus_one - 1 & 0xff;
            continue;
        case 0x67: /* 上 */
            previous_coordinate = map_state[3];
            if (previous_coordinate == 0)
                continue;
            map_state[3] = previous_coordinate - 1;
            scroll_mode = 1;
            if (map_state[1] > (uint8_t)(previous_coordinate - 1))
            {
                map_state[1] = previous_coordinate - 1;
                scroll_mode = 0;
            }
            break;
        case 0x69: /* 左 */
            previous_coordinate = map_state[2];
            if (previous_coordinate == 0)
                continue;
            map_state[2] = previous_coordinate - 1;
            scroll_mode = 2;
            if (*map_state > (uint8_t)(previous_coordinate - 1))
            {
                *map_state = previous_coordinate - 1;
                scroll_mode = 0;
            }
            break;
        case 0x6a: /* 右 */
            previous_coordinate = map_state[2];
            if (previous_coordinate > 10)
                continue;
            map_state[2] = previous_coordinate + 1;
            scroll_mode = 4;
            if ((uint32_t)(uint8_t)(previous_coordinate + 1) >= *map_state + 7)
            {
                *map_state = previous_coordinate - 5;
                scroll_mode = 0;
            }
            break;
        case 0x6c: /* 下 */
            previous_coordinate = map_state[3];
            if (previous_coordinate > 7)
                continue;
            map_state[3] = previous_coordinate + 1;
            scroll_mode = 3;
            if ((uint32_t)(uint8_t)(previous_coordinate + 1) >= map_state[1] + 7)
            {
                map_state[1] = previous_coordinate - 5;
                scroll_mode = 0;
            }
            break;
        default:
            continue;
        }
        redraw_map = true;
    }
}
#undef event_kind
#undef key_code

/* 原函数 0x81c12e18 */
/* 绘制12列战略底图的7×7可见区域、城市归属图标及底部状态。 */
uint32_t sango_strategy_draw_map(uint8_t *map_state, uint8_t scroll_mode)
{
    int resource_address;
    uint8_t *bitmap;
    char *city_id_output;
    uint32_t tile_index;
    short tile_y;
    uint32_t tile_column;
    char *status_text;
    uint8_t city_marker_frame;
    uint32_t cursor_row;
    uint32_t cursor_column;
    uint32_t tile_row;
    char *text_part;

    resource_address = sango_resource_item(2, '\x0e', g_resource_package_address);
    uint32_t map_row = 0;
    uint32_t source_offset = (uint32_t)map_state[1] * 0xc + (uint32_t)*map_state;
    do
    {
        bbk_memcpy(&g_visible_city_ids + map_row * 7, (void *)(resource_address + source_offset),
                   7);
        map_row = map_row + 1 & 0xff;
        source_offset = source_offset + 0xc & 0xffff;
    } while (map_row < 7);
    cursor_row = (uint32_t)map_state[3] - (uint32_t)map_state[1] & 0xff;
    cursor_column = (uint32_t)map_state[2] - (uint32_t)*map_state & 0xff;
    resource_address = sango_resource_item(0x36, '\x01', g_resource_package_address);
    uint16_t footer_top = sango_color_strategy_map_begin(g_game_context) ? SANGO_STATUSBAR_TOP : 224;
    /* 全图重画或仅恢复光标离开的那一块，随后共用底栏绘制。 */
    if (scroll_mode == 0)
    {
        tile_row = 0;
        do
        {
            tile_column = 0;
            tile_index = ((tile_row + map_state[1]) * 0xc + (uint32_t)*map_state) * 0x100;
            do
            {
                sango_raster_draw_opaque(tile_column << 5, (short)(tile_row << 5), 0x20, 0x20,
                                         resource_address + 6 + (tile_index & 0xffff),
                                         g_game_context);
                tile_column = tile_column + 1 & 0xff;
                tile_index = (tile_index & 0xffff) + 0x100;
            } while (tile_column < 7);
            tile_row = tile_row + 1 & 0xff;
        } while (tile_row < 7);
        tile_row = 0;
        do
        {
            tile_index = 0;
            bitmap = &g_visible_city_ids + tile_row * 7;
            do
            {
                city_marker_frame = 8;
                if (*bitmap != 0)
                {
                    if (((uint32_t)(uint8_t)(&g_city_owner_one_based_view)[(uint32_t)*bitmap *
                                                                           0x24] !=
                         g_player_character + 1) &&
                        (city_marker_frame = 7,
                         (uint8_t)(&g_city_owner_one_based_view)[(uint32_t)*bitmap * 0x24] == 0))
                    {
                        city_marker_frame = 0;
                    }
                    bitmap =
                        (uint8_t *)sango_resource_item(0x37, '\x01', g_resource_package_address);
                    sango_bitmap_draw_frame((short)tile_index * 0x20 + 8,
                                            (short)tile_row * 0x20 + 8, 0x10, 0x10,
                                            city_marker_frame, bitmap, g_game_context);
                }
                tile_index = tile_index + 1 & 0xff;
                bitmap = &g_visible_city_ids + tile_row * 7 + tile_index;
            } while (tile_index < 7);
            tile_row = tile_row + 1 & 0xff;
        } while (tile_row < 7);
        goto draw_cursor_and_status;
    }
    tile_row = cursor_row;
    if (scroll_mode == 2)
    {
        tile_index = cursor_column + 1;
    restore_previous_column:
        tile_column = tile_index & 0xff;
    }
    else
    {
        tile_column = cursor_column;
        if (scroll_mode < 3)
        {
            tile_index = cursor_row + 1;
            if (scroll_mode == 1)
            {
            restore_previous_row:
                tile_row = tile_index & 0xff;
            }
        }
        else
        {
            tile_index = cursor_row - 1;
            if (scroll_mode == 3)
                goto restore_previous_row;
            tile_index = cursor_column - 1;
            if (scroll_mode == 4)
                goto restore_previous_column;
        }
    }
    tile_y = (short)tile_row * 0x20;
    sango_raster_draw_opaque(
        tile_column * 0x20, tile_y, 0x20, 0x20,
        resource_address + 6 +
            (((tile_row + map_state[1]) * 0xc + (uint32_t)*map_state + tile_column) * 0x100 &
             0xffff),
        g_game_context);
    if ((uint8_t)(&g_visible_city_ids)[tile_column + tile_row * 7] != 0)
    {
        city_marker_frame = 8;
        if (((uint32_t)(uint8_t)(&g_city_owner_one_based_view)
                 [(uint32_t)(uint8_t)(&g_visible_city_ids)[tile_column + tile_row * 7] * 0x24] !=
             g_player_character + 1) &&
            (city_marker_frame = 7,
             (uint8_t)(&g_city_owner_one_based_view)
                     [(uint32_t)(uint8_t)(&g_visible_city_ids)[tile_column + tile_row * 7] *
                      0x24] == 0))
        {
            city_marker_frame = 0;
        }
        bitmap = (uint8_t *)sango_resource_item(0x37, '\x01', g_resource_package_address);
        sango_bitmap_draw_frame((short)(tile_column * 0x20) + 8, tile_y + 8, 0x10, 0x10,
                                city_marker_frame, bitmap, g_game_context);
    }
draw_cursor_and_status:
    resource_address = sango_resource_item(0x38, '\x01', g_resource_package_address);
    sango_raster_draw_masked(cursor_column * 0x20 + 8, (short)cursor_row * 0x20 + 0x10, 0x10, 0x10,
                             resource_address + 6, g_game_context);
    text_part = (char *)(g_scratch_buffer_address + 0x154);
    status_text = (char *)(g_scratch_buffer_address + 300);
    sango_color_strategy_map_end();
    sango_render_clear_rectangle(0, footer_top, 0xef, 0x13f, g_game_context);
    sango_statusbar_draw(g_game_context);
    bitmap = (uint8_t *)sango_resource_item(g_scenario_id_view2 + 0x2f, '\x01',
                                            g_resource_package_address);
    sango_bitmap_draw_frame(0x15, 0x10f, 0x18, 0x18, g_player_character, bitmap, g_game_context);
    bitmap = (uint8_t *)sango_resource_item(0x45, '\x01', g_resource_package_address);
    sango_bitmap_draw_frame(0x35, 0x10f, 7, 9, 1, bitmap, g_game_context);
    uint32_t player_id = (uint32_t)g_player_character;
    uint32_t city_count = 0;
    uint32_t city_id = 0;
    int city_stride_factor = 0;
    do
    {
        city_id_output = status_text + city_count;
        if ((uint32_t)(uint8_t)(&g_first_city_owner)[(city_stride_factor + city_id) * 4] ==
            player_id + 1)
        {
            city_count = city_count + 1 & 0xff;
            *city_id_output = (char)city_id;
        }
        city_id = city_id + 1 & 0xff;
        city_stride_factor = city_id << 3;
    } while (city_id < 0x26);
    sango_format_integer(city_count, status_text, 10);
    sango_text_draw_context(0x3f, 0x10e, status_text, g_game_context);
    sango_bitmap_draw_frame(0x35, 0x11e, 7, 9, 0, bitmap, g_game_context);
    tile_row = sango_faction_count_characters((uint32_t)g_player_character);
    sango_format_integer(tile_row, status_text, 10);
    sango_text_draw_context(0x3f, 0x11c, status_text, g_game_context);
    sango_format_integer((uint32_t)g_current_year, status_text, 10);
    sango_resource_read_text(0x40, 0x3f, text_part);
    bbk_strcat(status_text, text_part);
    sango_text_draw_context(0x52, 0x10e, status_text, g_game_context);
    sango_format_integer((uint32_t)g_current_month, status_text, 10);
    sango_resource_read_text(0x40, 0x40, text_part);
    bbk_strcat(status_text, text_part);
    sango_text_draw_context(0x52, 0x11c, status_text, g_game_context);
    city_marker_frame = (&g_visible_city_ids)[cursor_column + cursor_row * 7];
    if (city_marker_frame != 0)
    {
        sango_city_read_name(city_marker_frame - 1, text_part);
        sango_text_draw_context(0x78, 0x115, text_part, g_game_context);
    }
    sango_battle_summary_remember(city_count, tile_row, city_marker_frame);
    sango_strategy_present();
    return (uint32_t)(uint8_t)(&g_visible_city_ids)[cursor_column + cursor_row * 7];
}

/* 原函数 0x81c13494 */
void sango_strategy_present(void)
{
    sango_render_present(g_game_context);
    return;
}

/* 原函数 0x81c134b8 */
uint32_t sango_city_add_character(uint32_t city_id, uint8_t character_id)
{
    uint8_t *previous_roster_entry;
    char previous_count;
    uint32_t inserted;
    uint8_t *destination_entry;
    uint32_t shift_index;
    uint32_t insert_position;
    uint32_t city_index;

    city_index = city_id & 0xff;
    inserted = 0;
    if ((city_index < 0x26) && (character_id < 200))
    {
        insert_position =
            (uint32_t)(uint8_t)(&g_first_city_character_start)[city_index * 0x24] +
                (uint32_t)(uint8_t)(&g_first_city_character_count)[city_index * 0x24] &
            0xff;
        shift_index = 199;
        if (insert_position < 199)
        {
            do
            {
                destination_entry = &g_city_character_roster + shift_index;
                previous_roster_entry = (uint8_t *)(shift_index + 0x81c2b30f);
                shift_index = shift_index - 1 & 0xff;
                *destination_entry = *previous_roster_entry;
            } while (insert_position < shift_index);
        }
        previous_count = (&g_first_city_character_count)[city_index * 0x24];
        (&g_city_character_roster)[insert_position] = character_id;
        (&g_first_city_character_count)[city_index * 0x24] = previous_count + '\x01';
        while (city_index = city_index + 1 & 0xff, city_index < 0x26)
        {
            (&g_first_city_character_start)[city_index * 0x24] =
                (&g_first_city_character_start)[city_index * 0x24] + '\x01';
        }
        inserted = 1;
    }
    return inserted;
}

/* 原函数 0x81c135a8 */
uint32_t sango_city_add_item(uint32_t city_id, uint8_t item_id)
{
    uint8_t *previous_roster_entry;
    char previous_count;
    uint32_t inserted;
    uint8_t *destination_entry;
    uint32_t shift_index;
    uint32_t insert_position;
    uint32_t city_index;

    city_index = city_id & 0xff;
    inserted = 0;
    if ((city_index < 0x26) && (item_id < 0x21))
    {
        insert_position = (uint32_t)(uint8_t)(&g_first_city_item_start)[city_index * 0x24] +
                              (uint32_t)(uint8_t)(&g_first_city_item_count)[city_index * 0x24] &
                          0xff;
        shift_index = 0x20;
        if (insert_position < 0x20)
        {
            do
            {
                destination_entry = &g_city_item_roster + shift_index;
                previous_roster_entry = (uint8_t *)(shift_index + 0x81c2b3df);
                shift_index = shift_index - 1 & 0xff;
                *destination_entry = *previous_roster_entry;
            } while (insert_position < shift_index);
        }
        previous_count = (&g_first_city_item_count)[city_index * 0x24];
        (&g_city_item_roster)[insert_position] = item_id;
        (&g_first_city_item_count)[city_index * 0x24] = previous_count + '\x01';
        while (city_index = city_index + 1 & 0xff, city_index < 0x26)
        {
            (&g_first_city_item_start)[city_index * 0x24] =
                (&g_first_city_item_start)[city_index * 0x24] + '\x01';
        }
        inserted = 1;
    }
    return inserted;
}

/* 原函数 0x81c13698 */
void sango_city_roster_noop(void)
{
    return;
}

/* 原函数 0x81c136a0 */
uint32_t sango_city_adjacent_distance(uint32_t source_city, uint8_t source_x, uint8_t source_y,
                                      uint32_t target_city, uint8_t target_x, uint8_t target_y)
{
    unsigned char abi_storage[21] __attribute__((aligned(8)));
    (*(uint8_t *)(abi_storage + 0)) = target_x;
    (*(uint8_t *)(abi_storage + 4)) = target_y;
#define target_x (*(uint8_t *)(abi_storage + 0))
#define target_y (*(uint8_t *)(abi_storage + 4))

    char distance_y;
    uint8_t distance;
    int neighbor_table_address;
    uint8_t *neighbor_entry;
    uint32_t direction_index;
    uint8_t *city_neighbors;

    neighbor_table_address = sango_resource_item(0x3b, '\x01', g_resource_package_address);
    city_neighbors = (uint8_t *)(neighbor_table_address + (source_city & 0xff) * 0x10);
    direction_index = 0;
    neighbor_entry = city_neighbors;
    do
    {
        if ((uint32_t)*neighbor_entry == (target_city & 0xff) + 1)
        {
            if (7 < direction_index)
            {
                return 0xff;
            }
            distance_y = source_y - target_y;
            if (source_y < target_y)
            {
                distance_y = target_y - source_y;
            }
            if (source_x < target_x)
            {
                distance = (distance_y + target_x) - source_x;
            }
            else
            {
                distance = (distance_y + source_x) - target_x;
            }
            return (uint32_t)distance;
        }
        direction_index = direction_index + 1 & 0xff;
        neighbor_entry = city_neighbors + direction_index;
    } while (direction_index < 8);
    return 0xff;
}
#undef target_x
#undef target_y

/* 原函数 0x81c13794 */
uint32_t sango_faction_list_cities(uint32_t ruler_id, int output_city_ids)
{
    uint8_t *destination_entry;
    uint32_t scanned_city;
    uint32_t city_count;

    city_count = 0;
    scanned_city = 0;
    do
    {
        destination_entry = (uint8_t *)(output_city_ids + city_count);
        if ((uint32_t)(uint8_t)(&g_first_city_owner)[scanned_city * 0x24] == (ruler_id & 0xff) + 1)
        {
            city_count = city_count + 1 & 0xff;
            *destination_entry = (char)scanned_city;
        }
        scanned_city = scanned_city + 1 & 0xff;
    } while (scanned_city < 0x26);
    return city_count;
}

/* 原函数 0x81c137f0 */
uint32_t sango_character_find_city(char character_id)
{
    char *roster_entry;
    uint32_t roster_position;
    uint8_t roster_index;
    uint32_t city_index;

    city_index = 0;
    do
    {
        roster_position = (uint32_t)(uint8_t)(&g_first_city_character_start)[city_index * 0x24];
        roster_index = 0;
        if ((&g_first_city_character_count)[city_index * 0x24] != 0)
        {
            do
            {
                roster_entry = &g_city_character_roster + roster_position;
                roster_index = roster_index + 1;
                roster_position = roster_position + 1 & 0xff;
                if (*roster_entry == character_id)
                {
                    return city_index;
                }
            } while (roster_index < (uint8_t)(&g_first_city_character_count)[city_index * 0x24]);
        }
        city_index = city_index + 1 & 0xff;
    } while (city_index < 0x26);
    return 0xff;
}

/* 原函数 0x81c13870 */
uint32_t sango_city_list_idle_characters(uint32_t city_id, int output_character_ids)
{
    int roster_position;
    uint8_t *destination_entry;
    int city_offset;
    uint32_t roster_index;
    uint32_t idle_count;

    city_offset = (city_id & 0xff) * 0x24;
    idle_count = 0;
    roster_index = 0;
    if ((&g_first_city_character_count)[city_offset] != '\0')
    {
        do
        {
            roster_position = roster_index + (uint8_t)(&g_first_city_character_start)[city_offset];
            roster_index = roster_index + 1 & 0xff;
            destination_entry = (uint8_t *)(output_character_ids + idle_count);
            if (*(char *)((uint32_t)(uint8_t)(&g_city_character_roster)[roster_position] * 0x10 +
                          g_character_table_address + 1) == (&g_first_city_owner)[city_offset])
            {
                idle_count = idle_count + 1 & 0xff;
                *destination_entry = (&g_city_character_roster)[roster_position];
            }
        } while (roster_index < (uint8_t)(&g_first_city_character_count)[city_offset]);
    }
    return idle_count;
}

/* 原函数 0x81c13918 */
uint32_t sango_city_list_available_characters(uint32_t city_id, int destination_address)
{
    int roster_position;
    int city_offset;
    uint8_t *destination_entry;
    uint32_t roster_index;
    uint32_t character_count;

    city_offset = (city_id & 0xff) * 0x24;
    character_count = 0;
    roster_index = 0;
    if ((&g_first_city_character_count)[city_offset] != '\0')
    {
        do
        {
            roster_position = roster_index + (uint8_t)(&g_first_city_character_start)[city_offset];
            roster_index = roster_index + 1 & 0xff;
            destination_entry = (uint8_t *)(destination_address + character_count);
            if (*(char *)((uint32_t)(uint8_t)(&g_city_character_roster)[roster_position] * 0x10 +
                          g_character_table_address + 1) == '\0')
            {
                character_count = character_count + 1 & 0xff;
                *destination_entry = (&g_city_character_roster)[roster_position];
            }
        } while (roster_index < (uint8_t)(&g_first_city_character_count)[city_offset]);
    }
    return character_count;
}

/* 原函数 0x81c139a8 */
uint32_t sango_city_list_captives(uint32_t city_id, int destination_address)
{
    int roster_position;
    int city_offset;
    uint8_t *destination_entry;
    uint32_t roster_index;
    uint32_t character_count;

    city_offset = (city_id & 0xff) * 0x24;
    character_count = 0;
    roster_index = 0;
    if ((&g_first_city_character_count)[city_offset] != '\0')
    {
        do
        {
            roster_position = roster_index + (uint8_t)(&g_first_city_character_start)[city_offset];
            roster_index = roster_index + 1 & 0xff;
            destination_entry = (uint8_t *)(destination_address + character_count);
            if (*(char *)((uint32_t)(uint8_t)(&g_city_character_roster)[roster_position] * 0x10 +
                          g_character_table_address + 1) == -1)
            {
                character_count = character_count + 1 & 0xff;
                *destination_entry = (&g_city_character_roster)[roster_position];
            }
        } while (roster_index < (uint8_t)(&g_first_city_character_count)[city_offset]);
    }
    return character_count;
}

/* 原函数 0x81c13a40 */
uint32_t sango_city_list_enemy_rulers(uint32_t ruler_id, int destination_address)
{
    uint8_t governor_id;
    int city_offset;
    uint32_t city_index;
    uint32_t owner_id;
    char *destination_entry;
    uint32_t governor_count;

    governor_count = 0;
    city_index = 0;
    do
    {
        city_offset = city_index * 0x24;
        owner_id = (uint32_t)(uint8_t)(&g_first_city_owner)[city_offset];
        city_index = city_index + 1 & 0xff;
        if (owner_id != 0)
        {
            governor_id = (&g_first_city_governor)[city_offset];
            if ((governor_id != 0) && (owner_id != (ruler_id & 0xff) + 1))
            {
                destination_entry = (char *)(destination_address + governor_count);
                if (governor_id != owner_id)
                {
                    governor_count = governor_count + 1 & 0xff;
                    *destination_entry = governor_id - 1;
                }
            }
        }
    } while (city_index < 0x26);
    return governor_count;
}

/* 原函数 0x81c13ab8 */
uint32_t sango_faction_list_characters(uint32_t ruler_id, int destination_address)
{
    int roster_position;
    uint8_t *destination_entry;
    int city_offset;
    uint32_t roster_index;
    uint32_t city_character_count;
    uint32_t city_index;
    uint32_t total_characters;

    total_characters = 0;
    city_index = 0;
    do
    {
        city_offset = city_index * 0x24;
        if ((uint32_t)(uint8_t)(&g_first_city_owner)[city_offset] == (ruler_id & 0xff) + 1)
        {
            city_character_count = 0;
            roster_index = 0;
            if ((&g_first_city_character_count)[city_offset] != '\0')
            {
                do
                {
                    roster_position =
                        roster_index + (uint8_t)(&g_first_city_character_start)[city_offset];
                    roster_index = roster_index + 1 & 0xff;
                    destination_entry =
                        (uint8_t *)(destination_address + total_characters + city_character_count);
                    if (*(char *)((uint32_t)(uint8_t)(&g_city_character_roster)[roster_position] *
                                      0x10 +
                                  g_character_table_address + 1) ==
                        (&g_first_city_owner)[city_offset])
                    {
                        city_character_count = city_character_count + 1 & 0xff;
                        *destination_entry = (&g_city_character_roster)[roster_position];
                    }
                } while (roster_index < (uint8_t)(&g_first_city_character_count)[city_offset]);
            }
            total_characters = total_characters + city_character_count & 0xff;
        }
        city_index = city_index + 1 & 0xff;
    } while (city_index < 0x26);
    return total_characters;
}

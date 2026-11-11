#include "sango_internal.h"

/* 初始会话、主菜单、剧本和君主选择。 */

/* 原函数 0x81c159a0 */
int sango_allocate_session_state(void)
{
    int allocation_failed;

    g_battle_load_failed = 0;
    sango_memory_fill(g_army_slot_used_address, 0, 0x1e);
    sango_memory_fill(g_order_queue_address, 0x4b0, 0xff);
    g_viewport_tiles_address_view2 = bbk_alloc(0xe1);
    allocation_failed = 1;
    if (g_viewport_tiles_address_view2 != 0)
    {
        g_move_costs_address_view2 = bbk_alloc(0xfa);
        allocation_failed = 1;
        if (g_move_costs_address_view2 != 0)
        {
            g_temp_character_ids_address_view2 = bbk_alloc(0x56);
            allocation_failed = 1;
            if (g_temp_character_ids_address_view2 != 0)
            {
                g_character_table_address_view2 = bbk_alloc(0xc84);
                allocation_failed = 1;
                if (g_character_table_address_view2 != 0)
                {
                    g_strategy_cursor_y = 0;
                    g_battle_animate_movement_view2 = 1;
                    g_legacy_data_81c2b144 = 0;
                    g_legacy_data_81c2b180 = 0;
                    g_battle_map_width_aux_view2 = 0;
                    g_legacy_touch_y_byte = 0;
                    g_player_character = 0;
                    g_strategy_viewport_x = 0;
                    g_strategy_viewport_y = 0;
                    g_strategy_cursor_x = 0;
                    g_current_year = 0;
                    g_current_month = 1;
                    g_battle_render_enabled_view2 = 1;
                    g_battle_show_animations_view2 = 1;
                    allocation_failed = 0;
                }
            }
        }
    }
    return allocation_failed;
}

/* 原函数 0x81c15acc */
int sango_select_session(void)
{
    int scratch;
    uint32_t selection;
    int city_coordinates;
    uint8_t *city_position;
    uint32_t character_count;
    uint32_t character_index;

    sango_music_set_scene(SANGO_MUSIC_MENU);
    do
    {
        while (true)
        {
            while (true)
            {
                while (true)
                {
                    selection = sango_menu_select_animated(0x2c, 100);
                    if (selection != 2)
                        break;
                    sango_menu_show_credits();
                }
                if ((int)selection < 3)
                    break;
                if ((selection == 3) || (selection == 0xff))
                {
                    return 0;
                }
            }
            if (selection != 0)
                break;
            selection = sango_menu_select_animated(0x2d, 0x68);
            if (selection != 0xff)
            {
                selection =
                    sango_scenario_load((char)selection + '\x01', g_temp_character_ids_address);
                selection = sango_menu_choose_ruler(selection);
                if (selection != 0xff)
                {
                    g_player_character = (uint8_t)selection;
                    selection = sango_character_find_city(g_player_character);
                    city_coordinates =
                        sango_resource_item(2, '\x06', g_resource_package_address);
                    scratch = g_scratch_buffer_address;
                    city_position = (uint8_t *)(city_coordinates + selection * 2);
                    g_strategy_cursor_x = *city_position;
                    g_strategy_cursor_y = city_position[1];
                    if (g_strategy_cursor_x + 3 < 0xc)
                    {
                        g_strategy_viewport_x_view2 = g_strategy_cursor_x - 3;
                        if (g_strategy_cursor_x < 3)
                        {
                            g_strategy_viewport_x_view2 = '\0';
                        }
                    }
                    else
                    {
                        g_strategy_viewport_x_view2 = '\x05';
                    }
                    if (g_strategy_cursor_y + 3 < 9)
                    {
                        g_strategy_viewport_y_view2 = g_strategy_cursor_y - 3;
                        if (g_strategy_cursor_y < 3)
                        {
                            g_strategy_viewport_y_view2 = '\0';
                        }
                    }
                    else
                    {
                        g_strategy_viewport_y_view2 = '\x02';
                    }
                    selection = 0;
                    do
                    {
                        if ((uint32_t)(uint8_t)(&g_first_city_owner)[selection * 0x24] !=
                            g_player_character + 1)
                        {
                            character_count =
                                sango_city_list_idle_characters(selection, scratch);
                            city_coordinates = g_character_table_address;
                            character_index = 0;
                            if (character_count != 0)
                            {
                                do
                                {
                                    city_position = (uint8_t *)(scratch + character_index);
                                    character_index = character_index + 1 & 0xff;
                                    *(uint16_t *)((uint32_t)*city_position * 0x10 +
                                                  city_coordinates + 10) = 800;
                                } while (character_index < character_count);
                            }
                            (&g_first_city_food)[selection * 0x12] =
                                (&g_first_city_food)[selection * 0x12] + 1000;
                        }
                        selection = selection + 1 & 0xff;
                    } while (selection < 0x26);
                    return 1;
                }
            }
        }
    } while ((selection != 1) ||
             (selection = sango_save_choose_slot('\x01'), selection == 0xff));
    return 1;
}

/* 原函数 0x81c15d18 */
/* 静态背景加选中项动画；键盘选择范围保持0～3。 */
uint32_t sango_menu_select_animated(uint16_t background_resource,
                                    short selection_animation_base)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define event_kind (*(int *)(abi_storage + 0))
#define key_code (*(uint32_t *)(abi_storage + 4))

    uint32_t key_or_result;
    uint32_t selection;

    selection = 0;
    sango_bitmap_draw_resource((uint32_t)background_resource, 1, 0, 0, '\0');
poll_menu_event:
    sango_input_next_event(&event_kind);
    do
    {
        if (event_kind == SANGO_TOUCH_TAP || event_kind == SANGO_TOUCH_HOLD)
        {
            int tapped = sango_touch_menu_row(background_resource, &event_kind);
            if (tapped >= 0)
                return (uint32_t)tapped;
        }
        if (event_kind == 5)
        {
            if (key_code == SANGO_TOUCH_ANIMATION_KEY)
            {
                int tapped = sango_touch_last_menu_row(background_resource);
                if (tapped >= 0)
                    return (uint32_t)tapped;
                goto poll_menu_event;
            }
            if (key_code == 0x67)
            {
            select_previous_option:
                key_or_result = selection - 1;
            store_selection:
                selection = key_or_result & 0xff;
            }
            else if ((int)key_code < 0x68)
            {
                key_or_result = 0xff;
                if ((key_code == 1) || (key_or_result = selection, key_code == 0x1c))
                {
                    return key_or_result;
                }
            }
            else
            {
                key_or_result = selection + 1;
                if (key_code == 0x6a)
                    goto store_selection;
                if ((int)key_code < 0x6b)
                {
                    if (key_code == 0x69)
                        goto select_previous_option;
                }
                else if (key_code == 0x6c)
                {
                    selection = selection + 1;
                }
            }
            selection = selection & 3;
            sango_bitmap_draw_resource((uint32_t)background_resource, 1, 0, 0, '\0');
        }
        key_or_result =
            sango_animation_play_resource(selection_animation_base + (short)selection);
        if (key_or_result == 0xff)
            goto poll_menu_event;
        event_kind = 5;
        key_code = key_or_result;
    } while (true);
}
#undef event_kind
#undef key_code

/* 原函数 0x81c15e44 */
void sango_menu_show_credits(void)
{
    sango_credits_draw(g_game_context);
    sango_input_wait(5000, '\x01');
    return;
}

/* 原函数 0x81c15e6c */
uint32_t sango_menu_choose_ruler(uint32_t ruler_count)
{
    enum
    {
        NAME_BYTES = 6,
        NAME_BUFFER_BYTES = 250,
        VISIBLE_ROWS = SANGO_RULER_ROWS
    };
    uint8_t city_ids_or_title[40];
    int event[3];
    uint32_t total_rulers = ruler_count & 0xff;
    uint32_t first_visible = 0, selected_ruler = 0;
    uint32_t city_count;
    int city_coordinates_address;
    bool cities_flash_on = false;

    if (!total_rulers)
        return 0xff;
    /* The shared move-cost buffer has 250 bytes. Every padded name needs six
     * bytes, followed by a final NUL: padding used to overwrite that NUL and
     * let the text renderer walk into old heap data. */
    if (total_rulers > (NAME_BUFFER_BYTES - 1) / NAME_BYTES)
        total_rulers = (NAME_BUFFER_BYTES - 1) / NAME_BYTES;
    for (uint32_t index = 0; index < total_rulers; ++index)
    {
        char *name_slot = g_move_costs_address_view3 + index * NAME_BYTES;
        sango_load_named_text(g_temp_character_ids_address[index], name_slot);
        uint32_t name_bytes = sango_crt_strlen(name_slot);
        if (name_bytes < NAME_BYTES)
            sango_memory_fill(name_slot + name_bytes, 0x20, NAME_BYTES - name_bytes);
    }
    g_move_costs_address_view3[total_rulers * NAME_BYTES] = 0;

    sango_ui_paint_begin();
    sango_ruler_begin(total_rulers);
    sango_menu_draw_ruler_names(0);
    sango_ruler_select(0, 0, 0, 0);
    sango_ui_paint_end();
    city_coordinates_address = sango_resource_item(2, 6, g_resource_package_address);
    city_count =
        sango_faction_list_cities(g_temp_character_ids_address[0], (int)city_ids_or_title);

    while (true)
    {
        sango_input_next_event(event);
        int tapped = sango_touch_choose_row(
            event, SANGO_RULER_LIST_LEFT, SANGO_RULER_LIST_TOP, SANGO_RULER_LIST_RIGHT,
            SANGO_RULER_ROW_HEIGHT, VISIBLE_ROWS, first_visible, total_rulers);
        int button = sango_ruler_touch_button(event);
        if (button)
        {
            event[0] = 5;
            event[1] = button;
        }
        if (event[0] == SANGO_TOUCH_PAN_END)
        {
            event[1] = sango_touch_swipe_key(event);
            if (event[1])
                event[0] = 5;
        }
        if (event[0] == 6)
        {
            cities_flash_on = !cities_flash_on;
            sango_menu_flash_ruler_cities(city_count, city_ids_or_title,
                                          city_coordinates_address);
            continue;
        }
        if (event[0] != 5 && tapped < 0)
            continue;
        /* Confirm/cancel return immediately; only a changed selection needs
         * paint work. Touch updates and unrelated keys cannot redraw names. */
        if (event[0] == 5 && event[1] == BDA_KEY_ENTER)
            return sango_ruler_end(g_temp_character_ids_address[selected_ruler]);
        if (event[0] == 5 && event[1] == BDA_KEY_ESCAPE)
            return sango_ruler_end(0xff);
        uint32_t previous_selection = selected_ruler;
        uint32_t previous_first = first_visible;
        if (tapped >= 0)
            selected_ruler = (unsigned int)tapped;
        else if (event[1] == BDA_KEY_UP && selected_ruler > 0)
            --selected_ruler;
        else if (event[1] == BDA_KEY_DOWN && selected_ruler + 1 < total_rulers)
            ++selected_ruler;
        if (selected_ruler == previous_selection)
            continue;
        if (selected_ruler < first_visible)
            first_visible = selected_ruler;
        else if (selected_ruler >= first_visible + VISIBLE_ROWS)
            first_visible = selected_ruler - VISIBLE_ROWS + 1;

        if (cities_flash_on)
        {
            sango_menu_flash_ruler_cities(city_count, city_ids_or_title,
                                          city_coordinates_address);
            cities_flash_on = false;
        }
        sango_ui_paint_begin();
        sango_ruler_select(previous_selection, previous_first, selected_ruler, first_visible);
        sango_ui_paint_end();
        city_count = sango_faction_list_cities(g_temp_character_ids_address[selected_ruler],
                                               (int)city_ids_or_title);
    }
}

/* 原函数 0x81c161c4 */
void sango_menu_flash_ruler_cities(uint32_t city_count, uint8_t *city_ids,
                                   int city_positions_address)
{
    uint16_t screen_x;
    uint16_t screen_y;
    uint8_t *city_or_position_entry;
    uint32_t city_index;

    city_index = 0;
    city_or_position_entry = city_ids;
    if ((city_count & 0xff) != 0)
    {
        do
        {
            city_or_position_entry =
                (uint8_t *)(city_positions_address + (*city_or_position_entry & 0x7f) * 2);
            screen_x = (uint16_t)*city_or_position_entry * 7 + SANGO_RULER_MAP_X + 3;
            screen_y = (uint16_t)city_or_position_entry[1] * 7 + SANGO_RULER_MAP_Y + 3;
            sango_display_invert_rectangle(screen_x, screen_y, screen_x + 1, screen_y + 1, 0);
            city_index = city_index + 1 & 0xff;
            city_or_position_entry = city_ids + city_index;
        } while (city_index < (city_count & 0xff));
    }
    return;
}

/* 原函数 0x81c16274 */
void sango_menu_draw_ruler_names(uint32_t first_ruler)
{
    sango_ruler_draw_names(first_ruler);
    return;
}

/* 原函数 0x81c162e0 */
uint32_t sango_animation_play_resource(uint16_t resource_id)
{
    int animation;
    uint32_t result;

    animation = sango_resource_item((uint32_t)resource_id, '\x01', g_resource_package_address);
    result = sango_animation_play_range((uint32_t)resource_id, 0,
                                        (uint32_t) * (uint8_t *)(animation + 5), 1, 0, 0);
    return result;
}

#include "sango_internal.h"

/* 初始会话、主菜单、剧本和君主选择。 */

/* 原函数 0x81c159a0 */
int sango_allocate_session_state(void)
{
    int iVar1;

    g_battle_load_failed = 0;
    sango_memory_fill(g_army_slot_used_address, 0, 0x1e);
    sango_memory_fill(g_order_queue_address, 0x4b0, 0xff);
    g_viewport_tiles_address_view2 = bbk_alloc(0xe1);
    iVar1 = 1;
    if (g_viewport_tiles_address_view2 != 0)
    {
        g_move_costs_address_view2 = bbk_alloc(0xfa);
        iVar1 = 1;
        if (g_move_costs_address_view2 != 0)
        {
            g_temp_character_ids_address_view2 = bbk_alloc(0x56);
            iVar1 = 1;
            if (g_temp_character_ids_address_view2 != 0)
            {
                g_character_table_address_view2 = bbk_alloc(0xc84);
                iVar1 = 1;
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
                    iVar1 = 0;
                }
            }
        }
    }
    return iVar1;
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
                    city_coordinates = sango_resource_item(2, '\x06', g_resource_package_address);
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
                            character_count = sango_city_list_idle_characters(selection, scratch);
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
    } while ((selection != 1) || (selection = sango_save_choose_slot('\x01'), selection == 0xff));
    return 1;
}

/* 原函数 0x81c15d18 */
/* 静态背景加选中项动画；键盘选择范围保持0～3。 */
uint32_t sango_menu_select_animated(uint16_t background_resource, short selection_animation_base)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define event_kind (*(int *)(abi_storage + 0))
#define key_code (*(uint32_t *)(abi_storage + 4))

    uint32_t key_or_result;
    uint32_t selection;

    selection = 0;
    sango_bitmap_draw_resource((uint32_t)background_resource, 1, 0, 0, '\0');
LAB_81c15d5c:
    sango_input_poll_native_event(&event_kind);
    do
    {
        if (event_kind == 5)
        {
            if (key_code == 0x67)
            {
            LAB_81c15e28:
                key_or_result = selection - 1;
            LAB_81c15e2c:
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
                    goto LAB_81c15e2c;
                if ((int)key_code < 0x6b)
                {
                    if (key_code == 0x69)
                        goto LAB_81c15e28;
                }
                else if (key_code == 0x6c)
                {
                    selection = selection + 1;
                }
            }
            selection = selection & 3;
            sango_bitmap_draw_resource((uint32_t)background_resource, 1, 0, 0, '\0');
        }
        key_or_result = sango_animation_play_resource(selection_animation_base + (short)selection);
        if (key_or_result == 0xff)
            goto LAB_81c15d5c;
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
    unsigned char abi_storage[64] __attribute__((aligned(8)));
#define city_ids_or_title (*(uint8_t(*)[40])(abi_storage + 0))
#define event_kind (*(int *)(abi_storage + 40))
#define key_code (*(int *)(abi_storage + 44))

    bool cities_flash_on;
    int city_coordinates_address;
    uint32_t first_visible;
    uint32_t highlight_top;
    int row_position;
    uint32_t city_count;
    uint32_t selected_ruler;
    uint32_t total_rulers;

    total_rulers = ruler_count & 0xff;
    uint32_t ruler_index = 0;
    sango_display_fill_gray_rectangle(0, 0, 0xef, 0x13f, 0, 0);
    if (total_rulers != 0)
    {
        do
        {
            uint32_t text_slot_offset = ruler_index * 6 & 0xff;
            sango_load_named_text(g_temp_character_ids_address[ruler_index],
                                  g_move_costs_address_view3 + text_slot_offset);
            uint32_t text_bytes = sango_crt_strlen(g_move_costs_address_view3);
            text_bytes = text_bytes & 0xff;
            if (text_bytes < text_slot_offset + 6)
            {
                sango_memory_fill(g_move_costs_address_view3 + text_bytes, 0x20,
                                  (text_slot_offset - text_bytes) + 6);
            }
            ruler_index = ruler_index + 1 & 0xff;
        } while (ruler_index < total_rulers);
    }
    sango_display_draw_rectangle(0, 0, 0xef, 0x13f, 3, 0, 0);
    sango_resource_read_text(1, 0x2d, city_ids_or_title);
    sango_text_draw_legacy(0x48, 4, (char *)city_ids_or_title);
    sango_bitmap_draw_resource(0x2f, 1, 0x3c, 0x14, '\x01');
    sango_display_draw_rectangle(0xd, 10, 0x36, 0x13b, 3, 0, 0);
    city_coordinates_address = sango_resource_item(2, '\x06', g_resource_package_address);
    sango_menu_draw_ruler_names(0);
    sango_display_invert_rectangle(0x10, 0xd, 0x34, 0x19, 0);
    first_visible = 0;
    selected_ruler = 0;
    cities_flash_on = false;
    city_count =
        sango_faction_list_cities((uint32_t)*g_temp_character_ids_address, (int)city_ids_or_title);
    highlight_top = 0xd;
    row_position = 0x19;
    do
    {
        while (sango_input_next_event(&event_kind), event_kind != 5)
        {
            cities_flash_on = (bool)(cities_flash_on ^ 1);
            sango_menu_flash_ruler_cities(city_count, city_ids_or_title, city_coordinates_address);
        }
        sango_display_invert_rectangle(0x10, (short)highlight_top, 0x34, (short)row_position, 0);
        if (cities_flash_on)
        {
            sango_menu_flash_ruler_cities(city_count, city_ids_or_title, city_coordinates_address);
            cities_flash_on = false;
        }
        if (key_code == 0x1c)
        {
            return (uint32_t)g_temp_character_ids_address[selected_ruler];
        }
        if (key_code < 0x1d)
        {
            row_position = selected_ruler - first_visible;
            if (key_code == 1)
            {
                return 0xff;
            }
        }
        else if (key_code == 0x67)
        {
            row_position = -first_visible;
            if (selected_ruler != 0)
            {
                if (selected_ruler == first_visible)
                {
                    first_visible = selected_ruler - 1 & 0xff;
                }
                selected_ruler = selected_ruler - 1 & 0xff;
            update_visible_row:
                row_position = selected_ruler - first_visible;
            }
        }
        else
        {
            row_position = selected_ruler - first_visible;
            if ((key_code == 0x6c) && ((int)selected_ruler < (int)(total_rulers - 1)))
            {
                selected_ruler = selected_ruler + 1 & 0xff;
                row_position = selected_ruler - first_visible;
                if (0x18 < row_position)
                {
                    first_visible = first_visible + 1 & 0xff;
                    goto update_visible_row;
                }
            }
        }
        sango_menu_draw_ruler_names(first_visible);
        highlight_top = row_position * 0xc + 0xdU & 0xff;
        row_position = highlight_top + 0xc;
        sango_display_invert_rectangle(0x10, (short)highlight_top, 0x34, (short)row_position, 0);
        city_count = sango_faction_list_cities(
            (uint32_t)g_temp_character_ids_address[selected_ruler], (int)city_ids_or_title);
    } while (true);
}
#undef city_ids_or_title
#undef event_kind
#undef key_code

/* 原函数 0x81c161c4 */
void sango_menu_flash_ruler_cities(uint32_t param_1, uint8_t *param_2, int param_3)
{
    uint16_t uVar1;
    uint16_t uVar2;
    uint8_t *pbVar3;
    uint32_t uVar4;

    uVar4 = 0;
    pbVar3 = param_2;
    if ((param_1 & 0xff) != 0)
    {
        do
        {
            pbVar3 = (uint8_t *)(param_3 + (*pbVar3 & 0x7f) * 2);
            uVar1 = (uint16_t)*pbVar3 * 7 + 0x3f & 0xff;
            uVar2 = (uint16_t)pbVar3[1] * 7 + 0x17 & 0xff;
            sango_display_invert_rectangle(uVar1, uVar2, uVar1 + 1, uVar2 + 1, 0);
            uVar4 = uVar4 + 1 & 0xff;
            pbVar3 = param_2 + uVar4;
        } while (uVar4 < (param_1 & 0xff));
    }
    return;
}

/* 原函数 0x81c16274 */
void sango_menu_draw_ruler_names(uint32_t param_1)
{
    g_text_left = 0x10;
    g_text_right = 0x34;
    g_text_top = 0xd;
    g_text_bottom = 0x139;
    sango_text_draw_legacy(0x10, 0xd, (char *)(g_move_costs_address + (param_1 & 0xff) * 6));
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

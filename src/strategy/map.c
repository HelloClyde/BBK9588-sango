#include "sango_internal.h"

/* 战略地图、城市选择和归属查询。 */

/* 原函数 0x81c12b18 */
/* 战略城市选择循环；map_state包含视口与当前光标，城市返回值为0基索引。 */
uint32_t sango_strategy_select_city(uint8_t *map_state)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define event_kind (*(int *)(abi_storage + 0))
#define key_code (*(int *)(abi_storage + 4))

    bool redraw_map;
    bool showing_find_map;
    uint8_t bVar3;
    uint8_t *find_map;
    uint32_t uVar5;
    short sVar6;
    uint8_t scroll_mode;
    uint32_t selected_city_plus_one;

    redraw_map = true;
    scroll_mode = 0;
    showing_find_map = false;
    sango_render_clear_rectangle(0, 0, 0xef, 0x13f, g_game_context);
LAB_81c12b64:
    if (!redraw_map)
        goto LAB_81c12b8c;
LAB_81c12b6c:
    if (showing_find_map)
        goto LAB_81c12b8c;
    do
    {
        selected_city_plus_one = sango_strategy_draw_map(map_state, scroll_mode);
        redraw_map = false;
        scroll_mode = 0;
    LAB_81c12b8c:
        sango_input_next_event(&event_kind);
        if (event_kind == 5)
        {
            if (!showing_find_map)
                break;
        }
        else
        {
            if (event_kind != 0xb)
                goto LAB_81c12b64;
            if (!showing_find_map)
            {
                /* The input message retains full 16-bit x/y at bytes 8/10.
                      Legacy coordinate globals truncate y to a uint8_t above row 255. */
                enum SangoStatusbarAction action = sango_statusbar_hit(
                    *(uint16_t *)(abi_storage + 8), *(uint16_t *)(abi_storage + 10));
                if (action == SANGO_STATUSBAR_INFO)
                {
                    sango_ui_show_message(&g_legacy_data_81c20570, 2);
                    sango_strategy_present();
                }
                if (action != SANGO_STATUSBAR_FIND)
                    goto LAB_81c12b64;
                sVar6 = 0x13f;
                goto LAB_81c12c2c;
            }
        }
        showing_find_map = false;
    } while (true);
    if (key_code == 0x67)
    {
        bVar3 = map_state[3];
        if (bVar3 == 0)
            goto LAB_81c12b64;
        map_state[3] = bVar3 - 1;
        scroll_mode = 1;
        if (map_state[1] <= (uint8_t)(bVar3 - 1))
            goto LAB_81c12d6c;
        map_state[1] = bVar3 - 1;
    }
    else
    {
        if (key_code < 0x68)
        {
            if (key_code == 0x1c)
            {
                if (selected_city_plus_one == 0)
                    goto LAB_81c12b64;
                uVar5 = selected_city_plus_one - 1 & 0xff;
            }
            else
            {
                if (0x1c < key_code)
                {
                    sVar6 = 0x13f;
                    if (key_code == 0x1f)
                    {
                    LAB_81c12c2c:
                        sango_display_fill_gray_rectangle(0, 0, 0xef, sVar6, 0, 0);
                        find_map = (uint8_t *)sango_resource_item(0x4b, '\x01',
                                                                  g_resource_package_address);
                        showing_find_map = true;
                        /* The 9588 resource is 84x64, unlike the 9288S 160x160 map.
                              Respect its descriptor rather than reading past the bitmap. */
                        uint16_t map_width = (uint16_t)(find_map[0] | (find_map[1] << 8));
                        uint16_t map_height = (uint16_t)(find_map[2] | (find_map[3] << 8));
                        sango_bitmap_draw_frame_screen((240 - map_width) / 2,
                                                       (320 - map_height) / 2, map_width,
                                                       map_height, 0, find_map);
                    }
                    goto LAB_81c12b64;
                }
                uVar5 = 0xff;
                if (key_code != 1)
                    goto LAB_81c12b64;
            }
            return uVar5;
        }
        if (key_code == 0x6a)
        {
            bVar3 = map_state[2];
            if (10 < bVar3)
                goto LAB_81c12b64;
            map_state[2] = bVar3 + 1;
            scroll_mode = 4;
            if ((uint32_t)(uint8_t)(bVar3 + 1) < *map_state + 7)
                goto LAB_81c12d6c;
            *map_state = bVar3 - 5;
        }
        else if (key_code < 0x6b)
        {
            if (key_code != 0x69)
                goto LAB_81c12b64;
            bVar3 = map_state[2];
            if (bVar3 == 0)
                goto LAB_81c12b64;
            map_state[2] = bVar3 - 1;
            scroll_mode = 2;
            if (*map_state <= (uint8_t)(bVar3 - 1))
                goto LAB_81c12d6c;
            *map_state = bVar3 - 1;
        }
        else
        {
            if (key_code != 0x6c)
                goto LAB_81c12b64;
            bVar3 = map_state[3];
            if (7 < bVar3)
                goto LAB_81c12b64;
            map_state[3] = bVar3 + 1;
            scroll_mode = 3;
            if ((uint32_t)(uint8_t)(bVar3 + 1) < map_state[1] + 7)
                goto LAB_81c12d6c;
            map_state[1] = bVar3 - 5;
        }
    }
    scroll_mode = 0;
LAB_81c12d6c:
    redraw_map = true;
    goto LAB_81c12b6c;
}
#undef event_kind
#undef key_code

/* 原函数 0x81c12e18 */
/* 绘制12列战略底图的7×7可见区域、城市归属图标及底部状态。 */
uint32_t sango_strategy_draw_map(uint8_t *map_state, uint8_t scroll_mode)
{
    int iVar1;
    uint8_t *pbVar2;
    char *city_id_output;
    uint32_t uVar4;
    short sVar5;
    uint32_t uVar6;
    char *status_text;
    uint8_t city_marker_frame;
    uint32_t uVar8;
    uint32_t uVar9;
    uint32_t uVar10;
    char *text_part;

    iVar1 = sango_resource_item(2, '\x0e', g_resource_package_address);
    uVar9 = 0;
    uVar8 = (uint32_t)map_state[1] * 0xc + (uint32_t)*map_state;
    do
    {
        bbk_memcpy(&g_visible_city_ids + uVar9 * 7, (void *)(iVar1 + uVar8), 7);
        uVar9 = uVar9 + 1 & 0xff;
        uVar8 = uVar8 + 0xc & 0xffff;
    } while (uVar9 < 7);
    uVar8 = (uint32_t)map_state[3] - (uint32_t)map_state[1] & 0xff;
    uVar9 = (uint32_t)map_state[2] - (uint32_t)*map_state & 0xff;
    iVar1 = sango_resource_item(0x36, '\x01', g_resource_package_address);
    if (scroll_mode == 0)
    {
        uVar10 = 0;
        do
        {
            uVar6 = 0;
            uVar4 = ((uVar10 + map_state[1]) * 0xc + (uint32_t)*map_state) * 0x100;
            do
            {
                sango_raster_draw_opaque(uVar6 << 5, (short)(uVar10 << 5), 0x20, 0x20,
                                         iVar1 + 6 + (uVar4 & 0xffff), g_game_context);
                uVar6 = uVar6 + 1 & 0xff;
                uVar4 = (uVar4 & 0xffff) + 0x100;
            } while (uVar6 < 7);
            uVar10 = uVar10 + 1 & 0xff;
        } while (uVar10 < 7);
        uVar10 = 0;
        do
        {
            uVar4 = 0;
            pbVar2 = &g_visible_city_ids + uVar10 * 7;
            do
            {
                city_marker_frame = 8;
                if (*pbVar2 != 0)
                {
                    if (((uint32_t)(uint8_t)(&g_city_owner_one_based_view)[(uint32_t)*pbVar2 *
                                                                           0x24] !=
                         g_player_character + 1) &&
                        (city_marker_frame = 7,
                         (uint8_t)(&g_city_owner_one_based_view)[(uint32_t)*pbVar2 * 0x24] == 0))
                    {
                        city_marker_frame = 0;
                    }
                    pbVar2 =
                        (uint8_t *)sango_resource_item(0x37, '\x01', g_resource_package_address);
                    sango_bitmap_draw_frame((short)uVar4 * 0x20 + 8, (short)uVar10 * 0x20 + 8, 0x10,
                                            0x10, city_marker_frame, pbVar2, g_game_context);
                }
                uVar4 = uVar4 + 1 & 0xff;
                pbVar2 = &g_visible_city_ids + uVar10 * 7 + uVar4;
            } while (uVar4 < 7);
            uVar10 = uVar10 + 1 & 0xff;
        } while (uVar10 < 7);
        goto LAB_81c1304c;
    }
    uVar10 = uVar8;
    if (scroll_mode == 2)
    {
        uVar4 = uVar9 + 1;
    LAB_81c13484:
        uVar6 = uVar4 & 0xff;
    }
    else
    {
        uVar6 = uVar9;
        if (scroll_mode < 3)
        {
            uVar4 = uVar8 + 1;
            if (scroll_mode == 1)
            {
            LAB_81c13468:
                uVar10 = uVar4 & 0xff;
            }
        }
        else
        {
            uVar4 = uVar8 - 1;
            if (scroll_mode == 3)
                goto LAB_81c13468;
            uVar4 = uVar9 - 1;
            if (scroll_mode == 4)
                goto LAB_81c13484;
        }
    }
    sVar5 = (short)uVar10 * 0x20;
    sango_raster_draw_opaque(
        uVar6 * 0x20, sVar5, 0x20, 0x20,
        iVar1 + 6 +
            (((uVar10 + map_state[1]) * 0xc + (uint32_t)*map_state + uVar6) * 0x100 & 0xffff),
        g_game_context);
    if ((uint8_t)(&g_visible_city_ids)[uVar6 + uVar10 * 7] != 0)
    {
        city_marker_frame = 8;
        if (((uint32_t)(uint8_t)(&g_city_owner_one_based_view)
                 [(uint32_t)(uint8_t)(&g_visible_city_ids)[uVar6 + uVar10 * 7] * 0x24] !=
             g_player_character + 1) &&
            (city_marker_frame = 7,
             (uint8_t)(&g_city_owner_one_based_view)
                     [(uint32_t)(uint8_t)(&g_visible_city_ids)[uVar6 + uVar10 * 7] * 0x24] == 0))
        {
            city_marker_frame = 0;
        }
        pbVar2 = (uint8_t *)sango_resource_item(0x37, '\x01', g_resource_package_address);
        sango_bitmap_draw_frame((short)(uVar6 * 0x20) + 8, sVar5 + 8, 0x10, 0x10, city_marker_frame,
                                pbVar2, g_game_context);
    }
LAB_81c1304c:
    iVar1 = sango_resource_item(0x38, '\x01', g_resource_package_address);
    sango_raster_draw_masked(uVar9 * 0x20 + 8, (short)uVar8 * 0x20 + 0x10, 0x10, 0x10, iVar1 + 6,
                             g_game_context);
    text_part = (char *)(g_scratch_buffer_address + 0x154);
    status_text = (char *)(g_scratch_buffer_address + 300);
    sango_render_clear_rectangle(0, 0xe0, 0xef, 0x13f, g_game_context);
    sango_statusbar_draw(g_game_context);
    pbVar2 = (uint8_t *)sango_resource_item(g_scenario_id_view2 + 0x2f, '\x01',
                                            g_resource_package_address);
    sango_bitmap_draw_frame(0x15, 0x10f, 0x18, 0x18, g_player_character, pbVar2, g_game_context);
    pbVar2 = (uint8_t *)sango_resource_item(0x45, '\x01', g_resource_package_address);
    sango_bitmap_draw_frame(0x35, 0x10f, 7, 9, 1, pbVar2, g_game_context);
    uVar10 = (uint32_t)g_player_character;
    uVar4 = 0;
    uVar6 = 0;
    iVar1 = 0;
    do
    {
        city_id_output = status_text + uVar4;
        if ((uint32_t)(uint8_t)(&g_first_city_owner)[(iVar1 + uVar6) * 4] == uVar10 + 1)
        {
            uVar4 = uVar4 + 1 & 0xff;
            *city_id_output = (char)uVar6;
        }
        uVar6 = uVar6 + 1 & 0xff;
        iVar1 = uVar6 << 3;
    } while (uVar6 < 0x26);
    sango_format_integer(uVar4, status_text, 10);
    sango_text_draw_context(0x3f, 0x10e, status_text, g_game_context);
    sango_bitmap_draw_frame(0x35, 0x11e, 7, 9, 0, pbVar2, g_game_context);
    uVar10 = sango_faction_count_characters((uint32_t)g_player_character);
    sango_format_integer(uVar10, status_text, 10);
    sango_text_draw_context(0x3f, 0x11c, status_text, g_game_context);
    sango_format_integer((uint32_t)g_current_year, status_text, 10);
    sango_resource_read_text(0x40, 0x3f, text_part);
    bbk_strcat(status_text, text_part);
    sango_text_draw_context(0x52, 0x10e, status_text, g_game_context);
    sango_format_integer((uint32_t)g_current_month, status_text, 10);
    sango_resource_read_text(0x40, 0x40, text_part);
    bbk_strcat(status_text, text_part);
    sango_text_draw_context(0x52, 0x11c, status_text, g_game_context);
    city_marker_frame = (&g_visible_city_ids)[uVar9 + uVar8 * 7];
    if (city_marker_frame != 0)
    {
        sango_city_read_name(city_marker_frame - 1, text_part);
        sango_text_draw_context(0x78, 0x115, text_part, g_game_context);
    }
    sango_strategy_present();
    return (uint32_t)(uint8_t)(&g_visible_city_ids)[uVar9 + uVar8 * 7];
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
    uint8_t *puVar1;
    char cVar2;
    uint32_t uVar3;
    uint8_t *puVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;

    uVar7 = city_id & 0xff;
    uVar3 = 0;
    if ((uVar7 < 0x26) && (character_id < 200))
    {
        uVar6 = (uint32_t)(uint8_t)(&g_first_city_character_start)[uVar7 * 0x24] +
                    (uint32_t)(uint8_t)(&g_first_city_character_count)[uVar7 * 0x24] &
                0xff;
        uVar5 = 199;
        if (uVar6 < 199)
        {
            do
            {
                puVar4 = &g_city_character_roster + uVar5;
                puVar1 = (uint8_t *)(uVar5 + 0x81c2b30f);
                uVar5 = uVar5 - 1 & 0xff;
                *puVar4 = *puVar1;
            } while (uVar6 < uVar5);
        }
        cVar2 = (&g_first_city_character_count)[uVar7 * 0x24];
        (&g_city_character_roster)[uVar6] = character_id;
        (&g_first_city_character_count)[uVar7 * 0x24] = cVar2 + '\x01';
        while (uVar7 = uVar7 + 1 & 0xff, uVar7 < 0x26)
        {
            (&g_first_city_character_start)[uVar7 * 0x24] =
                (&g_first_city_character_start)[uVar7 * 0x24] + '\x01';
        }
        uVar3 = 1;
    }
    return uVar3;
}

/* 原函数 0x81c135a8 */
uint32_t sango_city_add_item(uint32_t city_id, uint8_t item_id)
{
    uint8_t *puVar1;
    char cVar2;
    uint32_t uVar3;
    uint8_t *puVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;

    uVar7 = city_id & 0xff;
    uVar3 = 0;
    if ((uVar7 < 0x26) && (item_id < 0x21))
    {
        uVar6 = (uint32_t)(uint8_t)(&g_first_city_item_start)[uVar7 * 0x24] +
                    (uint32_t)(uint8_t)(&g_first_city_item_count)[uVar7 * 0x24] &
                0xff;
        uVar5 = 0x20;
        if (uVar6 < 0x20)
        {
            do
            {
                puVar4 = &g_city_item_roster + uVar5;
                puVar1 = (uint8_t *)(uVar5 + 0x81c2b3df);
                uVar5 = uVar5 - 1 & 0xff;
                *puVar4 = *puVar1;
            } while (uVar6 < uVar5);
        }
        cVar2 = (&g_first_city_item_count)[uVar7 * 0x24];
        (&g_city_item_roster)[uVar6] = item_id;
        (&g_first_city_item_count)[uVar7 * 0x24] = cVar2 + '\x01';
        while (uVar7 = uVar7 + 1 & 0xff, uVar7 < 0x26)
        {
            (&g_first_city_item_start)[uVar7 * 0x24] =
                (&g_first_city_item_start)[uVar7 * 0x24] + '\x01';
        }
        uVar3 = 1;
    }
    return uVar3;
}

/* 原函数 0x81c13698 */
void sango_city_roster_noop(void)
{
    return;
}

/* 原函数 0x81c136a0 */
uint32_t sango_city_adjacent_distance(uint32_t param_1, uint8_t param_2, uint8_t param_3,
                                      uint32_t param_4, uint8_t param_5, uint8_t param_6)
{
    unsigned char abi_storage[21] __attribute__((aligned(8)));
    (*(uint8_t *)(abi_storage + 0)) = param_5;
    (*(uint8_t *)(abi_storage + 4)) = param_6;
#define param_5 (*(uint8_t *)(abi_storage + 0))
#define param_6 (*(uint8_t *)(abi_storage + 4))

    char cVar1;
    uint8_t bVar2;
    int iVar3;
    uint8_t *pbVar4;
    uint32_t uVar5;
    uint8_t *pbVar6;

    iVar3 = sango_resource_item(0x3b, '\x01', g_resource_package_address);
    pbVar6 = (uint8_t *)(iVar3 + (param_1 & 0xff) * 0x10);
    uVar5 = 0;
    pbVar4 = pbVar6;
    do
    {
        if ((uint32_t)*pbVar4 == (param_4 & 0xff) + 1)
        {
            if (7 < uVar5)
            {
                return 0xff;
            }
            cVar1 = param_3 - param_6;
            if (param_3 < param_6)
            {
                cVar1 = param_6 - param_3;
            }
            if (param_2 < param_5)
            {
                bVar2 = (cVar1 + param_5) - param_2;
            }
            else
            {
                bVar2 = (cVar1 + param_2) - param_5;
            }
            return (uint32_t)bVar2;
        }
        uVar5 = uVar5 + 1 & 0xff;
        pbVar4 = pbVar6 + uVar5;
    } while (uVar5 < 8);
    return 0xff;
}
#undef param_5
#undef param_6

/* 原函数 0x81c13794 */
uint32_t sango_faction_list_cities(uint32_t ruler_id, int output_city_ids)
{
    uint8_t *puVar1;
    uint32_t uVar2;
    uint32_t city_index;

    city_index = 0;
    uVar2 = 0;
    do
    {
        puVar1 = (uint8_t *)(output_city_ids + city_index);
        if ((uint32_t)(uint8_t)(&g_first_city_owner)[uVar2 * 0x24] == (ruler_id & 0xff) + 1)
        {
            city_index = city_index + 1 & 0xff;
            *puVar1 = (char)uVar2;
        }
        uVar2 = uVar2 + 1 & 0xff;
    } while (uVar2 < 0x26);
    return city_index;
}

/* 原函数 0x81c137f0 */
uint32_t sango_character_find_city(char character_id)
{
    char *pcVar1;
    uint32_t uVar2;
    uint8_t bVar3;
    uint32_t uVar4;

    uVar4 = 0;
    do
    {
        uVar2 = (uint32_t)(uint8_t)(&g_first_city_character_start)[uVar4 * 0x24];
        bVar3 = 0;
        if ((&g_first_city_character_count)[uVar4 * 0x24] != 0)
        {
            do
            {
                pcVar1 = &g_city_character_roster + uVar2;
                bVar3 = bVar3 + 1;
                uVar2 = uVar2 + 1 & 0xff;
                if (*pcVar1 == character_id)
                {
                    return uVar4;
                }
            } while (bVar3 < (uint8_t)(&g_first_city_character_count)[uVar4 * 0x24]);
        }
        uVar4 = uVar4 + 1 & 0xff;
    } while (uVar4 < 0x26);
    return 0xff;
}

/* 原函数 0x81c13870 */
uint32_t sango_city_list_idle_characters(uint32_t city_id, int output_character_ids)
{
    int iVar1;
    uint8_t *pbVar2;
    int iVar3;
    uint32_t uVar4;
    uint32_t uVar5;

    iVar3 = (city_id & 0xff) * 0x24;
    uVar5 = 0;
    uVar4 = 0;
    if ((&g_first_city_character_count)[iVar3] != '\0')
    {
        do
        {
            iVar1 = uVar4 + (uint8_t)(&g_first_city_character_start)[iVar3];
            uVar4 = uVar4 + 1 & 0xff;
            pbVar2 = (uint8_t *)(output_character_ids + uVar5);
            if (*(char *)((uint32_t)(uint8_t)(&g_city_character_roster)[iVar1] * 0x10 +
                          g_character_table_address + 1) == (&g_first_city_owner)[iVar3])
            {
                uVar5 = uVar5 + 1 & 0xff;
                *pbVar2 = (&g_city_character_roster)[iVar1];
            }
        } while (uVar4 < (uint8_t)(&g_first_city_character_count)[iVar3]);
    }
    return uVar5;
}

/* 原函数 0x81c13918 */
uint32_t sango_city_list_available_characters(uint32_t param_1, int param_2)
{
    int iVar1;
    int iVar2;
    uint8_t *pbVar3;
    uint32_t uVar4;
    uint32_t uVar5;

    iVar2 = (param_1 & 0xff) * 0x24;
    uVar5 = 0;
    uVar4 = 0;
    if ((&g_first_city_character_count)[iVar2] != '\0')
    {
        do
        {
            iVar1 = uVar4 + (uint8_t)(&g_first_city_character_start)[iVar2];
            uVar4 = uVar4 + 1 & 0xff;
            pbVar3 = (uint8_t *)(param_2 + uVar5);
            if (*(char *)((uint32_t)(uint8_t)(&g_city_character_roster)[iVar1] * 0x10 +
                          g_character_table_address + 1) == '\0')
            {
                uVar5 = uVar5 + 1 & 0xff;
                *pbVar3 = (&g_city_character_roster)[iVar1];
            }
        } while (uVar4 < (uint8_t)(&g_first_city_character_count)[iVar2]);
    }
    return uVar5;
}

/* 原函数 0x81c139a8 */
uint32_t sango_city_list_captives(uint32_t param_1, int param_2)
{
    int iVar1;
    int iVar2;
    uint8_t *pbVar3;
    uint32_t uVar4;
    uint32_t uVar5;

    iVar2 = (param_1 & 0xff) * 0x24;
    uVar5 = 0;
    uVar4 = 0;
    if ((&g_first_city_character_count)[iVar2] != '\0')
    {
        do
        {
            iVar1 = uVar4 + (uint8_t)(&g_first_city_character_start)[iVar2];
            uVar4 = uVar4 + 1 & 0xff;
            pbVar3 = (uint8_t *)(param_2 + uVar5);
            if (*(char *)((uint32_t)(uint8_t)(&g_city_character_roster)[iVar1] * 0x10 +
                          g_character_table_address + 1) == -1)
            {
                uVar5 = uVar5 + 1 & 0xff;
                *pbVar3 = (&g_city_character_roster)[iVar1];
            }
        } while (uVar4 < (uint8_t)(&g_first_city_character_count)[iVar2]);
    }
    return uVar5;
}

/* 原函数 0x81c13a40 */
uint32_t sango_city_list_enemy_rulers(uint32_t param_1, int param_2)
{
    uint8_t bVar1;
    int iVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    char *pcVar5;
    uint32_t uVar6;

    uVar6 = 0;
    uVar3 = 0;
    do
    {
        iVar2 = uVar3 * 0x24;
        uVar4 = (uint32_t)(uint8_t)(&g_first_city_owner)[iVar2];
        uVar3 = uVar3 + 1 & 0xff;
        if (uVar4 != 0)
        {
            bVar1 = (&g_first_city_governor)[iVar2];
            if ((bVar1 != 0) && (uVar4 != (param_1 & 0xff) + 1))
            {
                pcVar5 = (char *)(param_2 + uVar6);
                if (bVar1 != uVar4)
                {
                    uVar6 = uVar6 + 1 & 0xff;
                    *pcVar5 = bVar1 - 1;
                }
            }
        }
    } while (uVar3 < 0x26);
    return uVar6;
}

/* 原函数 0x81c13ab8 */
uint32_t sango_faction_list_characters(uint32_t param_1, int param_2)
{
    int iVar1;
    uint8_t *pbVar2;
    int iVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;

    uVar7 = 0;
    uVar6 = 0;
    do
    {
        iVar3 = uVar6 * 0x24;
        if ((uint32_t)(uint8_t)(&g_first_city_owner)[iVar3] == (param_1 & 0xff) + 1)
        {
            uVar5 = 0;
            uVar4 = 0;
            if ((&g_first_city_character_count)[iVar3] != '\0')
            {
                do
                {
                    iVar1 = uVar4 + (uint8_t)(&g_first_city_character_start)[iVar3];
                    uVar4 = uVar4 + 1 & 0xff;
                    pbVar2 = (uint8_t *)(param_2 + uVar7 + uVar5);
                    if (*(char *)((uint32_t)(uint8_t)(&g_city_character_roster)[iVar1] * 0x10 +
                                  g_character_table_address + 1) == (&g_first_city_owner)[iVar3])
                    {
                        uVar5 = uVar5 + 1 & 0xff;
                        *pbVar2 = (&g_city_character_roster)[iVar1];
                    }
                } while (uVar4 < (uint8_t)(&g_first_city_character_count)[iVar3]);
            }
            uVar7 = uVar7 + uVar5 & 0xff;
        }
        uVar6 = uVar6 + 1 & 0xff;
    } while (uVar6 < 0x26);
    return uVar7;
}

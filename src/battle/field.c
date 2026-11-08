#include "sango_internal.h"

/* 战场初始化、日更新与地图绘制。 */

/* 原函数 0x81c03c98 */
uint32_t sango_battle_initialize_field(void)
{
    int iVar1;
    char cVar2;
    char cVar3;
    uint8_t *map;
    uint32_t uVar5;
    uint32_t spawn_x;
    uint32_t spawn_y;
    uint32_t uVar8;
    char *pcVar9;
    char *pcVar10;
    uint32_t tile_index;
    int iVar12;
    char cVar13;
    char cVar14;
    char cVar15;
    char cVar16;

    map = (uint8_t *)sango_battle_resource_item((uint32_t)g_battle_map_resource, '\x01');
    if (map == (uint8_t *)0x0)
    {
        g_battle_load_failed = 1;
        uVar8 = 1;
    }
    else
    {
        g_battle_map_width = *map;
        g_battle_map_height = map[2];
        g_battle_tileset_resource = 4;
        tile_index = 0;
        if (map[0x10] != 3)
        {
            uVar5 = 1;
            do
            {
                tile_index = uVar5 & 0xffff;
                uVar5 = tile_index + 1;
            } while ((map + 0x10)[tile_index] != 3);
        }
        uVar5 = (uint32_t)g_battle_map_width;
        if (uVar5 == 0)
        {
            sango_legacy_trap(7);
        }
        g_battle_spawn_x_view2 = (char)(tile_index % uVar5);
        cVar3 = g_battle_spawn_x_view2 + -2;
        g_battle_spawn_y_view2 = (char)(tile_index / uVar5);
        cVar2 = g_battle_spawn_y_view2 + -2;
        spawn_x = sango_battle_spawn_origin('x');
        spawn_y = sango_battle_spawn_origin('y');
        tile_index = 8;
        uVar5 = (uint32_t)g_battle_entry_direction;
        cVar16 = cVar3;
        cVar15 = cVar2;
        cVar14 = (char)spawn_x;
        cVar13 = (char)spawn_y;
        if (g_battle_control_mode == '\x01')
        {
            uVar5 = 8;
            tile_index = (uint32_t)g_battle_entry_direction;
            cVar16 = (char)spawn_x;
            cVar15 = (char)spawn_y;
            cVar14 = cVar3;
            cVar13 = cVar2;
        }
        spawn_x = sango_battle_resource_item(2, '\x05');
        spawn_y = 0;
        do
        {
            iVar12 = (spawn_y & 0x7f) * 2;
            pcVar9 = (char *)(spawn_x + tile_index * 0x14 + iVar12);
            iVar1 = spawn_y * 7;
            (&g_first_unit_x)[iVar1] = *pcVar9 + cVar16;
            pcVar10 = (char *)(spawn_x + uVar5 * 0x14 + iVar12);
            (&g_first_unit_y)[iVar1] = pcVar9[1] + cVar15;
            spawn_y = spawn_y + 1 & 0xff;
            (&g_second_side_first_x)[iVar1] = cVar14 + *pcVar10;
            (&g_second_side_first_y)[iVar1] = cVar13 + pcVar10[1];
        } while (spawn_y < 10);
        uVar8 = 0;
    }
    return uVar8;
}

/* 原函数 0x81c03ea8 */
uint32_t sango_battle_spawn_origin(char param_1)
{
    uint32_t uVar1;
    uint32_t uVar2;

    uVar1 = g_battle_map_width - 5 & 0xff;
    uVar2 = g_battle_map_height - 5 & 0xff;
    switch (g_battle_entry_direction)
    {
    case 0:
        uVar1 = (g_battle_map_width >> 1) - 2 & 0xff;
        goto LAB_81c03f04;
    case 1:
        uVar2 = 2;
        break;
    case 2:
        uVar2 = (g_battle_map_height >> 1) - 2 & 0xff;
        break;
    case 4:
        uVar1 = (g_battle_map_width >> 1) - 2 & 0xff;
        break;
    case 6:
        uVar2 = (g_battle_map_height >> 1) - 2 & 0xff;
    case 5:
        uVar1 = 2;
        break;
    case 7:
        uVar1 = 0;
    LAB_81c03f04:
        uVar2 = 0;
    }
    if (param_1 != 'x')
    {
        uVar1 = uVar2;
    }
    return uVar1;
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
    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint32_t uVar4;

    uVar4 = 0;
    uVar2 = (uint32_t)*g_temp_character_ids_address;
    uVar3 = (uint32_t)g_battle_cursor_y - (uint32_t)g_temp_character_ids_address[2] & 0xff;
    uVar1 = (uint32_t)g_battle_cursor_x - (uint32_t)g_temp_character_ids_address[1] & 0xff;
    if ((uVar3 < uVar2) && (uVar1 < uVar2))
    {
        uVar4 = (uint32_t)(g_temp_character_ids_address[uVar1 + uVar3 * uVar2 + 3] == 1);
    }
    return uVar4;
}

/* 原函数 0x81c04064 */
/* 推进战斗天数，处理粮草/状态及已修复的居中弹窗。 */
void sango_battle_advance_day(void)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define acStack_30 (*(char(*)[32])(abi_storage + 8))

    int iVar2;
    uint32_t uVar3;

    g_battle_day = g_battle_day + 1;
    g_battle_recon_food = 0;
    uVar3 = 0;
    if (g_battle_day < 0x1f)
    {
        iVar2 = 0;
        do
        {
            iVar2 = iVar2 - uVar3;
            uVar3 = uVar3 + 1 & 0xff;
            (&g_first_unit_has_acted)[iVar2] = 0;
            iVar2 = uVar3 << 3;
        } while (uVar3 < 0x14);
        sango_battle_change_weather();
        sango_battle_day_popup_draw((uint32_t)g_battle_day);
        sango_input_wait(0x32, '\0');
        if (g_battle_defender_food_view2 == 0)
        {
            g_battle_result = '\x01';
            uVar3 = 0x26;
        }
        if (g_battle_attacker_food_view2 == 0)
        {
            g_battle_result = '\x02';
            uVar3 = 0x25;
        }
        if (g_battle_result != '\0')
        {
            sango_battle_load_text(uVar3, acStack_30);
            sango_ui_show_message(acStack_30, 1);
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
#undef acStack_30

/* 原函数 0x81c041f8 */
void sango_battle_scroll_viewport(char param_1)
{
    uint8_t bVar1;
    uint8_t bVar2;

    if (param_1 != '\0')
    {
        return;
    }
    bVar1 = g_battle_viewport_x - 1;
    bVar2 = g_battle_viewport_y;
    if ((uint32_t)g_battle_viewport_x <= (uint32_t)g_battle_cursor_x)
    {
        if ((uint32_t)g_battle_cursor_y < (uint32_t)g_battle_viewport_y)
        {
            bVar1 = g_battle_viewport_x;
            bVar2 = g_battle_viewport_y - 1;
        }
        else
        {
            bVar1 = g_battle_viewport_x + 1;
            if (((uint32_t)g_battle_cursor_x < g_battle_viewport_x + 0xf) &&
                (bVar1 = g_battle_viewport_x, bVar2 = g_battle_viewport_y + 1,
                 (uint32_t)g_battle_cursor_y < g_battle_viewport_y + 0xf))
                goto LAB_81c04248;
        }
    }
    g_battle_viewport_y = bVar2;
    g_battle_viewport_x = bVar1;
    sango_battle_draw_terrain((uint32_t)g_battle_viewport_x, (uint32_t)g_battle_viewport_y);
LAB_81c04248:
    sango_battle_draw_hud();
    sango_battle_draw_cursor_description();
    return;
}

/* 原函数 0x81c042c4 */
void sango_battle_tick_unit_statuses(void)
{
    bool bVar1;
    bool bVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    char cVar5;
    int iVar6;
    uint16_t uVar7;
    int iVar8;
    uint32_t uVar9;

    if (g_battle_result != '\0')
    {
        return;
    }
    uVar4 = 0;
    iVar8 = 0;
LAB_81c042fc:
    cVar5 = (&g_first_unit_status)[iVar8 - uVar4];
    if (cVar5 != '\b')
    {
        uVar3 = sango_battle_unit_character(uVar4);
        uVar9 = 0;
        iVar6 = g_character_table_address + uVar3 * 0x10;
        uVar3 = bbk_rand();
        uVar7 = *(uint16_t *)(iVar6 + 10);
        bVar2 = false;
        bVar1 = (int)uVar3 % 0x3c < (int)(uint32_t)(*(uint8_t *)(iVar6 + 4) >> 1);
        switch (cVar5)
        {
        default:
            break;
        case '\x01':
        case '\x02':
        case '\x03':
            goto switchD_81c043d0_caseD_1;
        case '\x04':
        case '\a':
            if (!bVar1)
                goto LAB_81c04450;
            goto LAB_81c0431c;
        case '\x06':
            goto switchD_81c043d0_caseD_6;
        }
    }
switchD_81c043d0_caseD_0:
LAB_81c0431c:
    uVar4 = uVar4 + 1 & 0xff;
    iVar8 = uVar4 << 3;
    if (0x13 < uVar4)
    {
        return;
    }
    goto LAB_81c042fc;
switchD_81c043d0_caseD_6:
    uVar9 = (uint32_t)(uVar7 >> 3);
    uVar7 = uVar7 - (uVar7 >> 3);
switchD_81c043d0_caseD_1:
    if (bVar1)
    {
        sango_battle_remove_unit_status(uVar4);
    LAB_81c04450:
        cVar5 = '\0';
        bVar2 = true;
    }
    if (uVar9 != 0)
    {
        sango_battle_redraw_field(uVar4);
        sango_battle_show_unit_delta('-', uVar4, uVar9);
        *(uint16_t *)(iVar6 + 10) = uVar7;
    }
    if (!bVar2)
        goto switchD_81c043d0_caseD_0;
    (&g_first_unit_status)[iVar8 - uVar4] = cVar5;
    sango_battle_redraw_field(uVar4);
    sango_battle_blink_unit(uVar4, 4);
    goto LAB_81c0431c;
}

/* 原函数 0x81c04468 */
void sango_battle_redraw_field(uint32_t param_1)
{
    int iVar1;
    uint32_t uVar2;
    uint32_t uVar3;

    iVar1 = (param_1 & 0xff) * 7;
    g_battle_cursor_x = (&g_first_unit_x)[iVar1];
    g_battle_cursor_y = (&g_first_unit_y)[iVar1];
    uVar2 = 0;
    if (6 < g_battle_cursor_x)
    {
        uVar2 = g_battle_cursor_x - 7 & 0xffff;
    }
    uVar3 = 0;
    if (4 < g_battle_cursor_y)
    {
        uVar3 = g_battle_cursor_y - 5 & 0xffff;
    }
    sango_battle_draw_terrain(uVar2, uVar3);
    sango_battle_draw_units(0);
    sango_battle_draw_cursor_description();
    sango_battle_present();
    return;
}

/* 原函数 0x81c044f8 */
void sango_battle_show_unit_delta(char param_1, uint32_t param_2, uint32_t param_3)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define auStack_17 (*(uint8_t(*)[15])(abi_storage + 1))
#define local_18 (*(char *)(abi_storage + 0))

    int iVar1;

    local_18 = param_1;
    sango_format_integer(param_3 & 0xffff, auStack_17, 10);
    iVar1 = (param_2 & 0xff) * 7;
    sango_text_draw_legacy(
        ((uint16_t)(uint8_t)(&g_first_unit_x)[iVar1] - (uint16_t)g_battle_viewport_x) * 0x10 & 0xff,
        ((uint16_t)(uint8_t)(&g_first_unit_y)[iVar1] - (uint16_t)g_battle_viewport_y) * 0x10 & 0xff,
        &local_18);
    sango_input_wait(0x32, '\0');
    return;
}
#undef auStack_17
#undef local_18

/* 原函数 0x81c04590 */
void sango_battle_blink_unit(uint32_t param_1, uint8_t param_2)
{
    int iVar1;
    uint8_t bVar2;

    sango_battle_draw_units(0);
    iVar1 = (param_1 & 0xff) * 7;
    bVar2 = 1;
    while (true)
    {
        sango_battle_present();
        if (param_2 < bVar2)
            break;
        sango_input_wait(10, '\0');
        sango_battle_draw_tile((uint32_t)(uint8_t)(&g_first_unit_x)[iVar1],
                               (uint32_t)(uint8_t)(&g_first_unit_y)[iVar1], '\x01');
        sango_input_wait(10, '\0');
        bVar2 = bVar2 + 1;
    }
    return;
}

/* 原函数 0x81c04630 */
void sango_battle_draw_units(uint32_t param_1)
{
    char cVar1;
    uint8_t bVar2;
    uint32_t uVar3;
    int iVar4;
    short sVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint32_t uVar8;
    uint32_t uVar9;

    uVar8 = 0;
    do
    {
        iVar4 = uVar8 * 7;
        cVar1 = (&g_first_unit_status)[iVar4];
        if (cVar1 != '\b')
        {
            uVar7 = (uint32_t)(uint8_t)(&g_first_unit_x)[iVar4];
            bVar2 = (&g_first_unit_y)[iVar4];
            uVar9 = (uint32_t)bVar2;
            if ((((g_battle_viewport_x <= uVar7) && (uVar7 < g_battle_viewport_x + 0xf)) &&
                 (g_battle_viewport_y <= uVar9)) &&
                (uVar9 < g_battle_viewport_y + 0xf))
            {
                uVar3 = sango_battle_unit_sprite_frame(uVar8);
                if ((&g_first_unit_has_acted)[iVar4] == '\0')
                {
                    uVar3 = uVar3 + (param_1 & 0xff) & 0xff;
                }
                sVar5 = ((uint16_t)bVar2 - (uint16_t)g_battle_viewport_y) * 0x10;
                uVar6 = (uVar7 - g_battle_viewport_x) * 0x10 & 0xffff;
                sango_battle_draw_tile(uVar7, uVar9, '\0');
                sango_battle_draw_bitmap(5, uVar3 + 1 & 0xff, uVar6, sVar5);
                iVar4 = 2;
                if ((cVar1 == '\x02') || (iVar4 = 4, cVar1 == '\x03'))
                {
                    sango_battle_draw_bitmap(0x22, iVar4 + (param_1 & 0xff) + 1 & 0xff, uVar6,
                                             sVar5);
                }
            }
        }
        uVar8 = uVar8 + 1 & 0xff;
    } while (uVar8 < 0x14);
    return;
}

/* 原函数 0x81c047bc */
void sango_battle_draw_tile(uint32_t param_1, uint32_t param_2, char param_3)
{
    uint8_t bVar1;
    uint32_t uVar2;
    int iVar3;
    uint16_t uVar4;
    uint32_t uVar5;

    bVar1 = *(
        uint8_t *)(g_viewport_tiles_address +
                   ((((param_2 & 0xff) - (uint32_t)g_battle_viewport_y) * 0xf + (param_1 & 0xff)) -
                        (uint32_t)g_battle_viewport_x &
                    0xff));
    uVar2 = sango_battle_resource_item((uint32_t)g_battle_tileset_resource, '\x01');
    uVar5 = ((param_1 & 0xff) - (uint32_t)g_battle_viewport_x) * 0x10 & 0xff;
    uVar4 = ((short)(param_2 & 0xff) - (uint16_t)g_battle_viewport_y) * 0x10 & 0xff;
    iVar3 = uVar2 + (uint32_t)bVar1 * 0x40 + 6;
    if (param_3 == '\0')
    {
        sango_raster_draw_opaque(uVar5, uVar4, 0x10, 0x10, iVar3, g_game_context);
    }
    else
    {
        sango_raster_draw_screen(uVar5, uVar4, 0x10, 0x10, iVar3);
    }
    return;
}

/* 原函数 0x81c048bc */
void sango_battle_show_action_message(uint32_t param_1)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define acStack_30 (*(char(*)[24])(abi_storage + 0))
#define acStack_18 (*(char(*)[8])(abi_storage + 24))

    sango_battle_load_text(0x16, acStack_30);
    sango_format_integer(param_1 & 0xff, acStack_18, 10);
    sango_crt_strcat(acStack_30, acStack_18);
    sango_battle_show_short_message(acStack_30, 1, 0xff);
    return;
}
#undef acStack_30
#undef acStack_18

/* 原函数 0x81c04920 */
void sango_battle_check_level_and_retreat(void)
{
    uint8_t bVar1;
    uint8_t bVar2;
    char cVar3;
    int iVar4;
    char *pcVar5;
    uint8_t bVar6;
    uint32_t uVar7;
    uint32_t uVar8;
    int iVar9;
    uint32_t uVar10;

    pcVar5 = g_scratch_buffer_address;
    uVar10 = 0;
    do
    {
        iVar4 = uVar10 * 7;
        if ((&g_first_unit_status)[iVar4] != '\b')
        {
            uVar7 = sango_battle_unit_character(uVar10);
            bVar1 = (&g_first_unit_x)[iVar4];
            bVar2 = (&g_first_unit_y)[iVar4];
            iVar9 = g_character_table_address + uVar7 * 0x10;
            uVar8 = bbk_rand();
            uVar8 = (int)uVar8 % 3 & 0xff;
            if (*(uint8_t *)(iVar9 + 7) < 100)
            {
                cVar3 = (&g_first_unit_life)[iVar4];
            }
            else
            {
                sango_battle_redraw_field(uVar10);
                bVar6 = *(char *)(iVar9 + 2) + 1;
                *(char *)(iVar9 + 7) = *(char *)(iVar9 + 7) + -100;
                *(uint8_t *)(iVar9 + 2) = bVar6;
                if (0x14 < bVar6)
                {
                    *(uint8_t *)(iVar9 + 2) = 0x14;
                }
                sango_battle_play_unit_effect(0, 5, (uint16_t)bVar1, (uint16_t)bVar2);
                sango_battle_load_text(uVar8 + 0x27 & 0xff, pcVar5);
                sango_ui_show_character_message((uint8_t)uVar7, pcVar5);
                cVar3 = (&g_first_unit_life)[iVar4];
            }
            if ((cVar3 == '\0') || (*(short *)(iVar9 + 10) == 0))
            {
                sango_battle_redraw_field(uVar10);
                (&g_first_unit_status)[iVar4] = 8;
                sango_battle_play_unit_effect(6, 0xb, (uint16_t)bVar1, (uint16_t)bVar2);
                sango_battle_load_text(uVar8 + 0x2a & 0xff, pcVar5);
                sango_ui_show_character_message((uint8_t)uVar7, pcVar5);
            }
        }
        uVar10 = uVar10 + 1 & 0xff;
    } while (uVar10 < 0x14);
    return;
}

/* 原函数 0x81c04ae8 */
void sango_battle_play_unit_effect(uint32_t param_1, uint32_t param_2, uint16_t param_3,
                                   uint16_t param_4)
{
    uint16_t uVar1;
    uint16_t uVar2;

    uVar1 = (uint16_t)g_battle_viewport_x;
    if ((uVar1 <= param_3) && (param_3 < (uint16_t)(uVar1 + 0xf)))
    {
        uVar2 = (uint16_t)g_battle_viewport_y;
        if (uVar2 <= param_4)
        {
            if (param_4 < (uint16_t)(uVar2 + 0xf))
            {
                sango_animation_play_range(0x1b, param_1 & 0xff, param_2 & 0xff, 0,
                                           (param_3 - uVar1) * 0x10, (param_4 - uVar2) * 0x10);
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
void sango_battle_check_finish(char param_1)
{
    int iVar1;
    uint32_t uVar2;

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
        if (param_1 == '\0')
        {
            g_battle_result = '\x01';
            uVar2 = 10;
        }
        else
        {
            uVar2 = 0;
            g_battle_result = '\x02';
        }
        if (uVar2 < 0x14)
        {
            while (true)
            {
                iVar1 = uVar2 * 7;
                uVar2 = uVar2 + 1 & 0xff;
                if ((&g_first_unit_status)[iVar1] != '\b')
                    break;
                if (0x13 < uVar2)
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
uint32_t sango_battle_unit_character(uint32_t param_1)
{
    return (uint8_t)(&g_battle_roster_first)[param_1 & 0xff] - 1 & 0xff;
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

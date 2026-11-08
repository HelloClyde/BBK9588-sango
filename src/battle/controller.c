#include "sango_internal.h"

/* 战斗主循环与界面恢复。 */

/* 原函数 0x81c04fe0 */
/* 战斗主流程：准备阵列，交替执行玩家和电脑回合，检查结束条件。 */
uint32_t sango_battle_run(void)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define ai_action (*(uint8_t(*)[8])(abi_storage + 0))

    int ai_action_ready;
    uint32_t action_result;
    int status_offset;
    uint32_t unit_index;

    g_battle_weather = 3;
    g_battle_result = '\0';
    g_battle_day = 0;
    if (g_battle_control_mode == '\x01')
    {
        g_battle_player_unit_begin = 0;
    }
    else
    {
        g_battle_player_unit_begin = 10;
    }
    sango_battle_initialize_unit_stats();
    if (g_battle_result == '\0')
    {
        if (g_battle_control_mode == '\x02')
        {
            sango_battle_choose_auto_result();
        }
        else
        {
            sango_battle_initialize_field();
            sango_battle_draw_hud();
            sango_battle_redraw_field(10);
            sango_input_wait(100, '\0');
            sango_battle_redraw_field(0);
            sango_input_wait(100, '\0');
            sango_battle_check_level_and_retreat();
            sango_battle_check_finish('\0');
            sango_battle_check_finish('\x01');
        }
    }
    do
    {
        if (g_battle_result != '\0')
        {
            return 0;
        }
        sango_battle_advance_day();
        sango_battle_run_player_turn();
        while (g_battle_result == '\0')
        {
            ai_action_ready = sango_battle_plan_ai_action(ai_action);
            if (ai_action_ready == 0)
                break;
            action_result = sango_battle_finish_unit_action(ai_action);
            if ((g_battle_control_mode == '\0') && (action_result == 5))
            {
                g_battle_result = '\x02';
            }
            else
            {
                sango_battle_check_finish('\x01');
            }
        }
        if (g_battle_result == '\0')
        {
            unit_index = 0;
            g_battle_result = '\x02';
            status_offset = 0;
            do
            {
                /* 原记录步长为7；保留地址运算和8位回绕，避免改变旧布局。 */
                status_offset = status_offset - unit_index;
                unit_index = unit_index + 1 & 0xff;
                if ((&g_first_unit_status)[status_offset] != SANGO_UNIT_RETIRED)
                {
                    g_battle_result = '\0';
                    break;
                }
                status_offset = unit_index << 3;
            } while (unit_index < SANGO_UNITS_PER_SIDE);
        }
        sango_battle_consume_daily_food();
    } while (true);
}
#undef ai_action

/* 原函数 0x81c051e8 */
void sango_battle_begin(void)
{
    g_battle_weather = 3;
    g_battle_result = '\0';
    g_battle_day = 0;
    if (g_battle_control_mode == '\x01')
    {
        g_battle_player_unit_begin = 0;
    }
    else
    {
        g_battle_player_unit_begin = 10;
    }
    sango_battle_initialize_unit_stats();
    if (g_battle_result == '\0')
    {
        if (g_battle_control_mode == '\x02')
        {
            sango_battle_choose_auto_result();
        }
        else
        {
            sango_battle_initialize_field();
            sango_battle_draw_hud();
            sango_battle_redraw_field(10);
            sango_input_wait(100, '\0');
            sango_battle_redraw_field(0);
            sango_input_wait(100, '\0');
            sango_battle_check_level_and_retreat();
            sango_battle_check_finish('\0');
            sango_battle_check_finish('\x01');
        }
    }
    return;
}

/* 原函数 0x81c052cc */
void sango_battle_run_ai_turn(void)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define ai_action (*(uint8_t(*)[8])(abi_storage + 0))

    int ai_action_ready;
    uint32_t action_result;
    int status_offset;
    uint32_t unit_index;

    if (g_battle_result == '\0')
    {
        do
        {
            ai_action_ready = sango_battle_plan_ai_action(ai_action);
            if (ai_action_ready == 0)
                break;
            action_result = sango_battle_finish_unit_action(ai_action);
            if ((g_battle_control_mode == '\0') && (action_result == 5))
            {
                g_battle_result = '\x02';
            }
            else
            {
                sango_battle_check_finish('\x01');
            }
        } while (g_battle_result == '\0');
    }
    if (g_battle_result == '\0')
    {
        unit_index = 0;
        g_battle_result = '\x02';
        do
        {
            status_offset = unit_index * SANGO_BATTLE_UNIT_STRIDE;
            unit_index = unit_index + 1 & 0xff;
            if ((&g_first_unit_status)[status_offset] != SANGO_UNIT_RETIRED)
            {
                g_battle_result = 0;
                return;
            }
        } while (unit_index < SANGO_UNITS_PER_SIDE);
    }
    return;
}
#undef ai_action

/* 原函数 0x81c053c4 */
void sango_battle_refresh_target_preview(char redraw_markers)
{
    if (redraw_markers == '\0')
    {
        sango_battle_scroll_viewport('\0');
    }
    else
    {
        sango_battle_draw_target_markers();
    }
    return;
}

/* 原函数 0x81c05400 */
void sango_battle_refresh_move_preview(char redraw_range)
{
    if (redraw_range == '\0')
    {
        sango_battle_scroll_viewport('\0');
    }
    else
    {
        sango_battle_draw_move_range();
    }
    return;
}

/* 原函数 0x81c0543c */
uint32_t sango_battle_reset_session(void)
{
    g_battle_weather = 3;
    g_battle_result_view2 = 0;
    g_battle_day = 0;
    if (g_battle_control_mode == '\x01')
    {
        g_battle_player_unit_begin = 0;
    }
    else
    {
        g_battle_player_unit_begin = 10;
    }
    sango_battle_initialize_unit_stats();
    return 0;
}

/* 原函数 0x81c054a0 */
void sango_battle_refresh_display(void)
{
    sango_battle_draw_hud();
    sango_battle_redraw_field(10);
    sango_input_wait(100, '\0');
    sango_battle_redraw_field(0);
    sango_input_wait(100, '\0');
    return;
}

/* 原函数 0x81c054e4 */
void sango_battle_focus_viewport(void)
{
    uint8_t bVar1;
    uint8_t bVar2;

    bVar1 = g_battle_viewport_x - 1;
    bVar2 = g_battle_viewport_y;
    if ((uint32_t)g_battle_viewport_x <= (uint32_t)g_battle_cursor_x)
    {
        bVar1 = g_battle_viewport_x;
        bVar2 = g_battle_viewport_y - 1;
        if ((uint32_t)g_battle_viewport_y <= (uint32_t)g_battle_cursor_y)
        {
            bVar1 = g_battle_viewport_x + 1;
            bVar2 = g_battle_viewport_y;
            if (((uint32_t)g_battle_cursor_x < g_battle_viewport_x + 0xf) &&
                (bVar1 = g_battle_viewport_x, bVar2 = g_battle_viewport_y + 1,
                 (uint32_t)g_battle_cursor_y < g_battle_viewport_y + 0xf))
            {
                return;
            }
        }
    }
    g_battle_viewport_y = bVar2;
    g_battle_viewport_x = bVar1;
    sango_battle_draw_terrain((uint32_t)g_battle_viewport_x, (uint32_t)g_battle_viewport_y);
    return;
}

/* 原函数 0x81c055b0 */
void sango_battle_show_cursor_info(void)
{
    unsigned char abi_storage[80] __attribute__((aligned(8)));
#define local_28 (*(uint16_t(*)[8])(abi_storage + 48))
#define acStack_58 (*(char(*)[16])(abi_storage + 0))
#define auStack_48 (*(uint8_t(*)[32])(abi_storage + 16))

    char *destination;
    uint32_t uVar1;
    uint8_t *pbVar2;
    int iVar3;
    int iVar4;

    sango_display_fill_gray_rectangle(5, 5, 0xe9, 0x139, 0, 0);
    sango_display_draw_rectangle(4, 4, 0xea, 0x13a, 3, 0, 0);
    destination = (char *)bbk_alloc(0x96);
    if (destination != (char *)0x0)
    {
        uVar1 = sango_battle_find_unit_at((uint16_t)g_battle_cursor_x, (uint16_t)g_battle_cursor_y);
        if (uVar1 == 0xff)
        {
            iVar3 =
                sango_battle_terrain_at((uint32_t)g_battle_cursor_x, (uint32_t)g_battle_cursor_y);
            sango_battle_read_text(iVar3 + 0xeU & 0xff, destination);
            g_text_top = 8;
            g_text_right = 0xe6;
            g_text_bottom = 0x136;
            g_text_left = 8;
            sango_text_draw_legacy(8, 8, destination);
        }
        else
        {
            iVar3 = uVar1 * 7;
            sango_display_draw_rectangle(0xb6, 8, 0xe8, 0x30, 3, 0, 0);
            local_28[1] = 6;
            local_28[4] = 0xb4;
            local_28[3] = 0x138;
            local_28[5] = 8;
            local_28[0] = 8;
            local_28[6] = 0xe8;
            local_28[2] = 0xe8;
            local_28[7] = 0x32;
            sango_battle_prepare_combatant(0, uVar1);
            uVar1 = sango_battle_resolve_character(uVar1);
            sango_load_named_text((uint8_t)uVar1, acStack_58);
            sango_text_draw_centered(0xd0, 0x24, acStack_58);
            pbVar2 = (uint8_t *)sango_resource_item(g_scenario_id_view2 + 0x2f, '\x01',
                                                    g_resource_package_address);
            sango_bitmap_draw_frame_screen(0xc3, 10, 0x18, 0x18, (uint8_t)uVar1, pbVar2);
            sango_battle_read_text(0xd, destination);
            iVar4 = g_character_table_address + uVar1 * 0x10;
            if (*(uint8_t *)(iVar4 + 2) < 0x14)
            {
                sango_battle_append_stat_value(destination, (uint32_t) * (uint8_t *)(iVar4 + 2));
            }
            else
            {
                destination[5] = 'M';
                destination[6] = 'X';
            }
            sango_battle_read_text(0xc, auStack_48);
            bbk_memcpy(destination + 0xd, auStack_48 + (*(uint8_t *)(iVar4 + 9) & 0x3f) * 4, 4);
            sango_battle_append_stat_value(destination, (uint32_t) * (uint8_t *)(iVar4 + 3));
            sango_battle_append_stat_value(destination, (uint32_t) * (uint8_t *)(iVar4 + 4));
            sango_battle_append_stat_value(destination, (uint32_t) * (uint8_t *)(iVar4 + 7));
            sango_battle_append_stat_value(destination,
                                           (uint32_t)(uint8_t)(&g_first_unit_life)[iVar3]);
            sango_battle_append_stat_value(destination,
                                           (uint32_t)(uint8_t)(&g_first_unit_energy)[iVar3]);
            sango_battle_append_stat_value(destination, (uint32_t)g_attacker_attack_view2);
            sango_battle_append_stat_value(destination, (uint32_t)g_attacker_defense);
            sango_battle_append_stat_value(destination, (uint32_t) * (uint16_t *)(iVar4 + 10));
            sango_battle_read_text((uint8_t)(&g_first_unit_status)[iVar3] + 0x1c & 0xff,
                                   acStack_58);
            bbk_strcat(destination, acStack_58);
            sango_text_draw_wrapped_box(local_28, local_28 + 4, destination);
        }
        sango_input_wait(100, '\x01');
        bbk_free_if_nonnull(destination);
    }
    return;
}
#undef local_28
#undef acStack_58
#undef auStack_48

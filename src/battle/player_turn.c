#include "sango_internal.h"

/* 部队回合、操作命令与目标输入。 */

/* 原函数 0x81c02f4c */
uint32_t sango_battle_plan_ai_action(uint8_t *action)
{
    uint8_t target_unit;
    int unit_offset;
    uint32_t planned_unit;
    uint32_t has_action;

    planned_unit = sango_battle_ai_plan_unit(action);
    has_action = 0;
    if (planned_unit != 0xff)
    {
        if (*action < 2)
        {
            target_unit = action[3];
            sango_battle_redraw_field((uint32_t)target_unit);
            unit_offset = (uint32_t)target_unit * 7;
            sango_animation_play_range(0x1b, 0xc, 0x11, 0,
                                       ((uint16_t)(uint8_t)(&g_first_unit_x)[unit_offset] -
                                        (uint16_t)g_battle_viewport_x) *
                                           0x10,
                                       ((uint16_t)(uint8_t)(&g_first_unit_y)[unit_offset] -
                                        (uint16_t)g_battle_viewport_y) *
                                           0x10);
            has_action = 1;
        }
        else
        {
            has_action = 1;
        }
    }
    return has_action;
}

/* 原函数 0x81c03020 */
void sango_battle_run_player_turn(void)
{
    unsigned char abi_storage[19] __attribute__((aligned(8)));
#define auStack_20 (*(uint8_t(*)[2])(abi_storage + 0))
#define local_1e (*(uint8_t *)(abi_storage + 2))

    char cVar1;
    int iVar2;
    uint32_t uVar3;

    if (g_battle_result == '\0')
    {
        uVar3 = 0;
        g_battle_result = '\x02';
        iVar2 = 0;
        do
        {
            if ((&g_first_unit_status)[iVar2 - uVar3] != '\b')
            {
                g_battle_result = '\0';
                break;
            }
            uVar3 = uVar3 + 1 & 0xff;
            iVar2 = uVar3 << 3;
        } while (uVar3 < 10);
        sango_battle_redraw_field(uVar3);
        cVar1 = g_battle_result;
        while (
            (g_battle_result = cVar1,
             g_battle_result == '\0' && (uVar3 = sango_battle_select_active_unit(), uVar3 != 0xff)))
        {
            iVar2 = sango_battle_select_move_destination(uVar3);
            cVar1 = g_battle_result;
            if (iVar2 == 0)
            {
                local_1e = (uint8_t)uVar3;
                sango_battle_show_unit_commands((char *)auStack_20);
                uVar3 = sango_battle_finish_unit_action(auStack_20);
                if ((g_battle_control_mode != '\x01') || (cVar1 = '\x01', uVar3 != 5))
                {
                    sango_battle_check_finish('\0');
                    cVar1 = g_battle_result;
                }
            }
        }
    }
    return;
}
#undef auStack_20
#undef local_1e

/* 原函数 0x81c03154 */
void sango_battle_show_unit_commands(char *action)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define menu_bounds (*(uint16_t(*)[4])(abi_storage + 0))

    bool choosing_target;
    char command;
    uint8_t *menu_text;
    uint32_t menu_selection;
    uint32_t skill_id;
    uint32_t unit_id;
    uint32_t target_id;

    unit_id = (uint32_t)(uint8_t)action[2];
    choosing_target = true;
    sango_battle_unit_character(unit_id);
    menu_text = (uint8_t *)bbk_alloc(100);
    menu_selection = 0;
    do
    {
        skill_id = 0;
        sango_battle_present();
        sango_battle_filter_unit_commands(unit_id, menu_bounds);
        sango_battle_load_text(8, menu_text);
        menu_selection = sango_ui_choose_option(menu_bounds, menu_selection, (char *)menu_text);
        command = (char)menu_selection;
        *action = command;
        if (menu_selection == 2)
        {
            skill_id = 0xff;
            sango_battle_show_cursor_info();
        }
        else if ((int)menu_selection < 3)
        {
            if ((menu_selection == 1) &&
                (skill_id = 0xff, (&g_first_unit_status)[unit_id * 7] != '\x02'))
            {
                skill_id = sango_battle_choose_skill(unit_id, menu_bounds, menu_text);
            }
        }
        else if ((menu_selection == 3) || (menu_selection == 0xff))
            goto release_menu_text;
        if (skill_id != 0xff)
        {
            sango_battle_load_range_template(command, skill_id, unit_id);
            target_id = sango_battle_select_target(command, (char)skill_id, unit_id);
            if (target_id != 0xff)
            {
                choosing_target = false;
            }
        }
    } while (choosing_target);
    action[3] = (char)target_id;
    action[1] = (char)skill_id;
release_menu_text:
    bbk_free_if_nonnull(menu_text);
    return;
}
#undef menu_bounds

/* 原函数 0x81c032d4 */
uint32_t sango_battle_select_target(char param_1, char param_2, uint32_t param_3)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define acStack_40 (*(char(*)[16])(abi_storage + 0))
#define acStack_30 (*(char(*)[16])(abi_storage + 16))

    uint32_t uVar1;
    bool bVar2;
    int iVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    char *pcVar6;
    uint32_t uVar7;

    uVar1 = (uint32_t)(uint8_t)param_2;
    uVar7 = param_3 & 0xff;
    if ((uVar1 != 0x16) && (uVar1 != 0x1e))
    {
        sango_battle_load_text(2, acStack_40);
        sango_battle_load_text(3, acStack_30);
        sango_battle_draw_target_markers();
        while (true)
        {
            sango_battle_present();
            iVar3 = sango_battle_poll_map_action('\x01');
            if (iVar3 == 0xff)
                break;
            uVar4 =
                sango_battle_find_unit_at((uint16_t)g_battle_cursor_x, (uint16_t)g_battle_cursor_y);
            if (uVar4 == 0xff)
            {
                pcVar6 = acStack_40;
            }
            else
            {
                uVar5 = sango_battle_target_side_allowed();
                pcVar6 = acStack_30;
                if (uVar5 != 0)
                {
                    bVar2 = false;
                    if (((uVar7 < 10) && (uVar4 < 10)) || ((10 < uVar7 && (10 < uVar4))))
                    {
                        bVar2 = true;
                    }
                    if (param_1 == '\x01')
                    {
                        iVar3 = sango_battle_skill_terrain_allowed(uVar1, bVar2, uVar4);
                        if (iVar3 != 0)
                        {
                            return uVar4;
                        }
                    }
                    else if (!bVar2)
                    {
                        return uVar4;
                    }
                }
            }
            sango_battle_draw_text(0x6a, 0xf3, pcVar6);
        }
        sango_battle_redraw_field(uVar7);
        uVar7 = 0xff;
    }
    return uVar7;
}
#undef acStack_40
#undef acStack_30

/* 原函数 0x81c0343c */
void sango_battle_draw_target_markers(void)
{
    uint8_t bVar1;
    uint16_t uVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint32_t uVar8;

    uVar7 = (uint32_t)*g_temp_character_ids_address;
    uVar8 = 0;
    if (uVar7 != 0)
    {
        bVar1 = g_temp_character_ids_address[2];
        while (true)
        {
            uVar6 = uVar8 + bVar1 & 0xff;
            if ((g_battle_viewport_y <= uVar6) && (uVar6 < g_battle_viewport_y + 0xf))
            {
                uVar2 = (uint16_t)g_battle_viewport_y;
                uVar5 = 0;
                if (uVar7 != 0)
                {
                    bVar1 = g_temp_character_ids_address[1];
                    while (true)
                    {
                        uVar4 = (uint32_t)g_battle_viewport_x;
                        uVar3 = uVar5 + bVar1 & 0xff;
                        if (((uVar4 <= uVar3) && (uVar3 < uVar4 + 0xf)) &&
                            (g_temp_character_ids_address[uVar8 * uVar7 + uVar5 + 3] == 1))
                        {
                            sango_battle_draw_bitmap(7, 2, (uVar3 - uVar4) * 0x10 & 0xff,
                                                     ((short)uVar6 - uVar2) * 0x10 & 0xff);
                        }
                        uVar5 = uVar5 + 1 & 0xff;
                        if (uVar7 <= uVar5)
                            break;
                        bVar1 = g_temp_character_ids_address[1];
                    }
                }
            }
            uVar8 = uVar8 + 1 & 0xff;
            if (uVar7 <= uVar8)
                break;
            bVar1 = g_temp_character_ids_address[2];
        }
    }
    return;
}

/* 原函数 0x81c03590 */
void sango_battle_filter_unit_commands(uint32_t param_1, uint16_t *param_2)
{
    int iVar1;
    uint16_t uVar2;
    uint16_t uVar3;
    uint16_t uVar4;
    uint32_t uVar5;
    uint16_t uVar6;

    iVar1 = (param_1 & 0xff) * 7;
    uVar5 = (uint32_t)g_battle_viewport_y;
    uVar2 = ((uint16_t)(uint8_t)(&g_first_unit_x)[iVar1] - (uint16_t)g_battle_viewport_x) * 0x10 +
                0x12 &
            0xff;
    uVar3 = uVar2 + 0x18;
    uVar6 = 0x2d;
    uVar4 = 0xfd;
    if (0xef < uVar3)
    {
        uVar2 = uVar2 - 0x28 & 0xff;
        uVar3 = uVar2 + 0x18;
    }
    *param_2 = uVar2;
    param_2[2] = uVar3;
    uVar5 = ((uint8_t)(&g_first_unit_y)[iVar1] - uVar5) * 0x10 & 0xff;
    if (3 < (int)(0x127 - uVar5) / 0xc)
    {
        uVar4 = (short)uVar5 + 4U & 0xff;
        uVar6 = uVar4 + 0x30 & 0xff;
    }
    param_2[3] = uVar6;
    param_2[1] = uVar4;
    return;
}

/* 原函数 0x81c03654 */
uint32_t sango_battle_finish_unit_action(uint8_t *record)
{
    uint8_t bVar1;
    int iVar2;
    uint32_t uVar3;

    bVar1 = record[2];
    uVar3 = sango_battle_execute_action(record);
    if ((uVar3 & 0xff) != 0)
    {
        sango_battle_draw_terrain((uint32_t)g_battle_viewport_x, (uint32_t)g_battle_viewport_y);
        sango_battle_draw_units(0);
        *g_attacker_experience_address_view2 = (char)uVar3 + *g_attacker_experience_address_view2;
        if (bVar1 < 10)
        {
            sango_battle_show_action_message(uVar3 & 0xff);
        }
        sango_battle_check_level_and_retreat();
    }
    iVar2 = (uint32_t)bVar1 * 7;
    uVar3 = sango_battle_terrain_at((uint32_t)(uint8_t)(&g_first_unit_x)[iVar2],
                                    (uint32_t)(uint8_t)(&g_first_unit_y)[iVar2]);
    return uVar3;
}

/* 原函数 0x81c03708 */
uint32_t sango_battle_select_move_destination(uint32_t param_1)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define acStack_28 (*(char(*)[24])(abi_storage + 0))

    int iVar1;
    uint8_t bVar2;
    int iVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;

    uVar6 = param_1 & 0xff;
    iVar1 = uVar6 * 7;
    if ((&g_first_unit_move_range)[iVar1] != '\x01')
    {
        sango_battle_build_move_range(uVar6);
        sango_memory_fill(acStack_28, 0, 0x14);
        sango_battle_load_text(1, acStack_28);
        sango_battle_draw_move_range();
        while (true)
        {
            sango_battle_present();
            iVar3 = sango_battle_poll_map_action('\x02');
            bVar2 = g_battle_cursor_x;
            if (iVar3 == 0xff)
                break;
            uVar5 = (uint32_t)g_move_window_left +
                        ((uint32_t)g_battle_cursor_x - (uint32_t)g_move_source_x) &
                    0xff;
            uVar4 = (uint32_t)g_move_window_top +
                        ((uint32_t)g_battle_cursor_y - (uint32_t)g_move_source_y) &
                    0xff;
            if (((uVar5 < 0x10) && (uVar4 < 0x10)) &&
                (*(uint8_t *)(g_move_costs_address + uVar4 * 0xf + uVar5) < 0x81))
            {
                g_legacy_data_81c2b172 = (&g_first_unit_x)[iVar1];
                g_legacy_data_81c2b148 = (&g_first_unit_y)[iVar1];
                (&g_first_unit_y)[iVar1] = g_battle_cursor_y;
                (&g_first_unit_x)[iVar1] = bVar2;
                sango_battle_redraw_field(uVar6);
                return 0;
            }
            sango_battle_draw_text(0x6a, 0xf3, acStack_28);
        }
        sango_battle_redraw_field(uVar6);
    }
    return 1;
}
#undef acStack_28

/* 原函数 0x81c03874 */
uint32_t sango_battle_select_active_unit(void)
{
    int iVar1;
    uint32_t uVar2;

    sango_battle_draw_terrain((uint32_t)g_battle_viewport_x, (uint32_t)g_battle_viewport_y);
    sango_battle_draw_hud();
    sango_battle_draw_cursor_description();
    do
    {
        while (iVar1 = sango_battle_poll_map_action('\x03'), iVar1 == 0)
        {
            uVar2 = sango_battle_find_actionable_unit_at_cursor();
            if (uVar2 != 0xff)
            {
                return uVar2;
            }
        }
        iVar1 = sango_battle_show_options();
    } while (iVar1 != 0xff);
    return 0xff;
}

/* 原函数 0x81c038f4 */
/* 处理键盘和完整16位触摸坐标；按钮命中后恢复战场HUD。 */
uint32_t sango_battle_poll_map_action(char param_1)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define local_28 (*(int *)(abi_storage + 0))
#define local_24 (*(int *)(abi_storage + 4))

    uint8_t bVar1;
    char cVar2;
    uint32_t uVar3;
    uint32_t unaff_s0;
    uint32_t uVar4;

    uVar4 = 0;
LAB_81c03918:
    sango_input_next_event(&local_28);
    if (local_28 == 5)
    {
        uVar3 = 0;
        if ((local_24 == 0x1c) || (uVar3 = 0xff, local_24 == 1))
        {
            return uVar3;
        }
        sango_battle_draw_tile((uint32_t)g_battle_cursor_x, (uint32_t)g_battle_cursor_y, '\0');
    }
    if (local_28 == 6)
        goto LAB_81c03b8c;
    if (local_28 < 7)
    {
        if (local_28 == 5)
        {
            if (local_24 == 0x67)
            {
                bVar1 = g_battle_cursor_y - 1;
                if (g_battle_cursor_y != 0)
                {
                LAB_81c03aac:
                    g_battle_cursor_y = bVar1;
                }
            }
            else if (local_24 < 0x68)
            {
                if (local_24 == 0x1f)
                {
                    sango_battle_show_overview();
                    sango_battle_draw_hud();
                }
                else if (local_24 == 0x23)
                {
                    sango_battle_show_cursor_info();
                    sango_battle_draw_hud();
                }
            }
            else if (local_24 == 0x6a)
            {
                bVar1 = g_battle_cursor_x + 1;
                if ((int)(uint32_t)g_battle_cursor_x < (int)(g_battle_map_width - 1))
                {
                LAB_81c03a74:
                    g_battle_cursor_x = bVar1;
                }
            }
            else if (local_24 < 0x6b)
            {
                if ((local_24 == 0x69) && (bVar1 = g_battle_cursor_x - 1, g_battle_cursor_x != 0))
                    goto LAB_81c03a74;
            }
            else if ((local_24 == 0x6c) &&
                     (bVar1 = g_battle_cursor_y + 1,
                      (int)(uint32_t)g_battle_cursor_y < (int)(g_battle_map_height - 1)))
                goto LAB_81c03aac;
            if (param_1 == '\x01')
            {
                cVar2 = '\0';
                if (uVar4 == 0)
                    goto LAB_81c039e8;
                sango_battle_draw_target_markers();
            }
            else
            {
                cVar2 = (char)uVar4;
                if ((param_1 == '\x02') && (cVar2 = '\0', uVar4 != 0))
                {
                    sango_battle_draw_move_range();
                }
                else
                {
                LAB_81c039e8:
                    sango_battle_scroll_viewport(cVar2);
                }
            }
        }
    }
    else if (local_28 == 0xb)
    {
        /* Read the original full-width coordinates from the input packet;
              the legacy uint8_t slots wrap y=300 to 44. */
        enum SangoBattleToolbarAction action = sango_battle_toolbar_hit(
            *(uint16_t *)(abi_storage + 8), *(uint16_t *)(abi_storage + 10));
        if (action == SANGO_BATTLE_TOOLBAR_INFO)
        {
            sango_battle_show_cursor_info();
        }
        else if (action == SANGO_BATTLE_TOOLBAR_OVERVIEW)
        {
            sango_battle_show_overview();
        }
        if (action != SANGO_BATTLE_TOOLBAR_NONE)
        {
            sango_battle_draw_hud();
        }
    }
    goto LAB_81c03950;
LAB_81c03b8c:
    unaff_s0 = unaff_s0 + 1 & 0xff;
    if (unaff_s0 % 10 != 0)
        goto LAB_81c03918;
    uVar4 = (uint32_t)(uVar4 == 0);
LAB_81c03950:
    sango_battle_draw_units(uVar4);
    if (param_1 == '\x01')
    {
        cVar2 = '\0';
        if (uVar4 != 0)
        {
            sango_battle_draw_target_markers();
            goto LAB_81c03970;
        }
    }
    else
    {
        cVar2 = (char)uVar4;
        if ((param_1 == '\x02') && (cVar2 = '\0', uVar4 != 0))
        {
            sango_battle_draw_move_range();
            goto LAB_81c03970;
        }
    }
    sango_battle_scroll_viewport(cVar2);
LAB_81c03970:
    sango_battle_draw_cursor();
    goto LAB_81c03918;
}
#undef local_28
#undef local_24

/* 原函数 0x81c03c20 */
void sango_battle_draw_cursor(void)
{
    uint16_t uVar1;

    uVar1 = ((uint16_t)g_battle_cursor_y - (uint16_t)g_battle_viewport_y) * 0x10;
    if (uVar1 < 0x101)
    {
        sango_battle_draw_bitmap(
            7, 5, ((uint32_t)g_battle_cursor_x - (uint32_t)g_battle_viewport_x) * 0x10 & 0xffff,
            uVar1);
        sango_battle_present();
    }
    return;
}

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
#define action_start (*(uint8_t(*)[2])(abi_storage + 0))
#define actor_unit (*(uint8_t *)(abi_storage + 2))

    char battle_result;
    int unit_stride_or_move_result;
    uint32_t unit_or_action_result;

    if (g_battle_result == '\0')
    {
        unit_or_action_result = 0;
        g_battle_result = '\x02';
        unit_stride_or_move_result = 0;
        do
        {
            if ((&g_first_unit_status)[unit_stride_or_move_result - unit_or_action_result] != '\b')
            {
                g_battle_result = '\0';
                break;
            }
            unit_or_action_result = unit_or_action_result + 1 & 0xff;
            unit_stride_or_move_result = unit_or_action_result << 3;
        } while (unit_or_action_result < 10);
        sango_battle_redraw_field(unit_or_action_result);
        battle_result = g_battle_result;
        while (
            (g_battle_result = battle_result,
             g_battle_result == '\0' && (unit_or_action_result = sango_battle_select_active_unit(),
                                         unit_or_action_result != 0xff)))
        {
            unit_stride_or_move_result =
                sango_battle_select_move_destination(unit_or_action_result);
            battle_result = g_battle_result;
            if (unit_stride_or_move_result == 0)
            {
                actor_unit = (uint8_t)unit_or_action_result;
                sango_battle_show_unit_commands((char *)action_start);
                unit_or_action_result = sango_battle_finish_unit_action(action_start);
                if ((g_battle_control_mode != '\x01') ||
                    (battle_result = '\x01', unit_or_action_result != 5))
                {
                    sango_battle_check_finish('\0');
                    battle_result = g_battle_result;
                }
            }
        }
    }
    return;
}
#undef action_start
#undef actor_unit

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
uint32_t sango_battle_select_target(char action_kind, char selected_skill, uint32_t actor_unit)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define empty_target_text (*(char(*)[16])(abi_storage + 0))
#define invalid_target_text (*(char(*)[16])(abi_storage + 16))

    uint32_t skill_id;
    bool same_side;
    int input_or_target_allowed;
    uint32_t target_unit;
    uint32_t inside_target_template;
    char *error_text;
    uint32_t actor_or_cancel_result;

    skill_id = (uint32_t)(uint8_t)selected_skill;
    actor_or_cancel_result = actor_unit & 0xff;
    if ((skill_id != 0x16) && (skill_id != 0x1e))
    {
        sango_battle_load_text(2, empty_target_text);
        sango_battle_load_text(3, invalid_target_text);
        sango_battle_draw_target_markers();
        while (true)
        {
            sango_battle_present();
            input_or_target_allowed = sango_battle_poll_map_action('\x01');
            if (input_or_target_allowed == 0xff)
                break;
            target_unit =
                sango_battle_find_unit_at((uint16_t)g_battle_cursor_x, (uint16_t)g_battle_cursor_y);
            if (target_unit == 0xff)
            {
                error_text = empty_target_text;
            }
            else
            {
                inside_target_template = sango_battle_target_side_allowed();
                error_text = invalid_target_text;
                if (inside_target_template != 0)
                {
                    same_side = false;
                    if (((actor_or_cancel_result < 10) && (target_unit < 10)) ||
                        ((10 < actor_or_cancel_result && (10 < target_unit))))
                    {
                        same_side = true;
                    }
                    if (action_kind == '\x01')
                    {
                        input_or_target_allowed =
                            sango_battle_skill_terrain_allowed(skill_id, same_side, target_unit);
                        if (input_or_target_allowed != 0)
                        {
                            return target_unit;
                        }
                    }
                    else if (!same_side)
                    {
                        return target_unit;
                    }
                }
            }
            sango_battle_draw_text(0x6a, 0xf3, error_text);
        }
        sango_battle_redraw_field(actor_or_cancel_result);
        actor_or_cancel_result = 0xff;
    }
    return actor_or_cancel_result;
}
#undef empty_target_text
#undef invalid_target_text

/* 原函数 0x81c0343c */
void sango_battle_draw_target_markers(void)
{
    uint8_t template_origin;
    uint16_t viewport_y;
    uint32_t map_x;
    uint32_t viewport_x;
    uint32_t template_column;
    uint32_t map_y;
    uint32_t template_width;
    uint32_t template_row;

    template_width = (uint32_t)*g_temp_character_ids_address;
    template_row = 0;
    if (template_width != 0)
    {
        template_origin = g_temp_character_ids_address[2];
        while (true)
        {
            map_y = template_row + template_origin & 0xff;
            if ((g_battle_viewport_y <= map_y) && (map_y < g_battle_viewport_y + 0xf))
            {
                viewport_y = (uint16_t)g_battle_viewport_y;
                template_column = 0;
                if (template_width != 0)
                {
                    template_origin = g_temp_character_ids_address[1];
                    while (true)
                    {
                        viewport_x = (uint32_t)g_battle_viewport_x;
                        map_x = template_column + template_origin & 0xff;
                        if (((viewport_x <= map_x) && (map_x < viewport_x + 0xf)) &&
                            (g_temp_character_ids_address[template_row * template_width +
                                                          template_column + 3] == 1))
                        {
                            sango_battle_draw_bitmap(7, 2, (map_x - viewport_x) * 0x10 & 0xff,
                                                     ((short)map_y - viewport_y) * 0x10 & 0xff);
                        }
                        template_column = template_column + 1 & 0xff;
                        if (template_width <= template_column)
                            break;
                        template_origin = g_temp_character_ids_address[1];
                    }
                }
            }
            template_row = template_row + 1 & 0xff;
            if (template_width <= template_row)
                break;
            template_origin = g_temp_character_ids_address[2];
        }
    }
    return;
}

/* 原函数 0x81c03590 */
void sango_battle_filter_unit_commands(uint32_t unit_id, uint16_t *menu_bounds)
{
    int unit_offset;
    uint16_t left;
    uint16_t right;
    uint16_t top;
    uint32_t viewport_y_or_screen_y;
    uint16_t bottom;

    unit_offset = (unit_id & 0xff) * 7;
    viewport_y_or_screen_y = (uint32_t)g_battle_viewport_y;
    left =
        ((uint16_t)(uint8_t)(&g_first_unit_x)[unit_offset] - (uint16_t)g_battle_viewport_x) * 0x10 +
            0x12 &
        0xff;
    right = left + 0x18;
    bottom = 0x2d;
    top = 0xfd;
    if (0xef < right)
    {
        left = left - 0x28 & 0xff;
        right = left + 0x18;
    }
    *menu_bounds = left;
    menu_bounds[2] = right;
    viewport_y_or_screen_y =
        ((uint8_t)(&g_first_unit_y)[unit_offset] - viewport_y_or_screen_y) * 0x10 & 0xff;
    if (3 < (int)(0x127 - viewport_y_or_screen_y) / 0xc)
    {
        top = (short)viewport_y_or_screen_y + 4U & 0xff;
        bottom = top + 0x30 & 0xff;
    }
    menu_bounds[3] = bottom;
    menu_bounds[1] = top;
    return;
}

/* 原函数 0x81c03654 */
uint32_t sango_battle_finish_unit_action(uint8_t *record)
{
    uint8_t actor_unit;
    int unit_offset;
    uint32_t experience_or_terrain;

    actor_unit = record[2];
    experience_or_terrain = sango_battle_execute_action(record);
    if ((experience_or_terrain & 0xff) != 0)
    {
        sango_battle_draw_terrain((uint32_t)g_battle_viewport_x, (uint32_t)g_battle_viewport_y);
        sango_battle_draw_units(0);
        *g_attacker_experience_address_view2 =
            (char)experience_or_terrain + *g_attacker_experience_address_view2;
        if (actor_unit < 10)
        {
            sango_battle_show_action_message(experience_or_terrain & 0xff);
        }
        sango_battle_check_level_and_retreat();
    }
    unit_offset = (uint32_t)actor_unit * 7;
    experience_or_terrain =
        sango_battle_terrain_at((uint32_t)(uint8_t)(&g_first_unit_x)[unit_offset],
                                (uint32_t)(uint8_t)(&g_first_unit_y)[unit_offset]);
    return experience_or_terrain;
}

/* 原函数 0x81c03708 */
uint32_t sango_battle_select_move_destination(uint32_t unit_id)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define invalid_move_text (*(char(*)[24])(abi_storage + 0))

    int unit_offset;
    uint8_t destination_x;
    int input_result;
    uint32_t window_y;
    uint32_t window_x;
    uint32_t unit_index;

    unit_index = unit_id & 0xff;
    unit_offset = unit_index * 7;
    if ((&g_first_unit_move_range)[unit_offset] != '\x01')
    {
        sango_battle_build_move_range(unit_index);
        sango_memory_fill(invalid_move_text, 0, 0x14);
        sango_battle_load_text(1, invalid_move_text);
        sango_battle_draw_move_range();
        while (true)
        {
            sango_battle_present();
            input_result = sango_battle_poll_map_action('\x02');
            destination_x = g_battle_cursor_x;
            if (input_result == 0xff)
                break;
            window_x = (uint32_t)g_move_window_left +
                           ((uint32_t)g_battle_cursor_x - (uint32_t)g_move_source_x) &
                       0xff;
            window_y = (uint32_t)g_move_window_top +
                           ((uint32_t)g_battle_cursor_y - (uint32_t)g_move_source_y) &
                       0xff;
            if (((window_x < 0x10) && (window_y < 0x10)) &&
                (*(uint8_t *)(g_move_costs_address + window_y * 0xf + window_x) < 0x81))
            {
                g_legacy_data_81c2b172 = (&g_first_unit_x)[unit_offset];
                g_legacy_data_81c2b148 = (&g_first_unit_y)[unit_offset];
                (&g_first_unit_y)[unit_offset] = g_battle_cursor_y;
                (&g_first_unit_x)[unit_offset] = destination_x;
                sango_battle_redraw_field(unit_index);
                return 0;
            }
            sango_battle_draw_text(0x6a, 0xf3, invalid_move_text);
        }
        sango_battle_redraw_field(unit_index);
    }
    return 1;
}
#undef invalid_move_text

/* 原函数 0x81c03874 */
uint32_t sango_battle_select_active_unit(void)
{
    int input_or_option_result;
    uint32_t selected_unit;

    sango_battle_draw_terrain((uint32_t)g_battle_viewport_x, (uint32_t)g_battle_viewport_y);
    sango_battle_draw_hud();
    sango_battle_draw_cursor_description();
    do
    {
        while (input_or_option_result = sango_battle_poll_map_action('\x03'),
               input_or_option_result == 0)
        {
            selected_unit = sango_battle_find_actionable_unit_at_cursor();
            if (selected_unit != 0xff)
            {
                return selected_unit;
            }
        }
        input_or_option_result = sango_battle_show_options();
    } while (input_or_option_result != 0xff);
    return 0xff;
}

/* 原函数 0x81c038f4 */
/* 处理键盘和完整16位触摸坐标；按钮命中后恢复战场HUD。 */
uint32_t sango_battle_poll_map_action(char preview_mode)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define event_kind (*(int *)(abi_storage + 0))
#define key_code (*(int *)(abi_storage + 4))

    /* 原恢复入口没有给此计数器赋初值；保留当前编译ABI的首拍相位，
     * 不在可读性重构中加入新的初始化行为。 */
    uint32_t legacy_timer_ticks;
    uint32_t blink_phase = 0;
    while (true)
    {
        sango_input_next_event(&event_kind);
        if (event_kind == 5)
        {
            if (key_code == 0x1c)
                return 0;
            if (key_code == 1)
                return 0xff;
            sango_battle_draw_tile((uint32_t)g_battle_cursor_x, (uint32_t)g_battle_cursor_y, '\0');
        }

        if (event_kind == 6)
        {
            legacy_timer_ticks = legacy_timer_ticks + 1 & 0xff;
            if (legacy_timer_ticks % 10 != 0)
                continue;
            blink_phase = (uint32_t)(blink_phase == 0);
        }
        else if (event_kind == 5)
        {
            switch (key_code)
            {
            case 0x67:
                if (g_battle_cursor_y != 0)
                    g_battle_cursor_y = g_battle_cursor_y - 1;
                break;
            case 0x69:
                if (g_battle_cursor_x != 0)
                    g_battle_cursor_x = g_battle_cursor_x - 1;
                break;
            case 0x6a:
                if ((int)(uint32_t)g_battle_cursor_x < (int)(g_battle_map_width - 1))
                    g_battle_cursor_x = g_battle_cursor_x + 1;
                break;
            case 0x6c:
                if ((int)(uint32_t)g_battle_cursor_y < (int)(g_battle_map_height - 1))
                    g_battle_cursor_y = g_battle_cursor_y + 1;
                break;
            case 0x1f:
                sango_battle_show_overview();
                sango_battle_draw_hud();
                break;
            case 0x23:
                sango_battle_show_cursor_info();
                sango_battle_draw_hud();
                break;
            }
            /* 按键后先恢复移动/目标预览，再进入共同的部队重画流程。 */
            if (preview_mode == '\x01')
                sango_battle_refresh_target_preview((char)blink_phase);
            else if (preview_mode == '\x02')
                sango_battle_refresh_move_preview((char)blink_phase);
            else
                sango_battle_scroll_viewport((char)blink_phase);
        }
        else if (event_kind == 0xb)
        {
            /* 输入包中的完整16位坐标用于底栏命中，不能使用会截断的旧坐标槽。 */
            enum SangoBattleToolbarAction action = sango_battle_toolbar_hit(
                *(uint16_t *)(abi_storage + 8), *(uint16_t *)(abi_storage + 10));
            if (action == SANGO_BATTLE_TOOLBAR_INFO)
                sango_battle_show_cursor_info();
            else if (action == SANGO_BATTLE_TOOLBAR_OVERVIEW)
                sango_battle_show_overview();
            if (action != SANGO_BATTLE_TOOLBAR_NONE)
                sango_battle_draw_hud();
        }

        sango_battle_draw_units(blink_phase);
        if (preview_mode == '\x01')
            sango_battle_refresh_target_preview((char)blink_phase);
        else if (preview_mode == '\x02')
            sango_battle_refresh_move_preview((char)blink_phase);
        else
            sango_battle_scroll_viewport((char)blink_phase);
        sango_battle_draw_cursor();
    }
}
#undef event_kind
#undef key_code

/* 原函数 0x81c03c20 */
void sango_battle_draw_cursor(void)
{
    uint16_t screen_y;

    screen_y = ((uint16_t)g_battle_cursor_y - (uint16_t)g_battle_viewport_y) * 0x10;
    if (screen_y < 0x101)
    {
        sango_battle_draw_bitmap(
            7, 5, ((uint32_t)g_battle_cursor_x - (uint32_t)g_battle_viewport_x) * 0x10 & 0xffff,
            screen_y);
        sango_battle_present();
    }
    return;
}

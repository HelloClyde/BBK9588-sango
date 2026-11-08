#include "sango_internal.h"

/* 普通攻击、计谋执行和演出反馈。 */

/* 原函数 0x81c058b8 */
/* 计谋ID读取名称、消耗和状态参数；动画资源及指令范围来自初始化表。 */
uint32_t sango_battle_execute_skill(int param_1)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define local_43 (*(uint8_t *)(abi_storage + 5))
#define local_28 (*(uint16_t *)(abi_storage + 32))
#define local_26 (*(uint16_t(*)[3])(abi_storage + 34))
#define acStack_48 (*(char(*)[5])(abi_storage + 0))
#define uStack_42 (*(uint8_t *)(abi_storage + 6))
#define uStack_41 (*(uint8_t *)(abi_storage + 7))
#define auStack_40 (*(uint8_t(*)[4])(abi_storage + 8))
#define auStack_3c (*(uint8_t(*)[20])(abi_storage + 12))

    char cVar1;
    char cVar2;
    uint16_t uVar3;
    char *pcVar4;
    uint32_t uVar5;
    int iVar6;
    uint16_t *puVar7;
    uint32_t uVar8;
    uint32_t uVar9;
    uint32_t uVar10;

    uVar8 = (uint32_t) * (uint8_t *)(param_1 + 1);
    uVar9 = (uint32_t) * (uint8_t *)(param_1 + 2);
    uVar10 = (uint32_t) * (uint8_t *)(param_1 + 3);
    pcVar4 = (char *)sango_battle_skill_parameters(uVar8);
    (&g_first_unit_energy)[uVar9 * 7] = (&g_first_unit_energy)[uVar9 * 7] - pcVar4[6];
    sango_memory_fill(acStack_48, 0x20, 10);
    uVar5 = bbk_rand();
    if (g_defender_initiative + 0x14 == 0)
    {
        sango_legacy_trap(7);
    }
    if ((uint32_t)(g_attacker_initiative >> 1) <
        ((int)uVar5 % (int)(g_defender_initiative + 0x14) & 0xffU))
    {
        sango_resource_read_text(0xb, uVar8, acStack_48 + 1);
        local_43 = 0x20;
        sango_battle_read_text(0x1a, &uStack_41);
        sango_battle_show_short_message(acStack_48, 1, 0xff);
        uVar5 = 0;
    }
    else
    {
        if (g_battle_show_animations == '\0')
        {
            sango_resource_read_text(0xb, uVar8, &uStack_42);
            sango_battle_show_short_message(acStack_48, 1, 0);
            cVar1 = pcVar4[1];
        }
        else
        {
            cVar1 = pcVar4[1];
        }
        (&g_first_unit_status)[uVar10 * 7] = cVar1;
        if (cVar1 == '\x03')
        {
            (&g_first_unit_move_range)[uVar10 * 7] = 1;
        }
        cVar2 = *pcVar4;
        if (uVar8 == 0x16)
        {
            sango_battle_change_weather();
            uVar5 = 8;
        }
        else if (uVar8 == 0x1b)
        {
            uVar5 = sango_battle_execute_surround_attack(uVar10);
            sango_battle_prepare_combatant(0, uVar9);
        }
        else if (uVar8 == 0x1e)
        {
            g_battle_recon_food = g_battle_defender_food;
            sango_battle_read_text(0x37, g_scratch_buffer_address);
            uVar5 = sango_battle_resolve_character(uVar9);
            sango_ui_show_character_message((uint8_t)uVar5, g_scratch_buffer_address);
            sango_render_present(g_game_context);
            uVar5 = 8;
        }
        else
        {
            sango_battle_compute_skill_effect((int)pcVar4, &local_28, local_26);
            uVar5 = uVar8 - 1 & 0xff;
            uVar3 = *(uint16_t *)(&g_skill_animation_resource_bytes + uVar5 * 2);
            if ((uVar3 != 0) && (g_battle_show_animations != '\0'))
            {
                if ((&g_skill_animation_background_flag)[uVar5] != '\0')
                {
                    sango_bitmap_draw_resource(0x10, 1, 0x14, 0x31, '\0');
                }
                sango_animation_play_range(
                    (uint32_t)uVar3, (uint32_t)(uint8_t)(&g_skill_animation_first_command)[uVar5],
                    (uint32_t)(uint8_t)(&g_skill_animation_last_command)[uVar5], 0,
                    (uint8_t)(&g_skill_animation_x_offset)[uVar5] + 0x14, 0x31);
            }
            if (local_28 == 0)
            {
                puVar7 = &g_battle_defender_food;
                if (9 < uVar9)
                {
                    puVar7 = &g_battle_attacker_food;
                }
                local_28 = local_26[0];
                uVar5 = sango_battle_subtract_clamped(puVar7, local_26[0]);
                local_26[0] = (uint16_t)uVar5;
                uVar5 = 0x19;
            }
            else if (cVar2 == '\0')
            {
                uVar5 = 0x17;
                uVar8 = sango_battle_subtract_clamped(g_defender_troops_address, local_28);
                local_28 = (uint16_t)uVar8;
            }
            else
            {
                uVar5 = sango_battle_resolve_character(uVar10);
                iVar6 = sango_character_troop_capacity(uVar5);
                uVar5 = 0x18;
                uVar8 = sango_battle_add_clamped(g_defender_troops_address, (uint32_t)local_28,
                                                 (uint16_t)iVar6);
                local_28 = (uint16_t)uVar8;
            }
            if (local_28 != 0)
            {
                if (g_battle_show_animations == '\0')
                {
                    sango_battle_draw_unit_damage('-', uVar10, (uint32_t)local_28);
                }
                else
                {
                    sango_battle_read_text(uVar5, acStack_48);
                    sango_text_draw_legacy(0x3c, 0x33, acStack_48);
                    sango_battle_draw_damage_digits(0x3c, 0x59, (uint32_t)local_28);
                }
                sango_input_wait(0x32, '\0');
            }
            if (cVar1 != '\0')
            {
                uVar5 = sango_battle_resolve_character(uVar10);
                sango_load_named_text((uint8_t)uVar5, acStack_48);
                uVar5 = bbk_strlen(acStack_48);
                uVar5 = uVar5 & 0xffff;
                sango_battle_read_text(0x1b, acStack_48 + uVar5);
                sango_battle_read_text((uint32_t)(uint8_t)(cVar1 + 0x1c), auStack_40 + uVar5);
                sango_battle_read_text(0x24, auStack_3c + uVar5);
                sango_ui_show_message(acStack_48, 1);
            }
            uVar5 = sango_battle_damage_feedback(local_28);
        }
    }
    return uVar5;
}
#undef local_43
#undef local_28
#undef local_26
#undef acStack_48
#undef uStack_42
#undef uStack_41
#undef auStack_40
#undef auStack_3c

/* 原函数 0x81c05cdc */
uint32_t sango_battle_execute_surround_attack(uint32_t param_1)
{
    bool bVar1;
    int iVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;

    uVar5 = param_1 & 0xff;
    uVar4 = 0;
    uVar6 = 0;
LAB_81c05d0c:
    do
    {
        bVar1 = uVar4 < 4;
        do
        {
            do
            {
                iVar2 = uVar4 * 2;
                if (!bVar1)
                {
                    return uVar6 >> 1;
                }
                uVar4 = uVar4 + 1 & 0xff;
            } while ((((&g_first_unit_x)[uVar5 * 7] == 0) &&
                      (bVar1 = uVar4 < 4, 0x80 < (uint8_t)(&g_legacy_data_81c201cc)[iVar2])) ||
                     (((&g_first_unit_y)[uVar5 * 7] == 0 &&
                       (bVar1 = uVar4 < 4, 0x80 < (uint8_t)(&g_legacy_data_81c201cd)[iVar2]))));
            uVar3 = sango_battle_find_unit_at(
                (uint16_t)(uint8_t)(&g_first_unit_x)[uVar5 * 7] +
                        (uint16_t)(uint8_t)(&g_legacy_data_81c201cc)[iVar2] &
                    0xff,
                (uint16_t)(uint8_t)(&g_first_unit_y)[uVar5 * 7] +
                        (uint16_t)(uint8_t)(&g_legacy_data_81c201cd)[iVar2] &
                    0xff);
            if (uVar3 == 0xff)
                goto LAB_81c05d0c;
        } while (((uVar5 < 10) && (bVar1 = uVar4 < 4, uVar3 < 10)) ||
                 ((10 < uVar5 && (bVar1 = uVar4 < 4, 10 < uVar3))));
        sango_battle_blink_unit(uVar3, 2);
        sango_battle_prepare_combatant(0, uVar3);
        uVar3 = sango_battle_execute_normal_attack(uVar5);
        uVar6 = uVar6 + uVar3 & 0xff;
    } while (true);
}

/* 原函数 0x81c05e0c */
/* 普通攻击：计算伤害、扣除兵力，再按地形和兵种播放演出。 */
uint32_t sango_battle_execute_normal_attack(uint32_t target_unit)
{
    uint32_t damage;
    uint32_t applied_damage;
    uint32_t first_command;
    uint32_t last_command;
    uint32_t animation_resource;
    int feedback_delay;

    damage = sango_battle_roll_attack_damage();
    applied_damage = sango_battle_subtract_clamped(g_defender_troops_address, (uint16_t)damage);
    if (g_battle_show_animations == '\0')
    {
        sango_battle_draw_unit_damage('-', target_unit & 0xff, applied_damage);
    }
    else
    {
        sango_bitmap_draw_resource(0x10, 1, 0x14, 0x31, '\0');
        animation_resource = 0x19;
        first_command = 0;
        last_command = 4;
        if (g_defender_terrain_view2 != '\a')
        {
            animation_resource = g_attacker_troop_type + 0x13;
            first_command =
                (uint32_t)(uint8_t)(&g_attack_animation_command_strides)[g_attacker_troop_type] *
                    (uint32_t)g_defender_troop_type &
                0xff;
            last_command = (first_command +
                            (uint8_t)(&g_attack_animation_command_strides)[g_attacker_troop_type]) -
                               1 &
                           0xff;
        }
        sango_animation_play_range(animation_resource, first_command, last_command, 0, 0x14, 0x31);
        sango_battle_draw_damage_digits(0x3c, 0x59, applied_damage);
    }
    sango_input_wait(0x32, '\0');
    if ((uint8_t)(*g_attacker_level_address_view2 - *g_defender_level_address) < 0xe1)
    {
        feedback_delay = 0x10;
        if (*g_attacker_level_address_view2 != *g_defender_level_address)
        {
            feedback_delay = 8;
        }
    }
    else
    {
        feedback_delay = 0x18;
    }
    first_command = sango_battle_damage_feedback((uint16_t)applied_damage);
    return (uint32_t)(damage != applied_damage) * feedback_delay + first_command & 0xff;
}

/* 原函数 0x81c05f7c */
void sango_battle_draw_damage_digits(uint16_t param_1, uint16_t param_2, uint32_t param_3)
{
    unsigned char abi_storage[36] __attribute__((aligned(8)));
#define local_40 (*(char(*)[16])(abi_storage + 0))
#define local_30 (*(uint32_t *)(abi_storage + 16))

    uint8_t bVar1;
    uint8_t bVar2;
    char cVar3;
    uint8_t *pbVar4;
    uint16_t uVar5;
    uint16_t uVar6;
    uint32_t uVar7;

    sango_format_integer(param_3 & 0xffff, local_40, 10);
    local_30 = bbk_strlen(local_40);
    local_30 = local_30 & 0xff;
    pbVar4 = (uint8_t *)sango_resource_item(0xf, '\x01', g_resource_package_address);
    bVar1 = *pbVar4;
    bVar2 = pbVar4[2];
    uVar7 = 0;
    if (local_30 != 0)
    {
        do
        {
            cVar3 = local_40[uVar7];
            sango_input_wait(4, '\0');
            uVar5 = 0;
            if (bVar2 != 0)
            {
                uVar6 = 1;
                do
                {
                    sango_bitmap_draw_frame_screen(param_1 & 0xff, (param_2 & 0xff) - uVar5,
                                                   (uint16_t)bVar1, uVar6, cVar3 - 0x30, pbVar4);
                    sango_input_wait(1, '\0');
                    uVar5 = uVar6 & 0xff;
                    uVar6 = uVar5 + 1;
                } while (uVar5 < bVar2);
            }
            uVar7 = uVar7 + 1 & 0xff;
            param_1 = (param_1 & 0xff) + (uint16_t)bVar1;
        } while (uVar7 < local_30);
    }
    return;
}
#undef local_40
#undef local_30

/* 原函数 0x81c060c8 */
void sango_battle_append_stat_value(char *param_1, uint32_t param_2)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define acStack_20 (*(char(*)[16])(abi_storage + 0))

    uint32_t uVar1;
    uint32_t uVar2;
    char *dst;

    uVar1 = sango_crt_strlen(param_1);
    uVar2 = 0;
    if ((uVar1 & 0xffff) != 0)
    {
        do
        {
            dst = param_1 + uVar2;
            uVar2 = uVar2 + 1 & 0xffff;
            if (*dst == '%')
                break;
            dst = (char *)0x0;
        } while (uVar2 < (uVar1 & 0xffff));
        if (dst != (char *)0x0)
        {
            sango_format_integer(param_2 & 0xffff, acStack_20, 10);
            uVar1 = sango_crt_strlen(acStack_20);
            bbk_memcpy(dst, acStack_20, uVar1 & 0xffff);
        }
    }
    return;
}
#undef acStack_20

/* 原函数 0x81c06168 */
uint32_t sango_battle_damage_feedback(uint16_t param_1)
{
    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;

    uVar3 = (uint32_t)*g_attacker_level_address_view3 - (uint32_t)*g_defender_level_address_view2 &
            0xff;
    uVar1 = sango_math_sqrt_step_search(param_1);
    uVar1 = uVar1 >> 2 & 0xff;
    if ((0x80 < uVar3) || (uVar2 = 0, uVar3 < uVar1))
    {
        uVar2 = uVar1 - uVar3 & 0xff;
    }
    return (uVar2 + 2 & 0xff) % 100;
}

/* 原函数 0x81c0620c */
uint32_t sango_battle_terrain_at(uint32_t map_x, uint32_t map_y)
{
    uint8_t tile;
    uint8_t *map;
    uint32_t terrain;

    map = (uint8_t *)sango_resource_item((uint32_t)g_battle_map_resource, '\x01',
                                         g_resource_package_address);
    terrain = 6;
    tile = map[((uint32_t)*map * (map_y & 0xff) + (map_x & 0xff) & 0xffff) + 0x10];
    if (tile != 0x29)
    {
        terrain = 7;
    }
    if (tile < 0x10)
    {
        terrain = 2;
        if (tile < 6)
        {
            terrain = 3;
            if (tile < 5)
            {
                terrain = 4;
                if (tile < 4)
                {
                    terrain = 5;
                    if ((tile < 3) && (terrain = 0, tile < 2))
                    {
                        terrain = 1;
                    }
                }
            }
        }
    }
    return terrain;
}

/* 原函数 0x81c062d0 */
int sango_battle_skill_parameters(uint32_t skill_id)
{
    int parameters;

    parameters = sango_resource_item(10, '\x01', g_resource_package_address);
    return parameters + (((skill_id & 0xff) - 1) * 0x22 & 0xffff);
}

/* 原函数 0x81c06318 */
uint32_t sango_battle_find_unit_at(uint16_t map_x, uint16_t map_y)
{
    int unit_offset;
    uint32_t unit_index;

    unit_index = 0;
    while (true)
    {
        unit_offset = unit_index * 7;
        if ((((&g_first_unit_status)[unit_offset] != '\b') &&
             ((uint8_t)(&g_first_unit_x)[unit_offset] == map_x)) &&
            ((uint8_t)(&g_first_unit_y)[unit_offset] == map_y))
            break;
        unit_index = unit_index + 1 & 0xff;
        if (0x13 < unit_index)
        {
            return 0xff;
        }
    }
    return unit_index;
}

/* 原函数 0x81c06384 */
void sango_battle_change_weather(void)
{
    uint32_t weather;

    weather = bbk_rand();
    weather = (int)weather % 5 + 1;
    g_battle_weather = (uint8_t)weather;
    sango_bitmap_draw_resource((weather & 0xff) + 0x1b, 1, 0x14, 0x31, '\x01');
    sango_bitmap_draw_resource(9, (uint32_t)g_battle_weather, 0x4b, 0xf3, '\x01');
    sango_bitmap_draw_resource(9, (uint32_t)g_battle_weather, 0x4b, 0xf3, '\0');
    sango_input_wait(0x32, '\0');
    return;
}

/* 原函数 0x81c06440 */
uint32_t sango_battle_show_options(void)
{
    unsigned char abi_storage[80] __attribute__((aligned(8)));
#define local_30 (*(uint16_t(*)[8])(abi_storage + 48))
#define acStack_60 (*(char(*)[48])(abi_storage + 0))

    uint32_t uVar1;
    uint32_t uVar2;
    uint8_t *unaff_s2;

    local_30[2] = 0x38;
    local_30[4] = 0x6b;
    local_30[6] = 0x83;
    local_30[3] = 0x44;
    local_30[1] = 8;
    local_30[5] = 0x93;
    local_30[7] = 0xab;
    local_30[0] = 8;
    uVar2 = 0x9f;
    uVar1 = 0;
    do
    {
        sango_battle_read_text(9, acStack_60);
        uVar1 = sango_ui_choose_option(local_30, uVar1, acStack_60);
        if (uVar1 == 2)
        {
            unaff_s2 = &g_battle_show_animations_view2;
            uVar2 = 10;
        }
        else if ((int)uVar1 < 3)
        {
            if (uVar1 == 0)
            {
            LAB_81c06534:
                sango_render_present(g_game_context);
                return 0xff;
            }
            if (uVar1 == 1)
            {
                g_battle_result_view2 = 2;
                goto LAB_81c06534;
            }
        }
        else if (uVar1 == 4)
        {
            unaff_s2 = &g_battle_render_enabled_view2;
            uVar2 = 10;
        }
        else if ((int)uVar1 < 4)
        {
            unaff_s2 = &g_battle_animate_movement_view2;
            uVar2 = 0xb;
        }
        else if (uVar1 == 0xff)
        {
            sango_render_present(g_game_context);
            return 1;
        }
        sango_battle_read_text(uVar2, acStack_60);
        uVar2 = sango_ui_choose_option(local_30 + 4, (uint32_t)*unaff_s2, acStack_60);
        if (uVar2 != 0xff)
        {
            *unaff_s2 = (uint8_t)uVar2;
        }
        sango_render_present(g_game_context);
    } while (true);
}
#undef local_30
#undef acStack_60

/* 原函数 0x81c065c4 */
void sango_battle_draw_unit_damage(char param_1, uint32_t param_2, uint32_t param_3)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define local_18 (*(char *)(abi_storage + 0))
#define auStack_17 (*(uint8_t(*)[15])(abi_storage + 1))

    int iVar1;

    local_18 = param_1;
    sango_format_integer(param_3 & 0xffff, auStack_17, 10);
    iVar1 = (param_2 & 0xff) * 7;
    sango_text_draw_legacy(
        ((uint16_t)(uint8_t)(&g_first_unit_x)[iVar1] - (uint16_t)g_battle_viewport_x) * 0x10 & 0xff,
        ((uint16_t)(uint8_t)(&g_first_unit_y)[iVar1] - (uint16_t)g_battle_viewport_y) * 0x10 & 0xff,
        &local_18);
    return;
}
#undef local_18
#undef auStack_17

/* 原函数 0x81c06650 */
uint32_t sango_battle_resolve_character(uint32_t unit_id)
{
    return (uint8_t)(&g_battle_roster_first)[unit_id & 0xff] - 1 & 0xff;
}

/* 原函数 0x81c0666c */
void sango_battle_read_text(uint32_t text_id, void *output)
{
    sango_resource_read_text(1, text_id & 0xff, output);
    return;
}

/* 原函数 0x81c06694 */
uint32_t sango_battle_execute_action(uint8_t *record)
{
    uint8_t bVar1;
    uint8_t bVar2;
    uint8_t uVar3;
    uint32_t uVar4;
    uint32_t unaff_s2;
    int iVar5;
    uint32_t uVar6;

    uVar6 = (uint32_t)record[2];
    iVar5 = uVar6 * 7;
    (&g_first_unit_has_acted)[iVar5] = 1;
    sango_battle_prepare_combatant(0, uVar6);
    sango_battle_prepare_combatant(1, (uint32_t)record[3]);
    bVar1 = *record;
    if (bVar1 == 1)
    {
        unaff_s2 = sango_battle_execute_skill((int)record);
    }
    else if (bVar1 < 2)
    {
        if (bVar1 == 0)
        {
            unaff_s2 = sango_battle_execute_normal_attack((uint32_t)record[3]);
        }
    }
    else
    {
        if (bVar1 != 3)
        {
            if (bVar1 != 0xff)
            {
                return unaff_s2;
            }
            (&g_first_unit_x)[iVar5] = g_legacy_data_81c2b172;
            uVar3 = g_legacy_data_81c2b148;
            (&g_first_unit_has_acted)[iVar5] = 0;
            (&g_first_unit_y)[iVar5] = uVar3;
            sango_battle_redraw_field(uVar6);
        }
        uVar4 = sango_battle_resolve_character(uVar6);
        iVar5 = g_character_table_address + uVar4 * 0x10;
        bVar1 = *(uint8_t *)(iVar5 + 4);
        uVar4 = sango_math_sqrt_step_search((uint16_t) * (uint8_t *)(iVar5 + 3));
        bVar2 = (&g_first_unit_energy)[uVar6 * 7];
        if ((uint32_t)bVar2 < (((((uint32_t)bVar1 * 0x50) / 100 + (uVar4 >> 1 & 0xff) +
                                 (uint32_t) * (uint8_t *)(iVar5 + 2)) *
                                (uint32_t) * (uint8_t *)(iVar5 + 8)) /
                                   100 &
                               0xff))
        {
            (&g_first_unit_energy)[uVar6 * 7] = bVar2 + 1;
        }
        unaff_s2 = 0;
    }
    return unaff_s2;
}

/* 原函数 0x81c06838 */
uint32_t sango_battle_unit_sprite_frame(uint32_t unit_id)
{
    uint32_t character_id;
    int unit_offset;
    uint32_t frame;
    uint32_t unit_index;

    unit_index = unit_id & 0xff;
    unit_offset = unit_index * 7;
    character_id = sango_battle_resolve_character(unit_index);
    if (((&g_first_unit_status)[unit_offset] == '\x06') ||
        ((&g_first_unit_status)[unit_offset] == '\x01'))
    {
        frame = 0xe;
    }
    else
    {
        unit_offset = sango_battle_terrain_at((uint32_t)(uint8_t)(&g_first_unit_x)[unit_offset],
                                              (uint32_t)(uint8_t)(&g_first_unit_y)[unit_offset]);
        frame = 0xc;
        if (unit_offset != 7)
        {
            frame = (*(uint8_t *)(character_id * 0x10 + g_character_table_address + 9) & 0x7f) << 1;
        }
    }
    if (9 < unit_index)
    {
        frame = frame + 0x10 & 0xff;
    }
    return frame;
}

/* 原函数 0x81c068f0 */
void sango_battle_regenerate_unit_energy(uint32_t param_1)
{
    uint8_t bVar1;
    uint8_t bVar2;
    uint32_t uVar3;
    int iVar4;

    uVar3 = sango_battle_resolve_character(param_1 & 0xff);
    iVar4 = g_character_table_address + uVar3 * 0x10;
    bVar1 = *(uint8_t *)(iVar4 + 4);
    uVar3 = sango_math_sqrt_step_search((uint16_t) * (uint8_t *)(iVar4 + 3));
    bVar2 = (&g_first_unit_energy)[(param_1 & 0xff) * 7];
    if ((uint32_t)bVar2 < (((((uint32_t)bVar1 * 0x50) / 100 + (uVar3 >> 1 & 0xff) +
                             (uint32_t) * (uint8_t *)(iVar4 + 2)) *
                            (uint32_t) * (uint8_t *)(iVar4 + 8)) /
                               100 &
                           0xff))
    {
        (&g_first_unit_energy)[(param_1 & 0xff) * 7] = bVar2 + 1;
    }
    return;
}

/* 原函数 0x81c069d4 */
uint32_t sango_battle_find_actionable_unit_at_cursor(void)
{
    char cVar1;
    int iVar2;
    uint32_t uVar3;

    uVar3 = 0;
    while (true)
    {
        iVar2 = uVar3 * 7;
        cVar1 = (&g_first_unit_status)[iVar2];
        if (((cVar1 != '\b') && ((&g_first_unit_x)[iVar2] == g_battle_cursor_x_view2)) &&
            ((&g_first_unit_y)[iVar2] == g_battle_cursor_y_view2))
            break;
        uVar3 = uVar3 + 1 & 0xff;
        if (9 < uVar3)
        {
            return 0xff;
        }
    }
    if ((&g_first_unit_has_acted)[iVar2] != '\0')
    {
        return 0xff;
    }
    if (cVar1 == '\x01')
    {
        return 0xff;
    }
    if (cVar1 != '\x06')
    {
        return uVar3;
    }
    return 0xff;
}

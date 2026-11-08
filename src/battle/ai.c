#include "sango_internal.h"

/* 电脑部队行动与目标选择。 */

/* 原函数 0x81c017a0 */
uint32_t sango_battle_ai_plan_unit(uint8_t *param_1)
{
    uint32_t uVar1;
    int iVar2;
    uint32_t uVar3;

    uVar1 = sango_battle_select_ai_unit();
    if (uVar1 != 0xff)
    {
        param_1[2] = (char)uVar1;
        sango_battle_build_move_range(uVar1);
        if (g_battle_render_enabled != '\0')
        {
            sango_battle_redraw_field(uVar1);
            sango_battle_draw_move_range();
            sango_battle_blink_unit(uVar1, 1);
            sango_render_present(g_game_context);
            if (g_battle_animate_movement != '\0')
            {
                sango_input_wait(0x32, '\0');
            }
        }
        sango_battle_ai_choose_destination(uVar1);
        if ((g_battle_render_enabled != '\0') &&
            (sango_battle_redraw_field(uVar1), g_battle_animate_movement != '\0'))
        {
            sango_input_wait(0x32, '\0');
        }
        iVar2 = sango_battle_ai_choose_skill(param_1);
        if ((iVar2 == 0) && (uVar3 = sango_battle_ai_prepare_attack(param_1), uVar3 == 0))
        {
            *param_1 = 3;
        }
    }
    return uVar1;
}

/* 原函数 0x81c018b0 */
uint32_t sango_battle_ai_choose_skill(uint8_t *param_1)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define abStack_30 (*(uint8_t(*)[16])(abi_storage + 0))

    uint8_t bVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    int iVar7;

    uVar6 = (uint32_t)(uint8_t)param_1[2];
    if ((&g_first_unit_status)[uVar6 * 7] != '\x02')
    {
        uVar2 = sango_battle_is_player_unit(uVar6);
        iVar7 = g_character_table_address + uVar2 * 0x10;
        uVar3 = bbk_rand();
        if ((uVar3 & 0xffff) % 0x96 <= (uint32_t) * (uint8_t *)(iVar7 + 4))
        {
            if (*(char *)(iVar7 + 9) != '\x05')
            {
                uVar4 = sango_character_troop_capacity(uVar2);
                uVar5 = uVar4 + (uVar4 >> 1) & 0xffff;
                uVar4 = bbk_rand();
                if (uVar5 == 0)
                {
                    sango_legacy_trap(7);
                }
                if ((int)uVar4 % (int)uVar5 < (int)(uint32_t) * (uint16_t *)(iVar7 + 10))
                {
                    return 0;
                }
            }
            sango_battle_collect_unit_skills(uVar2, (char *)abStack_30);
            uVar2 = sango_crt_strlen((char *)abStack_30);
            if (uVar2 == 0)
            {
                sango_legacy_trap(7);
            }
            bVar1 = abStack_30[(uVar3 & 0xffff) % uVar2 & 0xff];
            uVar2 = (uint32_t)bVar1;
            iVar7 = sango_battle_skill_target_allowed(uVar2, uVar6);
            if (iVar7 == 0)
            {
                sango_battle_load_range_template('\x01', uVar2, uVar6);
                uVar6 = 0;
                iVar7 = 0;
                do
                {
                    iVar7 = iVar7 - uVar6;
                    if ((&g_first_unit_status)[iVar7] != '\b')
                    {
                        uVar3 = sango_battle_target_in_skill_range(
                            (uint32_t)(uint8_t)(&g_first_unit_x)[iVar7],
                            (uint32_t)(uint8_t)(&g_first_unit_y)[iVar7]);
                        if ((uVar3 != 0) &&
                            (iVar7 = sango_battle_skill_terrain_allowed(uVar2, 9 < uVar6, uVar6),
                             iVar7 != 0))
                        {
                            if ((uVar2 != 0x11) && (uVar2 != 0x1d))
                            {
                                param_1[1] = bVar1;
                                *param_1 = 1;
                                param_1[3] = (char)uVar6;
                                return 1;
                            }
                            sango_character_troop_capacity(
                                (uint8_t)(&g_battle_roster_first)[uVar6] - 1 & 0xff);
                        }
                    }
                    uVar6 = uVar6 + 1 & 0xff;
                    iVar7 = uVar6 << 3;
                } while (uVar6 < 0x14);
            }
        }
    }
    return 0;
}
#undef abStack_30

/* 原函数 0x81c01af0 */
uint32_t sango_battle_ai_prepare_attack(uint8_t *param_1)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define local_18 (*(char(*)[2])(abi_storage + 0))
#define auStack_16 (*(uint16_t(*)[3])(abi_storage + 2))

    uint8_t bVar1;

    bVar1 = param_1[2];
    sango_battle_load_range_template('\0', 0, (uint32_t)bVar1);
    sango_battle_prepare_combatant(0, (uint32_t)bVar1);
    sango_battle_select_combat_target(auStack_16, local_18);
    if (local_18[0] != -1)
    {
        param_1[3] = local_18[0];
        *param_1 = 0;
    }
    return (uint32_t)(local_18[0] != -1);
}
#undef local_18
#undef auStack_16

/* 原函数 0x81c01b68 */
void sango_battle_ai_choose_destination(uint32_t param_1)
{
    unsigned char abi_storage[44] __attribute__((aligned(8)));
#define local_38 (*(uint32_t *)(abi_storage + 16))
#define local_34 (*(uint32_t *)(abi_storage + 20))
#define local_30 (*(int *)(abi_storage + 24))
#define auStack_46 (*(uint8_t(*)[2])(abi_storage + 2))
#define local_48 (*(uint8_t *)(abi_storage + 0))
#define local_47 (*(uint8_t *)(abi_storage + 1))
#define local_44 (*(uint16_t(*)[2])(abi_storage + 4))
#define local_40 (*(uint32_t *)(abi_storage + 8))
#define local_3c (*(uint32_t *)(abi_storage + 12))

    uint16_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    int iVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint32_t uVar8;
    uint32_t uVar9;
    uint32_t uVar10;
    uint8_t bVar11;
    uint8_t bVar12;
    uint32_t uVar13;
    uint32_t uVar14;
    uint32_t uVar15;
    uint32_t index;
    uint16_t uVar16;
    uint8_t bVar17;
    uint32_t uVar18;

    index = param_1 & 0xff;
    uVar3 = sango_battle_unit_terrain(index);
    if (uVar3 != 5)
    {
        local_30 = index << 3;
        sango_battle_distance_components(&local_48, &local_47);
        uVar16 = 0;
        local_3c = (uint32_t)(uint8_t)(&g_first_unit_y)[local_30 - index];
        local_40 = (uint32_t)(uint8_t)(&g_first_unit_x)[local_30 - index];
        sango_battle_is_player_unit(index);
        local_38 = 0xff;
        bVar17 = (uint8_t)local_3c;
        local_34 = local_40;
        uVar18 = local_3c;
        for (uVar3 = (uint32_t)g_move_window_left; uVar3 < 0xf; uVar3 = uVar3 + 1 & 0xff)
        {
            for (uVar13 = (uint32_t)g_move_window_top; bVar17 = (uint8_t)uVar18, uVar13 < 0xf;
                 uVar13 = uVar13 + 1 & 0xff)
            {
                if (-1 < *(char *)(g_move_costs_address + uVar13 * 0xf + uVar3))
                {
                    uVar10 = (uint32_t)g_move_source_x + (uVar3 - g_move_window_left);
                    uVar4 = (uint32_t)g_move_source_y + (uVar13 - g_move_window_top);
                    uVar15 = uVar10 & 0xff;
                    uVar14 = uVar4 & 0xff;
                    iVar5 = sango_battle_terrain_at(uVar15, uVar14);
                    bVar11 = (uint8_t)uVar10;
                    bVar12 = (uint8_t)uVar4;
                    if ((g_battle_control_mode == '\0') && (iVar5 == 5))
                    {
                        (&g_first_unit_y)[local_30 - index] = bVar12;
                        (&g_first_unit_x)[local_30 - index] = bVar11;
                        sango_battle_redraw_field(index);
                        return;
                    }
                    uVar6 = sango_battle_manhattan_distance(bVar11, bVar12, local_48, local_47);
                    sango_battle_preview_skill_range(index, bVar11, bVar12);
                    sango_battle_select_combat_target(local_44, auStack_46);
                    uVar1 = local_44[0];
                    uVar4 = uVar14;
                    uVar10 = uVar6;
                    uVar2 = uVar15;
                    if (uVar16 == 0)
                    {
                        if (((local_44[0] == 0) && (local_38 <= uVar6)) &&
                            (uVar4 = uVar18, uVar10 = local_38, uVar2 = local_34,
                             local_38 == uVar6))
                        {
                            uVar4 = bbk_rand();
                            uVar7 = (int)uVar4 % 10 & 0xff;
                            uVar16 = uVar1;
                        LAB_81c01dc8:
                            uVar4 = uVar14;
                            uVar10 = uVar6;
                            uVar2 = uVar15;
                            if (uVar7 == 0)
                                goto LAB_81c01d0c;
                        }
                    }
                    else
                    {
                        if (local_44[0] < uVar16)
                            goto LAB_81c01d0c;
                        if ((local_44[0] <= uVar16) && (4 < (iVar5 - 2U & 0xff)))
                        {
                            uVar8 = sango_battle_manhattan_distance(
                                bVar11, bVar12, (uint8_t)local_40, (uint8_t)local_3c);
                            uVar9 = sango_battle_manhattan_distance(
                                (uint8_t)local_34, bVar17, (uint8_t)local_40, (uint8_t)local_3c);
                            uVar7 = 0;
                            if (uVar8 <= uVar9)
                                goto LAB_81c01dc8;
                        }
                    }
                    local_34 = uVar2;
                    local_38 = uVar10;
                    uVar18 = uVar4;
                    uVar16 = local_44[0];
                }
            LAB_81c01d0c:
            }
        }
        if (local_38 != 0xff)
        {
            (&g_first_unit_y)[local_30 - index] = bVar17;
            (&g_first_unit_x)[local_30 - index] = (char)local_34;
        }
    }
    return;
}
#undef local_38
#undef local_34
#undef local_30
#undef auStack_46
#undef local_48
#undef local_47
#undef local_44
#undef local_40
#undef local_3c

/* 原函数 0x81c01e74 */
uint32_t sango_battle_choose_skill(uint32_t param_1, uint16_t *param_2, uint8_t *param_3)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define acStack_30 (*(char(*)[16])(abi_storage + 0))

    uint8_t bVar1;
    uint16_t uVar2;
    uint16_t uVar3;
    uint32_t uVar4;
    uint16_t uVar5;

    uVar4 = sango_battle_is_player_unit(param_1 & 0xff);
    sango_battle_collect_unit_skills(uVar4, (char *)param_3);
    sango_battle_load_skill_names(param_3);
    uVar4 = bbk_strlen((char *)(param_3 + 0xb));
    uVar2 = param_2[2];
    uVar3 = *param_2;
    uVar5 = uVar2 + 4;
    uVar4 = uVar4 >> 2 & 0xff;
    *param_2 = uVar3 + 4;
    param_2[2] = uVar5;
    if (0xd3 < uVar5)
    {
        *param_2 = uVar3 - 0x14;
        param_2[2] = uVar2 - 0x14;
    }
    uVar2 = param_2[1];
    param_2[3] = param_2[3] - 6;
    param_2[1] = uVar2 + 6;
    if (uVar4 < 3)
    {
        param_2[3] = uVar2 + 6 + (short)uVar4 * 0xc;
    }
    while (true)
    {
        uVar4 = sango_ui_choose_option(param_2, 0, (char *)(param_3 + 0xb));
        if (uVar4 == 0xff)
        {
            return 0xff;
        }
        bVar1 = param_3[uVar4];
        uVar4 = sango_battle_skill_target_allowed((uint32_t)bVar1, param_1 & 0xff);
        if (uVar4 == 0)
            break;
        sango_battle_load_overview_text(uVar4, acStack_30);
        sango_text_draw_legacy(0x6a, 0xf3, acStack_30);
    }
    return (uint32_t)bVar1;
}
#undef acStack_30

/* 原函数 0x81c01fbc */
uint32_t sango_battle_skill_target_allowed(uint32_t param_1, uint32_t param_2)
{
    uint32_t uVar1;
    int iVar2;
    uint32_t uVar3;

    uVar1 = sango_battle_unit_terrain(param_2 & 0xff);
    iVar2 = sango_battle_skill_parameters(param_1 & 0xff);
    uVar3 = 6;
    if (((*(uint8_t *)(iVar2 + 6) <= (uint8_t)(&g_first_unit_energy)[(param_2 & 0xff) * 7]) &&
         (uVar3 = 5, *(char *)(uVar1 + iVar2 + 0x14) != '\0')) &&
        (uVar3 = 4, *(char *)((uint32_t)g_battle_weather + iVar2 + 6) != '\0'))
    {
        uVar3 = 0;
    }
    return uVar3;
}

/* 原函数 0x81c0205c */
void sango_battle_collect_unit_skills(uint32_t param_1, char *param_2)
{
    char cVar1;
    int iVar2;
    uint32_t right;
    uint32_t uVar3;
    uint32_t uVar4;
    int iVar5;

    sango_memory_fill(param_2, 0, 0xb);
    uVar3 = param_1 & 0xff;
    iVar2 = sango_resource_item(0xe, g_scenario_id, g_resource_package_address);
    if (*(char *)(iVar2 + uVar3) != '\0')
    {
        *param_2 = *(char *)(iVar2 + uVar3);
        param_2 = param_2 + 1;
    }
    if ((uint32_t) * (uint8_t *)(uVar3 * 0x10 + g_character_table_address + 1) == uVar3 + 1)
    {
        *param_2 = '\x1e';
        param_2 = param_2 + 1;
    }
    iVar2 = sango_resource_item(2, '\x02', g_resource_package_address);
    iVar5 = uVar3 * 0x10 + g_character_table_address;
    uVar4 = (uint32_t) * (uint8_t *)(iVar5 + 9);
    cVar1 = (&g_legacy_data_81c200bc)[uVar4];
    uVar3 = sango_soft_int_to_f32((int)cVar1);
    if (cVar1 < 0)
    {
        uVar3 = soft_float_add(uVar3, g_legacy_data_81c20c4c);
    }
    right = sango_soft_int_to_f32((uint32_t) * (uint8_t *)(iVar5 + 2));
    uVar3 = soft_float_mul(uVar3, right);
    uVar3 = soft_float_div(uVar3, g_legacy_data_81c20c54);
    uVar3 = soft_float_add(uVar3, g_legacy_data_81c20c58);
    uVar3 = sango_soft_f32_to_int(uVar3);
    bbk_memcpy(param_2, (void *)(iVar2 + uVar4 * 10), uVar3 & 0xff);
    return;
}

/* 原函数 0x81c021d4 */
void sango_battle_load_skill_names(uint8_t *param_1)
{
    uint8_t *pbVar1;
    uint8_t *pbVar2;
    uint32_t uVar3;

    uVar3 = 0;
    pbVar1 = param_1;
    pbVar2 = param_1 + 0xb;
    do
    {
        if (*pbVar1 == 0)
        {
            return;
        }
        sango_resource_read_text(0xb, (uint32_t)*pbVar1, pbVar2);
        uVar3 = uVar3 + 1 & 0xff;
        pbVar1 = param_1 + uVar3;
        pbVar2 = pbVar2 + 4;
    } while (uVar3 < 10);
    return;
}

/* 原函数 0x81c02244 */
uint32_t sango_battle_skill_terrain_allowed(uint32_t param_1, char param_2, uint32_t param_3)
{
    uint8_t bVar1;
    uint32_t uVar2;
    char *pcVar3;
    uint32_t uVar4;

    bVar1 = *(uint8_t *)((uint32_t)(uint8_t)(&g_battle_roster_first)[param_3 & 0xff] * 0x10 +
                         g_character_table_address + -7);
    uVar2 = sango_battle_unit_terrain(param_3 & 0xff);
    pcVar3 = (char *)sango_battle_skill_parameters(param_1 & 0xff);
    uVar4 = 0;
    if ((((pcVar3[bVar1 + 0x1c] != '\0') && (pcVar3[uVar2 + 0xc] != '\0')) &&
         ((*pcVar3 != '\x01' || (param_2 != '\0')))) &&
        ((*pcVar3 != '\0' || (param_2 == '\0'))))
    {
        uVar4 = 1;
    }
    return uVar4;
}

/* 原函数 0x81c02314 */
uint32_t sango_battle_unit_terrain(uint32_t index)
{
    int iVar1;
    uint32_t uVar2;

    iVar1 = (index & 0xff) * 7;
    uVar2 = sango_battle_terrain_at((uint32_t)(uint8_t)(&g_first_unit_x)[iVar1],
                                    (uint32_t)(uint8_t)(&g_first_unit_y)[iVar1]);
    return uVar2;
}

/* 原函数 0x81c02354 */
void sango_battle_select_combat_target(uint16_t *param_1, uint8_t *param_2)
{
    int iVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t uVar5;

    uVar5 = 0xff;
    uVar4 = 0;
    uVar3 = 0;
    iVar1 = 0;
    do
    {
        iVar1 = iVar1 - uVar3;
        if (((&g_first_unit_status)[iVar1] != '\b') &&
            (uVar2 =
                 sango_battle_target_in_skill_range((uint32_t)(uint8_t)(&g_first_unit_x)[iVar1],
                                                    (uint32_t)(uint8_t)(&g_first_unit_y)[iVar1]),
             uVar2 != 0))
        {
            if (g_battle_player_unit_begin == uVar3)
            {
                uVar4 = 0xffff;
                uVar5 = uVar3;
                break;
            }
            sango_battle_prepare_combatant(1, uVar3);
            uVar2 = sango_battle_roll_attack_damage();
            if (uVar4 < uVar2)
            {
                uVar4 = uVar2;
                uVar5 = uVar3;
            }
        }
        uVar3 = uVar3 + 1 & 0xff;
        iVar1 = uVar3 << 3;
    } while (uVar3 < 10);
    *param_1 = (short)uVar4;
    *param_2 = (char)uVar5;
    return;
}

/* 原函数 0x81c02444 */
uint32_t sango_battle_target_in_skill_range(int param_1, int param_2)
{
    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint32_t uVar4;

    uVar4 = (uint32_t)*g_temp_character_ids_address;
    uVar3 = param_2 - (uint32_t)g_temp_character_ids_address[2] & 0xff;
    uVar2 = param_1 - (uint32_t)g_temp_character_ids_address[1] & 0xff;
    uVar1 = 0;
    if ((uVar3 < uVar4) && (uVar2 < uVar4))
    {
        uVar1 = (uint32_t)(g_temp_character_ids_address[uVar2 + uVar3 * uVar4 + 3] == 1);
    }
    return uVar1;
}

/* 原函数 0x81c024a0 */
void sango_battle_preview_skill_range(uint32_t param_1, uint8_t param_2, uint8_t param_3)
{
    uint8_t uVar1;
    uint8_t uVar2;
    int iVar3;
    uint8_t *puVar4;
    uint32_t uVar5;

    uVar5 = param_1 & 0xff;
    iVar3 = uVar5 * 7;
    puVar4 = &g_first_unit_x + iVar3;
    uVar1 = *puVar4;
    uVar2 = (&g_first_unit_y)[iVar3];
    *puVar4 = param_2;
    (&g_first_unit_y)[iVar3] = param_3;
    sango_battle_prepare_combatant(0, uVar5);
    sango_battle_load_range_template('\0', 0, uVar5);
    (&g_first_unit_y)[iVar3] = uVar2;
    *puVar4 = uVar1;
    return;
}

/* 原函数 0x81c02524 */
void sango_battle_load_range_template(char param_1, uint32_t param_2, uint32_t param_3)
{
    char cVar1;
    int iVar2;
    uint32_t in_t0;
    char in_t1;
    uint32_t unaff_s1;
    uint32_t unaff_s2;

    if (param_1 == '\0')
    {
        in_t0 = 2;
        in_t1 = '\x01';
        unaff_s1 = 5;
        unaff_s2 = (uint32_t) *
                   (uint8_t *)((uint32_t)(uint8_t)(&g_battle_roster_first)[param_3 & 0xff] * 0x10 +
                               g_character_table_address + -7) *
                   0x19;
    }
    else if (param_1 == '\x01')
    {
        unaff_s2 = ((param_2 & 0xff) - 1 & 0xffff) * 0x51 & 0xffff;
        unaff_s1 = 9;
        in_t0 = 0xd;
        in_t1 = '\x01';
    }
    iVar2 = sango_resource_item(in_t0, in_t1, g_resource_package_address);
    if ((int)(unaff_s1 * unaff_s1) < 0x54)
    {
        bbk_memcpy(g_temp_character_ids_address + 3, (void *)(iVar2 + unaff_s2),
                   unaff_s1 * unaff_s1);
        iVar2 = (param_3 & 0xff) * 7;
        *g_temp_character_ids_address = (char)unaff_s1;
        cVar1 = (char)(unaff_s1 >> 1);
        g_temp_character_ids_address[1] = (&g_first_unit_x)[iVar2] - cVar1;
        g_temp_character_ids_address[2] = (&g_first_unit_y)[iVar2] - cVar1;
    }
    return;
}

/* 原函数 0x81c02664 */
uint32_t sango_battle_select_ai_unit(void)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define local_18 (*(uint8_t *)(abi_storage + 0))
#define local_17 (*(uint8_t(*)[7])(abi_storage + 1))

    char cVar1;
    int iVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;

    uVar5 = 0xff;
    sango_battle_distance_components(&local_18, local_17);
    uVar6 = 0xff;
    uVar4 = 10;
    iVar2 = 0x50;
    do
    {
        iVar2 = iVar2 - uVar4;
        cVar1 = (&g_first_unit_status)[iVar2];
        if ((((cVar1 != '\b') && (cVar1 != '\x01')) && (cVar1 != '\x06')) &&
            (((&g_first_unit_has_acted)[iVar2] != '\x01' &&
              (uVar3 = sango_battle_manhattan_distance(
                   (&g_first_unit_x)[iVar2], (&g_first_unit_y)[iVar2], local_18, local_17[0]),
               uVar3 < uVar5))))
        {
            uVar5 = uVar3;
            uVar6 = uVar4;
        }
        uVar4 = uVar4 + 1 & 0xff;
        iVar2 = uVar4 << 3;
    } while (uVar4 < 0x14);
    return uVar6;
}
#undef local_18
#undef local_17

/* 原函数 0x81c0272c */
void sango_battle_distance_components(uint8_t *param_1, uint8_t *param_2)
{
    if (g_battle_control_mode != '\x01')
    {
        *param_1 = g_battle_spawn_x;
        *param_2 = g_battle_spawn_y;
        return;
    }
    *param_1 = (&g_first_unit_x)[(uint32_t)g_battle_player_unit_begin * 7];
    *param_2 = (&g_first_unit_y)[(uint32_t)g_battle_player_unit_begin * 7];
    return;
}

/* 原函数 0x81c027a0 */
uint32_t sango_battle_manhattan_distance(uint8_t param_1, uint8_t param_2, uint8_t param_3,
                                         uint8_t param_4)
{
    char cVar1;
    char cVar2;

    cVar1 = param_1 - param_3;
    if (param_1 < param_3)
    {
        cVar1 = -(param_1 - param_3);
    }
    cVar2 = param_2 - param_4;
    if (param_2 < param_4)
    {
        cVar2 = -(param_2 - param_4);
    }
    return (uint32_t)(uint8_t)(cVar1 + cVar2);
}

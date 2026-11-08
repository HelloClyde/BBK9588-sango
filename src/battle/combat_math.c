#include "sango_internal.h"

/* 部队属性与伤害计算。 */

/* 原函数 0x81c00bfc */
void sango_battle_initialize_unit_stats(void)
{
    uint8_t bVar1;
    uint8_t bVar2;
    uint8_t bVar3;
    uint8_t bVar4;
    char cVar5;
    int iVar6;
    uint32_t uVar7;
    int iVar8;
    int iVar9;
    uint32_t uVar10;
    uint32_t uVar11;
    char unaff_s6;

    uVar11 = 0;
    do
    {
        iVar6 = uVar11 * 7;
        (&g_first_unit_status)[iVar6] = 0;
        if (uVar11 % 10 == 0)
        {
            unaff_s6 = '\0';
        }
        uVar7 = sango_battle_character_id(uVar11);
        if (uVar7 == 0xff)
        {
            unaff_s6 = unaff_s6 + '\x01';
            (&g_first_unit_status)[iVar6] = 8;
            if (unaff_s6 == '\n')
            {
                g_battle_result = '\x02' - (char)(uVar11 / 10);
                return;
            }
        }
        else
        {
            iVar8 = g_character_table_address + uVar7 * 0x10;
            bVar1 = *(uint8_t *)(iVar8 + 3);
            bVar2 = *(uint8_t *)(iVar8 + 4);
            bVar3 = *(uint8_t *)(iVar8 + 2);
            bVar4 = *(uint8_t *)(iVar8 + 8);
            uVar10 = 0;
            (&g_first_unit_life)[iVar6] =
                (char)(((((uint32_t)bVar1 * 0x50) / 100 + ((uint32_t)bVar2 * 0x1e) / 100 +
                         (uint32_t)bVar3) *
                        (uint32_t)bVar4) /
                       100);
            uVar7 = sango_math_sqrt_step_search((uint16_t)bVar1);
            (&g_first_unit_energy)[iVar6] =
                (char)(((((uint32_t)bVar2 * 0x50) / 100 + (uVar7 >> 1 & 0xff) + (uint32_t)bVar3) *
                        (uint32_t)bVar4) /
                       100);
            uVar7 = sango_battle_character_id(uVar11);
            iVar9 = g_character_table_address + uVar7 * 0x10;
            (&g_first_unit_move_range)[iVar6] = (&g_legacy_data_81c1ffc0)[*(uint8_t *)(iVar9 + 9)];
            iVar8 = iVar9;
            do
            {
                bVar1 = *(uint8_t *)(iVar8 + 0xc);
                if (bVar1 != 0)
                {
                    iVar8 = sango_resource_item(0x42, '\x01', g_resource_package_address);
                    iVar8 = iVar8 + (bVar1 - 1 & 0xffff) * 0x42;
                    if ((iVar8 != 0) && (cVar5 = *(char *)(iVar8 + 0x40), cVar5 != '\0'))
                    {
                        (&g_first_unit_move_range)[iVar6] =
                            (&g_first_unit_move_range)[iVar6] + cVar5;
                    }
                }
                uVar10 = uVar10 + 1 & 0xff;
                iVar8 = uVar10 + iVar9;
            } while (uVar10 < 2);
            if (8 < (uint8_t)(&g_first_unit_move_range)[iVar6])
            {
                (&g_first_unit_move_range)[iVar6] = 8;
            }
        }
        uVar11 = uVar11 + 1 & 0xff;
    } while (uVar11 < 0x14);
    return;
}

/* 原函数 0x81c00e90 */
void sango_battle_refresh_unit_stats(uint32_t param_1)
{
    uint8_t bVar1;
    uint8_t bVar2;
    uint8_t bVar3;
    uint8_t bVar4;
    char cVar5;
    int iVar6;
    uint32_t uVar7;
    int iVar8;
    int iVar9;
    uint32_t uVar10;
    uint32_t uVar11;

    uVar10 = param_1 & 0xff;
    iVar6 = uVar10 * 7;
    uVar7 = sango_battle_character_id(uVar10);
    iVar8 = g_character_table_address + uVar7 * 0x10;
    bVar1 = *(uint8_t *)(iVar8 + 3);
    bVar2 = *(uint8_t *)(iVar8 + 4);
    bVar3 = *(uint8_t *)(iVar8 + 2);
    bVar4 = *(uint8_t *)(iVar8 + 8);
    uVar11 = 0;
    (&g_first_unit_life)[iVar6] = (char)(((((uint32_t)bVar1 * 0x50) / 100 +
                                           ((uint32_t)bVar2 * 0x1e) / 100 + (uint32_t)bVar3) *
                                          (uint32_t)bVar4) /
                                         100);
    uVar7 = sango_math_sqrt_step_search((uint16_t)bVar1);
    (&g_first_unit_energy)[iVar6] =
        (char)(((((uint32_t)bVar2 * 0x50) / 100 + (uVar7 >> 1 & 0xff) + (uint32_t)bVar3) *
                (uint32_t)bVar4) /
               100);
    uVar7 = sango_battle_character_id(uVar10);
    iVar9 = g_character_table_address + uVar7 * 0x10;
    (&g_first_unit_move_range)[iVar6] = (&g_legacy_data_81c1ffc0)[*(uint8_t *)(iVar9 + 9)];
    iVar8 = iVar9;
    do
    {
        bVar1 = *(uint8_t *)(iVar8 + 0xc);
        if (bVar1 != 0)
        {
            iVar8 = sango_resource_item(0x42, '\x01', g_resource_package_address);
            iVar8 = iVar8 + (bVar1 - 1 & 0xffff) * 0x42;
            if ((iVar8 != 0) && (cVar5 = *(char *)(iVar8 + 0x40), cVar5 != '\0'))
            {
                (&g_first_unit_move_range)[iVar6] = (&g_first_unit_move_range)[iVar6] + cVar5;
            }
        }
        uVar11 = uVar11 + 1 & 0xff;
        iVar8 = uVar11 + iVar9;
    } while (uVar11 < 2);
    if (8 < (uint8_t)(&g_first_unit_move_range)[iVar6])
    {
        (&g_first_unit_move_range)[iVar6] = 8;
    }
    return;
}

/* 原函数 0x81c0108c */
void sango_battle_remove_unit_status(uint32_t param_1)
{
    uint8_t bVar1;
    char cVar2;
    int iVar3;
    uint32_t uVar4;
    int iVar5;
    uint32_t uVar6;
    int iVar7;

    iVar3 = (param_1 & 0xff) * 7;
    uVar4 = sango_battle_character_id(param_1 & 0xff);
    uVar6 = 0;
    iVar7 = g_character_table_address + uVar4 * 0x10;
    (&g_first_unit_move_range)[iVar3] = (&g_legacy_data_81c1ffc0)[*(uint8_t *)(iVar7 + 9)];
    iVar5 = iVar7;
    do
    {
        bVar1 = *(uint8_t *)(iVar5 + 0xc);
        if (bVar1 != 0)
        {
            iVar5 = sango_resource_item(0x42, '\x01', g_resource_package_address);
            iVar5 = iVar5 + (bVar1 - 1 & 0xffff) * 0x42;
            if ((iVar5 != 0) && (cVar2 = *(char *)(iVar5 + 0x40), cVar2 != '\0'))
            {
                (&g_first_unit_move_range)[iVar3] = (&g_first_unit_move_range)[iVar3] + cVar2;
            }
        }
        uVar6 = uVar6 + 1 & 0xff;
        iVar5 = uVar6 + iVar7;
    } while (uVar6 < 2);
    if (8 < (uint8_t)(&g_first_unit_move_range)[iVar3])
    {
        (&g_first_unit_move_range)[iVar3] = 8;
    }
    return;
}

/* 原函数 0x81c0118c */
uint32_t sango_battle_roll_attack_damage(void)
{
    uint32_t uVar1;
    uint32_t uVar2;

    uVar2 = (uint32_t)g_attacker_attack;
    uVar1 = sango_soft_int_to_f32(uVar2);
    if ((int)uVar2 < 0)
    {
        uVar1 = soft_float_add(uVar1, g_legacy_data_81c20c48);
    }
    uVar2 = sango_soft_int_to_f32((uint32_t)g_legacy_data_81c2b256);
    uVar1 = soft_float_div(uVar1, uVar2);
    uVar2 = sango_soft_int_to_f32((uint32_t)(*g_attacker_troops_address >> 3));
    uVar1 = soft_float_mul(uVar1, uVar2);
    uVar1 = sango_soft_f32_to_int(uVar1);
    uVar1 = sango_soft_int_to_f32(uVar1 & 0xffff);
    uVar1 = soft_float_mul(
        uVar1,
        *(uint32_t *)(((uint32_t)g_attacker_troop_type * 6 + (uint32_t)g_defender_troop_type) * 4 +
                      -0x7e3e0038));
    uVar1 = sango_soft_f32_to_int(uVar1);
    return uVar1 + 10 & 0xffff;
}

/* 原函数 0x81c01278 */
/* 将攻击方或防守方的武将属性、地形和兵种写入20字节战斗视图。 */
void sango_battle_prepare_combatant(uint32_t param_1, uint32_t param_2)
{
    uint8_t bVar1;
    uint8_t bVar2;
    uint32_t uVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    uint32_t uVar7;
    int iVar8;
    uint32_t uVar9;

    uVar7 = param_1 & 0xff;
    uVar3 = sango_battle_character_id(param_2 & 0xff);
    iVar6 = uVar7 * 0x14;
    iVar5 = (param_2 & 0xff) * 7;
    if (uVar3 < 200)
    {
        bVar1 = (&g_first_unit_y)[iVar5];
        bVar2 = (&g_first_unit_x)[iVar5];
        iVar8 = g_character_table_address + uVar3 * 0x10;
        (&g_attacker_level_address)[uVar7 * 5] = iVar8 + 2;
        (&g_attacker_initiative)[iVar6] = *(char *)(iVar8 + 4) + *(char *)(iVar8 + 2) + '\x05';
        iVar4 = sango_battle_terrain_at((uint32_t)bVar2, (uint32_t)bVar1);
        (&g_attacker_terrain)[iVar6] = (char)iVar4;
        (&g_legacy_data_81c2b236)[iVar6] = 0;
        iVar5 = g_resource_package_address;
        bVar1 = *(uint8_t *)(iVar8 + 9);
        (&g_attacker_experience_address)[uVar7 * 5] = iVar8 + 7;
        (&g_attacker_troop_type)[iVar6] = bVar1;
        (&g_attacker_troops_address_view2)[uVar7 * 5] = iVar8 + 10;
        iVar5 = sango_resource_item(2, '\x04', iVar5);
        iVar6 = (uint32_t)bVar1 * 4;
        uVar9 = (uint32_t) * (uint8_t *)(iVar5 + (uint32_t)bVar1 * 8 + iVar4);
        uVar3 = sango_soft_int_to_f32((uint32_t) * (uint8_t *)(iVar8 + 3) *
                                      (*(uint8_t *)(iVar8 + 2) + 10));
        uVar3 = soft_float_mul(uVar3, *(uint32_t *)(&g_legacy_data_81c20058 + iVar6));
        uVar3 = sango_soft_f32_to_int(uVar3);
        (&g_attacker_attack_view2)[uVar7 * 10] = (short)((int)(uVar3 & 0xffff) >> (uVar9 & 0x1f));
        uVar3 = sango_soft_int_to_f32((uint32_t) * (uint8_t *)(iVar8 + 4) *
                                      (*(uint8_t *)(iVar8 + 2) + 10));
        uVar3 = soft_float_mul(uVar3, *(uint32_t *)(&g_legacy_data_81c20070 + iVar6));
        uVar3 = sango_soft_f32_to_int(uVar3);
        uVar3 = sango_soft_int_to_f32((int)(uVar3 & 0xffff) >> (uVar9 & 0x1f) & 0xffff);
        uVar3 = soft_float_mul(uVar3, *(uint32_t *)(&g_legacy_data_81c20088 + iVar4 * 4));
        uVar3 = sango_soft_f32_to_int(uVar3);
        (&g_attacker_defense)[uVar7 * 10] = (short)uVar3;
    }
    return;
}

/* 原函数 0x81c0142c */
void sango_battle_consume_daily_food(void)
{
    uint32_t daily_cost;
    uint16_t *food;
    uint8_t side;

    side = 0;
    do
    {
        daily_cost = sango_battle_sum_side_troops(side);
        daily_cost = sango_math_sqrt_step_search((uint16_t)daily_cost);
        food = &g_battle_defender_food;
        if (side == 0)
        {
            food = &g_battle_attacker_food;
        }
        daily_cost = daily_cost / 3 & 0xff;
        if (*food < daily_cost)
        {
            *food = 0;
        }
        else
        {
            *food = *food - (short)daily_cost;
        }
        side = side + 1;
    } while (side < 2);
    return;
}

/* 原函数 0x81c014bc */
uint32_t sango_battle_subtract_clamped(uint16_t *value, uint16_t amount)
{
    uint16_t removed;
    uint16_t uVar2;
    uint32_t uVar3;

    removed = *value;
    uVar3 = (uint32_t)amount;
    uVar2 = removed - amount;
    if (removed <= uVar3)
    {
        uVar2 = 0;
        uVar3 = (uint32_t)removed;
    }
    *value = uVar2;
    return uVar3;
}

/* 原函数 0x81c014ec */
uint32_t sango_battle_add_clamped(uint16_t *value, uint32_t amount, uint16_t limit)
{
    uint32_t added;
    uint32_t uVar2;

    added = amount & 0xffff;
    uVar2 = *value + added;
    if (limit < uVar2)
    {
        added = (uint32_t)limit - (uint32_t)*value & 0xffff;
    }
    else
    {
        limit = (uint16_t)uVar2;
    }
    *value = limit;
    return added;
}

/* 原函数 0x81c01524 */
void sango_battle_compute_skill_effect(int param_1, uint16_t *param_2, uint16_t *param_3)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define local_38 (*(uint16_t(*)[4])(abi_storage + 0))
#define local_30 (*(uint32_t *)(abi_storage + 8))
#define local_2c (*(uint32_t *)(abi_storage + 12))

    uint32_t uVar1;
    int iVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint32_t uVar8;

    uVar1 = (uint32_t)g_battle_weather;
    local_2c = (uint32_t)g_attacker_terrain;
    uVar8 = (uint32_t)g_defender_terrain;
    local_30 = (uint32_t)g_defender_troop_type;
    local_38[0] = *(uint16_t *)(param_1 + 2);
    local_38[1] = *(uint16_t *)(param_1 + 4);
    uVar7 = 0;
    iVar2 = 0;
    do
    {
        uVar4 = (uint32_t) * (uint16_t *)((int)local_38 + iVar2);
        if (uVar4 != 0)
        {
            uVar4 = sango_soft_int_to_f32(uVar4);
            uVar5 = (uint32_t) * (char *)(uVar1 + param_1 + 6);
            uVar3 = sango_soft_int_to_f32(uVar5);
            if ((int)uVar5 < 0)
            {
                uVar3 = soft_float_add(uVar3, g_legacy_data_81c20c4c);
            }
            uVar5 = g_legacy_data_81c20c50;
            uVar3 = soft_float_div(uVar3, g_legacy_data_81c20c50);
            uVar4 = soft_float_mul(uVar4, uVar3);
            uVar4 = sango_soft_f32_to_int(uVar4);
            uVar4 = sango_soft_int_to_f32(uVar4 & 0xffff);
            uVar6 = (uint32_t) * (char *)(local_30 + param_1 + 0x1c);
            uVar3 = sango_soft_int_to_f32(uVar6);
            if ((int)uVar6 < 0)
            {
                uVar3 = soft_float_add(uVar3, g_legacy_data_81c20c4c);
            }
            uVar3 = soft_float_div(uVar3, uVar5);
            uVar4 = soft_float_mul(uVar4, uVar3);
            uVar4 = sango_soft_f32_to_int(uVar4);
            uVar4 = sango_soft_int_to_f32(uVar4 & 0xffff);
            uVar6 = (uint32_t) * (char *)(uVar8 + param_1 + 0xc);
            uVar3 = sango_soft_int_to_f32(uVar6);
            if ((int)uVar6 < 0)
            {
                uVar3 = soft_float_add(uVar3, g_legacy_data_81c20c4c);
            }
            uVar3 = soft_float_div(uVar3, uVar5);
            uVar4 = soft_float_mul(uVar4, uVar3);
            uVar4 = sango_soft_f32_to_int(uVar4);
            uVar4 = sango_soft_int_to_f32(uVar4 & 0xffff);
            uVar5 = (uint32_t) * (char *)(local_2c + param_1 + 0x14);
            uVar3 = sango_soft_int_to_f32(uVar5);
            if ((int)uVar5 < 0)
            {
                uVar3 = soft_float_add(uVar3, g_legacy_data_81c20c4c);
            }
            uVar3 = soft_float_div(uVar3, g_legacy_data_81c20c50);
            uVar4 = soft_float_mul(uVar4, uVar3);
            uVar4 = sango_soft_f32_to_int(uVar4);
            *(uint16_t *)((int)local_38 + iVar2) = (uint16_t)uVar4;
        }
        uVar7 = uVar7 + 1 & 0xff;
        iVar2 = uVar7 << 1;
    } while (uVar7 < 2);
    *param_2 = local_38[0];
    *param_3 = local_38[1];
    return;
}
#undef local_38
#undef local_30
#undef local_2c

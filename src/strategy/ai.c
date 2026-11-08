#include "sango_internal.h"

/* 电脑城市的内政、外交和军事决策。 */

/* 原函数 0x81c19df8 */
void sango_strategy_run_city_ai(void)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define abStack_20 (*(uint8_t(*)[8])(abi_storage + 0))
#define abStack_18 (*(uint8_t(*)[8])(abi_storage + 8))

    char cVar1;
    uint8_t bVar2;
    int iVar3;
    uint32_t uVar4;
    uint8_t bVar5;
    uint32_t uVar6;
    uint32_t uVar7;

    sango_resource_read_text(2, 0xc, abStack_20);
    sango_resource_read_text(2, 0xd, abStack_18);
    uVar7 = 0;
    do
    {
        iVar3 = uVar7 * 0x24;
        uVar6 = (uint32_t)(uint8_t)(&g_first_city_owner)[iVar3];
        (&g_first_city_status)[iVar3] = 0;
        if ((uVar6 != 0) && (uVar6 != g_player_character + 1))
        {
            cVar1 = (&g_first_city_disaster_prevention)[iVar3];
            (&g_first_city_disaster_prevention)[iVar3] = cVar1 + 1U;
            if (100 < (uint8_t)(cVar1 + 1U))
            {
                (&g_first_city_disaster_prevention)[iVar3] = 100;
            }
            if ((uint16_t)(&g_first_city_food)[uVar7 * 0x12] < 100)
            {
                (&g_first_city_food)[uVar7 * 0x12] = 500;
            }
            if (10000 < (uint16_t)(&g_first_city_money)[uVar7 * 0x12])
            {
                (&g_first_city_money)[uVar7 * 0x12] =
                    (uint16_t)(&g_first_city_money)[uVar7 * 0x12] >> 1;
            }
            uVar4 = bbk_rand();
            bVar2 = *(uint8_t *)(uVar6 * 0x10 + g_character_table_address + -10);
            uVar6 = (int)uVar4 % 100 & 0xff;
            bVar5 = (uint8_t)uVar7;
            if (uVar6 < abStack_20[bVar2])
            {
                sango_strategy_ai_domestic_actions(bVar5);
                sango_strategy_ai_city_events(bVar5);
            }
            else if (uVar6 < abStack_18[bVar2])
            {
                sango_strategy_ai_diplomacy_actions(bVar5);
            }
            else
            {
                sango_strategy_ai_military_actions(bVar5);
            }
        }
        uVar7 = uVar7 + 1 & 0xff;
    } while (uVar7 < 0x26);
    return;
}
#undef abStack_20
#undef abStack_18

/* 原函数 0x81c19f8c */
void sango_strategy_ai_domestic_actions(uint8_t param_1)
{
    unsigned char abi_storage[44] __attribute__((aligned(8)));
#define local_38 (*(int *)(abi_storage + 16))
#define local_34 (*(uint32_t *)(abi_storage + 20))
#define local_30 (*(uint32_t *)(abi_storage + 24))
#define local_48 (*(uint8_t *)(abi_storage + 0))
#define local_47 (*(uint8_t *)(abi_storage + 1))
#define local_46 (*(uint8_t *)(abi_storage + 2))
#define local_45 (*(uint8_t *)(abi_storage + 3))
#define local_3d (*(uint8_t *)(abi_storage + 11))

    uint8_t bVar1;
    uint16_t uVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint8_t *pbVar6;
    uint32_t uVar7;
    uint32_t *puVar8;
    uint8_t *pbVar9;
    uint16_t *puVar10;
    uint16_t *puVar11;

    uVar3 = (uint32_t)param_1;
    local_38 = g_scratch_buffer_address;
    local_30 = (uint32_t)(uint16_t)(&g_first_city_agriculture_limit)[uVar3 * 0x12];
    local_34 = (uint32_t)(uint16_t)(&g_first_city_commerce_limit)[uVar3 * 0x12];
    uVar4 = sango_city_list_idle_characters(uVar3, g_scratch_buffer_address);
    puVar11 = &g_first_city_agriculture + uVar3 * 0x12;
    puVar10 = &g_first_city_commerce + uVar3 * 0x12;
    pbVar9 = &g_first_city_loyalty + uVar3 * 0x24;
    puVar8 = &g_first_city_population_limit + uVar3 * 9;
    uVar7 = 0;
    if (uVar4 != 0)
    {
        do
        {
            uVar5 = bbk_rand();
            switch ((int)uVar5 % 5 & 0xff)
            {
            case 0:
                uVar2 = *puVar11;
                *puVar11 = uVar2 + 200;
                if (local_30 < (uint16_t)(uVar2 + 200))
                {
                    *puVar11 = (uint16_t)local_30;
                }
                local_48 = 1;
                break;
            case 1:
                uVar2 = *puVar10;
                *puVar10 = uVar2 + 200;
                if (local_34 < (uint16_t)(uVar2 + 200))
                {
                    *puVar10 = (uint16_t)local_34;
                }
                local_48 = 2;
                break;
            case 2:
                local_48 = 3;
                break;
            case 3:
                bVar1 = *pbVar9;
                *pbVar9 = bVar1 + 4;
                if (100 < (uint8_t)(bVar1 + 4))
                {
                    *pbVar9 = 100;
                }
                uVar5 = *puVar8;
                *puVar8 = uVar5 + 100;
                if ((uint32_t)(&g_first_city_population)[uVar3 * 9] < uVar5 + 100)
                {
                    *puVar8 = (&g_first_city_population)[uVar3 * 9];
                }
                local_48 = 5;
                break;
            case 4:
                goto switchD_81c1a094_caseD_4;
            }
            pbVar6 = (uint8_t *)(local_38 + uVar7);
            local_47 = *pbVar6;
            local_3d = 0;
            local_46 = param_1;
            local_45 = param_1;
            sango_strategy_enqueue_order(&local_48);
            sango_city_remove_character(uVar3, *pbVar6);
        switchD_81c1a094_caseD_4:
            uVar7 = uVar7 + 1 & 0xff;
        } while (uVar7 < uVar4);
    }
    return;
}
#undef local_38
#undef local_34
#undef local_30
#undef local_48
#undef local_47
#undef local_46
#undef local_45
#undef local_3d

/* 原函数 0x81c1a188 */
void sango_strategy_ai_diplomacy_actions(uint8_t param_1)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define local_30 (*(uint8_t *)(abi_storage + 0))
#define local_2f (*(uint8_t *)(abi_storage + 1))
#define local_2e (*(uint8_t *)(abi_storage + 2))
#define local_2d (*(uint8_t *)(abi_storage + 3))
#define local_25 (*(uint8_t *)(abi_storage + 11))

    uint32_t uVar1;
    int iVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint8_t bVar6;
    uint8_t *pbVar7;
    uint8_t *pbVar8;
    uint32_t uVar9;

    iVar2 = g_scratch_buffer_address;
    uVar1 = (uint32_t)param_1;
    uVar3 = sango_city_list_idle_characters(uVar1, g_scratch_buffer_address);
    pbVar8 = (uint8_t *)(iVar2 + 200);
    uVar9 = 0;
    if (uVar3 != 0)
    {
        do
        {
            uVar4 = bbk_rand();
            uVar5 = uVar4 + 7;
            if (-1 < (int)uVar4)
            {
                uVar5 = uVar4;
            }
            uVar4 = uVar4 + ((int)uVar5 >> 3) * -8 & 0xff;
            uVar5 = sango_city_list_captives(uVar1, (int)pbVar8);
            if (uVar5 != 0)
            {
                uVar4 = 0;
            }
            switch (uVar4)
            {
            case 0:
                if (uVar5 != 0)
                {
                    uVar4 = bbk_rand();
                    if (uVar5 == 0)
                    {
                        sango_legacy_trap(7);
                    }
                    pbVar7 = (uint8_t *)((uint32_t)pbVar8[(int)uVar4 % (int)uVar5 & 0xff] * 0x10 +
                                         g_character_table_address);
                    if ((uint32_t)*pbVar7 == g_player_character + 1)
                    {
                        sango_city_remove_character(uVar1, pbVar8[(int)uVar4 % (int)uVar5 & 0xff]);
                        local_30 = 6;
                        goto switchD_81c1a250_default;
                    }
                    pbVar7[1] = (&g_first_city_owner)[uVar1 * 0x24];
                }
                break;
            case 1:
                if (uVar5 != 0)
                {
                    uVar4 = bbk_rand();
                    if (uVar5 == 0)
                    {
                        sango_legacy_trap(7);
                    }
                    bVar6 = pbVar8[(int)uVar4 % (int)uVar5 & 0xff];
                    goto LAB_81c1a320;
                }
                break;
            case 2:
            case 7:
                break;
            case 3:
                uVar5 = sango_city_list_enemy_neighbors(uVar1, (int)pbVar8);
                if (uVar5 != 0)
                {
                    uVar4 = bbk_rand();
                    if (uVar5 == 0)
                    {
                        sango_legacy_trap(7);
                    }
                    local_2d = pbVar8[(int)uVar4 % (int)uVar5 & 0xff];
                    local_30 = 0xf;
                    goto switchD_81c1a250_default;
                }
                break;
            case 4:
                uVar5 = sango_city_list_enemy_neighbors(uVar1, (int)pbVar8);
                if (uVar5 != 0)
                {
                    uVar4 = bbk_rand();
                    if (uVar5 == 0)
                    {
                        sango_legacy_trap(7);
                    }
                    local_2d = pbVar8[(int)uVar4 % (int)uVar5 & 0xff];
                    local_30 = 0x10;
                    goto switchD_81c1a250_default;
                }
                break;
            case 5:
                uVar5 = sango_city_list_enemy_rulers(uVar1, (int)pbVar8);
                if (uVar5 != 0)
                {
                    uVar4 = bbk_rand();
                    if (uVar5 == 0)
                    {
                        sango_legacy_trap(7);
                    }
                    local_2d = pbVar8[(int)uVar4 % (int)uVar5 & 0xff];
                    local_30 = 0x11;
                    goto switchD_81c1a250_default;
                }
                break;
            case 6:
                uVar5 = sango_strategy_list_rulers(uVar1, pbVar8);
                if (uVar5 != 0)
                {
                    uVar4 = bbk_rand();
                    if (uVar5 == 0)
                    {
                        sango_legacy_trap(7);
                    }
                    local_2d = pbVar8[(int)uVar4 % (int)uVar5 & 0xff];
                    local_30 = 0x13;
                    goto switchD_81c1a250_default;
                }
                break;
            default:
            switchD_81c1a250_default:
                pbVar7 = (uint8_t *)(iVar2 + uVar9);
                local_2f = *pbVar7;
                local_25 = 0;
                local_2e = param_1;
                sango_strategy_enqueue_order(&local_30);
                bVar6 = *pbVar7;
            LAB_81c1a320:
                sango_city_remove_character(uVar1, bVar6);
                goto LAB_81c1a264;
            }
        LAB_81c1a264:
            uVar9 = uVar9 + 1 & 0xff;
        } while (uVar9 < uVar3);
    }
    return;
}
#undef local_30
#undef local_2f
#undef local_2e
#undef local_2d
#undef local_25

/* 原函数 0x81c1a480 */
void sango_strategy_ai_city_events(uint8_t param_1)
{
    unsigned char abi_storage[36] __attribute__((aligned(8)));
#define local_40 (*(uint8_t *)(abi_storage + 0))
#define local_3f (*(uint8_t *)(abi_storage + 1))
#define local_3e (*(uint8_t *)(abi_storage + 2))
#define local_3d (*(uint8_t *)(abi_storage + 3))
#define local_35 (*(uint8_t *)(abi_storage + 11))
#define local_30 (*(uint32_t *)(abi_storage + 16))

    char cVar1;
    uint32_t uVar2;
    int iVar3;
    int iVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint8_t *pbVar7;
    uint32_t uVar8;
    uint32_t uVar9;
    uint32_t uVar10;
    uint8_t *pbVar11;

    iVar3 = g_scratch_buffer_address;
    uVar2 = (uint32_t)param_1;
    iVar4 = uVar2 * 0x24;
    uVar5 = sango_city_list_idle_characters(uVar2, g_scratch_buffer_address);
    pbVar11 = (uint8_t *)(iVar3 + 200);
    uVar10 = 0;
    if (uVar5 != 0)
    {
        do
        {
            uVar6 = bbk_rand();
            switch ((int)uVar6 % 7 & 0xff)
            {
            case 0:
                cVar1 = (&g_first_city_disaster_prevention)[iVar4];
                (&g_first_city_status)[iVar4] = 0;
                (&g_first_city_disaster_prevention)[iVar4] = cVar1 + 4U;
                if (100 < (uint8_t)(cVar1 + 4U))
                {
                    (&g_first_city_disaster_prevention)[iVar4] = 100;
                }
                local_40 = 4;
            default:
            switchD_81c1a570_default:
                local_3f = *(uint8_t *)(iVar3 + uVar10);
                local_35 = 0;
                local_3e = param_1;
                sango_strategy_enqueue_order(&local_40);
                sango_city_remove_character(uVar2, *(uint8_t *)(iVar3 + uVar10));
            case 1:
            case 2:
            case 3:
            case 4:
            case 6:
                break;
            case 5:
                if ((2 < uVar10) &&
                    (uVar6 = sango_faction_list_cities(
                         (uint8_t)(&g_first_city_owner)[iVar4] - 1 & 0xff, (int)pbVar11),
                     1 < uVar6))
                {
                    local_30 = 0;
                    uVar9 = 0;
                    pbVar7 = pbVar11;
                    if (uVar6 != 0)
                    {
                        do
                        {
                            uVar8 =
                                sango_city_find_neighbor_position((uint32_t)*pbVar7, iVar3 + 0xee);
                            if ((uVar8 != 0) && (uVar8 = bbk_rand(), local_30 = uVar9,
                                                 ((int)uVar8 % 2 & 0xffU) != 0))
                                break;
                            uVar9 = uVar9 + 1 & 0xff;
                            pbVar7 = pbVar11 + uVar9;
                        } while (uVar9 < uVar6);
                    }
                    local_3d = pbVar11[local_30];
                    local_40 = 0xe;
                    goto switchD_81c1a570_default;
                }
            }
            uVar10 = uVar10 + 1 & 0xff;
        } while (uVar10 < uVar5);
    }
    return;
}
#undef local_40
#undef local_3f
#undef local_3e
#undef local_3d
#undef local_35
#undef local_30

/* 原函数 0x81c1a6a4 */
void sango_strategy_ai_military_actions(uint8_t param_1)
{
    unsigned char abi_storage[44] __attribute__((aligned(8)));
#define local_38 (*(uint8_t *)(abi_storage + 16))
#define local_37 (*(uint8_t *)(abi_storage + 17))
#define local_36 (*(uint8_t *)(abi_storage + 18))
#define local_35 (*(uint8_t *)(abi_storage + 19))
#define local_34 (*(uint16_t *)(abi_storage + 20))
#define local_32 (*(uint16_t *)(abi_storage + 22))
#define local_2d (*(uint8_t *)(abi_storage + 27))
#define local_48 (*(char(*)[16])(abi_storage + 0))

    uint8_t bVar1;
    uint32_t uVar2;
    int iVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint8_t bVar8;
    char *pcVar9;
    int iVar10;
    uint32_t uVar11;
    uint8_t *pbVar12;
    uint8_t *pbVar13;
    uint32_t uVar14;

    iVar3 = g_scratch_buffer_address;
    uVar2 = (uint32_t)param_1;
    uVar4 = sango_city_list_idle_characters(uVar2, g_scratch_buffer_address);
    pbVar13 = (uint8_t *)(iVar3 + 200);
    if (uVar4 != 0)
    {
        uVar5 = bbk_rand();
        if (uVar4 == 0)
        {
            sango_legacy_trap(7);
        }
        iVar10 = g_character_table_address +
                 (uint32_t) * (uint8_t *)(iVar3 + (int)uVar5 % (int)uVar4) * 0x10;
        if (((uint32_t)g_current_month % 3 == 0) &&
            (bVar8 = *(char *)(iVar10 + 2) + 1, *(uint8_t *)(iVar10 + 2) = bVar8, 0x14 < bVar8))
        {
            *(uint8_t *)(iVar10 + 2) = 0x14;
        }
        uVar5 = 0;
        if (uVar4 != 0)
        {
            do
            {
                uVar6 = bbk_rand();
                switch ((int)uVar6 % 9 & 0xff)
                {
                case 0:
                    local_38 = 0x17;
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    iVar10 =
                        g_character_table_address + (uint32_t) * (uint8_t *)(iVar3 + uVar5) * 0x10;
                    *(uint16_t *)(iVar10 + 10) = ((uint16_t) * (uint8_t *)(iVar10 + 2) * 10 +
                                                  (uint16_t) * (uint8_t *)(iVar10 + 3) +
                                                  (uint16_t) * (uint8_t *)(iVar10 + 4)) *
                                                 10;
                    local_38 = 0x18;
                    local_34 = 0;
                    break;
                case 6:
                    local_38 = 0x1a;
                    break;
                case 7:
                    if (uVar5 == 0)
                    {
                        uVar6 = sango_city_find_neighbor_position(uVar2, (int)pbVar13);
                        if (uVar6 == 0)
                            break;
                        uVar7 = bbk_rand();
                        if (uVar6 << 1 == 0)
                        {
                            sango_legacy_trap(7);
                        }
                        if (((int)uVar7 % (int)(uVar6 << 1) & 0xffU) < uVar6)
                        {
                            uVar6 = sango_city_find_weakest_target(uVar6, (int)pbVar13);
                            local_35 = (uint8_t)uVar6;
                            uVar6 = sango_city_list_idle_characters(uVar2, (int)pbVar13);
                            if (uVar6 == 0)
                                break;
                            uVar7 = uVar6 - 1;
                            iVar10 = g_character_table_address;
                            if ((int)uVar7 < 1)
                            {
                                bVar8 = *pbVar13;
                            }
                            else
                            {
                                uVar11 = 0;
                                do
                                {
                                    uVar14 = uVar11 + 1 & 0xff;
                                    if (uVar14 < uVar6)
                                    {
                                        do
                                        {
                                            bVar8 = pbVar13[uVar11];
                                            bVar1 = pbVar13[uVar14];
                                            if (*(uint16_t *)((uint32_t)bVar8 * 0x10 + iVar10 +
                                                              10) <
                                                *(uint16_t *)((uint32_t)bVar1 * 0x10 + iVar10 + 10))
                                            {
                                                pbVar13[uVar14] = bVar8;
                                                pbVar13[uVar11] = bVar1;
                                                iVar10 = g_character_table_address;
                                            }
                                            if (*(short *)((uint32_t)pbVar13[uVar4 - 1] * 0x10 +
                                                           iVar10 + 10) == 0)
                                            {
                                                uVar6 = uVar7 & 0xff;
                                                uVar7 = uVar6 - 1;
                                            }
                                            uVar14 = uVar14 + 1 & 0xff;
                                        } while (uVar14 < uVar6);
                                    }
                                    uVar11 = uVar11 + 1 & 0xff;
                                } while ((int)uVar11 < (int)uVar7);
                                bVar8 = *pbVar13;
                            }
                            if ((999 < *(uint16_t *)((uint32_t)bVar8 * 0x10 + iVar10 + 10)) &&
                                (3 < uVar6))
                            {
                                uVar7 = uVar7 & 0xff;
                                local_38 = 0x1b;
                                sango_memory_fill(local_48, 0, 10);
                                if (10 < uVar7)
                                {
                                    uVar7 = 10;
                                }
                                uVar4 = 0;
                                if (uVar7 != 0)
                                {
                                    do
                                    {
                                        pbVar12 = pbVar13 + uVar4;
                                        sango_city_remove_character(uVar2, *pbVar12);
                                        pcVar9 = local_48 + uVar4;
                                        uVar4 = uVar4 + 1 & 0xff;
                                        *pcVar9 = *pbVar12 + 1;
                                    } while (uVar4 < uVar7);
                                }
                                local_32 = (&g_first_city_food)[uVar2 * 0x12];
                                local_2d = 0;
                                local_36 = param_1;
                                sango_strategy_queue_army(&local_38, local_48);
                                return;
                            }
                        }
                    }
                    goto LAB_81c1a810;
                case 8:
                    break;
                default:
                    local_37 = *(uint8_t *)(iVar3 + uVar5);
                    local_2d = 0;
                    local_36 = param_1;
                    sango_strategy_enqueue_order(&local_38);
                    sango_city_remove_character(uVar2, *(uint8_t *)(iVar3 + uVar5));
                    goto LAB_81c1a810;
                }
            LAB_81c1a810:
                uVar5 = uVar5 + 1 & 0xff;
            } while (uVar5 < uVar4);
        }
    }
    return;
}
#undef local_38
#undef local_37
#undef local_36
#undef local_35
#undef local_34
#undef local_32
#undef local_2d
#undef local_48

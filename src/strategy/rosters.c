#include "sango_internal.h"

/* 行动消耗、武将宝物列表与城市关系。 */

/* 原函数 0x81c12308 */
uint32_t sango_city_can_pay_command(uint32_t param_1, uint32_t param_2)
{
    int iVar1;

    iVar1 = sango_resource_item(2, '\v', g_resource_package_address);
    return (uint32_t)((uint16_t) * (uint8_t *)(iVar1 + (param_2 & 0xff)) <=
                      (uint16_t)(&g_first_city_money)[(param_1 & 0xff) * 0x12]);
}

/* 原函数 0x81c12374 */
void sango_city_pay_command(uint32_t param_1, uint32_t param_2)
{
    int iVar1;

    iVar1 = sango_resource_item(2, '\v', g_resource_package_address);
    (&g_first_city_money)[(param_1 & 0xff) * 0x12] =
        (&g_first_city_money)[(param_1 & 0xff) * 0x12] -
        (uint16_t) * (uint8_t *)(iVar1 + (param_2 & 0xff));
    return;
}

/* 原函数 0x81c123f0 */
uint32_t sango_city_remove_character(uint32_t param_1, uint8_t param_2)
{
    uint8_t bVar1;
    bool bVar2;
    int iVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;

    uVar6 = param_1 & 0xff;
    if ((uVar6 < 0x26) && (param_2 < 200))
    {
        iVar3 = uVar6 * 0x24;
        uVar4 = (uint32_t)(uint8_t)(&g_first_city_character_start)[iVar3];
        bVar1 = (&g_first_city_character_count)[iVar3];
        uVar5 = uVar4 + bVar1;
        for (; bVar2 = uVar4 < (uVar5 & 0xff), bVar2; uVar4 = uVar4 + 1 & 0xff)
        {
            if ((&g_city_character_roster)[uVar4] == param_2)
            {
                if (bVar2)
                {
                    for (; uVar4 < 199; uVar4 = uVar4 + 1 & 0xff)
                    {
                        (&g_city_character_roster)[uVar4] = (&g_city_character_roster_next)[uVar4];
                    }
                    (&g_first_city_character_count)[iVar3] = bVar1 - 1;
                    while (uVar6 = uVar6 + 1 & 0xff, uVar6 < 0x26)
                    {
                        (&g_first_city_character_start)[uVar6 * 0x24] =
                            (&g_first_city_character_start)[uVar6 * 0x24] + -1;
                    }
                    return 1;
                }
                return 0;
            }
        }
    }
    return 0;
}

/* 原函数 0x81c12504 */
uint32_t sango_city_remove_item(uint32_t param_1, uint8_t param_2)
{
    uint8_t bVar1;
    bool bVar2;
    int iVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;

    uVar6 = param_1 & 0xff;
    if ((uVar6 < 0x26) && (param_2 < 0x21))
    {
        iVar3 = uVar6 * 0x24;
        uVar4 = (uint32_t)(uint8_t)(&g_first_city_item_start)[iVar3];
        bVar1 = (&g_first_city_item_count)[iVar3];
        uVar5 = uVar4 + bVar1;
        for (; bVar2 = uVar4 < (uVar5 & 0xff), bVar2; uVar4 = uVar4 + 1 & 0xff)
        {
            if (((&g_city_item_roster)[uVar4] & 0x7f) == param_2)
            {
                if (bVar2)
                {
                    for (; uVar4 < 0x20; uVar4 = uVar4 + 1 & 0xff)
                    {
                        (&g_city_item_roster)[uVar4] = (&g_city_item_roster_next)[uVar4];
                    }
                    (&g_first_city_item_count)[iVar3] = bVar1 - 1;
                    while (uVar6 = uVar6 + 1 & 0xff, uVar6 < 0x26)
                    {
                        (&g_first_city_item_start)[uVar6 * 0x24] =
                            (&g_first_city_item_start)[uVar6 * 0x24] + -1;
                    }
                    return 1;
                }
                return 0;
            }
        }
    }
    return 0;
}

/* 原函数 0x81c1261c */
uint32_t sango_city_route_distance(uint32_t param_1, uint8_t param_2, uint8_t param_3, char param_4,
                                   uint8_t param_5, uint8_t param_6)
{
    unsigned char abi_storage[21] __attribute__((aligned(8)));
    (*(uint8_t *)(abi_storage + 0)) = param_5;
    (*(uint8_t *)(abi_storage + 4)) = param_6;
#define param_5 (*(uint8_t *)(abi_storage + 0))
#define param_6 (*(uint8_t *)(abi_storage + 4))

    char cVar1;
    uint8_t bVar2;
    uint32_t uVar3;
    char *pcVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    char *pcVar8;
    uint32_t uVar9;

    pcVar8 = (char *)(g_scratch_buffer_address + 200);
    uVar3 = sango_city_find_neighbor(param_1 & 0xff, (int)pcVar8);
    if (uVar3 != 0)
    {
        do
        {
            uVar7 = uVar3;
            uVar9 = 0;
            uVar3 = uVar7;
            if (uVar7 != 0)
            {
                do
                {
                    uVar6 = sango_city_find_neighbor((uint32_t)(uint8_t)pcVar8[uVar9],
                                                     (int)(pcVar8 + uVar3));
                    uVar9 = uVar9 + 1 & 0xff;
                    uVar3 = uVar3 + uVar6 & 0xff;
                } while (uVar9 < uVar7);
            }
            uVar9 = 0;
            if (uVar3 != 0)
            {
                uVar6 = 1;
                do
                {
                    uVar5 = uVar6 & 0xff;
                    if (uVar5 < uVar3)
                    {
                        do
                        {
                            if (pcVar8[uVar9] == pcVar8[uVar5])
                            {
                                uVar3 = uVar3 - 1 & 0xff;
                                pcVar8[uVar5] = pcVar8[uVar3];
                            }
                            else
                            {
                                uVar5 = uVar5 + 1 & 0xff;
                            }
                        } while (uVar5 < uVar3);
                    }
                    uVar9 = uVar6 & 0xff;
                    uVar6 = uVar9 + 1;
                } while (uVar9 < uVar3);
            }
        } while (uVar3 != uVar7);
        uVar3 = 0;
        if (uVar7 != 0)
        {
            pcVar4 = pcVar8;
            do
            {
                uVar3 = uVar3 + 1 & 0xff;
                if (*pcVar4 == param_4)
                {
                    cVar1 = param_6 - param_3;
                    if (param_6 <= param_3)
                    {
                        cVar1 = param_3 - param_6;
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
                pcVar4 = pcVar8 + uVar3;
            } while (uVar3 < uVar7);
        }
    }
    return 0xff;
}
#undef param_5
#undef param_6

/* 原函数 0x81c127ec */
uint32_t sango_city_find_neighbor(uint32_t param_1, int param_2)
{
    char cVar1;
    uint8_t bVar2;
    int iVar3;
    uint8_t *pbVar4;
    uint32_t uVar5;
    char *pcVar6;
    uint8_t *pbVar7;
    uint32_t uVar8;

    iVar3 = sango_resource_item(0x3b, '\x01', g_resource_package_address);
    cVar1 = (&g_first_city_owner)[(param_1 & 0xff) * 0x24];
    pbVar7 = (uint8_t *)(iVar3 + (param_1 & 0xff) * 0x10);
    uVar8 = 0;
    uVar5 = 0;
    pbVar4 = pbVar7;
    do
    {
        bVar2 = *pbVar4;
        uVar5 = uVar5 + 1 & 0xff;
        if (bVar2 != 0)
        {
            pcVar6 = (char *)(param_2 + uVar8);
            if ((&g_city_owner_one_based_view)[(uint32_t)bVar2 * 0x24] == cVar1)
            {
                uVar8 = uVar8 + 1 & 0xff;
                *pcVar6 = bVar2 - 1;
            }
        }
        pbVar4 = pbVar7 + uVar5;
    } while (uVar5 < 8);
    return uVar8;
}

/* 原函数 0x81c128b4 */
uint32_t sango_city_find_neighbor_position(uint32_t param_1, int param_2)
{
    char cVar1;
    uint8_t bVar2;
    int iVar3;
    uint8_t *pbVar4;
    uint32_t uVar5;
    char *pcVar6;
    uint8_t *pbVar7;
    uint32_t uVar8;

    iVar3 = sango_resource_item(0x3b, '\x01', g_resource_package_address);
    cVar1 = (&g_first_city_owner)[(param_1 & 0xff) * 0x24];
    pbVar7 = (uint8_t *)(iVar3 + (param_1 & 0xff) * 0x10);
    uVar8 = 0;
    uVar5 = 0;
    pbVar4 = pbVar7;
    do
    {
        bVar2 = *pbVar4;
        uVar5 = uVar5 + 1 & 0xff;
        if (bVar2 != 0)
        {
            if ((&g_city_owner_one_based_view)[(uint32_t)bVar2 * 0x24] != '\0')
            {
                pcVar6 = (char *)(param_2 + uVar8);
                if ((&g_city_owner_one_based_view)[(uint32_t)bVar2 * 0x24] != cVar1)
                {
                    uVar8 = uVar8 + 1 & 0xff;
                    *pcVar6 = bVar2 - 1;
                }
            }
        }
        pbVar4 = pbVar7 + uVar5;
    } while (uVar5 < 8);
    return uVar8;
}

/* 原函数 0x81c1297c */
uint32_t sango_city_list_enemy_neighbors(uint32_t param_1, int param_2)
{
    uint8_t bVar1;
    int iVar2;
    uint8_t *pbVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;

    uVar7 = 0;
    uVar6 = 0;
    do
    {
        iVar2 = uVar6 * 0x24;
        uVar4 = (uint32_t)(uint8_t)(&g_first_city_owner)[iVar2];
        if (((uVar4 != (param_1 & 0xff) + 1) && (uVar4 != 0)) &&
            (uVar5 = 0, (&g_first_city_character_count)[iVar2] != '\0'))
        {
            do
            {
                bVar1 = (&g_city_character_roster)
                    [uVar5 + (uint8_t)(&g_first_city_character_start)[uVar6 * 0x24]];
                uVar5 = uVar5 + 1 & 0xff;
                if (*(uint8_t *)((uint32_t)bVar1 * 0x10 + g_character_table_address + 1) == uVar4)
                {
                    pbVar3 = (uint8_t *)(param_2 + uVar7);
                    if (bVar1 + 1 != uVar4)
                    {
                        uVar7 = uVar7 + 1 & 0xff;
                        *pbVar3 = bVar1;
                    }
                }
            } while (uVar5 < (uint8_t)(&g_first_city_character_count)[iVar2]);
        }
        uVar6 = uVar6 + 1 & 0xff;
    } while (uVar6 < 0x26);
    return uVar7;
}

/* 原函数 0x81c12a68 */
uint32_t sango_strategy_list_rulers(uint32_t param_1, uint8_t *param_2)
{
    bool bVar1;
    uint8_t *pbVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;

    uVar6 = 0;
    uVar5 = 0;
    do
    {
        uVar4 = (uint32_t)(uint8_t)(&g_first_city_owner)[uVar5 * 0x24];
        if ((uVar4 != 0) && (uVar4 != (param_1 & 0xff) + 1))
        {
            uVar3 = 0;
            if (uVar6 == 0)
            {
                bVar1 = false;
            LAB_81c12b00:
                if (bVar1)
                    goto LAB_81c12ae4;
            }
            else
            {
                pbVar2 = param_2;
                do
                {
                    if ((uint32_t)*pbVar2 == uVar4 - 1)
                    {
                        bVar1 = uVar3 < uVar6;
                        goto LAB_81c12b00;
                    }
                    uVar3 = uVar3 + 1 & 0xff;
                    pbVar2 = param_2 + uVar3;
                } while (uVar3 < uVar6);
            }
            param_2[uVar6] = (&g_first_city_owner)[uVar5 * 0x24] - 1;
            uVar6 = uVar6 + 1 & 0xff;
        }
    LAB_81c12ae4:
        uVar5 = uVar5 + 1 & 0xff;
        if (0x25 < uVar5)
        {
            return uVar6;
        }
    } while (true);
}

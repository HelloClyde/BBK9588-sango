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
uint32_t sango_city_route_distance(uint32_t source_city, uint8_t source_x, uint8_t source_y,
                                   char target_city, uint8_t target_x, uint8_t target_y)
{
    unsigned char abi_storage[21] __attribute__((aligned(8)));
    (*(uint8_t *)(abi_storage + 0)) = target_x;
    (*(uint8_t *)(abi_storage + 4)) = target_y;
#define target_x (*(uint8_t *)(abi_storage + 0))
#define target_y (*(uint8_t *)(abi_storage + 4))

    char distance_y;
    uint8_t route_length;
    uint32_t reachable_count;
    char *city_entry;
    uint32_t compare_index;
    uint32_t next_unique_index;
    uint32_t previous_count;
    char *reachable_cities;
    uint32_t search_index;

    reachable_cities = (char *)(g_scratch_buffer_address + 200);
    reachable_count = sango_city_find_neighbor(source_city & 0xff, (int)reachable_cities);
    if (reachable_count != 0)
    {
        do
        {
            previous_count = reachable_count;
            search_index = 0;
            reachable_count = previous_count;
            if (previous_count != 0)
            {
                do
                {
                    uint32_t appended_count =
                        sango_city_find_neighbor((uint32_t)(uint8_t)reachable_cities[search_index],
                                                 (int)(reachable_cities + reachable_count));
                    search_index = search_index + 1 & 0xff;
                    reachable_count = reachable_count + appended_count & 0xff;
                } while (search_index < previous_count);
            }
            search_index = 0;
            if (reachable_count != 0)
            {
                next_unique_index = 1;
                do
                {
                    compare_index = next_unique_index & 0xff;
                    if (compare_index < reachable_count)
                    {
                        do
                        {
                            if (reachable_cities[search_index] == reachable_cities[compare_index])
                            {
                                reachable_count = reachable_count - 1 & 0xff;
                                reachable_cities[compare_index] = reachable_cities[reachable_count];
                            }
                            else
                            {
                                compare_index = compare_index + 1 & 0xff;
                            }
                        } while (compare_index < reachable_count);
                    }
                    search_index = next_unique_index & 0xff;
                    next_unique_index = search_index + 1;
                } while (search_index < reachable_count);
            }
        } while (reachable_count != previous_count);
        reachable_count = 0;
        if (previous_count != 0)
        {
            city_entry = reachable_cities;
            do
            {
                reachable_count = reachable_count + 1 & 0xff;
                if (*city_entry == target_city)
                {
                    distance_y = target_y - source_y;
                    if (target_y <= source_y)
                    {
                        distance_y = source_y - target_y;
                    }
                    if (source_x < target_x)
                    {
                        route_length = (distance_y + target_x) - source_x;
                    }
                    else
                    {
                        route_length = (distance_y + source_x) - target_x;
                    }
                    return (uint32_t)route_length;
                }
                city_entry = reachable_cities + reachable_count;
            } while (reachable_count < previous_count);
        }
    }
    return 0xff;
}
#undef target_x
#undef target_y

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

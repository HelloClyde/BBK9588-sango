#include "sango_internal.h"

/* 行动消耗、武将宝物列表与城市关系。 */

/* 原函数 0x81c12308 */
uint32_t sango_city_can_pay_command(uint32_t city_id, uint32_t command_id)
{
    int command_costs_address;

    command_costs_address = sango_resource_item(2, '\v', g_resource_package_address);
    return (uint32_t)((uint16_t) * (uint8_t *)(command_costs_address + (command_id & 0xff)) <=
                      (uint16_t)(&g_first_city_money)[(city_id & 0xff) * 0x12]);
}

/* 原函数 0x81c12374 */
void sango_city_pay_command(uint32_t city_id, uint32_t command_id)
{
    int command_costs_address;

    command_costs_address = sango_resource_item(2, '\v', g_resource_package_address);
    (&g_first_city_money)[(city_id & 0xff) * 0x12] =
        (&g_first_city_money)[(city_id & 0xff) * 0x12] -
        (uint16_t) * (uint8_t *)(command_costs_address + (command_id & 0xff));
    return;
}

/* 原函数 0x81c123f0 */
uint32_t sango_city_remove_character(uint32_t city_id, uint8_t character_id)
{
    uint8_t roster_count;
    bool inside_city_roster;
    int city_offset;
    uint32_t roster_position;
    uint32_t roster_end;
    uint32_t city_index;

    city_index = city_id & 0xff;
    if ((city_index < 0x26) && (character_id < 200))
    {
        city_offset = city_index * 0x24;
        roster_position = (uint32_t)(uint8_t)(&g_first_city_character_start)[city_offset];
        roster_count = (&g_first_city_character_count)[city_offset];
        roster_end = roster_position + roster_count;
        for (; inside_city_roster = roster_position < (roster_end & 0xff), inside_city_roster;
             roster_position = roster_position + 1 & 0xff)
        {
            if ((&g_city_character_roster)[roster_position] == character_id)
            {
                if (inside_city_roster)
                {
                    for (; roster_position < 199; roster_position = roster_position + 1 & 0xff)
                    {
                        (&g_city_character_roster)[roster_position] =
                            (&g_city_character_roster_next)[roster_position];
                    }
                    (&g_first_city_character_count)[city_offset] = roster_count - 1;
                    while (city_index = city_index + 1 & 0xff, city_index < 0x26)
                    {
                        (&g_first_city_character_start)[city_index * 0x24] =
                            (&g_first_city_character_start)[city_index * 0x24] + -1;
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
uint32_t sango_city_remove_item(uint32_t city_id, uint8_t item_id)
{
    uint8_t item_count;
    bool inside_city_roster;
    int city_offset;
    uint32_t roster_position;
    uint32_t roster_end;
    uint32_t city_index;

    city_index = city_id & 0xff;
    if ((city_index < 0x26) && (item_id < 0x21))
    {
        city_offset = city_index * 0x24;
        roster_position = (uint32_t)(uint8_t)(&g_first_city_item_start)[city_offset];
        item_count = (&g_first_city_item_count)[city_offset];
        roster_end = roster_position + item_count;
        for (; inside_city_roster = roster_position < (roster_end & 0xff), inside_city_roster;
             roster_position = roster_position + 1 & 0xff)
        {
            if (((&g_city_item_roster)[roster_position] & 0x7f) == item_id)
            {
                if (inside_city_roster)
                {
                    for (; roster_position < 0x20; roster_position = roster_position + 1 & 0xff)
                    {
                        (&g_city_item_roster)[roster_position] =
                            (&g_city_item_roster_next)[roster_position];
                    }
                    (&g_first_city_item_count)[city_offset] = item_count - 1;
                    while (city_index = city_index + 1 & 0xff, city_index < 0x26)
                    {
                        (&g_first_city_item_start)[city_index * 0x24] =
                            (&g_first_city_item_start)[city_index * 0x24] + -1;
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
uint32_t sango_city_find_neighbor(uint32_t city_id, int destination_address)
{
    char owner_id;
    uint8_t neighbor_one_based;
    int neighbor_table_address;
    uint8_t *neighbor_entry;
    uint32_t direction_index;
    char *destination_entry;
    uint8_t *city_neighbors;
    uint32_t neighbor_count;

    neighbor_table_address = sango_resource_item(0x3b, '\x01', g_resource_package_address);
    owner_id = (&g_first_city_owner)[(city_id & 0xff) * 0x24];
    city_neighbors = (uint8_t *)(neighbor_table_address + (city_id & 0xff) * 0x10);
    neighbor_count = 0;
    direction_index = 0;
    neighbor_entry = city_neighbors;
    do
    {
        neighbor_one_based = *neighbor_entry;
        direction_index = direction_index + 1 & 0xff;
        if (neighbor_one_based != 0)
        {
            destination_entry = (char *)(destination_address + neighbor_count);
            if ((&g_city_owner_one_based_view)[(uint32_t)neighbor_one_based * 0x24] == owner_id)
            {
                neighbor_count = neighbor_count + 1 & 0xff;
                *destination_entry = neighbor_one_based - 1;
            }
        }
        neighbor_entry = city_neighbors + direction_index;
    } while (direction_index < 8);
    return neighbor_count;
}

/* 原函数 0x81c128b4 */
uint32_t sango_city_find_neighbor_position(uint32_t city_id, int destination_address)
{
    char owner_id;
    uint8_t neighbor_one_based;
    int neighbor_table_address;
    uint8_t *neighbor_entry;
    uint32_t direction_index;
    char *destination_entry;
    uint8_t *city_neighbors;
    uint32_t neighbor_count;

    neighbor_table_address = sango_resource_item(0x3b, '\x01', g_resource_package_address);
    owner_id = (&g_first_city_owner)[(city_id & 0xff) * 0x24];
    city_neighbors = (uint8_t *)(neighbor_table_address + (city_id & 0xff) * 0x10);
    neighbor_count = 0;
    direction_index = 0;
    neighbor_entry = city_neighbors;
    do
    {
        neighbor_one_based = *neighbor_entry;
        direction_index = direction_index + 1 & 0xff;
        if (neighbor_one_based != 0)
        {
            if ((&g_city_owner_one_based_view)[(uint32_t)neighbor_one_based * 0x24] != '\0')
            {
                destination_entry = (char *)(destination_address + neighbor_count);
                if ((&g_city_owner_one_based_view)[(uint32_t)neighbor_one_based * 0x24] != owner_id)
                {
                    neighbor_count = neighbor_count + 1 & 0xff;
                    *destination_entry = neighbor_one_based - 1;
                }
            }
        }
        neighbor_entry = city_neighbors + direction_index;
    } while (direction_index < 8);
    return neighbor_count;
}

/* 原函数 0x81c1297c */
uint32_t sango_city_list_enemy_neighbors(uint32_t ruler_id, int destination_address)
{
    uint8_t character_id;
    int city_offset;
    uint8_t *destination_entry;
    uint32_t owner_id;
    uint32_t roster_index;
    uint32_t city_index;
    uint32_t enemy_character_count;

    enemy_character_count = 0;
    city_index = 0;
    do
    {
        city_offset = city_index * 0x24;
        owner_id = (uint32_t)(uint8_t)(&g_first_city_owner)[city_offset];
        if (((owner_id != (ruler_id & 0xff) + 1) && (owner_id != 0)) &&
            (roster_index = 0, (&g_first_city_character_count)[city_offset] != '\0'))
        {
            do
            {
                character_id = (&g_city_character_roster)
                    [roster_index + (uint8_t)(&g_first_city_character_start)[city_index * 0x24]];
                roster_index = roster_index + 1 & 0xff;
                if (*(uint8_t *)((uint32_t)character_id * 0x10 + g_character_table_address + 1) ==
                    owner_id)
                {
                    destination_entry = (uint8_t *)(destination_address + enemy_character_count);
                    if (character_id + 1 != owner_id)
                    {
                        enemy_character_count = enemy_character_count + 1 & 0xff;
                        *destination_entry = character_id;
                    }
                }
            } while (roster_index < (uint8_t)(&g_first_city_character_count)[city_offset]);
        }
        city_index = city_index + 1 & 0xff;
    } while (city_index < 0x26);
    return enemy_character_count;
}

/* 原函数 0x81c12a68 */
uint32_t sango_strategy_list_rulers(uint32_t excluded_ruler_id, uint8_t *ruler_ids)
{
    bool already_listed;
    uint8_t *ruler_entry;
    uint32_t scan_index;
    uint32_t city_owner;
    uint32_t city_index;
    uint32_t ruler_count;

    ruler_count = 0;
    city_index = 0;
    do
    {
        city_owner = (uint32_t)(uint8_t)(&g_first_city_owner)[city_index * 0x24];
        if ((city_owner != 0) && (city_owner != (excluded_ruler_id & 0xff) + 1))
        {
            scan_index = 0;
            if (ruler_count == 0)
            {
                already_listed = false;
            check_duplicate_ruler:
                if (already_listed)
                    goto next_city;
            }
            else
            {
                ruler_entry = ruler_ids;
                do
                {
                    if ((uint32_t)*ruler_entry == city_owner - 1)
                    {
                        already_listed = scan_index < ruler_count;
                        goto check_duplicate_ruler;
                    }
                    scan_index = scan_index + 1 & 0xff;
                    ruler_entry = ruler_ids + scan_index;
                } while (scan_index < ruler_count);
            }
            ruler_ids[ruler_count] = (&g_first_city_owner)[city_index * 0x24] - 1;
            ruler_count = ruler_count + 1 & 0xff;
        }
    next_city:
        city_index = city_index + 1 & 0xff;
        if (0x25 < city_index)
        {
            return ruler_count;
        }
    } while (true);
}

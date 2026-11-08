#include "sango_internal.h"

/* 电脑城市的内政、外交和军事决策。 */

/* 原函数 0x81c19df8 */
void sango_strategy_run_city_ai(void)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define domestic_thresholds (*(uint8_t(*)[8])(abi_storage + 0))
#define diplomacy_thresholds (*(uint8_t(*)[8])(abi_storage + 8))

    char previous_prevention;
    uint8_t ruler_profile;
    int city_offset;
    uint32_t random_roll;
    uint8_t city_argument;
    uint32_t action_choice;
    uint32_t city_id;

    sango_resource_read_text(2, 0xc, domestic_thresholds);
    sango_resource_read_text(2, 0xd, diplomacy_thresholds);
    city_id = 0;
    do
    {
        city_offset = city_id * 0x24;
        uint32_t owner_id = (uint32_t)(uint8_t)(&g_first_city_owner)[city_offset];
        (&g_first_city_status)[city_offset] = 0;
        if ((owner_id != 0) && (owner_id != g_player_character + 1))
        {
            previous_prevention = (&g_first_city_disaster_prevention)[city_offset];
            (&g_first_city_disaster_prevention)[city_offset] = previous_prevention + 1U;
            if (100 < (uint8_t)(previous_prevention + 1U))
            {
                (&g_first_city_disaster_prevention)[city_offset] = 100;
            }
            if ((uint16_t)(&g_first_city_food)[city_id * 0x12] < 100)
            {
                (&g_first_city_food)[city_id * 0x12] = 500;
            }
            if (10000 < (uint16_t)(&g_first_city_money)[city_id * 0x12])
            {
                (&g_first_city_money)[city_id * 0x12] =
                    (uint16_t)(&g_first_city_money)[city_id * 0x12] >> 1;
            }
            random_roll = bbk_rand();
            ruler_profile = *(uint8_t *)(owner_id * 0x10 + g_character_table_address + -10);
            action_choice = (int)random_roll % 100 & 0xff;
            city_argument = (uint8_t)city_id;
            if (action_choice < domestic_thresholds[ruler_profile])
            {
                sango_strategy_ai_domestic_actions(city_argument);
                sango_strategy_ai_city_events(city_argument);
            }
            else if (action_choice < diplomacy_thresholds[ruler_profile])
            {
                sango_strategy_ai_diplomacy_actions(city_argument);
            }
            else
            {
                sango_strategy_ai_military_actions(city_argument);
            }
        }
        city_id = city_id + 1 & 0xff;
    } while (city_id < 0x26);
    return;
}
#undef domestic_thresholds
#undef diplomacy_thresholds

/* 原函数 0x81c19f8c */
void sango_strategy_ai_domestic_actions(uint8_t city_id)
{
    unsigned char abi_storage[44] __attribute__((aligned(8)));
#define idle_ids_address (*(int *)(abi_storage + 16))
#define commerce_limit (*(uint32_t *)(abi_storage + 20))
#define agriculture_limit (*(uint32_t *)(abi_storage + 24))
#define order_kind (*(uint8_t *)(abi_storage + 0))
#define order_character (*(uint8_t *)(abi_storage + 1))
#define order_city (*(uint8_t *)(abi_storage + 2))
#define order_target (*(uint8_t *)(abi_storage + 3))
#define order_months (*(uint8_t *)(abi_storage + 11))

    uint8_t previous_loyalty;
    uint16_t previous_development;
    uint32_t city_index;
    uint32_t idle_count;
    uint32_t previous_population;
    uint8_t *character_entry;
    uint32_t character_index;
    uint32_t *population_limit;
    uint8_t *loyalty;
    uint16_t *commerce;
    uint16_t *agriculture;

    city_index = (uint32_t)city_id;
    idle_ids_address = g_scratch_buffer_address;
    agriculture_limit = (uint32_t)(uint16_t)(&g_first_city_agriculture_limit)[city_index * 0x12];
    commerce_limit = (uint32_t)(uint16_t)(&g_first_city_commerce_limit)[city_index * 0x12];
    idle_count = sango_city_list_idle_characters(city_index, g_scratch_buffer_address);
    agriculture = &g_first_city_agriculture + city_index * 0x12;
    commerce = &g_first_city_commerce + city_index * 0x12;
    loyalty = &g_first_city_loyalty + city_index * 0x24;
    population_limit = &g_first_city_population_limit + city_index * 9;
    character_index = 0;
    if (idle_count != 0)
    {
        do
        {
            uint32_t command_roll = bbk_rand();
            switch ((int)command_roll % 5 & 0xff)
            {
            case 0:
                previous_development = *agriculture;
                *agriculture = previous_development + 200;
                if (agriculture_limit < (uint16_t)(previous_development + 200))
                {
                    *agriculture = (uint16_t)agriculture_limit;
                }
                order_kind = 1;
                break;
            case 1:
                previous_development = *commerce;
                *commerce = previous_development + 200;
                if (commerce_limit < (uint16_t)(previous_development + 200))
                {
                    *commerce = (uint16_t)commerce_limit;
                }
                order_kind = 2;
                break;
            case 2:
                order_kind = 3;
                break;
            case 3:
                previous_loyalty = *loyalty;
                *loyalty = previous_loyalty + 4;
                if (100 < (uint8_t)(previous_loyalty + 4))
                {
                    *loyalty = 100;
                }
                previous_population = *population_limit;
                *population_limit = previous_population + 100;
                if ((uint32_t)(&g_first_city_population)[city_index * 9] <
                    previous_population + 100)
                {
                    *population_limit = (&g_first_city_population)[city_index * 9];
                }
                order_kind = 5;
                break;
            case 4:
                character_index = character_index + 1 & 0xff;
                continue;
            }
            character_entry = (uint8_t *)(idle_ids_address + character_index);
            order_character = *character_entry;
            order_months = 0;
            order_city = city_id;
            order_target = city_id;
            sango_strategy_enqueue_order(&order_kind);
            sango_city_remove_character(city_index, *character_entry);
            character_index = character_index + 1 & 0xff;
        } while (character_index < idle_count);
    }
    return;
}
#undef idle_ids_address
#undef commerce_limit
#undef agriculture_limit
#undef order_kind
#undef order_character
#undef order_city
#undef order_target
#undef order_months

/* 原函数 0x81c1a188 */
void sango_strategy_ai_diplomacy_actions(uint8_t city_id)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define order_kind (*(uint8_t *)(abi_storage + 0))
#define order_character (*(uint8_t *)(abi_storage + 1))
#define order_city (*(uint8_t *)(abi_storage + 2))
#define order_target (*(uint8_t *)(abi_storage + 3))
#define order_months (*(uint8_t *)(abi_storage + 11))

    uint32_t city_index;
    int idle_ids_address;
    uint32_t idle_count;
    uint32_t random_choice;
    uint32_t candidate_count;
    uint8_t removed_character;
    uint8_t *character_entry;
    uint8_t *candidate_ids;
    uint32_t character_index;

    idle_ids_address = g_scratch_buffer_address;
    city_index = (uint32_t)city_id;
    idle_count = sango_city_list_idle_characters(city_index, g_scratch_buffer_address);
    candidate_ids = (uint8_t *)(idle_ids_address + 200);
    character_index = 0;
    if (idle_count != 0)
    {
        do
        {
            random_choice = bbk_rand();
            uint32_t rounded_random = random_choice + 7;
            if (-1 < (int)random_choice)
            {
                rounded_random = random_choice;
            }
            random_choice = random_choice + ((int)rounded_random >> 3) * -8 & 0xff;
            candidate_count = sango_city_list_captives(city_index, (int)candidate_ids);
            if (candidate_count != 0)
            {
                random_choice = 0;
            }
            bool should_enqueue = false;
            switch (random_choice)
            {
            case 0:
                if (candidate_count != 0)
                {
                    random_choice = bbk_rand();
                    if (candidate_count == 0)
                    {
                        sango_legacy_trap(7);
                    }
                    character_entry = (uint8_t *)((uint32_t)candidate_ids[(int)random_choice %
                                                                              (int)candidate_count &
                                                                          0xff] *
                                                      0x10 +
                                                  g_character_table_address);
                    if ((uint32_t)*character_entry == g_player_character + 1)
                    {
                        sango_city_remove_character(
                            city_index,
                            candidate_ids[(int)random_choice % (int)candidate_count & 0xff]);
                        order_kind = 6;
                        should_enqueue = true;
                        break;
                    }
                    character_entry[1] = (&g_first_city_owner)[city_index * 0x24];
                }
                break;
            case 1:
                if (candidate_count != 0)
                {
                    random_choice = bbk_rand();
                    if (candidate_count == 0)
                    {
                        sango_legacy_trap(7);
                    }
                    removed_character =
                        candidate_ids[(int)random_choice % (int)candidate_count & 0xff];
                    sango_city_remove_character(city_index, removed_character);
                    break;
                }
                break;
            case 2:
            case 7:
                break;
            case 3:
                candidate_count = sango_city_list_enemy_neighbors(city_index, (int)candidate_ids);
                if (candidate_count != 0)
                {
                    random_choice = bbk_rand();
                    if (candidate_count == 0)
                    {
                        sango_legacy_trap(7);
                    }
                    order_target = candidate_ids[(int)random_choice % (int)candidate_count & 0xff];
                    order_kind = 0xf;
                    should_enqueue = true;
                    break;
                }
                break;
            case 4:
                candidate_count = sango_city_list_enemy_neighbors(city_index, (int)candidate_ids);
                if (candidate_count != 0)
                {
                    random_choice = bbk_rand();
                    if (candidate_count == 0)
                    {
                        sango_legacy_trap(7);
                    }
                    order_target = candidate_ids[(int)random_choice % (int)candidate_count & 0xff];
                    order_kind = 0x10;
                    should_enqueue = true;
                    break;
                }
                break;
            case 5:
                candidate_count = sango_city_list_enemy_rulers(city_index, (int)candidate_ids);
                if (candidate_count != 0)
                {
                    random_choice = bbk_rand();
                    if (candidate_count == 0)
                    {
                        sango_legacy_trap(7);
                    }
                    order_target = candidate_ids[(int)random_choice % (int)candidate_count & 0xff];
                    order_kind = 0x11;
                    should_enqueue = true;
                    break;
                }
                break;
            case 6:
                candidate_count = sango_strategy_list_rulers(city_index, candidate_ids);
                if (candidate_count != 0)
                {
                    random_choice = bbk_rand();
                    if (candidate_count == 0)
                    {
                        sango_legacy_trap(7);
                    }
                    order_target = candidate_ids[(int)random_choice % (int)candidate_count & 0xff];
                    order_kind = 0x13;
                    should_enqueue = true;
                    break;
                }
                break;
            default:
                should_enqueue = true;
                break;
            }
            if (should_enqueue)
            {
                character_entry = (uint8_t *)(idle_ids_address + character_index);
                order_character = *character_entry;
                order_months = 0;
                order_city = city_id;
                sango_strategy_enqueue_order(&order_kind);
                removed_character = *character_entry;
                sango_city_remove_character(city_index, removed_character);
            }
            character_index = character_index + 1 & 0xff;
        } while (character_index < idle_count);
    }
    return;
}
#undef order_kind
#undef order_character
#undef order_city
#undef order_target
#undef order_months

/* 原函数 0x81c1a480 */
void sango_strategy_ai_city_events(uint8_t city_id)
{
    unsigned char abi_storage[36] __attribute__((aligned(8)));
#define order_kind (*(uint8_t *)(abi_storage + 0))
#define order_character (*(uint8_t *)(abi_storage + 1))
#define order_city (*(uint8_t *)(abi_storage + 2))
#define order_target (*(uint8_t *)(abi_storage + 3))
#define order_months (*(uint8_t *)(abi_storage + 11))
#define target_index (*(uint32_t *)(abi_storage + 16))

    char previous_prevention;
    uint32_t city_index;
    int idle_ids_address;
    int city_offset;
    uint32_t idle_count;
    uint32_t random_or_candidate_count;
    uint8_t *city_entry;
    uint32_t neighbor_count_or_roll;
    uint32_t candidate_index;
    uint32_t character_index;
    uint8_t *candidate_ids;

    idle_ids_address = g_scratch_buffer_address;
    city_index = (uint32_t)city_id;
    city_offset = city_index * 0x24;
    idle_count = sango_city_list_idle_characters(city_index, g_scratch_buffer_address);
    candidate_ids = (uint8_t *)(idle_ids_address + 200);
    character_index = 0;
    if (idle_count != 0)
    {
        do
        {
            random_or_candidate_count = bbk_rand();
            switch ((int)random_or_candidate_count % 7 & 0xff)
            {
            case 0:
                previous_prevention = (&g_first_city_disaster_prevention)[city_offset];
                (&g_first_city_status)[city_offset] = 0;
                (&g_first_city_disaster_prevention)[city_offset] = previous_prevention + 4U;
                if (100 < (uint8_t)(previous_prevention + 4U))
                {
                    (&g_first_city_disaster_prevention)[city_offset] = 100;
                }
                order_kind = 4;
            default:
            enqueue_order:
                order_character = *(uint8_t *)(idle_ids_address + character_index);
                order_months = 0;
                order_city = city_id;
                sango_strategy_enqueue_order(&order_kind);
                sango_city_remove_character(city_index,
                                            *(uint8_t *)(idle_ids_address + character_index));
            case 1:
            case 2:
            case 3:
            case 4:
            case 6:
                break;
            case 5:
                if ((2 < character_index) &&
                    (random_or_candidate_count = sango_faction_list_cities(
                         (uint8_t)(&g_first_city_owner)[city_offset] - 1 & 0xff,
                         (int)candidate_ids),
                     1 < random_or_candidate_count))
                {
                    target_index = 0;
                    candidate_index = 0;
                    city_entry = candidate_ids;
                    if (random_or_candidate_count != 0)
                    {
                        do
                        {
                            neighbor_count_or_roll = sango_city_find_neighbor_position(
                                (uint32_t)*city_entry, idle_ids_address + 0xee);
                            if ((neighbor_count_or_roll != 0) &&
                                (neighbor_count_or_roll = bbk_rand(),
                                 target_index = candidate_index,
                                 ((int)neighbor_count_or_roll % 2 & 0xffU) != 0))
                                break;
                            candidate_index = candidate_index + 1 & 0xff;
                            city_entry = candidate_ids + candidate_index;
                        } while (candidate_index < random_or_candidate_count);
                    }
                    order_target = candidate_ids[target_index];
                    order_kind = 0xe;
                    goto enqueue_order;
                }
            }
            character_index = character_index + 1 & 0xff;
        } while (character_index < idle_count);
    }
    return;
}
#undef order_kind
#undef order_character
#undef order_city
#undef order_target
#undef order_months
#undef target_index

/* 原函数 0x81c1a6a4 */
void sango_strategy_ai_military_actions(uint8_t city_id)
{
    unsigned char abi_storage[44] __attribute__((aligned(8)));
#define order_kind (*(uint8_t *)(abi_storage + 16))
#define order_character (*(uint8_t *)(abi_storage + 17))
#define order_city (*(uint8_t *)(abi_storage + 18))
#define order_target (*(uint8_t *)(abi_storage + 19))
#define order_value0 (*(uint16_t *)(abi_storage + 20))
#define army_food (*(uint16_t *)(abi_storage + 22))
#define order_months (*(uint8_t *)(abi_storage + 27))
#define army_character_ids (*(char(*)[16])(abi_storage + 0))

    uint8_t swap_character;
    uint32_t city_index;
    int idle_ids_address;
    uint32_t idle_count;
    uint32_t character_index;
    uint32_t candidate_count;
    uint32_t army_limit;
    uint8_t leading_character;
    char *army_slot;
    int character_address;
    uint32_t sort_index;
    uint8_t *character_entry;
    uint8_t *candidate_ids;
    uint32_t compare_index;

    idle_ids_address = g_scratch_buffer_address;
    city_index = (uint32_t)city_id;
    idle_count = sango_city_list_idle_characters(city_index, g_scratch_buffer_address);
    candidate_ids = (uint8_t *)(idle_ids_address + 200);
    if (idle_count != 0)
    {
        uint32_t training_roll = bbk_rand();
        if (idle_count == 0)
        {
            sango_legacy_trap(7);
        }
        character_address =
            g_character_table_address +
            (uint32_t) * (uint8_t *)(idle_ids_address + (int)training_roll % (int)idle_count) *
                0x10;
        uint8_t promoted_level;
        if (((uint32_t)g_current_month % 3 == 0) &&
            (promoted_level = *(char *)(character_address + 2) + 1,
             *(uint8_t *)(character_address + 2) = promoted_level, 0x14 < promoted_level))
        {
            *(uint8_t *)(character_address + 2) = 0x14;
        }
        character_index = 0;
        if (idle_count != 0)
        {
            do
            {
                uint32_t command_roll = bbk_rand();
                switch ((int)command_roll % 9 & 0xff)
                {
                case 0:
                    order_kind = 0x17;
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    character_address =
                        g_character_table_address +
                        (uint32_t) * (uint8_t *)(idle_ids_address + character_index) * 0x10;
                    *(uint16_t *)(character_address + 10) =
                        ((uint16_t) * (uint8_t *)(character_address + 2) * 10 +
                         (uint16_t) * (uint8_t *)(character_address + 3) +
                         (uint16_t) * (uint8_t *)(character_address + 4)) *
                        10;
                    order_kind = 0x18;
                    order_value0 = 0;
                    break;
                case 6:
                    order_kind = 0x1a;
                    break;
                case 7:
                    if (character_index == 0)
                    {
                        candidate_count =
                            sango_city_find_neighbor_position(city_index, (int)candidate_ids);
                        if (candidate_count == 0)
                            break;
                        uint32_t attack_roll = bbk_rand();
                        if (candidate_count << 1 == 0)
                        {
                            sango_legacy_trap(7);
                        }
                        if (((int)attack_roll % (int)(candidate_count << 1) & 0xffU) <
                            candidate_count)
                        {
                            uint32_t target_city =
                                sango_city_find_weakest_target(candidate_count, (int)candidate_ids);
                            order_target = (uint8_t)target_city;
                            candidate_count =
                                sango_city_list_idle_characters(city_index, (int)candidate_ids);
                            if (candidate_count == 0)
                                break;
                            army_limit = candidate_count - 1;
                            character_address = g_character_table_address;
                            if ((int)army_limit < 1)
                            {
                                leading_character = *candidate_ids;
                            }
                            else
                            {
                                sort_index = 0;
                                do
                                {
                                    compare_index = sort_index + 1 & 0xff;
                                    if (compare_index < candidate_count)
                                    {
                                        do
                                        {
                                            leading_character = candidate_ids[sort_index];
                                            swap_character = candidate_ids[compare_index];
                                            if (*(uint16_t *)((uint32_t)leading_character * 0x10 +
                                                              character_address + 10) <
                                                *(uint16_t *)((uint32_t)swap_character * 0x10 +
                                                              character_address + 10))
                                            {
                                                candidate_ids[compare_index] = leading_character;
                                                candidate_ids[sort_index] = swap_character;
                                                character_address = g_character_table_address;
                                            }
                                            if (*(short *)((uint32_t)candidate_ids[idle_count - 1] *
                                                               0x10 +
                                                           character_address + 10) == 0)
                                            {
                                                candidate_count = army_limit & 0xff;
                                                army_limit = candidate_count - 1;
                                            }
                                            compare_index = compare_index + 1 & 0xff;
                                        } while (compare_index < candidate_count);
                                    }
                                    sort_index = sort_index + 1 & 0xff;
                                } while ((int)sort_index < (int)army_limit);
                                leading_character = *candidate_ids;
                            }
                            if ((999 < *(uint16_t *)((uint32_t)leading_character * 0x10 +
                                                     character_address + 10)) &&
                                (3 < candidate_count))
                            {
                                army_limit = army_limit & 0xff;
                                order_kind = 0x1b;
                                sango_memory_fill(army_character_ids, 0, 10);
                                if (10 < army_limit)
                                {
                                    army_limit = 10;
                                }
                                uint32_t army_index = 0;
                                if (army_limit != 0)
                                {
                                    do
                                    {
                                        character_entry = candidate_ids + army_index;
                                        sango_city_remove_character(city_index, *character_entry);
                                        army_slot = army_character_ids + army_index;
                                        army_index = army_index + 1 & 0xff;
                                        *army_slot = *character_entry + 1;
                                    } while (army_index < army_limit);
                                }
                                army_food = (&g_first_city_food)[city_index * 0x12];
                                order_months = 0;
                                order_city = city_id;
                                sango_strategy_queue_army(&order_kind, army_character_ids);
                                return;
                            }
                        }
                    }
                    break;
                case 8:
                    break;
                default:
                    order_character = *(uint8_t *)(idle_ids_address + character_index);
                    order_months = 0;
                    order_city = city_id;
                    sango_strategy_enqueue_order(&order_kind);
                    sango_city_remove_character(city_index,
                                                *(uint8_t *)(idle_ids_address + character_index));
                    break;
                }
                character_index = character_index + 1 & 0xff;
            } while (character_index < idle_count);
        }
    }
    return;
}
#undef order_kind
#undef order_character
#undef order_city
#undef order_target
#undef order_value0
#undef army_food
#undef order_months
#undef army_character_ids

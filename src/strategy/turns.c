#include "sango_internal.h"

/* 战略月份推进、城池汇总和剧本初始化。 */

/* 原函数 0x81c1aab4 */
/* 每月先处理玩家指令和系统菜单，再执行电脑、队列和城市事件。 */
uint32_t sango_strategy_run_months(void)
{
    uint32_t end_condition;
    int system_action;

    while (true)
    {
        end_condition = sango_strategy_player_has_no_cities();
        if (end_condition != 0)
        {
            sango_ui_show_strategy_text(0x59);
            return 1;
        }
        end_condition = sango_strategy_player_is_only_ruler();
        if (end_condition != 0)
            break;
        sango_strategy_refresh_city_governors();
        while (true)
        {
            do
            {
                sango_strategy_run_player_commands();
                system_action = sango_ui_show_system_menu();
            } while (system_action == 0);
            if (system_action == 1)
                break;
            if (system_action == 2)
            {
                return 2;
            }
        }
        sango_ui_show_ai_progress();
        sango_strategy_run_city_ai();
        sango_strategy_advance_orders();
        g_current_month = g_current_month + 1;
        if (0xc < g_current_month)
        {
            g_current_month = 1;
            g_current_year_view2 = g_current_year_view2 + 1;
            sango_strategy_spawn_items_for_year();
            sango_strategy_update_character_ages_and_debut();
        }
        sango_strategy_apply_monthly_economy();
        sango_strategy_apply_disaster_losses();
        sango_strategy_apply_city_disasters();
    }
    sango_ui_show_strategy_text(0x5a);
    return 0;
}

/* 原函数 0x81c1abd4 */
uint32_t sango_strategy_player_is_only_ruler(void)
{
    uint32_t opponent_count;

    opponent_count =
        sango_strategy_list_rulers((uint32_t)g_player_character, g_scratch_buffer_address);
    return (uint32_t)(opponent_count == 0);
}

/* 原函数 0x81c1ac04 */
uint32_t sango_strategy_player_has_no_cities(void)
{
    uint32_t city_count;

    city_count = sango_faction_list_cities((uint32_t)g_player_character, g_scratch_buffer_address);
    return (uint32_t)(city_count == 0);
}

/* 原函数 0x81c1ac34 */
/* 君主在城时由君主治理，否则选择本势力智力最高的武将。 */
void sango_strategy_refresh_city_governors(void)
{
    int city_offset;
    uint8_t *roster_entry;
    int character_address;
    uint32_t character_owner_id;
    uint32_t roster_index;
    uint32_t ruler_owner_id;
    uint32_t city_id;
    uint32_t best_governor_owner_id;
    uint32_t governor_owner_id;
    int scaled_city_id;

    city_id = 0;
    scaled_city_id = 0;
    do
    {
        city_offset = (scaled_city_id + city_id) * 4;
        ruler_owner_id = (uint32_t)(uint8_t)(&g_first_city_owner)[city_offset];
        best_governor_owner_id = 0;
        if (ruler_owner_id == 0)
        {
            (&g_first_city_governor)[city_offset] = 0;
        }
        else
        {
            roster_index = 0;
            governor_owner_id = best_governor_owner_id;
            if ((uint8_t)(&g_first_city_character_count)[city_offset] != 0)
            {
                roster_entry = &g_city_character_roster +
                               (uint8_t)(&g_first_city_character_start)[city_offset];
                do
                {
                    character_address = (uint32_t)*roster_entry * 0x10 + g_character_table_address;
                    character_owner_id = *roster_entry + 1;
                    if (*(uint8_t *)(character_address + 1) == ruler_owner_id)
                    {
                        governor_owner_id = ruler_owner_id;
                        if (ruler_owner_id == character_owner_id)
                            break;
                        if ((best_governor_owner_id == 0) ||
                            (*(uint8_t *)(best_governor_owner_id * 0x10 +
                                          g_character_table_address + -0xc) <
                             *(uint8_t *)(character_address + 4)))
                        {
                            best_governor_owner_id = character_owner_id & 0xff;
                        }
                    }
                    roster_index = roster_index + 1 & 0xff;
                    roster_entry = &g_city_character_roster +
                                   (uint8_t)(&g_first_city_character_start)[city_offset] +
                                   roster_index;
                    governor_owner_id = best_governor_owner_id;
                } while (roster_index < (uint8_t)(&g_first_city_character_count)[city_offset]);
            }
            (&g_first_city_governor)[(scaled_city_id + city_id) * 4] = (char)governor_owner_id;
        }
        city_id = city_id + 1 & 0xff;
        scaled_city_id = city_id << 3;
        if (0x25 < city_id)
        {
            return;
        }
    } while (true);
}

/* 原函数 0x81c1ad30 */
uint32_t sango_scenario_collect_rulers(uint8_t *ruler_ids)
{
    uint8_t owner_id;
    bool already_listed;
    uint8_t *ruler_entry;
    uint32_t ruler_index;
    uint32_t ruler_count;
    uint32_t city_id;

    ruler_count = 0;
    city_id = 0;
    do
    {
        owner_id = (&g_first_city_owner)[city_id * 0x24];
        if (owner_id != 0)
        {
            ruler_index = 0;
            if (ruler_count == 0)
            {
                already_listed = false;
            check_duplicate:
                if (already_listed)
                    goto next_city;
            }
            else
            {
                ruler_entry = ruler_ids;
                do
                {
                    if ((uint32_t)*ruler_entry == owner_id - 1)
                    {
                        already_listed = ruler_index < ruler_count;
                        goto check_duplicate;
                    }
                    ruler_index = ruler_index + 1 & 0xff;
                    ruler_entry = ruler_ids + ruler_index;
                } while (ruler_index < ruler_count);
            }
            ruler_ids[ruler_count] = owner_id - 1;
            ruler_count = ruler_count + 1 & 0xff;
        }
    next_city:
        city_id = city_id + 1 & 0xff;
        if (0x25 < city_id)
        {
            return ruler_count;
        }
    } while (true);
}

/* 原函数 0x81c1add4 */
/* 将每个剧本的31字节城市及15字节武将源记录展开到原运行时布局。 */
void sango_scenario_initialize(char scenario_id)
{
    uint8_t high_byte;
    uint8_t *source_record;
    int assembled_value_or_character_address;
    void *roster_data;
    uint32_t next_city_id;
    uint32_t next_record_id;
    int record_offset;
    uint32_t record_id;
    uint8_t *item_count_byte;
    uint8_t *source_cursor;

    source_record = (uint8_t *)sango_resource_item(0x39, scenario_id, g_resource_package_address);
    record_id = 0;
    source_cursor = source_record;
    do
    {
        record_offset = record_id * 0x24;
        (&g_first_city_status)[record_offset] = *source_cursor;
        (&g_first_city_owner)[record_offset] = source_cursor[1];
        (&g_first_city_governor)[record_offset] = source_cursor[2];
        high_byte = source_cursor[4];
        (&g_first_city_agriculture_limit)[record_id * 0x12] = (uint16_t)high_byte * 0x100;
        (&g_first_city_agriculture_limit)[record_id * 0x12] =
            (uint16_t)high_byte * 0x100 + (uint16_t)(uint8_t)source_cursor[3];
        high_byte = source_cursor[6];
        next_record_id = record_id + 1 & 0xff;
        (&g_first_city_agriculture)[record_id * 0x12] = (uint16_t)high_byte * 0x100;
        (&g_first_city_agriculture)[record_id * 0x12] =
            (uint16_t)high_byte * 0x100 + (uint16_t)(uint8_t)source_cursor[5];
        high_byte = source_cursor[8];
        (&g_first_city_commerce_limit)[record_id * 0x12] = (uint16_t)high_byte * 0x100;
        (&g_first_city_commerce_limit)[record_id * 0x12] =
            (uint16_t)high_byte * 0x100 + (uint16_t)(uint8_t)source_cursor[7];
        high_byte = source_cursor[10];
        (&g_first_city_commerce)[record_id * 0x12] = (uint16_t)high_byte * 0x100;
        (&g_first_city_commerce)[record_id * 0x12] =
            (uint16_t)high_byte * 0x100 + (uint16_t)(uint8_t)source_cursor[9];
        (&g_first_city_loyalty)[record_offset] = source_cursor[0xb];
        (&g_first_city_disaster_prevention)[record_offset] = source_cursor[0xc];
        high_byte = source_cursor[0x10];
        (&g_first_city_population)[record_id * 9] = (uint32_t)high_byte * 0x100;
        assembled_value_or_character_address =
            ((uint32_t)high_byte * 0x100 + (uint32_t)(uint8_t)source_cursor[0xf]) * 0x100;
        (&g_first_city_population)[record_id * 9] = assembled_value_or_character_address;
        assembled_value_or_character_address =
            (assembled_value_or_character_address + (uint32_t)(uint8_t)source_cursor[0xe]) * 0x100;
        (&g_first_city_population)[record_id * 9] = assembled_value_or_character_address;
        (&g_first_city_population)[record_id * 9] =
            assembled_value_or_character_address + (uint32_t)(uint8_t)source_cursor[0xd];
        high_byte = source_cursor[0x14];
        (&g_first_city_population_limit)[record_id * 9] = (uint32_t)high_byte * 0x100;
        assembled_value_or_character_address =
            ((uint32_t)high_byte * 0x100 + (uint32_t)(uint8_t)source_cursor[0x13]) * 0x100;
        (&g_first_city_population_limit)[record_id * 9] = assembled_value_or_character_address;
        assembled_value_or_character_address =
            (assembled_value_or_character_address + (uint32_t)(uint8_t)source_cursor[0x12]) * 0x100;
        (&g_first_city_population_limit)[record_id * 9] = assembled_value_or_character_address;
        (&g_first_city_population_limit)[record_id * 9] =
            assembled_value_or_character_address + (uint32_t)(uint8_t)source_cursor[0x11];
        high_byte = source_cursor[0x16];
        (&g_first_city_money)[record_id * 0x12] = (uint16_t)high_byte * 0x100;
        (&g_first_city_money)[record_id * 0x12] =
            (uint16_t)high_byte * 0x100 + (uint16_t)(uint8_t)source_cursor[0x15];
        high_byte = source_cursor[0x18];
        (&g_first_city_food)[record_id * 0x12] = (uint16_t)high_byte * 0x100;
        (&g_first_city_food)[record_id * 0x12] =
            (uint16_t)high_byte * 0x100 + (uint16_t)(uint8_t)source_cursor[0x17];
        high_byte = source_cursor[0x1a];
        (&g_first_city_reserve_troops)[record_id * 0x12] = (uint16_t)high_byte * 0x100;
        (&g_first_city_reserve_troops)[record_id * 0x12] =
            (uint16_t)high_byte * 0x100 + (uint16_t)(uint8_t)source_cursor[0x19];
        (&g_first_city_character_start)[record_offset] = source_cursor[0x1b];
        (&g_first_city_character_count)[record_offset] = source_cursor[0x1c];
        item_count_byte = source_cursor + 0x1e;
        (&g_first_city_item_start)[record_offset] = source_cursor[0x1d];
        source_cursor = source_cursor + 0x1f;
        (&g_first_city_item_count)[record_offset] = *item_count_byte;
        record_id = next_record_id;
    } while (next_record_id < 0x26);
    g_current_year_view2 =
        (uint16_t)(uint8_t)source_record[0x49b] * 0x100 + (uint16_t)(uint8_t)source_record[0x49a];
    source_cursor = (uint8_t *)sango_resource_item(0x3d, scenario_id, g_resource_package_address);
    record_id = 0;
    do
    {
        record_offset = record_id * 0x10;
        *(uint8_t *)(record_offset + g_character_table_address) = *source_cursor;
        *(uint8_t *)(record_offset + g_character_table_address + 1) = source_cursor[1];
        *(uint8_t *)(record_offset + g_character_table_address + 2) = source_cursor[2];
        *(uint8_t *)(record_offset + g_character_table_address + 3) = source_cursor[3];
        *(uint8_t *)(record_offset + g_character_table_address + 4) = source_cursor[4];
        *(uint8_t *)(record_offset + g_character_table_address + 5) = source_cursor[5];
        *(uint8_t *)(record_offset + g_character_table_address + 6) = source_cursor[6];
        *(uint8_t *)(record_offset + g_character_table_address + 7) = source_cursor[7];
        *(uint8_t *)(record_offset + g_character_table_address + 8) = source_cursor[8];
        *(uint8_t *)(record_offset + g_character_table_address + 9) = source_cursor[9];
        high_byte = source_cursor[0xb];
        assembled_value_or_character_address = record_offset + g_character_table_address;
        *(uint16_t *)(assembled_value_or_character_address + 10) = (uint16_t)high_byte * 0x100;
        record_id = record_id + 1 & 0xff;
        *(uint16_t *)(assembled_value_or_character_address + 10) =
            (uint16_t)high_byte * 0x100 + (uint16_t)(uint8_t)source_cursor[10];
        *(uint8_t *)(assembled_value_or_character_address + 0xc) = source_cursor[0xc];
        source_record = source_cursor + 0xe;
        *(uint8_t *)(record_offset + g_character_table_address + 0xd) = source_cursor[0xd];
        source_cursor = source_cursor + 0xf;
        *(uint8_t *)(record_offset + g_character_table_address + 0xe) = *source_record;
    } while (record_id < 200);
    roster_data = (void *)sango_resource_item(0x41, scenario_id, g_resource_package_address);
    bbk_memcpy(&g_city_character_roster, roster_data, 200);
    roster_data = (void *)sango_resource_item(0x44, scenario_id, g_resource_package_address);
    bbk_memcpy(&g_city_item_roster, roster_data, 0x21);
    sango_memory_fill(g_army_slot_used_address, 0, 0x1e);
    sango_memory_fill(g_order_queue_address, 0xff, 0x4b0);
    next_record_id = 1;
    record_id = 0;
    g_scenario_id = scenario_id;
    do
    {
        next_city_id = next_record_id & 0xff;
        (&g_first_city_status)[record_id * 0x24] = 0;
        next_record_id = next_city_id + 1;
        record_id = next_city_id;
    } while (next_city_id < 0x26);
    record_id = 0;
    do
    {
        assembled_value_or_character_address = record_id * 0x10;
        *(uint8_t *)(assembled_value_or_character_address + g_character_table_address + 8) = 100;
        record_id = record_id + 1 & 0xff;
        source_cursor =
            (uint8_t *)(assembled_value_or_character_address + g_character_table_address);
        *source_cursor = 0;
        *(uint16_t *)(source_cursor + 10) = 100;
    } while (record_id < 200);
    g_current_month = 1;
    return;
}

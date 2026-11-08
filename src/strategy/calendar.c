#include "sango_internal.h"

/* 城市月度事件与年度武将更新。 */

/* 原函数 0x81c16e00 */
uint32_t sango_strategy_apply_monthly_economy(void)
{
    char previous_city_status;
    uint16_t previous_troops;
    uint8_t *roster_buffer;
    int city_byte_offset;
    int character_table_base;
    int city_word_offset;
    char *captive_record;
    int character_address;
    uint32_t updated_troops;
    uint32_t city_id;
    uint32_t roster_index;
    uint8_t *roster_entry;
    uint32_t total_troops;
    uint32_t roster_count;

    if ((g_current_month == 6) || (g_current_month == 10))
    {
        sango_strategy_collect_agriculture_income();
    }
    if (g_current_month % 3 == 0)
    {
        sango_strategy_collect_commerce_income();
    }
    uint32_t active_character_count =
        (uint32_t)g_legacy_data_81c2b9a2 + (uint32_t)g_legacy_data_81c2b9a3 & 0xff;
    uint32_t character_index = 0;
    if (active_character_count != 0)
    {
        do
        {
            int regenerating_character = character_index * 0x10 + g_character_table_address;
            *(char *)(regenerating_character + 8) = *(char *)(regenerating_character + 8) + '\x04';
            regenerating_character = character_index * 0x10 + g_character_table_address;
            if (100 < *(uint8_t *)(regenerating_character + 8))
            {
                *(uint8_t *)(regenerating_character + 8) = 100;
            }
            character_index = character_index + 1 & 0xff;
        } while (character_index < active_character_count);
    }
    roster_buffer = g_scratch_buffer_address;
    city_id = 0;
    city_word_offset = 0;
    do
    {
        city_word_offset = city_word_offset + city_id;
        city_byte_offset = city_word_offset * 4;
        if ((&g_first_city_owner)[city_byte_offset] != '\0')
        {
            if ((uint32_t)g_current_month % 3 == 0)
            {
                uint32_t random_roll = bbk_rand();
                uint32_t degradation_amount = random_roll + 3;
                if (-1 < (int)random_roll)
                {
                    degradation_amount = random_roll;
                }
                degradation_amount = random_roll + ((int)degradation_amount >> 2) * -4 + 1;
                if ((degradation_amount & 0xff) <
                    (uint32_t)(uint8_t)(&g_first_city_disaster_prevention)[city_byte_offset])
                {
                    (&g_first_city_disaster_prevention)[city_byte_offset] =
                        (&g_first_city_disaster_prevention)[city_byte_offset] -
                        (char)degradation_amount;
                }
            }
            if (30000 < (uint16_t)(&g_first_city_money)[city_word_offset * 2])
            {
                (&g_first_city_money)[city_word_offset * 2] = 30000;
            }
            int previous_population_limit = (&g_first_city_population_limit)[city_word_offset];
            (&g_first_city_population_limit)[city_word_offset] = previous_population_limit + 0x32U;
            if ((uint32_t)(&g_first_city_population)[city_word_offset] <
                previous_population_limit + 0x32U)
            {
                (&g_first_city_population_limit)[city_word_offset] =
                    (&g_first_city_population)[city_word_offset];
            }
            total_troops = (uint32_t)(uint16_t)(&g_first_city_reserve_troops)[city_word_offset * 2];
            roster_count = sango_city_list_idle_characters(city_id, (int)roster_buffer);
            character_table_base = g_character_table_address;
            roster_index = 0;
            if (roster_count != 0)
            {
                do
                {
                    roster_entry = roster_buffer + roster_index;
                    previous_troops =
                        *(uint16_t *)((uint32_t)*roster_entry * 0x10 + character_table_base + 10);
                    updated_troops = (uint32_t)previous_troops;
                    switch ((&g_first_city_status)[roster_count * 0x24])
                    {
                    case 2:
                    case 3:
                        updated_troops = updated_troops - (previous_troops >> 2) & 0xffff;
                        break;
                    case 4:
                        updated_troops = (uint32_t)(previous_troops >> 1);
                    }
                    roster_index = roster_index + 1 & 0xff;
                    *(short *)((uint32_t)*roster_entry * 0x10 + character_table_base + 10) =
                        (short)updated_troops;
                    total_troops = total_troops + updated_troops & 0xffff;
                } while (roster_index < roster_count);
            }
            character_table_base = g_character_table_address;
            if (total_troops / 0x32 <
                (uint32_t)(uint16_t)(&g_first_city_food)[city_word_offset * 2])
            {
                (&g_first_city_food)[city_word_offset * 2] =
                    (&g_first_city_food)[city_word_offset * 2] - (short)(total_troops / 0x32);
            }
            else
            {
                roster_index = 0;
                if (roster_count != 0)
                {
                    do
                    {
                        roster_entry = roster_buffer + roster_index;
                        roster_index = roster_index + 1 & 0xff;
                        character_address = (uint32_t)*roster_entry * 0x10 + character_table_base;
                        *(uint16_t *)(character_address + 10) =
                            *(uint16_t *)(character_address + 10) >> 1;
                    } while (roster_index < roster_count);
                }
                (&g_first_city_food)[city_word_offset * 2] = 0;
                previous_city_status = (&g_first_city_status)[city_byte_offset];
                (&g_first_city_status)[city_byte_offset] = '\x01';
                if ((previous_city_status != '\x01') &&
                    ((uint32_t)(uint8_t)(&g_first_city_owner)[city_byte_offset] ==
                     g_player_character + 1))
                {
                    sango_ui_show_city_event((uint8_t)city_id,
                                             &g_first_city_food + city_word_offset * 2,
                                             roster_index, roster_count);
                }
            }
            roster_count = sango_city_list_captives(city_id, (int)roster_buffer);
            roster_index = 0;
            roster_entry = roster_buffer;
            if (roster_count != 0)
            {
                do
                {
                    captive_record =
                        (char *)((uint32_t)*roster_entry * 0x10 + g_character_table_address);
                    if (*captive_record == (&g_first_city_owner)[city_byte_offset])
                    {
                        captive_record[1] = (&g_first_city_owner)[city_byte_offset];
                    }
                    roster_index = roster_index + 1 & 0xff;
                    roster_entry = roster_buffer + roster_index;
                } while (roster_index < roster_count);
            }
        }
        city_id = city_id + 1 & 0xff;
        city_word_offset = city_id << 3;
    } while (city_id < 0x26);
    return 1;
}

/* 原函数 0x81c171cc */
uint32_t sango_strategy_apply_city_disasters(void)
{
    uint8_t owner_id;
    uint8_t new_status;
    int event_argument;
    uint32_t random_roll;
    uint16_t recovered;
    uint32_t event_condition;
    uint32_t previous_status;
    int city_stride_base;
    uint8_t *city_status;
    uint32_t city_id;

    /* 原表中的地址值只作为状态处理标签比较，不能当作新的函数入口。 */
    enum
    {
        ROLL_NEW_DISASTER = 0x81c172a4,
        RECOVER_WITH_FOOD = 0x81c173b0,
        RECOVER_WITH_PREVENTION = 0x81c173d4,
        RECOVER_WITH_LOYALTY = 0x81c173f0
    };
    city_id = 0;
    city_stride_base = 0;
    do
    {
        event_argument = (city_stride_base + city_id) * 4;
        city_status = &g_first_city_status + event_argument;
        owner_id = (&g_first_city_owner)[event_argument];
        if (owner_id != 0)
        {
            random_roll = bbk_rand();
            previous_status = (uint32_t)*city_status;
            event_condition = (uint32_t)(previous_status < 5);
            random_roll = (int)random_roll % 100 & 0xff;
            if (event_condition != 0)
            {
                switch ((uint32_t)(&g_city_status_dispatch_tags)[previous_status] & 0xfffffffe)
                {
                case ROLL_NEW_DISASTER:
                    city_stride_base = (city_stride_base + city_id) * 4;
                    if ((uint8_t)(&g_first_city_disaster_prevention)[city_stride_base] <
                        random_roll)
                    {
                        random_roll = bbk_rand();
                        event_argument = (int)random_roll >> 0x1f;
                        random_roll = (int)random_roll % 5 & 0xff;
                        new_status = 3;
                        if (random_roll == 1)
                        {
                        apply_new_disaster:
                            *city_status = new_status;
                        notify_player:
                            if ((*city_status != 0) &&
                                ((uint32_t)owner_id == g_player_character + 1))
                            {
                                sango_ui_show_city_event((uint8_t)city_id, event_argument,
                                                         event_condition, previous_status);
                            }
                        }
                        else if (random_roll < 2)
                        {
                            new_status = 2;
                            if (random_roll == 0)
                                goto apply_new_disaster;
                        }
                        else if (random_roll == 2)
                        {
                            random_roll = bbk_rand();
                            event_argument = (int)random_roll >> 0x1f;
                            event_condition = (uint32_t)((uint32_t)(uint8_t)(&g_first_city_loyalty)
                                                             [city_stride_base] <
                                                         ((int)random_roll % 100 & 0xffU));
                            new_status = 4;
                            if (event_condition != 0)
                                goto apply_new_disaster;
                            goto notify_player;
                        }
                    }
                    goto next_city;
                case RECOVER_WITH_FOOD:
                    recovered = (&g_first_city_food)[(city_stride_base + city_id) * 2];
                    break;
                case RECOVER_WITH_PREVENTION:
                    recovered =
                        (uint16_t)(random_roll < (uint8_t)(&g_first_city_disaster_prevention)
                                                     [(city_stride_base + city_id) * 4]);
                    break;
                case RECOVER_WITH_LOYALTY:
                    recovered =
                        (uint16_t)(random_roll <
                                   (uint8_t)(&g_first_city_loyalty)[(city_stride_base + city_id) *
                                                                    4]);
                }
                if (recovered != 0)
                {
                    *city_status = 0;
                }
            }
        }
    next_city:
        city_id = city_id + 1 & 0xff;
        city_stride_base = city_id << 3;
        if (0x25 < city_id)
        {
            return 1;
        }
    } while (true);
}

/* 原函数 0x81c1740c */
uint32_t sango_strategy_apply_disaster_losses(void)
{
    uint16_t uVar1;
    uint32_t uVar2;
    uint8_t *pbVar3;
    uint16_t *puVar4;
    uint32_t *puVar5;
    uint16_t *puVar6;
    uint16_t *puVar7;
    uint16_t *puVar8;
    uint32_t uVar9;

    uVar9 = 0;
    do
    {
        pbVar3 = &g_first_city_loyalty + uVar9 * 0x24;
        puVar6 = &g_first_city_commerce + uVar9 * 0x12;
        puVar7 = &g_first_city_reserve_troops + uVar9 * 0x12;
        puVar4 = &g_first_city_food + uVar9 * 0x12;
        puVar8 = &g_first_city_money + uVar9 * 0x12;
        puVar5 = &g_first_city_population_limit + uVar9 * 9;
        switch ((&g_first_city_status)[uVar9 * 0x24])
        {
        case 0:
            goto switchD_81c17494_caseD_0;
        case 1:
            *puVar6 = *puVar6 - *puVar6 / 0x14;
            *pbVar3 = *pbVar3 - *pbVar3 / 0x14;
            uVar2 = *puVar5;
            *puVar7 = *puVar7 >> 1;
            *puVar5 = uVar2 - (uVar2 >> 2);
            break;
        case 2:
            uVar1 = *puVar4;
            *puVar5 = *puVar5 - (*puVar5 >> 2);
            *puVar4 = uVar1 - uVar1 / 0x14;
            goto LAB_81c1756c;
        case 3:
            uVar1 = *puVar4;
            *puVar5 = *puVar5 - (*puVar5 >> 2);
            *puVar4 = uVar1 - uVar1 / 0x14;
            *puVar6 = *puVar6 - *puVar6 / 10;
            *puVar8 = *puVar8 - *puVar8 / 10;
        LAB_81c1756c:
            *puVar7 = *puVar7 - (*puVar7 >> 2);
            break;
        case 4:
            *puVar4 = *puVar4 - *puVar4 / 0x14;
            *puVar6 = *puVar6 - *puVar6 / 0x14;
            *puVar8 = *puVar8 - *puVar8 / 0x14;
            *pbVar3 = *pbVar3 - *pbVar3 / 10;
            *puVar7 = *puVar7 >> 1;
        }
        uVar1 = (&g_first_city_agriculture)[uVar9 * 0x12];
        (&g_first_city_agriculture)[uVar9 * 0x12] = uVar1 - uVar1 / 0x14;
    switchD_81c17494_caseD_0:
        uVar9 = uVar9 + 1 & 0xff;
        if (0x25 < uVar9)
        {
            return 1;
        }
    } while (true);
}

/* 原函数 0x81c1767c */
void sango_strategy_collect_commerce_income(void)
{
    uint16_t uVar1;
    int iVar2;
    uint32_t uVar3;

    uVar3 = 0;
    iVar2 = 0;
    do
    {
        iVar2 = iVar2 + uVar3;
        uVar1 = (&g_first_city_money)[iVar2 * 2];
        uVar3 = uVar3 + 1 & 0xff;
        if (uVar1 < 30000)
        {
            (&g_first_city_money)[iVar2 * 2] =
                uVar1 + ((uint16_t)(&g_first_city_commerce)[iVar2 * 2] >> 1);
        }
        iVar2 = uVar3 << 3;
    } while (uVar3 < 0x26);
    return;
}

/* 原函数 0x81c176d8 */
void sango_strategy_collect_agriculture_income(void)
{
    int iVar1;
    uint32_t uVar2;

    uVar2 = 0;
    iVar1 = 0;
    do
    {
        iVar1 = iVar1 + uVar2;
        uVar2 = uVar2 + 1 & 0xff;
        if ((uint16_t)(&g_first_city_food)[iVar1 * 2] < 30000)
        {
            (&g_first_city_food)[iVar1 * 2] =
                (&g_first_city_food)[iVar1 * 2] +
                ((uint16_t)(&g_first_city_agriculture)[iVar1 * 2] >> 2);
        }
        iVar1 = uVar2 << 3;
    } while (uVar2 < 0x26);
    return;
}

/* 原函数 0x81c17734 */
/* 年度武将年龄与登场更新；原数据中出生年+16为成年登场年份。 */
uint32_t sango_strategy_update_character_ages_and_debut(void)
{
    bool already_present;
    int record_address;
    uint32_t roster_index;
    int city_offset_or_result;
    uint32_t spawn_city;
    uint32_t present_count;
    uint32_t character_id;
    uint32_t record_offset;

    if (g_current_month_view2 == '\x01')
    {
        character_id = 0;
        do
        {
            record_address = character_id * 0x10 + g_character_table_address;
            character_id = character_id + 1 & 0xff;
            *(char *)(record_address + 0xe) = *(char *)(record_address + 0xe) + '\x01';
        } while (character_id < 200);
    }
    character_id = 0;
    record_address = sango_resource_item(0x3f, g_scenario_id, g_resource_package_address);
    record_offset = 0;
    do
    {
        if ((uint16_t)(*(uint8_t *)(record_address + record_offset) + 0x10) == g_current_year_view2)
        {
            spawn_city = (uint32_t)((uint8_t *)(record_address + record_offset))[2];
            if (spawn_city == 0)
            {
                spawn_city = bbk_rand();
                spawn_city = (int)spawn_city % 0x26 & 0xff;
            }
            present_count = 0;
            roster_index = 0;
            do
            {
                city_offset_or_result = roster_index * 0x24;
                roster_index = roster_index + 1 & 0xff;
                present_count =
                    present_count +
                        (uint8_t)(&g_first_city_character_count)[city_offset_or_result] &
                    0xff;
            } while (roster_index < 0x26);
            roster_index = 0;
            if (present_count == 0)
            {
                already_present = false;
            check_duplicate_character:
                if (already_present)
                    goto next_character_record;
            }
            else
            {
                do
                {
                    if ((uint8_t)(&g_city_character_roster)[roster_index] == character_id)
                    {
                        already_present = roster_index < present_count;
                        goto check_duplicate_character;
                    }
                    roster_index = roster_index + 1 & 0xff;
                } while (roster_index < present_count);
            }
            city_offset_or_result = sango_city_add_character(spawn_city, (uint8_t)character_id);
            if (city_offset_or_result == 0)
            {
                return 0;
            }
            *(uint8_t *)(character_id * 0x10 + g_character_table_address + 0xe) = 0x10;
        }
    next_character_record:
        character_id = character_id + 1 & 0xff;
        record_offset = record_offset + 3 & 0xffff;
        if (199 < character_id)
        {
            uint32_t city_index = 0;
            record_address = 0;
            do
            {
                record_address = (record_address + city_index) * 4;
                uint32_t roster_position =
                    (uint32_t)(uint8_t)(&g_first_city_character_start)[record_address];
                uint32_t roster_end =
                    roster_position + (uint8_t)(&g_first_city_character_count)[record_address];
                for (; roster_position < (roster_end & 0xff);
                     roster_position = roster_position + 1 & 0xff)
                {
                    record_address = roster_position * 0x10 + g_character_table_address;
                    *(char *)(record_address + 0xe) = *(char *)(record_address + 0xe) + '\x01';
                    if (((0x59 <
                          *(uint8_t *)(roster_position * 0x10 + g_character_table_address + 0xe)) &&
                         (roster_index = bbk_rand(), (int)roster_index % 100 < 0x32)) &&
                        (record_address =
                             sango_city_remove_character(city_index, (uint8_t)roster_position),
                         record_address == 0))
                    {
                        return 0;
                    }
                }
                city_index = city_index + 1 & 0xff;
                record_address = city_index << 3;
                if (0x25 < city_index)
                {
                    return 1;
                }
            } while (true);
        }
    } while (true);
}

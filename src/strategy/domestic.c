#include "sango_internal.h"

/* 内政、俘虏、赏赐与交易等城市命令。 */

/* 原函数 0x81c0b6f0 */
uint32_t sango_strategy_resolve_search(int order_address)
{
    sango_strategy_present();
    char *message = g_scratch_buffer_address;
    uint32_t random_value = bbk_rand();
    uint32_t adjusted_random = random_value + 3;
    if (-1 < (int)random_value)
        adjusted_random = random_value;
    uint8_t actor_id = *(uint8_t *)(order_address + 1);
    uint32_t actor_index = (uint32_t)actor_id;
    uint32_t outcome = random_value + ((int)adjusted_random >> 2) * -4 & 0xff;
    int actor_address = actor_index * 16 + g_character_table_address;
    uint32_t intelligence = (uint32_t) * (uint8_t *)(actor_address + 4);
    char *text_part = message + 0x28;
    uint8_t actor_owner_id = *(uint8_t *)(actor_address + 1);
    uint32_t actor_owner = (uint32_t)actor_owner_id;
    uint32_t found_amount;
    uint32_t player_index;
    bool player_index_captured = false;

    /* 结果0为空、1为人物/宝物、2为金钱、3为粮食。
     * 保留原随机余数的有符号处理及每条路径的随机调用顺序。 */
    if (outcome == 1)
    {
        outcome = 0;
        uint32_t discovery_roll = bbk_rand();
        uint32_t discovery_threshold = (int)discovery_roll % 150 & 0xff;
        uint32_t discovery_kind = (int)discovery_roll % 150 & 1;
        if (discovery_threshold < intelligence)
        {
            if (discovery_kind == 0)
            {
                uint32_t candidate_count = sango_city_list_available_characters(
                    (uint32_t) * (uint8_t *)(order_address + 2), (int)message);
                if (candidate_count != 0)
                {
                    uint32_t selection_roll = bbk_rand();
                    if (candidate_count == 0)
                        sango_legacy_trap(7);
                    uint32_t recruitment_result = 0;
                    uint8_t discovered_id =
                        message[(int)selection_roll % (int)candidate_count & 0xff];
                    int debut_address =
                        sango_resource_item(0x3f, g_scenario_id, g_resource_package_address);
                    uint32_t required_discoverer =
                        (uint32_t) * (uint8_t *)(debut_address + (uint32_t)discovered_id * 3 + 1);
                    bool recruit_character = required_discoverer - 1 == actor_index;
                    if (!recruit_character && required_discoverer == 0)
                    {
                        uint32_t recruitment_roll = bbk_rand();
                        recruitment_result = 2;
                        recruit_character = ((int)recruitment_roll % 110 & 0xffU) < intelligence;
                    }
                    if (recruit_character)
                    {
                        recruitment_result = 1;
                        int discovered_address =
                            (uint32_t)discovered_id * 16 + g_character_table_address;
                        *(uint8_t *)(discovered_address + 1) = actor_owner_id;
                        uint32_t loyalty_roll = bbk_rand();
                        *(char *)(discovered_address + 5) =
                            (char)loyalty_roll + (char)((int)loyalty_roll / 30) * -30 + 'F';
                    }

                    player_index = (uint32_t)g_player_character;
                    player_index_captured = actor_owner != player_index + 1;
                    if (actor_owner == player_index + 1)
                    {
                        outcome = 1;
                        uint8_t speaker_id = discovered_id;
                        if (recruitment_result == 0)
                        {
                            sango_resource_read_text(0x40, 100, message);
                            speaker_id = actor_id;
                        }
                        else
                        {
                            sango_resource_read_text(0x40, 99, message);
                            sango_load_named_text(discovered_id, text_part);
                            bbk_strcat(message, text_part);
                            sango_ui_show_character_message(actor_id, message);
                            uint32_t response_text_id = recruitment_result;
                            if (recruitment_result == 1 || recruitment_result == 2)
                            {
                                uint32_t response_roll = bbk_rand();
                                uint32_t adjusted_response = response_roll + 3;
                                if (-1 < (int)response_roll)
                                    adjusted_response = response_roll;
                                uint32_t response_index =
                                    response_roll + ((int)adjusted_response >> 2) * -4;
                                response_text_id =
                                    (response_index - (recruitment_result == 1 ? 0x7a : 0x76)) &
                                    0xff;
                            }
                            sango_resource_read_text(0x40, response_text_id, message);
                        }
                        sango_ui_show_character_message(speaker_id, message);
                    }
                }
            }
            else if (discovery_kind == 1)
            {
                uint32_t candidate_count =
                    sango_city_find_item((uint32_t) * (uint8_t *)(order_address + 2), (int)message);
                if (candidate_count != 0)
                {
                    uint32_t selection_roll = bbk_rand();
                    if (candidate_count == 0)
                        sango_legacy_trap(7);
                    uint8_t item_id = message[(int)selection_roll % (int)candidate_count & 0xff];
                    int debut_address =
                        sango_resource_item(0x43, g_scenario_id, g_resource_package_address);
                    uint32_t required_discoverer =
                        (uint32_t) * (uint8_t *)(debut_address + (uint32_t)item_id * 3 + 1);
                    if (required_discoverer == 0 || required_discoverer - 1 == actor_index)
                    {
                        bool is_player = actor_owner == g_player_character + 1;
                        if (is_player)
                        {
                            sango_resource_read_text(0x40, 99, message);
                            sango_item_read_name(item_id, text_part);
                            bbk_strcat(message, text_part);
                            sango_ui_show_character_message(actor_id, message);
                        }
                        outcome = (uint32_t)is_player;
                        sango_item_mark_discovered(item_id);
                    }
                }
            }
        }
    }
    else if (1 < outcome)
    {
        if (outcome == 2 || outcome == 3)
        {
            uint32_t amount_roll = bbk_rand();
            if (intelligence == 0)
                sango_legacy_trap(7);
            player_index = (uint32_t)g_player_character;
            player_index_captured = true;
            found_amount = (int)amount_roll % (int)(intelligence << 1) + 10U & 0xff;
            uint32_t city_id = (uint32_t) * (uint8_t *)(order_address + 2);
            if (outcome == 2)
                (&g_first_city_money)[city_id * 0x12] =
                    (&g_first_city_money)[city_id * 0x12] + (short)found_amount;
            else
                (&g_first_city_food)[city_id * 0x12] =
                    (&g_first_city_food)[city_id * 0x12] + (short)found_amount;
        }
    }

    if (!player_index_captured)
        player_index = (uint32_t)g_player_character;
    if (actor_owner == player_index + 1 && outcome != 1)
    {
        if (outcome == 0)
            sango_resource_read_text(0x40, 0x65, message);
        else
        {
            sango_resource_read_text(0x40, outcome + 100 & 0xff, message);
            sango_format_integer(found_amount, text_part, 10);
            bbk_strcat(message, text_part);
        }
        sango_ui_show_character_message(actor_id, message);
    }
    uint8_t return_city = *(uint8_t *)(order_address + 2);
    sango_city_add_character((uint32_t)return_city, actor_id);
    return 1;
}

/* 原函数 0x81c0bc70 */
uint32_t sango_strategy_resolve_sow_discord(int param_1)
{
    uint8_t bVar1;
    uint8_t bVar2;
    uint8_t bVar3;
    bool bVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    char *pcVar7;
    int iVar8;
    int iVar9;

    bVar1 = *(uint8_t *)(param_1 + 1);
    bVar2 = *(uint8_t *)(param_1 + 3);
    iVar9 = (uint32_t)bVar1 * 0x10;
    iVar8 = g_character_table_address + (uint32_t)bVar2 * 0x10;
    bVar4 = false;
    if (*(char *)(iVar8 + 1) != *(char *)(iVar9 + g_character_table_address + 1))
    {
        uVar6 = ((uint32_t) * (uint8_t *)(iVar9 + g_character_table_address + 4) -
                 (uint32_t) * (uint8_t *)(iVar8 + 4)) +
                    0x32 &
                0xff;
        uVar5 = bbk_rand();
        if (((int)uVar5 % 100 & 0xffU) <= uVar6)
        {
            switch (*(uint8_t *)(iVar8 + 6))
            {
            case 0:
                uVar6 = 2;
                break;
            case 1:
                uVar6 = 5;
                break;
            case 2:
                uVar6 = 4;
                break;
            case 3:
                uVar6 = 3;
                break;
            case 4:
                uVar6 = 1;
            }
            bVar3 = *(uint8_t *)(iVar8 + 5);
            *(uint8_t *)(iVar8 + 5) = bVar3 - bVar3 / 10;
            if (bVar3 < 0x3d)
            {
                if (uVar6 == 0)
                {
                    sango_legacy_trap(7);
                }
                uVar5 = bbk_rand();
                if (bVar3 / uVar6 <= ((int)uVar5 % 100 & 0xffU))
                {
                    bVar4 = true;
                    *(uint8_t *)(iVar8 + 1) = *(uint8_t *)(iVar9 + g_character_table_address + 1);
                    uVar5 = bbk_rand();
                    *(char *)(iVar8 + 5) = (char)uVar5 + (char)((int)uVar5 / 0x28) * -0x28 + '(';
                }
            }
        }
        if ((uint32_t) * (uint8_t *)(iVar9 + g_character_table_address + 1) ==
            g_player_character + 1)
        {
            if (bVar4)
            {
                sango_strategy_show_recruit_success(bVar2);
                uVar5 = (uint32_t) * (uint8_t *)(param_1 + 2);
            }
            else
            {
                pcVar7 = (char *)(g_scratch_buffer_address + 300);
                uVar5 = bbk_rand();
                sango_resource_read_text(0x40, (int)uVar5 % 3 + 0x7aU & 0xff, pcVar7);
                sango_strategy_present();
                sango_ui_show_character_message(bVar2, pcVar7);
                uVar5 = (uint32_t) * (uint8_t *)(param_1 + 2);
            }
            goto LAB_81c0bd9c;
        }
    }
    uVar5 = (uint32_t) * (uint8_t *)(param_1 + 2);
LAB_81c0bd9c:
    sango_city_add_character(uVar5, bVar1);
    return 1;
}

/* 原函数 0x81c0bf24 */
uint32_t sango_strategy_resolve_recruit(int param_1)
{
    uint32_t uVar1;
    uint8_t bVar2;
    uint32_t uVar3;
    int iVar4;

    iVar4 = (uint32_t) * (uint8_t *)(param_1 + 3) * 0x10;
    uVar3 = ((uint32_t) * (uint8_t *)((uint32_t) * (uint8_t *)(param_1 + 1) * 0x10 +
                                      g_character_table_address + 4) -
             (uint32_t) * (uint8_t *)(iVar4 + g_character_table_address + 4)) +
                0x32 &
            0xff;
    uVar1 = bbk_rand();
    if (uVar3 < ((int)uVar1 % 100 & 0xffU))
    {
    LAB_81c0bfbc:
        bVar2 = *(uint8_t *)(param_1 + 1);
        if ((uint32_t) * (uint8_t *)((uint32_t)bVar2 * 0x10 + g_character_table_address + 1) !=
            g_player_character + 1)
            goto LAB_81c0bfec;
    LAB_81c0c018:
        sango_ui_show_character_message(bVar2, &g_legacy_data_81c20284);
    }
    else
    {
        uVar1 = bbk_rand();
        if (((int)uVar1 % 100 & 0xffU) <
            (uint32_t) * (uint8_t *)(iVar4 + g_character_table_address + 5))
        {
            bVar2 = *(uint8_t *)(param_1 + 1);
            if ((uint32_t) * (uint8_t *)((uint32_t)bVar2 * 0x10 + g_character_table_address + 1) !=
                g_player_character + 1)
                goto LAB_81c0bfec;
            goto LAB_81c0c018;
        }
        switch (*(uint8_t *)(iVar4 + g_character_table_address + 6))
        {
        case 0:
            uVar3 = 0x32;
            break;
        case 1:
        case 3:
            uVar3 = 0x1e;
            break;
        case 2:
            uVar3 = 0x28;
            break;
        case 4:
            uVar3 = 5;
        }
        uVar1 = bbk_rand();
        if (uVar3 < ((int)uVar1 % 100 & 0xffU))
            goto LAB_81c0bfbc;
        iVar4 = iVar4 + g_character_table_address;
        if (*(uint8_t *)(iVar4 + 5) < 5)
        {
            *(uint8_t *)(iVar4 + 5) = 0;
        }
        else
        {
            *(uint8_t *)(iVar4 + 5) = *(uint8_t *)(iVar4 + 5) - 4;
        }
    }
    bVar2 = *(uint8_t *)(param_1 + 1);
LAB_81c0bfec:
    sango_city_add_character((uint32_t) * (uint8_t *)(param_1 + 2), bVar2);
    return 1;
}

/* 原函数 0x81c0c168 */
uint32_t sango_strategy_resolve_defection(int order_address)
{
    uint8_t envoy_id;
    uint32_t random_or_city;
    uint8_t character_id;
    char *message;
    uint32_t success_threshold;
    int target_offset;
    int envoy_offset;

    character_id = *(uint8_t *)(order_address + 3);
    envoy_id = *(uint8_t *)(order_address + 1);
    target_offset = (uint32_t)character_id * 0x10;
    envoy_offset = (uint32_t)envoy_id * 0x10;
    success_threshold = ((uint32_t) * (uint8_t *)(envoy_offset + g_character_table_address + 4) -
                         (uint32_t) * (uint8_t *)(target_offset + g_character_table_address + 4)) +
                            0x32 &
                        0xff;
    random_or_city = bbk_rand();
    if (success_threshold < ((int)random_or_city % 100 & 0xffU))
    {
    report_failed_recruitment:
        character_id = *(uint8_t *)(order_address + 1);
        if ((uint32_t) *
                (uint8_t *)((uint32_t)character_id * 0x10 + g_character_table_address + 1) ==
            g_player_character + 1)
        {
        use_failure_message:
            message = &g_legacy_data_81c202a8;
        show_envoy_message:
            sango_ui_show_character_message(character_id, message);
            random_or_city = (uint32_t) * (uint8_t *)(order_address + 2);
            goto return_envoy;
        }
    }
    else
    {
        random_or_city = bbk_rand();
        if (((int)random_or_city % 100 & 0xffU) <
            (uint32_t) * (uint8_t *)(target_offset + g_character_table_address + 5))
        {
            character_id = *(uint8_t *)(order_address + 1);
            if ((uint32_t) *
                    (uint8_t *)((uint32_t)character_id * 0x10 + g_character_table_address + 1) ==
                g_player_character + 1)
                goto use_failure_message;
        }
        else
        {
            switch (*(uint8_t *)(target_offset + g_character_table_address + 6))
            {
            case 0:
                success_threshold = 0xf;
                break;
            case 1:
                success_threshold = 0x28;
                break;
            case 2:
                success_threshold = 0x1e;
                break;
            case 3:
                success_threshold = 0x14;
                break;
            case 4:
                success_threshold = 5;
            }
            random_or_city = bbk_rand();
            if (success_threshold < ((int)random_or_city % 100 & 0xffU))
            {
                character_id = *(uint8_t *)(order_address + 1);
                if ((uint32_t) * (uint8_t *)((uint32_t)character_id * 0x10 +
                                             g_character_table_address + 1) ==
                    g_player_character + 1)
                {
                    message = &g_legacy_data_81c202b8;
                    goto show_envoy_message;
                }
            }
            else
            {
                random_or_city = sango_character_find_city(character_id);
                if (random_or_city == 0xff)
                    goto report_failed_recruitment;
                sango_city_remove_character(random_or_city, character_id);
                sango_city_add_character((uint32_t) * (uint8_t *)(order_address + 2), character_id);
                *(uint8_t *)(target_offset + g_character_table_address + 1) =
                    *(uint8_t *)(envoy_offset + g_character_table_address + 1);
                int target_address = target_offset + g_character_table_address;
                random_or_city = bbk_rand();
                *(char *)(target_address + 5) =
                    (char)random_or_city + (char)((int)random_or_city / 0x28) * -0x28 + '(';
                if ((uint32_t) * (uint8_t *)(envoy_offset + g_character_table_address + 1) ==
                    g_player_character + 1)
                {
                    sango_strategy_show_recruit_success(character_id);
                    random_or_city = (uint32_t) * (uint8_t *)(order_address + 2);
                    goto return_envoy;
                }
            }
        }
    }
    random_or_city = (uint32_t) * (uint8_t *)(order_address + 2);
return_envoy:
    sango_city_add_character(random_or_city, envoy_id);
    return 1;
}

/* 原函数 0x81c0c490 */
uint32_t sango_strategy_resolve_surrender(int param_1)
{
    uint32_t uVar1;
    uint8_t *pbVar2;
    uint8_t bVar3;
    char cVar4;
    uint32_t uVar5;
    int iVar6;

    bVar3 = *(uint8_t *)(param_1 + 3);
    iVar6 = (uint32_t)bVar3 * 0x10;
    uVar5 = ((uint32_t) * (uint8_t *)((uint32_t) * (uint8_t *)(param_1 + 1) * 0x10 +
                                      g_character_table_address + 4) -
             (uint32_t) * (uint8_t *)(iVar6 + g_character_table_address + 4)) +
                0x32 &
            0xff;
    uVar1 = bbk_rand();
    if (uVar5 < ((int)uVar1 % 100 & 0xffU))
    {
    LAB_81c0c52c:
        bVar3 = *(uint8_t *)(param_1 + 1);
        if ((uint32_t) * (uint8_t *)((uint32_t)bVar3 * 0x10 + g_character_table_address + 1) !=
            g_player_character + 1)
            goto LAB_81c0c55c;
    }
    else
    {
        uVar1 = bbk_rand();
        if ((uint32_t) * (uint8_t *)(iVar6 + g_character_table_address + 5) <=
            ((int)uVar1 % 100 & 0xffU))
        {
            switch (*(uint8_t *)(iVar6 + g_character_table_address + 6))
            {
            case 0:
                uVar5 = 0x1e;
                break;
            case 1:
                uVar5 = 10;
                break;
            case 2:
                uVar5 = 0x14;
                break;
            case 3:
                uVar5 = 0x3c;
                break;
            case 4:
                uVar5 = 5;
            }
            uVar1 = bbk_rand();
            if (((int)uVar1 % 100 & 0xffU) <= uVar5)
            {
                uVar1 = sango_character_find_city(bVar3);
                cVar4 = bVar3 + 1;
                if (uVar1 != 0xff)
                {
                    *(char *)(iVar6 + g_character_table_address + 1) = cVar4;
                    iVar6 = g_scratch_buffer_address;
                    uVar5 = sango_city_list_idle_characters(uVar1, g_scratch_buffer_address);
                    (&g_first_city_owner)[uVar1 * 0x24] = cVar4;
                    uVar1 = 0;
                    if (uVar5 != 0)
                    {
                        do
                        {
                            pbVar2 = (uint8_t *)(iVar6 + uVar1);
                            uVar1 = uVar1 + 1 & 0xff;
                            *(char *)((uint32_t)*pbVar2 * 0x10 + g_character_table_address + 1) =
                                cVar4;
                        } while (uVar1 < uVar5);
                    }
                    sango_strategy_show_ruler_defection(bVar3);
                    bVar3 = *(uint8_t *)(param_1 + 1);
                    goto LAB_81c0c55c;
                }
            }
            goto LAB_81c0c52c;
        }
        bVar3 = *(uint8_t *)(param_1 + 1);
        if ((uint32_t) * (uint8_t *)((uint32_t)bVar3 * 0x10 + g_character_table_address + 1) !=
            g_player_character + 1)
            goto LAB_81c0c55c;
    }
    sango_ui_show_character_message(bVar3, &g_legacy_data_81c202e0);
    bVar3 = *(uint8_t *)(param_1 + 1);
LAB_81c0c55c:
    sango_city_add_character((uint32_t) * (uint8_t *)(param_1 + 2), bVar3);
    return 1;
}

/* 原函数 0x81c0c754 */
uint32_t sango_strategy_resolve_diplomatic_mission(int order_address)
{
    uint8_t target_ruler;
    uint8_t envoy_id;
    bool surrendered;
    uint32_t target_count_or_chance;
    int scratch_or_message_base;
    uint8_t owner_or_speaker;
    uint32_t character_index;
    uint32_t player_or_city_count;
    char *text_part;
    char *message;
    int target_record_or_roster;
    int envoy_offset;
    uint32_t target_or_city_index;
    uint32_t envoy_owner;

    scratch_or_message_base = g_scratch_buffer_address;
    player_or_city_count = (uint32_t)g_player_character;
    target_ruler = *(uint8_t *)(order_address + 3);
    target_or_city_index = (uint32_t)target_ruler;
    envoy_id = *(uint8_t *)(order_address + 1);
    surrendered = false;
    if (player_or_city_count == target_or_city_index)
    {
        owner_or_speaker = envoy_id;
        if ((uint32_t) * (uint8_t *)((uint32_t)envoy_id * 0x10 + g_character_table_address + 1) !=
            target_or_city_index + 1)
            goto show_result_and_return_envoy;
    }
    else
    {
        envoy_offset = (uint32_t)envoy_id * 0x10;
        owner_or_speaker = *(uint8_t *)(envoy_offset + g_character_table_address + 1);
        envoy_owner = (uint32_t)owner_or_speaker;
        target_record_or_roster = target_or_city_index * 0x10;
        player_or_city_count =
            sango_faction_list_cities(envoy_owner - 1 & 0xff, g_scratch_buffer_address);
        target_count_or_chance = sango_faction_list_cities(
            *(uint8_t *)(target_record_or_roster + g_character_table_address + 1) - 1 & 0xff,
            scratch_or_message_base);
        if ((int)(target_count_or_chance << 1) <= (int)player_or_city_count)
        {
            target_count_or_chance =
                ((uint32_t) * (uint8_t *)(envoy_offset + g_character_table_address + 4) -
                 (uint32_t) *
                     (uint8_t *)(target_record_or_roster + g_character_table_address + 4)) +
                    0x32 &
                0xff;
            player_or_city_count = bbk_rand();
            if (((int)player_or_city_count % 100 & 0xffU) <= target_count_or_chance)
            {
                switch (*(uint8_t *)(target_record_or_roster + g_character_table_address + 6))
                {
                case 0:
                    target_count_or_chance = 10;
                    break;
                case 1:
                    target_count_or_chance = 1;
                    break;
                case 2:
                    target_count_or_chance = 0x14;
                    break;
                case 3:
                    target_count_or_chance = 5;
                    break;
                case 4:
                    target_count_or_chance = 0xf;
                }
                player_or_city_count = bbk_rand();
                if (((int)player_or_city_count % 100 & 0xffU) <= target_count_or_chance)
                {
                    target_record_or_roster = g_scratch_buffer_address + 0x26;
                    player_or_city_count =
                        sango_faction_list_cities(target_or_city_index, scratch_or_message_base);
                    target_or_city_index = 0;
                    if (player_or_city_count != 0)
                    {
                        do
                        {
                            target_count_or_chance = sango_city_list_idle_characters(
                                (uint32_t) *
                                    (uint8_t *)(scratch_or_message_base + target_or_city_index),
                                target_record_or_roster);
                            (&g_first_city_owner)[(uint32_t) *
                                                  (uint8_t *)(scratch_or_message_base +
                                                              target_or_city_index) *
                                                  0x24] = owner_or_speaker;
                            character_index = 0;
                            if (target_count_or_chance != 0)
                            {
                                do
                                {
                                    character_index = character_index + 1 & 0xff;
                                    *(uint8_t *)((uint32_t) *
                                                     (uint8_t *)(target_record_or_roster +
                                                                 target_or_city_index) *
                                                     0x10 +
                                                 g_character_table_address + 1) = owner_or_speaker;
                                } while (character_index < target_count_or_chance);
                            }
                            target_or_city_index = target_or_city_index + 1 & 0xff;
                        } while (target_or_city_index < player_or_city_count);
                    }
                    player_or_city_count = (uint32_t)g_player_character;
                    surrendered = true;
                    goto show_result_and_return_envoy;
                }
            }
        }
        player_or_city_count = (uint32_t)g_player_character;
        owner_or_speaker = *(uint8_t *)(order_address + 1);
        if ((uint32_t) * (uint8_t *)((uint32_t) * (uint8_t *)(order_address + 1) * 0x10 +
                                     g_character_table_address + 1) !=
            player_or_city_count + 1)
            goto show_result_and_return_envoy;
    }
    sango_ui_show_character_message(owner_or_speaker, &g_legacy_data_81c20304);
    player_or_city_count = (uint32_t)g_player_character;
show_result_and_return_envoy:
    text_part = (char *)(g_scratch_buffer_address + 0x154);
    message = (char *)(g_scratch_buffer_address + 300);
    if (envoy_owner == player_or_city_count + 1)
    {
        scratch_or_message_base = 0x9d;
        if (!surrendered)
        {
            scratch_or_message_base = 0x99;
        }
        target_or_city_index = bbk_rand();
        player_or_city_count = target_or_city_index + 3;
        if (-1 < (int)target_or_city_index)
        {
            player_or_city_count = target_or_city_index;
        }
        sango_resource_read_text(0x40,
                                 scratch_or_message_base + target_or_city_index +
                                         ((int)player_or_city_count >> 2) * -4 &
                                     0xff,
                                 message);
        sango_strategy_present();
        sango_ui_show_character_message(target_ruler, message);
        player_or_city_count = (uint32_t) * (uint8_t *)(order_address + 2);
    }
    else if (surrendered)
    {
        sango_load_named_text(target_ruler, message);
        sango_resource_read_text(0x40, 0x6e, text_part);
        bbk_strcat(message, text_part);
        sango_load_named_text((char)envoy_owner + 0xff, text_part);
        bbk_strcat(message, text_part);
        sango_ui_show_message(message, 2);
        player_or_city_count = (uint32_t) * (uint8_t *)(order_address + 2);
    }
    else
    {
        player_or_city_count = (uint32_t) * (uint8_t *)(order_address + 2);
    }
    sango_city_add_character(player_or_city_count, envoy_id);
    return 1;
}

/* 原函数 0x81c0cb64 */
uint32_t sango_strategy_resolve_plunder(int param_1)
{
    uint8_t bVar1;
    uint16_t uVar2;
    uint16_t uVar3;
    char *destination;
    int iVar4;
    uint32_t uVar5;
    int iVar6;
    int iVar7;
    uint32_t uVar8;
    char *source;

    iVar4 = g_character_table_address;
    uVar5 = (uint32_t) * (uint8_t *)(param_1 + 2);
    uVar2 = (&g_first_city_agriculture)[uVar5 * 0x12];
    uVar3 = (&g_first_city_commerce)[uVar5 * 0x12];
    (&g_first_city_loyalty)[uVar5 * 0x24] = (uint8_t)(&g_first_city_loyalty)[uVar5 * 0x24] >> 1;
    (&g_first_city_agriculture)[uVar5 * 0x12] = uVar2 >> 1;
    (&g_first_city_commerce)[uVar5 * 0x12] = uVar3 >> 1;
    iVar6 = (uint32_t) * (uint8_t *)(param_1 + 1) * 0x10 + iVar4;
    uVar8 = (uint32_t)g_player_character;
    iVar6 = (uint32_t) * (uint8_t *)(iVar6 + 4) + (uint32_t) * (uint8_t *)(iVar6 + 3);
    iVar7 = iVar6 * 2;
    iVar6 = iVar6 * 5;
    (&g_first_city_money)[uVar5 * 0x12] = (short)iVar7 + (&g_first_city_money)[uVar5 * 0x12];
    (&g_first_city_food)[uVar5 * 0x12] = (short)iVar6 + (&g_first_city_food)[uVar5 * 0x12];
    destination = g_scratch_buffer_address;
    bVar1 = *(uint8_t *)(param_1 + 1);
    if ((uint32_t) * (uint8_t *)((uint32_t)bVar1 * 0x10 + iVar4 + 1) == uVar8 + 1)
    {
        source = g_scratch_buffer_address + 100;
        sango_resource_read_text(0x40, 0x95, g_scratch_buffer_address);
        sango_format_integer(iVar7, source, 10);
        bbk_strcat(destination, source);
        sango_resource_read_text(0x40, 0x96, source);
        bbk_strcat(destination, source);
        sango_format_integer(iVar6, source, 10);
        bbk_strcat(destination, source);
        sango_resource_read_text(0x40, 0x97, source);
        bbk_strcat(destination, source);
        sango_ui_show_character_message(*(uint8_t *)(param_1 + 1), destination);
        bVar1 = *(uint8_t *)(param_1 + 1);
    }
    sango_city_add_character((uint32_t) * (uint8_t *)(param_1 + 2), bVar1);
    return 1;
}

/* 原函数 0x81c0cd08 */
uint32_t sango_strategy_execute_queued_order(uint8_t *order)
{
    char target_owner;
    char character_owner;
    char *message;
    uint32_t target_or_roll;
    uint8_t character_id;
    uint32_t message_id;

    sango_strategy_find_ready_order();
    switch (*order)
    {
    case 0:
    case 0x14:
    case 0x15:
    case 0x16:
        goto order_done;
    case 1:
        sango_city_add_character((uint32_t)(uint8_t)order[2], order[1]);
        break;
    case 2:
        sango_city_add_character((uint32_t)(uint8_t)order[2], order[1]);
    case 0xc:
        break;
    case 3:
        sango_strategy_resolve_search((int)order);
        break;
    case 4:
        sango_city_add_character((uint32_t)(uint8_t)order[2], order[1]);
        break;
    case 5:
        sango_city_add_character((uint32_t)(uint8_t)order[2], order[1]);
        break;
    case 6:
        sango_strategy_resolve_sow_discord((int)order);
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        break;
    case 10:
        break;
    case 0xb:
        sango_city_add_character((uint32_t)(uint8_t)order[2], order[1]);
        break;
    case 0xd:
        target_or_roll = bbk_rand();
        message_id = 0x78;
        if (0x14 < (int)target_or_roll % 100)
        {
            target_or_roll = (uint32_t)(uint8_t)order[3];
            message_id = 0x77;
            (&g_first_city_food)[target_or_roll * 0x12] =
                (&g_first_city_food)[target_or_roll * 0x12] + *(short *)(order + 6);
            (&g_first_city_money)[target_or_roll * 0x12] =
                (&g_first_city_money)[target_or_roll * 0x12] + *(short *)(order + 8);
            (&g_first_city_reserve_troops)[target_or_roll * 0x12] =
                (&g_first_city_reserve_troops)[target_or_roll * 0x12] + *(short *)(order + 4);
        }
        message = g_scratch_buffer_address;
        sango_resource_read_text(0x40, message_id, g_scratch_buffer_address);
        sango_ui_show_character_message(order[1], message);
        sango_city_add_character((uint32_t)(uint8_t)order[2], order[1]);
        break;
    case 0xe:
        target_or_roll = (uint32_t)(uint8_t)order[3];
        character_id = order[1];
        target_owner = (&g_first_city_owner)[target_or_roll * 0x24];
        character_owner = *(char *)((uint32_t)character_id * 0x10 + g_character_table_address + 1);
        if (target_owner == '\0')
        {
            (&g_first_city_owner)[target_or_roll * 0x24] = character_owner;
            character_id = order[1];
        }
        else if (target_owner != character_owner)
        {
            target_or_roll = (uint32_t)(uint8_t)order[2];
        }
        sango_city_add_character(target_or_roll, character_id);
        break;
    case 0xf:
        sango_strategy_resolve_recruit((int)order);
        break;
    case 0x10:
        sango_strategy_resolve_defection((int)order);
        break;
    case 0x11:
        sango_strategy_resolve_surrender((int)order);
        break;
    case 0x12:
        break;
    case 0x13:
        sango_strategy_resolve_diplomatic_mission((int)order);
        break;
    case 0x17:
        sango_city_add_character((uint32_t)(uint8_t)order[2], order[1]);
        break;
    case 0x18:
        sango_city_add_character((uint32_t)(uint8_t)order[2], order[1]);
        break;
    case 0x19:
        break;
    case 0x1a:
        sango_strategy_resolve_plunder((int)order);
        break;
    case 0x1b:
        sango_strategy_resolve_attack((int)order);
        break;
    default:
        return 1;
    }
    sango_strategy_find_ready_order();
order_done:
    return 1;
}

/* 原函数 0x81c0d03c */
void sango_strategy_find_ready_order(void)
{
    unsigned char abi_storage[120] __attribute__((aligned(8)));
#define auStack_70 (*(uint8_t(*)[104])(abi_storage + 0))

    uint8_t bVar1;
    uint8_t uVar2;
    int iVar3;
    uint8_t *puVar4;
    uint8_t *pbVar5;
    int iVar6;
    int iVar7;
    int iVar8;

    iVar7 = 0;
    pbVar5 = &g_first_city_character_count;
    iVar3 = 0x25;
    do
    {
        bVar1 = *pbVar5;
        iVar3 = iVar3 + -1;
        pbVar5 = pbVar5 + 0x24;
        iVar7 = iVar7 + (uint32_t)bVar1;
    } while (-1 < iVar3);
    iVar3 = 0;
    if (0 < iVar7 + -1)
    {
        do
        {
            iVar8 = iVar3 + 1;
            if (iVar8 < iVar7)
            {
                puVar4 = &g_city_character_roster_next + iVar3;
                iVar6 = iVar8;
                do
                {
                    uVar2 = *puVar4;
                    iVar6 = iVar6 + 1;
                    puVar4 = puVar4 + 1;
                    if ((&g_city_character_roster)[iVar3] == uVar2)
                    {
                        sango_load_named_text((&g_city_character_roster)[iVar3], auStack_70);
                        return;
                    }
                } while (iVar6 < iVar7);
            }
            iVar3 = iVar8;
        } while (iVar8 < iVar7 + -1);
    }
    return;
}
#undef auStack_70

/* 原函数 0x81c0d0e4 */
uint32_t sango_strategy_return_order_character(int param_1)
{
    sango_city_add_character((uint32_t) * (uint8_t *)(param_1 + 2), *(uint8_t *)(param_1 + 1));
    return 1;
}

/* 原函数 0x81c0d304 */
uint32_t sango_strategy_success_stub(void)
{
    return 1;
}

/* 原函数 0x81c0d354 */
void sango_strategy_advance_orders(void)
{
    int iVar1;
    char *pcVar2;
    uint32_t uVar3;

    iVar1 = g_order_queue_address;
    uVar3 = 0;
    do
    {
        pcVar2 = (char *)(uVar3 * 0xc + iVar1);
        if (*pcVar2 != -1)
        {
            sango_strategy_execute_queued_order(pcVar2);
            sango_strategy_queue_noop(pcVar2);
        }
        uVar3 = uVar3 + 1 & 0xff;
    } while (uVar3 < 100);
    return;
}

/* 原函数 0x81c0d3e0 */
uint32_t sango_city_choose_command(void)
{
    uint32_t uVar1;

    while (true)
    {
        while (true)
        {
            while (true)
            {
                sango_strategy_present();
                uVar1 = sango_city_choose_command_group();
                if (uVar1 != 2)
                    break;
                uVar1 = sango_city_choose_military_command();
                if (uVar1 != 0xff)
                {
                    return uVar1 + 0x17 & 0xff;
                }
            }
            if (2 < (int)uVar1)
                break;
            if (uVar1 == 0)
            {
                uVar1 = sango_city_choose_domestic_command();
                if (uVar1 != 0xff)
                {
                    return uVar1 + 1 & 0xff;
                }
            }
            else if (uVar1 == 1)
            {
                uVar1 = sango_city_choose_diplomacy_command();
                if (uVar1 != 0xff)
                {
                    return uVar1 + 0xf & 0xff;
                }
            }
        }
        if (uVar1 == 3)
            break;
        if (uVar1 == 0xff)
        {
            return 0xff;
        }
    }
    return 0xfe;
}

/* 原函数 0x81c0d498 */
uint32_t sango_city_choose_command_group(void)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define local_30 (*(uint16_t(*)[4])(abi_storage + 0))
#define acStack_28 (*(char(*)[32])(abi_storage + 8))

    uint32_t uVar1;

    sango_resource_read_text(0x40, 0x25, acStack_28);
    local_30[0] = 0x4f;
    local_30[2] = 0x67;
    local_30[1] = 10;
    local_30[3] = 0x3a;
    uVar1 = sango_ui_choose_option(local_30, 0, acStack_28);
    return uVar1;
}
#undef local_30
#undef acStack_28

/* 原函数 0x81c0d4f8 */
uint32_t sango_city_choose_domestic_command(void)
{
    unsigned char abi_storage[104] __attribute__((aligned(8)));
#define local_60 (*(uint16_t(*)[4])(abi_storage + 0))
#define acStack_58 (*(char(*)[80])(abi_storage + 8))

    uint32_t uVar1;

    sango_resource_read_text(0x40, 0x26, acStack_58);
    local_60[0] = 0x77;
    local_60[2] = 0x8f;
    local_60[1] = 0xe;
    local_60[3] = 0xb2;
    uVar1 = sango_ui_choose_option(local_60, 0, acStack_58);
    return uVar1;
}
#undef local_60
#undef acStack_58

/* 原函数 0x81c0d558 */
uint32_t sango_city_choose_diplomacy_command(void)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define acStack_28 (*(char(*)[32])(abi_storage + 8))
#define local_30 (*(uint16_t(*)[4])(abi_storage + 0))

    uint32_t uVar1;

    sango_resource_read_text(0x40, 0x27, acStack_28);
    local_30[0] = 0x77;
    local_30[2] = 0x8f;
    local_30[1] = 0xe;
    local_30[3] = 0x4a;
    uVar1 = sango_ui_choose_option(local_30, 0, acStack_28);
    return uVar1;
}
#undef acStack_28
#undef local_30

/* 原函数 0x81c0d5b8 */
uint32_t sango_city_choose_military_command(void)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define acStack_28 (*(char(*)[32])(abi_storage + 8))
#define local_30 (*(uint16_t(*)[4])(abi_storage + 0))

    uint32_t uVar1;

    sango_resource_read_text(0x40, 0x28, acStack_28);
    local_30[0] = 0x77;
    local_30[2] = 0x8f;
    local_30[1] = 0xe;
    local_30[3] = 0x4a;
    uVar1 = sango_ui_choose_option(local_30, 0, acStack_28);
    return uVar1;
}
#undef acStack_28
#undef local_30

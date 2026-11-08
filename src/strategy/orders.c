#include "sango_internal.h"

/* 战略命令选择、目标及执行队列。 */

/* 原函数 0x81c0d618 */
/* 城市命令分派。数值对应原存档/队列中的命令ID，不能重新编号。 */
uint32_t sango_city_execute_command(uint8_t city_id, uint8_t command_id)
{
    uint32_t city_index;
    uint32_t accepted;

    city_index = (uint32_t)city_id;
    accepted = 0;
    if (city_index < 0x26)
    {
        accepted = 1;
        switch (command_id)
        {
        case 1:
            sango_city_order_agriculture(city_id);
        case 0:
        case 0x14:
        case 0x15:
        case 0x16:
            accepted = 1;
            break;
        case 2:
            sango_city_order_commerce(city_id);
            accepted = 1;
            break;
        case 3:
            sango_city_order_search(city_id);
            accepted = 1;
            break;
        case 4:
            sango_city_order_disaster_prevention(city_id);
            accepted = 1;
            break;
        case 5:
            sango_city_order_patrol(city_id);
            accepted = 1;
            break;
        case 6:
            sango_city_order_recruit_captive(city_id);
            accepted = 1;
            break;
        case 7:
            sango_city_order_execute_captive(city_index);
            accepted = 1;
            break;
        case 8:
            sango_city_order_exile_character(city_index);
            accepted = 1;
            break;
        case 9:
            sango_city_order_reward(city_index);
            accepted = 1;
            break;
        case 10:
            sango_city_order_confiscate(city_index);
            accepted = 1;
            break;
        case 0xb:
            sango_city_order_trade(city_id);
            accepted = 1;
            break;
        case 0xc:
            sango_city_order_banquet(city_index);
            accepted = 1;
            break;
        case 0xd:
            sango_city_order_transport(city_index);
            accepted = 1;
            break;
        case 0xe:
            sango_city_order_transfer(city_id);
            accepted = 1;
            break;
        case 0xf:
            sango_city_order_sow_discord(city_id);
            accepted = 1;
            break;
        case 0x10:
            sango_city_order_recruit_enemy(city_id);
            accepted = 1;
            break;
        case 0x11:
            sango_city_order_defection(city_id);
            accepted = 1;
            break;
        case 0x12:
            sango_city_order_counterintelligence();
            accepted = 1;
            break;
        case 0x13:
            sango_city_order_demand_surrender(city_id);
            accepted = 1;
            break;
        case 0x17:
            sango_city_order_scout(city_id);
            accepted = 1;
            break;
        case 0x18:
            sango_city_order_recruit_troops(city_id);
            accepted = 1;
            break;
        case 0x19:
            sango_city_assign_troops(city_index);
            accepted = 1;
            break;
        case 0x1a:
            sango_city_order_plunder(city_id);
            accepted = 1;
            break;
        case 0x1b:
            sango_city_order_attack(city_id);
            accepted = 1;
        }
    }
    return accepted;
}

/* 原函数 0x81c0d7e4 */
uint32_t sango_city_order_agriculture(uint8_t city_id)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define order_actor (*(uint8_t *)(abi_storage + 1))
#define order_city (*(uint8_t *)(abi_storage + 2))
#define order_months (*(uint8_t *)(abi_storage + 11))
#define order_kind (*(uint8_t *)(abi_storage + 0))

    uint8_t intelligence;
    uint16_t development_limit;
    uint32_t city_index;
    int roster_address;
    uint32_t count_or_development_total;
    uint32_t selection_or_development_gain;
    uint8_t actor_or_error_text;
    uint32_t actor_id;
    uint16_t *development_address;

    roster_address = g_scratch_buffer_address;
    city_index = (uint32_t)city_id;
    count_or_development_total =
        sango_city_list_idle_characters(city_index, g_scratch_buffer_address);
    actor_or_error_text = 0x54;
    if (count_or_development_total != 0)
    {
        development_address = &g_first_city_agriculture + city_index * 0x12;
        development_limit = (&g_first_city_agriculture_limit)[city_index * 0x12];
        while (true)
        {
            actor_or_error_text = 0x34;
            if ((uint32_t)development_limit <= (uint32_t)*development_address)
                break;
            count_or_development_total = sango_city_can_pay_command(city_index, 1);
            if (count_or_development_total == 0)
            {
                actor_or_error_text = 0x3b;
                break;
            }
            count_or_development_total =
                sango_city_list_idle_characters(city_index, roster_address);
            if (count_or_development_total == 0)
            {
                return 1;
            }
            while (true)
            {
                sango_strategy_present();
                selection_or_development_gain = sango_ui_select_character(
                    roster_address, count_or_development_total, 4, 2, 0xeb, 0x3d);
                if (selection_or_development_gain == 0xff)
                {
                    return 1;
                }
                actor_or_error_text = *(uint8_t *)(roster_address + selection_or_development_gain);
                actor_id = (uint32_t)actor_or_error_text;
                selection_or_development_gain = sango_character_can_pay_action(actor_id, 1);
                if (selection_or_development_gain != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
            intelligence = *(uint8_t *)(actor_id * 0x10 + g_character_table_address + 4);
            selection_or_development_gain = bbk_rand();
            count_or_development_total = selection_or_development_gain + 3;
            if (-1 < (int)selection_or_development_gain)
            {
                count_or_development_total = selection_or_development_gain;
            }
            selection_or_development_gain =
                (intelligence / 10) * (selection_or_development_gain +
                                       ((int)count_or_development_total >> 2) * -4 + 2) +
                (uint32_t)(*(uint8_t *)(actor_id * 0x10 + g_character_table_address + 4) >> 1);
            count_or_development_total =
                (selection_or_development_gain & 0xffff) + (uint32_t)*development_address;
            *development_address = (uint16_t)count_or_development_total;
            if ((uint32_t)development_limit < (count_or_development_total & 0xffff))
            {
                *development_address = development_limit;
            }
            sango_city_show_development_result(city_index, actor_or_error_text,
                                               (uint8_t)selection_or_development_gain, 0);
            sango_character_pay_action(actor_id, 1);
            sango_city_pay_command(city_index, 1);
            order_kind = 1;
            order_months = 0;
            order_actor = actor_or_error_text;
            order_city = city_id;
            sango_strategy_enqueue_order(&order_kind);
            sango_city_remove_character(city_index, actor_or_error_text);
            development_limit = (&g_first_city_agriculture_limit)[city_index * 0x12];
        }
    }
    sango_ui_show_strategy_text(actor_or_error_text);
    return 1;
}
#undef order_actor
#undef order_city
#undef order_months
#undef order_kind

/* 原函数 0x81c0da0c */
uint32_t sango_city_order_commerce(uint8_t city_id)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define order_months (*(uint8_t *)(abi_storage + 11))
#define order_kind (*(uint8_t *)(abi_storage + 0))
#define order_actor (*(uint8_t *)(abi_storage + 1))
#define order_city (*(uint8_t *)(abi_storage + 2))

    uint8_t intelligence;
    uint16_t development_limit;
    uint32_t city_index;
    int roster_address;
    uint32_t count_or_development_total;
    uint32_t selection_or_development_gain;
    uint8_t actor_or_error_text;
    uint32_t actor_id;
    uint16_t *development_address;

    roster_address = g_scratch_buffer_address;
    city_index = (uint32_t)city_id;
    count_or_development_total =
        sango_city_list_idle_characters(city_index, g_scratch_buffer_address);
    actor_or_error_text = 0x54;
    if (count_or_development_total != 0)
    {
        development_address = &g_first_city_commerce + city_index * 0x12;
        while (true)
        {
            development_limit = (&g_first_city_commerce_limit)[city_index * 0x12];
            actor_or_error_text = 0x35;
            if ((uint32_t)development_limit <= (uint32_t)*development_address)
                break;
            count_or_development_total = sango_city_can_pay_command(city_index, 2);
            if (count_or_development_total == 0)
            {
                actor_or_error_text = 0x3b;
                break;
            }
            count_or_development_total =
                sango_city_list_idle_characters(city_index, roster_address);
            if (count_or_development_total == 0)
            {
                return 1;
            }
            while (true)
            {
                sango_strategy_present();
                selection_or_development_gain = sango_ui_select_character(
                    roster_address, count_or_development_total, 4, 2, 0xeb, 0x3d);
                if (selection_or_development_gain == 0xff)
                {
                    return 1;
                }
                actor_or_error_text = *(uint8_t *)(roster_address + selection_or_development_gain);
                actor_id = (uint32_t)actor_or_error_text;
                selection_or_development_gain = sango_character_can_pay_action(actor_id, 2);
                if (selection_or_development_gain != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
            intelligence = *(uint8_t *)(actor_id * 0x10 + g_character_table_address + 4);
            selection_or_development_gain = bbk_rand();
            count_or_development_total = selection_or_development_gain + 3;
            if (-1 < (int)selection_or_development_gain)
            {
                count_or_development_total = selection_or_development_gain;
            }
            selection_or_development_gain =
                (int)((intelligence / 10) * (selection_or_development_gain +
                                             ((int)count_or_development_total >> 2) * -4 + 2) +
                      (uint32_t) * (uint8_t *)(actor_id * 0x10 + g_character_table_address + 4)) >>
                1;
            count_or_development_total =
                (selection_or_development_gain & 0xffff) + (uint32_t)*development_address;
            *development_address = (uint16_t)count_or_development_total;
            if ((uint32_t)development_limit < (count_or_development_total & 0xffff))
            {
                *development_address = development_limit;
            }
            sango_city_show_development_result(city_index, actor_or_error_text,
                                               (uint8_t)selection_or_development_gain, 1);
            sango_character_pay_action(actor_id, 2);
            sango_city_pay_command(city_index, 2);
            order_kind = 2;
            order_months = 0;
            order_actor = actor_or_error_text;
            order_city = city_id;
            sango_strategy_enqueue_order(&order_kind);
            sango_city_remove_character(city_index, actor_or_error_text);
        }
    }
    sango_ui_show_strategy_text(actor_or_error_text);
    return 1;
}
#undef order_months
#undef order_kind
#undef order_actor
#undef order_city

/* 原函数 0x81c0dc30 */
void sango_city_show_development_result(uint32_t city_id, uint8_t actor_id,
                                        uint8_t development_gain, uint8_t development_kind)
{
    char *source;
    char *destination;
    uint32_t city_or_development_value;

    city_or_development_value = city_id & 0xff;
    source = (char *)(g_scratch_buffer_address + 0x15e);
    destination = (char *)(g_scratch_buffer_address + 300);
    if (development_kind == 1)
    {
        sango_resource_read_text(0x40, 0x74, destination);
        city_or_development_value =
            (uint32_t)(uint16_t)(&g_first_city_commerce)[city_or_development_value * 0x12];
    }
    else if (development_kind < 2)
    {
        if (development_kind != 0)
            goto append_result_message;
        sango_resource_read_text(0x40, 0x71, destination);
        city_or_development_value =
            (uint32_t)(uint16_t)(&g_first_city_agriculture)[city_or_development_value * 0x12];
    }
    else if (development_kind == 2)
    {
        sango_resource_read_text(0x40, 0x75, destination);
        city_or_development_value =
            (uint32_t)(uint8_t)(&g_first_city_loyalty)[city_or_development_value * 0x24];
    }
    else
    {
        if (development_kind != 3)
            goto append_result_message;
        sango_resource_read_text(0x40, 0x76, destination);
        city_or_development_value =
            (uint32_t)(uint8_t)(&g_first_city_disaster_prevention)[city_or_development_value *
                                                                   0x24];
    }
    sango_format_integer(city_or_development_value, source, 10);
append_result_message:
    bbk_strcat(destination, source);
    sango_resource_read_text(0x40, 0x72, source);
    bbk_strcat(destination, source);
    sango_format_integer((uint32_t)development_gain, source, 10);
    bbk_strcat(destination, source);
    sango_resource_read_text(0x40, 0x73, source);
    bbk_strcat(destination, source);
    sango_strategy_present();
    sango_ui_show_character_message(actor_id, destination);
    return;
}

/* 原函数 0x81c0ddf0 */
uint32_t sango_city_order_search(uint8_t city_id)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define order_kind (*(uint8_t *)(abi_storage + 0))
#define order_actor (*(uint8_t *)(abi_storage + 1))
#define order_city (*(uint8_t *)(abi_storage + 2))
#define order_months (*(uint8_t *)(abi_storage + 11))

    uint32_t city_index;
    int roster_address;
    uint32_t count_or_message_roll;
    uint32_t selection_or_message_variant;
    uint8_t actor_or_error_text;
    char *message;
    uint32_t actor_id;

    roster_address = g_scratch_buffer_address;
    city_index = (uint32_t)city_id;
    count_or_message_roll = sango_city_list_idle_characters(city_index, g_scratch_buffer_address);
    actor_or_error_text = 0x54;
    if (count_or_message_roll != 0)
    {
        while (count_or_message_roll = sango_city_can_pay_command(city_index, 3),
               count_or_message_roll != 0)
        {
            count_or_message_roll = sango_city_list_idle_characters(city_index, roster_address);
            if (count_or_message_roll == 0)
            {
                return 1;
            }
            while (true)
            {
                sango_strategy_present();
                selection_or_message_variant = sango_ui_select_character(
                    roster_address, count_or_message_roll, 4, 2, 0xeb, 0x3d);
                if (selection_or_message_variant == 0xff)
                {
                    return 1;
                }
                actor_or_error_text = *(uint8_t *)(roster_address + selection_or_message_variant);
                actor_id = (uint32_t)actor_or_error_text;
                selection_or_message_variant = sango_character_can_pay_action(actor_id, 3);
                if (selection_or_message_variant != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
            sango_character_pay_action(actor_id, 3);
            sango_city_pay_command(city_index, 3);
            count_or_message_roll = bbk_rand();
            selection_or_message_variant = (int)count_or_message_roll % 3 & 0xff;
            count_or_message_roll = selection_or_message_variant - 0x6f;
            if (g_player_character != actor_id)
            {
                count_or_message_roll = selection_or_message_variant - 0x72;
            }
            message = (char *)(g_scratch_buffer_address + 300);
            sango_resource_read_text(0x40, count_or_message_roll & 0xff, message);
            sango_ui_show_character_message(actor_or_error_text, message);
            order_kind = 3;
            order_months = 0;
            order_actor = actor_or_error_text;
            order_city = city_id;
            sango_strategy_enqueue_order(&order_kind);
            sango_city_remove_character(city_index, actor_or_error_text);
        }
        actor_or_error_text = 0x3b;
    }
    sango_ui_show_strategy_text(actor_or_error_text);
    return 1;
}
#undef order_kind
#undef order_actor
#undef order_city
#undef order_months

/* 原函数 0x81c0df94 */
uint32_t sango_city_order_disaster_prevention(uint8_t city_id)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define order_kind (*(uint8_t *)(abi_storage + 0))
#define order_actor (*(uint8_t *)(abi_storage + 1))
#define order_city (*(uint8_t *)(abi_storage + 2))
#define order_months (*(uint8_t *)(abi_storage + 11))

    uint32_t city_index;
    int roster_address;
    uint32_t count_or_prevention_gain;
    uint32_t selection_or_prevention_total;
    uint8_t actor_or_error_text;
    int city_offset;

    roster_address = g_scratch_buffer_address;
    city_index = (uint32_t)city_id;
    count_or_prevention_gain =
        sango_city_list_idle_characters(city_index, g_scratch_buffer_address);
    actor_or_error_text = 0x54;
    if (count_or_prevention_gain != 0)
    {
        while (count_or_prevention_gain = sango_city_can_pay_command(city_index, 4),
               count_or_prevention_gain != 0)
        {
            city_offset = city_index * 0x24;
            if (((&g_first_city_status)[city_offset] == '\0') &&
                (99 < (uint8_t)(&g_first_city_disaster_prevention)[city_offset]))
            {
                actor_or_error_text = 0x3d;
                goto show_command_error;
            }
            count_or_prevention_gain = sango_city_list_idle_characters(city_index, roster_address);
            if (count_or_prevention_gain == 0)
            {
                return 1;
            }
            while (true)
            {
                sango_strategy_present();
                selection_or_prevention_total = sango_ui_select_character(
                    roster_address, count_or_prevention_gain, 4, 2, 0xeb, 0x3d);
                if (selection_or_prevention_total == 0xff)
                {
                    return 1;
                }
                actor_or_error_text = *(uint8_t *)(roster_address + selection_or_prevention_total);
                selection_or_prevention_total =
                    sango_character_can_pay_action((uint32_t)actor_or_error_text, 4);
                if (selection_or_prevention_total != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
            sango_character_pay_action((uint32_t)actor_or_error_text, 4);
            sango_city_pay_command(city_index, 4);
            selection_or_prevention_total = bbk_rand();
            count_or_prevention_gain = selection_or_prevention_total + 3;
            if (-1 < (int)selection_or_prevention_total)
            {
                count_or_prevention_gain = selection_or_prevention_total;
            }
            count_or_prevention_gain =
                selection_or_prevention_total + ((int)count_or_prevention_gain >> 2) * -4 + 1;
            selection_or_prevention_total =
                (count_or_prevention_gain & 0xff) +
                (uint32_t)(uint8_t)(&g_first_city_disaster_prevention)[city_offset];
            (&g_first_city_status)[city_offset] = 0;
            (&g_first_city_disaster_prevention)[city_offset] = (char)selection_or_prevention_total;
            if (100 < (selection_or_prevention_total & 0xff))
            {
                (&g_first_city_disaster_prevention)[city_offset] = 100;
            }
            sango_city_show_development_result(city_index, actor_or_error_text,
                                               (uint8_t)count_or_prevention_gain, 3);
            order_kind = 4;
            order_months = 0;
            order_actor = actor_or_error_text;
            order_city = city_id;
            sango_strategy_enqueue_order(&order_kind);
            sango_city_remove_character(city_index, actor_or_error_text);
        }
        actor_or_error_text = 0x3b;
    }
show_command_error:
    sango_ui_show_strategy_text(actor_or_error_text);
    return 1;
}
#undef order_kind
#undef order_actor
#undef order_city
#undef order_months

/* 原函数 0x81c0e184 */
uint32_t sango_city_order_patrol(uint8_t city_id)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define order_kind (*(uint8_t *)(abi_storage + 0))
#define order_actor (*(uint8_t *)(abi_storage + 1))
#define order_city (*(uint8_t *)(abi_storage + 2))
#define order_months (*(uint8_t *)(abi_storage + 11))

    uint32_t city_index;
    int roster_address;
    uint32_t count_or_loyalty_gain;
    uint32_t selection_or_population_limit;
    uint32_t *population_limit_address;
    uint8_t actor_or_error_text;
    uint32_t previous_loyalty;
    uint8_t *loyalty_address;

    roster_address = g_scratch_buffer_address;
    city_index = (uint32_t)city_id;
    count_or_loyalty_gain = sango_city_list_idle_characters(city_index, g_scratch_buffer_address);
    actor_or_error_text = 0x54;
    if (count_or_loyalty_gain != 0)
    {
        while (count_or_loyalty_gain = sango_city_can_pay_command(city_index, 5),
               count_or_loyalty_gain != 0)
        {
            count_or_loyalty_gain = sango_city_list_idle_characters(city_index, roster_address);
            if (count_or_loyalty_gain == 0)
            {
                return 1;
            }
            while (true)
            {
                sango_strategy_present();
                selection_or_population_limit = sango_ui_select_character(
                    roster_address, count_or_loyalty_gain, 4, 2, 0xeb, 0x3d);
                if (selection_or_population_limit == 0xff)
                {
                    return 1;
                }
                actor_or_error_text = *(uint8_t *)(roster_address + selection_or_population_limit);
                selection_or_population_limit =
                    sango_character_can_pay_action((uint32_t)actor_or_error_text, 5);
                if (selection_or_population_limit != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
            sango_character_pay_action((uint32_t)actor_or_error_text, 5);
            sango_city_pay_command(city_index, 5);
            selection_or_population_limit = bbk_rand();
            count_or_loyalty_gain = selection_or_population_limit + 3;
            if (-1 < (int)selection_or_population_limit)
            {
                count_or_loyalty_gain = selection_or_population_limit;
            }
            loyalty_address = &g_first_city_loyalty + city_index * 0x24;
            previous_loyalty = (uint32_t)*loyalty_address;
            count_or_loyalty_gain =
                selection_or_population_limit + ((int)count_or_loyalty_gain >> 2) * -4 + 1 & 0xff;
            if (100 < previous_loyalty + count_or_loyalty_gain)
            {
                count_or_loyalty_gain = 100 - previous_loyalty & 0xff;
            }
            *loyalty_address = (uint8_t)(count_or_loyalty_gain + previous_loyalty);
            if (100 < (count_or_loyalty_gain + previous_loyalty & 0xff))
            {
                *loyalty_address = 100;
            }
            population_limit_address = &g_first_city_population_limit + city_index * 9;
            selection_or_population_limit = *population_limit_address;
            *population_limit_address = selection_or_population_limit + 100;
            if ((uint32_t)(&g_first_city_population)[city_index * 9] <
                selection_or_population_limit + 100)
            {
                *population_limit_address = (&g_first_city_population)[city_index * 9];
            }
            sango_city_show_development_result(city_index, actor_or_error_text,
                                               (uint8_t)count_or_loyalty_gain, 2);
            order_kind = 5;
            order_months = 0;
            order_actor = actor_or_error_text;
            order_city = city_id;
            sango_strategy_enqueue_order(&order_kind);
            sango_city_remove_character(city_index, actor_or_error_text);
        }
        actor_or_error_text = 0x3b;
    }
    sango_ui_show_strategy_text(actor_or_error_text);
    return 1;
}
#undef order_kind
#undef order_actor
#undef order_city
#undef order_months

/* 原函数 0x81c0e38c */
uint32_t sango_city_order_recruit_captive(uint8_t city_id)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define order_kind (*(uint8_t *)(abi_storage + 0))
#define order_actor (*(uint8_t *)(abi_storage + 1))
#define order_city (*(uint8_t *)(abi_storage + 2))
#define order_target (*(char *)(abi_storage + 3))
#define order_months (*(uint8_t *)(abi_storage + 11))

    char captive_id;
    uint32_t city_index;
    char *roster;
    char *message;
    uint32_t count_or_captive_selection;
    uint32_t actor_selection_or_allowed;
    uint8_t actor_or_error_text;

    roster = g_scratch_buffer_address;
    city_index = (uint32_t)city_id;
    count_or_captive_selection =
        sango_city_list_idle_characters(city_index, (int)g_scratch_buffer_address);
    actor_or_error_text = 0x54;
    if (count_or_captive_selection != 0)
    {
    choose_captive:
        count_or_captive_selection = sango_city_list_captives(city_index, (int)roster);
        if (count_or_captive_selection != 0)
        {
            sango_strategy_present();
            count_or_captive_selection = sango_ui_select_character(
                (int)roster, count_or_captive_selection, 4, 2, 0xeb, 0x3d);
            if (count_or_captive_selection == 0xff)
            {
                return 1;
            }
            captive_id = roster[count_or_captive_selection];
            count_or_captive_selection = sango_city_list_idle_characters(city_index, (int)roster);
            if (count_or_captive_selection == 0)
            {
                return 1;
            }
            while (true)
            {
                sango_strategy_present();
                actor_selection_or_allowed = sango_ui_select_character(
                    (int)roster, count_or_captive_selection, 4, 2, 0xeb, 0x3d);
                if (actor_selection_or_allowed == 0xff)
                    break;
                actor_or_error_text = roster[actor_selection_or_allowed];
                actor_selection_or_allowed =
                    sango_character_can_pay_action((uint32_t)actor_or_error_text, 6);
                if (actor_selection_or_allowed != 0)
                {
                    sango_character_pay_action((uint32_t)actor_or_error_text, 6);
                    order_kind = 6;
                    order_months = 0;
                    order_actor = actor_or_error_text;
                    order_city = city_id;
                    order_target = captive_id;
                    sango_strategy_enqueue_order(&order_kind);
                    sango_city_remove_character(city_index, actor_or_error_text);
                    message = g_scratch_buffer_address;
                    sango_resource_read_text(0x40, 0xa2, g_scratch_buffer_address);
                    sango_strategy_present();
                    sango_ui_show_character_message(actor_or_error_text, message);
                    break;
                }
                sango_ui_show_strategy_text(0x3c);
            }
            goto choose_captive;
        }
        actor_or_error_text = 0x58;
    }
    sango_ui_show_strategy_text(actor_or_error_text);
    return 1;
}
#undef order_kind
#undef order_actor
#undef order_city
#undef order_target
#undef order_months

/* 原函数 0x81c0e53c */
uint32_t sango_city_order_execute_captive(uint32_t city_id)
{
    char second_item_id;
    uint32_t selection_or_message_roll;
    int roster_or_character_address;
    char *message;
    uint8_t *selected_captive;
    uint32_t city_index;

    roster_or_character_address = g_scratch_buffer_address;
    city_index = city_id & 0xff;
    selection_or_message_roll = sango_city_list_captives(city_index, g_scratch_buffer_address);
    if (selection_or_message_roll == 0)
    {
        sango_ui_show_strategy_text(0x58);
    }
    selection_or_message_roll = sango_ui_select_character(
        roster_or_character_address, selection_or_message_roll, 4, 2, 0xeb, 0x3d);
    selected_captive = (uint8_t *)(roster_or_character_address + selection_or_message_roll);
    if (selection_or_message_roll != 0xff)
    {
        roster_or_character_address =
            g_character_table_address + (uint32_t)*selected_captive * 0x10;
        if (*(char *)(roster_or_character_address + 0xc) == '\0')
        {
            second_item_id = *(char *)(roster_or_character_address + 0xd);
        }
        else
        {
            sango_city_add_item(city_index, *(char *)(roster_or_character_address + 0xc) - 1);
            sango_item_mark_discovered(*(char *)(roster_or_character_address + 0xc) - 1);
            second_item_id = *(char *)(roster_or_character_address + 0xd);
        }
        if (second_item_id != '\0')
        {
            sango_city_add_item(city_index, second_item_id - 1);
            sango_item_mark_discovered(*(char *)(roster_or_character_address + 0xd) - 1);
        }
        message = (char *)(g_scratch_buffer_address + 300);
        selection_or_message_roll = bbk_rand();
        sango_resource_read_text(0x40, (int)selection_or_message_roll % 3 + 0x7dU & 0xff, message);
        sango_strategy_present();
        sango_ui_show_character_message(*selected_captive, message);
        sango_city_remove_character(city_index, *selected_captive);
    }
    return 1;
}

/* 原函数 0x81c0e6c4 */
uint32_t sango_city_order_exile_character(uint32_t city_id)
{
    uint8_t character_id;
    char original_owner;
    int roster_address;
    uint32_t count_selection_or_destination;
    uint32_t captive_or_faction_city_count;
    uint32_t city_index;
    int character_offset;

    roster_address = g_scratch_buffer_address;
    city_index = city_id & 0xff;
    count_selection_or_destination =
        sango_city_list_idle_characters(city_index, g_scratch_buffer_address);
    captive_or_faction_city_count =
        sango_city_list_captives(city_index, roster_address + count_selection_or_destination);
    count_selection_or_destination =
        count_selection_or_destination + captive_or_faction_city_count & 0xff;
    if (count_selection_or_destination == 0)
    {
        sango_ui_show_strategy_text(0x54);
    }
    else
    {
        count_selection_or_destination = sango_ui_select_character(
            roster_address, count_selection_or_destination, 4, 2, 0xeb, 0x3d);
        if (count_selection_or_destination != 0xff)
        {
            character_id = *(uint8_t *)(roster_address + count_selection_or_destination);
            character_offset = (uint32_t)character_id * 0x10;
            if ((uint32_t)g_player_character != (uint32_t)character_id)
            {
                *(uint8_t *)(character_offset + g_character_table_address + 1) = 0;
                count_selection_or_destination = bbk_rand();
                count_selection_or_destination = (int)count_selection_or_destination % 0x26 & 0xff;
                if (((((char *)(character_offset + g_character_table_address))[1] == -1) &&
                     (original_owner = *(char *)(character_offset + g_character_table_address),
                      original_owner != '\0')) &&
                    (captive_or_faction_city_count = sango_faction_list_cities(
                         (uint32_t)(uint8_t)(original_owner - 1), roster_address),
                     captive_or_faction_city_count != 0))
                {
                    ((uint8_t *)(character_offset + g_character_table_address))[1] =
                        *(uint8_t *)(character_offset + g_character_table_address);
                    count_selection_or_destination = bbk_rand();
                    if (captive_or_faction_city_count == 0)
                    {
                        sango_legacy_trap(7);
                    }
                    count_selection_or_destination =
                        (int)count_selection_or_destination % (int)captive_or_faction_city_count &
                        0xff;
                }
                sango_city_remove_character(city_index, character_id);
                sango_city_add_character(count_selection_or_destination, character_id);
                return 1;
            }
            sango_ui_show_message(&g_legacy_data_81c204d0, 2);
            return 0;
        }
    }
    return 1;
}

/* 原函数 0x81c0e87c */
uint32_t sango_city_order_reward(uint32_t city_id)
{
    uint8_t item_id;
    uint32_t item_selection_or_roll;
    uint32_t character_selection;
    int character_list_or_record;
    uint32_t item_effect_result;
    uint8_t character_or_message;
    uint8_t message_id;
    char *message;
    int item_ids_address;
    uint32_t city_index;
    int character_offset;
    int equipment_slot;

    city_index = city_id & 0xff;
    item_ids_address = g_scratch_buffer_address + 200;
    item_selection_or_roll = sango_city_list_items(city_index, item_ids_address);
    character_or_message = 0x56;
    if (item_selection_or_roll != 0)
    {
        item_selection_or_roll =
            sango_ui_select_item(item_ids_address, item_selection_or_roll, 4, 2, 0xeb, 0x3d);
        if (item_selection_or_roll == 0xff)
        {
            return 1;
        }
        while (true)
        {
            character_list_or_record = g_scratch_buffer_address;
            equipment_slot = 0;
            character_selection =
                sango_city_list_idle_characters(city_index, g_scratch_buffer_address);
            if (character_selection == 0)
                break;
            character_selection = sango_ui_select_character(character_list_or_record,
                                                            character_selection, 4, 2, 0xeb, 0x3d);
            if (character_selection == 0xff)
            {
                return 1;
            }
            character_or_message = *(uint8_t *)(character_list_or_record + character_selection);
            character_selection = (uint32_t)character_or_message;
            item_id = *(uint8_t *)(item_ids_address + item_selection_or_roll);
            character_offset = character_selection * 0x10;
            character_list_or_record = g_character_table_address + character_offset;
            if ((*(char *)(character_list_or_record + 0xc) == '\0') ||
                (equipment_slot = 1, *(char *)(character_list_or_record + 0xd) == '\0'))
            {
                item_effect_result =
                    sango_item_apply_attributes((uint32_t)item_id, character_selection);
                message_id = 0x6d;
                if (item_effect_result == 1)
                {
                finish_item_reward:
                    sango_city_remove_item(city_index, item_id);
                    if (g_player_character == character_selection)
                    {
                        sango_strategy_present();
                        sango_ui_show_character_message(character_or_message,
                                                        &g_legacy_data_81c204e0);
                        return 1;
                    }
                    message = (char *)(g_scratch_buffer_address + 300);
                    item_selection_or_roll = bbk_rand();
                    sango_resource_read_text(0x40, (int)item_selection_or_roll % 3 - 0x7dU & 0xff,
                                             message);
                    sango_strategy_present();
                    sango_ui_show_character_message(character_or_message, message);
                    *(char *)(character_offset + g_character_table_address + 5) =
                        *(char *)(character_offset + g_character_table_address + 5) + '\b';
                    if (*(uint8_t *)(character_offset + g_character_table_address + 5) < 0x65)
                    {
                        return 1;
                    }
                    *(uint8_t *)(character_offset + g_character_table_address + 5) = 100;
                    return 1;
                }
                if ((int)item_effect_result < 2)
                {
                    if (item_effect_result == 0)
                    {
                        *(uint8_t *)(character_list_or_record + 0xc + equipment_slot) = item_id + 1;
                    }
                    goto finish_item_reward;
                }
                if (item_effect_result != 0xff)
                    goto finish_item_reward;
            }
            else
            {
                message_id = 0x57;
            }
            sango_ui_show_strategy_text(message_id);
            sango_strategy_present();
        }
        character_or_message = 0x54;
    }
    sango_ui_show_strategy_text(character_or_message);
    return 1;
}

/* 原函数 0x81c0eb10 */
uint32_t sango_city_order_trade(uint8_t city_id)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define order_city (*(uint8_t *)(abi_storage + 18))
#define order_months (*(uint8_t *)(abi_storage + 27))
#define menu_text (*(char(*)[16])(abi_storage + 0))
#define menu_bounds (*(uint16_t(*)[4])(abi_storage + 32))
#define order_kind (*(uint8_t *)(abi_storage + 16))
#define order_character (*(uint8_t *)(abi_storage + 17))

    uint32_t city_index;
    int idle_ids_address;
    uint32_t selection;
    uint32_t updated_money;
    uint8_t character_id;
    uint8_t error_text_id;

    idle_ids_address = g_scratch_buffer_address;
    city_index = (uint32_t)city_id;
    do
    {
        while (true)
        {
            selection = sango_city_list_idle_characters(city_index, idle_ids_address);
            error_text_id = 0x54;
            if (selection == 0)
                goto report_unavailable_trade;
            sango_strategy_present();
            selection = sango_ui_select_character(idle_ids_address, selection, 4, 2, 0xeb, 0x3d);
            if (selection == 0xff)
            {
                return 1;
            }
            character_id = *(uint8_t *)(idle_ids_address + selection);
            selection = sango_character_can_pay_action((uint32_t)character_id, 0xb);
            if (selection != 0)
                break;
            sango_ui_show_strategy_text(0x3c);
        }
        sango_resource_read_text(0x40, 0x2e, menu_text);
        menu_bounds[0] = 0x77;
        menu_bounds[2] = 0x8f;
        menu_bounds[1] = 0xe;
        menu_bounds[3] = 0x26;
        selection = sango_ui_choose_option(menu_bounds, 0, menu_text);
    } while (selection == 0xff);
    if (selection == 0)
    {
        selection = sango_city_can_pay_command(city_index, 0xc);
        if (selection == 0)
        {
            error_text_id = 0x3b;
        report_unavailable_trade:
            sango_ui_show_strategy_text(error_text_id);
            return 1;
        }
        if (((uint16_t)(&g_first_city_money)[city_index * 0x12] / 5 != 0) &&
            (selection = sango_ui_input_food_amount(
                 1, (uint16_t)(&g_first_city_money)[city_index * 0x12] / 5),
             selection != 0xffff))
        {
            (&g_first_city_money)[city_index * 0x12] =
                (&g_first_city_money)[city_index * 0x12] + (short)selection * -5;
            (&g_first_city_food)[city_index * 0x12] =
                (short)selection + (&g_first_city_food)[city_index * 0x12];
        }
    }
    else if (selection == 1)
    {
        if ((uint16_t)(&g_first_city_food)[city_index * 0x12] == 0)
        {
            sango_ui_show_message(&g_legacy_data_81c20510, 2);
            return 1;
        }
        selection = sango_ui_input_food_amount(
            1, (uint32_t)(uint16_t)(&g_first_city_food)[city_index * 0x12]);
        if (selection != 0xffff)
        {
            updated_money = (selection & 0x7fff) * 2 +
                            (uint32_t)(uint16_t)(&g_first_city_money)[city_index * 0x12];
            (&g_first_city_food)[city_index * 0x12] =
                (&g_first_city_food)[city_index * 0x12] - (short)selection;
            (&g_first_city_money)[city_index * 0x12] = (short)updated_money;
            if (30000 < (updated_money & 0xffff))
            {
                (&g_first_city_money)[city_index * 0x12] = 30000;
            }
        }
    }
    sango_character_pay_action((uint32_t)character_id, 0xb);
    order_kind = 0xb;
    order_months = 0;
    order_character = character_id;
    order_city = city_id;
    sango_strategy_enqueue_order(&order_kind);
    sango_city_remove_character(city_index, character_id);
    return 1;
}
#undef order_city
#undef order_months
#undef menu_text
#undef menu_bounds
#undef order_kind
#undef order_character

/* 原函数 0x81c0ed78 */
uint32_t sango_city_order_banquet(uint32_t city_id)
{
    char *roster;
    char *message;
    uint32_t count_or_selection;
    uint8_t updated_stamina;
    uint8_t actor_or_error_text;
    int character_address;
    uint32_t city_index;

    roster = g_scratch_buffer_address;
    city_index = city_id & 0xff;
    count_or_selection = sango_city_list_idle_characters(city_index, (int)g_scratch_buffer_address);
    actor_or_error_text = 0x54;
    if (count_or_selection != 0)
    {
        while (count_or_selection = sango_city_can_pay_command(city_index, 0xc),
               count_or_selection != 0)
        {
            sango_strategy_present();
            count_or_selection = sango_city_list_idle_characters(city_index, (int)roster);
            if (count_or_selection == 0)
            {
                return 1;
            }
            count_or_selection =
                sango_ui_select_character((int)roster, count_or_selection, 4, 2, 0xeb, 0x3d);
            if (count_or_selection == 0xff)
            {
                return 1;
            }
            actor_or_error_text = roster[count_or_selection];
            character_address = g_character_table_address + (uint32_t)actor_or_error_text * 0x10;
            sango_city_pay_command(city_index, 0xc);
            updated_stamina = *(char *)(character_address + 8) + 0x32;
            *(uint8_t *)(character_address + 8) = updated_stamina;
            if (100 < updated_stamina)
            {
                *(uint8_t *)(character_address + 8) = 100;
            }
            message = g_scratch_buffer_address;
            if ((uint32_t)g_player_character == (uint32_t)actor_or_error_text)
            {
                sango_strategy_present();
                sango_ui_show_character_message(actor_or_error_text, &g_legacy_data_81c2051c);
            }
            else
            {
                sango_resource_read_text(0x40, 0xa1, g_scratch_buffer_address);
                sango_strategy_present();
                sango_ui_show_character_message(actor_or_error_text, message);
                if (*(uint8_t *)(character_address + 5) < 100)
                {
                    *(uint8_t *)(character_address + 5) = *(uint8_t *)(character_address + 5) + 1;
                }
            }
        }
        actor_or_error_text = 0x3b;
    }
    sango_ui_show_strategy_text(actor_or_error_text);
    return 1;
}

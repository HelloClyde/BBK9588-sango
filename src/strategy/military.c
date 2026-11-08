#include "sango_internal.h"

/* 军事行动、出征编队与进入战斗。 */

/* 原函数 0x81c0ef00 */
uint32_t sango_city_order_transport(uint32_t city_id)
{
    unsigned char abi_storage[52] __attribute__((aligned(8)));
#define source_city (*(uint32_t *)(abi_storage + 16))
#define idle_ids_address (*(int *)(abi_storage + 20))
#define city_word_offset (*(int *)(abi_storage + 24))
#define city_byte_offset (*(int *)(abi_storage + 28))
#define source_byte_offset (*(int *)(abi_storage + 32))
#define order_kind (*(uint8_t *)(abi_storage + 0))
#define order_character (*(uint8_t *)(abi_storage + 1))
#define order_city (*(uint8_t *)(abi_storage + 2))
#define order_target (*(char *)(abi_storage + 3))
#define transport_troops (*(short *)(abi_storage + 4))
#define transport_food (*(short *)(abi_storage + 6))
#define transport_money (*(short *)(abi_storage + 8))
#define travel_months (*(uint8_t *)(abi_storage + 11))

    uint8_t source_map_x;
    uint8_t source_map_y;
    uint32_t selection;
    uint32_t route_months;
    uint8_t courier_argument;
    uint8_t message_id;
    uint32_t city_index;
    int input_step;
    char *message;
    uint32_t courier_id;

    city_index = city_id & 0xff;
    city_word_offset = city_index * 9;
    city_byte_offset = city_index * 0x24;
    idle_ids_address = g_scratch_buffer_address;
    /* 输入向导：选运输武将→粮食→金钱→兵力→目的城市；取消退回上一步。 */
    enum
    {
        CHOOSE_COURIER = 0,
        INPUT_FOOD = 1,
        INPUT_MONEY = 2,
        INPUT_TROOPS = 3,
        CHOOSE_DESTINATION = 4
    };
    input_step = CHOOSE_COURIER;
    source_city = city_index;
resume_transport_input:
    do
    {
        if (input_step == CHOOSE_COURIER)
            goto choose_courier;
        while (true)
        {
            while (true)
            {
                while (true)
                {
                    while (source_map_y = g_strategy_cursor_y, source_map_x = g_strategy_cursor_x,
                           input_step == INPUT_FOOD)
                    {
                        input_step = INPUT_MONEY;
                        selection = sango_ui_input_food_amount(
                            0, (uint32_t)(uint16_t)(&g_first_city_food)[city_index * 0x12]);
                        transport_food = (short)selection;
                        if (selection == 0xffff)
                        {
                        choose_courier:
                            while (true)
                            {
                                selection =
                                    sango_city_list_idle_characters(source_city, idle_ids_address);
                                if (selection == 0)
                                {
                                    sango_ui_show_strategy_text(0x54);
                                    return 1;
                                }
                                sango_strategy_present();
                                selection = sango_ui_select_character(idle_ids_address, selection,
                                                                      4, 2, 0xeb, 0x3d);
                                if (selection == 0xff)
                                {
                                    return 1;
                                }
                                input_step = INPUT_FOOD;
                                courier_id = (uint32_t) * (uint8_t *)(idle_ids_address + selection);
                                selection = sango_character_can_pay_action(courier_id, 0xd);
                                if (selection != 0)
                                    break;
                                sango_ui_show_strategy_text(0x3c);
                            }
                        }
                    }
                    if (input_step != INPUT_MONEY)
                        break;
                    input_step = INPUT_FOOD;
                    selection = sango_ui_input_money_amount(
                        0, (uint32_t) * (uint16_t *)((int)&g_first_city_money + city_byte_offset));
                    if (selection != 0xffff)
                    {
                        input_step = INPUT_TROOPS;
                    }
                    transport_money = (short)selection;
                }
                if (input_step != INPUT_TROOPS)
                    break;
                input_step = INPUT_MONEY;
                selection = sango_ui_input_troop_amount(
                    0, (uint32_t)(uint16_t)(&g_first_city_reserve_troops)[city_index * 0x12]);
                if (selection != 0xffff)
                {
                    input_step = CHOOSE_DESTINATION;
                }
                transport_troops = (short)selection;
            }
            if (input_step != CHOOSE_DESTINATION)
                goto resume_transport_input;
            message = (char *)(g_scratch_buffer_address + 300);
            sango_resource_read_text(0x40, 0x5d, message);
            sango_strategy_present();
            courier_argument = (uint8_t)courier_id;
            sango_ui_show_character_message(courier_argument, message);
            selection = sango_strategy_select_city(&g_strategy_viewport_x);
            if (selection != 0xff)
                break;
            input_step = INPUT_TROOPS;
        }
        if (selection != source_city)
        {
            message_id = 0x38;
            if ((&g_first_city_owner)[selection * 0x24] != '\0')
            {
                source_byte_offset = city_word_offset * 4;
                message_id = 0x36;
                if ((&g_first_city_owner)[selection * 0x24] ==
                    (&g_first_city_owner)[source_byte_offset])
                {
                    route_months = sango_city_route_distance(
                        source_city, source_map_x, source_map_y, (char)selection,
                        g_strategy_cursor_x, g_strategy_cursor_y);
                    message_id = 0x37;
                    if (route_months != 0xff)
                    {
                        sango_character_pay_action(courier_id, 0xd);
                        *(short *)((int)&g_first_city_food + source_byte_offset) =
                            *(short *)((int)&g_first_city_food + source_byte_offset) -
                            transport_food;
                        *(short *)((int)&g_first_city_reserve_troops + source_byte_offset) =
                            *(short *)((int)&g_first_city_reserve_troops + source_byte_offset) -
                            transport_troops;
                        *(short *)((int)&g_first_city_money + source_byte_offset) =
                            *(short *)((int)&g_first_city_money + source_byte_offset) -
                            transport_money;
                        sango_resource_read_text(0x40, 0x98, message);
                        sango_ui_show_character_message(courier_argument, message);
                        order_kind = 0xd;
                        travel_months = (uint8_t)route_months;
                        order_city = (uint8_t)source_city;
                        order_character = courier_argument;
                        order_target = (char)selection;
                        sango_strategy_enqueue_order(&order_kind);
                        sango_city_remove_character(source_city, courier_argument);
                        return 1;
                    }
                }
            }
            sango_ui_show_strategy_text(message_id);
        }
    } while (true);
}
#undef source_city
#undef idle_ids_address
#undef city_word_offset
#undef city_byte_offset
#undef source_byte_offset
#undef order_kind
#undef order_character
#undef order_city
#undef order_target
#undef transport_troops
#undef transport_food
#undef transport_money
#undef travel_months

/* 原函数 0x81c0f244 */
uint32_t sango_city_order_transfer(uint8_t city_id)
{
    unsigned char abi_storage[36] __attribute__((aligned(8)));
#define order_kind (*(uint8_t *)(abi_storage + 0))
#define order_character (*(uint8_t *)(abi_storage + 1))
#define order_city (*(uint8_t *)(abi_storage + 2))
#define order_target (*(char *)(abi_storage + 3))
#define travel_months (*(uint8_t *)(abi_storage + 11))
#define source_city_record (*(uint8_t **)(abi_storage + 16))

    uint32_t city_index;
    bool has_character;
    int idle_ids_address;
    uint8_t source_map_x;
    uint8_t source_map_y;
    uint32_t selection;
    uint32_t route_months;
    uint8_t character_argument;
    uint8_t message_id;
    uint32_t character_id;
    char *message;

    idle_ids_address = g_scratch_buffer_address;
    city_index = (uint32_t)city_id;
    source_city_record = &g_first_city_status + city_index * 0x24;
    has_character = false;
    do
    {
        if (!has_character)
            goto choose_character;
        while (source_map_y = g_strategy_cursor_y, source_map_x = g_strategy_cursor_x,
               has_character)
        {
            message = (char *)(g_scratch_buffer_address + 300);
            sango_resource_read_text(0x40, 0x5d, message);
            sango_strategy_present();
            character_argument = (uint8_t)character_id;
            sango_ui_show_character_message(character_argument, message);
            selection = sango_strategy_select_city(&g_strategy_viewport_x);
            if (selection != 0xff)
            {
                if (selection != city_index)
                {
                    if ((&g_first_city_owner)[selection * 0x24] == '\0')
                    {
                        sango_ui_show_strategy_text(0x38);
                    validate_transfer_route:
                        route_months = sango_city_route_distance(
                            city_index, source_map_x, source_map_y, (char)selection,
                            g_strategy_cursor_x, g_strategy_cursor_y);
                        message_id = 0x37;
                        if (route_months != 0xff)
                        {
                            sango_character_pay_action(character_id, 0xd);
                            sango_resource_read_text(0x40, 0x98, message);
                            sango_ui_show_character_message(character_argument, message);
                            order_kind = 0xe;
                            travel_months = (uint8_t)route_months;
                            order_character = character_argument;
                            order_city = city_id;
                            order_target = (char)selection;
                            sango_strategy_enqueue_order(&order_kind);
                            sango_city_remove_character(city_index, character_argument);
                            return 1;
                        }
                    }
                    else
                    {
                        message_id = 0x36;
                        if ((&g_first_city_owner)[selection * 0x24] == source_city_record[1])
                            goto validate_transfer_route;
                    }
                    sango_ui_show_strategy_text(message_id);
                }
                break;
            }
        choose_character:
            while (true)
            {
                selection = sango_city_list_idle_characters(city_index, idle_ids_address);
                if (selection == 0)
                {
                    sango_ui_show_strategy_text(0x54);
                    return 1;
                }
                sango_strategy_present();
                selection =
                    sango_ui_select_character(idle_ids_address, selection, 4, 2, 0xeb, 0x3d);
                if (selection == 0xff)
                {
                    return 1;
                }
                character_id = (uint32_t) * (uint8_t *)(idle_ids_address + selection);
                has_character = true;
                selection = sango_character_can_pay_action(character_id, 0xe);
                if (selection != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
        }
    } while (true);
}
#undef order_kind
#undef order_character
#undef order_city
#undef order_target
#undef travel_months
#undef source_city_record

/* 原函数 0x81c0f49c */
uint32_t sango_city_order_sow_discord(uint8_t city_id)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define order_months (*(uint8_t *)(abi_storage + 11))
#define order_kind (*(uint8_t *)(abi_storage + 0))
#define order_actor (*(uint8_t *)(abi_storage + 1))
#define order_city (*(uint8_t *)(abi_storage + 2))
#define order_target (*(uint8_t *)(abi_storage + 3))

    uint32_t city_index;
    int roster_address;
    uint32_t count_or_selection;
    uint32_t actor_can_pay;
    uint8_t actor_or_error_text;

    city_index = (uint32_t)city_id;
    count_or_selection = sango_city_can_pay_command(city_index, 0xf);
    roster_address = g_scratch_buffer_address;
    actor_or_error_text = 0x3b;
    if (count_or_selection == 0)
    {
    show_command_error:
        sango_ui_show_strategy_text(actor_or_error_text);
    }
    else
    {
        do
        {
            while (true)
            {
                count_or_selection = sango_city_list_idle_characters(city_index, roster_address);
                if (count_or_selection == 0)
                {
                    actor_or_error_text = 0x54;
                    goto show_command_error;
                }
                sango_strategy_present();
                count_or_selection =
                    sango_ui_select_character(roster_address, count_or_selection, 4, 2, 0xeb, 0x3d);
                if (count_or_selection == 0xff)
                {
                    return 1;
                }
                actor_can_pay = sango_character_can_pay_action(
                    (uint32_t) * (uint8_t *)(roster_address + count_or_selection), 0xf);
                if (actor_can_pay != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
            actor_or_error_text = *(uint8_t *)(roster_address + count_or_selection);
            count_or_selection =
                sango_city_list_enemy_neighbors((uint32_t)g_player_character, roster_address);
            sango_strategy_present();
            count_or_selection =
                sango_ui_select_character(roster_address, count_or_selection, 4, 2, 0xeb, 0x3d);
        } while (count_or_selection == 0xff);
        sango_character_pay_action((uint32_t) * (uint8_t *)(roster_address + count_or_selection),
                                   0xf);
        sango_city_pay_command(city_index, 0xf);
        order_kind = 0xf;
        order_target = *(uint8_t *)(roster_address + count_or_selection);
        order_months = 10;
        order_actor = actor_or_error_text;
        order_city = city_id;
        sango_strategy_enqueue_order(&order_kind);
        sango_city_remove_character(city_index, actor_or_error_text);
    }
    return 1;
}
#undef order_months
#undef order_kind
#undef order_actor
#undef order_city
#undef order_target

/* 原函数 0x81c0f61c */
uint32_t sango_city_order_recruit_enemy(uint8_t city_id)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define order_kind (*(uint8_t *)(abi_storage + 0))
#define order_actor (*(uint8_t *)(abi_storage + 1))
#define order_city (*(uint8_t *)(abi_storage + 2))
#define order_target (*(uint8_t *)(abi_storage + 3))
#define order_months (*(uint8_t *)(abi_storage + 11))

    uint32_t city_index;
    int roster_address;
    uint32_t count_or_selection;
    uint8_t actor_or_error_text;

    city_index = (uint32_t)city_id;
    count_or_selection = sango_city_can_pay_command(city_index, 0x10);
    roster_address = g_scratch_buffer_address;
    actor_or_error_text = 0x3b;
    if (count_or_selection == 0)
    {
    show_command_error:
        sango_ui_show_strategy_text(actor_or_error_text);
    }
    else
    {
        do
        {
            while (true)
            {
                count_or_selection = sango_city_list_idle_characters(city_index, roster_address);
                if (count_or_selection == 0)
                {
                    actor_or_error_text = 0x54;
                    goto show_command_error;
                }
                sango_strategy_present();
                count_or_selection =
                    sango_ui_select_character(roster_address, count_or_selection, 4, 2, 0xeb, 0x3d);
                if (count_or_selection == 0xff)
                {
                    return 1;
                }
                actor_or_error_text = *(uint8_t *)(roster_address + count_or_selection);
                count_or_selection =
                    sango_character_can_pay_action((uint32_t)actor_or_error_text, 0x10);
                if (count_or_selection != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
            count_or_selection =
                sango_city_list_enemy_neighbors((uint32_t)g_player_character, roster_address);
            sango_strategy_present();
            count_or_selection =
                sango_ui_select_character(roster_address, count_or_selection, 4, 2, 0xeb, 0x3d);
        } while (count_or_selection == 0xff);
        sango_character_pay_action((uint32_t)actor_or_error_text, 0x10);
        sango_city_pay_command(city_index, 0x10);
        order_kind = 0x10;
        order_target = *(uint8_t *)(roster_address + count_or_selection);
        order_months = 10;
        order_actor = actor_or_error_text;
        order_city = city_id;
        sango_strategy_enqueue_order(&order_kind);
        sango_city_remove_character(city_index, actor_or_error_text);
    }
    return 1;
}
#undef order_kind
#undef order_actor
#undef order_city
#undef order_target
#undef order_months

/* 原函数 0x81c0f7a0 */
uint32_t sango_city_order_defection(uint8_t city_id)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define order_kind (*(uint8_t *)(abi_storage + 0))
#define order_actor (*(uint8_t *)(abi_storage + 1))
#define order_city (*(uint8_t *)(abi_storage + 2))
#define order_target (*(uint8_t *)(abi_storage + 3))
#define order_months (*(uint8_t *)(abi_storage + 11))

    uint32_t city_index;
    int roster_address;
    uint32_t count_or_selection;
    uint8_t actor_or_error_text;

    city_index = (uint32_t)city_id;
    count_or_selection = sango_city_can_pay_command(city_index, 0x11);
    roster_address = g_scratch_buffer_address;
    actor_or_error_text = 0x3b;
    if (count_or_selection == 0)
    {
    show_command_error:
        sango_ui_show_strategy_text(actor_or_error_text);
    }
    else
    {
        do
        {
            while (true)
            {
                count_or_selection = sango_city_list_idle_characters(city_index, roster_address);
                if (count_or_selection == 0)
                {
                    actor_or_error_text = 0x54;
                    goto show_command_error;
                }
                sango_strategy_present();
                count_or_selection =
                    sango_ui_select_character(roster_address, count_or_selection, 4, 2, 0xeb, 0x3d);
                if (count_or_selection == 0xff)
                {
                    return 1;
                }
                actor_or_error_text = *(uint8_t *)(roster_address + count_or_selection);
                count_or_selection =
                    sango_character_can_pay_action((uint32_t)actor_or_error_text, 0x11);
                if (count_or_selection != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
            count_or_selection =
                sango_city_list_enemy_rulers((uint32_t)g_player_character, roster_address);
            sango_strategy_present();
            if (count_or_selection == 0)
            {
                return 1;
            }
            sango_strategy_present();
            count_or_selection =
                sango_ui_select_character(roster_address, count_or_selection, 4, 2, 0xeb, 0x3d);
        } while (count_or_selection == 0xff);
        sango_character_pay_action((uint32_t)actor_or_error_text, 0x11);
        sango_city_pay_command(city_index, 0x11);
        order_kind = 0x11;
        order_target = *(uint8_t *)(roster_address + count_or_selection);
        order_months = 10;
        order_actor = actor_or_error_text;
        order_city = city_id;
        sango_strategy_enqueue_order(&order_kind);
        sango_city_remove_character(city_index, actor_or_error_text);
    }
    return 1;
}
#undef order_kind
#undef order_actor
#undef order_city
#undef order_target
#undef order_months

/* 原函数 0x81c0f934 */
uint32_t sango_city_order_demand_surrender(uint8_t city_id)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define order_kind (*(uint8_t *)(abi_storage + 0))
#define order_actor (*(uint8_t *)(abi_storage + 1))
#define order_city (*(uint8_t *)(abi_storage + 2))
#define order_target (*(uint8_t *)(abi_storage + 3))
#define order_months (*(uint8_t *)(abi_storage + 11))

    uint32_t city_index;
    uint8_t *roster;
    uint32_t count_or_selection;
    uint8_t actor_or_error_text;

    city_index = (uint32_t)city_id;
    count_or_selection = sango_city_can_pay_command(city_index, 0x13);
    roster = g_scratch_buffer_address;
    actor_or_error_text = 0x3b;
    if (count_or_selection == 0)
    {
    show_command_error:
        sango_ui_show_strategy_text(actor_or_error_text);
    }
    else
    {
        do
        {
            while (true)
            {
                count_or_selection = sango_city_list_idle_characters(city_index, (int)roster);
                if (count_or_selection == 0)
                {
                    actor_or_error_text = 0x54;
                    goto show_command_error;
                }
                sango_strategy_present();
                count_or_selection =
                    sango_ui_select_character((int)roster, count_or_selection, 4, 2, 0xeb, 0x3d);
                if (count_or_selection == 0xff)
                {
                    return 1;
                }
                actor_or_error_text = roster[count_or_selection];
                count_or_selection =
                    sango_character_can_pay_action((uint32_t)actor_or_error_text, 0x13);
                if (count_or_selection != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
            count_or_selection = sango_strategy_list_rulers((uint32_t)g_player_character, roster);
            sango_strategy_present();
            count_or_selection =
                sango_ui_select_character((int)roster, count_or_selection, 4, 2, 0xeb, 0x3d);
        } while (count_or_selection == 0xff);
        sango_character_pay_action((uint32_t)actor_or_error_text, 0x13);
        sango_city_pay_command(city_index, 0x13);
        order_kind = 0x13;
        order_target = roster[count_or_selection];
        order_months = 10;
        order_actor = actor_or_error_text;
        order_city = city_id;
        sango_strategy_enqueue_order(&order_kind);
        sango_city_remove_character(city_index, actor_or_error_text);
    }
    return 1;
}
#undef order_kind
#undef order_actor
#undef order_city
#undef order_target
#undef order_months

/* 原函数 0x81c0fab8 */
uint32_t sango_city_order_scout(uint8_t city_id)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define order_kind (*(uint8_t *)(abi_storage + 0))
#define order_actor (*(uint8_t *)(abi_storage + 1))
#define order_city (*(uint8_t *)(abi_storage + 2))
#define order_target (*(uint8_t *)(abi_storage + 3))
#define order_months (*(uint8_t *)(abi_storage + 11))

    uint32_t city_index;
    bool has_actor;
    int roster_address;
    uint32_t count_or_selection;
    uint8_t actor_or_error_text;
    char *destination_prompt;
    uint32_t actor_id;

    city_index = (uint32_t)city_id;
    count_or_selection = sango_city_can_pay_command(city_index, 0x17);
    roster_address = g_scratch_buffer_address;
    actor_or_error_text = 0x3b;
    if (count_or_selection == 0)
    {
    show_command_error:
        sango_ui_show_strategy_text(actor_or_error_text);
        return 1;
    }
    has_actor = false;
    do
    {
        if (!has_actor)
            goto choose_actor;
        while (has_actor)
        {
            destination_prompt = (char *)(g_scratch_buffer_address + 300);
            sango_resource_read_text(0x40, 0x5d, destination_prompt);
            sango_strategy_present();
            actor_or_error_text = (uint8_t)actor_id;
            sango_ui_show_character_message(actor_or_error_text, destination_prompt);
            count_or_selection = sango_strategy_select_city(&g_strategy_viewport_x);
            if (count_or_selection != 0xff)
            {
                if (count_or_selection != city_index)
                {
                    if ((&g_first_city_owner)[count_or_selection * 0x24] !=
                        (&g_first_city_owner)[city_index * 0x24])
                    {
                        sango_ui_show_city_details((uint8_t)count_or_selection);
                        sango_character_pay_action(actor_id, 0x17);
                        sango_city_pay_command(city_index, 0x17);
                        order_kind = 0x17;
                        order_actor = actor_or_error_text;
                        order_city = city_id;
                        order_target = (uint8_t)count_or_selection;
                        order_months = has_actor;
                        sango_strategy_enqueue_order(&order_kind);
                        sango_city_remove_character(city_index, actor_or_error_text);
                        return 1;
                    }
                    sango_ui_show_strategy_text(0x3a);
                }
                break;
            }
        choose_actor:
            while (true)
            {
                count_or_selection = sango_city_list_idle_characters(city_index, roster_address);
                if (count_or_selection == 0)
                {
                    actor_or_error_text = 0x54;
                    goto show_command_error;
                }
                sango_strategy_present();
                count_or_selection =
                    sango_ui_select_character(roster_address, count_or_selection, 4, 2, 0xeb, 0x3d);
                if (count_or_selection == 0xff)
                {
                    return 1;
                }
                actor_id = (uint32_t) * (uint8_t *)(roster_address + count_or_selection);
                has_actor = true;
                count_or_selection = sango_character_can_pay_action(actor_id, 0x17);
                if (count_or_selection != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
        }
    } while (true);
}
#undef order_kind
#undef order_actor
#undef order_city
#undef order_target
#undef order_months

/* 原函数 0x81c0fca4 */
uint32_t sango_city_order_recruit_troops(uint8_t city_id)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define order_kind (*(uint8_t *)(abi_storage + 0))
#define order_actor (*(uint8_t *)(abi_storage + 1))
#define order_city (*(uint8_t *)(abi_storage + 2))
#define order_months (*(uint8_t *)(abi_storage + 11))

    uint32_t city_index;
    int roster_address;
    uint32_t count_or_can_pay;
    uint32_t selection_or_troop_amount;
    uint8_t actor_or_error_text;
    uint32_t recruitment_limit;
    uint16_t *city_money_address;

    roster_address = g_scratch_buffer_address;
    city_index = (uint32_t)city_id;
    count_or_can_pay = sango_city_list_idle_characters(city_index, g_scratch_buffer_address);
    actor_or_error_text = 0x54;
    if (count_or_can_pay != 0)
    {
        while (count_or_can_pay = sango_city_can_pay_command(city_index, 0x18),
               count_or_can_pay != 0)
        {
            count_or_can_pay = sango_city_list_idle_characters(city_index, roster_address);
            if (count_or_can_pay == 0)
            {
                return 1;
            }
            do
            {
                while (true)
                {
                    sango_strategy_present();
                    selection_or_troop_amount = sango_ui_select_character(
                        roster_address, count_or_can_pay, 4, 2, 0xeb, 0x3d);
                    city_money_address = &g_first_city_money + city_index * 0x12;
                    if (selection_or_troop_amount == 0xff)
                    {
                        return 1;
                    }
                    actor_or_error_text = *(uint8_t *)(roster_address + selection_or_troop_amount);
                    selection_or_troop_amount =
                        sango_character_can_pay_action((uint32_t)actor_or_error_text, 0x18);
                    if (selection_or_troop_amount != 0)
                        break;
                    sango_ui_show_strategy_text(0x3c);
                }
                selection_or_troop_amount = (uint32_t)*city_money_address;
                if (selection_or_troop_amount < 0x1900)
                {
                    selection_or_troop_amount = selection_or_troop_amount * 10 & 0xffff;
                }
                recruitment_limit =
                    (uint32_t)(uint8_t)(&g_first_city_loyalty)[city_index * 0x24] * 0x14;
                if (selection_or_troop_amount <
                    (uint32_t)(uint8_t)(&g_first_city_loyalty)[city_index * 0x24] * 0x14)
                {
                    recruitment_limit = selection_or_troop_amount;
                }
                selection_or_troop_amount = sango_ui_input_troop_amount(0, recruitment_limit);
            } while (selection_or_troop_amount == 0xffff);
            (&g_first_city_reserve_troops)[city_index * 0x12] =
                (short)selection_or_troop_amount +
                (&g_first_city_reserve_troops)[city_index * 0x12];
            sango_character_pay_action((uint32_t)actor_or_error_text, 0x18);
            order_kind = 0x18;
            order_months = 0;
            *city_money_address = *city_money_address - (short)(selection_or_troop_amount / 10);
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

/* 原函数 0x81c0fe88 */
uint32_t sango_city_assign_troops(uint32_t city_id)
{
    bool has_selection;
    int roster_address;
    uint32_t roster_count_or_troop_amount;
    int character_address;
    uint32_t available_troops;
    uint32_t selected_row;
    int character_offset_or_address;
    uint32_t city_index;

    roster_address = g_scratch_buffer_address;
    city_index = city_id & 0xff;
    roster_count_or_troop_amount =
        sango_city_list_idle_characters(city_index, g_scratch_buffer_address);
    if (roster_count_or_troop_amount == 0)
    {
        sango_ui_show_strategy_text(0x54);
        return 1;
    }
    has_selection = false;
    do
    {
        if (has_selection)
            goto edit_troop_assignment;
        while (true)
        {
            roster_count_or_troop_amount =
                sango_city_list_idle_characters(city_index, roster_address);
            if (roster_count_or_troop_amount == 0)
            {
                return 1;
            }
            sango_strategy_present();
            selected_row = sango_ui_select_character(roster_address, roster_count_or_troop_amount,
                                                     4, 2, 0xeb, 0x3d);
            has_selection = true;
            if (selected_row == 0xff)
            {
                return 1;
            }
        edit_troop_assignment:
            if (!has_selection)
                break;
            character_offset_or_address =
                (uint32_t) * (uint8_t *)(roster_address + selected_row) * 0x10;
            character_address = character_offset_or_address + g_character_table_address;
            available_troops =
                (uint32_t)(uint16_t)(&g_first_city_reserve_troops)[city_index * 0x12] +
                (uint32_t) * (uint16_t *)(character_address + 10);
            roster_count_or_troop_amount = ((uint32_t) * (uint8_t *)(character_address + 2) * 10 +
                                            (uint32_t) * (uint8_t *)(character_address + 3) +
                                            (uint32_t) * (uint8_t *)(character_address + 4)) *
                                           10;
            if (available_troops < roster_count_or_troop_amount)
            {
                roster_count_or_troop_amount = available_troops;
            }
            if (roster_count_or_troop_amount == 0)
            {
                sango_ui_show_strategy_text(0x39);
            }
            else
            {
                roster_count_or_troop_amount =
                    sango_ui_input_troop_amount(0, roster_count_or_troop_amount & 0xffff);
                if (roster_count_or_troop_amount != 0xffff)
                {
                    character_offset_or_address =
                        character_offset_or_address + g_character_table_address;
                    (&g_first_city_reserve_troops)[city_index * 0x12] =
                        ((&g_first_city_reserve_troops)[city_index * 0x12] +
                         *(short *)(character_offset_or_address + 10)) -
                        (short)roster_count_or_troop_amount;
                    *(short *)(character_offset_or_address + 10) =
                        (short)roster_count_or_troop_amount;
                }
            }
        }
    } while (true);
}

/* 原函数 0x81c10020 */
uint32_t sango_city_order_counterintelligence(void)
{
    sango_ui_show_message(&g_legacy_data_81c20538, 2);
    return 1;
}

/* 原函数 0x81c10050 */
uint32_t sango_city_order_attack(uint8_t city_id)
{
    unsigned char abi_storage[44] __attribute__((aligned(8)));
#define army_character_ids (*(char(*)[16])(abi_storage + 0))
#define order_prefix (*(uint8_t(*)[2])(abi_storage + 16))
#define order_city (*(uint8_t *)(abi_storage + 18))
#define order_target (*(uint8_t *)(abi_storage + 19))
#define army_food (*(short *)(abi_storage + 22))
#define travel_months (*(uint8_t *)(abi_storage + 27))

    bool has_food;
    uint32_t city_index;
    char *scratch_text_or_ids;
    uint8_t source_map_x;
    uint8_t source_map_y;
    uint32_t selection;
    uint32_t route_months;
    uint8_t message_id;
    uint32_t army_size;

    city_index = (uint32_t)city_id;
    selection = sango_city_can_pay_command(city_index, 0x1b);
    source_map_y = g_strategy_cursor_y;
    source_map_x = g_strategy_cursor_x;
    scratch_text_or_ids = g_scratch_buffer_address;
    message_id = 0x3b;
    if (selection != 0)
    {
        selection = sango_city_list_idle_characters(city_index, (int)g_scratch_buffer_address);
        if (selection != 0)
        {
            sango_memory_fill(army_character_ids, 0, 10);
            army_size = 0;
            do
            {
                sango_strategy_present();
                selection = sango_ui_select_character((int)scratch_text_or_ids, selection, 4, 2,
                                                      0xeb, 0x3d);
                if (selection == 0xff)
                    break;
                army_character_ids[army_size] = scratch_text_or_ids[selection] + 1;
                sango_city_remove_character(city_index, scratch_text_or_ids[selection]);
                selection = sango_city_list_idle_characters(city_index, (int)scratch_text_or_ids);
                army_size = army_size + 1 & 0xff;
            } while (army_size < 10);
            if (army_size == 0)
            {
                return 1;
            }
            sango_strategy_present();
            selection = (uint32_t)(uint16_t)(&g_first_city_food)[city_index * 0x12];
            has_food = selection != 0;
            if (!has_food)
            {
                selection = 0;
            }
            selection = sango_ui_input_food_amount((uint32_t)has_food, selection);
            army_food = (short)selection;
            if ((short)selection != -1)
            {
                do
                {
                    do
                    {
                        scratch_text_or_ids = g_scratch_buffer_address;
                        sango_resource_read_text(0x40, 0x5d, g_scratch_buffer_address);
                        sango_strategy_present();
                        sango_ui_show_character_message(army_character_ids[0] + 0xff,
                                                        scratch_text_or_ids);
                        selection = sango_strategy_select_city(&g_strategy_viewport_x);
                        if (selection == 0xff)
                        {
                            while (army_size = army_size - 1 & 0xff, (army_size + 1 & 0xff) != 0)
                            {
                                sango_city_add_character(city_index,
                                                         army_character_ids[army_size] - 1);
                            }
                            return 1;
                        }
                    } while (selection == city_index);
                    message_id = 0x3a;
                    if ((&g_first_city_owner)[selection * 0x24] !=
                        (&g_first_city_owner)[city_index * 0x24])
                    {
                        route_months = sango_city_adjacent_distance(
                            city_index, source_map_x, source_map_y, selection, g_strategy_cursor_x,
                            g_strategy_cursor_y);
                        message_id = 0x37;
                        if (route_months != 0xff)
                        {
                            sango_ui_show_strategy_text(0x5e);
                            (&g_first_city_food)[city_index * 0x12] =
                                (&g_first_city_food)[city_index * 0x12] - army_food;
                            sango_city_pay_command(city_index, 0x1b);
                            order_prefix[0] = 0x1b;
                            order_target = (uint8_t)selection;
                            travel_months = (uint8_t)route_months;
                            order_city = city_id;
                            sango_strategy_queue_army(order_prefix, army_character_ids);
                            return 1;
                        }
                    }
                    sango_ui_show_strategy_text(message_id);
                } while (true);
            }
            while (army_size = army_size - 1 & 0xff, (army_size + 1 & 0xff) != 0)
            {
                sango_city_add_character(city_index, army_character_ids[army_size] - 1);
            }
            return 1;
        }
        message_id = 0x60;
    }
    sango_ui_show_strategy_text(message_id);
    return 1;
}
#undef army_character_ids
#undef order_prefix
#undef order_city
#undef order_target
#undef army_food
#undef travel_months

/* 原函数 0x81c10394 */
uint32_t sango_strategy_resolve_attack(int order_address)
{
    uint8_t selected_character;
    uint8_t defender_owner_id;
    uint8_t attacker_owner_id;
    uint8_t swap_character;
    uint32_t roster_count;
    uint8_t *marching_entry;
    uint8_t *roster_buffer;
    int character_table_base;
    uint32_t next_sort_index;
    uint8_t *roster_entry;
    uint32_t compare_index;
    uint32_t defender_index;
    uint32_t target_city;
    uint32_t last_defender_index;

    roster_buffer = g_scratch_buffer_address;
    *(uint8_t *)(g_army_slot_used_address + (uint32_t) * (uint8_t *)(order_address + 1)) = 0;
    roster_entry =
        (uint8_t *)((uint32_t) * (uint8_t *)(order_address + 1) * 10 + g_army_rosters_address);
    sango_memory_fill(&g_battle_roster_first, 0, 0x14);
    uint8_t target_city_id = *(uint8_t *)(order_address + 3);
    target_city = (uint32_t)target_city_id;
    defender_owner_id = (&g_first_city_owner)[target_city * 0x24];
    uint32_t defender_owner = (uint32_t)defender_owner_id;
    attacker_owner_id =
        *(uint8_t *)((uint32_t)*roster_entry * 0x10 + g_character_table_address + -0xf);
    uint32_t attacker_owner = (uint32_t)attacker_owner_id;
    sango_resource_read_text(2, 0xf, roster_buffer);
    g_battle_map_resource_view2 = roster_buffer[target_city] + 0x6e;
    uint32_t entry_direction =
        sango_city_neighbor_direction(target_city, (uint32_t) * (uint8_t *)(order_address + 2));
    g_battle_entry_direction = (uint8_t)entry_direction;
    sango_strategy_show_army_attack(attacker_owner_id - 1, target_city_id);
    /* 玩家防守：先选择守军，来犯军放入另一侧阵列。 */
    if (defender_owner == g_player_character + 1)
    {
        if (attacker_owner != defender_owner)
        {
            g_battle_attacker_food = (&g_first_city_food)[target_city * 0x12];
            g_battle_control_mode_view2 = 0;
            roster_count = 0;
            g_battle_defender_food = *(uint16_t *)(order_address + 6);
            do
            {
                defender_index = sango_city_list_idle_characters(target_city, (int)roster_buffer);
                sango_strategy_present();
                defender_index =
                    sango_ui_select_character((int)roster_buffer, defender_index, 4, 2, 0xeb, 0x3d);
                if (defender_index == 0xff)
                    break;
                (&g_battle_roster_first)[roster_count] = roster_buffer[defender_index] + 1;
                sango_city_remove_character(target_city, roster_buffer[defender_index]);
                roster_count = roster_count + 1 & 0xff;
            } while (roster_count < 10);
            bbk_memcpy(&g_battle_roster_second, roster_entry, 10);
            sango_battle_run();
            sango_strategy_finish_battle(target_city, g_battle_result);
            return 1;
        }
        roster_count = 0;
        roster_buffer = roster_entry;
        do
        {
            if (*roster_buffer != 0)
            {
                sango_city_add_character(target_city, *roster_buffer - 1);
            }
            roster_count = roster_count + 1 & 0xff;
            roster_buffer = roster_entry + roster_count;
        } while (roster_count < 10);
    }
    else
    {
        /* 玩家出征；空城和同势力城直接入城，否则选择电脑守军。 */
        if (attacker_owner == g_player_character + 1)
        {
            if (defender_owner != 0)
            {
                if (defender_owner == attacker_owner)
                {
                    roster_count = 0;
                    roster_buffer = roster_entry;
                    do
                    {
                        if (*roster_buffer != 0)
                        {
                            sango_city_add_character(target_city, *roster_buffer - 1);
                        }
                        sango_strategy_show_battle_victory(attacker_owner_id);
                        roster_count = roster_count + 1 & 0xff;
                        roster_buffer = roster_entry + roster_count;
                    } while (roster_count < 10);
                    return 1;
                }
                g_battle_control_mode_view2 = 1;
                g_battle_attacker_food = *(uint16_t *)(order_address + 6);
                g_battle_defender_food = (&g_first_city_food)[target_city * 0x12];
                bbk_memcpy(&g_battle_roster_first, roster_entry, 10);
                roster_count = sango_city_list_idle_characters(target_city, (int)roster_buffer);
                if (roster_count != 0)
                {
                    last_defender_index = roster_count - 1;
                    defender_index = 0;
                    if (0 < (int)last_defender_index)
                    {
                        next_sort_index = 1;
                        do
                        {
                            compare_index = next_sort_index & 0xff;
                            if (compare_index < roster_count)
                            {
                                character_table_base = g_character_table_address;
                                do
                                {
                                    roster_entry = roster_buffer + compare_index;
                                    selected_character = roster_buffer[defender_index];
                                    swap_character = *roster_entry;
                                    compare_index = compare_index + 1 & 0xff;
                                    if (*(uint16_t *)((uint32_t)selected_character * 0x10 +
                                                      character_table_base + 10) <
                                        *(uint16_t *)((uint32_t)swap_character * 0x10 +
                                                      character_table_base + 10))
                                    {
                                        *roster_entry = selected_character;
                                        roster_buffer[defender_index] = swap_character;
                                        character_table_base = g_character_table_address;
                                    }
                                    if (*(short *)((uint32_t)roster_buffer[roster_count - 1] *
                                                       0x10 +
                                                   character_table_base + 10) == 0)
                                    {
                                        roster_count = last_defender_index & 0xff;
                                        last_defender_index = roster_count - 1;
                                    }
                                } while (compare_index < roster_count);
                            }
                            defender_index = next_sort_index & 0xff;
                            next_sort_index = defender_index + 1;
                        } while ((int)defender_index < (int)last_defender_index);
                    }
                    if (roster_count == 0)
                    {
                        g_battle_roster_second = *roster_buffer + 1;
                        sango_city_remove_character(target_city, *roster_buffer);
                    }
                    else
                    {
                        if (10 < roster_count)
                        {
                            roster_count = 10;
                        }
                        defender_index = 0;
                        roster_entry = roster_buffer;
                        if (roster_count != 0)
                        {
                            do
                            {
                                sango_city_remove_character(target_city, *roster_entry);
                                (&g_battle_roster_second)[defender_index] = *roster_entry + 1;
                                defender_index = defender_index + 1 & 0xff;
                                roster_entry = roster_buffer + defender_index;
                            } while (defender_index < roster_count);
                        }
                    }
                }
                sango_battle_run();
                sango_strategy_finish_battle(target_city, g_battle_result);
                return 1;
            }
            roster_count = 0;
            do
            {
                if (roster_entry[roster_count] != 0)
                {
                    sango_city_add_character(target_city, roster_entry[roster_count] - 1);
                }
                roster_count = roster_count + 1 & 0xff;
            } while (roster_count < 10);
        }
        else
        {
            roster_count = 0;
            marching_entry = roster_entry;
            if (defender_owner != 0)
            {
                if (defender_owner == attacker_owner)
                {
                    roster_count = 0;
                    roster_buffer = roster_entry;
                    do
                    {
                        if (*roster_buffer != 0)
                        {
                            sango_city_add_character(target_city, *roster_buffer - 1);
                        }
                        roster_count = roster_count + 1 & 0xff;
                        roster_buffer = roster_entry + roster_count;
                    } while (roster_count < 10);
                    sango_strategy_show_battle_victory(attacker_owner_id);
                    return 1;
                }
                bbk_memcpy(&g_battle_roster_first, roster_entry, 10);
                roster_count = sango_city_list_idle_characters(target_city, (int)roster_buffer);
                if (roster_count != 0)
                {
                    last_defender_index = roster_count - 1;
                    defender_index = 0;
                    if (0 < (int)last_defender_index)
                    {
                        next_sort_index = 1;
                        do
                        {
                            compare_index = next_sort_index & 0xff;
                            if (compare_index < roster_count)
                            {
                                character_table_base = g_character_table_address;
                                do
                                {
                                    roster_entry = roster_buffer + compare_index;
                                    selected_character = roster_buffer[defender_index];
                                    swap_character = *roster_entry;
                                    compare_index = compare_index + 1 & 0xff;
                                    if (*(uint16_t *)((uint32_t)selected_character * 0x10 +
                                                      character_table_base + 10) <
                                        *(uint16_t *)((uint32_t)swap_character * 0x10 +
                                                      character_table_base + 10))
                                    {
                                        *roster_entry = selected_character;
                                        roster_buffer[defender_index] = swap_character;
                                        character_table_base = g_character_table_address;
                                    }
                                    if (*(short *)((uint32_t)roster_buffer[roster_count - 1] *
                                                       0x10 +
                                                   character_table_base + 10) == 0)
                                    {
                                        roster_count = last_defender_index & 0xff;
                                        last_defender_index = roster_count - 1;
                                    }
                                } while (compare_index < roster_count);
                            }
                            defender_index = next_sort_index & 0xff;
                            next_sort_index = defender_index + 1;
                        } while ((int)defender_index < (int)last_defender_index);
                    }
                    if (roster_count == 0)
                    {
                        g_battle_roster_second = *roster_buffer;
                        sango_city_remove_character(target_city, *roster_buffer);
                    }
                    else
                    {
                        if (10 < roster_count)
                        {
                            roster_count = 10;
                        }
                        defender_index = 0;
                        roster_entry = roster_buffer;
                        if (roster_count != 0)
                        {
                            do
                            {
                                sango_city_remove_character(target_city, *roster_entry);
                                (&g_battle_roster_second)[defender_index] = *roster_entry + 1;
                                defender_index = defender_index + 1 & 0xff;
                                roster_entry = roster_buffer + defender_index;
                            } while (defender_index < roster_count);
                        }
                    }
                }
                g_battle_control_mode_view2 = 2;
                g_battle_attacker_food = *(uint16_t *)(order_address + 6);
                g_battle_defender_food = (&g_first_city_food)[target_city * 0x12];
                sango_strategy_show_armies_engage(attacker_owner_id - 1, defender_owner_id - 1);
                sango_battle_run();
                sango_strategy_finish_battle(target_city, g_battle_result);
                return 1;
            }
            do
            {
                if (*marching_entry != 0)
                {
                    sango_city_add_character(target_city, *marching_entry - 1);
                }
                roster_count = roster_count + 1 & 0xff;
                marching_entry = roster_entry + roster_count;
            } while (roster_count < 10);
        }
        (&g_first_city_owner)[target_city * 0x24] = attacker_owner_id;
    }
    sango_strategy_show_battle_victory(attacker_owner_id);
    return 1;
}

/* 原函数 0x81c10a4c */
uint32_t sango_strategy_finish_battle(uint32_t city_id, char battle_result)
{
    uint16_t previous_agriculture;
    uint16_t previous_commerce;
    uint16_t previous_money;
    char *message;
    uint32_t roster_index_or_ruler;
    uint32_t city_index;
    uint32_t defeated_ruler;
    char *text_part;

    city_index = city_id & 0xff;
    g_capture_count = 0;
    defeated_ruler = 0xff;
    if (battle_result == '\x01')
    {
        roster_index_or_ruler = 0;
        do
        {
            if ((&g_battle_roster_first)[roster_index_or_ruler] != '\0')
            {
                sango_city_add_character(city_index,
                                         (&g_battle_roster_first)[roster_index_or_ruler] - 1);
            }
            roster_index_or_ruler = roster_index_or_ruler + 1 & 0xff;
        } while (roster_index_or_ruler < 10);
        sango_strategy_show_battle_victory(*(uint8_t *)((uint32_t)g_battle_roster_first * 0x10 +
                                                        g_character_table_address + -0xf));
        if ((uint8_t)(g_battle_control_mode - 1U) < 2)
        {
            defeated_ruler =
                sango_city_choose_postbattle_governor(g_battle_roster_first - 1, city_index);
        }
        roster_index_or_ruler =
            sango_strategy_handle_defeated_units(city_index, (char *)&g_battle_roster_second);
        if (roster_index_or_ruler != 0xff)
        {
            defeated_ruler = roster_index_or_ruler;
        }
    }
    else
    {
        roster_index_or_ruler = 10;
        if (battle_result == '\x02')
        {
            do
            {
                if ((&g_battle_roster_first)[roster_index_or_ruler] != '\0')
                {
                    sango_city_add_character(city_index,
                                             (&g_battle_roster_first)[roster_index_or_ruler] - 1);
                }
                roster_index_or_ruler = roster_index_or_ruler + 1 & 0xff;
            } while (roster_index_or_ruler < 0x14);
            if (g_battle_control_mode == '\0')
            {
                defeated_ruler =
                    sango_city_choose_postbattle_governor(g_battle_roster_second - 1, city_index);
            }
            roster_index_or_ruler =
                sango_strategy_handle_defeated_units(city_index, (char *)&g_battle_roster_first);
            if (roster_index_or_ruler != 0xff)
            {
                defeated_ruler = roster_index_or_ruler;
            }
            if (g_battle_control_mode == '\x02')
            {
                sango_strategy_show_battle_victory(
                    *(uint8_t *)((uint32_t)g_battle_roster_second * 0x10 +
                                 g_character_table_address + -0xf));
            }
            else
            {
                sango_strategy_show_battle_defeat();
                message = g_scratch_buffer_address;
                if (g_capture_count != 0)
                {
                    text_part = g_scratch_buffer_address + 0x28;
                    if (1 < g_capture_count)
                    {
                        g_capture_count = 2;
                    }
                    sango_load_named_text(g_captured_character, g_scratch_buffer_address);
                    sango_resource_read_text(0x40, g_capture_count + 0x69 & 0xff, text_part);
                    bbk_strcat(message, text_part);
                    sango_ui_show_message(message, 2);
                }
            }
        }
    }
    previous_agriculture = (&g_first_city_agriculture)[city_index * 0x12];
    previous_commerce = (&g_first_city_commerce)[city_index * 0x12];
    previous_money = (&g_first_city_money)[city_index * 0x12];
    (&g_first_city_loyalty)[city_index * 0x24] =
        (&g_first_city_loyalty)[city_index * 0x24] -
        (uint8_t)(&g_first_city_loyalty)[city_index * 0x24] / 10;
    (&g_first_city_agriculture)[city_index * 0x12] =
        previous_agriculture - previous_agriculture / 0x14;
    (&g_first_city_commerce)[city_index * 0x12] = previous_commerce - previous_commerce / 0x14;
    (&g_first_city_money)[city_index * 0x12] = previous_money - previous_money / 0x14;
    if (defeated_ruler != 0xff)
    {
        sango_strategy_resolve_ruler_succession((uint8_t)defeated_ruler);
    }
    (&g_first_city_food)[city_index * 0x12] =
        g_battle_attacker_food_view2 + g_battle_defender_food_view2;
    return 0;
}

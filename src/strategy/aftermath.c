#include "sango_internal.h"

/* 战后处理、君主继承和战斗事件提示。 */

/* 原函数 0x81c10d6c */
uint32_t sango_strategy_handle_defeated_units(uint32_t city_id, char *defeated_roster)
{
    char second_item_id;
    uint8_t index;
    uint32_t escape_roll;
    int escaped;
    char *source;
    char *roster_entry;
    uint32_t character_id;
    int character_address;
    uint32_t roster_index;
    uint32_t city_index;
    uint32_t defeated_ruler;
    char *destination;

    source = (char *)(g_scratch_buffer_address + 0x154);
    city_index = city_id & 0xff;
    defeated_ruler = 0xff;
    destination = (char *)(g_scratch_buffer_address + 300);
    roster_index = 0;
    roster_entry = defeated_roster;
    do
    {
        index = *roster_entry - 1;
        if (*roster_entry != '\0')
        {
            character_id = (uint32_t)index;
            character_address = g_character_table_address + character_id * 0x10;
            escape_roll = bbk_rand();
            escape_roll = (int)escape_roll % 100 & 0xff;
            if (*(uint8_t *)(character_address + 4) < escape_roll)
            {
                if (*(char *)(character_address + 1) == *roster_entry)
                {
                    defeated_ruler = character_id;
                }
            capture_character:
                sango_character_return_to_city(index, city_index);
            }
            else
            {
                escaped = sango_character_escape_to_friendly_city(index);
                if (escaped == 0)
                {
                    if (*(char *)(character_address + 1) == *roster_entry)
                    {
                        defeated_ruler = character_id;
                    }
                    if (escape_roll != 0)
                        goto capture_character;
                    if (*(char *)(character_address + 0xc) == '\0')
                    {
                        second_item_id = *(char *)(character_address + 0xd);
                    }
                    else
                    {
                        sango_city_add_item(city_index, *(char *)(character_address + 0xc) - 1);
                        sango_item_mark_discovered(*(char *)(character_address + 0xc) - 1);
                        second_item_id = *(char *)(character_address + 0xd);
                    }
                    if (second_item_id != '\0')
                    {
                        sango_city_add_item(city_index, second_item_id - 1);
                        sango_item_mark_discovered(*(char *)(character_address + 0xd) - 1);
                    }
                    if (g_battle_control_mode != '\x02')
                    {
                        sango_load_named_text(index, destination);
                        sango_resource_read_text(0x40, 0x6c, source);
                        bbk_strcat(destination, source);
                        sango_ui_show_message(destination, 2);
                    }
                }
            }
        }
        roster_index = roster_index + 1 & 0xff;
        roster_entry = defeated_roster + roster_index;
        if (9 < roster_index)
        {
            return defeated_ruler;
        }
    } while (true);
}

/* 原函数 0x81c10f78 */
void sango_character_return_to_city(uint8_t character_id, uint32_t city_id)
{
    uint8_t previous_owner;
    uint8_t *character_record;

    character_record = (uint8_t *)(g_character_table_address + (uint32_t)character_id * 0x10);
    previous_owner = character_record[1];
    character_record[1] = 0xff;
    *character_record = previous_owner;
    *(uint16_t *)(character_record + 10) = 0;
    g_capture_count_view2 = g_capture_count_view2 + '\x01';
    g_captured_character = character_id;
    sango_city_add_character(city_id & 0xff, character_id);
    return;
}

/* 原函数 0x81c10fdc */
uint32_t sango_character_escape_to_friendly_city(uint8_t character_id)
{
    int city_list_address;
    uint32_t city_count;
    uint32_t escaped;
    uint32_t random_roll;

    city_list_address = g_scratch_buffer_address;
    city_count = sango_faction_list_cities(
        *(uint8_t *)((uint32_t)character_id * 0x10 + g_character_table_address + 1) - 1 & 0xff,
        g_scratch_buffer_address);
    escaped = 0;
    if (city_count != 0)
    {
        random_roll = bbk_rand();
        if (city_count == 0)
        {
            sango_legacy_trap(7);
        }
        sango_city_add_character(
            (uint32_t) *
                (uint8_t *)(city_list_address + ((int)random_roll % (int)city_count & 0xffU)),
            character_id);
        escaped = 1;
    }
    return escaped;
}

/* 原函数 0x81c1107c */
uint32_t sango_city_choose_postbattle_governor(uint8_t governor_id, uint32_t city_id)
{
    uint8_t new_owner;
    uint8_t *roster;
    uint32_t roster_count;
    int city_offset;
    uint8_t *roster_entry;
    int character_table_or_record;
    uint32_t roster_index;
    uint32_t character_or_defeated_ruler;
    uint32_t previous_defeated_ruler;

    roster = g_scratch_buffer_address;
    roster_count = sango_city_list_idle_characters(city_id & 0xff, (int)g_scratch_buffer_address);
    character_table_or_record = g_character_table_address;
    new_owner = *(uint8_t *)((uint32_t)governor_id * 0x10 + g_character_table_address + 1);
    city_offset = (city_id & 0xff) * 0x24;
    (&g_first_city_governor)[city_offset] = governor_id + 1;
    (&g_first_city_owner)[city_offset] = new_owner;
    character_or_defeated_ruler = 0xff;
    roster_index = 0;
    roster_entry = roster;
    previous_defeated_ruler = character_or_defeated_ruler;
    if (roster_count != 0)
    {
        while (true)
        {
            character_or_defeated_ruler = (uint32_t)*roster_entry;
            character_table_or_record =
                character_table_or_record + character_or_defeated_ruler * 0x10;
            if ((uint32_t) * (uint8_t *)(character_table_or_record + 1) ==
                character_or_defeated_ruler + 1)
            {
                g_capture_count_view2 = g_capture_count_view2 + '\x01';
                g_captured_character = *roster_entry;
                *(uint8_t *)(character_table_or_record + 1) = 0xff;
            }
            else
            {
                *(uint8_t *)(character_table_or_record + 1) = 0;
                character_or_defeated_ruler = previous_defeated_ruler;
            }
            roster_index = roster_index + 1 & 0xff;
            *(uint16_t *)(character_table_or_record + 10) = 0;
            if (roster_count <= roster_index)
                break;
            roster_entry = roster + roster_index;
            character_table_or_record = g_character_table_address;
            previous_defeated_ruler = character_or_defeated_ruler;
        }
    }
    return character_or_defeated_ruler;
}

/* 原函数 0x81c11188 */
void sango_strategy_resolve_ruler_succession(uint8_t previous_ruler)
{
    unsigned char abi_storage[224] __attribute__((aligned(8)));
#define owner_name (*(uint8_t(*)[104])(abi_storage + 0))
#define character_name (*(uint8_t(*)[104])(abi_storage + 104))

    uint32_t city_count;
    uint32_t character_count;
    uint8_t successor_id;
    uint8_t *roster_entry;
    uint8_t *roster_cursor;
    uint32_t candidate_index;
    uint32_t roster_index;
    uint8_t *successor_entry;
    uint8_t *member_ids;

    uint32_t previous_ruler_id = (uint32_t)previous_ruler;
    sango_strategy_show_new_ruler(previous_ruler);
    roster_cursor = g_scratch_buffer_address;
    city_count = sango_faction_list_cities(previous_ruler_id, (int)g_scratch_buffer_address);
    member_ids = roster_cursor + 0x26;
    if (city_count == 0)
    {
        sango_strategy_show_faction_destroyed(previous_ruler);
    }
    else
    {
        character_count = sango_faction_list_characters(previous_ruler_id, (int)member_ids);
        if (character_count == 0)
        {
            sango_strategy_show_faction_destroyed(previous_ruler);
            roster_index = 0;
            member_ids = roster_cursor;
            if (city_count != 0)
            {
                do
                {
                    roster_index = roster_index + 1 & 0xff;
                    (&g_first_city_owner)[(uint32_t)*member_ids * 0x24] = 0;
                    member_ids = roster_cursor + roster_index;
                } while (roster_index < city_count);
            }
        }
        else
        {
            candidate_index = 1;
            if (g_player_character == previous_ruler_id)
            {
                sango_ui_show_strategy_text(0x50);
                do
                {
                    roster_index = sango_ui_select_character((int)member_ids, character_count, 4, 2,
                                                             0xeb, 0x3d);
                } while (roster_index == 0xff);
                successor_entry = member_ids + roster_index;
                g_player_character = *successor_entry;
                successor_id = *successor_entry;
            }
            else
            {
                successor_entry = member_ids;
                if (1 < character_count)
                {
                    do
                    {
                        roster_entry = member_ids + candidate_index;
                        candidate_index = candidate_index + 1 & 0xff;
                        if (*(uint8_t *)((uint32_t)*successor_entry * 0x10 +
                                         g_character_table_address + 4) <
                            *(uint8_t *)((uint32_t)*roster_entry * 0x10 +
                                         g_character_table_address + 4))
                        {
                            successor_entry = roster_entry;
                        }
                    } while (candidate_index < character_count);
                }
                successor_id = *successor_entry;
            }
            roster_index = 0;
            sango_strategy_show_ruler_changed(successor_id);
            *(uint8_t *)((uint32_t)*successor_entry * 0x10 + g_character_table_address + 5) = 100;
            roster_entry = roster_cursor;
            if (city_count != 0)
            {
                do
                {
                    roster_index = roster_index + 1 & 0xff;
                    (&g_first_city_owner)[(uint32_t)*roster_entry * 0x24] = *successor_entry + 1;
                    roster_entry = roster_cursor + roster_index;
                } while (roster_index < city_count);
            }
            roster_index = 0;
            if (character_count != 0)
            {
                roster_cursor = member_ids;
                do
                {
                    *(uint8_t *)((uint32_t)*roster_cursor * 0x10 + g_character_table_address + 1) =
                        *successor_entry + 1;
                    sango_load_named_text(
                        *(char *)((uint32_t)*roster_cursor * 0x10 + g_character_table_address + 1) +
                            0xff,
                        owner_name);
                    sango_load_named_text(*roster_cursor, character_name);
                    roster_index = roster_index + 1 & 0xff;
                    roster_cursor = member_ids + roster_index;
                } while (roster_index < character_count);
            }
        }
    }
    return;
}
#undef owner_name
#undef character_name

/* 原函数 0x81c11404 */
void sango_strategy_show_new_ruler(uint8_t ruler_id)
{
    char *source;
    char *destination;

    destination = (char *)(g_scratch_buffer_address + 300);
    source = (char *)(g_scratch_buffer_address + 0x154);
    sango_resource_read_text(0x40, 0x4e, destination);
    sango_load_named_text(ruler_id, source);
    bbk_strcat(destination, source);
    sango_resource_read_text(0x40, 0x4f, source);
    bbk_strcat(destination, source);
    sango_ui_show_message(destination, 2);
    return;
}

/* 原函数 0x81c11494 */
void sango_strategy_show_ruler_changed(uint8_t ruler_id)
{
    char *source;
    char *destination;

    destination = (char *)(g_scratch_buffer_address + 300);
    source = (char *)(g_scratch_buffer_address + 0x154);
    sango_load_named_text(ruler_id, destination);
    sango_resource_read_text(0x40, 0x51, source);
    bbk_strcat(destination, source);
    sango_ui_show_message(destination, 2);
    return;
}

/* 原函数 0x81c114fc */
void sango_strategy_show_faction_destroyed(uint8_t ruler_id)
{
    char *source;
    char *destination;

    destination = (char *)(g_scratch_buffer_address + 300);
    source = (char *)(g_scratch_buffer_address + 0x154);
    sango_load_named_text(ruler_id, destination);
    sango_resource_read_text(0x40, 0x53, source);
    bbk_strcat(destination, source);
    sango_ui_show_message(destination, 2);
    return;
}

/* 原函数 0x81c11564 */
uint32_t sango_strategy_queue_army(void *order_record, void *army_roster)
{
    char *dst;
    uint32_t army_slot_or_queue_index;

    army_slot_or_queue_index = 0;
    do
    {
        if (*(char *)(g_army_slot_used_address + army_slot_or_queue_index) == '\0')
        {
            *(char *)(g_army_slot_used_address + army_slot_or_queue_index) = '\x01';
            bbk_memcpy((void *)(army_slot_or_queue_index * 10 + g_army_rosters_address),
                       army_roster, 10);
            *(char *)((int)order_record + 1) = (char)army_slot_or_queue_index;
            army_slot_or_queue_index = 0x46;
            do
            {
                dst = (char *)(army_slot_or_queue_index * 0xc + g_order_queue_address);
                army_slot_or_queue_index = army_slot_or_queue_index + 1 & 0xff;
                if (*dst == -1)
                {
                    bbk_memcpy(dst, order_record, 0xc);
                    return 1;
                }
            } while (army_slot_or_queue_index < 100);
            return 1;
        }
        army_slot_or_queue_index = army_slot_or_queue_index + 1 & 0xff;
    } while (army_slot_or_queue_index < 100);
    return 0;
}

/* 原函数 0x81c11638 */
void sango_strategy_show_ruler_defection(uint8_t ruler_id)
{
    char *source;
    char *destination;

    destination = (char *)(g_scratch_buffer_address + 300);
    source = (char *)(g_scratch_buffer_address + 0x154);
    sango_load_named_text(ruler_id, destination);
    sango_resource_read_text(0x40, 0x52, source);
    bbk_strcat(destination, source);
    sango_ui_show_message(destination, 2);
    return;
}

/* 原函数 0x81c116a0 */
void sango_strategy_show_recruit_success(uint8_t character_id)
{
    char *message;

    message = (char *)(g_scratch_buffer_address + 300);
    sango_resource_read_text(0x40, 0x5f, message);
    sango_ui_show_character_message(character_id, message);
    return;
}

/* 原函数 0x81c116f0 */
uint32_t sango_strategy_enqueue_order(void *order_record)
{
    int order_stride_base;
    uint32_t order_index;
    char *dst;

    order_index = 0;
    order_stride_base = 0;
    do
    {
        dst = (char *)((order_stride_base + order_index) * 4 + g_order_queue_address);
        order_index = order_index + 1 & 0xff;
        if (*dst == -1)
        {
            bbk_memcpy(dst, order_record, 0xc);
            return 0;
        }
        order_stride_base = order_index << 1;
    } while (order_index < 100);
    return 1;
}

/* 原函数 0x81c11758 */
uint32_t sango_strategy_remove_order(void *order_record)
{
    int order_stride_base;
    uint32_t order_index;
    char *dst;

    order_index = 0x46;
    order_stride_base = 0x8c;
    do
    {
        dst = (char *)((order_stride_base + order_index) * 4 + g_order_queue_address);
        order_index = order_index + 1 & 0xff;
        if (*dst == -1)
        {
            bbk_memcpy(dst, order_record, 0xc);
            return 0;
        }
        order_stride_base = order_index << 1;
    } while (order_index < 100);
    return 1;
}

/* 原函数 0x81c117c0 */
uint32_t sango_strategy_queue_noop(uint8_t *order_record)
{
    *order_record = 0xff;
    return 1;
}

/* 原函数 0x81c117d0 */
uint32_t sango_city_order_confiscate(uint32_t city_id)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define equipped_item_ids (*(uint8_t(*)[8])(abi_storage + 0))

    bool first_slot_occupied;
    uint8_t character_id;
    int roster_address;
    uint32_t count_selection_or_character;
    uint32_t item_count_or_selection;
    uint32_t random_roll;
    int character_address;
    char *message;
    uint8_t *selected_item;
    char *equipment_slots;

    roster_address = g_scratch_buffer_address;
    while (true)
    {
        count_selection_or_character =
            sango_city_list_idle_characters(city_id & 0xff, roster_address);
        if (count_selection_or_character == 0)
        {
            sango_ui_show_strategy_text(0x54);
            return 1;
        }
        sango_strategy_present();
        count_selection_or_character = sango_ui_select_character(
            roster_address, count_selection_or_character, 4, 2, 0xeb, 0x3d);
        if (count_selection_or_character == 0xff)
            break;
        character_id = *(uint8_t *)(roster_address + count_selection_or_character);
        count_selection_or_character = (uint32_t)character_id;
        character_address = g_character_table_address + count_selection_or_character * 0x10;
        first_slot_occupied = *(char *)(character_address + 0xc) != '\0';
        equipment_slots = (char *)(character_address + 0xc);
        if (!first_slot_occupied)
        {
            *(uint8_t *)(character_address + 0xc) = *(uint8_t *)(character_address + 0xd);
            *(uint8_t *)(character_address + 0xd) = 0;
        }
        item_count_or_selection = (uint32_t)first_slot_occupied;
        if (equipment_slots[item_count_or_selection] != '\0')
        {
            item_count_or_selection = item_count_or_selection + 1;
        }
        equipped_item_ids[0] = *equipment_slots - 1;
        equipped_item_ids[1] = *(char *)(character_address + 0xd) + -1;
        if (item_count_or_selection == 0)
        {
            sango_ui_show_strategy_text(0x55);
        }
        else
        {
            sango_strategy_present();
            item_count_or_selection = sango_ui_select_item(
                (int)equipped_item_ids, item_count_or_selection, 4, 2, 0xeb, 0x3d);
            if (item_count_or_selection != 0xff)
            {
                if (g_player_character == count_selection_or_character)
                {
                    sango_strategy_present();
                    sango_ui_show_character_message(character_id, &g_legacy_data_81c20540);
                }
                else
                {
                    message = (char *)(g_scratch_buffer_address + 300);
                    random_roll = bbk_rand();
                    sango_resource_read_text(0x40, (int)random_roll % 3 - 0x80U & 0xff, message);
                    sango_strategy_present();
                    sango_ui_show_character_message(character_id, message);
                    character_address =
                        count_selection_or_character * 0x10 + g_character_table_address;
                    if (*(uint8_t *)(character_address + 5) < 0x14)
                    {
                        *(uint8_t *)(character_address + 5) = 0;
                    }
                    else
                    {
                        *(uint8_t *)(character_address + 5) =
                            *(uint8_t *)(character_address + 5) - 0x14;
                    }
                }
                selected_item = equipped_item_ids + item_count_or_selection;
                sango_city_add_item(city_id & 0xff, *selected_item);
                sango_item_mark_discovered(*selected_item);
                sango_item_remove_attributes((uint32_t)*selected_item,
                                             count_selection_or_character);
                equipment_slots[item_count_or_selection] = '\0';
            }
        }
    }
    return 1;
}
#undef equipped_item_ids

/* 原函数 0x81c11a2c */
uint32_t sango_city_order_plunder(uint8_t city_id)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define order_kind (*(uint8_t *)(abi_storage + 0))
#define order_actor (*(uint8_t *)(abi_storage + 1))
#define order_city (*(uint8_t *)(abi_storage + 2))
#define order_months (*(uint8_t *)(abi_storage + 11))

    uint8_t actor_id;
    int roster_address;
    uint32_t count_or_selection;
    char *message;

    roster_address = g_scratch_buffer_address;
    while (true)
    {
        count_or_selection = sango_city_list_idle_characters((uint32_t)city_id, roster_address);
        if (count_or_selection == 0)
        {
            sango_ui_show_strategy_text(0x54);
            return 1;
        }
        sango_strategy_present();
        count_or_selection =
            sango_ui_select_character(roster_address, count_or_selection, 4, 2, 0xeb, 0x3d);
        if (count_or_selection == 0xff)
            break;
        actor_id = *(uint8_t *)(roster_address + count_or_selection);
        count_or_selection = sango_character_can_pay_action((uint32_t)actor_id, 0x18);
        if (count_or_selection != 0)
        {
            sango_character_pay_action((uint32_t)actor_id, 0x18);
            message = (char *)(g_scratch_buffer_address + 300);
            sango_resource_read_text(0x40, 0x94, message);
            sango_ui_show_character_message(actor_id, message);
            order_kind = 0x1a;
            order_months = 0;
            order_actor = actor_id;
            order_city = city_id;
            sango_strategy_enqueue_order(&order_kind);
            sango_city_remove_character((uint32_t)city_id, actor_id);
            return 1;
        }
        sango_ui_show_strategy_text(0x3c);
    }
    return 1;
}
#undef order_kind
#undef order_actor
#undef order_city
#undef order_months

/* 原函数 0x81c11b50 */
uint32_t sango_character_can_pay_action(uint32_t character_id, uint32_t command_id)
{
    int action_costs_address;

    action_costs_address = sango_resource_item(2, '\n', g_resource_package_address);
    return (uint32_t)(*(uint8_t *)(action_costs_address + (command_id & 0xff)) <=
                      *(uint8_t *)((character_id & 0xff) * 0x10 + g_character_table_address + 8));
}

/* 原函数 0x81c11bbc */
void sango_character_pay_action(uint32_t character_id, uint32_t command_id)
{
    int action_costs_address;
    int character_address;

    action_costs_address = sango_resource_item(2, '\n', g_resource_package_address);
    character_address = (character_id & 0xff) * 0x10 + g_character_table_address;
    *(char *)(character_address + 8) =
        *(char *)(character_address + 8) - *(char *)(action_costs_address + (command_id & 0xff));
    return;
}

/* 原函数 0x81c11c28 */
uint32_t sango_city_find_weakest_target(uint32_t city_count, int city_ids_address)
{
    char order_kind;
    int city_or_order_stride;
    uint8_t *roster_entry;
    uint16_t city_troops;
    int character_address;
    uint32_t roster_or_order_index;
    uint16_t lowest_troops;
    char *order_record;
    uint32_t city_list_index;
    uint32_t weakest_city_index;

    lowest_troops = 0xffff;
    city_list_index = 0;
    if ((city_count & 0xff) != 0)
    {
        do
        {
            city_troops = 0;
            city_or_order_stride =
                (uint32_t) * (uint8_t *)(city_ids_address + city_list_index) * 0x24;
            roster_or_order_index = 0;
            if ((uint8_t)(&g_first_city_character_count)[city_or_order_stride] != 0)
            {
                roster_entry = &g_city_character_roster +
                               (uint8_t)(&g_first_city_character_start)[city_or_order_stride];
                do
                {
                    roster_or_order_index = roster_or_order_index + 1 & 0xff;
                    character_address = (uint32_t)*roster_entry * 0x10 + g_character_table_address;
                    if (*(char *)(character_address + 1) ==
                        (&g_first_city_owner)[city_or_order_stride])
                    {
                        city_troops = city_troops + *(short *)(character_address + 10);
                    }
                    roster_entry = &g_city_character_roster +
                                   (uint8_t)(&g_first_city_character_start)[city_or_order_stride] +
                                   roster_or_order_index;
                } while (roster_or_order_index <
                         (uint8_t)(&g_first_city_character_count)[city_or_order_stride]);
            }
            roster_or_order_index = 0;
            city_or_order_stride = 0;
            do
            {
                order_record = (char *)((city_or_order_stride + roster_or_order_index) * 4 +
                                        g_order_queue_address);
                order_kind = *order_record;
                roster_or_order_index = roster_or_order_index + 1 & 0xff;
                if ((((order_kind != -1) && (order_kind != '\x0e')) && (order_kind != '\x1b')) &&
                    (order_record[2] == *(uint8_t *)(city_ids_address + city_list_index)))
                {
                    city_troops =
                        city_troops + *(short *)((uint32_t)(uint8_t)order_record[1] * 0x10 +
                                                 g_character_table_address + 10);
                }
                city_or_order_stride = roster_or_order_index << 1;
            } while (roster_or_order_index < 100);
            if (city_troops < lowest_troops)
            {
                weakest_city_index = city_list_index;
                lowest_troops = city_troops;
            }
            city_list_index = city_list_index + 1 & 0xff;
        } while (city_list_index < (city_count & 0xff));
    }
    return (uint32_t) * (uint8_t *)(city_ids_address + weakest_city_index);
}

/* 原函数 0x81c11d98 */
void sango_strategy_show_army_attack(uint8_t ruler_id, char city_id)
{
    uint8_t *event_images;
    char *message;
    char *text_part;

    sango_ui_paint_begin();
    sango_display_fill_gray_rectangle(0x3b, 0x75, 0xb3, 0xc9, 0, 0);
    sango_display_draw_rectangle(0x3b, 0x75, 0xb3, 0xc9, 3, 0, 0);
    event_images = (uint8_t *)sango_resource_item(0x4c, '\x01', g_resource_package_address);
    sango_bitmap_draw_frame_screen(0x4d, 0x77, 0x54, 0x40, 0, event_images);
    message = (char *)(g_scratch_buffer_address + 300);
    text_part = (char *)(g_scratch_buffer_address + 0x154);
    if (g_player_character == ruler_id)
    {
        sango_resource_read_text(0x40, 0x62, message);
    }
    else
    {
        sango_load_named_text(ruler_id, message);
    }
    sango_resource_read_text(0x40, 0x61, text_part);
    bbk_strcat(message, text_part);
    sango_city_read_name(city_id, text_part);
    bbk_strcat(message, text_part);
    sango_text_draw_centered(0x77, 0xb9, message);
    sango_ui_paint_end();
    sango_input_wait(0x1e, '\0');
    sango_render_clear_rectangle(0x78, 0xd4, 0x9f, 0xef, g_game_context);
    sango_text_draw_context(0x78, 0xd4, text_part, g_game_context);
    return;
}

/* 原函数 0x81c11f18 */
void sango_strategy_show_armies_engage(uint8_t first_ruler, uint8_t second_ruler)
{
    uint8_t *event_images;
    char *text_part;
    char *message;

    sango_ui_paint_begin();
    sango_display_fill_gray_rectangle(0x3b, 0x75, 0xb3, 0xc9, 0, 0);
    sango_display_draw_rectangle(0x3b, 0x75, 0xb3, 0xc9, 3, 0, 0);
    event_images = (uint8_t *)sango_resource_item(0x4c, '\x01', g_resource_package_address);
    sango_bitmap_draw_frame_screen(0x4d, 0x77, 0x54, 0x40, 1, event_images);
    message = (char *)(g_scratch_buffer_address + 300);
    text_part = (char *)(g_scratch_buffer_address + 0x154);
    sango_load_named_text(first_ruler, message);
    sango_resource_read_text(0x40, 0x68, text_part);
    bbk_strcat(message, text_part);
    sango_load_named_text(second_ruler, text_part);
    bbk_strcat(message, text_part);
    sango_resource_read_text(0x40, 0x69, text_part);
    bbk_strcat(message, text_part);
    sango_text_draw_centered(0x77, 0xb9, message);
    sango_ui_paint_end();
    sango_input_wait(0x32, '\0');
    return;
}

/* 原函数 0x81c12058 */
void sango_strategy_show_battle_victory(uint8_t owner_id)
{
    uint8_t *event_images;
    char *message;
    char *text_part;

    sango_ui_paint_begin();
    sango_display_fill_gray_rectangle(0x3b, 0x75, 0xb3, 0xc9, 0, 0);
    sango_display_draw_rectangle(0x3b, 0x75, 0xb3, 0xc9, 3, 0, 0);
    event_images = (uint8_t *)sango_resource_item(0x4c, '\x01', g_resource_package_address);
    sango_bitmap_draw_frame_screen(0x4d, 0x77, 0x54, 0x40, 2, event_images);
    message = (char *)(g_scratch_buffer_address + 300);
    text_part = (char *)(g_scratch_buffer_address + 0x154);
    if ((uint32_t)owner_id == g_player_character + 1)
    {
        sango_resource_read_text(0x40, 0x62, message);
    }
    else
    {
        sango_load_named_text(owner_id - 1, message);
    }
    sango_resource_read_text(0x40, 0x5b, text_part);
    bbk_strcat(message, text_part);
    sango_text_draw_centered(0x77, 0xb9, message);
    sango_ui_paint_end();
    sango_input_wait(0x32, '\0');
    return;
}

/* 原函数 0x81c12188 */
void sango_strategy_show_battle_defeat(void)
{
    uint8_t *event_images;
    char *text_part;
    char *message;

    sango_ui_paint_begin();
    sango_display_fill_gray_rectangle(0x3b, 0x75, 0xb3, 0xc9, 0, 0);
    sango_display_draw_rectangle(0x3b, 0x75, 0xb3, 0xc9, 3, 0, 0);
    event_images = (uint8_t *)sango_resource_item(0x4c, '\x01', g_resource_package_address);
    sango_bitmap_draw_frame_screen(0x4d, 0x77, 0x54, 0x40, 3, event_images);
    message = (char *)(g_scratch_buffer_address + 300);
    text_part = (char *)(g_scratch_buffer_address + 0x154);
    sango_resource_read_text(0x40, 0x62, message);
    sango_resource_read_text(0x40, 0x5c, text_part);
    bbk_strcat(message, text_part);
    sango_text_draw_centered(0x77, 0xb9, message);
    sango_ui_paint_end();
    sango_input_wait(0x32, '\0');
    return;
}

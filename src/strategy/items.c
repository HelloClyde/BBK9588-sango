#include "sango_internal.h"

/* 宝物装备属性修改和数量统计。 */

/* 原函数 0x81c17a08 */
uint32_t sango_item_apply_attributes(uint32_t item_id, uint32_t character_id)
{
    uint8_t troop_conversion_kind;
    uint8_t converted_troop_type;
    int item_table_address;
    int item_address;
    int character_offset;

    item_table_address = sango_resource_item(0x42, '\x01', g_resource_package_address);
    character_offset = (character_id & 0xff) * 0x10;
    item_address = (item_id & 0xff) * 0x42 + item_table_address;
    *(char *)(character_offset + g_character_table_address + 3) =
        *(char *)(character_offset + g_character_table_address + 3) +
        *(char *)(item_address + 0x3e);
    *(char *)(character_offset + g_character_table_address + 4) =
        *(char *)(character_offset + g_character_table_address + 4) +
        *(char *)(item_address + 0x3f);
    troop_conversion_kind = *(uint8_t *)(item_address + 0x41);
    if (troop_conversion_kind == 2)
    {
        if (*(uint8_t *)(character_offset + g_character_table_address + 4) < 0x6a)
        {
            return 0xff;
        }
        converted_troop_type = 5;
    }
    else
    {
        if (troop_conversion_kind < 3)
        {
            if (troop_conversion_kind == 1)
            {
                *(uint8_t *)(character_offset + g_character_table_address + 9) = 3;
            }
            goto return_item_kind;
        }
        if (troop_conversion_kind != 3)
            goto return_item_kind;
        if (*(uint8_t *)(character_offset + g_character_table_address + 3) < 0x6a)
        {
            return 0xff;
        }
        converted_troop_type = 4;
    }
    *(uint8_t *)(character_offset + g_character_table_address + 9) = converted_troop_type;
return_item_kind:
    return (uint32_t) * (uint8_t *)((item_id & 0xff) * 0x42 + item_table_address + 1);
}

/* 原函数 0x81c17b3c */
uint32_t sango_faction_count_characters(uint32_t ruler_id)
{
    int order_stride_base;
    char *order_or_army_entry;
    char *army_roster;
    uint32_t army_slot;
    uint32_t order_index_or_idle_count;
    uint32_t character_count;

    character_count = 0;
    order_index_or_idle_count = 0;
    order_stride_base = 0;
    do
    {
        order_or_army_entry =
            (char *)((order_stride_base + order_index_or_idle_count) * 4 + g_order_queue_address);
        if ((*order_or_army_entry != -1) &&
            ((uint32_t)(uint8_t)(&g_first_city_owner)[(uint32_t)(uint8_t)order_or_army_entry[2] *
                                                      0x24] == (ruler_id & 0xff) + 1))
        {
            army_slot = 0;
            if (*order_or_army_entry == '\x1b')
            {
                army_roster = (char *)(g_army_rosters_address +
                                       (uint32_t)(uint8_t)order_or_army_entry[1] * 10);
                order_or_army_entry = army_roster;
                do
                {
                    army_slot = army_slot + 1 & 0xff;
                    if (*order_or_army_entry != '\0')
                    {
                        character_count = character_count + 1 & 0xff;
                    }
                    order_or_army_entry = army_roster + army_slot;
                } while (army_slot < 10);
            }
            else
            {
                character_count = character_count + 1 & 0xff;
            }
        }
        order_index_or_idle_count = order_index_or_idle_count + 1 & 0xff;
        order_stride_base = order_index_or_idle_count << 1;
    } while (order_index_or_idle_count < 100);
    order_index_or_idle_count =
        sango_faction_list_characters(ruler_id & 0xff, g_scratch_buffer_address);
    return character_count + order_index_or_idle_count & 0xff;
}

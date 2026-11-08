#include "sango_internal.h"

/* 城市事件、武将提示、宝物出现与属性消息。 */

/* 原函数 0x81c17c48 */
void sango_ui_show_city_event(uint8_t city_id, uint32_t unused_event_value,
                              uint32_t unused_event_aux, uint32_t status_text_fallback)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define governor_name (*(char(*)[16])(abi_storage + 16))
#define text_boxes (*(uint16_t(*)[8])(abi_storage + 0))

    char governor_one_based;
    uint8_t *portraits;
    char *status_destination;
    uint8_t governor_id;
    char *source;
    char *destination;

    governor_one_based = (&g_first_city_governor)[(uint32_t)city_id * 0x24];
    if (governor_one_based != '\0')
    {
        destination = (char *)(g_scratch_buffer_address + 300);
        source = (char *)(g_scratch_buffer_address + 0x154);
        sango_city_read_name(city_id, destination);
        status_destination = source;
        sango_resource_read_text(0x40, 0x6f, source);
        bbk_strcat(destination, source);
        sango_city_format_status((uint32_t)city_id, source, status_destination,
                                 status_text_fallback);
        bbk_strcat(destination, source);
        sango_resource_read_text(0x40, 0x70, source);
        bbk_strcat(destination, source);
        governor_id = governor_one_based - 1;
        sango_strategy_present();
        sango_display_fill_gray_rectangle(4, 0x10b, 0xea, 0x13b, 0, 0);
        sango_display_draw_rectangle(4, 0x10b, 0xea, 0x13a, 3, 0, 0);
        text_boxes[0] = 8;
        text_boxes[1] = 0x10b;
        text_boxes[2] = 0xe8;
        text_boxes[3] = 0x138;
        text_boxes[4] = 10;
        text_boxes[5] = 0x111;
        text_boxes[7] = 0x13b;
        text_boxes[6] = 0x3e;
        portraits = (uint8_t *)sango_resource_item(g_scenario_id_view2 + 0x2f, '\x01',
                                                   g_resource_package_address);
        sango_bitmap_draw_frame_screen(0x15, 0x111, 0x18, 0x18, governor_id, portraits);
        sango_load_named_text(governor_id, governor_name);
        sango_text_draw_centered(0x22, 299, governor_name);
        sango_text_draw_wrapped_box(text_boxes, text_boxes + 4, destination);
        sango_input_wait(100, '\x01');
    }
    return;
}
#undef governor_name
#undef text_boxes

/* 原函数 0x81c17e18 */
/* 按年份向城市宝物列表加入本剧本新出现的宝物。 */
uint32_t sango_strategy_spawn_items_for_year(void)
{
    uint8_t item_id;
    int debut_table_address;
    int item_added;
    uint32_t debut_offset;

    debut_table_address = sango_resource_item(0x43, g_scenario_id, g_resource_package_address);
    item_id = 0;
    debut_offset = 0;
    while ((*(uint8_t *)(debut_table_address + debut_offset) != g_current_year ||
            (item_added = sango_city_add_item(
                 (uint32_t)((uint8_t *)(debut_table_address + debut_offset))[2], item_id),
             item_added != 0)))
    {
        item_id = item_id + 1;
        debut_offset = debut_offset + 3 & 0xffff;
        if (199 < item_id)
        {
            return 0;
        }
    }
    return 0;
}

/* 原函数 0x81c17eb4 */
void sango_item_remove_attributes(uint32_t item_id, uint32_t character_id)
{
    int item_table_or_record;
    int character_address;
    int character_offset_or_address;

    item_table_or_record = sango_resource_item(0x42, '\x01', g_resource_package_address);
    character_offset_or_address = (character_id & 0xff) * 0x10;
    item_table_or_record = (item_id & 0xff) * 0x42 + item_table_or_record;
    character_address = character_offset_or_address + g_character_table_address;
    *(char *)(character_address + 3) =
        *(char *)(character_address + 3) - *(char *)(item_table_or_record + 0x3e);
    character_offset_or_address = character_offset_or_address + g_character_table_address;
    *(char *)(character_offset_or_address + 4) =
        *(char *)(character_offset_or_address + 4) - *(char *)(item_table_or_record + 0x3f);
    return;
}

/* 原函数 0x81c17f44 */
void sango_ui_show_strategy_text(uint8_t text_id)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define message (*(char(*)[24])(abi_storage + 0))

    sango_resource_read_text(0x40, (uint32_t)text_id, message);
    sango_ui_show_message(message, 2);
    return;
}
#undef message

/* 原函数 0x81c17f78 */
void sango_ui_draw_character_panel(short left, short top, uint8_t character_id)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define character_name (*(char(*)[16])(abi_storage + 0))

    uint8_t *portraits;

    portraits = (uint8_t *)sango_resource_item(g_scenario_id_view2 + 0x2f, '\x01',
                                               g_resource_package_address);
    sango_bitmap_draw_frame_screen(left + 0xd, top + 2, 0x18, 0x18, character_id, portraits);
    sango_load_named_text(character_id, character_name);
    sango_text_draw_centered(left + 0x1a, top + 0x1c, character_name);
    return;
}
#undef character_name

/* 原函数 0x81c18024 */
void sango_ui_show_character_message(uint8_t character_id, char *message)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define character_name (*(char(*)[16])(abi_storage + 16))
#define text_boxes (*(uint16_t(*)[8])(abi_storage + 0))

    uint8_t *portraits;

    sango_display_fill_gray_rectangle(4, 0x10b, 0xea, 0x13b, 0, 0);
    sango_display_draw_rectangle(4, 0x10b, 0xea, 0x13a, 3, 0, 0);
    text_boxes[0] = 8;
    text_boxes[1] = 0x10b;
    text_boxes[2] = 0xe8;
    text_boxes[3] = 0x138;
    text_boxes[4] = 10;
    text_boxes[5] = 0x111;
    text_boxes[7] = 0x13b;
    text_boxes[6] = 0x3e;
    portraits = (uint8_t *)sango_resource_item(g_scenario_id_view2 + 0x2f, '\x01',
                                               g_resource_package_address);
    sango_bitmap_draw_frame_screen(0x15, 0x111, 0x18, 0x18, character_id, portraits);
    sango_load_named_text(character_id, character_name);
    sango_text_draw_centered(0x22, 299, character_name);
    sango_text_draw_wrapped_box(text_boxes, text_boxes + 4, message);
    sango_input_wait(100, '\x01');
    return;
}
#undef character_name
#undef text_boxes

/* 原函数 0x81c18150 */
void sango_item_mark_discovered(uint8_t item_id)
{
    uint8_t roster_value;
    uint32_t roster_index;
    uint8_t *roster_entry;
    uint32_t total_items;

    total_items = (uint32_t)g_legacy_data_81c2b9a4 + (uint32_t)g_legacy_data_81c2b9a5 & 0xff;
    roster_index = 0;
    if (total_items != 0)
    {
        do
        {
            roster_entry = &g_city_item_roster + roster_index;
            roster_value = *roster_entry;
            roster_index = roster_index + 1 & 0xff;
            if ((roster_value & 0x7f) == item_id)
            {
                *roster_entry = roster_value | 0x80;
                return;
            }
        } while (roster_index < total_items);
    }
    return;
}

/* 原函数 0x81c181b8 */
uint32_t sango_city_list_items(uint32_t city_id, int destination_address)
{
    char *signed_roster_entry;
    uint8_t *roster_entry;
    uint8_t roster_index;
    int city_offset;
    uint32_t roster_position;
    uint8_t *destination_entry;
    uint32_t discovered_count;

    city_offset = (city_id & 0xff) * 0x24;
    discovered_count = 0;
    roster_position = (uint32_t)(uint8_t)(&g_first_city_item_start)[city_offset];
    roster_index = 0;
    if ((&g_first_city_item_count)[city_offset] != '\0')
    {
        do
        {
            signed_roster_entry = &g_city_item_roster + roster_position;
            roster_index = roster_index + 1;
            roster_entry = &g_city_item_roster + roster_position;
            destination_entry = (uint8_t *)(destination_address + discovered_count);
            roster_position = roster_position + 1 & 0xff;
            if (*signed_roster_entry < '\0')
            {
                discovered_count = discovered_count + 1 & 0xff;
                *destination_entry = *roster_entry & 0x7f;
            }
        } while (roster_index < (uint8_t)(&g_first_city_item_count)[city_offset]);
    }
    return discovered_count;
}

/* 原函数 0x81c18248 */
uint32_t sango_city_find_item(uint32_t city_id, int destination_address)
{
    char *signed_roster_entry;
    uint8_t *roster_entry;
    uint8_t roster_index;
    int city_offset;
    uint32_t roster_position;
    uint8_t *destination_entry;
    uint32_t undiscovered_count;

    city_offset = (city_id & 0xff) * 0x24;
    undiscovered_count = 0;
    roster_position = (uint32_t)(uint8_t)(&g_first_city_item_start)[city_offset];
    roster_index = 0;
    if ((&g_first_city_item_count)[city_offset] != '\0')
    {
        do
        {
            signed_roster_entry = &g_city_item_roster + roster_position;
            roster_index = roster_index + 1;
            roster_entry = &g_city_item_roster + roster_position;
            destination_entry = (uint8_t *)(destination_address + undiscovered_count);
            roster_position = roster_position + 1 & 0xff;
            if (-1 < *signed_roster_entry)
            {
                undiscovered_count = undiscovered_count + 1 & 0xff;
                *destination_entry = *roster_entry;
            }
        } while (roster_index < (uint8_t)(&g_first_city_item_count)[city_offset]);
    }
    return undiscovered_count;
}

/* 原函数 0x81c182d0 */
uint32_t sango_city_neighbor_direction(uint32_t city_id, uint32_t neighbor_city)
{
    int neighbor_table_address;
    uint8_t *neighbor_entry;
    uint32_t direction_index;
    uint8_t *city_neighbors;

    neighbor_table_address = sango_resource_item(0x3b, '\x01', g_resource_package_address);
    city_neighbors = (uint8_t *)(neighbor_table_address + (city_id & 0xff) * 0x10);
    direction_index = 0;
    neighbor_entry = city_neighbors;
    do
    {
        if ((uint32_t)*neighbor_entry == (neighbor_city & 0xff) + 1)
        {
            return direction_index;
        }
        direction_index = direction_index + 1 & 0xff;
        neighbor_entry = city_neighbors + direction_index;
    } while (direction_index < 8);
    return direction_index;
}

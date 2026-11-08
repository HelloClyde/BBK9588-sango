#include "sango_internal.h"

/* 城市名称、属性面板和城市命令入口。 */

/* 原函数 0x81c1971c */
void sango_city_read_name(char city_id, void *name)
{
    sango_resource_read_text(0x3a, (uint8_t)city_id + 1 & 0xff, name);
    return;
}

/* 原函数 0x81c19748 */
void sango_city_format_attribute(uint32_t city_id, uint8_t attribute, char *output,
                                 uint32_t legacy_context)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define value_text (*(char(*)[24])(abi_storage + 0))

    uint8_t character_owner_id;
    uint16_t development_limit;
    uint32_t text_length;
    char *status_context;
    uint16_t name_resource;
    uint32_t attribute_value;

    uint32_t city_index = city_id & 0xff;
    *output = '\0';
    switch (attribute)
    {
    case 0:
        sango_resource_read_text(0x40, 2, output);
        character_owner_id = (&g_first_city_owner)[city_index * 0x24];
        goto append_character_name;
    case 1:
        sango_resource_read_text(0x40, 3, output);
        character_owner_id = (&g_first_city_governor)[city_index * 0x24];
    append_character_name:
        if (character_owner_id == 0)
        {
            name_resource = 0x40;
            attribute_value = 0x32;
        }
        else
        {
            if (g_scenario_id_view2 == 2)
            {
                name_resource = 0x46;
            }
            else if (g_scenario_id_view2 < 3)
            {
                if (g_scenario_id_view2 == 1)
                {
                    name_resource = 0x3e;
                }
            }
            else if (g_scenario_id_view2 == 3)
            {
                name_resource = 0x47;
            }
            else if (g_scenario_id_view2 == 4)
            {
                name_resource = 0x48;
            }
            attribute_value = (uint32_t)character_owner_id;
        }
        sango_resource_read_text(name_resource, attribute_value, output + 5);
        return;
    case 2:
        sango_resource_read_text(0x40, 4, output);
        sango_format_integer((uint32_t)(uint16_t)(&g_first_city_agriculture)[city_index * 0x12],
                             value_text, 10);
        bbk_strcat(output, value_text);
        text_length = bbk_strlen(output);
        output[text_length + 1] = '\0';
        text_length = bbk_strlen(output);
        output[text_length] = '/';
        development_limit = (&g_first_city_agriculture_limit)[city_index * 0x12];
        goto use_development_limit;
    case 3:
        sango_resource_read_text(0x40, 5, output);
        sango_format_integer((uint32_t)(uint16_t)(&g_first_city_commerce)[city_index * 0x12],
                             value_text, 10);
        bbk_strcat(output, value_text);
        text_length = bbk_strlen(output);
        output[text_length + 1] = '\0';
        text_length = bbk_strlen(output);
        output[text_length] = '/';
        development_limit = (&g_first_city_commerce_limit)[city_index * 0x12];
    use_development_limit:
        attribute_value = (uint32_t)development_limit;
        break;
    case 4:
        sango_resource_read_text(0x40, 6, output);
        attribute_value = (uint32_t)(uint8_t)(&g_first_city_loyalty)[city_index * 0x24];
        break;
    case 5:
        sango_resource_read_text(0x40, 7, output);
        attribute_value = (uint32_t)(uint8_t)(&g_first_city_disaster_prevention)[city_index * 0x24];
        break;
    case 6:
        sango_resource_read_text(0x40, 8, output);
        attribute_value = (&g_first_city_population_limit)[city_index * 9];
        break;
    case 7:
        sango_resource_read_text(0x40, 9, output);
        attribute_value = (uint32_t)(uint16_t)(&g_first_city_money)[city_index * 0x12];
        break;
    case 8:
        sango_resource_read_text(0x40, 10, output);
        attribute_value = (uint32_t)(uint16_t)(&g_first_city_food)[city_index * 0x12];
        break;
    case 9:
        sango_resource_read_text(0x40, 0xb, output);
        attribute_value = (uint32_t)(uint16_t)(&g_first_city_reserve_troops)[city_index * 0x12];
        break;
    case 10:
        status_context = output;
        sango_resource_read_text(0x40, 1, output);
        sango_city_format_status(city_index, value_text, status_context, legacy_context);
        goto append_value_text;
    default:
        goto attribute_done;
    }
    sango_format_integer(attribute_value, value_text, 10);
append_value_text:
    bbk_strcat(output, value_text);
attribute_done:
    return;
}
#undef value_text

/* 原函数 0x81c19a98 */
void sango_city_format_status(uint32_t city_id, void *destination, uint32_t unused_format_argument,
                              uint32_t fallback_text_id)
{
    switch ((&g_first_city_status)[(city_id & 0xff) * 0x24])
    {
    case 0:
        fallback_text_id = 0xc;
        break;
    case 1:
        fallback_text_id = 0xd;
        break;
    case 2:
        fallback_text_id = 0xe;
        break;
    case 3:
        fallback_text_id = 0xf;
        break;
    case 4:
        fallback_text_id = 0x10;
    }
    sango_resource_read_text(0x40, fallback_text_id, destination);
    return;
}

/* 原函数 0x81c19b1c */
uint32_t sango_ui_show_city_details(uint8_t city_id)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define attribute_text (*(char(*)[32])(abi_storage + 0))
#define event_kind (*(int *)(abi_storage + 32))
#define event_key (*(int *)(abi_storage + 36))

    bool initial_draw;
    uint32_t accepted;
    uint16_t attribute_index_or_page;
    uint32_t attribute_format_argument;
    uint16_t visible_row;
    uint16_t first_attribute;

    first_attribute = 0;
    initial_draw = true;
    do
    {
        if (initial_draw)
            goto redraw_attributes;
        while (sango_input_next_event(&event_kind), event_kind == 5)
        {
            if (event_key == 0x67)
            {
            previous_page:
                attribute_index_or_page = first_attribute - 0x17;
                if (first_attribute == 0)
                    break;
            }
            else
            {
                if (event_key < 0x68)
                {
                    accepted = 0;
                    if ((event_key == 1) || (accepted = 1, event_key == 0x1c))
                    {
                        return accepted;
                    }
                    break;
                }
                if (event_key != 0x6a)
                {
                    if (event_key < 0x6b)
                    {
                        if (event_key == 0x69)
                            goto previous_page;
                        break;
                    }
                    if (event_key != 0x6c)
                        break;
                }
                attribute_index_or_page = first_attribute + 0x17;
                if (10 < attribute_index_or_page)
                    break;
            }
            first_attribute = attribute_index_or_page & 0xff;
        redraw_attributes:
            sango_display_fill_gray_rectangle(0x45, 2, 0xa9, 0x13a, 0, 0);
            attribute_format_argument = 0x13b;
            sango_display_draw_rectangle(0x44, 1, 0xaa, 0x13b, 3, 0, 0);
            sango_city_read_name(city_id, attribute_text);
            sango_text_draw_legacy(0x4a, 2, attribute_text);
            visible_row = 0;
            attribute_index_or_page = first_attribute;
            do
            {
                sango_city_format_attribute((uint32_t)city_id, (char)attribute_index_or_page,
                                            attribute_text, attribute_format_argument);
                sango_text_draw_legacy(0x4a, visible_row * 0xd + 0xe, attribute_text);
                visible_row = visible_row + 1 & 0xff;
                attribute_index_or_page = first_attribute + visible_row;
            } while (visible_row < 0x17);
            initial_draw = false;
        }
    } while (true);
}
#undef attribute_text
#undef event_kind
#undef event_key

/* 原函数 0x81c19cac */
void sango_load_named_text(uint8_t character_id, void *name)
{
    uint16_t name_resource;

    if (g_scenario_id_view2 == 2)
    {
        name_resource = 0x46;
    }
    else if (g_scenario_id_view2 < 3)
    {
        if (g_scenario_id_view2 == 1)
        {
            name_resource = 0x3e;
        }
    }
    else if (g_scenario_id_view2 == 3)
    {
        name_resource = 0x47;
    }
    else if (g_scenario_id_view2 == 4)
    {
        name_resource = 0x48;
    }
    sango_resource_read_text(name_resource, character_id + 1 & 0xff, name);
    return;
}

/* 原函数 0x81c19d30 */
uint32_t sango_strategy_run_player_commands(void)
{
    uint32_t city_id;
    uint32_t command_id;
    uint8_t error_text_id;

    while (true)
    {
        city_id = sango_strategy_select_city(&g_strategy_viewport_x);
        if (city_id == 0xff)
            break;
        if ((uint32_t)(uint8_t)(&g_first_city_owner)[city_id * 0x24] == g_player_character + 1)
        {
            command_id = sango_city_choose_command();
            if (command_id == 0xfe)
            {
                sango_ui_show_city_details((uint8_t)city_id);
            }
            else if (command_id != 0xff)
            {
                sango_city_execute_command((uint8_t)city_id, (char)command_id);
            }
        }
        else
        {
            error_text_id = 0x36;
            if ((uint8_t)(&g_first_city_owner)[city_id * 0x24] == 0)
            {
                error_text_id = 0x38;
            }
            sango_ui_show_strategy_text(error_text_id);
        }
    }
    return 1;
}

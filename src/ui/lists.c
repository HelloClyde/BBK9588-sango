#include "sango_internal.h"

/* 分页表格、宝物及武将列表。 */

/* 原函数 0x81c18350 */
void sango_ui_table_begin(uint8_t left, uint8_t top, uint8_t right, uint8_t bottom,
                          uint8_t *table_state)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(uint8_t **)(abi_storage + 0)) = table_state;
#define table_state (*(uint8_t **)(abi_storage + 0))

    table_state[7] = top;
    table_state[2] = right;
    table_state[3] = bottom;
    table_state[6] = left;
    *table_state = left;
    table_state[1] = top;
    table_state[4] = left;
    table_state[5] = top;
    return;
}
#undef table_state

/* 原函数 0x81c18380 */
uint32_t sango_ui_table_next_cell(uint8_t cell_width, uint8_t cell_height, int table_address,
                                  uint8_t *cell_x, uint8_t *cell_y)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(uint8_t **)(abi_storage + 0)) = cell_y;
#define cell_y (*(uint8_t **)(abi_storage + 0))

    char next_x;
    int cell_bottom;
    uint32_t cell_fits;

    cell_bottom = (uint32_t) * (uint8_t *)(table_address + 5) + (uint32_t)cell_height + -1;
    cell_fits = 0;
    if (cell_bottom <= (int)(uint32_t) * (uint8_t *)(table_address + 3))
    {
        next_x = *(uint8_t *)(table_address + 6) + 1;
        if ((int)((uint32_t) * (uint8_t *)(table_address + 6) + (uint32_t)cell_width + -1) <=
            (int)(uint32_t) * (uint8_t *)(table_address + 2))
        {
            *(uint8_t *)(table_address + 6) = cell_width + next_x + -1;
            *(char *)(table_address + 4) = next_x;
            cell_fits = 1;
            if ((int)(uint32_t) * (uint8_t *)(table_address + 7) < cell_bottom)
            {
                *(uint8_t *)(table_address + 7) =
                    cell_height + *(uint8_t *)(table_address + 5) + -1;
            }
            *cell_x = *(uint8_t *)(table_address + 4);
            *cell_y = *(uint8_t *)(table_address + 5);
        }
    }
    return cell_fits;
}
#undef cell_y

/* 原函数 0x81c18410 */
uint32_t sango_ui_table_next_row(uint8_t *table_state)
{
    char previous_bottom;

    previous_bottom = table_state[7];
    if (previous_bottom != table_state[3])
    {
        table_state[7] = previous_bottom + '\x01';
        table_state[5] = previous_bottom + '\x01';
        table_state[6] = *table_state;
        table_state[4] = *table_state;
    }
    return (uint32_t)(previous_bottom != table_state[3]);
}

/* 原函数 0x81c18450 */
void sango_ui_draw_item_row(uint8_t item_id, uint32_t first_attribute, char left, char top,
                            char width)
{
    unsigned char abi_storage[113] __attribute__((aligned(8)));
    (*(char *)(abi_storage + 96)) = width;
#define column_widths (*(uint8_t(*)[8])(abi_storage + 32))
#define attribute_text (*(char(*)[24])(abi_storage + 8))
#define table_state (*(uint8_t(*)[8])(abi_storage + 40))
#define cell_x (*(uint8_t *)(abi_storage + 0))
#define cell_y (*(uint8_t(*)[7])(abi_storage + 1))
#define width (*(char *)(abi_storage + 96))

    int cell_fits;
    uint32_t attribute_index;
    uint8_t *column_width;

    attribute_index = first_attribute & 0xff;
    sango_ui_table_begin(left, top, left + width + -1, top + '\f', table_state);
    cell_fits = sango_ui_table_next_cell(0x3d, 0xc, (int)table_state, &cell_x, cell_y);
    if (cell_fits != 0)
    {
        sango_item_read_name(item_id, attribute_text);
        sango_text_draw_centered(cell_x + 0x1e, (uint16_t)cell_y[0], attribute_text);
        sango_resource_read_text(2, 7, column_widths);
        for (; attribute_index < 5; attribute_index = attribute_index + 1 & 0xff)
        {
            column_width = column_widths + attribute_index;
            cell_fits = sango_ui_table_next_cell(*column_width * '\x06' + 1, 0xc,
                                                 (int)table_state, &cell_x, cell_y);
            if (cell_fits == 0)
            {
                return;
            }
            sango_item_format_attribute((uint32_t)item_id, (char)attribute_index,
                                        attribute_text);
            sango_text_draw_centered((uint16_t)*column_width * 3 + (uint16_t)cell_x,
                                     (uint16_t)cell_y[0], attribute_text);
        }
    }
    return;
}
#undef column_widths
#undef attribute_text
#undef table_state
#undef cell_x
#undef cell_y
#undef width

/* 原函数 0x81c185cc */
void sango_item_format_attribute(uint32_t item_id, uint8_t attribute, uint8_t *output)
{
    uint8_t troop_type;
    int item_address;
    uint32_t number;
    uint32_t text_id;

    item_address = sango_resource_item(0x42, '\x01', g_resource_package_address);
    item_address = item_address + (item_id & 0xff) * 0x42;
    switch (attribute)
    {
    case 0:
        if (*(char *)(item_address + 1) == '\0')
        {
            text_id = 0x47;
        }
        else if (*(char *)(item_address + 1) == '\x01')
        {
            text_id = 0x48;
        }
        sango_resource_read_text(0x40, text_id, output);
        return;
    case 1:
        number = (uint32_t) * (uint8_t *)(item_address + 0x3e);
        break;
    case 2:
        number = (uint32_t) * (uint8_t *)(item_address + 0x3f);
        break;
    case 3:
        number = (uint32_t) * (uint8_t *)(item_address + 0x40);
        break;
    case 4:
        troop_type = *(uint8_t *)(item_address + 0x41);
        if (troop_type == 1)
        {
            text_id = 0x49;
        }
        else if (troop_type < 2)
        {
            if (troop_type == 0)
            {
                text_id = 0x32;
            }
        }
        else if (troop_type == 2)
        {
            text_id = 0x4a;
        }
        else if (troop_type == 3)
        {
            text_id = 0x4b;
        }
        sango_resource_read_text(0x40, text_id, output);
    default:
        return;
    }
    sango_format_integer(number, output, 10);
    return;
}

/* 原函数 0x81c18704 */
uint32_t sango_ui_draw_item_header(uint32_t first_attribute, char left, char top, char width)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define table_state (*(uint8_t(*)[8])(abi_storage + 32))
#define cell_x (*(uint8_t *)(abi_storage + 0))
#define cell_y (*(uint8_t(*)[7])(abi_storage + 1))
#define column_widths (*(uint8_t(*)[8])(abi_storage + 24))
#define header_text (*(char(*)[16])(abi_storage + 8))

    int cell_fits;
    uint32_t attribute_index;
    uint8_t *column_width;

    sango_ui_table_begin(left, top, left + width + -1, top + '\f', table_state);
    cell_fits = sango_ui_table_next_cell(0x3d, 0xc, (int)table_state, &cell_x, cell_y);
    attribute_index = 0;
    if (cell_fits != 0)
    {
        sango_resource_read_text(0x40, 0x41, header_text);
        sango_text_draw_centered(cell_x + 0x1e, (uint16_t)cell_y[0], header_text);
        sango_resource_read_text(2, 7, column_widths);
        attribute_index = first_attribute & 0xff;
        while (true)
        {
            column_width = column_widths + attribute_index;
            if (4 < attribute_index)
                break;
            cell_fits = sango_ui_table_next_cell(*column_width * '\x06' + 1, 0xc,
                                                 (int)table_state, &cell_x, cell_y);
            if (cell_fits == 0)
            {
                return attribute_index;
            }
            sango_resource_read_text(0x40, attribute_index + 0x42 & 0xff, header_text);
            sango_text_draw_centered((uint16_t)*column_width * 3 + (uint16_t)cell_x,
                                     (uint16_t)cell_y[0], header_text);
            attribute_index = attribute_index + 1 & 0xff;
        }
    }
    return attribute_index;
}
#undef table_state
#undef cell_x
#undef cell_y
#undef column_widths
#undef header_text

/* 原函数 0x81c18874 */
uint32_t sango_ui_select_item(int item_ids_address, uint32_t item_count, uint32_t left,
                              uint32_t top, uint8_t right, uint8_t bottom)
{
    unsigned char abi_storage[117] __attribute__((aligned(8)));
    (*(uint8_t *)(abi_storage + 96)) = right;
    (*(uint8_t *)(abi_storage + 100)) = bottom;
#define right (*(uint8_t *)(abi_storage + 96))
#define bottom (*(uint8_t *)(abi_storage + 100))
#define column_pages (*(uint8_t(*)[8])(abi_storage + 0))
#define event_kind (*(int *)(abi_storage + 8))
#define key_code (*(int *)(abi_storage + 12))

    uint32_t total_rows = item_count & 0xff;
    uint32_t box_top = top & 0xff;
    if (total_rows == 0)
        return 0xff;
    char table_width = (right - (char)left) + '\x01';
    uint32_t visible_rows = (int)((bottom - box_top) + 1) / 12 - 1U & 0xff;
    if (total_rows < visible_rows)
        visible_rows = total_rows;
    uint32_t frame_bottom = box_top + visible_rows * 12 + 12 & 0xff;

    uint32_t header_left = (left & 0xff) + 1;
    uint32_t content_left = header_left & 0xff;
    uint32_t content_top = box_top + 1 & 0xff;
    uint32_t content_right = (uint32_t)right - 1 & 0xff;
    short highlight_right = (short)(content_left + 0x3b);
    uint32_t column_page = 0;
    uint32_t top_row = 0;
    uint32_t selected_row = 0;
    bool redraw_table = true;
    column_pages[0] = 0;

    while (true)
    {
        if (redraw_table)
        {
            sango_ui_paint_begin();
            sango_display_draw_rectangle((short)(left & 0xff), (short)box_top,
                                         (uint16_t)right, (short)frame_bottom + 1, 3, 0, 0);
            sango_display_fill_gray_rectangle(
                (short)content_left, (short)content_top, (short)content_right,
                (short)(content_top + visible_rows * 12 + 11), 0, 0);
            uint8_t *first_attribute = column_pages + column_page;
            char header_x = (char)header_left;
            char header_y = (char)(box_top + 1);
            uint32_t next_attribute = sango_ui_draw_item_header(
                (uint32_t)*first_attribute, header_x, header_y, table_width);
            column_pages[column_page + 1] = (uint8_t)next_attribute;
            uint32_t row_index = 0;
            if (visible_rows != 0)
            {
                int twice_row_index = 0;
                do
                {
                    /* 保留旧行填充规则；不在本次重构中修正尾页填充。 */
                    if (total_rows <= row_index)
                        break;
                    sango_ui_draw_item_row(
                        (uint32_t) * (uint8_t *)(item_ids_address + top_row + row_index),
                        (uint32_t)*first_attribute, header_x,
                        header_y + ((char)twice_row_index + (char)row_index) * '\x04' + '\f',
                        table_width);
                    row_index = row_index + 1 & 0xff;
                    twice_row_index = row_index << 1;
                } while (row_index < visible_rows);
            }
            int row_origin = content_top + (selected_row - top_row) * 12;
            int highlight_top = row_origin + 12;
            sango_ui_paint_end();
            if (true)
                sango_display_invert_rectangle((short)content_left, (short)highlight_top,
                                               highlight_right, (short)(row_origin + 23), 0);
            redraw_table = false;
        }

        sango_input_next_event(&event_kind);
        int tapped =
            sango_touch_choose_row(&event_kind, (int)content_left, (int)content_top + 12,
                                   (int)content_right, 12, visible_rows, top_row, total_rows);
        if (tapped >= 0)
            return (uint32_t)tapped;
        if (event_kind == SANGO_TOUCH_PAN_END)
        {
            key_code = sango_touch_swipe_key(&event_kind);
            if (key_code)
                event_kind = 5;
        }
        if (event_kind != 5)
            continue;
        if (key_code == 1)
            return 0xff;
        if (key_code == 0x1c)
            return selected_row;

        if (key_code == 0x67 || false)
        {
            if (selected_row == 0)
                continue;
            int row_origin = content_top + (selected_row - top_row) * 12;
            sango_display_invert_rectangle((short)content_left, (short)(row_origin + 12),
                                           highlight_right, (short)(row_origin + 23), 0);
            selected_row = selected_row - 1 & 0xff;
            if (top_row <= selected_row)
            {
                row_origin = content_top + (selected_row - top_row) * 12;
                sango_display_invert_rectangle((short)content_left, (short)(row_origin + 12),
                                               highlight_right, (short)(row_origin + 23), 0);
            }
            else
            {
                top_row = selected_row;
                redraw_table = true;
            }
            continue;
        }

        if (key_code == 0x6c || false)
        {
            if ((int)selected_row >= (int)(total_rows - 1))
                continue;
            int row_origin = content_top + (selected_row - top_row) * 12;
            int highlight_top = row_origin + 12;
            if (true)
                sango_display_invert_rectangle((short)content_left, (short)highlight_top,
                                               highlight_right, (short)(row_origin + 23), 0);
            selected_row = selected_row + 1 & 0xff;
            if (selected_row < top_row + visible_rows)
            {
                row_origin = content_top + (selected_row - top_row) * 12;
                sango_display_invert_rectangle((short)content_left, (short)(row_origin + 12),
                                               highlight_right, (short)(row_origin + 23), 0);
            }
            else
            {
                top_row = (selected_row - visible_rows) + 1 & 0xff;
                redraw_table = true;
            }
            continue;
        }
        if (key_code == 0x69 && column_pages[column_page] != 0)
        {
            column_page = column_page - 1 & 0xff;
            redraw_table = true;
        }
        else if (key_code == 0x6a && column_pages[column_page + 1] <= 4)
        {
            column_page = column_page + 1 & 0xff;
            redraw_table = true;
        }
    }
}
#undef right
#undef bottom
#undef column_pages
#undef event_kind
#undef key_code
#undef content_right
#undef column_page
#undef twice_visible_rows
#undef highlight_right_fixed

/* 原函数 0x81c18c80 */
void sango_item_read_name(char item_id, void *name)
{
    sango_resource_read_text(0x49, (uint8_t)item_id + 1 & 0xff, name);
    return;
}

/* 原函数 0x81c18cac */
void sango_ui_draw_character_row(uint32_t character_id, uint32_t first_attribute, char left,
                                 char top, char width)
{
    unsigned char abi_storage[121] __attribute__((aligned(8)));
    (*(char *)(abi_storage + 104)) = width;
#define cell_x (*(uint8_t *)(abi_storage + 0))
#define cell_y (*(uint8_t(*)[7])(abi_storage + 1))
#define width (*(char *)(abi_storage + 104))
#define column_widths (*(uint8_t(*)[16])(abi_storage + 32))
#define attribute_text (*(char(*)[24])(abi_storage + 8))
#define table_state (*(uint8_t(*)[8])(abi_storage + 48))

    int cell_fits;
    uint32_t attribute_index;
    uint16_t name_resource;
    uint8_t *column_width;

    attribute_index = first_attribute & 0xff;
    sango_ui_table_begin(left, top, left + width + -1, top + '\f', table_state);
    cell_fits = sango_ui_table_next_cell(0x31, 0xc, (int)table_state, &cell_x, cell_y);
    if (cell_fits != 0)
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
        sango_resource_read_text(name_resource, (character_id & 0xff) + 1 & 0xff,
                                 attribute_text);
        sango_text_draw_centered(cell_x + 0x18, (uint16_t)cell_y[0], attribute_text);
        sango_resource_read_text(2, 8, column_widths);
        for (; attribute_index < 0xd; attribute_index = attribute_index + 1 & 0xff)
        {
            column_width = column_widths + attribute_index;
            cell_fits = sango_ui_table_next_cell(*column_width * '\x06' + 1, 0xc,
                                                 (int)table_state, &cell_x, cell_y);
            if (cell_fits == 0)
            {
                return;
            }
            sango_character_format_attribute(character_id & 0xff, (char)attribute_index,
                                             attribute_text);
            sango_text_draw_centered((uint16_t)*column_width * 3 + (uint16_t)cell_x,
                                     (uint16_t)cell_y[0], attribute_text);
        }
    }
    return;
}
#undef cell_x
#undef cell_y
#undef width
#undef column_widths
#undef attribute_text
#undef table_state

/* 原函数 0x81c18e88 */
void sango_character_format_attribute(uint32_t character_id, uint8_t attribute, uint8_t *output)
{
    char equipped_item;
    uint16_t text_resource;
    uint32_t number;
    uint32_t owner_id;
    int character_offset;
    uint32_t text_id;

    uint32_t character_index = character_id & 0xff;
    character_offset = character_index * 0x10;
    owner_id = (uint32_t) * (uint8_t *)(character_offset + g_character_table_address + 1);
    switch (attribute)
    {
    case 0:
        if (owner_id == 0xff)
        {
            text_resource = 0x40;
            text_id = 0x31;
        }
        else
        {
            text_resource = 0x40;
            if (owner_id == character_index + 1)
            {
                text_id = 0x30;
            }
            else if (owner_id == 0)
            {
                text_resource = 0x40;
                text_id = 0x2f;
            }
            else
            {
                if (g_scenario_id_view2 == 2)
                {
                    number = 0x46;
                }
                else
                {
                    number = text_id;
                    if (g_scenario_id_view2 < 3)
                    {
                        if (g_scenario_id_view2 == 1)
                        {
                            number = 0x3e;
                        }
                    }
                    else if (g_scenario_id_view2 == 3)
                    {
                        number = 0x47;
                    }
                    else if (g_scenario_id_view2 == 4)
                    {
                        number = 0x48;
                    }
                }
                text_id = (owner_id - 1 & 0xff) + 1 & 0xff;
                text_resource = (uint16_t)number;
            }
        }
        sango_resource_read_text(text_resource, text_id, output);
        return;
    case 1:
        number = sango_character_find_city((char)character_id);
        sango_city_read_name((char)number, output);
        return;
    case 2:
        number = (uint32_t) * (uint8_t *)(character_offset + g_character_table_address + 2);
        break;
    case 3:
        number = (uint32_t) * (uint8_t *)(character_offset + g_character_table_address + 3);
        break;
    case 4:
        number = (uint32_t) * (uint8_t *)(character_offset + g_character_table_address + 4);
        break;
    case 5:
        if ((owner_id == character_index + 1) || (owner_id == 0))
        {
            text_resource = 0x40;
            text_id = 0x33;
            sango_resource_read_text(text_resource, text_id, output);
            return;
        }
        number = (uint32_t) * (uint8_t *)(character_offset + g_character_table_address + 5);
        break;
    case 6:
        number = (uint32_t) * (uint8_t *)(character_offset + g_character_table_address + 7);
        break;
    case 7:
        number = (uint32_t) * (uint8_t *)(character_offset + g_character_table_address + 8);
        break;
    case 8:
        switch (*(uint8_t *)(character_offset + g_character_table_address + 9))
        {
        case 0:
            text_id = 0x11;
            break;
        case 1:
            text_id = 0x12;
            break;
        case 2:
            text_id = 0x13;
            break;
        case 3:
            text_id = 0x14;
            break;
        case 4:
            text_id = 0x15;
            break;
        case 5:
            text_id = 0x16;
        }
        text_resource = 0x40;
        sango_resource_read_text(text_resource, text_id, output);
        return;
    case 9:
        number = (uint32_t) * (uint16_t *)(character_offset + g_character_table_address + 10);
        break;
    case 10:
        number = (uint32_t) * (uint8_t *)(character_offset + g_character_table_address + 0xe);
        break;
    case 0xb:
        *output = 0;
        equipped_item = *(char *)(character_offset + g_character_table_address + 0xc);
        if (equipped_item != '\0')
            sango_item_read_name(equipped_item - 1, output);
        return;
    case 0xc:
        *output = 0;
        equipped_item = *(char *)(character_offset + g_character_table_address + 0xd);
        if (equipped_item != '\0')
        {
            sango_item_read_name(equipped_item + -1, output);
        }
    default:
        return;
    }
    sango_format_integer(number, output, 10);
    return;
}

/* 原函数 0x81c19100 */
uint32_t sango_ui_draw_character_header(uint32_t first_attribute, char left, char top,
                                        char width)
{
    unsigned char abi_storage[64] __attribute__((aligned(8)));
#define cell_y (*(uint8_t(*)[7])(abi_storage + 1))
#define table_state (*(uint8_t(*)[8])(abi_storage + 40))
#define column_widths (*(uint8_t(*)[16])(abi_storage + 24))
#define header_text (*(char(*)[16])(abi_storage + 8))
#define cell_x (*(uint8_t *)(abi_storage + 0))

    int cell_fits;
    uint32_t attribute_index;
    uint8_t *column_width;

    sango_ui_table_begin(left, top, left + width + -1, top + '\f', table_state);
    cell_fits = sango_ui_table_next_cell(0x31, 0xc, (int)table_state, &cell_x, cell_y);
    attribute_index = 0;
    if (cell_fits != 0)
    {
        sango_resource_read_text(0x40, 0x17, header_text);
        sango_text_draw_centered(cell_x + 0x18, (uint16_t)cell_y[0], header_text);
        sango_resource_read_text(2, 8, column_widths);
        attribute_index = first_attribute & 0xff;
        while (true)
        {
            column_width = column_widths + attribute_index;
            if (0xc < attribute_index)
                break;
            cell_fits = sango_ui_table_next_cell(*column_width * '\x06' + 1, 0xc,
                                                 (int)table_state, &cell_x, cell_y);
            if (cell_fits == 0)
            {
                return attribute_index;
            }
            sango_resource_read_text(0x40, attribute_index + 0x18 & 0xff, header_text);
            sango_text_draw_centered((uint16_t)*column_width * 3 + (uint16_t)cell_x,
                                     (uint16_t)cell_y[0], header_text);
            attribute_index = attribute_index + 1 & 0xff;
        }
    }
    return attribute_index;
}
#undef cell_y
#undef table_state
#undef column_widths
#undef header_text
#undef cell_x

/* 原函数 0x81c19270 */
uint32_t sango_ui_select_character(int character_ids_address, uint32_t character_count,
                                   uint32_t left, uint32_t top, uint8_t right, uint8_t bottom)
{
    unsigned char abi_storage[117] __attribute__((aligned(8)));
    (*(uint8_t *)(abi_storage + 96)) = right;
    (*(uint8_t *)(abi_storage + 100)) = bottom;
#define right (*(uint8_t *)(abi_storage + 96))
#define bottom (*(uint8_t *)(abi_storage + 100))
#define column_pages (*(uint8_t(*)[8])(abi_storage + 0))
#define event_kind (*(int *)(abi_storage + 8))
#define key_code (*(int *)(abi_storage + 12))

    uint32_t total_rows = character_count & 0xff;
    uint32_t box_top = top & 0xff;
    if (total_rows == 0)
        return 0xff;
    char table_width = (right - (char)left) - 1;
    uint32_t visible_rows = (int)((bottom - box_top) + -1) / 12 - 1U & 0xff;
    if (total_rows < visible_rows)
        visible_rows = total_rows;
    uint32_t frame_bottom = box_top + visible_rows * 12 + 12 & 0xff;

    uint32_t header_left = (left & 0xff) + 1;
    uint32_t content_left = header_left & 0xff;
    uint32_t content_top = box_top + 1 & 0xff;
    uint32_t content_right = (uint32_t)right - 1 & 0xff;
    short highlight_right = (short)(content_left + 0x2f);
    uint32_t column_page = 0;
    uint32_t top_row = 0;
    uint32_t selected_row = 0;
    bool redraw_table = true;
    column_pages[0] = 0;

    while (true)
    {
        if (redraw_table)
        {
            sango_ui_paint_begin();
            sango_display_draw_rectangle((short)(left & 0xff), (short)box_top,
                                         (uint16_t)right, (short)frame_bottom + 1, 3, 0, 0);
            sango_display_fill_gray_rectangle((short)content_left, (short)content_top,
                                              (short)content_right, (short)frame_bottom, 0, 0);
            uint8_t *first_attribute = column_pages + column_page;
            char header_x = (char)header_left;
            char header_y = (char)(box_top + 1);
            uint32_t next_attribute = sango_ui_draw_character_header(
                (uint32_t)*first_attribute, header_x, header_y, table_width);
            column_pages[column_page + 1] = (uint8_t)next_attribute;
            uint32_t row_index = 0;
            if (visible_rows != 0)
            {
                int twice_row_index = 0;
                do
                {
                    /* 保留旧行填充规则；不在本次重构中修正尾页填充。 */
                    if (total_rows <= row_index)
                        break;
                    sango_ui_draw_character_row(
                        (uint32_t) * (uint8_t *)(character_ids_address + top_row + row_index),
                        (uint32_t)*first_attribute, header_x,
                        header_y + ((char)twice_row_index + (char)row_index) * '\x04' + '\f',
                        table_width);
                    row_index = row_index + 1 & 0xff;
                    twice_row_index = row_index << 1;
                } while (row_index < visible_rows);
            }
            int row_origin = content_top + (selected_row - top_row) * 12;
            int highlight_top = row_origin + 12;
            sango_ui_paint_end();
            if (highlight_top < 0x8c)
                sango_display_invert_rectangle((short)content_left, (short)highlight_top,
                                               highlight_right, (short)(row_origin + 23), 0);
            redraw_table = false;
        }

        sango_input_next_event(&event_kind);
        int tapped =
            sango_touch_choose_row(&event_kind, (int)content_left, (int)content_top + 12,
                                   (int)content_right, 12, visible_rows, top_row, total_rows);
        if (tapped >= 0)
            return (uint32_t)tapped;
        if (event_kind == SANGO_TOUCH_PAN_END)
        {
            key_code = sango_touch_swipe_key(&event_kind);
            if (key_code)
                event_kind = 5;
        }
        if (event_kind != 5)
            continue;
        if (key_code == 1)
            return 0xff;
        if (key_code == 0x1c)
            return selected_row;

        /* 翻页沿用原来的“先调位置、再执行一次上移”规则。 */
        if (key_code == 0x68)
        {
            if (selected_row == 0)
                continue;
            if (selected_row < visible_rows)
                selected_row = 1;
            else
                selected_row = (selected_row - visible_rows) + 1 & 0xff;
            redraw_table = true;
        }
        if (key_code == 0x67 || key_code == 0x68)
        {
            if (selected_row == 0)
                continue;
            int row_origin = content_top + (selected_row - top_row) * 12;
            sango_display_invert_rectangle((short)content_left, (short)(row_origin + 12),
                                           highlight_right, (short)(row_origin + 23), 0);
            selected_row = selected_row - 1 & 0xff;
            if (top_row <= selected_row)
            {
                row_origin = content_top + (selected_row - top_row) * 12;
                sango_display_invert_rectangle((short)content_left, (short)(row_origin + 12),
                                               highlight_right, (short)(row_origin + 23), 0);
            }
            else
            {
                top_row = selected_row;
                redraw_table = true;
            }
            continue;
        }
        if (key_code == 0x6d && (int)selected_row < (int)(total_rows - 2))
        {
            selected_row = (selected_row + visible_rows) - 1 & 0xff;
            if ((int)(total_rows - 1) <= (int)selected_row)
                selected_row = total_rows - 2 & 0xff;
            redraw_table = true;
        }
        if (key_code == 0x6c || key_code == 0x6d)
        {
            if ((int)selected_row >= (int)(total_rows - 1))
                continue;
            int row_origin = content_top + (selected_row - top_row) * 12;
            int highlight_top = row_origin + 12;
            if (highlight_top < 0x8c)
                sango_display_invert_rectangle((short)content_left, (short)highlight_top,
                                               highlight_right, (short)(row_origin + 23), 0);
            selected_row = selected_row + 1 & 0xff;
            if (selected_row < top_row + visible_rows)
            {
                row_origin = content_top + (selected_row - top_row) * 12;
                sango_display_invert_rectangle((short)content_left, (short)(row_origin + 12),
                                               highlight_right, (short)(row_origin + 23), 0);
            }
            else
            {
                top_row = (selected_row - visible_rows) + 1 & 0xff;
                redraw_table = true;
            }
            continue;
        }
        if (key_code == 0x69 && column_pages[column_page] != 0)
        {
            column_page = column_page - 1 & 0xff;
            redraw_table = true;
        }
        else if (key_code == 0x6a && column_pages[column_page + 1] <= 12)
        {
            column_page = column_page + 1 & 0xff;
            redraw_table = true;
        }
    }
}
#undef column_pages
#undef event_kind
#undef key_code
#undef content_right
#undef content_bottom
#undef column_page
#undef right
#undef highlight_right_fixed
#undef bottom

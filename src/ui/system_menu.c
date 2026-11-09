#include "sango_internal.h"

/* 系统菜单、数值选择及电脑执行提示。 */

/* 原函数 0x81c1b2b4 */
uint32_t sango_ui_show_system_menu(void)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define menu_bounds (*(uint16_t(*)[4])(abi_storage + 0))
#define menu_text (*(char(*)[32])(abi_storage + 8))

    uint32_t selection;
    uint32_t menu_result;

    sango_resource_read_text(0x40, 0x79, menu_text);
    menu_bounds[0] = 0x4f;
    menu_bounds[2] = 0x7f;
    menu_bounds[3] = 0x2e;
    menu_bounds[1] = 10;
    selection = sango_ui_choose_option(menu_bounds, 0, menu_text);
    if (selection == 1)
    {
        sango_save_choose_slot('\0');
        menu_result = 0;
    }
    else if ((int)selection < 2)
    {
        menu_result = 1;
    }
    else
    {
        menu_result = 2;
        if (selection != 2)
        {
            menu_result = 0;
        }
    }
    return menu_result;
}
#undef menu_bounds
#undef menu_text

/* 原函数 0x81c1b364 */
uint32_t sango_ui_select_number(uint32_t initial_value, uint32_t maximum_value)
{
    unsigned char abi_storage[61] __attribute__((aligned(8)));
#define event_kind (*(int *)(abi_storage + 24))
#define key_code (*(int *)(abi_storage + 28))
#define prompt_text (*(char(*)[7])(abi_storage + 0))
#define maximum_text (*(char(*)[17])(abi_storage + 7))
#define digit0 (*(char *)(abi_storage + 40))
#define digit1 (*(char *)(abi_storage + 41))
#define digit2 (*(char *)(abi_storage + 42))
#define digit3 (*(char *)(abi_storage + 43))
#define digit_terminator (*(uint8_t *)(abi_storage + 44))

    uint32_t limit = maximum_value & 0xffff;
    if (9999 < limit)
        limit = 9999;
    uint32_t value = initial_value & 0xffff;
    sango_resource_read_text(0x40, 0x2c, prompt_text);
    sango_text_draw_legacy(0x53, 0x99, prompt_text);
    sango_resource_read_text(0x40, 0x2d, prompt_text);
    sango_format_integer(limit, maximum_text, 10);
    sango_text_draw_legacy(0x53, 0xa5, prompt_text);
    sango_touch_draw_number_controls();

    uint32_t last_digit_index = bbk_strlen(maximum_text) - 1 & 0xff;
    uint32_t digit_index = last_digit_index;
    uint32_t step = 1;
    bool redraw_digits = true;
    while (true)
    {
        if (redraw_digits)
        {
            /* 保留原来的逐位生成和8/16位转换，包括超出上限的初始值。 */
            char low_value_byte = (char)value;
            if (last_digit_index == 3)
            {
                digit_terminator = 0;
                digit0 = (char)(value / 1000) + '0';
                digit3 = low_value_byte + (char)(value / 10) * -10 + '0';
                digit1 = (char)((value % 1000) / 100) + '0';
                digit2 = (char)((value % 100) / 10) + '0';
            }
            if (last_digit_index == 2)
            {
                digit3 = '\0';
                digit2 = low_value_byte + (char)(value / 10) * -10 + '0';
                digit0 = (char)((value % 1000) / 100) + '0';
                digit1 = (char)((value % 100) / 10) + '0';
            }
            if (last_digit_index == 1)
            {
                digit2 = '\0';
                digit1 = low_value_byte + (char)(value / 10) * -10 + '0';
                digit0 = (char)((value % 100) / 10) + '0';
            }
            if (last_digit_index == 0)
            {
                digit1 = '\0';
                digit0 = low_value_byte + (char)(value / 10) * -10 + '0';
            }
            sango_text_draw_legacy(0x7d, 0x99, &digit0);
            short highlight_offset = (short)digit_index * 6;
            redraw_digits = false;
            sango_display_invert_rectangle(highlight_offset + 0x7d, 0x99, highlight_offset + 0x82,
                                           0xa4, 0);
        }

        sango_input_next_event(&event_kind);
        if (event_kind == SANGO_TOUCH_TAP || event_kind == SANGO_TOUCH_HOLD)
        {
            int x = sango_touch_x(&event_kind), y = sango_touch_y(&event_kind);
            if (x >= 125 && x < 125 + (int)(last_digit_index + 1) * 6 && y >= 153 && y < 165)
            {
                digit_index = (uint32_t)(x - 125) / 6;
                step = 1;
                for (uint32_t place = digit_index; place < last_digit_index; ++place)
                    step *= 10;
                redraw_digits = true;
                continue;
            }
            if (y >= 183 && y <= 205 && x >= 40 && x < 204 && (x - 40) % 42 < 38)
            {
                static const int button_keys[4] = {BDA_KEY_DOWN, BDA_KEY_UP, BDA_KEY_ENTER,
                                                   BDA_KEY_ESCAPE};
                key_code = button_keys[(x - 40) / 42];
                event_kind = 5;
            }
        }
        if (event_kind != 5)
            continue;
        switch (key_code)
        {
        case 1:
            return 0xffff;
        case 0x1c:
            return value;
        case 0x67: /* 增加当前十进制位 */
            if (limit < value + step)
                continue;
            value = value + step & 0xffff;
            break;
        case 0x6c: /* 减少当前十进制位 */
            if ((value < step) || ((int)(value - step) < 0))
                continue;
            value = value - step & 0xffff;
            break;
        case 0x69: /* 光标向高位移动 */
            if (digit_index == 0)
                continue;
            digit_index = digit_index - 1 & 0xff;
            step = step * 10 & 0xffff;
            break;
        case 0x6a: /* 光标向低位移动 */
            if (last_digit_index <= digit_index)
                continue;
            digit_index = digit_index + 1 & 0xff;
            step = step / 10 & 0xffff;
            break;
        default:
            continue;
        }
        redraw_digits = true;
    }
}
#undef event_kind
#undef key_code
#undef prompt_text
#undef digit0
#undef digit1
#undef digit2
#undef maximum_text
#undef digit3
#undef digit_terminator

/* 原函数 0x81c1b784 */
void sango_ui_show_ai_progress(void)
{
    uint8_t *scratch_buffer;
    uint32_t ruler_count;
    uint8_t *ruler_entry;
    uint8_t *destination;
    uint32_t ruler_index;

    sango_strategy_present();
    scratch_buffer = g_scratch_buffer_address;
    ruler_index = 0;
    ruler_count =
        sango_strategy_list_rulers((uint32_t)g_player_character, g_scratch_buffer_address);
    destination = scratch_buffer + 200;
    ruler_entry = scratch_buffer;
    if (ruler_count != 0)
    {
        do
        {
            sango_load_named_text(*ruler_entry, destination);
            sango_resource_read_text(0x40, 0xa3, scratch_buffer + 0xfa);
            bbk_strcat((char *)destination, (char *)(scratch_buffer + 0xfa));
            sango_display_fill_gray_rectangle(0x3c, 0x12f, 0xb2, 0x13d, 0, 0);
            sango_display_draw_rectangle(0x3c, 0x12f, 0xb2, 0x13d, 3, 0, 0);
            sango_text_draw_legacy(0x3e, 0x131, (char *)destination);
            sango_input_wait(0x14, '\0');
            ruler_index = ruler_index + 1 & 0xff;
            ruler_entry = scratch_buffer + ruler_index;
        } while (ruler_index < ruler_count);
    }
    sango_strategy_present();
    return;
}

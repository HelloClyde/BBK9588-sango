#include "sango_internal.h"

/* 粮食、金钱、兵力输入面板。 */

/* 原函数 0x81c13b9c */
uint32_t sango_ui_input_food_amount(uint32_t value, uint32_t mode)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define acStack_28 (*(char(*)[24])(abi_storage + 0))

    uint32_t uVar1;

    sango_display_fill_gray_rectangle(0x53, 0x8d, 0x9b, 0xb1, 0, 0);
    sango_display_draw_rectangle(0x52, 0x8c, 0x9c, 0xb2, 3, 0, 0);
    sango_resource_read_text(0x40, 0x29, acStack_28);
    sango_text_draw_legacy(0x53, 0x8d, acStack_28);
    uVar1 = sango_ui_select_number(value & 0xffff, mode & 0xffff);
    return uVar1;
}
#undef acStack_28

/* 原函数 0x81c13c3c */
uint32_t sango_ui_input_money_amount(uint32_t value, uint32_t mode)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define acStack_28 (*(char(*)[24])(abi_storage + 0))

    uint32_t uVar1;

    sango_display_fill_gray_rectangle(0x53, 0x8d, 0x9b, 0xb1, 0, 0);
    sango_display_draw_rectangle(0x52, 0x8c, 0x9c, 0xb2, 3, 0, 0);
    sango_resource_read_text(0x40, 0x2a, acStack_28);
    sango_text_draw_legacy(0x53, 0x8d, acStack_28);
    uVar1 = sango_ui_select_number(value & 0xffff, mode & 0xffff);
    return uVar1;
}
#undef acStack_28

/* 原函数 0x81c13cdc */
uint32_t sango_ui_input_troop_amount(uint32_t value, uint32_t mode)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define acStack_28 (*(char(*)[24])(abi_storage + 0))

    uint32_t uVar1;

    sango_display_fill_gray_rectangle(0x53, 0x8d, 0x9b, 0xb1, 0, 0);
    sango_display_draw_rectangle(0x52, 0x8c, 0x9c, 0xb2, 3, 0, 0);
    sango_resource_read_text(0x40, 0x2b, acStack_28);
    sango_text_draw_legacy(0x53, 0x8d, acStack_28);
    uVar1 = sango_ui_select_number(value & 0xffff, mode & 0xffff);
    return uVar1;
}
#undef acStack_28

#include "sango_internal.h"

/* 可移动区域及战场形势信息。 */

/* 原函数 0x81c027f0 */
void sango_battle_draw_move_range(void)
{
    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    int iVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint32_t uVar8;
    uint32_t uVar9;
    uint32_t uVar10;
    uint32_t uVar11;

    uVar1 = (uint32_t)g_move_window_left;
    uVar8 = (uint32_t)g_battle_viewport_x;
    uVar7 = (uint32_t)g_battle_viewport_y;
    uVar6 = (uint32_t)g_move_source_x;
    uVar2 = (uint32_t)g_move_window_top;
    uVar3 = (uint32_t)g_move_source_y;
    iVar4 = sango_resource_item(7, '\x01', g_resource_package_address);
    for (uVar10 = (uint32_t)g_move_window_left; uVar10 < 0xf; uVar10 = uVar10 + 1 & 0xff)
    {
        uVar9 = (uint32_t)g_move_window_top;
        if (uVar9 < 0xf)
        {
            uVar11 = uVar10 - ((uVar8 + uVar1) - uVar6 & 0xff);
            do
            {
                uVar5 = uVar9 - ((uVar7 + uVar2) - uVar3 & 0xff);
                if (((uVar11 & 0xff) < 0xf) && ((uVar5 & 0xff) < 0xf))
                {
                    if ('\0' < *(char *)(g_move_costs_address + uVar9 * 0xf + uVar10))
                    {
                        sango_raster_draw_masked((uVar11 & 0xf) << 4, (short)((uVar5 & 0xf) << 4),
                                                 0x10, 0x10, iVar4 + 6, g_game_context);
                    }
                }
                uVar9 = uVar9 + 1 & 0xff;
            } while (uVar9 < 0xf);
        }
    }
    return;
}

/* 原函数 0x81c02954 */
void sango_battle_show_overview(void)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define acStack_38 (*(char(*)[24])(abi_storage + 0))

    int iVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    char cVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint32_t uVar8;
    uint32_t uVar9;

    sango_display_fill_gray_rectangle(0, 0, 0xef, 0x13f, 0, 0);
    uVar6 = (int)(0x78 - (uint32_t)g_battle_map_width) / 2 & 0xff;
    uVar7 = (int)(0x140 - (uint32_t)g_battle_map_height) / 2 + 0x14U & 0xff;
    sango_battle_load_overview_text(0x31, acStack_38);
    sango_text_draw_legacy(5, 3, acStack_38);
    sango_battle_load_overview_text(0x30, acStack_38);
    sango_format_integer((uint32_t)g_battle_day, acStack_38 + 3, 10);
    uVar2 = bbk_strlen(acStack_38);
    acStack_38[uVar2] = ' ';
    sango_text_draw_legacy(5, 0x11, acStack_38);
    sango_battle_load_overview_text(0x36, acStack_38);
    sango_text_draw_legacy(0x24, (short)uVar7 - 0xf, acStack_38);
    sango_battle_draw_overview_rows('\x01', 0);
    uVar2 = 3;
    sango_display_draw_rectangle((short)uVar6 + -1, (short)uVar7 + -1,
                                 (short)((g_battle_map_width + uVar6) * 0x10000 >> 0x10),
                                 (short)((g_battle_map_height + uVar7) * 0x10000 >> 0x10), 3, 0, 0);
    uVar9 = 1;
    uVar8 = 0;
    do
    {
        do
        {
            uVar5 = 0;
            do
            {
                iVar1 = uVar5 * 7;
                if ((&g_first_unit_status)[iVar1] != '\b')
                {
                    sango_display_put_gray_pixel(
                        (short)(((uint8_t)(&g_first_unit_x)[iVar1] + uVar6) * 0x10000 >> 0x10),
                        (short)(((uint8_t)(&g_first_unit_y)[iVar1] + uVar7) * 0x10000 >> 0x10),
                        uVar2, 0);
                    sango_display_put_gray_pixel(
                        (short)(((uint8_t)(&g_first_unit_x)[iVar1] + uVar6) * 0x10000 >> 0x10),
                        (short)(((uint8_t)(&g_first_unit_y)[iVar1] + uVar7) * 0x10000 >> 0x10),
                        uVar2, 0);
                }
                uVar5 = uVar5 + 1 & 0xff;
            } while (uVar5 < 0x14);
            if (uVar2 != 3)
            {
                uVar2 = 0;
            }
            uVar5 = sango_input_wait(0x32, '\x01');
        } while (uVar5 == 0);
        cVar4 = (char)uVar9;
        if (uVar5 == 0x67)
        {
            uVar5 = uVar8 - 0x18;
            if (uVar8 == 0)
                goto LAB_81c02b4c;
        LAB_81c02bd0:
            uVar8 = uVar5 & 0xff;
        LAB_81c02b48:
            cVar4 = (char)uVar9;
        }
        else
        {
            if ((int)uVar5 < 0x68)
            {
                if (uVar5 != 0xb)
                {
                    uVar3 = 0x1c;
                    if ((int)uVar5 < 0xc)
                    {
                        uVar3 = 1;
                    }
                    if (uVar5 != uVar3)
                        goto LAB_81c02b48;
                }
                return;
            }
            if (0x68 < (int)uVar5)
            {
                if ((int)uVar5 < 0x6b)
                {
                    uVar9 = (uint32_t)(uVar9 == 0);
                    uVar8 = 0;
                    goto LAB_81c02b48;
                }
                if (((uVar5 == 0x6c) &&
                     (uVar5 = sango_battle_count_active_units(uVar9), 0x17 < uVar5)) &&
                    (uVar5 = sango_battle_count_active_units(uVar9),
                     (int)uVar8 < (int)(uVar5 - 0x18)))
                {
                    uVar5 = uVar8 + 0x18;
                    goto LAB_81c02bd0;
                }
            }
        }
    LAB_81c02b4c:
        sango_battle_draw_overview_rows(cVar4, uVar8);
    } while (true);
}
#undef acStack_38

/* 原函数 0x81c02c4c */
void sango_battle_draw_overview_rows(char param_1, uint32_t param_2)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define acStack_38 (*(char(*)[5])(abi_storage + 0))
#define auStack_33 (*(uint8_t(*)[3])(abi_storage + 5))
#define auStack_30 (*(uint8_t(*)[16])(abi_storage + 8))

    uint16_t uVar1;
    uint8_t index;
    uint32_t uVar2;
    char *pcVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;

    uVar6 = (uint32_t)(uint8_t)param_1 * 10 & 0xff;
    sango_display_fill_gray_rectangle(0x78, 0, 0xef, 0x13f, 0, 0);
    sango_display_draw_rectangle(0x78, 0, 0xef, 0x13f, 3, 0, 0);
    sango_display_draw_line(0x78, 0xe, 0xef, 0xe, 3, 0, 0);
    sango_display_draw_line(0x78, 0x1c, 0xef, 0x1c, 3, 0, 0);
    uVar2 = sango_battle_is_player_unit(uVar6);
    sango_load_named_text(*(char *)(uVar2 * 0x10 + g_character_table_address + 1) + 0xff,
                          acStack_38);
    uVar2 = bbk_strlen(acStack_38);
    pcVar3 = acStack_38 + (uVar2 & 0xff);
    *pcVar3 = ' ';
    sango_battle_load_overview_text(0x32, pcVar3);
    sango_text_draw_legacy((short)(uVar2 & 0xff) * -3 - 0x52U & 0xff, 2, acStack_38);
    sango_battle_load_overview_text(0x34, acStack_38);
    if (param_1 == '\0')
    {
        uVar2 = (uint32_t)g_battle_attacker_food;
    }
    else
    {
        uVar2 = (uint32_t)g_battle_recon_food;
        if (uVar2 == 0)
        {
            sango_battle_load_overview_text(0x35, auStack_33);
            goto LAB_81c02db4;
        }
    }
    sango_format_integer(uVar2, auStack_33, 10);
LAB_81c02db4:
    sango_text_draw_legacy(0x7b, 0x10, acStack_38);
    uVar5 = (param_2 & 0xff) + uVar6 & 0xff;
    uVar4 = 0;
    uVar2 = uVar5;
    while (true)
    {
        if (10 < (int)((uVar2 & 0xff) - uVar6))
        {
            return;
        }
        index = (&g_battle_roster_first)[uVar2 & 0xff] - 1;
        if ((&g_battle_roster_first)[uVar2 & 0xff] == '\0')
            break;
        uVar1 = *(uint16_t *)((uint32_t)index * 0x10 + g_character_table_address + 10);
        sango_load_named_text(index, acStack_38);
        uVar2 = bbk_strlen(acStack_38);
        sango_memory_fill(acStack_38 + (uVar2 & 0xff), 0x20, 0x14 - (uVar2 & 0xff));
        sango_format_integer((uint32_t)uVar1, auStack_30, 10);
        sango_text_draw_legacy(0x7b, (short)uVar4 * 0xc + 0x1e, acStack_38);
        uVar4 = uVar4 + 1 & 0xff;
        uVar2 = uVar4 + uVar5;
        if (0x17 < uVar4)
        {
            return;
        }
    }
    return;
}
#undef acStack_38
#undef auStack_33
#undef auStack_30

/* 原函数 0x81c02ec0 */
uint32_t sango_battle_count_active_units(uint32_t param_1)
{
    uint32_t uVar1;

    uVar1 = 0;
    do
    {
        if ((&g_battle_roster_first)[uVar1 + ((param_1 & 0xff) * 10 & 0xff)] == '\0')
        {
            return uVar1;
        }
        uVar1 = uVar1 + 1 & 0xff;
    } while (uVar1 < 10);
    return uVar1;
}

/* 原函数 0x81c02f08 */
void sango_battle_load_overview_text(uint32_t param_1, void *param_2)
{
    sango_resource_read_text(1, param_1 & 0xff, param_2);
    return;
}

/* 原函数 0x81c02f30 */
uint32_t sango_battle_is_player_unit(uint32_t param_1)
{
    return (uint8_t)(&g_battle_roster_first)[param_1 & 0xff] - 1 & 0xff;
}

#include "sango_internal.h"

/* 系统菜单、数值选择及电脑执行提示。 */

/* 原函数 0x81c1b2b4 */
uint32_t sango_ui_show_system_menu(void)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define local_30 (*(uint16_t(*)[4])(abi_storage + 0))
#define acStack_28 (*(char(*)[32])(abi_storage + 8))

    uint32_t uVar1;
    uint32_t uVar2;

    sango_resource_read_text(0x40, 0x79, acStack_28);
    local_30[0] = 0x4f;
    local_30[2] = 0x7f;
    local_30[3] = 0x2e;
    local_30[1] = 10;
    uVar1 = sango_ui_choose_option(local_30, 0, acStack_28);
    if (uVar1 == 1)
    {
        sango_save_choose_slot('\0');
        uVar2 = 0;
    }
    else if ((int)uVar1 < 2)
    {
        uVar2 = 1;
    }
    else
    {
        uVar2 = 2;
        if (uVar1 != 2)
        {
            uVar2 = 0;
        }
    }
    return uVar2;
}
#undef local_30
#undef acStack_28

/* 原函数 0x81c1b364 */
uint32_t sango_ui_select_number(uint32_t param_1, uint32_t param_2)
{
    unsigned char abi_storage[61] __attribute__((aligned(8)));
#define local_40 (*(int *)(abi_storage + 24))
#define local_3c (*(int *)(abi_storage + 28))
#define acStack_58 (*(char(*)[7])(abi_storage + 0))
#define local_30 (*(char *)(abi_storage + 40))
#define local_2f (*(char *)(abi_storage + 41))
#define local_2e (*(char *)(abi_storage + 42))
#define acStack_51 (*(char(*)[17])(abi_storage + 7))
#define local_2d (*(char *)(abi_storage + 43))
#define local_2c (*(uint8_t *)(abi_storage + 44))

    bool bVar1;
    short sVar2;
    char cVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint32_t uVar8;
    uint32_t uVar9;

    uVar8 = param_2 & 0xffff;
    if (9999 < uVar8)
    {
        uVar8 = 9999;
    }
    uVar6 = param_1 & 0xffff;
    sango_resource_read_text(0x40, 0x2c, acStack_58);
    sango_text_draw_legacy(0x53, 0x99, acStack_58);
    sango_resource_read_text(0x40, 0x2d, acStack_58);
    sango_format_integer(uVar8, acStack_51, 10);
    sango_text_draw_legacy(0x53, 0xa5, acStack_58);
    uVar4 = bbk_strlen(acStack_51);
    uVar7 = uVar4 - 1 & 0xff;
    uVar9 = 1;
    bVar1 = true;
    uVar4 = uVar7;
LAB_81c1b42c:
    do
    {
        if (!bVar1)
            goto LAB_81c1b4bc;
    LAB_81c1b434:
        while (true)
        {
            cVar3 = (char)uVar6;
            if (uVar7 == 3)
            {
                local_2c = 0;
                local_30 = (char)(uVar6 / 1000) + '0';
                local_2d = cVar3 + (char)(uVar6 / 10) * -10 + '0';
                local_2f = (char)((uVar6 % 1000) / 100) + '0';
                local_2e = (char)((uVar6 % 100) / 10) + '0';
            }
            if (uVar7 == 2)
            {
                local_2d = '\0';
                local_2e = cVar3 + (char)(uVar6 / 10) * -10 + '0';
                local_30 = (char)((uVar6 % 1000) / 100) + '0';
                local_2f = (char)((uVar6 % 100) / 10) + '0';
            }
            if (uVar7 == 1)
            {
                local_2e = '\0';
                local_2f = cVar3 + (char)(uVar6 / 10) * -10 + '0';
                local_30 = (char)((uVar6 % 100) / 10) + '0';
            }
            if (uVar7 == 0)
            {
                local_2f = '\0';
                local_30 = cVar3 + (char)(uVar6 / 10) * -10 + '0';
            }
            sango_text_draw_legacy(0x7d, 0x99, &local_30);
            sVar2 = (short)uVar4 * 6;
            bVar1 = false;
            sango_display_invert_rectangle(sVar2 + 0x7d, 0x99, sVar2 + 0x82, 0xa4, 0);
        LAB_81c1b4bc:
            sango_input_next_event(&local_40);
            if (local_40 != 5)
                goto LAB_81c1b42c;
            if (local_3c != 0x67)
                break;
            if (uVar8 < uVar6 + uVar9)
                goto LAB_81c1b42c;
            uVar6 = uVar6 + uVar9 & 0xffff;
        }
        if (0x67 < local_3c)
        {
            if (local_3c == 0x6a)
            {
                if (uVar7 <= uVar4)
                    goto LAB_81c1b42c;
                uVar4 = uVar4 + 1;
                uVar9 = uVar9 / 10;
            }
            else
            {
                if (0x6a < local_3c)
                {
                    if (((local_3c != 0x6c) || (uVar6 < uVar9)) || ((int)(uVar6 - uVar9) < 0))
                        goto LAB_81c1b42c;
                    uVar6 = uVar6 - uVar9 & 0xffff;
                    goto LAB_81c1b434;
                }
                if ((local_3c != 0x69) || (uVar4 == 0))
                    goto LAB_81c1b42c;
                uVar4 = uVar4 - 1;
                uVar9 = uVar9 * 10;
            }
            uVar4 = uVar4 & 0xff;
            uVar9 = uVar9 & 0xffff;
            goto LAB_81c1b434;
        }
        uVar5 = 0xffff;
        if ((local_3c == 1) || (uVar5 = uVar6, local_3c == 0x1c))
        {
            return uVar5;
        }
    } while (true);
}
#undef local_40
#undef local_3c
#undef acStack_58
#undef local_30
#undef local_2f
#undef local_2e
#undef acStack_51
#undef local_2d
#undef local_2c

/* 原函数 0x81c1b784 */
void sango_ui_show_ai_progress(void)
{
    uint8_t *pbVar1;
    uint32_t uVar2;
    uint8_t *pbVar3;
    uint8_t *destination;
    uint32_t uVar4;

    sango_strategy_present();
    pbVar1 = g_scratch_buffer_address;
    uVar4 = 0;
    uVar2 = sango_strategy_list_rulers((uint32_t)g_player_character, g_scratch_buffer_address);
    destination = pbVar1 + 200;
    pbVar3 = pbVar1;
    if (uVar2 != 0)
    {
        do
        {
            sango_load_named_text(*pbVar3, destination);
            sango_resource_read_text(0x40, 0xa3, pbVar1 + 0xfa);
            bbk_strcat((char *)destination, (char *)(pbVar1 + 0xfa));
            sango_display_fill_gray_rectangle(0x3c, 0x12f, 0xb2, 0x13d, 0, 0);
            sango_display_draw_rectangle(0x3c, 0x12f, 0xb2, 0x13d, 3, 0, 0);
            sango_text_draw_legacy(0x3e, 0x131, (char *)destination);
            sango_input_wait(0x14, '\0');
            uVar4 = uVar4 + 1 & 0xff;
            pbVar3 = pbVar1 + uVar4;
        } while (uVar4 < uVar2);
    }
    sango_strategy_present();
    return;
}

#include "sango_internal.h"

/* 分页表格、宝物及武将列表。 */

/* 原函数 0x81c18350 */
void sango_ui_table_begin(uint8_t param_1, uint8_t param_2, uint8_t param_3, uint8_t param_4,
                          uint8_t *param_5)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(uint8_t **)(abi_storage + 0)) = param_5;
#define param_5 (*(uint8_t **)(abi_storage + 0))

    param_5[7] = param_2;
    param_5[2] = param_3;
    param_5[3] = param_4;
    param_5[6] = param_1;
    *param_5 = param_1;
    param_5[1] = param_2;
    param_5[4] = param_1;
    param_5[5] = param_2;
    return;
}
#undef param_5

/* 原函数 0x81c18380 */
uint32_t sango_ui_table_next_cell(uint8_t param_1, uint8_t param_2, int param_3, uint8_t *param_4,
                                  uint8_t *param_5)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(uint8_t **)(abi_storage + 0)) = param_5;
#define param_5 (*(uint8_t **)(abi_storage + 0))

    char cVar1;
    int iVar2;
    uint32_t uVar3;

    iVar2 = (uint32_t) * (uint8_t *)(param_3 + 5) + (uint32_t)param_2 + -1;
    uVar3 = 0;
    if (iVar2 <= (int)(uint32_t) * (uint8_t *)(param_3 + 3))
    {
        cVar1 = *(uint8_t *)(param_3 + 6) + 1;
        if ((int)((uint32_t) * (uint8_t *)(param_3 + 6) + (uint32_t)param_1 + -1) <=
            (int)(uint32_t) * (uint8_t *)(param_3 + 2))
        {
            *(uint8_t *)(param_3 + 6) = param_1 + cVar1 + -1;
            *(char *)(param_3 + 4) = cVar1;
            uVar3 = 1;
            if ((int)(uint32_t) * (uint8_t *)(param_3 + 7) < iVar2)
            {
                *(uint8_t *)(param_3 + 7) = param_2 + *(uint8_t *)(param_3 + 5) + -1;
            }
            *param_4 = *(uint8_t *)(param_3 + 4);
            *param_5 = *(uint8_t *)(param_3 + 5);
        }
    }
    return uVar3;
}
#undef param_5

/* 原函数 0x81c18410 */
uint32_t sango_ui_table_next_row(uint8_t *param_1)
{
    char cVar1;

    cVar1 = param_1[7];
    if (cVar1 != param_1[3])
    {
        param_1[7] = cVar1 + '\x01';
        param_1[5] = cVar1 + '\x01';
        param_1[6] = *param_1;
        param_1[4] = *param_1;
    }
    return (uint32_t)(cVar1 != param_1[3]);
}

/* 原函数 0x81c18450 */
void sango_ui_draw_item_row(uint8_t param_1, uint32_t param_2, char param_3, char param_4,
                            char param_5)
{
    unsigned char abi_storage[113] __attribute__((aligned(8)));
    (*(char *)(abi_storage + 96)) = param_5;
#define abStack_30 (*(uint8_t(*)[8])(abi_storage + 32))
#define acStack_48 (*(char(*)[24])(abi_storage + 8))
#define auStack_28 (*(uint8_t(*)[8])(abi_storage + 40))
#define local_50 (*(uint8_t *)(abi_storage + 0))
#define local_4f (*(uint8_t(*)[7])(abi_storage + 1))
#define param_5 (*(char *)(abi_storage + 96))

    int iVar1;
    uint32_t uVar2;
    uint8_t *pbVar3;

    uVar2 = param_2 & 0xff;
    sango_ui_table_begin(param_3, param_4, param_3 + param_5 + -1, param_4 + '\f', auStack_28);
    iVar1 = sango_ui_table_next_cell(0x3d, 0xc, (int)auStack_28, &local_50, local_4f);
    if (iVar1 != 0)
    {
        sango_item_read_name(param_1, acStack_48);
        sango_text_draw_centered(local_50 + 0x1e, (uint16_t)local_4f[0], acStack_48);
        sango_resource_read_text(2, 7, abStack_30);
        for (; uVar2 < 5; uVar2 = uVar2 + 1 & 0xff)
        {
            pbVar3 = abStack_30 + uVar2;
            iVar1 = sango_ui_table_next_cell(*pbVar3 * '\x06' + 1, 0xc, (int)auStack_28, &local_50,
                                             local_4f);
            if (iVar1 == 0)
            {
                return;
            }
            sango_item_format_attribute((uint32_t)param_1, (char)uVar2, acStack_48);
            sango_text_draw_centered((uint16_t)*pbVar3 * 3 + (uint16_t)local_50,
                                     (uint16_t)local_4f[0], acStack_48);
        }
    }
    return;
}
#undef abStack_30
#undef acStack_48
#undef auStack_28
#undef local_50
#undef local_4f
#undef param_5

/* 原函数 0x81c185cc */
void sango_item_format_attribute(uint32_t param_1, uint8_t param_2, uint8_t *param_3)
{
    uint8_t bVar1;
    int iVar2;
    uint32_t uVar3;
    uint32_t unaff_s3;

    iVar2 = sango_resource_item(0x42, '\x01', g_resource_package_address);
    iVar2 = iVar2 + (param_1 & 0xff) * 0x42;
    switch (param_2)
    {
    case 0:
        if (*(char *)(iVar2 + 1) == '\0')
        {
            unaff_s3 = 0x47;
        }
        else if (*(char *)(iVar2 + 1) == '\x01')
        {
            unaff_s3 = 0x48;
        }
        goto LAB_81c18654;
    case 1:
        uVar3 = (uint32_t) * (uint8_t *)(iVar2 + 0x3e);
        break;
    case 2:
        uVar3 = (uint32_t) * (uint8_t *)(iVar2 + 0x3f);
        break;
    case 3:
        uVar3 = (uint32_t) * (uint8_t *)(iVar2 + 0x40);
        break;
    case 4:
        bVar1 = *(uint8_t *)(iVar2 + 0x41);
        if (bVar1 == 1)
        {
            unaff_s3 = 0x49;
        }
        else if (bVar1 < 2)
        {
            if (bVar1 == 0)
            {
                unaff_s3 = 0x32;
            }
        }
        else if (bVar1 == 2)
        {
            unaff_s3 = 0x4a;
        }
        else if (bVar1 == 3)
        {
            unaff_s3 = 0x4b;
        }
    LAB_81c18654:
        sango_resource_read_text(0x40, unaff_s3, param_3);
    default:
        goto switchD_81c18634_default;
    }
    sango_format_integer(uVar3, param_3, 10);
switchD_81c18634_default:
    return;
}

/* 原函数 0x81c18704 */
uint32_t sango_ui_draw_item_header(uint32_t param_1, char param_2, char param_3, char param_4)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define auStack_28 (*(uint8_t(*)[8])(abi_storage + 32))
#define local_48 (*(uint8_t *)(abi_storage + 0))
#define local_47 (*(uint8_t(*)[7])(abi_storage + 1))
#define abStack_30 (*(uint8_t(*)[8])(abi_storage + 24))
#define acStack_40 (*(char(*)[16])(abi_storage + 8))

    int iVar1;
    uint32_t uVar2;
    uint8_t *pbVar3;

    sango_ui_table_begin(param_2, param_3, param_2 + param_4 + -1, param_3 + '\f', auStack_28);
    iVar1 = sango_ui_table_next_cell(0x3d, 0xc, (int)auStack_28, &local_48, local_47);
    uVar2 = 0;
    if (iVar1 != 0)
    {
        sango_resource_read_text(0x40, 0x41, acStack_40);
        sango_text_draw_centered(local_48 + 0x1e, (uint16_t)local_47[0], acStack_40);
        sango_resource_read_text(2, 7, abStack_30);
        uVar2 = param_1 & 0xff;
        while (true)
        {
            pbVar3 = abStack_30 + uVar2;
            if (4 < uVar2)
                break;
            iVar1 = sango_ui_table_next_cell(*pbVar3 * '\x06' + 1, 0xc, (int)auStack_28, &local_48,
                                             local_47);
            if (iVar1 == 0)
            {
                return uVar2;
            }
            sango_resource_read_text(0x40, uVar2 + 0x42 & 0xff, acStack_40);
            sango_text_draw_centered((uint16_t)*pbVar3 * 3 + (uint16_t)local_48,
                                     (uint16_t)local_47[0], acStack_40);
            uVar2 = uVar2 + 1 & 0xff;
        }
    }
    return uVar2;
}
#undef auStack_28
#undef local_48
#undef local_47
#undef abStack_30
#undef acStack_40

/* 原函数 0x81c18874 */
uint32_t sango_ui_select_item(int param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4,
                              uint8_t param_5, uint8_t param_6)
{
    unsigned char abi_storage[117] __attribute__((aligned(8)));
    (*(uint8_t *)(abi_storage + 96)) = param_5;
    (*(uint8_t *)(abi_storage + 100)) = param_6;
#define param_5 (*(uint8_t *)(abi_storage + 96))
#define param_6 (*(uint8_t *)(abi_storage + 100))
#define local_50 (*(uint8_t(*)[8])(abi_storage + 0))
#define local_48 (*(int *)(abi_storage + 8))
#define local_44 (*(int *)(abi_storage + 12))
#define local_38 (*(uint32_t *)(abi_storage + 24))
#define local_34 (*(uint32_t *)(abi_storage + 28))
#define local_30 (*(int *)(abi_storage + 32))
#define local_2c (*(int *)(abi_storage + 36))

    bool bVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    short sVar4;
    char cVar5;
    char cVar6;
    char cVar7;
    int iVar8;
    short sVar9;
    uint8_t *pbVar10;
    uint32_t uVar11;
    uint32_t uVar12;
    uint32_t uVar13;
    uint32_t uVar14;
    uint32_t uVar15;
    uint32_t uVar16;
    uint32_t uVar17;
    uint32_t uVar18;

    local_38 = (uint32_t)param_5;
    uVar15 = param_2 & 0xff;
    uVar11 = param_4 & 0xff;
    if (uVar15 == 0)
    {
        return 0xff;
    }
    cVar7 = (param_5 - (char)param_3) + '\x01';
    local_34 = 0;
    uVar16 = 0;
    bVar1 = true;
    uVar14 = (int)((param_6 - uVar11) + 1) / 0xc - 1U & 0xff;
    if (uVar15 < uVar14)
    {
        uVar14 = uVar15;
    }
    local_30 = uVar14 * 2;
    sango_display_draw_rectangle((short)(param_3 & 0xff), (short)uVar11, (uint16_t)param_5,
                                 ((short)uVar11 + (short)uVar14 * 0xc + 0xcU & 0xff) + 1, 3, 0, 0);
    uVar2 = (param_3 & 0xff) + 1;
    uVar13 = uVar2 & 0xff;
    local_38 = local_38 - 1 & 0xff;
    local_2c = (uVar13 + 0x3b) * 0x10000;
    uVar12 = uVar11 + 1 & 0xff;
    local_50[0] = 0;
    uVar18 = 0;
    do
    {
        sVar4 = (short)uVar13;
        uVar17 = uVar16;
        if (bVar1)
            goto LAB_81c18a44;
        while (sango_input_next_event(&local_48), local_48 == 5)
        {
            sVar9 = (short)((uint32_t)local_2c >> 0x10);
            if (local_44 == 0x67)
            {
                if (uVar18 == 0)
                    break;
                iVar8 = uVar12 + (uVar18 - uVar16) * 0xc;
                sango_display_invert_rectangle(
                    sVar4, (short)((uint32_t)((iVar8 + 0xc) * 0x10000) >> 0x10), sVar9,
                    (short)((uint32_t)((iVar8 + 0x17) * 0x10000) >> 0x10), 0);
                uVar17 = uVar18 - 1 & 0xff;
                iVar8 = uVar17 - uVar16;
                uVar18 = uVar17;
                if (uVar16 <= uVar17)
                {
                LAB_81c18bbc:
                    iVar8 = uVar12 + iVar8 * 0xc;
                    sango_display_invert_rectangle(
                        sVar4, (short)((uint32_t)((iVar8 + 0xc) * 0x10000) >> 0x10), sVar9,
                        (short)((uint32_t)((iVar8 + 0x17) * 0x10000) >> 0x10), 0);
                    uVar18 = uVar17;
                    break;
                }
            }
            else
            {
                if (local_44 < 0x68)
                {
                    if (local_44 == 1)
                    {
                        return 0xff;
                    }
                    if (local_44 == 0x1c)
                    {
                        return uVar18;
                    }
                    break;
                }
                if (local_44 == 0x6a)
                {
                    if (4 < local_50[local_34 + 1])
                        break;
                    local_34 = local_34 + 1;
                }
                else
                {
                    if (0x6a < local_44)
                    {
                        if ((local_44 == 0x6c) && ((int)uVar18 < (int)(uVar15 - 1)))
                        {
                            iVar8 = uVar12 + (uVar18 - uVar16) * 0xc;
                            sango_display_invert_rectangle(
                                sVar4, (short)((uint32_t)((iVar8 + 0xc) * 0x10000) >> 0x10), sVar9,
                                (short)((uint32_t)((iVar8 + 0x17) * 0x10000) >> 0x10), 0);
                            uVar18 = uVar18 + 1 & 0xff;
                            if (uVar18 < uVar16 + uVar14)
                            {
                                iVar8 = uVar18 - uVar16;
                                uVar17 = uVar18;
                                goto LAB_81c18bbc;
                            }
                            uVar17 = (uVar18 - uVar14) + 1 & 0xff;
                            goto LAB_81c18a44;
                        }
                        break;
                    }
                    if ((local_44 != 0x69) || (local_50[local_34] == 0))
                        break;
                    local_34 = local_34 - 1;
                }
                local_34 = local_34 & 0xff;
                uVar17 = uVar16;
            }
        LAB_81c18a44:
            sango_display_fill_gray_rectangle(
                sVar4, (short)uVar12, (short)local_38,
                (short)((uVar12 + (local_30 + uVar14) * 4 + 0xb) * 0x10000 >> 0x10), 0, 0);
            uVar16 = local_34;
            pbVar10 = local_50 + local_34;
            cVar5 = (char)uVar2;
            cVar6 = (char)(uVar11 + 1);
            uVar3 = sango_ui_draw_item_header((uint32_t)*pbVar10, cVar5, cVar6, cVar7);
            local_50[uVar16 + 1] = (uint8_t)uVar3;
            uVar16 = 0;
            if (uVar14 != 0)
            {
                iVar8 = 0;
                do
                {
                    if (uVar15 <= uVar16)
                        break;
                    sango_ui_draw_item_row(
                        *(uint8_t *)(param_1 + uVar17 + uVar16), (uint32_t)*pbVar10, cVar5,
                        cVar6 + ((char)iVar8 + (char)uVar16) * '\x04' + '\f', cVar7);
                    uVar16 = uVar16 + 1 & 0xff;
                    iVar8 = uVar16 << 1;
                } while (uVar16 < uVar14);
            }
            iVar8 = uVar12 + (uVar18 - uVar17) * 0xc;
            bVar1 = false;
            sango_display_invert_rectangle(
                sVar4, (short)((uint32_t)((iVar8 + 0xc) * 0x10000) >> 0x10),
                (short)((uint32_t)local_2c >> 0x10),
                (short)((uint32_t)((iVar8 + 0x17) * 0x10000) >> 0x10), 0);
            uVar16 = uVar17;
        }
    } while (true);
}
#undef param_5
#undef param_6
#undef local_50
#undef local_48
#undef local_44
#undef local_38
#undef local_34
#undef local_30
#undef local_2c

/* 原函数 0x81c18c80 */
void sango_item_read_name(char item_id, void *name)
{
    sango_resource_read_text(0x49, (uint8_t)item_id + 1 & 0xff, name);
    return;
}

/* 原函数 0x81c18cac */
void sango_ui_draw_character_row(uint32_t param_1, uint32_t param_2, char param_3, char param_4,
                                 char param_5)
{
    unsigned char abi_storage[121] __attribute__((aligned(8)));
    (*(char *)(abi_storage + 104)) = param_5;
#define local_58 (*(uint8_t *)(abi_storage + 0))
#define local_57 (*(uint8_t(*)[7])(abi_storage + 1))
#define param_5 (*(char *)(abi_storage + 104))
#define abStack_38 (*(uint8_t(*)[16])(abi_storage + 32))
#define acStack_50 (*(char(*)[24])(abi_storage + 8))
#define auStack_28 (*(uint8_t(*)[8])(abi_storage + 48))

    int iVar1;
    uint32_t uVar2;
    uint16_t unaff_s1;
    uint8_t *pbVar3;

    uVar2 = param_2 & 0xff;
    sango_ui_table_begin(param_3, param_4, param_3 + param_5 + -1, param_4 + '\f', auStack_28);
    iVar1 = sango_ui_table_next_cell(0x31, 0xc, (int)auStack_28, &local_58, local_57);
    if (iVar1 != 0)
    {
        if (g_scenario_id_view2 == 2)
        {
            unaff_s1 = 0x46;
        }
        else if (g_scenario_id_view2 < 3)
        {
            if (g_scenario_id_view2 == 1)
            {
                unaff_s1 = 0x3e;
            }
        }
        else if (g_scenario_id_view2 == 3)
        {
            unaff_s1 = 0x47;
        }
        else if (g_scenario_id_view2 == 4)
        {
            unaff_s1 = 0x48;
        }
        sango_resource_read_text(unaff_s1, (param_1 & 0xff) + 1 & 0xff, acStack_50);
        sango_text_draw_centered(local_58 + 0x18, (uint16_t)local_57[0], acStack_50);
        sango_resource_read_text(2, 8, abStack_38);
        for (; uVar2 < 0xd; uVar2 = uVar2 + 1 & 0xff)
        {
            pbVar3 = abStack_38 + uVar2;
            iVar1 = sango_ui_table_next_cell(*pbVar3 * '\x06' + 1, 0xc, (int)auStack_28, &local_58,
                                             local_57);
            if (iVar1 == 0)
            {
                return;
            }
            sango_character_format_attribute(param_1 & 0xff, (char)uVar2, acStack_50);
            sango_text_draw_centered((uint16_t)*pbVar3 * 3 + (uint16_t)local_58,
                                     (uint16_t)local_57[0], acStack_50);
        }
    }
    return;
}
#undef local_58
#undef local_57
#undef param_5
#undef abStack_38
#undef acStack_50
#undef auStack_28

/* 原函数 0x81c18e88 */
void sango_character_format_attribute(uint32_t param_1, uint8_t param_2, uint8_t *param_3)
{
    char cVar1;
    uint16_t uVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    int iVar5;
    uint32_t in_t1;

    uVar3 = param_1 & 0xff;
    iVar5 = uVar3 * 0x10;
    uVar4 = (uint32_t) * (uint8_t *)(iVar5 + g_character_table_address + 1);
    switch (param_2)
    {
    case 0:
        if (uVar4 == 0xff)
        {
            uVar2 = 0x40;
            in_t1 = 0x31;
        }
        else
        {
            uVar2 = 0x40;
            if (uVar4 == uVar3 + 1)
            {
                in_t1 = 0x30;
            }
            else if (uVar4 == 0)
            {
                uVar2 = 0x40;
                in_t1 = 0x2f;
            }
            else
            {
                if (g_scenario_id_view2 == 2)
                {
                    uVar3 = 0x46;
                }
                else
                {
                    uVar3 = in_t1;
                    if (g_scenario_id_view2 < 3)
                    {
                        if (g_scenario_id_view2 == 1)
                        {
                            uVar3 = 0x3e;
                        }
                    }
                    else if (g_scenario_id_view2 == 3)
                    {
                        uVar3 = 0x47;
                    }
                    else if (g_scenario_id_view2 == 4)
                    {
                        uVar3 = 0x48;
                    }
                }
                in_t1 = (uVar4 - 1 & 0xff) + 1 & 0xff;
                uVar2 = (uint16_t)uVar3;
            }
        }
        goto LAB_81c18f2c;
    case 1:
        uVar3 = sango_character_find_city((char)param_1);
        sango_city_read_name((char)uVar3, param_3);
        return;
    case 2:
        uVar3 = (uint32_t) * (uint8_t *)(iVar5 + g_character_table_address + 2);
        break;
    case 3:
        uVar3 = (uint32_t) * (uint8_t *)(iVar5 + g_character_table_address + 3);
        break;
    case 4:
        uVar3 = (uint32_t) * (uint8_t *)(iVar5 + g_character_table_address + 4);
        break;
    case 5:
        if ((uVar4 == uVar3 + 1) || (uVar4 == 0))
        {
            uVar2 = 0x40;
            in_t1 = 0x33;
            goto LAB_81c18f2c;
        }
        uVar3 = (uint32_t) * (uint8_t *)(iVar5 + g_character_table_address + 5);
        break;
    case 6:
        uVar3 = (uint32_t) * (uint8_t *)(iVar5 + g_character_table_address + 7);
        break;
    case 7:
        uVar3 = (uint32_t) * (uint8_t *)(iVar5 + g_character_table_address + 8);
        break;
    case 8:
        switch (*(uint8_t *)(iVar5 + g_character_table_address + 9))
        {
        case 0:
            in_t1 = 0x11;
            break;
        case 1:
            in_t1 = 0x12;
            break;
        case 2:
            in_t1 = 0x13;
            break;
        case 3:
            in_t1 = 0x14;
            break;
        case 4:
            in_t1 = 0x15;
            break;
        case 5:
            in_t1 = 0x16;
        }
        uVar2 = 0x40;
    LAB_81c18f2c:
        sango_resource_read_text(uVar2, in_t1, param_3);
        return;
    case 9:
        uVar3 = (uint32_t) * (uint16_t *)(iVar5 + g_character_table_address + 10);
        break;
    case 10:
        uVar3 = (uint32_t) * (uint8_t *)(iVar5 + g_character_table_address + 0xe);
        break;
    case 0xb:
        *param_3 = 0;
        cVar1 = *(char *)(iVar5 + g_character_table_address + 0xc);
        goto LAB_81c190cc;
    case 0xc:
        *param_3 = 0;
        cVar1 = *(char *)(iVar5 + g_character_table_address + 0xd);
    LAB_81c190cc:
        if (cVar1 != '\0')
        {
            sango_item_read_name(cVar1 + -1, param_3);
        }
    default:
        goto switchD_81c18ecc_default;
    }
    sango_format_integer(uVar3, param_3, 10);
switchD_81c18ecc_default:
    return;
}

/* 原函数 0x81c19100 */
uint32_t sango_ui_draw_character_header(uint32_t param_1, char param_2, char param_3, char param_4)
{
    unsigned char abi_storage[64] __attribute__((aligned(8)));
#define local_4f (*(uint8_t(*)[7])(abi_storage + 1))
#define auStack_28 (*(uint8_t(*)[8])(abi_storage + 40))
#define abStack_38 (*(uint8_t(*)[16])(abi_storage + 24))
#define acStack_48 (*(char(*)[16])(abi_storage + 8))
#define local_50 (*(uint8_t *)(abi_storage + 0))

    int iVar1;
    uint32_t uVar2;
    uint8_t *pbVar3;

    sango_ui_table_begin(param_2, param_3, param_2 + param_4 + -1, param_3 + '\f', auStack_28);
    iVar1 = sango_ui_table_next_cell(0x31, 0xc, (int)auStack_28, &local_50, local_4f);
    uVar2 = 0;
    if (iVar1 != 0)
    {
        sango_resource_read_text(0x40, 0x17, acStack_48);
        sango_text_draw_centered(local_50 + 0x18, (uint16_t)local_4f[0], acStack_48);
        sango_resource_read_text(2, 8, abStack_38);
        uVar2 = param_1 & 0xff;
        while (true)
        {
            pbVar3 = abStack_38 + uVar2;
            if (0xc < uVar2)
                break;
            iVar1 = sango_ui_table_next_cell(*pbVar3 * '\x06' + 1, 0xc, (int)auStack_28, &local_50,
                                             local_4f);
            if (iVar1 == 0)
            {
                return uVar2;
            }
            sango_resource_read_text(0x40, uVar2 + 0x18 & 0xff, acStack_48);
            sango_text_draw_centered((uint16_t)*pbVar3 * 3 + (uint16_t)local_50,
                                     (uint16_t)local_4f[0], acStack_48);
            uVar2 = uVar2 + 1 & 0xff;
        }
    }
    return uVar2;
}
#undef local_4f
#undef auStack_28
#undef abStack_38
#undef acStack_48
#undef local_50

/* 原函数 0x81c19270 */
uint32_t sango_ui_select_character(int param_1, uint32_t param_2, uint32_t param_3,
                                   uint32_t param_4, uint8_t param_5, uint8_t param_6)
{
    unsigned char abi_storage[117] __attribute__((aligned(8)));
    (*(uint8_t *)(abi_storage + 96)) = param_5;
    (*(uint8_t *)(abi_storage + 100)) = param_6;
#define local_50 (*(uint8_t(*)[8])(abi_storage + 0))
#define local_48 (*(int *)(abi_storage + 8))
#define local_44 (*(int *)(abi_storage + 12))
#define local_38 (*(uint32_t *)(abi_storage + 24))
#define local_34 (*(uint32_t *)(abi_storage + 28))
#define local_30 (*(uint32_t *)(abi_storage + 32))
#define param_5 (*(uint8_t *)(abi_storage + 96))
#define local_2c (*(int *)(abi_storage + 36))
#define param_6 (*(uint8_t *)(abi_storage + 100))

    bool bVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    short sVar4;
    char cVar5;
    short sVar6;
    int iVar7;
    char cVar8;
    short sVar9;
    char cVar10;
    short sVar11;
    int iVar12;
    uint32_t uVar13;
    uint8_t *pbVar14;
    uint32_t uVar15;
    uint32_t uVar16;
    uint32_t uVar17;
    uint32_t uVar18;
    uint32_t uVar19;
    uint32_t uVar20;
    uint32_t uVar21;

    local_38 = (uint32_t)param_5;
    uVar19 = param_2 & 0xff;
    uVar15 = param_4 & 0xff;
    if (uVar19 == 0)
    {
        return 0xff;
    }
    cVar10 = (param_5 - (char)param_3) + -1;
    local_30 = 0;
    uVar20 = 0;
    bVar1 = true;
    uVar18 = (int)((param_6 - uVar15) + -1) / 0xc - 1U & 0xff;
    if (uVar19 < uVar18)
    {
        uVar18 = uVar19;
    }
    local_34 = uVar15 + uVar18 * 0xc + 0xc & 0xff;
    sango_display_draw_rectangle((short)(param_3 & 0xff), (short)uVar15, (uint16_t)param_5,
                                 (short)local_34 + 1, 3, 0, 0);
    uVar2 = (param_3 & 0xff) + 1;
    uVar17 = uVar2 & 0xff;
    local_38 = local_38 - 1 & 0xff;
    local_2c = (uVar17 + 0x2f) * 0x10000;
    uVar16 = uVar15 + 1 & 0xff;
    local_50[0] = 0;
    uVar21 = 0;
    do
    {
        sVar9 = (short)local_38;
        sVar4 = (short)uVar17;
        uVar13 = uVar21;
        if (bVar1)
            goto LAB_81c1947c;
        while (sango_input_next_event(&local_48), uVar21 = uVar13, local_48 == 5)
        {
            sVar9 = (short)((uint32_t)local_2c >> 0x10);
            if (local_44 == 0x68)
            {
                if (uVar20 == 0)
                    break;
                if (uVar20 < uVar18)
                {
                    uVar20 = 1;
                }
                else
                {
                    uVar20 = (uVar20 - uVar18) + 1 & 0xff;
                }
                bVar1 = true;
            LAB_81c19418:
                if (uVar20 == 0)
                    break;
                iVar7 = uVar16 + (uVar20 - uVar13) * 0xc;
                sango_display_invert_rectangle(
                    sVar4, (short)((uint32_t)((iVar7 + 0xc) * 0x10000) >> 0x10), sVar9,
                    (short)((uint32_t)((iVar7 + 0x17) * 0x10000) >> 0x10), 0);
                uVar21 = uVar20 - 1 & 0xff;
                uVar20 = uVar21;
                if (uVar13 <= uVar21)
                {
                    iVar7 = uVar16 + (uVar21 - uVar13) * 0xc;
                    sVar6 = (short)((uint32_t)((iVar7 + 0xc) * 0x10000) >> 0x10);
                    sVar11 = (short)((uint32_t)((iVar7 + 0x17) * 0x10000) >> 0x10);
                LAB_81c1959c:
                    sango_display_invert_rectangle(sVar4, sVar6, sVar9, sVar11, 0);
                    uVar21 = uVar13;
                    break;
                }
            }
            else
            {
                if (local_44 < 0x69)
                {
                    if (local_44 == 0x1c)
                    {
                        return uVar20;
                    }
                    if (local_44 < 0x1d)
                    {
                        if (local_44 == 1)
                        {
                            return 0xff;
                        }
                    }
                    else if (local_44 == 0x67)
                        goto LAB_81c19418;
                    break;
                }
                if (local_44 != 0x6a)
                {
                    if (local_44 < 0x6a)
                    {
                        uVar13 = local_30 - 1;
                        if (local_50[local_30] != 0)
                            goto LAB_81c196c8;
                        break;
                    }
                    if (local_44 != 0x6c)
                    {
                        if (local_44 != 0x6d)
                            break;
                        if ((int)uVar20 < (int)(uVar19 - 2))
                        {
                            uVar20 = (uVar20 + uVar18) - 1 & 0xff;
                            if ((int)(uVar19 - 1) <= (int)uVar20)
                            {
                                uVar20 = uVar19 - 2 & 0xff;
                            }
                            bVar1 = true;
                        }
                    }
                    if ((int)uVar20 < (int)(uVar19 - 1))
                    {
                        iVar12 = uVar16 + (uVar20 - uVar13) * 0xc;
                        iVar7 = iVar12 + 0xc;
                        if (iVar7 < 0x8c)
                        {
                            sango_display_invert_rectangle(
                                sVar4, (short)((uint32_t)(iVar7 * 0x10000) >> 0x10), sVar9,
                                (short)((uint32_t)((iVar12 + 0x17) * 0x10000) >> 0x10), 0);
                        }
                        uVar20 = uVar20 + 1 & 0xff;
                        if (uVar13 + uVar18 <= uVar20)
                        {
                            uVar21 = (uVar20 - uVar18) + 1 & 0xff;
                            goto LAB_81c19478;
                        }
                        iVar7 = uVar16 + (uVar20 - uVar13) * 0xc;
                        sVar6 = (short)((uint32_t)((iVar7 + 0xc) * 0x10000) >> 0x10);
                        sVar11 = (short)((uint32_t)((iVar7 + 0x17) * 0x10000) >> 0x10);
                        sVar9 = (short)((uint32_t)local_2c >> 0x10);
                        goto LAB_81c1959c;
                    }
                    break;
                }
                if (0xc < local_50[local_30 + 1])
                    break;
                uVar13 = local_30 + 1;
            LAB_81c196c8:
                local_30 = uVar13 & 0xff;
            }
        LAB_81c19478:
            sVar9 = (short)local_38;
        LAB_81c1947c:
            sango_display_fill_gray_rectangle(sVar4, (short)uVar16, sVar9, (short)local_34, 0, 0);
            uVar13 = local_30;
            pbVar14 = local_50 + local_30;
            cVar5 = (char)uVar2;
            cVar8 = (char)(uVar15 + 1);
            uVar3 = sango_ui_draw_character_header((uint32_t)*pbVar14, cVar5, cVar8, cVar10);
            local_50[uVar13 + 1] = (uint8_t)uVar3;
            uVar13 = 0;
            if (uVar18 != 0)
            {
                iVar7 = 0;
                do
                {
                    if (uVar19 <= uVar13)
                        break;
                    sango_ui_draw_character_row(
                        (uint32_t) * (uint8_t *)(param_1 + uVar21 + uVar13), (uint32_t)*pbVar14,
                        cVar5, cVar8 + ((char)iVar7 + (char)uVar13) * '\x04' + '\f', cVar10);
                    uVar13 = uVar13 + 1 & 0xff;
                    iVar7 = uVar13 << 1;
                } while (uVar13 < uVar18);
            }
            iVar12 = uVar16 + (uVar20 - uVar21) * 0xc;
            iVar7 = iVar12 + 0xc;
            uVar13 = uVar21;
            if (iVar7 < 0x8c)
            {
                sango_display_invert_rectangle(
                    sVar4, (short)((uint32_t)(iVar7 * 0x10000) >> 0x10),
                    (short)((uint32_t)local_2c >> 0x10),
                    (short)((uint32_t)((iVar12 + 0x17) * 0x10000) >> 0x10), 0);
                bVar1 = false;
            }
            else
            {
                bVar1 = false;
            }
        }
    } while (true);
}
#undef local_50
#undef local_48
#undef local_44
#undef local_38
#undef local_34
#undef local_30
#undef param_5
#undef local_2c
#undef param_6

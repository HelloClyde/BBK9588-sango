#include "sango_internal.h"

/* 内政、俘虏、赏赐与交易等城市命令。 */

/* 原函数 0x81c0b6f0 */
uint32_t sango_strategy_resolve_search(int param_1)
{
    bool bVar1;
    uint8_t bVar2;
    uint8_t bVar3;
    char *destination;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint8_t index;
    int iVar7;
    uint32_t uVar8;
    uint32_t uVar9;
    uint32_t unaff_s5;
    uint32_t uVar10;
    char *source;

    sango_strategy_present();
    destination = g_scratch_buffer_address;
    uVar4 = bbk_rand();
    uVar8 = uVar4 + 3;
    if (-1 < (int)uVar4)
    {
        uVar8 = uVar4;
    }
    bVar2 = *(uint8_t *)(param_1 + 1);
    uVar9 = (uint32_t)bVar2;
    uVar8 = uVar4 + ((int)uVar8 >> 2) * -4 & 0xff;
    iVar7 = uVar9 * 0x10 + g_character_table_address;
    uVar4 = (uint32_t) * (uint8_t *)(iVar7 + 4);
    source = destination + 0x28;
    bVar3 = *(uint8_t *)(iVar7 + 1);
    uVar10 = (uint32_t)bVar3;
    if (uVar8 == 1)
    {
        uVar8 = 0;
        uVar5 = bbk_rand();
        unaff_s5 = (int)uVar5 % 0x96 & 0xff;
        uVar5 = (int)uVar5 % 0x96 & 1;
        if (unaff_s5 < uVar4)
        {
            if (uVar5 == 0)
            {
                uVar5 = sango_city_list_available_characters((uint32_t) * (uint8_t *)(param_1 + 2),
                                                             (int)destination);
                if (uVar5 != 0)
                {
                    uVar6 = bbk_rand();
                    if (uVar5 == 0)
                    {
                        sango_legacy_trap(7);
                    }
                    unaff_s5 = 0;
                    index = destination[(int)uVar6 % (int)uVar5 & 0xff];
                    iVar7 = sango_resource_item(0x3f, g_scenario_id, g_resource_package_address);
                    uVar5 = (uint32_t) * (uint8_t *)(iVar7 + (uint32_t)index * 3 + 1);
                    if (uVar5 - 1 == uVar9)
                    {
                    LAB_81c0bc08:
                        unaff_s5 = 1;
                        iVar7 = (uint32_t)index * 0x10;
                        *(uint8_t *)(iVar7 + g_character_table_address + 1) = bVar3;
                        iVar7 = iVar7 + g_character_table_address;
                        uVar4 = bbk_rand();
                        *(char *)(iVar7 + 5) =
                            (char)uVar4 + (char)((int)uVar4 / 0x1e) * -0x1e + 'F';
                    }
                    else if (uVar5 == 0)
                    {
                        uVar9 = bbk_rand();
                        unaff_s5 = 2;
                        if (((int)uVar9 % 0x6e & 0xffU) < uVar4)
                            goto LAB_81c0bc08;
                    }
                    uVar9 = (uint32_t)g_player_character;
                    if (uVar10 != uVar9 + 1)
                        goto LAB_81c0b79c;
                    uVar8 = 1;
                    if (unaff_s5 == 0)
                    {
                        sango_resource_read_text(0x40, 100, destination);
                        index = bVar2;
                    }
                    else
                    {
                        sango_resource_read_text(0x40, 99, destination);
                        sango_load_named_text(index, source);
                        bbk_strcat(destination, source);
                        sango_ui_show_character_message(bVar2, destination);
                        if (unaff_s5 == 1)
                        {
                            uVar9 = bbk_rand();
                            uVar4 = uVar9 + 3;
                            if (-1 < (int)uVar9)
                            {
                                uVar4 = uVar9;
                            }
                            uVar4 = (uVar9 + ((int)uVar4 >> 2) * -4) - 0x7a;
                        LAB_81c0bb8c:
                            unaff_s5 = uVar4 & 0xff;
                        }
                        else if (unaff_s5 == 2)
                        {
                            uVar9 = bbk_rand();
                            uVar4 = uVar9 + 3;
                            if (-1 < (int)uVar9)
                            {
                                uVar4 = uVar9;
                            }
                            uVar4 = (uVar9 + ((int)uVar4 >> 2) * -4) - 0x76;
                            goto LAB_81c0bb8c;
                        }
                        sango_resource_read_text(0x40, unaff_s5, destination);
                    }
                    sango_ui_show_character_message(index, destination);
                }
            }
            else if ((uVar5 == 1) && (uVar4 = sango_city_find_item(
                                          (uint32_t) * (uint8_t *)(param_1 + 2), (int)destination),
                                      uVar4 != 0))
            {
                uVar5 = bbk_rand();
                if (uVar4 == 0)
                {
                    sango_legacy_trap(7);
                }
                bVar3 = destination[(int)uVar5 % (int)uVar4 & 0xff];
                iVar7 = sango_resource_item(0x43, g_scenario_id, g_resource_package_address);
                uVar4 = (uint32_t) * (uint8_t *)(iVar7 + (uint32_t)bVar3 * 3 + 1);
                if ((uVar4 == 0) || (uVar4 - 1 == uVar9))
                {
                    bVar1 = uVar10 == g_player_character + 1;
                    if (bVar1)
                    {
                        sango_resource_read_text(0x40, 99, destination);
                        sango_item_read_name(bVar3, source);
                        bbk_strcat(destination, source);
                        sango_ui_show_character_message(bVar2, destination);
                    }
                    uVar8 = (uint32_t)bVar1;
                    sango_character_add_item(bVar3);
                }
            }
        }
    }
    else if (1 < uVar8)
    {
        if (uVar8 == 2)
        {
            uVar5 = bbk_rand();
            if (uVar4 == 0)
            {
                sango_legacy_trap(7);
            }
            uVar9 = (uint32_t)g_player_character;
            unaff_s5 = (int)uVar5 % (int)(uVar4 << 1) + 10U & 0xff;
            (&g_first_city_money)[(uint32_t) * (uint8_t *)(param_1 + 2) * 0x12] =
                (&g_first_city_money)[(uint32_t) * (uint8_t *)(param_1 + 2) * 0x12] +
                (short)unaff_s5;
            goto LAB_81c0b79c;
        }
        if (uVar8 == 3)
        {
            uVar5 = bbk_rand();
            if (uVar4 == 0)
            {
                sango_legacy_trap(7);
            }
            uVar9 = (uint32_t)g_player_character;
            unaff_s5 = (int)uVar5 % (int)(uVar4 << 1) + 10U & 0xff;
            (&g_first_city_food)[(uint32_t) * (uint8_t *)(param_1 + 2) * 0x12] =
                (&g_first_city_food)[(uint32_t) * (uint8_t *)(param_1 + 2) * 0x12] +
                (short)unaff_s5;
            goto LAB_81c0b79c;
        }
    }
    uVar9 = (uint32_t)g_player_character;
LAB_81c0b79c:
    if ((uVar10 == uVar9 + 1) && (uVar8 != 1))
    {
        if (uVar8 == 0)
        {
            sango_resource_read_text(0x40, 0x65, destination);
        }
        else
        {
            sango_resource_read_text(0x40, uVar8 + 100 & 0xff, destination);
            sango_format_integer(unaff_s5, source, 10);
            bbk_strcat(destination, source);
        }
        sango_ui_show_character_message(bVar2, destination);
        bVar3 = *(uint8_t *)(param_1 + 2);
    }
    else
    {
        bVar3 = *(uint8_t *)(param_1 + 2);
    }
    sango_city_add_character((uint32_t)bVar3, bVar2);
    return 1;
}

/* 原函数 0x81c0bc70 */
uint32_t sango_strategy_resolve_sow_discord(int param_1)
{
    uint8_t bVar1;
    uint8_t bVar2;
    uint8_t bVar3;
    bool bVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    char *pcVar7;
    int iVar8;
    int iVar9;

    bVar1 = *(uint8_t *)(param_1 + 1);
    bVar2 = *(uint8_t *)(param_1 + 3);
    iVar9 = (uint32_t)bVar1 * 0x10;
    iVar8 = g_character_table_address + (uint32_t)bVar2 * 0x10;
    bVar4 = false;
    if (*(char *)(iVar8 + 1) != *(char *)(iVar9 + g_character_table_address + 1))
    {
        uVar6 = ((uint32_t) * (uint8_t *)(iVar9 + g_character_table_address + 4) -
                 (uint32_t) * (uint8_t *)(iVar8 + 4)) +
                    0x32 &
                0xff;
        uVar5 = bbk_rand();
        if (((int)uVar5 % 100 & 0xffU) <= uVar6)
        {
            switch (*(uint8_t *)(iVar8 + 6))
            {
            case 0:
                uVar6 = 2;
                break;
            case 1:
                uVar6 = 5;
                break;
            case 2:
                uVar6 = 4;
                break;
            case 3:
                uVar6 = 3;
                break;
            case 4:
                uVar6 = 1;
            }
            bVar3 = *(uint8_t *)(iVar8 + 5);
            *(uint8_t *)(iVar8 + 5) = bVar3 - bVar3 / 10;
            if (bVar3 < 0x3d)
            {
                if (uVar6 == 0)
                {
                    sango_legacy_trap(7);
                }
                uVar5 = bbk_rand();
                if (bVar3 / uVar6 <= ((int)uVar5 % 100 & 0xffU))
                {
                    bVar4 = true;
                    *(uint8_t *)(iVar8 + 1) = *(uint8_t *)(iVar9 + g_character_table_address + 1);
                    uVar5 = bbk_rand();
                    *(char *)(iVar8 + 5) = (char)uVar5 + (char)((int)uVar5 / 0x28) * -0x28 + '(';
                }
            }
        }
        if ((uint32_t) * (uint8_t *)(iVar9 + g_character_table_address + 1) ==
            g_player_character + 1)
        {
            if (bVar4)
            {
                sango_strategy_show_recruit_success(bVar2);
                uVar5 = (uint32_t) * (uint8_t *)(param_1 + 2);
            }
            else
            {
                pcVar7 = (char *)(g_scratch_buffer_address + 300);
                uVar5 = bbk_rand();
                sango_resource_read_text(0x40, (int)uVar5 % 3 + 0x7aU & 0xff, pcVar7);
                sango_strategy_present();
                sango_ui_show_character_message(bVar2, pcVar7);
                uVar5 = (uint32_t) * (uint8_t *)(param_1 + 2);
            }
            goto LAB_81c0bd9c;
        }
    }
    uVar5 = (uint32_t) * (uint8_t *)(param_1 + 2);
LAB_81c0bd9c:
    sango_city_add_character(uVar5, bVar1);
    return 1;
}

/* 原函数 0x81c0bf24 */
uint32_t sango_strategy_resolve_recruit(int param_1)
{
    uint32_t uVar1;
    uint8_t bVar2;
    uint32_t uVar3;
    int iVar4;

    iVar4 = (uint32_t) * (uint8_t *)(param_1 + 3) * 0x10;
    uVar3 = ((uint32_t) * (uint8_t *)((uint32_t) * (uint8_t *)(param_1 + 1) * 0x10 +
                                      g_character_table_address + 4) -
             (uint32_t) * (uint8_t *)(iVar4 + g_character_table_address + 4)) +
                0x32 &
            0xff;
    uVar1 = bbk_rand();
    if (uVar3 < ((int)uVar1 % 100 & 0xffU))
    {
    LAB_81c0bfbc:
        bVar2 = *(uint8_t *)(param_1 + 1);
        if ((uint32_t) * (uint8_t *)((uint32_t)bVar2 * 0x10 + g_character_table_address + 1) !=
            g_player_character + 1)
            goto LAB_81c0bfec;
    LAB_81c0c018:
        sango_ui_show_character_message(bVar2, &g_legacy_data_81c20284);
    }
    else
    {
        uVar1 = bbk_rand();
        if (((int)uVar1 % 100 & 0xffU) <
            (uint32_t) * (uint8_t *)(iVar4 + g_character_table_address + 5))
        {
            bVar2 = *(uint8_t *)(param_1 + 1);
            if ((uint32_t) * (uint8_t *)((uint32_t)bVar2 * 0x10 + g_character_table_address + 1) !=
                g_player_character + 1)
                goto LAB_81c0bfec;
            goto LAB_81c0c018;
        }
        switch (*(uint8_t *)(iVar4 + g_character_table_address + 6))
        {
        case 0:
            uVar3 = 0x32;
            break;
        case 1:
        case 3:
            uVar3 = 0x1e;
            break;
        case 2:
            uVar3 = 0x28;
            break;
        case 4:
            uVar3 = 5;
        }
        uVar1 = bbk_rand();
        if (uVar3 < ((int)uVar1 % 100 & 0xffU))
            goto LAB_81c0bfbc;
        iVar4 = iVar4 + g_character_table_address;
        if (*(uint8_t *)(iVar4 + 5) < 5)
        {
            *(uint8_t *)(iVar4 + 5) = 0;
        }
        else
        {
            *(uint8_t *)(iVar4 + 5) = *(uint8_t *)(iVar4 + 5) - 4;
        }
    }
    bVar2 = *(uint8_t *)(param_1 + 1);
LAB_81c0bfec:
    sango_city_add_character((uint32_t) * (uint8_t *)(param_1 + 2), bVar2);
    return 1;
}

/* 原函数 0x81c0c168 */
uint32_t sango_strategy_resolve_defection(int param_1)
{
    uint8_t bVar1;
    uint32_t uVar2;
    uint8_t bVar3;
    char *pcVar4;
    uint32_t uVar5;
    int iVar6;
    int iVar7;

    bVar3 = *(uint8_t *)(param_1 + 3);
    bVar1 = *(uint8_t *)(param_1 + 1);
    iVar6 = (uint32_t)bVar3 * 0x10;
    iVar7 = (uint32_t)bVar1 * 0x10;
    uVar5 = ((uint32_t) * (uint8_t *)(iVar7 + g_character_table_address + 4) -
             (uint32_t) * (uint8_t *)(iVar6 + g_character_table_address + 4)) +
                0x32 &
            0xff;
    uVar2 = bbk_rand();
    if (uVar5 < ((int)uVar2 % 100 & 0xffU))
    {
    LAB_81c0c20c:
        bVar3 = *(uint8_t *)(param_1 + 1);
        if ((uint32_t) * (uint8_t *)((uint32_t)bVar3 * 0x10 + g_character_table_address + 1) ==
            g_player_character + 1)
        {
        LAB_81c0c270:
            pcVar4 = &g_legacy_data_81c202a8;
        LAB_81c0c278:
            sango_ui_show_character_message(bVar3, pcVar4);
            uVar2 = (uint32_t) * (uint8_t *)(param_1 + 2);
            goto LAB_81c0c23c;
        }
    }
    else
    {
        uVar2 = bbk_rand();
        if (((int)uVar2 % 100 & 0xffU) <
            (uint32_t) * (uint8_t *)(iVar6 + g_character_table_address + 5))
        {
            bVar3 = *(uint8_t *)(param_1 + 1);
            if ((uint32_t) * (uint8_t *)((uint32_t)bVar3 * 0x10 + g_character_table_address + 1) ==
                g_player_character + 1)
                goto LAB_81c0c270;
        }
        else
        {
            switch (*(uint8_t *)(iVar6 + g_character_table_address + 6))
            {
            case 0:
                uVar5 = 0xf;
                break;
            case 1:
                uVar5 = 0x28;
                break;
            case 2:
                uVar5 = 0x1e;
                break;
            case 3:
                uVar5 = 0x14;
                break;
            case 4:
                uVar5 = 5;
            }
            uVar2 = bbk_rand();
            if (uVar5 < ((int)uVar2 % 100 & 0xffU))
            {
                bVar3 = *(uint8_t *)(param_1 + 1);
                if ((uint32_t) *
                        (uint8_t *)((uint32_t)bVar3 * 0x10 + g_character_table_address + 1) ==
                    g_player_character + 1)
                {
                    pcVar4 = &g_legacy_data_81c202b8;
                    goto LAB_81c0c278;
                }
            }
            else
            {
                uVar2 = sango_character_find_city(bVar3);
                if (uVar2 == 0xff)
                    goto LAB_81c0c20c;
                sango_city_remove_character(uVar2, bVar3);
                sango_city_add_character((uint32_t) * (uint8_t *)(param_1 + 2), bVar3);
                *(uint8_t *)(iVar6 + g_character_table_address + 1) =
                    *(uint8_t *)(iVar7 + g_character_table_address + 1);
                iVar6 = iVar6 + g_character_table_address;
                uVar2 = bbk_rand();
                *(char *)(iVar6 + 5) = (char)uVar2 + (char)((int)uVar2 / 0x28) * -0x28 + '(';
                if ((uint32_t) * (uint8_t *)(iVar7 + g_character_table_address + 1) ==
                    g_player_character + 1)
                {
                    sango_strategy_show_recruit_success(bVar3);
                    uVar2 = (uint32_t) * (uint8_t *)(param_1 + 2);
                    goto LAB_81c0c23c;
                }
            }
        }
    }
    uVar2 = (uint32_t) * (uint8_t *)(param_1 + 2);
LAB_81c0c23c:
    sango_city_add_character(uVar2, bVar1);
    return 1;
}

/* 原函数 0x81c0c490 */
uint32_t sango_strategy_resolve_surrender(int param_1)
{
    uint32_t uVar1;
    uint8_t *pbVar2;
    uint8_t bVar3;
    char cVar4;
    uint32_t uVar5;
    int iVar6;

    bVar3 = *(uint8_t *)(param_1 + 3);
    iVar6 = (uint32_t)bVar3 * 0x10;
    uVar5 = ((uint32_t) * (uint8_t *)((uint32_t) * (uint8_t *)(param_1 + 1) * 0x10 +
                                      g_character_table_address + 4) -
             (uint32_t) * (uint8_t *)(iVar6 + g_character_table_address + 4)) +
                0x32 &
            0xff;
    uVar1 = bbk_rand();
    if (uVar5 < ((int)uVar1 % 100 & 0xffU))
    {
    LAB_81c0c52c:
        bVar3 = *(uint8_t *)(param_1 + 1);
        if ((uint32_t) * (uint8_t *)((uint32_t)bVar3 * 0x10 + g_character_table_address + 1) !=
            g_player_character + 1)
            goto LAB_81c0c55c;
    }
    else
    {
        uVar1 = bbk_rand();
        if ((uint32_t) * (uint8_t *)(iVar6 + g_character_table_address + 5) <=
            ((int)uVar1 % 100 & 0xffU))
        {
            switch (*(uint8_t *)(iVar6 + g_character_table_address + 6))
            {
            case 0:
                uVar5 = 0x1e;
                break;
            case 1:
                uVar5 = 10;
                break;
            case 2:
                uVar5 = 0x14;
                break;
            case 3:
                uVar5 = 0x3c;
                break;
            case 4:
                uVar5 = 5;
            }
            uVar1 = bbk_rand();
            if (((int)uVar1 % 100 & 0xffU) <= uVar5)
            {
                uVar1 = sango_character_find_city(bVar3);
                cVar4 = bVar3 + 1;
                if (uVar1 != 0xff)
                {
                    *(char *)(iVar6 + g_character_table_address + 1) = cVar4;
                    iVar6 = g_scratch_buffer_address;
                    uVar5 = sango_city_list_idle_characters(uVar1, g_scratch_buffer_address);
                    (&g_first_city_owner)[uVar1 * 0x24] = cVar4;
                    uVar1 = 0;
                    if (uVar5 != 0)
                    {
                        do
                        {
                            pbVar2 = (uint8_t *)(iVar6 + uVar1);
                            uVar1 = uVar1 + 1 & 0xff;
                            *(char *)((uint32_t)*pbVar2 * 0x10 + g_character_table_address + 1) =
                                cVar4;
                        } while (uVar1 < uVar5);
                    }
                    sango_strategy_show_ruler_defection(bVar3);
                    bVar3 = *(uint8_t *)(param_1 + 1);
                    goto LAB_81c0c55c;
                }
            }
            goto LAB_81c0c52c;
        }
        bVar3 = *(uint8_t *)(param_1 + 1);
        if ((uint32_t) * (uint8_t *)((uint32_t)bVar3 * 0x10 + g_character_table_address + 1) !=
            g_player_character + 1)
            goto LAB_81c0c55c;
    }
    sango_ui_show_character_message(bVar3, &g_legacy_data_81c202e0);
    bVar3 = *(uint8_t *)(param_1 + 1);
LAB_81c0c55c:
    sango_city_add_character((uint32_t) * (uint8_t *)(param_1 + 2), bVar3);
    return 1;
}

/* 原函数 0x81c0c754 */
uint32_t sango_strategy_resolve_diplomatic_mission(int param_1)
{
    uint8_t index;
    uint8_t bVar1;
    bool bVar2;
    uint32_t uVar3;
    int iVar4;
    uint8_t bVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    char *source;
    char *destination;
    int iVar8;
    int iVar9;
    uint32_t uVar10;
    uint32_t unaff_s5;

    iVar4 = g_scratch_buffer_address;
    uVar7 = (uint32_t)g_player_character;
    index = *(uint8_t *)(param_1 + 3);
    uVar10 = (uint32_t)index;
    bVar1 = *(uint8_t *)(param_1 + 1);
    bVar2 = false;
    if (uVar7 == uVar10)
    {
        bVar5 = bVar1;
        if ((uint32_t) * (uint8_t *)((uint32_t)bVar1 * 0x10 + g_character_table_address + 1) !=
            uVar10 + 1)
            goto LAB_81c0c844;
    }
    else
    {
        iVar9 = (uint32_t)bVar1 * 0x10;
        bVar5 = *(uint8_t *)(iVar9 + g_character_table_address + 1);
        unaff_s5 = (uint32_t)bVar5;
        iVar8 = uVar10 * 0x10;
        uVar7 = sango_faction_list_cities(unaff_s5 - 1 & 0xff, g_scratch_buffer_address);
        uVar3 = sango_faction_list_cities(
            *(uint8_t *)(iVar8 + g_character_table_address + 1) - 1 & 0xff, iVar4);
        if ((int)(uVar3 << 1) <= (int)uVar7)
        {
            uVar3 = ((uint32_t) * (uint8_t *)(iVar9 + g_character_table_address + 4) -
                     (uint32_t) * (uint8_t *)(iVar8 + g_character_table_address + 4)) +
                        0x32 &
                    0xff;
            uVar7 = bbk_rand();
            if (((int)uVar7 % 100 & 0xffU) <= uVar3)
            {
                switch (*(uint8_t *)(iVar8 + g_character_table_address + 6))
                {
                case 0:
                    uVar3 = 10;
                    break;
                case 1:
                    uVar3 = 1;
                    break;
                case 2:
                    uVar3 = 0x14;
                    break;
                case 3:
                    uVar3 = 5;
                    break;
                case 4:
                    uVar3 = 0xf;
                }
                uVar7 = bbk_rand();
                if (((int)uVar7 % 100 & 0xffU) <= uVar3)
                {
                    iVar8 = g_scratch_buffer_address + 0x26;
                    uVar7 = sango_faction_list_cities(uVar10, iVar4);
                    uVar10 = 0;
                    if (uVar7 != 0)
                    {
                        do
                        {
                            uVar3 = sango_city_list_idle_characters(
                                (uint32_t) * (uint8_t *)(iVar4 + uVar10), iVar8);
                            (&g_first_city_owner)[(uint32_t) * (uint8_t *)(iVar4 + uVar10) * 0x24] =
                                bVar5;
                            uVar6 = 0;
                            if (uVar3 != 0)
                            {
                                do
                                {
                                    uVar6 = uVar6 + 1 & 0xff;
                                    *(uint8_t *)((uint32_t) * (uint8_t *)(iVar8 + uVar10) * 0x10 +
                                                 g_character_table_address + 1) = bVar5;
                                } while (uVar6 < uVar3);
                            }
                            uVar10 = uVar10 + 1 & 0xff;
                        } while (uVar10 < uVar7);
                    }
                    uVar7 = (uint32_t)g_player_character;
                    bVar2 = true;
                    goto LAB_81c0c844;
                }
            }
        }
        uVar7 = (uint32_t)g_player_character;
        bVar5 = *(uint8_t *)(param_1 + 1);
        if ((uint32_t) * (uint8_t *)((uint32_t) * (uint8_t *)(param_1 + 1) * 0x10 +
                                     g_character_table_address + 1) !=
            uVar7 + 1)
            goto LAB_81c0c844;
    }
    sango_ui_show_character_message(bVar5, &g_legacy_data_81c20304);
    uVar7 = (uint32_t)g_player_character;
LAB_81c0c844:
    source = (char *)(g_scratch_buffer_address + 0x154);
    destination = (char *)(g_scratch_buffer_address + 300);
    if (unaff_s5 == uVar7 + 1)
    {
        iVar4 = 0x9d;
        if (!bVar2)
        {
            iVar4 = 0x99;
        }
        uVar10 = bbk_rand();
        uVar7 = uVar10 + 3;
        if (-1 < (int)uVar10)
        {
            uVar7 = uVar10;
        }
        sango_resource_read_text(0x40, iVar4 + uVar10 + ((int)uVar7 >> 2) * -4 & 0xff, destination);
        sango_strategy_present();
        sango_ui_show_character_message(index, destination);
        uVar7 = (uint32_t) * (uint8_t *)(param_1 + 2);
    }
    else if (bVar2)
    {
        sango_load_named_text(index, destination);
        sango_resource_read_text(0x40, 0x6e, source);
        bbk_strcat(destination, source);
        sango_load_named_text((char)unaff_s5 + 0xff, source);
        bbk_strcat(destination, source);
        sango_ui_show_message(destination, 2);
        uVar7 = (uint32_t) * (uint8_t *)(param_1 + 2);
    }
    else
    {
        uVar7 = (uint32_t) * (uint8_t *)(param_1 + 2);
    }
    sango_city_add_character(uVar7, bVar1);
    return 1;
}

/* 原函数 0x81c0cb64 */
uint32_t sango_strategy_resolve_plunder(int param_1)
{
    uint8_t bVar1;
    uint16_t uVar2;
    uint16_t uVar3;
    char *destination;
    int iVar4;
    uint32_t uVar5;
    int iVar6;
    int iVar7;
    uint32_t uVar8;
    char *source;

    iVar4 = g_character_table_address;
    uVar5 = (uint32_t) * (uint8_t *)(param_1 + 2);
    uVar2 = (&g_first_city_agriculture)[uVar5 * 0x12];
    uVar3 = (&g_first_city_commerce)[uVar5 * 0x12];
    (&g_first_city_loyalty)[uVar5 * 0x24] = (uint8_t)(&g_first_city_loyalty)[uVar5 * 0x24] >> 1;
    (&g_first_city_agriculture)[uVar5 * 0x12] = uVar2 >> 1;
    (&g_first_city_commerce)[uVar5 * 0x12] = uVar3 >> 1;
    iVar6 = (uint32_t) * (uint8_t *)(param_1 + 1) * 0x10 + iVar4;
    uVar8 = (uint32_t)g_player_character;
    iVar6 = (uint32_t) * (uint8_t *)(iVar6 + 4) + (uint32_t) * (uint8_t *)(iVar6 + 3);
    iVar7 = iVar6 * 2;
    iVar6 = iVar6 * 5;
    (&g_first_city_money)[uVar5 * 0x12] = (short)iVar7 + (&g_first_city_money)[uVar5 * 0x12];
    (&g_first_city_food)[uVar5 * 0x12] = (short)iVar6 + (&g_first_city_food)[uVar5 * 0x12];
    destination = g_scratch_buffer_address;
    bVar1 = *(uint8_t *)(param_1 + 1);
    if ((uint32_t) * (uint8_t *)((uint32_t)bVar1 * 0x10 + iVar4 + 1) == uVar8 + 1)
    {
        source = g_scratch_buffer_address + 100;
        sango_resource_read_text(0x40, 0x95, g_scratch_buffer_address);
        sango_format_integer(iVar7, source, 10);
        bbk_strcat(destination, source);
        sango_resource_read_text(0x40, 0x96, source);
        bbk_strcat(destination, source);
        sango_format_integer(iVar6, source, 10);
        bbk_strcat(destination, source);
        sango_resource_read_text(0x40, 0x97, source);
        bbk_strcat(destination, source);
        sango_ui_show_character_message(*(uint8_t *)(param_1 + 1), destination);
        bVar1 = *(uint8_t *)(param_1 + 1);
    }
    sango_city_add_character((uint32_t) * (uint8_t *)(param_1 + 2), bVar1);
    return 1;
}

/* 原函数 0x81c0cd08 */
uint32_t sango_strategy_execute_queued_order(uint8_t *param_1)
{
    char cVar1;
    char cVar2;
    char *pcVar3;
    uint32_t uVar4;
    uint8_t bVar5;
    uint32_t uVar6;

    sango_strategy_find_ready_order();
    switch (*param_1)
    {
    case 0:
    case 0x14:
    case 0x15:
    case 0x16:
        goto switchD_81c0cd48_caseD_0;
    case 1:
        sango_city_add_character((uint32_t)(uint8_t)param_1[2], param_1[1]);
        break;
    case 2:
        sango_city_add_character((uint32_t)(uint8_t)param_1[2], param_1[1]);
    case 0xc:
        break;
    case 3:
        sango_strategy_resolve_search((int)param_1);
        break;
    case 4:
        sango_city_add_character((uint32_t)(uint8_t)param_1[2], param_1[1]);
        break;
    case 5:
        sango_city_add_character((uint32_t)(uint8_t)param_1[2], param_1[1]);
        break;
    case 6:
        sango_strategy_resolve_sow_discord((int)param_1);
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        break;
    case 10:
        break;
    case 0xb:
        sango_city_add_character((uint32_t)(uint8_t)param_1[2], param_1[1]);
        break;
    case 0xd:
        uVar4 = bbk_rand();
        uVar6 = 0x78;
        if (0x14 < (int)uVar4 % 100)
        {
            uVar4 = (uint32_t)(uint8_t)param_1[3];
            uVar6 = 0x77;
            (&g_first_city_food)[uVar4 * 0x12] =
                (&g_first_city_food)[uVar4 * 0x12] + *(short *)(param_1 + 6);
            (&g_first_city_money)[uVar4 * 0x12] =
                (&g_first_city_money)[uVar4 * 0x12] + *(short *)(param_1 + 8);
            (&g_first_city_reserve_troops)[uVar4 * 0x12] =
                (&g_first_city_reserve_troops)[uVar4 * 0x12] + *(short *)(param_1 + 4);
        }
        pcVar3 = g_scratch_buffer_address;
        sango_resource_read_text(0x40, uVar6, g_scratch_buffer_address);
        sango_ui_show_character_message(param_1[1], pcVar3);
        sango_city_add_character((uint32_t)(uint8_t)param_1[2], param_1[1]);
        break;
    case 0xe:
        uVar4 = (uint32_t)(uint8_t)param_1[3];
        bVar5 = param_1[1];
        cVar1 = (&g_first_city_owner)[uVar4 * 0x24];
        cVar2 = *(char *)((uint32_t)bVar5 * 0x10 + g_character_table_address + 1);
        if (cVar1 == '\0')
        {
            (&g_first_city_owner)[uVar4 * 0x24] = cVar2;
            bVar5 = param_1[1];
        }
        else if (cVar1 != cVar2)
        {
            uVar4 = (uint32_t)(uint8_t)param_1[2];
        }
        sango_city_add_character(uVar4, bVar5);
        break;
    case 0xf:
        sango_strategy_resolve_recruit((int)param_1);
        break;
    case 0x10:
        sango_strategy_resolve_defection((int)param_1);
        break;
    case 0x11:
        sango_strategy_resolve_surrender((int)param_1);
        break;
    case 0x12:
        break;
    case 0x13:
        sango_strategy_resolve_diplomatic_mission((int)param_1);
        break;
    case 0x17:
        sango_city_add_character((uint32_t)(uint8_t)param_1[2], param_1[1]);
        break;
    case 0x18:
        sango_city_add_character((uint32_t)(uint8_t)param_1[2], param_1[1]);
        break;
    case 0x19:
        break;
    case 0x1a:
        sango_strategy_resolve_plunder((int)param_1);
        break;
    case 0x1b:
        sango_strategy_resolve_attack((int)param_1);
        break;
    default:
        return 1;
    }
    sango_strategy_find_ready_order();
switchD_81c0cd48_caseD_0:
    return 1;
}

/* 原函数 0x81c0d03c */
void sango_strategy_find_ready_order(void)
{
    unsigned char abi_storage[120] __attribute__((aligned(8)));
#define auStack_70 (*(uint8_t(*)[104])(abi_storage + 0))

    uint8_t bVar1;
    uint8_t uVar2;
    int iVar3;
    uint8_t *puVar4;
    uint8_t *pbVar5;
    int iVar6;
    int iVar7;
    int iVar8;

    iVar7 = 0;
    pbVar5 = &g_first_city_character_count;
    iVar3 = 0x25;
    do
    {
        bVar1 = *pbVar5;
        iVar3 = iVar3 + -1;
        pbVar5 = pbVar5 + 0x24;
        iVar7 = iVar7 + (uint32_t)bVar1;
    } while (-1 < iVar3);
    iVar3 = 0;
    if (0 < iVar7 + -1)
    {
        do
        {
            iVar8 = iVar3 + 1;
            if (iVar8 < iVar7)
            {
                puVar4 = &g_city_character_roster_next + iVar3;
                iVar6 = iVar8;
                do
                {
                    uVar2 = *puVar4;
                    iVar6 = iVar6 + 1;
                    puVar4 = puVar4 + 1;
                    if ((&g_city_character_roster)[iVar3] == uVar2)
                    {
                        sango_load_named_text((&g_city_character_roster)[iVar3], auStack_70);
                        return;
                    }
                } while (iVar6 < iVar7);
            }
            iVar3 = iVar8;
        } while (iVar8 < iVar7 + -1);
    }
    return;
}
#undef auStack_70

/* 原函数 0x81c0d0e4 */
uint32_t sango_strategy_return_order_character(int param_1)
{
    sango_city_add_character((uint32_t) * (uint8_t *)(param_1 + 2), *(uint8_t *)(param_1 + 1));
    return 1;
}

/* 原函数 0x81c0d304 */
uint32_t sango_strategy_success_stub(void)
{
    return 1;
}

/* 原函数 0x81c0d354 */
void sango_strategy_advance_orders(void)
{
    int iVar1;
    char *pcVar2;
    uint32_t uVar3;

    iVar1 = g_order_queue_address;
    uVar3 = 0;
    do
    {
        pcVar2 = (char *)(uVar3 * 0xc + iVar1);
        if (*pcVar2 != -1)
        {
            sango_strategy_execute_queued_order(pcVar2);
            sango_strategy_queue_noop(pcVar2);
        }
        uVar3 = uVar3 + 1 & 0xff;
    } while (uVar3 < 100);
    return;
}

/* 原函数 0x81c0d3e0 */
uint32_t sango_city_choose_command(void)
{
    uint32_t uVar1;

    while (true)
    {
        while (true)
        {
            while (true)
            {
                sango_strategy_present();
                uVar1 = sango_city_choose_command_group();
                if (uVar1 != 2)
                    break;
                uVar1 = sango_city_choose_military_command();
                if (uVar1 != 0xff)
                {
                    return uVar1 + 0x17 & 0xff;
                }
            }
            if (2 < (int)uVar1)
                break;
            if (uVar1 == 0)
            {
                uVar1 = sango_city_choose_domestic_command();
                if (uVar1 != 0xff)
                {
                    return uVar1 + 1 & 0xff;
                }
            }
            else if (uVar1 == 1)
            {
                uVar1 = sango_city_choose_diplomacy_command();
                if (uVar1 != 0xff)
                {
                    return uVar1 + 0xf & 0xff;
                }
            }
        }
        if (uVar1 == 3)
            break;
        if (uVar1 == 0xff)
        {
            return 0xff;
        }
    }
    return 0xfe;
}

/* 原函数 0x81c0d498 */
uint32_t sango_city_choose_command_group(void)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define local_30 (*(uint16_t(*)[4])(abi_storage + 0))
#define acStack_28 (*(char(*)[32])(abi_storage + 8))

    uint32_t uVar1;

    sango_resource_read_text(0x40, 0x25, acStack_28);
    local_30[0] = 0x4f;
    local_30[2] = 0x67;
    local_30[1] = 10;
    local_30[3] = 0x3a;
    uVar1 = sango_ui_choose_option(local_30, 0, acStack_28);
    return uVar1;
}
#undef local_30
#undef acStack_28

/* 原函数 0x81c0d4f8 */
uint32_t sango_city_choose_domestic_command(void)
{
    unsigned char abi_storage[104] __attribute__((aligned(8)));
#define local_60 (*(uint16_t(*)[4])(abi_storage + 0))
#define acStack_58 (*(char(*)[80])(abi_storage + 8))

    uint32_t uVar1;

    sango_resource_read_text(0x40, 0x26, acStack_58);
    local_60[0] = 0x77;
    local_60[2] = 0x8f;
    local_60[1] = 0xe;
    local_60[3] = 0xb2;
    uVar1 = sango_ui_choose_option(local_60, 0, acStack_58);
    return uVar1;
}
#undef local_60
#undef acStack_58

/* 原函数 0x81c0d558 */
uint32_t sango_city_choose_diplomacy_command(void)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define acStack_28 (*(char(*)[32])(abi_storage + 8))
#define local_30 (*(uint16_t(*)[4])(abi_storage + 0))

    uint32_t uVar1;

    sango_resource_read_text(0x40, 0x27, acStack_28);
    local_30[0] = 0x77;
    local_30[2] = 0x8f;
    local_30[1] = 0xe;
    local_30[3] = 0x4a;
    uVar1 = sango_ui_choose_option(local_30, 0, acStack_28);
    return uVar1;
}
#undef acStack_28
#undef local_30

/* 原函数 0x81c0d5b8 */
uint32_t sango_city_choose_military_command(void)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define acStack_28 (*(char(*)[32])(abi_storage + 8))
#define local_30 (*(uint16_t(*)[4])(abi_storage + 0))

    uint32_t uVar1;

    sango_resource_read_text(0x40, 0x28, acStack_28);
    local_30[0] = 0x77;
    local_30[2] = 0x8f;
    local_30[1] = 0xe;
    local_30[3] = 0x4a;
    uVar1 = sango_ui_choose_option(local_30, 0, acStack_28);
    return uVar1;
}
#undef acStack_28
#undef local_30

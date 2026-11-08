#include "sango_internal.h"

/* 军事行动、出征编队与进入战斗。 */

/* 原函数 0x81c0ef00 */
uint32_t sango_city_order_transport(uint32_t param_1)
{
    unsigned char abi_storage[52] __attribute__((aligned(8)));
#define local_40 (*(uint32_t *)(abi_storage + 16))
#define local_3c (*(int *)(abi_storage + 20))
#define local_38 (*(int *)(abi_storage + 24))
#define local_34 (*(int *)(abi_storage + 28))
#define local_30 (*(int *)(abi_storage + 32))
#define local_50 (*(uint8_t *)(abi_storage + 0))
#define local_4f (*(uint8_t *)(abi_storage + 1))
#define local_4e (*(uint8_t *)(abi_storage + 2))
#define local_4d (*(char *)(abi_storage + 3))
#define local_4c (*(short *)(abi_storage + 4))
#define local_4a (*(short *)(abi_storage + 6))
#define local_48 (*(short *)(abi_storage + 8))
#define local_45 (*(uint8_t *)(abi_storage + 11))

    uint8_t bVar1;
    uint8_t bVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint8_t bVar5;
    uint8_t bVar6;
    uint32_t uVar7;
    int iVar8;
    char *pcVar9;
    uint32_t unaff_s6;

    uVar7 = param_1 & 0xff;
    local_38 = uVar7 * 9;
    local_34 = uVar7 * 0x24;
    local_3c = g_scratch_buffer_address;
    iVar8 = 0;
    local_40 = uVar7;
LAB_81c0ef6c:
    do
    {
        if (iVar8 == 0)
            goto LAB_81c0f1b8;
        while (true)
        {
            while (true)
            {
                while (true)
                {
                    while (bVar2 = g_strategy_cursor_y, bVar1 = g_strategy_cursor_x, iVar8 == 1)
                    {
                        iVar8 = 2;
                        uVar3 = sango_ui_input_food_amount(
                            0, (uint32_t)(uint16_t)(&g_first_city_food)[uVar7 * 0x12]);
                        local_4a = (short)uVar3;
                        if (uVar3 == 0xffff)
                        {
                        LAB_81c0f1b8:
                            while (true)
                            {
                                uVar3 = sango_city_list_idle_characters(local_40, local_3c);
                                if (uVar3 == 0)
                                {
                                    sango_ui_show_strategy_text(0x54);
                                    return 1;
                                }
                                sango_strategy_present();
                                uVar3 =
                                    sango_ui_select_character(local_3c, uVar3, 4, 2, 0xeb, 0x3d);
                                if (uVar3 == 0xff)
                                {
                                    return 1;
                                }
                                iVar8 = 1;
                                unaff_s6 = (uint32_t) * (uint8_t *)(local_3c + uVar3);
                                uVar3 = sango_character_can_pay_action(unaff_s6, 0xd);
                                if (uVar3 != 0)
                                    break;
                                sango_ui_show_strategy_text(0x3c);
                            }
                        }
                    }
                    if (iVar8 != 2)
                        break;
                    iVar8 = 1;
                    uVar3 = sango_ui_input_money_amount(
                        0, (uint32_t) * (uint16_t *)((int)&g_first_city_money + local_34));
                    if (uVar3 != 0xffff)
                    {
                        iVar8 = 3;
                    }
                    local_48 = (short)uVar3;
                }
                if (iVar8 != 3)
                    break;
                iVar8 = 2;
                uVar3 = sango_ui_input_troop_amount(
                    0, (uint32_t)(uint16_t)(&g_first_city_reserve_troops)[uVar7 * 0x12]);
                if (uVar3 != 0xffff)
                {
                    iVar8 = 4;
                }
                local_4c = (short)uVar3;
            }
            if (iVar8 != 4)
                goto LAB_81c0ef6c;
            pcVar9 = (char *)(g_scratch_buffer_address + 300);
            sango_resource_read_text(0x40, 0x5d, pcVar9);
            sango_strategy_present();
            bVar5 = (uint8_t)unaff_s6;
            sango_ui_show_character_message(bVar5, pcVar9);
            uVar3 = sango_strategy_select_city(&g_strategy_viewport_x);
            if (uVar3 != 0xff)
                break;
            iVar8 = 3;
        }
        if (uVar3 != local_40)
        {
            bVar6 = 0x38;
            if ((&g_first_city_owner)[uVar3 * 0x24] != '\0')
            {
                local_30 = local_38 * 4;
                bVar6 = 0x36;
                if ((&g_first_city_owner)[uVar3 * 0x24] == (&g_first_city_owner)[local_30])
                {
                    uVar4 = sango_city_route_distance(local_40, bVar1, bVar2, (char)uVar3,
                                                      g_strategy_cursor_x, g_strategy_cursor_y);
                    bVar6 = 0x37;
                    if (uVar4 != 0xff)
                    {
                        sango_character_pay_action(unaff_s6, 0xd);
                        *(short *)((int)&g_first_city_food + local_30) =
                            *(short *)((int)&g_first_city_food + local_30) - local_4a;
                        *(short *)((int)&g_first_city_reserve_troops + local_30) =
                            *(short *)((int)&g_first_city_reserve_troops + local_30) - local_4c;
                        *(short *)((int)&g_first_city_money + local_30) =
                            *(short *)((int)&g_first_city_money + local_30) - local_48;
                        sango_resource_read_text(0x40, 0x98, pcVar9);
                        sango_ui_show_character_message(bVar5, pcVar9);
                        local_50 = 0xd;
                        local_45 = (uint8_t)uVar4;
                        local_4e = (uint8_t)local_40;
                        local_4f = bVar5;
                        local_4d = (char)uVar3;
                        sango_strategy_enqueue_order(&local_50);
                        sango_city_remove_character(local_40, bVar5);
                        return 1;
                    }
                }
            }
            sango_ui_show_strategy_text(bVar6);
        }
    } while (true);
}
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_50
#undef local_4f
#undef local_4e
#undef local_4d
#undef local_4c
#undef local_4a
#undef local_48
#undef local_45

/* 原函数 0x81c0f244 */
uint32_t sango_city_order_transfer(uint8_t param_1)
{
    unsigned char abi_storage[36] __attribute__((aligned(8)));
#define local_40 (*(uint8_t *)(abi_storage + 0))
#define local_3f (*(uint8_t *)(abi_storage + 1))
#define local_3e (*(uint8_t *)(abi_storage + 2))
#define local_3d (*(char *)(abi_storage + 3))
#define local_35 (*(uint8_t *)(abi_storage + 11))
#define local_30 (*(uint8_t **)(abi_storage + 16))

    uint32_t uVar1;
    bool bVar2;
    int iVar3;
    uint8_t bVar4;
    uint8_t bVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint8_t bVar8;
    uint8_t bVar9;
    uint32_t unaff_s4;
    char *pcVar10;

    iVar3 = g_scratch_buffer_address;
    uVar1 = (uint32_t)param_1;
    local_30 = &g_first_city_status + uVar1 * 0x24;
    bVar2 = false;
    do
    {
        if (!bVar2)
            goto LAB_81c0f41c;
        while (bVar5 = g_strategy_cursor_y, bVar4 = g_strategy_cursor_x, bVar2)
        {
            pcVar10 = (char *)(g_scratch_buffer_address + 300);
            sango_resource_read_text(0x40, 0x5d, pcVar10);
            sango_strategy_present();
            bVar8 = (uint8_t)unaff_s4;
            sango_ui_show_character_message(bVar8, pcVar10);
            uVar6 = sango_strategy_select_city(&g_strategy_viewport_x);
            if (uVar6 != 0xff)
            {
                if (uVar6 != uVar1)
                {
                    if ((&g_first_city_owner)[uVar6 * 0x24] == '\0')
                    {
                        sango_ui_show_strategy_text(0x38);
                    LAB_81c0f348:
                        uVar7 = sango_city_route_distance(uVar1, bVar4, bVar5, (char)uVar6,
                                                          g_strategy_cursor_x, g_strategy_cursor_y);
                        bVar9 = 0x37;
                        if (uVar7 != 0xff)
                        {
                            sango_character_pay_action(unaff_s4, 0xd);
                            sango_resource_read_text(0x40, 0x98, pcVar10);
                            sango_ui_show_character_message(bVar8, pcVar10);
                            local_40 = 0xe;
                            local_35 = (uint8_t)uVar7;
                            local_3f = bVar8;
                            local_3e = param_1;
                            local_3d = (char)uVar6;
                            sango_strategy_enqueue_order(&local_40);
                            sango_city_remove_character(uVar1, bVar8);
                            return 1;
                        }
                    }
                    else
                    {
                        bVar9 = 0x36;
                        if ((&g_first_city_owner)[uVar6 * 0x24] == local_30[1])
                            goto LAB_81c0f348;
                    }
                    sango_ui_show_strategy_text(bVar9);
                }
                break;
            }
        LAB_81c0f41c:
            while (true)
            {
                uVar6 = sango_city_list_idle_characters(uVar1, iVar3);
                if (uVar6 == 0)
                {
                    sango_ui_show_strategy_text(0x54);
                    return 1;
                }
                sango_strategy_present();
                uVar6 = sango_ui_select_character(iVar3, uVar6, 4, 2, 0xeb, 0x3d);
                if (uVar6 == 0xff)
                {
                    return 1;
                }
                unaff_s4 = (uint32_t) * (uint8_t *)(iVar3 + uVar6);
                bVar2 = true;
                uVar6 = sango_character_can_pay_action(unaff_s4, 0xe);
                if (uVar6 != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
        }
    } while (true);
}
#undef local_40
#undef local_3f
#undef local_3e
#undef local_3d
#undef local_35
#undef local_30

/* 原函数 0x81c0f49c */
uint32_t sango_city_order_sow_discord(uint8_t param_1)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define local_25 (*(uint8_t *)(abi_storage + 11))
#define local_30 (*(uint8_t *)(abi_storage + 0))
#define local_2f (*(uint8_t *)(abi_storage + 1))
#define local_2e (*(uint8_t *)(abi_storage + 2))
#define local_2d (*(uint8_t *)(abi_storage + 3))

    uint32_t uVar1;
    int iVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint8_t bVar5;

    uVar1 = (uint32_t)param_1;
    uVar3 = sango_city_can_pay_command(uVar1, 0xf);
    iVar2 = g_scratch_buffer_address;
    bVar5 = 0x3b;
    if (uVar3 == 0)
    {
    LAB_81c0f60c:
        sango_ui_show_strategy_text(bVar5);
    }
    else
    {
        do
        {
            while (true)
            {
                uVar3 = sango_city_list_idle_characters(uVar1, iVar2);
                if (uVar3 == 0)
                {
                    bVar5 = 0x54;
                    goto LAB_81c0f60c;
                }
                sango_strategy_present();
                uVar3 = sango_ui_select_character(iVar2, uVar3, 4, 2, 0xeb, 0x3d);
                if (uVar3 == 0xff)
                {
                    return 1;
                }
                uVar4 =
                    sango_character_can_pay_action((uint32_t) * (uint8_t *)(iVar2 + uVar3), 0xf);
                if (uVar4 != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
            bVar5 = *(uint8_t *)(iVar2 + uVar3);
            uVar3 = sango_city_list_enemy_neighbors((uint32_t)g_player_character, iVar2);
            sango_strategy_present();
            uVar3 = sango_ui_select_character(iVar2, uVar3, 4, 2, 0xeb, 0x3d);
        } while (uVar3 == 0xff);
        sango_character_pay_action((uint32_t) * (uint8_t *)(iVar2 + uVar3), 0xf);
        sango_city_pay_command(uVar1, 0xf);
        local_30 = 0xf;
        local_2d = *(uint8_t *)(iVar2 + uVar3);
        local_25 = 10;
        local_2f = bVar5;
        local_2e = param_1;
        sango_strategy_enqueue_order(&local_30);
        sango_city_remove_character(uVar1, bVar5);
    }
    return 1;
}
#undef local_25
#undef local_30
#undef local_2f
#undef local_2e
#undef local_2d

/* 原函数 0x81c0f61c */
uint32_t sango_city_order_recruit_enemy(uint8_t param_1)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define local_30 (*(uint8_t *)(abi_storage + 0))
#define local_2f (*(uint8_t *)(abi_storage + 1))
#define local_2e (*(uint8_t *)(abi_storage + 2))
#define local_2d (*(uint8_t *)(abi_storage + 3))
#define local_25 (*(uint8_t *)(abi_storage + 11))

    uint32_t uVar1;
    int iVar2;
    uint32_t uVar3;
    uint8_t bVar4;

    uVar1 = (uint32_t)param_1;
    uVar3 = sango_city_can_pay_command(uVar1, 0x10);
    iVar2 = g_scratch_buffer_address;
    bVar4 = 0x3b;
    if (uVar3 == 0)
    {
    LAB_81c0f790:
        sango_ui_show_strategy_text(bVar4);
    }
    else
    {
        do
        {
            while (true)
            {
                uVar3 = sango_city_list_idle_characters(uVar1, iVar2);
                if (uVar3 == 0)
                {
                    bVar4 = 0x54;
                    goto LAB_81c0f790;
                }
                sango_strategy_present();
                uVar3 = sango_ui_select_character(iVar2, uVar3, 4, 2, 0xeb, 0x3d);
                if (uVar3 == 0xff)
                {
                    return 1;
                }
                bVar4 = *(uint8_t *)(iVar2 + uVar3);
                uVar3 = sango_character_can_pay_action((uint32_t)bVar4, 0x10);
                if (uVar3 != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
            uVar3 = sango_city_list_enemy_neighbors((uint32_t)g_player_character, iVar2);
            sango_strategy_present();
            uVar3 = sango_ui_select_character(iVar2, uVar3, 4, 2, 0xeb, 0x3d);
        } while (uVar3 == 0xff);
        sango_character_pay_action((uint32_t)bVar4, 0x10);
        sango_city_pay_command(uVar1, 0x10);
        local_30 = 0x10;
        local_2d = *(uint8_t *)(iVar2 + uVar3);
        local_25 = 10;
        local_2f = bVar4;
        local_2e = param_1;
        sango_strategy_enqueue_order(&local_30);
        sango_city_remove_character(uVar1, bVar4);
    }
    return 1;
}
#undef local_30
#undef local_2f
#undef local_2e
#undef local_2d
#undef local_25

/* 原函数 0x81c0f7a0 */
uint32_t sango_city_order_defection(uint8_t param_1)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define local_30 (*(uint8_t *)(abi_storage + 0))
#define local_2f (*(uint8_t *)(abi_storage + 1))
#define local_2e (*(uint8_t *)(abi_storage + 2))
#define local_2d (*(uint8_t *)(abi_storage + 3))
#define local_25 (*(uint8_t *)(abi_storage + 11))

    uint32_t uVar1;
    int iVar2;
    uint32_t uVar3;
    uint8_t bVar4;

    uVar1 = (uint32_t)param_1;
    uVar3 = sango_city_can_pay_command(uVar1, 0x11);
    iVar2 = g_scratch_buffer_address;
    bVar4 = 0x3b;
    if (uVar3 == 0)
    {
    LAB_81c0f924:
        sango_ui_show_strategy_text(bVar4);
    }
    else
    {
        do
        {
            while (true)
            {
                uVar3 = sango_city_list_idle_characters(uVar1, iVar2);
                if (uVar3 == 0)
                {
                    bVar4 = 0x54;
                    goto LAB_81c0f924;
                }
                sango_strategy_present();
                uVar3 = sango_ui_select_character(iVar2, uVar3, 4, 2, 0xeb, 0x3d);
                if (uVar3 == 0xff)
                {
                    return 1;
                }
                bVar4 = *(uint8_t *)(iVar2 + uVar3);
                uVar3 = sango_character_can_pay_action((uint32_t)bVar4, 0x11);
                if (uVar3 != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
            uVar3 = sango_city_list_enemy_rulers((uint32_t)g_player_character, iVar2);
            sango_strategy_present();
            if (uVar3 == 0)
            {
                return 1;
            }
            sango_strategy_present();
            uVar3 = sango_ui_select_character(iVar2, uVar3, 4, 2, 0xeb, 0x3d);
        } while (uVar3 == 0xff);
        sango_character_pay_action((uint32_t)bVar4, 0x11);
        sango_city_pay_command(uVar1, 0x11);
        local_30 = 0x11;
        local_2d = *(uint8_t *)(iVar2 + uVar3);
        local_25 = 10;
        local_2f = bVar4;
        local_2e = param_1;
        sango_strategy_enqueue_order(&local_30);
        sango_city_remove_character(uVar1, bVar4);
    }
    return 1;
}
#undef local_30
#undef local_2f
#undef local_2e
#undef local_2d
#undef local_25

/* 原函数 0x81c0f934 */
uint32_t sango_city_order_demand_surrender(uint8_t param_1)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define local_30 (*(uint8_t *)(abi_storage + 0))
#define local_2f (*(uint8_t *)(abi_storage + 1))
#define local_2e (*(uint8_t *)(abi_storage + 2))
#define local_2d (*(uint8_t *)(abi_storage + 3))
#define local_25 (*(uint8_t *)(abi_storage + 11))

    uint32_t uVar1;
    uint8_t *pbVar2;
    uint32_t uVar3;
    uint8_t bVar4;

    uVar1 = (uint32_t)param_1;
    uVar3 = sango_city_can_pay_command(uVar1, 0x13);
    pbVar2 = g_scratch_buffer_address;
    bVar4 = 0x3b;
    if (uVar3 == 0)
    {
    LAB_81c0faa8:
        sango_ui_show_strategy_text(bVar4);
    }
    else
    {
        do
        {
            while (true)
            {
                uVar3 = sango_city_list_idle_characters(uVar1, (int)pbVar2);
                if (uVar3 == 0)
                {
                    bVar4 = 0x54;
                    goto LAB_81c0faa8;
                }
                sango_strategy_present();
                uVar3 = sango_ui_select_character((int)pbVar2, uVar3, 4, 2, 0xeb, 0x3d);
                if (uVar3 == 0xff)
                {
                    return 1;
                }
                bVar4 = pbVar2[uVar3];
                uVar3 = sango_character_can_pay_action((uint32_t)bVar4, 0x13);
                if (uVar3 != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
            uVar3 = sango_strategy_list_rulers((uint32_t)g_player_character, pbVar2);
            sango_strategy_present();
            uVar3 = sango_ui_select_character((int)pbVar2, uVar3, 4, 2, 0xeb, 0x3d);
        } while (uVar3 == 0xff);
        sango_character_pay_action((uint32_t)bVar4, 0x13);
        sango_city_pay_command(uVar1, 0x13);
        local_30 = 0x13;
        local_2d = pbVar2[uVar3];
        local_25 = 10;
        local_2f = bVar4;
        local_2e = param_1;
        sango_strategy_enqueue_order(&local_30);
        sango_city_remove_character(uVar1, bVar4);
    }
    return 1;
}
#undef local_30
#undef local_2f
#undef local_2e
#undef local_2d
#undef local_25

/* 原函数 0x81c0fab8 */
uint32_t sango_city_order_scout(uint8_t param_1)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define local_30 (*(uint8_t *)(abi_storage + 0))
#define local_2f (*(uint8_t *)(abi_storage + 1))
#define local_2e (*(uint8_t *)(abi_storage + 2))
#define local_2d (*(uint8_t *)(abi_storage + 3))
#define local_25 (*(uint8_t *)(abi_storage + 11))

    uint32_t uVar1;
    bool bVar2;
    int iVar3;
    uint32_t uVar4;
    uint8_t bVar5;
    char *pcVar6;
    uint32_t unaff_s4;

    uVar1 = (uint32_t)param_1;
    uVar4 = sango_city_can_pay_command(uVar1, 0x17);
    iVar3 = g_scratch_buffer_address;
    bVar5 = 0x3b;
    if (uVar4 == 0)
    {
    LAB_81c0fc94:
        sango_ui_show_strategy_text(bVar5);
        return 1;
    }
    bVar2 = false;
    do
    {
        if (!bVar2)
            goto LAB_81c0fc20;
        while (bVar2)
        {
            pcVar6 = (char *)(g_scratch_buffer_address + 300);
            sango_resource_read_text(0x40, 0x5d, pcVar6);
            sango_strategy_present();
            bVar5 = (uint8_t)unaff_s4;
            sango_ui_show_character_message(bVar5, pcVar6);
            uVar4 = sango_strategy_select_city(&g_strategy_viewport_x);
            if (uVar4 != 0xff)
            {
                if (uVar4 != uVar1)
                {
                    if ((&g_first_city_owner)[uVar4 * 0x24] != (&g_first_city_owner)[uVar1 * 0x24])
                    {
                        sango_ui_show_city_details((uint8_t)uVar4);
                        sango_character_pay_action(unaff_s4, 0x17);
                        sango_city_pay_command(uVar1, 0x17);
                        local_30 = 0x17;
                        local_2f = bVar5;
                        local_2e = param_1;
                        local_2d = (uint8_t)uVar4;
                        local_25 = bVar2;
                        sango_strategy_enqueue_order(&local_30);
                        sango_city_remove_character(uVar1, bVar5);
                        return 1;
                    }
                    sango_ui_show_strategy_text(0x3a);
                }
                break;
            }
        LAB_81c0fc20:
            while (true)
            {
                uVar4 = sango_city_list_idle_characters(uVar1, iVar3);
                if (uVar4 == 0)
                {
                    bVar5 = 0x54;
                    goto LAB_81c0fc94;
                }
                sango_strategy_present();
                uVar4 = sango_ui_select_character(iVar3, uVar4, 4, 2, 0xeb, 0x3d);
                if (uVar4 == 0xff)
                {
                    return 1;
                }
                unaff_s4 = (uint32_t) * (uint8_t *)(iVar3 + uVar4);
                bVar2 = true;
                uVar4 = sango_character_can_pay_action(unaff_s4, 0x17);
                if (uVar4 != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
        }
    } while (true);
}
#undef local_30
#undef local_2f
#undef local_2e
#undef local_2d
#undef local_25

/* 原函数 0x81c0fca4 */
uint32_t sango_city_order_recruit_troops(uint8_t param_1)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define local_38 (*(uint8_t *)(abi_storage + 0))
#define local_37 (*(uint8_t *)(abi_storage + 1))
#define local_36 (*(uint8_t *)(abi_storage + 2))
#define local_2d (*(uint8_t *)(abi_storage + 11))

    uint32_t uVar1;
    int iVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint8_t bVar5;
    uint32_t mode;
    uint16_t *puVar6;

    iVar2 = g_scratch_buffer_address;
    uVar1 = (uint32_t)param_1;
    uVar3 = sango_city_list_idle_characters(uVar1, g_scratch_buffer_address);
    bVar5 = 0x54;
    if (uVar3 != 0)
    {
        while (uVar3 = sango_city_can_pay_command(uVar1, 0x18), uVar3 != 0)
        {
            uVar3 = sango_city_list_idle_characters(uVar1, iVar2);
            if (uVar3 == 0)
            {
                return 1;
            }
            do
            {
                while (true)
                {
                    sango_strategy_present();
                    uVar4 = sango_ui_select_character(iVar2, uVar3, 4, 2, 0xeb, 0x3d);
                    puVar6 = &g_first_city_money + uVar1 * 0x12;
                    if (uVar4 == 0xff)
                    {
                        return 1;
                    }
                    bVar5 = *(uint8_t *)(iVar2 + uVar4);
                    uVar4 = sango_character_can_pay_action((uint32_t)bVar5, 0x18);
                    if (uVar4 != 0)
                        break;
                    sango_ui_show_strategy_text(0x3c);
                }
                uVar4 = (uint32_t)*puVar6;
                if (uVar4 < 0x1900)
                {
                    uVar4 = uVar4 * 10 & 0xffff;
                }
                mode = (uint32_t)(uint8_t)(&g_first_city_loyalty)[uVar1 * 0x24] * 0x14;
                if (uVar4 < (uint32_t)(uint8_t)(&g_first_city_loyalty)[uVar1 * 0x24] * 0x14)
                {
                    mode = uVar4;
                }
                uVar4 = sango_ui_input_troop_amount(0, mode);
            } while (uVar4 == 0xffff);
            (&g_first_city_reserve_troops)[uVar1 * 0x12] =
                (short)uVar4 + (&g_first_city_reserve_troops)[uVar1 * 0x12];
            sango_character_pay_action((uint32_t)bVar5, 0x18);
            local_38 = 0x18;
            local_2d = 0;
            *puVar6 = *puVar6 - (short)(uVar4 / 10);
            local_37 = bVar5;
            local_36 = param_1;
            sango_strategy_enqueue_order(&local_38);
            sango_city_remove_character(uVar1, bVar5);
        }
        bVar5 = 0x3b;
    }
    sango_ui_show_strategy_text(bVar5);
    return 1;
}
#undef local_38
#undef local_37
#undef local_36
#undef local_2d

/* 原函数 0x81c0fe88 */
uint32_t sango_city_assign_troops(uint32_t param_1)
{
    bool bVar1;
    int iVar2;
    uint32_t uVar3;
    int iVar4;
    uint32_t uVar5;
    uint32_t unaff_s1;
    int iVar6;
    uint32_t uVar7;

    iVar2 = g_scratch_buffer_address;
    uVar7 = param_1 & 0xff;
    uVar3 = sango_city_list_idle_characters(uVar7, g_scratch_buffer_address);
    if (uVar3 == 0)
    {
        sango_ui_show_strategy_text(0x54);
        return 1;
    }
    bVar1 = false;
    do
    {
        if (bVar1)
            goto LAB_81c0ff2c;
        while (true)
        {
            uVar3 = sango_city_list_idle_characters(uVar7, iVar2);
            if (uVar3 == 0)
            {
                return 1;
            }
            sango_strategy_present();
            unaff_s1 = sango_ui_select_character(iVar2, uVar3, 4, 2, 0xeb, 0x3d);
            bVar1 = true;
            if (unaff_s1 == 0xff)
            {
                return 1;
            }
        LAB_81c0ff2c:
            if (!bVar1)
                break;
            iVar6 = (uint32_t) * (uint8_t *)(iVar2 + unaff_s1) * 0x10;
            iVar4 = iVar6 + g_character_table_address;
            uVar5 = (uint32_t)(uint16_t)(&g_first_city_reserve_troops)[uVar7 * 0x12] +
                    (uint32_t) * (uint16_t *)(iVar4 + 10);
            uVar3 = ((uint32_t) * (uint8_t *)(iVar4 + 2) * 10 +
                     (uint32_t) * (uint8_t *)(iVar4 + 3) + (uint32_t) * (uint8_t *)(iVar4 + 4)) *
                    10;
            if (uVar5 < uVar3)
            {
                uVar3 = uVar5;
            }
            if (uVar3 == 0)
            {
                sango_ui_show_strategy_text(0x39);
            }
            else
            {
                uVar3 = sango_ui_input_troop_amount(0, uVar3 & 0xffff);
                if (uVar3 != 0xffff)
                {
                    iVar6 = iVar6 + g_character_table_address;
                    (&g_first_city_reserve_troops)[uVar7 * 0x12] =
                        ((&g_first_city_reserve_troops)[uVar7 * 0x12] + *(short *)(iVar6 + 10)) -
                        (short)uVar3;
                    *(short *)(iVar6 + 10) = (short)uVar3;
                }
            }
        }
    } while (true);
}

/* 原函数 0x81c10020 */
uint32_t sango_city_order_counterintelligence(void)
{
    sango_ui_show_message(&g_legacy_data_81c20538, 2);
    return 1;
}

/* 原函数 0x81c10050 */
uint32_t sango_city_order_attack(uint8_t param_1)
{
    unsigned char abi_storage[44] __attribute__((aligned(8)));
#define local_48 (*(char(*)[16])(abi_storage + 0))
#define local_38 (*(uint8_t(*)[2])(abi_storage + 16))
#define local_36 (*(uint8_t *)(abi_storage + 18))
#define local_35 (*(uint8_t *)(abi_storage + 19))
#define local_32 (*(short *)(abi_storage + 22))
#define local_2d (*(uint8_t *)(abi_storage + 27))

    bool bVar1;
    uint32_t uVar2;
    char *pcVar3;
    uint8_t bVar4;
    uint8_t bVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint8_t bVar8;
    uint32_t uVar9;

    uVar2 = (uint32_t)param_1;
    uVar6 = sango_city_can_pay_command(uVar2, 0x1b);
    bVar5 = g_strategy_cursor_y;
    bVar4 = g_strategy_cursor_x;
    pcVar3 = g_scratch_buffer_address;
    bVar8 = 0x3b;
    if (uVar6 != 0)
    {
        uVar6 = sango_city_list_idle_characters(uVar2, (int)g_scratch_buffer_address);
        if (uVar6 != 0)
        {
            sango_memory_fill(local_48, 0, 10);
            uVar9 = 0;
            do
            {
                sango_strategy_present();
                uVar6 = sango_ui_select_character((int)pcVar3, uVar6, 4, 2, 0xeb, 0x3d);
                if (uVar6 == 0xff)
                    break;
                local_48[uVar9] = pcVar3[uVar6] + 1;
                sango_city_remove_character(uVar2, pcVar3[uVar6]);
                uVar6 = sango_city_list_idle_characters(uVar2, (int)pcVar3);
                uVar9 = uVar9 + 1 & 0xff;
            } while (uVar9 < 10);
            if (uVar9 == 0)
            {
                return 1;
            }
            sango_strategy_present();
            uVar6 = (uint32_t)(uint16_t)(&g_first_city_food)[uVar2 * 0x12];
            bVar1 = uVar6 != 0;
            if (!bVar1)
            {
                uVar6 = 0;
            }
            uVar6 = sango_ui_input_food_amount((uint32_t)bVar1, uVar6);
            local_32 = (short)uVar6;
            if ((short)uVar6 != -1)
            {
                do
                {
                    do
                    {
                        pcVar3 = g_scratch_buffer_address;
                        sango_resource_read_text(0x40, 0x5d, g_scratch_buffer_address);
                        sango_strategy_present();
                        sango_ui_show_character_message(local_48[0] + 0xff, pcVar3);
                        uVar6 = sango_strategy_select_city(&g_strategy_viewport_x);
                        if (uVar6 == 0xff)
                        {
                            while (uVar9 = uVar9 - 1 & 0xff, (uVar9 + 1 & 0xff) != 0)
                            {
                                sango_city_add_character(uVar2, local_48[uVar9] - 1);
                            }
                            return 1;
                        }
                    } while (uVar6 == uVar2);
                    bVar8 = 0x3a;
                    if ((&g_first_city_owner)[uVar6 * 0x24] != (&g_first_city_owner)[uVar2 * 0x24])
                    {
                        uVar7 = sango_city_adjacent_distance(
                            uVar2, bVar4, bVar5, uVar6, g_strategy_cursor_x, g_strategy_cursor_y);
                        bVar8 = 0x37;
                        if (uVar7 != 0xff)
                        {
                            sango_ui_show_strategy_text(0x5e);
                            (&g_first_city_food)[uVar2 * 0x12] =
                                (&g_first_city_food)[uVar2 * 0x12] - local_32;
                            sango_city_pay_command(uVar2, 0x1b);
                            local_38[0] = 0x1b;
                            local_35 = (uint8_t)uVar6;
                            local_2d = (uint8_t)uVar7;
                            local_36 = param_1;
                            sango_strategy_queue_army(local_38, local_48);
                            return 1;
                        }
                    }
                    sango_ui_show_strategy_text(bVar8);
                } while (true);
            }
            while (uVar9 = uVar9 - 1 & 0xff, (uVar9 + 1 & 0xff) != 0)
            {
                sango_city_add_character(uVar2, local_48[uVar9] - 1);
            }
            return 1;
        }
        bVar8 = 0x60;
    }
    sango_ui_show_strategy_text(bVar8);
    return 1;
}
#undef local_48
#undef local_38
#undef local_36
#undef local_35
#undef local_32
#undef local_2d

/* 原函数 0x81c10394 */
uint32_t sango_strategy_resolve_attack(int param_1)
{
    uint8_t bVar1;
    uint8_t bVar2;
    uint8_t bVar3;
    uint8_t bVar4;
    uint32_t uVar5;
    uint8_t *pbVar6;
    uint8_t *pbVar7;
    int iVar8;
    uint32_t uVar9;
    uint8_t *pbVar10;
    uint32_t uVar11;
    uint32_t uVar12;
    uint32_t uVar13;
    uint32_t uVar14;

    pbVar7 = g_scratch_buffer_address;
    *(uint8_t *)(g_army_slot_used_address + (uint32_t) * (uint8_t *)(param_1 + 1)) = 0;
    pbVar10 = (uint8_t *)((uint32_t) * (uint8_t *)(param_1 + 1) * 10 + g_army_rosters_address);
    sango_memory_fill(&g_battle_roster_first, 0, 0x14);
    bVar1 = *(uint8_t *)(param_1 + 3);
    uVar13 = (uint32_t)bVar1;
    bVar2 = (&g_first_city_owner)[uVar13 * 0x24];
    uVar14 = (uint32_t)bVar2;
    bVar3 = *(uint8_t *)((uint32_t)*pbVar10 * 0x10 + g_character_table_address + -0xf);
    uVar12 = (uint32_t)bVar3;
    sango_resource_read_text(2, 0xf, pbVar7);
    g_battle_map_resource_view2 = pbVar7[uVar13] + 0x6e;
    uVar5 = sango_city_neighbor_direction(uVar13, (uint32_t) * (uint8_t *)(param_1 + 2));
    g_battle_entry_direction = (uint8_t)uVar5;
    sango_strategy_show_army_attack(bVar3 - 1, bVar1);
    if (uVar14 == g_player_character + 1)
    {
        if (uVar12 != uVar14)
        {
            g_battle_attacker_food = (&g_first_city_food)[uVar13 * 0x12];
            g_battle_control_mode_view2 = 0;
            uVar5 = 0;
            g_battle_defender_food = *(uint16_t *)(param_1 + 6);
            do
            {
                uVar12 = sango_city_list_idle_characters(uVar13, (int)pbVar7);
                sango_strategy_present();
                uVar12 = sango_ui_select_character((int)pbVar7, uVar12, 4, 2, 0xeb, 0x3d);
                if (uVar12 == 0xff)
                    break;
                (&g_battle_roster_first)[uVar5] = pbVar7[uVar12] + 1;
                sango_city_remove_character(uVar13, pbVar7[uVar12]);
                uVar5 = uVar5 + 1 & 0xff;
            } while (uVar5 < 10);
            bbk_memcpy(&g_battle_roster_second, pbVar10, 10);
            goto LAB_81c10678;
        }
        uVar5 = 0;
        pbVar7 = pbVar10;
        do
        {
            if (*pbVar7 != 0)
            {
                sango_city_add_character(uVar13, *pbVar7 - 1);
            }
            uVar5 = uVar5 + 1 & 0xff;
            pbVar7 = pbVar10 + uVar5;
        } while (uVar5 < 10);
    }
    else
    {
        if (uVar12 == g_player_character + 1)
        {
            if (uVar14 != 0)
            {
                if (uVar14 == uVar12)
                {
                    uVar5 = 0;
                    pbVar7 = pbVar10;
                    do
                    {
                        if (*pbVar7 != 0)
                        {
                            sango_city_add_character(uVar13, *pbVar7 - 1);
                        }
                        sango_strategy_show_battle_victory(bVar3);
                        uVar5 = uVar5 + 1 & 0xff;
                        pbVar7 = pbVar10 + uVar5;
                    } while (uVar5 < 10);
                    return 1;
                }
                g_battle_control_mode_view2 = 1;
                g_battle_attacker_food = *(uint16_t *)(param_1 + 6);
                g_battle_defender_food = (&g_first_city_food)[uVar13 * 0x12];
                bbk_memcpy(&g_battle_roster_first, pbVar10, 10);
                uVar5 = sango_city_list_idle_characters(uVar13, (int)pbVar7);
                if (uVar5 != 0)
                {
                    uVar14 = uVar5 - 1;
                    uVar12 = 0;
                    if (0 < (int)uVar14)
                    {
                        uVar9 = 1;
                        do
                        {
                            uVar11 = uVar9 & 0xff;
                            if (uVar11 < uVar5)
                            {
                                iVar8 = g_character_table_address;
                                do
                                {
                                    pbVar10 = pbVar7 + uVar11;
                                    bVar1 = pbVar7[uVar12];
                                    bVar2 = *pbVar10;
                                    uVar11 = uVar11 + 1 & 0xff;
                                    if (*(uint16_t *)((uint32_t)bVar1 * 0x10 + iVar8 + 10) <
                                        *(uint16_t *)((uint32_t)bVar2 * 0x10 + iVar8 + 10))
                                    {
                                        *pbVar10 = bVar1;
                                        pbVar7[uVar12] = bVar2;
                                        iVar8 = g_character_table_address;
                                    }
                                    if (*(short *)((uint32_t)pbVar7[uVar5 - 1] * 0x10 + iVar8 +
                                                   10) == 0)
                                    {
                                        uVar5 = uVar14 & 0xff;
                                        uVar14 = uVar5 - 1;
                                    }
                                } while (uVar11 < uVar5);
                            }
                            uVar12 = uVar9 & 0xff;
                            uVar9 = uVar12 + 1;
                        } while ((int)uVar12 < (int)uVar14);
                    }
                    if (uVar5 == 0)
                    {
                        g_battle_roster_second = *pbVar7 + 1;
                        sango_city_remove_character(uVar13, *pbVar7);
                    }
                    else
                    {
                        if (10 < uVar5)
                        {
                            uVar5 = 10;
                        }
                        uVar12 = 0;
                        pbVar10 = pbVar7;
                        if (uVar5 != 0)
                        {
                            do
                            {
                                sango_city_remove_character(uVar13, *pbVar10);
                                (&g_battle_roster_second)[uVar12] = *pbVar10 + 1;
                                uVar12 = uVar12 + 1 & 0xff;
                                pbVar10 = pbVar7 + uVar12;
                            } while (uVar12 < uVar5);
                        }
                    }
                }
                goto LAB_81c10678;
            }
            uVar5 = 0;
            do
            {
                if (pbVar10[uVar5] != 0)
                {
                    sango_city_add_character(uVar13, pbVar10[uVar5] - 1);
                }
                uVar5 = uVar5 + 1 & 0xff;
            } while (uVar5 < 10);
        }
        else
        {
            uVar5 = 0;
            pbVar6 = pbVar10;
            if (uVar14 != 0)
            {
                if (uVar14 == uVar12)
                {
                    uVar5 = 0;
                    pbVar7 = pbVar10;
                    do
                    {
                        if (*pbVar7 != 0)
                        {
                            sango_city_add_character(uVar13, *pbVar7 - 1);
                        }
                        uVar5 = uVar5 + 1 & 0xff;
                        pbVar7 = pbVar10 + uVar5;
                    } while (uVar5 < 10);
                    goto LAB_81c104f4;
                }
                bbk_memcpy(&g_battle_roster_first, pbVar10, 10);
                uVar5 = sango_city_list_idle_characters(uVar13, (int)pbVar7);
                if (uVar5 != 0)
                {
                    uVar14 = uVar5 - 1;
                    uVar12 = 0;
                    if (0 < (int)uVar14)
                    {
                        uVar9 = 1;
                        do
                        {
                            uVar11 = uVar9 & 0xff;
                            if (uVar11 < uVar5)
                            {
                                iVar8 = g_character_table_address;
                                do
                                {
                                    pbVar10 = pbVar7 + uVar11;
                                    bVar1 = pbVar7[uVar12];
                                    bVar4 = *pbVar10;
                                    uVar11 = uVar11 + 1 & 0xff;
                                    if (*(uint16_t *)((uint32_t)bVar1 * 0x10 + iVar8 + 10) <
                                        *(uint16_t *)((uint32_t)bVar4 * 0x10 + iVar8 + 10))
                                    {
                                        *pbVar10 = bVar1;
                                        pbVar7[uVar12] = bVar4;
                                        iVar8 = g_character_table_address;
                                    }
                                    if (*(short *)((uint32_t)pbVar7[uVar5 - 1] * 0x10 + iVar8 +
                                                   10) == 0)
                                    {
                                        uVar5 = uVar14 & 0xff;
                                        uVar14 = uVar5 - 1;
                                    }
                                } while (uVar11 < uVar5);
                            }
                            uVar12 = uVar9 & 0xff;
                            uVar9 = uVar12 + 1;
                        } while ((int)uVar12 < (int)uVar14);
                    }
                    if (uVar5 == 0)
                    {
                        g_battle_roster_second = *pbVar7;
                        sango_city_remove_character(uVar13, *pbVar7);
                    }
                    else
                    {
                        if (10 < uVar5)
                        {
                            uVar5 = 10;
                        }
                        uVar12 = 0;
                        pbVar10 = pbVar7;
                        if (uVar5 != 0)
                        {
                            do
                            {
                                sango_city_remove_character(uVar13, *pbVar10);
                                (&g_battle_roster_second)[uVar12] = *pbVar10 + 1;
                                uVar12 = uVar12 + 1 & 0xff;
                                pbVar10 = pbVar7 + uVar12;
                            } while (uVar12 < uVar5);
                        }
                    }
                }
                g_battle_control_mode_view2 = 2;
                g_battle_attacker_food = *(uint16_t *)(param_1 + 6);
                g_battle_defender_food = (&g_first_city_food)[uVar13 * 0x12];
                sango_strategy_show_armies_engage(bVar3 - 1, bVar2 - 1);
            LAB_81c10678:
                sango_battle_run();
                sango_strategy_finish_battle(uVar13, g_battle_result);
                return 1;
            }
            do
            {
                if (*pbVar6 != 0)
                {
                    sango_city_add_character(uVar13, *pbVar6 - 1);
                }
                uVar5 = uVar5 + 1 & 0xff;
                pbVar6 = pbVar10 + uVar5;
            } while (uVar5 < 10);
        }
        (&g_first_city_owner)[uVar13 * 0x24] = bVar3;
    }
LAB_81c104f4:
    sango_strategy_show_battle_victory(bVar3);
    return 1;
}

/* 原函数 0x81c10a4c */
uint32_t sango_strategy_finish_battle(uint32_t param_1, char param_2)
{
    uint16_t uVar1;
    uint16_t uVar2;
    uint16_t uVar3;
    char *destination;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    char *source;

    uVar5 = param_1 & 0xff;
    g_capture_count = 0;
    uVar6 = 0xff;
    if (param_2 == '\x01')
    {
        uVar4 = 0;
        do
        {
            if ((&g_battle_roster_first)[uVar4] != '\0')
            {
                sango_city_add_character(uVar5, (&g_battle_roster_first)[uVar4] - 1);
            }
            uVar4 = uVar4 + 1 & 0xff;
        } while (uVar4 < 10);
        sango_strategy_show_battle_victory(*(uint8_t *)((uint32_t)g_battle_roster_first * 0x10 +
                                                        g_character_table_address + -0xf));
        if ((uint8_t)(g_battle_control_mode - 1U) < 2)
        {
            uVar6 = sango_city_choose_postbattle_governor(g_battle_roster_first - 1, uVar5);
        }
        uVar4 = sango_strategy_handle_defeated_units(uVar5, (char *)&g_battle_roster_second);
        if (uVar4 != 0xff)
        {
            uVar6 = uVar4;
        }
    }
    else
    {
        uVar4 = 10;
        if (param_2 == '\x02')
        {
            do
            {
                if ((&g_battle_roster_first)[uVar4] != '\0')
                {
                    sango_city_add_character(uVar5, (&g_battle_roster_first)[uVar4] - 1);
                }
                uVar4 = uVar4 + 1 & 0xff;
            } while (uVar4 < 0x14);
            if (g_battle_control_mode == '\0')
            {
                uVar6 = sango_city_choose_postbattle_governor(g_battle_roster_second - 1, uVar5);
            }
            uVar4 = sango_strategy_handle_defeated_units(uVar5, (char *)&g_battle_roster_first);
            if (uVar4 != 0xff)
            {
                uVar6 = uVar4;
            }
            if (g_battle_control_mode == '\x02')
            {
                sango_strategy_show_battle_victory(
                    *(uint8_t *)((uint32_t)g_battle_roster_second * 0x10 +
                                 g_character_table_address + -0xf));
            }
            else
            {
                sango_strategy_show_battle_defeat();
                destination = g_scratch_buffer_address;
                if (g_capture_count != 0)
                {
                    source = g_scratch_buffer_address + 0x28;
                    if (1 < g_capture_count)
                    {
                        g_capture_count = 2;
                    }
                    sango_load_named_text(g_captured_character, g_scratch_buffer_address);
                    sango_resource_read_text(0x40, g_capture_count + 0x69 & 0xff, source);
                    bbk_strcat(destination, source);
                    sango_ui_show_message(destination, 2);
                }
            }
        }
    }
    uVar1 = (&g_first_city_agriculture)[uVar5 * 0x12];
    uVar2 = (&g_first_city_commerce)[uVar5 * 0x12];
    uVar3 = (&g_first_city_money)[uVar5 * 0x12];
    (&g_first_city_loyalty)[uVar5 * 0x24] =
        (&g_first_city_loyalty)[uVar5 * 0x24] - (uint8_t)(&g_first_city_loyalty)[uVar5 * 0x24] / 10;
    (&g_first_city_agriculture)[uVar5 * 0x12] = uVar1 - uVar1 / 0x14;
    (&g_first_city_commerce)[uVar5 * 0x12] = uVar2 - uVar2 / 0x14;
    (&g_first_city_money)[uVar5 * 0x12] = uVar3 - uVar3 / 0x14;
    if (uVar6 != 0xff)
    {
        sango_strategy_resolve_ruler_succession((uint8_t)uVar6);
    }
    (&g_first_city_food)[uVar5 * 0x12] =
        g_battle_attacker_food_view2 + g_battle_defender_food_view2;
    return 0;
}

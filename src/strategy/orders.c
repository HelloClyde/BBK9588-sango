#include "sango_internal.h"

/* 战略命令选择、目标及执行队列。 */

/* 原函数 0x81c0d618 */
/* 城市命令分派。数值对应原存档/队列中的命令ID，不能重新编号。 */
uint32_t sango_city_execute_command(uint8_t param_1, uint8_t param_2)
{
    uint32_t uVar1;
    uint32_t uVar2;

    uVar1 = (uint32_t)param_1;
    uVar2 = 0;
    if (uVar1 < 0x26)
    {
        uVar2 = 1;
        switch (param_2)
        {
        case 1:
            sango_city_order_agriculture(param_1);
        case 0:
        case 0x14:
        case 0x15:
        case 0x16:
            uVar2 = 1;
            break;
        case 2:
            sango_city_order_commerce(param_1);
            uVar2 = 1;
            break;
        case 3:
            sango_city_order_search(param_1);
            uVar2 = 1;
            break;
        case 4:
            sango_city_order_disaster_prevention(param_1);
            uVar2 = 1;
            break;
        case 5:
            sango_city_order_patrol(param_1);
            uVar2 = 1;
            break;
        case 6:
            sango_city_order_recruit_captive(param_1);
            uVar2 = 1;
            break;
        case 7:
            sango_city_order_execute_captive(uVar1);
            uVar2 = 1;
            break;
        case 8:
            sango_city_order_exile_character(uVar1);
            uVar2 = 1;
            break;
        case 9:
            sango_city_order_reward(uVar1);
            uVar2 = 1;
            break;
        case 10:
            sango_city_order_confiscate(uVar1);
            uVar2 = 1;
            break;
        case 0xb:
            sango_city_order_trade(param_1);
            uVar2 = 1;
            break;
        case 0xc:
            sango_city_order_banquet(uVar1);
            uVar2 = 1;
            break;
        case 0xd:
            sango_city_order_transport(uVar1);
            uVar2 = 1;
            break;
        case 0xe:
            sango_city_order_transfer(param_1);
            uVar2 = 1;
            break;
        case 0xf:
            sango_city_order_sow_discord(param_1);
            uVar2 = 1;
            break;
        case 0x10:
            sango_city_order_recruit_enemy(param_1);
            uVar2 = 1;
            break;
        case 0x11:
            sango_city_order_defection(param_1);
            uVar2 = 1;
            break;
        case 0x12:
            sango_city_order_counterintelligence();
            uVar2 = 1;
            break;
        case 0x13:
            sango_city_order_demand_surrender(param_1);
            uVar2 = 1;
            break;
        case 0x17:
            sango_city_order_scout(param_1);
            uVar2 = 1;
            break;
        case 0x18:
            sango_city_order_recruit_troops(param_1);
            uVar2 = 1;
            break;
        case 0x19:
            sango_city_assign_troops(uVar1);
            uVar2 = 1;
            break;
        case 0x1a:
            sango_city_order_plunder(param_1);
            uVar2 = 1;
            break;
        case 0x1b:
            sango_city_order_attack(param_1);
            uVar2 = 1;
        }
    }
    return uVar2;
}

/* 原函数 0x81c0d7e4 */
uint32_t sango_city_order_agriculture(uint8_t param_1)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define local_37 (*(uint8_t *)(abi_storage + 1))
#define local_36 (*(uint8_t *)(abi_storage + 2))
#define local_2d (*(uint8_t *)(abi_storage + 11))
#define local_38 (*(uint8_t *)(abi_storage + 0))

    uint8_t bVar1;
    uint16_t uVar2;
    uint32_t uVar3;
    int iVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint8_t bVar7;
    uint32_t uVar8;
    uint16_t *puVar9;

    iVar4 = g_scratch_buffer_address;
    uVar3 = (uint32_t)param_1;
    uVar5 = sango_city_list_idle_characters(uVar3, g_scratch_buffer_address);
    bVar7 = 0x54;
    if (uVar5 != 0)
    {
        puVar9 = &g_first_city_agriculture + uVar3 * 0x12;
        uVar2 = (&g_first_city_agriculture_limit)[uVar3 * 0x12];
        while (true)
        {
            bVar7 = 0x34;
            if ((uint32_t)uVar2 <= (uint32_t)*puVar9)
                break;
            uVar5 = sango_city_can_pay_command(uVar3, 1);
            if (uVar5 == 0)
            {
                bVar7 = 0x3b;
                break;
            }
            uVar5 = sango_city_list_idle_characters(uVar3, iVar4);
            if (uVar5 == 0)
            {
                return 1;
            }
            while (true)
            {
                sango_strategy_present();
                uVar6 = sango_ui_select_character(iVar4, uVar5, 4, 2, 0xeb, 0x3d);
                if (uVar6 == 0xff)
                {
                    return 1;
                }
                bVar7 = *(uint8_t *)(iVar4 + uVar6);
                uVar8 = (uint32_t)bVar7;
                uVar6 = sango_character_can_pay_action(uVar8, 1);
                if (uVar6 != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
            bVar1 = *(uint8_t *)(uVar8 * 0x10 + g_character_table_address + 4);
            uVar6 = bbk_rand();
            uVar5 = uVar6 + 3;
            if (-1 < (int)uVar6)
            {
                uVar5 = uVar6;
            }
            uVar6 = (bVar1 / 10) * (uVar6 + ((int)uVar5 >> 2) * -4 + 2) +
                    (uint32_t)(*(uint8_t *)(uVar8 * 0x10 + g_character_table_address + 4) >> 1);
            uVar5 = (uVar6 & 0xffff) + (uint32_t)*puVar9;
            *puVar9 = (uint16_t)uVar5;
            if ((uint32_t)uVar2 < (uVar5 & 0xffff))
            {
                *puVar9 = uVar2;
            }
            sango_city_show_development_result(uVar3, bVar7, (uint8_t)uVar6, 0);
            sango_character_pay_action(uVar8, 1);
            sango_city_pay_command(uVar3, 1);
            local_38 = 1;
            local_2d = 0;
            local_37 = bVar7;
            local_36 = param_1;
            sango_strategy_enqueue_order(&local_38);
            sango_city_remove_character(uVar3, bVar7);
            uVar2 = (&g_first_city_agriculture_limit)[uVar3 * 0x12];
        }
    }
    sango_ui_show_strategy_text(bVar7);
    return 1;
}
#undef local_37
#undef local_36
#undef local_2d
#undef local_38

/* 原函数 0x81c0da0c */
uint32_t sango_city_order_commerce(uint8_t param_1)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define local_2d (*(uint8_t *)(abi_storage + 11))
#define local_38 (*(uint8_t *)(abi_storage + 0))
#define local_37 (*(uint8_t *)(abi_storage + 1))
#define local_36 (*(uint8_t *)(abi_storage + 2))

    uint8_t bVar1;
    uint16_t uVar2;
    uint32_t uVar3;
    int iVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint8_t bVar7;
    uint32_t uVar8;
    uint16_t *puVar9;

    iVar4 = g_scratch_buffer_address;
    uVar3 = (uint32_t)param_1;
    uVar5 = sango_city_list_idle_characters(uVar3, g_scratch_buffer_address);
    bVar7 = 0x54;
    if (uVar5 != 0)
    {
        puVar9 = &g_first_city_commerce + uVar3 * 0x12;
        while (true)
        {
            uVar2 = (&g_first_city_commerce_limit)[uVar3 * 0x12];
            bVar7 = 0x35;
            if ((uint32_t)uVar2 <= (uint32_t)*puVar9)
                break;
            uVar5 = sango_city_can_pay_command(uVar3, 2);
            if (uVar5 == 0)
            {
                bVar7 = 0x3b;
                break;
            }
            uVar5 = sango_city_list_idle_characters(uVar3, iVar4);
            if (uVar5 == 0)
            {
                return 1;
            }
            while (true)
            {
                sango_strategy_present();
                uVar6 = sango_ui_select_character(iVar4, uVar5, 4, 2, 0xeb, 0x3d);
                if (uVar6 == 0xff)
                {
                    return 1;
                }
                bVar7 = *(uint8_t *)(iVar4 + uVar6);
                uVar8 = (uint32_t)bVar7;
                uVar6 = sango_character_can_pay_action(uVar8, 2);
                if (uVar6 != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
            bVar1 = *(uint8_t *)(uVar8 * 0x10 + g_character_table_address + 4);
            uVar6 = bbk_rand();
            uVar5 = uVar6 + 3;
            if (-1 < (int)uVar6)
            {
                uVar5 = uVar6;
            }
            uVar6 = (int)((bVar1 / 10) * (uVar6 + ((int)uVar5 >> 2) * -4 + 2) +
                          (uint32_t) * (uint8_t *)(uVar8 * 0x10 + g_character_table_address + 4)) >>
                    1;
            uVar5 = (uVar6 & 0xffff) + (uint32_t)*puVar9;
            *puVar9 = (uint16_t)uVar5;
            if ((uint32_t)uVar2 < (uVar5 & 0xffff))
            {
                *puVar9 = uVar2;
            }
            sango_city_show_development_result(uVar3, bVar7, (uint8_t)uVar6, 1);
            sango_character_pay_action(uVar8, 2);
            sango_city_pay_command(uVar3, 2);
            local_38 = 2;
            local_2d = 0;
            local_37 = bVar7;
            local_36 = param_1;
            sango_strategy_enqueue_order(&local_38);
            sango_city_remove_character(uVar3, bVar7);
        }
    }
    sango_ui_show_strategy_text(bVar7);
    return 1;
}
#undef local_2d
#undef local_38
#undef local_37
#undef local_36

/* 原函数 0x81c0dc30 */
void sango_city_show_development_result(uint32_t param_1, uint8_t param_2, uint8_t param_3,
                                        uint8_t param_4)
{
    char *source;
    char *destination;
    uint32_t uVar1;

    uVar1 = param_1 & 0xff;
    source = (char *)(g_scratch_buffer_address + 0x15e);
    destination = (char *)(g_scratch_buffer_address + 300);
    if (param_4 == 1)
    {
        sango_resource_read_text(0x40, 0x74, destination);
        uVar1 = (uint32_t)(uint16_t)(&g_first_city_commerce)[uVar1 * 0x12];
    }
    else if (param_4 < 2)
    {
        if (param_4 != 0)
            goto LAB_81c0dc94;
        sango_resource_read_text(0x40, 0x71, destination);
        uVar1 = (uint32_t)(uint16_t)(&g_first_city_agriculture)[uVar1 * 0x12];
    }
    else if (param_4 == 2)
    {
        sango_resource_read_text(0x40, 0x75, destination);
        uVar1 = (uint32_t)(uint8_t)(&g_first_city_loyalty)[uVar1 * 0x24];
    }
    else
    {
        if (param_4 != 3)
            goto LAB_81c0dc94;
        sango_resource_read_text(0x40, 0x76, destination);
        uVar1 = (uint32_t)(uint8_t)(&g_first_city_disaster_prevention)[uVar1 * 0x24];
    }
    sango_format_integer(uVar1, source, 10);
LAB_81c0dc94:
    bbk_strcat(destination, source);
    sango_resource_read_text(0x40, 0x72, source);
    bbk_strcat(destination, source);
    sango_format_integer((uint32_t)param_3, source, 10);
    bbk_strcat(destination, source);
    sango_resource_read_text(0x40, 0x73, source);
    bbk_strcat(destination, source);
    sango_strategy_present();
    sango_ui_show_character_message(param_2, destination);
    return;
}

/* 原函数 0x81c0ddf0 */
uint32_t sango_city_order_search(uint8_t param_1)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define local_28 (*(uint8_t *)(abi_storage + 0))
#define local_27 (*(uint8_t *)(abi_storage + 1))
#define local_26 (*(uint8_t *)(abi_storage + 2))
#define local_1d (*(uint8_t *)(abi_storage + 11))

    uint32_t uVar1;
    int iVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint8_t bVar5;
    char *pcVar6;
    uint32_t uVar7;

    iVar2 = g_scratch_buffer_address;
    uVar1 = (uint32_t)param_1;
    uVar3 = sango_city_list_idle_characters(uVar1, g_scratch_buffer_address);
    bVar5 = 0x54;
    if (uVar3 != 0)
    {
        while (uVar3 = sango_city_can_pay_command(uVar1, 3), uVar3 != 0)
        {
            uVar3 = sango_city_list_idle_characters(uVar1, iVar2);
            if (uVar3 == 0)
            {
                return 1;
            }
            while (true)
            {
                sango_strategy_present();
                uVar4 = sango_ui_select_character(iVar2, uVar3, 4, 2, 0xeb, 0x3d);
                if (uVar4 == 0xff)
                {
                    return 1;
                }
                bVar5 = *(uint8_t *)(iVar2 + uVar4);
                uVar7 = (uint32_t)bVar5;
                uVar4 = sango_character_can_pay_action(uVar7, 3);
                if (uVar4 != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
            sango_character_pay_action(uVar7, 3);
            sango_city_pay_command(uVar1, 3);
            uVar3 = bbk_rand();
            uVar4 = (int)uVar3 % 3 & 0xff;
            uVar3 = uVar4 - 0x6f;
            if (g_player_character != uVar7)
            {
                uVar3 = uVar4 - 0x72;
            }
            pcVar6 = (char *)(g_scratch_buffer_address + 300);
            sango_resource_read_text(0x40, uVar3 & 0xff, pcVar6);
            sango_ui_show_character_message(bVar5, pcVar6);
            local_28 = 3;
            local_1d = 0;
            local_27 = bVar5;
            local_26 = param_1;
            sango_strategy_enqueue_order(&local_28);
            sango_city_remove_character(uVar1, bVar5);
        }
        bVar5 = 0x3b;
    }
    sango_ui_show_strategy_text(bVar5);
    return 1;
}
#undef local_28
#undef local_27
#undef local_26
#undef local_1d

/* 原函数 0x81c0df94 */
uint32_t sango_city_order_disaster_prevention(uint8_t param_1)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define local_28 (*(uint8_t *)(abi_storage + 0))
#define local_27 (*(uint8_t *)(abi_storage + 1))
#define local_26 (*(uint8_t *)(abi_storage + 2))
#define local_1d (*(uint8_t *)(abi_storage + 11))

    uint32_t uVar1;
    int iVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint8_t bVar5;
    int iVar6;

    iVar2 = g_scratch_buffer_address;
    uVar1 = (uint32_t)param_1;
    uVar3 = sango_city_list_idle_characters(uVar1, g_scratch_buffer_address);
    bVar5 = 0x54;
    if (uVar3 != 0)
    {
        while (uVar3 = sango_city_can_pay_command(uVar1, 4), uVar3 != 0)
        {
            iVar6 = uVar1 * 0x24;
            if (((&g_first_city_status)[iVar6] == '\0') &&
                (99 < (uint8_t)(&g_first_city_disaster_prevention)[iVar6]))
            {
                bVar5 = 0x3d;
                goto LAB_81c0e16c;
            }
            uVar3 = sango_city_list_idle_characters(uVar1, iVar2);
            if (uVar3 == 0)
            {
                return 1;
            }
            while (true)
            {
                sango_strategy_present();
                uVar4 = sango_ui_select_character(iVar2, uVar3, 4, 2, 0xeb, 0x3d);
                if (uVar4 == 0xff)
                {
                    return 1;
                }
                bVar5 = *(uint8_t *)(iVar2 + uVar4);
                uVar4 = sango_character_can_pay_action((uint32_t)bVar5, 4);
                if (uVar4 != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
            sango_character_pay_action((uint32_t)bVar5, 4);
            sango_city_pay_command(uVar1, 4);
            uVar4 = bbk_rand();
            uVar3 = uVar4 + 3;
            if (-1 < (int)uVar4)
            {
                uVar3 = uVar4;
            }
            uVar3 = uVar4 + ((int)uVar3 >> 2) * -4 + 1;
            uVar4 = (uVar3 & 0xff) + (uint32_t)(uint8_t)(&g_first_city_disaster_prevention)[iVar6];
            (&g_first_city_status)[iVar6] = 0;
            (&g_first_city_disaster_prevention)[iVar6] = (char)uVar4;
            if (100 < (uVar4 & 0xff))
            {
                (&g_first_city_disaster_prevention)[iVar6] = 100;
            }
            sango_city_show_development_result(uVar1, bVar5, (uint8_t)uVar3, 3);
            local_28 = 4;
            local_1d = 0;
            local_27 = bVar5;
            local_26 = param_1;
            sango_strategy_enqueue_order(&local_28);
            sango_city_remove_character(uVar1, bVar5);
        }
        bVar5 = 0x3b;
    }
LAB_81c0e16c:
    sango_ui_show_strategy_text(bVar5);
    return 1;
}
#undef local_28
#undef local_27
#undef local_26
#undef local_1d

/* 原函数 0x81c0e184 */
uint32_t sango_city_order_patrol(uint8_t param_1)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define local_30 (*(uint8_t *)(abi_storage + 0))
#define local_2f (*(uint8_t *)(abi_storage + 1))
#define local_2e (*(uint8_t *)(abi_storage + 2))
#define local_25 (*(uint8_t *)(abi_storage + 11))

    uint32_t uVar1;
    int iVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t *puVar5;
    uint8_t bVar6;
    uint32_t uVar7;
    uint8_t *pbVar8;

    iVar2 = g_scratch_buffer_address;
    uVar1 = (uint32_t)param_1;
    uVar3 = sango_city_list_idle_characters(uVar1, g_scratch_buffer_address);
    bVar6 = 0x54;
    if (uVar3 != 0)
    {
        while (uVar3 = sango_city_can_pay_command(uVar1, 5), uVar3 != 0)
        {
            uVar3 = sango_city_list_idle_characters(uVar1, iVar2);
            if (uVar3 == 0)
            {
                return 1;
            }
            while (true)
            {
                sango_strategy_present();
                uVar4 = sango_ui_select_character(iVar2, uVar3, 4, 2, 0xeb, 0x3d);
                if (uVar4 == 0xff)
                {
                    return 1;
                }
                bVar6 = *(uint8_t *)(iVar2 + uVar4);
                uVar4 = sango_character_can_pay_action((uint32_t)bVar6, 5);
                if (uVar4 != 0)
                    break;
                sango_ui_show_strategy_text(0x3c);
            }
            sango_character_pay_action((uint32_t)bVar6, 5);
            sango_city_pay_command(uVar1, 5);
            uVar4 = bbk_rand();
            uVar3 = uVar4 + 3;
            if (-1 < (int)uVar4)
            {
                uVar3 = uVar4;
            }
            pbVar8 = &g_first_city_loyalty + uVar1 * 0x24;
            uVar7 = (uint32_t)*pbVar8;
            uVar3 = uVar4 + ((int)uVar3 >> 2) * -4 + 1 & 0xff;
            if (100 < uVar7 + uVar3)
            {
                uVar3 = 100 - uVar7 & 0xff;
            }
            *pbVar8 = (uint8_t)(uVar3 + uVar7);
            if (100 < (uVar3 + uVar7 & 0xff))
            {
                *pbVar8 = 100;
            }
            puVar5 = &g_first_city_population_limit + uVar1 * 9;
            uVar4 = *puVar5;
            *puVar5 = uVar4 + 100;
            if ((uint32_t)(&g_first_city_population)[uVar1 * 9] < uVar4 + 100)
            {
                *puVar5 = (&g_first_city_population)[uVar1 * 9];
            }
            sango_city_show_development_result(uVar1, bVar6, (uint8_t)uVar3, 2);
            local_30 = 5;
            local_25 = 0;
            local_2f = bVar6;
            local_2e = param_1;
            sango_strategy_enqueue_order(&local_30);
            sango_city_remove_character(uVar1, bVar6);
        }
        bVar6 = 0x3b;
    }
    sango_ui_show_strategy_text(bVar6);
    return 1;
}
#undef local_30
#undef local_2f
#undef local_2e
#undef local_25

/* 原函数 0x81c0e38c */
uint32_t sango_city_order_recruit_captive(uint8_t param_1)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define local_38 (*(uint8_t *)(abi_storage + 0))
#define local_37 (*(uint8_t *)(abi_storage + 1))
#define local_36 (*(uint8_t *)(abi_storage + 2))
#define local_35 (*(char *)(abi_storage + 3))
#define local_2d (*(uint8_t *)(abi_storage + 11))

    char cVar1;
    uint32_t uVar2;
    char *pcVar3;
    char *pcVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint8_t bVar7;

    pcVar3 = g_scratch_buffer_address;
    uVar2 = (uint32_t)param_1;
    uVar5 = sango_city_list_idle_characters(uVar2, (int)g_scratch_buffer_address);
    bVar7 = 0x54;
    if (uVar5 != 0)
    {
    LAB_81c0e3e4:
        uVar5 = sango_city_list_captives(uVar2, (int)pcVar3);
        if (uVar5 != 0)
        {
            sango_strategy_present();
            uVar5 = sango_ui_select_character((int)pcVar3, uVar5, 4, 2, 0xeb, 0x3d);
            if (uVar5 == 0xff)
            {
                return 1;
            }
            cVar1 = pcVar3[uVar5];
            uVar5 = sango_city_list_idle_characters(uVar2, (int)pcVar3);
            if (uVar5 == 0)
            {
                return 1;
            }
            while (true)
            {
                sango_strategy_present();
                uVar6 = sango_ui_select_character((int)pcVar3, uVar5, 4, 2, 0xeb, 0x3d);
                if (uVar6 == 0xff)
                    break;
                bVar7 = pcVar3[uVar6];
                uVar6 = sango_character_can_pay_action((uint32_t)bVar7, 6);
                if (uVar6 != 0)
                {
                    sango_character_pay_action((uint32_t)bVar7, 6);
                    local_38 = 6;
                    local_2d = 0;
                    local_37 = bVar7;
                    local_36 = param_1;
                    local_35 = cVar1;
                    sango_strategy_enqueue_order(&local_38);
                    sango_city_remove_character(uVar2, bVar7);
                    pcVar4 = g_scratch_buffer_address;
                    sango_resource_read_text(0x40, 0xa2, g_scratch_buffer_address);
                    sango_strategy_present();
                    sango_ui_show_character_message(bVar7, pcVar4);
                    break;
                }
                sango_ui_show_strategy_text(0x3c);
            }
            goto LAB_81c0e3e4;
        }
        bVar7 = 0x58;
    }
    sango_ui_show_strategy_text(bVar7);
    return 1;
}
#undef local_38
#undef local_37
#undef local_36
#undef local_35
#undef local_2d

/* 原函数 0x81c0e53c */
uint32_t sango_city_order_execute_captive(uint32_t param_1)
{
    char cVar1;
    uint32_t uVar2;
    int iVar3;
    char *pcVar4;
    uint8_t *pbVar5;
    uint32_t uVar6;

    iVar3 = g_scratch_buffer_address;
    uVar6 = param_1 & 0xff;
    uVar2 = sango_city_list_captives(uVar6, g_scratch_buffer_address);
    if (uVar2 == 0)
    {
        sango_ui_show_strategy_text(0x58);
    }
    uVar2 = sango_ui_select_character(iVar3, uVar2, 4, 2, 0xeb, 0x3d);
    pbVar5 = (uint8_t *)(iVar3 + uVar2);
    if (uVar2 != 0xff)
    {
        iVar3 = g_character_table_address + (uint32_t)*pbVar5 * 0x10;
        if (*(char *)(iVar3 + 0xc) == '\0')
        {
            cVar1 = *(char *)(iVar3 + 0xd);
        }
        else
        {
            sango_city_add_item(uVar6, *(char *)(iVar3 + 0xc) - 1);
            sango_character_add_item(*(char *)(iVar3 + 0xc) - 1);
            cVar1 = *(char *)(iVar3 + 0xd);
        }
        if (cVar1 != '\0')
        {
            sango_city_add_item(uVar6, cVar1 - 1);
            sango_character_add_item(*(char *)(iVar3 + 0xd) - 1);
        }
        pcVar4 = (char *)(g_scratch_buffer_address + 300);
        uVar2 = bbk_rand();
        sango_resource_read_text(0x40, (int)uVar2 % 3 + 0x7dU & 0xff, pcVar4);
        sango_strategy_present();
        sango_ui_show_character_message(*pbVar5, pcVar4);
        sango_city_remove_character(uVar6, *pbVar5);
    }
    return 1;
}

/* 原函数 0x81c0e6c4 */
uint32_t sango_city_order_exile_character(uint32_t param_1)
{
    uint8_t bVar1;
    char cVar2;
    int iVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    int iVar7;

    iVar3 = g_scratch_buffer_address;
    uVar6 = param_1 & 0xff;
    uVar4 = sango_city_list_idle_characters(uVar6, g_scratch_buffer_address);
    uVar5 = sango_city_list_captives(uVar6, iVar3 + uVar4);
    uVar4 = uVar4 + uVar5 & 0xff;
    if (uVar4 == 0)
    {
        sango_ui_show_strategy_text(0x54);
    }
    else
    {
        uVar4 = sango_ui_select_character(iVar3, uVar4, 4, 2, 0xeb, 0x3d);
        if (uVar4 != 0xff)
        {
            bVar1 = *(uint8_t *)(iVar3 + uVar4);
            iVar7 = (uint32_t)bVar1 * 0x10;
            if ((uint32_t)g_player_character != (uint32_t)bVar1)
            {
                *(uint8_t *)(iVar7 + g_character_table_address + 1) = 0;
                uVar4 = bbk_rand();
                uVar4 = (int)uVar4 % 0x26 & 0xff;
                if (((((char *)(iVar7 + g_character_table_address))[1] == -1) &&
                     (cVar2 = *(char *)(iVar7 + g_character_table_address), cVar2 != '\0')) &&
                    (uVar5 = sango_faction_list_cities((uint32_t)(uint8_t)(cVar2 - 1), iVar3),
                     uVar5 != 0))
                {
                    ((uint8_t *)(iVar7 + g_character_table_address))[1] =
                        *(uint8_t *)(iVar7 + g_character_table_address);
                    uVar4 = bbk_rand();
                    if (uVar5 == 0)
                    {
                        sango_legacy_trap(7);
                    }
                    uVar4 = (int)uVar4 % (int)uVar5 & 0xff;
                }
                sango_city_remove_character(uVar6, bVar1);
                sango_city_add_character(uVar4, bVar1);
                return 1;
            }
            sango_ui_show_message(&g_legacy_data_81c204d0, 2);
            return 0;
        }
    }
    return 1;
}

/* 原函数 0x81c0e87c */
uint32_t sango_city_order_reward(uint32_t param_1)
{
    uint8_t bVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    int iVar4;
    uint32_t uVar5;
    uint8_t bVar6;
    uint8_t bVar7;
    char *pcVar8;
    int iVar9;
    uint32_t uVar10;
    int iVar11;
    int iVar12;

    uVar10 = param_1 & 0xff;
    iVar9 = g_scratch_buffer_address + 200;
    uVar2 = sango_city_list_items(uVar10, iVar9);
    bVar6 = 0x56;
    if (uVar2 != 0)
    {
        uVar2 = sango_ui_select_item(iVar9, uVar2, 4, 2, 0xeb, 0x3d);
        if (uVar2 == 0xff)
        {
            return 1;
        }
        while (true)
        {
            iVar4 = g_scratch_buffer_address;
            iVar12 = 0;
            uVar3 = sango_city_list_idle_characters(uVar10, g_scratch_buffer_address);
            if (uVar3 == 0)
                break;
            uVar3 = sango_ui_select_character(iVar4, uVar3, 4, 2, 0xeb, 0x3d);
            if (uVar3 == 0xff)
            {
                return 1;
            }
            bVar6 = *(uint8_t *)(iVar4 + uVar3);
            uVar3 = (uint32_t)bVar6;
            bVar1 = *(uint8_t *)(iVar9 + uVar2);
            iVar11 = uVar3 * 0x10;
            iVar4 = g_character_table_address + iVar11;
            if ((*(char *)(iVar4 + 0xc) == '\0') || (iVar12 = 1, *(char *)(iVar4 + 0xd) == '\0'))
            {
                uVar5 = sango_item_apply_attributes((uint32_t)bVar1, uVar3);
                bVar7 = 0x6d;
                if (uVar5 == 1)
                {
                LAB_81c0e9b4:
                    sango_city_remove_item(uVar10, bVar1);
                    if (g_player_character == uVar3)
                    {
                        sango_strategy_present();
                        sango_ui_show_character_message(bVar6, &g_legacy_data_81c204e0);
                        return 1;
                    }
                    pcVar8 = (char *)(g_scratch_buffer_address + 300);
                    uVar2 = bbk_rand();
                    sango_resource_read_text(0x40, (int)uVar2 % 3 - 0x7dU & 0xff, pcVar8);
                    sango_strategy_present();
                    sango_ui_show_character_message(bVar6, pcVar8);
                    *(char *)(iVar11 + g_character_table_address + 5) =
                        *(char *)(iVar11 + g_character_table_address + 5) + '\b';
                    if (*(uint8_t *)(iVar11 + g_character_table_address + 5) < 0x65)
                    {
                        return 1;
                    }
                    *(uint8_t *)(iVar11 + g_character_table_address + 5) = 100;
                    return 1;
                }
                if ((int)uVar5 < 2)
                {
                    if (uVar5 == 0)
                    {
                        *(uint8_t *)(iVar4 + 0xc + iVar12) = bVar1 + 1;
                    }
                    goto LAB_81c0e9b4;
                }
                if (uVar5 != 0xff)
                    goto LAB_81c0e9b4;
            }
            else
            {
                bVar7 = 0x57;
            }
            sango_ui_show_strategy_text(bVar7);
            sango_strategy_present();
        }
        bVar6 = 0x54;
    }
    sango_ui_show_strategy_text(bVar6);
    return 1;
}

/* 原函数 0x81c0eb10 */
uint32_t sango_city_order_trade(uint8_t param_1)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define local_3e (*(uint8_t *)(abi_storage + 18))
#define local_35 (*(uint8_t *)(abi_storage + 27))
#define acStack_50 (*(char(*)[16])(abi_storage + 0))
#define local_30 (*(uint16_t(*)[4])(abi_storage + 32))
#define local_40 (*(uint8_t *)(abi_storage + 16))
#define local_3f (*(uint8_t *)(abi_storage + 17))

    uint32_t uVar1;
    int iVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint8_t bVar5;

    iVar2 = g_scratch_buffer_address;
    uVar1 = (uint32_t)param_1;
    do
    {
        while (true)
        {
            uVar3 = sango_city_list_idle_characters(uVar1, iVar2);
            bVar5 = 0x54;
            if (uVar3 == 0)
                goto LAB_81c0ed68;
            sango_strategy_present();
            uVar3 = sango_ui_select_character(iVar2, uVar3, 4, 2, 0xeb, 0x3d);
            if (uVar3 == 0xff)
            {
                return 1;
            }
            bVar5 = *(uint8_t *)(iVar2 + uVar3);
            uVar3 = sango_character_can_pay_action((uint32_t)bVar5, 0xb);
            if (uVar3 != 0)
                break;
            sango_ui_show_strategy_text(0x3c);
        }
        sango_resource_read_text(0x40, 0x2e, acStack_50);
        local_30[0] = 0x77;
        local_30[2] = 0x8f;
        local_30[1] = 0xe;
        local_30[3] = 0x26;
        uVar3 = sango_ui_choose_option(local_30, 0, acStack_50);
    } while (uVar3 == 0xff);
    if (uVar3 == 0)
    {
        uVar3 = sango_city_can_pay_command(uVar1, 0xc);
        if (uVar3 == 0)
        {
            bVar5 = 0x3b;
        LAB_81c0ed68:
            sango_ui_show_strategy_text(bVar5);
            return 1;
        }
        if (((uint16_t)(&g_first_city_money)[uVar1 * 0x12] / 5 != 0) &&
            (uVar3 =
                 sango_ui_input_food_amount(1, (uint16_t)(&g_first_city_money)[uVar1 * 0x12] / 5),
             uVar3 != 0xffff))
        {
            (&g_first_city_money)[uVar1 * 0x12] =
                (&g_first_city_money)[uVar1 * 0x12] + (short)uVar3 * -5;
            (&g_first_city_food)[uVar1 * 0x12] = (short)uVar3 + (&g_first_city_food)[uVar1 * 0x12];
        }
    }
    else if (uVar3 == 1)
    {
        if ((uint16_t)(&g_first_city_food)[uVar1 * 0x12] == 0)
        {
            sango_ui_show_message(&g_legacy_data_81c20510, 2);
            return 1;
        }
        uVar3 =
            sango_ui_input_food_amount(1, (uint32_t)(uint16_t)(&g_first_city_food)[uVar1 * 0x12]);
        if (uVar3 != 0xffff)
        {
            uVar4 = (uVar3 & 0x7fff) * 2 + (uint32_t)(uint16_t)(&g_first_city_money)[uVar1 * 0x12];
            (&g_first_city_food)[uVar1 * 0x12] = (&g_first_city_food)[uVar1 * 0x12] - (short)uVar3;
            (&g_first_city_money)[uVar1 * 0x12] = (short)uVar4;
            if (30000 < (uVar4 & 0xffff))
            {
                (&g_first_city_money)[uVar1 * 0x12] = 30000;
            }
        }
    }
    sango_character_pay_action((uint32_t)bVar5, 0xb);
    local_40 = 0xb;
    local_35 = 0;
    local_3f = bVar5;
    local_3e = param_1;
    sango_strategy_enqueue_order(&local_40);
    sango_city_remove_character(uVar1, bVar5);
    return 1;
}
#undef local_3e
#undef local_35
#undef acStack_50
#undef local_30
#undef local_40
#undef local_3f

/* 原函数 0x81c0ed78 */
uint32_t sango_city_order_banquet(uint32_t param_1)
{
    char *pcVar1;
    char *pcVar2;
    uint32_t uVar3;
    uint8_t bVar4;
    uint8_t bVar5;
    int iVar6;
    uint32_t uVar7;

    pcVar1 = g_scratch_buffer_address;
    uVar7 = param_1 & 0xff;
    uVar3 = sango_city_list_idle_characters(uVar7, (int)g_scratch_buffer_address);
    bVar5 = 0x54;
    if (uVar3 != 0)
    {
        while (uVar3 = sango_city_can_pay_command(uVar7, 0xc), uVar3 != 0)
        {
            sango_strategy_present();
            uVar3 = sango_city_list_idle_characters(uVar7, (int)pcVar1);
            if (uVar3 == 0)
            {
                return 1;
            }
            uVar3 = sango_ui_select_character((int)pcVar1, uVar3, 4, 2, 0xeb, 0x3d);
            if (uVar3 == 0xff)
            {
                return 1;
            }
            bVar5 = pcVar1[uVar3];
            iVar6 = g_character_table_address + (uint32_t)bVar5 * 0x10;
            sango_city_pay_command(uVar7, 0xc);
            bVar4 = *(char *)(iVar6 + 8) + 0x32;
            *(uint8_t *)(iVar6 + 8) = bVar4;
            if (100 < bVar4)
            {
                *(uint8_t *)(iVar6 + 8) = 100;
            }
            pcVar2 = g_scratch_buffer_address;
            if ((uint32_t)g_player_character == (uint32_t)bVar5)
            {
                sango_strategy_present();
                sango_ui_show_character_message(bVar5, &g_legacy_data_81c2051c);
            }
            else
            {
                sango_resource_read_text(0x40, 0xa1, g_scratch_buffer_address);
                sango_strategy_present();
                sango_ui_show_character_message(bVar5, pcVar2);
                if (*(uint8_t *)(iVar6 + 5) < 100)
                {
                    *(uint8_t *)(iVar6 + 5) = *(uint8_t *)(iVar6 + 5) + 1;
                }
            }
        }
        bVar5 = 0x3b;
    }
    sango_ui_show_strategy_text(bVar5);
    return 1;
}

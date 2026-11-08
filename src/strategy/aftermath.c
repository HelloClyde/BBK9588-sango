#include "sango_internal.h"

/* 战后处理、君主继承和战斗事件提示。 */

/* 原函数 0x81c10d6c */
uint32_t sango_strategy_handle_defeated_units(uint32_t param_1, char *param_2)
{
    char cVar1;
    uint8_t index;
    uint32_t uVar2;
    int iVar3;
    char *source;
    char *pcVar4;
    uint32_t uVar5;
    int iVar6;
    uint32_t uVar7;
    uint32_t uVar8;
    uint32_t uVar9;
    char *destination;

    source = (char *)(g_scratch_buffer_address + 0x154);
    uVar8 = param_1 & 0xff;
    uVar9 = 0xff;
    destination = (char *)(g_scratch_buffer_address + 300);
    uVar7 = 0;
    pcVar4 = param_2;
    do
    {
        index = *pcVar4 - 1;
        if (*pcVar4 != '\0')
        {
            uVar5 = (uint32_t)index;
            iVar6 = g_character_table_address + uVar5 * 0x10;
            uVar2 = bbk_rand();
            uVar2 = (int)uVar2 % 100 & 0xff;
            if (*(uint8_t *)(iVar6 + 4) < uVar2)
            {
                if (*(char *)(iVar6 + 1) == *pcVar4)
                {
                    uVar9 = uVar5;
                }
            LAB_81c10e88:
                sango_character_return_to_city(index, uVar8);
            }
            else
            {
                iVar3 = sango_character_escape_to_friendly_city(index);
                if (iVar3 == 0)
                {
                    if (*(char *)(iVar6 + 1) == *pcVar4)
                    {
                        uVar9 = uVar5;
                    }
                    if (uVar2 != 0)
                        goto LAB_81c10e88;
                    if (*(char *)(iVar6 + 0xc) == '\0')
                    {
                        cVar1 = *(char *)(iVar6 + 0xd);
                    }
                    else
                    {
                        sango_city_add_item(uVar8, *(char *)(iVar6 + 0xc) - 1);
                        sango_item_mark_discovered(*(char *)(iVar6 + 0xc) - 1);
                        cVar1 = *(char *)(iVar6 + 0xd);
                    }
                    if (cVar1 != '\0')
                    {
                        sango_city_add_item(uVar8, cVar1 - 1);
                        sango_item_mark_discovered(*(char *)(iVar6 + 0xd) - 1);
                    }
                    if (g_battle_control_mode != '\x02')
                    {
                        sango_load_named_text(index, destination);
                        sango_resource_read_text(0x40, 0x6c, source);
                        bbk_strcat(destination, source);
                        sango_ui_show_message(destination, 2);
                    }
                }
            }
        }
        uVar7 = uVar7 + 1 & 0xff;
        pcVar4 = param_2 + uVar7;
        if (9 < uVar7)
        {
            return uVar9;
        }
    } while (true);
}

/* 原函数 0x81c10f78 */
void sango_character_return_to_city(uint8_t param_1, uint32_t param_2)
{
    uint8_t uVar1;
    uint8_t *puVar2;

    puVar2 = (uint8_t *)(g_character_table_address + (uint32_t)param_1 * 0x10);
    uVar1 = puVar2[1];
    puVar2[1] = 0xff;
    *puVar2 = uVar1;
    *(uint16_t *)(puVar2 + 10) = 0;
    g_capture_count_view2 = g_capture_count_view2 + '\x01';
    g_captured_character = param_1;
    sango_city_add_character(param_2 & 0xff, param_1);
    return;
}

/* 原函数 0x81c10fdc */
uint32_t sango_character_escape_to_friendly_city(uint8_t param_1)
{
    int iVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint32_t uVar4;

    iVar1 = g_scratch_buffer_address;
    uVar2 = sango_faction_list_cities(
        *(uint8_t *)((uint32_t)param_1 * 0x10 + g_character_table_address + 1) - 1 & 0xff,
        g_scratch_buffer_address);
    uVar3 = 0;
    if (uVar2 != 0)
    {
        uVar4 = bbk_rand();
        if (uVar2 == 0)
        {
            sango_legacy_trap(7);
        }
        sango_city_add_character(
            (uint32_t) * (uint8_t *)(iVar1 + ((int)uVar4 % (int)uVar2 & 0xffU)), param_1);
        uVar3 = 1;
    }
    return uVar3;
}

/* 原函数 0x81c1107c */
uint32_t sango_city_choose_postbattle_governor(uint8_t param_1, uint32_t param_2)
{
    uint8_t uVar1;
    uint8_t *pbVar2;
    uint32_t uVar3;
    int iVar4;
    uint8_t *pbVar5;
    int iVar6;
    uint32_t uVar7;
    uint32_t uVar8;
    uint32_t uVar9;

    pbVar2 = g_scratch_buffer_address;
    uVar3 = sango_city_list_idle_characters(param_2 & 0xff, (int)g_scratch_buffer_address);
    iVar6 = g_character_table_address;
    uVar1 = *(uint8_t *)((uint32_t)param_1 * 0x10 + g_character_table_address + 1);
    iVar4 = (param_2 & 0xff) * 0x24;
    (&g_first_city_governor)[iVar4] = param_1 + 1;
    (&g_first_city_owner)[iVar4] = uVar1;
    uVar8 = 0xff;
    uVar7 = 0;
    pbVar5 = pbVar2;
    uVar9 = uVar8;
    if (uVar3 != 0)
    {
        while (true)
        {
            uVar8 = (uint32_t)*pbVar5;
            iVar6 = iVar6 + uVar8 * 0x10;
            if ((uint32_t) * (uint8_t *)(iVar6 + 1) == uVar8 + 1)
            {
                g_capture_count_view2 = g_capture_count_view2 + '\x01';
                g_captured_character = *pbVar5;
                *(uint8_t *)(iVar6 + 1) = 0xff;
            }
            else
            {
                *(uint8_t *)(iVar6 + 1) = 0;
                uVar8 = uVar9;
            }
            uVar7 = uVar7 + 1 & 0xff;
            *(uint16_t *)(iVar6 + 10) = 0;
            if (uVar3 <= uVar7)
                break;
            pbVar5 = pbVar2 + uVar7;
            iVar6 = g_character_table_address;
            uVar9 = uVar8;
        }
    }
    return uVar8;
}

/* 原函数 0x81c11188 */
void sango_strategy_resolve_ruler_succession(uint8_t previous_ruler)
{
    unsigned char abi_storage[224] __attribute__((aligned(8)));
#define owner_name (*(uint8_t(*)[104])(abi_storage + 0))
#define character_name (*(uint8_t(*)[104])(abi_storage + 104))

    uint32_t city_count;
    uint32_t character_count;
    uint8_t successor_id;
    uint8_t *roster_entry;
    uint8_t *roster_cursor;
    uint32_t candidate_index;
    uint32_t roster_index;
    uint8_t *successor_entry;
    uint8_t *member_ids;

    uint32_t previous_ruler_id = (uint32_t)previous_ruler;
    sango_strategy_show_new_ruler(previous_ruler);
    roster_cursor = g_scratch_buffer_address;
    city_count = sango_faction_list_cities(previous_ruler_id, (int)g_scratch_buffer_address);
    member_ids = roster_cursor + 0x26;
    if (city_count == 0)
    {
        sango_strategy_show_faction_destroyed(previous_ruler);
    }
    else
    {
        character_count = sango_faction_list_characters(previous_ruler_id, (int)member_ids);
        if (character_count == 0)
        {
            sango_strategy_show_faction_destroyed(previous_ruler);
            roster_index = 0;
            member_ids = roster_cursor;
            if (city_count != 0)
            {
                do
                {
                    roster_index = roster_index + 1 & 0xff;
                    (&g_first_city_owner)[(uint32_t)*member_ids * 0x24] = 0;
                    member_ids = roster_cursor + roster_index;
                } while (roster_index < city_count);
            }
        }
        else
        {
            candidate_index = 1;
            if (g_player_character == previous_ruler_id)
            {
                sango_ui_show_strategy_text(0x50);
                do
                {
                    roster_index = sango_ui_select_character((int)member_ids, character_count, 4, 2,
                                                             0xeb, 0x3d);
                } while (roster_index == 0xff);
                successor_entry = member_ids + roster_index;
                g_player_character = *successor_entry;
                successor_id = *successor_entry;
            }
            else
            {
                successor_entry = member_ids;
                if (1 < character_count)
                {
                    do
                    {
                        roster_entry = member_ids + candidate_index;
                        candidate_index = candidate_index + 1 & 0xff;
                        if (*(uint8_t *)((uint32_t)*successor_entry * 0x10 +
                                         g_character_table_address + 4) <
                            *(uint8_t *)((uint32_t)*roster_entry * 0x10 +
                                         g_character_table_address + 4))
                        {
                            successor_entry = roster_entry;
                        }
                    } while (candidate_index < character_count);
                }
                successor_id = *successor_entry;
            }
            roster_index = 0;
            sango_strategy_show_ruler_changed(successor_id);
            *(uint8_t *)((uint32_t)*successor_entry * 0x10 + g_character_table_address + 5) = 100;
            roster_entry = roster_cursor;
            if (city_count != 0)
            {
                do
                {
                    roster_index = roster_index + 1 & 0xff;
                    (&g_first_city_owner)[(uint32_t)*roster_entry * 0x24] = *successor_entry + 1;
                    roster_entry = roster_cursor + roster_index;
                } while (roster_index < city_count);
            }
            roster_index = 0;
            if (character_count != 0)
            {
                roster_cursor = member_ids;
                do
                {
                    *(uint8_t *)((uint32_t)*roster_cursor * 0x10 + g_character_table_address + 1) =
                        *successor_entry + 1;
                    sango_load_named_text(
                        *(char *)((uint32_t)*roster_cursor * 0x10 + g_character_table_address + 1) +
                            0xff,
                        owner_name);
                    sango_load_named_text(*roster_cursor, character_name);
                    roster_index = roster_index + 1 & 0xff;
                    roster_cursor = member_ids + roster_index;
                } while (roster_index < character_count);
            }
        }
    }
    return;
}
#undef owner_name
#undef character_name

/* 原函数 0x81c11404 */
void sango_strategy_show_new_ruler(uint8_t param_1)
{
    char *source;
    char *destination;

    destination = (char *)(g_scratch_buffer_address + 300);
    source = (char *)(g_scratch_buffer_address + 0x154);
    sango_resource_read_text(0x40, 0x4e, destination);
    sango_load_named_text(param_1, source);
    bbk_strcat(destination, source);
    sango_resource_read_text(0x40, 0x4f, source);
    bbk_strcat(destination, source);
    sango_ui_show_message(destination, 2);
    return;
}

/* 原函数 0x81c11494 */
void sango_strategy_show_ruler_changed(uint8_t param_1)
{
    char *source;
    char *destination;

    destination = (char *)(g_scratch_buffer_address + 300);
    source = (char *)(g_scratch_buffer_address + 0x154);
    sango_load_named_text(param_1, destination);
    sango_resource_read_text(0x40, 0x51, source);
    bbk_strcat(destination, source);
    sango_ui_show_message(destination, 2);
    return;
}

/* 原函数 0x81c114fc */
void sango_strategy_show_faction_destroyed(uint8_t param_1)
{
    char *source;
    char *destination;

    destination = (char *)(g_scratch_buffer_address + 300);
    source = (char *)(g_scratch_buffer_address + 0x154);
    sango_load_named_text(param_1, destination);
    sango_resource_read_text(0x40, 0x53, source);
    bbk_strcat(destination, source);
    sango_ui_show_message(destination, 2);
    return;
}

/* 原函数 0x81c11564 */
uint32_t sango_strategy_queue_army(void *param_1, void *param_2)
{
    char *dst;
    uint32_t uVar1;

    uVar1 = 0;
    do
    {
        if (*(char *)(g_army_slot_used_address + uVar1) == '\0')
        {
            *(char *)(g_army_slot_used_address + uVar1) = '\x01';
            bbk_memcpy((void *)(uVar1 * 10 + g_army_rosters_address), param_2, 10);
            *(char *)((int)param_1 + 1) = (char)uVar1;
            uVar1 = 0x46;
            do
            {
                dst = (char *)(uVar1 * 0xc + g_order_queue_address);
                uVar1 = uVar1 + 1 & 0xff;
                if (*dst == -1)
                {
                    bbk_memcpy(dst, param_1, 0xc);
                    return 1;
                }
            } while (uVar1 < 100);
            return 1;
        }
        uVar1 = uVar1 + 1 & 0xff;
    } while (uVar1 < 100);
    return 0;
}

/* 原函数 0x81c11638 */
void sango_strategy_show_ruler_defection(uint8_t param_1)
{
    char *source;
    char *destination;

    destination = (char *)(g_scratch_buffer_address + 300);
    source = (char *)(g_scratch_buffer_address + 0x154);
    sango_load_named_text(param_1, destination);
    sango_resource_read_text(0x40, 0x52, source);
    bbk_strcat(destination, source);
    sango_ui_show_message(destination, 2);
    return;
}

/* 原函数 0x81c116a0 */
void sango_strategy_show_recruit_success(uint8_t param_1)
{
    char *pcVar1;

    pcVar1 = (char *)(g_scratch_buffer_address + 300);
    sango_resource_read_text(0x40, 0x5f, pcVar1);
    sango_ui_show_character_message(param_1, pcVar1);
    return;
}

/* 原函数 0x81c116f0 */
uint32_t sango_strategy_enqueue_order(void *param_1)
{
    int iVar1;
    uint32_t uVar2;
    char *dst;

    uVar2 = 0;
    iVar1 = 0;
    do
    {
        dst = (char *)((iVar1 + uVar2) * 4 + g_order_queue_address);
        uVar2 = uVar2 + 1 & 0xff;
        if (*dst == -1)
        {
            bbk_memcpy(dst, param_1, 0xc);
            return 0;
        }
        iVar1 = uVar2 << 1;
    } while (uVar2 < 100);
    return 1;
}

/* 原函数 0x81c11758 */
uint32_t sango_strategy_remove_order(void *param_1)
{
    int iVar1;
    uint32_t uVar2;
    char *dst;

    uVar2 = 0x46;
    iVar1 = 0x8c;
    do
    {
        dst = (char *)((iVar1 + uVar2) * 4 + g_order_queue_address);
        uVar2 = uVar2 + 1 & 0xff;
        if (*dst == -1)
        {
            bbk_memcpy(dst, param_1, 0xc);
            return 0;
        }
        iVar1 = uVar2 << 1;
    } while (uVar2 < 100);
    return 1;
}

/* 原函数 0x81c117c0 */
uint32_t sango_strategy_queue_noop(uint8_t *param_1)
{
    *param_1 = 0xff;
    return 1;
}

/* 原函数 0x81c117d0 */
uint32_t sango_city_order_confiscate(uint32_t param_1)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define local_30 (*(uint8_t(*)[8])(abi_storage + 0))

    bool bVar1;
    uint8_t bVar2;
    int iVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    int iVar7;
    char *pcVar8;
    uint8_t *pbVar9;
    char *pcVar10;

    iVar3 = g_scratch_buffer_address;
    while (true)
    {
        uVar4 = sango_city_list_idle_characters(param_1 & 0xff, iVar3);
        if (uVar4 == 0)
        {
            sango_ui_show_strategy_text(0x54);
            return 1;
        }
        sango_strategy_present();
        uVar4 = sango_ui_select_character(iVar3, uVar4, 4, 2, 0xeb, 0x3d);
        if (uVar4 == 0xff)
            break;
        bVar2 = *(uint8_t *)(iVar3 + uVar4);
        uVar4 = (uint32_t)bVar2;
        iVar7 = g_character_table_address + uVar4 * 0x10;
        bVar1 = *(char *)(iVar7 + 0xc) != '\0';
        pcVar10 = (char *)(iVar7 + 0xc);
        if (!bVar1)
        {
            *(uint8_t *)(iVar7 + 0xc) = *(uint8_t *)(iVar7 + 0xd);
            *(uint8_t *)(iVar7 + 0xd) = 0;
        }
        uVar5 = (uint32_t)bVar1;
        if (pcVar10[uVar5] != '\0')
        {
            uVar5 = uVar5 + 1;
        }
        local_30[0] = *pcVar10 - 1;
        local_30[1] = *(char *)(iVar7 + 0xd) + -1;
        if (uVar5 == 0)
        {
            sango_ui_show_strategy_text(0x55);
        }
        else
        {
            sango_strategy_present();
            uVar5 = sango_ui_select_item((int)local_30, uVar5, 4, 2, 0xeb, 0x3d);
            if (uVar5 != 0xff)
            {
                if (g_player_character == uVar4)
                {
                    sango_strategy_present();
                    sango_ui_show_character_message(bVar2, &g_legacy_data_81c20540);
                }
                else
                {
                    pcVar8 = (char *)(g_scratch_buffer_address + 300);
                    uVar6 = bbk_rand();
                    sango_resource_read_text(0x40, (int)uVar6 % 3 - 0x80U & 0xff, pcVar8);
                    sango_strategy_present();
                    sango_ui_show_character_message(bVar2, pcVar8);
                    iVar7 = uVar4 * 0x10 + g_character_table_address;
                    if (*(uint8_t *)(iVar7 + 5) < 0x14)
                    {
                        *(uint8_t *)(iVar7 + 5) = 0;
                    }
                    else
                    {
                        *(uint8_t *)(iVar7 + 5) = *(uint8_t *)(iVar7 + 5) - 0x14;
                    }
                }
                pbVar9 = local_30 + uVar5;
                sango_city_add_item(param_1 & 0xff, *pbVar9);
                sango_item_mark_discovered(*pbVar9);
                sango_item_remove_attributes((uint32_t)*pbVar9, uVar4);
                pcVar10[uVar5] = '\0';
            }
        }
    }
    return 1;
}
#undef local_30

/* 原函数 0x81c11a2c */
uint32_t sango_city_order_plunder(uint8_t param_1)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define local_28 (*(uint8_t *)(abi_storage + 0))
#define local_27 (*(uint8_t *)(abi_storage + 1))
#define local_26 (*(uint8_t *)(abi_storage + 2))
#define local_1d (*(uint8_t *)(abi_storage + 11))

    uint8_t bVar1;
    int iVar2;
    uint32_t uVar3;
    char *pcVar4;

    iVar2 = g_scratch_buffer_address;
    while (true)
    {
        uVar3 = sango_city_list_idle_characters((uint32_t)param_1, iVar2);
        if (uVar3 == 0)
        {
            sango_ui_show_strategy_text(0x54);
            return 1;
        }
        sango_strategy_present();
        uVar3 = sango_ui_select_character(iVar2, uVar3, 4, 2, 0xeb, 0x3d);
        if (uVar3 == 0xff)
            break;
        bVar1 = *(uint8_t *)(iVar2 + uVar3);
        uVar3 = sango_character_can_pay_action((uint32_t)bVar1, 0x18);
        if (uVar3 != 0)
        {
            sango_character_pay_action((uint32_t)bVar1, 0x18);
            pcVar4 = (char *)(g_scratch_buffer_address + 300);
            sango_resource_read_text(0x40, 0x94, pcVar4);
            sango_ui_show_character_message(bVar1, pcVar4);
            local_28 = 0x1a;
            local_1d = 0;
            local_27 = bVar1;
            local_26 = param_1;
            sango_strategy_enqueue_order(&local_28);
            sango_city_remove_character((uint32_t)param_1, bVar1);
            return 1;
        }
        sango_ui_show_strategy_text(0x3c);
    }
    return 1;
}
#undef local_28
#undef local_27
#undef local_26
#undef local_1d

/* 原函数 0x81c11b50 */
uint32_t sango_character_can_pay_action(uint32_t param_1, uint32_t param_2)
{
    int iVar1;

    iVar1 = sango_resource_item(2, '\n', g_resource_package_address);
    return (uint32_t)(*(uint8_t *)(iVar1 + (param_2 & 0xff)) <=
                      *(uint8_t *)((param_1 & 0xff) * 0x10 + g_character_table_address + 8));
}

/* 原函数 0x81c11bbc */
void sango_character_pay_action(uint32_t param_1, uint32_t param_2)
{
    int iVar1;
    int iVar2;

    iVar1 = sango_resource_item(2, '\n', g_resource_package_address);
    iVar2 = (param_1 & 0xff) * 0x10 + g_character_table_address;
    *(char *)(iVar2 + 8) = *(char *)(iVar2 + 8) - *(char *)(iVar1 + (param_2 & 0xff));
    return;
}

/* 原函数 0x81c11c28 */
uint32_t sango_city_find_weakest_target(uint32_t param_1, int param_2)
{
    char cVar1;
    int iVar2;
    uint8_t *pbVar3;
    uint16_t uVar4;
    int iVar5;
    uint32_t uVar6;
    uint16_t uVar7;
    char *pcVar8;
    uint32_t uVar9;
    uint32_t unaff_s1;

    uVar7 = 0xffff;
    uVar9 = 0;
    if ((param_1 & 0xff) != 0)
    {
        do
        {
            uVar4 = 0;
            iVar2 = (uint32_t) * (uint8_t *)(param_2 + uVar9) * 0x24;
            uVar6 = 0;
            if ((uint8_t)(&g_first_city_character_count)[iVar2] != 0)
            {
                pbVar3 = &g_city_character_roster + (uint8_t)(&g_first_city_character_start)[iVar2];
                do
                {
                    uVar6 = uVar6 + 1 & 0xff;
                    iVar5 = (uint32_t)*pbVar3 * 0x10 + g_character_table_address;
                    if (*(char *)(iVar5 + 1) == (&g_first_city_owner)[iVar2])
                    {
                        uVar4 = uVar4 + *(short *)(iVar5 + 10);
                    }
                    pbVar3 = &g_city_character_roster +
                             (uint8_t)(&g_first_city_character_start)[iVar2] + uVar6;
                } while (uVar6 < (uint8_t)(&g_first_city_character_count)[iVar2]);
            }
            uVar6 = 0;
            iVar2 = 0;
            do
            {
                pcVar8 = (char *)((iVar2 + uVar6) * 4 + g_order_queue_address);
                cVar1 = *pcVar8;
                uVar6 = uVar6 + 1 & 0xff;
                if ((((cVar1 != -1) && (cVar1 != '\x0e')) && (cVar1 != '\x1b')) &&
                    (pcVar8[2] == *(uint8_t *)(param_2 + uVar9)))
                {
                    uVar4 = uVar4 + *(short *)((uint32_t)(uint8_t)pcVar8[1] * 0x10 +
                                               g_character_table_address + 10);
                }
                iVar2 = uVar6 << 1;
            } while (uVar6 < 100);
            if (uVar4 < uVar7)
            {
                unaff_s1 = uVar9;
                uVar7 = uVar4;
            }
            uVar9 = uVar9 + 1 & 0xff;
        } while (uVar9 < (param_1 & 0xff));
    }
    return (uint32_t) * (uint8_t *)(param_2 + unaff_s1);
}

/* 原函数 0x81c11d98 */
void sango_strategy_show_army_attack(uint8_t ruler_id, char city_id)
{
    uint8_t *event_images;
    char *message;
    char *text_part;

    sango_display_fill_gray_rectangle(0x3b, 0x75, 0xb3, 0xc9, 0, 0);
    sango_display_draw_rectangle(0x3b, 0x75, 0xb3, 0xc9, 3, 0, 0);
    event_images = (uint8_t *)sango_resource_item(0x4c, '\x01', g_resource_package_address);
    sango_bitmap_draw_frame_screen(0x4d, 0x77, 0x54, 0x40, 0, event_images);
    message = (char *)(g_scratch_buffer_address + 300);
    text_part = (char *)(g_scratch_buffer_address + 0x154);
    if (g_player_character == ruler_id)
    {
        sango_resource_read_text(0x40, 0x62, message);
    }
    else
    {
        sango_load_named_text(ruler_id, message);
    }
    sango_resource_read_text(0x40, 0x61, text_part);
    bbk_strcat(message, text_part);
    sango_city_read_name(city_id, text_part);
    bbk_strcat(message, text_part);
    sango_text_draw_centered(0x77, 0xb9, message);
    sango_input_wait(0x1e, '\0');
    sango_render_clear_rectangle(0x78, 0xd4, 0x9f, 0xef, g_game_context);
    sango_text_draw_context(0x78, 0xd4, text_part, g_game_context);
    return;
}

/* 原函数 0x81c11f18 */
void sango_strategy_show_armies_engage(uint8_t first_ruler, uint8_t second_ruler)
{
    uint8_t *event_images;
    char *text_part;
    char *message;

    sango_display_fill_gray_rectangle(0x3b, 0x75, 0xb3, 0xc9, 0, 0);
    sango_display_draw_rectangle(0x3b, 0x75, 0xb3, 0xc9, 3, 0, 0);
    event_images = (uint8_t *)sango_resource_item(0x4c, '\x01', g_resource_package_address);
    sango_bitmap_draw_frame_screen(0x4d, 0x77, 0x54, 0x40, 1, event_images);
    message = (char *)(g_scratch_buffer_address + 300);
    text_part = (char *)(g_scratch_buffer_address + 0x154);
    sango_load_named_text(first_ruler, message);
    sango_resource_read_text(0x40, 0x68, text_part);
    bbk_strcat(message, text_part);
    sango_load_named_text(second_ruler, text_part);
    bbk_strcat(message, text_part);
    sango_resource_read_text(0x40, 0x69, text_part);
    bbk_strcat(message, text_part);
    sango_text_draw_centered(0x77, 0xb9, message);
    sango_input_wait(0x32, '\0');
    return;
}

/* 原函数 0x81c12058 */
void sango_strategy_show_battle_victory(uint8_t owner_id)
{
    uint8_t *event_images;
    char *message;
    char *text_part;

    sango_display_fill_gray_rectangle(0x3b, 0x75, 0xb3, 0xc9, 0, 0);
    sango_display_draw_rectangle(0x3b, 0x75, 0xb3, 0xc9, 3, 0, 0);
    event_images = (uint8_t *)sango_resource_item(0x4c, '\x01', g_resource_package_address);
    sango_bitmap_draw_frame_screen(0x4d, 0x77, 0x54, 0x40, 2, event_images);
    message = (char *)(g_scratch_buffer_address + 300);
    text_part = (char *)(g_scratch_buffer_address + 0x154);
    if ((uint32_t)owner_id == g_player_character + 1)
    {
        sango_resource_read_text(0x40, 0x62, message);
    }
    else
    {
        sango_load_named_text(owner_id - 1, message);
    }
    sango_resource_read_text(0x40, 0x5b, text_part);
    bbk_strcat(message, text_part);
    sango_text_draw_centered(0x77, 0xb9, message);
    sango_input_wait(0x32, '\0');
    return;
}

/* 原函数 0x81c12188 */
void sango_strategy_show_battle_defeat(void)
{
    uint8_t *event_images;
    char *text_part;
    char *message;

    sango_display_fill_gray_rectangle(0x3b, 0x75, 0xb3, 0xc9, 0, 0);
    sango_display_draw_rectangle(0x3b, 0x75, 0xb3, 0xc9, 3, 0, 0);
    event_images = (uint8_t *)sango_resource_item(0x4c, '\x01', g_resource_package_address);
    sango_bitmap_draw_frame_screen(0x4d, 0x77, 0x54, 0x40, 3, event_images);
    message = (char *)(g_scratch_buffer_address + 300);
    text_part = (char *)(g_scratch_buffer_address + 0x154);
    sango_resource_read_text(0x40, 0x62, message);
    sango_resource_read_text(0x40, 0x5c, text_part);
    bbk_strcat(message, text_part);
    sango_text_draw_centered(0x77, 0xb9, message);
    sango_input_wait(0x32, '\0');
    return;
}

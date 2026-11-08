#include "sango_internal.h"

/* 三个存档槽、双文件读取与写入。 */

/* 原函数 0x81c16330 */
/* 存取档共用三个槽；load_mode决定确认时读取还是写入。 */
uint32_t sango_save_choose_slot(char load_mode)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define event_kind (*(int *)(abi_storage + 0))
#define key_code (*(int *)(abi_storage + 4))

    uint32_t highlight_row;
    uint32_t slot;
    int iVar3;
    int iVar4;

    sango_save_draw_slots();
    slot = 0;
    sango_display_invert_rectangle(0x18, 0x74, 0x86, 0x80, 0);
    iVar4 = 0x74;
    iVar3 = 0x80;
    do
    {
        do
        {
            sango_input_next_event(&event_kind);
        } while (event_kind != 5);
        sango_display_invert_rectangle(0x18, (short)iVar4, 0x86, (short)iVar3, 0);
        if (key_code == 0x1c)
        {
            if (load_mode == '\0')
            {
                iVar4 = sango_save_write_slot((char)slot);
            }
            else
            {
                iVar4 = sango_save_load_slot((char)slot);
            }
            if (iVar4 != 0)
            {
                return slot & 0xff;
            }
            sango_save_draw_slots();
        }
        else if (key_code < 0x1d)
        {
            if (key_code == 1)
            {
                return 0xff;
            }
        }
        else if (key_code == 0x67)
        {
            slot = slot - 1;
            if (slot == 0xffffffff)
            {
                slot = 2;
            }
        }
        else if ((key_code == 0x6c) && (slot = slot + 1, slot == 3))
        {
            slot = 0;
        }
        slot = (int)slot % 3;
        highlight_row = slot * 0x1b + 0x22 & 0xff;
        iVar3 = highlight_row + 0x5e;
        iVar4 = highlight_row + 0x52;
        sango_display_invert_rectangle(0x18, (short)iVar4, 0x86, (short)iVar3, 0);
    } while (true);
}
#undef event_kind
#undef key_code

/* 原函数 0x81c164c8 */
void sango_save_draw_slots(void)
{
    unsigned char abi_storage[128] __attribute__((aligned(8)));
#define local_90 (*(uint8_t(*)[8])(abi_storage + 0))
#define local_71 (*(char *)(abi_storage + 31))
#define local_49 (*(char *)(abi_storage + 71))
#define local_28 (*(uint16_t(*)[4])(abi_storage + 104))
#define acStack_88 (*(char(*)[10])(abi_storage + 8))
#define auStack_7e (*(uint8_t(*)[13])(abi_storage + 18))
#define acStack_60 (*(char(*)[23])(abi_storage + 48))
#define acStack_38 (*(char(*)[16])(abi_storage + 88))

    char cVar1;
    bool bVar2;
    uint8_t uVar3;
    void *file;
    void *file_00;
    uint32_t uVar4;
    uint16_t uVar5;

    sango_bitmap_draw_resource(0x2e, 1, 0, 0, '\x01');
    uVar3 = g_scenario_id_view2;
    uVar5 = 0;
    do
    {
        cVar1 = (char)uVar5 * '\x02';
        sango_resource_read_text(1, 0x40, acStack_88);
        local_71 = cVar1 + '0';
        file = bbk_fopen(acStack_88, &g_legacy_data_81c205e0);
        sango_resource_read_text(1, 0x40, acStack_60);
        local_49 = cVar1 + '1';
        file_00 = bbk_fopen(acStack_60, &g_legacy_data_81c205e0);
        bVar2 = false;
        if (file_00 == 0)
        {
            if (file != 0)
            {
                bbk_fclose(file);
            }
            sango_resource_read_text(1, 0x42, acStack_88);
            bVar2 = true;
        }
        if (file == 0)
        {
            if (file_00 != 0)
            {
                bbk_fclose(file_00);
            }
            sango_resource_read_text(1, 0x42, acStack_88);
            bVar2 = true;
        }
        if (!bVar2)
        {
            bbk_fread(&g_scenario_id_view2, 1, 1, file);
            bbk_fread(local_90, 1, 1, file);
            bbk_fread(local_28, 1, 2, file);
            bbk_fclose(file);
            bbk_fclose(file_00);
            sango_resource_read_text(1, 0x41, acStack_88);
            sango_load_named_text(local_90[0], acStack_38);
            uVar4 = bbk_strlen(acStack_38);
            local_90[0] = (uint8_t)uVar4;
            bbk_memcpy(acStack_88, acStack_38, uVar4 & 0xff);
            sango_format_integer((uint32_t)local_28[0], acStack_38, 10);
            uVar4 = bbk_strlen(acStack_38);
            bbk_memcpy(auStack_7e, acStack_38, uVar4 + 1 & 0xff);
        }
        sango_text_draw_legacy(0x28, uVar5 * 0x1b + 0x74, acStack_88);
        uVar5 = uVar5 + 1 & 0xff;
    } while (uVar5 < 3);
    g_scenario_id_view2 = uVar3;
    return;
}
#undef local_90
#undef local_71
#undef local_49
#undef local_28
#undef acStack_88
#undef auStack_7e
#undef acStack_60
#undef acStack_38

/* 原函数 0x81c16704 */
/* 一个槽位包含两份文件：会话/城市/武将数据及进行中的战略命令。 */
uint32_t sango_save_load_slot(char slot)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define acStack_38 (*(char(*)[23])(abi_storage + 0))
#define local_21 (*(char *)(abi_storage + 23))

    void *pvVar1;

    sango_resource_read_text(1, 0x44, acStack_38);
    sango_ui_show_message(acStack_38, 1);
    sango_resource_read_text(1, 0x40, acStack_38);
    local_21 = slot * '\x02' + '0';
    pvVar1 = bbk_fopen(acStack_38, &g_legacy_data_81c205e0);
    if (pvVar1 != 0)
    {
        bbk_fread(&g_scenario_id_view2, 1, 1, pvVar1);
        bbk_fread(&g_player_character, 1, 1, pvVar1);
        bbk_fread(&g_current_year, 2, 1, pvVar1);
        bbk_fread(&g_battle_render_enabled_view2, 1, 1, pvVar1);
        bbk_fread(&g_battle_show_animations_view2, 1, 1, pvVar1);
        bbk_fread(&g_battle_animate_movement_view2, 1, 1, pvVar1);
        bbk_fread(&g_current_month, 1, 1, pvVar1);
        bbk_fread(&g_strategy_viewport_x, 4, 1, pvVar1);
        bbk_fread(g_character_table_address_view2, 0x10, 200, pvVar1);
        bbk_fread(&g_city_character_roster, 1, 200, pvVar1);
        bbk_fread(&g_city_item_roster, 1, 0x21, pvVar1);
        bbk_fclose(pvVar1);
        local_21 = slot * '\x02' + '1';
        pvVar1 = bbk_fopen(acStack_38, &g_legacy_data_81c205e0);
        if (pvVar1 != 0)
        {
            bbk_fread(g_army_slot_used_address, 1, 0x1e, pvVar1);
            bbk_fread(g_army_rosters_address, 10, 0x1e, pvVar1);
            bbk_fread(g_order_queue_address, 0xc, 100, pvVar1);
            bbk_fread(&g_first_city_status, 0x24, 0x26, pvVar1);
            bbk_fclose(pvVar1);
            return 1;
        }
    }
    sango_resource_read_text(1, 0x46, acStack_38);
    sango_ui_show_message(acStack_38, 2);
    return 0;
}
#undef acStack_38
#undef local_21

/* 原函数 0x81c16940 */
/* 保留原双文件存档路径和布局；不改变武将、城市或命令记录宽度。 */
uint32_t sango_save_write_slot(char slot)
{
    unsigned char abi_storage[84] __attribute__((aligned(8)));
#define local_49 (*(char *)(abi_storage + 23))
#define local_1d (*(char *)(abi_storage + 67))
#define acStack_60 (*(char(*)[23])(abi_storage + 0))
#define auStack_38 (*(uint8_t(*)[27])(abi_storage + 40))

    int iVar1;
    void *pvVar2;
    char cVar3;

    sango_resource_read_text(1, 0x43, acStack_60);
    sango_ui_show_message(acStack_60, 0);
    sango_resource_read_text(1, 0x40, acStack_60);
    sango_resource_read_text(1, 0x47, auStack_38);
    iVar1 = bda_sango_fs_access((char *)0x81c205e4, 0);
    if (iVar1 == -1)
    {
        bda_sango_fs_mkdir((char *)0x81c205e4);
    }
    iVar1 = bda_sango_fs_access((char *)0x81c205f4, 0);
    if (iVar1 == -1)
    {
        cVar3 = slot << 1;
        bda_sango_fs_mkdir((char *)0x81c205f4);
    }
    else
    {
        cVar3 = slot * '\x02';
    }
    local_49 = cVar3 + '0';
    local_1d = local_49;
    pvVar2 = bbk_fopen(acStack_60, &g_legacy_data_81c20608);
    if (pvVar2 != 0)
    {
        bbk_fwrite(&g_scenario_id_view2, 1, 1, pvVar2);
        bbk_fwrite(&g_player_character, 1, 1, pvVar2);
        bbk_fwrite(&g_current_year, 2, 1, pvVar2);
        bbk_fwrite(&g_battle_render_enabled_view2, 1, 1, pvVar2);
        bbk_fwrite(&g_battle_show_animations_view2, 1, 1, pvVar2);
        bbk_fwrite(&g_battle_animate_movement_view2, 1, 1, pvVar2);
        bbk_fwrite(&g_current_month, 1, 1, pvVar2);
        bbk_fwrite(&g_strategy_viewport_x, 4, 1, pvVar2);
        bbk_fwrite(g_character_table_address_view2, 0x10, 200, pvVar2);
        bbk_fwrite(&g_city_character_roster, 1, 200, pvVar2);
        bbk_fwrite(&g_city_item_roster, 1, 0x21, pvVar2);
        bbk_fclose(pvVar2);
        local_49 = cVar3 + '1';
        pvVar2 = bbk_fopen(acStack_60, &g_legacy_data_81c20608);
        if (pvVar2 != 0)
        {
            bbk_fwrite(g_army_slot_used_address, 1, 0x1e, pvVar2);
            bbk_fwrite(g_army_rosters_address, 10, 0x1e, pvVar2);
            bbk_fwrite(g_order_queue_address, 0xc, 100, pvVar2);
            bbk_fwrite(&g_first_city_status, 0x24, 0x26, pvVar2);
            bbk_fclose(pvVar2);
            return 1;
        }
    }
    sango_resource_read_text(1, 0x45, acStack_60);
    sango_ui_show_message(acStack_60, 2);
    return 0;
}
#undef local_49
#undef local_1d
#undef acStack_60
#undef auStack_38

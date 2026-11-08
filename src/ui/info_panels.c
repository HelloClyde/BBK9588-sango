#include "sango_internal.h"

/* 城市事件、武将提示、宝物出现与属性消息。 */

/* 原函数 0x81c17c48 */
void sango_ui_show_city_event(uint8_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define acStack_28 (*(char(*)[16])(abi_storage + 16))
#define local_38 (*(uint16_t(*)[8])(abi_storage + 0))

    char cVar1;
    uint8_t *pbVar2;
    char *pcVar3;
    uint8_t index;
    char *source;
    char *destination;

    cVar1 = (&g_first_city_governor)[(uint32_t)param_1 * 0x24];
    if (cVar1 != '\0')
    {
        destination = (char *)(g_scratch_buffer_address + 300);
        source = (char *)(g_scratch_buffer_address + 0x154);
        sango_city_read_name(param_1, destination);
        pcVar3 = source;
        sango_resource_read_text(0x40, 0x6f, source);
        bbk_strcat(destination, source);
        sango_city_format_status((uint32_t)param_1, source, pcVar3, param_4);
        bbk_strcat(destination, source);
        sango_resource_read_text(0x40, 0x70, source);
        bbk_strcat(destination, source);
        index = cVar1 - 1;
        sango_strategy_present();
        sango_display_fill_gray_rectangle(4, 0x10b, 0xea, 0x13b, 0, 0);
        sango_display_draw_rectangle(4, 0x10b, 0xea, 0x13a, 3, 0, 0);
        local_38[0] = 8;
        local_38[1] = 0x10b;
        local_38[2] = 0xe8;
        local_38[3] = 0x138;
        local_38[4] = 10;
        local_38[5] = 0x111;
        local_38[7] = 0x13b;
        local_38[6] = 0x3e;
        pbVar2 = (uint8_t *)sango_resource_item(g_scenario_id_view2 + 0x2f, '\x01',
                                                g_resource_package_address);
        sango_bitmap_draw_frame_screen(0x15, 0x111, 0x18, 0x18, index, pbVar2);
        sango_load_named_text(index, acStack_28);
        sango_text_draw_centered(0x22, 299, acStack_28);
        sango_text_draw_wrapped_box(local_38, local_38 + 4, destination);
        sango_input_wait(100, '\x01');
    }
    return;
}
#undef acStack_28
#undef local_38

/* 原函数 0x81c17e18 */
/* 按年份向城市宝物列表加入本剧本新出现的宝物。 */
uint32_t sango_strategy_spawn_items_for_year(void)
{
    uint8_t bVar1;
    int iVar2;
    int iVar3;
    uint32_t uVar4;

    iVar2 = sango_resource_item(0x43, g_scenario_id, g_resource_package_address);
    bVar1 = 0;
    uVar4 = 0;
    while ((*(uint8_t *)(iVar2 + uVar4) != g_current_year ||
            (iVar3 = sango_city_add_item((uint32_t)((uint8_t *)(iVar2 + uVar4))[2], bVar1),
             iVar3 != 0)))
    {
        bVar1 = bVar1 + 1;
        uVar4 = uVar4 + 3 & 0xffff;
        if (199 < bVar1)
        {
            return 0;
        }
    }
    return 0;
}

/* 原函数 0x81c17eb4 */
void sango_item_remove_attributes(uint32_t param_1, uint32_t param_2)
{
    int iVar1;
    int iVar2;
    int iVar3;

    iVar1 = sango_resource_item(0x42, '\x01', g_resource_package_address);
    iVar3 = (param_2 & 0xff) * 0x10;
    iVar1 = (param_1 & 0xff) * 0x42 + iVar1;
    iVar2 = iVar3 + g_character_table_address;
    *(char *)(iVar2 + 3) = *(char *)(iVar2 + 3) - *(char *)(iVar1 + 0x3e);
    iVar3 = iVar3 + g_character_table_address;
    *(char *)(iVar3 + 4) = *(char *)(iVar3 + 4) - *(char *)(iVar1 + 0x3f);
    return;
}

/* 原函数 0x81c17f44 */
void sango_ui_show_strategy_text(uint8_t param_1)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define acStack_20 (*(char(*)[24])(abi_storage + 0))

    sango_resource_read_text(0x40, (uint32_t)param_1, acStack_20);
    sango_ui_show_message(acStack_20, 2);
    return;
}
#undef acStack_20

/* 原函数 0x81c17f78 */
void sango_ui_draw_character_panel(short param_1, short param_2, uint8_t param_3)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define acStack_20 (*(char(*)[16])(abi_storage + 0))

    uint8_t *pbVar1;

    pbVar1 = (uint8_t *)sango_resource_item(g_scenario_id_view2 + 0x2f, '\x01',
                                            g_resource_package_address);
    sango_bitmap_draw_frame_screen(param_1 + 0xd, param_2 + 2, 0x18, 0x18, param_3, pbVar1);
    sango_load_named_text(param_3, acStack_20);
    sango_text_draw_centered(param_1 + 0x1a, param_2 + 0x1c, acStack_20);
    return;
}
#undef acStack_20

/* 原函数 0x81c18024 */
void sango_ui_show_character_message(uint8_t param_1, char *param_2)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define acStack_20 (*(char(*)[16])(abi_storage + 16))
#define local_30 (*(uint16_t(*)[8])(abi_storage + 0))

    uint8_t *pbVar1;

    sango_display_fill_gray_rectangle(4, 0x10b, 0xea, 0x13b, 0, 0);
    sango_display_draw_rectangle(4, 0x10b, 0xea, 0x13a, 3, 0, 0);
    local_30[0] = 8;
    local_30[1] = 0x10b;
    local_30[2] = 0xe8;
    local_30[3] = 0x138;
    local_30[4] = 10;
    local_30[5] = 0x111;
    local_30[7] = 0x13b;
    local_30[6] = 0x3e;
    pbVar1 = (uint8_t *)sango_resource_item(g_scenario_id_view2 + 0x2f, '\x01',
                                            g_resource_package_address);
    sango_bitmap_draw_frame_screen(0x15, 0x111, 0x18, 0x18, param_1, pbVar1);
    sango_load_named_text(param_1, acStack_20);
    sango_text_draw_centered(0x22, 299, acStack_20);
    sango_text_draw_wrapped_box(local_30, local_30 + 4, param_2);
    sango_input_wait(100, '\x01');
    return;
}
#undef acStack_20
#undef local_30

/* 原函数 0x81c18150 */
void sango_character_add_item(uint8_t param_1)
{
    uint8_t bVar1;
    uint32_t uVar2;
    uint8_t *pbVar3;
    uint32_t uVar4;

    uVar4 = (uint32_t)g_legacy_data_81c2b9a4 + (uint32_t)g_legacy_data_81c2b9a5 & 0xff;
    uVar2 = 0;
    if (uVar4 != 0)
    {
        do
        {
            pbVar3 = &g_city_item_roster + uVar2;
            bVar1 = *pbVar3;
            uVar2 = uVar2 + 1 & 0xff;
            if ((bVar1 & 0x7f) == param_1)
            {
                *pbVar3 = bVar1 | 0x80;
                return;
            }
        } while (uVar2 < uVar4);
    }
    return;
}

/* 原函数 0x81c181b8 */
uint32_t sango_city_list_items(uint32_t param_1, int param_2)
{
    char *pcVar1;
    uint8_t *pbVar2;
    uint8_t bVar3;
    int iVar4;
    uint32_t uVar5;
    uint8_t *pbVar6;
    uint32_t uVar7;

    iVar4 = (param_1 & 0xff) * 0x24;
    uVar7 = 0;
    uVar5 = (uint32_t)(uint8_t)(&g_first_city_item_start)[iVar4];
    bVar3 = 0;
    if ((&g_first_city_item_count)[iVar4] != '\0')
    {
        do
        {
            pcVar1 = &g_city_item_roster + uVar5;
            bVar3 = bVar3 + 1;
            pbVar2 = &g_city_item_roster + uVar5;
            pbVar6 = (uint8_t *)(param_2 + uVar7);
            uVar5 = uVar5 + 1 & 0xff;
            if (*pcVar1 < '\0')
            {
                uVar7 = uVar7 + 1 & 0xff;
                *pbVar6 = *pbVar2 & 0x7f;
            }
        } while (bVar3 < (uint8_t)(&g_first_city_item_count)[iVar4]);
    }
    return uVar7;
}

/* 原函数 0x81c18248 */
uint32_t sango_city_find_item(uint32_t param_1, int param_2)
{
    char *pcVar1;
    uint8_t *puVar2;
    uint8_t bVar3;
    int iVar4;
    uint32_t uVar5;
    uint8_t *puVar6;
    uint32_t uVar7;

    iVar4 = (param_1 & 0xff) * 0x24;
    uVar7 = 0;
    uVar5 = (uint32_t)(uint8_t)(&g_first_city_item_start)[iVar4];
    bVar3 = 0;
    if ((&g_first_city_item_count)[iVar4] != '\0')
    {
        do
        {
            pcVar1 = &g_city_item_roster + uVar5;
            bVar3 = bVar3 + 1;
            puVar2 = &g_city_item_roster + uVar5;
            puVar6 = (uint8_t *)(param_2 + uVar7);
            uVar5 = uVar5 + 1 & 0xff;
            if (-1 < *pcVar1)
            {
                uVar7 = uVar7 + 1 & 0xff;
                *puVar6 = *puVar2;
            }
        } while (bVar3 < (uint8_t)(&g_first_city_item_count)[iVar4]);
    }
    return uVar7;
}

/* 原函数 0x81c182d0 */
uint32_t sango_city_neighbor_direction(uint32_t param_1, uint32_t param_2)
{
    int iVar1;
    uint8_t *pbVar2;
    uint32_t uVar3;
    uint8_t *pbVar4;

    iVar1 = sango_resource_item(0x3b, '\x01', g_resource_package_address);
    pbVar4 = (uint8_t *)(iVar1 + (param_1 & 0xff) * 0x10);
    uVar3 = 0;
    pbVar2 = pbVar4;
    do
    {
        if ((uint32_t)*pbVar2 == (param_2 & 0xff) + 1)
        {
            return uVar3;
        }
        uVar3 = uVar3 + 1 & 0xff;
        pbVar2 = pbVar4 + uVar3;
    } while (uVar3 < 8);
    return uVar3;
}

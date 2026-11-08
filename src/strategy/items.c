#include "sango_internal.h"

/* 宝物装备属性修改和数量统计。 */

/* 原函数 0x81c17a08 */
uint32_t sango_item_apply_attributes(uint32_t param_1, uint32_t param_2)
{
    uint8_t bVar1;
    uint8_t uVar2;
    int iVar3;
    int iVar4;
    int iVar5;

    iVar3 = sango_resource_item(0x42, '\x01', g_resource_package_address);
    iVar5 = (param_2 & 0xff) * 0x10;
    iVar4 = (param_1 & 0xff) * 0x42 + iVar3;
    *(char *)(iVar5 + g_character_table_address + 3) =
        *(char *)(iVar5 + g_character_table_address + 3) + *(char *)(iVar4 + 0x3e);
    *(char *)(iVar5 + g_character_table_address + 4) =
        *(char *)(iVar5 + g_character_table_address + 4) + *(char *)(iVar4 + 0x3f);
    bVar1 = *(uint8_t *)(iVar4 + 0x41);
    if (bVar1 == 2)
    {
        if (*(uint8_t *)(iVar5 + g_character_table_address + 4) < 0x6a)
        {
            return 0xff;
        }
        uVar2 = 5;
    }
    else
    {
        if (bVar1 < 3)
        {
            if (bVar1 == 1)
            {
                *(uint8_t *)(iVar5 + g_character_table_address + 9) = 3;
            }
            goto LAB_81c17ab0;
        }
        if (bVar1 != 3)
            goto LAB_81c17ab0;
        if (*(uint8_t *)(iVar5 + g_character_table_address + 3) < 0x6a)
        {
            return 0xff;
        }
        uVar2 = 4;
    }
    *(uint8_t *)(iVar5 + g_character_table_address + 9) = uVar2;
LAB_81c17ab0:
    return (uint32_t) * (uint8_t *)((param_1 & 0xff) * 0x42 + iVar3 + 1);
}

/* 原函数 0x81c17b3c */
uint32_t sango_faction_count_characters(uint32_t param_1)
{
    int iVar1;
    char *pcVar2;
    char *pcVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;

    uVar6 = 0;
    uVar5 = 0;
    iVar1 = 0;
    do
    {
        pcVar2 = (char *)((iVar1 + uVar5) * 4 + g_order_queue_address);
        if ((*pcVar2 != -1) &&
            ((uint32_t)(uint8_t)(&g_first_city_owner)[(uint32_t)(uint8_t)pcVar2[2] * 0x24] ==
             (param_1 & 0xff) + 1))
        {
            uVar4 = 0;
            if (*pcVar2 == '\x1b')
            {
                pcVar3 = (char *)(g_army_rosters_address + (uint32_t)(uint8_t)pcVar2[1] * 10);
                pcVar2 = pcVar3;
                do
                {
                    uVar4 = uVar4 + 1 & 0xff;
                    if (*pcVar2 != '\0')
                    {
                        uVar6 = uVar6 + 1 & 0xff;
                    }
                    pcVar2 = pcVar3 + uVar4;
                } while (uVar4 < 10);
            }
            else
            {
                uVar6 = uVar6 + 1 & 0xff;
            }
        }
        uVar5 = uVar5 + 1 & 0xff;
        iVar1 = uVar5 << 1;
    } while (uVar5 < 100);
    uVar5 = sango_faction_list_characters(param_1 & 0xff, g_scratch_buffer_address);
    return uVar6 + uVar5 & 0xff;
}

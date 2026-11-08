#include "sango_internal.h"

/* 地形成本、移动范围与可达位置。 */

/* 原函数 0x81c003b8 */
void sango_battle_build_move_range(uint32_t param_1)
{
    unsigned char abi_storage[76] __attribute__((aligned(8)));
#define abStack_50 (*(uint8_t(*)[24])(abi_storage + 24))
#define local_68 (*(uint8_t(*)[24])(abi_storage + 0))
#define local_38 (*(uint8_t *)(abi_storage + 48))
#define local_37 (*(uint8_t(*)[3])(abi_storage + 49))
#define local_34 (*(uint32_t *)(abi_storage + 52))
#define local_30 (*(int *)(abi_storage + 56))

    uint8_t bVar1;
    uint8_t *pbVar2;
    int iVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint8_t *pbVar6;
    uint8_t *pbVar7;
    uint8_t *pbVar8;
    uint32_t uVar9;

    uVar9 = param_1 & 0xff;
    sango_battle_copy_move_window(uVar9);
    local_30 = uVar9 << 3;
    sango_battle_load_movement_costs(uVar9);
    local_68[0] = (&g_first_unit_move_range)[local_30 - uVar9] * '\x10' - 0x10;
    local_34 = (uint32_t)local_68[0];
    local_38 = 1;
    local_37[0] = 0;
    uVar5 = 1;
    iVar3 = g_move_costs_address;
    pbVar6 = local_68;
    pbVar7 = local_37;
    pbVar8 = abStack_50;
    do
    {
        uVar4 = 0;
        pbVar2 = pbVar6;
        if (uVar5 != 0)
        {
            do
            {
                if (1 < *(uint8_t *)(iVar3 + (uint32_t)*pbVar2))
                {
                    sango_battle_mark_blocked_positions((uint32_t)*pbVar2, (int)pbVar8, pbVar7);
                    iVar3 = g_move_costs_address;
                }
                uVar4 = uVar4 + 1 & 0xff;
                pbVar2 = pbVar6 + uVar4;
            } while (uVar4 < uVar5);
        }
        if (pbVar6 == local_68)
        {
            pbVar7 = &local_38;
            local_38 = 0;
            pbVar6 = abStack_50;
            pbVar8 = local_68;
            bVar1 = local_37[0];
        }
        else
        {
            local_37[0] = 0;
            pbVar6 = local_68;
            pbVar7 = local_37;
            pbVar8 = abStack_50;
            bVar1 = local_38;
        }
        uVar5 = (uint32_t)bVar1;
    } while (uVar5 != 0);
    *(uint8_t *)(iVar3 + local_34) = 0;
    sango_battle_expand_reachable_tiles(uVar9);
    if ((&g_first_unit_status)[local_30 - uVar9] == '\x04')
    {
        sango_battle_relax_move_costs(uVar9);
    }
    return;
}
#undef abStack_50
#undef local_68
#undef local_38
#undef local_37
#undef local_34
#undef local_30

/* 原函数 0x81c00558 */
void sango_battle_copy_move_window(uint32_t param_1)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
#define local_30 (*(uint32_t *)(abi_storage + 0))

    int iVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint32_t uVar8;
    uint32_t uVar9;

    sango_memory_fill(g_move_costs_address_view2, 0xff, 0xe1);
    iVar1 = (param_1 & 0xff) * 7;
    uVar2 = (uint32_t)(uint8_t)(&g_first_unit_move_range)[iVar1];
    uVar3 = (uint8_t)(&g_first_unit_x)[iVar1] + 1 & 0xff;
    uVar4 = (uint8_t)(&g_first_unit_y)[iVar1] + 1 & 0xff;
    if (uVar3 < uVar2)
    {
        local_30 = uVar2 - uVar3 & 0xff;
        uVar8 = 0;
    }
    else
    {
        uVar8 = uVar3 - uVar2 & 0xff;
        local_30 = 0;
    }
    if (uVar4 < uVar2)
    {
        uVar9 = uVar2 - uVar4 & 0xff;
        uVar7 = 0;
    }
    else
    {
        uVar7 = uVar4 - uVar2 & 0xff;
        uVar9 = 0;
    }
    uVar6 = uVar2 - local_30 & 0xff;
    if ((int)uVar2 < (int)(g_battle_map_width - uVar3))
    {
        uVar6 = (uVar6 + uVar2) - 1;
    }
    else
    {
        uVar6 = uVar6 + (g_battle_map_width - uVar3);
    }
    uVar3 = uVar2 - uVar9 & 0xff;
    if ((int)uVar2 < (int)(g_battle_map_height - uVar4))
    {
        uVar3 = (uVar3 + uVar2) - 1;
    }
    else
    {
        uVar3 = uVar3 + (g_battle_map_height - uVar4);
    }
    iVar1 =
        sango_resource_item((uint32_t)g_battle_map_resource, '\x01', g_resource_package_address);
    uVar5 = 0;
    uVar4 = uVar7 * g_battle_map_width + uVar8;
    uVar2 = uVar9 * 0xf + local_30;
    if ((uVar3 & 0xff) != 0)
    {
        do
        {
            bbk_memcpy((void *)((int)g_move_costs_address_view2 + (uVar2 & 0xffff)),
                       (void *)(iVar1 + 0x10 + (uVar4 & 0xffff)), uVar6 & 0xff);
            uVar5 = uVar5 + 1 & 0xff;
            uVar4 = (uVar4 & 0xffff) + (uint32_t)g_battle_map_width;
            uVar2 = (uVar2 & 0xffff) + 0xf;
        } while (uVar5 < (uVar3 & 0xff));
    }
    g_move_source_x = (char)uVar8;
    g_move_source_y = (char)uVar7;
    g_move_window_top = (char)uVar9;
    g_move_window_left = (char)local_30;
    return;
}
#undef local_30

/* 原函数 0x81c00784 */
void sango_battle_load_movement_costs(uint32_t param_1)
{
    uint8_t bVar1;
    int iVar2;
    uint32_t uVar3;
    uint8_t *pbVar4;
    uint32_t uVar5;
    uint32_t uVar6;

    uVar6 = param_1 & 0xff;
    bVar1 = *(uint8_t *)((uint32_t)(uint8_t)(&g_battle_roster_first)[uVar6] * 0x10 +
                         g_character_table_address + -7);
    iVar2 = sango_resource_item(2, '\x03', g_resource_package_address);
    uVar5 = 0;
    do
    {
        pbVar4 = (uint8_t *)(g_move_costs_address + uVar5);
        uVar3 = (uint32_t)*pbVar4;
        uVar5 = uVar5 + 1 & 0xff;
        if (uVar3 != 0xff)
        {
            *pbVar4 = *(uint8_t *)(iVar2 + (uint32_t)bVar1 * 0x2e + uVar3);
        }
    } while (uVar5 < 0xe1);
    sango_battle_relax_move_costs(uVar6);
    *(uint8_t *)(g_move_costs_address +
                 (((uint8_t)(&g_first_unit_move_range)[uVar6 * 7] - 1) * 0x10 & 0xf0)) =
        (&g_first_unit_move_range)[uVar6 * 7];
    return;
}

/* 原函数 0x81c00870 */
void sango_battle_expand_reachable_tiles(uint32_t param_1)
{
    int iVar1;
    uint8_t bVar2;
    uint8_t bVar3;
    uint32_t uVar4;
    char cVar5;
    char cVar6;
    uint32_t uVar7;
    uint32_t uVar8;

    cVar6 = g_move_source_x_view2 - g_move_window_left_view2;
    uVar4 = 10;
    cVar5 = g_move_source_y_view2 - g_move_window_top_view2;
    if ((param_1 & 0xff) < 10)
    {
        uVar4 = 0;
    }
    uVar8 = uVar4 + 10;
    do
    {
        iVar1 = uVar4 * 7;
        if (((&g_first_unit_status)[iVar1] != '\b') && ((param_1 & 0xff) != uVar4))
        {
            bVar2 = (&g_first_unit_x)[iVar1] - cVar6;
            bVar3 = (&g_first_unit_y)[iVar1] - cVar5;
            if ((bVar2 < 0x10) &&
                ((bVar3 < 0x10 &&
                  (uVar7 = (uint32_t)(uint8_t)(bVar3 * '\x0f' + bVar2), uVar7 < 0xe1))))
            {
                *(uint8_t *)(g_move_costs_address + uVar7) = 0xfe;
            }
        }
        uVar4 = uVar4 + 1 & 0xff;
    } while (uVar4 < uVar8);
    return;
}

/* 原函数 0x81c00954 */
void sango_battle_relax_move_costs(uint32_t param_1)
{
    int iVar1;
    uint8_t bVar2;
    uint8_t bVar3;
    uint32_t uVar4;
    char cVar5;
    char cVar6;
    uint32_t uVar7;
    uint32_t uVar8;

    cVar6 = g_move_source_x_view2 - g_move_window_left_view2;
    uVar4 = 10;
    if (9 < (param_1 & 0xff))
    {
        uVar4 = 0;
    }
    cVar5 = g_move_source_y_view2 - g_move_window_top_view2;
    uVar8 = uVar4 + 10;
    do
    {
        iVar1 = uVar4 * 7;
        if ((&g_first_unit_status)[iVar1] != '\b')
        {
            bVar2 = (&g_first_unit_x)[iVar1] - cVar6;
            bVar3 = (&g_first_unit_y)[iVar1] - cVar5;
            if ((((bVar2 < 0x10) && (bVar3 < 0x10)) &&
                 (uVar7 = (uint32_t)(uint8_t)(bVar3 * '\x0f' + bVar2), uVar7 < 0xe1)) &&
                (*(uint8_t *)(g_move_costs_address + uVar7) = 0xfe,
                 (&g_first_unit_status)[(param_1 & 0xff) * 7] != '\x04'))
            {
                if ((bVar2 != 0) && (1 < uVar7))
                {
                    *(uint8_t *)(g_move_costs_address + uVar7 + -1) =
                        *(uint8_t *)(g_move_costs_address + uVar7 + -1) | 0xa0;
                }
                if ((bVar2 < 0xe) && (uVar7 < 0xe0))
                {
                    *(uint8_t *)(g_move_costs_address + uVar7 + 1) =
                        *(uint8_t *)(g_move_costs_address + uVar7 + 1) | 0xa0;
                }
                if ((bVar3 != 0) && (0xe < uVar7))
                {
                    *(uint8_t *)(g_move_costs_address + uVar7 + -0xf) =
                        *(uint8_t *)(g_move_costs_address + uVar7 + -0xf) | 0xa0;
                }
                if ((bVar3 < 0xe) && (uVar7 < 0xd1))
                {
                    *(uint8_t *)(g_move_costs_address + uVar7 + 0xf) =
                        *(uint8_t *)(g_move_costs_address + uVar7 + 0xf) | 0xa0;
                }
            }
        }
        uVar4 = uVar4 + 1 & 0xff;
    } while (uVar4 < uVar8);
    return;
}

/* 原函数 0x81c00b18 */
void sango_battle_mark_blocked_positions(uint32_t param_1, int param_2, uint8_t *param_3)
{
    uint8_t bVar1;
    uint8_t bVar2;
    char cVar3;
    uint32_t uVar4;
    uint8_t *puVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint8_t bVar8;
    uint32_t uVar9;

    uVar9 = (uint32_t)*param_3;
    bVar1 = *(uint8_t *)(g_move_costs_address + (param_1 & 0xff));
    uVar7 = 0;
    do
    {
        uVar4 = (param_1 & 0xff) + (uint32_t)(uint8_t)(&g_legacy_data_81c200a8)[uVar7];
        uVar6 = uVar4 & 0xff;
        if ((((uVar6 < 0xe1) && (bVar2 = *(uint8_t *)(g_move_costs_address + uVar6),
                                 (char)*(uint8_t *)(g_move_costs_address + uVar6) < '\0')) &&
             (bVar2 != 0xfe)) &&
            (bVar2 != 0xff))
        {
            if ((bVar2 < 0xa1) || (cVar3 = '\x01', bVar1 <= (uint8_t)(bVar2 + 0x60)))
            {
                bVar8 = bVar1 + 0x80;
                cVar3 = bVar8 - bVar2;
                if (bVar8 <= bVar2)
                {
                    cVar3 = '\0';
                }
                if (cVar3 == '\0')
                    goto LAB_81c00b64;
            }
            puVar5 = (uint8_t *)(param_2 + uVar9);
            *(char *)(g_move_costs_address + uVar6) = cVar3;
            uVar9 = uVar9 + 1 & 0xff;
            *puVar5 = (char)uVar4;
        }
    LAB_81c00b64:
        uVar7 = uVar7 + 1 & 0xff;
        if (3 < uVar7)
        {
            *param_3 = (uint8_t)uVar9;
            return;
        }
    } while (true);
}

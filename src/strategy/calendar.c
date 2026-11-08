#include "sango_internal.h"

/* 城市月度事件与年度武将更新。 */

/* 原函数 0x81c16e00 */
uint32_t sango_strategy_apply_monthly_economy(void)
{
    char cVar1;
    uint16_t uVar2;
    uint8_t *pbVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    char *pcVar7;
    int iVar8;
    uint32_t uVar9;
    uint32_t uVar10;
    uint32_t uVar11;
    uint8_t *pbVar12;
    uint32_t uVar13;
    uint32_t uVar14;

    if ((g_current_month == 6) || (g_current_month == 10))
    {
        sango_strategy_collect_agriculture_income();
    }
    if (g_current_month % 3 == 0)
    {
        sango_strategy_collect_commerce_income();
    }
    uVar10 = (uint32_t)g_legacy_data_81c2b9a2 + (uint32_t)g_legacy_data_81c2b9a3 & 0xff;
    uVar14 = 0;
    if (uVar10 != 0)
    {
        do
        {
            iVar6 = uVar14 * 0x10 + g_character_table_address;
            *(char *)(iVar6 + 8) = *(char *)(iVar6 + 8) + '\x04';
            iVar6 = uVar14 * 0x10 + g_character_table_address;
            if (100 < *(uint8_t *)(iVar6 + 8))
            {
                *(uint8_t *)(iVar6 + 8) = 100;
            }
            uVar14 = uVar14 + 1 & 0xff;
        } while (uVar14 < uVar10);
    }
    pbVar3 = g_scratch_buffer_address;
    uVar10 = 0;
    iVar6 = 0;
    do
    {
        iVar6 = iVar6 + uVar10;
        iVar4 = iVar6 * 4;
        if ((&g_first_city_owner)[iVar4] != '\0')
        {
            if ((uint32_t)g_current_month % 3 == 0)
            {
                uVar11 = bbk_rand();
                uVar14 = uVar11 + 3;
                if (-1 < (int)uVar11)
                {
                    uVar14 = uVar11;
                }
                uVar14 = uVar11 + ((int)uVar14 >> 2) * -4 + 1;
                if ((uVar14 & 0xff) < (uint32_t)(uint8_t)(&g_first_city_disaster_prevention)[iVar4])
                {
                    (&g_first_city_disaster_prevention)[iVar4] =
                        (&g_first_city_disaster_prevention)[iVar4] - (char)uVar14;
                }
            }
            if (30000 < (uint16_t)(&g_first_city_money)[iVar6 * 2])
            {
                (&g_first_city_money)[iVar6 * 2] = 30000;
            }
            iVar5 = (&g_first_city_population_limit)[iVar6];
            (&g_first_city_population_limit)[iVar6] = iVar5 + 0x32U;
            if ((uint32_t)(&g_first_city_population)[iVar6] < iVar5 + 0x32U)
            {
                (&g_first_city_population_limit)[iVar6] = (&g_first_city_population)[iVar6];
            }
            uVar13 = (uint32_t)(uint16_t)(&g_first_city_reserve_troops)[iVar6 * 2];
            uVar14 = sango_city_list_idle_characters(uVar10, (int)pbVar3);
            iVar5 = g_character_table_address;
            uVar11 = 0;
            if (uVar14 != 0)
            {
                do
                {
                    pbVar12 = pbVar3 + uVar11;
                    uVar2 = *(uint16_t *)((uint32_t)*pbVar12 * 0x10 + iVar5 + 10);
                    uVar9 = (uint32_t)uVar2;
                    switch ((&g_first_city_status)[uVar14 * 0x24])
                    {
                    case 2:
                    case 3:
                        uVar9 = uVar9 - (uVar2 >> 2) & 0xffff;
                        break;
                    case 4:
                        uVar9 = (uint32_t)(uVar2 >> 1);
                    }
                    uVar11 = uVar11 + 1 & 0xff;
                    *(short *)((uint32_t)*pbVar12 * 0x10 + iVar5 + 10) = (short)uVar9;
                    uVar13 = uVar13 + uVar9 & 0xffff;
                } while (uVar11 < uVar14);
            }
            iVar5 = g_character_table_address;
            if (uVar13 / 0x32 < (uint32_t)(uint16_t)(&g_first_city_food)[iVar6 * 2])
            {
                (&g_first_city_food)[iVar6 * 2] =
                    (&g_first_city_food)[iVar6 * 2] - (short)(uVar13 / 0x32);
            }
            else
            {
                uVar11 = 0;
                if (uVar14 != 0)
                {
                    do
                    {
                        pbVar12 = pbVar3 + uVar11;
                        uVar11 = uVar11 + 1 & 0xff;
                        iVar8 = (uint32_t)*pbVar12 * 0x10 + iVar5;
                        *(uint16_t *)(iVar8 + 10) = *(uint16_t *)(iVar8 + 10) >> 1;
                    } while (uVar11 < uVar14);
                }
                (&g_first_city_food)[iVar6 * 2] = 0;
                cVar1 = (&g_first_city_status)[iVar4];
                (&g_first_city_status)[iVar4] = '\x01';
                if ((cVar1 != '\x01') &&
                    ((uint32_t)(uint8_t)(&g_first_city_owner)[iVar4] == g_player_character + 1))
                {
                    sango_ui_show_city_event((uint8_t)uVar10, &g_first_city_food + iVar6 * 2,
                                             uVar11, uVar14);
                }
            }
            uVar14 = sango_city_list_captives(uVar10, (int)pbVar3);
            uVar11 = 0;
            pbVar12 = pbVar3;
            if (uVar14 != 0)
            {
                do
                {
                    pcVar7 = (char *)((uint32_t)*pbVar12 * 0x10 + g_character_table_address);
                    if (*pcVar7 == (&g_first_city_owner)[iVar4])
                    {
                        pcVar7[1] = (&g_first_city_owner)[iVar4];
                    }
                    uVar11 = uVar11 + 1 & 0xff;
                    pbVar12 = pbVar3 + uVar11;
                } while (uVar11 < uVar14);
            }
        }
        uVar10 = uVar10 + 1 & 0xff;
        iVar6 = uVar10 << 3;
    } while (uVar10 < 0x26);
    return 1;
}

/* 原函数 0x81c171cc */
uint32_t sango_strategy_apply_city_disasters(void)
{
    uint8_t bVar1;
    uint8_t bVar2;
    int iVar3;
    uint32_t uVar4;
    uint16_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    int iVar8;
    uint8_t *pbVar9;
    uint32_t uVar10;

    uVar10 = 0;
    iVar8 = 0;
    do
    {
        iVar3 = (iVar8 + uVar10) * 4;
        pbVar9 = &g_first_city_status + iVar3;
        bVar1 = (&g_first_city_owner)[iVar3];
        if (bVar1 != 0)
        {
            uVar4 = bbk_rand();
            uVar7 = (uint32_t)*pbVar9;
            uVar6 = (uint32_t)(uVar7 < 5);
            uVar4 = (int)uVar4 % 100 & 0xff;
            if (uVar6 != 0)
            {
                switch ((uint32_t)(&g_legacy_data_81c20624)[uVar7] & 0xfffffffe)
                {
                case 0x81c172a4:
                    iVar8 = (iVar8 + uVar10) * 4;
                    if ((uint8_t)(&g_first_city_disaster_prevention)[iVar8] < uVar4)
                    {
                        uVar4 = bbk_rand();
                        iVar3 = (int)uVar4 >> 0x1f;
                        uVar4 = (int)uVar4 % 5 & 0xff;
                        bVar2 = 3;
                        if (uVar4 == 1)
                        {
                        LAB_81c1736c:
                            *pbVar9 = bVar2;
                        LAB_81c17370:
                            if ((*pbVar9 != 0) && ((uint32_t)bVar1 == g_player_character + 1))
                            {
                                sango_ui_show_city_event((uint8_t)uVar10, iVar3, uVar6, uVar7);
                            }
                        }
                        else if (uVar4 < 2)
                        {
                            bVar2 = 2;
                            if (uVar4 == 0)
                                goto LAB_81c1736c;
                        }
                        else if (uVar4 == 2)
                        {
                            uVar4 = bbk_rand();
                            iVar3 = (int)uVar4 >> 0x1f;
                            uVar6 = (uint32_t)((uint32_t)(uint8_t)(&g_first_city_loyalty)[iVar8] <
                                               ((int)uVar4 % 100 & 0xffU));
                            bVar2 = 4;
                            if (uVar6 != 0)
                                goto LAB_81c1736c;
                            goto LAB_81c17370;
                        }
                    }
                    goto switchD_81c1729c_default;
                case 0x81c173b0:
                    uVar5 = (&g_first_city_food)[(iVar8 + uVar10) * 2];
                    break;
                case 0x81c173d4:
                    uVar5 =
                        (uint16_t)(uVar4 <
                                   (uint8_t)(&g_first_city_disaster_prevention)[(iVar8 + uVar10) *
                                                                                4]);
                    break;
                case 0x81c173f0:
                    uVar5 =
                        (uint16_t)(uVar4 < (uint8_t)(&g_first_city_loyalty)[(iVar8 + uVar10) * 4]);
                }
                if (uVar5 != 0)
                {
                    *pbVar9 = 0;
                }
            }
        }
    switchD_81c1729c_default:
        uVar10 = uVar10 + 1 & 0xff;
        iVar8 = uVar10 << 3;
        if (0x25 < uVar10)
        {
            return 1;
        }
    } while (true);
}

/* 原函数 0x81c1740c */
uint32_t sango_strategy_apply_disaster_losses(void)
{
    uint16_t uVar1;
    uint32_t uVar2;
    uint8_t *pbVar3;
    uint16_t *puVar4;
    uint32_t *puVar5;
    uint16_t *puVar6;
    uint16_t *puVar7;
    uint16_t *puVar8;
    uint32_t uVar9;

    uVar9 = 0;
    do
    {
        pbVar3 = &g_first_city_loyalty + uVar9 * 0x24;
        puVar6 = &g_first_city_commerce + uVar9 * 0x12;
        puVar7 = &g_first_city_reserve_troops + uVar9 * 0x12;
        puVar4 = &g_first_city_food + uVar9 * 0x12;
        puVar8 = &g_first_city_money + uVar9 * 0x12;
        puVar5 = &g_first_city_population_limit + uVar9 * 9;
        switch ((&g_first_city_status)[uVar9 * 0x24])
        {
        case 0:
            goto switchD_81c17494_caseD_0;
        case 1:
            *puVar6 = *puVar6 - *puVar6 / 0x14;
            *pbVar3 = *pbVar3 - *pbVar3 / 0x14;
            uVar2 = *puVar5;
            *puVar7 = *puVar7 >> 1;
            *puVar5 = uVar2 - (uVar2 >> 2);
            break;
        case 2:
            uVar1 = *puVar4;
            *puVar5 = *puVar5 - (*puVar5 >> 2);
            *puVar4 = uVar1 - uVar1 / 0x14;
            goto LAB_81c1756c;
        case 3:
            uVar1 = *puVar4;
            *puVar5 = *puVar5 - (*puVar5 >> 2);
            *puVar4 = uVar1 - uVar1 / 0x14;
            *puVar6 = *puVar6 - *puVar6 / 10;
            *puVar8 = *puVar8 - *puVar8 / 10;
        LAB_81c1756c:
            *puVar7 = *puVar7 - (*puVar7 >> 2);
            break;
        case 4:
            *puVar4 = *puVar4 - *puVar4 / 0x14;
            *puVar6 = *puVar6 - *puVar6 / 0x14;
            *puVar8 = *puVar8 - *puVar8 / 0x14;
            *pbVar3 = *pbVar3 - *pbVar3 / 10;
            *puVar7 = *puVar7 >> 1;
        }
        uVar1 = (&g_first_city_agriculture)[uVar9 * 0x12];
        (&g_first_city_agriculture)[uVar9 * 0x12] = uVar1 - uVar1 / 0x14;
    switchD_81c17494_caseD_0:
        uVar9 = uVar9 + 1 & 0xff;
        if (0x25 < uVar9)
        {
            return 1;
        }
    } while (true);
}

/* 原函数 0x81c1767c */
void sango_strategy_collect_commerce_income(void)
{
    uint16_t uVar1;
    int iVar2;
    uint32_t uVar3;

    uVar3 = 0;
    iVar2 = 0;
    do
    {
        iVar2 = iVar2 + uVar3;
        uVar1 = (&g_first_city_money)[iVar2 * 2];
        uVar3 = uVar3 + 1 & 0xff;
        if (uVar1 < 30000)
        {
            (&g_first_city_money)[iVar2 * 2] =
                uVar1 + ((uint16_t)(&g_first_city_commerce)[iVar2 * 2] >> 1);
        }
        iVar2 = uVar3 << 3;
    } while (uVar3 < 0x26);
    return;
}

/* 原函数 0x81c176d8 */
void sango_strategy_collect_agriculture_income(void)
{
    int iVar1;
    uint32_t uVar2;

    uVar2 = 0;
    iVar1 = 0;
    do
    {
        iVar1 = iVar1 + uVar2;
        uVar2 = uVar2 + 1 & 0xff;
        if ((uint16_t)(&g_first_city_food)[iVar1 * 2] < 30000)
        {
            (&g_first_city_food)[iVar1 * 2] =
                (&g_first_city_food)[iVar1 * 2] +
                ((uint16_t)(&g_first_city_agriculture)[iVar1 * 2] >> 2);
        }
        iVar1 = uVar2 << 3;
    } while (uVar2 < 0x26);
    return;
}

/* 原函数 0x81c17734 */
/* 年度武将年龄与登场更新；原数据中出生年+16为成年登场年份。 */
uint32_t sango_strategy_update_character_ages_and_debut(void)
{
    bool bVar1;
    int iVar2;
    uint32_t uVar3;
    int iVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint32_t uVar8;

    if (g_current_month_view2 == '\x01')
    {
        uVar7 = 0;
        do
        {
            iVar2 = uVar7 * 0x10 + g_character_table_address;
            uVar7 = uVar7 + 1 & 0xff;
            *(char *)(iVar2 + 0xe) = *(char *)(iVar2 + 0xe) + '\x01';
        } while (uVar7 < 200);
    }
    uVar7 = 0;
    iVar2 = sango_resource_item(0x3f, g_scenario_id, g_resource_package_address);
    uVar8 = 0;
    do
    {
        if ((uint16_t)(*(uint8_t *)(iVar2 + uVar8) + 0x10) == g_current_year_view2)
        {
            uVar5 = (uint32_t)((uint8_t *)(iVar2 + uVar8))[2];
            if (uVar5 == 0)
            {
                uVar5 = bbk_rand();
                uVar5 = (int)uVar5 % 0x26 & 0xff;
            }
            uVar6 = 0;
            uVar3 = 0;
            do
            {
                iVar4 = uVar3 * 0x24;
                uVar3 = uVar3 + 1 & 0xff;
                uVar6 = uVar6 + (uint8_t)(&g_first_city_character_count)[iVar4] & 0xff;
            } while (uVar3 < 0x26);
            uVar3 = 0;
            if (uVar6 == 0)
            {
                bVar1 = false;
            LAB_81c17974:
                if (bVar1)
                    goto LAB_81c177a0;
            }
            else
            {
                do
                {
                    if ((uint8_t)(&g_city_character_roster)[uVar3] == uVar7)
                    {
                        bVar1 = uVar3 < uVar6;
                        goto LAB_81c17974;
                    }
                    uVar3 = uVar3 + 1 & 0xff;
                } while (uVar3 < uVar6);
            }
            iVar4 = sango_city_add_character(uVar5, (uint8_t)uVar7);
            if (iVar4 == 0)
            {
                return 0;
            }
            *(uint8_t *)(uVar7 * 0x10 + g_character_table_address + 0xe) = 0x10;
        }
    LAB_81c177a0:
        uVar7 = uVar7 + 1 & 0xff;
        uVar8 = uVar8 + 3 & 0xffff;
        if (199 < uVar7)
        {
            uVar7 = 0;
            iVar2 = 0;
            do
            {
                iVar2 = (iVar2 + uVar7) * 4;
                uVar8 = (uint32_t)(uint8_t)(&g_first_city_character_start)[iVar2];
                uVar5 = uVar8 + (uint8_t)(&g_first_city_character_count)[iVar2];
                for (; uVar8 < (uVar5 & 0xff); uVar8 = uVar8 + 1 & 0xff)
                {
                    iVar2 = uVar8 * 0x10 + g_character_table_address;
                    *(char *)(iVar2 + 0xe) = *(char *)(iVar2 + 0xe) + '\x01';
                    if (((0x59 < *(uint8_t *)(uVar8 * 0x10 + g_character_table_address + 0xe)) &&
                         (uVar3 = bbk_rand(), (int)uVar3 % 100 < 0x32)) &&
                        (iVar2 = sango_city_remove_character(uVar7, (uint8_t)uVar8), iVar2 == 0))
                    {
                        return 0;
                    }
                }
                uVar7 = uVar7 + 1 & 0xff;
                iVar2 = uVar7 << 3;
                if (0x25 < uVar7)
                {
                    return 1;
                }
            } while (true);
        }
    } while (true);
}

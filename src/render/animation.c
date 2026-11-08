#include "sango_internal.h"

/* 五字节指令时间轴播放器。 */

/* 原函数 0x81c06a70 */
/* 时间轴每条5字节：x、y、存活时间、延迟、精灵索引；范围两端均包含。 */
uint32_t sango_animation_play_range(uint32_t resource_id, uint32_t first_command,
                                    uint32_t last_command, uint32_t play_flags, uint16_t origin_x,
                                    short origin_y)
{
    unsigned char abi_storage[86] __attribute__((aligned(8)));
    (*(uint16_t *)(abi_storage + 64)) = origin_x;
    (*(short *)(abi_storage + 68)) = origin_y;
#define local_30 (*(uint32_t *)(abi_storage + 0))
#define origin_x (*(uint16_t *)(abi_storage + 64))
#define origin_y (*(short *)(abi_storage + 68))

    uint8_t bVar1;
    uint8_t bVar2;
    uint8_t bVar3;
    bool needs_erase;
    bool needs_draw;
    int iVar6;
    uint8_t bVar7;
    int iVar8;
    uint32_t uVar9;
    uint32_t range_end;
    uint8_t *pbVar11;
    uint32_t uVar12;
    uint8_t *pbVar13;
    uint32_t uVar14;
    uint8_t *pbVar15;
    uint32_t uVar16;
    uint32_t uVar17;
    uint8_t *lifetimes;
    uint32_t range_begin;
    int commands_address;
    int delays_address;

    range_end = last_command & 0xff;
    range_begin = first_command & 0xff;
    iVar8 = sango_resource_item(resource_id & 0xffff, '\x01', g_resource_package_address);
    iVar6 = g_scratch_buffer_address;
    needs_erase = true;
    needs_draw = true;
    if (iVar8 == 0)
    {
        sango_debug_show_resource_id(resource_id & 0xffff);
    }
    else
    {
        commands_address = iVar8 + 6;
        bVar7 = *(uint8_t *)(iVar8 + 3);
        delays_address = g_scratch_buffer_address + 400;
        pbVar15 = (uint8_t *)(commands_address + (uint32_t) * (uint8_t *)(iVar8 + 2) * 5);
        lifetimes = (uint8_t *)(g_scratch_buffer_address + 500);
        uVar17 = 0;
        if (-1 < (int)(range_end - range_begin))
        {
            do
            {
                iVar8 = (uVar17 + range_begin) * 5 + commands_address;
                *(uint8_t *)(delays_address + uVar17) = *(uint8_t *)(iVar8 + 3);
                pbVar11 = lifetimes + uVar17;
                uVar17 = uVar17 + 1 & 0xff;
                *pbVar11 = *(uint8_t *)(iVar8 + 2);
            } while ((int)uVar17 <= (int)(range_end - range_begin));
        }
        uVar17 = 0;
        if (bVar7 != 0)
        {
            do
            {
                bVar1 = pbVar15[3];
                bVar2 = pbVar15[2];
                uVar9 = (uint32_t)pbVar15[1] * 0x100 + (uint32_t)*pbVar15;
                bVar3 = pbVar15[5];
                iVar8 = uVar17 * 4;
                uVar17 = uVar17 + 1 & 0xff;
                uVar12 = (uVar9 & 0xffff) >> 2;
                if ((uVar9 & 3) != 0)
                {
                    uVar12 = uVar12 + 1;
                }
                *(uint8_t **)(iVar8 + iVar6) = pbVar15;
                uVar12 = uVar12 * ((uint32_t)bVar1 * 0x100 + (uint32_t)bVar2 & 0xffff) & 0xffff;
                pbVar15 = pbVar15 + ((bVar3 & 1) * uVar12 + uVar12 + 6 & 0xffff);
            } while (uVar17 < bVar7);
        }
        uVar17 = 0;
        local_30 = 0;
        do
        {
            do
            {
                uVar12 = 0;
                pbVar15 = lifetimes;
                if (((play_flags & 1) != 0) && (uVar9 = sango_input_peek_key(), uVar9 != 0xff))
                {
                    return uVar9;
                }
                do
                {
                    if (*pbVar15 == 1)
                    {
                        pbVar11 = (uint8_t *)((uVar12 + range_begin) * 5 + commands_address);
                        needs_erase = true;
                        if ((play_flags & 2) != 0)
                            goto LAB_81c06c20;
                        pbVar13 = *(uint8_t **)((uint32_t)pbVar11[4] * 4 + iVar6);
                        sango_render_clear_rectangle(
                            origin_x + *pbVar11, origin_y + (uint16_t)pbVar11[1],
                            origin_x + *pbVar11 + (uint16_t)pbVar13[1] * 0x100 +
                                (uint16_t)*pbVar13 + -1,
                            origin_y + (uint16_t)pbVar11[1] + (uint16_t)pbVar13[3] * 0x100 +
                                (uint16_t)pbVar13[2] + -1,
                            g_game_context);
                        bVar7 = *pbVar15;
                    }
                    else
                    {
                    LAB_81c06c20:
                        bVar7 = *pbVar15;
                    }
                    uVar12 = uVar12 + 1 & 0xff;
                    if (bVar7 != 0)
                    {
                        *pbVar15 = bVar7 - 1;
                    }
                    pbVar15 = lifetimes + uVar12;
                } while (uVar12 <= uVar17);
                if (needs_erase)
                {
                    uVar12 = 0;
                    do
                    {
                        pbVar15 = (uint8_t *)((uVar12 + range_begin) * 5 + commands_address);
                        if (lifetimes[uVar12] != 0)
                        {
                            pbVar11 = *(uint8_t **)((uint32_t)pbVar15[4] * 4 + iVar6);
                            uVar16 = (uint32_t)origin_x + (uint32_t)*pbVar15 & 0xffff;
                            uVar9 = (uint32_t)pbVar11[1] * 0x100 + (uint32_t)*pbVar11 & 0xffff;
                            uVar14 = (uint32_t)pbVar11[3] * 0x100 + (uint32_t)pbVar11[2] & 0xffff;
                            if ((pbVar11[5] & 1) == 1)
                            {
                                sango_raster_draw_masked(uVar16, origin_y + (uint16_t)pbVar15[1],
                                                         uVar9, uVar14, (int)(pbVar11 + 6),
                                                         g_game_context);
                            }
                            else
                            {
                                sango_raster_draw_opaque(uVar16, origin_y + (uint16_t)pbVar15[1],
                                                         uVar9, uVar14, (int)(pbVar11 + 6),
                                                         g_game_context);
                            }
                        }
                        uVar12 = uVar12 + 1 & 0xff;
                    } while (uVar12 <= local_30);
                }
                uVar12 = local_30;
                if (needs_draw)
                {
                    while (uVar12 = uVar12 + 1 & 0xff, local_30 = uVar17, uVar12 <= uVar17)
                    {
                        pbVar15 = (uint8_t *)((uVar12 + range_begin) * 5 + commands_address);
                        if (lifetimes[uVar12] != 0)
                        {
                            pbVar11 = *(uint8_t **)((uint32_t)pbVar15[4] * 4 + iVar6);
                            uVar16 = (uint32_t)origin_x + (uint32_t)*pbVar15 & 0xffff;
                            uVar9 = (uint32_t)pbVar11[1] * 0x100 + (uint32_t)*pbVar11 & 0xffff;
                            uVar14 = (uint32_t)pbVar11[3] * 0x100 + (uint32_t)pbVar11[2] & 0xffff;
                            if ((pbVar11[5] & 1) == 1)
                            {
                                sango_raster_draw_masked(uVar16, origin_y + (uint16_t)pbVar15[1],
                                                         uVar9, uVar14, (int)(pbVar11 + 6),
                                                         g_game_context);
                            }
                            else
                            {
                                sango_raster_draw_opaque(uVar16, origin_y + (uint16_t)pbVar15[1],
                                                         uVar9, uVar14, (int)(pbVar11 + 6),
                                                         g_game_context);
                            }
                        }
                    }
                }
                if ((needs_draw) || (needs_erase))
                {
                    needs_draw = false;
                    needs_erase = false;
                    sango_render_present(g_game_context);
                }
                else
                {
                    uVar12 = sango_input_wait(1, '\x01');
                    if (uVar12 != 0)
                    {
                        return uVar12;
                    }
                }
                bVar7 = *(uint8_t *)(delays_address + uVar17);
                if (bVar7 != 0)
                {
                    bVar7 = bVar7 - 1;
                    *(uint8_t *)(delays_address + uVar17) = bVar7;
                }
                uVar12 = uVar17 + range_begin;
                if ((bVar7 < 2) && (uVar12 < range_end))
                {
                    needs_draw = true;
                    do
                    {
                        uVar17 = uVar17 + 1 & 0xff;
                        uVar12 = uVar17 + range_begin;
                        if (1 < *(uint8_t *)(delays_address + uVar17))
                            break;
                    } while (uVar12 < range_end);
                }
            } while (uVar12 < range_end);
            uVar12 = 0;
            pbVar15 = lifetimes;
            while (*pbVar15 < 2)
            {
                uVar12 = uVar12 + 1 & 0xff;
                pbVar15 = lifetimes + uVar12;
                if (uVar17 < uVar12)
                {
                    return 0xff;
                }
            }
        } while (uVar12 <= uVar17);
    }
    return 0xff;
}
#undef local_30
#undef origin_x
#undef origin_y

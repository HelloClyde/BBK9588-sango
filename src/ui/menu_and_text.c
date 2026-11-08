#include "sango_internal.h"

/* 选项菜单、位图控件、文本布局与数值提示。 */

/* 原函数 0x81c07068 */
uint32_t sango_ui_choose_option(uint16_t *param_1, uint32_t param_2, char *param_3)
{
    unsigned char abi_storage[68] __attribute__((aligned(8)));
#define local_60 (*(int *)(abi_storage + 0))
#define local_5c (*(int *)(abi_storage + 4))
#define local_40 (*(uint32_t *)(abi_storage + 32))
#define local_3c (*(uint32_t *)(abi_storage + 36))
#define local_38 (*(uint32_t *)(abi_storage + 40))
#define local_34 (*(uint32_t *)(abi_storage + 44))
#define local_30 (*(uint32_t *)(abi_storage + 48))

    bool bVar1;
    bool bVar2;
    short sVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    short sVar6;
    uint32_t uVar7;
    uint32_t uVar8;
    int iVar9;
    int iVar10;
    uint32_t uVar11;

    g_text_auto_clip = 0;
    g_text_bottom = param_1[3];
    g_text_top = param_1[1];
    g_text_left = *param_1;
    g_text_right = param_1[2];
    uVar11 = param_2 & 0xff;
    local_34 = (int)((uint32_t)g_text_bottom - (uint32_t)g_text_top) / 0xc & 0xff;
    local_40 = (int)((uint32_t)g_text_right - (uint32_t)g_text_left) / 6 & 0xff;
    uVar4 = bbk_strlen(param_3);
    if (local_40 == 0)
    {
        sango_legacy_trap(7);
    }
    local_3c = uVar4 / local_40 & 0xff;
    sango_display_fill_gray_rectangle(g_text_left - 3, g_text_top - 3, g_text_right + 2,
                                      g_text_bottom + 2, 0, 0);
    bVar1 = local_34 < local_3c;
    local_38 = uVar11;
    if (!bVar1)
    {
        local_38 = 0;
    }
    sango_display_draw_rectangle(g_text_left - 3, g_text_top - 3, g_text_right + 2,
                                 g_text_bottom + 2, 3, 0, 0);
    if (bVar1)
    {
        sango_display_fill_gray_rectangle(g_text_right + 2, g_text_top - 3, g_text_right + 6,
                                          g_text_bottom + 2, 0, 0);
        sango_display_draw_rectangle(g_text_right + 2, g_text_top - 3, g_text_right + 6,
                                     g_text_bottom + 2, 3, 0, 0);
        sango_display_draw_rectangle(g_text_right + 2, g_text_top - 1, g_text_right + 6,
                                     g_text_bottom, 3, 0, 0);
        if ((int)local_3c < (int)(local_38 + local_34))
        {
            local_38 = local_3c - local_34 & 0xff;
        }
    }
    local_30 = local_38 * local_40;
    bVar2 = true;
    iVar10 = uVar11 - local_38;
    sango_text_draw_legacy(g_text_left, g_text_top, param_3 + local_30);
    uVar8 = (uint32_t)(uint8_t)g_text_top + iVar10 * 0xc & 0xff;
    iVar9 = uVar8 + 0xc;
    sango_display_invert_rectangle(g_text_left, (short)uVar8, g_text_right, (short)iVar9, 0);
    uVar4 = (uint32_t)(uint8_t)g_text_top;
    do
    {
        do
        {
            if (bVar1)
            {
                sVar3 = (short)uVar4;
                sVar6 = sVar3 + 2;
                if (bVar2)
                {
                    sango_display_draw_rectangle(g_text_right + 3, sVar3, g_text_right + 5, sVar6,
                                                 0, 0, 0);
                    sango_display_put_gray_pixel(g_text_right + 4, sVar3 + 1, 0, 0);
                    sango_display_put_gray_pixel(g_text_right + 4, sVar3 + 1, 0, 0);
                    uVar4 = sango_soft_int_to_f32((int)(char)uVar11);
                    if ((char)uVar11 < 0)
                    {
                        uVar4 = soft_float_add(uVar4, g_legacy_data_81c20c4c);
                    }
                    bVar2 = false;
                    uVar5 = sango_soft_int_to_f32(local_3c - 1);
                    uVar4 = soft_float_div(uVar4, uVar5);
                    uVar7 = (uint32_t)g_text_top;
                    uVar5 = sango_soft_int_to_f32((g_text_bottom - uVar7) - 3);
                    uVar4 = soft_float_mul(uVar4, uVar5);
                    uVar5 = sango_soft_int_to_f32(uVar7);
                    uVar4 = soft_float_add(uVar4, uVar5);
                    uVar4 = sango_soft_f32_to_int(uVar4);
                    uVar4 = uVar4 & 0xff;
                    sVar6 = (short)uVar4 + 2;
                    sango_display_draw_rectangle(g_text_right + 3, (short)uVar4, g_text_right + 5,
                                                 sVar6, 3, 0, 0);
                }
                sango_display_invert_rectangle(g_text_right + 3, (short)uVar4, g_text_right + 5,
                                               sVar6, 0);
            }
            sango_input_next_event(&local_60);
        } while (local_60 != 5);
        sango_display_invert_rectangle(g_text_left, (short)uVar8, g_text_right, (short)iVar9, 0);
        if (local_5c == 0x1c)
        {
            g_text_left = 0;
            g_text_auto_clip = 1;
            g_text_bottom = 0x140;
            g_text_top = 0;
            g_text_right = 0xef;
            return uVar11;
        }
        if (local_5c < 0x1d)
        {
            if (local_5c == 1)
            {
                g_text_auto_clip = 1;
                g_text_bottom = 0x140;
                g_text_right = 0xef;
                g_text_left = 0;
                g_text_top = 0;
                return 0xff;
            }
        }
        else
        {
            if (local_5c == 0x67)
            {
                if (uVar11 == 0)
                {
                    bVar2 = true;
                    local_38 = local_3c - local_34 & 0xff;
                    local_30 = local_38 * local_40;
                    uVar11 = local_3c - 1 & 0xff;
                    iVar10 = uVar11 - local_38;
                }
                else
                {
                    uVar11 = uVar11 - 1 & 0xff;
                    bVar2 = true;
                    iVar10 = uVar11 - local_38;
                    if (local_38 <= uVar11)
                        goto LAB_81c07348;
                    local_38 = local_38 - 1 & 0xff;
                    local_30 = local_30 - local_40 & 0xffff;
                    iVar10 = uVar11 - local_38;
                }
            }
            else
            {
                if (local_5c != 0x6c)
                    goto LAB_81c07348;
                if (uVar11 == local_3c - 1)
                {
                    uVar11 = 0;
                    bVar2 = true;
                    iVar10 = 0;
                    local_38 = 0;
                    local_30 = 0;
                }
                else
                {
                    if ((int)uVar11 < (int)(local_3c - 1))
                    {
                        uVar11 = uVar11 + 1 & 0xff;
                        bVar2 = true;
                        iVar10 = uVar11 - local_38;
                    }
                    if (iVar10 < (int)local_34)
                        goto LAB_81c07348;
                    local_38 = local_38 + 1 & 0xff;
                    local_30 = local_30 + local_40 & 0xffff;
                    iVar10 = uVar11 - local_38;
                }
            }
            sango_text_draw_legacy(g_text_left, g_text_top, param_3 + local_30);
        }
    LAB_81c07348:
        uVar8 = (uint32_t)(uint8_t)g_text_top + iVar10 * 0xc & 0xff;
        iVar9 = uVar8 + 0xc;
        sango_display_invert_rectangle(g_text_left, (short)uVar8, g_text_right, (short)iVar9, 0);
    } while (true);
}
#undef local_60
#undef local_5c
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30

/* 原函数 0x81c077bc */
void sango_bitmap_draw_resource(uint32_t resource_id, uint32_t frame_number, uint32_t x, short y,
                                char draw_to_screen)
{
    unsigned char abi_storage[17] __attribute__((aligned(8)));
    (*(char *)(abi_storage + 0)) = draw_to_screen;
#define draw_to_screen (*(char *)(abi_storage + 0))

    uint8_t flags;
    uint8_t *bitmap;
    uint32_t dimension;
    uint32_t row_bytes;
    uint32_t width;
    uint32_t screen_x;

    screen_x = x & 0xffff;
    bitmap =
        (uint8_t *)sango_resource_item(resource_id & 0xffff, '\x01', g_resource_package_address);
    if ((bitmap != (uint8_t *)0x0) && ((frame_number & 0xff) <= (uint32_t)bitmap[4]))
    {
        dimension = (uint32_t)*bitmap + (uint32_t)bitmap[1] * 0x100;
        width = dimension & 0xffff;
        row_bytes = width >> 2;
        if ((dimension & 3) != 0)
        {
            row_bytes = (width >> 2) + 1;
        }
        dimension = (uint32_t)bitmap[2] + (uint32_t)bitmap[3] * 0x100 & 0xffff;
        flags = bitmap[5];
        bitmap = bitmap +
                 (((row_bytes * dimension & 0xffff) << (flags & 1)) * ((frame_number & 0xff) - 1) &
                  0xffff) +
                 6;
        if (draw_to_screen == '\0')
        {
            if ((flags & 1) == 0)
            {
                sango_raster_draw_opaque(screen_x, y, width, dimension, (int)bitmap,
                                         g_game_context);
            }
            else
            {
                sango_raster_draw_masked(screen_x, y, width, dimension, (int)bitmap,
                                         g_game_context);
            }
        }
        else if ((flags & 1) == 0)
        {
            sango_raster_draw_screen(screen_x, y, width, dimension, (int)bitmap);
        }
        else
        {
            sango_raster_draw_masked_screen(screen_x, y, width, dimension, (int)bitmap);
        }
    }
    return;
}
#undef draw_to_screen

/* 原函数 0x81c0791c */
void sango_text_draw_wrapped_box(uint16_t *param_1, uint16_t *param_2, char *param_3)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define local_20 (*(uint16_t(*)[4])(abi_storage + 16))
#define local_18 (*(uint16_t(*)[4])(abi_storage + 24))
#define local_30 (*(uint16_t(*)[4])(abi_storage + 0))
#define local_28 (*(uint16_t(*)[4])(abi_storage + 8))

    int iVar1;
    uint32_t uVar2;

    local_30[0] = *param_1;
    local_28[1] = param_2[1];
    local_28[3] = param_2[3];
    local_20[0] = param_1[2];
    local_18[3] = param_1[3];
    local_28[0] = param_1[1];
    local_20[1] = *param_2;
    local_30[2] = param_2[2];
    uVar2 = 0;
    local_30[1] = local_30[0];
    local_30[3] = local_30[0];
    local_28[2] = local_28[1];
    local_20[2] = local_20[0];
    local_20[3] = local_20[0];
    local_18[0] = local_28[1];
    local_18[1] = local_28[3];
    local_18[2] = local_28[3];
    sango_crt_strlen(param_3);
    iVar1 = 0;
    do
    {
        param_3 = sango_text_wrap_lines(
            *(uint16_t *)((int)local_30 + iVar1), *(uint16_t *)((int)local_28 + iVar1),
            *(uint16_t *)((int)local_20 + iVar1), *(uint16_t *)((int)local_18 + iVar1), param_3);
        uVar2 = uVar2 + 1 & 0xff;
        if (param_3 == (char *)0x0)
        {
            return;
        }
        iVar1 = uVar2 << 1;
    } while (uVar2 < 4);
    return;
}
#undef local_20
#undef local_18
#undef local_30
#undef local_28

/* 原函数 0x81c079fc */
char *sango_text_wrap_lines(uint16_t param_1, uint16_t param_2, uint16_t param_3, uint16_t param_4,
                            char *param_5)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(char **)(abi_storage + 0)) = param_5;
#define param_5 (*(char **)(abi_storage + 0))

    uint32_t uVar1;
    uint32_t uVar2;
    char *pcVar3;

    pcVar3 = (char *)0x0;
    uVar2 = ((int)((uint32_t)param_3 - (uint32_t)param_1) / 6) *
                ((int)((uint32_t)param_4 - (uint32_t)param_2) / 0xc) &
            0xff;
    uVar1 = sango_crt_strlen(param_5);
    if (uVar2 <= uVar1)
    {
        pcVar3 = sango_text_find_line_end((int)param_5, uVar2, '|');
        if (pcVar3 == (char *)0x0)
        {
            pcVar3 = param_5 + uVar2;
            if (uVar2 == 0)
            {
                return param_5;
            }
        }
        else
        {
            *pcVar3 = '\0';
            pcVar3 = pcVar3 + 1;
        }
    }
    g_text_left = param_1;
    g_text_bottom = param_4;
    g_text_top = param_2;
    g_text_right = param_3;
    sango_text_draw_legacy(param_1, param_2, param_5);
    return pcVar3;
}
#undef param_5

/* 原函数 0x81c07b20 */
char *sango_text_find_line_end(int param_1, uint32_t param_2, char param_3)
{
    char *pcVar1;
    uint32_t uVar2;

    uVar2 = param_2 & 0xff;
    do
    {
        if (uVar2 == 0)
        {
            return (char *)0x0;
        }
        pcVar1 = (char *)(param_1 + uVar2);
        uVar2 = uVar2 - 1 & 0xff;
    } while (*pcVar1 != param_3);
    return pcVar1;
}

/* 原函数 0x81c07b58 */
void sango_text_draw_centered(short param_1, uint16_t param_2, char *param_3)
{
    uint32_t uVar1;

    uVar1 = bbk_strlen(param_3);
    sango_text_draw_legacy(param_1 - ((short)uVar1 * 3 & 0x7fU), param_2, param_3);
    return;
}

/* 原函数 0x81c07bc0 */
void sango_battle_show_short_message(char *param_1, uint16_t param_2, uint16_t param_3)
{
    uint16_t uVar1;
    uint8_t *pbVar2;
    uint32_t uVar3;

    pbVar2 = (uint8_t *)sango_resource_item(0x1a, '\x01', g_resource_package_address);
    uVar1 = (param_3 & 0xff) * 0xc;
    uVar3 = (int)(0xef - (uint32_t)*pbVar2) >> 1 & 0xff;
    if ((param_3 & 0xff) == 0xff)
    {
        uVar1 = (uint16_t)((int)(0x13f - (uint32_t)pbVar2[2]) >> 1);
    }
    sango_raster_draw_screen(uVar3, uVar1 & 0xff, (uint32_t)*pbVar2, (uint32_t)pbVar2[2],
                             (int)(pbVar2 + 6));
    sango_text_draw_legacy((short)uVar3 + 10, (uVar1 & 0xff) + 6, param_1);
    sango_input_wait((param_2 & 0xff) * 100, '\x01');
    return;
}

/* 原函数 0x81c07cac */
uint32_t sango_math_sqrt_step_search(uint16_t value)
{
    uint32_t candidate;
    uint32_t step;
    uint32_t previous;

    step = 10;
    candidate = 0;
    while (true)
    {
        previous = candidate;
        candidate = previous + step & 0xff;
        if (step == 0)
            break;
        if ((uint32_t)value <= candidate * candidate)
        {
            step = step - 1 & 0xff;
            candidate = previous;
        }
    }
    return previous;
}

/* 原函数 0x81c07cf0 */
void sango_text_draw_padded_number(uint16_t param_1, uint16_t param_2, uint32_t param_3,
                                   uint32_t param_4, int param_5)
{
    unsigned char abi_storage[108] __attribute__((aligned(8)));
    (*(int *)(abi_storage + 88)) = param_5;
#define param_5 (*(int *)(abi_storage + 88))
#define acStack_48 (*(char(*)[16])(abi_storage + 0))
#define acStack_38 (*(char(*)[16])(abi_storage + 16))

    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    char *dst;

    dst = acStack_48;
    uVar3 = param_4 & 0xff;
    sango_memory_fill(dst, 0x30, 0xc);
    uVar2 = *(uint32_t *)(&g_legacy_data_81c201e0 + uVar3 * 4);
    if (uVar2 == 0)
    {
        sango_legacy_trap(7);
    }
    sango_format_integer(param_3 % uVar2, acStack_38, 10);
    uVar1 = sango_crt_strlen(acStack_38);
    uVar1 = uVar1 & 0xff;
    if ((uVar1 <= uVar3) && (uVar2 <= param_3))
    {
        dst = dst + (uVar3 - uVar1);
    }
    bbk_memcpy(dst, acStack_38, uVar1 + 1);
    if (param_5 == 0)
    {
        sango_text_draw_legacy(param_1, param_2, acStack_48);
    }
    else
    {
        sango_text_draw_context(param_1, param_2, acStack_48, param_5);
    }
    return;
}
#undef param_5
#undef acStack_48
#undef acStack_38

/* 原函数 0x81c07e10 */
int sango_character_troop_capacity(uint32_t character_id)
{
    int character;

    character = g_character_table_address + (character_id & 0xff) * 0x10;
    return ((uint32_t) * (uint8_t *)(character + 3) + (uint32_t) * (uint8_t *)(character + 4)) *
               10 +
           (uint32_t) * (uint8_t *)(character + 2) * 100;
}

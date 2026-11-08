#include "sango_internal.h"

/* 四灰度位图、遮罩、文字及上下文呈现。 */

/* 原函数 0x81c14350 */
void sango_raster_draw_screen(uint32_t param_1, short param_2, uint32_t param_3, uint32_t param_4,
                              int param_5)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(int *)(abi_storage + 0)) = param_5;
#define param_5 (*(int *)(abi_storage + 0))

    int iVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;

    uVar7 = param_1 & 0xffff;
    sango_display_present_context(g_message_context_view2, 0);
    uVar2 = param_3 & 0xffff;
    /* Two-bit pixels occupy four pixels per uint8_t, as in the image header's
          frame stride. Rounding to eight pixels overreads 84-pixel-wide maps. */
    if ((param_3 & 3) != 0)
    {
        uVar2 = (param_3 & 0xfffc) + 4;
    }
    iVar1 = uVar2 * (param_4 & 0xffff);
    if (iVar1 < 0)
    {
        iVar1 = iVar1 + 3;
    }
    uVar2 = iVar1 >> 2 & 0xffff;
    iVar1 = 0;
    if (uVar2 != 0)
    {
        uVar5 = uVar7;
        do
        {
            uVar6 = 6;
            do
            {
                uVar3 = (int)(uint32_t) * (uint8_t *)(param_5 + iVar1) >> (uVar6 & 0x1f) & 3;
                uVar4 = 3;
                if ((((uVar3 == 3) || (uVar4 = 2, uVar3 == 2)) || (uVar4 = 1, uVar3 == 1)) ||
                    (uVar4 = 0, uVar3 == 0))
                {
                    sango_display_put_gray_pixel((short)uVar5, param_2, uVar4,
                                                 g_message_context_view2);
                }
                uVar5 = uVar5 + 1 & 0xffff;
                uVar6 = uVar6 - 2;
                if ((int)(uVar7 + (param_3 & 0xffff) + -1) < (int)uVar5)
                {
                    param_2 = param_2 + 1;
                    uVar5 = uVar7;
                    break;
                }
            } while (-1 < (int)uVar6);
            iVar1 = iVar1 + 1;
        } while (iVar1 < (int)uVar2);
    }
    sango_display_present_context(0, g_message_context_view2);
    sango_display_noop();
    return;
}
#undef param_5

/* 原函数 0x81c14504 */
void sango_raster_draw_opaque(uint32_t param_1, short param_2, uint32_t param_3, uint32_t param_4,
                              int param_5, uint32_t param_6)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
    (*(int *)(abi_storage + 0)) = param_5;
    (*(uint32_t *)(abi_storage + 4)) = param_6;
#define param_5 (*(int *)(abi_storage + 0))
#define param_6 (*(uint32_t *)(abi_storage + 4))

    int iVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;

    uVar7 = param_1 & 0xffff;
    uVar6 = param_3 & 0xffff;
    if ((param_3 & 3) != 0)
    {
        uVar6 = (param_3 & 0xfffc) + 4;
    }
    iVar1 = uVar6 * (param_4 & 0xffff);
    if (iVar1 < 0)
    {
        iVar1 = iVar1 + 3;
    }
    uVar6 = iVar1 >> 2 & 0xffff;
    iVar1 = 0;
    if (uVar6 != 0)
    {
        uVar4 = uVar7;
        do
        {
            uVar5 = 6;
            do
            {
                uVar2 = (int)(uint32_t) * (uint8_t *)(param_5 + iVar1) >> (uVar5 & 0x1f) & 3;
                uVar3 = 3;
                if ((((uVar2 == 3) || (uVar3 = 2, uVar2 == 2)) || (uVar3 = 1, uVar2 == 1)) ||
                    (uVar3 = 0, uVar2 == 0))
                {
                    sango_display_put_gray_pixel((short)uVar4, param_2, uVar3, param_6);
                }
                uVar4 = uVar4 + 1 & 0xffff;
                uVar5 = uVar5 - 2;
                if ((int)(uVar7 + (param_3 & 0xffff) + -1) < (int)uVar4)
                {
                    param_2 = param_2 + 1;
                    uVar4 = uVar7;
                    break;
                }
            } while (-1 < (int)uVar5);
            iVar1 = iVar1 + 1;
        } while (iVar1 < (int)uVar6);
    }
    return;
}
#undef param_5
#undef param_6

/* 原函数 0x81c14690 */
void sango_raster_draw_masked(uint32_t param_1, short param_2, uint32_t param_3, uint32_t param_4,
                              int param_5, uint32_t param_6)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
    (*(int *)(abi_storage + 0)) = param_5;
    (*(uint32_t *)(abi_storage + 4)) = param_6;
#define param_5 (*(int *)(abi_storage + 0))
#define param_6 (*(uint32_t *)(abi_storage + 4))

    int iVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;

    uVar6 = param_1 & 0xffff;
    uVar5 = param_3 & 0xffff;
    if ((param_3 & 3) != 0)
    {
        uVar5 = (param_3 & 0xfffc) + 4;
    }
    iVar1 = uVar5 * (param_4 & 0xffff);
    if (iVar1 < 0)
    {
        iVar1 = iVar1 + 3;
    }
    uVar5 = iVar1 >> 2 & 0xffff;
    iVar1 = 0;
    if (uVar5 != 0)
    {
        uVar3 = uVar6;
        do
        {
            uVar4 = 6;
            do
            {
                if (((int)(uint32_t) * (uint8_t *)(param_5 + iVar1) >> (uVar4 & 0x1f) & 1U) == 0)
                {
                    uVar2 =
                        (int)(uint32_t)((uint8_t *)(param_5 + iVar1))[uVar5] >> (uVar4 & 0x1f) & 3;
                    if (uVar2 == 3)
                    {
                        uVar2 = 3;
                    }
                    else if (uVar2 == 2)
                    {
                        uVar2 = 2;
                    }
                    else if (uVar2 == 1)
                    {
                        uVar2 = 1;
                    }
                    else
                    {
                        if (uVar2 != 0)
                            goto LAB_81c14764;
                        uVar2 = 0;
                    }
                    sango_display_put_gray_pixel((short)uVar3, param_2, uVar2, param_6);
                }
            LAB_81c14764:
                uVar3 = uVar3 + 1 & 0xffff;
                uVar4 = uVar4 - 2;
                if ((int)(uVar6 + (param_3 & 0xffff) + -1) < (int)uVar3)
                {
                    param_2 = param_2 + 1;
                    uVar3 = uVar6;
                    break;
                }
            } while (-1 < (int)uVar4);
            iVar1 = iVar1 + 1;
        } while (iVar1 < (int)uVar5);
    }
    return;
}
#undef param_5
#undef param_6

/* 原函数 0x81c14838 */
void sango_raster_draw_masked_screen(uint32_t param_1, short param_2, uint32_t param_3,
                                     uint32_t param_4, int param_5)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(int *)(abi_storage + 0)) = param_5;
#define param_5 (*(int *)(abi_storage + 0))

    int iVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;

    uVar6 = param_1 & 0xffff;
    uVar5 = param_3 & 0xffff;
    if ((param_3 & 3) != 0)
    {
        uVar5 = (param_3 & 0xfffc) + 4;
    }
    iVar1 = uVar5 * (param_4 & 0xffff);
    if (iVar1 < 0)
    {
        iVar1 = iVar1 + 3;
    }
    uVar5 = iVar1 >> 2 & 0xffff;
    iVar1 = 0;
    if (uVar5 != 0)
    {
        uVar3 = uVar6;
        do
        {
            uVar4 = 6;
            do
            {
                if (((int)(uint32_t) * (uint8_t *)(param_5 + iVar1) >> (uVar4 & 0x1f) & 1U) == 0)
                {
                    uVar2 =
                        (int)(uint32_t)((uint8_t *)(param_5 + iVar1))[uVar5] >> (uVar4 & 0x1f) & 3;
                    if (uVar2 == 3)
                    {
                        uVar2 = 3;
                    }
                    else if (uVar2 == 2)
                    {
                        uVar2 = 2;
                    }
                    else if (uVar2 == 1)
                    {
                        uVar2 = 1;
                    }
                    else
                    {
                        if (uVar2 != 0)
                            goto LAB_81c14908;
                        uVar2 = 0;
                    }
                    sango_display_put_gray_pixel((short)uVar3, param_2, uVar2, 0);
                }
            LAB_81c14908:
                uVar3 = uVar3 + 1 & 0xffff;
                uVar4 = uVar4 - 2;
                if ((int)(uVar6 + (param_3 & 0xffff) + -1) < (int)uVar3)
                {
                    param_2 = param_2 + 1;
                    uVar3 = uVar6;
                    break;
                }
            } while (-1 < (int)uVar4);
            iVar1 = iVar1 + 1;
        } while (iVar1 < (int)uVar5);
    }
    return;
}
#undef param_5

/* 原函数 0x81c149dc */
void sango_text_draw_legacy(uint16_t param_1, uint16_t param_2, char *param_3)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
#define local_34 (*(int *)(abi_storage + 4))
#define local_30 (*(int *)(abi_storage + 8))

    uint32_t uVar1;
    uint16_t uVar2;
    int iVar3;
    void *ptr;
    char *pcVar4;
    uint32_t uVar5;
    int iVar6;
    uint8_t *puVar7;
    int iVar8;
    uint32_t uVar9;
    int iVar10;
    bool bVar11;
    int iVar12;
    int iVar13;

    uVar2 = g_text_bottom;
    uVar1 = (uint32_t)param_2;
    uVar5 = (uint32_t)param_1;
    if ((uint32_t)param_1 < (uint32_t)g_text_left)
    {
        uVar5 = (uint32_t)g_text_left;
    }
    if (uVar1 < g_text_top)
    {
        param_2 = g_text_top;
    }
    uVar5 = (int)(g_text_right - uVar5) / 6;
    local_30 = 0;
    local_34 = 0;
    iVar3 = sango_crt_strlen(param_3);
    if (uVar5 == 0)
    {
        sango_legacy_trap(7);
    }
    uVar9 = iVar3 + iVar3 / (int)uVar5;
    if ((int)uVar9 < (int)uVar5)
    {
        uVar5 = uVar9;
    }
    ptr = bbk_alloc(uVar9 + 0x230);
    iVar3 = uVar5 + 1;
    sango_memory_fill(ptr, 0, uVar9 + 0x230);
    if (iVar3 == 0)
    {
        sango_legacy_trap(7);
    }
    if (-1 < (int)uVar9 / iVar3)
    {
        iVar13 = 0;
        iVar12 = 0;
        do
        {
            bVar11 = false;
            iVar10 = iVar12 + uVar5;
            bbk_memcpy((void *)((int)ptr + iVar12), param_3 + local_30, uVar5);
            puVar7 = (uint8_t *)((int)ptr + iVar10);
            local_30 = local_30 + uVar5;
            if ((0x80 < (uint8_t)puVar7[-1]) &&
                (iVar8 = iVar10 + -1, iVar6 = iVar8, iVar12 <= iVar8))
            {
                do
                {
                    pcVar4 = (char *)((int)ptr + iVar6);
                    iVar6 = iVar6 + -1;
                    if (-1 < *pcVar4)
                        break;
                    bVar11 = (bool)(bVar11 ^ 1);
                } while (iVar12 <= iVar6);
                if (bVar11)
                {
                    puVar7 = (uint8_t *)((int)ptr + iVar8);
                    local_30 = local_30 + -1;
                    iVar10 = iVar8;
                }
            }
            *puVar7 = 0;
            if (((int)(uVar9 - iVar12) < (int)uVar5) ||
                ((int)((uint32_t)uVar2 - (uint32_t)param_2) <= iVar13))
                break;
            sango_display_select_font(0, 0);
            sango_text_draw_native(param_1, (short)((uVar1 + iVar13) * 0x10000 >> 0x10),
                                   (char *)((int)ptr + iVar12), 0);
            local_34 = local_34 + 1;
            iVar13 = iVar13 + 0xc;
            if (iVar3 == 0)
            {
                sango_legacy_trap(7);
            }
            iVar12 = iVar10 + 1;
        } while (local_34 <= (int)uVar9 / iVar3);
    }
    if (g_text_auto_clip_view2 != '\0')
    {
        g_text_right = 0xef;
        g_text_bottom = 0x140;
        g_text_left = 0;
        g_text_top = 0;
    }
    bbk_free_if_nonnull(ptr);
    return;
}
#undef local_34
#undef local_30

/* 原函数 0x81c14cac */
void sango_font_load_glyph(uint32_t param_1, int param_2)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define local_20 (*(uint8_t(*)[24])(abi_storage + 0))

    uint8_t bVar1;
    uint8_t bVar2;
    uint8_t bVar3;
    int offset;
    uint32_t uVar4;
    uint8_t *pbVar5;
    uint32_t uVar6;

    if ((param_1 & 0xffff) >> 8 < 0xa1)
    {
        sango_memory_fill((void *)param_2, 0, 0x18);
    }
    else
    {
        offset = sango_font_glyph_offset(param_1 & 0xffff);
        bbk_fseek(g_font_file, offset, 0);
        bbk_fread(local_20, 1, 0x12, g_font_file);
        uVar6 = 0;
        do
        {
            uVar4 = uVar6 * 3 & 0xff;
            bVar1 = local_20[uVar4 + 2];
            bVar2 = local_20[uVar4 + 1];
            bVar3 = local_20[uVar4];
            uVar4 = uVar6 & 0x3f;
            uVar6 = uVar6 + 1 & 0xff;
            pbVar5 = (uint8_t *)(param_2 + uVar4 * 4);
            pbVar5[3] = bVar1 << 4;
            *pbVar5 = bVar3;
            pbVar5[1] = bVar2 & 0xf0;
            pbVar5[2] = bVar2 * '\x10' + (char)((int)(bVar1 & 0xf0) >> 4);
        } while (uVar6 < 6);
    }
    return;
}
#undef local_20

/* 原函数 0x81c14d98 */
int sango_font_glyph_offset(uint32_t param_1)
{
    return ((((param_1 & 0xffff) >> 8) - 0xa1) * 0x5e + (param_1 & 0xff) + -0xa1) * 0x12;
}

/* 原函数 0x81c14dd8 */
void sango_ui_show_message(char *param_1, uint32_t param_2)
{
    uint32_t uVar1;

    g_text_right_view2 = 0xeb;
    g_text_left = 5;
    uVar1 = bbk_strlen(param_1);
    uVar1 = (uVar1 & 0xff) / 0x25 + 1;
    g_text_top = (uint16_t)((int)(uVar1 * -0xc + 0x13f) >> 1);
    g_text_bottom_view2 = g_text_top + (short)uVar1 * 0xc;
    if (0x19 < uVar1)
    {
        g_text_bottom_view2 = 0x13a;
        g_text_top = 5;
    }
    sango_display_fill_gray_rectangle(g_text_left - 3, g_text_top - 3, g_text_right_view2 + 3,
                                      g_text_bottom_view2 + 2, 0, 0);
    sango_display_draw_rectangle(g_text_left - 3, g_text_top - 3, g_text_right_view2 + 3,
                                 g_text_bottom_view2 + 2, 3, 0, 0);
    sango_text_draw_legacy(g_text_left, g_text_top, param_1);
    if ((param_2 & 0xff) != 0)
    {
        sango_input_wait((short)(param_2 & 0xff) * 0x28, '\x01');
    }
    return;
}

/* 原函数 0x81c14f98 */
void sango_render_present(uint32_t param_1)
{
    sango_display_present_context(0, param_1);
    return;
}

/* 原函数 0x81c14fb8 */
void sango_bitmap_draw_frame_screen(uint16_t x, short y, uint16_t width, uint16_t height,
                                    uint8_t frame, uint8_t *bitmap)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
    (*(uint8_t *)(abi_storage + 0)) = frame;
    (*(uint8_t **)(abi_storage + 4)) = bitmap;
#define frame (*(uint8_t *)(abi_storage + 0))
#define bitmap (*(uint8_t **)(abi_storage + 4))

    if ((bitmap[5] & 1) == 1)
    {
        sango_raster_draw_masked_screen(
            (uint32_t)x, y, (uint32_t)width, (uint32_t)height,
            (int)(bitmap +
                  (((int)(((uint32_t)bitmap[1] * 0x100 + (uint32_t)*bitmap & 0xffff) + 3) >> 2) *
                       ((uint32_t)bitmap[3] * 0x100 + (uint32_t)bitmap[2] & 0xffff)
                   << (bitmap[5] & 1)) *
                      (uint32_t)frame +
                  6));
    }
    else
    {
        sango_raster_draw_screen(
            (uint32_t)x, y, (uint32_t)width, (uint32_t)height,
            (int)(bitmap +
                  (((int)(((uint32_t)bitmap[1] * 0x100 + (uint32_t)*bitmap & 0xffff) + 3) >> 2) *
                       ((uint32_t)bitmap[3] * 0x100 + (uint32_t)bitmap[2] & 0xffff)
                   << (bitmap[5] & 1)) *
                      (uint32_t)frame +
                  6));
    }
    return;
}
#undef frame
#undef bitmap

/* 原函数 0x81c15070 */
void sango_bitmap_draw_frame(uint16_t x, short y, uint16_t width, uint16_t height, uint8_t frame,
                             uint8_t *bitmap, uint32_t target)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
    (*(uint8_t **)(abi_storage + 4)) = bitmap;
    (*(uint32_t *)(abi_storage + 8)) = target;
    (*(uint8_t *)(abi_storage + 0)) = frame;
#define bitmap (*(uint8_t **)(abi_storage + 4))
#define target (*(uint32_t *)(abi_storage + 8))
#define frame (*(uint8_t *)(abi_storage + 0))

    if ((bitmap[5] & 1) == 1)
    {
        sango_raster_draw_masked(
            (uint32_t)x, y, (uint32_t)width, (uint32_t)height,
            (int)(bitmap +
                  (((int)(((uint32_t)bitmap[1] * 0x100 + (uint32_t)*bitmap & 0xffff) + 3) >> 2) *
                       ((uint32_t)bitmap[3] * 0x100 + (uint32_t)bitmap[2] & 0xffff)
                   << (bitmap[5] & 1)) *
                      (uint32_t)frame +
                  6),
            target);
    }
    else
    {
        sango_raster_draw_opaque(
            (uint32_t)x, y, (uint32_t)width, (uint32_t)height,
            (int)(bitmap +
                  (((int)(((uint32_t)bitmap[1] * 0x100 + (uint32_t)*bitmap & 0xffff) + 3) >> 2) *
                       ((uint32_t)bitmap[3] * 0x100 + (uint32_t)bitmap[2] & 0xffff)
                   << (bitmap[5] & 1)) *
                      (uint32_t)frame +
                  6),
            target);
    }
    return;
}
#undef bitmap
#undef target
#undef frame

/* 原函数 0x81c15134 */
void sango_text_draw_context(short x, short y, char *text, uint32_t target)
{
    sango_display_select_font(0, target);
    sango_text_draw_native(x, y, text, target);
    return;
}

/* 原函数 0x81c151a8 */
void sango_text_reset_clip_bounds(void)
{
    if (g_text_auto_clip_view2 != '\0')
    {
        g_text_right = 0xef;
        g_text_bottom = 0x140;
        g_text_left = 0;
        g_text_top = 0;
    }
    return;
}

/* 原函数 0x81c151e4 */
void sango_text_draw_character(uint8_t param_1, uint8_t param_2, uint8_t param_3)
{
    g_legacy_data_81c2b158 = 0;
    sango_text_draw_legacy((uint16_t)param_1, (uint16_t)param_2, (char *)(uint32_t)param_3);
    return;
}

/* 原函数 0x81c15210 */
void sango_render_clear_rectangle(short left, short top, short right, short bottom, uint32_t target)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(uint32_t *)(abi_storage + 0)) = target;
#define target (*(uint32_t *)(abi_storage + 0))

    sango_display_fill_rectangle(left, top, right, bottom, 0, target);
    return;
}
#undef target

/* 原函数 0x81c152a4 */
int sango_bitmap_rectangle_byte_count(int param_1, int param_2, int param_3, int param_4)
{
    uint32_t uVar1;
    uint32_t uVar2;
    int iVar3;

    uVar2 = (param_3 - param_1) + 1;
    uVar1 = (param_3 - param_1) + 4;
    if (-1 < (int)uVar2)
    {
        uVar1 = uVar2;
    }
    iVar3 = (int)uVar1 >> 2;
    if ((uVar2 & 3) != 0)
    {
        iVar3 = iVar3 + 1;
    }
    return (param_4 - param_2) * iVar3 + iVar3;
}

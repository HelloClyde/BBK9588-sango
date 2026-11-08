#include "sango_internal.h"

/* SDK窗口消息及基础绘图适配。 */

/* 原函数 0x81c07e70 */
uint32_t sango_window_proc(uint32_t handle, int message, uint32_t wparam, uint32_t lparam)
{
    uint32_t uVar1;

    g_native_event_kind = message;
    if (message < 0x13)
    {
        if (0xf < message)
        {
            g_native_event_key = wparam & 0xffff;
            g_native_event_data = lparam;
            return 0;
        }
        if ((message == 1) || (message == 2))
        {
            g_native_event_key = wparam & 0xffff;
            g_native_event_data = lparam;
        }
    }
    else
    {
        if (message == 0x66)
        {
            bda_sango_gui_end_draw(g_draw_context);
            bda_sango_gui_frame_stop(g_app_frame);
            bda_sango_gui_frame_release(g_app_frame);
            return 0;
        }
        if ((message < 0x67) && (message == 0x60))
        {
            g_app_frame = handle;
            g_draw_context = bda_sango_gui_current_draw(handle);
        }
    }
    uVar1 = bda_sango_gui_default_proc(handle, message, wparam, lparam);
    return uVar1;
}

/* 原函数 0x81c07fd4 */
void sango_display_copy_and_refresh(short param_1, short param_2, uint32_t param_3,
                                    uint32_t param_4)
{
    int iVar1;
    int iVar2;

    iVar1 = (int)param_1;
    iVar2 = (int)param_2;
    if (((iVar1 + 0xefU & 0xffff) < 0x1df) && ((iVar2 + 0x13fU & 0xffff) < 0x27f))
    {
        if (param_3 == 0)
        {
            if (param_4 != 0)
            {
                bda_sango_gui_context_copy(0, 0, 0, 0xf0, 0x140, g_draw_context, iVar1, iVar2, 0);
                bda_sango_gui_request_redraw(g_app_frame, 0, 0);
            }
        }
        else
        {
            if (param_4 == 0)
            {
                param_4 = 0;
                param_3 = g_draw_context;
            }
            bda_sango_gui_context_copy(param_3, 0, 0, 0xf0, 0x140, param_4, iVar1, iVar2, 0);
        }
    }
    return;
}

/* 原函数 0x81c08100 */
void sango_display_fill_rectangle(short left, short top, short right, short bottom, uint32_t color,
                                  uint32_t target)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
    (*(uint32_t *)(abi_storage + 0)) = color;
    (*(uint32_t *)(abi_storage + 4)) = target;
#define color (*(uint32_t *)(abi_storage + 0))
#define target (*(uint32_t *)(abi_storage + 4))

    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    uint32_t uVar5;

    iVar4 = (unsigned short)top;
    iVar3 = (unsigned short)left;
    iVar2 = (unsigned short)(bottom - top + 1);
    iVar1 = (unsigned short)(right - left + 1);
    if (color == 1)
    {
        uVar5 = 8;
    }
    else if (color == 0)
    {
        uVar5 = 0xf;
    }
    else if (color == 2)
    {
        uVar5 = 7;
    }
    else
    {
        uVar5 = 0x10;
        if (color != 3)
            goto LAB_81c08188;
    }
    color = (uint32_t)bda_sango_gui_draw_object(uVar5);
LAB_81c08188:
    if (target == 0)
    {
        bda_sango_gui_draw_guard(1);
        bda_sango_gui_bind_image_resource(g_draw_context, color);
        bda_sango_gui_fill_region(g_draw_context, iVar3, iVar4, iVar1, iVar2);
        bda_sango_gui_request_redraw(g_app_frame, 0, 0);
        bda_sango_gui_draw_guard(0);
    }
    else
    {
        bda_sango_gui_bind_image_resource(g_draw_context, color);
        bda_sango_gui_fill_region(g_draw_context, iVar3, iVar4, iVar1, iVar2);
        bda_sango_gui_bind_image_resource(target, color);
        bda_sango_gui_fill_region(target, iVar3, iVar4, iVar1, iVar2);
    }
    return;
}
#undef color
#undef target

/* 原函数 0x81c082fc */
void sango_display_blit_palette_bitmap(short param_1, short param_2, short param_3, short param_4,
                                       short param_5, short param_6, int param_7, uint32_t param_8,
                                       uint32_t param_9, uint32_t param_10, int param_11)
{
    unsigned char abi_storage[132] __attribute__((aligned(8)));
    (*(short *)(abi_storage + 88)) = param_5;
    (*(short *)(abi_storage + 92)) = param_6;
    (*(int *)(abi_storage + 96)) = param_7;
    (*(uint32_t *)(abi_storage + 100)) = param_8;
    (*(uint32_t *)(abi_storage + 104)) = param_9;
    (*(uint32_t *)(abi_storage + 108)) = param_10;
    (*(int *)(abi_storage + 112)) = param_11;
#define param_5 (*(short *)(abi_storage + 88))
#define local_48 (*(uint32_t *)(abi_storage + 0))
#define param_6 (*(short *)(abi_storage + 92))
#define local_44 (*(int *)(abi_storage + 4))
#define param_7 (*(int *)(abi_storage + 96))
#define local_40 (*(int *)(abi_storage + 8))
#define param_8 (*(uint32_t *)(abi_storage + 100))
#define local_3c (*(uint32_t *)(abi_storage + 12))
#define param_9 (*(uint32_t *)(abi_storage + 104))
#define local_38 (*(uint8_t *)(abi_storage + 16))
#define param_10 (*(uint32_t *)(abi_storage + 108))
#define local_37 (*(uint8_t *)(abi_storage + 17))
#define param_11 (*(int *)(abi_storage + 112))
#define local_34 (*(int *)(abi_storage + 20))
#define local_30 (*(int *)(abi_storage + 24))
#define local_28 (*(uint8_t *)(abi_storage + 32))
#define local_27 (*(uint8_t *)(abi_storage + 33))
#define local_26 (*(uint8_t *)(abi_storage + 34))
#define local_25 (*(uint8_t *)(abi_storage + 35))

    uint32_t uVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    int iVar7;

    local_48 = 0;
    iVar5 = (int)param_1;
    iVar6 = (int)param_2;
    local_44 =
        (((uint32_t) * (uint8_t *)(param_7 + 7) * 0x100 + (uint32_t) * (uint8_t *)(param_7 + 6)) *
             0x100 +
         (uint32_t) * (uint8_t *)(param_7 + 5)) *
            0x100 +
        (uint32_t) * (uint8_t *)(param_7 + 4);
    local_28 = *(uint8_t *)(param_7 + 8);
    iVar7 = (int)param_3;
    iVar2 = (int)param_4;
    local_27 = *(uint8_t *)(param_7 + 9);
    local_26 = *(uint8_t *)(param_7 + 10);
    local_25 = *(uint8_t *)(param_7 + 0xb);
    local_3c = 0;
    local_40 =
        (((uint32_t)local_25 * 0x100 + (uint32_t)local_26) * 0x100 + (uint32_t)local_27) * 0x100 +
        (uint32_t)local_28;
    local_38 = *(uint8_t *)(param_7 + 0x10);
    local_34 = param_7 + 0x16;
    local_37 = 0x10;
    local_30 = -1;
    iVar3 = (int)param_5;
    iVar4 = (int)param_6;
    if (param_11 == 0)
    {
        if (param_10 != 0)
        {
            bda_sango_gui_render_region(param_10, iVar5, iVar6, iVar7, iVar2, local_44, local_40,
                                        &local_48, iVar3, iVar4);
            return;
        }
        bda_sango_gui_draw_guard(1);
        uVar1 = bda_sango_gui_object_draw_begin(g_app_frame);
        bda_sango_gui_render_region(uVar1, iVar5, iVar6, iVar7, iVar2, local_44, local_40,
                                    &local_48, iVar3, iVar4);
    }
    else
    {
        if (param_11 != 1)
        {
            return;
        }
        if (param_10 != 0)
        {
            local_30 = bda_sango_gui_rgb(param_10, 0xff, 0, 0xff);
            bda_sango_gui_render_region(param_10, iVar5, iVar6, iVar7, iVar2, local_44, local_40,
                                        &local_48, iVar3, iVar4);
            return;
        }
        bda_sango_gui_draw_guard(1);
        uVar1 = bda_sango_gui_object_draw_begin(g_app_frame);
        local_30 = bda_sango_gui_rgb(uVar1, 0xff, 0, 0xff);
        bda_sango_gui_render_region(uVar1, iVar5, iVar6, iVar7, iVar2, local_44, local_40,
                                    &local_48, iVar3, iVar4);
    }
    bda_sango_gui_object_draw_end(g_app_frame, uVar1);
    bda_sango_gui_draw_guard(0);
    return;
}
#undef param_5
#undef local_48
#undef param_6
#undef local_44
#undef param_7
#undef local_40
#undef param_8
#undef local_3c
#undef param_9
#undef local_38
#undef param_10
#undef local_37
#undef param_11
#undef local_34
#undef local_30
#undef local_28
#undef local_27
#undef local_26
#undef local_25

/* 原函数 0x81c0863c */
void sango_display_capture_bitmap(short param_1, short param_2, short param_3, short param_4,
                                  short param_5, short param_6, uint16_t *param_7, int param_8,
                                  uint32_t param_9, int param_10, int param_11)
{
    unsigned char abi_storage[44] __attribute__((aligned(8)));
    (*(short *)(abi_storage + 0)) = param_5;
    (*(short *)(abi_storage + 4)) = param_6;
    (*(uint16_t **)(abi_storage + 8)) = param_7;
    (*(int *)(abi_storage + 12)) = param_8;
    (*(uint32_t *)(abi_storage + 16)) = param_9;
    (*(int *)(abi_storage + 20)) = param_10;
    (*(int *)(abi_storage + 24)) = param_11;
#define param_5 (*(short *)(abi_storage + 0))
#define param_6 (*(short *)(abi_storage + 4))
#define param_7 (*(uint16_t **)(abi_storage + 8))
#define param_8 (*(int *)(abi_storage + 12))
#define param_9 (*(uint32_t *)(abi_storage + 16))
#define param_10 (*(int *)(abi_storage + 20))
#define param_11 (*(int *)(abi_storage + 24))

    uint16_t uVar1;
    uint16_t uVar2;
    void *pvVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    uint32_t uVar7;
    uint32_t uVar8;
    uint32_t unaff_s5;
    void *pvVar9;

    uVar7 = (uint32_t)param_3;
    uVar8 = (uint32_t)param_4;
    iVar5 = (int)param_5;
    iVar6 = (int)param_6;
    if (param_11 == 1)
    {
        unaff_s5 = 1;
    }
    else if (param_11 == 2)
    {
        unaff_s5 = 2;
    }
    if (1 < (unaff_s5 - 1 & 0xff))
    {
        return;
    }
    if (param_7 == (uint16_t *)0x0)
    {
        return;
    }
    uVar1 = param_7[1];
    uVar2 = *param_7;
    pvVar9 = (void *)(param_8 + 0xc);
    if ((((iVar5 != 0) || (iVar6 != 0)) || (uVar2 != uVar7)) || (uVar1 != uVar8))
    {
        iVar4 = uVar7 + 3;
        if ((int)(uVar7 + 3) < 0)
        {
            iVar4 = uVar7 + 6;
        }
        pvVar3 = bda_sango_mem_alloc((iVar4 >> 2) * uVar8 + 0x20);
        if (pvVar3 == 0)
        {
            return;
        }
        iVar5 = bda_sango_gui_bitmap_crop((uint32_t)uVar2, (uint32_t)uVar1, iVar5, iVar6,
                                          iVar5 + uVar7 + -1, iVar6 + uVar8 + -1, pvVar9, pvVar3);
        pvVar9 = pvVar3;
        if (iVar5 == 0)
            goto LAB_81c08778;
    }
    if (param_10 == 0)
    {
        bda_sango_gui_bitmap_context(g_draw_context, (int)param_1, (int)param_2, uVar7, uVar8,
                                     pvVar9, unaff_s5);
        bda_sango_gui_bitmap_buffer((int)param_1, (int)param_2, uVar7, uVar8, pvVar9,
                                    g_frame_buffer, unaff_s5);
        bda_sango_gui_request_redraw(g_app_frame, 0, 0);
    }
LAB_81c08778:
    if (pvVar9 != 0)
    {
        bda_sango_mem_free(pvVar9);
    }
    return;
}
#undef param_5
#undef param_6
#undef param_7
#undef param_8
#undef param_9
#undef param_10
#undef param_11

/* 原函数 0x81c0886c */
void sango_display_put_gray_pixel(short param_1, short param_2, uint32_t param_3, uint32_t param_4)
{
    uint32_t uVar1;
    int iVar2;
    int iVar3;
    void *unaff_s3;

    iVar2 = (int)param_1;
    iVar3 = (int)param_2;
    if (iVar2 < 0)
    {
        return;
    }
    if (iVar3 < 0)
    {
        return;
    }
    if (0xef < iVar2)
    {
        return;
    }
    if (0x13f < iVar3)
    {
        return;
    }
    if (3 < param_3)
    {
        return;
    }
    if (param_3 == 1)
    {
        uVar1 = 8;
    }
    else if (param_3 == 0)
    {
        uVar1 = 0xf;
    }
    else if (param_3 == 2)
    {
        uVar1 = 7;
    }
    else
    {
        uVar1 = 0x10;
        if (param_3 != 3)
            goto LAB_81c088dc;
    }
    unaff_s3 = bda_sango_gui_draw_object(uVar1);
LAB_81c088dc:
    if (param_4 == 0)
    {
        bda_sango_gui_draw_guard(1);
        bda_sango_gui_put_pixel(g_draw_context, iVar2, iVar3, (uint32_t)unaff_s3);
        bda_sango_gui_request_redraw(g_app_frame, 0, 0);
        bda_sango_gui_draw_guard(0);
    }
    else
    {
        bda_sango_gui_put_pixel(param_4, iVar2, iVar3, (uint32_t)unaff_s3);
    }
    return;
}

/* 原函数 0x81c089c4 */
void sango_display_draw_line(short param_1, short param_2, short param_3, short param_4,
                             uint32_t param_5, uint32_t param_6, uint32_t param_7)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
    (*(uint32_t *)(abi_storage + 0)) = param_5;
    (*(uint32_t *)(abi_storage + 4)) = param_6;
    (*(uint32_t *)(abi_storage + 8)) = param_7;
#define param_5 (*(uint32_t *)(abi_storage + 0))
#define param_6 (*(uint32_t *)(abi_storage + 4))
#define param_7 (*(uint32_t *)(abi_storage + 8))

    short sVar1;
    short sVar2;
    int iVar3;
    int iVar4;
    void *pvVar5;
    int iVar6;
    uint32_t uVar7;
    void *unaff_s0;
    int iVar8;
    int iVar9;
    int iVar10;
    int iVar11;
    int iVar12;
    int iVar13;
    int iVar14;
    int iVar15;

    iVar8 = (int)param_1;
    iVar10 = (int)param_2;
    iVar12 = (int)param_3;
    iVar13 = (int)param_4;
    if ((iVar8 < 0) && (iVar12 < 0))
    {
        return;
    }
    if ((iVar10 < 0) && (iVar13 < 0))
    {
        return;
    }
    if ((0xef < iVar8) && (0xef < iVar12))
    {
        return;
    }
    if ((0x13f < iVar10) && (0x13f < iVar13))
    {
        return;
    }
    iVar9 = iVar8;
    if (iVar8 < 0)
    {
        iVar9 = 0;
    }
    if (iVar12 < 0)
    {
        iVar12 = 0;
    }
    iVar11 = iVar10;
    if (iVar10 < 0)
    {
        iVar11 = 0;
    }
    if (iVar13 < 0)
    {
        iVar13 = 0;
    }
    if (0xef < iVar12)
    {
        iVar12 = 0xef;
    }
    if (0x13f < iVar13)
    {
        iVar13 = 0x13f;
    }
    if (0xef < iVar8)
    {
        iVar9 = 0xef;
    }
    if (0x13f < iVar10)
    {
        iVar11 = 0x13f;
    }
    if (3 < param_5)
    {
        return;
    }
    if (param_5 == 1)
    {
        uVar7 = 8;
    }
    else if (param_5 == 0)
    {
        uVar7 = 0xf;
    }
    else if (param_5 == 2)
    {
        uVar7 = 7;
    }
    else
    {
        uVar7 = 0x10;
        if (param_5 != 3)
            goto LAB_81c08ab8;
    }
    unaff_s0 = bda_sango_gui_draw_object(uVar7);
LAB_81c08ab8:
    if (param_7 == 0)
    {
        pvVar5 = bda_sango_gui_select_draw_object(g_draw_context, unaff_s0);
        bda_sango_gui_draw_guard(1);
        bda_sango_gui_move_to(g_draw_context, iVar9, iVar11);
        bda_sango_gui_line_to(g_draw_context, iVar12, iVar13);
        bda_sango_gui_request_redraw(g_app_frame, 0, 0);
        bda_sango_gui_select_draw_object(g_draw_context, pvVar5);
        bda_sango_gui_draw_guard(0);
    }
    else if ((iVar9 == iVar12) || (iVar11 == iVar13))
    {
        iVar8 = iVar9;
        if (iVar12 < iVar9)
        {
            iVar8 = iVar12;
            iVar12 = iVar9;
        }
        iVar10 = iVar11;
        if (iVar13 < iVar11)
        {
            iVar10 = iVar13;
            iVar13 = iVar11;
        }
        sango_display_fill_rectangle((short)iVar8, (short)iVar10, (short)iVar12, (short)iVar13,
                                     param_5, param_7);
    }
    else
    {
        iVar8 = (iVar12 - iVar9) * 0x10000;
        iVar10 = (iVar13 - iVar11) * 0x10000;
        iVar15 = iVar8 >> 0x10;
        iVar14 = iVar10 >> 0x10;
        iVar6 = 1;
        if (iVar15 * iVar14 < 0)
        {
            iVar6 = -1;
        }
        iVar3 = sango_crt_abs(iVar15);
        iVar4 = sango_crt_abs(iVar14);
        sVar1 = (short)((uint32_t)iVar8 >> 0x10);
        sVar2 = (short)((uint32_t)iVar10 >> 0x10);
        if (iVar4 < iVar3)
        {
            iVar8 = iVar9;
            if (iVar15 < 0)
            {
                iVar15 = (int)-sVar1;
                iVar14 = (int)-sVar2;
                iVar8 = iVar12;
                iVar11 = iVar13;
                iVar12 = iVar9;
            }
            iVar13 = iVar14 * 2 - iVar15;
            sango_display_put_gray_pixel((short)iVar8, (short)iVar11, param_5, param_7);
            while (iVar8 < iVar12)
            {
                iVar13 = iVar13 * 0x10000 >> 0x10;
                iVar9 = (iVar8 + 1) * 0x10000;
                iVar8 = iVar9 >> 0x10;
                iVar10 = iVar14 << 0x11;
                if (-1 < iVar13)
                {
                    iVar11 = (iVar11 + iVar6) * 0x10000 >> 0x10;
                    iVar10 = (iVar14 - iVar15) * 0x20000;
                }
                iVar13 = iVar13 + (iVar10 >> 0x10);
                sango_display_put_gray_pixel((short)((uint32_t)iVar9 >> 0x10), (short)iVar11,
                                             param_5, param_7);
            }
        }
        else
        {
            iVar8 = iVar11;
            if (iVar14 < 0)
            {
                iVar15 = (int)-sVar1;
                iVar14 = (int)-sVar2;
                iVar9 = iVar12;
                iVar8 = iVar13;
                iVar13 = iVar11;
            }
            iVar12 = iVar15 * 2 - iVar14;
            sango_display_put_gray_pixel((short)iVar9, (short)iVar8, param_5, param_7);
            while (iVar8 < iVar13)
            {
                iVar12 = iVar12 * 0x10000 >> 0x10;
                iVar11 = (iVar8 + 1) * 0x10000;
                iVar8 = iVar11 >> 0x10;
                iVar10 = iVar15 << 0x11;
                if (-1 < iVar12)
                {
                    iVar9 = (iVar9 + iVar6) * 0x10000 >> 0x10;
                    iVar10 = (iVar15 - iVar14) * 0x20000;
                }
                iVar12 = iVar12 + (iVar10 >> 0x10);
                sango_display_put_gray_pixel((short)iVar9, (short)((uint32_t)iVar11 >> 0x10),
                                             param_5, param_7);
            }
        }
    }
    return;
}
#undef param_5
#undef param_6
#undef param_7

/* 原函数 0x81c08e7c */
void sango_display_draw_rectangle(short param_1, short param_2, short param_3, short param_4,
                                  uint32_t param_5, uint32_t param_6, int param_7)
{
    unsigned char abi_storage[28] __attribute__((aligned(8)));
    (*(uint32_t *)(abi_storage + 0)) = param_5;
    (*(uint32_t *)(abi_storage + 4)) = param_6;
    (*(int *)(abi_storage + 8)) = param_7;
#define param_5 (*(uint32_t *)(abi_storage + 0))
#define param_6 (*(uint32_t *)(abi_storage + 4))
#define param_7 (*(int *)(abi_storage + 8))

    void *pvVar1;
    short sVar2;
    uint32_t uVar3;
    short sVar4;
    short sVar5;
    short sVar6;
    int iVar7;
    int iVar8;
    int iVar9;
    int iVar10;
    int iVar11;
    void *unaff_s7;

    iVar11 = (int)param_1;
    iVar10 = (int)param_2;
    iVar7 = (int)param_3;
    iVar9 = (int)param_4;
    if (3 < param_5)
    {
        return;
    }
    iVar8 = iVar7;
    if (iVar7 < iVar11)
    {
        iVar8 = iVar11;
        iVar11 = iVar7;
    }
    iVar7 = iVar9;
    if (iVar9 < iVar10)
    {
        iVar7 = iVar10;
        iVar10 = iVar9;
    }
    uVar3 = 8;
    if (param_5 != 1)
    {
        if (param_5 == 0)
        {
            uVar3 = 0xf;
        }
        else if (param_5 == 2)
        {
            uVar3 = 7;
        }
        else
        {
            uVar3 = 0x10;
            if (param_5 != 3)
                goto LAB_81c08f2c;
        }
    }
    unaff_s7 = bda_sango_gui_draw_object(uVar3);
LAB_81c08f2c:
    if (param_7 == 0)
    {
        pvVar1 = bda_sango_gui_select_draw_object(g_draw_context, unaff_s7);
        bda_sango_gui_draw_guard(1);
        bda_sango_gui_rectangle(g_draw_context, iVar11, iVar10, iVar8 + 1, iVar7 + 1);
        bda_sango_gui_draw_guard(0);
        bda_sango_gui_request_redraw(g_app_frame, 0, 0);
        bda_sango_gui_select_draw_object(g_draw_context, pvVar1);
    }
    sVar2 = (short)iVar11;
    sVar4 = (short)iVar10;
    sVar5 = (short)iVar8;
    sango_display_draw_line(sVar2, sVar4, sVar5, sVar4, param_5, param_6, param_7);
    sVar6 = (short)iVar7;
    sango_display_draw_line(sVar5, sVar4, sVar5, sVar6, param_5, param_6, param_7);
    sango_display_draw_line(sVar2, sVar6, sVar5, sVar6, param_5, param_6, param_7);
    sango_display_draw_line(sVar2, sVar4, sVar2, sVar6, param_5, param_6, param_7);
    return;
}
#undef param_5
#undef param_6
#undef param_7

/* 原函数 0x81c090c4 */
void sango_display_draw_circle(short param_1, short param_2, int param_3, uint32_t param_4,
                               uint32_t param_5, int param_6)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
    (*(uint32_t *)(abi_storage + 0)) = param_5;
    (*(int *)(abi_storage + 4)) = param_6;
#define param_5 (*(uint32_t *)(abi_storage + 0))
#define param_6 (*(int *)(abi_storage + 4))

    int iVar1;
    void *pvVar2;
    int iVar3;
    short sVar4;
    short sVar5;
    int iVar6;
    uint32_t uVar7;
    short sVar8;
    void *unaff_s1;
    int iVar9;
    int iVar10;
    int iVar11;
    int iVar12;

    iVar6 = (int)param_1;
    iVar12 = (int)param_2;
    if (param_3 == 0)
    {
        return;
    }
    if (3 < param_4)
    {
        return;
    }
    if (param_4 == 1)
    {
        uVar7 = 8;
    }
    else if (param_4 == 0)
    {
        uVar7 = 0xf;
    }
    else if (param_4 == 2)
    {
        uVar7 = 7;
    }
    else
    {
        uVar7 = 0x10;
        if (param_4 != 3)
            goto LAB_81c09140;
    }
    unaff_s1 = bda_sango_gui_draw_object(uVar7);
LAB_81c09140:
    if (param_6 == 0)
    {
        pvVar2 = bda_sango_gui_select_draw_object(g_draw_context, unaff_s1);
        bda_sango_gui_circle(g_draw_context, iVar6, iVar12, param_3);
        bda_sango_gui_request_redraw(g_app_frame, 0, 0);
        bda_sango_gui_select_draw_object(g_draw_context, pvVar2);
    }
    iVar3 = param_3 * -2 + 3;
    iVar9 = (int)(short)param_3;
    iVar10 = 0;
    if (-1 < iVar9)
    {
        do
        {
            iVar11 = iVar3 * 0x10000 >> 0x10;
            sVar4 = (short)((uint32_t)((iVar6 + iVar10) * 0x10000) >> 0x10);
            sVar8 = (short)((uint32_t)((iVar12 + iVar9) * 0x10000) >> 0x10);
            sango_display_put_gray_pixel(sVar4, sVar8, param_4, param_6);
            sVar5 = (short)((uint32_t)((iVar6 - iVar10) * 0x10000) >> 0x10);
            sango_display_put_gray_pixel(sVar5, sVar8, param_4, param_6);
            sVar8 = (short)((uint32_t)((iVar12 - iVar9) * 0x10000) >> 0x10);
            sango_display_put_gray_pixel(sVar4, sVar8, param_4, param_6);
            sango_display_put_gray_pixel(sVar5, sVar8, param_4, param_6);
            sVar4 = (short)((uint32_t)((iVar6 + iVar9) * 0x10000) >> 0x10);
            sVar8 = (short)((uint32_t)((iVar12 + iVar10) * 0x10000) >> 0x10);
            sango_display_put_gray_pixel(sVar4, sVar8, param_4, param_6);
            sVar5 = (short)((uint32_t)((iVar6 - iVar9) * 0x10000) >> 0x10);
            sango_display_put_gray_pixel(sVar5, sVar8, param_4, param_6);
            sVar8 = (short)((uint32_t)((iVar12 - iVar10) * 0x10000) >> 0x10);
            sango_display_put_gray_pixel(sVar4, sVar8, param_4, param_6);
            sango_display_put_gray_pixel(sVar5, sVar8, param_4, param_6);
            iVar1 = iVar10 - iVar9;
            iVar3 = iVar11 + iVar10 * 4 + 6;
            if (-1 < iVar11)
            {
                iVar9 = (iVar9 + -1) * 0x10000 >> 0x10;
                iVar3 = iVar11 + iVar1 * 4 + 10;
            }
            iVar10 = (iVar10 + 1) * 0x10000 >> 0x10;
        } while (iVar10 <= iVar9);
    }
    return;
}
#undef param_5
#undef param_6

/* 原函数 0x81c093c0 */
void sango_display_draw_polyline(short param_1, short param_2, int param_3, uint32_t param_4,
                                 int param_5)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(int *)(abi_storage + 0)) = param_5;
#define param_5 (*(int *)(abi_storage + 0))

    int iVar1;
    int iVar2;
    short sVar3;
    short sVar4;
    short sVar5;
    short sVar6;
    short sVar7;
    int iVar8;
    int iVar9;
    int iVar10;
    int iVar11;
    int iVar12;

    iVar11 = (int)param_1;
    iVar10 = (int)param_2;
    if (((param_3 != 0) && (param_4 < 4)) && (param_5 != 0))
    {
        iVar2 = param_3 * -2 + 3;
        iVar8 = (int)(short)param_3;
        iVar9 = 0;
        if (-1 < iVar8)
        {
            do
            {
                iVar12 = iVar2 * 0x10000 >> 0x10;
                sVar3 = (short)((uint32_t)((iVar11 + iVar9) * 0x10000) >> 0x10);
                sVar4 = (short)((uint32_t)((iVar10 + iVar8) * 0x10000) >> 0x10);
                sVar6 = (short)((uint32_t)((iVar11 - iVar9) * 0x10000) >> 0x10);
                sango_display_draw_line(sVar3, sVar4, sVar6, sVar4, param_4, 0, param_5);
                sVar4 = (short)((uint32_t)((iVar11 + iVar8) * 0x10000) >> 0x10);
                sVar5 = (short)((uint32_t)((iVar10 + iVar9) * 0x10000) >> 0x10);
                sVar7 = (short)((uint32_t)((iVar11 - iVar8) * 0x10000) >> 0x10);
                sango_display_draw_line(sVar4, sVar5, sVar7, sVar5, param_4, 0, param_5);
                sVar5 = (short)((uint32_t)((iVar10 - iVar9) * 0x10000) >> 0x10);
                sango_display_draw_line(sVar4, sVar5, sVar7, sVar5, param_4, 0, param_5);
                sVar4 = (short)((uint32_t)((iVar10 - iVar8) * 0x10000) >> 0x10);
                sango_display_draw_line(sVar3, sVar4, sVar6, sVar4, param_4, 0, param_5);
                iVar1 = iVar9 - iVar8;
                iVar2 = iVar12 + iVar9 * 4 + 6;
                if (-1 < iVar12)
                {
                    iVar8 = (iVar8 + -1) * 0x10000 >> 0x10;
                    iVar2 = iVar12 + iVar1 * 4 + 10;
                }
                iVar9 = (iVar9 + 1) * 0x10000 >> 0x10;
            } while (iVar9 <= iVar8);
        }
    }
    return;
}
#undef param_5

/* 原函数 0x81c095b4 */
void sango_display_set_brush(int param_1, uint32_t param_2)
{
    void *pvVar1;
    uint32_t uVar2;

    if (param_1 == 1)
    {
        uVar2 = 8;
    }
    else if (param_1 == 0)
    {
        uVar2 = 0xf;
    }
    else if (param_1 == 2)
    {
        uVar2 = 7;
    }
    else
    {
        if (param_1 != 3)
        {
            return;
        }
        uVar2 = 0x10;
    }
    pvVar1 = bda_sango_gui_draw_object(uVar2);
    if (param_2 == 0)
    {
        bda_sango_gui_set_fill_object(g_draw_context, (uint32_t)pvVar1);
        g_legacy_data_81c2b204 = pvVar1;
    }
    else
    {
        bda_sango_gui_set_fill_object(param_2, (uint32_t)pvVar1);
    }
    return;
}

/* 原函数 0x81c09680 */
void sango_display_set_text_color(int param_1, uint32_t param_2)
{
    void *pvVar1;
    uint32_t uVar2;

    if (param_1 == 1)
    {
        uVar2 = 8;
    }
    else if (param_1 == 0)
    {
        uVar2 = 0xf;
    }
    else if (param_1 == 2)
    {
        uVar2 = 7;
    }
    else
    {
        if (param_1 != 3)
        {
            return;
        }
        uVar2 = 0x10;
    }
    pvVar1 = bda_sango_gui_draw_object(uVar2);
    if (param_2 == 0)
    {
        bda_sango_gui_set_text_color(g_draw_context, (uint32_t)pvVar1);
        g_legacy_data_81c2b208 = pvVar1;
    }
    else
    {
        bda_sango_gui_set_text_color(param_2, (uint32_t)pvVar1);
    }
    return;
}

/* 原函数 0x81c0974c */
uint32_t sango_display_select_font(uint8_t param_1, uint32_t param_2)
{
    uint32_t uVar1;
    uint8_t uVar2;

    uVar1 = 0;
    switch (param_1)
    {
    case 0:
    case 1:
    case 2:
        uVar2 = 0;
        break;
    case 3:
    case 4:
    case 5:
        uVar2 = 4;
        break;
    case 6:
    case 7:
    case 8:
        uVar2 = 8;
        break;
    default:
        goto switchD_81c09778_default;
    }
    if (param_2 == 0)
    {
        bda_sango_gui_select_font(g_draw_context, (uint32_t)uVar2);
        uVar1 = 1;
        g_legacy_data_81c2b210 = uVar2;
    }
    else
    {
        bda_sango_gui_select_font(param_2, (uint32_t)uVar2);
        uVar1 = 1;
    }
switchD_81c09778_default:
    return uVar1;
}

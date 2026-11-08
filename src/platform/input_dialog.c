#include "sango_internal.h"

/* 按键数据与文本输入对话框。 */

/* 原函数 0x81c097f4 */
uint16_t *sango_bitmap_open_embedded_entry(uint32_t *param_1, uint32_t param_2, int param_3,
                                           int param_4)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define local_18 (*(int(*)[2])(abi_storage + 0))

    uint16_t uVar1;
    uint16_t uVar2;
    uint16_t *puVar3;

    if (2 < param_2)
    {
        return (uint16_t *)0x0;
    }
    crt_memcpy(local_18, (void *)(param_4 + param_3 * 4), 4);
    puVar3 = (uint16_t *)(param_4 + local_18[0]);
    if (param_2 == 1)
    {
        *param_1 = puVar3;
    }
    else
    {
        if (param_2 != 0)
        {
            if (param_2 == 2)
            {
                uVar1 = *puVar3;
                uVar2 = puVar3[1];
                param_1[1] = puVar3;
                *param_1 = (uint16_t *)(((int)(uVar1 + 3) >> 2) * (uint32_t)uVar2 + (int)puVar3);
            }
            goto LAB_81c09858;
        }
        *param_1 = 0;
    }
    param_1[1] = 0;
LAB_81c09858:
    param_1[2] = param_2;
    return puVar3;
}
#undef local_18

/* 原函数 0x81c098b4 */
uint32_t sango_input_key_is_down(uint32_t param_1)
{
    unsigned char abi_storage[22] __attribute__((aligned(8)));
#define local_18 (*(char *)(abi_storage + 0))
#define local_17 (*(char *)(abi_storage + 1))
#define local_16 (*(char *)(abi_storage + 2))
#define local_15 (*(char *)(abi_storage + 3))
#define local_14 (*(char *)(abi_storage + 4))
#define local_13 (*(char *)(abi_storage + 5))

    crt_memset(&local_18, 0, 6);
    bda_sango_gui_input_packet(&local_18);
    if (param_1 != 0x67)
    {
        if (param_1 < 0x68)
        {
            local_15 = '\x01';
            if (param_1 != 1)
            {
                if (param_1 != 0x1c)
                {
                    return 0;
                }
                return (uint32_t)(local_13 == '\x01');
            }
            goto LAB_81c09944;
        }
        local_15 = local_18;
        if (param_1 != 0x6a)
        {
            if (param_1 < 0x6b)
            {
                local_15 = local_17;
                if (param_1 != 0x69)
                {
                    return 0;
                }
            }
            else
            {
                local_15 = local_16;
                if (param_1 != 0x6c)
                {
                    return 0;
                }
            }
        }
    }
    local_14 = '\x01';
LAB_81c09944:
    return (uint32_t)(local_14 == local_15);
}
#undef local_18
#undef local_17
#undef local_16
#undef local_15
#undef local_14
#undef local_13

/* 原函数 0x81c09990 */
void sango_input_decode_key_packet(short param_1, short param_2, short param_3, short param_4,
                                   int param_5)
{
    unsigned char abi_storage[52] __attribute__((aligned(8)));
    (*(int *)(abi_storage + 32)) = param_5;
#define param_5 (*(int *)(abi_storage + 32))
#define local_10 (*(uint32_t(*)[2])(abi_storage + 0))
#define local_8 (*(uint32_t(*)[2])(abi_storage + 8))

    uint8_t bVar1;
    uint8_t bVar2;
    uint8_t *pbVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    int iVar8;
    int iVar9;
    int iVar10;
    int iVar11;
    int iVar12;
    int iVar13;

    iVar6 = (int)param_1;
    local_10[0] = g_legacy_data_81c20244;
    local_8[0] = g_legacy_data_81c20248;
    iVar4 = (int)param_3;
    iVar8 = (int)param_2;
    iVar10 = (int)param_4;
    if (iVar6 < 0xf0)
    {
        if (iVar6 < 0)
        {
            iVar6 = 0;
        }
        if (iVar8 < 0x140)
        {
            if (iVar8 < 0)
            {
                iVar8 = 0;
            }
            if (-1 < iVar4)
            {
                if (0xef < iVar4)
                {
                    iVar4 = 0xef;
                }
                if (-1 < iVar10)
                {
                    iVar11 = iVar4 + 3;
                    if (-1 < iVar4)
                    {
                        iVar11 = iVar4;
                    }
                    iVar7 = iVar6 + 3;
                    if (-1 < iVar6)
                    {
                        iVar7 = iVar6;
                    }
                    iVar13 = (iVar6 + (iVar7 >> 2) * -4) * 0x10000 >> 0x10;
                    iVar11 = (iVar4 + (iVar11 >> 2) * -4) * 0x10000 >> 0x10;
                    iVar6 = (iVar4 - iVar11) + (iVar13 - iVar6);
                    iVar4 = iVar6 + 4;
                    if (0x13f < iVar10)
                    {
                        iVar10 = 0x13f;
                    }
                    if (iVar4 < 0)
                    {
                        iVar4 = iVar6 + 7;
                    }
                    iVar4 = iVar4 >> 2;
                    iVar6 = 0;
                    if (-1 < iVar10 - iVar8)
                    {
                        iVar9 = param_5 + (int)(short)(iVar7 >> 2) + iVar8 * 0x3c;
                        iVar12 = 0;
                        iVar7 = 0;
                        do
                        {
                            bVar1 = *(uint8_t *)(iVar7 + iVar9);
                            bVar2 = *(uint8_t *)((int)local_10 + iVar13);
                            iVar5 = iVar7 + iVar9 + iVar4;
                            *(uint8_t *)(iVar7 + iVar9) = ~bVar1 & bVar2 | bVar1 & ~bVar2;
                            bVar1 = *(uint8_t *)(iVar5 + -1);
                            bVar2 = *(uint8_t *)((int)local_8 + iVar11);
                            *(uint8_t *)(iVar5 + -1) = ~bVar1 & bVar2 | bVar1 & ~bVar2;
                            if ((2 < iVar4) && (0 < iVar4 + -2))
                            {
                                pbVar3 = (uint8_t *)(iVar12 * 4 + iVar9);
                                iVar5 = iVar4 + -2;
                                do
                                {
                                    pbVar3 = pbVar3 + 1;
                                    iVar5 = iVar5 + -1;
                                    *pbVar3 = ~*pbVar3;
                                } while (iVar5 != 0);
                            }
                            iVar6 = iVar6 + 1;
                            iVar7 = iVar7 + 0x3c;
                            iVar12 = iVar12 + 0xf;
                        } while (iVar6 <= iVar10 - iVar8);
                    }
                }
            }
        }
    }
    return;
}
#undef param_5
#undef local_10
#undef local_8

/* 原函数 0x81c09b6c */
uint32_t sango_text_input_proc(uint32_t handle, int message, uint32_t wparam, uint32_t lparam)
{
    uint32_t uVar1;

    if (message == 0x66)
    {
        bda_sango_gui_edit_finish();
        bda_sango_gui_control_destroy(g_platform_state_104);
        bda_sango_gui_frame_stop(handle);
        bda_sango_gui_frame_release(handle);
        uVar1 = 0;
    }
    else
    {
        if (message < 0x67)
        {
            if (message == 0x12)
            {
                if ((wparam & 0xffff) == 0x1c)
                {
                    bda_sango_gui_send_message(g_platform_state_104, 0x133, g_text_input_frame,
                                               g_legacy_data_81c2b10c);
                    bda_sango_gui_post_message(handle, 0x66, 0, 0);
                    g_platform_state_108 = 0;
                }
                else if ((wparam & 0xffff) == 1)
                {
                    bda_sango_gui_post_message(handle, 0x66, 0, 0);
                }
            }
            else if (message == 0x60)
            {
                g_platform_state_108 = 1;
                g_platform_state_104 = bda_sango_gui_control_create(
                    (char *)0x81c2024c, (char *)0x0, 0x48410000, 0, 0, 6, 8, 0x78, 0x18, handle, 0);
                bda_sango_gui_send_message(g_platform_state_104, 0xf0c5, g_text_input_frame,
                                           g_legacy_data_81c2b10c);
                bda_sango_gui_set_active(g_platform_state_104);
            }
        }
        uVar1 = bda_sango_gui_default_proc(handle, message, wparam, lparam);
    }
    return uVar1;
}

/* 原函数 0x81c09d90 */
uint32_t sango_text_input_dialog(uint32_t param_1, uint8_t *param_2, uint32_t param_3)
{
    unsigned char abi_storage[104] __attribute__((aligned(8)));
#define local_50 (*(SangoLegacyCode **)(abi_storage + 24))
#define local_4c (*(uint32_t *)(abi_storage + 28))
#define local_48 (*(uint32_t *)(abi_storage + 32))
#define local_44 (*(uint32_t *)(abi_storage + 36))
#define local_40 (*(uint32_t *)(abi_storage + 40))
#define local_3c (*(void **)(abi_storage + 44))
#define local_38 (*(uint32_t *)(abi_storage + 48))
#define auStack_30 (*(uint8_t(*)[32])(abi_storage + 56))
#define local_68 (*(uint32_t *)(abi_storage + 0))
#define local_64 (*(uint32_t *)(abi_storage + 4))
#define local_60 (*(uint32_t *)(abi_storage + 8))
#define local_5c (*(uint32_t *)(abi_storage + 12))
#define local_58 (*(uint32_t *)(abi_storage + 16))
#define local_54 (*(uint32_t *)(abi_storage + 20))

    int iVar1;
    uint32_t uVar2;
    uint32_t uVar3;

    *param_2 = 0;
    local_68 = 0x28400000;
    local_50 = sango_text_input_proc;
    local_4c = 0x5a;
    local_44 = 0xe6;
    local_48 = 0x50;
    local_40 = 0x8c;
    local_64 = 0;
    local_5c = 0;
    local_58 = 0;
    g_text_input_frame = param_3;
    g_legacy_data_81c2b10c_view2 = param_2;
    local_60 = param_1;
    local_3c = bda_sango_gui_draw_object(8);
    local_38 = 0;
    local_54 = 0;
    iVar1 = bda_sango_gui_display_metric(0, 6);
    g_input_dialog_backing = bda_sango_mem_alloc(iVar1 * 0x3200 + 10);
    if (g_input_dialog_backing != 0)
    {
        bda_sango_gui_capture_region(0, 200, 0x140, 0x28, g_input_dialog_backing);
    }
    uVar2 = bda_sango_gui_register_frame(&local_68);
    if (uVar2 == 0xffffffff)
    {
        bda_sango_mem_free(g_input_dialog_backing);
        uVar3 = 1;
    }
    else
    {
        while (iVar1 = bda_sango_gui_event_poll(auStack_30, 0), iVar1 != 0)
        {
            bda_sango_gui_event_step(auStack_30);
            bda_sango_gui_event_dispatch(auStack_30);
        }
        bda_sango_gui_close_frame(uVar2);
        uVar3 = g_platform_state_108;
        if (g_input_dialog_backing != 0)
        {
            bda_sango_gui_restore_region(0, 200, 0xf0, 0x28, g_input_dialog_backing);
            bda_sango_mem_free(g_input_dialog_backing);
            uVar3 = g_platform_state_108;
        }
    }
    return uVar3;
}
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef auStack_30
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_58
#undef local_54

/* 原函数 0x81c09fb0 */
void sango_display_render_bitmap_region(short param_1, short param_2, int param_3, uint32_t param_4,
                                        int param_5, int param_6)
{
    unsigned char abi_storage[120] __attribute__((aligned(8)));
    (*(int *)(abi_storage + 96)) = param_5;
    (*(int *)(abi_storage + 100)) = param_6;
#define param_5 (*(int *)(abi_storage + 96))
#define param_6 (*(int *)(abi_storage + 100))
#define local_50 (*(int(*)[4])(abi_storage + 0))
#define local_40 (*(uint32_t *)(abi_storage + 16))
#define local_3c (*(int *)(abi_storage + 20))
#define local_38 (*(int *)(abi_storage + 24))
#define local_34 (*(uint32_t *)(abi_storage + 28))
#define local_30 (*(uint8_t *)(abi_storage + 32))
#define local_2f (*(uint8_t *)(abi_storage + 33))
#define local_2c (*(int *)(abi_storage + 36))
#define local_28 (*(int *)(abi_storage + 40))
#define local_20 (*(uint8_t *)(abi_storage + 48))
#define local_1f (*(uint8_t *)(abi_storage + 49))
#define local_1e (*(uint8_t *)(abi_storage + 50))
#define local_1d (*(uint8_t *)(abi_storage + 51))

    uint32_t uVar1;
    int iVar2;
    int iVar3;

    iVar3 = (int)param_2;
    iVar2 = (int)param_1;
    sango_bitmap_open_embedded_entry(local_50, 1, param_3, param_6);
    local_40 = 0;
    local_3c = (((uint32_t) * (uint8_t *)(local_50[0] + 7) * 0x100 +
                 (uint32_t) * (uint8_t *)(local_50[0] + 6)) *
                    0x100 +
                (uint32_t) * (uint8_t *)(local_50[0] + 5)) *
                   0x100 +
               (uint32_t) * (uint8_t *)(local_50[0] + 4);
    local_20 = *(uint8_t *)(local_50[0] + 8);
    local_1f = *(uint8_t *)(local_50[0] + 9);
    local_1e = *(uint8_t *)(local_50[0] + 10);
    local_1d = *(uint8_t *)(local_50[0] + 0xb);
    local_34 = 0;
    local_38 =
        (((uint32_t)local_1d * 0x100 + (uint32_t)local_1e) * 0x100 + (uint32_t)local_1f) * 0x100 +
        (uint32_t)local_20;
    local_30 = *(uint8_t *)(local_50[0] + 0x10);
    local_2c = local_50[0] + 0x16;
    local_2f = 0x10;
    local_28 = -1;
    if (param_5 == 0)
    {
        if (param_4 != 0)
        {
            bda_sango_gui_render_region(param_4, iVar2, iVar3, local_3c, local_38, local_3c,
                                        local_38, &local_40, 0, 0);
            return;
        }
        bda_sango_gui_draw_guard(1);
        uVar1 = bda_sango_gui_object_draw_begin(g_app_frame);
        bda_sango_gui_render_region(uVar1, iVar2, iVar3, local_3c, local_38, local_3c, local_38,
                                    &local_40, 0, 0);
    }
    else
    {
        if (param_5 != 1)
        {
            return;
        }
        if (param_4 != 0)
        {
            local_28 = bda_sango_gui_rgb(param_4, 0xff, 0, 0xff);
            bda_sango_gui_render_region(param_4, iVar2, iVar3, local_3c, local_38, local_3c,
                                        local_38, &local_40, 0, 0);
            return;
        }
        bda_sango_gui_draw_guard(1);
        uVar1 = bda_sango_gui_object_draw_begin(g_app_frame);
        local_28 = bda_sango_gui_rgb(uVar1, 0xff, 0, 0xff);
        bda_sango_gui_render_region(uVar1, iVar2, iVar3, local_3c, local_38, local_3c, local_38,
                                    &local_40, 0, 0);
    }
    bda_sango_gui_object_draw_end(g_app_frame, uVar1);
    bda_sango_gui_draw_guard(0);
    return;
}
#undef param_5
#undef param_6
#undef local_50
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2f
#undef local_2c
#undef local_28
#undef local_20
#undef local_1f
#undef local_1e
#undef local_1d

/* 原函数 0x81c0a2c0 */
void sango_platform_window_auxiliary(uint32_t param_1, uint32_t param_2)
{
    bda_sango_gui_window_aux_a(g_app_frame, param_1, param_2);
    return;
}

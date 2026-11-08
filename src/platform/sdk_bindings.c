#include "sango_internal.h"

/* 应用窗口、计时、内存、文件和消息框适配。 */

/* 原函数 0x81c0a330 */
int sango_create_app_frame(void)
{
    unsigned char abi_storage[68] __attribute__((aligned(8)));
#define local_3c (*(uint32_t *)(abi_storage + 4))
#define local_38 (*(char **)(abi_storage + 8))
#define local_34 (*(uint32_t *)(abi_storage + 12))
#define local_30 (*(uint32_t *)(abi_storage + 16))
#define local_2c (*(uint32_t *)(abi_storage + 20))
#define local_28 (*(SangoLegacyCode **)(abi_storage + 24))
#define local_24 (*(uint32_t *)(abi_storage + 28))
#define local_20 (*(uint32_t *)(abi_storage + 32))
#define local_1c (*(uint32_t *)(abi_storage + 36))
#define local_18 (*(uint32_t *)(abi_storage + 40))
#define local_14 (*(void **)(abi_storage + 44))
#define local_10 (*(uint32_t *)(abi_storage + 48))
#define local_40 (*(uint32_t *)(abi_storage + 0))

    int iVar1;
    int iVar2;

    g_frame_buffer = bda_sango_mem_alloc(0x4b20);
    iVar2 = -1;
    if (g_frame_buffer != 0)
    {
        crt_memset(g_frame_buffer, 0xff, 0x4b00);
        local_40 = 0x8000000;
        local_38 = g_legacy_data_81c20210;
        local_28 = sango_window_proc;
        local_1c = 0xf0;
        local_18 = 0x140;
        local_3c = 0;
        local_34 = 0;
        local_30 = 0;
        local_24 = 0;
        local_20 = 0;
        local_14 = bda_sango_gui_draw_object(0xf);
        local_10 = 0;
        local_2c = 0;
        iVar1 = bda_sango_gui_register_frame(&local_40);
        iVar2 = -1;
        if (iVar1 != -1)
        {
            sango_display_set_brush(0, 0);
            sango_display_set_text_color(3, 0);
            bda_sango_gui_set_text_mode(g_draw_context, 0);
            g_legacy_data_81c2b20c = 0;
            iVar2 = 0;
        }
    }
    return iVar2;
}
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_40

/* 原函数 0x81c0a44c */
uint32_t sango_platform_allocate_zeroed_buffer(void)
{
    bool bVar1;

    g_frame_buffer = bda_sango_mem_alloc(0x4b20);
    bVar1 = g_frame_buffer != 0;
    if (bVar1)
    {
        crt_memset(g_frame_buffer, 0xff, 0x4b00);
    }
    return (uint32_t)bVar1;
}

/* 原函数 0x81c0a4a4 */
int sango_run_event_loop_and_close(void)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define auStack_28 (*(uint8_t(*)[32])(abi_storage + 0))

    int iVar1;

    bda_sango_gui_post_message(g_app_frame, 0x66, 0, 0);
    while (true)
    {
        iVar1 = bda_sango_gui_event_poll(auStack_28, 0);
        if (iVar1 == 0)
            break;
        bda_sango_gui_event_step(auStack_28);
        bda_sango_gui_event_dispatch(auStack_28);
    }
    bda_sango_gui_close_frame(g_app_frame);
    if (g_frame_buffer != 0)
    {
        bda_sango_mem_free((void *)g_frame_buffer);
    }
    return 1;
}
#undef auStack_28

/* 原函数 0x81c0a578 */
void sango_platform_init_window_descriptor(uint32_t *param_1)
{
    void *pvVar3;

    *param_1 = 0x8000000;
    param_1[2] = g_legacy_data_81c20210;
    param_1[6] = sango_window_proc;
    param_1[9] = 0xf0;
    param_1[10] = 0x140;
    param_1[1] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[7] = 0;
    param_1[8] = 0;
    pvVar3 = bda_sango_gui_draw_object(0xf);
    param_1[0xb] = pvVar3;
    param_1[5] = 0;
    param_1[0xc] = 0;
    return;
}

/* 原函数 0x81c0a5fc */
uint32_t sango_input_poll_native_event(uint32_t *param_1)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define auStack_28 (*(uint8_t(*)[32])(abi_storage + 0))

    int iVar1;

    iVar1 = bda_sango_gui_event_poll(auStack_28, 0);
    if (iVar1 != 0)
    {
        bda_sango_gui_event_step(auStack_28);
        bda_sango_gui_event_dispatch(auStack_28);
        *param_1 = g_native_event_kind_view2;
        param_1[1] = g_native_event_key;
        param_1[2] = g_native_event_data;
        g_native_event_kind_view2 = 0;
    }
    return (uint32_t)(iVar1 != 0);
}
#undef auStack_28

/* 原函数 0x81c0a6a0 */
int bbk_post_message(uint32_t message, uint32_t wparam, uint32_t lparam)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define local_24 (*(uint32_t *)(abi_storage + 4))
#define local_20 (*(uint32_t *)(abi_storage + 8))
#define local_1c (*(uint32_t *)(abi_storage + 12))
#define auStack_28 (*(uint8_t(*)[4])(abi_storage + 0))

    crt_memset(auStack_28, 0, 0x1c);
    local_24 = message;
    local_20 = wparam;
    local_1c = lparam;
    bda_sango_gui_post_message(g_app_frame, message, wparam, lparam);
    return 1;
}
#undef local_24
#undef local_20
#undef local_1c
#undef auStack_28

/* 原函数 0x81c0a704 */
void *bbk_alloc(uint32_t size)
{
    void *pvVar1;

    pvVar1 = bda_sango_mem_alloc(size);
    return pvVar1;
}

/* 原函数 0x81c0a72c */
void bbk_free_if_nonnull(void *ptr)
{
    if (ptr != 0)
    {
        bda_sango_mem_free(ptr);
    }
    return;
}

/* 原函数 0x81c0a774 */
char *bbk_strcat(char *destination, char *source)
{
    char *pcVar1;

    pcVar1 = sango_crt_strcat(destination, source);
    return pcVar1;
}

/* 原函数 0x81c0a790 */
uint32_t bbk_strlen(char *text)
{
    uint32_t uVar1;

    uVar1 = sango_crt_strlen(text);
    return uVar1;
}

/* 原函数 0x81c0a7ac */
void *bbk_memcpy(void *dst, void *src, uint32_t size)
{
    void *pvVar1;

    pvVar1 = crt_memcpy(dst, src, size);
    return pvVar1;
}

/* 原函数 0x81c0a7c8 */
void sango_memory_fill(void *destination, int value, uint32_t bytes)
{
    crt_memset(destination, value, bytes);
    return;
}

/* 原函数 0x81c0a7e4 */
uint8_t *sango_format_integer(int param_1, uint8_t *param_2, int param_3)
{
    int iVar1;
    uint8_t *pbVar2;

    pbVar2 = &g_legacy_data_81c20254;
    if (param_3 != 10)
    {
        if (param_3 < 0xb)
        {
            pbVar2 = &g_legacy_data_81c20258;
            iVar1 = 8;
        }
        else
        {
            pbVar2 = (uint8_t *)0x81c2025c;
            iVar1 = 0x10;
        }
        if (param_3 != iVar1)
        {
            return pbVar2;
        }
    }
    sango_crt_format_entry(param_2, pbVar2, param_1, param_3);
    return pbVar2;
}

/* 原函数 0x81c0a86c */
void bbk_zero_time_stub(uint16_t *time_fields)
{
    time_fields[7] = 0;
    *time_fields = 0;
    time_fields[1] = 0;
    time_fields[2] = 0;
    time_fields[5] = 0;
    time_fields[3] = 0;
    time_fields[6] = 0;
    time_fields[4] = 0;
    return;
}

/* 原函数 0x81c0a890 */
void bbk_srand(uint32_t seed)
{
    crt_srand(seed);
    return;
}

/* 原函数 0x81c0a8ac */
uint32_t bbk_rand(void)
{
    uint32_t uVar1;

    uVar1 = crt_rand();
    return uVar1;
}

/* 原函数 0x81c0a8c8 */
uint32_t sango_timer_start(uint32_t param_1, uint32_t param_2)
{
    bda_sango_gui_timer_start(g_app_frame, param_1, param_2);
    return 1;
}

/* 原函数 0x81c0a904 */
uint32_t sango_timer_stop(uint32_t param_1)
{
    bda_sango_gui_timer_stop(g_app_frame, param_1);
    return 1;
}

/* 原函数 0x81c0a938 */
void *bbk_compatible_context_create(void)
{
    void *pvVar1;

    pvVar1 = bda_sango_gui_compatible_create(g_draw_context);
    return pvVar1;
}

/* 原函数 0x81c0a964 */
int bbk_compatible_context_free(void *context)
{
    bda_sango_gui_compatible_free(context);
    return 1;
}

/* 原函数 0x81c0a990 */
void sango_display_present_context(uint32_t param_1, uint32_t param_2)
{

    if (param_1 == 0)
    {
        if (param_2 != 0)
        {
            bda_sango_gui_draw_guard(1);
            bda_sango_gui_context_copy(param_2, 0, 0, 0xf0, 0x140, g_draw_context, 0, 0, 0xf81f);
            bda_sango_gui_request_redraw(g_app_frame, 0, 0);
            bda_sango_gui_draw_guard(0);
        }
    }
    else
    {
        if (param_2 == 0)
        {
            param_2 = g_draw_context;
        }
        else
        {
        }
        bda_sango_gui_context_copy(param_2, 0, 0, 0xf0, 0x140, param_1, 0, 0, 0xf81f);
    }
    return;
}

/* 原函数 0x81c0aadc */
void sango_display_noop(void)
{
    return;
}

/* 原函数 0x81c0aae4 */
void sango_display_invert_rectangle(short param_1, short param_2, short param_3, short param_4,
                                    uint32_t param_5)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(uint32_t *)(abi_storage + 0)) = param_5;
#define param_5 (*(uint32_t *)(abi_storage + 0))

    int iVar1;
    int iVar2;

    iVar2 = (int)param_1;
    iVar1 = (int)param_2;
    if (param_5 == 0)
    {
        bda_sango_gui_draw_guard(1);
        bda_sango_gui_draw_aux_rectangle(g_draw_context, iVar2, iVar1, param_3 - iVar2,
                                         param_4 - iVar1);
        bda_sango_gui_draw_guard(0);
    }
    else
    {
        bda_sango_gui_draw_aux_rectangle(param_5, iVar2, iVar1, param_3 - iVar2, param_4 - iVar1);
    }
    return;
}
#undef param_5

/* 原函数 0x81c0abcc */
int sango_platform_noop(uint8_t *param_1)
{
    return (((uint32_t)param_1[3] * 0x100 + (uint32_t)param_1[2]) * 0x100 + (uint32_t)param_1[1]) *
               0x100 +
           (uint32_t)*param_1;
}

/* 原函数 0x81c0ac00 */
uint32_t sango_bitmap_query_dimensions(uint16_t *param_1, uint32_t param_2, uint32_t param_3,
                                       uint32_t *param_4, uint32_t *param_5)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(uint32_t **)(abi_storage + 0)) = param_5;
#define param_5 (*(uint32_t **)(abi_storage + 0))

    uint32_t uVar1;

    uVar1 = 0;
    if (((param_1 != (uint16_t *)0x0) && (param_4 != (uint32_t *)0x0)) &&
        (param_5 != (uint32_t *)0x0))
    {
        uVar1 = 1;
        *param_4 = (uint32_t)*param_1;
        *param_5 = (uint32_t)param_1[1];
    }
    return uVar1;
}
#undef param_5

/* 原函数 0x81c0ac48 */
void sango_display_fill_gray_rectangle(short param_1, short param_2, short param_3, short param_4,
                                       uint32_t param_5, uint32_t param_6)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
    (*(uint32_t *)(abi_storage + 0)) = param_5;
    (*(uint32_t *)(abi_storage + 4)) = param_6;
#define param_5 (*(uint32_t *)(abi_storage + 0))
#define param_6 (*(uint32_t *)(abi_storage + 4))

    sango_display_fill_rectangle(param_1, param_2, param_3, param_4, param_5, param_6);
    return;
}
#undef param_5
#undef param_6

/* 原函数 0x81c0ad1c */
void sango_text_get_font_metrics(uint16_t *param_1, uint32_t param_2)
{
    int iVar2;

    bda_sango_gui_current_font(param_2);
    bda_sango_gui_select_font(g_draw_context, param_2 & 0xff);
    iVar2 = bda_sango_gui_font_cell_width(g_draw_context);
    param_1[1] = (short)iVar2;
    iVar2 = bda_sango_gui_font_cell_height(g_draw_context);
    *param_1 = (short)iVar2;
    bda_sango_gui_select_font(g_draw_context, (uint32_t)g_legacy_data_81c2b210);
    return;
}

/* 原函数 0x81c0addc */
void sango_text_draw_native(short param_1, short param_2, char *param_3, uint32_t param_4)
{
    if (param_4 == 0)
    {
        bda_sango_gui_draw_guard(1);
        bda_sango_gui_draw_text(g_draw_context, (int)param_1, (int)param_2, param_3, -1);
        bda_sango_gui_draw_guard(0);
    }
    else
    {
        bda_sango_gui_draw_text(param_4, (int)param_1, (int)param_2, param_3, -1);
    }
    return;
}

/* 原函数 0x81c0aeb0 */
void bbk_clearerr(void *file)
{
    bda_sango_fs_clearerr(file);
    return;
}

/* 原函数 0x81c0aed8 */
int bbk_ferror(void *file)
{
    int iVar1;

    iVar1 = bda_sango_fs_ferror(file);
    return iVar1;
}

/* 原函数 0x81c0af00 */
int bbk_fclose(void *file)
{
    int iVar1;

    iVar1 = bda_sango_fs_fclose(file);
    return iVar1;
}

/* 原函数 0x81c0af28 */
int bbk_feof(void *file)
{
    int iVar1;

    iVar1 = bda_sango_fs_feof(file);
    return iVar1;
}

/* 原函数 0x81c0af50 */
uint32_t sango_platform_stub_0af50(void)
{
    return 0;
}

/* 原函数 0x81c0af58 */
uint32_t sango_platform_stub_0af58(void)
{
    return 0;
}

/* 原函数 0x81c0af60 */
void *bbk_fopen(char *path, char *mode)
{
    void *pvVar1;

    pvVar1 = bda_sango_fs_fopen(path, mode);
    return pvVar1;
}

/* 原函数 0x81c0af88 */
uint32_t sango_platform_stub_0af88(void)
{
    return 0;
}

/* 原函数 0x81c0af90 */
uint32_t sango_platform_stub_0af90(void)
{
    return 0;
}

/* 原函数 0x81c0af98 */
uint32_t bbk_fread(void *buffer, uint32_t size, uint32_t count, void *file)
{
    if ((size != 0) && (count != 0))
    {
        count = bda_sango_fs_fread(buffer, size, count, file);
    }
    return count;
}

/* 原函数 0x81c0afdc */
int bbk_fseek(void *file, int offset, int whence)
{
    int iVar1;

    iVar1 = bda_sango_fs_fseek(file, offset, whence);
    return iVar1;
}

/* 原函数 0x81c0b004 */
int bbk_ftell(void *file)
{
    int iVar1;

    iVar1 = bda_sango_fs_ftell(file);
    return iVar1;
}

/* 原函数 0x81c0b02c */
uint32_t bbk_fwrite(void *param_1, uint32_t param_2, uint32_t param_3, void *param_4)
{
    if ((param_2 != 0) && (param_3 != 0))
    {
        param_3 = bda_sango_fs_fwrite(param_1, param_2, param_3, param_4);
    }
    return param_3;
}

/* 原函数 0x81c0b070 */
uint32_t sango_platform_stub_0b070(void)
{
    return 0;
}

/* 原函数 0x81c0b078 */
uint32_t sango_platform_stub_0b078(void)
{
    return 0;
}

/* 原函数 0x81c0b080 */
uint32_t sango_platform_stub_0b080(void)
{
    return 0;
}

/* 原函数 0x81c0b088 */
uint32_t sango_platform_stub_0b088(void)
{
    return 0;
}

/* 原函数 0x81c0b090 */
uint32_t sango_platform_stub_0b090(void)
{
    return 0;
}

/* 原函数 0x81c0b098 */
int bbk_rename(char *old_path, char *new_path)
{
    int iVar1;

    iVar1 = bda_sango_fs_rename(old_path, new_path);
    return iVar1;
}

/* 原函数 0x81c0b0c0 */
void sango_platform_stub_0b0c0(void)
{
    return;
}

/* 原函数 0x81c0b0c8 */
void *bbk_load_file_with_progress(char *path)
{
    short sVar1;
    uint32_t uVar2;
    void *pvVar3;
    int iVar4;
    void *pvVar5;
    void *pvVar6;
    uint32_t uVar7;
    uint32_t uVar8;

    pvVar3 = bda_sango_fs_fopen(path, (char *)0x81c20260);
    pvVar6 = (void *)0x0;
    if (pvVar3 != 0)
    {
        bda_sango_fs_fseek(pvVar3, 0, 2);
        iVar4 = bda_sango_fs_ftell(pvVar3);
        uVar2 = iVar4 / 100;
        pvVar5 = bda_sango_mem_alloc(iVar4 + 1);
        pvVar6 = (void *)0x0;
        if (pvVar5 != 0)
        {
            uVar8 = 0;
            bda_sango_fs_fseek(pvVar3, 0, 0);
            sango_display_fill_rectangle(0x12, 0x118, 0xde, 0x124, 0, 0);
            uVar7 = 0;
            do
            {
                bda_sango_fs_read_at((void *)((int)pvVar5 + uVar7), uVar7, uVar2, pvVar3);
                uVar7 = bda_sango_gui_rgb(g_draw_context, 0x1f, 0x78, 0xa5);
                sVar1 = (short)uVar8 * 2;
                sango_display_fill_rectangle(sVar1 + 0x14, 0x11a, sVar1 + 0x16, 0x122, uVar7, 0);
                uVar8 = uVar8 + 1 & 0xff;
                uVar7 = uVar8 * uVar2;
            } while (uVar8 < 100);
            bda_sango_fs_fread((void *)((int)pvVar5 + uVar2 * 100), iVar4 % 100, 1, pvVar3);
            bda_sango_fs_fclose(pvVar3);
            pvVar6 = pvVar5;
        }
    }
    return pvVar6;
}

/* 原函数 0x81c0b2c4 */
uint32_t sango_platform_stub_0b2c4(void)
{
    return 1;
}

/* 原函数 0x81c0b2cc */
uint32_t sango_platform_stub_0b2cc(void)
{
    return 1;
}

/* 原函数 0x81c0b2d4 */
uint32_t sango_platform_stub_0b2d4(void)
{
    return 1;
}

/* 原函数 0x81c0b404 */
void sango_input_dispatch_pending_events(uint32_t param_1)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define auStack_38 (*(uint8_t(*)[32])(abi_storage + 0))

    bool bVar1;
    int iVar2;
    uint32_t uVar3;

    uVar3 = 0;
    bVar1 = true;
    do
    {
        iVar2 = bda_sango_gui_event_poll(auStack_38, 0);
        if (iVar2 != 0)
        {
            bda_sango_gui_event_step(auStack_38);
            bda_sango_gui_event_dispatch(auStack_38);
            iVar2 = g_native_event_kind;
            g_native_event_kind = 0;
            if (iVar2 == 0x144)
            {
                uVar3 = uVar3 + 1;
            }
            if (iVar2 == 0x10)
            {
                bVar1 = false;
            }
            if (param_1 / 0x2a <= uVar3)
            {
                bVar1 = false;
            }
        }
    } while (bVar1);
    return;
}
#undef auStack_38

/* 原函数 0x81c0b500 */
int graphics_init_stub(void)
{
    return 1;
}

/* 原函数 0x81c0b508 */
uint32_t sango_platform_stub_0b508(void)
{
    return 1;
}

/* 原函数 0x81c0b510 */
int bbk_message_box(char *message, char *title, uint32_t flags)
{
    void *pvVar1;
    int iVar2;

    pvVar1 = bda_sango_gui_compatible_create(g_draw_context);
    iVar2 = -1;
    if (pvVar1 != 0)
    {
        bda_sango_gui_context_copy(g_draw_context, 0, 0, 0xf0, 0x140, (uint32_t)pvVar1, 0, 0,
                                   0xf81f);
        iVar2 = bda_sango_gui_message_box(0, message, title, flags);
        bda_sango_gui_draw_guard(1);
        bda_sango_gui_context_copy((uint32_t)pvVar1, 0, 0, 0xf0, 0x140, g_draw_context, 0, 0,
                                   0xf81f);
        bda_sango_gui_request_redraw(g_app_frame, 0, 0);
        bda_sango_gui_draw_guard(0);
        bda_sango_gui_compatible_free(pvVar1);
    }
    return iVar2;
}

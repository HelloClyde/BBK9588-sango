#include "sango_internal.h"

/* 事件规范化、等待及按键探测。 */

/* 原函数 0x81c1408c */
uint32_t sango_input_next_event(int *event)
{
    int iVar1;
    int iVar2;

    if (g_legacy_data_81c2b9a8 == 0)
    {
        do
        {
            while (true)
            {
                sango_input_poll_native_event(event);
                iVar1 = *event;
                if (iVar1 == 0x10)
                {
                    iVar2 = 5;
                    goto LAB_81c14154;
                }
                if (0x10 < iVar1)
                    break;
                if (iVar1 == 1)
                {
                    *event = 0xb;
                    g_battle_map_width_aux_view2 = (char)event[2];
                    g_legacy_touch_y_byte = (char)*(uint16_t *)((int)event + 10);
                    return 0;
                }
            }
            iVar2 = 6;
        } while (iVar1 != 0x144);
    LAB_81c14154:
        *event = iVar2;
    }
    else
    {
        *event = g_legacy_data_81c2b9a8;
        event[1] = g_legacy_data_81c2b9ac;
        event[2] = g_legacy_data_81c2b9b0;
        g_legacy_data_81c2b9a8 = 0;
    }
    return 0;
}

/* 原函数 0x81c14164 */
uint32_t sango_input_wait(short ticks, char allow_key)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define local_28 (*(uint32_t *)(abi_storage + 0))
#define local_24 (*(uint32_t *)(abi_storage + 4))

    char cVar1;
    short sVar2;

    cVar1 = g_draw_enabled_view3;
    sango_timer_stop(1);
    if (ticks == 0)
    {
        sango_input_next_event((int *)&local_28);
    }
    else
    {
        sango_timer_start(1, 1);
        while (ticks != 0)
        {
            sango_input_next_event((int *)&local_28);
            if (local_28 == 0xb)
            {
                if (cVar1 != '\0')
                {
                    sango_timer_stop(1);
                    sango_timer_start(1, 1);
                    return local_28 & 0xff;
                }
                return 0xb;
            }
            sVar2 = ticks + -1;
            if ((local_28 != 6) && (sVar2 = ticks, allow_key != '\0'))
                break;
            ticks = sVar2;
            local_24 = 0;
        }
    }
    if (cVar1 != '\0')
    {
        sango_timer_stop(1);
        sango_timer_start(1, 1);
    }
    return local_24 & 0xff;
}
#undef local_28
#undef local_24

/* 原函数 0x81c14268 */
uint32_t sango_input_peek_key(void)
{
    unsigned char abi_storage[21] __attribute__((aligned(8)));
#define local_14 (*(uint8_t *)(abi_storage + 4))
#define local_18 (*(int *)(abi_storage + 0))

    uint32_t uVar1;

    sango_input_next_event(&local_18);
    uVar1 = 0xff;
    if (local_18 == 5)
    {
        uVar1 = (uint32_t)local_14;
    }
    return uVar1;
}
#undef local_14
#undef local_18

/* 原函数 0x81c14298 */
void sango_runtime_noop_a(void)
{
    return;
}

/* 原函数 0x81c142a0 */
void sango_runtime_noop_b(void)
{
    return;
}

/* 原函数 0x81c142a8 */
uint32_t sango_runtime_read_tick_counter(uint32_t *param_1)
{
    g_legacy_data_81c2b9a8_view2 = *param_1;
    g_legacy_data_81c2b9ac_view2 = param_1[1];
    g_legacy_data_81c2b9b0_view2 = param_1[2];
    return 0;
}

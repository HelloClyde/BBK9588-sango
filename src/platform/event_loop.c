#include "sango_internal.h"

/* 事件规范化、等待及按键探测。 */

/* 原函数 0x81c1408c */
uint32_t sango_input_next_event(int *event)
{
    int native_event_kind;
    int normalized_event_kind;

    if (g_legacy_data_81c2b9a8 == 0)
    {
        do
        {
            while (true)
            {
                sango_input_poll_native_event(event);
                native_event_kind = *event;
                if (native_event_kind == 0x10)
                {
                    normalized_event_kind = 5;
                    goto store_normalized_kind;
                }
                if (0x10 < native_event_kind)
                    break;
                if (native_event_kind == 1)
                {
                    *event = 0xb;
                    g_battle_map_width_aux_view2 = (char)event[2];
                    g_legacy_touch_y_byte = (char)*(uint16_t *)((int)event + 10);
                    return 0;
                }
            }
            normalized_event_kind = 6;
        } while (native_event_kind != 0x144);
    store_normalized_kind:
        *event = normalized_event_kind;
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
#define event_kind (*(uint32_t *)(abi_storage + 0))
#define event_key (*(uint32_t *)(abi_storage + 4))

    char restore_draw_timer;
    short remaining_ticks;

    restore_draw_timer = g_draw_enabled_view3;
    sango_timer_stop(1);
    if (ticks == 0)
    {
        sango_input_next_event((int *)&event_kind);
    }
    else
    {
        sango_timer_start(1, 1);
        while (ticks != 0)
        {
            sango_input_next_event((int *)&event_kind);
            if (event_kind == 0xb)
            {
                if (restore_draw_timer != '\0')
                {
                    sango_timer_stop(1);
                    sango_timer_start(1, 1);
                    return event_kind & 0xff;
                }
                return 0xb;
            }
            remaining_ticks = ticks + -1;
            if ((event_kind != 6) && (remaining_ticks = ticks, allow_key != '\0'))
                break;
            ticks = remaining_ticks;
            event_key = 0;
        }
    }
    if (restore_draw_timer != '\0')
    {
        sango_timer_stop(1);
        sango_timer_start(1, 1);
    }
    return event_key & 0xff;
}
#undef event_kind
#undef event_key

/* 原函数 0x81c14268 */
uint32_t sango_input_peek_key(void)
{
    unsigned char abi_storage[21] __attribute__((aligned(8)));
#define event_key (*(uint8_t *)(abi_storage + 4))
#define event_kind (*(int *)(abi_storage + 0))

    uint32_t key_code;

    sango_input_next_event(&event_kind);
    key_code = 0xff;
    if (event_kind == 5)
    {
        key_code = (uint32_t)event_key;
    }
    return key_code;
}
#undef event_key
#undef event_kind

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
uint32_t sango_runtime_read_tick_counter(uint32_t *queued_event)
{
    g_legacy_data_81c2b9a8_view2 = *queued_event;
    g_legacy_data_81c2b9ac_view2 = queued_event[1];
    g_legacy_data_81c2b9b0_view2 = queued_event[2];
    return 0;
}

#include "sango_internal.h"

/* 资源库及会话缓冲区生命周期。 */

/* 原函数 0x81c13d80 */
/* 按文件实际大小读取sango.lib；会话缓冲区仍沿用原分配及失败返回约定。 */
int sango_load_package_and_buffers(void)
{
    unsigned char abi_storage[288] __attribute__((aligned(8)));
#define clock_parts (*(uint16_t(*)[8])(abi_storage + 256))
#define library_path (*(char(*)[256])(abi_storage + 0))

    uint32_t library_bytes;
    uint32_t failed;

    g_draw_enabled_view2 = 1;
    sango_timer_start(1, 500);
    crt_memset(library_path, 0, 0xfa);
    bbk_memcpy(library_path, g_legacy_data_81c20590, 10);
    crt_memset(library_path, 0, 0xfa);
    bbk_memcpy(library_path, &g_legacy_data_81c2059c, 0xfa);
    g_resource_file = bbk_fopen(library_path, &g_legacy_data_81c205b8);
    failed = 1;
    if (g_resource_file != 0)
    {
        bbk_fseek(g_resource_file, 0, 2);
        library_bytes = bbk_ftell(g_resource_file);
        g_resource_package_address = bbk_alloc(library_bytes);
        failed = 1;
        if (g_resource_package_address != 0)
        {
            bbk_fseek(g_resource_file, 0, 0);
            bbk_fread(g_resource_package_address, library_bytes, 1, g_resource_file);
            g_army_slot_used_address = bbk_alloc(0x1e);
            failed = 1;
            if (g_army_slot_used_address != 0)
            {
                g_army_rosters_address = bbk_alloc(300);
                failed = 1;
                if (g_army_rosters_address != 0)
                {
                    g_order_queue_address = bbk_alloc(0x4b0);
                    failed = 1;
                    if (g_order_queue_address != 0)
                    {
                        bbk_zero_time_stub(clock_parts);
                        bbk_srand((uint32_t)clock_parts[0]);
                        g_text_bottom = 0x140;
                        g_text_auto_clip = 1;
                        g_text_right = 0xef;
                        g_text_left = 0;
                        g_text_top = 0;
                        g_message_context = bbk_compatible_context_create();
                        g_game_context_view3 = bbk_compatible_context_create();
                        g_aux_context = bbk_compatible_context_create();
                        g_scratch_buffer_address = bbk_alloc(0x1000);
                        failed = (uint32_t)(g_scratch_buffer_address == 0);
                        if (!failed)
                        {
                            sango_music_set_library_path(library_path);
                            sango_settings_load(library_path);
                            sango_color_load(library_path, library_bytes);
                        }
                    }
                }
            }
        }
    }
    return failed;
}
#undef clock_parts
#undef library_path

/* 原函数 0x81c13f64 */
int sango_release_package_and_buffers(void)
{
    sango_color_unload();
    if (g_resource_package_address != 0)
    {
        bbk_free_if_nonnull(g_resource_package_address);
    }
    if (g_game_context_view3 != 0)
    {
        bbk_compatible_context_free(g_game_context_view3);
    }
    if (g_aux_context != 0)
    {
        bbk_compatible_context_free(g_aux_context);
    }
    if (g_message_context != 0)
    {
        bbk_compatible_context_free(g_message_context);
    }
    if (g_scratch_buffer_address != 0)
    {
        bbk_free_if_nonnull(g_scratch_buffer_address);
    }
    if (g_army_slot_used_address != 0)
    {
        bbk_free_if_nonnull(g_army_slot_used_address);
    }
    if (g_army_rosters_address != 0)
    {
        bbk_free_if_nonnull(g_army_rosters_address);
    }
    if (g_order_queue_address != 0)
    {
        bbk_free_if_nonnull(g_order_queue_address);
    }
    sango_timer_stop(1);
    bbk_fclose(g_resource_file);
    return 0;
}

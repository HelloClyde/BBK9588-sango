#include "sango_internal.h"

/* 应用及游戏会话总流程。 */

/* 原函数 0x81c16c24 */
void sango_main(void)
{
    int frame_failed;

    frame_failed = bda_sango_gui_shell_open(1);
    if ((frame_failed != 0) && (frame_failed = sango_create_app_frame(), frame_failed != -1))
    {
        sango_game_lifecycle();
        sango_run_event_loop_and_close();
    }
    return;
}

/* 原函数 0x81c16c80 */
/* 应用内的一次游戏生命周期：载入资源、显示片头、选择会话、运行战略循环及释放。 */
void sango_game_lifecycle(void)
{
    unsigned char abi_storage[128] __attribute__((aligned(8)));
#define package_error_text (*(char(*)[56])(abi_storage + 0))
#define session_error_text (*(char(*)[56])(abi_storage + 56))

    int failed;

    graphics_init_stub();
    failed = sango_load_package_and_buffers();
    if (failed == 0)
    {
        sango_animation_play_resource(3);
        failed = sango_allocate_session_state();
        if (failed == 0)
        {
            while (failed = sango_select_session(), failed != 0)
            {
                sango_strategy_run_months();
            }
        }
        else
        {
            sango_resource_read_text(1, 0x2f, session_error_text);
            sango_ui_show_message(session_error_text, 2);
        }
        sango_music_shutdown();
        bbk_free_if_nonnull(g_viewport_tiles_address_view2);
        bbk_free_if_nonnull(g_move_costs_address_view2);
        bbk_free_if_nonnull(g_temp_character_ids_address_view2);
        bbk_free_if_nonnull(g_character_table_address_view2);
        sango_release_package_and_buffers();
    }
    else
    {
        sango_resource_read_text(1, 0x2e, package_error_text);
        sango_ui_show_message(package_error_text, 2);
    }
    return;
}
#undef package_error_text
#undef session_error_text

/* 原函数 0x81c16d68 */
void sango_app_free_resource_buffer(void)
{
    bbk_free_if_nonnull(g_viewport_tiles_address_view2);
    bbk_free_if_nonnull(g_move_costs_address_view2);
    bbk_free_if_nonnull(g_temp_character_ids_address_view2);
    bbk_free_if_nonnull(g_character_table_address_view2);
    return;
}

/* 原函数 0x81c16db0 */
void sango_app_show_initialization_error(char error_kind)
{
    unsigned char abi_storage[72] __attribute__((aligned(8)));
#define error_text (*(char(*)[56])(abi_storage + 0))

    sango_resource_read_text(1, (uint8_t)error_kind + 0x2e & 0xff, error_text);
    sango_ui_show_message(error_text, 2);
    return;
}
#undef error_text

/* 原函数 0x81c16de8 */
int sango_resource_prepare_hook(uint32_t unused_callback_argument, int resource_offset)
{
    return g_resource_package_address + resource_offset;
}

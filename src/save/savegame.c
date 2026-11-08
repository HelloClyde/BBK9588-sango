#include "sango_internal.h"

/* 三个存档槽、双文件读取与写入。 */

/* 原函数 0x81c16330 */
/* 存取档共用三个槽；load_mode决定确认时读取还是写入。 */
uint32_t sango_save_choose_slot(char load_mode)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define event_kind (*(int *)(abi_storage + 0))
#define key_code (*(int *)(abi_storage + 4))

    uint32_t highlight_row;
    uint32_t slot;
    int highlight_bottom;
    int highlight_top_or_io_result;

    sango_save_draw_slots();
    slot = 0;
    sango_display_invert_rectangle(0x18, 0x74, 0x86, 0x80, 0);
    highlight_top_or_io_result = 0x74;
    highlight_bottom = 0x80;
    do
    {
        do
        {
            sango_input_next_event(&event_kind);
        } while (event_kind != 5);
        sango_display_invert_rectangle(0x18, (short)highlight_top_or_io_result, 0x86,
                                       (short)highlight_bottom, 0);
        if (key_code == 0x1c)
        {
            if (load_mode == '\0')
            {
                highlight_top_or_io_result = sango_save_write_slot((char)slot);
            }
            else
            {
                highlight_top_or_io_result = sango_save_load_slot((char)slot);
            }
            if (highlight_top_or_io_result != 0)
            {
                return slot & 0xff;
            }
            sango_save_draw_slots();
        }
        else if (key_code < 0x1d)
        {
            if (key_code == 1)
            {
                return 0xff;
            }
        }
        else if (key_code == 0x67)
        {
            slot = slot - 1;
            if (slot == 0xffffffff)
            {
                slot = 2;
            }
        }
        else if ((key_code == 0x6c) && (slot = slot + 1, slot == 3))
        {
            slot = 0;
        }
        slot = (int)slot % 3;
        highlight_row = slot * 0x1b + 0x22 & 0xff;
        highlight_bottom = highlight_row + 0x5e;
        highlight_top_or_io_result = highlight_row + 0x52;
        sango_display_invert_rectangle(0x18, (short)highlight_top_or_io_result, 0x86,
                                       (short)highlight_bottom, 0);
    } while (true);
}
#undef event_kind
#undef key_code

/* 原函数 0x81c164c8 */
void sango_save_draw_slots(void)
{
    unsigned char abi_storage[128] __attribute__((aligned(8)));
#define ruler_or_name_length (*(uint8_t(*)[8])(abi_storage + 0))
#define primary_file_digit (*(char *)(abi_storage + 31))
#define secondary_file_digit (*(char *)(abi_storage + 71))
#define saved_year (*(uint16_t(*)[4])(abi_storage + 104))
#define primary_path_or_summary (*(char(*)[10])(abi_storage + 8))
#define year_text_start (*(uint8_t(*)[13])(abi_storage + 18))
#define secondary_path (*(char(*)[23])(abi_storage + 48))
#define formatted_value (*(char(*)[16])(abi_storage + 88))

    char file_pair_offset;
    bool missing_save_pair;
    uint8_t original_scenario;
    void *file;
    void *file_00;
    uint32_t text_length;
    uint16_t slot_index;

    sango_bitmap_draw_resource(0x2e, 1, 0, 0, '\x01');
    original_scenario = g_scenario_id_view2;
    slot_index = 0;
    do
    {
        file_pair_offset = (char)slot_index * '\x02';
        sango_resource_read_text(1, 0x40, primary_path_or_summary);
        primary_file_digit = file_pair_offset + '0';
        file = bbk_fopen(primary_path_or_summary, &g_legacy_data_81c205e0);
        sango_resource_read_text(1, 0x40, secondary_path);
        secondary_file_digit = file_pair_offset + '1';
        file_00 = bbk_fopen(secondary_path, &g_legacy_data_81c205e0);
        missing_save_pair = false;
        if (file_00 == 0)
        {
            if (file != 0)
            {
                bbk_fclose(file);
            }
            sango_resource_read_text(1, 0x42, primary_path_or_summary);
            missing_save_pair = true;
        }
        if (file == 0)
        {
            if (file_00 != 0)
            {
                bbk_fclose(file_00);
            }
            sango_resource_read_text(1, 0x42, primary_path_or_summary);
            missing_save_pair = true;
        }
        if (!missing_save_pair)
        {
            bbk_fread(&g_scenario_id_view2, 1, 1, file);
            bbk_fread(ruler_or_name_length, 1, 1, file);
            bbk_fread(saved_year, 1, 2, file);
            bbk_fclose(file);
            bbk_fclose(file_00);
            sango_resource_read_text(1, 0x41, primary_path_or_summary);
            sango_load_named_text(ruler_or_name_length[0], formatted_value);
            text_length = bbk_strlen(formatted_value);
            ruler_or_name_length[0] = (uint8_t)text_length;
            bbk_memcpy(primary_path_or_summary, formatted_value, text_length & 0xff);
            sango_format_integer((uint32_t)saved_year[0], formatted_value, 10);
            text_length = bbk_strlen(formatted_value);
            bbk_memcpy(year_text_start, formatted_value, text_length + 1 & 0xff);
        }
        sango_text_draw_legacy(0x28, slot_index * 0x1b + 0x74, primary_path_or_summary);
        slot_index = slot_index + 1 & 0xff;
    } while (slot_index < 3);
    g_scenario_id_view2 = original_scenario;
    return;
}
#undef ruler_or_name_length
#undef primary_file_digit
#undef secondary_file_digit
#undef saved_year
#undef primary_path_or_summary
#undef year_text_start
#undef secondary_path
#undef formatted_value

/* 原函数 0x81c16704 */
/* 一个槽位包含两份文件：会话/城市/武将数据及进行中的战略命令。 */
uint32_t sango_save_load_slot(char slot)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define message_or_path (*(char(*)[23])(abi_storage + 0))
#define path_slot_digit (*(char *)(abi_storage + 23))

    void *file_handle;

    sango_resource_read_text(1, 0x44, message_or_path);
    sango_ui_show_message(message_or_path, 1);
    sango_resource_read_text(1, 0x40, message_or_path);
    path_slot_digit = slot * '\x02' + '0';
    file_handle = bbk_fopen(message_or_path, &g_legacy_data_81c205e0);
    if (file_handle != 0)
    {
        bbk_fread(&g_scenario_id_view2, 1, 1, file_handle);
        bbk_fread(&g_player_character, 1, 1, file_handle);
        bbk_fread(&g_current_year, 2, 1, file_handle);
        bbk_fread(&g_battle_render_enabled_view2, 1, 1, file_handle);
        bbk_fread(&g_battle_show_animations_view2, 1, 1, file_handle);
        bbk_fread(&g_battle_animate_movement_view2, 1, 1, file_handle);
        bbk_fread(&g_current_month, 1, 1, file_handle);
        bbk_fread(&g_strategy_viewport_x, 4, 1, file_handle);
        bbk_fread(g_character_table_address_view2, 0x10, 200, file_handle);
        bbk_fread(&g_city_character_roster, 1, 200, file_handle);
        bbk_fread(&g_city_item_roster, 1, 0x21, file_handle);
        bbk_fclose(file_handle);
        path_slot_digit = slot * '\x02' + '1';
        file_handle = bbk_fopen(message_or_path, &g_legacy_data_81c205e0);
        if (file_handle != 0)
        {
            bbk_fread(g_army_slot_used_address, 1, 0x1e, file_handle);
            bbk_fread(g_army_rosters_address, 10, 0x1e, file_handle);
            bbk_fread(g_order_queue_address, 0xc, 100, file_handle);
            bbk_fread(&g_first_city_status, 0x24, 0x26, file_handle);
            bbk_fclose(file_handle);
            return 1;
        }
    }
    sango_resource_read_text(1, 0x46, message_or_path);
    sango_ui_show_message(message_or_path, 2);
    return 0;
}
#undef message_or_path
#undef path_slot_digit

/* 原函数 0x81c16940 */
/* 保留原双文件存档路径和布局；不改变武将、城市或命令记录宽度。 */
uint32_t sango_save_write_slot(char slot)
{
    unsigned char abi_storage[84] __attribute__((aligned(8)));
#define path_slot_digit (*(char *)(abi_storage + 23))
#define alternate_slot_digit (*(char *)(abi_storage + 67))
#define message_or_path (*(char(*)[23])(abi_storage + 0))
#define alternate_path (*(uint8_t(*)[27])(abi_storage + 40))

    int directory_access_result;
    void *file_handle;
    char file_pair_offset;

    sango_resource_read_text(1, 0x43, message_or_path);
    sango_ui_show_message(message_or_path, 0);
    sango_resource_read_text(1, 0x40, message_or_path);
    sango_resource_read_text(1, 0x47, alternate_path);
    directory_access_result = bda_sango_fs_access((char *)0x81c205e4, 0);
    if (directory_access_result == -1)
    {
        bda_sango_fs_mkdir((char *)0x81c205e4);
    }
    directory_access_result = bda_sango_fs_access((char *)0x81c205f4, 0);
    if (directory_access_result == -1)
    {
        file_pair_offset = slot << 1;
        bda_sango_fs_mkdir((char *)0x81c205f4);
    }
    else
    {
        file_pair_offset = slot * '\x02';
    }
    path_slot_digit = file_pair_offset + '0';
    alternate_slot_digit = path_slot_digit;
    file_handle = bbk_fopen(message_or_path, &g_legacy_data_81c20608);
    if (file_handle != 0)
    {
        bbk_fwrite(&g_scenario_id_view2, 1, 1, file_handle);
        bbk_fwrite(&g_player_character, 1, 1, file_handle);
        bbk_fwrite(&g_current_year, 2, 1, file_handle);
        bbk_fwrite(&g_battle_render_enabled_view2, 1, 1, file_handle);
        bbk_fwrite(&g_battle_show_animations_view2, 1, 1, file_handle);
        bbk_fwrite(&g_battle_animate_movement_view2, 1, 1, file_handle);
        bbk_fwrite(&g_current_month, 1, 1, file_handle);
        bbk_fwrite(&g_strategy_viewport_x, 4, 1, file_handle);
        bbk_fwrite(g_character_table_address_view2, 0x10, 200, file_handle);
        bbk_fwrite(&g_city_character_roster, 1, 200, file_handle);
        bbk_fwrite(&g_city_item_roster, 1, 0x21, file_handle);
        bbk_fclose(file_handle);
        path_slot_digit = file_pair_offset + '1';
        file_handle = bbk_fopen(message_or_path, &g_legacy_data_81c20608);
        if (file_handle != 0)
        {
            bbk_fwrite(g_army_slot_used_address, 1, 0x1e, file_handle);
            bbk_fwrite(g_army_rosters_address, 10, 0x1e, file_handle);
            bbk_fwrite(g_order_queue_address, 0xc, 100, file_handle);
            bbk_fwrite(&g_first_city_status, 0x24, 0x26, file_handle);
            bbk_fclose(file_handle);
            return 1;
        }
    }
    sango_resource_read_text(1, 0x45, message_or_path);
    sango_ui_show_message(message_or_path, 2);
    return 0;
}
#undef path_slot_digit
#undef alternate_slot_digit
#undef message_or_path
#undef alternate_path

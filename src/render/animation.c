#include "sango_internal.h"

/* 五字节指令时间轴播放器。 */

/* 原函数 0x81c06a70 */
/* 时间轴每条5字节：x、y、存活时间、延迟、精灵索引；范围两端均包含。 */
uint32_t sango_animation_play_range(uint32_t resource_id, uint32_t first_command,
                                    uint32_t last_command, uint32_t play_flags, uint16_t origin_x,
                                    short origin_y)
{
    unsigned char abi_storage[86] __attribute__((aligned(8)));
    (*(uint16_t *)(abi_storage + 64)) = origin_x;
    (*(short *)(abi_storage + 68)) = origin_y;
#define last_drawn_index (*(uint32_t *)(abi_storage + 0))
#define origin_x (*(uint16_t *)(abi_storage + 64))
#define origin_y (*(short *)(abi_storage + 68))

    uint32_t range_end = last_command & 0xff;
    uint32_t range_begin = first_command & 0xff;
    int animation_address =
        sango_resource_item(resource_id & 0xffff, '\x01', g_resource_package_address);
    int sprite_table_address = g_scratch_buffer_address;
    bool needs_erase = true;
    bool needs_draw = true;
    if (animation_address == 0)
    {
        sango_debug_show_resource_id(resource_id & 0xffff);
        return 0xff;
    }

    sango_color_animation_begin(g_game_context);

    int commands_address = animation_address + 6;
    uint8_t sprite_count = *(uint8_t *)(animation_address + 3);
    int delays_address = g_scratch_buffer_address + 400;
    uint8_t *sprite_cursor =
        (uint8_t *)(commands_address + (uint32_t) * (uint8_t *)(animation_address + 2) * 5);
    uint8_t *lifetimes = (uint8_t *)(g_scratch_buffer_address + 500);

    /* 每条指令使用独立的延迟、存活计数；原有8位计数和包含末端的范围不变。 */
    uint32_t command_index = 0;
    if (-1 < (int)(range_end - range_begin))
    {
        do
        {
            int command_address = (command_index + range_begin) * 5 + commands_address;
            *(uint8_t *)(delays_address + command_index) = *(uint8_t *)(command_address + 3);
            uint8_t *lifetime_entry = lifetimes + command_index;
            command_index = command_index + 1 & 0xff;
            *lifetime_entry = *(uint8_t *)(command_address + 2);
        } while ((int)command_index <= (int)(range_end - range_begin));
    }

    /* 精灵在资源中紧邻排列，mask标志决定每帧是否附带第二个像素平面。 */
    uint32_t sprite_index = 0;
    if (sprite_count != 0)
    {
        do
        {
            uint8_t height_high = sprite_cursor[3];
            uint8_t height_low = sprite_cursor[2];
            uint32_t sprite_width = (uint32_t)sprite_cursor[1] * 0x100 + (uint32_t)*sprite_cursor;
            uint8_t bitmap_flags = sprite_cursor[5];
            int sprite_slot_offset = sprite_index * 4;
            sprite_index = sprite_index + 1 & 0xff;
            uint32_t row_bytes = (sprite_width & 0xffff) >> 2;
            if ((sprite_width & 3) != 0)
                row_bytes = row_bytes + 1;
            *(uint8_t **)(sprite_slot_offset + sprite_table_address) = sprite_cursor;
            uint32_t plane_bytes =
                row_bytes * ((uint32_t)height_high * 0x100 + (uint32_t)height_low & 0xffff) &
                0xffff;
            sprite_cursor =
                sprite_cursor + ((bitmap_flags & 1) * plane_bytes + plane_bytes + 6 & 0xffff);
        } while (sprite_index < sprite_count);
    }

    uint32_t active_end_index = 0;
    last_drawn_index = 0;
    do
    {
        uint32_t absolute_command;
        do
        {
            command_index = 0;
            uint8_t *lifetime_cursor = lifetimes;
            if ((play_flags & 1) != 0)
            {
                uint32_t key = sango_input_peek_key();
                if (key != 0xff)
                    return sango_color_animation_end(key);
            }

            /* 先擦除本拍到期的精灵，再减少计数；禁用擦除也要触发后续重绘。 */
            do
            {
                if (*lifetime_cursor == 1)
                {
                    uint8_t *command =
                        (uint8_t *)((command_index + range_begin) * 5 + commands_address);
                    needs_erase = true;
                    if ((play_flags & 2) == 0)
                    {
                        uint8_t *bitmap =
                            *(uint8_t **)((uint32_t)command[4] * 4 + sprite_table_address);
                        sango_color_animation_erase(
                            origin_x + *command, origin_y + (uint16_t)command[1],
                            origin_x + *command + (uint16_t)bitmap[1] * 0x100 + (uint16_t)*bitmap -
                                1,
                            origin_y + (uint16_t)command[1] + (uint16_t)bitmap[3] * 0x100 +
                                (uint16_t)bitmap[2] - 1,
                            g_game_context);
                    }
                }
                uint8_t remaining_lifetime = *lifetime_cursor;
                command_index = command_index + 1 & 0xff;
                if (remaining_lifetime != 0)
                    *lifetime_cursor = remaining_lifetime - 1;
                lifetime_cursor = lifetimes + command_index;
            } while (command_index <= active_end_index);

            if (needs_erase)
            {
                command_index = 0;
                do
                {
                    uint8_t *command =
                        (uint8_t *)((command_index + range_begin) * 5 + commands_address);
                    if (lifetimes[command_index] != 0)
                    {
                        uint8_t *bitmap =
                            *(uint8_t **)((uint32_t)command[4] * 4 + sprite_table_address);
                        uint32_t screen_x = (uint32_t)origin_x + (uint32_t)*command & 0xffff;
                        uint32_t sprite_width =
                            (uint32_t)bitmap[1] * 0x100 + (uint32_t)*bitmap & 0xffff;
                        uint32_t sprite_height =
                            (uint32_t)bitmap[3] * 0x100 + (uint32_t)bitmap[2] & 0xffff;
                        if ((bitmap[5] & 1) == 1)
                            sango_raster_draw_masked(screen_x, origin_y + (uint16_t)command[1],
                                                     sprite_width, sprite_height, (int)(bitmap + 6),
                                                     g_game_context);
                        else
                            sango_raster_draw_opaque(screen_x, origin_y + (uint16_t)command[1],
                                                     sprite_width, sprite_height, (int)(bitmap + 6),
                                                     g_game_context);
                    }
                    command_index = command_index + 1 & 0xff;
                } while (command_index <= last_drawn_index);
            }

            command_index = last_drawn_index;
            if (needs_draw)
            {
                while (command_index = command_index + 1 & 0xff,
                       last_drawn_index = active_end_index, command_index <= active_end_index)
                {
                    uint8_t *command =
                        (uint8_t *)((command_index + range_begin) * 5 + commands_address);
                    if (lifetimes[command_index] != 0)
                    {
                        uint8_t *bitmap =
                            *(uint8_t **)((uint32_t)command[4] * 4 + sprite_table_address);
                        uint32_t screen_x = (uint32_t)origin_x + (uint32_t)*command & 0xffff;
                        uint32_t sprite_width =
                            (uint32_t)bitmap[1] * 0x100 + (uint32_t)*bitmap & 0xffff;
                        uint32_t sprite_height =
                            (uint32_t)bitmap[3] * 0x100 + (uint32_t)bitmap[2] & 0xffff;
                        if ((bitmap[5] & 1) == 1)
                            sango_raster_draw_masked(screen_x, origin_y + (uint16_t)command[1],
                                                     sprite_width, sprite_height, (int)(bitmap + 6),
                                                     g_game_context);
                        else
                            sango_raster_draw_opaque(screen_x, origin_y + (uint16_t)command[1],
                                                     sprite_width, sprite_height, (int)(bitmap + 6),
                                                     g_game_context);
                    }
                }
            }

            if (needs_draw || needs_erase)
            {
                needs_draw = false;
                needs_erase = false;
                sango_render_present(g_game_context);
            }
            else
            {
                uint32_t input_result = sango_input_wait(1, '\x01');
                if (input_result != 0)
                    return sango_color_animation_end(input_result);
            }

            uint8_t *delay = (uint8_t *)(delays_address + active_end_index);
            uint8_t remaining_delay = *delay;
            if (remaining_delay != 0)
            {
                remaining_delay = remaining_delay - 1;
                *delay = remaining_delay;
            }
            absolute_command = active_end_index + range_begin;
            if ((remaining_delay < 2) && (absolute_command < range_end))
            {
                needs_draw = true;
                do
                {
                    active_end_index = active_end_index + 1 & 0xff;
                    absolute_command = active_end_index + range_begin;
                    if (1 < *(uint8_t *)(delays_address + active_end_index))
                        break;
                } while (absolute_command < range_end);
            }
        } while (absolute_command < range_end);

        /* 最后一条指令已进入播放，仍需等已激活精灵全部到期。 */
        command_index = 0;
        uint8_t *lifetime_cursor = lifetimes;
        while (*lifetime_cursor < 2)
        {
            command_index = command_index + 1 & 0xff;
            lifetime_cursor = lifetimes + command_index;
            if (active_end_index < command_index)
                return sango_color_animation_end(0xff);
        }
    } while (command_index <= active_end_index);
    return sango_color_animation_end(0xff);
}
#undef last_drawn_index
#undef origin_x
#undef origin_y

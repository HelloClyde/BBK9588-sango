#include "sango_internal.h"

/* 地形成本、移动范围与可达位置。 */

/* 原函数 0x81c003b8 */
void sango_battle_build_move_range(uint32_t unit_id)
{
    unsigned char abi_storage[76] __attribute__((aligned(8)));
#define frontier_b (*(uint8_t(*)[24])(abi_storage + 24))
#define frontier_a (*(uint8_t(*)[24])(abi_storage + 0))
#define frontier_a_count (*(uint8_t *)(abi_storage + 48))
#define frontier_b_count (*(uint8_t(*)[3])(abi_storage + 49))
#define origin_cell (*(uint32_t *)(abi_storage + 52))
#define unit_stride_base (*(int *)(abi_storage + 56))

    uint8_t next_frontier_count;
    uint8_t *frontier_entry;
    int move_costs_address;
    uint32_t frontier_index;
    uint32_t frontier_count;
    uint8_t *current_frontier;
    uint8_t *next_count_address;
    uint8_t *next_frontier;
    uint32_t unit_index;

    unit_index = unit_id & 0xff;
    sango_battle_copy_move_window(unit_index);
    unit_stride_base = unit_index << 3;
    sango_battle_load_movement_costs(unit_index);
    frontier_a[0] = (&g_first_unit_move_range)[unit_stride_base - unit_index] * '\x10' - 0x10;
    origin_cell = (uint32_t)frontier_a[0];
    frontier_a_count = 1;
    frontier_b_count[0] = 0;
    frontier_count = 1;
    move_costs_address = g_move_costs_address;
    current_frontier = frontier_a;
    next_count_address = frontier_b_count;
    next_frontier = frontier_b;
    do
    {
        frontier_index = 0;
        frontier_entry = current_frontier;
        if (frontier_count != 0)
        {
            do
            {
                if (1 < *(uint8_t *)(move_costs_address + (uint32_t)*frontier_entry))
                {
                    sango_battle_mark_blocked_positions((uint32_t)*frontier_entry,
                                                        (int)next_frontier, next_count_address);
                    move_costs_address = g_move_costs_address;
                }
                frontier_index = frontier_index + 1 & 0xff;
                frontier_entry = current_frontier + frontier_index;
            } while (frontier_index < frontier_count);
        }
        if (current_frontier == frontier_a)
        {
            next_count_address = &frontier_a_count;
            frontier_a_count = 0;
            current_frontier = frontier_b;
            next_frontier = frontier_a;
            next_frontier_count = frontier_b_count[0];
        }
        else
        {
            frontier_b_count[0] = 0;
            current_frontier = frontier_a;
            next_count_address = frontier_b_count;
            next_frontier = frontier_b;
            next_frontier_count = frontier_a_count;
        }
        frontier_count = (uint32_t)next_frontier_count;
    } while (frontier_count != 0);
    *(uint8_t *)(move_costs_address + origin_cell) = 0;
    sango_battle_expand_reachable_tiles(unit_index);
    if ((&g_first_unit_status)[unit_stride_base - unit_index] == '\x04')
    {
        sango_battle_relax_move_costs(unit_index);
    }
    return;
}
#undef frontier_b
#undef frontier_a
#undef frontier_a_count
#undef frontier_b_count
#undef origin_cell
#undef unit_stride_base

/* 原函数 0x81c00558 */
void sango_battle_copy_move_window(uint32_t unit_id)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
#define window_left (*(uint32_t *)(abi_storage + 0))

    int unit_or_map_address;
    uint32_t range_or_destination_offset;
    uint32_t unit_x_or_copy_height;
    uint32_t unit_y_or_source_offset;
    uint32_t row_index;
    uint32_t copy_width;
    uint32_t source_top;
    uint32_t source_left;
    uint32_t window_top;

    sango_memory_fill(g_move_costs_address_view2, 0xff, 0xe1);
    unit_or_map_address = (unit_id & 0xff) * 7;
    range_or_destination_offset =
        (uint32_t)(uint8_t)(&g_first_unit_move_range)[unit_or_map_address];
    unit_x_or_copy_height = (uint8_t)(&g_first_unit_x)[unit_or_map_address] + 1 & 0xff;
    unit_y_or_source_offset = (uint8_t)(&g_first_unit_y)[unit_or_map_address] + 1 & 0xff;
    if (unit_x_or_copy_height < range_or_destination_offset)
    {
        window_left = range_or_destination_offset - unit_x_or_copy_height & 0xff;
        source_left = 0;
    }
    else
    {
        source_left = unit_x_or_copy_height - range_or_destination_offset & 0xff;
        window_left = 0;
    }
    if (unit_y_or_source_offset < range_or_destination_offset)
    {
        window_top = range_or_destination_offset - unit_y_or_source_offset & 0xff;
        source_top = 0;
    }
    else
    {
        source_top = unit_y_or_source_offset - range_or_destination_offset & 0xff;
        window_top = 0;
    }
    copy_width = range_or_destination_offset - window_left & 0xff;
    if ((int)range_or_destination_offset < (int)(g_battle_map_width - unit_x_or_copy_height))
    {
        copy_width = (copy_width + range_or_destination_offset) - 1;
    }
    else
    {
        copy_width = copy_width + (g_battle_map_width - unit_x_or_copy_height);
    }
    unit_x_or_copy_height = range_or_destination_offset - window_top & 0xff;
    if ((int)range_or_destination_offset < (int)(g_battle_map_height - unit_y_or_source_offset))
    {
        unit_x_or_copy_height = (unit_x_or_copy_height + range_or_destination_offset) - 1;
    }
    else
    {
        unit_x_or_copy_height =
            unit_x_or_copy_height + (g_battle_map_height - unit_y_or_source_offset);
    }
    unit_or_map_address =
        sango_resource_item((uint32_t)g_battle_map_resource, '\x01', g_resource_package_address);
    row_index = 0;
    unit_y_or_source_offset = source_top * g_battle_map_width + source_left;
    range_or_destination_offset = window_top * 0xf + window_left;
    if ((unit_x_or_copy_height & 0xff) != 0)
    {
        do
        {
            bbk_memcpy(
                (void *)((int)g_move_costs_address_view2 + (range_or_destination_offset & 0xffff)),
                (void *)(unit_or_map_address + 0x10 + (unit_y_or_source_offset & 0xffff)),
                copy_width & 0xff);
            row_index = row_index + 1 & 0xff;
            unit_y_or_source_offset =
                (unit_y_or_source_offset & 0xffff) + (uint32_t)g_battle_map_width;
            range_or_destination_offset = (range_or_destination_offset & 0xffff) + 0xf;
        } while (row_index < (unit_x_or_copy_height & 0xff));
    }
    g_move_source_x = (char)source_left;
    g_move_source_y = (char)source_top;
    g_move_window_top = (char)window_top;
    g_move_window_left = (char)window_left;
    return;
}
#undef window_left

/* 原函数 0x81c00784 */
void sango_battle_load_movement_costs(uint32_t unit_id)
{
    uint8_t troop_type;
    int movement_table_address;
    uint32_t terrain_id;
    uint8_t *cost_entry;
    uint32_t cell_index;
    uint32_t unit_index;

    unit_index = unit_id & 0xff;
    troop_type = *(uint8_t *)((uint32_t)(uint8_t)(&g_battle_roster_first)[unit_index] * 0x10 +
                              g_character_table_address + -7);
    movement_table_address = sango_resource_item(2, '\x03', g_resource_package_address);
    cell_index = 0;
    do
    {
        cost_entry = (uint8_t *)(g_move_costs_address + cell_index);
        terrain_id = (uint32_t)*cost_entry;
        cell_index = cell_index + 1 & 0xff;
        if (terrain_id != 0xff)
        {
            *cost_entry =
                *(uint8_t *)(movement_table_address + (uint32_t)troop_type * 0x2e + terrain_id);
        }
    } while (cell_index < 0xe1);
    sango_battle_relax_move_costs(unit_index);
    *(uint8_t *)(g_move_costs_address +
                 (((uint8_t)(&g_first_unit_move_range)[unit_index * 7] - 1) * 0x10 & 0xf0)) =
        (&g_first_unit_move_range)[unit_index * 7];
    return;
}

/* 原函数 0x81c00870 */
void sango_battle_expand_reachable_tiles(uint32_t unit_id)
{
    int unit_offset;
    uint8_t window_x;
    uint8_t window_y;
    uint32_t other_unit;
    char window_origin_y;
    char window_origin_x;
    uint32_t cell_index;
    uint32_t side_end;

    window_origin_x = g_move_source_x_view2 - g_move_window_left_view2;
    other_unit = 10;
    window_origin_y = g_move_source_y_view2 - g_move_window_top_view2;
    if ((unit_id & 0xff) < 10)
    {
        other_unit = 0;
    }
    side_end = other_unit + 10;
    do
    {
        unit_offset = other_unit * 7;
        if (((&g_first_unit_status)[unit_offset] != '\b') && ((unit_id & 0xff) != other_unit))
        {
            window_x = (&g_first_unit_x)[unit_offset] - window_origin_x;
            window_y = (&g_first_unit_y)[unit_offset] - window_origin_y;
            if ((window_x < 0x10) &&
                ((window_y < 0x10 &&
                  (cell_index = (uint32_t)(uint8_t)(window_y * '\x0f' + window_x),
                   cell_index < 0xe1))))
            {
                *(uint8_t *)(g_move_costs_address + cell_index) = 0xfe;
            }
        }
        other_unit = other_unit + 1 & 0xff;
    } while (other_unit < side_end);
    return;
}

/* 原函数 0x81c00954 */
void sango_battle_relax_move_costs(uint32_t unit_id)
{
    int unit_offset;
    uint8_t window_x;
    uint8_t window_y;
    uint32_t other_unit;
    char window_origin_y;
    char window_origin_x;
    uint32_t cell_index;
    uint32_t side_end;

    window_origin_x = g_move_source_x_view2 - g_move_window_left_view2;
    other_unit = 10;
    if (9 < (unit_id & 0xff))
    {
        other_unit = 0;
    }
    window_origin_y = g_move_source_y_view2 - g_move_window_top_view2;
    side_end = other_unit + 10;
    do
    {
        unit_offset = other_unit * 7;
        if ((&g_first_unit_status)[unit_offset] != '\b')
        {
            window_x = (&g_first_unit_x)[unit_offset] - window_origin_x;
            window_y = (&g_first_unit_y)[unit_offset] - window_origin_y;
            if ((((window_x < 0x10) && (window_y < 0x10)) &&
                 (cell_index = (uint32_t)(uint8_t)(window_y * '\x0f' + window_x),
                  cell_index < 0xe1)) &&
                (*(uint8_t *)(g_move_costs_address + cell_index) = 0xfe,
                 (&g_first_unit_status)[(unit_id & 0xff) * 7] != '\x04'))
            {
                if ((window_x != 0) && (1 < cell_index))
                {
                    *(uint8_t *)(g_move_costs_address + cell_index + -1) =
                        *(uint8_t *)(g_move_costs_address + cell_index + -1) | 0xa0;
                }
                if ((window_x < 0xe) && (cell_index < 0xe0))
                {
                    *(uint8_t *)(g_move_costs_address + cell_index + 1) =
                        *(uint8_t *)(g_move_costs_address + cell_index + 1) | 0xa0;
                }
                if ((window_y != 0) && (0xe < cell_index))
                {
                    *(uint8_t *)(g_move_costs_address + cell_index + -0xf) =
                        *(uint8_t *)(g_move_costs_address + cell_index + -0xf) | 0xa0;
                }
                if ((window_y < 0xe) && (cell_index < 0xd1))
                {
                    *(uint8_t *)(g_move_costs_address + cell_index + 0xf) =
                        *(uint8_t *)(g_move_costs_address + cell_index + 0xf) | 0xa0;
                }
            }
        }
        other_unit = other_unit + 1 & 0xff;
    } while (other_unit < side_end);
    return;
}

/* 原函数 0x81c00b18 */
void sango_battle_mark_blocked_positions(uint32_t source_cell, int next_frontier_address,
                                         uint8_t *next_count_address)
{
    uint8_t remaining_movement;
    uint8_t neighbor_cost;
    char next_movement;
    uint32_t neighbor_offset;
    uint8_t *next_frontier_entry;
    uint32_t neighbor_cell;
    uint32_t direction_index;
    uint8_t biased_movement;
    uint32_t next_count;

    next_count = (uint32_t)*next_count_address;
    remaining_movement = *(uint8_t *)(g_move_costs_address + (source_cell & 0xff));
    direction_index = 0;
    do
    {
        neighbor_offset =
            (source_cell & 0xff) + (uint32_t)(uint8_t)(&g_legacy_data_81c200a8)[direction_index];
        neighbor_cell = neighbor_offset & 0xff;
        if ((((neighbor_cell < 0xe1) &&
              (neighbor_cost = *(uint8_t *)(g_move_costs_address + neighbor_cell),
               (char)*(uint8_t *)(g_move_costs_address + neighbor_cell) < '\0')) &&
             (neighbor_cost != 0xfe)) &&
            (neighbor_cost != 0xff))
        {
            if ((neighbor_cost < 0xa1) ||
                (next_movement = '\x01', remaining_movement <= (uint8_t)(neighbor_cost + 0x60)))
            {
                biased_movement = remaining_movement + 0x80;
                next_movement = biased_movement - neighbor_cost;
                if (biased_movement <= neighbor_cost)
                {
                    next_movement = '\0';
                }
                if (next_movement == '\0')
                    goto next_direction;
            }
            next_frontier_entry = (uint8_t *)(next_frontier_address + next_count);
            *(char *)(g_move_costs_address + neighbor_cell) = next_movement;
            next_count = next_count + 1 & 0xff;
            *next_frontier_entry = (char)neighbor_offset;
        }
    next_direction:
        direction_index = direction_index + 1 & 0xff;
        if (3 < direction_index)
        {
            *next_count_address = (uint8_t)next_count;
            return;
        }
    } while (true);
}

#include "sango_internal.h"

/* 电脑部队行动与目标选择。 */

/* 原函数 0x81c017a0 */
uint32_t sango_battle_ai_plan_unit(uint8_t *action)
{
    uint32_t unit_id;
    int skill_chosen;
    uint32_t attack_chosen;

    unit_id = sango_battle_select_ai_unit();
    if (unit_id != 0xff)
    {
        action[2] = (char)unit_id;
        sango_battle_build_move_range(unit_id);
        if (g_battle_render_enabled != '\0')
        {
            sango_battle_redraw_field(unit_id);
            sango_battle_draw_move_range();
            sango_battle_blink_unit(unit_id, 1);
            sango_render_present(g_game_context);
            if (g_battle_animate_movement != '\0')
            {
                sango_input_wait(0x32, '\0');
            }
        }
        sango_battle_ai_choose_destination(unit_id);
        if ((g_battle_render_enabled != '\0') &&
            (sango_battle_redraw_field(unit_id), g_battle_animate_movement != '\0'))
        {
            sango_input_wait(0x32, '\0');
        }
        skill_chosen = sango_battle_ai_choose_skill(action);
        if ((skill_chosen == 0) &&
            (attack_chosen = sango_battle_ai_prepare_attack(action), attack_chosen == 0))
        {
            *action = 3;
        }
    }
    return unit_id;
}

/* 原函数 0x81c018b0 */
uint32_t sango_battle_ai_choose_skill(uint8_t *action)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define skill_ids (*(uint8_t(*)[16])(abi_storage + 0))

    uint8_t chosen_skill;
    uint32_t character_or_skill_id;
    uint32_t decision_roll_or_in_range;
    uint32_t capacity_or_random_roll;
    uint32_t troop_roll_limit;
    uint32_t actor_or_target_unit;
    int character_or_target_address;

    actor_or_target_unit = (uint32_t)(uint8_t)action[2];
    if ((&g_first_unit_status)[actor_or_target_unit * 7] != '\x02')
    {
        character_or_skill_id = sango_battle_is_player_unit(actor_or_target_unit);
        character_or_target_address = g_character_table_address + character_or_skill_id * 0x10;
        decision_roll_or_in_range = bbk_rand();
        if ((decision_roll_or_in_range & 0xffff) % 0x96 <=
            (uint32_t) * (uint8_t *)(character_or_target_address + 4))
        {
            if (*(char *)(character_or_target_address + 9) != '\x05')
            {
                capacity_or_random_roll = sango_character_troop_capacity(character_or_skill_id);
                troop_roll_limit =
                    capacity_or_random_roll + (capacity_or_random_roll >> 1) & 0xffff;
                capacity_or_random_roll = bbk_rand();
                if (troop_roll_limit == 0)
                {
                    sango_legacy_trap(7);
                }
                if ((int)capacity_or_random_roll % (int)troop_roll_limit <
                    (int)(uint32_t) * (uint16_t *)(character_or_target_address + 10))
                {
                    return 0;
                }
            }
            sango_battle_collect_unit_skills(character_or_skill_id, (char *)skill_ids);
            character_or_skill_id = sango_crt_strlen((char *)skill_ids);
            if (character_or_skill_id == 0)
            {
                sango_legacy_trap(7);
            }
            chosen_skill =
                skill_ids[(decision_roll_or_in_range & 0xffff) % character_or_skill_id & 0xff];
            character_or_skill_id = (uint32_t)chosen_skill;
            character_or_target_address =
                sango_battle_skill_target_allowed(character_or_skill_id, actor_or_target_unit);
            if (character_or_target_address == 0)
            {
                sango_battle_load_range_template('\x01', character_or_skill_id,
                                                 actor_or_target_unit);
                actor_or_target_unit = 0;
                character_or_target_address = 0;
                do
                {
                    character_or_target_address =
                        character_or_target_address - actor_or_target_unit;
                    if ((&g_first_unit_status)[character_or_target_address] != '\b')
                    {
                        decision_roll_or_in_range = sango_battle_target_in_skill_range(
                            (uint32_t)(uint8_t)(&g_first_unit_x)[character_or_target_address],
                            (uint32_t)(uint8_t)(&g_first_unit_y)[character_or_target_address]);
                        if ((decision_roll_or_in_range != 0) &&
                            (character_or_target_address = sango_battle_skill_terrain_allowed(
                                 character_or_skill_id, 9 < actor_or_target_unit,
                                 actor_or_target_unit),
                             character_or_target_address != 0))
                        {
                            if ((character_or_skill_id != 0x11) && (character_or_skill_id != 0x1d))
                            {
                                action[1] = chosen_skill;
                                *action = 1;
                                action[3] = (char)actor_or_target_unit;
                                return 1;
                            }
                            sango_character_troop_capacity(
                                (uint8_t)(&g_battle_roster_first)[actor_or_target_unit] - 1 & 0xff);
                        }
                    }
                    actor_or_target_unit = actor_or_target_unit + 1 & 0xff;
                    character_or_target_address = actor_or_target_unit << 3;
                } while (actor_or_target_unit < 0x14);
            }
        }
    }
    return 0;
}
#undef skill_ids

/* 原函数 0x81c01af0 */
uint32_t sango_battle_ai_prepare_attack(uint8_t *action)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define target_unit (*(char(*)[2])(abi_storage + 0))
#define damage_estimate (*(uint16_t(*)[3])(abi_storage + 2))

    uint8_t actor_unit;

    actor_unit = action[2];
    sango_battle_load_range_template('\0', 0, (uint32_t)actor_unit);
    sango_battle_prepare_combatant(0, (uint32_t)actor_unit);
    sango_battle_select_combat_target(damage_estimate, target_unit);
    if (target_unit[0] != -1)
    {
        action[3] = target_unit[0];
        *action = 0;
    }
    return (uint32_t)(target_unit[0] != -1);
}
#undef target_unit
#undef damage_estimate

/* 原函数 0x81c01b68 */
void sango_battle_ai_choose_destination(uint32_t unit_id)
{
    unsigned char abi_storage[44] __attribute__((aligned(8)));
#define best_distance (*(uint32_t *)(abi_storage + 16))
#define best_x (*(uint32_t *)(abi_storage + 20))
#define unit_stride_base (*(int *)(abi_storage + 24))
#define combat_target (*(uint8_t(*)[2])(abi_storage + 2))
#define objective_x (*(uint8_t *)(abi_storage + 0))
#define objective_y (*(uint8_t *)(abi_storage + 1))
#define attack_score (*(uint16_t(*)[2])(abi_storage + 4))
#define original_x (*(uint32_t *)(abi_storage + 8))
#define original_y (*(uint32_t *)(abi_storage + 12))

    uint16_t candidate_score;
    uint32_t chosen_x;
    uint32_t window_x;
    uint32_t chosen_y_or_roll;
    int terrain_type;
    uint32_t candidate_distance;
    uint32_t tie_break;
    uint32_t distance_from_origin;
    uint32_t best_origin_distance;
    uint32_t chosen_distance;
    uint8_t candidate_x_byte;
    uint8_t candidate_y_byte;
    uint32_t window_y;
    uint32_t candidate_y;
    uint32_t candidate_x;
    uint32_t unit_index;
    uint16_t best_attack_score;
    uint8_t best_y_byte;
    uint32_t best_y;

    unit_index = unit_id & 0xff;
    window_x = sango_battle_unit_terrain(unit_index);
    if (window_x != 5)
    {
        unit_stride_base = unit_index << 3;
        sango_battle_distance_components(&objective_x, &objective_y);
        best_attack_score = 0;
        original_y = (uint32_t)(uint8_t)(&g_first_unit_y)[unit_stride_base - unit_index];
        original_x = (uint32_t)(uint8_t)(&g_first_unit_x)[unit_stride_base - unit_index];
        sango_battle_is_player_unit(unit_index);
        best_distance = 0xff;
        best_y_byte = (uint8_t)original_y;
        best_x = original_x;
        best_y = original_y;
        for (window_x = (uint32_t)g_move_window_left; window_x < 0xf;
             window_x = window_x + 1 & 0xff)
        {
            for (window_y = (uint32_t)g_move_window_top;
                 best_y_byte = (uint8_t)best_y, window_y < 0xf; window_y = window_y + 1 & 0xff)
            {
                if (-1 < *(char *)(g_move_costs_address + window_y * 0xf + window_x))
                {
                    chosen_distance = (uint32_t)g_move_source_x + (window_x - g_move_window_left);
                    chosen_y_or_roll = (uint32_t)g_move_source_y + (window_y - g_move_window_top);
                    candidate_x = chosen_distance & 0xff;
                    candidate_y = chosen_y_or_roll & 0xff;
                    terrain_type = sango_battle_terrain_at(candidate_x, candidate_y);
                    candidate_x_byte = (uint8_t)chosen_distance;
                    candidate_y_byte = (uint8_t)chosen_y_or_roll;
                    if ((g_battle_control_mode == '\0') && (terrain_type == 5))
                    {
                        (&g_first_unit_y)[unit_stride_base - unit_index] = candidate_y_byte;
                        (&g_first_unit_x)[unit_stride_base - unit_index] = candidate_x_byte;
                        sango_battle_redraw_field(unit_index);
                        return;
                    }
                    candidate_distance = sango_battle_manhattan_distance(
                        candidate_x_byte, candidate_y_byte, objective_x, objective_y);
                    sango_battle_preview_skill_range(unit_index, candidate_x_byte,
                                                     candidate_y_byte);
                    sango_battle_select_combat_target(attack_score, combat_target);
                    candidate_score = attack_score[0];
                    chosen_y_or_roll = candidate_y;
                    chosen_distance = candidate_distance;
                    chosen_x = candidate_x;
                    if (best_attack_score == 0)
                    {
                        if (((attack_score[0] == 0) && (best_distance <= candidate_distance)) &&
                            (chosen_y_or_roll = best_y, chosen_distance = best_distance,
                             chosen_x = best_x, best_distance == candidate_distance))
                        {
                            chosen_y_or_roll = bbk_rand();
                            tie_break = (int)chosen_y_or_roll % 10 & 0xff;
                            best_attack_score = candidate_score;
                        consider_tied_candidate:
                            chosen_y_or_roll = candidate_y;
                            chosen_distance = candidate_distance;
                            chosen_x = candidate_x;
                            if (tie_break == 0)
                                goto next_candidate;
                        }
                    }
                    else
                    {
                        if (attack_score[0] < best_attack_score)
                            goto next_candidate;
                        if ((attack_score[0] <= best_attack_score) &&
                            (4 < (terrain_type - 2U & 0xff)))
                        {
                            distance_from_origin = sango_battle_manhattan_distance(
                                candidate_x_byte, candidate_y_byte, (uint8_t)original_x,
                                (uint8_t)original_y);
                            best_origin_distance = sango_battle_manhattan_distance(
                                (uint8_t)best_x, best_y_byte, (uint8_t)original_x,
                                (uint8_t)original_y);
                            tie_break = 0;
                            if (distance_from_origin <= best_origin_distance)
                                goto consider_tied_candidate;
                        }
                    }
                    best_x = chosen_x;
                    best_distance = chosen_distance;
                    best_y = chosen_y_or_roll;
                    best_attack_score = attack_score[0];
                }
            next_candidate:
            }
        }
        if (best_distance != 0xff)
        {
            (&g_first_unit_y)[unit_stride_base - unit_index] = best_y_byte;
            (&g_first_unit_x)[unit_stride_base - unit_index] = (char)best_x;
        }
    }
    return;
}
#undef best_distance
#undef best_x
#undef unit_stride_base
#undef combat_target
#undef objective_x
#undef objective_y
#undef attack_score
#undef original_x
#undef original_y

/* 原函数 0x81c01e74 */
uint32_t sango_battle_choose_skill(uint32_t unit_id, uint16_t *menu_bounds, uint8_t *skill_buffer)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define error_text (*(char(*)[16])(abi_storage + 0))

    uint8_t skill_id;
    uint16_t original_right_or_top;
    uint16_t original_left;
    uint32_t character_count_or_selection;
    uint16_t shifted_right;

    character_count_or_selection = sango_battle_is_player_unit(unit_id & 0xff);
    sango_battle_collect_unit_skills(character_count_or_selection, (char *)skill_buffer);
    sango_battle_load_skill_names(skill_buffer);
    character_count_or_selection = bbk_strlen((char *)(skill_buffer + 0xb));
    original_right_or_top = menu_bounds[2];
    original_left = *menu_bounds;
    shifted_right = original_right_or_top + 4;
    character_count_or_selection = character_count_or_selection >> 2 & 0xff;
    *menu_bounds = original_left + 4;
    menu_bounds[2] = shifted_right;
    if (0xd3 < shifted_right)
    {
        *menu_bounds = original_left - 0x14;
        menu_bounds[2] = original_right_or_top - 0x14;
    }
    original_right_or_top = menu_bounds[1];
    menu_bounds[3] = menu_bounds[3] - 6;
    menu_bounds[1] = original_right_or_top + 6;
    if (character_count_or_selection < 3)
    {
        menu_bounds[3] = original_right_or_top + 6 + (short)character_count_or_selection * 0xc;
    }
    while (true)
    {
        character_count_or_selection =
            sango_ui_choose_option(menu_bounds, 0, (char *)(skill_buffer + 0xb));
        if (character_count_or_selection == 0xff)
        {
            return 0xff;
        }
        skill_id = skill_buffer[character_count_or_selection];
        character_count_or_selection =
            sango_battle_skill_target_allowed((uint32_t)skill_id, unit_id & 0xff);
        if (character_count_or_selection == 0)
            break;
        sango_battle_load_overview_text(character_count_or_selection, error_text);
        sango_battle_status_draw_description(error_text, 0);
    }
    return (uint32_t)skill_id;
}
#undef error_text

/* 原函数 0x81c01fbc */
uint32_t sango_battle_skill_target_allowed(uint32_t skill_id, uint32_t unit_id)
{
    uint32_t actor_terrain;
    int parameters_address;
    uint32_t error_text_id;

    actor_terrain = sango_battle_unit_terrain(unit_id & 0xff);
    parameters_address = sango_battle_skill_parameters(skill_id & 0xff);
    error_text_id = 6;
    if (((*(uint8_t *)(parameters_address + 6) <=
          (uint8_t)(&g_first_unit_energy)[(unit_id & 0xff) * 7]) &&
         (error_text_id = 5, *(char *)(actor_terrain + parameters_address + 0x14) != '\0')) &&
        (error_text_id = 4, *(char *)((uint32_t)g_battle_weather + parameters_address + 6) != '\0'))
    {
        error_text_id = 0;
    }
    return error_text_id;
}

/* 原函数 0x81c0205c */
void sango_battle_collect_unit_skills(uint32_t character_id, char *skill_ids)
{
    char skills_per_level;
    int skill_table_address;
    uint32_t level_bits;
    uint32_t character_or_skill_count;
    uint32_t troop_type;
    int character_address;

    sango_memory_fill(skill_ids, 0, 0xb);
    character_or_skill_count = character_id & 0xff;
    skill_table_address = sango_resource_item(0xe, g_scenario_id, g_resource_package_address);
    if (*(char *)(skill_table_address + character_or_skill_count) != '\0')
    {
        *skill_ids = *(char *)(skill_table_address + character_or_skill_count);
        skill_ids = skill_ids + 1;
    }
    if ((uint32_t) * (uint8_t *)(character_or_skill_count * 0x10 + g_character_table_address + 1) ==
        character_or_skill_count + 1)
    {
        *skill_ids = '\x1e';
        skill_ids = skill_ids + 1;
    }
    skill_table_address = sango_resource_item(2, '\x02', g_resource_package_address);
    character_address = character_or_skill_count * 0x10 + g_character_table_address;
    troop_type = (uint32_t) * (uint8_t *)(character_address + 9);
    skills_per_level = (&g_legacy_data_81c200bc)[troop_type];
    character_or_skill_count = sango_soft_int_to_f32((int)skills_per_level);
    if (skills_per_level < 0)
    {
        character_or_skill_count = soft_float_add(character_or_skill_count, g_legacy_data_81c20c4c);
    }
    level_bits = sango_soft_int_to_f32((uint32_t) * (uint8_t *)(character_address + 2));
    character_or_skill_count = soft_float_mul(character_or_skill_count, level_bits);
    character_or_skill_count = soft_float_div(character_or_skill_count, g_legacy_data_81c20c54);
    character_or_skill_count = soft_float_add(character_or_skill_count, g_legacy_data_81c20c58);
    character_or_skill_count = sango_soft_f32_to_int(character_or_skill_count);
    bbk_memcpy(skill_ids, (void *)(skill_table_address + troop_type * 10),
               character_or_skill_count & 0xff);
    return;
}

/* 原函数 0x81c021d4 */
void sango_battle_load_skill_names(uint8_t *skill_buffer)
{
    uint8_t *skill_entry;
    uint8_t *name_destination;
    uint32_t skill_index;

    skill_index = 0;
    skill_entry = skill_buffer;
    name_destination = skill_buffer + 0xb;
    do
    {
        if (*skill_entry == 0)
        {
            return;
        }
        sango_resource_read_text(0xb, (uint32_t)*skill_entry, name_destination);
        skill_index = skill_index + 1 & 0xff;
        skill_entry = skill_buffer + skill_index;
        name_destination = name_destination + 4;
    } while (skill_index < 10);
    return;
}

/* 原函数 0x81c02244 */
uint32_t sango_battle_skill_terrain_allowed(uint32_t skill_id, char target_side,
                                            uint32_t target_unit)
{
    uint8_t target_troop_type;
    uint32_t target_terrain;
    char *skill_parameters;
    uint32_t allowed;

    target_troop_type =
        *(uint8_t *)((uint32_t)(uint8_t)(&g_battle_roster_first)[target_unit & 0xff] * 0x10 +
                     g_character_table_address + -7);
    target_terrain = sango_battle_unit_terrain(target_unit & 0xff);
    skill_parameters = (char *)sango_battle_skill_parameters(skill_id & 0xff);
    allowed = 0;
    if ((((skill_parameters[target_troop_type + 0x1c] != '\0') &&
          (skill_parameters[target_terrain + 0xc] != '\0')) &&
         ((*skill_parameters != '\x01' || (target_side != '\0')))) &&
        ((*skill_parameters != '\0' || (target_side == '\0'))))
    {
        allowed = 1;
    }
    return allowed;
}

/* 原函数 0x81c02314 */
uint32_t sango_battle_unit_terrain(uint32_t index)
{
    int unit_offset;
    uint32_t terrain;

    unit_offset = (index & 0xff) * 7;
    terrain = sango_battle_terrain_at((uint32_t)(uint8_t)(&g_first_unit_x)[unit_offset],
                                      (uint32_t)(uint8_t)(&g_first_unit_y)[unit_offset]);
    return terrain;
}

/* 原函数 0x81c02354 */
void sango_battle_select_combat_target(uint16_t *damage_estimate, uint8_t *target_unit)
{
    int unit_stride_base;
    uint32_t in_range_or_damage;
    uint32_t candidate_unit;
    uint32_t best_damage;
    uint32_t best_target;

    best_target = 0xff;
    best_damage = 0;
    candidate_unit = 0;
    unit_stride_base = 0;
    do
    {
        unit_stride_base = unit_stride_base - candidate_unit;
        if (((&g_first_unit_status)[unit_stride_base] != '\b') &&
            (in_range_or_damage = sango_battle_target_in_skill_range(
                 (uint32_t)(uint8_t)(&g_first_unit_x)[unit_stride_base],
                 (uint32_t)(uint8_t)(&g_first_unit_y)[unit_stride_base]),
             in_range_or_damage != 0))
        {
            if (g_battle_player_unit_begin == candidate_unit)
            {
                best_damage = 0xffff;
                best_target = candidate_unit;
                break;
            }
            sango_battle_prepare_combatant(1, candidate_unit);
            in_range_or_damage = sango_battle_roll_attack_damage();
            if (best_damage < in_range_or_damage)
            {
                best_damage = in_range_or_damage;
                best_target = candidate_unit;
            }
        }
        candidate_unit = candidate_unit + 1 & 0xff;
        unit_stride_base = candidate_unit << 3;
    } while (candidate_unit < 10);
    *damage_estimate = (short)best_damage;
    *target_unit = (char)best_target;
    return;
}

/* 原函数 0x81c02444 */
uint32_t sango_battle_target_in_skill_range(int map_x, int map_y)
{
    uint32_t in_range;
    uint32_t template_x;
    uint32_t template_y;
    uint32_t template_width;

    template_width = (uint32_t)*g_temp_character_ids_address;
    template_y = map_y - (uint32_t)g_temp_character_ids_address[2] & 0xff;
    template_x = map_x - (uint32_t)g_temp_character_ids_address[1] & 0xff;
    in_range = 0;
    if ((template_y < template_width) && (template_x < template_width))
    {
        in_range =
            (uint32_t)(g_temp_character_ids_address[template_x + template_y * template_width + 3] ==
                       1);
    }
    return in_range;
}

/* 原函数 0x81c024a0 */
void sango_battle_preview_skill_range(uint32_t unit_id, uint8_t preview_x, uint8_t preview_y)
{
    uint8_t original_x;
    uint8_t original_y;
    int unit_offset;
    uint8_t *unit_x_address;
    uint32_t unit_index;

    unit_index = unit_id & 0xff;
    unit_offset = unit_index * 7;
    unit_x_address = &g_first_unit_x + unit_offset;
    original_x = *unit_x_address;
    original_y = (&g_first_unit_y)[unit_offset];
    *unit_x_address = preview_x;
    (&g_first_unit_y)[unit_offset] = preview_y;
    sango_battle_prepare_combatant(0, unit_index);
    sango_battle_load_range_template('\0', 0, unit_index);
    (&g_first_unit_y)[unit_offset] = original_y;
    *unit_x_address = original_x;
    return;
}

/* 原函数 0x81c02524 */
void sango_battle_load_range_template(char range_kind, uint32_t skill_id, uint32_t unit_id)
{
    char half_width;
    int template_or_unit_address;
    uint32_t resource_id;
    char resource_item;
    uint32_t template_width;
    uint32_t template_offset;

    if (range_kind == '\0')
    {
        resource_id = 2;
        resource_item = '\x01';
        template_width = 5;
        template_offset =
            (uint32_t) *
            (uint8_t *)((uint32_t)(uint8_t)(&g_battle_roster_first)[unit_id & 0xff] * 0x10 +
                        g_character_table_address + -7) *
            0x19;
    }
    else if (range_kind == '\x01')
    {
        template_offset = ((skill_id & 0xff) - 1 & 0xffff) * 0x51 & 0xffff;
        template_width = 9;
        resource_id = 0xd;
        resource_item = '\x01';
    }
    template_or_unit_address =
        sango_resource_item(resource_id, resource_item, g_resource_package_address);
    if ((int)(template_width * template_width) < 0x54)
    {
        bbk_memcpy(g_temp_character_ids_address + 3,
                   (void *)(template_or_unit_address + template_offset),
                   template_width * template_width);
        template_or_unit_address = (unit_id & 0xff) * 7;
        *g_temp_character_ids_address = (char)template_width;
        half_width = (char)(template_width >> 1);
        g_temp_character_ids_address[1] = (&g_first_unit_x)[template_or_unit_address] - half_width;
        g_temp_character_ids_address[2] = (&g_first_unit_y)[template_or_unit_address] - half_width;
    }
    return;
}

/* 原函数 0x81c02664 */
uint32_t sango_battle_select_ai_unit(void)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define reference_x (*(uint8_t *)(abi_storage + 0))
#define reference_y (*(uint8_t(*)[7])(abi_storage + 1))

    char unit_status;
    int unit_stride_base;
    uint32_t distance;
    uint32_t candidate_unit;
    uint32_t nearest_distance;
    uint32_t nearest_unit;

    nearest_distance = 0xff;
    sango_battle_distance_components(&reference_x, reference_y);
    nearest_unit = 0xff;
    candidate_unit = 10;
    unit_stride_base = 0x50;
    do
    {
        unit_stride_base = unit_stride_base - candidate_unit;
        unit_status = (&g_first_unit_status)[unit_stride_base];
        if ((((unit_status != '\b') && (unit_status != '\x01')) && (unit_status != '\x06')) &&
            (((&g_first_unit_has_acted)[unit_stride_base] != '\x01' &&
              (distance = sango_battle_manhattan_distance((&g_first_unit_x)[unit_stride_base],
                                                          (&g_first_unit_y)[unit_stride_base],
                                                          reference_x, reference_y[0]),
               distance < nearest_distance))))
        {
            nearest_distance = distance;
            nearest_unit = candidate_unit;
        }
        candidate_unit = candidate_unit + 1 & 0xff;
        unit_stride_base = candidate_unit << 3;
    } while (candidate_unit < 0x14);
    return nearest_unit;
}
#undef reference_x
#undef reference_y

/* 原函数 0x81c0272c */
void sango_battle_distance_components(uint8_t *reference_x, uint8_t *reference_y)
{
    if (g_battle_control_mode != '\x01')
    {
        *reference_x = g_battle_spawn_x;
        *reference_y = g_battle_spawn_y;
        return;
    }
    *reference_x = (&g_first_unit_x)[(uint32_t)g_battle_player_unit_begin * 7];
    *reference_y = (&g_first_unit_y)[(uint32_t)g_battle_player_unit_begin * 7];
    return;
}

/* 原函数 0x81c027a0 */
uint32_t sango_battle_manhattan_distance(uint8_t source_x, uint8_t source_y, uint8_t target_x,
                                         uint8_t target_y)
{
    char distance_x;
    char distance_y;

    distance_x = source_x - target_x;
    if (source_x < target_x)
    {
        distance_x = -(source_x - target_x);
    }
    distance_y = source_y - target_y;
    if (source_y < target_y)
    {
        distance_y = -(source_y - target_y);
    }
    return (uint32_t)(uint8_t)(distance_x + distance_y);
}

#include "sango_internal.h"

/* 普通攻击、计谋执行和演出反馈。 */

/* 原函数 0x81c058b8 */
/* 计谋ID读取名称、消耗和状态参数；动画资源及指令范围来自初始化表。 */
uint32_t sango_battle_execute_skill(int action_address)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define message_separator (*(uint8_t *)(abi_storage + 5))
#define effect_amount (*(uint16_t *)(abi_storage + 32))
#define effect_aux (*(uint16_t(*)[3])(abi_storage + 34))
#define message_start (*(char(*)[5])(abi_storage + 0))
#define skill_name_start (*(uint8_t *)(abi_storage + 6))
#define failure_suffix_start (*(uint8_t *)(abi_storage + 7))
#define status_text_start (*(uint8_t(*)[4])(abi_storage + 8))
#define status_suffix_start (*(uint8_t(*)[20])(abi_storage + 12))

    const SangoBattleAction *action = (const SangoBattleAction *)(uintptr_t)action_address;
    uint32_t skill_id = (uint32_t)action->skill;
    uint32_t actor_unit = (uint32_t)action->actor_unit;
    uint32_t target_unit = (uint32_t)action->target_unit;
    char *skill_parameters = (char *)sango_battle_skill_parameters(skill_id);
    char new_status;
    char restores_troops;
    uint32_t result;

    /* 先扣除技力，再做原有命中判定；失败也消耗技力。 */
    (&g_first_unit_energy)[actor_unit * 7] =
        (&g_first_unit_energy)[actor_unit * 7] - skill_parameters[6];
    /* 这些消息片段共享连续栈区，不可拆为独立的小数组。 */
    sango_memory_fill(message_start, 0x20, 10);
    uint32_t random_roll = bbk_rand();
    if (g_defender_initiative + 0x14 == 0)
        sango_legacy_trap(7);

    if ((uint32_t)(g_attacker_initiative >> 1) <
        ((int)random_roll % (int)(g_defender_initiative + 0x14) & 0xffU))
    {
        sango_resource_read_text(0xb, skill_id, message_start + 1);
        message_separator = 0x20;
        sango_battle_read_text(0x1a, &failure_suffix_start);
        sango_battle_show_short_message(message_start, 1, 0xff);
        result = 0;
    }
    else
    {
        if (g_battle_show_animations == '\0')
        {
            sango_resource_read_text(0xb, skill_id, &skill_name_start);
            sango_battle_show_short_message(message_start, 1, 0);
            new_status = skill_parameters[1];
        }
        else
            new_status = skill_parameters[1];

        (&g_first_unit_status)[target_unit * 7] = new_status;
        if (new_status == '\x03')
            (&g_first_unit_move_range)[target_unit * 7] = 1;
        restores_troops = *skill_parameters;

        /* 天变、围攻、侦察走各自的效果流程，其余计谋共用伤害/回复路径。 */
        if (skill_id == 0x16)
        {
            sango_battle_change_weather();
            result = 8;
        }
        else if (skill_id == 0x1b)
        {
            result = sango_battle_execute_surround_attack(target_unit);
            sango_battle_prepare_combatant(0, actor_unit);
        }
        else if (skill_id == 0x1e)
        {
            g_battle_recon_food = g_battle_defender_food;
            sango_battle_read_text(0x37, g_scratch_buffer_address);
            uint32_t actor_character = sango_battle_resolve_character(actor_unit);
            sango_ui_show_character_message((uint8_t)actor_character, g_scratch_buffer_address);
            sango_render_present(g_game_context);
            result = 8;
        }
        else
        {
            sango_battle_compute_skill_effect((int)skill_parameters, &effect_amount, effect_aux);
            uint32_t skill_index = skill_id - 1 & 0xff;
            uint16_t animation_resource =
                *(uint16_t *)(&g_skill_animation_resource_bytes + skill_index * 2);
            if ((animation_resource != 0) && (g_battle_show_animations != '\0'))
            {
                if ((&g_skill_animation_background_flag)[skill_index] != '\0')
                    sango_bitmap_draw_resource(0x10, 1, 0x14, 0x31, '\0');
                sango_animation_play_range(
                    (uint32_t)animation_resource,
                    (uint32_t)(uint8_t)(&g_skill_animation_first_command)[skill_index],
                    (uint32_t)(uint8_t)(&g_skill_animation_last_command)[skill_index], 0,
                    (uint8_t)(&g_skill_animation_x_offset)[skill_index] + 0x14, 0x31);
            }

            uint32_t effect_text_id;
            uint32_t applied_amount;
            if (effect_amount == 0)
            {
                uint16_t *enemy_food = &g_battle_defender_food;
                if (9 < actor_unit)
                    enemy_food = &g_battle_attacker_food;
                effect_amount = effect_aux[0];
                applied_amount = sango_battle_subtract_clamped(enemy_food, effect_aux[0]);
                effect_aux[0] = (uint16_t)applied_amount;
                effect_text_id = 0x19;
            }
            else if (restores_troops == '\0')
            {
                effect_text_id = 0x17;
                applied_amount =
                    sango_battle_subtract_clamped(g_defender_troops_address, effect_amount);
                effect_amount = (uint16_t)applied_amount;
            }
            else
            {
                uint32_t target_character = sango_battle_resolve_character(target_unit);
                int troop_limit = sango_character_troop_capacity(target_character);
                effect_text_id = 0x18;
                applied_amount = sango_battle_add_clamped(
                    g_defender_troops_address, (uint32_t)effect_amount, (uint16_t)troop_limit);
                effect_amount = (uint16_t)applied_amount;
            }

            if (effect_amount != 0)
            {
                if (g_battle_show_animations == '\0')
                    sango_battle_draw_unit_damage('-', target_unit, (uint32_t)effect_amount);
                else
                {
                    sango_battle_read_text(effect_text_id, message_start);
                    sango_text_draw_legacy(0x3c, 0x33, message_start);
                    sango_battle_draw_damage_digits(0x3c, 0x59, (uint32_t)effect_amount);
                }
                sango_input_wait(0x32, '\0');
            }
            if (new_status != '\0')
            {
                uint32_t target_character = sango_battle_resolve_character(target_unit);
                sango_load_named_text((uint8_t)target_character, message_start);
                uint32_t name_length = bbk_strlen(message_start);
                name_length = name_length & 0xffff;
                sango_battle_read_text(0x1b, message_start + name_length);
                sango_battle_read_text((uint32_t)(uint8_t)(new_status + 0x1c),
                                       status_text_start + name_length);
                sango_battle_read_text(0x24, status_suffix_start + name_length);
                sango_ui_show_message(message_start, 1);
            }
            result = sango_battle_damage_feedback(effect_amount);
        }
    }
    return result;
}
#undef message_separator
#undef effect_amount
#undef effect_aux
#undef message_start
#undef skill_name_start
#undef failure_suffix_start
#undef status_text_start
#undef status_suffix_start

/* 原函数 0x81c05cdc */
uint32_t sango_battle_execute_surround_attack(uint32_t target_unit)
{
    bool more_directions;
    int direction_offset;
    uint32_t neighbor_unit_or_experience;
    uint32_t direction_index;
    uint32_t target_index;
    uint32_t experience_total;

    target_index = target_unit & 0xff;
    direction_index = 0;
    experience_total = 0;
find_next_attacker:
    do
    {
        more_directions = direction_index < 4;
        do
        {
            do
            {
                direction_offset = direction_index * 2;
                if (!more_directions)
                {
                    return experience_total >> 1;
                }
                direction_index = direction_index + 1 & 0xff;
            } while ((((&g_first_unit_x)[target_index * 7] == 0) &&
                      (more_directions = direction_index < 4,
                       0x80 < (uint8_t)(&g_legacy_data_81c201cc)[direction_offset])) ||
                     (((&g_first_unit_y)[target_index * 7] == 0 &&
                       (more_directions = direction_index < 4,
                        0x80 < (uint8_t)(&g_legacy_data_81c201cd)[direction_offset]))));
            neighbor_unit_or_experience = sango_battle_find_unit_at(
                (uint16_t)(uint8_t)(&g_first_unit_x)[target_index * 7] +
                        (uint16_t)(uint8_t)(&g_legacy_data_81c201cc)[direction_offset] &
                    0xff,
                (uint16_t)(uint8_t)(&g_first_unit_y)[target_index * 7] +
                        (uint16_t)(uint8_t)(&g_legacy_data_81c201cd)[direction_offset] &
                    0xff);
            if (neighbor_unit_or_experience == 0xff)
                goto find_next_attacker;
        } while (((target_index < 10) &&
                  (more_directions = direction_index < 4, neighbor_unit_or_experience < 10)) ||
                 ((10 < target_index &&
                   (more_directions = direction_index < 4, 10 < neighbor_unit_or_experience))));
        sango_battle_blink_unit(neighbor_unit_or_experience, 2);
        sango_battle_prepare_combatant(0, neighbor_unit_or_experience);
        neighbor_unit_or_experience = sango_battle_execute_normal_attack(target_index);
        experience_total = experience_total + neighbor_unit_or_experience & 0xff;
    } while (true);
}

/* 原函数 0x81c05e0c */
/* 普通攻击：计算伤害、扣除兵力，再按地形和兵种播放演出。 */
uint32_t sango_battle_execute_normal_attack(uint32_t target_unit)
{
    uint32_t damage;
    uint32_t applied_damage;
    uint32_t first_command;
    uint32_t last_command;
    uint32_t animation_resource;
    int feedback_delay;

    damage = sango_battle_roll_attack_damage();
    applied_damage = sango_battle_subtract_clamped(g_defender_troops_address, (uint16_t)damage);
    if (g_battle_show_animations == '\0')
    {
        sango_battle_draw_unit_damage('-', target_unit & 0xff, applied_damage);
    }
    else
    {
        sango_bitmap_draw_resource(0x10, 1, 0x14, 0x31, '\0');
        animation_resource = 0x19;
        first_command = 0;
        last_command = 4;
        if (g_defender_terrain_view2 != '\a')
        {
            animation_resource = g_attacker_troop_type + 0x13;
            first_command =
                (uint32_t)(uint8_t)(&g_attack_animation_command_strides)[g_attacker_troop_type] *
                    (uint32_t)g_defender_troop_type &
                0xff;
            last_command = (first_command +
                            (uint8_t)(&g_attack_animation_command_strides)[g_attacker_troop_type]) -
                               1 &
                           0xff;
        }
        sango_animation_play_range(animation_resource, first_command, last_command, 0, 0x14, 0x31);
        sango_battle_draw_damage_digits(0x3c, 0x59, applied_damage);
    }
    sango_input_wait(0x32, '\0');
    if ((uint8_t)(*g_attacker_level_address_view2 - *g_defender_level_address) < 0xe1)
    {
        feedback_delay = 0x10;
        if (*g_attacker_level_address_view2 != *g_defender_level_address)
        {
            feedback_delay = 8;
        }
    }
    else
    {
        feedback_delay = 0x18;
    }
    first_command = sango_battle_damage_feedback((uint16_t)applied_damage);
    return (uint32_t)(damage != applied_damage) * feedback_delay + first_command & 0xff;
}

/* 原函数 0x81c05f7c */
void sango_battle_draw_damage_digits(uint16_t x, uint16_t y, uint32_t damage)
{
    unsigned char abi_storage[36] __attribute__((aligned(8)));
#define digits (*(char(*)[16])(abi_storage + 0))
#define digit_count (*(uint32_t *)(abi_storage + 16))

    uint8_t glyph_width;
    uint8_t glyph_height;
    char digit;
    uint8_t *number_bitmap;
    uint16_t revealed_height;
    uint16_t next_height;
    uint32_t digit_index;

    sango_format_integer(damage & 0xffff, digits, 10);
    digit_count = bbk_strlen(digits);
    digit_count = digit_count & 0xff;
    number_bitmap = (uint8_t *)sango_resource_item(0xf, '\x01', g_resource_package_address);
    glyph_width = *number_bitmap;
    glyph_height = number_bitmap[2];
    digit_index = 0;
    if (digit_count != 0)
    {
        do
        {
            digit = digits[digit_index];
            sango_input_wait(4, '\0');
            revealed_height = 0;
            if (glyph_height != 0)
            {
                next_height = 1;
                do
                {
                    sango_bitmap_draw_frame_screen(x & 0xff, (y & 0xff) - revealed_height,
                                                   (uint16_t)glyph_width, next_height, digit - 0x30,
                                                   number_bitmap);
                    sango_input_wait(1, '\0');
                    revealed_height = next_height & 0xff;
                    next_height = revealed_height + 1;
                } while (revealed_height < glyph_height);
            }
            digit_index = digit_index + 1 & 0xff;
            x = (x & 0xff) + (uint16_t)glyph_width;
        } while (digit_index < digit_count);
    }
    return;
}
#undef digits
#undef digit_count

/* 原函数 0x81c060c8 */
void sango_battle_append_stat_value(char *text, uint32_t value)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define number_text (*(char(*)[16])(abi_storage + 0))

    uint32_t text_length;
    uint32_t character_index;
    char *dst;

    text_length = sango_crt_strlen(text);
    character_index = 0;
    if ((text_length & 0xffff) != 0)
    {
        do
        {
            dst = text + character_index;
            character_index = character_index + 1 & 0xffff;
            if (*dst == '%')
                break;
            dst = (char *)0x0;
        } while (character_index < (text_length & 0xffff));
        if (dst != (char *)0x0)
        {
            sango_format_integer(value & 0xffff, number_text, 10);
            text_length = sango_crt_strlen(number_text);
            bbk_memcpy(dst, number_text, text_length & 0xffff);
        }
    }
    return;
}
#undef number_text

/* 原函数 0x81c06168 */
uint32_t sango_battle_damage_feedback(uint16_t damage)
{
    uint32_t damage_experience;
    uint32_t adjusted_experience;
    uint32_t level_difference;

    level_difference =
        (uint32_t)*g_attacker_level_address_view3 - (uint32_t)*g_defender_level_address_view2 &
        0xff;
    damage_experience = sango_math_sqrt_step_search(damage);
    damage_experience = damage_experience >> 2 & 0xff;
    if ((0x80 < level_difference) ||
        (adjusted_experience = 0, level_difference < damage_experience))
    {
        adjusted_experience = damage_experience - level_difference & 0xff;
    }
    return (adjusted_experience + 2 & 0xff) % 100;
}

/* 原函数 0x81c0620c */
uint32_t sango_battle_terrain_at(uint32_t map_x, uint32_t map_y)
{
    uint8_t tile;
    uint8_t *map;
    uint32_t terrain;

    map = (uint8_t *)sango_resource_item((uint32_t)g_battle_map_resource, '\x01',
                                         g_resource_package_address);
    terrain = 6;
    tile = map[((uint32_t)*map * (map_y & 0xff) + (map_x & 0xff) & 0xffff) + 0x10];
    if (tile != 0x29)
    {
        terrain = 7;
    }
    if (tile < 0x10)
    {
        terrain = 2;
        if (tile < 6)
        {
            terrain = 3;
            if (tile < 5)
            {
                terrain = 4;
                if (tile < 4)
                {
                    terrain = 5;
                    if ((tile < 3) && (terrain = 0, tile < 2))
                    {
                        terrain = 1;
                    }
                }
            }
        }
    }
    return terrain;
}

/* 原函数 0x81c062d0 */
int sango_battle_skill_parameters(uint32_t skill_id)
{
    int parameters;

    parameters = sango_resource_item(10, '\x01', g_resource_package_address);
    return parameters + (((skill_id & 0xff) - 1) * 0x22 & 0xffff);
}

/* 原函数 0x81c06318 */
uint32_t sango_battle_find_unit_at(uint16_t map_x, uint16_t map_y)
{
    int unit_offset;
    uint32_t unit_index;

    unit_index = 0;
    while (true)
    {
        unit_offset = unit_index * 7;
        if ((((&g_first_unit_status)[unit_offset] != '\b') &&
             ((uint8_t)(&g_first_unit_x)[unit_offset] == map_x)) &&
            ((uint8_t)(&g_first_unit_y)[unit_offset] == map_y))
            break;
        unit_index = unit_index + 1 & 0xff;
        if (0x13 < unit_index)
        {
            return 0xff;
        }
    }
    return unit_index;
}

/* 原函数 0x81c06384 */
void sango_battle_change_weather(void)
{
    uint32_t weather;

    weather = bbk_rand();
    weather = (int)weather % 5 + 1;
    g_battle_weather = (uint8_t)weather;
    sango_bitmap_draw_resource((weather & 0xff) + 0x1b, 1, 0x14, 0x31, '\x01');
    sango_battle_status_draw_weather(0);
    sango_battle_status_draw_weather(g_game_context);
    sango_input_wait(0x32, '\0');
    return;
}

/* 原函数 0x81c06440 */
uint32_t sango_battle_show_options(void)
{
    unsigned char abi_storage[80] __attribute__((aligned(8)));
#define menu_boxes (*(uint16_t(*)[8])(abi_storage + 48))
#define menu_text (*(char(*)[48])(abi_storage + 0))

    uint32_t main_selection;
    uint32_t option_text_or_selection;
    uint8_t *option_address;

    menu_boxes[2] = 0x38;
    menu_boxes[4] = 0x6b;
    menu_boxes[6] = 0x83;
    menu_boxes[3] = 0x44;
    menu_boxes[1] = 8;
    menu_boxes[5] = 0x93;
    menu_boxes[7] = 0xab;
    menu_boxes[0] = 8;
    option_text_or_selection = 0x9f;
    main_selection = 0;
    do
    {
        sango_battle_read_text(9, menu_text);
        main_selection = sango_ui_choose_option(menu_boxes, main_selection, menu_text);
        if (main_selection == 2)
        {
            option_address = &g_battle_show_animations_view2;
            option_text_or_selection = 10;
        }
        else if ((int)main_selection < 3)
        {
            if (main_selection == 0)
            {
            return_to_battle:
                sango_render_present(g_game_context);
                return 0xff;
            }
            if (main_selection == 1)
            {
                g_battle_result_view2 = 2;
                goto return_to_battle;
            }
        }
        else if (main_selection == 4)
        {
            option_address = &g_battle_render_enabled_view2;
            option_text_or_selection = 10;
        }
        else if ((int)main_selection < 4)
        {
            option_address = &g_battle_animate_movement_view2;
            option_text_or_selection = 0xb;
        }
        else if (main_selection == 0xff)
        {
            sango_render_present(g_game_context);
            return 1;
        }
        sango_battle_read_text(option_text_or_selection, menu_text);
        option_text_or_selection =
            sango_ui_choose_option(menu_boxes + 4, (uint32_t)*option_address, menu_text);
        if (option_text_or_selection != 0xff)
        {
            *option_address = (uint8_t)option_text_or_selection;
        }
        sango_render_present(g_game_context);
    } while (true);
}
#undef menu_boxes
#undef menu_text

/* 原函数 0x81c065c4 */
void sango_battle_draw_unit_damage(char sign, uint32_t unit_id, uint32_t amount)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define message_sign (*(char *)(abi_storage + 0))
#define amount_text (*(uint8_t(*)[15])(abi_storage + 1))

    int unit_offset;

    message_sign = sign;
    sango_format_integer(amount & 0xffff, amount_text, 10);
    unit_offset = (unit_id & 0xff) * 7;
    sango_text_draw_legacy(
        ((uint16_t)(uint8_t)(&g_first_unit_x)[unit_offset] - (uint16_t)g_battle_viewport_x) * 0x10 &
            0xff,
        ((uint16_t)(uint8_t)(&g_first_unit_y)[unit_offset] - (uint16_t)g_battle_viewport_y) * 0x10 &
            0xff,
        &message_sign);
    return;
}
#undef message_sign
#undef amount_text

/* 原函数 0x81c06650 */
uint32_t sango_battle_resolve_character(uint32_t unit_id)
{
    return (uint8_t)(&g_battle_roster_first)[unit_id & 0xff] - 1 & 0xff;
}

/* 原函数 0x81c0666c */
void sango_battle_read_text(uint32_t text_id, void *output)
{
    sango_resource_read_text(1, text_id & 0xff, output);
    return;
}

/* 原函数 0x81c06694 */
uint32_t sango_battle_execute_action(uint8_t *record)
{
    uint8_t command_or_intelligence;
    uint8_t current_energy;
    uint8_t original_y;
    uint32_t character_or_sqrt_result;
    uint32_t experience_gain;
    int unit_or_character_address;
    uint32_t actor_unit;

    actor_unit = (uint32_t)record[2];
    unit_or_character_address = actor_unit * 7;
    (&g_first_unit_has_acted)[unit_or_character_address] = 1;
    sango_battle_prepare_combatant(0, actor_unit);
    sango_battle_prepare_combatant(1, (uint32_t)record[3]);
    command_or_intelligence = *record;
    if (command_or_intelligence == 1)
    {
        experience_gain = sango_battle_execute_skill((int)record);
    }
    else if (command_or_intelligence < 2)
    {
        if (command_or_intelligence == 0)
        {
            experience_gain = sango_battle_execute_normal_attack((uint32_t)record[3]);
        }
    }
    else
    {
        if (command_or_intelligence != 3)
        {
            if (command_or_intelligence != 0xff)
            {
                return experience_gain;
            }
            (&g_first_unit_x)[unit_or_character_address] = g_legacy_data_81c2b172;
            original_y = g_legacy_data_81c2b148;
            (&g_first_unit_has_acted)[unit_or_character_address] = 0;
            (&g_first_unit_y)[unit_or_character_address] = original_y;
            sango_battle_redraw_field(actor_unit);
        }
        character_or_sqrt_result = sango_battle_resolve_character(actor_unit);
        unit_or_character_address = g_character_table_address + character_or_sqrt_result * 0x10;
        command_or_intelligence = *(uint8_t *)(unit_or_character_address + 4);
        character_or_sqrt_result =
            sango_math_sqrt_step_search((uint16_t) * (uint8_t *)(unit_or_character_address + 3));
        current_energy = (&g_first_unit_energy)[actor_unit * 7];
        if ((uint32_t)current_energy < (((((uint32_t)command_or_intelligence * 0x50) / 100 +
                                          (character_or_sqrt_result >> 1 & 0xff) +
                                          (uint32_t) * (uint8_t *)(unit_or_character_address + 2)) *
                                         (uint32_t) * (uint8_t *)(unit_or_character_address + 8)) /
                                            100 &
                                        0xff))
        {
            (&g_first_unit_energy)[actor_unit * 7] = current_energy + 1;
        }
        experience_gain = 0;
    }
    return experience_gain;
}

/* 原函数 0x81c06838 */
uint32_t sango_battle_unit_sprite_frame(uint32_t unit_id)
{
    uint32_t character_id;
    int unit_offset;
    uint32_t frame;
    uint32_t unit_index;

    unit_index = unit_id & 0xff;
    unit_offset = unit_index * 7;
    character_id = sango_battle_resolve_character(unit_index);
    if (((&g_first_unit_status)[unit_offset] == '\x06') ||
        ((&g_first_unit_status)[unit_offset] == '\x01'))
    {
        frame = 0xe;
    }
    else
    {
        unit_offset = sango_battle_terrain_at((uint32_t)(uint8_t)(&g_first_unit_x)[unit_offset],
                                              (uint32_t)(uint8_t)(&g_first_unit_y)[unit_offset]);
        frame = 0xc;
        if (unit_offset != 7)
        {
            frame = (*(uint8_t *)(character_id * 0x10 + g_character_table_address + 9) & 0x7f) << 1;
        }
    }
    if (9 < unit_index)
    {
        frame = frame + 0x10 & 0xff;
    }
    return frame;
}

/* 原函数 0x81c068f0 */
void sango_battle_regenerate_unit_energy(uint32_t unit_id)
{
    uint8_t intelligence;
    uint8_t current_energy;
    uint32_t character_or_sqrt_result;
    int character_address;

    character_or_sqrt_result = sango_battle_resolve_character(unit_id & 0xff);
    character_address = g_character_table_address + character_or_sqrt_result * 0x10;
    intelligence = *(uint8_t *)(character_address + 4);
    character_or_sqrt_result =
        sango_math_sqrt_step_search((uint16_t) * (uint8_t *)(character_address + 3));
    current_energy = (&g_first_unit_energy)[(unit_id & 0xff) * 7];
    if ((uint32_t)current_energy <
        (((((uint32_t)intelligence * 0x50) / 100 + (character_or_sqrt_result >> 1 & 0xff) +
           (uint32_t) * (uint8_t *)(character_address + 2)) *
          (uint32_t) * (uint8_t *)(character_address + 8)) /
             100 &
         0xff))
    {
        (&g_first_unit_energy)[(unit_id & 0xff) * 7] = current_energy + 1;
    }
    return;
}

/* 原函数 0x81c069d4 */
uint32_t sango_battle_find_actionable_unit_at_cursor(void)
{
    char unit_status;
    int unit_offset;
    uint32_t unit_index;

    unit_index = 0;
    while (true)
    {
        unit_offset = unit_index * 7;
        unit_status = (&g_first_unit_status)[unit_offset];
        if (((unit_status != '\b') &&
             ((&g_first_unit_x)[unit_offset] == g_battle_cursor_x_view2)) &&
            ((&g_first_unit_y)[unit_offset] == g_battle_cursor_y_view2))
            break;
        unit_index = unit_index + 1 & 0xff;
        if (9 < unit_index)
        {
            return 0xff;
        }
    }
    if ((&g_first_unit_has_acted)[unit_offset] != '\0')
    {
        return 0xff;
    }
    if (unit_status == '\x01')
    {
        return 0xff;
    }
    if (unit_status != '\x06')
    {
        return unit_index;
    }
    return 0xff;
}

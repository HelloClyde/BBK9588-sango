#include "sango_internal.h"

/* 部队属性与伤害计算。 */

/* 原函数 0x81c00bfc */
void sango_battle_initialize_unit_stats(void)
{
    uint8_t strength_or_item_id;
    uint8_t intelligence;
    uint8_t level;
    uint8_t stamina;
    char movement_bonus;
    int unit_offset;
    uint32_t character_or_sqrt_result;
    int character_or_item_address;
    int character_address;
    uint32_t equipment_slot;
    uint32_t unit_index;
    char empty_side_slots;

    unit_index = 0;
    do
    {
        unit_offset = unit_index * 7;
        (&g_first_unit_status)[unit_offset] = 0;
        if (unit_index % 10 == 0)
        {
            empty_side_slots = '\0';
        }
        character_or_sqrt_result = sango_battle_character_id(unit_index);
        if (character_or_sqrt_result == 0xff)
        {
            empty_side_slots = empty_side_slots + '\x01';
            (&g_first_unit_status)[unit_offset] = 8;
            if (empty_side_slots == '\n')
            {
                g_battle_result = '\x02' - (char)(unit_index / 10);
                return;
            }
        }
        else
        {
            character_or_item_address = g_character_table_address + character_or_sqrt_result * 0x10;
            strength_or_item_id = *(uint8_t *)(character_or_item_address + 3);
            intelligence = *(uint8_t *)(character_or_item_address + 4);
            level = *(uint8_t *)(character_or_item_address + 2);
            stamina = *(uint8_t *)(character_or_item_address + 8);
            equipment_slot = 0;
            (&g_first_unit_life)[unit_offset] =
                (char)(((((uint32_t)strength_or_item_id * 0x50) / 100 +
                         ((uint32_t)intelligence * 0x1e) / 100 + (uint32_t)level) *
                        (uint32_t)stamina) /
                       100);
            character_or_sqrt_result = sango_math_sqrt_step_search((uint16_t)strength_or_item_id);
            (&g_first_unit_energy)[unit_offset] =
                (char)(((((uint32_t)intelligence * 0x50) / 100 +
                         (character_or_sqrt_result >> 1 & 0xff) + (uint32_t)level) *
                        (uint32_t)stamina) /
                       100);
            character_or_sqrt_result = sango_battle_character_id(unit_index);
            character_address = g_character_table_address + character_or_sqrt_result * 0x10;
            (&g_first_unit_move_range)[unit_offset] =
                (&g_legacy_data_81c1ffc0)[*(uint8_t *)(character_address + 9)];
            character_or_item_address = character_address;
            do
            {
                strength_or_item_id = *(uint8_t *)(character_or_item_address + 0xc);
                if (strength_or_item_id != 0)
                {
                    character_or_item_address =
                        sango_resource_item(0x42, '\x01', g_resource_package_address);
                    character_or_item_address =
                        character_or_item_address + (strength_or_item_id - 1 & 0xffff) * 0x42;
                    if ((character_or_item_address != 0) &&
                        (movement_bonus = *(char *)(character_or_item_address + 0x40),
                         movement_bonus != '\0'))
                    {
                        (&g_first_unit_move_range)[unit_offset] =
                            (&g_first_unit_move_range)[unit_offset] + movement_bonus;
                    }
                }
                equipment_slot = equipment_slot + 1 & 0xff;
                character_or_item_address = equipment_slot + character_address;
            } while (equipment_slot < 2);
            if (8 < (uint8_t)(&g_first_unit_move_range)[unit_offset])
            {
                (&g_first_unit_move_range)[unit_offset] = 8;
            }
        }
        unit_index = unit_index + 1 & 0xff;
    } while (unit_index < 0x14);
    return;
}

/* 原函数 0x81c00e90 */
void sango_battle_refresh_unit_stats(uint32_t unit_id)
{
    uint8_t strength_or_item_id;
    uint8_t intelligence;
    uint8_t level;
    uint8_t stamina;
    char movement_bonus;
    int unit_offset;
    uint32_t character_or_sqrt_result;
    int character_or_item_address;
    int character_address;
    uint32_t unit_index;
    uint32_t equipment_slot;

    unit_index = unit_id & 0xff;
    unit_offset = unit_index * 7;
    character_or_sqrt_result = sango_battle_character_id(unit_index);
    character_or_item_address = g_character_table_address + character_or_sqrt_result * 0x10;
    strength_or_item_id = *(uint8_t *)(character_or_item_address + 3);
    intelligence = *(uint8_t *)(character_or_item_address + 4);
    level = *(uint8_t *)(character_or_item_address + 2);
    stamina = *(uint8_t *)(character_or_item_address + 8);
    equipment_slot = 0;
    (&g_first_unit_life)[unit_offset] =
        (char)(((((uint32_t)strength_or_item_id * 0x50) / 100 +
                 ((uint32_t)intelligence * 0x1e) / 100 + (uint32_t)level) *
                (uint32_t)stamina) /
               100);
    character_or_sqrt_result = sango_math_sqrt_step_search((uint16_t)strength_or_item_id);
    (&g_first_unit_energy)[unit_offset] =
        (char)(((((uint32_t)intelligence * 0x50) / 100 + (character_or_sqrt_result >> 1 & 0xff) +
                 (uint32_t)level) *
                (uint32_t)stamina) /
               100);
    character_or_sqrt_result = sango_battle_character_id(unit_index);
    character_address = g_character_table_address + character_or_sqrt_result * 0x10;
    (&g_first_unit_move_range)[unit_offset] =
        (&g_legacy_data_81c1ffc0)[*(uint8_t *)(character_address + 9)];
    character_or_item_address = character_address;
    do
    {
        strength_or_item_id = *(uint8_t *)(character_or_item_address + 0xc);
        if (strength_or_item_id != 0)
        {
            character_or_item_address =
                sango_resource_item(0x42, '\x01', g_resource_package_address);
            character_or_item_address =
                character_or_item_address + (strength_or_item_id - 1 & 0xffff) * 0x42;
            if ((character_or_item_address != 0) &&
                (movement_bonus = *(char *)(character_or_item_address + 0x40),
                 movement_bonus != '\0'))
            {
                (&g_first_unit_move_range)[unit_offset] =
                    (&g_first_unit_move_range)[unit_offset] + movement_bonus;
            }
        }
        equipment_slot = equipment_slot + 1 & 0xff;
        character_or_item_address = equipment_slot + character_address;
    } while (equipment_slot < 2);
    if (8 < (uint8_t)(&g_first_unit_move_range)[unit_offset])
    {
        (&g_first_unit_move_range)[unit_offset] = 8;
    }
    return;
}

/* 原函数 0x81c0108c */
void sango_battle_remove_unit_status(uint32_t unit_id)
{
    uint8_t item_id;
    char movement_bonus;
    int unit_offset;
    uint32_t character_id;
    int equipment_or_item_address;
    uint32_t equipment_slot;
    int character_address;

    unit_offset = (unit_id & 0xff) * 7;
    character_id = sango_battle_character_id(unit_id & 0xff);
    equipment_slot = 0;
    character_address = g_character_table_address + character_id * 0x10;
    (&g_first_unit_move_range)[unit_offset] =
        (&g_legacy_data_81c1ffc0)[*(uint8_t *)(character_address + 9)];
    equipment_or_item_address = character_address;
    do
    {
        item_id = *(uint8_t *)(equipment_or_item_address + 0xc);
        if (item_id != 0)
        {
            equipment_or_item_address =
                sango_resource_item(0x42, '\x01', g_resource_package_address);
            equipment_or_item_address = equipment_or_item_address + (item_id - 1 & 0xffff) * 0x42;
            if ((equipment_or_item_address != 0) &&
                (movement_bonus = *(char *)(equipment_or_item_address + 0x40),
                 movement_bonus != '\0'))
            {
                (&g_first_unit_move_range)[unit_offset] =
                    (&g_first_unit_move_range)[unit_offset] + movement_bonus;
            }
        }
        equipment_slot = equipment_slot + 1 & 0xff;
        equipment_or_item_address = equipment_slot + character_address;
    } while (equipment_slot < 2);
    if (8 < (uint8_t)(&g_first_unit_move_range)[unit_offset])
    {
        (&g_first_unit_move_range)[unit_offset] = 8;
    }
    return;
}

/* 原函数 0x81c0118c */
uint32_t sango_battle_roll_attack_damage(void)
{
    uint32_t damage_value;
    uint32_t factor_value;

    factor_value = (uint32_t)g_attacker_attack;
    damage_value = sango_soft_int_to_f32(factor_value);
    if ((int)factor_value < 0)
    {
        damage_value = soft_float_add(damage_value, g_legacy_data_81c20c48);
    }
    factor_value = sango_soft_int_to_f32((uint32_t)g_legacy_data_81c2b256);
    damage_value = soft_float_div(damage_value, factor_value);
    factor_value = sango_soft_int_to_f32((uint32_t)(*g_attacker_troops_address >> 3));
    damage_value = soft_float_mul(damage_value, factor_value);
    damage_value = sango_soft_f32_to_int(damage_value);
    damage_value = sango_soft_int_to_f32(damage_value & 0xffff);
    damage_value = soft_float_mul(
        damage_value,
        *(uint32_t *)(((uint32_t)g_attacker_troop_type * 6 + (uint32_t)g_defender_troop_type) * 4 +
                      -0x7e3e0038));
    damage_value = sango_soft_f32_to_int(damage_value);
    return damage_value + 10 & 0xffff;
}

/* 原函数 0x81c01278 */
/* 将攻击方或防守方的武将属性、地形和兵种写入20字节战斗视图。 */
void sango_battle_prepare_combatant(uint32_t combatant_side, uint32_t unit_id)
{
    uint8_t unit_y_or_troop_type;
    uint8_t unit_x;
    uint32_t character_or_stat_value;
    int terrain;
    int unit_or_rule_address;
    int side_or_troop_offset;
    uint32_t side_index;
    int character_address;
    uint32_t terrain_shift;

    side_index = combatant_side & 0xff;
    character_or_stat_value = sango_battle_character_id(unit_id & 0xff);
    side_or_troop_offset = side_index * 0x14;
    unit_or_rule_address = (unit_id & 0xff) * 7;
    if (character_or_stat_value < 200)
    {
        unit_y_or_troop_type = (&g_first_unit_y)[unit_or_rule_address];
        unit_x = (&g_first_unit_x)[unit_or_rule_address];
        character_address = g_character_table_address + character_or_stat_value * 0x10;
        (&g_attacker_level_address)[side_index * 5] = character_address + 2;
        (&g_attacker_initiative)[side_or_troop_offset] =
            *(char *)(character_address + 4) + *(char *)(character_address + 2) + '\x05';
        terrain = sango_battle_terrain_at((uint32_t)unit_x, (uint32_t)unit_y_or_troop_type);
        (&g_attacker_terrain)[side_or_troop_offset] = (char)terrain;
        (&g_legacy_data_81c2b236)[side_or_troop_offset] = 0;
        unit_or_rule_address = g_resource_package_address;
        unit_y_or_troop_type = *(uint8_t *)(character_address + 9);
        (&g_attacker_experience_address)[side_index * 5] = character_address + 7;
        (&g_attacker_troop_type)[side_or_troop_offset] = unit_y_or_troop_type;
        (&g_attacker_troops_address_view2)[side_index * 5] = character_address + 10;
        unit_or_rule_address = sango_resource_item(2, '\x04', unit_or_rule_address);
        side_or_troop_offset = (uint32_t)unit_y_or_troop_type * 4;
        terrain_shift = (uint32_t) * (uint8_t *)(unit_or_rule_address +
                                                 (uint32_t)unit_y_or_troop_type * 8 + terrain);
        character_or_stat_value =
            sango_soft_int_to_f32((uint32_t) * (uint8_t *)(character_address + 3) *
                                  (*(uint8_t *)(character_address + 2) + 10));
        character_or_stat_value = soft_float_mul(
            character_or_stat_value, *(uint32_t *)(&g_legacy_data_81c20058 + side_or_troop_offset));
        character_or_stat_value = sango_soft_f32_to_int(character_or_stat_value);
        (&g_attacker_attack_view2)[side_index * 10] =
            (short)((int)(character_or_stat_value & 0xffff) >> (terrain_shift & 0x1f));
        character_or_stat_value =
            sango_soft_int_to_f32((uint32_t) * (uint8_t *)(character_address + 4) *
                                  (*(uint8_t *)(character_address + 2) + 10));
        character_or_stat_value = soft_float_mul(
            character_or_stat_value, *(uint32_t *)(&g_legacy_data_81c20070 + side_or_troop_offset));
        character_or_stat_value = sango_soft_f32_to_int(character_or_stat_value);
        character_or_stat_value = sango_soft_int_to_f32(
            (int)(character_or_stat_value & 0xffff) >> (terrain_shift & 0x1f) & 0xffff);
        character_or_stat_value = soft_float_mul(
            character_or_stat_value, *(uint32_t *)(&g_legacy_data_81c20088 + terrain * 4));
        character_or_stat_value = sango_soft_f32_to_int(character_or_stat_value);
        (&g_attacker_defense)[side_index * 10] = (short)character_or_stat_value;
    }
    return;
}

/* 原函数 0x81c0142c */
void sango_battle_consume_daily_food(void)
{
    uint32_t daily_cost;
    uint16_t *food;
    uint8_t side;

    side = 0;
    do
    {
        daily_cost = sango_battle_sum_side_troops(side);
        daily_cost = sango_math_sqrt_step_search((uint16_t)daily_cost);
        food = &g_battle_defender_food;
        if (side == 0)
        {
            food = &g_battle_attacker_food;
        }
        daily_cost = daily_cost / 3 & 0xff;
        if (*food < daily_cost)
        {
            *food = 0;
        }
        else
        {
            *food = *food - (short)daily_cost;
        }
        side = side + 1;
    } while (side < 2);
    return;
}

/* 原函数 0x81c014bc */
uint32_t sango_battle_subtract_clamped(uint16_t *value, uint16_t amount)
{
    uint16_t removed;
    uint16_t remaining_value;
    uint32_t applied_amount;

    removed = *value;
    applied_amount = (uint32_t)amount;
    remaining_value = removed - amount;
    if (removed <= applied_amount)
    {
        remaining_value = 0;
        applied_amount = (uint32_t)removed;
    }
    *value = remaining_value;
    return applied_amount;
}

/* 原函数 0x81c014ec */
uint32_t sango_battle_add_clamped(uint16_t *value, uint32_t amount, uint16_t limit)
{
    uint32_t added;
    uint32_t updated_value;

    added = amount & 0xffff;
    updated_value = *value + added;
    if (limit < updated_value)
    {
        added = (uint32_t)limit - (uint32_t)*value & 0xffff;
    }
    else
    {
        limit = (uint16_t)updated_value;
    }
    *value = limit;
    return added;
}

/* 原函数 0x81c01524 */
void sango_battle_compute_skill_effect(int skill_parameters_address, uint16_t *troop_effect,
                                       uint16_t *food_effect)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define effect_amounts (*(uint16_t(*)[4])(abi_storage + 0))
#define target_troop_type (*(uint32_t *)(abi_storage + 8))
#define actor_terrain (*(uint32_t *)(abi_storage + 12))

    uint32_t weather;
    int effect_offset;
    uint32_t multiplier_bits;
    uint32_t effect_value;
    uint32_t weather_or_actor_factor;
    uint32_t target_factor;
    uint32_t effect_index;
    uint32_t target_terrain;

    weather = (uint32_t)g_battle_weather;
    actor_terrain = (uint32_t)g_attacker_terrain;
    target_terrain = (uint32_t)g_defender_terrain;
    target_troop_type = (uint32_t)g_defender_troop_type;
    effect_amounts[0] = *(uint16_t *)(skill_parameters_address + 2);
    effect_amounts[1] = *(uint16_t *)(skill_parameters_address + 4);
    effect_index = 0;
    effect_offset = 0;
    do
    {
        effect_value = (uint32_t) * (uint16_t *)((int)effect_amounts + effect_offset);
        if (effect_value != 0)
        {
            effect_value = sango_soft_int_to_f32(effect_value);
            weather_or_actor_factor = (uint32_t) * (char *)(weather + skill_parameters_address + 6);
            multiplier_bits = sango_soft_int_to_f32(weather_or_actor_factor);
            if ((int)weather_or_actor_factor < 0)
            {
                multiplier_bits = soft_float_add(multiplier_bits, g_legacy_data_81c20c4c);
            }
            weather_or_actor_factor = g_legacy_data_81c20c50;
            multiplier_bits = soft_float_div(multiplier_bits, g_legacy_data_81c20c50);
            effect_value = soft_float_mul(effect_value, multiplier_bits);
            effect_value = sango_soft_f32_to_int(effect_value);
            effect_value = sango_soft_int_to_f32(effect_value & 0xffff);
            target_factor =
                (uint32_t) * (char *)(target_troop_type + skill_parameters_address + 0x1c);
            multiplier_bits = sango_soft_int_to_f32(target_factor);
            if ((int)target_factor < 0)
            {
                multiplier_bits = soft_float_add(multiplier_bits, g_legacy_data_81c20c4c);
            }
            multiplier_bits = soft_float_div(multiplier_bits, weather_or_actor_factor);
            effect_value = soft_float_mul(effect_value, multiplier_bits);
            effect_value = sango_soft_f32_to_int(effect_value);
            effect_value = sango_soft_int_to_f32(effect_value & 0xffff);
            target_factor = (uint32_t) * (char *)(target_terrain + skill_parameters_address + 0xc);
            multiplier_bits = sango_soft_int_to_f32(target_factor);
            if ((int)target_factor < 0)
            {
                multiplier_bits = soft_float_add(multiplier_bits, g_legacy_data_81c20c4c);
            }
            multiplier_bits = soft_float_div(multiplier_bits, weather_or_actor_factor);
            effect_value = soft_float_mul(effect_value, multiplier_bits);
            effect_value = sango_soft_f32_to_int(effect_value);
            effect_value = sango_soft_int_to_f32(effect_value & 0xffff);
            weather_or_actor_factor =
                (uint32_t) * (char *)(actor_terrain + skill_parameters_address + 0x14);
            multiplier_bits = sango_soft_int_to_f32(weather_or_actor_factor);
            if ((int)weather_or_actor_factor < 0)
            {
                multiplier_bits = soft_float_add(multiplier_bits, g_legacy_data_81c20c4c);
            }
            multiplier_bits = soft_float_div(multiplier_bits, g_legacy_data_81c20c50);
            effect_value = soft_float_mul(effect_value, multiplier_bits);
            effect_value = sango_soft_f32_to_int(effect_value);
            *(uint16_t *)((int)effect_amounts + effect_offset) = (uint16_t)effect_value;
        }
        effect_index = effect_index + 1 & 0xff;
        effect_offset = effect_index << 1;
    } while (effect_index < 2);
    *troop_effect = effect_amounts[0];
    *food_effect = effect_amounts[1];
    return;
}
#undef effect_amounts
#undef target_troop_type
#undef actor_terrain

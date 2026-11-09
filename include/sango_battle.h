#ifndef SANGO_BATTLE_H
#define SANGO_BATTLE_H
#include "sango_types.h"

/* Display viewport only. Movement/skill rule windows keep their original 15x15 size. */
enum
{
    SANGO_BATTLE_TILE_SIZE = 16,
    SANGO_BATTLE_VIEW_COLUMNS = 15,
    SANGO_BATTLE_VIEW_ROWS = 13,
    SANGO_BATTLE_MAP_WIDTH = SANGO_BATTLE_VIEW_COLUMNS * SANGO_BATTLE_TILE_SIZE,
    SANGO_BATTLE_MAP_HEIGHT = SANGO_BATTLE_VIEW_ROWS * SANGO_BATTLE_TILE_SIZE
};

void sango_battle_choose_auto_result(void);
uint32_t sango_battle_sum_side_troops(char side);
uint32_t sango_battle_character_id(uint32_t unit_id);
void sango_battle_build_move_range(uint32_t unit_id);
void sango_battle_copy_move_window(uint32_t unit_id);
void sango_battle_load_movement_costs(uint32_t unit_id);
void sango_battle_expand_reachable_tiles(uint32_t unit_id);
void sango_battle_relax_move_costs(uint32_t unit_id);
void sango_battle_mark_blocked_positions(uint32_t source_cell, int next_frontier_address,
                                         uint8_t *next_count_address);
void sango_battle_initialize_unit_stats(void);
void sango_battle_refresh_unit_stats(uint32_t unit_id);
void sango_battle_remove_unit_status(uint32_t unit_id);
uint32_t sango_battle_roll_attack_damage(void);
void sango_battle_prepare_combatant(uint32_t combatant_side, uint32_t unit_id);
void sango_battle_consume_daily_food(void);
uint32_t sango_battle_subtract_clamped(uint16_t *value, uint16_t amount);
uint32_t sango_battle_add_clamped(uint16_t *value, uint32_t amount, uint16_t limit);
void sango_battle_compute_skill_effect(int skill_parameters_address, uint16_t *troop_effect,
                                       uint16_t *food_effect);
uint32_t sango_battle_ai_plan_unit(uint8_t *action);
uint32_t sango_battle_ai_choose_skill(uint8_t *action);
uint32_t sango_battle_ai_prepare_attack(uint8_t *action);
void sango_battle_ai_choose_destination(uint32_t unit_id);
uint32_t sango_battle_choose_skill(uint32_t unit_id, uint16_t *menu_bounds, uint8_t *skill_buffer);
uint32_t sango_battle_skill_target_allowed(uint32_t skill_id, uint32_t unit_id);
void sango_battle_collect_unit_skills(uint32_t character_id, char *skill_ids);
void sango_battle_load_skill_names(uint8_t *skill_buffer);
uint32_t sango_battle_skill_terrain_allowed(uint32_t skill_id, char target_side,
                                            uint32_t target_unit);
uint32_t sango_battle_unit_terrain(uint32_t index);
void sango_battle_select_combat_target(uint16_t *damage_estimate, uint8_t *target_unit);
uint32_t sango_battle_target_in_skill_range(int map_x, int map_y);
void sango_battle_preview_skill_range(uint32_t unit_id, uint8_t preview_x, uint8_t preview_y);
void sango_battle_load_range_template(char range_kind, uint32_t skill_id, uint32_t unit_id);
uint32_t sango_battle_select_ai_unit(void);
void sango_battle_distance_components(uint8_t *reference_x, uint8_t *reference_y);
uint32_t sango_battle_manhattan_distance(uint8_t source_x, uint8_t source_y, uint8_t target_x,
                                         uint8_t target_y);
void sango_battle_draw_move_range(void);
void sango_battle_show_overview(void);
void sango_battle_draw_overview_rows(char side, uint32_t first_row);
uint32_t sango_battle_count_active_units(uint32_t side);
void sango_battle_load_overview_text(uint32_t text_id, void *destination);
uint32_t sango_battle_is_player_unit(uint32_t unit_id);
uint32_t sango_battle_plan_ai_action(uint8_t *action);
void sango_battle_run_player_turn(void);
void sango_battle_show_unit_commands(char *action);
uint32_t sango_battle_select_target(char action_kind, char selected_skill, uint32_t actor_unit);
void sango_battle_draw_target_markers(void);
void sango_battle_filter_unit_commands(uint32_t unit_id, uint16_t *menu_bounds);
uint32_t sango_battle_finish_unit_action(uint8_t *record);
uint32_t sango_battle_select_move_destination(uint32_t unit_id);
uint32_t sango_battle_select_active_unit(void);
uint32_t sango_battle_poll_map_action(char preview_mode);
void sango_battle_draw_cursor(void);
uint32_t sango_battle_initialize_field(void);
uint32_t sango_battle_spawn_origin(char axis);
void sango_battle_draw_hud(void);
uint32_t sango_battle_target_side_allowed(void);
void sango_battle_advance_day(void);
void sango_battle_scroll_viewport(char suppress_scroll);
void sango_battle_tick_unit_statuses(void);
void sango_battle_redraw_field(uint32_t unit_id);
void sango_battle_show_unit_delta(char sign, uint32_t unit_id, uint32_t amount);
void sango_battle_blink_unit(uint32_t unit_id, uint8_t blink_count);
void sango_battle_draw_units(uint32_t animation_phase);
void sango_battle_draw_tile(uint32_t map_x, uint32_t map_y, char draw_to_screen);
void sango_battle_show_action_message(uint32_t experience_gain);
void sango_battle_check_level_and_retreat(void);
void sango_battle_play_unit_effect(uint32_t first_command, uint32_t last_command, uint16_t map_x,
                                   uint16_t map_y);
void sango_battle_draw_terrain(uint32_t view_x, uint32_t view_y);
void sango_battle_copy_viewport_tiles(uint32_t requested_x, uint32_t requested_y);
void sango_battle_draw_cursor_description(void);
void sango_battle_check_finish(char active_side);
uint32_t sango_battle_unit_character(uint32_t unit_id);
void sango_battle_load_text(uint32_t text_id, void *output);
uint32_t sango_battle_resource_item(uint32_t resource_id, char item_number);
void sango_battle_present(void);
void sango_battle_draw_text(short x, short y, char *text);
void sango_battle_draw_bitmap(uint32_t resource_id, uint32_t frame_number, uint32_t x, short y);
uint32_t sango_battle_run(void);
void sango_battle_begin(void);
void sango_battle_run_ai_turn(void);
void sango_battle_refresh_target_preview(char redraw_markers);
void sango_battle_refresh_move_preview(char redraw_range);
uint32_t sango_battle_reset_session(void);
void sango_battle_refresh_display(void);
void sango_battle_focus_viewport(void);
void sango_battle_show_cursor_info(void) __attribute__((noinline));
uint32_t sango_battle_execute_skill(int action_address);
uint32_t sango_battle_execute_surround_attack(uint32_t target_unit);
uint32_t sango_battle_execute_normal_attack(uint32_t target_unit);
void sango_battle_draw_damage_digits(uint16_t x, uint16_t y, uint32_t damage);
void sango_battle_append_stat_value(char *text, uint32_t value);
uint32_t sango_battle_damage_feedback(uint16_t damage);
uint32_t sango_battle_terrain_at(uint32_t map_x, uint32_t map_y);
int sango_battle_skill_parameters(uint32_t skill_id);
uint32_t sango_battle_find_unit_at(uint16_t map_x, uint16_t map_y);
void sango_battle_change_weather(void);
uint32_t sango_battle_show_options(void);
void sango_battle_draw_unit_damage(char sign, uint32_t unit_id, uint32_t amount);
uint32_t sango_battle_resolve_character(uint32_t unit_id);
void sango_battle_read_text(uint32_t text_id, void *output);
uint32_t sango_battle_execute_action(uint8_t *record);
uint32_t sango_battle_unit_sprite_frame(uint32_t unit_id);
void sango_battle_regenerate_unit_energy(uint32_t unit_id);
uint32_t sango_battle_find_actionable_unit_at_cursor(void);

#endif

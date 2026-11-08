#ifndef SANGO_UI_H
#define SANGO_UI_H
#include "sango_types.h"

uint32_t sango_ui_choose_option(uint16_t *bounds, uint32_t initial_selection, char *menu_text);
void sango_bitmap_draw_resource(uint32_t resource_id, uint32_t frame_number, uint32_t x, short y,
                                char draw_to_screen);
void sango_text_draw_wrapped_box(uint16_t *outer_bounds, uint16_t *inner_bounds, char *text);
char *sango_text_wrap_lines(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom,
                            char *text);
char *sango_text_find_line_end(int text_address, uint32_t max_length, char delimiter);
void sango_text_draw_centered(short center_x, uint16_t y, char *text);
void sango_battle_show_short_message(char *text, uint16_t wait_units, uint16_t row_or_center);
uint32_t sango_math_sqrt_step_search(uint16_t value);
void sango_text_draw_padded_number(uint16_t x, uint16_t y, uint32_t value, uint32_t field_width,
                                   int context);
int sango_character_troop_capacity(uint32_t character_id);
uint32_t sango_ui_input_food_amount(uint32_t value, uint32_t maximum_amount);
uint32_t sango_ui_input_money_amount(uint32_t value, uint32_t maximum_amount);
uint32_t sango_ui_input_troop_amount(uint32_t value, uint32_t maximum_amount);
int sango_allocate_session_state(void);
int sango_select_session(void);
uint32_t sango_menu_select_animated(uint16_t background_resource, short selection_animation_base);
void sango_menu_show_credits(void);
uint32_t sango_menu_choose_ruler(uint32_t ruler_count);
void sango_menu_flash_ruler_cities(uint32_t city_count, uint8_t *city_ids,
                                   int city_positions_address);
void sango_menu_draw_ruler_names(uint32_t first_ruler);
uint32_t sango_animation_play_resource(uint16_t resource_id);
void sango_ui_show_city_event(uint8_t city_id, uint32_t unused_event_value,
                              uint32_t unused_event_aux, uint32_t status_text_fallback);
uint32_t sango_strategy_spawn_items_for_year(void);
void sango_item_remove_attributes(uint32_t item_id, uint32_t character_id);
void sango_ui_show_strategy_text(uint8_t text_id);
void sango_ui_draw_character_panel(short left, short top, uint8_t character_id);
void sango_ui_show_character_message(uint8_t character_id, char *message);
void sango_item_mark_discovered(uint8_t item_id);
uint32_t sango_city_list_items(uint32_t city_id, int destination_address);
uint32_t sango_city_find_item(uint32_t city_id, int destination_address);
uint32_t sango_city_neighbor_direction(uint32_t city_id, uint32_t neighbor_city);
void sango_ui_table_begin(uint8_t left, uint8_t top, uint8_t right, uint8_t bottom,
                          uint8_t *table_state);
uint32_t sango_ui_table_next_cell(uint8_t cell_width, uint8_t cell_height, int table_address,
                                  uint8_t *cell_x, uint8_t *cell_y);
uint32_t sango_ui_table_next_row(uint8_t *table_state);
void sango_ui_draw_item_row(uint8_t item_id, uint32_t first_attribute, char left, char top,
                            char width);
void sango_item_format_attribute(uint32_t item_id, uint8_t attribute, uint8_t *output);
uint32_t sango_ui_draw_item_header(uint32_t first_attribute, char left, char top, char width);
uint32_t sango_ui_select_item(int item_ids_address, uint32_t item_count, uint32_t left,
                              uint32_t top, uint8_t right, uint8_t bottom);
void sango_item_read_name(char item_id, void *name);
void sango_ui_draw_character_row(uint32_t character_id, uint32_t first_attribute, char left,
                                 char top, char width);
void sango_character_format_attribute(uint32_t character_id, uint8_t attribute, uint8_t *output);
uint32_t sango_ui_draw_character_header(uint32_t first_attribute, char left, char top, char width);
uint32_t sango_ui_select_character(int character_ids_address, uint32_t character_count,
                                   uint32_t left, uint32_t top, uint8_t right, uint8_t bottom);
void sango_city_read_name(char city_id, void *name);
void sango_city_format_attribute(uint32_t city_id, uint8_t attribute, char *output,
                                 uint32_t legacy_context);
void sango_city_format_status(uint32_t city_id, void *destination, uint32_t unused_format_argument,
                              uint32_t fallback_text_id);
uint32_t sango_ui_show_city_details(uint8_t city_id);
void sango_load_named_text(uint8_t character_id, void *name);
uint32_t sango_strategy_run_player_commands(void);
uint32_t sango_ui_show_system_menu(void);
uint32_t sango_ui_select_number(uint32_t initial_value, uint32_t maximum_value);
void sango_ui_show_ai_progress(void);

#endif

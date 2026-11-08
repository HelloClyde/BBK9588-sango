#ifndef SANGO_UI_H
#define SANGO_UI_H
#include "sango_types.h"

uint32_t sango_ui_choose_option(uint16_t *param_1, uint32_t param_2, char *param_3);
void sango_bitmap_draw_resource(uint32_t resource_id, uint32_t frame_number, uint32_t x, short y,
                                char draw_to_screen);
void sango_text_draw_wrapped_box(uint16_t *param_1, uint16_t *param_2, char *param_3);
char *sango_text_wrap_lines(uint16_t param_1, uint16_t param_2, uint16_t param_3, uint16_t param_4,
                            char *param_5);
char *sango_text_find_line_end(int param_1, uint32_t param_2, char param_3);
void sango_text_draw_centered(short param_1, uint16_t param_2, char *param_3);
void sango_battle_show_short_message(char *param_1, uint16_t param_2, uint16_t param_3);
uint32_t sango_math_sqrt_step_search(uint16_t value);
void sango_text_draw_padded_number(uint16_t param_1, uint16_t param_2, uint32_t param_3,
                                   uint32_t param_4, int param_5);
int sango_character_troop_capacity(uint32_t character_id);
uint32_t sango_ui_input_food_amount(uint32_t value, uint32_t mode);
uint32_t sango_ui_input_money_amount(uint32_t value, uint32_t mode);
uint32_t sango_ui_input_troop_amount(uint32_t value, uint32_t mode);
int sango_allocate_session_state(void);
int sango_select_session(void);
uint32_t sango_menu_select_animated(uint16_t background_resource, short selection_animation_base);
void sango_menu_show_credits(void);
uint32_t sango_menu_choose_ruler(uint32_t param_1);
void sango_menu_flash_ruler_cities(uint32_t param_1, uint8_t *param_2, int param_3);
void sango_menu_draw_ruler_names(uint32_t param_1);
uint32_t sango_animation_play_resource(uint16_t resource_id);
void sango_ui_show_city_event(uint8_t param_1, uint32_t param_2, uint32_t param_3,
                              uint32_t param_4);
uint32_t sango_strategy_spawn_items_for_year(void);
void sango_item_remove_attributes(uint32_t param_1, uint32_t param_2);
void sango_ui_show_strategy_text(uint8_t param_1);
void sango_ui_draw_character_panel(short param_1, short param_2, uint8_t param_3);
void sango_ui_show_character_message(uint8_t param_1, char *param_2);
void sango_character_add_item(uint8_t param_1);
uint32_t sango_city_list_items(uint32_t param_1, int param_2);
uint32_t sango_city_find_item(uint32_t param_1, int param_2);
uint32_t sango_city_neighbor_direction(uint32_t param_1, uint32_t param_2);
void sango_ui_table_begin(uint8_t param_1, uint8_t param_2, uint8_t param_3, uint8_t param_4,
                          uint8_t *param_5);
uint32_t sango_ui_table_next_cell(uint8_t param_1, uint8_t param_2, int param_3, uint8_t *param_4,
                                  uint8_t *param_5);
uint32_t sango_ui_table_next_row(uint8_t *param_1);
void sango_ui_draw_item_row(uint8_t param_1, uint32_t param_2, char param_3, char param_4,
                            char param_5);
void sango_item_format_attribute(uint32_t param_1, uint8_t param_2, uint8_t *param_3);
uint32_t sango_ui_draw_item_header(uint32_t param_1, char param_2, char param_3, char param_4);
uint32_t sango_ui_select_item(int param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4,
                              uint8_t param_5, uint8_t param_6);
void sango_item_read_name(char item_id, void *name);
void sango_ui_draw_character_row(uint32_t param_1, uint32_t param_2, char param_3, char param_4,
                                 char param_5);
void sango_character_format_attribute(uint32_t param_1, uint8_t param_2, uint8_t *param_3);
uint32_t sango_ui_draw_character_header(uint32_t param_1, char param_2, char param_3, char param_4);
uint32_t sango_ui_select_character(int param_1, uint32_t param_2, uint32_t param_3,
                                   uint32_t param_4, uint8_t param_5, uint8_t param_6);
void sango_city_read_name(char city_id, void *name);
void sango_city_format_attribute(uint32_t param_1, uint8_t param_2, char *param_3,
                                 uint32_t param_4);
void sango_city_format_status(uint32_t param_1, void *param_2, uint32_t param_3, uint32_t param_4);
uint32_t sango_ui_show_city_details(uint8_t param_1);
void sango_load_named_text(uint8_t character_id, void *name);
uint32_t sango_strategy_run_player_commands(void);
uint32_t sango_ui_show_system_menu(void);
uint32_t sango_ui_select_number(uint32_t param_1, uint32_t param_2);
void sango_ui_show_ai_progress(void);

#endif

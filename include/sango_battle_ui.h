#ifndef SANGO_BATTLE_UI_H
#define SANGO_BATTLE_UI_H
void sango_battle_day_popup_draw(unsigned int day);
void sango_battle_status_draw(void);
void sango_battle_status_draw_weather(unsigned int target);
void sango_battle_status_draw_description(char *text, unsigned int target);
void sango_battle_summary_remember(unsigned int cities, unsigned int characters,
                                   unsigned int city_plus_one);
void sango_battle_summary_draw(unsigned int target);
unsigned int sango_battle_animation_left(void);
short sango_battle_animation_top(void);
void sango_battle_info_show(void);
void sango_battle_info_prepare_canvas(unsigned int target);
#endif

#ifndef SANGO_BATTLE_UI_H
#define SANGO_BATTLE_UI_H
void sango_battle_day_popup_draw(unsigned int day);
void sango_battle_status_draw(void);
void sango_battle_status_draw_weather(unsigned int target);
void sango_battle_status_draw_description(char *text, unsigned int target);
void sango_battle_summary_remember(unsigned int cities, unsigned int characters,
                                   unsigned int city_plus_one);
void sango_battle_summary_draw(unsigned int target);
#endif

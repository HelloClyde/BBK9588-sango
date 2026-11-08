#ifndef SANGO_BATTLE_UI_H
#define SANGO_BATTLE_UI_H
void sango_battle_day_popup_draw(unsigned int day);
void sango_battle_status_draw(void);
void sango_battle_status_draw_weather(unsigned int target);
void sango_battle_status_draw_description(char *text, unsigned int target);
#endif

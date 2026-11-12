#include "sango_internal.h"
#define MARK ((volatile unsigned int*)0x81c3f000)
uint32_t fixture_entry(void){sango_scenario_load(1,g_temp_character_ids_address);uint8_t ids[20];for(int j=0;j<20;j++)ids[j]=j;
sango_display_fill_gray_rectangle(0,0,239,319,2,0);MARK[0]=1;sango_input_wait(0,1);sango_touch_cancel();MARK[0]=2;MARK[1]=sango_city_choose_command_group();
sango_display_fill_gray_rectangle(0,0,239,319,2,0);MARK[0]=3;sango_input_wait(0,1);sango_touch_cancel();MARK[0]=4;MARK[2]=sango_city_choose_domestic_command();
sango_display_fill_gray_rectangle(0,0,239,319,2,0);MARK[0]=5;sango_input_wait(0,1);sango_touch_cancel();MARK[0]=6;MARK[3]=sango_city_choose_diplomacy_command();
sango_display_fill_gray_rectangle(0,0,239,319,2,0);MARK[0]=7;sango_input_wait(0,1);sango_touch_cancel();MARK[0]=8;MARK[4]=sango_city_choose_military_command();
sango_display_fill_gray_rectangle(0,0,239,319,2,0);MARK[0]=9;sango_input_wait(0,1);sango_touch_cancel();MARK[0]=10;MARK[5]=sango_ui_select_character((int)g_temp_character_ids_address,20,4,2,235,181);
sango_display_fill_gray_rectangle(0,0,239,319,2,0);MARK[0]=11;sango_input_wait(0,1);sango_touch_cancel();MARK[0]=12;MARK[6]=sango_ui_select_item((int)ids,20,4,2,235,181);
sango_display_fill_gray_rectangle(0,0,239,319,2,0);MARK[0]=13;sango_input_wait(0,1);sango_touch_cancel();MARK[0]=14;MARK[7]=sango_ui_input_food_amount(123,9999);
sango_display_fill_gray_rectangle(0,0,239,319,2,0);MARK[0]=15;sango_input_wait(0,1);sango_touch_cancel();MARK[0]=16;MARK[8]=sango_ui_show_city_details(0);
MARK[0]=17;sango_input_wait(0,1);return 255;}

#include "sango_internal.h"

/* 月末事件及剧本加载包装。 */

/* 原函数 0x81c1b89c */
void sango_strategy_apply_calendar_events(void)
{
    g_current_month = g_current_month + 1;
    if (0xc < g_current_month)
    {
        g_current_month = 1;
        g_current_year_view2 = g_current_year_view2 + 1;
        sango_strategy_spawn_items_for_year();
        sango_strategy_update_character_ages_and_debut();
    }
    sango_strategy_apply_monthly_economy();
    sango_strategy_apply_disaster_losses();
    sango_strategy_apply_city_disasters();
    return;
}

/* 原函数 0x81c1b91c */
uint32_t sango_scenario_load(char scenario_id, uint8_t *ruler_ids)
{
    uint32_t ruler_count;

    sango_scenario_initialize(scenario_id);
    ruler_count = sango_scenario_collect_rulers(ruler_ids);
    return ruler_count;
}

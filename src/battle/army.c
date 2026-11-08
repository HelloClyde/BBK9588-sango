#include "sango_internal.h"

/* 战场队伍索引与兵力合计。 */

/* 原函数 0x81c001a0 */
void sango_battle_choose_auto_result(void)
{
    uint32_t attacker_troops;
    uint32_t defender_troops;
    bool attacker_wins;
    uint32_t random_percent;

    attacker_troops = bbk_rand();
    random_percent = (int)attacker_troops % 0x65 & 0xff;
    attacker_troops = sango_battle_sum_side_troops('\0');
    if (attacker_troops == 0)
    {
        g_battle_result = 2;
    }
    defender_troops = sango_battle_sum_side_troops('\x01');
    if (defender_troops < attacker_troops)
    {
        attacker_wins = random_percent < 0x1e;
        if (((attacker_troops >> 1 & 0xffff) <= defender_troops) &&
            (attacker_wins = random_percent < 0x3c,
             g_battle_defender_food < g_battle_attacker_food))
        {
            attacker_wins = random_percent < 0x28;
        }
        attacker_wins = !attacker_wins;
    }
    else
    {
        attacker_wins = random_percent < 3;
        if (((defender_troops >> 1 & 0xffff) <= attacker_troops) &&
            (attacker_wins = random_percent < 0x1f,
             g_battle_attacker_food <= g_battle_defender_food))
        {
            attacker_wins = random_percent < 0xb;
        }
    }
    g_battle_result = '\x02' - attacker_wins;
    return;
}

/* 原函数 0x81c002b4 */
uint32_t sango_battle_sum_side_troops(char side)
{
    uint8_t unit_index;
    uint32_t character_id;
    uint8_t slot;
    uint32_t total_troops;

    total_troops = 0;
    slot = 0;
    unit_index = side * '\n';
    do
    {
        if (g_battle_units[unit_index].status != SANGO_UNIT_RETIRED)
        {
            character_id = sango_battle_character_id((uint32_t)unit_index);
            total_troops = total_troops + g_characters[character_id].troops & 0xffff;
        }
        slot = slot + 1;
        unit_index = slot + side * '\n';
    } while (slot < 10);
    return total_troops;
}

/* 原函数 0x81c0036c */
/* 战斗槽位为0～19；阵列保存的是武将ID+1。退场或越界返回255。 */
uint32_t sango_battle_character_id(uint32_t unit_id)
{
    uint32_t unit_index;
    uint32_t character_id;

    unit_index = unit_id & 0xff;
    character_id = 0xff;
    if ((unit_index < SANGO_BATTLE_UNIT_COUNT) &&
        (g_battle_units[unit_index].status != SANGO_UNIT_RETIRED))
    {
        character_id = (uint8_t)(&g_battle_roster_first)[unit_index] - 1 & 0xff;
    }
    return character_id;
}

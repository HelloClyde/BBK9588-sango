#ifndef SANGO_STATE_H
#define SANGO_STATE_H

#include "sango_types.h"

enum
{
    SANGO_SCREEN_WIDTH = 240,
    SANGO_SCREEN_HEIGHT = 320,
    SANGO_CHARACTER_COUNT = 200,
    SANGO_CITY_COUNT = 38,
    SANGO_BATTLE_UNIT_COUNT = 20,
    SANGO_UNITS_PER_SIDE = 10,
    SANGO_ORDER_CAPACITY = 100,
    SANGO_INVALID_ID = 255,
    SANGO_CITY_STRIDE = 36,
    SANGO_CHARACTER_STRIDE = 16,
    SANGO_BATTLE_UNIT_STRIDE = 7,
    SANGO_ORDER_STRIDE = 12
};

/* Character/city indices are zero-based. Ownership and equipped-item fields
 * use 0 for none, and otherwise store index+1. Preserve this distinction. */
typedef struct
{
    uint8_t command_state;
    uint8_t owner;
    uint8_t level;
    uint8_t strength;
    uint8_t intelligence;
    uint8_t loyalty;
    uint8_t reserved6;
    uint8_t experience;
    uint8_t stamina;
    uint8_t troop_type;
    uint16_t troops;
    uint8_t equipped_item1;
    uint8_t equipped_item2;
    uint8_t age;
    uint8_t reserved15;
} SangoCharacter;

typedef struct
{
    uint8_t status;
    uint8_t owner;
    uint8_t governor;
    uint8_t reserved3;
    uint16_t agriculture_limit;
    uint16_t agriculture;
    uint16_t commerce_limit;
    uint16_t commerce;
    uint8_t loyalty;
    uint8_t disaster_prevention;
    uint8_t reserved14[2];
    uint32_t population;
    uint32_t population_limit;
    uint16_t money;
    uint16_t food;
    uint16_t reserve_troops;
    uint8_t character_start;
    uint8_t character_count;
    uint8_t item_start;
    uint8_t item_count;
    uint8_t reserved34[2];
} SangoCity;

enum SangoBattleUnitStatus
{
    SANGO_UNIT_NORMAL,
    SANGO_UNIT_CONFUSED,
    SANGO_UNIT_SILENCED,
    SANGO_UNIT_IMMOBILIZED,
    SANGO_UNIT_QIMEN,
    SANGO_UNIT_DUNJIA,
    SANGO_UNIT_STONE_FORMATION,
    SANGO_UNIT_HIDDEN,
    SANGO_UNIT_RETIRED
};

typedef struct
{
    uint8_t x;
    uint8_t y;
    uint8_t life;
    uint8_t energy;
    uint8_t move_range;
    uint8_t has_acted;
    uint8_t status;
} SangoBattleUnit;

/* 战斗命令前四字节；栈缓冲可能更大，消息和旧ABI仍按原长度传递。 */
typedef struct
{
    uint8_t command;
    uint8_t skill;
    uint8_t actor_unit;
    uint8_t target_unit;
} SangoBattleAction;

typedef struct
{
    uint8_t kind;
    uint8_t character;
    uint8_t source_city;
    uint8_t target;
    uint16_t value0;
    uint16_t value1;
    uint16_t value2;
    uint8_t reserved10;
    uint8_t remaining_months;
} SangoOrder;

typedef struct
{
    uint32_t level_address;
    uint8_t initiative;
    uint8_t terrain;
    uint8_t flags;
    uint8_t troop_type;
    uint32_t experience_address;
    uint32_t troops_address;
    uint16_t attack;
    uint16_t defense;
} SangoCombatant;

_Static_assert(sizeof(SangoCharacter) == SANGO_CHARACTER_STRIDE, "character record");
_Static_assert(offsetof(SangoCharacter, troops) == 10, "character troops");
_Static_assert(sizeof(SangoCity) == SANGO_CITY_STRIDE, "city record");
_Static_assert(offsetof(SangoCity, population) == 16, "city population");
_Static_assert(offsetof(SangoCity, money) == 24, "city money");
_Static_assert(offsetof(SangoCity, character_start) == 30, "city roster");
_Static_assert(sizeof(SangoBattleUnit) == SANGO_BATTLE_UNIT_STRIDE, "battle unit");
_Static_assert(sizeof(SangoBattleAction) == 4, "battle action prefix");
_Static_assert(offsetof(SangoBattleUnit, status) == 6, "battle status");
_Static_assert(sizeof(SangoOrder) == SANGO_ORDER_STRIDE, "order record");
_Static_assert(sizeof(SangoCombatant) == 20, "combatant view");

/* All raw fixed-address views are isolated here. Typed overlays below describe
 * the same storage; they do not allocate or migrate the original save state. */
#include "sango_legacy_memory.h"

#define g_battle_units ((SangoBattleUnit *)0x81c2b280u)
#define g_cities ((SangoCity *)0x81c2b450u)
#define g_characters ((SangoCharacter *)(uintptr_t)g_character_table_address)

#endif

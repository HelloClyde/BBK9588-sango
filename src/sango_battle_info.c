#include "sango_internal.h"

/* A native 240x320 information sheet. Draw into the message context first;
 * the live battlefield remains in g_game_context and is restored on closing. */
__attribute__((noinline)) void sango_battle_info_prepare_canvas(unsigned int target)
{
    bda_handle_t context = (bda_handle_t)target;
    void *white = bda_gui_draw_object_create(15);
    void *black = bda_gui_draw_object_create(16);
    void *old_pen;
    /* The legacy fill helper also touches the visible context. Keep every
     * modal preparation call bound solely to this off-screen context. */
    bda_sango_gui_bind_image_resource(target, (uint32_t)white);
    bda_sango_gui_fill_region(target, 0, 0, 240, 320);
    old_pen = bda_gui_select_draw_object(context, black);
    bda_gui_rectangle(context, 4, 4, 235, 315);
    bda_gui_move_to(context, 12, 76);
    bda_gui_line_to(context, 227, 76);
    bda_gui_select_draw_object(context, old_pen);
}

static void info_text(unsigned int target, int x, int y, const char *text)
{
    sango_color_sdk_text(target, 3, x, y, text);
}

static void info_value(unsigned int target, int column, int row, const char *label,
                       unsigned int value)
{
    char number[12];
    int left = column ? 124 : 12;
    sango_format_integer(value, (uint8_t *)number, 10);
    info_text(target, left, 90 + row * 28, label);
    info_text(target, left + 48, 90 + row * 28, number);
}

static void info_paragraph(unsigned int target, int top, const char *text)
{
    char line[27];
    unsigned int offset = 0, used, last_bytes;
    while (text[offset] && top <= 258)
    {
        used = 0;
        last_bytes = 0;
        while (text[offset] && used < 26)
        {
            unsigned int bytes = (uint8_t)text[offset] >= 0x80 ? 2 : 1;
            if (used + bytes > 26 || (bytes == 2 && !text[offset + 1]))
                break;
            line[used++] = text[offset++];
            if (bytes == 2)
                line[used++] = text[offset++];
            last_bytes = bytes;
        }
        /* Keep Chinese closing punctuation off the start of the next row. */
        if (used > last_bytes &&
            (((uint8_t)text[offset] == 0xa1 &&
              ((uint8_t)text[offset + 1] == 0xa2 || (uint8_t)text[offset + 1] == 0xa3)) ||
             ((uint8_t)text[offset] == 0xa3 &&
              ((uint8_t)text[offset + 1] == 0xa1 || (uint8_t)text[offset + 1] == 0xac ||
               (uint8_t)text[offset + 1] == 0xba || (uint8_t)text[offset + 1] == 0xbb ||
               (uint8_t)text[offset + 1] == 0xbf))))
        {
            used -= last_bytes;
            offset -= last_bytes;
        }
        line[used] = 0;
        if (!used)
            break;
        info_text(target, 12, top, line);
        top += 22;
    }
}

static void info_unit(unsigned int target, unsigned int unit_id)
{
    char name[16], troop_names[32], troop_name[5], status[24];
    SangoCombatant saved;
    unsigned int character_id = sango_battle_resolve_character(unit_id);
    unsigned int attack, defense, troop;
    const SangoCharacter *character;
    const SangoBattleUnit *unit;
    uint8_t *portraits;
    if (character_id >= SANGO_CHARACTER_COUNT)
    {
        info_text(target, 12, 44, "\xd7\xca\xc1\xcf\xb2\xbb\xbf\xc9\xd3\xc3");
        return;
    }
    character = &g_characters[character_id];
    unit = &g_battle_units[unit_id];
    bbk_memcpy(&saved, (void *)&g_attacker_level_address, sizeof(saved));
    sango_battle_prepare_combatant(0, unit_id);
    attack = g_attacker_attack_view2;
    defense = g_attacker_defense;
    bbk_memcpy((void *)&g_attacker_level_address, &saved, sizeof(saved));

    info_text(target, 12, 14, "\xce\xe4\xbd\xab\xd0\xc5\xcf\xa2");
    sango_load_named_text((uint8_t)character_id, name);
    info_text(target, 12, 44, name);
    portraits =
        (uint8_t *)sango_resource_item(g_scenario_id_view2 + 47, 1, g_resource_package_address);
    if (portraits)
        sango_bitmap_draw_frame(196, 14, 24, 24, character_id, portraits, target);
    sango_battle_read_text(12, troop_names);
    troop = character->troop_type & 0x3f;
    if (troop < 6)
    {
        bbk_memcpy(troop_name, troop_names + troop * 4, 4);
        troop_name[4] = 0;
    }
    else
        bbk_memcpy(troop_name, "\xce\xb4\xd6\xaa", 5);
    if (character->level < 20)
        info_value(target, 0, 0, "\xb5\xc8\xbc\xb6", character->level);
    else
    {
        info_text(target, 12, 90, "\xb5\xc8\xbc\xb6");
        info_text(target, 60, 90, "MAX");
    }
    info_text(target, 124, 90, "\xb1\xf8\xd6\xd6");
    info_text(target, 172, 90, troop_name);
    info_value(target, 0, 1, "\xce\xe4\xc1\xa6", character->strength);
    info_value(target, 1, 1, "\xd6\xc7\xc1\xa6", character->intelligence);
    info_value(target, 0, 2, "\xc9\xfa\xc3\xfc", unit->life);
    info_value(target, 1, 2, "\xbc\xbc\xc1\xa6", unit->energy);
    info_value(target, 0, 3, "\xb9\xa5\xbb\xf7", attack);
    info_value(target, 1, 3, "\xb7\xc0\xd3\xf9", defense);
    info_value(target, 0, 4, "\xb1\xf8\xc1\xa6", character->troops);
    info_value(target, 1, 4, "\xbe\xad\xd1\xe9", character->experience);
    info_text(target, 12, 230, "\xd7\xb4\xcc\xac");
    if (unit->status < SANGO_UNIT_RETIRED)
        sango_battle_read_text(unit->status + 28, status);
    else
        bbk_memcpy(status, "\xce\xb4\xd6\xaa", 5);
    info_text(target, 60, 230, status);
}

void sango_battle_info_show(void)
{
    unsigned int target = (uint32_t)g_message_context;
    unsigned int unit_id;
    bool owned = false;
    if (!target)
    {
        target = (uint32_t)bbk_compatible_context_create();
        owned = true;
    }
    if (!target)
        return;
    sango_battle_info_prepare_canvas(target);
    unit_id = sango_battle_find_unit_at(g_battle_cursor_x, g_battle_cursor_y);
    if (unit_id < SANGO_BATTLE_UNIT_COUNT)
        info_unit(target, unit_id);
    else
    {
        char description[160];
        unsigned int terrain = sango_battle_terrain_at(g_battle_cursor_x, g_battle_cursor_y);
        info_text(target, 12, 14, "\xb5\xd8\xd0\xce\xd0\xc5\xcf\xa2");
        if (terrain < 8)
        {
            char name[5];
            const char *body = description;
            sango_battle_read_text(terrain + 14, description);
            if ((uint8_t)description[4] == 0xa3 && (uint8_t)description[5] == 0xba)
            {
                bbk_memcpy(name, description, 4);
                name[4] = 0;
                info_text(target, 12, 44, name);
                body += 6;
            }
            info_paragraph(target, 90, body);
        }
    }
    info_text(target, 56, 290, "\xb5\xe3\xbb\xf7\xbb\xf2\xb0\xb4\xbc\xfc\xb7\xb5\xbb\xd8");
    /* One publish after every field is ready; no per-character screen draws. */
    sango_render_present(target);
    sango_input_wait(0, 1);
    sango_render_present(g_game_context);
    if (owned)
        bbk_compatible_context_free((void *)target);
}

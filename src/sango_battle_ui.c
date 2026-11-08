#include "sango_internal.h"
#include "sango_battle_ui.h"

enum
{
    STATUS_REFERENCE_WIDTH = 160,
    STATUS_FOOD_X = 21,         /* 9288S: 14 */
    STATUS_WEATHER_X = 112,     /* 9288S: 75 */
    STATUS_DESCRIPTION_X = 159, /* 9288S: 106 */
    STATUS_TEXT_TOP = SANGO_BATTLE_STATUS_TOP + 4,
    STATUS_WEATHER_TOP = SANGO_BATTLE_STATUS_TOP + 3,
    STATUS_TEXT_FONT = 3 /* Existing font selector -> native 16-pixel font. */
};

unsigned int sango_battle_animation_left(void)
{
    const SangoBitmapHeader *panel;
    if (!sango_color_is_loaded())
        return 20;
    panel = (const SangoBitmapHeader *)sango_resource_item(16, 1, g_resource_package_address);
    return panel && panel->width <= 240 ? (240 - panel->width) / 2 : 20;
}

short sango_battle_animation_top(void)
{
    const SangoBitmapHeader *panel;
    if (!sango_color_is_loaded())
        return 49;
    panel = (const SangoBitmapHeader *)sango_resource_item(16, 1, g_resource_package_address);
    return panel && panel->height <= SANGO_BATTLE_MAP_HEIGHT
               ? (SANGO_BATTLE_MAP_HEIGHT - panel->height) / 2
               : 49;
}

/* The 9588 port extended resource 8 from 160 to 240 pixels by adding blank
 * columns before the right border. Its labels and separators still occupy
 * the original 160-pixel coordinate system. Scale that logical row, keeping
 * the actual right border, instead of stretching the appended blank area.
 * Weather frames use the same 3:2 mapping. All output uses named SDK bindings. */
static void draw_status_bitmap_region(const SangoBitmapHeader *bitmap, unsigned int frame,
                                      unsigned int reference_width, unsigned int left,
                                      unsigned int top, unsigned int target, unsigned int clip_left,
                                      unsigned int clip_right)
{
    unsigned int row_bytes, plane_bytes, plane_count, width, height, x, y;
    const uint8_t *mask, *colors;
    const uint16_t *rgb;
    bool keyed_alpha;
    if (!bitmap || !reference_width || reference_width > bitmap->width || bitmap->width > 240 ||
        !bitmap->height || bitmap->height > 16 || frame >= bitmap->frames)
        return;
    row_bytes = (bitmap->width + 3) / 4;
    plane_bytes = row_bytes * bitmap->height;
    plane_count = (bitmap->flags & 1) ? 2 : 1;
    mask = (const uint8_t *)(bitmap + 1) + frame * plane_bytes * plane_count;
    colors = mask + ((bitmap->flags & 1) ? plane_bytes : 0);
    rgb = sango_color_pixels((uint32_t)mask, bitmap->width, bitmap->height, bitmap->flags & 1);
    keyed_alpha = rgb && (sango_color_frame_flags((uint32_t)mask, bitmap->width, bitmap->height,
                                                  bitmap->flags & 1) &
                          SANGO_COLOR_TRANSPARENT_ZERO);
    width = reference_width * 3 / 2;
    height = bitmap->height * 3 / 2;
    for (y = 0; y < height; ++y)
    {
        unsigned int source_y = (y * 2 + 1) / 3;
        for (x = 0; x < width; ++x)
        {
            if (left + x < clip_left || left + x >= clip_right)
                continue;
            unsigned int source_x = (x * 2 + 1) / 3;
            unsigned int offset, shift, gray;
            if (source_x == reference_width - 1)
                source_x = bitmap->width - 1;
            offset = source_y * row_bytes + source_x / 4;
            shift = 6 - (source_x % 4) * 2;
            if (!keyed_alpha && (bitmap->flags & 1) && ((mask[offset] >> shift) & 1))
                continue;
            if (rgb)
            {
                if (keyed_alpha && !rgb[source_y * bitmap->width + source_x])
                    continue;
                sango_color_put_pixel(left + x, top + y, rgb[source_y * bitmap->width + source_x],
                                      target);
                continue;
            }
            gray = (colors[offset] >> shift) & 3;
            sango_display_put_gray_pixel((short)(left + x), (short)(top + y), gray, target);
        }
    }
}

static void draw_status_bitmap(const SangoBitmapHeader *bitmap, unsigned int frame,
                               unsigned int reference_width, unsigned int left, unsigned int top,
                               unsigned int target)
{
    draw_status_bitmap_region(bitmap, frame, reference_width, left, top, target, 0, 240);
}

static void restore_status_image(unsigned int left, unsigned int right, unsigned int target)
{
    const SangoBitmapHeader *background =
        (const SangoBitmapHeader *)sango_resource_item(8, 1, g_resource_package_address);
    draw_status_bitmap_region(background, 0, STATUS_REFERENCE_WIDTH, 0, SANGO_BATTLE_STATUS_TOP,
                              target, left, right);
}

static void draw_status_text(unsigned int x, char *text, unsigned int target)
{
    /* The last field fits four full GBK characters at 16 pixels. Keep a
     * complete character boundary even if a malformed string is supplied. */
    char visible[10];
    unsigned int bytes = 0, limit = (237 - x) / 8;
    if (!text)
        return;
    if (limit > sizeof(visible) - 1)
        limit = sizeof(visible) - 1;
    while (text[bytes] && bytes < limit)
    {
        unsigned int character_bytes = ((uint8_t)text[bytes] & 0x80) ? 2 : 1;
        if (bytes + character_bytes > limit || (character_bytes == 2 && !text[bytes + 1]))
            break;
        visible[bytes] = text[bytes];
        if (character_bytes == 2)
            visible[bytes + 1] = text[bytes + 1];
        bytes += character_bytes;
    }
    visible[bytes] = 0;
    if (sango_color_is_loaded())
    {
        sango_color_sdk_text(target, STATUS_TEXT_FONT, x, STATUS_TEXT_TOP, visible);
        return;
    }
    sango_display_select_font(STATUS_TEXT_FONT, target);
    sango_text_draw_native((short)x, STATUS_TEXT_TOP, visible, target);
    sango_display_select_font(0, target);
}

void sango_battle_status_draw_weather(unsigned int target)
{
    const SangoBitmapHeader *weather =
        (const SangoBitmapHeader *)sango_resource_item(9, 1, g_resource_package_address);
    if (g_battle_weather == 0)
        return;
    if (sango_color_is_loaded())
        restore_status_image(STATUS_WEATHER_X, STATUS_WEATHER_X + 18, target);
    draw_status_bitmap(weather, g_battle_weather - 1, 12, STATUS_WEATHER_X, STATUS_WEATHER_TOP,
                       target);
}

void sango_battle_status_draw(void)
{
    char food[16];
    const SangoBitmapHeader *background =
        (const SangoBitmapHeader *)sango_resource_item(8, 1, g_resource_package_address);
    draw_status_bitmap(background, 0, STATUS_REFERENCE_WIDTH, 0, SANGO_BATTLE_STATUS_TOP,
                       g_game_context);
    sango_format_integer((uint32_t)g_battle_attacker_food, (uint8_t *)food, 10);
    draw_status_text(STATUS_FOOD_X, food, g_game_context);
    sango_battle_status_draw_weather(g_game_context);
    sango_battle_toolbar_draw(g_game_context);
    sango_battle_summary_draw(g_game_context);
}

/* The stock 9288S battle paints over the strategy map's upper area, leaving
 * its ruler/counts/date/city summary visible. Remember that last map summary,
 * rather than recounting troops or changing shared gameplay scratch buffers
 * on every battle redraw. This UI cache is outside the saved legacy state. */
static struct
{
    uint16_t year;
    uint8_t month, ruler, scenario, cities, characters, city_plus_one;
    bool valid;
} battle_summary;

void sango_battle_summary_remember(unsigned int cities, unsigned int characters,
                                   unsigned int city_plus_one)
{
    battle_summary.year = g_current_year;
    battle_summary.month = g_current_month;
    battle_summary.ruler = g_player_character;
    battle_summary.scenario = g_scenario_id_view2;
    battle_summary.cities = cities;
    battle_summary.characters = characters;
    battle_summary.city_plus_one = city_plus_one;
    battle_summary.valid = true;
}

void sango_battle_summary_draw(unsigned int target)
{
    char text[24], suffix[8];
    uint8_t *portraits, *icons;
    unsigned int top = SANGO_BATTLE_SUMMARY_TOP + 5;
    if (!battle_summary.valid)
        return;
    portraits =
        (uint8_t *)sango_resource_item(battle_summary.scenario + 47, 1, g_resource_package_address);
    icons = (uint8_t *)sango_resource_item(69, 1, g_resource_package_address);
    sango_bitmap_draw_frame(31, top + 1, 24, 24, battle_summary.ruler, portraits, target);
    sango_bitmap_draw_frame(79, top + 1, 7, 9, 1, icons, target);
    sango_format_integer(battle_summary.cities, text, 10);
    sango_text_draw_context(94, top, text, target);
    sango_bitmap_draw_frame(79, top + 16, 7, 9, 0, icons, target);
    sango_format_integer(battle_summary.characters, text, 10);
    sango_text_draw_context(94, top + 14, text, target);
    sango_format_integer(battle_summary.year, text, 10);
    sango_resource_read_text(64, 63, suffix);
    bbk_strcat(text, suffix);
    sango_text_draw_context(123, top, text, target);
    sango_format_integer(battle_summary.month, text, 10);
    sango_resource_read_text(64, 64, suffix);
    bbk_strcat(text, suffix);
    sango_text_draw_context(123, top + 14, text, target);
    if (battle_summary.city_plus_one != 0)
    {
        sango_city_read_name(battle_summary.city_plus_one - 1, text);
        sango_text_draw_context(180, top + 7, text, target);
    }
}

void sango_battle_status_draw_description(char *text, unsigned int target)
{
    if (sango_color_is_loaded())
        restore_status_image(STATUS_DESCRIPTION_X, 238, target);
    else
        sango_render_clear_rectangle(STATUS_DESCRIPTION_X, SANGO_BATTLE_STATUS_TOP + 2, 237,
                                     SANGO_BATTLE_STATUS_TOP + SANGO_BATTLE_STATUS_HEIGHT - 3,
                                     target);
    draw_status_text(STATUS_DESCRIPTION_X, text, target);
}

void sango_battle_day_popup_draw(unsigned int day)
{
    uint8_t *bitmap = (uint8_t *)sango_resource_item(33, 1, *(uint32_t *)0x81c2b154u);
    unsigned int width, height, left, top, digits_width;
    char digits[12];
    if (!bitmap)
        return;
    width = (unsigned int)bitmap[0] + ((unsigned int)bitmap[1] << 8);
    height = (unsigned int)bitmap[2] + ((unsigned int)bitmap[3] << 8);
    if (!width || width > 240 || height < 12 || height > 320)
        return;
    left = (240 - width) / 2;
    top = (320 - height) / 2;
    sango_bitmap_draw_resource(33, 1, left, (short)top, 1);
    sango_format_integer(day, digits, 10);
    digits_width = bbk_strlen(digits) * 6;
    if (digits_width > width)
        return;
    sango_text_draw_legacy((uint16_t)(left + (width - digits_width) / 2),
                           (uint16_t)(top + (height - 12) / 2), digits);
}

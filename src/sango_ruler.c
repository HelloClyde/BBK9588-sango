#include "sango_internal.h"
#include "sango_ruler_portraits.inc"

/* Presentation state only, outside the original save/global memory region. */
static unsigned int page_background, page_count;

static int draw_picture(unsigned int resource, unsigned int frame, int x, int y)
{
    /* Original LIB descriptors can start at odd byte addresses. */
    uint8_t *bitmap = (uint8_t *)sango_resource_item(resource, 1, g_resource_package_address);
    if (!bitmap || frame >= bitmap[4])
        return 0;
    unsigned int width = bitmap[0] | (unsigned int)bitmap[1] << 8;
    unsigned int height = bitmap[2] | (unsigned int)bitmap[3] << 8;
    sango_bitmap_draw_frame(x, y, width, height, frame, bitmap, 0);
    return 1;
}

/* Transparent native16px type: full name per call, no per-character refresh. */
__attribute__((noinline)) void sango_ruler_sdk_text(int x, int y, const char *text, int selected)
{
    bda_handle_t context = (bda_handle_t)g_draw_context;
    int old_mode, old_color;
    sango_color_sdk_guard(1);
    old_mode = bda_gui_set_text_mode(context, 1);
    old_color = bda_gui_set_text_color(context, selected ? bda_gui_rgb(context, 255, 230, 181)
                                                         : bda_gui_rgb(context, 24, 20, 8));
    sango_display_select_font(3, (uint32_t)context);
    bda_gui_draw_text(context, x, y, text, -1);
    sango_display_select_font(0, (uint32_t)context);
    bda_gui_set_text_color(context, old_color);
    bda_gui_set_text_mode(context, old_mode);
    sango_color_sdk_guard(0);
}

static void restore_rectangle(int left, int top, int right, int bottom)
{
    if (page_background)
        sango_color_sdk_restore(page_background, left, top, right, bottom, g_draw_context);
}

static void draw_row(unsigned int index, unsigned int first, int selected)
{
    char name[7];
    int top = SANGO_RULER_LIST_TOP + (index - first) * SANGO_RULER_ROW_HEIGHT;
    restore_rectangle(28, top, 83, top + 17);
    if (selected)
        draw_picture(77, 0, 28, top);
    for (unsigned int i = 0; i < 6; ++i)
        name[i] = g_move_costs_address_view3[index * 6 + i];
    name[6] = 0;
    sango_ruler_sdk_text(32, top + 1, name, selected);
}

void sango_ruler_draw_names(unsigned int first)
{
    for (unsigned int row = 0; row < SANGO_RULER_ROWS && first + row < page_count; ++row)
        draw_row(first + row, first, 0);
}

unsigned int sango_ruler_end(unsigned int result)
{
    /* Borrowed application canvas; its owner frees it at game shutdown. */
    page_background = page_count = 0;
    return result;
}

void sango_ruler_begin(unsigned int count)
{
    sango_ruler_end(255);
    page_count = count;
    if (!draw_picture(52, 0, 0, 0))
        sango_display_fill_gray_rectangle(0, 0, 239, 319, 0, 0);
    page_background = g_game_context;
    if (page_background)
        sango_color_sdk_restore(g_draw_context, 0, 0, 239, 319, page_background);
    draw_picture(47, 0, SANGO_RULER_MAP_X, SANGO_RULER_MAP_Y);
}

void sango_ruler_update(unsigned int character)
{
    char name[16];
    unsigned int scenario = g_scenario_id_view2;
    int drawn = 0;
    restore_rectangle(126, 164, 188, 218);
    restore_rectangle(100, 231, 212, 250);
    if (scenario >= 1 && scenario <= 4 && character < 19)
    {
        unsigned int frame = ruler_portrait_frames[scenario - 1][character];
        if (frame != 255)
            drawn = draw_picture(53, frame, 133, 168);
    }
    if (!drawn && scenario >= 1 && scenario <= 4 && character < SANGO_CHARACTER_COUNT)
    {
        uint8_t *portraits =
            (uint8_t *)sango_resource_item(scenario + 47, 1, g_resource_package_address);
        if (portraits)
            sango_bitmap_draw_frame(145, 180, 24, 24, character, portraits, 0);
    }
    sango_load_named_text(character, name);
    sango_ruler_sdk_text(157 - sango_crt_strlen(name) * 4, 232, name, 0);
}

void sango_ruler_select(unsigned int previous, unsigned int previous_first, unsigned int selected,
                        unsigned int first)
{
    if (!page_background)
    {
        /* Low-memory fallback keeps the page correct by repainting its art. */
        if (!draw_picture(52, 0, 0, 0))
            sango_display_fill_gray_rectangle(0, 0, 239, 319, 0, 0);
        sango_menu_draw_ruler_names(first);
        draw_picture(47, 0, SANGO_RULER_MAP_X, SANGO_RULER_MAP_Y);
    }
    else if (first != previous_first)
    {
        restore_rectangle(28, 64, 83, 243);
        sango_menu_draw_ruler_names(first);
    }
    else
        draw_row(previous, previous_first, 0);
    draw_row(selected, first, 1);
    sango_ruler_update(g_temp_character_ids_address[selected]);
}

int sango_ruler_touch_button(const int *event)
{
    if (event[0] != SANGO_TOUCH_TAP && event[0] != SANGO_TOUCH_HOLD)
        return 0;
    int x = sango_touch_x(event), y = sango_touch_y(event);
    if (y < 267 || y > 294)
        return 0;
    if (x >= 24 && x <= 104)
        return BDA_KEY_ESCAPE;
    if (x >= 136 && x <= 218)
        return BDA_KEY_ENTER;
    return 0;
}

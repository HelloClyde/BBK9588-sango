#include "sango_internal.h"
#include "sango_ruler_portraits.inc"

enum { DIRTY_FULL = 1, DIRTY_LIST = 2, DIRTY_MAP = 4, DIRTY_PREVIEW = 8 };
/* Borrow application surfaces, keep the window untouched until presentation. */
static unsigned int page_background, page_canvas, page_window, page_count;
static unsigned int page_owned, page_dirty, cities_visible;
static int dirty_top, dirty_bottom;

__attribute__((noinline)) void sango_ruler_sdk_picture(unsigned int target, int x, int y,
                                                       unsigned int width, unsigned int height,
                                                       const uint16_t *pixels)
{
    bda_gui_picture_t picture = {0};
    bda_handle_t context = (bda_handle_t)target;
    picture.width = width;
    picture.height = height;
    picture.source_pixels = pixels;
    picture.selected_index = -1;
    void *old = bda_gui_select_draw_object(context, bda_gui_draw_object_create(7));
    bda_gui_render_picture(context, x, y, width, height, &picture);
    bda_gui_select_draw_object(context, old);
}

static unsigned int canvas(void)
{
    return page_canvas ? page_canvas : g_draw_context;
}

static int draw_picture(unsigned int resource, unsigned int frame, int x, int y,
                         unsigned int target)
{
    uint8_t *bitmap = (uint8_t *)sango_resource_item(resource, 1, g_resource_package_address);
    if (!bitmap || frame >= bitmap[4])
        return 0;
    /* LIB descriptors may be unaligned; validated RGB565 payloads are not. */
    unsigned int width = bitmap[0] | (unsigned int)bitmap[1] << 8;
    unsigned int height = bitmap[2] | (unsigned int)bitmap[3] << 8;
    unsigned int stride = ((width + 3) / 4) * height * ((bitmap[5] & 1) ? 2 : 1);
    unsigned int source = (unsigned int)(bitmap + 6 + frame * stride);
    const uint16_t *pixels = sango_color_pixels(source, width, height, bitmap[5] & 1);
    if (pixels && !(bitmap[5] & 1) &&
        !(sango_color_frame_flags(source, width, height, 0) & SANGO_COLOR_TRANSPARENT_ZERO))
        sango_ruler_sdk_picture(target, x, y, width, height, pixels);
    else
        sango_bitmap_draw_frame(x, y, width, height, frame, bitmap, target);
    return 1;
}

__attribute__((noinline)) void sango_ruler_sdk_text_at(unsigned int target, int x, int y,
                                                       const char *text, int selected)
{
    bda_handle_t context = (bda_handle_t)target;
    int mode = bda_gui_set_text_mode(context, 1);
    int color = bda_gui_set_text_color(context, selected ? bda_gui_rgb(context, 255, 230, 181)
                                                        : bda_gui_rgb(context, 24, 20, 8));
    sango_display_select_font(3, target);
    bda_gui_draw_text(context, x, y, text, -1);
    sango_display_select_font(0, target);
    bda_gui_set_text_color(context, color);
    bda_gui_set_text_mode(context, mode);
}

/* Existing settings-page text boundary retains its visible draw guard. */
__attribute__((noinline)) void sango_ruler_sdk_text(int x, int y, const char *text, int selected)
{
    sango_color_sdk_guard(1);
    sango_ruler_sdk_text_at(g_draw_context, x, y, text, selected);
    sango_color_sdk_guard(0);
}

__attribute__((noinline)) void sango_ruler_sdk_present(unsigned int source, unsigned int window,
                                                       unsigned int dirty, int top, int bottom)
{
    sango_color_sdk_guard(1);
    if (source != window)
    {
        if (dirty & DIRTY_FULL)
            sango_color_sdk_restore(source, 0, 0, 239, 319, window);
        else
        {
            if (dirty & DIRTY_LIST)
                sango_color_sdk_restore(source, 28, top, 83, bottom, window);
            if (dirty & DIRTY_MAP)
                sango_color_sdk_restore(source, 118, 64, 201, 127, window);
            if (dirty & DIRTY_PREVIEW)
            {
                sango_color_sdk_restore(source, 126, 164, 188, 218, window);
                sango_color_sdk_restore(source, 100, 231, 212, 250, window);
            }
        }
    }
    bda_sango_gui_request_redraw(g_app_frame, 0, 0);
    sango_color_sdk_guard(0);
}

void sango_ruler_present(void)
{
    if (!page_dirty)
        return;
    sango_ruler_sdk_present(canvas(), page_window, page_dirty, dirty_top, dirty_bottom);
    page_dirty = 0;
    dirty_top = 320;
    dirty_bottom = 0;
}

static void restore_rectangle(int left, int top, int right, int bottom)
{
    if (page_background)
        sango_color_sdk_restore(page_background, left, top, right, bottom, canvas());
}

static void draw_row(unsigned int index, unsigned int first, int selected)
{
    char name[7];
    int top = SANGO_RULER_LIST_TOP + (index - first) * SANGO_RULER_ROW_HEIGHT;
    restore_rectangle(28, top, 83, top + 17);
    if (selected)
        draw_picture(77, 0, 28, top, canvas());
    for (unsigned int i = 0; i < 6; ++i)
        name[i] = g_move_costs_address_view3[index * 6 + i];
    name[6] = 0;
    sango_ruler_sdk_text_at(canvas(), 32, top + 1, name, selected);
    if (top < dirty_top)
        dirty_top = top;
    if (top + 17 > dirty_bottom)
        dirty_bottom = top + 17;
    page_dirty |= DIRTY_LIST;
}

void sango_ruler_draw_names(unsigned int first)
{
    for (unsigned int row = 0; row < SANGO_RULER_ROWS && first + row < page_count; ++row)
        draw_row(first + row, first, 0);
}

unsigned int sango_ruler_end(unsigned int result)
{
    if (page_owned)
        sango_color_sdk_snapshot_free(page_canvas);
    page_background = page_canvas = page_window = page_count = page_owned = 0;
    page_dirty = cities_visible = 0;
    return result;
}

void sango_ruler_begin(unsigned int count)
{
    sango_ruler_end(255);
    sango_touch_cancel();
    page_count = count;
    page_window = g_draw_context;
    page_background = g_game_context;
    page_canvas = g_aux_context ? g_aux_context : (unsigned int)g_message_context;
    if (!page_canvas || page_canvas == page_background || page_canvas == page_window)
    {
        page_canvas = sango_color_sdk_snapshot(page_window);
        page_owned = page_canvas != 0;
    }
    if (!page_canvas)
        page_canvas = page_window;
    if (page_background == page_canvas || page_background == page_window)
        page_background = 0;
    unsigned int background = page_background ? page_background : canvas();
    if (page_canvas == page_window)
        sango_color_sdk_guard(1);
    if (!draw_picture(52, 0, 0, 0, background))
        sango_display_fill_gray_rectangle(0, 0, 239, 319, 0, background);
    draw_picture(47, 0, SANGO_RULER_MAP_X, SANGO_RULER_MAP_Y, background);
    if (page_background)
        restore_rectangle(0, 0, 239, 319);
    page_dirty = DIRTY_FULL;
    dirty_top = 320;
    dirty_bottom = 0;
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
            drawn = draw_picture(53, frame, 133, 168, canvas());
    }
    if (!drawn && scenario >= 1 && scenario <= 4 && character < SANGO_CHARACTER_COUNT)
    {
        uint8_t *portraits = (uint8_t *)sango_resource_item(scenario + 47, 1, g_resource_package_address);
        if (portraits)
            sango_bitmap_draw_frame(145, 180, 24, 24, character, portraits, canvas());
    }
    sango_load_named_text(character, name);
    sango_ruler_sdk_text_at(canvas(), 157 - sango_crt_strlen(name) * 4, 232, name, 0);
    page_dirty |= DIRTY_PREVIEW;
}

void sango_ruler_select(unsigned int previous, unsigned int previous_first, unsigned int selected,
                        unsigned int first)
{
    if (page_canvas == page_window)
        sango_color_sdk_guard(1);
    if (!page_background && !(page_dirty & DIRTY_FULL))
    {
        draw_picture(52, 0, 0, 0, canvas());
        draw_picture(47, 0, SANGO_RULER_MAP_X, SANGO_RULER_MAP_Y, canvas());
        sango_menu_draw_ruler_names(first);
        page_dirty |= DIRTY_FULL;
    }
    else if (first != previous_first)
    {
        restore_rectangle(28, 64, 83, 243);
        sango_menu_draw_ruler_names(first);
    }
    else if (!(page_dirty & DIRTY_FULL))
        draw_row(previous, previous_first, 0);
    restore_rectangle(118, 64, 201, 127);
    cities_visible = 0;
    page_dirty |= DIRTY_MAP;
    draw_row(selected, first, 1);
    sango_ruler_update(g_temp_character_ids_address[selected]);
}

void sango_ruler_flash_cities(unsigned int count, const uint8_t *cities, int positions)
{
    if (!page_count)
        return;
    if (page_canvas == page_window)
        sango_color_sdk_guard(1);
    if (page_background)
        restore_rectangle(118, 64, 201, 127);
    else
        draw_picture(47, 0, SANGO_RULER_MAP_X, SANGO_RULER_MAP_Y, canvas());
    cities_visible = !cities_visible;
    uint8_t *map = (uint8_t *)sango_resource_item(47, 1, g_resource_package_address);
    const uint16_t *pixels = map ? sango_color_pixels((unsigned int)(map + 6), 84, 64, map[5] & 1) : 0;
    for (unsigned int city = 0; map && cities_visible && city < count && city < 40; ++city)
    {
        const uint8_t *position = (uint8_t *)positions + (cities[city] & 0x7f) * 2;
        int x = position[0] * 7 + 3, y = position[1] * 7 + 3;
        if (x + 1 >= 84 || y + 1 >= 64)
            continue;
        for (int row = y; row <= y + 1; ++row)
            for (int col = x; col <= x + 1; ++col)
            {
                uint16_t color;
                if (pixels)
                    color = pixels[row * 84 + col];
                else
                {
                    unsigned int gray = (map[6 + row * 21 + col / 4] >> (6 - (col % 4) * 2)) & 3;
                    color = (uint16_t)(((gray * 31 / 3) << 11) | ((gray * 63 / 3) << 5) | (gray * 31 / 3));
                }
                sango_color_sdk_pixel(canvas(), SANGO_RULER_MAP_X + col,
                                      SANGO_RULER_MAP_Y + row, color ^ 0xffff);
            }
    }
    page_dirty |= DIRTY_MAP;
    sango_ruler_present();
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

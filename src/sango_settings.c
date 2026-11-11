#include "bda_sdk.h"
#include "sango_internal.h"

/* Presentation/preferences only; never part of the recovered save region. */
static char settings_path[224];
static unsigned int settings_dirty;

__attribute__((noinline)) int sango_settings_sdk_read(void *bytes, unsigned int size)
{
    int file = bda_fs_fopen_raw(settings_path, "rb");
    if (!bda_fs_file_is_valid(file))
        return 0;
    int got = bda_fs_read_raw(file, bytes, size);
    bda_fs_close_raw(file);
    return got;
}

__attribute__((noinline)) int sango_settings_sdk_write(const void *bytes, unsigned int size)
{
    int file = bda_fs_fopen_raw(settings_path, "wb");
    if (!bda_fs_file_is_valid(file))
        return 0;
    int wrote = bda_fs_write_raw(file, bytes, size);
    bda_fs_close_raw(file);
    bda_fs_flush_all();
    return wrote;
}

void sango_settings_load(const char *library_path)
{
    uint8_t bytes[8];
    unsigned int length = 0, last = 0;
    settings_path[0] = 0;
    settings_dirty = 0;
    while (library_path[length])
    {
        if (length >= 200)
            return;
        if (library_path[length] == '/' || library_path[length] == '\\')
            last = length + 1;
        ++length;
    }
    for (unsigned int i = 0; i < last; ++i)
        settings_path[i] = library_path[i];
    const char *name = "sango.cfg";
    for (unsigned int i = 0;; ++i)
    {
        settings_path[last + i] = name[i];
        if (!name[i])
            break;
    }
    if (sango_settings_sdk_read(bytes, sizeof(bytes)) == sizeof(bytes) &&
        bytes[0] == 'S' && bytes[1] == 'G' && bytes[2] == 'S' && bytes[3] == 1 &&
        bytes[4] <= 1 && bytes[5] <= 10 && !bytes[6] &&
        bytes[7] == (uint8_t)(0xa5 ^ bytes[4] ^ bytes[5]))
    {
        sango_music_set_volume(bytes[5]);
        sango_music_set_enabled(bytes[4]);
    }
}

void sango_settings_save(void)
{
    uint8_t bytes[8] = {'S', 'G', 'S', 1, 0, 0, 0, 0};
    if (!settings_dirty || !settings_path[0])
        return;
    bytes[4] = sango_music_is_enabled();
    bytes[5] = sango_music_get_volume();
    bytes[7] = 0xa5 ^ bytes[4] ^ bytes[5];
    if (sango_settings_sdk_write(bytes, sizeof(bytes)) == sizeof(bytes))
        settings_dirty = 0;
}

void sango_settings_draw(unsigned int selected)
{
    static const short focus[4][4] = {
        {22, 70, 218, 116}, {22, 128, 218, 196},
        {22, 208, 218, 252}, {66, 265, 174, 299}};
    char percent[5];
    unsigned int level = sango_music_get_volume();
    unsigned int count = 0;
    sango_ui_paint_begin();
    sango_bitmap_draw_resource(SANGO_SETTINGS_RESOURCE, 1, 0, 0, 1);
    sango_ruler_sdk_text(176, 84, sango_music_is_enabled() ? "\xbf\xaa" : "\xb9\xd8", 0);
    if (level == 10)
        percent[count++] = '1';
    percent[count++] = '0' + level % 10;
    if (level)
        percent[count++] = '0';
    percent[count++] = '%';
    percent[count] = 0;
    sango_ruler_sdk_text(120 - count * 4, 168, percent, 0);
    if (selected < 4)
        sango_display_draw_rectangle(focus[selected][0], focus[selected][1],
                                     focus[selected][2], focus[selected][3], 3, 0, 0);
    sango_ui_paint_end();
}

/* Negative values mean no hit;0=music,1/2=volume minus/plus,3=credits,4=back. */
int sango_settings_touch(const int *event)
{
    if (event[0] != SANGO_TOUCH_TAP)
        return -1;
    int x = sango_touch_x(event), y = sango_touch_y(event);
    if (x >= 24 && x <= 216 && y >= 72 && y <= 114)
        return 0;
    if (y >= 162 && y <= 188)
    {
        if (x >= 32 && x <= 66)
            return 1;
        if (x >= 174 && x <= 208)
            return 2;
    }
    if (x >= 24 && x <= 216 && y >= 210 && y <= 250)
        return 3;
    if (x >= 68 && x <= 172 && y >= 267 && y <= 297)
        return 4;
    return -1;
}

void sango_settings_show(void)
{
    int event[6];
    unsigned int selected = 0;
    sango_settings_draw(selected);
    for (;;)
    {
        int action = -1;
        sango_input_next_event(event);
        if (event[0] == SANGO_TOUCH_TAP)
            action = sango_settings_touch(event);
        else if (event[0] == 5)
        {
            unsigned int key = (unsigned int)event[1];
            if (key == BDA_KEY_ESCAPE)
                action = 4;
            else if (key == BDA_KEY_UP || key == BDA_KEY_DOWN)
            {
                selected = (selected + (key == BDA_KEY_UP ? 3 : 1)) & 3;
                sango_settings_draw(selected);
            }
            else if (key == BDA_KEY_LEFT || key == BDA_KEY_RIGHT)
            {
                if (selected == 1)
                    action = key == BDA_KEY_LEFT ? 1 : 2;
                else if (selected == 0 &&
                         sango_music_is_enabled() != (key == BDA_KEY_RIGHT))
                    action = 0;
            }
            else if (key == BDA_KEY_ENTER)
                action = selected == 0 ? 0 : selected == 1 ? 2 : selected + 1;
        }
        if (action == 4)
        {
            sango_settings_save();
            sango_touch_cancel();
            return;
        }
        if (action < 0)
            continue;
        if (action == 3)
        {
            selected = 2;
            sango_menu_show_credits();
        }
        else if (action == 0)
        {
            selected = 0;
            sango_music_set_enabled(!sango_music_is_enabled());
            settings_dirty = 1;
        }
        else
        {
            unsigned int level = sango_music_get_volume();
            selected = 1;
            if (action == 1 && level)
                --level;
            else if (action == 2 && level < 10)
                ++level;
            sango_music_set_volume(level);
            settings_dirty = 1;
        }
        sango_settings_draw(selected);
    }
}

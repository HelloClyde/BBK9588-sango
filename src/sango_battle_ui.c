#include "sango_internal.h"
#include "sango_battle_ui.h"

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

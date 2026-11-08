#include "sango_internal.h"
#include "sango_color.h"

/* Optional RGB565 companion for the unmodified indexed sango.lib. This cache
 * lives outside the legacy saved state. All display calls use named SDK APIs. */
static uint8_t *color_file;
static uint32_t color_entries, color_library_bytes;
static bool color_file_owned;
static uint32_t strategy_map_context;
static const uint16_t *native_status;
static uint32_t native_status_source;

static uint32_t color_read32(const uint8_t *bytes)
{
    return (uint32_t)bytes[0] | ((uint32_t)bytes[1] << 8) | ((uint32_t)bytes[2] << 16) |
           ((uint32_t)bytes[3] << 24);
}

static uint16_t color_read16(const uint8_t *bytes)
{
    return (uint16_t)((uint16_t)bytes[0] | ((uint16_t)bytes[1] << 8));
}

static uint32_t color_crc32(const uint8_t *bytes, uint32_t size)
{
    uint32_t crc = 0xffffffffu, offset, bit;
    for (offset = 0; offset < size; ++offset)
    {
        crc ^= bytes[offset];
        for (bit = 0; bit < 8; ++bit)
            crc = (crc >> 1) ^ ((0u - (crc & 1u)) & 0xedb88320u);
    }
    return ~crc;
}

int sango_color_is_loaded(void)
{
    return color_file != NULL;
}

void sango_color_unload(void)
{
    sango_color_animation_end(0);
    if (color_file_owned && color_file)
        bbk_free_if_nonnull(color_file);
    color_file = NULL;
    native_status = NULL;
    native_status_source = 0;
    strategy_map_context = 0;
    color_entries = color_library_bytes = 0;
    color_file_owned = false;
}

/* The file loader owns its allocation; a verifier may also lend an exact
 * buffer. Bounds and LIB identity are validated before any colored rendering. */
int sango_color_use_buffer(void *buffer, uint32_t bytes, uint32_t library_bytes)
{
    const uint8_t magic[] = {'S', 'G', 'C', 'O', 'L', 'O', 'R', '1'};
    uint8_t *data = (uint8_t *)buffer;
    uint32_t count, payload, index, previous = 0, indexed_end = 0;
    sango_color_unload();
    if (!data || bytes < 32 || bytes > 16u * 1024u * 1024u)
        return 0;
    for (index = 0; index < sizeof(magic); ++index)
        if (data[index] != magic[index])
            return 0;
    count = color_read32(data + 12);
    payload = color_read32(data + 20);
    if (color_read32(data + 8) != bytes || color_read32(data + 16) != 32 || !count ||
        count > 4096 || payload != 32 + count * 16 || payload > bytes ||
        color_read32(data + 24) != library_bytes ||
        color_read32(data + 28) !=
            color_crc32((const uint8_t *)g_resource_package_address, library_bytes))
        return 0;
    for (index = 0; index < count; ++index)
    {
        const uint8_t *entry = data + 32 + index * 16;
        uint32_t source = color_read32(entry), pixels = color_read32(entry + 4);
        uint32_t width = color_read16(entry + 8), height = color_read16(entry + 10);
        uint32_t flags = color_read32(entry + 12), raw_bytes;
        if (!width || width > 320 || !height || height > 320 ||
            ((flags & ~SANGO_COLOR_TRANSPARENT_ZERO) != 0 &&
             (flags & ~SANGO_COLOR_TRANSPARENT_ZERO) != 1 &&
             (flags & ~SANGO_COLOR_TRANSPARENT_ZERO) != 32 &&
             (flags & ~SANGO_COLOR_TRANSPARENT_ZERO) != 33))
            return 0;
        raw_bytes = ((width + 3) / 4) * height * ((flags & 1) ? 2 : 1);
        if ((index && source <= previous) || source > library_bytes ||
            raw_bytes > library_bytes - source || (pixels & 1) || pixels < payload ||
            pixels > bytes || width * height * 2 > bytes - pixels)
            return 0;
        previous = source;
        if (pixels + width * height * 2 > indexed_end)
            indexed_end = pixels + width * height * 2;
    }
    /* Optional native-size image trailer; older SGCOLOR1 files remain valid.
     * No original indexed frame, mask, LIB record or saved state is changed. */
    if (bytes >= 64)
    {
        const uint8_t tag[] = {'S', 'G', 'H', 'U', 'D', '0', '1', 0};
        const uint8_t *trailer = data + bytes - 32;
        for (index = 0; index < sizeof(tag) && trailer[index] == tag[index]; ++index)
            ;
        if (index == sizeof(tag))
        {
            uint32_t offset = color_read32(trailer + 8), source = color_read32(trailer + 24);
            bool found = false;
            if ((offset & 1) || offset < indexed_end || offset > bytes - 32 ||
                color_read32(trailer + 12) != 11520 || bytes - 32 - offset != 11520 ||
                color_read32(trailer + 16) != 240 || color_read32(trailer + 20) != 24 ||
                color_crc32(data + offset, 11520) != color_read32(trailer + 28))
                return 0;
            for (index = 0; index < count; ++index)
            {
                const uint8_t *entry = data + 32 + index * 16;
                if (color_read32(entry) == source && color_read16(entry + 8) == 240 &&
                    color_read16(entry + 10) == 16)
                    found = true;
            }
            if (!found)
                return 0;
            native_status = (const uint16_t *)(data + offset);
            native_status_source = source;
        }
    }
    color_file = data;
    color_entries = count;
    color_library_bytes = library_bytes;
    return 1;
}

const uint16_t *sango_color_native_status(uint32_t original_pixels)
{
    return color_file && original_pixels >= g_resource_package_address &&
                   original_pixels - g_resource_package_address == native_status_source
               ? native_status
               : NULL;
}

void sango_color_load(const char *library_path, uint32_t library_bytes)
{
    char path[256];
    uint32_t length, size;
    void *file, *buffer;
    sango_color_unload();
    length = bbk_strlen((char *)library_path);
    if (length < 4 || length >= sizeof(path))
        return;
    bbk_memcpy(path, (void *)library_path, length + 1);
    path[length - 3] = 'c';
    path[length - 2] = 'l';
    path[length - 1] = 'r';
    file = bbk_fopen(path, "rb");
    if (!file)
        return;
    bbk_fseek(file, 0, 2);
    size = bbk_ftell(file);
    if (size < 32 || size > 16u * 1024u * 1024u)
    {
        bbk_fclose(file);
        return;
    }
    buffer = bbk_alloc(size);
    if (!buffer)
    {
        bbk_fclose(file);
        return;
    }
    bbk_fseek(file, 0, 0);
    if (bbk_fread(buffer, size, 1, file) != 1)
    {
        bbk_fclose(file);
        bbk_free_if_nonnull(buffer);
        return;
    }
    bbk_fclose(file);
    if (sango_color_use_buffer(buffer, size, library_bytes))
        color_file_owned = true;
    else
        bbk_free_if_nonnull(buffer);
}

static const uint8_t *color_find_entry(uint32_t original_pixels, uint32_t width, uint32_t height,
                                       int masked)
{
    uint32_t offset, first = 0, last = color_entries;
    if (!color_file || original_pixels < g_resource_package_address)
        return NULL;
    offset = original_pixels - g_resource_package_address;
    if (offset >= color_library_bytes)
        return NULL;
    while (first < last)
    {
        uint32_t middle = first + (last - first) / 2;
        const uint8_t *entry = color_file + 32 + middle * 16;
        uint32_t source = color_read32(entry);
        if (source < offset)
            first = middle + 1;
        else if (source > offset)
            last = middle;
        else
        {
            if (color_read16(entry + 8) != width || color_read16(entry + 10) != height ||
                (color_read32(entry + 12) & 1) != (uint32_t)(masked != 0))
                return NULL;
            return entry;
        }
    }
    return NULL;
}

const uint16_t *sango_color_pixels(uint32_t original_pixels, uint32_t width, uint32_t height,
                                   int masked)
{
    const uint8_t *entry = color_find_entry(original_pixels, width, height, masked);
    return entry ? (const uint16_t *)(color_file + color_read32(entry + 4)) : NULL;
}

uint32_t sango_color_frame_flags(uint32_t original_pixels, uint32_t width, uint32_t height,
                                 int masked)
{
    const uint8_t *entry = color_find_entry(original_pixels, width, height, masked);
    return entry ? color_read32(entry + 12) : 0;
}

/* Keep the original 7x7 logical grid and camera/selection rules. Only colored
 * map output fills the 240x232 area above the toolbar; footer and battle
 * painters remain outside this scope. Global pixel edges avoid tile seams. */
int sango_color_strategy_map_begin(uint32_t target)
{
    strategy_map_context = color_file ? target : 0;
    return strategy_map_context != 0;
}

void sango_color_strategy_map_end(void)
{
    strategy_map_context = 0;
}

static void color_write_pixel(uint32_t context, int x, int y, uint16_t color)
{
    color = bda_gui_rgb565_avoid_black_key(color);
    if (strategy_map_context && context == strategy_map_context && x >= 0 && x < 224 && y >= 0 &&
        y < 224)
    {
        int left = x * 15 / 14, right = (x + 1) * 15 / 14;
        int top = y * 29 / 28, bottom = (y + 1) * 29 / 28;
        int screen_x, screen_y;
        for (screen_y = top; screen_y < bottom; ++screen_y)
            for (screen_x = left; screen_x < right; ++screen_x)
                sango_color_sdk_pixel(context, screen_x, screen_y, color);
    }
    else
        sango_color_sdk_pixel(context, x, y, color);
}

void sango_color_put_pixel(short x, short y, uint16_t color, unsigned int target)
{
    bda_handle_t context = (bda_handle_t)(target ? target : g_draw_context);
    if (x < 0 || x >= 240 || y < 0 || y >= 320)
        return;
    if (!target)
        sango_color_sdk_guard(1);
    color_write_pixel((uint32_t)context, x, y, color);
    if (!target)
        sango_color_sdk_guard(0);
}

int sango_color_draw_raster(uint32_t x, short y, uint32_t width, uint32_t height,
                            uint32_t original_pixels, uint32_t target, int masked)
{
    uint32_t column, row, stride = (width + 3) / 4;
    const uint8_t *mask = (const uint8_t *)original_pixels;
    const uint8_t *entry = color_find_entry(original_pixels, width, height, masked);
    const uint16_t *pixels;
    uint32_t flags;
    bda_handle_t context = (bda_handle_t)(target ? target : g_draw_context);
    if (!entry)
        return 0;
    pixels = (const uint16_t *)(color_file + color_read32(entry + 4));
    flags = color_read32(entry + 12);
    if (!target)
        sango_color_sdk_guard(1);
    for (row = 0; row < height; ++row)
        for (column = 0; column < width; ++column)
        {
            int screen_x = (short)((x + column) & 0xffffu);
            int screen_y = (int)y + row;
            if (screen_x < 0 || screen_x >= 240 || screen_y < 0 || screen_y >= 320)
                continue;
            /* Explicit keyed alpha replaces a broken legacy mask (city cursor).
             * Untagged masked frames still use the original LIB mask exactly. */
            if (masked && !(flags & SANGO_COLOR_TRANSPARENT_ZERO) &&
                ((mask[row * stride + column / 4] >> (6 - (column % 4) * 2)) & 1))
                continue;
            if ((flags & SANGO_COLOR_TRANSPARENT_ZERO) && !pixels[row * width + column])
                continue;
            color_write_pixel((uint32_t)context, screen_x, screen_y, pixels[row * width + column]);
        }
    if (!target)
        sango_color_sdk_guard(0);
    return 1;
}

int sango_color_draw_resource(unsigned int resource, int x, short y, unsigned int target)
{
    const SangoBitmapHeader *bitmap;
    if (!color_file)
        return 0;
    bitmap =
        (const SangoBitmapHeader *)sango_resource_item(resource, 1, g_resource_package_address);
    if (!bitmap)
        return 0;
    return sango_color_draw_raster(x, y, bitmap->width, bitmap->height, (uint32_t)(bitmap + 1),
                                   target, bitmap->flags & 1);
}

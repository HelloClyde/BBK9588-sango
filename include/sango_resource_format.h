#ifndef SANGO_RESOURCE_FORMAT_H
#define SANGO_RESOURCE_FORMAT_H
#include "sango_types.h"

enum
{
    SANGO_RESOURCE_RECORD_BYTES = 12,
    SANGO_RESOURCE_INDEX_BYTES = 4
};

/* LIB index: resource ID -> uint32 little-endian file offset.
 * Item numbers are 1-based. Variable records use (offset,length) pairs;
 * fixed records use item_stride. Encoding is subtracted from text bytes. */
typedef struct
{
    uint32_t bytes;
    uint16_t id;
    uint16_t item_count;
    uint16_t item_stride;
    uint16_t encoding;
} SangoResourceHeader;

typedef struct
{
    uint16_t offset;
    uint16_t bytes;
} SangoResourceIndexEntry;

typedef struct
{
    uint16_t width;
    uint16_t height;
    uint8_t frames;
    uint8_t flags;
} SangoBitmapHeader;

_Static_assert(sizeof(SangoResourceHeader) == 12, "LIB header");
_Static_assert(offsetof(SangoResourceHeader, item_count) == 6, "LIB count");
_Static_assert(offsetof(SangoResourceHeader, item_stride) == 8, "LIB stride");
_Static_assert(offsetof(SangoResourceHeader, encoding) == 10, "LIB encoding");
_Static_assert(sizeof(SangoResourceIndexEntry) == 4, "LIB item entry");
_Static_assert(sizeof(SangoBitmapHeader) == 6, "bitmap descriptor");

#endif

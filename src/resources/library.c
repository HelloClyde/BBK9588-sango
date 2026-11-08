#include "sango_internal.h"

/* 索引资源读取、文字解码和诊断显示。 */

/* 原函数 0x81c152f0 */
/* 资源ID和item_number均为1基；返回原O32的32位地址值。保留旧格式的计数/步长规则。 */
int sango_resource_item(uint32_t resource_id, char item_number, int package_base)
{
    unsigned char abi_storage[27] __attribute__((aligned(8)));
#define record_header ((SangoResourceHeader *)abi_storage)
#define item_count (record_header->item_count)
#define item_stride (record_header->item_stride)
#define encoding (*(char *)&record_header->encoding)

    int record_offset;
    uint8_t *index_entry;
    int item_address;
    uint32_t item_index;
    void *record;

    item_address = 0;
    if (item_number != '\0')
    {
        item_index = (uint8_t)item_number - 1 & 0xff;
        record_offset = sango_resource_offset(resource_id & 0xffff);
        item_address = 0;
        if (record_offset != 0)
        {
            record = (void *)(package_base + record_offset);
            sango_resource_prepare_hook(record, record_offset);
            bbk_memcpy(record_header, record, 0xc);
            if ((item_count < item_index) || (encoding != '\0'))
            {
                item_address = 0;
            }
            else if (item_stride == 0)
            {
                if (item_count == 1)
                {
                    item_address = (int)record + 0xc;
                }
                else
                {
                    index_entry = (uint8_t *)((int)record + item_index * 4 + 0xc);
                    item_address =
                        (int)record +
                        ((uint32_t)index_entry[1] * 0x100 + (uint32_t)*index_entry & 0xffff);
                }
            }
            else
            {
                item_address = (int)record + item_index * item_stride + 0xc;
            }
        }
    }
    return item_address;
}
#undef item_count
#undef item_stride
#undef encoding
#undef record_header

/* 原函数 0x81c153d8 */
/* 索引槽位为(resource_id-1)*4。0xffffffff是原格式缺失值，调用端不得把它当作有效地址。 */
int sango_resource_offset(uint32_t resource_id)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define offset_words (*(int(*)[2])(abi_storage + 0))

    int index_offset;

    index_offset = ((resource_id & 0xffff) - 1) * 4;
    offset_words[0] = 0;
    if ((resource_id & 0xffff) != 0)
    {
        offset_words[0] = index_offset;
        bbk_memcpy(offset_words, (void *)(g_resource_package_address + index_offset), 4);
    }
    return offset_words[0];
}
#undef offset_words

/* 原函数 0x81c15428 */
uint32_t sango_resource_item_size(uint16_t resource_id, uint32_t item_number)
{
    unsigned char abi_storage[34] __attribute__((aligned(8)));
#define header_bytes (*(uint8_t(*)[8])(abi_storage + 8))
#define index_bytes (*(uint8_t(*)[2])(abi_storage + 0))
#define indexed_length (*(uint16_t *)(abi_storage + 2))
#define fixed_stride (*(uint16_t *)(abi_storage + 16))

    int record_offset;
    uint32_t item_bytes;

    record_offset = sango_resource_offset((uint32_t)resource_id);
    item_bytes = 0;
    if (record_offset != 0)
    {
        bbk_memcpy(header_bytes, (void *)(g_resource_package_address + record_offset), 0xc);
        if (fixed_stride == 0)
        {
            bbk_memcpy(index_bytes,
                       (void *)(g_resource_package_address + record_offset +
                                ((item_number & 0xff) - 1) * 4 + 0xc),
                       4);
            item_bytes = (uint32_t)indexed_length;
        }
        else
        {
            item_bytes = (uint32_t)fixed_stride;
        }
    }
    return item_bytes;
}
#undef header_bytes
#undef index_bytes
#undef indexed_length
#undef fixed_stride

/* 原函数 0x81c154d8 */
/* 读取可变长或固定步长文字项；编码字节逐个相减，末尾补NUL。 */
uint32_t sango_resource_read_text(uint16_t resource_id, uint32_t item_number, void *output)
{
    unsigned char abi_storage[35] __attribute__((aligned(8)));
#define record_header ((SangoResourceHeader *)(abi_storage + 8))
#define item_offset (*(uint16_t *)(abi_storage + 0))
#define item_bytes (*(uint16_t *)(abi_storage + 2))
#define item_stride (record_header->item_stride)
#define encoding (*(char *)&record_header->encoding)

    int record_offset;
    uint32_t failed;
    int item_index;
    char *character;
    uint32_t decode_index;
    uint32_t text_bytes;

    record_offset = sango_resource_offset((uint32_t)resource_id);
    failed = 1;
    if (record_offset != 0)
    {
        bbk_memcpy(record_header, (void *)(g_resource_package_address + record_offset), 0xc);
        item_index = (item_number & 0xff) - 1;
        if (item_stride == 0)
        {
            bbk_memcpy(&item_offset,
                       (void *)(g_resource_package_address + record_offset + item_index * 4 + 0xc),
                       4);
        }
        else
        {
            item_bytes = item_stride;
            item_offset = (short)item_index * item_stride + 0xc;
        }
        text_bytes = (uint32_t)item_bytes;
        bbk_memcpy(output,
                   (void *)(g_resource_package_address + record_offset + (uint32_t)item_offset),
                   text_bytes);
        *(uint8_t *)((int)output + text_bytes) = 0;
        if ((encoding != '\0') && (decode_index = 0, text_bytes != 0))
        {
            do
            {
                character = (char *)((int)output + decode_index);
                decode_index = decode_index + 1 & 0xffff;
                *character = *character - encoding;
            } while (decode_index < text_bytes);
        }
        failed = 0;
    }
    return failed;
}
#undef record_header
#undef item_offset
#undef item_bytes
#undef item_stride
#undef encoding

/* 原函数 0x81c155e4 */
void sango_resource_decode_bytes(int buffer_address, char encoding, uint32_t byte_count)
{
    char *character;
    uint32_t index;

    index = 0;
    if ((byte_count & 0xffff) != 0)
    {
        do
        {
            character = (char *)(buffer_address + index);
            index = index + 1 & 0xffff;
            *character = *character - encoding;
        } while (index < (byte_count & 0xffff));
    }
    return;
}

/* 原函数 0x81c156e0 */
void sango_debug_draw_integer(uint16_t x, uint16_t y, int value, uint8_t radix, char show_sign)
{
    unsigned char abi_storage[137] __attribute__((aligned(8)));
    (*(char *)(abi_storage + 120)) = show_sign;
#define digit_text (*(char(*)[40])(abi_storage + 32))
#define reversed_digits (*(uint8_t(*)[25])(abi_storage + 7))
#define show_sign (*(char *)(abi_storage + 120))

    uint8_t digit_value;
    int quotient;
    uint8_t *digit_entry;
    uint32_t digit_index;
    uint32_t digit_count;

    if ((show_sign == '\x01') && (value < 0))
    {
        sango_text_draw_character((uint8_t)x, (uint8_t)y, 0x2d);
        x = x + 8;
        value = -value;
    }
    if (radix == 0)
    {
        sango_legacy_trap(7);
    }
    digit_index = 0;
    while (true)
    {
        quotient = value / (int)(uint32_t)radix;
        if (quotient == 0)
            break;
        reversed_digits[digit_index + 1] = (uint8_t)value - (char)quotient * radix;
        digit_index = digit_index + 1 & 0xffff;
        value = quotient;
        if (radix == 0)
        {
            sango_legacy_trap(7);
        }
    }
    digit_count = digit_index + 1 & 0xffff;
    reversed_digits[digit_index + 1] = (uint8_t)value;
    digit_index = 0;
    if (digit_count != 0)
    {
        digit_entry = reversed_digits + digit_count;
        do
        {
            digit_value = *digit_entry;
            digit_index = digit_index + 1;
            digit_entry = digit_entry + -1;
            sango_format_integer((uint32_t)(uint8_t)g_legacy_data_81c205c0[digit_value], digit_text,
                                 10);
            sango_text_draw_native(x, y, digit_text, 0);
            x = x + 8;
        } while (digit_index < digit_count);
    }
    return;
}
#undef digit_text
#undef reversed_digits
#undef show_sign

/* 原函数 0x81c15834 */
void sango_debug_show_resource_id(int resource_id)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define event_kind (*(int *)(abi_storage + 0))
#define event_key (*(int *)(abi_storage + 4))

    uint8_t column;

    column = 0;
    do
    {
        sango_text_draw_character(column << 3, 0, 0x20);
        column = column + 1;
    } while (column < 8);
    sango_debug_draw_integer(0, 0, resource_id, 0x10, '\0');
    do
    {
        do
        {
            sango_input_next_event(&event_kind);
        } while (event_kind != 5);
    } while ((event_key != 0x1c) && (event_key != 1));
    return;
}
#undef event_kind
#undef event_key

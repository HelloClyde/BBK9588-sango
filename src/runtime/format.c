#include "sango_internal.h"

/* 恢复的数值格式化和浮点文本转换。 */

/* 原函数 0x81c1c48c */
void sango_crt_append_character(uint8_t character, int *output_cursor_address)
{
    uint8_t *output_cursor;

    output_cursor = (uint8_t *)*output_cursor_address;
    *output_cursor = character;
    *output_cursor_address = (int)(output_cursor + 1);
    return;
}

/* 原函数 0x81c1c4a0 */
void sango_crt_initialize(void)
{
    g_legacy_data_81c2b9cc = 1;
    g_legacy_data_81c2b9d0 = 0x45;
    g_legacy_data_81c2b9d4 = 2;
    g_legacy_data_81c2b1a0 = &g_legacy_data_81c2b9c0;
    g_legacy_data_81c2b19c = &g_legacy_data_81c2b9c8;
    g_legacy_data_81c2b1ac = &g_legacy_data_81c2b9d0;
    g_legacy_data_81c2b9c0 = 0x45;
    g_legacy_data_81c2b9c2 = 0;
    g_legacy_data_81c2b9c4 = 0;
    g_legacy_data_81c2b9c8 = 0x45;
    g_legacy_data_81c2b9ca = 0;
    g_legacy_data_81c2b9d2 = 0;
    g_runtime_errno = 0;
    sango_crt_heap_initialize(-0x7f5ce000, -0x7e400000);
    g_random_seed = 1;
    g_legacy_data_81c2b1a4 = 0xffffffff;
    return;
}

/* 原函数 0x81c1c540 */
int sango_crt_read_buffer(uint32_t stream_handle, uint8_t *output, int requested_bytes)
{
    int bytes_read;

    bytes_read = 0;
    while ((requested_bytes != 0 && (g_legacy_data_81c2b1f4 != '\x01')))
    {
        if (g_legacy_data_81c2b9e0 == '\0')
        {
            g_legacy_data_81c2b1f4 = '\x01';
            g_legacy_data_81c2b1f0 = 1;
        }
        else
        {
            g_legacy_data_81c2b9e0 = g_legacy_data_81c2b9e0 + -1;
            requested_bytes = requested_bytes + -1;
            bytes_read = bytes_read + 1;
            *output = (&g_legacy_data_81c2b9e0)[g_legacy_data_81c2b1f0];
            g_legacy_data_81c2b1f0 = g_legacy_data_81c2b1f0 + 1;
            output = output + 1;
        }
    }
    return bytes_read;
}

/* 原函数 0x81c1c5d8 */
void sango_crt_abort_loop(void)
{
    do
    {
        /* WARNING: Do nothing block with infinite loop */
    } while (true);
}

/* 原函数 0x81c1c5e0 */
void sango_crt_reset_input_buffer(void)
{
    g_legacy_data_81c2b1f4_view2 = 0;
    g_legacy_data_81c2b9e0 = 0;
    return;
}

/* 原函数 0x81c1c5f4 */
void crt_diagnostic_noop(uint32_t ignored, ...)
{
    return;
}

/* 原函数 0x81c1c600 */
int sango_crt_isdigit(char character)
{
    int result;

    result = (int)character;
    if (9 < result - 0x30U)
    {
        result = 0;
    }
    return result;
}

/* 原函数 0x81c1c620 */
int sango_crt_isspace(char character)
{
    int result;
    int character_code;

    character_code = (int)character;
    result = character_code;
    if ((4 < character_code - 9U) && (result = 0, character_code == 0x20))
    {
        result = character_code;
    }
    return result;
}

/* 原函数 0x81c1c650 */
int sango_crt_toupper(char character)
{
    int uppercase;
    int character_code;

    character_code = (int)character;
    uppercase = character_code + -0x20;
    if (0x19 < character_code - 0x61U)
    {
        uppercase = character_code;
    }
    return uppercase;
}

/* 原函数 0x81c1c670 */
int sango_crt_format_entry(uint8_t *output, uint8_t *format, int argument0, uint32_t argument1)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define second_argument_word (*(uint32_t *)(abi_storage + 4))
#define first_argument_word (*(int *)(abi_storage + 0))

    int output_bytes;

    first_argument_word = argument0;
    second_argument_word = argument1;
    output_bytes = sango_crt_format_words(0x4d, output, format, &first_argument_word);
    if (output_bytes < 0)
    {
        *output = 0;
    }
    else
    {
        output[output_bytes] = 0;
    }
    return output_bytes;
}
#undef second_argument_word
#undef first_argument_word

/* 原函数 0x81c1c6d0 */
int sango_crt_format_words(int output_mode, void *output_target, uint8_t *format, int *arguments)
{
    unsigned char abi_storage[120] __attribute__((aligned(8)));
#define argument_cursor (*(int **)(abi_storage + 0))
#define alignment_code (*(uint32_t *)(abi_storage + 4))
#define sign_code (*(int *)(abi_storage + 8))
#define zero_padding_code (*(uint32_t *)(abi_storage + 12))
#define alternate_code (*(uint32_t *)(abi_storage + 16))
#define length_modifier (*(uint32_t *)(abi_storage + 20))
#define field_width (*(int *)(abi_storage + 24))
#define precision (*(int *)(abi_storage + 28))
#define field_body (*(void **)(abi_storage + 32))
#define leading_spaces (*(uint32_t *)(abi_storage + 36))
#define leading_zeros (*(uint32_t *)(abi_storage + 40))
#define internal_zeros (*(uint32_t *)(abi_storage + 44))
#define fractional_zeros (*(uint32_t *)(abi_storage + 48))
#define trailing_spaces (*(uint32_t *)(abi_storage + 52))
#define prefix_length (*(uint32_t *)(abi_storage + 56))
#define body_length (*(uint32_t *)(abi_storage + 60))
#define suffix_length (*(uint32_t *)(abi_storage + 64))
#define field_prefix (*(char(*)[32])(abi_storage + 72))

    uint8_t format_byte;
    uint32_t stream_result_word;
    int *argument_word;
    int parse_status;
    uint8_t *specifier_cursor;
    uint8_t *next_format;
    void *output_cursor;
    uint32_t span_length;
    int output_count;

    output_count = 0;
    output_cursor = output_target;
    argument_cursor = arguments;
    if (format != (uint8_t *)0x0)
    {
        do
        {
            span_length = 0;
            format_byte = *format;
            specifier_cursor = format;
            while ((format_byte != 0x25 && (format_byte != 0)))
            {
                specifier_cursor = specifier_cursor + 1;
                span_length = span_length + 1;
                format_byte = *specifier_cursor;
            }
            stream_result_word = 0x53;
            if (output_mode == 0x53)
            {
                crt_diagnostic_noop(*(uint32_t *)((int)output_target + 4), format, span_length);
                if (stream_result_word != span_length)
                {
                    return -1;
                }
            }
            else
            {
                crt_memcpy(output_cursor, format, span_length);
                output_cursor = (void *)((int)output_cursor + span_length);
            }
            output_count = output_count + span_length;
            if (*specifier_cursor != 0x25)
            {
                return output_count;
            }
            alignment_code = 0x4c;
            sign_code = 0x4c;
            zero_padding_code = 0x4c;
            alternate_code = 0x4c;
            parse_status = 0x4c;
            do
            {
                next_format = specifier_cursor;
                specifier_cursor = next_format + 1;
                switch (*specifier_cursor)
                {
                case 0x20:
                    if (sign_code == 0x4c)
                    {
                        sign_code = 0x20;
                    }
                    break;
                default:
                    parse_status = 0x48;
                    break;
                case 0x23:
                    alternate_code = 0x48;
                    break;
                case 0x2b:
                    sign_code = 0x2b;
                    break;
                case 0x2d:
                    alignment_code = 0x48;
                    break;
                case 0x30:
                    zero_padding_code = 0x48;
                }
            } while (parse_status == 0x4c);
            if (*specifier_cursor == 0x2a)
            {
                argument_word = (int *)((int)argument_cursor + 3U & 0xfffffffc);
                argument_cursor = argument_word + 1;
                field_width = *argument_word;
                if (field_width < 0)
                {
                    alignment_code = 0x48;
                    field_width = -field_width;
                }
                specifier_cursor = next_format + 2;
                format_byte = *specifier_cursor;
            }
            else
            {
                field_width = 0;
                while (parse_status = sango_crt_isdigit(*specifier_cursor), parse_status != 0)
                {
                    field_width = field_width * 10 + (uint32_t)*specifier_cursor + -0x30;
                    specifier_cursor = specifier_cursor + 1;
                }
                format_byte = *specifier_cursor;
            }
            if (format_byte == 0x2e)
            {
                next_format = specifier_cursor + 1;
                if (*next_format == 0x2a)
                {
                    argument_word = (int *)((int)argument_cursor + 3U & 0xfffffffc);
                    argument_cursor = argument_word + 1;
                    precision = *argument_word;
                    next_format = specifier_cursor + 2;
                }
                else
                {
                    precision = 0;
                    while (parse_status = sango_crt_isdigit(*next_format), parse_status != 0)
                    {
                        precision = precision * 10 + (uint32_t)*next_format - '0';
                        next_format = next_format + 1;
                    }
                }
            }
            else
            {
                precision = -1;
                next_format = specifier_cursor;
            }
            format_byte = *next_format;
            length_modifier = (uint32_t)format_byte;
            if ((length_modifier == 0x68) ||
                (length_modifier = (uint32_t)*next_format, length_modifier == 0x6c))
            {
                next_format = next_format + 1;
            }
            else
            {
                length_modifier = 0x4c;
            }
            format = (uint8_t *)sango_crt_format_field((int *)&argument_cursor, (char *)next_format,
                                                       field_prefix);
            for (span_length = leading_spaces; 0x14 < (int)span_length;
                 span_length = span_length - 0x14)
            {
                parse_status = 0x53;
                if (output_mode == 0x53)
                {
                    crt_diagnostic_noop(*(uint32_t *)((int)output_target + 4),
                                        g_legacy_data_81c20990, 0x14);
                    if (parse_status != 0x14)
                    {
                        return -1;
                    }
                }
                else
                {
                    crt_memcpy(output_cursor, g_legacy_data_81c20990, 0x14);
                    output_cursor = (void *)((int)output_cursor + 0x14);
                }
                output_count = output_count + 0x14;
            }
            stream_result_word = 0x53;
            if (output_mode == 0x53)
            {
                crt_diagnostic_noop(*(uint32_t *)((int)output_target + 4), g_legacy_data_81c20990,
                                    span_length);
                if (stream_result_word != span_length)
                {
                    return -1;
                }
            }
            else
            {
                crt_memcpy(output_cursor, g_legacy_data_81c20990, span_length);
                output_cursor = (void *)((int)output_cursor + span_length);
            }
            stream_result_word = 0x53;
            if (output_mode == 0x53)
            {
                crt_diagnostic_noop(*(uint32_t *)((int)output_target + 4), field_prefix,
                                    prefix_length);
                if (stream_result_word != prefix_length)
                {
                    return -1;
                }
            }
            else
            {
                crt_memcpy(output_cursor, field_prefix, prefix_length);
                output_cursor = (void *)((int)output_cursor + prefix_length);
            }
            output_count = output_count + span_length + prefix_length;
            for (span_length = leading_zeros; 0x14 < (int)span_length;
                 span_length = span_length - 0x14)
            {
                parse_status = 0x53;
                if (output_mode == 0x53)
                {
                    crt_diagnostic_noop(*(uint32_t *)((int)output_target + 4),
                                        g_legacy_data_81c209a8, 0x14);
                    if (parse_status != 0x14)
                    {
                        return -1;
                    }
                }
                else
                {
                    crt_memcpy(output_cursor, g_legacy_data_81c209a8, 0x14);
                    output_cursor = (void *)((int)output_cursor + 0x14);
                }
                output_count = output_count + 0x14;
            }
            stream_result_word = 0x53;
            if (output_mode == 0x53)
            {
                crt_diagnostic_noop(*(uint32_t *)((int)output_target + 4), g_legacy_data_81c209a8,
                                    span_length);
                if (stream_result_word != span_length)
                {
                    return -1;
                }
            }
            else
            {
                crt_memcpy(output_cursor, g_legacy_data_81c209a8, span_length);
                output_cursor = (void *)((int)output_cursor + span_length);
            }
            stream_result_word = 0x53;
            if (output_mode == 0x53)
            {
                crt_diagnostic_noop(*(uint32_t *)((int)output_target + 4), field_body, body_length);
                if (stream_result_word != body_length)
                {
                    return -1;
                }
            }
            else
            {
                crt_memcpy(output_cursor, field_body, body_length);
                output_cursor = (void *)((int)output_cursor + body_length);
            }
            output_count = output_count + span_length + body_length;
            for (span_length = internal_zeros; 0x14 < (int)span_length;
                 span_length = span_length - 0x14)
            {
                parse_status = 0x53;
                if (output_mode == 0x53)
                {
                    crt_diagnostic_noop(*(uint32_t *)((int)output_target + 4),
                                        g_legacy_data_81c209a8, 0x14);
                    if (parse_status != 0x14)
                    {
                        return -1;
                    }
                }
                else
                {
                    crt_memcpy(output_cursor, g_legacy_data_81c209a8, 0x14);
                    output_cursor = (void *)((int)output_cursor + 0x14);
                }
                output_count = output_count + 0x14;
            }
            stream_result_word = 0x53;
            if (output_mode == 0x53)
            {
                crt_diagnostic_noop(*(uint32_t *)((int)output_target + 4), g_legacy_data_81c209a8,
                                    span_length);
                if (stream_result_word != span_length)
                {
                    return -1;
                }
            }
            else
            {
                crt_memcpy(output_cursor, g_legacy_data_81c209a8, span_length);
                output_cursor = (void *)((int)output_cursor + span_length);
            }
            if (output_mode == 0x53)
            {
                stream_result_word = body_length;
                crt_diagnostic_noop(*(uint32_t *)((int)output_target + 4),
                                    (int)field_body + body_length, suffix_length);
                if (stream_result_word != suffix_length)
                {
                    return -1;
                }
            }
            else
            {
                crt_memcpy(output_cursor, (void *)((int)field_body + body_length), suffix_length);
                output_cursor = (void *)((int)output_cursor + suffix_length);
            }
            output_count = output_count + span_length + suffix_length;
            for (span_length = fractional_zeros; 0x14 < (int)span_length;
                 span_length = span_length - 0x14)
            {
                parse_status = 0x53;
                if (output_mode == 0x53)
                {
                    crt_diagnostic_noop(*(uint32_t *)((int)output_target + 4),
                                        g_legacy_data_81c209a8, 0x14);
                    if (parse_status != 0x14)
                    {
                        return -1;
                    }
                }
                else
                {
                    crt_memcpy(output_cursor, g_legacy_data_81c209a8, 0x14);
                    output_cursor = (void *)((int)output_cursor + 0x14);
                }
                output_count = output_count + 0x14;
            }
            stream_result_word = 0x53;
            if (output_mode == 0x53)
            {
                crt_diagnostic_noop(*(uint32_t *)((int)output_target + 4), g_legacy_data_81c209a8,
                                    span_length);
                if (stream_result_word != span_length)
                {
                    return -1;
                }
            }
            else
            {
                crt_memcpy(output_cursor, g_legacy_data_81c209a8, span_length);
                output_cursor = (void *)((int)output_cursor + span_length);
            }
            output_count = output_count + span_length;
            for (span_length = trailing_spaces; 0x14 < (int)span_length;
                 span_length = span_length - 0x14)
            {
                parse_status = 0x53;
                if (output_mode == 0x53)
                {
                    crt_diagnostic_noop(*(uint32_t *)((int)output_target + 4),
                                        g_legacy_data_81c20990, 0x14);
                    if (parse_status != 0x14)
                    {
                        return -1;
                    }
                }
                else
                {
                    crt_memcpy(output_cursor, g_legacy_data_81c20990, 0x14);
                    output_cursor = (void *)((int)output_cursor + 0x14);
                }
                output_count = output_count + 0x14;
            }
            stream_result_word = 0x53;
            if (output_mode == 0x53)
            {
                crt_diagnostic_noop(*(uint32_t *)((int)output_target + 4), g_legacy_data_81c20990,
                                    span_length);
                if (stream_result_word != span_length)
                {
                    return -1;
                }
            }
            else
            {
                crt_memcpy(output_cursor, g_legacy_data_81c20990, span_length);
                output_cursor = (void *)((int)output_cursor + span_length);
            }
            output_count = output_count + span_length;
        } while (format != (uint8_t *)0x0);
    }
    return output_count;
}
#undef argument_cursor
#undef alignment_code
#undef sign_code
#undef zero_padding_code
#undef alternate_code
#undef length_modifier
#undef field_width
#undef precision
#undef field_body
#undef leading_spaces
#undef leading_zeros
#undef internal_zeros
#undef fractional_zeros
#undef trailing_spaces
#undef prefix_length
#undef body_length
#undef suffix_length
#undef field_prefix

/* 原函数 0x81c1ce34 */
char *sango_crt_format_field(int *field, char *conversion, char *prefix_buffer)
{
    SangoLegacyCode *trap_handler;
    uint32_t *string_argument;
    uint32_t *argument_word;
    int remaining_width;
    int precision;
    char *string_value;
    uint32_t value_low;
    uint32_t value_high_or_radix;

    field[9] = 0;
    field[0xe] = 0;
    field[10] = 0;
    field[0xf] = 0;
    field[0xb] = 0;
    field[0x10] = 0;
    field[0xc] = 0;
    field[0xd] = 0;
    switch (*conversion)
    {
    case '%':
        *prefix_buffer = '%';
        field[8] = (int)(prefix_buffer + 1);
        field[0xe] = 1;
        break;
    default:
        *prefix_buffer = *conversion;
        field[0xe] = 1;
        field[6] = 0;
        break;
    case 'E':
    case 'G':
    case 'e':
    case 'f':
    case 'g':
        argument_word = (uint32_t *)(*field + 7U & 0xfffffff8);
        *field = (int)(argument_word + 2);
        value_low = *argument_word;
        value_high_or_radix = argument_word[1];
        if ((int)value_high_or_radix < 0)
        {
            *prefix_buffer = '-';
            field[0xe] = 1;
            value_high_or_radix = value_high_or_radix & 0x7fffffff;
        }
        else
        {
            if (field[2] == 0x20)
            {
                *prefix_buffer = ' ';
            }
            else
            {
                if (field[2] != 0x2b)
                    goto prepare_float_body;
                *prefix_buffer = '+';
            }
            field[0xe] = 1;
        }
    prepare_float_body:
        field[8] = (int)(prefix_buffer + field[0xe]);
        if (*conversion == 'G')
        {
            *conversion = 'E';
        }
        else if (*conversion == 'g')
        {
            *conversion = 'e';
        }
        if (field[7] < 0)
        {
            field[7] = 6;
        }
        sango_crt_format_double_digits((int)field, conversion, value_low, value_high_or_radix,
                                       conversion);
        remaining_width = field[6];
        goto apply_field_padding;
    case 'X':
    case 'o':
    case 'u':
    case 'x':
        if (field[5] == 0x68)
        {
            sango_legacy_trap();
        }
        argument_word = (uint32_t *)(*field + 3U & 0xfffffffc);
        *field = (int)(argument_word + 1);
        value_low = *argument_word;
        if ((field[4] == 0x48) && (*conversion != 'u'))
        {
            prefix_buffer[field[0xe]] = '0';
            remaining_width = field[0xe];
            field[0xe] = remaining_width + 1;
            if (*conversion != 'o')
            {
                prefix_buffer[remaining_width + 1] = *conversion;
                field[0xe] = field[0xe] + 1;
            }
        }
        field[8] = (int)(prefix_buffer + field[0xe]);
        value_high_or_radix = 8;
        if ((*conversion != 'o') && (value_high_or_radix = 10, *conversion != 'u'))
        {
            value_high_or_radix = 0x10;
        }
        goto format_integer_digits;
    case 'c':
        /* WARNING: Does not return */
        trap_handler = (SangoLegacyCode *)sango_legacy_trap(0);
        (*trap_handler)();
    case 'd':
    case 'i':
        if (field[5] == 0x68)
        {
            sango_legacy_trap();
        }
        argument_word = (uint32_t *)(*field + 3U & 0xfffffffc);
        *field = (int)(argument_word + 1);
        value_low = *argument_word;
        if ((int)value_low < 0)
        {
            *prefix_buffer = '-';
            field[0xe] = 1;
            value_low = -value_low;
        }
        else
        {
            if (field[2] == 0x20)
            {
                *prefix_buffer = ' ';
            }
            else
            {
                if (field[2] != 0x2b)
                    goto prepare_integer_body;
                *prefix_buffer = '+';
            }
            field[0xe] = 1;
        }
    prepare_integer_body:
        field[8] = (int)(prefix_buffer + field[0xe]);
        value_high_or_radix = 10;
    format_integer_digits:
        sango_crt_format_unsigned_digits((int)field, value_low, value_high_or_radix, conversion);
        remaining_width = field[6];
        goto apply_field_padding;
    case 's':
        string_argument = (uint32_t *)(*field + 3U & 0xfffffffc);
        *field = (int)(string_argument + 1);
        string_value = (char *)*string_argument;
        field[8] = (int)string_value;
        remaining_width = sango_crt_strlen(string_value);
        field[0xf] = remaining_width;
        precision = field[7];
        if ((-1 < precision) && (precision < remaining_width))
        {
            field[0xf] = precision;
        }
    }
    remaining_width = field[6];
apply_field_padding:
    remaining_width =
        (((((remaining_width - field[0xe]) - field[10]) - field[0xf]) - field[0xb]) - field[0x10]) -
        field[0xc];
    field[6] = remaining_width;
    if (0 < remaining_width)
    {
        if (field[1] == 0x4c)
        {
            field[9] = remaining_width;
        }
        else
        {
            field[0xd] = field[6];
        }
    }
    return conversion + 1;
}

/* 原函数 0x81c1d198 */
void sango_crt_format_unsigned_digits(int field_address, uint32_t value, uint32_t radix,
                                      char *conversion)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define reverse_digits (*(char(*)[25])(abi_storage + 7))

    char *digit_table;
    int precision_or_write_index;
    int first_digit;

    digit_table = g_legacy_data_81c20b68;
    if (*conversion != 'X')
    {
        digit_table = g_legacy_data_81c20b54;
    }
    precision_or_write_index = 0x18;
    do
    {
        first_digit = precision_or_write_index;
        precision_or_write_index = first_digit + -1;
        if (radix == 0)
        {
            sango_legacy_trap(7);
        }
        reverse_digits[first_digit] = digit_table[value % radix];
        if (radix == 0)
        {
            sango_legacy_trap(7);
        }
    } while ((value / radix != 0) && (value = value / radix, 0 < precision_or_write_index));
    *(uint32_t *)(field_address + 0x3c) = 0x18U - precision_or_write_index;
    crt_memcpy(*(void **)(field_address + 0x20), reverse_digits + first_digit,
               0x18U - precision_or_write_index);
    precision_or_write_index = *(int *)(field_address + 0x1c);
    if (precision_or_write_index < 1)
    {
        if (*(int *)(field_address + 0x1c) == 0)
        {
            if (**(char **)(field_address + 0x20) != '0')
            {
                return;
            }
            *(uint32_t *)(field_address + 0x3c) = 0;
            return;
        }
        if (*(int *)(field_address + 0xc) != 0x48)
        {
            return;
        }
        if (*(int *)(field_address + 4) != 0x4c)
        {
            return;
        }
        if (*(int *)(field_address + 0x18) <=
            *(int *)(field_address + 0x3c) + *(int *)(field_address + 0x38))
        {
            return;
        }
        precision_or_write_index =
            (*(int *)(field_address + 0x18) - *(int *)(field_address + 0x3c)) -
            *(int *)(field_address + 0x38);
    }
    else
    {
        if (precision_or_write_index <= *(int *)(field_address + 0x3c))
        {
            return;
        }
        precision_or_write_index = precision_or_write_index - *(int *)(field_address + 0x3c);
    }
    *(int *)(field_address + 0x28) = precision_or_write_index;
    return;
}
#undef reverse_digits

/* 原函数 0x81c1d2d4 */
void sango_crt_format_double_digits(int field_address, uint32_t abi_alignment_word,
                                    uint32_t value_low, int value_high, char *conversion)
{
    unsigned char abi_storage[108] __attribute__((aligned(8)));
    (*(char **)(abi_storage + 88)) = conversion;
#define decimal_digits (*(char(*)[24])(abi_storage + 0))
#define decimal_exponent (*(uint32_t(*)[2])(abi_storage + 24))
#define conversion (*(char **)(abi_storage + 88))

    char conversion_character;
    int digit_count_or_scale_index;
    int prefix_or_table_offset;
    int comparison_result;
    uint32_t threshold_low;
    uint32_t scaled_low_or_digit_count;
    uint32_t scaled_high_or_length;
    uint64_t scaled_value;
    uint64_t candidate_value;

    scaled_value = CONCAT44(value_high, value_low);
    if ((value_high == 0x7ff00000) && (value_low == 0))
    {
        crt_memcpy(*(void **)(field_address + 0x20), &g_legacy_data_81c20bf8, 3);
        *(uint32_t *)(field_address + 0x3c) = 3;
    disable_zero_padding:
        *(uint32_t *)(field_address + 0xc) = 0x4c;
        return;
    }
    if (0x7fefffff < value_high)
    {
        crt_memcpy(*(void **)(field_address + 0x20), &g_legacy_data_81c20bfc, 3);
        *(uint32_t *)(field_address + 0x3c) = 3;
        *(uint32_t *)(field_address + 0x38) = 0;
        goto disable_zero_padding;
    }
    decimal_exponent[0] = 0;
    digit_count_or_scale_index = sango_soft_compare_f64_nan_low_compat(
        value_low, value_high, g_legacy_data_81c20c70, g_legacy_data_81c20c74);
    if (digit_count_or_scale_index < 0)
    {
        digit_count_or_scale_index = sango_soft_compare_f64_nan_low(value_low, value_high, 0, 0);
        candidate_value = CONCAT44(value_high, value_low);
        scaled_low_or_digit_count = decimal_exponent[0];
        if (((0 < digit_count_or_scale_index) &&
             (digit_count_or_scale_index = sango_soft_compare_f64_nan_high_compat(
                  value_low, value_high, g_legacy_data_81c20c78, g_legacy_data_81c20c7c),
              candidate_value = CONCAT44(value_high, value_low),
              scaled_low_or_digit_count = decimal_exponent[0], digit_count_or_scale_index < 0)) &&
            (digit_count_or_scale_index = 0, candidate_value = CONCAT44(value_high, value_low),
             0 < g_legacy_data_81c20bd0))
        {
            conversion_character = *conversion;
            do
            {
                scaled_high_or_length = (uint32_t)((uint64_t)scaled_value >> 0x20);
                if ((conversion_character == 'e') || (conversion_character == 'E'))
                {
                    candidate_value = sango_soft_mul_f64(
                        (uint32_t)scaled_value, scaled_high_or_length,
                        (&g_legacy_data_81c20b80)[digit_count_or_scale_index * 2],
                        (&g_legacy_data_81c20b84)[digit_count_or_scale_index * 2]);
                    threshold_low = g_legacy_data_81c20c70;
                    scaled_high_or_length = g_legacy_data_81c20c74;
                }
                else
                {
                    candidate_value = sango_soft_mul_f64(
                        (uint32_t)scaled_value, scaled_high_or_length,
                        (&g_legacy_data_81c20b80)[digit_count_or_scale_index * 2],
                        (&g_legacy_data_81c20b84)[digit_count_or_scale_index * 2]);
                    threshold_low = g_legacy_data_81c20c78;
                    scaled_high_or_length = g_legacy_data_81c20c7c;
                }
                prefix_or_table_offset = sango_soft_compare_f64_nan_high_compat(
                    (uint32_t)candidate_value, (int)((uint64_t)candidate_value >> 0x20),
                    threshold_low, scaled_high_or_length);
                if (prefix_or_table_offset < 0)
                {
                    scaled_low_or_digit_count =
                        scaled_low_or_digit_count -
                        (&g_legacy_data_81c20bd0)[digit_count_or_scale_index];
                    scaled_value = candidate_value;
                }
                digit_count_or_scale_index = digit_count_or_scale_index + 1;
                candidate_value = scaled_value;
            } while (0 < (&g_legacy_data_81c20bd0)[digit_count_or_scale_index]);
        }
    }
    else
    {
        digit_count_or_scale_index = 0;
        candidate_value = scaled_value;
        scaled_low_or_digit_count = decimal_exponent[0];
        if (0 < g_legacy_data_81c20bd0)
        {
            prefix_or_table_offset = 0;
            do
            {
                scaled_high_or_length = (uint32_t)((uint64_t)scaled_value >> 0x20);
                comparison_result = sango_soft_compare_f64_nan_low_compat(
                    (uint32_t)scaled_value, scaled_high_or_length,
                    *(uint32_t *)((int)&g_legacy_data_81c20b80 + prefix_or_table_offset),
                    *(uint32_t *)((int)&g_legacy_data_81c20b84 + prefix_or_table_offset));
                if (-1 < comparison_result)
                {
                    scaled_value = sango_soft_div_f64(
                        (uint32_t)scaled_value, scaled_high_or_length,
                        *(uint32_t *)((int)&g_legacy_data_81c20b80 + prefix_or_table_offset),
                        *(uint32_t *)((int)&g_legacy_data_81c20b84 + prefix_or_table_offset));
                    scaled_low_or_digit_count =
                        scaled_low_or_digit_count +
                        (&g_legacy_data_81c20bd0)[digit_count_or_scale_index];
                }
                digit_count_or_scale_index = digit_count_or_scale_index + 1;
                prefix_or_table_offset = digit_count_or_scale_index * 8;
                candidate_value = scaled_value;
            } while (0 < (&g_legacy_data_81c20bd0)[digit_count_or_scale_index]);
        }
    }
    decimal_exponent[0] = scaled_low_or_digit_count;
    scaled_high_or_length = (uint32_t)((uint64_t)candidate_value >> 0x20);
    scaled_low_or_digit_count = (uint32_t)candidate_value;
    if ((*conversion == 'e') || (*conversion == 'E'))
    {
        digit_count_or_scale_index = 0x11;
        if (*(int *)(field_address + 0x1c) < 0x11)
        {
            digit_count_or_scale_index = *(int *)(field_address + 0x1c) + 1;
        }
        digit_count_or_scale_index = sango_crt_scale_double_decimal(
            scaled_low_or_digit_count, scaled_high_or_length, (int *)decimal_exponent,
            digit_count_or_scale_index, decimal_digits);
        **(char **)(field_address + 0x20) = decimal_digits[0];
        prefix_or_table_offset = 1;
        if (((1 < digit_count_or_scale_index) || (*(int *)(field_address + 0x10) == 0x48)) ||
            (0 < *(int *)(field_address + 0x1c)))
        {
            *(uint8_t *)(*(int *)(field_address + 0x20) + 1) = 0x2e;
            crt_memcpy((void *)(*(int *)(field_address + 0x20) + 2), decimal_digits + 1,
                       digit_count_or_scale_index - 1);
            prefix_or_table_offset = digit_count_or_scale_index + 1;
        }
        *(int *)(field_address + 0x3c) = prefix_or_table_offset;
        if (digit_count_or_scale_index + -1 < *(int *)(field_address + 0x1c))
        {
            *(int *)(field_address + 0x2c) =
                (*(int *)(field_address + 0x1c) - digit_count_or_scale_index) + 1;
        }
        *(char *)(*(int *)(field_address + 0x20) + prefix_or_table_offset) = *conversion;
        if ((int)decimal_exponent[0] < 0)
        {
            *(uint8_t *)(*(int *)(field_address + 0x20) + prefix_or_table_offset + 1) = 0x2d;
            decimal_exponent[0] = -decimal_exponent[0];
        }
        else
        {
            *(uint8_t *)(*(int *)(field_address + 0x20) + prefix_or_table_offset + 1) = 0x2b;
        }
        prefix_or_table_offset = prefix_or_table_offset + 2;
        if ((int)decimal_exponent[0] < 10)
        {
            *(uint8_t *)(*(int *)(field_address + 0x20) + prefix_or_table_offset) = 0x30;
            *(char *)(prefix_or_table_offset + *(int *)(field_address + 0x20) + 1) =
                (char)decimal_exponent[0] + '0';
            digit_count_or_scale_index = 4;
        }
        else
        {
            digit_count_or_scale_index = 10;
            for (; 0 < (int)decimal_exponent[0];
                 decimal_exponent[0] = (int)decimal_exponent[0] / 10)
            {
                decimal_digits[digit_count_or_scale_index] =
                    (char)decimal_exponent[0] + (char)((int)decimal_exponent[0] / 10) * -10 + '0';
                digit_count_or_scale_index = digit_count_or_scale_index + -1;
            }
            crt_memcpy((void *)(prefix_or_table_offset + *(int *)(field_address + 0x20)),
                       decimal_digits + digit_count_or_scale_index + 1,
                       10 - digit_count_or_scale_index);
            digit_count_or_scale_index = 0xc - digit_count_or_scale_index;
        }
        *(int *)(field_address + 0x40) = digit_count_or_scale_index;
        goto apply_zero_padding;
    }
    if ((int)decimal_exponent[0] < 0)
    {
        digit_count_or_scale_index = 0;
        if ((int)~decimal_exponent[0] < *(int *)(field_address + 0x1c))
        {
            prefix_or_table_offset = *(int *)(field_address + 0x1c) + decimal_exponent[0] + 1;
            digit_count_or_scale_index = 0x11;
            if (prefix_or_table_offset < 0x12)
            {
                digit_count_or_scale_index = prefix_or_table_offset;
            }
        }
        scaled_low_or_digit_count = sango_crt_scale_double_decimal(
            scaled_low_or_digit_count, scaled_high_or_length, (int *)decimal_exponent,
            digit_count_or_scale_index, decimal_digits);
        **(uint8_t **)(field_address + 0x20) = 0x30;
        scaled_high_or_length = 1;
        if (((0 < (int)scaled_low_or_digit_count) || (*(int *)(field_address + 0x10) == 0x48)) ||
            (0 < *(int *)(field_address + 0x1c)))
        {
            *(uint8_t *)(*(int *)(field_address + 0x20) + 1) = 0x2e;
            scaled_high_or_length = 2;
            crt_memcpy((void *)(*(int *)(field_address + 0x20) + 2), decimal_digits,
                       scaled_low_or_digit_count);
        }
        *(uint32_t *)(field_address + 0x3c) = scaled_high_or_length;
        *(uint32_t *)(field_address + 0x40) = scaled_low_or_digit_count;
        if (*(int *)(field_address + 0x1c) < (int)~decimal_exponent[0])
        {
            *(uint32_t *)(field_address + 0x2c) = *(uint32_t *)(field_address + 0x1c);
        }
        else
        {
            *(uint32_t *)(field_address + 0x2c) = ~decimal_exponent[0];
        }
        if (*(int *)(field_address + 0x1c) <=
            *(int *)(field_address + 0x40) + *(int *)(field_address + 0x2c))
            goto apply_zero_padding;
        digit_count_or_scale_index =
            (*(int *)(field_address + 0x1c) - *(int *)(field_address + 0x40)) -
            *(int *)(field_address + 0x2c);
    }
    else
    {
        digit_count_or_scale_index = 0x11;
        if (*(int *)(field_address + 0x1c) < (int)(0x10 - decimal_exponent[0]))
        {
            digit_count_or_scale_index = *(int *)(field_address + 0x1c) + decimal_exponent[0] + 1;
        }
        scaled_low_or_digit_count = sango_crt_scale_double_decimal(
            scaled_low_or_digit_count, scaled_high_or_length, (int *)decimal_exponent,
            digit_count_or_scale_index, decimal_digits);
        if ((int)scaled_low_or_digit_count <= (int)(decimal_exponent[0] + 1))
        {
            crt_memcpy(*(void **)(field_address + 0x20), decimal_digits, scaled_low_or_digit_count);
            *(uint32_t *)(field_address + 0x3c) = scaled_low_or_digit_count;
            if ((*(int *)(field_address + 0x10) == 0x48) || (0 < *(int *)(field_address + 0x1c)))
            {
                *(uint8_t *)(*(int *)(field_address + 0x20) + scaled_low_or_digit_count) = 0x2e;
                *(uint32_t *)(field_address + 0x40) = 1;
                *(uint32_t *)(field_address + 0x30) = *(uint32_t *)(field_address + 0x1c);
            }
            if ((int)scaled_low_or_digit_count < (int)(decimal_exponent[0] + 1))
            {
                *(uint32_t *)(field_address + 0x2c) =
                    (decimal_exponent[0] - scaled_low_or_digit_count) + 1;
            }
            goto apply_zero_padding;
        }
        crt_memcpy(*(void **)(field_address + 0x20), decimal_digits, decimal_exponent[0] + 1);
        *(uint8_t *)(*(int *)(field_address + 0x20) + decimal_exponent[0] + 1) = 0x2e;
        crt_memcpy((void *)(*(int *)(field_address + 0x20) + decimal_exponent[0] + 2),
                   decimal_digits + decimal_exponent[0] + 1,
                   (scaled_low_or_digit_count - decimal_exponent[0]) - 1);
        *(uint32_t *)(field_address + 0x3c) = decimal_exponent[0] + 1;
        *(uint32_t *)(field_address + 0x40) = scaled_low_or_digit_count - decimal_exponent[0];
        if (*(int *)(field_address + 0x1c) <=
            (int)((scaled_low_or_digit_count - decimal_exponent[0]) + -1))
            goto apply_zero_padding;
        digit_count_or_scale_index =
            (*(int *)(field_address + 0x1c) - scaled_low_or_digit_count) + decimal_exponent[0] + 1;
    }
    *(int *)(field_address + 0x30) = digit_count_or_scale_index;
apply_zero_padding:
    if (*(int *)(field_address + 0xc) != 0x48)
    {
        return;
    }
    if (*(int *)(field_address + 4) != 0x4c)
    {
        return;
    }
    digit_count_or_scale_index = *(int *)(field_address + 0x38) + *(int *)(field_address + 0x3c) +
                                 *(int *)(field_address + 0x2c) + *(int *)(field_address + 0x40) +
                                 *(int *)(field_address + 0x30);
    if (*(int *)(field_address + 0x18) <= digit_count_or_scale_index)
    {
        return;
    }
    *(int *)(field_address + 0x28) = *(int *)(field_address + 0x18) - digit_count_or_scale_index;
    return;
}
#undef decimal_digits
#undef decimal_exponent
#undef conversion

/* 原函数 0x81c1da28 */
int sango_crt_scale_double_decimal(uint32_t value_low, uint32_t value_high, int *decimal_exponent,
                                   int requested_digits, uint8_t *output_digits)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(uint8_t **)(abi_storage + 0)) = output_digits;
#define output_digits (*(uint8_t **)(abi_storage + 0))

    uint32_t ten_low;
    uint32_t ten_high;
    char carried_digit;
    int digit_index;
    uint32_t integral_digit;
    char *rounding_digit;
    int trimmed_digits;
    uint32_t scaled_high;
    uint64_t integral_as_double;
    uint64_t scaled_value;

    scaled_value = CONCAT44(value_high, value_low);
    digit_index = sango_soft_compare_f64_nan_high(value_low, value_high, 0, 0);
    ten_high = g_legacy_data_81c20c74;
    ten_low = g_legacy_data_81c20c70;
    if (digit_index == 0)
    {
        *output_digits = 0x30;
        return 1;
    }
    if (requested_digits == 0)
    {
        return 0;
    }
    digit_index = 0;
    if (0 < requested_digits + 1)
    {
        do
        {
            scaled_high = (uint32_t)((uint64_t)scaled_value >> 0x20);
            integral_digit = sango_soft_f64_to_int((uint32_t)scaled_value, scaled_high);
            output_digits[digit_index] = (char)integral_digit + '0';
            integral_as_double = sango_soft_int_to_f64(integral_digit);
            scaled_value = sango_soft_sub_f64((uint32_t)scaled_value, scaled_high,
                                              (uint32_t)integral_as_double,
                                              (int)((uint64_t)integral_as_double >> 0x20));
            scaled_value = sango_soft_mul_f64(
                (uint32_t)scaled_value, (int)((uint64_t)scaled_value >> 0x20), ten_low, ten_high);
            digit_index = digit_index + 1;
        } while (digit_index < requested_digits + 1);
    }
    digit_index = digit_index + -1;
    if (((requested_digits - *decimal_exponent) - 1 < 16) && (*decimal_exponent + 1 <= 15) &&
        (digit_index >= 16))
        digit_index = 15;
    rounding_digit = output_digits + digit_index;
    if (*rounding_digit < '5')
    {
        output_digits[digit_index] = 0x30;
        do
        {
            trimmed_digits = digit_index;
            digit_index = trimmed_digits + -1;
        } while (output_digits[trimmed_digits + -1] == '0');
    }
    else
    {
        do
        {
            trimmed_digits = digit_index;
            if (trimmed_digits == 0)
            {
                *output_digits = 0x31;
                *decimal_exponent = *decimal_exponent + 1;
                return 1;
            }
            output_digits[trimmed_digits] = 0x30;
            carried_digit = output_digits[trimmed_digits + -1] + '\x01';
            output_digits[trimmed_digits + -1] = carried_digit;
            digit_index = trimmed_digits + -1;
        } while ('9' < carried_digit);
    }
    return trimmed_digits;
}
#undef output_digits

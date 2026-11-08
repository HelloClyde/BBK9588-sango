#include "sango_internal.h"

/* 恢复的字符串与基础格式化运行库。 */

/* 原函数 0x81c1b950 */
char *sango_crt_memchr(char *buffer, int character, int byte_count)
{
    char *candidate;
    int remaining_bytes;

    remaining_bytes = byte_count + -1;
    do
    {
        candidate = buffer;
        if (remaining_bytes < 0)
        {
            return (char *)0x0;
        }
        remaining_bytes = remaining_bytes + -1;
        buffer = candidate + 1;
    } while (*candidate != character);
    return candidate;
}

/* 原函数 0x81c1b980 */
void sango_crt_sprintf_words(uint8_t *output, uint8_t *format, uint32_t argument0,
                             uint32_t argument1)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define saved_format (*(uint8_t **)(abi_storage + 4))
#define first_argument_word (*(uint32_t *)(abi_storage + 8))
#define second_argument_word (*(uint32_t *)(abi_storage + 12))
#define output_cursor (*(uint8_t **)(abi_storage + 0))

    output_cursor = output;
    saved_format = format;
    first_argument_word = argument0;
    second_argument_word = argument1;
    sango_crt_vformat(format, &first_argument_word, sango_crt_append_character, &output_cursor);
    *output_cursor = 0;
    return;
}
#undef saved_format
#undef first_argument_word
#undef second_argument_word
#undef output_cursor

/* 原函数 0x81c1b9d4 */
int sango_crt_strlen(char *text)
{
    char character;
    char *cursor;
    int length;

    length = 0;
    character = *text;
    cursor = text + 1;
    while (character != '\0')
    {
        length = length + 1;
        character = *cursor;
        cursor = cursor + 1;
    }
    return length;
}

/* 原函数 0x81c1ba04 */
int sango_crt_strtol(char *cursor, uint32_t *end_pointer, int base)
{
    int number = 0;
    int sign = 1;
    while (sango_crt_isspace(*cursor) != 0)
        cursor = cursor + 1;
    char character = *cursor;
    if (character == '+')
    {
        cursor = cursor + 1;
        character = *cursor;
    }
    else if (character == '-')
    {
        cursor = cursor + 1;
        character = *cursor;
        sign = -1;
    }

    bool alphabetic_digits;
    if (character == '0')
    {
        char *next = cursor + 1;
        if (sango_crt_toupper(*next) == 'X')
        {
            cursor = cursor + 2;
            character = *cursor;
            base = 16;
            alphabetic_digits = true;
        }
        else
        {
            cursor = next;
            character = *cursor;
            if (base == 0)
                base = 8;
            alphabetic_digits = base >= 11;
        }
    }
    else
    {
        alphabetic_digits = base >= 11;
        if (base == 0)
            base = 10;
    }

    /* 这是旧转换器的两个分支，不改成标准库strtol：
     * 十进制字符分支保留原来的进制检查及溢出阈值；0x会强制切换16进制。 */
    if (alphabetic_digits)
    {
        while (character != 0)
        {
            int digit = character - '0';
            if (sango_crt_isdigit(character) == 0)
            {
                int uppercase = sango_crt_toupper(character);
                if (uppercase < 'A' || base + 0x37 <= uppercase)
                    break;
                digit = uppercase - 0x37;
            }
            cursor = cursor + 1;
            if (base == 0)
                sango_legacy_trap(7);
            bool overflow = 0x7fffffff / base - 1 <= number;
            number = number * base + digit;
            if (overflow)
            {
                number = 0x7fffffff;
                g_runtime_errno = 0x22;
            }
            character = *cursor;
        }
    }
    else
    {
        while (sango_crt_isdigit(character) != 0)
        {
            if (base == 0)
                sango_legacy_trap(7);
            if (number < 0x7fffffff / base - 1)
                number = number * base + (int)*cursor - '0';
            else
            {
                g_runtime_errno = 0x22;
                number = 0x7fffffff;
            }
            cursor = cursor + 1;
            character = *cursor;
        }
    }
    if (end_pointer != 0)
        *end_pointer = (uint32_t)(uintptr_t)cursor;
    if (sign == -1)
        number = -number;
    return number;
}

/* 原函数 0x81c1bc58 */
void sango_crt_atoi_compat(char *text)
{
    sango_crt_strtol(text, (uint32_t *)0x0, 10);
    return;
}

/* 原函数 0x81c1bcbc */
char *sango_crt_strcpy(char *destination, char *source)
{
    char character;
    char *output_cursor;

    output_cursor = destination;
    do
    {
        character = *source;
        source = source + 1;
        *output_cursor = character;
        output_cursor = output_cursor + 1;
    } while (character != '\0');
    return destination;
}

/* 原函数 0x81c1bce0 */
void *crt_memset(void *dst, int value, uint32_t size)
{
    uint8_t *output_cursor;
    int remaining_bytes;

    output_cursor = (uint8_t *)dst;
    for (remaining_bytes = size - 1; remaining_bytes != -1; remaining_bytes = remaining_bytes + -1)
    {
        *output_cursor = (char)value;
        output_cursor = output_cursor + 1;
    }
    return dst;
}

/* 原函数 0x81c1bd08 */
void *crt_memcpy(void *dst, void *src, uint32_t size)
{
    uint8_t byte;
    uint8_t *output_cursor;
    int remaining_bytes;

    output_cursor = (uint8_t *)dst;
    for (remaining_bytes = size - 1; remaining_bytes != -1; remaining_bytes = remaining_bytes + -1)
    {
        /* WARNING: Load size is inaccurate */
        byte = *(uint8_t *)src;
        src = (void *)((int)src + 1);
        *output_cursor = byte;
        output_cursor = output_cursor + 1;
    }
    return dst;
}

/* 原函数 0x81c1bd3c */
uint8_t *sango_crt_stub_1bd3c(void)
{
    return &g_legacy_data_81c2b1e0;
}

/* 原函数 0x81c1bd48 */
void sango_crt_stub_1bd48(void)
{
    return;
}

/* 原函数 0x81c1bd50 */
int sango_crt_vformat(uint8_t *format, uint32_t *arguments, uint8_t *emit_callback_address,
                      uint32_t emit_context)
{
    unsigned char abi_storage[104] __attribute__((aligned(8)));
#define minimum_digits (*(int *)(abi_storage + 48))
#define flags (*(uint32_t *)(abi_storage + 52))
#define body_length (*(int *)(abi_storage + 56))
#define field_width (*(int *)(abi_storage + 60))
#define sign_character (*(int *)(abi_storage + 64))
#define digit_table (*(char **)(abi_storage + 68))
#define has_hex_prefix (*(uint32_t *)(abi_storage + 72))
#define has_precision_padding (*(uint32_t *)(abi_storage + 76))
#define padding_mode (*(uint32_t *)(abi_storage + 80))
#define has_field_padding (*(uint32_t *)(abi_storage + 84))

    enum
    {
        FORMAT_LONG = 1,
        FORMAT_LONG_DOUBLE = 2,
        FORMAT_SHORT = 4,
        FORMAT_ALTERNATE = 8,
        FORMAT_LEFT = 16,
        FORMAT_ZERO = 32,
        FORMAT_HEX_PREFIX = 64
    };
    SangoLegacyCode *emit = (SangoLegacyCode *)emit_callback_address;
    int output_count = 0;
    digit_table = g_legacy_data_81c20770;

    while (*format != 0)
    {
        if (*format != '%')
        {
            /* 普通文本中的换行发出CR/LF，并按实际发出的两个字节计数。 */
            if (*format == '\n')
            {
                emit('\r', emit_context);
                emit('\n', emit_context);
                output_count = output_count + 1;
            }
            else
                emit((uint32_t)*format, emit_context);
            output_count = output_count + 1;
            format = format + 1;
            continue;
        }

        flags = 0;
        minimum_digits = 0;
        field_width = 0;
        sign_character = 0;
        int precision = -1;
        char *body_cursor;
        uint32_t numeric_value = 0;
        uint32_t radix = 10;
        bool numeric_conversion = false;
        bool unsigned_conversion = false;
        bool literal_conversion = false;
        bool count_conversion = false;

        /* 扫描标志、宽度、精度及长度；遇到转换字符后进入一次输出流程。 */
        while (true)
        {
            format = format + 1;
            uint32_t conversion = (uint32_t)*format;
            if (conversion == 0)
                return output_count;
            if (conversion == ' ')
            {
                if (sign_character == 0)
                    sign_character = ' ';
                continue;
            }
            if (conversion == '#')
            {
                flags |= FORMAT_ALTERNATE;
                continue;
            }
            if (conversion == '+')
            {
                sign_character = '+';
                continue;
            }
            if (conversion == '-')
            {
                flags |= FORMAT_LEFT;
                continue;
            }
            if (conversion == '0')
            {
                flags |= FORMAT_ZERO;
                continue;
            }
            if (conversion == 'h')
            {
                flags |= FORMAT_SHORT;
                continue;
            }
            if (conversion == 'l')
            {
                flags |= FORMAT_LONG;
                continue;
            }
            if (conversion == 'L')
            {
                flags |= FORMAT_LONG_DOUBLE;
                continue;
            }
            if (conversion == '*')
            {
                uint32_t *word = (uint32_t *)((uint32_t)((int)arguments + 3) & 0xfffffffc);
                field_width = (int)*word;
                arguments = word + 1;
                if (field_width < 0)
                {
                    field_width = -field_width;
                    flags |= FORMAT_LEFT;
                }
                continue;
            }
            if (conversion >= '1' && conversion <= '9')
            {
                field_width = 0;
                do
                {
                    field_width = field_width * 10 + (uint32_t)*format - '0';
                    format = format + 1;
                } while ((char)*format >= 0 && sango_crt_isdigit(*format) != 0);
                format = format - 1;
                continue;
            }
            if (conversion == '.')
            {
                format = format + 1;
                precision = 0;
                if (*format == '*')
                {
                    uint32_t *word = (uint32_t *)((uint32_t)((int)arguments + 3) & 0xfffffffc);
                    precision = (int)*word;
                    arguments = word + 1;
                }
                else
                {
                    while ((char)*format >= 0 && sango_crt_isdigit(*format) != 0)
                    {
                        precision = precision * 10 + (uint32_t)*format - '0';
                        format = format + 1;
                    }
                    format = format - 1;
                }
                if (precision < -1)
                    precision = -1;
                continue;
            }

            if (conversion == 'n')
            {
                uint32_t *word = (uint32_t *)((uint32_t)((int)arguments + 3) & 0xfffffffc);
                arguments = word + 1;
                if ((flags & FORMAT_LONG) == 0 && (flags & FORMAT_SHORT) != 0)
                    *(short *)*word = (short)output_count;
                else
                    *(int *)*word = output_count;
                count_conversion = true;
                break;
            }
            if (conversion == 'c')
            {
                uint8_t *word = (uint8_t *)((uint32_t)((int)arguments + 3) & 0xfffffffc);
                abi_storage[16] = *word;
                body_cursor = (char *)(abi_storage + 16);
                arguments = (uint32_t *)(word + 4);
                body_length = 1;
                sign_character = 0;
                break;
            }
            if (conversion == 's')
            {
                uint32_t *word = (uint32_t *)((uint32_t)((int)arguments + 3) & 0xfffffffc);
                body_cursor = (char *)*word;
                arguments = word + 1;
                if (body_cursor == 0)
                    body_cursor = g_legacy_data_81c20798;
                if (precision < 0)
                    body_length = sango_crt_strlen(body_cursor);
                else
                {
                    char *terminator = sango_crt_memchr(body_cursor, 0, precision);
                    body_length = precision;
                    if (terminator != 0)
                    {
                        body_length = (int)terminator - (int)body_cursor;
                        if (precision < body_length)
                            body_length = precision;
                    }
                }
                sign_character = 0;
                break;
            }

            switch (conversion)
            {
            case 'D':
                flags |= FORMAT_LONG;
            case 'd':
            case 'i':
                radix = 10;
                break;
            case 'O':
                flags |= FORMAT_LONG;
            case 'o':
                radix = 8;
                unsigned_conversion = true;
                break;
            case 'U':
                flags |= FORMAT_LONG;
            case 'u':
                radix = 10;
                unsigned_conversion = true;
                break;
            case 'X':
                digit_table = g_legacy_data_81c20784;
            case 'x':
                radix = 16;
                unsigned_conversion = true;
                break;
            case 'p':
                radix = 16;
                unsigned_conversion = true;
                break;
            default:
                literal_conversion = true;
                break;
            }
            if (literal_conversion)
                break;
            uint32_t *word = (uint32_t *)((uint32_t)((int)arguments + 3) & 0xfffffffc);
            /* 原运行库对h无符号转换也按short读入，保留其符号扩展。 */
            if (conversion != 'p' && (flags & FORMAT_SHORT) != 0)
                numeric_value = (uint32_t) * (short *)word;
            else
                numeric_value = *word;
            arguments = word + 1;
            if (!unsigned_conversion && (int)numeric_value < 0)
            {
                numeric_value = -numeric_value;
                sign_character = '-';
            }
            if ((conversion == 'x' || conversion == 'X') && (flags & FORMAT_ALTERNATE) != 0 &&
                numeric_value != 0)
                flags |= FORMAT_HEX_PREFIX;
            if (unsigned_conversion)
                sign_character = 0;
            numeric_conversion = true;
            break;
        }

        if (count_conversion)
        {
            format = format + 1;
            continue;
        }
        if (literal_conversion)
        {
            emit((uint32_t)(char)*format, emit_context);
            output_count = output_count + 1;
            format = format + 1;
            continue;
        }
        if (numeric_conversion)
        {
            minimum_digits = precision;
            if (precision >= 0)
                flags &= ~FORMAT_ZERO;
            body_cursor = (char *)(abi_storage + 48);
            if (numeric_value != 0 || precision != 0)
            {
                char leading_digit;
                do
                {
                    uint32_t quotient = numeric_value / radix;
                    if (radix == 0)
                        sango_legacy_trap(7);
                    body_cursor = body_cursor - 1;
                    leading_digit = digit_table[numeric_value % radix];
                    *body_cursor = leading_digit;
                    numeric_value = quotient;
                } while (numeric_value != 0);
                digit_table = g_legacy_data_81c20770;
                if ((flags & FORMAT_ALTERNATE) != 0 && radix == 8 && leading_digit != '0')
                    *--body_cursor = '0';
            }
            body_length = (int)(abi_storage + 48) - (int)body_cursor;
        }

        /* 统一输出次序：左空格、符号/前缀、宽度零、精度零、正文、右空格。 */
        int prefixed_length = body_length;
        if (sign_character != 0)
            prefixed_length = prefixed_length + 1;
        if ((flags & FORMAT_HEX_PREFIX) != 0)
            prefixed_length = prefixed_length + 2;
        has_hex_prefix = flags & FORMAT_HEX_PREFIX;
        has_precision_padding = (uint32_t)(prefixed_length < minimum_digits);
        int measured_length = prefixed_length;
        if (prefixed_length < minimum_digits)
            measured_length = minimum_digits;
        padding_mode = flags & (FORMAT_LEFT | FORMAT_ZERO);
        uint32_t width_needed = (uint32_t)(measured_length < field_width);
        has_field_padding = width_needed;
        if (padding_mode == 0)
        {
            has_field_padding = (uint32_t)(measured_length < 0);
            if (field_width != 0)
            {
                has_field_padding = width_needed;
                if (width_needed != 0)
                    for (int position = measured_length; position < field_width; position++)
                        emit(' ', emit_context);
            }
        }
        if (sign_character != 0)
            emit(sign_character, emit_context);
        if (has_hex_prefix != 0)
        {
            emit('0', emit_context);
            emit((int)(char)*format, emit_context);
        }
        if (padding_mode == FORMAT_ZERO && has_field_padding != 0)
            for (int remaining = field_width - measured_length; remaining != 0; remaining--)
                emit('0', emit_context);
        if (has_precision_padding != 0)
            for (int remaining = minimum_digits - prefixed_length; remaining != 0; remaining--)
                emit('0', emit_context);
        for (int remaining = body_length; - 1 < remaining - 1; remaining--)
            emit((int)*body_cursor++, emit_context);
        if ((flags & FORMAT_LEFT) != 0 && has_field_padding != 0)
            for (int remaining = field_width - measured_length; remaining != 0; remaining--)
                emit(' ', emit_context);
        output_count = output_count + (has_field_padding != 0 ? field_width : measured_length);
        format = format + 1;
    }
    return output_count;
}
#undef has_hex_prefix
#undef has_precision_padding
#undef padding_mode
#undef has_field_padding
#undef digits_storage
#undef character_storage
#undef digits_tail
#undef minimum_digits
#undef flags
#undef body_length
#undef field_width
#undef sign_character
#undef digit_table

#include "sango_internal.h"

/* 恢复的整数转换、随机数及字符串辅助。 */

/* 原函数 0x81c1dc10 */
int sango_crt_heap_allocate(int requested_bytes)
{
    uint32_t block_flags_and_size;
    uint32_t block_index;
    int *block_descriptor;
    uint32_t aligned_bytes;
    int block_address;
    int legacy_gp;

    if (requested_bytes != 0)
    {
        block_descriptor = (int *)(*(int *)(legacy_gp + 0xe0) + -8);
        if (7 < *(int *)(legacy_gp + 0xe8) - *(int *)(legacy_gp + 0xf0))
        {
            block_index = 0;
            if (*(int *)(legacy_gp + 0xec) != 0)
            {
                do
                {
                    block_flags_and_size = block_descriptor[1];
                    if (((block_flags_and_size & 1) == 0) &&
                        (aligned_bytes = requested_bytes + 3U & 0xfffffffc,
                         aligned_bytes <= block_flags_and_size))
                    {
                        block_descriptor[1] = aligned_bytes | 1;
                        block_address = *block_descriptor;
                        if (block_flags_and_size - aligned_bytes == 0)
                        {
                            return block_address;
                        }
                        sango_crt_heap_shift_forward(*(uint32_t **)(legacy_gp + 0xe8),
                                                     (*(int *)(legacy_gp + 0xec) - block_index) +
                                                         -1);
                        block_descriptor[-1] = block_flags_and_size - aligned_bytes;
                        block_descriptor[-2] = block_address + aligned_bytes;
                        *(int *)(legacy_gp + 0xe8) = *(int *)(legacy_gp + 0xe8) + -8;
                        *(int *)(legacy_gp + 0xec) = *(int *)(legacy_gp + 0xec) + 1;
                        return block_address;
                    }
                    block_index = block_index + 1;
                    block_descriptor = block_descriptor + -2;
                } while (block_index < *(uint32_t *)(legacy_gp + 0xec));
            }
            if ((requested_bytes + 3U & 0xfffffffc) + 8 <=
                (uint32_t)(*(int *)(legacy_gp + 0xe8) - *(int *)(legacy_gp + 0xf0)))
            {
                block_address = *(int *)(legacy_gp + 0xf0);
                *block_descriptor = block_address;
                block_index = requested_bytes + 3U & 0xfffffffc;
                block_descriptor[1] = block_index | 1;
                *(uint32_t *)(legacy_gp + 0xf0) = block_index + *(int *)(legacy_gp + 0xf0);
                *(int *)(legacy_gp + 0xec) = *(int *)(legacy_gp + 0xec) + 1;
                *(int *)(legacy_gp + 0xe8) = *(int *)(legacy_gp + 0xe8) + -8;
                return block_address;
            }
        }
        g_runtime_errno = 0xc;
    }
    return 0;
}

/* 原函数 0x81c1dd88 */
uint32_t sango_crt_heap_initialize(int heap_begin, int heap_end)
{
    bool range_too_small;
    uint32_t aligned_begin;
    uint32_t aligned_end;
    int legacy_gp;

    aligned_begin = heap_begin + 3U & 0xfffffffc;
    *(uint32_t *)(legacy_gp + 0xe4) = aligned_begin;
    aligned_end = heap_end + 3U & 0xfffffffc;
    *(uint32_t *)(legacy_gp + 0xe0) = aligned_end;
    range_too_small = aligned_end < aligned_begin + 0x10;
    if (!range_too_small)
    {
        *(uint32_t *)(legacy_gp + 0xf0) = *(uint32_t *)(legacy_gp + 0xe4);
        *(int *)(legacy_gp + 0xe8) = *(int *)(legacy_gp + 0xe0) + -8;
        *(uint32_t *)(legacy_gp + 0xec) = 0;
    }
    return (uint32_t)range_too_small;
}

/* 原函数 0x81c1de00 */
int sango_crt_abs(int value)
{
    if (value < 0)
    {
        value = -value;
    }
    return value;
}

/* 原函数 0x81c1de20 */
uint32_t crt_rand(void)
{
    g_random_seed = g_random_seed * 0x41c64e6d + 0x3039;
    return g_random_seed / 0xffff & 0x7fff;
}

/* 原函数 0x81c1de60 */
void crt_srand(uint32_t seed)
{
    g_random_seed = seed;
    return;
}

/* 原函数 0x81c1de70 */
char *sango_crt_strcat(char *destination, char *source)
{
    char character;
    char *terminator_search;
    char *output_cursor;

    terminator_search = destination;
    do
    {
        output_cursor = terminator_search;
        terminator_search = output_cursor + 1;
    } while (*output_cursor != '\0');
    output_cursor = output_cursor + -1;
    do
    {
        character = *source;
        source = source + 1;
        output_cursor = output_cursor + 1;
        *output_cursor = character;
    } while (character != '\0');
    return destination;
}

/* 原函数 0x81c1deb0 */
void sango_crt_heap_shift_forward(uint32_t *descriptor_words, int descriptor_count)
{
    int descriptor_index;

    descriptor_index = 0;
    if (0 < descriptor_count)
    {
        do
        {
            descriptor_words[-2] = *descriptor_words;
            descriptor_words[-1] = descriptor_words[1];
            descriptor_index = descriptor_index + 1;
            descriptor_words = descriptor_words + 2;
        } while (descriptor_index < descriptor_count);
    }
    return;
}

/* 原函数 0x81c1dee0 */
void sango_crt_zero_bytes(uint8_t *buffer, int byte_count)
{
    uint8_t *destination;
    int byte_index;

    byte_index = 0;
    destination = buffer;
    if (0 < byte_count)
    {
        do
        {
            *destination = 0;
            byte_index = byte_index + 1;
            destination = buffer + byte_index;
        } while (byte_index < byte_count);
    }
    return;
}

/* 原函数 0x81c1df08 */
void sango_crt_heap_shift_backward(uint32_t *destination, int block_count)
{
    int block_index;

    block_index = 0;
    if (0 < block_count)
    {
        do
        {
            *destination = destination[-2];
            destination[1] = destination[-1];
            block_index = block_index + 1;
            destination = destination + -2;
        } while (block_index < block_count);
    }
    return;
}

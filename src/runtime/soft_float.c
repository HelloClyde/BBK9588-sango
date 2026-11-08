#include "sango_internal.h"

/* 恢复的IEEE754软件浮点实现。 */

/* 原函数 0x81c1df40 */
uint32_t sango_soft_f32_to_int(uint32_t float_bits)
{
    int range_comparison;
    uint32_t converted_value;

    range_comparison = sango_soft_compare_f32(float_bits, g_legacy_data_81c20c60);
    if (range_comparison < 0)
    {
        converted_value = sango_soft_unpack_f32_integer(float_bits);
    }
    else
    {
        converted_value = soft_float_add(float_bits, g_legacy_data_81c20c64);
        converted_value = sango_soft_unpack_f32_integer(converted_value);
        converted_value = converted_value + 0x80000000;
    }
    return converted_value;
}

/* 原函数 0x81c1dfb0 */
uint32_t *sango_soft_add_f32_parts(uint32_t *left, uint32_t *right, uint32_t *output)
{
    SangoSoftF32Parts *left_parts = (SangoSoftF32Parts *)left;
    SangoSoftF32Parts *right_parts = (SangoSoftF32Parts *)right;
    SangoSoftF32Parts *output_parts = (SangoSoftF32Parts *)output;
    uint32_t left_kind;
    uint32_t right_kind;

    bool left_has_smaller_exponent;
    int exponent_distance;
    uint32_t significand;
    uint32_t aligned_exponent;
    uint32_t *chosen_parts;
    uint32_t result_exponent;
    uint32_t left_exponent;
    uint32_t right_significand;

    left_kind = left_parts->kind;
    chosen_parts = left;
    if ((1 < left_kind) && (right_kind = right_parts->kind, chosen_parts = right, 1 < right_kind))
    {
        if (left_kind == 4)
        {
            chosen_parts = left;
            if (((right_kind ^ 4) == 0) && (chosen_parts = (uint32_t *)&g_legacy_data_81c20c00,
                                            left_parts->sign == right_parts->sign))
            {
                chosen_parts = left;
            }
        }
        else
        {
            chosen_parts = right;
            if ((right_kind ^ 4) != 0)
            {
                if (right_kind == 2)
                {
                    chosen_parts = left;
                    if ((left_kind ^ 2) == 0)
                    {
                        output_parts->kind = left_kind;
                        output_parts->sign = left_parts->sign;
                        output_parts->exponent_bits = left_parts->exponent_bits;
                        output_parts->significand = left_parts->significand;
                        output_parts->sign = left_parts->sign & right_parts->sign;
                        chosen_parts = output;
                    }
                }
                else
                {
                    chosen_parts = right;
                    if ((left_kind ^ 2) != 0)
                    {
                        /* 对阶时保留右移丢失位作为sticky位；随后做同号加法或异号减法。 */
                        left_exponent = left_parts->exponent_bits;
                        result_exponent = right_parts->exponent_bits;
                        significand = left_parts->significand;
                        exponent_distance = left_exponent - result_exponent;
                        if (exponent_distance < 0)
                        {
                            exponent_distance = -exponent_distance;
                        }
                        right_significand = right_parts->significand;
                        if (exponent_distance < 0x20)
                        {
                            left_has_smaller_exponent = (int)left_exponent < (int)result_exponent;
                            aligned_exponent = result_exponent;
                            if ((int)left_exponent > (int)result_exponent)
                            {
                                exponent_distance = left_exponent - result_exponent;
                                do
                                {
                                    exponent_distance = exponent_distance + -1;
                                    right_significand =
                                        right_significand & 1 | right_significand >> 1;
                                } while (exponent_distance != 0);
                                left_has_smaller_exponent = false;
                                aligned_exponent = left_exponent;
                            }
                            result_exponent = left_exponent;
                            if (left_has_smaller_exponent)
                            {
                                exponent_distance = aligned_exponent - left_exponent;
                                do
                                {
                                    exponent_distance = exponent_distance + -1;
                                    significand = significand & 1 | significand >> 1;
                                    result_exponent = aligned_exponent;
                                } while (exponent_distance != 0);
                            }
                        }
                        else if ((int)left_exponent <= (int)result_exponent)
                        {
                            significand = 0;
                        }
                        else
                        {
                            right_significand = 0;
                            result_exponent = left_exponent;
                        }
                        uint32_t left_sign = left_parts->sign;
                        if (left_sign == right_parts->sign)
                        {
                            significand = significand + right_significand;
                            output_parts->sign = left_sign;
                            output_parts->exponent_bits = result_exponent;
                            output_parts->significand = significand;
                        }
                        else
                        {
                            uint32_t difference = right_significand - significand;
                            if (left_sign == 0)
                            {
                                difference = significand - right_significand;
                            }
                            if ((int)difference < 0)
                            {
                                output_parts->sign = 1;
                                output_parts->exponent_bits = result_exponent;
                                output_parts->significand = -difference;
                            }
                            else
                            {
                                output_parts->exponent_bits = result_exponent;
                                output_parts->significand = difference;
                                output_parts->sign = 0;
                            }
                            significand = output_parts->significand;
                            if (significand - 1 < 0x3fffffff)
                            {
                                result_exponent = output_parts->exponent_bits;
                                do
                                {
                                    significand = significand * 2;
                                    result_exponent = result_exponent - 1;
                                } while (significand - 1 < 0x3fffffff);
                                output_parts->exponent_bits = result_exponent;
                                output_parts->significand = significand;
                            }
                        }
                        output_parts->kind = 3;
                        chosen_parts = output;
                        if ((int)significand < 0)
                        {
                            output_parts->significand = significand & 1 | significand >> 1;
                            output_parts->exponent_bits = output_parts->exponent_bits + 1;
                        }
                    }
                }
            }
        }
    }
    return chosen_parts;
}

/* 原函数 0x81c1e1ec */
uint32_t soft_float_add(uint32_t left, uint32_t right)
{
    unsigned char abi_storage[72] __attribute__((aligned(8)));
#define left_bits (*(uint32_t *)(abi_storage + 48))
#define right_bits (*(uint32_t *)(abi_storage + 52))
#define right_parts (*(uint32_t(*)[4])(abi_storage + 16))
#define left_parts (*(uint32_t(*)[4])(abi_storage + 0))
#define sum_parts (*(uint32_t(*)[4])(abi_storage + 32))

    uint32_t *result_parts;
    uint32_t result_bits;

    left_bits = left;
    right_bits = right;
    sango_soft_unpack_f32(&left_bits, left_parts);
    sango_soft_unpack_f32(&right_bits, right_parts);
    result_parts = sango_soft_add_f32_parts(left_parts, right_parts, sum_parts);
    result_bits = sango_soft_pack_f32(result_parts);
    return result_bits;
}
#undef left_bits
#undef right_bits
#undef right_parts
#undef left_parts
#undef sum_parts

/* 原函数 0x81c1e24c */
uint32_t soft_float_sub(uint32_t left, uint32_t right)
{
    unsigned char abi_storage[72] __attribute__((aligned(8)));
#define left_parts (*(uint32_t(*)[4])(abi_storage + 0))
#define right_sign (*(uint32_t *)(abi_storage + 20))
#define left_bits (*(uint32_t *)(abi_storage + 48))
#define right_bits (*(uint32_t *)(abi_storage + 52))
#define right_parts_start (*(uint32_t *)(abi_storage + 16))
#define difference_parts (*(uint32_t(*)[4])(abi_storage + 32))

    uint32_t *result_parts;
    uint32_t result_bits;

    left_bits = left;
    right_bits = right;
    sango_soft_unpack_f32(&left_bits, left_parts);
    sango_soft_unpack_f32(&right_bits, &right_parts_start);
    right_sign = right_sign ^ 1;
    result_parts = sango_soft_add_f32_parts(left_parts, &right_parts_start, difference_parts);
    result_bits = sango_soft_pack_f32(result_parts);
    return result_bits;
}
#undef left_parts
#undef right_sign
#undef left_bits
#undef right_bits
#undef right_parts_start
#undef difference_parts

/* 原函数 0x81c1e2c0 */
uint32_t soft_float_mul(uint32_t left, uint32_t right)
{
    unsigned char abi_storage[72] __attribute__((aligned(8)));
#define left_kind (*(uint32_t *)(abi_storage + 0))
#define left_sign (*(uint32_t *)(abi_storage + 4))
#define left_exponent (*(int *)(abi_storage + 8))
#define left_significand (*(uint32_t *)(abi_storage + 12))
#define right_kind (*(uint32_t *)(abi_storage + 16))
#define right_sign (*(uint32_t *)(abi_storage + 20))
#define right_exponent (*(int *)(abi_storage + 24))
#define right_significand (*(uint32_t *)(abi_storage + 28))
#define result_kind (*(uint32_t *)(abi_storage + 32))
#define result_sign (*(uint32_t *)(abi_storage + 36))
#define result_exponent (*(int *)(abi_storage + 40))
#define result_significand (*(uint32_t *)(abi_storage + 44))
#define left_bits (*(uint32_t *)(abi_storage + 48))
#define right_bits (*(uint32_t *)(abi_storage + 52))

    uint64_t wide_product;
    uint32_t product_word;
    uint32_t *chosen_parts;

    left_bits = left;
    right_bits = right;
    sango_soft_unpack_f32(&left_bits, &left_kind);
    sango_soft_unpack_f32(&right_bits, &right_kind);
    chosen_parts = &result_kind;
    if (left_kind < 2)
    {
    use_left_special_value:
        left_sign = (uint32_t)(left_sign != right_sign);
        chosen_parts = &left_kind;
    }
    else
    {
        if (1 < right_kind)
        {
            if (left_kind == 4)
            {
                chosen_parts = (uint32_t *)&g_legacy_data_81c20c00;
                if (right_kind == 2)
                    goto pack_product;
                goto use_left_special_value;
            }
            if (right_kind == 4)
            {
                chosen_parts = (uint32_t *)&g_legacy_data_81c20c00;
                if ((left_kind ^ 2) == 0)
                    goto pack_product;
            }
            else
            {
                if ((left_kind ^ 2) == 0)
                    goto use_left_special_value;
                if (right_kind != 2)
                {
                    wide_product = (uint64_t)left_significand * (uint64_t)right_significand;
                    result_exponent = left_exponent + right_exponent + 2;
                    result_sign = (uint32_t)(left_sign != right_sign);
                    if ((int64_t)wide_product < 0)
                    {
                        product_word = (uint32_t)wide_product;
                        result_exponent = left_exponent + right_exponent + 3;
                        if ((wide_product & 0x100000000) != 0)
                        {
                            product_word = product_word >> 1 | 0x80000000;
                        }
                        wide_product = CONCAT44((uint32_t)(wide_product >> 0x21), product_word);
                    }
                    if (wide_product < 0x4000000000000000)
                    {
                        do
                        {
                            product_word = (int)(wide_product >> 0x20) << 1;
                            result_exponent = result_exponent + -1;
                            if ((int)wide_product < 0)
                            {
                                product_word = product_word | 1;
                            }
                            wide_product = CONCAT44(product_word, (int)wide_product << 1);
                        } while (product_word < 0x40000000);
                    }
                    result_significand = (uint32_t)(wide_product >> 0x20);
                    if (((result_significand & 0x7f) == 0x40) &&
                        (((wide_product & 0x8000000000) != 0 || ((int)wide_product != 0))))
                    {
                        result_significand = result_significand + 0x40;
                    }
                    result_kind = 3;
                    goto pack_product;
                }
            }
        }
        right_sign = (uint32_t)(left_sign != right_sign);
        chosen_parts = &right_kind;
    }
pack_product:
    product_word = sango_soft_pack_f32(chosen_parts);
    return product_word;
}
#undef left_kind
#undef left_sign
#undef left_exponent
#undef left_significand
#undef right_kind
#undef right_sign
#undef right_exponent
#undef right_significand
#undef result_kind
#undef result_sign
#undef result_exponent
#undef result_significand
#undef left_bits
#undef right_bits

/* 原函数 0x81c1e4b0 */
uint32_t soft_float_div(uint32_t left, uint32_t right)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define left_kind (*(uint32_t *)(abi_storage + 0))
#define left_sign (*(uint32_t *)(abi_storage + 4))
#define left_exponent (*(int *)(abi_storage + 8))
#define left_significand (*(uint32_t *)(abi_storage + 12))
#define right_kind (*(uint32_t *)(abi_storage + 16))
#define right_sign (*(uint32_t *)(abi_storage + 20))
#define right_exponent (*(int *)(abi_storage + 24))
#define right_significand (*(uint32_t *)(abi_storage + 28))
#define left_bits (*(uint32_t *)(abi_storage + 32))
#define right_bits (*(uint32_t *)(abi_storage + 36))

    bool remainder_below_divisor;
    uint32_t quotient_or_result_bits;
    uint32_t quotient_bit;
    uint32_t *result_parts;

    left_bits = left;
    right_bits = right;
    sango_soft_unpack_f32(&left_bits, &left_kind);
    sango_soft_unpack_f32(&right_bits, &right_kind);
    result_parts = &left_kind;
    if ((left_kind < 2) || (result_parts = &right_kind, right_kind < 2))
        goto pack_division_result;
    left_sign = left_sign ^ right_sign;
    if ((left_kind == 4) || (left_kind == 2))
    {
        result_parts = (uint32_t *)&g_legacy_data_81c20c00;
        quotient_or_result_bits = left_significand;
        if (left_kind == right_kind)
            goto pack_division_result;
    }
    else
    {
        if (right_kind == 4)
        {
            left_significand = 0;
            left_exponent = 0;
            result_parts = &left_kind;
            goto pack_division_result;
        }
        if (right_kind == 2)
        {
            left_kind = 4;
            result_parts = &left_kind;
            goto pack_division_result;
        }
        remainder_below_divisor = left_significand < right_significand;
        left_exponent = left_exponent - right_exponent;
        if (remainder_below_divisor)
        {
            left_exponent = left_exponent + -1;
            left_significand = left_significand << 1;
            remainder_below_divisor = left_significand < right_significand;
        }
        quotient_bit = 0x40000000;
        quotient_or_result_bits = 0;
        do
        {
            if (!remainder_below_divisor)
            {
                quotient_or_result_bits = quotient_or_result_bits | quotient_bit;
                left_significand = left_significand - right_significand;
            }
            left_significand = left_significand << 1;
            quotient_bit = quotient_bit >> 1;
            remainder_below_divisor = left_significand < right_significand;
        } while (quotient_bit != 0);
        if (((quotient_or_result_bits & 0x7f) == 0x40) &&
            (((quotient_or_result_bits & 0x80) != 0 || (left_significand != 0))))
        {
            quotient_or_result_bits = quotient_or_result_bits + 0x40;
        }
    }
    left_significand = quotient_or_result_bits;
    result_parts = &left_kind;
pack_division_result:
    quotient_or_result_bits = sango_soft_pack_f32(result_parts);
    return quotient_or_result_bits;
}
#undef left_kind
#undef left_sign
#undef left_exponent
#undef left_significand
#undef right_kind
#undef right_sign
#undef right_exponent
#undef right_significand
#undef left_bits
#undef right_bits

/* 原函数 0x81c1e620 */
int sango_soft_compare_f32(uint32_t left, uint32_t right)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define left_parts (*(uint32_t(*)[4])(abi_storage + 0))
#define right_parts (*(uint32_t(*)[4])(abi_storage + 16))
#define left_bits (*(uint32_t *)(abi_storage + 32))
#define right_bits (*(uint32_t *)(abi_storage + 36))

    int comparison;

    left_bits = left;
    right_bits = right;
    sango_soft_unpack_f32(&left_bits, left_parts);
    sango_soft_unpack_f32(&right_bits, right_parts);
    comparison = -1;
    if ((1 < left_parts[0]) && (1 < right_parts[0]))
    {
        comparison = sango_soft_compare_f32_parts(left_parts, right_parts);
    }
    return comparison;
}
#undef left_parts
#undef right_parts
#undef left_bits
#undef right_bits

/* 原函数 0x81c1e6b0 */
uint32_t sango_soft_int_to_f32(uint32_t integer_value)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define exponent (*(int *)(abi_storage + 8))
#define significand (*(uint32_t *)(abi_storage + 12))
#define kind (*(uint32_t *)(abi_storage + 0))
#define sign (*(int *)(abi_storage + 4))

    uint32_t result_bits;

    sign = -((int)integer_value >> 0x1f);
    kind = 3;
    if (integer_value == 0)
    {
        kind = 2;
    }
    else
    {
        exponent = 0x1e;
        significand = integer_value;
        if (sign != 0)
        {
            if (integer_value == 0x80000000)
            {
                return g_legacy_data_81c20c64;
            }
            significand = -integer_value;
        }
        if (significand < 0x40000000)
        {
            exponent = 0x1e;
            do
            {
                significand = significand << 1;
                exponent = exponent + -1;
            } while (significand < 0x40000000);
        }
    }
    result_bits = sango_soft_pack_f32(&kind);
    return result_bits;
}
#undef exponent
#undef significand
#undef kind
#undef sign

/* 原函数 0x81c1e770 */
uint32_t sango_soft_unpack_f32_integer(uint32_t float_bits)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define kind (*(uint32_t *)(abi_storage + 0))
#define sign (*(int *)(abi_storage + 4))
#define exponent (*(int *)(abi_storage + 8))
#define significand (*(uint32_t *)(abi_storage + 12))
#define source_bits (*(uint32_t(*)[2])(abi_storage + 16))

    source_bits[0] = float_bits;
    sango_soft_unpack_f32(source_bits, &kind);
    if (kind == 2)
    {
        return 0;
    }
    if (kind < 2)
    {
        return 0;
    }
    if (kind != 4)
    {
        if (exponent < 0)
        {
            return 0;
        }
        if (exponent < 0x1f)
        {
            significand = significand >> (0x1eU - exponent & 0x1f);
            if (sign == 0)
            {
                return significand;
            }
            return -significand;
        }
    }
    return 0x80000000 - (sign == 0);
}
#undef kind
#undef sign
#undef exponent
#undef significand
#undef source_bits

/* 原函数 0x81c1e810 */
uint32_t *sango_soft_add_f64_parts(uint32_t *left, uint32_t *right, uint32_t *output)
{
    SangoSoftF64Parts *left_parts = (SangoSoftF64Parts *)left;
    SangoSoftF64Parts *right_parts = (SangoSoftF64Parts *)right;
    SangoSoftF64Parts *output_parts = (SangoSoftF64Parts *)output;
    uint32_t left_kind;
    uint32_t right_kind;

    bool left_has_smaller_exponent;
    int exponent_distance;
    uint32_t significand_high;
    uint32_t result_exponent;
    uint32_t aligned_exponent;
    uint32_t difference_high;
    uint32_t *chosen_parts;
    uint32_t right_significand_low;
    uint32_t right_significand_high;
    uint32_t left_significand_low;
    uint32_t left_exponent;

    left_kind = left_parts->kind;
    chosen_parts = left;
    if ((1 < left_kind) && (right_kind = right_parts->kind, chosen_parts = right, 1 < right_kind))
    {
        if (left_kind == 4)
        {
            chosen_parts = left;
            if (((right_kind ^ 4) == 0) && (chosen_parts = (uint32_t *)&g_legacy_data_81c20c10,
                                            left_parts->sign == right_parts->sign))
            {
                chosen_parts = left;
            }
        }
        else
        {
            chosen_parts = right;
            if ((right_kind ^ 4) != 0)
            {
                if (right_kind == 2)
                {
                    chosen_parts = left;
                    if ((left_kind ^ 2) == 0)
                    {
                        output_parts->kind = left_kind;
                        output_parts->sign = left_parts->sign;
                        output_parts->exponent_bits = left_parts->exponent_bits;
                        output_parts->reserved = left_parts->reserved;
                        output_parts->significand_low = left_parts->significand_low;
                        output_parts->significand_high = left_parts->significand_high;
                        output_parts->sign = left_parts->sign & right_parts->sign;
                        chosen_parts = output;
                    }
                }
                else
                {
                    chosen_parts = right;
                    if ((left_kind ^ 2) != 0)
                    {
                        /* 对阶时保留右移丢失位作为sticky位；随后做同号加法或异号减法。 */
                        left_exponent = left_parts->exponent_bits;
                        result_exponent = right_parts->exponent_bits;
                        left_significand_low = left_parts->significand_low;
                        significand_high = left_parts->significand_high;
                        exponent_distance = left_exponent - result_exponent;
                        if (exponent_distance < 0)
                        {
                            exponent_distance = -exponent_distance;
                        }
                        right_significand_low = right_parts->significand_low;
                        right_significand_high = right_parts->significand_high;
                        if (exponent_distance < 0x40)
                        {
                            left_has_smaller_exponent = (int)left_exponent < (int)result_exponent;
                            aligned_exponent = result_exponent;
                            if ((int)left_exponent > (int)result_exponent)
                            {
                                exponent_distance = left_exponent - result_exponent;
                                do
                                {
                                    uint32_t shift_carry = right_significand_high << 0x1f;
                                    right_significand_high = right_significand_high >> 1;
                                    exponent_distance = exponent_distance + -1;
                                    right_significand_low = right_significand_low & 1 |
                                                            right_significand_low >> 1 |
                                                            shift_carry;
                                } while (exponent_distance != 0);
                                left_has_smaller_exponent = false;
                                aligned_exponent = left_exponent;
                            }
                            result_exponent = left_exponent;
                            if (left_has_smaller_exponent)
                            {
                                exponent_distance = aligned_exponent - left_exponent;
                                do
                                {
                                    uint32_t shift_carry = significand_high << 0x1f;
                                    significand_high = significand_high >> 1;
                                    exponent_distance = exponent_distance + -1;
                                    left_significand_low = left_significand_low & 1 |
                                                           left_significand_low >> 1 | shift_carry;
                                    result_exponent = aligned_exponent;
                                } while (exponent_distance != 0);
                            }
                        }
                        else if ((int)left_exponent <= (int)result_exponent)
                        {
                            left_significand_low = 0;
                            significand_high = 0;
                        }
                        else
                        {
                            right_significand_low = 0;
                            right_significand_high = 0;
                            result_exponent = left_exponent;
                        }
                        uint32_t left_sign = left_parts->sign;
                        if (left_sign == right_parts->sign)
                        {
                            output_parts->sign = left_sign;
                            output_parts->exponent_bits = result_exponent;
                            output_parts->significand_low =
                                left_significand_low + right_significand_low;
                            output_parts->significand_high =
                                significand_high + right_significand_high +
                                (uint32_t)(left_significand_low + right_significand_low <
                                           right_significand_low);
                        }
                        else
                        {
                            uint32_t difference_low = right_significand_low - left_significand_low;
                            difference_high =
                                (right_significand_high - significand_high) -
                                (uint32_t)(right_significand_low < left_significand_low);
                            if (left_sign == 0)
                            {
                                difference_low = left_significand_low - right_significand_low;
                                difference_high =
                                    (significand_high - right_significand_high) -
                                    (uint32_t)(left_significand_low < right_significand_low);
                            }
                            if ((int)difference_high < 0)
                            {
                                output_parts->sign = 1;
                                output_parts->exponent_bits = result_exponent;
                                output_parts->significand_low = -difference_low;
                                output_parts->significand_high =
                                    -(uint32_t)(-difference_low != 0) - difference_high;
                            }
                            else
                            {
                                output_parts->exponent_bits = result_exponent;
                                output_parts->significand_low = difference_low;
                                output_parts->significand_high = difference_high;
                                output_parts->sign = 0;
                            }
                            result_exponent = output_parts->significand_low;
                            significand_high = output_parts->significand_high;
                            uint32_t normalization_guard =
                                (significand_high - 1) + (uint32_t)(result_exponent != 0);
                            while ((normalization_guard < 0x10000000 &&
                                    ((normalization_guard != 0xfffffff || (result_exponent != 0)))))
                            {
                                significand_high = significand_high << 1 | result_exponent >> 0x1f;
                                result_exponent = result_exponent * 2;
                                normalization_guard =
                                    (significand_high - 1) + (uint32_t)(result_exponent != 0);
                                output_parts->exponent_bits = output_parts->exponent_bits - 1;
                                output_parts->significand_low = result_exponent;
                                output_parts->significand_high = significand_high;
                            }
                        }
                        output_parts->kind = 3;
                        chosen_parts = output;
                        if (0x1fffffff < output_parts->significand_high)
                        {
                            output_parts->significand_low = output_parts->significand_low & 1 |
                                                            output_parts->significand_low >> 1 |
                                                            output_parts->significand_high << 0x1f;
                            output_parts->significand_high = output_parts->significand_high >> 1;
                            output_parts->exponent_bits = output_parts->exponent_bits + 1;
                        }
                    }
                }
            }
        }
    }
    return chosen_parts;
}

/* 原函数 0x81c1eb70 */
uint64_t sango_soft_add_f64(uint32_t left_low, uint32_t left_high, uint32_t right_low,
                            uint32_t right_high)
{
    unsigned char abi_storage[104] __attribute__((aligned(8)));
#define right_bits_low (*(uint32_t *)(abi_storage + 80))
#define right_bits_high (*(uint32_t *)(abi_storage + 84))
#define right_parts (*(uint32_t(*)[6])(abi_storage + 24))
#define left_parts (*(uint32_t(*)[6])(abi_storage + 0))
#define sum_parts (*(uint32_t(*)[6])(abi_storage + 48))
#define left_bits_low (*(uint32_t *)(abi_storage + 72))
#define left_bits_high (*(uint32_t *)(abi_storage + 76))

    uint32_t *result_parts;
    uint64_t result_bits;

    left_bits_low = left_low;
    left_bits_high = left_high;
    right_bits_low = right_low;
    right_bits_high = right_high;
    sango_soft_unpack_f64(&left_bits_low, left_parts);
    sango_soft_unpack_f64(&right_bits_low, right_parts);
    result_parts = sango_soft_add_f64_parts(left_parts, right_parts, sum_parts);
    result_bits = sango_soft_pack_f64(result_parts);
    return result_bits;
}
#undef right_bits_low
#undef right_bits_high
#undef right_parts
#undef left_parts
#undef sum_parts
#undef left_bits_low
#undef left_bits_high

/* 原函数 0x81c1ebd8 */
uint64_t sango_soft_sub_f64(uint32_t left_low, uint32_t left_high, uint32_t right_low,
                            uint32_t right_high)
{
    unsigned char abi_storage[104] __attribute__((aligned(8)));
#define right_sign (*(uint32_t *)(abi_storage + 28))
#define left_bits_low (*(uint32_t *)(abi_storage + 72))
#define left_bits_high (*(uint32_t *)(abi_storage + 76))
#define left_parts (*(uint32_t(*)[6])(abi_storage + 0))
#define right_bits_low (*(uint32_t *)(abi_storage + 80))
#define right_bits_high (*(uint32_t *)(abi_storage + 84))
#define right_parts_start (*(uint32_t *)(abi_storage + 24))
#define difference_parts (*(uint32_t(*)[6])(abi_storage + 48))

    uint32_t *result_parts;
    uint64_t result_bits;

    left_bits_low = left_low;
    left_bits_high = left_high;
    right_bits_low = right_low;
    right_bits_high = right_high;
    sango_soft_unpack_f64(&left_bits_low, left_parts);
    sango_soft_unpack_f64(&right_bits_low, &right_parts_start);
    right_sign = right_sign ^ 1;
    result_parts = sango_soft_add_f64_parts(left_parts, &right_parts_start, difference_parts);
    result_bits = sango_soft_pack_f64(result_parts);
    return result_bits;
}
#undef right_sign
#undef left_bits_low
#undef left_bits_high
#undef left_parts
#undef right_bits_low
#undef right_bits_high
#undef right_parts_start
#undef difference_parts

/* 原函数 0x81c1ec50 */
uint64_t sango_soft_mul_f64(uint32_t left_low, uint32_t left_high, uint32_t right_low,
                            uint32_t right_high)
{
    unsigned char abi_storage[104] __attribute__((aligned(8)));
#define left_kind (*(uint32_t *)(abi_storage + 0))
#define left_sign (*(uint32_t *)(abi_storage + 4))
#define left_exponent (*(int *)(abi_storage + 8))
#define left_significand_low (*(uint32_t *)(abi_storage + 16))
#define left_significand_high (*(uint32_t *)(abi_storage + 20))
#define right_kind (*(uint32_t *)(abi_storage + 24))
#define right_sign (*(uint32_t *)(abi_storage + 28))
#define right_exponent (*(int *)(abi_storage + 32))
#define right_significand_low (*(uint32_t *)(abi_storage + 40))
#define right_significand_high (*(uint32_t *)(abi_storage + 44))
#define result_kind (*(uint32_t *)(abi_storage + 48))
#define result_sign (*(uint32_t *)(abi_storage + 52))
#define result_exponent (*(int *)(abi_storage + 56))
#define result_significand (*(uint64_t *)(abi_storage + 64))
#define left_bits_low (*(uint32_t *)(abi_storage + 72))
#define left_bits_high (*(uint32_t *)(abi_storage + 76))
#define right_bits_low (*(uint32_t *)(abi_storage + 80))
#define right_bits_high (*(uint32_t *)(abi_storage + 84))

    int64_t cross_product0;
    int64_t cross_product_sum;
    uint64_t normalization_candidate;
    uint64_t shifted_high_word;
    uint32_t *chosen_parts;
    uint32_t middle_product_word;
    uint32_t cross_sum_high;
    uint32_t cross_sum_carry;
    uint32_t low_product_word;
    uint32_t cross_product0_high;
    uint32_t low_product_high;
    uint64_t packed_result;

    left_bits_low = left_low;
    left_bits_high = left_high;
    right_bits_low = right_low;
    right_bits_high = right_high;
    sango_soft_unpack_f64(&left_bits_low, &left_kind);
    sango_soft_unpack_f64(&right_bits_low, &right_kind);
    chosen_parts = &result_kind;
    if (left_kind < 2)
    {
    use_left_special_value:
        left_sign = (uint32_t)(left_sign != right_sign);
        chosen_parts = &left_kind;
    }
    else
    {
        if (1 < right_kind)
        {
            if (left_kind == 4)
            {
                chosen_parts = (uint32_t *)&g_legacy_data_81c20c10;
                if (right_kind == 2)
                    goto pack_product;
                goto use_left_special_value;
            }
            if (right_kind == 4)
            {
                chosen_parts = (uint32_t *)&g_legacy_data_81c20c10;
                if ((left_kind ^ 2) == 0)
                    goto pack_product;
            }
            else
            {
                if ((left_kind ^ 2) == 0)
                    goto use_left_special_value;
                if (right_kind != 2)
                {
                    cross_sum_carry = 0;
                    cross_product0 =
                        (uint64_t)right_significand_high * (uint64_t)left_significand_low;
                    cross_product0_high = (uint32_t)((uint64_t)cross_product0 >> 0x20);
                    cross_product_sum =
                        (uint64_t)right_significand_low * (uint64_t)left_significand_high +
                        cross_product0;
                    middle_product_word = (uint32_t)cross_product_sum;
                    cross_sum_high = (uint32_t)((uint64_t)cross_product_sum >> 0x20);
                    low_product_word = (uint32_t)((uint64_t)right_significand_low *
                                                  (uint64_t)left_significand_low);
                    low_product_high = (uint32_t)((uint64_t)right_significand_low *
                                                      (uint64_t)left_significand_low >>
                                                  0x20);
                    if ((cross_sum_high < cross_product0_high) ||
                        ((cross_product0_high == cross_sum_high &&
                          (middle_product_word < (uint32_t)cross_product0))))
                    {
                        cross_sum_carry = 1;
                    }
                    middle_product_word = low_product_high + middle_product_word;
                    result_significand =
                        (uint64_t)right_significand_high * (uint64_t)left_significand_high +
                        CONCAT44(cross_sum_carry, cross_sum_high) +
                        (uint64_t)(middle_product_word < low_product_high);
                    result_sign = (uint32_t)(left_sign != right_sign);
                    result_exponent = left_exponent + right_exponent + 4;
                    normalization_candidate = result_significand;
                    if (0x1fffffffffffffff < result_significand)
                    {
                        do
                        {
                            normalization_candidate = result_significand & 1;
                            shifted_high_word = result_significand >> 0x21;
                            result_exponent = result_exponent + 1;
                            result_significand = result_significand >> 1;
                            if (normalization_candidate != 0)
                            {
                                low_product_word = low_product_word >> 1 | middle_product_word
                                                                               << 0x1f;
                                middle_product_word = middle_product_word >> 1 | 0x80000000;
                            }
                            normalization_candidate = result_significand;
                        } while (0x1fffffff < (uint32_t)shifted_high_word);
                    }
                    while (normalization_candidate < 0x1000000000000000)
                    {
                        result_exponent = result_exponent + -1;
                        normalization_candidate = result_significand << 1;
                        cross_sum_high = (uint32_t)normalization_candidate;
                        if ((int)middle_product_word < 0)
                        {
                            cross_sum_high = cross_sum_high | 1;
                        }
                        result_significand =
                            CONCAT44((int)(normalization_candidate >> 0x20), cross_sum_high);
                        middle_product_word = middle_product_word << 1 | low_product_word >> 0x1f;
                        low_product_word = low_product_word << 1;
                    }
                    if ((((uint32_t)result_significand & 0xff) == 0x80) &&
                        (((result_significand & 0x100) != 0 ||
                          (low_product_word != 0 || middle_product_word != 0))))
                    {
                        result_significand = result_significand + 0x80;
                    }
                    result_kind = 3;
                    goto pack_product;
                }
            }
        }
        right_sign = (uint32_t)(left_sign != right_sign);
        chosen_parts = &right_kind;
    }
pack_product:
    packed_result = sango_soft_pack_f64(chosen_parts);
    return packed_result;
}
#undef left_kind
#undef left_sign
#undef left_exponent
#undef left_significand_low
#undef left_significand_high
#undef right_kind
#undef right_sign
#undef right_exponent
#undef right_significand_low
#undef right_significand_high
#undef result_kind
#undef result_sign
#undef result_exponent
#undef result_significand
#undef left_bits_low
#undef left_bits_high
#undef right_bits_low
#undef right_bits_high

/* 原函数 0x81c1efe0 */
uint64_t sango_soft_div_f64(uint32_t left_low, uint32_t left_high, uint32_t right_low,
                            uint32_t right_high)
{
    unsigned char abi_storage[80] __attribute__((aligned(8)));
#define left_kind (*(uint32_t *)(abi_storage + 0))
#define result_sign (*(uint32_t *)(abi_storage + 4))
#define result_exponent (*(int *)(abi_storage + 8))
#define remainder_low (*(uint32_t *)(abi_storage + 16))
#define remainder_high (*(uint32_t *)(abi_storage + 20))
#define right_kind (*(uint32_t *)(abi_storage + 24))
#define right_sign (*(uint32_t *)(abi_storage + 28))
#define right_exponent (*(int *)(abi_storage + 32))
#define divisor_low (*(uint32_t *)(abi_storage + 40))
#define divisor_high (*(uint32_t *)(abi_storage + 44))
#define left_bits_low (*(uint32_t *)(abi_storage + 48))
#define left_bits_high (*(uint32_t *)(abi_storage + 52))
#define right_bits_low (*(uint32_t *)(abi_storage + 56))
#define right_bits_high (*(uint32_t *)(abi_storage + 60))

    bool remainder_below_divisor;
    uint32_t *chosen_parts;
    uint32_t quotient_bit_low;
    uint32_t quotient_bit_high;
    uint32_t quotient_low;
    uint32_t quotient_high;
    uint64_t packed_result;

    left_bits_low = left_low;
    left_bits_high = left_high;
    right_bits_low = right_low;
    right_bits_high = right_high;
    sango_soft_unpack_f64(&left_bits_low, &left_kind);
    sango_soft_unpack_f64(&right_bits_low, &right_kind);
    chosen_parts = &left_kind;
    quotient_bit_low = remainder_low;
    quotient_high = remainder_high;
    if ((1 < left_kind) && (chosen_parts = &right_kind, 1 < right_kind))
    {
        result_sign = result_sign ^ right_sign;
        if ((left_kind == 4) || (left_kind == 2))
        {
            chosen_parts = (uint32_t *)&g_legacy_data_81c20c10;
            if (left_kind != right_kind)
            {
                chosen_parts = &left_kind;
            }
        }
        else if (right_kind == 4)
        {
            remainder_low = 0;
            remainder_high = 0;
            result_exponent = 0;
            chosen_parts = &left_kind;
            quotient_bit_low = remainder_low;
            quotient_high = remainder_high;
        }
        else if (right_kind == 2)
        {
            left_kind = 4;
            chosen_parts = &left_kind;
        }
        else
        {
            remainder_below_divisor = remainder_high < divisor_high;
            result_exponent = result_exponent - right_exponent;
            if ((remainder_below_divisor) ||
                ((divisor_high == remainder_high && (remainder_low < divisor_low))))
            {
                result_exponent = result_exponent + -1;
                remainder_high = remainder_high << 1 | remainder_low >> 0x1f;
                remainder_low = remainder_low << 1;
                remainder_below_divisor = remainder_high < divisor_high;
            }
            quotient_bit_high = 0x10000000;
            quotient_bit_low = 0;
            quotient_low = 0;
            quotient_high = 0;
            do
            {
                if ((!remainder_below_divisor) &&
                    ((divisor_high != remainder_high || (divisor_low <= remainder_low))))
                {
                    remainder_below_divisor = remainder_low < divisor_low;
                    remainder_low = remainder_low - divisor_low;
                    remainder_high =
                        (remainder_high - divisor_high) - (uint32_t)remainder_below_divisor;
                    quotient_low = quotient_low | quotient_bit_low;
                    quotient_high = quotient_high | quotient_bit_high;
                }
                quotient_bit_low = quotient_bit_low >> 1 | quotient_bit_high << 0x1f;
                quotient_bit_high = quotient_bit_high >> 1;
                remainder_high = remainder_high << 1 | remainder_low >> 0x1f;
                remainder_low = remainder_low << 1;
                remainder_below_divisor = remainder_high < divisor_high;
            } while (quotient_bit_low != 0 || quotient_bit_high != 0);
            chosen_parts = &left_kind;
            quotient_bit_low = quotient_low;
            if (((quotient_low & 0xff) == 0x80) &&
                (((quotient_low & 0x100) != 0 || (remainder_low != 0 || remainder_high != 0))))
            {
                quotient_bit_low = quotient_low + 0x80;
                quotient_high = quotient_high + (quotient_low + 0x80 < 0x80);
            }
        }
    }
    remainder_high = quotient_high;
    remainder_low = quotient_bit_low;
    packed_result = sango_soft_pack_f64(chosen_parts);
    return packed_result;
}
#undef left_kind
#undef result_sign
#undef result_exponent
#undef remainder_low
#undef remainder_high
#undef right_kind
#undef right_sign
#undef right_exponent
#undef divisor_low
#undef divisor_high
#undef left_bits_low
#undef left_bits_high
#undef right_bits_low
#undef right_bits_high

/* 原函数 0x81c1f210 */
int sango_soft_compare_f64_nan_high(uint32_t left_low, uint32_t left_high, uint32_t right_low,
                                    uint32_t right_high)
{
    unsigned char abi_storage[80] __attribute__((aligned(8)));
#define left_parts (*(uint32_t(*)[6])(abi_storage + 0))
#define right_parts (*(uint32_t(*)[6])(abi_storage + 24))
#define left_bits_low (*(uint32_t *)(abi_storage + 48))
#define left_bits_high (*(uint32_t *)(abi_storage + 52))
#define right_bits_low (*(uint32_t *)(abi_storage + 56))
#define right_bits_high (*(uint32_t *)(abi_storage + 60))

    int comparison;

    left_bits_low = left_low;
    left_bits_high = left_high;
    right_bits_low = right_low;
    right_bits_high = right_high;
    sango_soft_unpack_f64(&left_bits_low, left_parts);
    sango_soft_unpack_f64(&right_bits_low, right_parts);
    comparison = 1;
    if ((1 < left_parts[0]) && (1 < right_parts[0]))
    {
        comparison = sango_soft_compare_f64_parts(left_parts, right_parts);
    }
    return comparison;
}
#undef left_parts
#undef right_parts
#undef left_bits_low
#undef left_bits_high
#undef right_bits_low
#undef right_bits_high

/* 原函数 0x81c1f2a0 */
int sango_soft_compare_f64_nan_low(uint32_t left_low, uint32_t left_high, uint32_t right_low,
                                   uint32_t right_high)
{
    unsigned char abi_storage[80] __attribute__((aligned(8)));
#define left_bits_high (*(uint32_t *)(abi_storage + 52))
#define right_bits_low (*(uint32_t *)(abi_storage + 56))
#define right_bits_high (*(uint32_t *)(abi_storage + 60))
#define left_parts (*(uint32_t(*)[6])(abi_storage + 0))
#define right_parts (*(uint32_t(*)[6])(abi_storage + 24))
#define left_bits_low (*(uint32_t *)(abi_storage + 48))

    int comparison;

    left_bits_low = left_low;
    left_bits_high = left_high;
    right_bits_low = right_low;
    right_bits_high = right_high;
    sango_soft_unpack_f64(&left_bits_low, left_parts);
    sango_soft_unpack_f64(&right_bits_low, right_parts);
    comparison = -1;
    if ((1 < left_parts[0]) && (1 < right_parts[0]))
    {
        comparison = sango_soft_compare_f64_parts(left_parts, right_parts);
    }
    return comparison;
}
#undef left_bits_high
#undef right_bits_low
#undef right_bits_high
#undef left_parts
#undef right_parts
#undef left_bits_low

/* 原函数 0x81c1f330 */
int sango_soft_compare_f64_nan_low_compat(uint32_t left_low, uint32_t left_high, uint32_t right_low,
                                          uint32_t right_high)
{
    unsigned char abi_storage[80] __attribute__((aligned(8)));
#define right_parts (*(uint32_t(*)[6])(abi_storage + 24))
#define left_bits_low (*(uint32_t *)(abi_storage + 48))
#define left_bits_high (*(uint32_t *)(abi_storage + 52))
#define right_bits_low (*(uint32_t *)(abi_storage + 56))
#define right_bits_high (*(uint32_t *)(abi_storage + 60))
#define left_parts (*(uint32_t(*)[6])(abi_storage + 0))

    int comparison;

    left_bits_low = left_low;
    left_bits_high = left_high;
    right_bits_low = right_low;
    right_bits_high = right_high;
    sango_soft_unpack_f64(&left_bits_low, left_parts);
    sango_soft_unpack_f64(&right_bits_low, right_parts);
    comparison = -1;
    if ((1 < left_parts[0]) && (1 < right_parts[0]))
    {
        comparison = sango_soft_compare_f64_parts(left_parts, right_parts);
    }
    return comparison;
}
#undef right_parts
#undef left_bits_low
#undef left_bits_high
#undef right_bits_low
#undef right_bits_high
#undef left_parts

/* 原函数 0x81c1f3c0 */
int sango_soft_compare_f64_nan_high_compat(uint32_t left_low, uint32_t left_high,
                                           uint32_t right_low, uint32_t right_high)
{
    unsigned char abi_storage[80] __attribute__((aligned(8)));
#define left_parts (*(uint32_t(*)[6])(abi_storage + 0))
#define right_parts (*(uint32_t(*)[6])(abi_storage + 24))
#define left_bits_low (*(uint32_t *)(abi_storage + 48))
#define left_bits_high (*(uint32_t *)(abi_storage + 52))
#define right_bits_low (*(uint32_t *)(abi_storage + 56))
#define right_bits_high (*(uint32_t *)(abi_storage + 60))

    int comparison;

    left_bits_low = left_low;
    left_bits_high = left_high;
    right_bits_low = right_low;
    right_bits_high = right_high;
    sango_soft_unpack_f64(&left_bits_low, left_parts);
    sango_soft_unpack_f64(&right_bits_low, right_parts);
    comparison = 1;
    if ((1 < left_parts[0]) && (1 < right_parts[0]))
    {
        comparison = sango_soft_compare_f64_parts(left_parts, right_parts);
    }
    return comparison;
}
#undef left_parts
#undef right_parts
#undef left_bits_low
#undef left_bits_high
#undef right_bits_low
#undef right_bits_high

/* 原函数 0x81c1f450 */
uint64_t sango_soft_int_to_f64(uint32_t integer_value)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define kind (*(uint32_t *)(abi_storage + 0))
#define sign (*(int *)(abi_storage + 4))
#define exponent (*(int *)(abi_storage + 8))
#define significand_low (*(uint32_t *)(abi_storage + 16))
#define significand_high (*(uint32_t *)(abi_storage + 20))

    uint32_t sign_extension;
    uint64_t result_bits;

    sign_extension = (int)integer_value >> 0x1f;
    sign = -sign_extension;
    kind = 3;
    if (integer_value == 0)
    {
        kind = 2;
    }
    else
    {
        exponent = 0x3c;
        if (sign != 0)
        {
            if (integer_value == 0x80000000)
            {
                return CONCAT44(g_legacy_data_81c20c84, g_legacy_data_81c20c80);
            }
            integer_value = -integer_value;
            sign_extension = (int)integer_value >> 0x1f;
        }
        significand_low = integer_value;
        significand_high = sign_extension;
        if (sign_extension < 0x10000000)
        {
            exponent = 0x3c;
            do
            {
                significand_high = significand_high << 1 | significand_low >> 0x1f;
                significand_low = significand_low << 1;
                exponent = exponent + -1;
            } while (significand_high < 0x10000000);
        }
    }
    result_bits = sango_soft_pack_f64(&kind);
    return result_bits;
}
#undef kind
#undef sign
#undef exponent
#undef significand_low
#undef significand_high

/* 原函数 0x81c1f540 */
uint32_t sango_soft_f64_to_int(uint32_t float_low, uint32_t float_high)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define kind (*(uint32_t *)(abi_storage + 0))
#define sign (*(int *)(abi_storage + 4))
#define exponent (*(int *)(abi_storage + 8))
#define significand_low (*(uint32_t *)(abi_storage + 16))
#define significand_high (*(uint32_t *)(abi_storage + 20))
#define source_low (*(uint32_t *)(abi_storage + 24))
#define source_high (*(uint32_t *)(abi_storage + 28))

    uint32_t right_shift;

    source_low = float_low;
    source_high = float_high;
    sango_soft_unpack_f64(&source_low, &kind);
    if (kind == 2)
    {
        return 0;
    }
    if (kind < 2)
    {
        return 0;
    }
    if (kind != 4)
    {
        if (exponent < 0)
        {
            return 0;
        }
        if (exponent < 0x1f)
        {
            right_shift = 0x3c - exponent;
            if ((int)(right_shift * 0x4000000) < 0)
            {
                significand_low = significand_high >> (right_shift & 0x1f);
            }
            else
            {
                significand_low = significand_low >> (right_shift & 0x1f);
                if (right_shift * 0x4000000 != 0)
                {
                    significand_low = significand_low | significand_high << (-right_shift & 0x1f);
                }
            }
            if (sign == 0)
            {
                return significand_low;
            }
            return -significand_low;
        }
    }
    return 0x80000000 - (sign == 0);
}
#undef kind
#undef sign
#undef exponent
#undef significand_low
#undef significand_high
#undef source_low
#undef source_high

/* 原函数 0x81c1f620 */
uint32_t sango_soft_pack_f32(uint32_t *parts)
{
    uint32_t kind_or_exponent;
    uint32_t significand;
    uint32_t encoded_exponent;

    kind_or_exponent = *parts;
    significand = parts[3];
    encoded_exponent = 0;
    if (kind_or_exponent < 2)
    {
        significand = significand | 0x100000;
        encoded_exponent = 0xff;
        goto assemble_float_bits;
    }
    if (kind_or_exponent == 4)
    {
    encode_infinity:
        encoded_exponent = 0xff;
    }
    else if (kind_or_exponent != 2)
    {
        if (significand == 0)
            goto assemble_float_bits;
        kind_or_exponent = parts[2];
        if ((int)kind_or_exponent < -0x7e)
        {
            kind_or_exponent = -kind_or_exponent - 0x7e;
            if ((int)kind_or_exponent < 0x1a)
            {
                significand =
                    significand >> (kind_or_exponent & 0x1f) |
                    (uint32_t)((significand & (1 << (kind_or_exponent & 0x1f)) - 1U) != 0);
            }
            else
            {
                significand = 0;
            }
            if ((significand & 0x7f) == 0x40)
            {
                if ((significand & 0x80) != 0)
                {
                    significand = significand + 0x40;
                }
            }
            else
            {
                significand = significand + 0x3f;
            }
            if (0x3fffffff < significand)
            {
                encoded_exponent = 1;
            }
        }
        else
        {
            if (0x7f < (int)kind_or_exponent)
                goto encode_infinity;
            encoded_exponent = kind_or_exponent + 0x7f;
            if ((significand & 0x7f) == 0x40)
            {
                if ((significand & 0x80) != 0)
                {
                    significand = significand + 0x40;
                }
            }
            else
            {
                significand = significand + 0x3f;
            }
            if ((int)significand < 0)
            {
                significand = significand >> 1;
                encoded_exponent = kind_or_exponent + 0x80;
            }
        }
        significand = significand >> 7;
        goto assemble_float_bits;
    }
    significand = 0;
assemble_float_bits:
    return significand & 0x7fffff | (encoded_exponent & 0xff) << 0x17 | parts[1] << 0x1f;
}

/* 原函数 0x81c1f790 */
void sango_soft_unpack_f32(uint32_t *source_bits, uint32_t *parts)
{
    uint32_t float_bits;
    uint32_t kind;
    int exponent;
    uint32_t encoded_exponent;
    uint32_t significand;

    float_bits = *source_bits;
    encoded_exponent = float_bits >> 0x17 & 0xff;
    parts[1] = float_bits >> 0x1f;
    significand = float_bits & 0x7fffff;
    if (encoded_exponent == 0)
    {
        kind = 2;
        if (significand != 0)
        {
            significand = significand << 7;
            exponent = -0x7e;
            parts[2] = 0xffffff82;
            *parts = 3;
            if (significand < 0x40000000)
            {
                do
                {
                    significand = significand << 1;
                    exponent = exponent + -1;
                } while (significand < 0x40000000);
                parts[2] = exponent;
            }
        store_significand:
            parts[3] = significand;
            return;
        }
    }
    else if (encoded_exponent == 0xff)
    {
        kind = 4;
        if (significand != 0)
        {
            if ((float_bits & 0x100000) == 0)
            {
                *parts = 0;
            }
            else
            {
                *parts = 1;
            }
            goto store_significand;
        }
    }
    else
    {
        parts[3] = significand << 7 | 0x40000000;
        kind = 3;
        parts[2] = encoded_exponent - 0x7f;
    }
    *parts = kind;
    return;
}

/* 原函数 0x81c1f860 */
int sango_soft_compare_f32_parts(uint32_t *left_parts, uint32_t *right_parts)
{
    int comparison;
    uint32_t left_kind_or_sign;
    uint32_t right_kind;

    left_kind_or_sign = *left_parts;
    if (left_kind_or_sign < 2)
    {
        return 1;
    }
    right_kind = *right_parts;
    if (right_kind < 2)
    {
        return 1;
    }
    if ((left_kind_or_sign == 4) && (right_kind == 4))
    {
        return right_parts[1] - left_parts[1];
    }
    if (left_kind_or_sign == 4)
    {
    compare_left_sign:
        if (left_parts[1] != 0)
        {
            return -1;
        }
        return 1;
    }
    if (right_kind != 4)
    {
        if (left_kind_or_sign != 2)
        {
            if (right_kind == 2)
                goto compare_left_sign;
            left_kind_or_sign = left_parts[1];
            if (left_kind_or_sign == right_parts[1])
            {
                if ((int)left_parts[2] <= (int)right_parts[2])
                {
                    if ((int)right_parts[2] <= (int)left_parts[2])
                    {
                        if (right_parts[3] < left_parts[3])
                            goto left_magnitude_greater;
                        if (right_parts[3] <= left_parts[3])
                        {
                            return 0;
                        }
                    }
                    if (left_kind_or_sign != 0)
                    {
                        return 1;
                    }
                    return -1;
                }
            }
        left_magnitude_greater:
            if (left_kind_or_sign != 0)
            {
                return -1;
            }
            return 1;
        }
        if (right_kind == 2)
        {
            return 0;
        }
    }
    comparison = 1;
    if (right_parts[1] == 0)
    {
        comparison = -1;
    }
    return comparison;
}

/* 原函数 0x81c1f9a0 */
uint64_t sango_soft_pack_f64(uint32_t *parts)
{
    const SangoSoftF64Parts *value = (const SangoSoftF64Parts *)parts;
    uint32_t kind = value->kind;
    uint32_t significand_low = value->significand_low;
    uint32_t significand_high = value->significand_high;
    uint32_t biased_exponent = 0;

    if (kind < 2)
    {
        /* NaN尾数保持原负载，同时设置quiet位。 */
        significand_high = significand_high | 0x80000;
        biased_exponent = 0x7ff;
    }
    else if (kind == 4 || kind == 2)
    {
        if (kind == 4)
            biased_exponent = 0x7ff;
        significand_low = 0;
        significand_high = 0;
    }
    else if (significand_low != 0 || significand_high != 0)
    {
        uint32_t exponent = value->exponent_bits;
        if ((int)exponent < -0x3fe)
        {
            uint32_t shift = -exponent - 0x3fe;
            if ((int)shift < 0x39)
            {
                uint32_t high_shift_marker;
                int low_shift_marker;
                if ((int)(shift * 0x4000000) < 0)
                {
                    high_shift_marker = 1 << (shift & 0x1f);
                    low_shift_marker = 0;
                }
                else
                {
                    high_shift_marker = 0 << (shift & 0x1f);
                    if (shift * 0x4000000 != 0)
                        high_shift_marker = high_shift_marker | 1U >> (-shift & 0x1f);
                    low_shift_marker = 1 << (shift & 0x1f);
                }
                /* 保留旧双字移位的掩码运算及sticky位规则，不替换成宿主double。 */
                uint32_t high_lost_bits =
                    significand_high &
                    (high_shift_marker - 1) + (uint32_t)(low_shift_marker - 1U != 0xffffffff);
                uint32_t shifted_low;
                if ((int)(shift * 0x4000000) < 0)
                {
                    shifted_low = significand_high >> (shift & 0x1f);
                    significand_high = 0;
                }
                else
                {
                    shifted_low = significand_low >> (shift & 0x1f);
                    if (shift * 0x4000000 != 0)
                        shifted_low = shifted_low | significand_high << (-shift & 0x1f);
                    significand_high = significand_high >> (shift & 0x1f);
                }
                significand_low = shifted_low | ((significand_low & low_shift_marker - 1U) != 0 ||
                                                 high_lost_bits != 0);
            }
            else
            {
                significand_low = 0;
                significand_high = 0;
            }

            /* 非规格化数：保留八个保护位的ties-to-even舍入，进位可变成最小规格数。 */
            bool apply_rounding =
                (significand_low & 0xff) != 0x80 || (significand_low & 0x100) != 0;
            if (apply_rounding)
            {
                uint32_t increment = (significand_low & 0xff) == 0x80 ? 0x80 : 0x7f;
                significand_low = significand_low + increment;
                significand_high = significand_high + (significand_low < increment);
            }
            if (0xfffffff < significand_high)
                biased_exponent = 1;
            uint32_t cross_word_bits = significand_high << 0x18;
            significand_low = significand_low >> 8 | cross_word_bits;
            significand_high = significand_high >> 8;
        }
        else if ((int)exponent > 0x3ff)
        {
            biased_exponent = 0x7ff;
            significand_low = 0;
            significand_high = 0;
        }
        else
        {
            biased_exponent = exponent + 0x3ff;
            bool apply_rounding =
                (significand_low & 0xff) != 0x80 || (significand_low & 0x100) != 0;
            if (apply_rounding)
            {
                uint32_t increment = (significand_low & 0xff) == 0x80 ? 0x80 : 0x7f;
                significand_low = significand_low + increment;
                significand_high = significand_high + (significand_low < increment);
            }
            if (0x1fffffff < significand_high)
            {
                significand_low = significand_low >> 1 | significand_high << 0x1f;
                significand_high = significand_high >> 1;
                biased_exponent = exponent + 0x400;
            }
            uint32_t cross_word_bits = significand_high << 0x18;
            significand_low = significand_low >> 8 | cross_word_bits;
            significand_high = significand_high >> 8;
        }
    }
    return CONCAT44(significand_high & 0xfffff | (biased_exponent & 0x7ff) << 0x14 |
                        value->sign << 0x1f,
                    significand_low);
}

/* 原函数 0x81c1fc40 */
void sango_soft_unpack_f64(uint32_t *source_bits, uint32_t *parts)
{
    uint32_t float_high;
    uint32_t kind;
    int exponent;
    uint32_t encoded_exponent;
    uint32_t significand_low;
    uint32_t significand_high;

    float_high = source_bits[1];
    encoded_exponent = float_high >> 0x14 & 0x7ff;
    significand_low = *source_bits;
    significand_high = float_high & 0xfffff;
    parts[1] = float_high >> 0x1f;
    if (encoded_exponent == 0)
    {
        if (significand_low != 0 || significand_high != 0)
        {
            significand_high = significand_high << 8 | significand_low >> 0x18;
            significand_low = significand_low << 8;
            parts[2] = 0xfffffc02;
            *parts = 3;
            if (significand_high < 0x10000000)
            {
                exponent = -0x3fe;
                do
                {
                    significand_high = significand_high << 1 | significand_low >> 0x1f;
                    significand_low = significand_low << 1;
                    exponent = exponent + -1;
                } while (significand_high < 0x10000000);
                parts[2] = exponent;
            }
        store_significand:
            parts[4] = significand_low;
            parts[5] = significand_high;
            return;
        }
        kind = 2;
    }
    else if (encoded_exponent == 0x7ff)
    {
        kind = 4;
        if (significand_low != 0 || significand_high != 0)
        {
            if ((float_high & 0x80000) == 0)
            {
                *parts = 0;
            }
            else
            {
                *parts = 1;
            }
            goto store_significand;
        }
    }
    else
    {
        parts[4] = significand_low << 8;
        parts[5] = significand_high << 8 | significand_low >> 0x18 | 0x10000000;
        kind = 3;
        parts[2] = encoded_exponent - 0x3ff;
    }
    *parts = kind;
    return;
}

/* 原函数 0x81c1fd60 */
int sango_soft_compare_f64_parts(uint32_t *left_parts, uint32_t *right_parts)
{
    int comparison;
    uint32_t left_kind_or_sign;
    uint32_t right_kind_or_significand_high;
    uint32_t left_significand_high;

    left_kind_or_sign = *left_parts;
    if (left_kind_or_sign < 2)
    {
        return 1;
    }
    right_kind_or_significand_high = *right_parts;
    if (right_kind_or_significand_high < 2)
    {
        return 1;
    }
    if ((left_kind_or_sign == 4) && (right_kind_or_significand_high == 4))
    {
        return right_parts[1] - left_parts[1];
    }
    if (left_kind_or_sign == 4)
    {
    compare_left_sign:
        if (left_parts[1] != 0)
        {
            return -1;
        }
        return 1;
    }
    if (right_kind_or_significand_high != 4)
    {
        if (left_kind_or_sign != 2)
        {
            if (right_kind_or_significand_high == 2)
                goto compare_left_sign;
            left_kind_or_sign = left_parts[1];
            if (left_kind_or_sign == right_parts[1])
            {
                if ((int)left_parts[2] <= (int)right_parts[2])
                {
                    if ((int)right_parts[2] <= (int)left_parts[2])
                    {
                        left_significand_high = left_parts[5];
                        right_kind_or_significand_high = right_parts[5];
                        if ((right_kind_or_significand_high < left_significand_high) ||
                            ((left_significand_high == right_kind_or_significand_high &&
                              (right_parts[4] < left_parts[4]))))
                            goto left_magnitude_greater;
                        if (right_kind_or_significand_high <= left_significand_high)
                        {
                            if (right_kind_or_significand_high != left_significand_high)
                            {
                                return 0;
                            }
                            if (right_parts[4] <= left_parts[4])
                            {
                                return 0;
                            }
                        }
                    }
                    if (left_kind_or_sign != 0)
                    {
                        return 1;
                    }
                    return -1;
                }
            }
        left_magnitude_greater:
            if (left_kind_or_sign != 0)
            {
                return -1;
            }
            return 1;
        }
        if (right_kind_or_significand_high == 2)
        {
            return 0;
        }
    }
    comparison = 1;
    if (right_parts[1] == 0)
    {
        comparison = -1;
    }
    return comparison;
}

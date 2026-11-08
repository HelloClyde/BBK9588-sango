#include "sango_internal.h"

/* 恢复的IEEE754软件浮点实现。 */

/* 原函数 0x81c1df40 */
uint32_t sango_soft_f32_to_int(uint32_t param_1)
{
    int iVar1;
    uint32_t uVar2;

    iVar1 = sango_soft_compare_f32(param_1, g_legacy_data_81c20c60);
    if (iVar1 < 0)
    {
        uVar2 = sango_soft_unpack_f32_integer(param_1);
    }
    else
    {
        uVar2 = soft_float_add(param_1, g_legacy_data_81c20c64);
        uVar2 = sango_soft_unpack_f32_integer(uVar2);
        uVar2 = uVar2 + 0x80000000;
    }
    return uVar2;
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
#define local_10 (*(uint32_t *)(abi_storage + 48))
#define local_c (*(uint32_t *)(abi_storage + 52))
#define auStack_30 (*(uint32_t(*)[4])(abi_storage + 16))
#define auStack_40 (*(uint32_t(*)[4])(abi_storage + 0))
#define auStack_20 (*(uint32_t(*)[4])(abi_storage + 32))

    uint32_t *puVar1;
    uint32_t uVar2;

    local_10 = left;
    local_c = right;
    sango_soft_unpack_f32(&local_10, auStack_40);
    sango_soft_unpack_f32(&local_c, auStack_30);
    puVar1 = sango_soft_add_f32_parts(auStack_40, auStack_30, auStack_20);
    uVar2 = sango_soft_pack_f32(puVar1);
    return uVar2;
}
#undef local_10
#undef local_c
#undef auStack_30
#undef auStack_40
#undef auStack_20

/* 原函数 0x81c1e24c */
uint32_t soft_float_sub(uint32_t left, uint32_t right)
{
    unsigned char abi_storage[72] __attribute__((aligned(8)));
#define auStack_40 (*(uint32_t(*)[4])(abi_storage + 0))
#define local_2c (*(uint32_t *)(abi_storage + 20))
#define local_10 (*(uint32_t *)(abi_storage + 48))
#define local_c (*(uint32_t *)(abi_storage + 52))
#define uStack_30 (*(uint32_t *)(abi_storage + 16))
#define auStack_20 (*(uint32_t(*)[4])(abi_storage + 32))

    uint32_t *puVar1;
    uint32_t uVar2;

    local_10 = left;
    local_c = right;
    sango_soft_unpack_f32(&local_10, auStack_40);
    sango_soft_unpack_f32(&local_c, &uStack_30);
    local_2c = local_2c ^ 1;
    puVar1 = sango_soft_add_f32_parts(auStack_40, &uStack_30, auStack_20);
    uVar2 = sango_soft_pack_f32(puVar1);
    return uVar2;
}
#undef auStack_40
#undef local_2c
#undef local_10
#undef local_c
#undef uStack_30
#undef auStack_20

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
#define local_30 (*(uint32_t *)(abi_storage + 0))
#define local_2c (*(uint32_t *)(abi_storage + 4))
#define local_28 (*(int *)(abi_storage + 8))
#define local_24 (*(uint32_t *)(abi_storage + 12))
#define local_20 (*(uint32_t *)(abi_storage + 16))
#define local_1c (*(uint32_t *)(abi_storage + 20))
#define local_18 (*(int *)(abi_storage + 24))
#define local_14 (*(uint32_t *)(abi_storage + 28))
#define local_10 (*(uint32_t *)(abi_storage + 32))
#define local_c (*(uint32_t *)(abi_storage + 36))

    bool bVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint32_t *puVar4;

    local_10 = left;
    local_c = right;
    sango_soft_unpack_f32(&local_10, &local_30);
    sango_soft_unpack_f32(&local_c, &local_20);
    puVar4 = &local_30;
    if ((local_30 < 2) || (puVar4 = &local_20, local_20 < 2))
        goto LAB_81c1e548;
    local_2c = local_2c ^ local_1c;
    if ((local_30 == 4) || (local_30 == 2))
    {
        puVar4 = (uint32_t *)&g_legacy_data_81c20c00;
        uVar2 = local_24;
        if (local_30 == local_20)
            goto LAB_81c1e548;
    }
    else
    {
        if (local_20 == 4)
        {
            local_24 = 0;
            local_28 = 0;
            puVar4 = &local_30;
            goto LAB_81c1e548;
        }
        if (local_20 == 2)
        {
            local_30 = 4;
            puVar4 = &local_30;
            goto LAB_81c1e548;
        }
        bVar1 = local_24 < local_14;
        local_28 = local_28 - local_18;
        if (bVar1)
        {
            local_28 = local_28 + -1;
            local_24 = local_24 << 1;
            bVar1 = local_24 < local_14;
        }
        uVar3 = 0x40000000;
        uVar2 = 0;
        do
        {
            if (!bVar1)
            {
                uVar2 = uVar2 | uVar3;
                local_24 = local_24 - local_14;
            }
            local_24 = local_24 << 1;
            uVar3 = uVar3 >> 1;
            bVar1 = local_24 < local_14;
        } while (uVar3 != 0);
        if (((uVar2 & 0x7f) == 0x40) && (((uVar2 & 0x80) != 0 || (local_24 != 0))))
        {
            uVar2 = uVar2 + 0x40;
        }
    }
    local_24 = uVar2;
    puVar4 = &local_30;
LAB_81c1e548:
    uVar2 = sango_soft_pack_f32(puVar4);
    return uVar2;
}
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c

/* 原函数 0x81c1e620 */
int sango_soft_compare_f32(uint32_t param_1, uint32_t param_2)
{
    unsigned char abi_storage[56] __attribute__((aligned(8)));
#define local_30 (*(uint32_t(*)[4])(abi_storage + 0))
#define local_20 (*(uint32_t(*)[4])(abi_storage + 16))
#define local_10 (*(uint32_t *)(abi_storage + 32))
#define local_c (*(uint32_t *)(abi_storage + 36))

    int iVar1;

    local_10 = param_1;
    local_c = param_2;
    sango_soft_unpack_f32(&local_10, local_30);
    sango_soft_unpack_f32(&local_c, local_20);
    iVar1 = -1;
    if ((1 < local_30[0]) && (1 < local_20[0]))
    {
        iVar1 = sango_soft_compare_f32_parts(local_30, local_20);
    }
    return iVar1;
}
#undef local_30
#undef local_20
#undef local_10
#undef local_c

/* 原函数 0x81c1e6b0 */
uint32_t sango_soft_int_to_f32(uint32_t param_1)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define local_10 (*(int *)(abi_storage + 8))
#define local_c (*(uint32_t *)(abi_storage + 12))
#define local_18 (*(uint32_t *)(abi_storage + 0))
#define local_14 (*(int *)(abi_storage + 4))

    uint32_t uVar1;

    local_14 = -((int)param_1 >> 0x1f);
    local_18 = 3;
    if (param_1 == 0)
    {
        local_18 = 2;
    }
    else
    {
        local_10 = 0x1e;
        local_c = param_1;
        if (local_14 != 0)
        {
            if (param_1 == 0x80000000)
            {
                return g_legacy_data_81c20c64;
            }
            local_c = -param_1;
        }
        if (local_c < 0x40000000)
        {
            local_10 = 0x1e;
            do
            {
                local_c = local_c << 1;
                local_10 = local_10 + -1;
            } while (local_c < 0x40000000);
        }
    }
    uVar1 = sango_soft_pack_f32(&local_18);
    return uVar1;
}
#undef local_10
#undef local_c
#undef local_18
#undef local_14

/* 原函数 0x81c1e770 */
uint32_t sango_soft_unpack_f32_integer(uint32_t param_1)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define local_20 (*(uint32_t *)(abi_storage + 0))
#define local_1c (*(int *)(abi_storage + 4))
#define local_18 (*(int *)(abi_storage + 8))
#define local_14 (*(uint32_t *)(abi_storage + 12))
#define local_10 (*(uint32_t(*)[2])(abi_storage + 16))

    local_10[0] = param_1;
    sango_soft_unpack_f32(local_10, &local_20);
    if (local_20 == 2)
    {
        return 0;
    }
    if (local_20 < 2)
    {
        return 0;
    }
    if (local_20 != 4)
    {
        if (local_18 < 0)
        {
            return 0;
        }
        if (local_18 < 0x1f)
        {
            local_14 = local_14 >> (0x1eU - local_18 & 0x1f);
            if (local_1c == 0)
            {
                return local_14;
            }
            return -local_14;
        }
    }
    return 0x80000000 - (local_1c == 0);
}
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10

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
uint64_t sango_soft_add_f64(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    unsigned char abi_storage[104] __attribute__((aligned(8)));
#define local_10 (*(uint32_t *)(abi_storage + 80))
#define local_c (*(uint32_t *)(abi_storage + 84))
#define auStack_48 (*(uint32_t(*)[6])(abi_storage + 24))
#define auStack_60 (*(uint32_t(*)[6])(abi_storage + 0))
#define auStack_30 (*(uint32_t(*)[6])(abi_storage + 48))
#define local_18 (*(uint32_t *)(abi_storage + 72))
#define local_14 (*(uint32_t *)(abi_storage + 76))

    uint32_t *puVar1;
    uint64_t uVar2;

    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    local_c = param_4;
    sango_soft_unpack_f64(&local_18, auStack_60);
    sango_soft_unpack_f64(&local_10, auStack_48);
    puVar1 = sango_soft_add_f64_parts(auStack_60, auStack_48, auStack_30);
    uVar2 = sango_soft_pack_f64(puVar1);
    return uVar2;
}
#undef local_10
#undef local_c
#undef auStack_48
#undef auStack_60
#undef auStack_30
#undef local_18
#undef local_14

/* 原函数 0x81c1ebd8 */
uint64_t sango_soft_sub_f64(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    unsigned char abi_storage[104] __attribute__((aligned(8)));
#define local_44 (*(uint32_t *)(abi_storage + 28))
#define local_18 (*(uint32_t *)(abi_storage + 72))
#define local_14 (*(uint32_t *)(abi_storage + 76))
#define auStack_60 (*(uint32_t(*)[6])(abi_storage + 0))
#define local_10 (*(uint32_t *)(abi_storage + 80))
#define local_c (*(uint32_t *)(abi_storage + 84))
#define uStack_48 (*(uint32_t *)(abi_storage + 24))
#define auStack_30 (*(uint32_t(*)[6])(abi_storage + 48))

    uint32_t *puVar1;
    uint64_t uVar2;

    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    local_c = param_4;
    sango_soft_unpack_f64(&local_18, auStack_60);
    sango_soft_unpack_f64(&local_10, &uStack_48);
    local_44 = local_44 ^ 1;
    puVar1 = sango_soft_add_f64_parts(auStack_60, &uStack_48, auStack_30);
    uVar2 = sango_soft_pack_f64(puVar1);
    return uVar2;
}
#undef local_44
#undef local_18
#undef local_14
#undef auStack_60
#undef local_10
#undef local_c
#undef uStack_48
#undef auStack_30

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
int sango_soft_compare_f64_nan_high(uint32_t param_1, uint32_t param_2, uint32_t param_3,
                                    uint32_t param_4)
{
    unsigned char abi_storage[80] __attribute__((aligned(8)));
#define local_48 (*(uint32_t(*)[6])(abi_storage + 0))
#define local_30 (*(uint32_t(*)[6])(abi_storage + 24))
#define local_18 (*(uint32_t *)(abi_storage + 48))
#define local_14 (*(uint32_t *)(abi_storage + 52))
#define local_10 (*(uint32_t *)(abi_storage + 56))
#define local_c (*(uint32_t *)(abi_storage + 60))

    int iVar1;

    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    local_c = param_4;
    sango_soft_unpack_f64(&local_18, local_48);
    sango_soft_unpack_f64(&local_10, local_30);
    iVar1 = 1;
    if ((1 < local_48[0]) && (1 < local_30[0]))
    {
        iVar1 = sango_soft_compare_f64_parts(local_48, local_30);
    }
    return iVar1;
}
#undef local_48
#undef local_30
#undef local_18
#undef local_14
#undef local_10
#undef local_c

/* 原函数 0x81c1f2a0 */
int sango_soft_compare_f64_nan_low(uint32_t param_1, uint32_t param_2, uint32_t param_3,
                                   uint32_t param_4)
{
    unsigned char abi_storage[80] __attribute__((aligned(8)));
#define local_14 (*(uint32_t *)(abi_storage + 52))
#define local_10 (*(uint32_t *)(abi_storage + 56))
#define local_c (*(uint32_t *)(abi_storage + 60))
#define local_48 (*(uint32_t(*)[6])(abi_storage + 0))
#define local_30 (*(uint32_t(*)[6])(abi_storage + 24))
#define local_18 (*(uint32_t *)(abi_storage + 48))

    int iVar1;

    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    local_c = param_4;
    sango_soft_unpack_f64(&local_18, local_48);
    sango_soft_unpack_f64(&local_10, local_30);
    iVar1 = -1;
    if ((1 < local_48[0]) && (1 < local_30[0]))
    {
        iVar1 = sango_soft_compare_f64_parts(local_48, local_30);
    }
    return iVar1;
}
#undef local_14
#undef local_10
#undef local_c
#undef local_48
#undef local_30
#undef local_18

/* 原函数 0x81c1f330 */
int sango_soft_compare_f64_nan_low_compat(uint32_t param_1, uint32_t param_2, uint32_t param_3,
                                          uint32_t param_4)
{
    unsigned char abi_storage[80] __attribute__((aligned(8)));
#define local_30 (*(uint32_t(*)[6])(abi_storage + 24))
#define local_18 (*(uint32_t *)(abi_storage + 48))
#define local_14 (*(uint32_t *)(abi_storage + 52))
#define local_10 (*(uint32_t *)(abi_storage + 56))
#define local_c (*(uint32_t *)(abi_storage + 60))
#define local_48 (*(uint32_t(*)[6])(abi_storage + 0))

    int iVar1;

    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    local_c = param_4;
    sango_soft_unpack_f64(&local_18, local_48);
    sango_soft_unpack_f64(&local_10, local_30);
    iVar1 = -1;
    if ((1 < local_48[0]) && (1 < local_30[0]))
    {
        iVar1 = sango_soft_compare_f64_parts(local_48, local_30);
    }
    return iVar1;
}
#undef local_30
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_48

/* 原函数 0x81c1f3c0 */
int sango_soft_compare_f64_nan_high_compat(uint32_t param_1, uint32_t param_2, uint32_t param_3,
                                           uint32_t param_4)
{
    unsigned char abi_storage[80] __attribute__((aligned(8)));
#define local_48 (*(uint32_t(*)[6])(abi_storage + 0))
#define local_30 (*(uint32_t(*)[6])(abi_storage + 24))
#define local_18 (*(uint32_t *)(abi_storage + 48))
#define local_14 (*(uint32_t *)(abi_storage + 52))
#define local_10 (*(uint32_t *)(abi_storage + 56))
#define local_c (*(uint32_t *)(abi_storage + 60))

    int iVar1;

    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    local_c = param_4;
    sango_soft_unpack_f64(&local_18, local_48);
    sango_soft_unpack_f64(&local_10, local_30);
    iVar1 = 1;
    if ((1 < local_48[0]) && (1 < local_30[0]))
    {
        iVar1 = sango_soft_compare_f64_parts(local_48, local_30);
    }
    return iVar1;
}
#undef local_48
#undef local_30
#undef local_18
#undef local_14
#undef local_10
#undef local_c

/* 原函数 0x81c1f450 */
uint64_t sango_soft_int_to_f64(uint32_t param_1)
{
    unsigned char abi_storage[40] __attribute__((aligned(8)));
#define local_20 (*(uint32_t *)(abi_storage + 0))
#define local_1c (*(int *)(abi_storage + 4))
#define local_18 (*(int *)(abi_storage + 8))
#define local_10 (*(uint32_t *)(abi_storage + 16))
#define local_c (*(uint32_t *)(abi_storage + 20))

    uint32_t uVar1;
    uint64_t uVar2;

    uVar1 = (int)param_1 >> 0x1f;
    local_1c = -uVar1;
    local_20 = 3;
    if (param_1 == 0)
    {
        local_20 = 2;
    }
    else
    {
        local_18 = 0x3c;
        if (local_1c != 0)
        {
            if (param_1 == 0x80000000)
            {
                return CONCAT44(g_legacy_data_81c20c84, g_legacy_data_81c20c80);
            }
            param_1 = -param_1;
            uVar1 = (int)param_1 >> 0x1f;
        }
        local_10 = param_1;
        local_c = uVar1;
        if (uVar1 < 0x10000000)
        {
            local_18 = 0x3c;
            do
            {
                local_c = local_c << 1 | local_10 >> 0x1f;
                local_10 = local_10 << 1;
                local_18 = local_18 + -1;
            } while (local_c < 0x10000000);
        }
    }
    uVar2 = sango_soft_pack_f64(&local_20);
    return uVar2;
}
#undef local_20
#undef local_1c
#undef local_18
#undef local_10
#undef local_c

/* 原函数 0x81c1f540 */
uint32_t sango_soft_f64_to_int(uint32_t param_1, uint32_t param_2)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define local_28 (*(uint32_t *)(abi_storage + 0))
#define local_24 (*(int *)(abi_storage + 4))
#define local_20 (*(int *)(abi_storage + 8))
#define local_18 (*(uint32_t *)(abi_storage + 16))
#define local_14 (*(uint32_t *)(abi_storage + 20))
#define local_10 (*(uint32_t *)(abi_storage + 24))
#define local_c (*(uint32_t *)(abi_storage + 28))

    uint32_t uVar1;

    local_10 = param_1;
    local_c = param_2;
    sango_soft_unpack_f64(&local_10, &local_28);
    if (local_28 == 2)
    {
        return 0;
    }
    if (local_28 < 2)
    {
        return 0;
    }
    if (local_28 != 4)
    {
        if (local_20 < 0)
        {
            return 0;
        }
        if (local_20 < 0x1f)
        {
            uVar1 = 0x3c - local_20;
            if ((int)(uVar1 * 0x4000000) < 0)
            {
                local_18 = local_14 >> (uVar1 & 0x1f);
            }
            else
            {
                local_18 = local_18 >> (uVar1 & 0x1f);
                if (uVar1 * 0x4000000 != 0)
                {
                    local_18 = local_18 | local_14 << (-uVar1 & 0x1f);
                }
            }
            if (local_24 == 0)
            {
                return local_18;
            }
            return -local_18;
        }
    }
    return 0x80000000 - (local_24 == 0);
}
#undef local_28
#undef local_24
#undef local_20
#undef local_18
#undef local_14
#undef local_10
#undef local_c

/* 原函数 0x81c1f620 */
uint32_t sango_soft_pack_f32(uint32_t *param_1)
{
    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;

    uVar1 = *param_1;
    uVar2 = param_1[3];
    uVar3 = 0;
    if (uVar1 < 2)
    {
        uVar2 = uVar2 | 0x100000;
        uVar3 = 0xff;
        goto LAB_81c1f648;
    }
    if (uVar1 == 4)
    {
    LAB_81c1f740:
        uVar3 = 0xff;
    }
    else if (uVar1 != 2)
    {
        if (uVar2 == 0)
            goto LAB_81c1f648;
        uVar1 = param_1[2];
        if ((int)uVar1 < -0x7e)
        {
            uVar1 = -uVar1 - 0x7e;
            if ((int)uVar1 < 0x1a)
            {
                uVar2 =
                    uVar2 >> (uVar1 & 0x1f) | (uint32_t)((uVar2 & (1 << (uVar1 & 0x1f)) - 1U) != 0);
            }
            else
            {
                uVar2 = 0;
            }
            if ((uVar2 & 0x7f) == 0x40)
            {
                if ((uVar2 & 0x80) != 0)
                {
                    uVar2 = uVar2 + 0x40;
                }
            }
            else
            {
                uVar2 = uVar2 + 0x3f;
            }
            if (0x3fffffff < uVar2)
            {
                uVar3 = 1;
            }
        }
        else
        {
            if (0x7f < (int)uVar1)
                goto LAB_81c1f740;
            uVar3 = uVar1 + 0x7f;
            if ((uVar2 & 0x7f) == 0x40)
            {
                if ((uVar2 & 0x80) != 0)
                {
                    uVar2 = uVar2 + 0x40;
                }
            }
            else
            {
                uVar2 = uVar2 + 0x3f;
            }
            if ((int)uVar2 < 0)
            {
                uVar2 = uVar2 >> 1;
                uVar3 = uVar1 + 0x80;
            }
        }
        uVar2 = uVar2 >> 7;
        goto LAB_81c1f648;
    }
    uVar2 = 0;
LAB_81c1f648:
    return uVar2 & 0x7fffff | (uVar3 & 0xff) << 0x17 | param_1[1] << 0x1f;
}

/* 原函数 0x81c1f790 */
void sango_soft_unpack_f32(uint32_t *param_1, uint32_t *param_2)
{
    uint32_t uVar1;
    uint32_t uVar2;
    int iVar3;
    uint32_t uVar4;
    uint32_t uVar5;

    uVar1 = *param_1;
    uVar4 = uVar1 >> 0x17 & 0xff;
    param_2[1] = uVar1 >> 0x1f;
    uVar5 = uVar1 & 0x7fffff;
    if (uVar4 == 0)
    {
        uVar2 = 2;
        if (uVar5 != 0)
        {
            uVar5 = uVar5 << 7;
            iVar3 = -0x7e;
            param_2[2] = 0xffffff82;
            *param_2 = 3;
            if (uVar5 < 0x40000000)
            {
                do
                {
                    uVar5 = uVar5 << 1;
                    iVar3 = iVar3 + -1;
                } while (uVar5 < 0x40000000);
                param_2[2] = iVar3;
            }
        LAB_81c1f7fc:
            param_2[3] = uVar5;
            return;
        }
    }
    else if (uVar4 == 0xff)
    {
        uVar2 = 4;
        if (uVar5 != 0)
        {
            if ((uVar1 & 0x100000) == 0)
            {
                *param_2 = 0;
            }
            else
            {
                *param_2 = 1;
            }
            goto LAB_81c1f7fc;
        }
    }
    else
    {
        param_2[3] = uVar5 << 7 | 0x40000000;
        uVar2 = 3;
        param_2[2] = uVar4 - 0x7f;
    }
    *param_2 = uVar2;
    return;
}

/* 原函数 0x81c1f860 */
int sango_soft_compare_f32_parts(uint32_t *param_1, uint32_t *param_2)
{
    int iVar1;
    uint32_t uVar2;
    uint32_t uVar3;

    uVar2 = *param_1;
    if (uVar2 < 2)
    {
        return 1;
    }
    uVar3 = *param_2;
    if (uVar3 < 2)
    {
        return 1;
    }
    if ((uVar2 == 4) && (uVar3 == 4))
    {
        return param_2[1] - param_1[1];
    }
    if (uVar2 == 4)
    {
    LAB_81c1f908:
        if (param_1[1] != 0)
        {
            return -1;
        }
        return 1;
    }
    if (uVar3 != 4)
    {
        if (uVar2 != 2)
        {
            if (uVar3 == 2)
                goto LAB_81c1f908;
            uVar2 = param_1[1];
            if (uVar2 == param_2[1])
            {
                if ((int)param_1[2] <= (int)param_2[2])
                {
                    if ((int)param_2[2] <= (int)param_1[2])
                    {
                        if (param_2[3] < param_1[3])
                            goto LAB_81c1f934;
                        if (param_2[3] <= param_1[3])
                        {
                            return 0;
                        }
                    }
                    if (uVar2 != 0)
                    {
                        return 1;
                    }
                    return -1;
                }
            }
        LAB_81c1f934:
            if (uVar2 != 0)
            {
                return -1;
            }
            return 1;
        }
        if (uVar3 == 2)
        {
            return 0;
        }
    }
    iVar1 = 1;
    if (param_2[1] == 0)
    {
        iVar1 = -1;
    }
    return iVar1;
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
void sango_soft_unpack_f64(uint32_t *param_1, uint32_t *param_2)
{
    uint32_t uVar1;
    uint32_t uVar2;
    int iVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;

    uVar1 = param_1[1];
    uVar4 = uVar1 >> 0x14 & 0x7ff;
    uVar5 = *param_1;
    uVar6 = uVar1 & 0xfffff;
    param_2[1] = uVar1 >> 0x1f;
    if (uVar4 == 0)
    {
        if (uVar5 != 0 || uVar6 != 0)
        {
            uVar6 = uVar6 << 8 | uVar5 >> 0x18;
            uVar5 = uVar5 << 8;
            param_2[2] = 0xfffffc02;
            *param_2 = 3;
            if (uVar6 < 0x10000000)
            {
                iVar3 = -0x3fe;
                do
                {
                    uVar6 = uVar6 << 1 | uVar5 >> 0x1f;
                    uVar5 = uVar5 << 1;
                    iVar3 = iVar3 + -1;
                } while (uVar6 < 0x10000000);
                param_2[2] = iVar3;
            }
        LAB_81c1fcdc:
            param_2[4] = uVar5;
            param_2[5] = uVar6;
            return;
        }
        uVar2 = 2;
    }
    else if (uVar4 == 0x7ff)
    {
        uVar2 = 4;
        if (uVar5 != 0 || uVar6 != 0)
        {
            if ((uVar1 & 0x80000) == 0)
            {
                *param_2 = 0;
            }
            else
            {
                *param_2 = 1;
            }
            goto LAB_81c1fcdc;
        }
    }
    else
    {
        param_2[4] = uVar5 << 8;
        param_2[5] = uVar6 << 8 | uVar5 >> 0x18 | 0x10000000;
        uVar2 = 3;
        param_2[2] = uVar4 - 0x3ff;
    }
    *param_2 = uVar2;
    return;
}

/* 原函数 0x81c1fd60 */
int sango_soft_compare_f64_parts(uint32_t *param_1, uint32_t *param_2)
{
    int iVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint32_t uVar4;

    uVar2 = *param_1;
    if (uVar2 < 2)
    {
        return 1;
    }
    uVar3 = *param_2;
    if (uVar3 < 2)
    {
        return 1;
    }
    if ((uVar2 == 4) && (uVar3 == 4))
    {
        return param_2[1] - param_1[1];
    }
    if (uVar2 == 4)
    {
    LAB_81c1fe08:
        if (param_1[1] != 0)
        {
            return -1;
        }
        return 1;
    }
    if (uVar3 != 4)
    {
        if (uVar2 != 2)
        {
            if (uVar3 == 2)
                goto LAB_81c1fe08;
            uVar2 = param_1[1];
            if (uVar2 == param_2[1])
            {
                if ((int)param_1[2] <= (int)param_2[2])
                {
                    if ((int)param_2[2] <= (int)param_1[2])
                    {
                        uVar4 = param_1[5];
                        uVar3 = param_2[5];
                        if ((uVar3 < uVar4) || ((uVar4 == uVar3 && (param_2[4] < param_1[4]))))
                            goto LAB_81c1fe34;
                        if (uVar3 <= uVar4)
                        {
                            if (uVar3 != uVar4)
                            {
                                return 0;
                            }
                            if (param_2[4] <= param_1[4])
                            {
                                return 0;
                            }
                        }
                    }
                    if (uVar2 != 0)
                    {
                        return 1;
                    }
                    return -1;
                }
            }
        LAB_81c1fe34:
            if (uVar2 != 0)
            {
                return -1;
            }
            return 1;
        }
        if (uVar3 == 2)
        {
            return 0;
        }
    }
    iVar1 = 1;
    if (param_2[1] == 0)
    {
        iVar1 = -1;
    }
    return iVar1;
}

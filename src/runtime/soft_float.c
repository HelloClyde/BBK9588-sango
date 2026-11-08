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
uint32_t *sango_soft_add_f32_parts(uint32_t *param_1, uint32_t *param_2, uint32_t *param_3)
{
    bool bVar1;
    int iVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t *puVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint32_t uVar8;

    uVar6 = *param_1;
    puVar5 = param_1;
    if ((1 < uVar6) && (uVar3 = *param_2, puVar5 = param_2, 1 < uVar3))
    {
        if (uVar6 == 4)
        {
            puVar5 = param_1;
            if (((uVar3 ^ 4) == 0) &&
                (puVar5 = (uint32_t *)&g_legacy_data_81c20c00, param_1[1] == param_2[1]))
            {
                puVar5 = param_1;
            }
        }
        else
        {
            puVar5 = param_2;
            if ((uVar3 ^ 4) != 0)
            {
                if (uVar3 == 2)
                {
                    puVar5 = param_1;
                    if ((uVar6 ^ 2) == 0)
                    {
                        *param_3 = uVar6;
                        param_3[1] = param_1[1];
                        param_3[2] = param_1[2];
                        param_3[3] = param_1[3];
                        param_3[1] = param_1[1] & param_2[1];
                        puVar5 = param_3;
                    }
                }
                else
                {
                    puVar5 = param_2;
                    if ((uVar6 ^ 2) != 0)
                    {
                        uVar7 = param_1[2];
                        uVar6 = param_2[2];
                        uVar3 = param_1[3];
                        iVar2 = uVar7 - uVar6;
                        if (iVar2 < 0)
                        {
                            iVar2 = -iVar2;
                        }
                        uVar8 = param_2[3];
                        if (iVar2 < 0x20)
                        {
                            bVar1 = (int)uVar7 < (int)uVar6;
                            uVar4 = uVar6;
                            if ((int)uVar7 > (int)uVar6)
                            {
                                iVar2 = uVar7 - uVar6;
                                do
                                {
                                    iVar2 = iVar2 + -1;
                                    uVar8 = uVar8 & 1 | uVar8 >> 1;
                                } while (iVar2 != 0);
                                bVar1 = false;
                                uVar4 = uVar7;
                            }
                            uVar6 = uVar7;
                            if (bVar1)
                            {
                                iVar2 = uVar4 - uVar7;
                                do
                                {
                                    iVar2 = iVar2 + -1;
                                    uVar3 = uVar3 & 1 | uVar3 >> 1;
                                    uVar6 = uVar4;
                                } while (iVar2 != 0);
                            }
                        }
                        else if ((int)uVar7 <= (int)uVar6)
                        {
                            uVar3 = 0;
                        }
                        else
                        {
                            uVar8 = 0;
                            uVar6 = uVar7;
                        }
                        uVar7 = param_1[1];
                        if (uVar7 == param_2[1])
                        {
                            uVar3 = uVar3 + uVar8;
                            param_3[1] = uVar7;
                            param_3[2] = uVar6;
                            param_3[3] = uVar3;
                        }
                        else
                        {
                            uVar4 = uVar8 - uVar3;
                            if (uVar7 == 0)
                            {
                                uVar4 = uVar3 - uVar8;
                            }
                            if ((int)uVar4 < 0)
                            {
                                param_3[1] = 1;
                                param_3[2] = uVar6;
                                param_3[3] = -uVar4;
                            }
                            else
                            {
                                param_3[2] = uVar6;
                                param_3[3] = uVar4;
                                param_3[1] = 0;
                            }
                            uVar3 = param_3[3];
                            if (uVar3 - 1 < 0x3fffffff)
                            {
                                uVar6 = param_3[2];
                                do
                                {
                                    uVar3 = uVar3 * 2;
                                    uVar6 = uVar6 - 1;
                                } while (uVar3 - 1 < 0x3fffffff);
                                param_3[2] = uVar6;
                                param_3[3] = uVar3;
                            }
                        }
                        *param_3 = 3;
                        puVar5 = param_3;
                        if ((int)uVar3 < 0)
                        {
                            param_3[3] = uVar3 & 1 | uVar3 >> 1;
                            param_3[2] = param_3[2] + 1;
                        }
                    }
                }
            }
        }
    }
    return puVar5;
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
#define local_40 (*(uint32_t *)(abi_storage + 0))
#define local_3c (*(uint32_t *)(abi_storage + 4))
#define local_38 (*(int *)(abi_storage + 8))
#define local_34 (*(uint32_t *)(abi_storage + 12))
#define local_30 (*(uint32_t *)(abi_storage + 16))
#define local_2c (*(uint32_t *)(abi_storage + 20))
#define local_28 (*(int *)(abi_storage + 24))
#define local_24 (*(uint32_t *)(abi_storage + 28))
#define local_20 (*(uint32_t *)(abi_storage + 32))
#define local_1c (*(uint32_t *)(abi_storage + 36))
#define local_18 (*(int *)(abi_storage + 40))
#define local_14 (*(uint32_t *)(abi_storage + 44))
#define local_10 (*(uint32_t *)(abi_storage + 48))
#define local_c (*(uint32_t *)(abi_storage + 52))

    uint64_t uVar1;
    uint32_t uVar2;
    uint32_t *puVar3;

    local_10 = left;
    local_c = right;
    sango_soft_unpack_f32(&local_10, &local_40);
    sango_soft_unpack_f32(&local_c, &local_30);
    puVar3 = &local_20;
    if (local_40 < 2)
    {
    LAB_81c1e33c:
        local_3c = (uint32_t)(local_3c != local_2c);
        puVar3 = &local_40;
    }
    else
    {
        if (1 < local_30)
        {
            if (local_40 == 4)
            {
                puVar3 = (uint32_t *)&g_legacy_data_81c20c00;
                if (local_30 == 2)
                    goto LAB_81c1e354;
                goto LAB_81c1e33c;
            }
            if (local_30 == 4)
            {
                puVar3 = (uint32_t *)&g_legacy_data_81c20c00;
                if ((local_40 ^ 2) == 0)
                    goto LAB_81c1e354;
            }
            else
            {
                if ((local_40 ^ 2) == 0)
                    goto LAB_81c1e33c;
                if (local_30 != 2)
                {
                    uVar1 = (uint64_t)local_34 * (uint64_t)local_24;
                    local_18 = local_38 + local_28 + 2;
                    local_1c = (uint32_t)(local_3c != local_2c);
                    if ((int64_t)uVar1 < 0)
                    {
                        uVar2 = (uint32_t)uVar1;
                        local_18 = local_38 + local_28 + 3;
                        if ((uVar1 & 0x100000000) != 0)
                        {
                            uVar2 = uVar2 >> 1 | 0x80000000;
                        }
                        uVar1 = CONCAT44((uint32_t)(uVar1 >> 0x21), uVar2);
                    }
                    if (uVar1 < 0x4000000000000000)
                    {
                        do
                        {
                            uVar2 = (int)(uVar1 >> 0x20) << 1;
                            local_18 = local_18 + -1;
                            if ((int)uVar1 < 0)
                            {
                                uVar2 = uVar2 | 1;
                            }
                            uVar1 = CONCAT44(uVar2, (int)uVar1 << 1);
                        } while (uVar2 < 0x40000000);
                    }
                    local_14 = (uint32_t)(uVar1 >> 0x20);
                    if (((local_14 & 0x7f) == 0x40) &&
                        (((uVar1 & 0x8000000000) != 0 || ((int)uVar1 != 0))))
                    {
                        local_14 = local_14 + 0x40;
                    }
                    local_20 = 3;
                    goto LAB_81c1e354;
                }
            }
        }
        local_2c = (uint32_t)(local_3c != local_2c);
        puVar3 = &local_30;
    }
LAB_81c1e354:
    uVar2 = sango_soft_pack_f32(puVar3);
    return uVar2;
}
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
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
uint32_t *sango_soft_add_f64_parts(uint32_t *param_1, uint32_t *param_2, uint32_t *param_3)
{
    bool bVar1;
    int iVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t *puVar7;
    uint32_t uVar8;
    uint32_t uVar9;
    uint32_t uVar10;
    uint32_t uVar11;

    uVar4 = *param_1;
    puVar7 = param_1;
    if ((1 < uVar4) && (uVar3 = *param_2, puVar7 = param_2, 1 < uVar3))
    {
        if (uVar4 == 4)
        {
            puVar7 = param_1;
            if (((uVar3 ^ 4) == 0) &&
                (puVar7 = (uint32_t *)&g_legacy_data_81c20c10, param_1[1] == param_2[1]))
            {
                puVar7 = param_1;
            }
        }
        else
        {
            puVar7 = param_2;
            if ((uVar3 ^ 4) != 0)
            {
                if (uVar3 == 2)
                {
                    puVar7 = param_1;
                    if ((uVar4 ^ 2) == 0)
                    {
                        *param_3 = uVar4;
                        param_3[1] = param_1[1];
                        param_3[2] = param_1[2];
                        param_3[3] = param_1[3];
                        param_3[4] = param_1[4];
                        param_3[5] = param_1[5];
                        param_3[1] = param_1[1] & param_2[1];
                        puVar7 = param_3;
                    }
                }
                else
                {
                    puVar7 = param_2;
                    if ((uVar4 ^ 2) != 0)
                    {
                        uVar11 = param_1[2];
                        uVar4 = param_2[2];
                        uVar10 = param_1[4];
                        uVar3 = param_1[5];
                        iVar2 = uVar11 - uVar4;
                        if (iVar2 < 0)
                        {
                            iVar2 = -iVar2;
                        }
                        uVar8 = param_2[4];
                        uVar9 = param_2[5];
                        if (iVar2 < 0x40)
                        {
                            bVar1 = (int)uVar11 < (int)uVar4;
                            uVar5 = uVar4;
                            if ((int)uVar11 > (int)uVar4)
                            {
                                iVar2 = uVar11 - uVar4;
                                do
                                {
                                    uVar4 = uVar9 << 0x1f;
                                    uVar9 = uVar9 >> 1;
                                    iVar2 = iVar2 + -1;
                                    uVar8 = uVar8 & 1 | uVar8 >> 1 | uVar4;
                                } while (iVar2 != 0);
                                bVar1 = false;
                                uVar5 = uVar11;
                            }
                            uVar4 = uVar11;
                            if (bVar1)
                            {
                                iVar2 = uVar5 - uVar11;
                                do
                                {
                                    uVar4 = uVar3 << 0x1f;
                                    uVar3 = uVar3 >> 1;
                                    iVar2 = iVar2 + -1;
                                    uVar10 = uVar10 & 1 | uVar10 >> 1 | uVar4;
                                    uVar4 = uVar5;
                                } while (iVar2 != 0);
                            }
                        }
                        else if ((int)uVar11 <= (int)uVar4)
                        {
                            uVar10 = 0;
                            uVar3 = 0;
                        }
                        else
                        {
                            uVar8 = 0;
                            uVar9 = 0;
                            uVar4 = uVar11;
                        }
                        uVar11 = param_1[1];
                        if (uVar11 == param_2[1])
                        {
                            param_3[1] = uVar11;
                            param_3[2] = uVar4;
                            param_3[4] = uVar10 + uVar8;
                            param_3[5] = uVar3 + uVar9 + (uint32_t)(uVar10 + uVar8 < uVar8);
                        }
                        else
                        {
                            uVar5 = uVar8 - uVar10;
                            uVar6 = (uVar9 - uVar3) - (uint32_t)(uVar8 < uVar10);
                            if (uVar11 == 0)
                            {
                                uVar5 = uVar10 - uVar8;
                                uVar6 = (uVar3 - uVar9) - (uint32_t)(uVar10 < uVar8);
                            }
                            if ((int)uVar6 < 0)
                            {
                                param_3[1] = 1;
                                param_3[2] = uVar4;
                                param_3[4] = -uVar5;
                                param_3[5] = -(uint32_t)(-uVar5 != 0) - uVar6;
                            }
                            else
                            {
                                param_3[2] = uVar4;
                                param_3[4] = uVar5;
                                param_3[5] = uVar6;
                                param_3[1] = 0;
                            }
                            uVar4 = param_3[4];
                            uVar3 = param_3[5];
                            uVar10 = (uVar3 - 1) + (uint32_t)(uVar4 != 0);
                            while ((uVar10 < 0x10000000 && ((uVar10 != 0xfffffff || (uVar4 != 0)))))
                            {
                                uVar3 = uVar3 << 1 | uVar4 >> 0x1f;
                                uVar4 = uVar4 * 2;
                                uVar10 = (uVar3 - 1) + (uint32_t)(uVar4 != 0);
                                param_3[2] = param_3[2] - 1;
                                param_3[4] = uVar4;
                                param_3[5] = uVar3;
                            }
                        }
                        *param_3 = 3;
                        puVar7 = param_3;
                        if (0x1fffffff < param_3[5])
                        {
                            param_3[4] = param_3[4] & 1 | param_3[4] >> 1 | param_3[5] << 0x1f;
                            param_3[5] = param_3[5] >> 1;
                            param_3[2] = param_3[2] + 1;
                        }
                    }
                }
            }
        }
    }
    return puVar7;
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
uint64_t sango_soft_mul_f64(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    unsigned char abi_storage[104] __attribute__((aligned(8)));
#define local_70 (*(uint32_t *)(abi_storage + 0))
#define local_6c (*(uint32_t *)(abi_storage + 4))
#define local_68 (*(int *)(abi_storage + 8))
#define local_60 (*(uint32_t *)(abi_storage + 16))
#define local_5c (*(uint32_t *)(abi_storage + 20))
#define local_58 (*(uint32_t *)(abi_storage + 24))
#define local_54 (*(uint32_t *)(abi_storage + 28))
#define local_50 (*(int *)(abi_storage + 32))
#define local_48 (*(uint32_t *)(abi_storage + 40))
#define local_44 (*(uint32_t *)(abi_storage + 44))
#define local_40 (*(uint32_t *)(abi_storage + 48))
#define local_3c (*(uint32_t *)(abi_storage + 52))
#define local_38 (*(int *)(abi_storage + 56))
#define local_30 (*(uint64_t *)(abi_storage + 64))
#define local_28 (*(uint32_t *)(abi_storage + 72))
#define local_24 (*(uint32_t *)(abi_storage + 76))
#define local_20 (*(uint32_t *)(abi_storage + 80))
#define local_1c (*(uint32_t *)(abi_storage + 84))

    int64_t lVar1;
    int64_t lVar2;
    uint64_t uVar3;
    uint64_t uVar4;
    uint32_t *puVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint32_t uVar8;
    uint32_t uVar9;
    uint32_t uVar10;
    uint32_t uVar11;
    uint64_t uVar12;

    local_28 = param_1;
    local_24 = param_2;
    local_20 = param_3;
    local_1c = param_4;
    sango_soft_unpack_f64(&local_28, &local_70);
    sango_soft_unpack_f64(&local_20, &local_58);
    puVar5 = &local_40;
    if (local_70 < 2)
    {
    LAB_81c1ece4:
        local_6c = (uint32_t)(local_6c != local_54);
        puVar5 = &local_70;
    }
    else
    {
        if (1 < local_58)
        {
            if (local_70 == 4)
            {
                puVar5 = (uint32_t *)&g_legacy_data_81c20c10;
                if (local_58 == 2)
                    goto LAB_81c1ecfc;
                goto LAB_81c1ece4;
            }
            if (local_58 == 4)
            {
                puVar5 = (uint32_t *)&g_legacy_data_81c20c10;
                if ((local_70 ^ 2) == 0)
                    goto LAB_81c1ecfc;
            }
            else
            {
                if ((local_70 ^ 2) == 0)
                    goto LAB_81c1ece4;
                if (local_58 != 2)
                {
                    uVar8 = 0;
                    lVar1 = (uint64_t)local_44 * (uint64_t)local_60;
                    uVar10 = (uint32_t)((uint64_t)lVar1 >> 0x20);
                    lVar2 = (uint64_t)local_48 * (uint64_t)local_5c + lVar1;
                    uVar6 = (uint32_t)lVar2;
                    uVar7 = (uint32_t)((uint64_t)lVar2 >> 0x20);
                    uVar9 = (uint32_t)((uint64_t)local_48 * (uint64_t)local_60);
                    uVar11 = (uint32_t)((uint64_t)local_48 * (uint64_t)local_60 >> 0x20);
                    if ((uVar7 < uVar10) || ((uVar10 == uVar7 && (uVar6 < (uint32_t)lVar1))))
                    {
                        uVar8 = 1;
                    }
                    uVar6 = uVar11 + uVar6;
                    local_30 = (uint64_t)local_44 * (uint64_t)local_5c + CONCAT44(uVar8, uVar7) +
                               (uint64_t)(uVar6 < uVar11);
                    local_3c = (uint32_t)(local_6c != local_54);
                    local_38 = local_68 + local_50 + 4;
                    uVar3 = local_30;
                    if (0x1fffffffffffffff < local_30)
                    {
                        do
                        {
                            uVar3 = local_30 & 1;
                            uVar4 = local_30 >> 0x21;
                            local_38 = local_38 + 1;
                            local_30 = local_30 >> 1;
                            if (uVar3 != 0)
                            {
                                uVar9 = uVar9 >> 1 | uVar6 << 0x1f;
                                uVar6 = uVar6 >> 1 | 0x80000000;
                            }
                            uVar3 = local_30;
                        } while (0x1fffffff < (uint32_t)uVar4);
                    }
                    while (uVar3 < 0x1000000000000000)
                    {
                        local_38 = local_38 + -1;
                        uVar3 = local_30 << 1;
                        uVar7 = (uint32_t)uVar3;
                        if ((int)uVar6 < 0)
                        {
                            uVar7 = uVar7 | 1;
                        }
                        local_30 = CONCAT44((int)(uVar3 >> 0x20), uVar7);
                        uVar6 = uVar6 << 1 | uVar9 >> 0x1f;
                        uVar9 = uVar9 << 1;
                    }
                    if ((((uint32_t)local_30 & 0xff) == 0x80) &&
                        (((local_30 & 0x100) != 0 || (uVar9 != 0 || uVar6 != 0))))
                    {
                        local_30 = local_30 + 0x80;
                    }
                    local_40 = 3;
                    goto LAB_81c1ecfc;
                }
            }
        }
        local_54 = (uint32_t)(local_6c != local_54);
        puVar5 = &local_58;
    }
LAB_81c1ecfc:
    uVar12 = sango_soft_pack_f64(puVar5);
    return uVar12;
}
#undef local_70
#undef local_6c
#undef local_68
#undef local_60
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_30
#undef local_28
#undef local_24
#undef local_20
#undef local_1c

/* 原函数 0x81c1efe0 */
uint64_t sango_soft_div_f64(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    unsigned char abi_storage[80] __attribute__((aligned(8)));
#define local_48 (*(uint32_t *)(abi_storage + 0))
#define local_44 (*(uint32_t *)(abi_storage + 4))
#define local_40 (*(int *)(abi_storage + 8))
#define local_38 (*(uint32_t *)(abi_storage + 16))
#define local_34 (*(uint32_t *)(abi_storage + 20))
#define local_30 (*(uint32_t *)(abi_storage + 24))
#define local_2c (*(uint32_t *)(abi_storage + 28))
#define local_28 (*(int *)(abi_storage + 32))
#define local_20 (*(uint32_t *)(abi_storage + 40))
#define local_1c (*(uint32_t *)(abi_storage + 44))
#define local_18 (*(uint32_t *)(abi_storage + 48))
#define local_14 (*(uint32_t *)(abi_storage + 52))
#define local_10 (*(uint32_t *)(abi_storage + 56))
#define local_c (*(uint32_t *)(abi_storage + 60))

    bool bVar1;
    uint32_t *puVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint64_t uVar7;

    local_18 = param_1;
    local_14 = param_2;
    local_10 = param_3;
    local_c = param_4;
    sango_soft_unpack_f64(&local_18, &local_48);
    sango_soft_unpack_f64(&local_10, &local_30);
    puVar2 = &local_48;
    uVar3 = local_38;
    uVar6 = local_34;
    if ((1 < local_48) && (puVar2 = &local_30, 1 < local_30))
    {
        local_44 = local_44 ^ local_2c;
        if ((local_48 == 4) || (local_48 == 2))
        {
            puVar2 = (uint32_t *)&g_legacy_data_81c20c10;
            if (local_48 != local_30)
            {
                puVar2 = &local_48;
            }
        }
        else if (local_30 == 4)
        {
            local_38 = 0;
            local_34 = 0;
            local_40 = 0;
            puVar2 = &local_48;
            uVar3 = local_38;
            uVar6 = local_34;
        }
        else if (local_30 == 2)
        {
            local_48 = 4;
            puVar2 = &local_48;
        }
        else
        {
            bVar1 = local_34 < local_1c;
            local_40 = local_40 - local_28;
            if ((bVar1) || ((local_1c == local_34 && (local_38 < local_20))))
            {
                local_40 = local_40 + -1;
                local_34 = local_34 << 1 | local_38 >> 0x1f;
                local_38 = local_38 << 1;
                bVar1 = local_34 < local_1c;
            }
            uVar4 = 0x10000000;
            uVar3 = 0;
            uVar5 = 0;
            uVar6 = 0;
            do
            {
                if ((!bVar1) && ((local_1c != local_34 || (local_20 <= local_38))))
                {
                    bVar1 = local_38 < local_20;
                    local_38 = local_38 - local_20;
                    local_34 = (local_34 - local_1c) - (uint32_t)bVar1;
                    uVar5 = uVar5 | uVar3;
                    uVar6 = uVar6 | uVar4;
                }
                uVar3 = uVar3 >> 1 | uVar4 << 0x1f;
                uVar4 = uVar4 >> 1;
                local_34 = local_34 << 1 | local_38 >> 0x1f;
                local_38 = local_38 << 1;
                bVar1 = local_34 < local_1c;
            } while (uVar3 != 0 || uVar4 != 0);
            puVar2 = &local_48;
            uVar3 = uVar5;
            if (((uVar5 & 0xff) == 0x80) &&
                (((uVar5 & 0x100) != 0 || (local_38 != 0 || local_34 != 0))))
            {
                uVar3 = uVar5 + 0x80;
                uVar6 = uVar6 + (uVar5 + 0x80 < 0x80);
            }
        }
    }
    local_34 = uVar6;
    local_38 = uVar3;
    uVar7 = sango_soft_pack_f64(puVar2);
    return uVar7;
}
#undef local_48
#undef local_44
#undef local_40
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c

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
uint64_t sango_soft_pack_f64(uint32_t *param_1)
{
    bool bVar1;
    uint32_t uVar2;
    int iVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint32_t uVar8;

    uVar4 = *param_1;
    uVar6 = param_1[4];
    uVar7 = param_1[5];
    uVar8 = 0;
    if (uVar4 < 2)
    {
        uVar7 = uVar7 | 0x80000;
        uVar8 = 0x7ff;
        goto LAB_81c1f9d4;
    }
    if (uVar4 == 4)
    {
    LAB_81c1fba8:
        uVar8 = 0x7ff;
    }
    else if (uVar4 != 2)
    {
        if (uVar6 == 0 && uVar7 == 0)
            goto LAB_81c1f9d4;
        uVar4 = param_1[2];
        if ((int)uVar4 < -0x3fe)
        {
            uVar4 = -uVar4 - 0x3fe;
            if ((int)uVar4 < 0x39)
            {
                if ((int)(uVar4 * 0x4000000) < 0)
                {
                    uVar2 = 1 << (uVar4 & 0x1f);
                    iVar3 = 0;
                }
                else
                {
                    uVar2 = 0 << (uVar4 & 0x1f);
                    if (uVar4 * 0x4000000 != 0)
                    {
                        uVar2 = uVar2 | 1U >> (-uVar4 & 0x1f);
                    }
                    iVar3 = 1 << (uVar4 & 0x1f);
                }
                uVar2 = uVar7 & (uVar2 - 1) + (uint32_t)(iVar3 - 1U != 0xffffffff);
                if ((int)(uVar4 * 0x4000000) < 0)
                {
                    uVar5 = uVar7 >> (uVar4 & 0x1f);
                    uVar7 = 0;
                }
                else
                {
                    uVar5 = uVar6 >> (uVar4 & 0x1f);
                    if (uVar4 * 0x4000000 != 0)
                    {
                        uVar5 = uVar5 | uVar7 << (-uVar4 & 0x1f);
                    }
                    uVar7 = uVar7 >> (uVar4 & 0x1f);
                }
                uVar6 = uVar5 | ((uVar6 & iVar3 - 1U) != 0 || uVar2 != 0);
            }
            else
            {
                uVar6 = 0;
                uVar7 = 0;
            }
            if ((uVar6 & 0xff) == 0x80)
            {
                if ((uVar6 & 0x100) != 0)
                {
                    uVar6 = uVar6 + 0x80;
                    bVar1 = uVar6 < 0x80;
                    goto LAB_81c1faa0;
                }
            }
            else
            {
                uVar6 = uVar6 + 0x7f;
                bVar1 = uVar6 < 0x7f;
            LAB_81c1faa0:
                uVar7 = uVar7 + bVar1;
            }
            uVar2 = uVar7 << 0x18;
            if (0xfffffff < uVar7)
            {
                uVar8 = 1;
            LAB_81c1fabc:
                uVar2 = uVar7 << 0x18;
            }
        }
        else
        {
            if (0x3ff < (int)uVar4)
                goto LAB_81c1fba8;
            uVar8 = uVar4 + 0x3ff;
            if ((uVar6 & 0xff) == 0x80)
            {
                if ((uVar6 & 0x100) != 0)
                {
                    uVar6 = uVar6 + 0x80;
                    bVar1 = uVar6 < 0x80;
                    goto LAB_81c1fbdc;
                }
            }
            else
            {
                uVar6 = uVar6 + 0x7f;
                bVar1 = uVar6 < 0x7f;
            LAB_81c1fbdc:
                uVar7 = uVar7 + bVar1;
            }
            uVar2 = uVar7 << 0x18;
            if (0x1fffffff < uVar7)
            {
                uVar6 = uVar6 >> 1 | uVar7 << 0x1f;
                uVar7 = uVar7 >> 1;
                uVar8 = uVar4 + 0x400;
                goto LAB_81c1fabc;
            }
        }
        uVar6 = uVar6 >> 8 | uVar2;
        uVar7 = uVar7 >> 8;
        goto LAB_81c1f9d4;
    }
    uVar6 = 0;
    uVar7 = 0;
LAB_81c1f9d4:
    return CONCAT44(uVar7 & 0xfffff | (uVar8 & 0x7ff) << 0x14 | param_1[1] << 0x1f, uVar6);
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

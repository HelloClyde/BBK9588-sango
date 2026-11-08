#include "sango_internal.h"

/* 恢复的数值格式化和浮点文本转换。 */

/* 原函数 0x81c1c48c */
void sango_crt_append_character(uint8_t param_1, int *param_2)
{
    uint8_t *puVar1;

    puVar1 = (uint8_t *)*param_2;
    *puVar1 = param_1;
    *param_2 = (int)(puVar1 + 1);
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
int sango_crt_read_buffer(uint32_t param_1, uint8_t *param_2, int param_3)
{
    int iVar1;

    iVar1 = 0;
    while ((param_3 != 0 && (g_legacy_data_81c2b1f4 != '\x01')))
    {
        if (g_legacy_data_81c2b9e0 == '\0')
        {
            g_legacy_data_81c2b1f4 = '\x01';
            g_legacy_data_81c2b1f0 = 1;
        }
        else
        {
            g_legacy_data_81c2b9e0 = g_legacy_data_81c2b9e0 + -1;
            param_3 = param_3 + -1;
            iVar1 = iVar1 + 1;
            *param_2 = (&g_legacy_data_81c2b9e0)[g_legacy_data_81c2b1f0];
            g_legacy_data_81c2b1f0 = g_legacy_data_81c2b1f0 + 1;
            param_2 = param_2 + 1;
        }
    }
    return iVar1;
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
int sango_crt_isdigit(char param_1)
{
    int iVar1;

    iVar1 = (int)param_1;
    if (9 < iVar1 - 0x30U)
    {
        iVar1 = 0;
    }
    return iVar1;
}

/* 原函数 0x81c1c620 */
int sango_crt_isspace(char param_1)
{
    int iVar1;
    int iVar2;

    iVar2 = (int)param_1;
    iVar1 = iVar2;
    if ((4 < iVar2 - 9U) && (iVar1 = 0, iVar2 == 0x20))
    {
        iVar1 = iVar2;
    }
    return iVar1;
}

/* 原函数 0x81c1c650 */
int sango_crt_toupper(char param_1)
{
    int iVar1;
    int iVar2;

    iVar2 = (int)param_1;
    iVar1 = iVar2 + -0x20;
    if (0x19 < iVar2 - 0x61U)
    {
        iVar1 = iVar2;
    }
    return iVar1;
}

/* 原函数 0x81c1c670 */
int sango_crt_format_integer_entry(uint8_t *param_1, uint8_t *param_2, int param_3,
                                   uint32_t param_4)
{
    unsigned char abi_storage[24] __attribute__((aligned(8)));
#define local_resc (*(uint32_t *)(abi_storage + 4))
#define local_res8 (*(int *)(abi_storage + 0))

    int iVar1;

    local_res8 = param_3;
    local_resc = param_4;
    iVar1 = sango_crt_format_integer_words(0x4d, param_1, param_2, &local_res8);
    if (iVar1 < 0)
    {
        *param_1 = 0;
    }
    else
    {
        param_1[iVar1] = 0;
    }
    return iVar1;
}
#undef local_resc
#undef local_res8

/* 原函数 0x81c1c6d0 */
int sango_crt_format_integer_words(int param_1, void *param_2, uint8_t *param_3, int *param_4)
{
    unsigned char abi_storage[120] __attribute__((aligned(8)));
#define local_90 (*(int **)(abi_storage + 0))
#define local_8c (*(uint32_t *)(abi_storage + 4))
#define local_88 (*(int *)(abi_storage + 8))
#define local_84 (*(uint32_t *)(abi_storage + 12))
#define local_80 (*(uint32_t *)(abi_storage + 16))
#define local_7c (*(uint32_t *)(abi_storage + 20))
#define local_78 (*(int *)(abi_storage + 24))
#define local_74 (*(int *)(abi_storage + 28))
#define local_70 (*(void **)(abi_storage + 32))
#define local_6c (*(uint32_t *)(abi_storage + 36))
#define local_68 (*(uint32_t *)(abi_storage + 40))
#define local_64 (*(uint32_t *)(abi_storage + 44))
#define local_60 (*(uint32_t *)(abi_storage + 48))
#define local_5c (*(uint32_t *)(abi_storage + 52))
#define local_58 (*(uint32_t *)(abi_storage + 56))
#define local_54 (*(uint32_t *)(abi_storage + 60))
#define local_50 (*(uint32_t *)(abi_storage + 64))
#define acStack_48 (*(char(*)[32])(abi_storage + 72))

    uint8_t bVar1;
    uint32_t uVar2;
    int *piVar3;
    int iVar4;
    uint8_t *pbVar5;
    uint8_t *pbVar6;
    void *dst;
    uint32_t uVar7;
    int iVar8;

    iVar8 = 0;
    dst = param_2;
    local_90 = param_4;
    if (param_3 != (uint8_t *)0x0)
    {
        do
        {
            uVar7 = 0;
            bVar1 = *param_3;
            pbVar5 = param_3;
            while ((bVar1 != 0x25 && (bVar1 != 0)))
            {
                pbVar5 = pbVar5 + 1;
                uVar7 = uVar7 + 1;
                bVar1 = *pbVar5;
            }
            uVar2 = 0x53;
            if (param_1 == 0x53)
            {
                crt_diagnostic_noop(*(uint32_t *)((int)param_2 + 4), param_3, uVar7);
                if (uVar2 != uVar7)
                {
                    return -1;
                }
            }
            else
            {
                crt_memcpy(dst, param_3, uVar7);
                dst = (void *)((int)dst + uVar7);
            }
            iVar8 = iVar8 + uVar7;
            if (*pbVar5 != 0x25)
            {
                return iVar8;
            }
            local_8c = 0x4c;
            local_88 = 0x4c;
            local_84 = 0x4c;
            local_80 = 0x4c;
            iVar4 = 0x4c;
            do
            {
                pbVar6 = pbVar5;
                pbVar5 = pbVar6 + 1;
                switch (*pbVar5)
                {
                case 0x20:
                    if (local_88 == 0x4c)
                    {
                        local_88 = 0x20;
                    }
                    break;
                default:
                    iVar4 = 0x48;
                    break;
                case 0x23:
                    local_80 = 0x48;
                    break;
                case 0x2b:
                    local_88 = 0x2b;
                    break;
                case 0x2d:
                    local_8c = 0x48;
                    break;
                case 0x30:
                    local_84 = 0x48;
                }
            } while (iVar4 == 0x4c);
            if (*pbVar5 == 0x2a)
            {
                piVar3 = (int *)((int)local_90 + 3U & 0xfffffffc);
                local_90 = piVar3 + 1;
                local_78 = *piVar3;
                if (local_78 < 0)
                {
                    local_8c = 0x48;
                    local_78 = -local_78;
                }
                pbVar5 = pbVar6 + 2;
                bVar1 = *pbVar5;
            }
            else
            {
                local_78 = 0;
                while (iVar4 = sango_crt_isdigit(*pbVar5), iVar4 != 0)
                {
                    local_78 = local_78 * 10 + (uint32_t)*pbVar5 + -0x30;
                    pbVar5 = pbVar5 + 1;
                }
                bVar1 = *pbVar5;
            }
            if (bVar1 == 0x2e)
            {
                pbVar6 = pbVar5 + 1;
                if (*pbVar6 == 0x2a)
                {
                    piVar3 = (int *)((int)local_90 + 3U & 0xfffffffc);
                    local_90 = piVar3 + 1;
                    local_74 = *piVar3;
                    pbVar6 = pbVar5 + 2;
                    goto LAB_81c1c938;
                }
                local_74 = 0;
                while (iVar4 = sango_crt_isdigit(*pbVar6), iVar4 != 0)
                {
                    local_74 = local_74 * 10 + (uint32_t)*pbVar6 + -0x30;
                    pbVar6 = pbVar6 + 1;
                }
                bVar1 = *pbVar6;
            }
            else
            {
                local_74 = -1;
                pbVar6 = pbVar5;
            LAB_81c1c938:
                bVar1 = *pbVar6;
            }
            local_7c = (uint32_t)bVar1;
            if ((local_7c == 0x68) || (local_7c = (uint32_t)*pbVar6, local_7c == 0x6c))
            {
                pbVar6 = pbVar6 + 1;
            }
            else
            {
                local_7c = 0x4c;
            }
            param_3 = (uint8_t *)sango_crt_format_float_field((int *)&local_90, (char *)pbVar6,
                                                              acStack_48);
            for (uVar7 = local_6c; 0x14 < (int)uVar7; uVar7 = uVar7 - 0x14)
            {
                iVar4 = 0x53;
                if (param_1 == 0x53)
                {
                    crt_diagnostic_noop(*(uint32_t *)((int)param_2 + 4), g_legacy_data_81c20990,
                                        0x14);
                    if (iVar4 != 0x14)
                    {
                        return -1;
                    }
                }
                else
                {
                    crt_memcpy(dst, g_legacy_data_81c20990, 0x14);
                    dst = (void *)((int)dst + 0x14);
                }
                iVar8 = iVar8 + 0x14;
            }
            uVar2 = 0x53;
            if (param_1 == 0x53)
            {
                crt_diagnostic_noop(*(uint32_t *)((int)param_2 + 4), g_legacy_data_81c20990, uVar7);
                if (uVar2 != uVar7)
                {
                    return -1;
                }
            }
            else
            {
                crt_memcpy(dst, g_legacy_data_81c20990, uVar7);
                dst = (void *)((int)dst + uVar7);
            }
            uVar2 = 0x53;
            if (param_1 == 0x53)
            {
                crt_diagnostic_noop(*(uint32_t *)((int)param_2 + 4), acStack_48, local_58);
                if (uVar2 != local_58)
                {
                    return -1;
                }
            }
            else
            {
                crt_memcpy(dst, acStack_48, local_58);
                dst = (void *)((int)dst + local_58);
            }
            iVar8 = iVar8 + uVar7 + local_58;
            for (uVar7 = local_68; 0x14 < (int)uVar7; uVar7 = uVar7 - 0x14)
            {
                iVar4 = 0x53;
                if (param_1 == 0x53)
                {
                    crt_diagnostic_noop(*(uint32_t *)((int)param_2 + 4), g_legacy_data_81c209a8,
                                        0x14);
                    if (iVar4 != 0x14)
                    {
                        return -1;
                    }
                }
                else
                {
                    crt_memcpy(dst, g_legacy_data_81c209a8, 0x14);
                    dst = (void *)((int)dst + 0x14);
                }
                iVar8 = iVar8 + 0x14;
            }
            uVar2 = 0x53;
            if (param_1 == 0x53)
            {
                crt_diagnostic_noop(*(uint32_t *)((int)param_2 + 4), g_legacy_data_81c209a8, uVar7);
                if (uVar2 != uVar7)
                {
                    return -1;
                }
            }
            else
            {
                crt_memcpy(dst, g_legacy_data_81c209a8, uVar7);
                dst = (void *)((int)dst + uVar7);
            }
            uVar2 = 0x53;
            if (param_1 == 0x53)
            {
                crt_diagnostic_noop(*(uint32_t *)((int)param_2 + 4), local_70, local_54);
                if (uVar2 != local_54)
                {
                    return -1;
                }
            }
            else
            {
                crt_memcpy(dst, local_70, local_54);
                dst = (void *)((int)dst + local_54);
            }
            iVar8 = iVar8 + uVar7 + local_54;
            for (uVar7 = local_64; 0x14 < (int)uVar7; uVar7 = uVar7 - 0x14)
            {
                iVar4 = 0x53;
                if (param_1 == 0x53)
                {
                    crt_diagnostic_noop(*(uint32_t *)((int)param_2 + 4), g_legacy_data_81c209a8,
                                        0x14);
                    if (iVar4 != 0x14)
                    {
                        return -1;
                    }
                }
                else
                {
                    crt_memcpy(dst, g_legacy_data_81c209a8, 0x14);
                    dst = (void *)((int)dst + 0x14);
                }
                iVar8 = iVar8 + 0x14;
            }
            uVar2 = 0x53;
            if (param_1 == 0x53)
            {
                crt_diagnostic_noop(*(uint32_t *)((int)param_2 + 4), g_legacy_data_81c209a8, uVar7);
                if (uVar2 != uVar7)
                {
                    return -1;
                }
            }
            else
            {
                crt_memcpy(dst, g_legacy_data_81c209a8, uVar7);
                dst = (void *)((int)dst + uVar7);
            }
            if (param_1 == 0x53)
            {
                uVar2 = local_54;
                crt_diagnostic_noop(*(uint32_t *)((int)param_2 + 4), (int)local_70 + local_54,
                                    local_50);
                if (uVar2 != local_50)
                {
                    return -1;
                }
            }
            else
            {
                crt_memcpy(dst, (void *)((int)local_70 + local_54), local_50);
                dst = (void *)((int)dst + local_50);
            }
            iVar8 = iVar8 + uVar7 + local_50;
            for (uVar7 = local_60; 0x14 < (int)uVar7; uVar7 = uVar7 - 0x14)
            {
                iVar4 = 0x53;
                if (param_1 == 0x53)
                {
                    crt_diagnostic_noop(*(uint32_t *)((int)param_2 + 4), g_legacy_data_81c209a8,
                                        0x14);
                    if (iVar4 != 0x14)
                    {
                        return -1;
                    }
                }
                else
                {
                    crt_memcpy(dst, g_legacy_data_81c209a8, 0x14);
                    dst = (void *)((int)dst + 0x14);
                }
                iVar8 = iVar8 + 0x14;
            }
            uVar2 = 0x53;
            if (param_1 == 0x53)
            {
                crt_diagnostic_noop(*(uint32_t *)((int)param_2 + 4), g_legacy_data_81c209a8, uVar7);
                if (uVar2 != uVar7)
                {
                    return -1;
                }
            }
            else
            {
                crt_memcpy(dst, g_legacy_data_81c209a8, uVar7);
                dst = (void *)((int)dst + uVar7);
            }
            iVar8 = iVar8 + uVar7;
            for (uVar7 = local_5c; 0x14 < (int)uVar7; uVar7 = uVar7 - 0x14)
            {
                iVar4 = 0x53;
                if (param_1 == 0x53)
                {
                    crt_diagnostic_noop(*(uint32_t *)((int)param_2 + 4), g_legacy_data_81c20990,
                                        0x14);
                    if (iVar4 != 0x14)
                    {
                        return -1;
                    }
                }
                else
                {
                    crt_memcpy(dst, g_legacy_data_81c20990, 0x14);
                    dst = (void *)((int)dst + 0x14);
                }
                iVar8 = iVar8 + 0x14;
            }
            uVar2 = 0x53;
            if (param_1 == 0x53)
            {
                crt_diagnostic_noop(*(uint32_t *)((int)param_2 + 4), g_legacy_data_81c20990, uVar7);
                if (uVar2 != uVar7)
                {
                    return -1;
                }
            }
            else
            {
                crt_memcpy(dst, g_legacy_data_81c20990, uVar7);
                dst = (void *)((int)dst + uVar7);
            }
            iVar8 = iVar8 + uVar7;
        } while (param_3 != (uint8_t *)0x0);
    }
    return iVar8;
}
#undef local_90
#undef local_8c
#undef local_88
#undef local_84
#undef local_80
#undef local_7c
#undef local_78
#undef local_74
#undef local_70
#undef local_6c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef acStack_48

/* 原函数 0x81c1ce34 */
char *sango_crt_format_float_field(int *param_1, char *param_2, char *param_3)
{
    SangoLegacyCode *pcVar1;
    uint32_t *puVar2;
    uint32_t *puVar3;
    int iVar4;
    int iVar5;
    char *pcVar6;
    uint32_t uVar7;
    uint32_t uVar8;

    param_1[9] = 0;
    param_1[0xe] = 0;
    param_1[10] = 0;
    param_1[0xf] = 0;
    param_1[0xb] = 0;
    param_1[0x10] = 0;
    param_1[0xc] = 0;
    param_1[0xd] = 0;
    switch (*param_2)
    {
    case '%':
        *param_3 = '%';
        param_1[8] = (int)(param_3 + 1);
        param_1[0xe] = 1;
        break;
    default:
        *param_3 = *param_2;
        param_1[0xe] = 1;
        param_1[6] = 0;
        break;
    case 'E':
    case 'G':
    case 'e':
    case 'f':
    case 'g':
        puVar3 = (uint32_t *)(*param_1 + 7U & 0xfffffff8);
        *param_1 = (int)(puVar3 + 2);
        uVar7 = *puVar3;
        uVar8 = puVar3[1];
        if ((int)uVar8 < 0)
        {
            *param_3 = '-';
            param_1[0xe] = 1;
            uVar8 = uVar8 & 0x7fffffff;
        }
        else
        {
            if (param_1[2] == 0x20)
            {
                *param_3 = ' ';
            }
            else
            {
                if (param_1[2] != 0x2b)
                    goto LAB_81c1d098;
                *param_3 = '+';
            }
            param_1[0xe] = 1;
        }
    LAB_81c1d098:
        param_1[8] = (int)(param_3 + param_1[0xe]);
        if (*param_2 == 'G')
        {
            *param_2 = 'E';
        }
        else if (*param_2 == 'g')
        {
            *param_2 = 'e';
        }
        if (param_1[7] < 0)
        {
            param_1[7] = 6;
        }
        sango_crt_format_double_digits((int)param_1, param_2, uVar7, uVar8, param_2);
        iVar4 = param_1[6];
        goto LAB_81c1d128;
    case 'X':
    case 'o':
    case 'u':
    case 'x':
        if (param_1[5] == 0x68)
        {
            sango_legacy_trap();
        }
        puVar3 = (uint32_t *)(*param_1 + 3U & 0xfffffffc);
        *param_1 = (int)(puVar3 + 1);
        uVar7 = *puVar3;
        if ((param_1[4] == 0x48) && (*param_2 != 'u'))
        {
            param_3[param_1[0xe]] = '0';
            iVar4 = param_1[0xe];
            param_1[0xe] = iVar4 + 1;
            if (*param_2 != 'o')
            {
                param_3[iVar4 + 1] = *param_2;
                param_1[0xe] = param_1[0xe] + 1;
            }
        }
        param_1[8] = (int)(param_3 + param_1[0xe]);
        uVar8 = 8;
        if ((*param_2 != 'o') && (uVar8 = 10, *param_2 != 'u'))
        {
            uVar8 = 0x10;
        }
        goto LAB_81c1d014;
    case 'c':
        /* WARNING: Does not return */
        pcVar1 = (SangoLegacyCode *)sango_legacy_trap(0);
        (*pcVar1)();
    case 'd':
    case 'i':
        if (param_1[5] == 0x68)
        {
            sango_legacy_trap();
        }
        puVar3 = (uint32_t *)(*param_1 + 3U & 0xfffffffc);
        *param_1 = (int)(puVar3 + 1);
        uVar7 = *puVar3;
        if ((int)uVar7 < 0)
        {
            *param_3 = '-';
            param_1[0xe] = 1;
            uVar7 = -uVar7;
        }
        else
        {
            if (param_1[2] == 0x20)
            {
                *param_3 = ' ';
            }
            else
            {
                if (param_1[2] != 0x2b)
                    goto LAB_81c1cf50;
                *param_3 = '+';
            }
            param_1[0xe] = 1;
        }
    LAB_81c1cf50:
        param_1[8] = (int)(param_3 + param_1[0xe]);
        uVar8 = 10;
    LAB_81c1d014:
        sango_crt_format_unsigned_digits((int)param_1, uVar7, uVar8, param_2);
        iVar4 = param_1[6];
        goto LAB_81c1d128;
    case 's':
        puVar2 = (uint32_t *)(*param_1 + 3U & 0xfffffffc);
        *param_1 = (int)(puVar2 + 1);
        pcVar6 = (char *)*puVar2;
        param_1[8] = (int)pcVar6;
        iVar4 = sango_crt_strlen(pcVar6);
        param_1[0xf] = iVar4;
        iVar5 = param_1[7];
        if ((-1 < iVar5) && (iVar5 < iVar4))
        {
            param_1[0xf] = iVar5;
        }
    }
    iVar4 = param_1[6];
LAB_81c1d128:
    iVar4 =
        (((((iVar4 - param_1[0xe]) - param_1[10]) - param_1[0xf]) - param_1[0xb]) - param_1[0x10]) -
        param_1[0xc];
    param_1[6] = iVar4;
    if (0 < iVar4)
    {
        if (param_1[1] == 0x4c)
        {
            param_1[9] = iVar4;
        }
        else
        {
            param_1[0xd] = param_1[6];
        }
    }
    return param_2 + 1;
}

/* 原函数 0x81c1d198 */
void sango_crt_format_unsigned_digits(int param_1, uint32_t param_2, uint32_t param_3,
                                      char *param_4)
{
    unsigned char abi_storage[48] __attribute__((aligned(8)));
#define acStack_21 (*(char(*)[25])(abi_storage + 7))

    char *pcVar1;
    int iVar2;
    int iVar3;

    pcVar1 = g_legacy_data_81c20b68;
    if (*param_4 != 'X')
    {
        pcVar1 = g_legacy_data_81c20b54;
    }
    iVar2 = 0x18;
    do
    {
        iVar3 = iVar2;
        iVar2 = iVar3 + -1;
        if (param_3 == 0)
        {
            sango_legacy_trap(7);
        }
        acStack_21[iVar3] = pcVar1[param_2 % param_3];
        if (param_3 == 0)
        {
            sango_legacy_trap(7);
        }
    } while ((param_2 / param_3 != 0) && (param_2 = param_2 / param_3, 0 < iVar2));
    *(uint32_t *)(param_1 + 0x3c) = 0x18U - iVar2;
    crt_memcpy(*(void **)(param_1 + 0x20), acStack_21 + iVar3, 0x18U - iVar2);
    iVar2 = *(int *)(param_1 + 0x1c);
    if (iVar2 < 1)
    {
        if (*(int *)(param_1 + 0x1c) == 0)
        {
            if (**(char **)(param_1 + 0x20) != '0')
            {
                return;
            }
            *(uint32_t *)(param_1 + 0x3c) = 0;
            return;
        }
        if (*(int *)(param_1 + 0xc) != 0x48)
        {
            return;
        }
        if (*(int *)(param_1 + 4) != 0x4c)
        {
            return;
        }
        if (*(int *)(param_1 + 0x18) <= *(int *)(param_1 + 0x3c) + *(int *)(param_1 + 0x38))
        {
            return;
        }
        iVar2 = (*(int *)(param_1 + 0x18) - *(int *)(param_1 + 0x3c)) - *(int *)(param_1 + 0x38);
    }
    else
    {
        if (iVar2 <= *(int *)(param_1 + 0x3c))
        {
            return;
        }
        iVar2 = iVar2 - *(int *)(param_1 + 0x3c);
    }
    *(int *)(param_1 + 0x28) = iVar2;
    return;
}
#undef acStack_21

/* 原函数 0x81c1d2d4 */
void sango_crt_format_double_digits(int param_1, uint32_t param_2, uint32_t param_3, int param_4,
                                    char *param_5)
{
    unsigned char abi_storage[108] __attribute__((aligned(8)));
    (*(char **)(abi_storage + 88)) = param_5;
#define local_48 (*(char(*)[24])(abi_storage + 0))
#define local_30 (*(uint32_t(*)[2])(abi_storage + 24))
#define param_5 (*(char **)(abi_storage + 88))

    char cVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint64_t uVar8;
    uint64_t uVar9;

    uVar8 = CONCAT44(param_4, param_3);
    if ((param_4 == 0x7ff00000) && (param_3 == 0))
    {
        crt_memcpy(*(void **)(param_1 + 0x20), &g_legacy_data_81c20bf8, 3);
        *(uint32_t *)(param_1 + 0x3c) = 3;
    LAB_81c1d378:
        *(uint32_t *)(param_1 + 0xc) = 0x4c;
        return;
    }
    if (0x7fefffff < param_4)
    {
        crt_memcpy(*(void **)(param_1 + 0x20), &g_legacy_data_81c20bfc, 3);
        *(uint32_t *)(param_1 + 0x3c) = 3;
        *(uint32_t *)(param_1 + 0x38) = 0;
        goto LAB_81c1d378;
    }
    local_30[0] = 0;
    iVar2 = sango_soft_compare_f64_nan_low_compat(param_3, param_4, g_legacy_data_81c20c70,
                                                  g_legacy_data_81c20c74);
    if (iVar2 < 0)
    {
        iVar2 = sango_soft_compare_f64_nan_low(param_3, param_4, 0, 0);
        uVar9 = CONCAT44(param_4, param_3);
        uVar6 = local_30[0];
        if (((0 < iVar2) && (iVar2 = sango_soft_compare_f64_nan_high_compat(
                                 param_3, param_4, g_legacy_data_81c20c78, g_legacy_data_81c20c7c),
                             uVar9 = CONCAT44(param_4, param_3), uVar6 = local_30[0], iVar2 < 0)) &&
            (iVar2 = 0, uVar9 = CONCAT44(param_4, param_3), 0 < g_legacy_data_81c20bd0))
        {
            cVar1 = *param_5;
            do
            {
                uVar7 = (uint32_t)((uint64_t)uVar8 >> 0x20);
                if ((cVar1 == 'e') || (cVar1 == 'E'))
                {
                    uVar9 = sango_soft_mul_f64((uint32_t)uVar8, uVar7,
                                               (&g_legacy_data_81c20b80)[iVar2 * 2],
                                               (&g_legacy_data_81c20b84)[iVar2 * 2]);
                    uVar5 = g_legacy_data_81c20c70;
                    uVar7 = g_legacy_data_81c20c74;
                }
                else
                {
                    uVar9 = sango_soft_mul_f64((uint32_t)uVar8, uVar7,
                                               (&g_legacy_data_81c20b80)[iVar2 * 2],
                                               (&g_legacy_data_81c20b84)[iVar2 * 2]);
                    uVar5 = g_legacy_data_81c20c78;
                    uVar7 = g_legacy_data_81c20c7c;
                }
                iVar3 = sango_soft_compare_f64_nan_high_compat(
                    (uint32_t)uVar9, (int)((uint64_t)uVar9 >> 0x20), uVar5, uVar7);
                if (iVar3 < 0)
                {
                    uVar6 = uVar6 - (&g_legacy_data_81c20bd0)[iVar2];
                    uVar8 = uVar9;
                }
                iVar2 = iVar2 + 1;
                uVar9 = uVar8;
            } while (0 < (&g_legacy_data_81c20bd0)[iVar2]);
        }
    }
    else
    {
        iVar2 = 0;
        uVar9 = uVar8;
        uVar6 = local_30[0];
        if (0 < g_legacy_data_81c20bd0)
        {
            iVar3 = 0;
            do
            {
                uVar7 = (uint32_t)((uint64_t)uVar8 >> 0x20);
                iVar4 = sango_soft_compare_f64_nan_low_compat(
                    (uint32_t)uVar8, uVar7, *(uint32_t *)((int)&g_legacy_data_81c20b80 + iVar3),
                    *(uint32_t *)((int)&g_legacy_data_81c20b84 + iVar3));
                if (-1 < iVar4)
                {
                    uVar8 = sango_soft_div_f64((uint32_t)uVar8, uVar7,
                                               *(uint32_t *)((int)&g_legacy_data_81c20b80 + iVar3),
                                               *(uint32_t *)((int)&g_legacy_data_81c20b84 + iVar3));
                    uVar6 = uVar6 + (&g_legacy_data_81c20bd0)[iVar2];
                }
                iVar2 = iVar2 + 1;
                iVar3 = iVar2 * 8;
                uVar9 = uVar8;
            } while (0 < (&g_legacy_data_81c20bd0)[iVar2]);
        }
    }
    local_30[0] = uVar6;
    uVar7 = (uint32_t)((uint64_t)uVar9 >> 0x20);
    uVar6 = (uint32_t)uVar9;
    if ((*param_5 == 'e') || (*param_5 == 'E'))
    {
        iVar2 = 0x11;
        if (*(int *)(param_1 + 0x1c) < 0x11)
        {
            iVar2 = *(int *)(param_1 + 0x1c) + 1;
        }
        iVar2 = sango_crt_scale_double_decimal(uVar6, uVar7, (int *)local_30, iVar2, local_48);
        **(char **)(param_1 + 0x20) = local_48[0];
        iVar3 = 1;
        if (((1 < iVar2) || (*(int *)(param_1 + 0x10) == 0x48)) || (0 < *(int *)(param_1 + 0x1c)))
        {
            *(uint8_t *)(*(int *)(param_1 + 0x20) + 1) = 0x2e;
            crt_memcpy((void *)(*(int *)(param_1 + 0x20) + 2), local_48 + 1, iVar2 - 1);
            iVar3 = iVar2 + 1;
        }
        *(int *)(param_1 + 0x3c) = iVar3;
        if (iVar2 + -1 < *(int *)(param_1 + 0x1c))
        {
            *(int *)(param_1 + 0x2c) = (*(int *)(param_1 + 0x1c) - iVar2) + 1;
        }
        *(char *)(*(int *)(param_1 + 0x20) + iVar3) = *param_5;
        if ((int)local_30[0] < 0)
        {
            *(uint8_t *)(*(int *)(param_1 + 0x20) + iVar3 + 1) = 0x2d;
            local_30[0] = -local_30[0];
        }
        else
        {
            *(uint8_t *)(*(int *)(param_1 + 0x20) + iVar3 + 1) = 0x2b;
        }
        iVar3 = iVar3 + 2;
        if ((int)local_30[0] < 10)
        {
            *(uint8_t *)(*(int *)(param_1 + 0x20) + iVar3) = 0x30;
            *(char *)(iVar3 + *(int *)(param_1 + 0x20) + 1) = (char)local_30[0] + '0';
            iVar2 = 4;
        }
        else
        {
            iVar2 = 10;
            for (; 0 < (int)local_30[0]; local_30[0] = (int)local_30[0] / 10)
            {
                local_48[iVar2] = (char)local_30[0] + (char)((int)local_30[0] / 10) * -10 + '0';
                iVar2 = iVar2 + -1;
            }
            crt_memcpy((void *)(iVar3 + *(int *)(param_1 + 0x20)), local_48 + iVar2 + 1,
                       10 - iVar2);
            iVar2 = 0xc - iVar2;
        }
        *(int *)(param_1 + 0x40) = iVar2;
        goto LAB_81c1d99c;
    }
    if ((int)local_30[0] < 0)
    {
        iVar2 = 0;
        if ((int)~local_30[0] < *(int *)(param_1 + 0x1c))
        {
            iVar3 = *(int *)(param_1 + 0x1c) + local_30[0] + 1;
            iVar2 = 0x11;
            if (iVar3 < 0x12)
            {
                iVar2 = iVar3;
            }
        }
        uVar6 = sango_crt_scale_double_decimal(uVar6, uVar7, (int *)local_30, iVar2, local_48);
        **(uint8_t **)(param_1 + 0x20) = 0x30;
        uVar7 = 1;
        if (((0 < (int)uVar6) || (*(int *)(param_1 + 0x10) == 0x48)) ||
            (0 < *(int *)(param_1 + 0x1c)))
        {
            *(uint8_t *)(*(int *)(param_1 + 0x20) + 1) = 0x2e;
            uVar7 = 2;
            crt_memcpy((void *)(*(int *)(param_1 + 0x20) + 2), local_48, uVar6);
        }
        *(uint32_t *)(param_1 + 0x3c) = uVar7;
        *(uint32_t *)(param_1 + 0x40) = uVar6;
        if (*(int *)(param_1 + 0x1c) < (int)~local_30[0])
        {
            *(uint32_t *)(param_1 + 0x2c) = *(uint32_t *)(param_1 + 0x1c);
        }
        else
        {
            *(uint32_t *)(param_1 + 0x2c) = ~local_30[0];
        }
        if (*(int *)(param_1 + 0x1c) <= *(int *)(param_1 + 0x40) + *(int *)(param_1 + 0x2c))
            goto LAB_81c1d99c;
        iVar2 = (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 0x40)) - *(int *)(param_1 + 0x2c);
    }
    else
    {
        iVar2 = 0x11;
        if (*(int *)(param_1 + 0x1c) < (int)(0x10 - local_30[0]))
        {
            iVar2 = *(int *)(param_1 + 0x1c) + local_30[0] + 1;
        }
        uVar6 = sango_crt_scale_double_decimal(uVar6, uVar7, (int *)local_30, iVar2, local_48);
        if ((int)uVar6 <= (int)(local_30[0] + 1))
        {
            crt_memcpy(*(void **)(param_1 + 0x20), local_48, uVar6);
            *(uint32_t *)(param_1 + 0x3c) = uVar6;
            if ((*(int *)(param_1 + 0x10) == 0x48) || (0 < *(int *)(param_1 + 0x1c)))
            {
                *(uint8_t *)(*(int *)(param_1 + 0x20) + uVar6) = 0x2e;
                *(uint32_t *)(param_1 + 0x40) = 1;
                *(uint32_t *)(param_1 + 0x30) = *(uint32_t *)(param_1 + 0x1c);
            }
            if ((int)uVar6 < (int)(local_30[0] + 1))
            {
                *(uint32_t *)(param_1 + 0x2c) = (local_30[0] - uVar6) + 1;
            }
            goto LAB_81c1d99c;
        }
        crt_memcpy(*(void **)(param_1 + 0x20), local_48, local_30[0] + 1);
        *(uint8_t *)(*(int *)(param_1 + 0x20) + local_30[0] + 1) = 0x2e;
        crt_memcpy((void *)(*(int *)(param_1 + 0x20) + local_30[0] + 2), local_48 + local_30[0] + 1,
                   (uVar6 - local_30[0]) - 1);
        *(uint32_t *)(param_1 + 0x3c) = local_30[0] + 1;
        *(uint32_t *)(param_1 + 0x40) = uVar6 - local_30[0];
        if (*(int *)(param_1 + 0x1c) <= (int)((uVar6 - local_30[0]) + -1))
            goto LAB_81c1d99c;
        iVar2 = (*(int *)(param_1 + 0x1c) - uVar6) + local_30[0] + 1;
    }
    *(int *)(param_1 + 0x30) = iVar2;
LAB_81c1d99c:
    if (*(int *)(param_1 + 0xc) != 0x48)
    {
        return;
    }
    if (*(int *)(param_1 + 4) != 0x4c)
    {
        return;
    }
    iVar2 = *(int *)(param_1 + 0x38) + *(int *)(param_1 + 0x3c) + *(int *)(param_1 + 0x2c) +
            *(int *)(param_1 + 0x40) + *(int *)(param_1 + 0x30);
    if (*(int *)(param_1 + 0x18) <= iVar2)
    {
        return;
    }
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x18) - iVar2;
    return;
}
#undef local_48
#undef local_30
#undef param_5

/* 原函数 0x81c1da28 */
int sango_crt_scale_double_decimal(uint32_t param_1, uint32_t param_2, int *param_3, int param_4,
                                   uint8_t *param_5)
{
    unsigned char abi_storage[20] __attribute__((aligned(8)));
    (*(uint8_t **)(abi_storage + 0)) = param_5;
#define param_5 (*(uint8_t **)(abi_storage + 0))

    uint32_t uVar1;
    uint32_t uVar2;
    char cVar3;
    int iVar4;
    uint32_t uVar5;
    char *pcVar6;
    int iVar7;
    uint32_t uVar8;
    uint64_t uVar9;
    uint64_t uVar10;

    uVar10 = CONCAT44(param_2, param_1);
    iVar4 = sango_soft_compare_f64_nan_high(param_1, param_2, 0, 0);
    uVar2 = g_legacy_data_81c20c74;
    uVar1 = g_legacy_data_81c20c70;
    if (iVar4 == 0)
    {
        *param_5 = 0x30;
        return 1;
    }
    if (param_4 == 0)
    {
        return 0;
    }
    iVar4 = 0;
    if (0 < param_4 + 1)
    {
        do
        {
            uVar8 = (uint32_t)((uint64_t)uVar10 >> 0x20);
            uVar5 = sango_soft_f64_to_int((uint32_t)uVar10, uVar8);
            param_5[iVar4] = (char)uVar5 + '0';
            uVar9 = sango_soft_int_to_f64(uVar5);
            uVar10 = sango_soft_sub_f64((uint32_t)uVar10, uVar8, (uint32_t)uVar9,
                                        (int)((uint64_t)uVar9 >> 0x20));
            uVar10 =
                sango_soft_mul_f64((uint32_t)uVar10, (int)((uint64_t)uVar10 >> 0x20), uVar1, uVar2);
            iVar4 = iVar4 + 1;
        } while (iVar4 < param_4 + 1);
    }
    iVar4 = iVar4 + -1;
    if ((param_4 - *param_3) + -1 < 0x10)
    {
        pcVar6 = param_5 + iVar4;
        if ((0xf < *param_3 + 1) || (pcVar6 = param_5 + iVar4, iVar4 < 0x10))
            goto LAB_81c1db48;
        iVar4 = 0xf;
    }
    pcVar6 = param_5 + iVar4;
LAB_81c1db48:
    if (*pcVar6 < '5')
    {
        param_5[iVar4] = 0x30;
        do
        {
            iVar7 = iVar4;
            iVar4 = iVar7 + -1;
        } while (param_5[iVar7 + -1] == '0');
    }
    else
    {
        do
        {
            iVar7 = iVar4;
            if (iVar7 == 0)
            {
                *param_5 = 0x31;
                *param_3 = *param_3 + 1;
                return 1;
            }
            param_5[iVar7] = 0x30;
            cVar3 = param_5[iVar7 + -1] + '\x01';
            param_5[iVar7 + -1] = cVar3;
            iVar4 = iVar7 + -1;
        } while ('9' < cVar3);
    }
    return iVar7;
}
#undef param_5

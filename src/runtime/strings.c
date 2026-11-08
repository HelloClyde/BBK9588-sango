#include "sango_internal.h"

/* 恢复的字符串与基础格式化运行库。 */

/* 原函数 0x81c1b950 */
char *sango_crt_memchr(char *param_1, int param_2, int param_3)
{
    char *pcVar1;
    int iVar2;

    iVar2 = param_3 + -1;
    do
    {
        pcVar1 = param_1;
        if (iVar2 < 0)
        {
            return (char *)0x0;
        }
        iVar2 = iVar2 + -1;
        param_1 = pcVar1 + 1;
    } while (*pcVar1 != param_2);
    return pcVar1;
}

/* 原函数 0x81c1b980 */
void sango_crt_sprintf_words(uint8_t *param_1, uint8_t *param_2, uint32_t param_3, uint32_t param_4)
{
    unsigned char abi_storage[32] __attribute__((aligned(8)));
#define local_res4 (*(uint8_t **)(abi_storage + 4))
#define local_res8 (*(uint32_t *)(abi_storage + 8))
#define local_resc (*(uint32_t *)(abi_storage + 12))
#define local_res0 (*(uint8_t **)(abi_storage + 0))

    local_res0 = param_1;
    local_res4 = param_2;
    local_res8 = param_3;
    local_resc = param_4;
    sango_crt_vformat(param_2, &local_res8, sango_crt_append_character, &local_res0);
    *local_res0 = 0;
    return;
}
#undef local_res4
#undef local_res8
#undef local_resc
#undef local_res0

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
int sango_crt_strtol(char *param_1, uint32_t *param_2, int param_3)
{
    bool bVar1;
    int iVar2;
    char cVar3;
    char *pcVar4;
    int iVar5;
    int iVar6;
    int iVar7;

    iVar6 = 0;
    iVar7 = 1;
    while (iVar2 = sango_crt_isspace(*param_1), iVar2 != 0)
    {
        param_1 = param_1 + 1;
    }
    cVar3 = *param_1;
    if (*param_1 == '+')
    {
        param_1 = param_1 + 1;
        cVar3 = *param_1;
    }
    else if (*param_1 == '-')
    {
        param_1 = param_1 + 1;
        cVar3 = *param_1;
        iVar7 = -1;
    }
    pcVar4 = param_1;
    if (cVar3 == '0')
    {
        pcVar4 = param_1 + 1;
        iVar2 = sango_crt_toupper(*pcVar4);
        if (iVar2 != 0x58)
        {
            if (param_3 == 0)
            {
                cVar3 = *pcVar4;
                param_3 = 8;
                goto LAB_81c1ba80;
            }
            cVar3 = *pcVar4;
            bVar1 = param_3 < 0xb;
            goto LAB_81c1bb3c;
        }
        pcVar4 = param_1 + 2;
        cVar3 = *pcVar4;
        param_3 = 0x10;
    joined_r0x81c1bb4c:
        while (cVar3 != 0)
        {
            iVar2 = sango_crt_isdigit(cVar3);
            iVar5 = cVar3 + -0x30;
            if (iVar2 == 0)
            {
                iVar2 = sango_crt_toupper(cVar3);
                if ((iVar2 < 0x41) || (iVar5 = iVar2 + -0x37, param_3 + 0x37 <= iVar2))
                    break;
            }
            pcVar4 = pcVar4 + 1;
            if (param_3 == 0)
            {
                sango_legacy_trap(7);
            }
            bVar1 = 0x7fffffff / param_3 + -1 <= iVar6;
            iVar6 = iVar6 * param_3 + iVar5;
            if (bVar1)
            {
                iVar6 = 0x7fffffff;
                g_runtime_errno = 0x22;
            }
            cVar3 = *pcVar4;
        }
    }
    else
    {
    LAB_81c1ba80:
        bVar1 = param_3 < 0xb;
        if (param_3 == 0)
        {
            param_3 = 10;
        }
        else
        {
        LAB_81c1bb3c:
            if (!bVar1)
                goto joined_r0x81c1bb4c;
        }
        while (iVar2 = sango_crt_isdigit(cVar3), iVar2 != 0)
        {
            if (param_3 == 0)
            {
                sango_legacy_trap(7);
            }
            if (iVar6 < 0x7fffffff / param_3 + -1)
            {
                iVar6 = iVar6 * param_3 + (int)*pcVar4 + -0x30;
            }
            else
            {
                g_runtime_errno = 0x22;
                iVar6 = 0x7fffffff;
            }
            pcVar4 = pcVar4 + 1;
            cVar3 = *pcVar4;
        }
    }
    if (param_2 != (uint32_t *)0x0)
    {
        *param_2 = pcVar4;
    }
    if (iVar7 == -1)
    {
        iVar6 = -iVar6;
    }
    return iVar6;
}

/* 原函数 0x81c1bc58 */
void sango_crt_atoi_compat(char *param_1)
{
    sango_crt_strtol(param_1, (uint32_t *)0x0, 10);
    return;
}

/* 原函数 0x81c1bcbc */
char *sango_crt_strcpy(char *param_1, char *param_2)
{
    char cVar1;
    char *pcVar2;

    pcVar2 = param_1;
    do
    {
        cVar1 = *param_2;
        param_2 = param_2 + 1;
        *pcVar2 = cVar1;
        pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    return param_1;
}

/* 原函数 0x81c1bce0 */
void *crt_memset(void *dst, int value, uint32_t size)
{
    uint8_t *puVar1;
    int iVar2;

    puVar1 = (uint8_t *)dst;
    for (iVar2 = size - 1; iVar2 != -1; iVar2 = iVar2 + -1)
    {
        *puVar1 = (char)value;
        puVar1 = puVar1 + 1;
    }
    return dst;
}

/* 原函数 0x81c1bd08 */
void *crt_memcpy(void *dst, void *src, uint32_t size)
{
    uint8_t uVar1;
    uint8_t *puVar2;
    int iVar3;

    puVar2 = (uint8_t *)dst;
    for (iVar3 = size - 1; iVar3 != -1; iVar3 = iVar3 + -1)
    {
        /* WARNING: Load size is inaccurate */
        uVar1 = *(uint8_t *)src;
        src = (void *)((int)src + 1);
        *puVar2 = uVar1;
        puVar2 = puVar2 + 1;
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
int sango_crt_vformat(uint8_t *param_1, uint32_t *param_2, uint8_t *param_3, uint32_t param_4)
{
    unsigned char abi_storage[104] __attribute__((aligned(8)));
#define local_38 (*(uint32_t *)(abi_storage + 72))
#define local_34 (*(uint32_t *)(abi_storage + 76))
#define local_30 (*(uint32_t *)(abi_storage + 80))
#define local_2c (*(uint32_t *)(abi_storage + 84))
#define auStack_80 (*(uint8_t(*)[16])(abi_storage + 0))
#define local_70 (*(uint8_t(*)[30])(abi_storage + 16))
#define local_52 (*(uint8_t(*)[2])(abi_storage + 46))
#define local_50 (*(char **)(abi_storage + 48))
#define local_4c (*(uint32_t *)(abi_storage + 52))
#define local_48 (*(char **)(abi_storage + 56))
#define local_44 (*(char **)(abi_storage + 60))
#define local_40 (*(int *)(abi_storage + 64))
#define local_3c (*(char **)(abi_storage + 68))

    uint8_t bVar1;
    char cVar2;
    uint8_t *puVar3;
    char *pcVar4;
    uint32_t uVar5;
    uint8_t bVar6;
    uint32_t uVar7;
    int iVar8;
    char *pcVar9;
    char **ppcVar10;
    char **ppcVar11;
    uint8_t *pbVar12;
    char *pcVar13;
    uint32_t *puVar14;
    uint32_t *puVar15;
    int *piVar16;
    int iVar17;
    uint32_t uVar18;

    bVar6 = *param_1;
    local_3c = g_legacy_data_81c20770;
    iVar17 = 0;
LAB_81c1bda0:
    uVar5 = (uint32_t)bVar6;
    if (uVar5 == 0)
    {
    LAB_81c1be54:
        return iVar17;
    }
    if (uVar5 == 0x25)
    {
        local_4c = 0;
        local_50 = (char *)0x0;
        local_44 = (char *)0x0;
        pcVar13 = (char *)0xffffffff;
        local_40 = 0;
        pbVar12 = param_1;
    LAB_81c1be0c:
        param_1 = pbVar12 + 1;
        uVar5 = (uint32_t)*param_1;
        switch (uVar5)
        {
        case 0:
            goto LAB_81c1be54;
        default:
            goto switchD_81c1be34_caseD_1;
        case 0x20:
            iVar8 = 0x20;
            pbVar12 = param_1;
            if (local_40 == 0)
                goto LAB_81c1be48;
            goto LAB_81c1be0c;
        case 0x23:
            local_4c = local_4c | 8;
            break;
        case 0x2a:
            puVar14 = (uint32_t *)((uint32_t)((int)param_2 + 3) & 0xfffffffc);
            local_44 = (char *)*puVar14;
            param_2 = puVar14 + 1;
            pbVar12 = param_1;
            if ((int)local_44 < 0)
            {
                local_44 = (char *)-(int)local_44;
                goto switchD_81c1be34_caseD_2d;
            }
            goto LAB_81c1be0c;
        case 0x2b:
            iVar8 = 0x2b;
        LAB_81c1be48:
            local_40 = iVar8;
            pbVar12 = param_1;
            goto LAB_81c1be0c;
        case 0x2d:
        switchD_81c1be34_caseD_2d:
            local_4c = local_4c | 0x10;
        LAB_81c1bec0:
            pbVar12 = param_1;
            goto LAB_81c1be0c;
        case 0x2e:
            pbVar12 = pbVar12 + 2;
            bVar6 = *pbVar12;
            pcVar13 = (char *)0x0;
            if (bVar6 == 0x2a)
            {
                puVar14 = (uint32_t *)((uint32_t)((int)param_2 + 3) & 0xfffffffc);
                pcVar13 = (char *)*puVar14;
                param_2 = puVar14 + 1;
            }
            else
            {
                while ((-1 < (char)bVar6 && (iVar8 = sango_crt_isdigit(bVar6), iVar8 != 0)))
                {
                    bVar1 = *pbVar12;
                    pbVar12 = pbVar12 + 1;
                    bVar6 = *pbVar12;
                    pcVar13 = (char *)((int)pcVar13 * 10 + (uint32_t)bVar1 + -0x30);
                }
                pbVar12 = pbVar12 + -1;
            }
            if ((int)pcVar13 < -1)
            {
                pcVar13 = (char *)0xffffffff;
            }
            goto LAB_81c1be0c;
        case 0x30:
            local_4c = local_4c | 0x20;
            break;
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
            pcVar4 = (char *)0x0;
            while (true)
            {
                pbVar12 = param_1 + 1;
                pcVar4 = (char *)((int)pcVar4 * 10 + uVar5 + -0x30);
                if (((char)*pbVar12 < '\0') || (iVar8 = sango_crt_isdigit(*pbVar12), iVar8 == 0))
                    break;
                uVar5 = (uint32_t)*pbVar12;
                param_1 = pbVar12;
            }
            local_44 = pcVar4;
            pbVar12 = param_1;
            goto LAB_81c1be0c;
        case 0x44:
            local_4c = local_4c | 1;
        case 100:
        case 0x69:
            puVar3 = (uint8_t *)((int)param_2 + 3);
            if ((local_4c & 4) == 0)
            {
                uVar5 = *(uint32_t *)((uint32_t)puVar3 & 0xfffffffc);
            }
            else
            {
                uVar5 = (uint32_t) * (short *)((uint32_t)puVar3 & 0xfffffffc);
            }
            param_2 = (uint32_t *)(((uint32_t)puVar3 & 0xfffffffc) + 4);
            if ((int)uVar5 < 0)
            {
                uVar5 = -uVar5;
                local_40 = 0x2d;
            }
            uVar7 = 10;
        LAB_81c1bfe4:
            local_50 = pcVar13;
            if (-1 < (int)pcVar13)
            {
                local_4c = local_4c & 0xffffffdf;
            }
            ppcVar11 = &local_50;
            if ((uVar5 != 0) || (puVar3 = auStack_80 + -(int)ppcVar11, pcVar13 != (char *)0x0))
                goto LAB_81c1c010;
            goto LAB_81c1c06c;
        case 0x4c:
            local_4c = local_4c | 2;
            goto LAB_81c1bec0;
        case 0x4f:
            local_4c = local_4c | 1;
        case 0x6f:
            puVar3 = (uint8_t *)((int)param_2 + 3);
            if ((local_4c & 4) == 0)
            {
                uVar5 = *(uint32_t *)((uint32_t)puVar3 & 0xfffffffc);
            }
            else
            {
                uVar5 = (uint32_t) * (short *)((uint32_t)puVar3 & 0xfffffffc);
            }
            param_2 = (uint32_t *)(((uint32_t)puVar3 & 0xfffffffc) + 4);
            uVar7 = 8;
        LAB_81c1c2a8:
            local_40 = 0;
            goto LAB_81c1bfe4;
        case 0x55:
            local_4c = local_4c | 1;
        case 0x75:
            puVar3 = (uint8_t *)((int)param_2 + 3);
            if ((local_4c & 4) == 0)
            {
                uVar5 = *(uint32_t *)((uint32_t)puVar3 & 0xfffffffc);
            }
            else
            {
                uVar5 = (uint32_t) * (short *)((uint32_t)puVar3 & 0xfffffffc);
            }
            param_2 = (uint32_t *)(((uint32_t)puVar3 & 0xfffffffc) + 4);
            uVar7 = 10;
            goto LAB_81c1c2a8;
        case 0x58:
            local_3c = g_legacy_data_81c20784;
        case 0x78:
            puVar3 = (uint8_t *)((int)param_2 + 3);
            if ((local_4c & 4) == 0)
            {
                uVar5 = *(uint32_t *)((uint32_t)puVar3 & 0xfffffffc);
            }
            else
            {
                uVar5 = (uint32_t) * (short *)((uint32_t)puVar3 & 0xfffffffc);
            }
            param_2 = (uint32_t *)(((uint32_t)puVar3 & 0xfffffffc) + 4);
            uVar7 = 0x10;
            if ((local_4c & 8) != 0)
            {
                if (uVar5 != 0)
                {
                    local_4c = local_4c | 0x40;
                }
            }
            goto LAB_81c1c2a8;
        case 99:
            puVar3 = (uint8_t *)((uint32_t)((int)param_2 + 3) & 0xfffffffc);
            local_70[0] = *puVar3;
            ppcVar11 = (char **)local_70;
            param_2 = (uint32_t *)(puVar3 + 4);
            local_48 = (char *)0x1;
            local_40 = 0;
            goto LAB_81c1c074;
        case 0x68:
            goto switchD_81c1be34_caseD_68;
        case 0x6c:
            local_4c = local_4c | 1;
            break;
        case 0x6e:
            if (((local_4c & 1) == 0) && ((local_4c & 4) != 0))
            {
                puVar14 = (uint32_t *)((uint32_t)((int)param_2 + 3) & 0xfffffffc);
                param_2 = puVar14 + 1;
                *(short *)*puVar14 = (short)iVar17;
            }
            else
            {
                puVar14 = (uint32_t *)((uint32_t)((int)param_2 + 3) & 0xfffffffc);
                param_2 = puVar14 + 1;
                *(int *)*puVar14 = iVar17;
            }
            goto LAB_81c1bdc4;
        case 0x70:
            puVar15 = (uint32_t *)((uint32_t)((int)param_2 + 3) & 0xfffffffc);
            uVar5 = *puVar15;
            uVar7 = 0x10;
            param_2 = puVar15 + 1;
            goto LAB_81c1c2a8;
        case 0x73:
            piVar16 = (int *)((uint32_t)((int)param_2 + 3) & 0xfffffffc);
            ppcVar11 = (char **)*piVar16;
            param_2 = (uint32_t *)(piVar16 + 1);
            if (ppcVar11 == (char **)0x0)
            {
                ppcVar11 = (char **)g_legacy_data_81c20798;
            }
            if ((int)pcVar13 < 0)
            {
                local_48 = (char *)sango_crt_strlen((char *)ppcVar11);
            }
            else
            {
                pcVar4 = sango_crt_memchr((char *)ppcVar11, 0, (int)pcVar13);
                local_48 = pcVar13;
                if ((pcVar4 != (char *)0x0) && (local_48 = pcVar4 + -(int)ppcVar11,
                                                (int)pcVar13 < (int)(pcVar4 + -(int)ppcVar11)))
                {
                    local_48 = pcVar13;
                }
            }
            local_40 = 0;
            goto LAB_81c1c074;
        }
        pbVar12 = param_1;
        goto LAB_81c1be0c;
    }
    if (uVar5 != 10)
        goto LAB_81c1bdb8;
    (*(SangoLegacyCode *)param_3)(0xd, param_4);
    (*(SangoLegacyCode *)param_3)(10, param_4);
    iVar17 = iVar17 + 1;
    goto LAB_81c1bdc0;
switchD_81c1be34_caseD_68:
    local_4c = local_4c | 4;
    pbVar12 = param_1;
    goto LAB_81c1be0c;
LAB_81c1c010:
    do
    {
        ppcVar10 = ppcVar11;
        uVar18 = uVar5 / uVar7;
        if (uVar7 == 0)
        {
            sango_legacy_trap(7);
        }
        ppcVar11 = (char **)((int)ppcVar10 + -1);
        cVar2 = local_3c[uVar5 % uVar7];
        *(char *)ppcVar11 = cVar2;
        uVar5 = uVar18;
    } while (uVar18 != 0);
    local_3c = g_legacy_data_81c20770;
    if (((local_4c & 8) == 0) || (uVar7 != 8))
    {
    LAB_81c1c068:
        puVar3 = auStack_80 + -(int)ppcVar11;
    }
    else
    {
        puVar3 = auStack_80 + -(int)ppcVar11;
        if (cVar2 != '0')
        {
            ppcVar11 = (char **)((int)ppcVar10 + -2);
            *(char *)ppcVar11 = '0';
            goto LAB_81c1c068;
        }
    }
LAB_81c1c06c:
    local_48 = puVar3 + 0x30;
LAB_81c1c074:
    pcVar13 = local_48;
    if (local_40 != 0)
    {
        pcVar13 = local_48 + 1;
    }
    if ((local_4c & 0x40) != 0)
    {
        pcVar13 = pcVar13 + 2;
    }
    local_38 = local_4c & 0x40;
    local_34 = (uint32_t)((int)pcVar13 < (int)local_50);
    pcVar4 = pcVar13;
    if ((int)pcVar13 < (int)local_50 != 0)
    {
        pcVar4 = local_50;
    }
    local_30 = local_4c & 0x30;
    uVar5 = (uint32_t)((int)pcVar4 < (int)local_44);
    local_2c = uVar5;
    if ((((local_4c & 0x30) == 0) &&
         (local_2c = (uint32_t)((int)pcVar4 < 0), local_44 != (char *)0x0)) &&
        (local_2c = uVar5, pcVar9 = pcVar4, uVar5 != 0))
    {
        do
        {
            (*(SangoLegacyCode *)param_3)(0x20, param_4);
            pcVar9 = pcVar9 + 1;
        } while ((int)pcVar9 < (int)local_44);
    }
    if (local_40 != 0)
    {
        (*(SangoLegacyCode *)param_3)(local_40, param_4);
    }
    if (local_38 != 0)
    {
        (*(SangoLegacyCode *)param_3)(0x30, param_4);
        (*(SangoLegacyCode *)param_3)((int)(char)*param_1, param_4);
    }
    if ((local_30 == 0x20) && (local_2c != 0))
    {
        iVar8 = (int)local_44 - (int)pcVar4;
        do
        {
            iVar8 = iVar8 + -1;
            (*(SangoLegacyCode *)param_3)(0x30, param_4);
        } while (iVar8 != 0);
    }
    pcVar9 = local_48;
    if (local_34 != 0)
    {
        iVar8 = (int)local_50 - (int)pcVar13;
        do
        {
            iVar8 = iVar8 + -1;
            (*(SangoLegacyCode *)param_3)(0x30, param_4);
            pcVar9 = local_48;
        } while (iVar8 != 0);
    }
    while (-1 < (int)(pcVar9 + -1))
    {
        (*(SangoLegacyCode *)param_3)((int)*(char *)ppcVar11, param_4);
        ppcVar11 = (char **)((int)ppcVar11 + 1);
        pcVar9 = pcVar9 + -1;
    }
    if (((local_4c & 0x10) != 0) && (local_2c != 0))
    {
        iVar8 = (int)local_44 - (int)pcVar4;
        do
        {
            iVar8 = iVar8 + -1;
            (*(SangoLegacyCode *)param_3)(0x20, param_4);
        } while (iVar8 != 0);
    }
    pcVar13 = local_44;
    if (local_2c == 0)
    {
        pcVar13 = pcVar4;
    }
    iVar17 = iVar17 + (int)pcVar13;
LAB_81c1bdc4:
    param_1 = param_1 + 1;
    bVar6 = *param_1;
    goto LAB_81c1bda0;
switchD_81c1be34_caseD_1:
    uVar5 = (uint32_t)(char)*param_1;
LAB_81c1bdb8:
    (*(SangoLegacyCode *)param_3)(uVar5, param_4);
LAB_81c1bdc0:
    iVar17 = iVar17 + 1;
    goto LAB_81c1bdc4;
}
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef auStack_80
#undef local_70
#undef local_52
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c

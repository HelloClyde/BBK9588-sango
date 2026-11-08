#include "sango_internal.h"

/* 恢复的整数转换、随机数及字符串辅助。 */

/* 原函数 0x81c1dc10 */
int sango_crt_heap_allocate(int param_1)
{
    uint32_t uVar1;
    uint32_t uVar2;
    int *piVar3;
    uint32_t uVar4;
    int iVar5;
    int unaff_gp;

    if (param_1 != 0)
    {
        piVar3 = (int *)(*(int *)(unaff_gp + 0xe0) + -8);
        if (7 < *(int *)(unaff_gp + 0xe8) - *(int *)(unaff_gp + 0xf0))
        {
            uVar2 = 0;
            if (*(int *)(unaff_gp + 0xec) != 0)
            {
                do
                {
                    uVar1 = piVar3[1];
                    if (((uVar1 & 1) == 0) && (uVar4 = param_1 + 3U & 0xfffffffc, uVar4 <= uVar1))
                    {
                        piVar3[1] = uVar4 | 1;
                        iVar5 = *piVar3;
                        if (uVar1 - uVar4 == 0)
                        {
                            return iVar5;
                        }
                        sango_crt_heap_shift_forward(*(uint32_t **)(unaff_gp + 0xe8),
                                                     (*(int *)(unaff_gp + 0xec) - uVar2) + -1);
                        piVar3[-1] = uVar1 - uVar4;
                        piVar3[-2] = iVar5 + uVar4;
                        *(int *)(unaff_gp + 0xe8) = *(int *)(unaff_gp + 0xe8) + -8;
                        *(int *)(unaff_gp + 0xec) = *(int *)(unaff_gp + 0xec) + 1;
                        return iVar5;
                    }
                    uVar2 = uVar2 + 1;
                    piVar3 = piVar3 + -2;
                } while (uVar2 < *(uint32_t *)(unaff_gp + 0xec));
            }
            if ((param_1 + 3U & 0xfffffffc) + 8 <=
                (uint32_t)(*(int *)(unaff_gp + 0xe8) - *(int *)(unaff_gp + 0xf0)))
            {
                iVar5 = *(int *)(unaff_gp + 0xf0);
                *piVar3 = iVar5;
                uVar2 = param_1 + 3U & 0xfffffffc;
                piVar3[1] = uVar2 | 1;
                *(uint32_t *)(unaff_gp + 0xf0) = uVar2 + *(int *)(unaff_gp + 0xf0);
                *(int *)(unaff_gp + 0xec) = *(int *)(unaff_gp + 0xec) + 1;
                *(int *)(unaff_gp + 0xe8) = *(int *)(unaff_gp + 0xe8) + -8;
                return iVar5;
            }
        }
        g_runtime_errno = 0xc;
    }
    return 0;
}

/* 原函数 0x81c1dd88 */
uint32_t sango_crt_heap_initialize(int param_1, int param_2)
{
    bool bVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    int unaff_gp;

    uVar2 = param_1 + 3U & 0xfffffffc;
    *(uint32_t *)(unaff_gp + 0xe4) = uVar2;
    uVar3 = param_2 + 3U & 0xfffffffc;
    *(uint32_t *)(unaff_gp + 0xe0) = uVar3;
    bVar1 = uVar3 < uVar2 + 0x10;
    if (!bVar1)
    {
        *(uint32_t *)(unaff_gp + 0xf0) = *(uint32_t *)(unaff_gp + 0xe4);
        *(int *)(unaff_gp + 0xe8) = *(int *)(unaff_gp + 0xe0) + -8;
        *(uint32_t *)(unaff_gp + 0xec) = 0;
    }
    return (uint32_t)bVar1;
}

/* 原函数 0x81c1de00 */
int sango_crt_abs(int param_1)
{
    if (param_1 < 0)
    {
        param_1 = -param_1;
    }
    return param_1;
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
char *sango_crt_strcat(char *param_1, char *param_2)
{
    char cVar1;
    char *pcVar2;
    char *pcVar3;

    pcVar2 = param_1;
    do
    {
        pcVar3 = pcVar2;
        pcVar2 = pcVar3 + 1;
    } while (*pcVar3 != '\0');
    pcVar3 = pcVar3 + -1;
    do
    {
        cVar1 = *param_2;
        param_2 = param_2 + 1;
        pcVar3 = pcVar3 + 1;
        *pcVar3 = cVar1;
    } while (cVar1 != '\0');
    return param_1;
}

/* 原函数 0x81c1deb0 */
void sango_crt_heap_shift_forward(uint32_t *param_1, int param_2)
{
    int iVar1;

    iVar1 = 0;
    if (0 < param_2)
    {
        do
        {
            param_1[-2] = *param_1;
            param_1[-1] = param_1[1];
            iVar1 = iVar1 + 1;
            param_1 = param_1 + 2;
        } while (iVar1 < param_2);
    }
    return;
}

/* 原函数 0x81c1dee0 */
void sango_crt_zero_bytes(uint8_t *param_1, int param_2)
{
    uint8_t *puVar1;
    int iVar2;

    iVar2 = 0;
    puVar1 = param_1;
    if (0 < param_2)
    {
        do
        {
            *puVar1 = 0;
            iVar2 = iVar2 + 1;
            puVar1 = param_1 + iVar2;
        } while (iVar2 < param_2);
    }
    return;
}

/* 原函数 0x81c1df08 */
void sango_crt_heap_shift_backward(uint32_t *param_1, int param_2)
{
    int iVar1;

    iVar1 = 0;
    if (0 < param_2)
    {
        do
        {
            *param_1 = param_1[-2];
            param_1[1] = param_1[-1];
            iVar1 = iVar1 + 1;
            param_1 = param_1 + -2;
        } while (iVar1 < param_2);
    }
    return;
}

#include "sango_internal.h"

/* 入口及旧版状态区初始化。 */

/* 原函数 0x81c00020 */
void bda_entry(void)
{
    bda_runtime_init();
    sango_main();
    return;
}

/* 原函数 0x81c00050 */
void bda_runtime_init(void)
{
    bda_memset((void *)0x81c2b0d0u, 0, 0x9a1u);
}

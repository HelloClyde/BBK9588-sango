#include "sango_internal.h"
__attribute__((section(".text.entry"))) int bda_main(void)
{
    bda_entry();
    return 0;
}

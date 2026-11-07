#include "sango_recovered.h"
#include "sango_credits.h"

static const unsigned char credits_bitmap[] = {
#include "sango_credits_bitmap.inc"
};

void sango_credits_draw(unsigned int target)
{
    FUN_81c15070(0,0,240,320,0,(byte *)credits_bitmap,target);
    FUN_81c14f98(target);
}

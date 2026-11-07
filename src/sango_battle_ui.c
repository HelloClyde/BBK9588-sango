#include "sango_recovered.h"
#include "sango_battle_ui.h"

void sango_battle_day_popup_draw(unsigned int day)
{
    byte *bitmap=(byte *)FUN_81c152f0(33,1,*(uint *)0x81c2b154u);
    unsigned int width,height,left,top,digits_width;
    char digits[12];
    if(!bitmap)return;
    width=(unsigned int)bitmap[0]+((unsigned int)bitmap[1]<<8);
    height=(unsigned int)bitmap[2]+((unsigned int)bitmap[3]<<8);
    if(!width || width>240 || height<12 || height>320)return;
    left=(240-width)/2;
    top=(320-height)/2;
    FUN_81c077bc(33,1,left,(short)top,1);
    FUN_81c0a7e4(day,digits,10);
    digits_width=bbk_strlen(digits)*6;
    if(digits_width>width)return;
    FUN_81c149dc((ushort)(left+(width-digits_width)/2),
                (ushort)(top+(height-12)/2),digits);
}

#include "sango_recovered.h"
#include "sango_statusbar.h"
#include "sango_credits.h"
#include "sango_battle_ui.h"

/* VA 0x81c00020; body bytes 36 */

void bda_entry(void)

{
  bda_runtime_init();
  sango_main();
  return;
}





void bda_runtime_init(void) { bda_memset((void *)0x81c2b0d0u, 0, 0x9a1u); }



#define DAT_81c2b18c (*(char *)(0x81c2b18cu))
#define DAT_81c2b264 (*(ushort *)(0x81c2b264u))
#define DAT_81c2b266 (*(ushort *)(0x81c2b266u))
/* VA 0x81c001a0; body bytes 276 */

void FUN_81c001a0(void)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  uint uVar4;

  uVar1 = bbk_rand();
  uVar4 = (int)uVar1 % 0x65 & 0xff;
  uVar1 = FUN_81c002b4('\0');
  if (uVar1 == 0) {
    DAT_81c2b18c = 2;
  }
  uVar2 = FUN_81c002b4('\x01');
  if (uVar2 < uVar1) {
    bVar3 = uVar4 < 0x1e;
    if (((uVar1 >> 1 & 0xffff) <= uVar2) && (bVar3 = uVar4 < 0x3c, DAT_81c2b266 < DAT_81c2b264)) {
      bVar3 = uVar4 < 0x28;
    }
    bVar3 = !bVar3;
  }
  else {
    bVar3 = uVar4 < 3;
    if (((uVar2 >> 1 & 0xffff) <= uVar1) && (bVar3 = uVar4 < 0x1f, DAT_81c2b264 <= DAT_81c2b266)) {
      bVar3 = uVar4 < 0xb;
    }
  }
  DAT_81c2b18c = '\x02' - bVar3;
  return;
}


#undef DAT_81c2b18c
#undef DAT_81c2b264
#undef DAT_81c2b266

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c002b4; body bytes 184 */

uint FUN_81c002b4(char param_1)

{
  byte bVar1;
  uint uVar2;
  byte bVar3;
  uint uVar4;

  uVar4 = 0;
  bVar3 = 0;
  bVar1 = param_1 * '\n';
  do {
    if ((&DAT_81c2b286)[(uint)bVar1 * 7] != '\b') {
      uVar2 = FUN_81c0036c((uint)bVar1);
      uVar4 = uVar4 + *(ushort *)(uVar2 * 0x10 + DAT_81c2b164 + 10) & 0xffff;
    }
    bVar3 = bVar3 + 1;
    bVar1 = bVar3 + param_1 * '\n';
  } while (bVar3 < 10);
  return uVar4;
}


#undef DAT_81c2b164
#undef DAT_81c2b286

#define DAT_81c2b268 (*(undefined1 *)(0x81c2b268u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c0036c; body bytes 76 */

uint FUN_81c0036c(uint param_1)

{
  uint uVar1;
  uint uVar2;

  uVar1 = param_1 & 0xff;
  uVar2 = 0xff;
  if ((uVar1 < 0x14) && ((&DAT_81c2b286)[uVar1 * 7] != '\b')) {
    uVar2 = (byte)(&DAT_81c2b268)[uVar1] - 1 & 0xff;
  }
  return uVar2;
}


#undef DAT_81c2b268
#undef DAT_81c2b286

#define DAT_81c2b14c (*(int *)(0x81c2b14cu))
#define DAT_81c2b284 (*(undefined1 *)(0x81c2b284u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c003b8; body bytes 416 */

void FUN_81c003b8(uint param_1)

{
  unsigned char sg_stack[76] __attribute__((aligned(8)));
#define abStack_50 (*(byte (*)[24])(sg_stack + 24))
#define local_68 (*(byte (*)[24])(sg_stack + 0))
#define local_38 (*(byte *)(sg_stack + 48))
#define local_37 (*(byte (*)[3])(sg_stack + 49))
#define local_34 (*(uint *)(sg_stack + 52))
#define local_30 (*(int *)(sg_stack + 56))

  byte bVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte *pbVar8;
  uint uVar9;

  uVar9 = param_1 & 0xff;
  FUN_81c00558(uVar9);
  local_30 = uVar9 << 3;
  FUN_81c00784(uVar9);
  local_68[0] = (&DAT_81c2b284)[local_30 - uVar9] * '\x10' - 0x10;
  local_34 = (uint)local_68[0];
  local_38 = 1;
  local_37[0] = 0;
  uVar5 = 1;
  iVar3 = DAT_81c2b14c;
  pbVar6 = local_68;
  pbVar7 = local_37;
  pbVar8 = abStack_50;
  do {
    uVar4 = 0;
    pbVar2 = pbVar6;
    if (uVar5 != 0) {
      do {
        if (1 < *(byte *)(iVar3 + (uint)*pbVar2)) {
          FUN_81c00b18((uint)*pbVar2,(int)pbVar8,pbVar7);
          iVar3 = DAT_81c2b14c;
        }
        uVar4 = uVar4 + 1 & 0xff;
        pbVar2 = pbVar6 + uVar4;
      } while (uVar4 < uVar5);
    }
    if (pbVar6 == local_68) {
      pbVar7 = &local_38;
      local_38 = 0;
      pbVar6 = abStack_50;
      pbVar8 = local_68;
      bVar1 = local_37[0];
    }
    else {
      local_37[0] = 0;
      pbVar6 = local_68;
      pbVar7 = local_37;
      pbVar8 = abStack_50;
      bVar1 = local_38;
    }
    uVar5 = (uint)bVar1;
  } while (uVar5 != 0);
  *(undefined1 *)(iVar3 + local_34) = 0;
  FUN_81c00870(uVar9);
  if ((&DAT_81c2b286)[local_30 - uVar9] == '\x04') {
    FUN_81c00954(uVar9);
  }
  return;
}


#undef DAT_81c2b14c
#undef DAT_81c2b284
#undef DAT_81c2b286
#undef abStack_50
#undef local_68
#undef local_38
#undef local_37
#undef local_34
#undef local_30

#define DAT_81c2b14c (*(void * *)(0x81c2b14cu))
#define DAT_81c2b184 (*(byte *)(0x81c2b184u))
#define DAT_81c2b117 (*(byte *)(0x81c2b117u))
#define DAT_81c2b262 (*(ushort *)(0x81c2b262u))
#define DAT_81c2b195 (*(undefined1 *)(0x81c2b195u))
#define DAT_81c2b162 (*(undefined1 *)(0x81c2b162u))
#define DAT_81c2b135 (*(undefined1 *)(0x81c2b135u))
#define DAT_81c2b134 (*(undefined1 *)(0x81c2b134u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
#define DAT_81c2b284 (*(undefined1 *)(0x81c2b284u))
/* VA 0x81c00558; body bytes 556 */

void FUN_81c00558(uint param_1)

{
  unsigned char sg_stack[20] __attribute__((aligned(8)));
#define local_30 (*(uint *)(sg_stack + 0))

  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;

  FUN_81c0a7c8(DAT_81c2b14c,0xff,0xe1);
  iVar1 = (param_1 & 0xff) * 7;
  uVar2 = (uint)(byte)(&DAT_81c2b284)[iVar1];
  uVar3 = (byte)(&DAT_81c2b280)[iVar1] + 1 & 0xff;
  uVar4 = (byte)(&DAT_81c2b281)[iVar1] + 1 & 0xff;
  if (uVar3 < uVar2) {
    local_30 = uVar2 - uVar3 & 0xff;
    uVar8 = 0;
  }
  else {
    uVar8 = uVar3 - uVar2 & 0xff;
    local_30 = 0;
  }
  if (uVar4 < uVar2) {
    uVar9 = uVar2 - uVar4 & 0xff;
    uVar7 = 0;
  }
  else {
    uVar7 = uVar4 - uVar2 & 0xff;
    uVar9 = 0;
  }
  uVar6 = uVar2 - local_30 & 0xff;
  if ((int)uVar2 < (int)(DAT_81c2b184 - uVar3)) {
    uVar6 = (uVar6 + uVar2) - 1;
  }
  else {
    uVar6 = uVar6 + (DAT_81c2b184 - uVar3);
  }
  uVar3 = uVar2 - uVar9 & 0xff;
  if ((int)uVar2 < (int)(DAT_81c2b117 - uVar4)) {
    uVar3 = (uVar3 + uVar2) - 1;
  }
  else {
    uVar3 = uVar3 + (DAT_81c2b117 - uVar4);
  }
  iVar1 = FUN_81c152f0((uint)DAT_81c2b262,'\x01',g_sango_package_data);
  uVar5 = 0;
  uVar4 = uVar7 * DAT_81c2b184 + uVar8;
  uVar2 = uVar9 * 0xf + local_30;
  if ((uVar3 & 0xff) != 0) {
    do {
      bbk_memcpy((void *)((int)DAT_81c2b14c + (uVar2 & 0xffff)),
                 (void *)(iVar1 + 0x10 + (uVar4 & 0xffff)),uVar6 & 0xff);
      uVar5 = uVar5 + 1 & 0xff;
      uVar4 = (uVar4 & 0xffff) + (uint)DAT_81c2b184;
      uVar2 = (uVar2 & 0xffff) + 0xf;
    } while (uVar5 < (uVar3 & 0xff));
  }
  DAT_81c2b195 = (char)uVar8;
  DAT_81c2b162 = (char)uVar7;
  DAT_81c2b135 = (char)uVar9;
  DAT_81c2b134 = (char)local_30;
  return;
}


#undef DAT_81c2b14c
#undef DAT_81c2b184
#undef DAT_81c2b117
#undef DAT_81c2b262
#undef DAT_81c2b195
#undef DAT_81c2b162
#undef DAT_81c2b135
#undef DAT_81c2b134
#undef DAT_81c2b280
#undef g_sango_package_data
#undef DAT_81c2b281
#undef DAT_81c2b284
#undef local_30

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b14c (*(int *)(0x81c2b14cu))
#define DAT_81c2b268 (*(undefined1 *)(0x81c2b268u))
#define DAT_81c2b284 (*(undefined1 *)(0x81c2b284u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c00784; body bytes 236 */

void FUN_81c00784(uint param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;

  uVar6 = param_1 & 0xff;
  bVar1 = *(byte *)((uint)(byte)(&DAT_81c2b268)[uVar6] * 0x10 + DAT_81c2b164 + -7);
  iVar2 = FUN_81c152f0(2,'\x03',g_sango_package_data);
  uVar5 = 0;
  do {
    pbVar4 = (byte *)(DAT_81c2b14c + uVar5);
    uVar3 = (uint)*pbVar4;
    uVar5 = uVar5 + 1 & 0xff;
    if (uVar3 != 0xff) {
      *pbVar4 = *(byte *)(iVar2 + (uint)bVar1 * 0x2e + uVar3);
    }
  } while (uVar5 < 0xe1);
  FUN_81c00954(uVar6);
  *(undefined1 *)(DAT_81c2b14c + (((byte)(&DAT_81c2b284)[uVar6 * 7] - 1) * 0x10 & 0xf0)) =
       (&DAT_81c2b284)[uVar6 * 7];
  return;
}


#undef DAT_81c2b164
#undef DAT_81c2b14c
#undef DAT_81c2b268
#undef DAT_81c2b284
#undef g_sango_package_data

#define DAT_81c2b134 (*(char *)(0x81c2b134u))
#define DAT_81c2b195 (*(char *)(0x81c2b195u))
#define DAT_81c2b162 (*(char *)(0x81c2b162u))
#define DAT_81c2b135 (*(char *)(0x81c2b135u))
#define DAT_81c2b14c (*(int *)(0x81c2b14cu))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c00870; body bytes 228 */

void FUN_81c00870(uint param_1)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  char cVar5;
  char cVar6;
  uint uVar7;
  uint uVar8;

  cVar6 = DAT_81c2b195 - DAT_81c2b134;
  uVar4 = 10;
  cVar5 = DAT_81c2b162 - DAT_81c2b135;
  if ((param_1 & 0xff) < 10) {
    uVar4 = 0;
  }
  uVar8 = uVar4 + 10;
  do {
    iVar1 = uVar4 * 7;
    if (((&DAT_81c2b286)[iVar1] != '\b') && ((param_1 & 0xff) != uVar4)) {
      bVar2 = (&DAT_81c2b280)[iVar1] - cVar6;
      bVar3 = (&DAT_81c2b281)[iVar1] - cVar5;
      if ((bVar2 < 0x10) &&
         ((bVar3 < 0x10 && (uVar7 = (uint)(byte)(bVar3 * '\x0f' + bVar2), uVar7 < 0xe1)))) {
        *(undefined1 *)(DAT_81c2b14c + uVar7) = 0xfe;
      }
    }
    uVar4 = uVar4 + 1 & 0xff;
  } while (uVar4 < uVar8);
  return;
}


#undef DAT_81c2b134
#undef DAT_81c2b195
#undef DAT_81c2b162
#undef DAT_81c2b135
#undef DAT_81c2b14c
#undef DAT_81c2b280
#undef DAT_81c2b281
#undef DAT_81c2b286

#define DAT_81c2b134 (*(char *)(0x81c2b134u))
#define DAT_81c2b195 (*(char *)(0x81c2b195u))
#define DAT_81c2b162 (*(char *)(0x81c2b162u))
#define DAT_81c2b135 (*(char *)(0x81c2b135u))
#define DAT_81c2b14c (*(int *)(0x81c2b14cu))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c00954; body bytes 452 */

void FUN_81c00954(uint param_1)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  char cVar5;
  char cVar6;
  uint uVar7;
  uint uVar8;

  cVar6 = DAT_81c2b195 - DAT_81c2b134;
  uVar4 = 10;
  if (9 < (param_1 & 0xff)) {
    uVar4 = 0;
  }
  cVar5 = DAT_81c2b162 - DAT_81c2b135;
  uVar8 = uVar4 + 10;
  do {
    iVar1 = uVar4 * 7;
    if ((&DAT_81c2b286)[iVar1] != '\b') {
      bVar2 = (&DAT_81c2b280)[iVar1] - cVar6;
      bVar3 = (&DAT_81c2b281)[iVar1] - cVar5;
      if ((((bVar2 < 0x10) && (bVar3 < 0x10)) &&
          (uVar7 = (uint)(byte)(bVar3 * '\x0f' + bVar2), uVar7 < 0xe1)) &&
         (*(undefined1 *)(DAT_81c2b14c + uVar7) = 0xfe,
         (&DAT_81c2b286)[(param_1 & 0xff) * 7] != '\x04')) {
        if ((bVar2 != 0) && (1 < uVar7)) {
          *(byte *)(DAT_81c2b14c + uVar7 + -1) = *(byte *)(DAT_81c2b14c + uVar7 + -1) | 0xa0;
        }
        if ((bVar2 < 0xe) && (uVar7 < 0xe0)) {
          *(byte *)(DAT_81c2b14c + uVar7 + 1) = *(byte *)(DAT_81c2b14c + uVar7 + 1) | 0xa0;
        }
        if ((bVar3 != 0) && (0xe < uVar7)) {
          *(byte *)(DAT_81c2b14c + uVar7 + -0xf) = *(byte *)(DAT_81c2b14c + uVar7 + -0xf) | 0xa0;
        }
        if ((bVar3 < 0xe) && (uVar7 < 0xd1)) {
          *(byte *)(DAT_81c2b14c + uVar7 + 0xf) = *(byte *)(DAT_81c2b14c + uVar7 + 0xf) | 0xa0;
        }
      }
    }
    uVar4 = uVar4 + 1 & 0xff;
  } while (uVar4 < uVar8);
  return;
}


#undef DAT_81c2b134
#undef DAT_81c2b195
#undef DAT_81c2b162
#undef DAT_81c2b135
#undef DAT_81c2b14c
#undef DAT_81c2b280
#undef DAT_81c2b281
#undef DAT_81c2b286

#define DAT_81c2b14c (*(int *)(0x81c2b14cu))
#define DAT_81c200a8 (*(undefined1 *)(0x81c200a8u))
/* VA 0x81c00b18; body bytes 228 */

void FUN_81c00b18(uint param_1,int param_2,byte *param_3)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  uint uVar4;
  undefined1 *puVar5;
  uint uVar6;
  uint uVar7;
  byte bVar8;
  uint uVar9;

  uVar9 = (uint)*param_3;
  bVar1 = *(byte *)(DAT_81c2b14c + (param_1 & 0xff));
  uVar7 = 0;
  do {
    uVar4 = (param_1 & 0xff) + (uint)(byte)(&DAT_81c200a8)[uVar7];
    uVar6 = uVar4 & 0xff;
    if ((((uVar6 < 0xe1) &&
         (bVar2 = *(byte *)(DAT_81c2b14c + uVar6), (char)*(byte *)(DAT_81c2b14c + uVar6) < '\0')) &&
        (bVar2 != 0xfe)) && (bVar2 != 0xff)) {
      if ((bVar2 < 0xa1) || (cVar3 = '\x01', bVar1 <= (byte)(bVar2 + 0x60))) {
        bVar8 = bVar1 + 0x80;
        cVar3 = bVar8 - bVar2;
        if (bVar8 <= bVar2) {
          cVar3 = '\0';
        }
        if (cVar3 == '\0') goto LAB_81c00b64;
      }
      puVar5 = (undefined1 *)(param_2 + uVar9);
      *(char *)(DAT_81c2b14c + uVar6) = cVar3;
      uVar9 = uVar9 + 1 & 0xff;
      *puVar5 = (char)uVar4;
    }
LAB_81c00b64:
    uVar7 = uVar7 + 1 & 0xff;
    if (3 < uVar7) {
      *param_3 = (byte)uVar9;
      return;
    }
  } while( true );
}


#undef DAT_81c2b14c
#undef DAT_81c200a8

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b18c (*(char *)(0x81c2b18cu))
#define DAT_81c1ffc0 (*(undefined *)(0x81c1ffc0u))
#define DAT_81c2b282 (*(undefined1 *)(0x81c2b282u))
#define DAT_81c2b283 (*(undefined1 *)(0x81c2b283u))
#define DAT_81c2b284 (*(undefined1 *)(0x81c2b284u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c00bfc; body bytes 660 */

void FUN_81c00bfc(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  char unaff_s6;

  uVar11 = 0;
  do {
    iVar6 = uVar11 * 7;
    (&DAT_81c2b286)[iVar6] = 0;
    if (uVar11 % 10 == 0) {
      unaff_s6 = '\0';
    }
    uVar7 = FUN_81c0036c(uVar11);
    if (uVar7 == 0xff) {
      unaff_s6 = unaff_s6 + '\x01';
      (&DAT_81c2b286)[iVar6] = 8;
      if (unaff_s6 == '\n') {
        DAT_81c2b18c = '\x02' - (char)(uVar11 / 10);
        return;
      }
    }
    else {
      iVar8 = DAT_81c2b164 + uVar7 * 0x10;
      bVar1 = *(byte *)(iVar8 + 3);
      bVar2 = *(byte *)(iVar8 + 4);
      bVar3 = *(byte *)(iVar8 + 2);
      bVar4 = *(byte *)(iVar8 + 8);
      uVar10 = 0;
      (&DAT_81c2b282)[iVar6] =
           (char)(((((uint)bVar1 * 0x50) / 100 + ((uint)bVar2 * 0x1e) / 100 + (uint)bVar3) *
                  (uint)bVar4) / 100);
      uVar7 = FUN_81c07cac((ushort)bVar1);
      (&DAT_81c2b283)[iVar6] =
           (char)(((((uint)bVar2 * 0x50) / 100 + (uVar7 >> 1 & 0xff) + (uint)bVar3) * (uint)bVar4) /
                 100);
      uVar7 = FUN_81c0036c(uVar11);
      iVar9 = DAT_81c2b164 + uVar7 * 0x10;
      (&DAT_81c2b284)[iVar6] = (&DAT_81c1ffc0)[*(byte *)(iVar9 + 9)];
      iVar8 = iVar9;
      do {
        bVar1 = *(byte *)(iVar8 + 0xc);
        if (bVar1 != 0) {
          iVar8 = FUN_81c152f0(0x42,'\x01',g_sango_package_data);
          iVar8 = iVar8 + (bVar1 - 1 & 0xffff) * 0x42;
          if ((iVar8 != 0) && (cVar5 = *(char *)(iVar8 + 0x40), cVar5 != '\0')) {
            (&DAT_81c2b284)[iVar6] = (&DAT_81c2b284)[iVar6] + cVar5;
          }
        }
        uVar10 = uVar10 + 1 & 0xff;
        iVar8 = uVar10 + iVar9;
      } while (uVar10 < 2);
      if (8 < (byte)(&DAT_81c2b284)[iVar6]) {
        (&DAT_81c2b284)[iVar6] = 8;
      }
    }
    uVar11 = uVar11 + 1 & 0xff;
  } while (uVar11 < 0x14);
  return;
}


#undef DAT_81c2b164
#undef DAT_81c2b18c
#undef DAT_81c1ffc0
#undef DAT_81c2b282
#undef DAT_81c2b283
#undef DAT_81c2b284
#undef DAT_81c2b286
#undef g_sango_package_data

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c1ffc0 (*(undefined *)(0x81c1ffc0u))
#define DAT_81c2b282 (*(undefined1 *)(0x81c2b282u))
#define DAT_81c2b283 (*(undefined1 *)(0x81c2b283u))
#define DAT_81c2b284 (*(undefined1 *)(0x81c2b284u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c00e90; body bytes 508 */

void FUN_81c00e90(uint param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;

  uVar10 = param_1 & 0xff;
  iVar6 = uVar10 * 7;
  uVar7 = FUN_81c0036c(uVar10);
  iVar8 = DAT_81c2b164 + uVar7 * 0x10;
  bVar1 = *(byte *)(iVar8 + 3);
  bVar2 = *(byte *)(iVar8 + 4);
  bVar3 = *(byte *)(iVar8 + 2);
  bVar4 = *(byte *)(iVar8 + 8);
  uVar11 = 0;
  (&DAT_81c2b282)[iVar6] =
       (char)(((((uint)bVar1 * 0x50) / 100 + ((uint)bVar2 * 0x1e) / 100 + (uint)bVar3) * (uint)bVar4
              ) / 100);
  uVar7 = FUN_81c07cac((ushort)bVar1);
  (&DAT_81c2b283)[iVar6] =
       (char)(((((uint)bVar2 * 0x50) / 100 + (uVar7 >> 1 & 0xff) + (uint)bVar3) * (uint)bVar4) / 100
             );
  uVar7 = FUN_81c0036c(uVar10);
  iVar9 = DAT_81c2b164 + uVar7 * 0x10;
  (&DAT_81c2b284)[iVar6] = (&DAT_81c1ffc0)[*(byte *)(iVar9 + 9)];
  iVar8 = iVar9;
  do {
    bVar1 = *(byte *)(iVar8 + 0xc);
    if (bVar1 != 0) {
      iVar8 = FUN_81c152f0(0x42,'\x01',g_sango_package_data);
      iVar8 = iVar8 + (bVar1 - 1 & 0xffff) * 0x42;
      if ((iVar8 != 0) && (cVar5 = *(char *)(iVar8 + 0x40), cVar5 != '\0')) {
        (&DAT_81c2b284)[iVar6] = (&DAT_81c2b284)[iVar6] + cVar5;
      }
    }
    uVar11 = uVar11 + 1 & 0xff;
    iVar8 = uVar11 + iVar9;
  } while (uVar11 < 2);
  if (8 < (byte)(&DAT_81c2b284)[iVar6]) {
    (&DAT_81c2b284)[iVar6] = 8;
  }
  return;
}


#undef DAT_81c2b164
#undef DAT_81c1ffc0
#undef DAT_81c2b282
#undef DAT_81c2b283
#undef DAT_81c2b284
#undef g_sango_package_data

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c1ffc0 (*(undefined *)(0x81c1ffc0u))
#define DAT_81c2b284 (*(undefined1 *)(0x81c2b284u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c0108c; body bytes 256 */

void FUN_81c0108c(uint param_1)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;

  iVar3 = (param_1 & 0xff) * 7;
  uVar4 = FUN_81c0036c(param_1 & 0xff);
  uVar6 = 0;
  iVar7 = DAT_81c2b164 + uVar4 * 0x10;
  (&DAT_81c2b284)[iVar3] = (&DAT_81c1ffc0)[*(byte *)(iVar7 + 9)];
  iVar5 = iVar7;
  do {
    bVar1 = *(byte *)(iVar5 + 0xc);
    if (bVar1 != 0) {
      iVar5 = FUN_81c152f0(0x42,'\x01',g_sango_package_data);
      iVar5 = iVar5 + (bVar1 - 1 & 0xffff) * 0x42;
      if ((iVar5 != 0) && (cVar2 = *(char *)(iVar5 + 0x40), cVar2 != '\0')) {
        (&DAT_81c2b284)[iVar3] = (&DAT_81c2b284)[iVar3] + cVar2;
      }
    }
    uVar6 = uVar6 + 1 & 0xff;
    iVar5 = uVar6 + iVar7;
  } while (uVar6 < 2);
  if (8 < (byte)(&DAT_81c2b284)[iVar3]) {
    (&DAT_81c2b284)[iVar3] = 8;
  }
  return;
}


#undef DAT_81c2b164
#undef DAT_81c1ffc0
#undef DAT_81c2b284
#undef g_sango_package_data

#define DAT_81c2b240 (*(short *)(0x81c2b240u))
#define DAT_81c2b256 (*(ushort *)(0x81c2b256u))
#define DAT_81c2b23c (*(ushort * *)(0x81c2b23cu))
#define DAT_81c2b237 (*(byte *)(0x81c2b237u))
#define DAT_81c2b24b (*(byte *)(0x81c2b24bu))
#define DAT_81c20c48 (*(uint *)(0x81c20c48u))
/* VA 0x81c0118c; body bytes 236 */

uint FUN_81c0118c(void)

{
  uint uVar1;
  uint uVar2;

  uVar2 = (uint)DAT_81c2b240;
  uVar1 = FUN_81c1e6b0(uVar2);
  if ((int)uVar2 < 0) {
    uVar1 = soft_float_add(uVar1,DAT_81c20c48);
  }
  uVar2 = FUN_81c1e6b0((uint)DAT_81c2b256);
  uVar1 = soft_float_div(uVar1,uVar2);
  uVar2 = FUN_81c1e6b0((uint)(*DAT_81c2b23c >> 3));
  uVar1 = soft_float_mul(uVar1,uVar2);
  uVar1 = FUN_81c1df40(uVar1);
  uVar1 = FUN_81c1e6b0(uVar1 & 0xffff);
  uVar1 = soft_float_mul(uVar1,*(uint *)(((uint)DAT_81c2b237 * 6 + (uint)DAT_81c2b24b) * 4 +
                                        -0x7e3e0038));
  uVar1 = FUN_81c1df40(uVar1);
  return uVar1 + 10 & 0xffff;
}


#undef DAT_81c2b240
#undef DAT_81c2b256
#undef DAT_81c2b23c
#undef DAT_81c2b237
#undef DAT_81c2b24b
#undef DAT_81c20c48

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c20058 (*(undefined *)(0x81c20058u))
#define DAT_81c20070 (*(undefined *)(0x81c20070u))
#define DAT_81c20088 (*(undefined *)(0x81c20088u))
#define DAT_81c2b230 (*(undefined4 *)(0x81c2b230u))
#define DAT_81c2b234 (*(undefined1 *)(0x81c2b234u))
#define DAT_81c2b235 (*(undefined1 *)(0x81c2b235u))
#define DAT_81c2b236 (*(undefined *)(0x81c2b236u))
#define DAT_81c2b237 (*(undefined1 *)(0x81c2b237u))
#define DAT_81c2b238 (*(undefined4 *)(0x81c2b238u))
#define DAT_81c2b23c (*(undefined4 *)(0x81c2b23cu))
#define DAT_81c2b240 (*(undefined2 *)(0x81c2b240u))
#define DAT_81c2b242 (*(undefined2 *)(0x81c2b242u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c01278; body bytes 436 */

void FUN_81c01278(uint param_1,uint param_2)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;

  uVar7 = param_1 & 0xff;
  uVar3 = FUN_81c0036c(param_2 & 0xff);
  iVar6 = uVar7 * 0x14;
  iVar5 = (param_2 & 0xff) * 7;
  if (uVar3 < 200) {
    bVar1 = (&DAT_81c2b281)[iVar5];
    bVar2 = (&DAT_81c2b280)[iVar5];
    iVar8 = DAT_81c2b164 + uVar3 * 0x10;
    (&DAT_81c2b230)[uVar7 * 5] = iVar8 + 2;
    (&DAT_81c2b234)[iVar6] = *(char *)(iVar8 + 4) + *(char *)(iVar8 + 2) + '\x05';
    iVar4 = FUN_81c0620c((uint)bVar2,(uint)bVar1);
    (&DAT_81c2b235)[iVar6] = (char)iVar4;
    (&DAT_81c2b236)[iVar6] = 0;
    iVar5 = g_sango_package_data;
    bVar1 = *(byte *)(iVar8 + 9);
    (&DAT_81c2b238)[uVar7 * 5] = iVar8 + 7;
    (&DAT_81c2b237)[iVar6] = bVar1;
    (&DAT_81c2b23c)[uVar7 * 5] = iVar8 + 10;
    iVar5 = FUN_81c152f0(2,'\x04',iVar5);
    iVar6 = (uint)bVar1 * 4;
    uVar9 = (uint)*(byte *)(iVar5 + (uint)bVar1 * 8 + iVar4);
    uVar3 = FUN_81c1e6b0((uint)*(byte *)(iVar8 + 3) * (*(byte *)(iVar8 + 2) + 10));
    uVar3 = soft_float_mul(uVar3,*(uint *)(&DAT_81c20058 + iVar6));
    uVar3 = FUN_81c1df40(uVar3);
    (&DAT_81c2b240)[uVar7 * 10] = (short)((int)(uVar3 & 0xffff) >> (uVar9 & 0x1f));
    uVar3 = FUN_81c1e6b0((uint)*(byte *)(iVar8 + 4) * (*(byte *)(iVar8 + 2) + 10));
    uVar3 = soft_float_mul(uVar3,*(uint *)(&DAT_81c20070 + iVar6));
    uVar3 = FUN_81c1df40(uVar3);
    uVar3 = FUN_81c1e6b0((int)(uVar3 & 0xffff) >> (uVar9 & 0x1f) & 0xffff);
    uVar3 = soft_float_mul(uVar3,*(uint *)(&DAT_81c20088 + iVar4 * 4));
    uVar3 = FUN_81c1df40(uVar3);
    (&DAT_81c2b242)[uVar7 * 10] = (short)uVar3;
  }
  return;
}


#undef DAT_81c2b164
#undef DAT_81c20058
#undef DAT_81c20070
#undef DAT_81c20088
#undef DAT_81c2b230
#undef DAT_81c2b234
#undef DAT_81c2b235
#undef DAT_81c2b236
#undef DAT_81c2b237
#undef DAT_81c2b238
#undef DAT_81c2b23c
#undef DAT_81c2b240
#undef DAT_81c2b242
#undef DAT_81c2b280
#undef DAT_81c2b281
#undef g_sango_package_data

#define DAT_81c2b264 (*(undefined2 *)(0x81c2b264u))
#define DAT_81c2b266 (*(undefined2 *)(0x81c2b266u))
/* VA 0x81c0142c; body bytes 144 */

void FUN_81c0142c(void)

{
  uint uVar1;
  ushort *puVar2;
  byte bVar3;

  bVar3 = 0;
  do {
    uVar1 = FUN_81c002b4(bVar3);
    uVar1 = FUN_81c07cac((ushort)uVar1);
    puVar2 = &DAT_81c2b266;
    if (bVar3 == 0) {
      puVar2 = &DAT_81c2b264;
    }
    uVar1 = uVar1 / 3 & 0xff;
    if (*puVar2 < uVar1) {
      *puVar2 = 0;
    }
    else {
      *puVar2 = *puVar2 - (short)uVar1;
    }
    bVar3 = bVar3 + 1;
  } while (bVar3 < 2);
  return;
}


#undef DAT_81c2b264
#undef DAT_81c2b266


/* VA 0x81c014bc; body bytes 48 */

uint FUN_81c014bc(ushort *param_1,ushort param_2)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;

  uVar1 = *param_1;
  uVar3 = (uint)param_2;
  uVar2 = uVar1 - param_2;
  if (uVar1 <= uVar3) {
    uVar2 = 0;
    uVar3 = (uint)uVar1;
  }
  *param_1 = uVar2;
  return uVar3;
}





/* VA 0x81c014ec; body bytes 56 */

uint FUN_81c014ec(ushort *param_1,uint param_2,ushort param_3)

{
  uint uVar1;
  uint uVar2;

  uVar1 = param_2 & 0xffff;
  uVar2 = *param_1 + uVar1;
  if (param_3 < uVar2) {
    uVar1 = (uint)param_3 - (uint)*param_1 & 0xffff;
  }
  else {
    param_3 = (ushort)uVar2;
  }
  *param_1 = param_3;
  return uVar1;
}




#define DAT_81c2b235 (*(byte *)(0x81c2b235u))
#define DAT_81c2b17d (*(byte *)(0x81c2b17du))
#define DAT_81c2b24b (*(byte *)(0x81c2b24bu))
#define DAT_81c2b249 (*(byte *)(0x81c2b249u))
#define DAT_81c20c50 (*(uint *)(0x81c20c50u))
#define DAT_81c20c4c (*(uint *)(0x81c20c4cu))
/* VA 0x81c01524; body bytes 632 */

void FUN_81c01524(int param_1,ushort *param_2,undefined2 *param_3)

{
  unsigned char sg_stack[32] __attribute__((aligned(8)));
#define local_38 (*(ushort (*)[4])(sg_stack + 0))
#define local_30 (*(uint *)(sg_stack + 8))
#define local_2c (*(uint *)(sg_stack + 12))

  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;

  uVar1 = (uint)DAT_81c2b17d;
  local_2c = (uint)DAT_81c2b235;
  uVar8 = (uint)DAT_81c2b249;
  local_30 = (uint)DAT_81c2b24b;
  local_38[0] = *(ushort *)(param_1 + 2);
  local_38[1] = *(undefined2 *)(param_1 + 4);
  uVar7 = 0;
  iVar2 = 0;
  do {
    uVar4 = (uint)*(ushort *)((int)local_38 + iVar2);
    if (uVar4 != 0) {
      uVar4 = FUN_81c1e6b0(uVar4);
      uVar5 = (uint)*(char *)(uVar1 + param_1 + 6);
      uVar3 = FUN_81c1e6b0(uVar5);
      if ((int)uVar5 < 0) {
        uVar3 = soft_float_add(uVar3,DAT_81c20c4c);
      }
      uVar5 = DAT_81c20c50;
      uVar3 = soft_float_div(uVar3,DAT_81c20c50);
      uVar4 = soft_float_mul(uVar4,uVar3);
      uVar4 = FUN_81c1df40(uVar4);
      uVar4 = FUN_81c1e6b0(uVar4 & 0xffff);
      uVar6 = (uint)*(char *)(local_30 + param_1 + 0x1c);
      uVar3 = FUN_81c1e6b0(uVar6);
      if ((int)uVar6 < 0) {
        uVar3 = soft_float_add(uVar3,DAT_81c20c4c);
      }
      uVar3 = soft_float_div(uVar3,uVar5);
      uVar4 = soft_float_mul(uVar4,uVar3);
      uVar4 = FUN_81c1df40(uVar4);
      uVar4 = FUN_81c1e6b0(uVar4 & 0xffff);
      uVar6 = (uint)*(char *)(uVar8 + param_1 + 0xc);
      uVar3 = FUN_81c1e6b0(uVar6);
      if ((int)uVar6 < 0) {
        uVar3 = soft_float_add(uVar3,DAT_81c20c4c);
      }
      uVar3 = soft_float_div(uVar3,uVar5);
      uVar4 = soft_float_mul(uVar4,uVar3);
      uVar4 = FUN_81c1df40(uVar4);
      uVar4 = FUN_81c1e6b0(uVar4 & 0xffff);
      uVar5 = (uint)*(char *)(local_2c + param_1 + 0x14);
      uVar3 = FUN_81c1e6b0(uVar5);
      if ((int)uVar5 < 0) {
        uVar3 = soft_float_add(uVar3,DAT_81c20c4c);
      }
      uVar3 = soft_float_div(uVar3,DAT_81c20c50);
      uVar4 = soft_float_mul(uVar4,uVar3);
      uVar4 = FUN_81c1df40(uVar4);
      *(ushort *)((int)local_38 + iVar2) = (ushort)uVar4;
    }
    uVar7 = uVar7 + 1 & 0xff;
    iVar2 = uVar7 << 1;
  } while (uVar7 < 2);
  *param_2 = local_38[0];
  *param_3 = local_38[1];
  return;
}


#undef DAT_81c2b235
#undef DAT_81c2b17d
#undef DAT_81c2b24b
#undef DAT_81c2b249
#undef DAT_81c20c50
#undef DAT_81c20c4c
#undef local_38
#undef local_30
#undef local_2c

#define DAT_81c2b114 (*(char *)(0x81c2b114u))
#define DAT_81c2b171 (*(char *)(0x81c2b171u))
#define DAT_81c2b128 (*(uint *)(0x81c2b128u))
/* VA 0x81c017a0; body bytes 272 */

uint FUN_81c017a0(undefined1 *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;

  uVar1 = FUN_81c02664();
  if (uVar1 != 0xff) {
    param_1[2] = (char)uVar1;
    FUN_81c003b8(uVar1);
    if (DAT_81c2b114 != '\0') {
      FUN_81c04468(uVar1);
      FUN_81c027f0();
      FUN_81c04590(uVar1,1);
      FUN_81c14f98(DAT_81c2b128);
      if (DAT_81c2b171 != '\0') {
        FUN_81c14164(0x32,'\0');
      }
    }
    FUN_81c01b68(uVar1);
    if ((DAT_81c2b114 != '\0') && (FUN_81c04468(uVar1), DAT_81c2b171 != '\0')) {
      FUN_81c14164(0x32,'\0');
    }
    iVar2 = FUN_81c018b0(param_1);
    if ((iVar2 == 0) && (uVar3 = FUN_81c01af0(param_1), uVar3 == 0)) {
      *param_1 = 3;
    }
  }
  return uVar1;
}


#undef DAT_81c2b114
#undef DAT_81c2b171
#undef DAT_81c2b128

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b268 (*(undefined1 *)(0x81c2b268u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c018b0; body bytes 576 */

undefined4 FUN_81c018b0(undefined1 *param_1)

{
  unsigned char sg_stack[32] __attribute__((aligned(8)));
#define abStack_30 (*(byte (*)[16])(sg_stack + 0))

  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;

  uVar6 = (uint)(byte)param_1[2];
  if ((&DAT_81c2b286)[uVar6 * 7] != '\x02') {
    uVar2 = FUN_81c02f30(uVar6);
    iVar7 = DAT_81c2b164 + uVar2 * 0x10;
    uVar3 = bbk_rand();
    if ((uVar3 & 0xffff) % 0x96 <= (uint)*(byte *)(iVar7 + 4)) {
      if (*(char *)(iVar7 + 9) != '\x05') {
        uVar4 = FUN_81c07e10(uVar2);
        uVar5 = uVar4 + (uVar4 >> 1) & 0xffff;
        uVar4 = bbk_rand();
        if (uVar5 == 0) {
          trap(7);
        }
        if ((int)uVar4 % (int)uVar5 < (int)(uint)*(ushort *)(iVar7 + 10)) {
          return 0;
        }
      }
      FUN_81c0205c(uVar2,(char *)abStack_30);
      uVar2 = FUN_81c1b9d4((char *)abStack_30);
      if (uVar2 == 0) {
        trap(7);
      }
      bVar1 = abStack_30[(uVar3 & 0xffff) % uVar2 & 0xff];
      uVar2 = (uint)bVar1;
      iVar7 = FUN_81c01fbc(uVar2,uVar6);
      if (iVar7 == 0) {
        FUN_81c02524('\x01',uVar2,uVar6);
        uVar6 = 0;
        iVar7 = 0;
        do {
          iVar7 = iVar7 - uVar6;
          if ((&DAT_81c2b286)[iVar7] != '\b') {
            uVar3 = FUN_81c02444((uint)(byte)(&DAT_81c2b280)[iVar7],
                                 (uint)(byte)(&DAT_81c2b281)[iVar7]);
            if ((uVar3 != 0) && (iVar7 = FUN_81c02244(uVar2,9 < uVar6,uVar6), iVar7 != 0)) {
              if ((uVar2 != 0x11) && (uVar2 != 0x1d)) {
                param_1[1] = bVar1;
                *param_1 = 1;
                param_1[3] = (char)uVar6;
                return 1;
              }
              FUN_81c07e10((byte)(&DAT_81c2b268)[uVar6] - 1 & 0xff);
            }
          }
          uVar6 = uVar6 + 1 & 0xff;
          iVar7 = uVar6 << 3;
        } while (uVar6 < 0x14);
      }
    }
  }
  return 0;
}


#undef DAT_81c2b164
#undef DAT_81c2b268
#undef DAT_81c2b280
#undef DAT_81c2b281
#undef DAT_81c2b286
#undef abStack_30


/* VA 0x81c01af0; body bytes 120 */

uint FUN_81c01af0(undefined1 *param_1)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
#define local_18 (*(char (*)[2])(sg_stack + 0))
#define auStack_16 (*(undefined2 (*)[3])(sg_stack + 2))

  byte bVar1;

  bVar1 = param_1[2];
  FUN_81c02524('\0',0,(uint)bVar1);
  FUN_81c01278(0,(uint)bVar1);
  FUN_81c02354(auStack_16,local_18);
  if (local_18[0] != -1) {
    param_1[3] = local_18[0];
    *param_1 = 0;
  }
  return (uint)(local_18[0] != -1);
}


#undef local_18
#undef auStack_16

#define DAT_81c2b134 (*(byte *)(0x81c2b134u))
#define DAT_81c2b135 (*(byte *)(0x81c2b135u))
#define DAT_81c2b14c (*(int *)(0x81c2b14cu))
#define DAT_81c2b195 (*(byte *)(0x81c2b195u))
#define DAT_81c2b162 (*(byte *)(0x81c2b162u))
#define DAT_81c2b260 (*(char *)(0x81c2b260u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
/* VA 0x81c01b68; body bytes 780 */

void FUN_81c01b68(uint param_1)

{
  unsigned char sg_stack[44] __attribute__((aligned(8)));
#define local_38 (*(uint *)(sg_stack + 16))
#define local_34 (*(uint *)(sg_stack + 20))
#define local_30 (*(int *)(sg_stack + 24))
#define auStack_46 (*(undefined1 (*)[2])(sg_stack + 2))
#define local_48 (*(byte *)(sg_stack + 0))
#define local_47 (*(byte *)(sg_stack + 1))
#define local_44 (*(ushort (*)[2])(sg_stack + 4))
#define local_40 (*(uint *)(sg_stack + 8))
#define local_3c (*(uint *)(sg_stack + 12))

  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  byte bVar11;
  byte bVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint index;
  ushort uVar16;
  byte bVar17;
  uint uVar18;

  index = param_1 & 0xff;
  uVar3 = FUN_81c02314(index);
  if (uVar3 != 5) {
    local_30 = index << 3;
    FUN_81c0272c(&local_48,&local_47);
    uVar16 = 0;
    local_3c = (uint)(byte)(&DAT_81c2b281)[local_30 - index];
    local_40 = (uint)(byte)(&DAT_81c2b280)[local_30 - index];
    FUN_81c02f30(index);
    local_38 = 0xff;
    bVar17 = (byte)local_3c;
    local_34 = local_40;
    uVar18 = local_3c;
    for (uVar3 = (uint)DAT_81c2b134; uVar3 < 0xf; uVar3 = uVar3 + 1 & 0xff) {
      for (uVar13 = (uint)DAT_81c2b135; bVar17 = (byte)uVar18, uVar13 < 0xf;
          uVar13 = uVar13 + 1 & 0xff) {
        if (-1 < *(char *)(DAT_81c2b14c + uVar13 * 0xf + uVar3)) {
          uVar10 = (uint)DAT_81c2b195 + (uVar3 - DAT_81c2b134);
          uVar4 = (uint)DAT_81c2b162 + (uVar13 - DAT_81c2b135);
          uVar15 = uVar10 & 0xff;
          uVar14 = uVar4 & 0xff;
          iVar5 = FUN_81c0620c(uVar15,uVar14);
          bVar11 = (byte)uVar10;
          bVar12 = (byte)uVar4;
          if ((DAT_81c2b260 == '\0') && (iVar5 == 5)) {
            (&DAT_81c2b281)[local_30 - index] = bVar12;
            (&DAT_81c2b280)[local_30 - index] = bVar11;
            FUN_81c04468(index);
            return;
          }
          uVar6 = FUN_81c027a0(bVar11,bVar12,local_48,local_47);
          FUN_81c024a0(index,bVar11,bVar12);
          FUN_81c02354(local_44,auStack_46);
          uVar1 = local_44[0];
          uVar4 = uVar14;
          uVar10 = uVar6;
          uVar2 = uVar15;
          if (uVar16 == 0) {
            if (((local_44[0] == 0) && (local_38 <= uVar6)) &&
               (uVar4 = uVar18, uVar10 = local_38, uVar2 = local_34, local_38 == uVar6)) {
              uVar4 = bbk_rand();
              uVar7 = (int)uVar4 % 10 & 0xff;
              uVar16 = uVar1;
LAB_81c01dc8:
              uVar4 = uVar14;
              uVar10 = uVar6;
              uVar2 = uVar15;
              if (uVar7 == 0) goto LAB_81c01d0c;
            }
          }
          else {
            if (local_44[0] < uVar16) goto LAB_81c01d0c;
            if ((local_44[0] <= uVar16) && (4 < (iVar5 - 2U & 0xff))) {
              uVar8 = FUN_81c027a0(bVar11,bVar12,(byte)local_40,(byte)local_3c);
              uVar9 = FUN_81c027a0((byte)local_34,bVar17,(byte)local_40,(byte)local_3c);
              uVar7 = 0;
              if (uVar8 <= uVar9) goto LAB_81c01dc8;
            }
          }
          local_34 = uVar2;
          local_38 = uVar10;
          uVar18 = uVar4;
          uVar16 = local_44[0];
        }
LAB_81c01d0c:
      }
    }
    if (local_38 != 0xff) {
      (&DAT_81c2b281)[local_30 - index] = bVar17;
      (&DAT_81c2b280)[local_30 - index] = (char)local_34;
    }
  }
  return;
}


#undef DAT_81c2b134
#undef DAT_81c2b135
#undef DAT_81c2b14c
#undef DAT_81c2b195
#undef DAT_81c2b162
#undef DAT_81c2b260
#undef DAT_81c2b280
#undef DAT_81c2b281
#undef local_38
#undef local_34
#undef local_30
#undef auStack_46
#undef local_48
#undef local_47
#undef local_44
#undef local_40
#undef local_3c


/* VA 0x81c01e74; body bytes 328 */

uint FUN_81c01e74(uint param_1,ushort *param_2,byte *param_3)

{
  unsigned char sg_stack[32] __attribute__((aligned(8)));
#define acStack_30 (*(char (*)[16])(sg_stack + 0))

  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  uint uVar4;
  ushort uVar5;

  uVar4 = FUN_81c02f30(param_1 & 0xff);
  FUN_81c0205c(uVar4,(char *)param_3);
  FUN_81c021d4(param_3);
  uVar4 = bbk_strlen((char *)(param_3 + 0xb));
  uVar2 = param_2[2];
  uVar3 = *param_2;
  uVar5 = uVar2 + 4;
  uVar4 = uVar4 >> 2 & 0xff;
  *param_2 = uVar3 + 4;
  param_2[2] = uVar5;
  if (0xd3 < uVar5) {
    *param_2 = uVar3 - 0x14;
    param_2[2] = uVar2 - 0x14;
  }
  uVar2 = param_2[1];
  param_2[3] = param_2[3] - 6;
  param_2[1] = uVar2 + 6;
  if (uVar4 < 3) {
    param_2[3] = uVar2 + 6 + (short)uVar4 * 0xc;
  }
  while( true ) {
    uVar4 = FUN_81c07068(param_2,0,(char *)(param_3 + 0xb));
    if (uVar4 == 0xff) {
      return 0xff;
    }
    bVar1 = param_3[uVar4];
    uVar4 = FUN_81c01fbc((uint)bVar1,param_1 & 0xff);
    if (uVar4 == 0) break;
    FUN_81c02f08(uVar4,acStack_30);
    FUN_81c149dc(0x6a,0xf3,acStack_30);
  }
  return (uint)bVar1;
}


#undef acStack_30

#define DAT_81c2b17d (*(byte *)(0x81c2b17du))
#define DAT_81c2b283 (*(undefined1 *)(0x81c2b283u))
/* VA 0x81c01fbc; body bytes 160 */

undefined4 FUN_81c01fbc(uint param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;

  uVar1 = FUN_81c02314(param_2 & 0xff);
  iVar2 = FUN_81c062d0(param_1 & 0xff);
  uVar3 = 6;
  if (((*(byte *)(iVar2 + 6) <= (byte)(&DAT_81c2b283)[(param_2 & 0xff) * 7]) &&
      (uVar3 = 5, *(char *)(uVar1 + iVar2 + 0x14) != '\0')) &&
     (uVar3 = 4, *(char *)((uint)DAT_81c2b17d + iVar2 + 6) != '\0')) {
    uVar3 = 0;
  }
  return uVar3;
}


#undef DAT_81c2b17d
#undef DAT_81c2b283

#define DAT_81c2b161 (*(char *)(0x81c2b161u))
#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c20c54 (*(uint *)(0x81c20c54u))
#define DAT_81c20c58 (*(uint *)(0x81c20c58u))
#define DAT_81c20c4c (*(uint *)(0x81c20c4cu))
#define DAT_81c200bc (*(undefined *)(0x81c200bcu))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c0205c; body bytes 376 */

void FUN_81c0205c(uint param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  uint right;
  uint uVar3;
  uint uVar4;
  int iVar5;

  FUN_81c0a7c8(param_2,0,0xb);
  uVar3 = param_1 & 0xff;
  iVar2 = FUN_81c152f0(0xe,DAT_81c2b161,g_sango_package_data);
  if (*(char *)(iVar2 + uVar3) != '\0') {
    *param_2 = *(char *)(iVar2 + uVar3);
    param_2 = param_2 + 1;
  }
  if ((uint)*(byte *)(uVar3 * 0x10 + DAT_81c2b164 + 1) == uVar3 + 1) {
    *param_2 = '\x1e';
    param_2 = param_2 + 1;
  }
  iVar2 = FUN_81c152f0(2,'\x02',g_sango_package_data);
  iVar5 = uVar3 * 0x10 + DAT_81c2b164;
  uVar4 = (uint)*(byte *)(iVar5 + 9);
  cVar1 = (&DAT_81c200bc)[uVar4];
  uVar3 = FUN_81c1e6b0((int)cVar1);
  if (cVar1 < 0) {
    uVar3 = soft_float_add(uVar3,DAT_81c20c4c);
  }
  right = FUN_81c1e6b0((uint)*(byte *)(iVar5 + 2));
  uVar3 = soft_float_mul(uVar3,right);
  uVar3 = soft_float_div(uVar3,DAT_81c20c54);
  uVar3 = soft_float_add(uVar3,DAT_81c20c58);
  uVar3 = FUN_81c1df40(uVar3);
  bbk_memcpy(param_2,(void *)(iVar2 + uVar4 * 10),uVar3 & 0xff);
  return;
}


#undef DAT_81c2b161
#undef DAT_81c2b164
#undef DAT_81c20c54
#undef DAT_81c20c58
#undef DAT_81c20c4c
#undef DAT_81c200bc
#undef g_sango_package_data


/* VA 0x81c021d4; body bytes 112 */

void FUN_81c021d4(byte *param_1)

{
  byte *pbVar1;
  byte *pbVar2;
  uint uVar3;

  uVar3 = 0;
  pbVar1 = param_1;
  pbVar2 = param_1 + 0xb;
  do {
    if (*pbVar1 == 0) {
      return;
    }
    FUN_81c154d8(0xb,(uint)*pbVar1,pbVar2);
    uVar3 = uVar3 + 1 & 0xff;
    pbVar1 = param_1 + uVar3;
    pbVar2 = pbVar2 + 4;
  } while (uVar3 < 10);
  return;
}




#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b268 (*(undefined1 *)(0x81c2b268u))
/* VA 0x81c02244; body bytes 208 */

undefined4 FUN_81c02244(uint param_1,char param_2,uint param_3)

{
  byte bVar1;
  uint uVar2;
  char *pcVar3;
  undefined4 uVar4;

  bVar1 = *(byte *)((uint)(byte)(&DAT_81c2b268)[param_3 & 0xff] * 0x10 + DAT_81c2b164 + -7);
  uVar2 = FUN_81c02314(param_3 & 0xff);
  pcVar3 = (char *)FUN_81c062d0(param_1 & 0xff);
  uVar4 = 0;
  if ((((pcVar3[bVar1 + 0x1c] != '\0') && (pcVar3[uVar2 + 0xc] != '\0')) &&
      ((*pcVar3 != '\x01' || (param_2 != '\0')))) && ((*pcVar3 != '\0' || (param_2 == '\0')))) {
    uVar4 = 1;
  }
  return uVar4;
}


#undef DAT_81c2b164
#undef DAT_81c2b268

#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
/* VA 0x81c02314; body bytes 64 */

uint FUN_81c02314(uint index)

{
  int iVar1;
  uint uVar2;

  iVar1 = (index & 0xff) * 7;
  uVar2 = FUN_81c0620c((uint)(byte)(&DAT_81c2b280)[iVar1],(uint)(byte)(&DAT_81c2b281)[iVar1]);
  return uVar2;
}


#undef DAT_81c2b280
#undef DAT_81c2b281

#define DAT_81c2b126 (*(byte *)(0x81c2b126u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c02354; body bytes 240 */

void FUN_81c02354(undefined2 *param_1,undefined1 *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;

  uVar5 = 0xff;
  uVar4 = 0;
  uVar3 = 0;
  iVar1 = 0;
  do {
    iVar1 = iVar1 - uVar3;
    if (((&DAT_81c2b286)[iVar1] != '\b') &&
       (uVar2 = FUN_81c02444((uint)(byte)(&DAT_81c2b280)[iVar1],(uint)(byte)(&DAT_81c2b281)[iVar1]),
       uVar2 != 0)) {
      if (DAT_81c2b126 == uVar3) {
        uVar4 = 0xffff;
        uVar5 = uVar3;
        break;
      }
      FUN_81c01278(1,uVar3);
      uVar2 = FUN_81c0118c();
      if (uVar4 < uVar2) {
        uVar4 = uVar2;
        uVar5 = uVar3;
      }
    }
    uVar3 = uVar3 + 1 & 0xff;
    iVar1 = uVar3 << 3;
  } while (uVar3 < 10);
  *param_1 = (short)uVar4;
  *param_2 = (char)uVar5;
  return;
}


#undef DAT_81c2b126
#undef DAT_81c2b280
#undef DAT_81c2b281
#undef DAT_81c2b286

#define DAT_81c2b15c (*(byte * *)(0x81c2b15cu))
/* VA 0x81c02444; body bytes 92 */

uint FUN_81c02444(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;

  uVar4 = (uint)*DAT_81c2b15c;
  uVar3 = param_2 - (uint)DAT_81c2b15c[2] & 0xff;
  uVar2 = param_1 - (uint)DAT_81c2b15c[1] & 0xff;
  uVar1 = 0;
  if ((uVar3 < uVar4) && (uVar2 < uVar4)) {
    uVar1 = (uint)(DAT_81c2b15c[uVar2 + uVar3 * uVar4 + 3] == 1);
  }
  return uVar1;
}


#undef DAT_81c2b15c

#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
/* VA 0x81c024a0; body bytes 132 */

void FUN_81c024a0(uint param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined1 *puVar4;
  uint uVar5;

  uVar5 = param_1 & 0xff;
  iVar3 = uVar5 * 7;
  puVar4 = &DAT_81c2b280 + iVar3;
  uVar1 = *puVar4;
  uVar2 = (&DAT_81c2b281)[iVar3];
  *puVar4 = param_2;
  (&DAT_81c2b281)[iVar3] = param_3;
  FUN_81c01278(0,uVar5);
  FUN_81c02524('\0',0,uVar5);
  (&DAT_81c2b281)[iVar3] = uVar2;
  *puVar4 = uVar1;
  return;
}


#undef DAT_81c2b280
#undef DAT_81c2b281

#define DAT_81c2b15c (*(undefined1 * *)(0x81c2b15cu))
#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b268 (*(undefined1 *)(0x81c2b268u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c02524; body bytes 320 */

void FUN_81c02524(char param_1,uint param_2,uint param_3)

{
  char cVar1;
  int iVar2;
  uint in_t0;
  char in_t1;
  uint unaff_s1;
  uint unaff_s2;

  if (param_1 == '\0') {
    in_t0 = 2;
    in_t1 = '\x01';
    unaff_s1 = 5;
    unaff_s2 = (uint)*(byte *)((uint)(byte)(&DAT_81c2b268)[param_3 & 0xff] * 0x10 + DAT_81c2b164 +
                              -7) * 0x19;
  }
  else if (param_1 == '\x01') {
    unaff_s2 = ((param_2 & 0xff) - 1 & 0xffff) * 0x51 & 0xffff;
    unaff_s1 = 9;
    in_t0 = 0xd;
    in_t1 = '\x01';
  }
  iVar2 = FUN_81c152f0(in_t0,in_t1,g_sango_package_data);
  if ((int)(unaff_s1 * unaff_s1) < 0x54) {
    bbk_memcpy(DAT_81c2b15c + 3,(void *)(iVar2 + unaff_s2),unaff_s1 * unaff_s1);
    iVar2 = (param_3 & 0xff) * 7;
    *DAT_81c2b15c = (char)unaff_s1;
    cVar1 = (char)(unaff_s1 >> 1);
    DAT_81c2b15c[1] = (&DAT_81c2b280)[iVar2] - cVar1;
    DAT_81c2b15c[2] = (&DAT_81c2b281)[iVar2] - cVar1;
  }
  return;
}


#undef DAT_81c2b15c
#undef DAT_81c2b164
#undef DAT_81c2b268
#undef DAT_81c2b280
#undef DAT_81c2b281
#undef g_sango_package_data

#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
#define DAT_81c2b285 (*(undefined1 *)(0x81c2b285u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c02664; body bytes 200 */

uint FUN_81c02664(void)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
#define local_18 (*(byte *)(sg_stack + 0))
#define local_17 (*(byte (*)[7])(sg_stack + 1))

  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;

  uVar5 = 0xff;
  FUN_81c0272c(&local_18,local_17);
  uVar6 = 0xff;
  uVar4 = 10;
  iVar2 = 0x50;
  do {
    iVar2 = iVar2 - uVar4;
    cVar1 = (&DAT_81c2b286)[iVar2];
    if ((((cVar1 != '\b') && (cVar1 != '\x01')) && (cVar1 != '\x06')) &&
       (((&DAT_81c2b285)[iVar2] != '\x01' &&
        (uVar3 = FUN_81c027a0((&DAT_81c2b280)[iVar2],(&DAT_81c2b281)[iVar2],local_18,local_17[0]),
        uVar3 < uVar5)))) {
      uVar5 = uVar3;
      uVar6 = uVar4;
    }
    uVar4 = uVar4 + 1 & 0xff;
    iVar2 = uVar4 << 3;
  } while (uVar4 < 0x14);
  return uVar6;
}


#undef DAT_81c2b280
#undef DAT_81c2b281
#undef DAT_81c2b285
#undef DAT_81c2b286
#undef local_18
#undef local_17

#define DAT_81c2b260 (*(char *)(0x81c2b260u))
#define DAT_81c2b11a (*(undefined1 *)(0x81c2b11au))
#define DAT_81c2b119 (*(undefined1 *)(0x81c2b119u))
#define DAT_81c2b126 (*(byte *)(0x81c2b126u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
/* VA 0x81c0272c; body bytes 116 */

void FUN_81c0272c(undefined1 *param_1,undefined1 *param_2)

{
  if (DAT_81c2b260 != '\x01') {
    *param_1 = DAT_81c2b11a;
    *param_2 = DAT_81c2b119;
    return;
  }
  *param_1 = (&DAT_81c2b280)[(uint)DAT_81c2b126 * 7];
  *param_2 = (&DAT_81c2b281)[(uint)DAT_81c2b126 * 7];
  return;
}


#undef DAT_81c2b260
#undef DAT_81c2b11a
#undef DAT_81c2b119
#undef DAT_81c2b126
#undef DAT_81c2b280
#undef DAT_81c2b281


/* VA 0x81c027a0; body bytes 80 */

uint FUN_81c027a0(byte param_1,byte param_2,byte param_3,byte param_4)

{
  char cVar1;
  char cVar2;

  cVar1 = param_1 - param_3;
  if (param_1 < param_3) {
    cVar1 = -(param_1 - param_3);
  }
  cVar2 = param_2 - param_4;
  if (param_2 < param_4) {
    cVar2 = -(param_2 - param_4);
  }
  return (uint)(byte)(cVar1 + cVar2);
}




#define DAT_81c2b134 (*(byte *)(0x81c2b134u))
#define DAT_81c2b150 (*(byte *)(0x81c2b150u))
#define DAT_81c2b160 (*(byte *)(0x81c2b160u))
#define DAT_81c2b195 (*(byte *)(0x81c2b195u))
#define DAT_81c2b135 (*(byte *)(0x81c2b135u))
#define DAT_81c2b162 (*(byte *)(0x81c2b162u))
#define DAT_81c2b14c (*(int *)(0x81c2b14cu))
#define DAT_81c2b128 (*(uint *)(0x81c2b128u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c027f0; body bytes 356 */

void FUN_81c027f0(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;

  uVar1 = (uint)DAT_81c2b134;
  uVar8 = (uint)DAT_81c2b150;
  uVar7 = (uint)DAT_81c2b160;
  uVar6 = (uint)DAT_81c2b195;
  uVar2 = (uint)DAT_81c2b135;
  uVar3 = (uint)DAT_81c2b162;
  iVar4 = FUN_81c152f0(7,'\x01',g_sango_package_data);
  for (uVar10 = (uint)DAT_81c2b134; uVar10 < 0xf; uVar10 = uVar10 + 1 & 0xff) {
    uVar9 = (uint)DAT_81c2b135;
    if (uVar9 < 0xf) {
      uVar11 = uVar10 - ((uVar8 + uVar1) - uVar6 & 0xff);
      do {
        uVar5 = uVar9 - ((uVar7 + uVar2) - uVar3 & 0xff);
        if (((uVar11 & 0xff) < 0xf) && ((uVar5 & 0xff) < 0xf)) {
          if ('\0' < *(char *)(DAT_81c2b14c + uVar9 * 0xf + uVar10)) {
            FUN_81c14690((uVar11 & 0xf) << 4,(short)((uVar5 & 0xf) << 4),0x10,0x10,iVar4 + 6,
                         DAT_81c2b128);
          }
        }
        uVar9 = uVar9 + 1 & 0xff;
      } while (uVar9 < 0xf);
    }
  }
  return;
}


#undef DAT_81c2b134
#undef DAT_81c2b150
#undef DAT_81c2b160
#undef DAT_81c2b195
#undef DAT_81c2b135
#undef DAT_81c2b162
#undef DAT_81c2b14c
#undef DAT_81c2b128
#undef g_sango_package_data

#define DAT_81c2b117 (*(byte *)(0x81c2b117u))
#define DAT_81c2b184 (*(byte *)(0x81c2b184u))
#define DAT_81c2b188 (*(byte *)(0x81c2b188u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c02954; body bytes 760 */

void FUN_81c02954(void)

{
  unsigned char sg_stack[40] __attribute__((aligned(8)));
#define acStack_38 (*(char (*)[24])(sg_stack + 0))

  int iVar1;
  uint uVar2;
  uint uVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;

  FUN_81c0ac48(0,0,0xef,0x13f,0,0);
  uVar6 = (int)(0x78 - (uint)DAT_81c2b184) / 2 & 0xff;
  uVar7 = (int)(0x140 - (uint)DAT_81c2b117) / 2 + 0x14U & 0xff;
  FUN_81c02f08(0x31,acStack_38);
  FUN_81c149dc(5,3,acStack_38);
  FUN_81c02f08(0x30,acStack_38);
  FUN_81c0a7e4((uint)DAT_81c2b188,acStack_38 + 3,10);
  uVar2 = bbk_strlen(acStack_38);
  acStack_38[uVar2] = ' ';
  FUN_81c149dc(5,0x11,acStack_38);
  FUN_81c02f08(0x36,acStack_38);
  FUN_81c149dc(0x24,(short)uVar7 - 0xf,acStack_38);
  FUN_81c02c4c('\x01',0);
  uVar2 = 3;
  FUN_81c08e7c((short)uVar6 + -1,(short)uVar7 + -1,(short)((DAT_81c2b184 + uVar6) * 0x10000 >> 0x10)
               ,(short)((DAT_81c2b117 + uVar7) * 0x10000 >> 0x10),3,0,0);
  uVar9 = 1;
  uVar8 = 0;
  do {
    do {
      uVar5 = 0;
      do {
        iVar1 = uVar5 * 7;
        if ((&DAT_81c2b286)[iVar1] != '\b') {
          FUN_81c0886c((short)(((byte)(&DAT_81c2b280)[iVar1] + uVar6) * 0x10000 >> 0x10),
                       (short)(((byte)(&DAT_81c2b281)[iVar1] + uVar7) * 0x10000 >> 0x10),uVar2,0);
          FUN_81c0886c((short)(((byte)(&DAT_81c2b280)[iVar1] + uVar6) * 0x10000 >> 0x10),
                       (short)(((byte)(&DAT_81c2b281)[iVar1] + uVar7) * 0x10000 >> 0x10),uVar2,0);
        }
        uVar5 = uVar5 + 1 & 0xff;
      } while (uVar5 < 0x14);
      if (uVar2 != 3) {
        uVar2 = 0;
      }
      uVar5 = FUN_81c14164(0x32,'\x01');
    } while (uVar5 == 0);
    cVar4 = (char)uVar9;
    if (uVar5 == 0x67) {
      uVar5 = uVar8 - 0x18;
      if (uVar8 == 0) goto LAB_81c02b4c;
LAB_81c02bd0:
      uVar8 = uVar5 & 0xff;
LAB_81c02b48:
      cVar4 = (char)uVar9;
    }
    else {
      if ((int)uVar5 < 0x68) {
        if (uVar5 != 0xb) {
          uVar3 = 0x1c;
          if ((int)uVar5 < 0xc) {
            uVar3 = 1;
          }
          if (uVar5 != uVar3) goto LAB_81c02b48;
        }
        return;
      }
      if (0x68 < (int)uVar5) {
        if ((int)uVar5 < 0x6b) {
          uVar9 = (uint)(uVar9 == 0);
          uVar8 = 0;
          goto LAB_81c02b48;
        }
        if (((uVar5 == 0x6c) && (uVar5 = FUN_81c02ec0(uVar9), 0x17 < uVar5)) &&
           (uVar5 = FUN_81c02ec0(uVar9), (int)uVar8 < (int)(uVar5 - 0x18))) {
          uVar5 = uVar8 + 0x18;
          goto LAB_81c02bd0;
        }
      }
    }
LAB_81c02b4c:
    FUN_81c02c4c(cVar4,uVar8);
  } while( true );
}


#undef DAT_81c2b117
#undef DAT_81c2b184
#undef DAT_81c2b188
#undef DAT_81c2b280
#undef DAT_81c2b281
#undef DAT_81c2b286
#undef acStack_38

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b168 (*(ushort *)(0x81c2b168u))
#define DAT_81c2b264 (*(ushort *)(0x81c2b264u))
#define DAT_81c2b268 (*(undefined1 *)(0x81c2b268u))
/* VA 0x81c02c4c; body bytes 628 */

void FUN_81c02c4c(char param_1,uint param_2)

{
  unsigned char sg_stack[40] __attribute__((aligned(8)));
#define acStack_38 (*(char (*)[5])(sg_stack + 0))
#define auStack_33 (*(undefined1 (*)[3])(sg_stack + 5))
#define auStack_30 (*(undefined1 (*)[16])(sg_stack + 8))

  ushort uVar1;
  byte index;
  uint uVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;

  uVar6 = (uint)(byte)param_1 * 10 & 0xff;
  FUN_81c0ac48(0x78,0,0xef,0x13f,0,0);
  FUN_81c08e7c(0x78,0,0xef,0x13f,3,0,0);
  FUN_81c089c4(0x78,0xe,0xef,0xe,3,0,0);
  FUN_81c089c4(0x78,0x1c,0xef,0x1c,3,0,0);
  uVar2 = FUN_81c02f30(uVar6);
  sango_load_named_text(*(char *)(uVar2 * 0x10 + DAT_81c2b164 + 1) + 0xff,acStack_38);
  uVar2 = bbk_strlen(acStack_38);
  pcVar3 = acStack_38 + (uVar2 & 0xff);
  *pcVar3 = ' ';
  FUN_81c02f08(0x32,pcVar3);
  FUN_81c149dc((short)(uVar2 & 0xff) * -3 - 0x52U & 0xff,2,acStack_38);
  FUN_81c02f08(0x34,acStack_38);
  if (param_1 == '\0') {
    uVar2 = (uint)DAT_81c2b264;
  }
  else {
    uVar2 = (uint)DAT_81c2b168;
    if (uVar2 == 0) {
      FUN_81c02f08(0x35,auStack_33);
      goto LAB_81c02db4;
    }
  }
  FUN_81c0a7e4(uVar2,auStack_33,10);
LAB_81c02db4:
  FUN_81c149dc(0x7b,0x10,acStack_38);
  uVar5 = (param_2 & 0xff) + uVar6 & 0xff;
  uVar4 = 0;
  uVar2 = uVar5;
  while( true ) {
    if (10 < (int)((uVar2 & 0xff) - uVar6)) {
      return;
    }
    index = (&DAT_81c2b268)[uVar2 & 0xff] - 1;
    if ((&DAT_81c2b268)[uVar2 & 0xff] == '\0') break;
    uVar1 = *(ushort *)((uint)index * 0x10 + DAT_81c2b164 + 10);
    sango_load_named_text(index,acStack_38);
    uVar2 = bbk_strlen(acStack_38);
    FUN_81c0a7c8(acStack_38 + (uVar2 & 0xff),0x20,0x14 - (uVar2 & 0xff));
    FUN_81c0a7e4((uint)uVar1,auStack_30,10);
    FUN_81c149dc(0x7b,(short)uVar4 * 0xc + 0x1e,acStack_38);
    uVar4 = uVar4 + 1 & 0xff;
    uVar2 = uVar4 + uVar5;
    if (0x17 < uVar4) {
      return;
    }
  }
  return;
}


#undef DAT_81c2b164
#undef DAT_81c2b168
#undef DAT_81c2b264
#undef DAT_81c2b268
#undef acStack_38
#undef auStack_33
#undef auStack_30

#define DAT_81c2b268 (*(undefined1 *)(0x81c2b268u))
/* VA 0x81c02ec0; body bytes 72 */

uint FUN_81c02ec0(uint param_1)

{
  uint uVar1;

  uVar1 = 0;
  do {
    if ((&DAT_81c2b268)[uVar1 + ((param_1 & 0xff) * 10 & 0xff)] == '\0') {
      return uVar1;
    }
    uVar1 = uVar1 + 1 & 0xff;
  } while (uVar1 < 10);
  return uVar1;
}


#undef DAT_81c2b268


/* VA 0x81c02f08; body bytes 40 */

void FUN_81c02f08(uint param_1,void *param_2)

{
  FUN_81c154d8(1,param_1 & 0xff,param_2);
  return;
}




#define DAT_81c2b268 (*(undefined1 *)(0x81c2b268u))
/* VA 0x81c02f30; body bytes 28 */

uint FUN_81c02f30(uint param_1)

{
  return (byte)(&DAT_81c2b268)[param_1 & 0xff] - 1 & 0xff;
}


#undef DAT_81c2b268

#define DAT_81c2b150 (*(byte *)(0x81c2b150u))
#define DAT_81c2b160 (*(byte *)(0x81c2b160u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
/* VA 0x81c02f4c; body bytes 204 */

undefined4 FUN_81c02f4c(byte *param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;

  uVar3 = FUN_81c017a0(param_1);
  uVar4 = 0;
  if (uVar3 != 0xff) {
    if (*param_1 < 2) {
      bVar1 = param_1[3];
      FUN_81c04468((uint)bVar1);
      iVar2 = (uint)bVar1 * 7;
      FUN_81c06a70(0x1b,0xc,0x11,0,
                   ((ushort)(byte)(&DAT_81c2b280)[iVar2] - (ushort)DAT_81c2b150) * 0x10,
                   ((ushort)(byte)(&DAT_81c2b281)[iVar2] - (ushort)DAT_81c2b160) * 0x10);
      uVar4 = 1;
    }
    else {
      uVar4 = 1;
    }
  }
  return uVar4;
}


#undef DAT_81c2b150
#undef DAT_81c2b160
#undef DAT_81c2b280
#undef DAT_81c2b281

#define DAT_81c2b18c (*(char *)(0x81c2b18cu))
#define DAT_81c2b260 (*(char *)(0x81c2b260u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c03020; body bytes 308 */

void FUN_81c03020(void)

{
  unsigned char sg_stack[19] __attribute__((aligned(8)));
#define auStack_20 (*(uchar (*)[2])(sg_stack + 0))
#define local_1e (*(undefined1 *)(sg_stack + 2))

  char cVar1;
  int iVar2;
  uint uVar3;

  if (DAT_81c2b18c == '\0') {
    uVar3 = 0;
    DAT_81c2b18c = '\x02';
    iVar2 = 0;
    do {
      if ((&DAT_81c2b286)[iVar2 - uVar3] != '\b') {
        DAT_81c2b18c = '\0';
        break;
      }
      uVar3 = uVar3 + 1 & 0xff;
      iVar2 = uVar3 << 3;
    } while (uVar3 < 10);
    FUN_81c04468(uVar3);
    cVar1 = DAT_81c2b18c;
    while ((DAT_81c2b18c = cVar1, DAT_81c2b18c == '\0' && (uVar3 = FUN_81c03874(), uVar3 != 0xff)))
    {
      iVar2 = FUN_81c03708(uVar3);
      cVar1 = DAT_81c2b18c;
      if (iVar2 == 0) {
        local_1e = (undefined1)uVar3;
        FUN_81c03154((char *)auStack_20);
        uVar3 = FUN_81c03654(auStack_20);
        if ((DAT_81c2b260 != '\x01') || (cVar1 = '\x01', uVar3 != 5)) {
          FUN_81c04e34('\0');
          cVar1 = DAT_81c2b18c;
        }
      }
    }
  }
  return;
}


#undef DAT_81c2b18c
#undef DAT_81c2b260
#undef DAT_81c2b286
#undef auStack_20
#undef local_1e

#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c03154; body bytes 384 */

void FUN_81c03154(char *param_1)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
#define auStack_30 (*(ushort (*)[4])(sg_stack + 0))

  bool bVar1;
  char cVar2;
  byte *ptr;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint unaff_s6;

  uVar5 = (uint)(byte)param_1[2];
  bVar1 = true;
  FUN_81c04efc(uVar5);
  ptr = (byte *)bbk_alloc(100);
  uVar3 = 0;
  do {
    uVar4 = 0;
    FUN_81c04f68();
    FUN_81c03590(uVar5,auStack_30);
    FUN_81c04f18(8,ptr);
    uVar3 = FUN_81c07068(auStack_30,uVar3,(char *)ptr);
    cVar2 = (char)uVar3;
    *param_1 = cVar2;
    if (uVar3 == 2) {
      uVar4 = 0xff;
      FUN_81c055b0();
    }
    else if ((int)uVar3 < 3) {
      if ((uVar3 == 1) && (uVar4 = 0xff, (&DAT_81c2b286)[uVar5 * 7] != '\x02')) {
        uVar4 = FUN_81c01e74(uVar5,auStack_30,ptr);
      }
    }
    else if ((uVar3 == 3) || (uVar3 == 0xff)) goto LAB_81c03248;
    if (uVar4 != 0xff) {
      FUN_81c02524(cVar2,uVar4,uVar5);
      unaff_s6 = FUN_81c032d4(cVar2,(char)uVar4,uVar5);
      if (unaff_s6 != 0xff) {
        bVar1 = false;
      }
    }
  } while (bVar1);
  param_1[3] = (char)unaff_s6;
  param_1[1] = (char)uVar4;
LAB_81c03248:
  bbk_free_if_nonnull(ptr);
  return;
}


#undef DAT_81c2b286
#undef auStack_30

#define DAT_81c2b125 (*(byte *)(0x81c2b125u))
#define DAT_81c2b116 (*(byte *)(0x81c2b116u))
/* VA 0x81c032d4; body bytes 360 */

uint FUN_81c032d4(char param_1,char param_2,uint param_3)

{
  unsigned char sg_stack[48] __attribute__((aligned(8)));
#define acStack_40 (*(char (*)[16])(sg_stack + 0))
#define acStack_30 (*(char (*)[16])(sg_stack + 16))

  uint uVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  uint uVar7;

  uVar1 = (uint)(byte)param_2;
  uVar7 = param_3 & 0xff;
  if ((uVar1 != 0x16) && (uVar1 != 0x1e)) {
    FUN_81c04f18(2,acStack_40);
    FUN_81c04f18(3,acStack_30);
    FUN_81c0343c();
    while( true ) {
      FUN_81c04f68();
      iVar3 = FUN_81c038f4('\x01');
      if (iVar3 == 0xff) break;
      uVar4 = FUN_81c06318((ushort)DAT_81c2b125,(ushort)DAT_81c2b116);
      if (uVar4 == 0xff) {
        pcVar6 = acStack_40;
      }
      else {
        uVar5 = FUN_81c03ff8();
        pcVar6 = acStack_30;
        if (uVar5 != 0) {
          bVar2 = false;
          if (((uVar7 < 10) && (uVar4 < 10)) || ((10 < uVar7 && (10 < uVar4)))) {
            bVar2 = true;
          }
          if (param_1 == '\x01') {
            iVar3 = FUN_81c02244(uVar1,bVar2,uVar4);
            if (iVar3 != 0) {
              return uVar4;
            }
          }
          else if (!bVar2) {
            return uVar4;
          }
        }
      }
      FUN_81c04f8c(0x6a,0xf3,pcVar6);
    }
    FUN_81c04468(uVar7);
    uVar7 = 0xff;
  }
  return uVar7;
}


#undef DAT_81c2b125
#undef DAT_81c2b116
#undef acStack_40
#undef acStack_30

#define DAT_81c2b15c (*(byte * *)(0x81c2b15cu))
#define DAT_81c2b160 (*(byte *)(0x81c2b160u))
#define DAT_81c2b150 (*(byte *)(0x81c2b150u))
/* VA 0x81c0343c; body bytes 340 */

void FUN_81c0343c(void)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;

  uVar7 = (uint)*DAT_81c2b15c;
  uVar8 = 0;
  if (uVar7 != 0) {
    bVar1 = DAT_81c2b15c[2];
    while( true ) {
      uVar6 = uVar8 + bVar1 & 0xff;
      if ((DAT_81c2b160 <= uVar6) && (uVar6 < DAT_81c2b160 + 0xf)) {
        uVar2 = (ushort)DAT_81c2b160;
        uVar5 = 0;
        if (uVar7 != 0) {
          bVar1 = DAT_81c2b15c[1];
          while( true ) {
            uVar4 = (uint)DAT_81c2b150;
            uVar3 = uVar5 + bVar1 & 0xff;
            if (((uVar4 <= uVar3) && (uVar3 < uVar4 + 0xf)) &&
               (DAT_81c2b15c[uVar8 * uVar7 + uVar5 + 3] == 1)) {
              FUN_81c04fb4(7,2,(uVar3 - uVar4) * 0x10 & 0xff,((short)uVar6 - uVar2) * 0x10 & 0xff);
            }
            uVar5 = uVar5 + 1 & 0xff;
            if (uVar7 <= uVar5) break;
            bVar1 = DAT_81c2b15c[1];
          }
        }
      }
      uVar8 = uVar8 + 1 & 0xff;
      if (uVar7 <= uVar8) break;
      bVar1 = DAT_81c2b15c[2];
    }
  }
  return;
}


#undef DAT_81c2b15c
#undef DAT_81c2b160
#undef DAT_81c2b150

#define DAT_81c2b150 (*(byte *)(0x81c2b150u))
#define DAT_81c2b160 (*(byte *)(0x81c2b160u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
/* VA 0x81c03590; body bytes 196 */

void FUN_81c03590(uint param_1,ushort *param_2)

{
  int iVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  uint uVar5;
  ushort uVar6;

  iVar1 = (param_1 & 0xff) * 7;
  uVar5 = (uint)DAT_81c2b160;
  uVar2 = ((ushort)(byte)(&DAT_81c2b280)[iVar1] - (ushort)DAT_81c2b150) * 0x10 + 0x12 & 0xff;
  uVar3 = uVar2 + 0x18;
  uVar6 = 0x2d;
  uVar4 = 0xfd;
  if (0xef < uVar3) {
    uVar2 = uVar2 - 0x28 & 0xff;
    uVar3 = uVar2 + 0x18;
  }
  *param_2 = uVar2;
  param_2[2] = uVar3;
  uVar5 = ((byte)(&DAT_81c2b281)[iVar1] - uVar5) * 0x10 & 0xff;
  if (3 < (int)(0x127 - uVar5) / 0xc) {
    uVar4 = (short)uVar5 + 4U & 0xff;
    uVar6 = uVar4 + 0x30 & 0xff;
  }
  param_2[3] = uVar6;
  param_2[1] = uVar4;
  return;
}


#undef DAT_81c2b150
#undef DAT_81c2b160
#undef DAT_81c2b280
#undef DAT_81c2b281

#define DAT_81c2b160 (*(byte *)(0x81c2b160u))
#define DAT_81c2b150 (*(byte *)(0x81c2b150u))
#define DAT_81c2b238 (*(char * *)(0x81c2b238u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
/* VA 0x81c03654; body bytes 180 */

uint FUN_81c03654(uchar *record)

{
  byte bVar1;
  int iVar2;
  uint uVar3;

  bVar1 = record[2];
  uVar3 = FUN_81c06694(record);
  if ((uVar3 & 0xff) != 0) {
    FUN_81c04b9c((uint)DAT_81c2b150,(uint)DAT_81c2b160);
    FUN_81c04630(0);
    *DAT_81c2b238 = (char)uVar3 + *DAT_81c2b238;
    if (bVar1 < 10) {
      FUN_81c048bc(uVar3 & 0xff);
    }
    FUN_81c04920();
  }
  iVar2 = (uint)bVar1 * 7;
  uVar3 = FUN_81c0620c((uint)(byte)(&DAT_81c2b280)[iVar2],(uint)(byte)(&DAT_81c2b281)[iVar2]);
  return uVar3;
}


#undef DAT_81c2b160
#undef DAT_81c2b150
#undef DAT_81c2b238
#undef DAT_81c2b280
#undef DAT_81c2b281

#define DAT_81c2b125 (*(byte *)(0x81c2b125u))
#define DAT_81c2b195 (*(byte *)(0x81c2b195u))
#define DAT_81c2b134 (*(byte *)(0x81c2b134u))
#define DAT_81c2b116 (*(byte *)(0x81c2b116u))
#define DAT_81c2b162 (*(byte *)(0x81c2b162u))
#define DAT_81c2b135 (*(byte *)(0x81c2b135u))
#define DAT_81c2b14c (*(int *)(0x81c2b14cu))
#define DAT_81c2b172 (*(byte *)(0x81c2b172u))
#define DAT_81c2b148 (*(undefined1 *)(0x81c2b148u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
#define DAT_81c2b284 (*(undefined1 *)(0x81c2b284u))
/* VA 0x81c03708; body bytes 364 */

undefined4 FUN_81c03708(uint param_1)

{
  unsigned char sg_stack[40] __attribute__((aligned(8)));
#define acStack_28 (*(char (*)[24])(sg_stack + 0))

  int iVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;

  uVar6 = param_1 & 0xff;
  iVar1 = uVar6 * 7;
  if ((&DAT_81c2b284)[iVar1] != '\x01') {
    FUN_81c003b8(uVar6);
    FUN_81c0a7c8(acStack_28,0,0x14);
    FUN_81c04f18(1,acStack_28);
    FUN_81c027f0();
    while( true ) {
      FUN_81c04f68();
      iVar3 = FUN_81c038f4('\x02');
      bVar2 = DAT_81c2b125;
      if (iVar3 == 0xff) break;
      uVar5 = (uint)DAT_81c2b134 + ((uint)DAT_81c2b125 - (uint)DAT_81c2b195) & 0xff;
      uVar4 = (uint)DAT_81c2b135 + ((uint)DAT_81c2b116 - (uint)DAT_81c2b162) & 0xff;
      if (((uVar5 < 0x10) && (uVar4 < 0x10)) &&
         (*(byte *)(DAT_81c2b14c + uVar4 * 0xf + uVar5) < 0x81)) {
        DAT_81c2b172 = (&DAT_81c2b280)[iVar1];
        DAT_81c2b148 = (&DAT_81c2b281)[iVar1];
        (&DAT_81c2b281)[iVar1] = DAT_81c2b116;
        (&DAT_81c2b280)[iVar1] = bVar2;
        FUN_81c04468(uVar6);
        return 0;
      }
      FUN_81c04f8c(0x6a,0xf3,acStack_28);
    }
    FUN_81c04468(uVar6);
  }
  return 1;
}


#undef DAT_81c2b125
#undef DAT_81c2b195
#undef DAT_81c2b134
#undef DAT_81c2b116
#undef DAT_81c2b162
#undef DAT_81c2b135
#undef DAT_81c2b14c
#undef DAT_81c2b172
#undef DAT_81c2b148
#undef DAT_81c2b280
#undef DAT_81c2b281
#undef DAT_81c2b284
#undef acStack_28

#define DAT_81c2b150 (*(byte *)(0x81c2b150u))
#define DAT_81c2b160 (*(byte *)(0x81c2b160u))
/* VA 0x81c03874; body bytes 128 */

uint FUN_81c03874(void)

{
  int iVar1;
  uint uVar2;

  FUN_81c04b9c((uint)DAT_81c2b150,(uint)DAT_81c2b160);
  FUN_81c03f6c();
  FUN_81c04d58();
  do {
    while (iVar1 = FUN_81c038f4('\x03'), iVar1 == 0) {
      uVar2 = FUN_81c069d4();
      if (uVar2 != 0xff) {
        return uVar2;
      }
    }
    iVar1 = FUN_81c06440();
  } while (iVar1 != 0xff);
  return 0xff;
}


#undef DAT_81c2b150
#undef DAT_81c2b160

#define DAT_81c2b125 (*(byte *)(0x81c2b125u))
#define DAT_81c2b116 (*(byte *)(0x81c2b116u))
#define DAT_81c2b117 (*(byte *)(0x81c2b117u))
#define DAT_81c2b184 (*(byte *)(0x81c2b184u))
/* VA 0x81c038f4; body bytes 812 */

undefined4 FUN_81c038f4(char param_1)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
#define local_28 (*(int *)(sg_stack + 0))
#define local_24 (*(int *)(sg_stack + 4))

  byte bVar1;
  char cVar2;
  undefined4 uVar3;
  uint unaff_s0;
  uint uVar4;

  uVar4 = 0;
LAB_81c03918:
  FUN_81c1408c(&local_28);
  if (local_28 == 5) {
    uVar3 = 0;
    if ((local_24 == 0x1c) || (uVar3 = 0xff, local_24 == 1)) {
      return uVar3;
    }
    FUN_81c047bc((uint)DAT_81c2b125,(uint)DAT_81c2b116,'\0');
  }
  if (local_28 == 6) goto LAB_81c03b8c;
  if (local_28 < 7) {
    if (local_28 == 5) {
      if (local_24 == 0x67) {
        bVar1 = DAT_81c2b116 - 1;
        if (DAT_81c2b116 != 0) {
LAB_81c03aac:
          DAT_81c2b116 = bVar1;
        }
      }
      else if (local_24 < 0x68) {
        if (local_24 == 0x1f) {
          FUN_81c02954();
          FUN_81c03f6c();
        }
        else if (local_24 == 0x23) {
          FUN_81c055b0();
          FUN_81c03f6c();
        }
      }
      else if (local_24 == 0x6a) {
        bVar1 = DAT_81c2b125 + 1;
        if ((int)(uint)DAT_81c2b125 < (int)(DAT_81c2b184 - 1)) {
LAB_81c03a74:
          DAT_81c2b125 = bVar1;
        }
      }
      else if (local_24 < 0x6b) {
        if ((local_24 == 0x69) && (bVar1 = DAT_81c2b125 - 1, DAT_81c2b125 != 0)) goto LAB_81c03a74;
      }
      else if ((local_24 == 0x6c) &&
              (bVar1 = DAT_81c2b116 + 1, (int)(uint)DAT_81c2b116 < (int)(DAT_81c2b117 - 1)))
      goto LAB_81c03aac;
      if (param_1 == '\x01') {
        cVar2 = '\0';
        if (uVar4 == 0) goto LAB_81c039e8;
        FUN_81c0343c();
      }
      else {
        cVar2 = (char)uVar4;
        if ((param_1 == '\x02') && (cVar2 = '\0', uVar4 != 0)) {
          FUN_81c027f0();
        }
        else {
LAB_81c039e8:
          FUN_81c041f8(cVar2);
        }
      }
    }
  }
  else if (local_28 == 0xb) {
    /* Read the original full-width coordinates from the input packet;
       the legacy byte slots wrap y=300 to 44. */
    enum SangoBattleToolbarAction action = sango_battle_toolbar_hit(
        *(ushort *)(sg_stack + 8),*(ushort *)(sg_stack + 10));
    if (action == SANGO_BATTLE_TOOLBAR_INFO) {
      FUN_81c055b0();
    }
    else if (action == SANGO_BATTLE_TOOLBAR_OVERVIEW) {
      FUN_81c02954();
    }
    if (action != SANGO_BATTLE_TOOLBAR_NONE) {
      FUN_81c03f6c();
    }
  }
  goto LAB_81c03950;
LAB_81c03b8c:
  unaff_s0 = unaff_s0 + 1 & 0xff;
  if (unaff_s0 % 10 != 0) goto LAB_81c03918;
  uVar4 = (uint)(uVar4 == 0);
LAB_81c03950:
  FUN_81c04630(uVar4);
  if (param_1 == '\x01') {
    cVar2 = '\0';
    if (uVar4 != 0) {
      FUN_81c0343c();
      goto LAB_81c03970;
    }
  }
  else {
    cVar2 = (char)uVar4;
    if ((param_1 == '\x02') && (cVar2 = '\0', uVar4 != 0)) {
      FUN_81c027f0();
      goto LAB_81c03970;
    }
  }
  FUN_81c041f8(cVar2);
LAB_81c03970:
  FUN_81c03c20();
  goto LAB_81c03918;
}


#undef DAT_81c2b125
#undef DAT_81c2b116
#undef DAT_81c2b117
#undef DAT_81c2b184
#undef local_28
#undef local_24

#define DAT_81c2b116 (*(byte *)(0x81c2b116u))
#define DAT_81c2b160 (*(byte *)(0x81c2b160u))
#define DAT_81c2b150 (*(byte *)(0x81c2b150u))
#define DAT_81c2b125 (*(byte *)(0x81c2b125u))
/* VA 0x81c03c20; body bytes 120 */

void FUN_81c03c20(void)

{
  ushort uVar1;

  uVar1 = ((ushort)DAT_81c2b116 - (ushort)DAT_81c2b160) * 0x10;
  if (uVar1 < 0x101) {
    FUN_81c04fb4(7,5,((uint)DAT_81c2b125 - (uint)DAT_81c2b150) * 0x10 & 0xffff,uVar1);
    FUN_81c04f68();
  }
  return;
}


#undef DAT_81c2b116
#undef DAT_81c2b160
#undef DAT_81c2b150
#undef DAT_81c2b125

#define DAT_81c2b262 (*(ushort *)(0x81c2b262u))
#define DAT_81c2b184 (*(byte *)(0x81c2b184u))
#define DAT_81c2b13e (*(undefined2 *)(0x81c2b13eu))
#define DAT_81c2b117 (*(byte *)(0x81c2b117u))
#define DAT_81c2b11a (*(char *)(0x81c2b11au))
#define DAT_81c2b119 (*(char *)(0x81c2b119u))
#define DAT_81c2b260 (*(char *)(0x81c2b260u))
#define DAT_81c2b261 (*(byte *)(0x81c2b261u))
#define DAT_81c2b12c (*(undefined1 *)(0x81c2b12cu))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
#define DAT_81c2b2c6 (*(undefined1 *)(0x81c2b2c6u))
#define DAT_81c2b2c7 (*(undefined1 *)(0x81c2b2c7u))
/* VA 0x81c03c98; body bytes 528 */

undefined4 FUN_81c03c98(void)

{
  int iVar1;
  char cVar2;
  char cVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  char *pcVar9;
  char *pcVar10;
  uint uVar11;
  int iVar12;
  char cVar13;
  char cVar14;
  char cVar15;
  char cVar16;

  pbVar4 = (byte *)FUN_81c04f40((uint)DAT_81c2b262,'\x01');
  if (pbVar4 == (byte *)0x0) {
    DAT_81c2b12c = 1;
    uVar8 = 1;
  }
  else {
    DAT_81c2b184 = *pbVar4;
    DAT_81c2b117 = pbVar4[2];
    DAT_81c2b13e = 4;
    uVar11 = 0;
    if (pbVar4[0x10] != 3) {
      uVar5 = 1;
      do {
        uVar11 = uVar5 & 0xffff;
        uVar5 = uVar11 + 1;
      } while ((pbVar4 + 0x10)[uVar11] != 3);
    }
    uVar5 = (uint)DAT_81c2b184;
    if (uVar5 == 0) {
      trap(7);
    }
    DAT_81c2b11a = (char)(uVar11 % uVar5);
    cVar3 = DAT_81c2b11a + -2;
    DAT_81c2b119 = (char)(uVar11 / uVar5);
    cVar2 = DAT_81c2b119 + -2;
    uVar6 = FUN_81c03ea8('x');
    uVar7 = FUN_81c03ea8('y');
    uVar11 = 8;
    uVar5 = (uint)DAT_81c2b261;
    cVar16 = cVar3;
    cVar15 = cVar2;
    cVar14 = (char)uVar6;
    cVar13 = (char)uVar7;
    if (DAT_81c2b260 == '\x01') {
      uVar5 = 8;
      uVar11 = (uint)DAT_81c2b261;
      cVar16 = (char)uVar6;
      cVar15 = (char)uVar7;
      cVar14 = cVar3;
      cVar13 = cVar2;
    }
    uVar6 = FUN_81c04f40(2,'\x05');
    uVar7 = 0;
    do {
      iVar12 = (uVar7 & 0x7f) * 2;
      pcVar9 = (char *)(uVar6 + uVar11 * 0x14 + iVar12);
      iVar1 = uVar7 * 7;
      (&DAT_81c2b280)[iVar1] = *pcVar9 + cVar16;
      pcVar10 = (char *)(uVar6 + uVar5 * 0x14 + iVar12);
      (&DAT_81c2b281)[iVar1] = pcVar9[1] + cVar15;
      uVar7 = uVar7 + 1 & 0xff;
      (&DAT_81c2b2c6)[iVar1] = cVar14 + *pcVar10;
      (&DAT_81c2b2c7)[iVar1] = cVar13 + pcVar10[1];
    } while (uVar7 < 10);
    uVar8 = 0;
  }
  return uVar8;
}


#undef DAT_81c2b262
#undef DAT_81c2b184
#undef DAT_81c2b13e
#undef DAT_81c2b117
#undef DAT_81c2b11a
#undef DAT_81c2b119
#undef DAT_81c2b260
#undef DAT_81c2b261
#undef DAT_81c2b12c
#undef DAT_81c2b280
#undef DAT_81c2b281
#undef DAT_81c2b2c6
#undef DAT_81c2b2c7

#define DAT_81c2b261 (*(undefined1 *)(0x81c2b261u))
#define DAT_81c2b184 (*(byte *)(0x81c2b184u))
#define DAT_81c2b117 (*(byte *)(0x81c2b117u))
/* VA 0x81c03ea8; body bytes 196 */

uint FUN_81c03ea8(char param_1)

{
  uint uVar1;
  uint uVar2;

  uVar1 = DAT_81c2b184 - 5 & 0xff;
  uVar2 = DAT_81c2b117 - 5 & 0xff;
  switch(DAT_81c2b261) {
  case 0:
    uVar1 = (DAT_81c2b184 >> 1) - 2 & 0xff;
    goto LAB_81c03f04;
  case 1:
    uVar2 = 2;
    break;
  case 2:
    uVar2 = (DAT_81c2b117 >> 1) - 2 & 0xff;
    break;
  case 4:
    uVar1 = (DAT_81c2b184 >> 1) - 2 & 0xff;
    break;
  case 6:
    uVar2 = (DAT_81c2b117 >> 1) - 2 & 0xff;
  case 5:
    uVar1 = 2;
    break;
  case 7:
    uVar1 = 0;
LAB_81c03f04:
    uVar2 = 0;
  }
  if (param_1 != 'x') {
    uVar1 = uVar2;
  }
  return uVar1;
}


#undef DAT_81c2b261
#undef DAT_81c2b184
#undef DAT_81c2b117

#define DAT_81c2b264 (*(ushort *)(0x81c2b264u))
#define DAT_81c2b128 (*(int *)(0x81c2b128u))
#define DAT_81c2b17d (*(byte *)(0x81c2b17du))
/* VA 0x81c03f6c; body bytes 140 */

void FUN_81c03f6c(void)

{
  unsigned char sg_stack[32] __attribute__((aligned(8)));
#define acStack_18 (*(char (*)[16])(sg_stack + 0))

  uint uVar1;

  FUN_81c04fb4(8,1,0,0xf1);
  FUN_81c0a7e4((uint)DAT_81c2b264,acStack_18,10);
  uVar1 = FUN_81c1b9d4(acStack_18);
  FUN_81c07cf0(0xe,0xf4,(uint)DAT_81c2b264,uVar1 & 0xff,DAT_81c2b128);
  FUN_81c04fb4(9,(uint)DAT_81c2b17d,0x4b,0xf3);
  sango_battle_toolbar_draw(DAT_81c2b128);
  return;
}


#undef DAT_81c2b264
#undef DAT_81c2b128
#undef DAT_81c2b17d
#undef acStack_18

#define DAT_81c2b15c (*(byte * *)(0x81c2b15cu))
#define DAT_81c2b116 (*(byte *)(0x81c2b116u))
#define DAT_81c2b125 (*(byte *)(0x81c2b125u))
/* VA 0x81c03ff8; body bytes 108 */

uint FUN_81c03ff8(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;

  uVar4 = 0;
  uVar2 = (uint)*DAT_81c2b15c;
  uVar3 = (uint)DAT_81c2b116 - (uint)DAT_81c2b15c[2] & 0xff;
  uVar1 = (uint)DAT_81c2b125 - (uint)DAT_81c2b15c[1] & 0xff;
  if ((uVar3 < uVar2) && (uVar1 < uVar2)) {
    uVar4 = (uint)(DAT_81c2b15c[uVar1 + uVar3 * uVar2 + 3] == 1);
  }
  return uVar4;
}


#undef DAT_81c2b15c
#undef DAT_81c2b116
#undef DAT_81c2b125

#define DAT_81c2b188 (*(byte *)(0x81c2b188u))
#define DAT_81c2b168 (*(undefined2 *)(0x81c2b168u))
#define DAT_81c2b260 (*(char *)(0x81c2b260u))
#define DAT_81c2b18c (*(char *)(0x81c2b18cu))
#define DAT_81c2b266 (*(short *)(0x81c2b266u))
#define DAT_81c2b264 (*(short *)(0x81c2b264u))
#define DAT_81c2b285 (*(undefined1 *)(0x81c2b285u))
/* VA 0x81c04064; body bytes 404 */

void FUN_81c04064(void)

{
  unsigned char sg_stack[56] __attribute__((aligned(8)));
#define acStack_30 (*(char (*)[32])(sg_stack + 8))

  int iVar2;
  uint uVar3;

  DAT_81c2b188 = DAT_81c2b188 + 1;
  DAT_81c2b168 = 0;
  uVar3 = 0;
  if (DAT_81c2b188 < 0x1f) {
    iVar2 = 0;
    do {
      iVar2 = iVar2 - uVar3;
      uVar3 = uVar3 + 1 & 0xff;
      (&DAT_81c2b285)[iVar2] = 0;
      iVar2 = uVar3 << 3;
    } while (uVar3 < 0x14);
    FUN_81c06384();
    sango_battle_day_popup_draw((uint)DAT_81c2b188);
    FUN_81c14164(0x32,'\0');
    if (DAT_81c2b266 == 0) {
      DAT_81c2b18c = '\x01';
      uVar3 = 0x26;
    }
    if (DAT_81c2b264 == 0) {
      DAT_81c2b18c = '\x02';
      uVar3 = 0x25;
    }
    if (DAT_81c2b18c != '\0') {
      FUN_81c04f18(uVar3,acStack_30);
      FUN_81c14dd8(acStack_30,1);
    }
    FUN_81c042c4();
  }
  else if (DAT_81c2b260 == '\x01') {
    DAT_81c2b18c = '\x02';
  }
  else {
    DAT_81c2b18c = '\x01';
  }
  return;
}


#undef DAT_81c2b188
#undef DAT_81c2b168
#undef DAT_81c2b260
#undef DAT_81c2b18c
#undef DAT_81c2b266
#undef DAT_81c2b264
#undef DAT_81c2b285
#undef acStack_30

#define DAT_81c2b150 (*(byte *)(0x81c2b150u))
#define DAT_81c2b125 (*(byte *)(0x81c2b125u))
#define DAT_81c2b160 (*(byte *)(0x81c2b160u))
#define DAT_81c2b116 (*(byte *)(0x81c2b116u))
/* VA 0x81c041f8; body bytes 204 */

void FUN_81c041f8(char param_1)

{
  byte bVar1;
  byte bVar2;

  if (param_1 != '\0') {
    return;
  }
  bVar1 = DAT_81c2b150 - 1;
  bVar2 = DAT_81c2b160;
  if ((uint)DAT_81c2b150 <= (uint)DAT_81c2b125) {
    if ((uint)DAT_81c2b116 < (uint)DAT_81c2b160) {
      bVar1 = DAT_81c2b150;
      bVar2 = DAT_81c2b160 - 1;
    }
    else {
      bVar1 = DAT_81c2b150 + 1;
      if (((uint)DAT_81c2b125 < DAT_81c2b150 + 0xf) &&
         (bVar1 = DAT_81c2b150, bVar2 = DAT_81c2b160 + 1, (uint)DAT_81c2b116 < DAT_81c2b160 + 0xf))
      goto LAB_81c04248;
    }
  }
  DAT_81c2b160 = bVar2;
  DAT_81c2b150 = bVar1;
  FUN_81c04b9c((uint)DAT_81c2b150,(uint)DAT_81c2b160);
LAB_81c04248:
  FUN_81c03f6c();
  FUN_81c04d58();
  return;
}


#undef DAT_81c2b150
#undef DAT_81c2b125
#undef DAT_81c2b160
#undef DAT_81c2b116

#define DAT_81c2b18c (*(char *)(0x81c2b18cu))
#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c042c4; body bytes 420 */

void FUN_81c042c4(void)

{
  bool bVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  char cVar5;
  int iVar6;
  ushort uVar7;
  int iVar8;
  uint uVar9;

  if (DAT_81c2b18c != '\0') {
    return;
  }
  uVar4 = 0;
  iVar8 = 0;
LAB_81c042fc:
  cVar5 = (&DAT_81c2b286)[iVar8 - uVar4];
  if (cVar5 != '\b') {
    uVar3 = FUN_81c04efc(uVar4);
    uVar9 = 0;
    iVar6 = DAT_81c2b164 + uVar3 * 0x10;
    uVar3 = bbk_rand();
    uVar7 = *(ushort *)(iVar6 + 10);
    bVar2 = false;
    bVar1 = (int)uVar3 % 0x3c < (int)(uint)(*(byte *)(iVar6 + 4) >> 1);
    switch(cVar5) {
    default:
      break;
    case '\x01':
    case '\x02':
    case '\x03':
      goto switchD_81c043d0_caseD_1;
    case '\x04':
    case '\a':
      if (!bVar1) goto LAB_81c04450;
      goto LAB_81c0431c;
    case '\x06':
      goto switchD_81c043d0_caseD_6;
    }
  }
switchD_81c043d0_caseD_0:
LAB_81c0431c:
  uVar4 = uVar4 + 1 & 0xff;
  iVar8 = uVar4 << 3;
  if (0x13 < uVar4) {
    return;
  }
  goto LAB_81c042fc;
switchD_81c043d0_caseD_6:
  uVar9 = (uint)(uVar7 >> 3);
  uVar7 = uVar7 - (uVar7 >> 3);
switchD_81c043d0_caseD_1:
  if (bVar1) {
    FUN_81c0108c(uVar4);
LAB_81c04450:
    cVar5 = '\0';
    bVar2 = true;
  }
  if (uVar9 != 0) {
    FUN_81c04468(uVar4);
    FUN_81c044f8('-',uVar4,uVar9);
    *(ushort *)(iVar6 + 10) = uVar7;
  }
  if (!bVar2) goto switchD_81c043d0_caseD_0;
  (&DAT_81c2b286)[iVar8 - uVar4] = cVar5;
  FUN_81c04468(uVar4);
  FUN_81c04590(uVar4,4);
  goto LAB_81c0431c;
}


#undef DAT_81c2b18c
#undef DAT_81c2b164
#undef DAT_81c2b286

#define DAT_81c2b125 (*(byte *)(0x81c2b125u))
#define DAT_81c2b116 (*(byte *)(0x81c2b116u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
/* VA 0x81c04468; body bytes 144 */

void FUN_81c04468(uint param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;

  iVar1 = (param_1 & 0xff) * 7;
  DAT_81c2b125 = (&DAT_81c2b280)[iVar1];
  DAT_81c2b116 = (&DAT_81c2b281)[iVar1];
  uVar2 = 0;
  if (6 < DAT_81c2b125) {
    uVar2 = DAT_81c2b125 - 7 & 0xffff;
  }
  uVar3 = 0;
  if (4 < DAT_81c2b116) {
    uVar3 = DAT_81c2b116 - 5 & 0xffff;
  }
  FUN_81c04b9c(uVar2,uVar3);
  FUN_81c04630(0);
  FUN_81c04d58();
  FUN_81c04f68();
  return;
}


#undef DAT_81c2b125
#undef DAT_81c2b116
#undef DAT_81c2b280
#undef DAT_81c2b281

#define DAT_81c2b150 (*(byte *)(0x81c2b150u))
#define DAT_81c2b160 (*(byte *)(0x81c2b160u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
/* VA 0x81c044f8; body bytes 152 */

void FUN_81c044f8(char param_1,uint param_2,uint param_3)

{
  unsigned char sg_stack[32] __attribute__((aligned(8)));
#define auStack_17 (*(undefined1 (*)[15])(sg_stack + 1))
#define local_18 (*(char *)(sg_stack + 0))

  int iVar1;

  local_18 = param_1;
  FUN_81c0a7e4(param_3 & 0xffff,auStack_17,10);
  iVar1 = (param_2 & 0xff) * 7;
  FUN_81c149dc(((ushort)(byte)(&DAT_81c2b280)[iVar1] - (ushort)DAT_81c2b150) * 0x10 & 0xff,
               ((ushort)(byte)(&DAT_81c2b281)[iVar1] - (ushort)DAT_81c2b160) * 0x10 & 0xff,&local_18
              );
  FUN_81c14164(0x32,'\0');
  return;
}


#undef DAT_81c2b150
#undef DAT_81c2b160
#undef DAT_81c2b280
#undef DAT_81c2b281
#undef auStack_17
#undef local_18

#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
/* VA 0x81c04590; body bytes 160 */

void FUN_81c04590(uint param_1,byte param_2)

{
  int iVar1;
  byte bVar2;

  FUN_81c04630(0);
  iVar1 = (param_1 & 0xff) * 7;
  bVar2 = 1;
  while( true ) {
    FUN_81c04f68();
    if (param_2 < bVar2) break;
    FUN_81c14164(10,'\0');
    FUN_81c047bc((uint)(byte)(&DAT_81c2b280)[iVar1],(uint)(byte)(&DAT_81c2b281)[iVar1],'\x01');
    FUN_81c14164(10,'\0');
    bVar2 = bVar2 + 1;
  }
  return;
}


#undef DAT_81c2b280
#undef DAT_81c2b281

#define DAT_81c2b150 (*(byte *)(0x81c2b150u))
#define DAT_81c2b160 (*(byte *)(0x81c2b160u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
#define DAT_81c2b285 (*(undefined1 *)(0x81c2b285u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c04630; body bytes 396 */

void FUN_81c04630(uint param_1)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  short sVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;

  uVar8 = 0;
  do {
    iVar4 = uVar8 * 7;
    cVar1 = (&DAT_81c2b286)[iVar4];
    if (cVar1 != '\b') {
      uVar7 = (uint)(byte)(&DAT_81c2b280)[iVar4];
      bVar2 = (&DAT_81c2b281)[iVar4];
      uVar9 = (uint)bVar2;
      if ((((DAT_81c2b150 <= uVar7) && (uVar7 < DAT_81c2b150 + 0xf)) && (DAT_81c2b160 <= uVar9)) &&
         (uVar9 < DAT_81c2b160 + 0xf)) {
        uVar3 = FUN_81c06838(uVar8);
        if ((&DAT_81c2b285)[iVar4] == '\0') {
          uVar3 = uVar3 + (param_1 & 0xff) & 0xff;
        }
        sVar5 = ((ushort)bVar2 - (ushort)DAT_81c2b160) * 0x10;
        uVar6 = (uVar7 - DAT_81c2b150) * 0x10 & 0xffff;
        FUN_81c047bc(uVar7,uVar9,'\0');
        FUN_81c04fb4(5,uVar3 + 1 & 0xff,uVar6,sVar5);
        iVar4 = 2;
        if ((cVar1 == '\x02') || (iVar4 = 4, cVar1 == '\x03')) {
          FUN_81c04fb4(0x22,iVar4 + (param_1 & 0xff) + 1 & 0xff,uVar6,sVar5);
        }
      }
    }
    uVar8 = uVar8 + 1 & 0xff;
  } while (uVar8 < 0x14);
  return;
}


#undef DAT_81c2b150
#undef DAT_81c2b160
#undef DAT_81c2b280
#undef DAT_81c2b281
#undef DAT_81c2b285
#undef DAT_81c2b286

#define DAT_81c2b160 (*(byte *)(0x81c2b160u))
#define DAT_81c2b150 (*(byte *)(0x81c2b150u))
#define DAT_81c2b16c (*(int *)(0x81c2b16cu))
#define DAT_81c2b13e (*(ushort *)(0x81c2b13eu))
#define DAT_81c2b128 (*(uint *)(0x81c2b128u))
/* VA 0x81c047bc; body bytes 256 */

void FUN_81c047bc(uint param_1,uint param_2,char param_3)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  ushort uVar4;
  uint uVar5;

  bVar1 = *(byte *)(DAT_81c2b16c +
                   ((((param_2 & 0xff) - (uint)DAT_81c2b160) * 0xf + (param_1 & 0xff)) -
                    (uint)DAT_81c2b150 & 0xff));
  uVar2 = FUN_81c04f40((uint)DAT_81c2b13e,'\x01');
  uVar5 = ((param_1 & 0xff) - (uint)DAT_81c2b150) * 0x10 & 0xff;
  uVar4 = ((short)(param_2 & 0xff) - (ushort)DAT_81c2b160) * 0x10 & 0xff;
  iVar3 = uVar2 + (uint)bVar1 * 0x40 + 6;
  if (param_3 == '\0') {
    FUN_81c14504(uVar5,uVar4,0x10,0x10,iVar3,DAT_81c2b128);
  }
  else {
    FUN_81c14350(uVar5,uVar4,0x10,0x10,iVar3);
  }
  return;
}


#undef DAT_81c2b160
#undef DAT_81c2b150
#undef DAT_81c2b16c
#undef DAT_81c2b13e
#undef DAT_81c2b128


/* VA 0x81c048bc; body bytes 100 */

void FUN_81c048bc(uint param_1)

{
  unsigned char sg_stack[48] __attribute__((aligned(8)));
#define acStack_30 (*(char (*)[24])(sg_stack + 0))
#define acStack_18 (*(char (*)[8])(sg_stack + 24))


  FUN_81c04f18(0x16,acStack_30);
  FUN_81c0a7e4(param_1 & 0xff,acStack_18,10);
  FUN_81c1de70(acStack_30,acStack_18);
  FUN_81c07bc0(acStack_30,1,0xff);
  return;
}


#undef acStack_30
#undef acStack_18

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
#define DAT_81c2b282 (*(undefined1 *)(0x81c2b282u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c04920; body bytes 456 */

void FUN_81c04920(void)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  char *pcVar5;
  byte bVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;

  pcVar5 = g_scratch_buffer_4096;
  uVar10 = 0;
  do {
    iVar4 = uVar10 * 7;
    if ((&DAT_81c2b286)[iVar4] != '\b') {
      uVar7 = FUN_81c04efc(uVar10);
      bVar1 = (&DAT_81c2b280)[iVar4];
      bVar2 = (&DAT_81c2b281)[iVar4];
      iVar9 = DAT_81c2b164 + uVar7 * 0x10;
      uVar8 = bbk_rand();
      uVar8 = (int)uVar8 % 3 & 0xff;
      if (*(byte *)(iVar9 + 7) < 100) {
        cVar3 = (&DAT_81c2b282)[iVar4];
      }
      else {
        FUN_81c04468(uVar10);
        bVar6 = *(char *)(iVar9 + 2) + 1;
        *(char *)(iVar9 + 7) = *(char *)(iVar9 + 7) + -100;
        *(byte *)(iVar9 + 2) = bVar6;
        if (0x14 < bVar6) {
          *(undefined1 *)(iVar9 + 2) = 0x14;
        }
        FUN_81c04ae8(0,5,(ushort)bVar1,(ushort)bVar2);
        FUN_81c04f18(uVar8 + 0x27 & 0xff,pcVar5);
        FUN_81c18024((uchar)uVar7,pcVar5);
        cVar3 = (&DAT_81c2b282)[iVar4];
      }
      if ((cVar3 == '\0') || (*(short *)(iVar9 + 10) == 0)) {
        FUN_81c04468(uVar10);
        (&DAT_81c2b286)[iVar4] = 8;
        FUN_81c04ae8(6,0xb,(ushort)bVar1,(ushort)bVar2);
        FUN_81c04f18(uVar8 + 0x2a & 0xff,pcVar5);
        FUN_81c18024((uchar)uVar7,pcVar5);
      }
    }
    uVar10 = uVar10 + 1 & 0xff;
  } while (uVar10 < 0x14);
  return;
}


#undef DAT_81c2b164
#undef DAT_81c2b280
#undef DAT_81c2b281
#undef DAT_81c2b282
#undef DAT_81c2b286
#undef g_scratch_buffer_4096

#define DAT_81c2b150 (*(byte *)(0x81c2b150u))
#define DAT_81c2b160 (*(byte *)(0x81c2b160u))
/* VA 0x81c04ae8; body bytes 180 */

void FUN_81c04ae8(uint param_1,uint param_2,ushort param_3,ushort param_4)

{
  ushort uVar1;
  ushort uVar2;

  uVar1 = (ushort)DAT_81c2b150;
  if ((uVar1 <= param_3) && (param_3 < (ushort)(uVar1 + 0xf))) {
    uVar2 = (ushort)DAT_81c2b160;
    if (uVar2 <= param_4) {
      if (param_4 < (ushort)(uVar2 + 0xf)) {
        FUN_81c06a70(0x1b,param_1 & 0xff,param_2 & 0xff,0,(param_3 - uVar1) * 0x10,
                     (param_4 - uVar2) * 0x10);
      }
    }
  }
  return;
}


#undef DAT_81c2b150
#undef DAT_81c2b160

#define DAT_81c2b13e (*(ushort *)(0x81c2b13eu))
#define DAT_81c2b16c (*(int *)(0x81c2b16cu))
#define DAT_81c2b128 (*(uint *)(0x81c2b128u))
/* VA 0x81c04b9c; body bytes 196 */

void FUN_81c04b9c(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;

  FUN_81c04c60(param_1 & 0xffff,param_2 & 0xffff);
  uVar1 = FUN_81c04f40((uint)DAT_81c2b13e,'\x01');
  uVar2 = 0;
  uVar3 = 0;
  do {
    FUN_81c14504((uVar2 + (uVar3 >> 3) * -0xf) * 0x10 & 0xffff,(short)(uVar3 >> 3) * 0x10,0x10,0x10,
                 uVar1 + 6 + (uint)*(byte *)(DAT_81c2b16c + uVar2) * 0x40,DAT_81c2b128);
    uVar2 = uVar2 + 1 & 0xffff;
    uVar3 = (uint)((ulonglong)uVar2 * 0x88888889 >> 0x20);
  } while (uVar2 < 0xe1);
  return;
}


#undef DAT_81c2b13e
#undef DAT_81c2b16c
#undef DAT_81c2b128

#define DAT_81c2b184 (*(byte *)(0x81c2b184u))
#define DAT_81c2b117 (*(byte *)(0x81c2b117u))
#define DAT_81c2b262 (*(ushort *)(0x81c2b262u))
#define DAT_81c2b160 (*(undefined1 *)(0x81c2b160u))
#define DAT_81c2b150 (*(undefined1 *)(0x81c2b150u))
#define DAT_81c2b16c (*(void * *)(0x81c2b16cu))
/* VA 0x81c04c60; body bytes 248 */

void FUN_81c04c60(uint param_1,uint param_2)

{
  uint uVar1;
  byte bVar2;
  void *src;
  void *dst;
  uint uVar3;
  uint uVar4;

  uVar4 = param_1 & 0xffff;
  uVar3 = param_2 & 0xffff;
  if ((uint)DAT_81c2b184 < uVar4 + 0xf) {
    uVar4 = DAT_81c2b184 - 0xf & 0xffff;
  }
  if ((uint)DAT_81c2b117 < uVar3 + 0xf) {
    uVar3 = DAT_81c2b117 - 0xf & 0xffff;
  }
  DAT_81c2b160 = (undefined1)uVar3;
  DAT_81c2b150 = (undefined1)uVar4;
  uVar1 = FUN_81c04f40((uint)DAT_81c2b262,'\x01');
  bVar2 = 0;
  src = (void *)(uVar3 * DAT_81c2b184 + uVar1 + 0x10 + uVar4);
  dst = DAT_81c2b16c;
  do {
    bbk_memcpy(dst,src,0xf);
    bVar2 = bVar2 + 1;
    src = (void *)((int)src + (uint)DAT_81c2b184);
    dst = (void *)((int)dst + 0xf);
  } while (bVar2 < 0xf);
  return;
}


#undef DAT_81c2b184
#undef DAT_81c2b117
#undef DAT_81c2b262
#undef DAT_81c2b160
#undef DAT_81c2b150
#undef DAT_81c2b16c

#define DAT_81c2b128 (*(uint *)(0x81c2b128u))
#define DAT_81c2b125 (*(byte *)(0x81c2b125u))
#define DAT_81c2b116 (*(byte *)(0x81c2b116u))
/* VA 0x81c04d58; body bytes 220 */

void FUN_81c04d58(void)

{
  unsigned char sg_stack[61] __attribute__((aligned(8)));
#define auStack_50 (*(undefined1 (*)[40])(sg_stack + 0))
#define acStack_28 (*(char (*)[4])(sg_stack + 40))
#define local_24 (*(undefined1 *)(sg_stack + 44))

  uint uVar1;

  FUN_81c15210(0x6a,0xf3,0x9a,0xff,DAT_81c2b128);
  uVar1 = FUN_81c06318((ushort)DAT_81c2b125,(ushort)DAT_81c2b116);
  if (uVar1 == 0xff) {
    uVar1 = FUN_81c0620c((uint)DAT_81c2b125,(uint)DAT_81c2b116);
    FUN_81c04f18(7,auStack_50);
    bbk_memcpy(acStack_28,auStack_50 + (uVar1 & 0x3f) * 4,4);
    local_24 = 0;
  }
  else {
    uVar1 = FUN_81c04efc(uVar1);
    sango_load_named_text((uchar)uVar1,acStack_28);
  }
  FUN_81c04f8c(0x6a,0xf3,acStack_28);
  return;
}


#undef DAT_81c2b128
#undef DAT_81c2b125
#undef DAT_81c2b116
#undef auStack_50
#undef acStack_28
#undef local_24

#define DAT_81c2b18c (*(char *)(0x81c2b18cu))
#define DAT_81c2b126 (*(byte *)(0x81c2b126u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c04e34; body bytes 200 */

void FUN_81c04e34(char param_1)

{
  int iVar1;
  uint uVar2;

  if (DAT_81c2b18c == '\0') {
    if ((&DAT_81c2b286)[(uint)DAT_81c2b126 * 7] == '\b') {
      DAT_81c2b18c = 1;
      if (DAT_81c2b126 != 10) {
        DAT_81c2b18c = 2;
      }
      return;
    }
    if (param_1 == '\0') {
      DAT_81c2b18c = '\x01';
      uVar2 = 10;
    }
    else {
      uVar2 = 0;
      DAT_81c2b18c = '\x02';
    }
    if (uVar2 < 0x14) {
      while( true ) {
        iVar1 = uVar2 * 7;
        uVar2 = uVar2 + 1 & 0xff;
        if ((&DAT_81c2b286)[iVar1] != '\b') break;
        if (0x13 < uVar2) {
          return;
        }
      }
      DAT_81c2b18c = '\0';
    }
  }
  return;
}


#undef DAT_81c2b18c
#undef DAT_81c2b126
#undef DAT_81c2b286

#define DAT_81c2b268 (*(undefined1 *)(0x81c2b268u))
/* VA 0x81c04efc; body bytes 28 */

uint FUN_81c04efc(uint param_1)

{
  return (byte)(&DAT_81c2b268)[param_1 & 0xff] - 1 & 0xff;
}


#undef DAT_81c2b268


/* VA 0x81c04f18; body bytes 40 */

void FUN_81c04f18(uint param_1,void *param_2)

{
  FUN_81c154d8(1,param_1 & 0xff,param_2);
  return;
}




#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c04f40; body bytes 40 */

uint FUN_81c04f40(uint kind,char index)

{
  uint uVar1;

  uVar1 = FUN_81c152f0(kind & 0xffff,index,g_sango_package_data);
  return uVar1;
}


#undef g_sango_package_data

#define DAT_81c2b128 (*(uint *)(0x81c2b128u))
/* VA 0x81c04f68; body bytes 36 */

void FUN_81c04f68(void)

{
  FUN_81c14f98(DAT_81c2b128);
  return;
}


#undef DAT_81c2b128

#define DAT_81c2b128 (*(uint *)(0x81c2b128u))
/* VA 0x81c04f8c; body bytes 40 */

void FUN_81c04f8c(short param_1,short param_2,char *param_3)

{
  FUN_81c15134(param_1,param_2,param_3,DAT_81c2b128);
  return;
}


#undef DAT_81c2b128


/* VA 0x81c04fb4; body bytes 44 */

void FUN_81c04fb4(uint param_1,uint param_2,uint param_3,short param_4)

{
  FUN_81c077bc(param_1 & 0xffff,param_2 & 0xff,param_3 & 0xffff,param_4,'\0');
  return;
}




#define DAT_81c2b260 (*(char *)(0x81c2b260u))
#define DAT_81c2b17d (*(undefined1 *)(0x81c2b17du))
#define DAT_81c2b18c (*(char *)(0x81c2b18cu))
#define DAT_81c2b188 (*(undefined1 *)(0x81c2b188u))
#define DAT_81c2b126 (*(undefined1 *)(0x81c2b126u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c04fe0; body bytes 520 */

undefined4 FUN_81c04fe0(void)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
#define abStack_10 (*(byte (*)[8])(sg_stack + 0))

  int iVar1;
  uint uVar2;

  DAT_81c2b17d = 3;
  DAT_81c2b18c = '\0';
  DAT_81c2b188 = 0;
  if (DAT_81c2b260 == '\x01') {
    DAT_81c2b126 = 0;
  }
  else {
    DAT_81c2b126 = 10;
  }
  FUN_81c00bfc();
  if (DAT_81c2b18c == '\0') {
    if (DAT_81c2b260 == '\x02') {
      FUN_81c001a0();
    }
    else {
      FUN_81c03c98();
      FUN_81c03f6c();
      FUN_81c04468(10);
      FUN_81c14164(100,'\0');
      FUN_81c04468(0);
      FUN_81c14164(100,'\0');
      FUN_81c04920();
      FUN_81c04e34('\0');
      FUN_81c04e34('\x01');
    }
  }
  do {
    if (DAT_81c2b18c != '\0') {
      return 0;
    }
    FUN_81c04064();
    FUN_81c03020();
    while (DAT_81c2b18c == '\0') {
      iVar1 = FUN_81c02f4c(abStack_10);
      if (iVar1 == 0) break;
      uVar2 = FUN_81c03654(abStack_10);
      if ((DAT_81c2b260 == '\0') && (uVar2 == 5)) {
        DAT_81c2b18c = '\x02';
      }
      else {
        FUN_81c04e34('\x01');
      }
    }
    if (DAT_81c2b18c == '\0') {
      uVar2 = 0;
      DAT_81c2b18c = '\x02';
      iVar1 = 0;
      do {
        iVar1 = iVar1 - uVar2;
        uVar2 = uVar2 + 1 & 0xff;
        if ((&DAT_81c2b286)[iVar1] != '\b') {
          DAT_81c2b18c = '\0';
          break;
        }
        iVar1 = uVar2 << 3;
      } while (uVar2 < 10);
    }
    FUN_81c0142c();
  } while( true );
}


#undef DAT_81c2b260
#undef DAT_81c2b17d
#undef DAT_81c2b18c
#undef DAT_81c2b188
#undef DAT_81c2b126
#undef DAT_81c2b286
#undef abStack_10

#define DAT_81c2b260 (*(char *)(0x81c2b260u))
#define DAT_81c2b17d (*(undefined1 *)(0x81c2b17du))
#define DAT_81c2b18c (*(char *)(0x81c2b18cu))
#define DAT_81c2b188 (*(undefined1 *)(0x81c2b188u))
#define DAT_81c2b126 (*(undefined1 *)(0x81c2b126u))
/* VA 0x81c051e8; body bytes 228 */

void FUN_81c051e8(void)

{
  DAT_81c2b17d = 3;
  DAT_81c2b18c = '\0';
  DAT_81c2b188 = 0;
  if (DAT_81c2b260 == '\x01') {
    DAT_81c2b126 = 0;
  }
  else {
    DAT_81c2b126 = 10;
  }
  FUN_81c00bfc();
  if (DAT_81c2b18c == '\0') {
    if (DAT_81c2b260 == '\x02') {
      FUN_81c001a0();
    }
    else {
      FUN_81c03c98();
      FUN_81c03f6c();
      FUN_81c04468(10);
      FUN_81c14164(100,'\0');
      FUN_81c04468(0);
      FUN_81c14164(100,'\0');
      FUN_81c04920();
      FUN_81c04e34('\0');
      FUN_81c04e34('\x01');
    }
  }
  return;
}


#undef DAT_81c2b260
#undef DAT_81c2b17d
#undef DAT_81c2b18c
#undef DAT_81c2b188
#undef DAT_81c2b126

#define DAT_81c2b18c (*(char *)(0x81c2b18cu))
#define DAT_81c2b260 (*(char *)(0x81c2b260u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c052cc; body bytes 248 */

void FUN_81c052cc(void)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
#define abStack_10 (*(byte (*)[8])(sg_stack + 0))

  int iVar1;
  uint uVar2;

  if (DAT_81c2b18c == '\0') {
    do {
      iVar1 = FUN_81c02f4c(abStack_10);
      if (iVar1 == 0) break;
      uVar2 = FUN_81c03654(abStack_10);
      if ((DAT_81c2b260 == '\0') && (uVar2 == 5)) {
        DAT_81c2b18c = '\x02';
      }
      else {
        FUN_81c04e34('\x01');
      }
    } while (DAT_81c2b18c == '\0');
  }
  if (DAT_81c2b18c == '\0') {
    uVar2 = 0;
    DAT_81c2b18c = '\x02';
    do {
      iVar1 = uVar2 * 7;
      uVar2 = uVar2 + 1 & 0xff;
      if ((&DAT_81c2b286)[iVar1] != '\b') {
        DAT_81c2b18c = 0;
        return;
      }
    } while (uVar2 < 10);
  }
  return;
}


#undef DAT_81c2b18c
#undef DAT_81c2b260
#undef DAT_81c2b286
#undef abStack_10


/* VA 0x81c053c4; body bytes 60 */

void FUN_81c053c4(char param_1)

{
  if (param_1 == '\0') {
    FUN_81c041f8('\0');
  }
  else {
    FUN_81c0343c();
  }
  return;
}





/* VA 0x81c05400; body bytes 60 */

void FUN_81c05400(char param_1)

{
  if (param_1 == '\0') {
    FUN_81c041f8('\0');
  }
  else {
    FUN_81c027f0();
  }
  return;
}




#define DAT_81c2b260 (*(char *)(0x81c2b260u))
#define DAT_81c2b17d (*(undefined1 *)(0x81c2b17du))
#define DAT_81c2b18c (*(undefined1 *)(0x81c2b18cu))
#define DAT_81c2b188 (*(undefined1 *)(0x81c2b188u))
#define DAT_81c2b126 (*(undefined1 *)(0x81c2b126u))
/* VA 0x81c0543c; body bytes 100 */

undefined4 FUN_81c0543c(void)

{
  DAT_81c2b17d = 3;
  DAT_81c2b18c = 0;
  DAT_81c2b188 = 0;
  if (DAT_81c2b260 == '\x01') {
    DAT_81c2b126 = 0;
  }
  else {
    DAT_81c2b126 = 10;
  }
  FUN_81c00bfc();
  return 0;
}


#undef DAT_81c2b260
#undef DAT_81c2b17d
#undef DAT_81c2b18c
#undef DAT_81c2b188
#undef DAT_81c2b126


/* VA 0x81c054a0; body bytes 68 */

void FUN_81c054a0(void)

{
  FUN_81c03f6c();
  FUN_81c04468(10);
  FUN_81c14164(100,'\0');
  FUN_81c04468(0);
  FUN_81c14164(100,'\0');
  return;
}




#define DAT_81c2b150 (*(byte *)(0x81c2b150u))
#define DAT_81c2b125 (*(byte *)(0x81c2b125u))
#define DAT_81c2b160 (*(byte *)(0x81c2b160u))
#define DAT_81c2b116 (*(byte *)(0x81c2b116u))
/* VA 0x81c054e4; body bytes 200 */

void FUN_81c054e4(void)

{
  byte bVar1;
  byte bVar2;

  bVar1 = DAT_81c2b150 - 1;
  bVar2 = DAT_81c2b160;
  if ((uint)DAT_81c2b150 <= (uint)DAT_81c2b125) {
    bVar1 = DAT_81c2b150;
    bVar2 = DAT_81c2b160 - 1;
    if ((uint)DAT_81c2b160 <= (uint)DAT_81c2b116) {
      bVar1 = DAT_81c2b150 + 1;
      bVar2 = DAT_81c2b160;
      if (((uint)DAT_81c2b125 < DAT_81c2b150 + 0xf) &&
         (bVar1 = DAT_81c2b150, bVar2 = DAT_81c2b160 + 1, (uint)DAT_81c2b116 < DAT_81c2b160 + 0xf))
      {
        return;
      }
    }
  }
  DAT_81c2b160 = bVar2;
  DAT_81c2b150 = bVar1;
  FUN_81c04b9c((uint)DAT_81c2b150,(uint)DAT_81c2b160);
  return;
}


#undef DAT_81c2b150
#undef DAT_81c2b125
#undef DAT_81c2b160
#undef DAT_81c2b116

#define DAT_81c2b125 (*(byte *)(0x81c2b125u))
#define DAT_81c2b116 (*(byte *)(0x81c2b116u))
#define DAT_81c2b161 (*(byte *)(0x81c2b161u))
#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b240 (*(ushort *)(0x81c2b240u))
#define DAT_81c2b242 (*(ushort *)(0x81c2b242u))
#define DAT_81c2b186 (*(undefined2 *)(0x81c2b186u))
#define DAT_81c2b18a (*(undefined2 *)(0x81c2b18au))
#define DAT_81c2b174 (*(undefined2 *)(0x81c2b174u))
#define DAT_81c2b120 (*(undefined2 *)(0x81c2b120u))
#define DAT_81c2b282 (*(undefined1 *)(0x81c2b282u))
#define DAT_81c2b283 (*(undefined1 *)(0x81c2b283u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c055b0; body bytes 776 */

void FUN_81c055b0(void)

{
  unsigned char sg_stack[80] __attribute__((aligned(8)));
#define local_28 (*(ushort (*)[8])(sg_stack + 48))
#define acStack_58 (*(char (*)[16])(sg_stack + 0))
#define auStack_48 (*(undefined1 (*)[32])(sg_stack + 16))

  char *destination;
  uint uVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;

  FUN_81c0ac48(5,5,0xe9,0x139,0,0);
  FUN_81c08e7c(4,4,0xea,0x13a,3,0,0);
  destination = (char *)bbk_alloc(0x96);
  if (destination != (char *)0x0) {
    uVar1 = FUN_81c06318((ushort)DAT_81c2b125,(ushort)DAT_81c2b116);
    if (uVar1 == 0xff) {
      iVar3 = FUN_81c0620c((uint)DAT_81c2b125,(uint)DAT_81c2b116);
      FUN_81c0666c(iVar3 + 0xeU & 0xff,destination);
      DAT_81c2b186 = 8;
      DAT_81c2b18a = 0xe6;
      DAT_81c2b174 = 0x136;
      DAT_81c2b120 = 8;
      FUN_81c149dc(8,8,destination);
    }
    else {
      iVar3 = uVar1 * 7;
      FUN_81c08e7c(0xb6,8,0xe8,0x30,3,0,0);
      local_28[1] = 6;
      local_28[4] = 0xb4;
      local_28[3] = 0x138;
      local_28[5] = 8;
      local_28[0] = 8;
      local_28[6] = 0xe8;
      local_28[2] = 0xe8;
      local_28[7] = 0x32;
      FUN_81c01278(0,uVar1);
      uVar1 = FUN_81c06650(uVar1);
      sango_load_named_text((byte)uVar1,acStack_58);
      FUN_81c07b58(0xd0,0x24,acStack_58);
      pbVar2 = (byte *)FUN_81c152f0(DAT_81c2b161 + 0x2f,'\x01',g_sango_package_data);
      FUN_81c14fb8(0xc3,10,0x18,0x18,(byte)uVar1,pbVar2);
      FUN_81c0666c(0xd,destination);
      iVar4 = DAT_81c2b164 + uVar1 * 0x10;
      if (*(byte *)(iVar4 + 2) < 0x14) {
        FUN_81c060c8(destination,(uint)*(byte *)(iVar4 + 2));
      }
      else {
        destination[5] = 'M';
        destination[6] = 'X';
      }
      FUN_81c0666c(0xc,auStack_48);
      bbk_memcpy(destination + 0xd,auStack_48 + (*(byte *)(iVar4 + 9) & 0x3f) * 4,4);
      FUN_81c060c8(destination,(uint)*(byte *)(iVar4 + 3));
      FUN_81c060c8(destination,(uint)*(byte *)(iVar4 + 4));
      FUN_81c060c8(destination,(uint)*(byte *)(iVar4 + 7));
      FUN_81c060c8(destination,(uint)(byte)(&DAT_81c2b282)[iVar3]);
      FUN_81c060c8(destination,(uint)(byte)(&DAT_81c2b283)[iVar3]);
      FUN_81c060c8(destination,(uint)DAT_81c2b240);
      FUN_81c060c8(destination,(uint)DAT_81c2b242);
      FUN_81c060c8(destination,(uint)*(ushort *)(iVar4 + 10));
      FUN_81c0666c((byte)(&DAT_81c2b286)[iVar3] + 0x1c & 0xff,acStack_58);
      bbk_strcat(destination,acStack_58);
      FUN_81c0791c(local_28,local_28 + 4,destination);
    }
    FUN_81c14164(100,'\x01');
    bbk_free_if_nonnull(destination);
  }
  return;
}


#undef DAT_81c2b125
#undef DAT_81c2b116
#undef DAT_81c2b161
#undef DAT_81c2b164
#undef DAT_81c2b240
#undef DAT_81c2b242
#undef DAT_81c2b186
#undef DAT_81c2b18a
#undef DAT_81c2b174
#undef DAT_81c2b120
#undef DAT_81c2b282
#undef DAT_81c2b283
#undef DAT_81c2b286
#undef g_sango_package_data
#undef local_28
#undef acStack_58
#undef auStack_48

#define DAT_81c2b248 (*(byte *)(0x81c2b248u))
#define DAT_81c2b234 (*(byte *)(0x81c2b234u))
#define DAT_81c2b194 (*(char *)(0x81c2b194u))
#define DAT_81c2b250 (*(ushort * *)(0x81c2b250u))
#define DAT_81c2b266 (*(undefined2 *)(0x81c2b266u))
#define DAT_81c2b168 (*(undefined2 *)(0x81c2b168u))
#define DAT_81c2b128 (*(uint *)(0x81c2b128u))
#define DAT_81c20110 (*(undefined *)(0x81c20110u))
#define DAT_81c2014c (*(undefined *)(0x81c2014cu))
#define DAT_81c2016c (*(undefined *)(0x81c2016cu))
#define DAT_81c2018c (*(undefined *)(0x81c2018cu))
#define DAT_81c201ac (*(undefined *)(0x81c201acu))
#define DAT_81c2b264 (*(undefined2 *)(0x81c2b264u))
#define DAT_81c2b283 (*(undefined1 *)(0x81c2b283u))
#define DAT_81c2b284 (*(undefined1 *)(0x81c2b284u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c058b8; body bytes 1060 */

uint FUN_81c058b8(int param_1)

{
  unsigned char sg_stack[56] __attribute__((aligned(8)));
#define local_43 (*(undefined1 *)(sg_stack + 5))
#define local_28 (*(ushort *)(sg_stack + 32))
#define local_26 (*(ushort (*)[3])(sg_stack + 34))
#define acStack_48 (*(char (*)[5])(sg_stack + 0))
#define uStack_42 (*(undefined1 *)(sg_stack + 6))
#define uStack_41 (*(undefined1 *)(sg_stack + 7))
#define auStack_40 (*(undefined1 (*)[4])(sg_stack + 8))
#define auStack_3c (*(undefined1 (*)[20])(sg_stack + 12))

  char cVar1;
  char cVar2;
  ushort uVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  ushort *puVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;

  uVar8 = (uint)*(byte *)(param_1 + 1);
  uVar9 = (uint)*(byte *)(param_1 + 2);
  uVar10 = (uint)*(byte *)(param_1 + 3);
  pcVar4 = (char *)FUN_81c062d0(uVar8);
  (&DAT_81c2b283)[uVar9 * 7] = (&DAT_81c2b283)[uVar9 * 7] - pcVar4[6];
  FUN_81c0a7c8(acStack_48,0x20,10);
  uVar5 = bbk_rand();
  if (DAT_81c2b248 + 0x14 == 0) {
    trap(7);
  }
  if ((uint)(DAT_81c2b234 >> 1) < ((int)uVar5 % (int)(DAT_81c2b248 + 0x14) & 0xffU)) {
    FUN_81c154d8(0xb,uVar8,acStack_48 + 1);
    local_43 = 0x20;
    FUN_81c0666c(0x1a,&uStack_41);
    FUN_81c07bc0(acStack_48,1,0xff);
    uVar5 = 0;
  }
  else {
    if (DAT_81c2b194 == '\0') {
      FUN_81c154d8(0xb,uVar8,&uStack_42);
      FUN_81c07bc0(acStack_48,1,0);
      cVar1 = pcVar4[1];
    }
    else {
      cVar1 = pcVar4[1];
    }
    (&DAT_81c2b286)[uVar10 * 7] = cVar1;
    if (cVar1 == '\x03') {
      (&DAT_81c2b284)[uVar10 * 7] = 1;
    }
    cVar2 = *pcVar4;
    if (uVar8 == 0x16) {
      FUN_81c06384();
      uVar5 = 8;
    }
    else if (uVar8 == 0x1b) {
      uVar5 = FUN_81c05cdc(uVar10);
      FUN_81c01278(0,uVar9);
    }
    else if (uVar8 == 0x1e) {
      DAT_81c2b168 = DAT_81c2b266;
      FUN_81c0666c(0x37,g_scratch_buffer_4096);
      uVar5 = FUN_81c06650(uVar9);
      FUN_81c18024((uchar)uVar5,g_scratch_buffer_4096);
      FUN_81c14f98(DAT_81c2b128);
      uVar5 = 8;
    }
    else {
      FUN_81c01524((int)pcVar4,&local_28,local_26);
      uVar5 = uVar8 - 1 & 0xff;
      uVar3 = *(ushort *)(&DAT_81c20110 + uVar5 * 2);
      if ((uVar3 != 0) && (DAT_81c2b194 != '\0')) {
        if ((&DAT_81c201ac)[uVar5] != '\0') {
          FUN_81c077bc(0x10,1,0x14,0x31,'\0');
        }
        FUN_81c06a70((uint)uVar3,(uint)(byte)(&DAT_81c2014c)[uVar5],
                     (uint)(byte)(&DAT_81c2016c)[uVar5],0,(byte)(&DAT_81c2018c)[uVar5] + 0x14,0x31);
      }
      if (local_28 == 0) {
        puVar7 = &DAT_81c2b266;
        if (9 < uVar9) {
          puVar7 = &DAT_81c2b264;
        }
        local_28 = local_26[0];
        uVar5 = FUN_81c014bc(puVar7,local_26[0]);
        local_26[0] = (ushort)uVar5;
        uVar5 = 0x19;
      }
      else if (cVar2 == '\0') {
        uVar5 = 0x17;
        uVar8 = FUN_81c014bc(DAT_81c2b250,local_28);
        local_28 = (ushort)uVar8;
      }
      else {
        uVar5 = FUN_81c06650(uVar10);
        iVar6 = FUN_81c07e10(uVar5);
        uVar5 = 0x18;
        uVar8 = FUN_81c014ec(DAT_81c2b250,(uint)local_28,(ushort)iVar6);
        local_28 = (ushort)uVar8;
      }
      if (local_28 != 0) {
        if (DAT_81c2b194 == '\0') {
          FUN_81c065c4('-',uVar10,(uint)local_28);
        }
        else {
          FUN_81c0666c(uVar5,acStack_48);
          FUN_81c149dc(0x3c,0x33,acStack_48);
          FUN_81c05f7c(0x3c,0x59,(uint)local_28);
        }
        FUN_81c14164(0x32,'\0');
      }
      if (cVar1 != '\0') {
        uVar5 = FUN_81c06650(uVar10);
        sango_load_named_text((uchar)uVar5,acStack_48);
        uVar5 = bbk_strlen(acStack_48);
        uVar5 = uVar5 & 0xffff;
        FUN_81c0666c(0x1b,acStack_48 + uVar5);
        FUN_81c0666c((uint)(byte)(cVar1 + 0x1c),auStack_40 + uVar5);
        FUN_81c0666c(0x24,auStack_3c + uVar5);
        FUN_81c14dd8(acStack_48,1);
      }
      uVar5 = FUN_81c06168(local_28);
    }
  }
  return uVar5;
}


#undef DAT_81c2b248
#undef DAT_81c2b234
#undef DAT_81c2b194
#undef DAT_81c2b250
#undef DAT_81c2b266
#undef DAT_81c2b168
#undef DAT_81c2b128
#undef DAT_81c20110
#undef DAT_81c2014c
#undef DAT_81c2016c
#undef DAT_81c2018c
#undef DAT_81c201ac
#undef DAT_81c2b264
#undef DAT_81c2b283
#undef DAT_81c2b284
#undef DAT_81c2b286
#undef g_scratch_buffer_4096
#undef local_43
#undef local_28
#undef local_26
#undef acStack_48
#undef uStack_42
#undef uStack_41
#undef auStack_40
#undef auStack_3c

#define DAT_81c201cc (*(undefined1 *)(0x81c201ccu))
#define DAT_81c201cd (*(undefined1 *)(0x81c201cdu))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
/* VA 0x81c05cdc; body bytes 304 */

uint FUN_81c05cdc(uint param_1)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;

  uVar5 = param_1 & 0xff;
  uVar4 = 0;
  uVar6 = 0;
LAB_81c05d0c:
  do {
    bVar1 = uVar4 < 4;
    do {
      do {
        iVar2 = uVar4 * 2;
        if (!bVar1) {
          return uVar6 >> 1;
        }
        uVar4 = uVar4 + 1 & 0xff;
      } while ((((&DAT_81c2b280)[uVar5 * 7] == 0) &&
               (bVar1 = uVar4 < 4, 0x80 < (byte)(&DAT_81c201cc)[iVar2])) ||
              (((&DAT_81c2b281)[uVar5 * 7] == 0 &&
               (bVar1 = uVar4 < 4, 0x80 < (byte)(&DAT_81c201cd)[iVar2]))));
      uVar3 = FUN_81c06318((ushort)(byte)(&DAT_81c2b280)[uVar5 * 7] +
                           (ushort)(byte)(&DAT_81c201cc)[iVar2] & 0xff,
                           (ushort)(byte)(&DAT_81c2b281)[uVar5 * 7] +
                           (ushort)(byte)(&DAT_81c201cd)[iVar2] & 0xff);
      if (uVar3 == 0xff) goto LAB_81c05d0c;
    } while (((uVar5 < 10) && (bVar1 = uVar4 < 4, uVar3 < 10)) ||
            ((10 < uVar5 && (bVar1 = uVar4 < 4, 10 < uVar3))));
    FUN_81c04590(uVar3,2);
    FUN_81c01278(0,uVar3);
    uVar3 = FUN_81c05e0c(uVar5);
    uVar6 = uVar6 + uVar3 & 0xff;
  } while( true );
}


#undef DAT_81c201cc
#undef DAT_81c201cd
#undef DAT_81c2b280
#undef DAT_81c2b281

#define DAT_81c2b250 (*(ushort * *)(0x81c2b250u))
#define DAT_81c2b194 (*(char *)(0x81c2b194u))
#define DAT_81c2b249 (*(char *)(0x81c2b249u))
#define DAT_81c2b237 (*(byte *)(0x81c2b237u))
#define DAT_81c2b24b (*(byte *)(0x81c2b24bu))
#define DAT_81c2b230 (*(char * *)(0x81c2b230u))
#define DAT_81c2b244 (*(char * *)(0x81c2b244u))
#define DAT_81c201d4 (*(undefined *)(0x81c201d4u))
/* VA 0x81c05e0c; body bytes 368 */

uint FUN_81c05e0c(uint param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;

  uVar1 = FUN_81c0118c();
  uVar2 = FUN_81c014bc(DAT_81c2b250,(ushort)uVar1);
  if (DAT_81c2b194 == '\0') {
    FUN_81c065c4('-',param_1 & 0xff,uVar2);
  }
  else {
    FUN_81c077bc(0x10,1,0x14,0x31,'\0');
    uVar5 = 0x19;
    uVar3 = 0;
    uVar4 = 4;
    if (DAT_81c2b249 != '\a') {
      uVar5 = DAT_81c2b237 + 0x13;
      uVar3 = (uint)(byte)(&DAT_81c201d4)[DAT_81c2b237] * (uint)DAT_81c2b24b & 0xff;
      uVar4 = (uVar3 + (byte)(&DAT_81c201d4)[DAT_81c2b237]) - 1 & 0xff;
    }
    FUN_81c06a70(uVar5,uVar3,uVar4,0,0x14,0x31);
    FUN_81c05f7c(0x3c,0x59,uVar2);
  }
  FUN_81c14164(0x32,'\0');
  if ((byte)(*DAT_81c2b230 - *DAT_81c2b244) < 0xe1) {
    iVar6 = 0x10;
    if (*DAT_81c2b230 != *DAT_81c2b244) {
      iVar6 = 8;
    }
  }
  else {
    iVar6 = 0x18;
  }
  uVar3 = FUN_81c06168((ushort)uVar2);
  return (uint)(uVar1 != uVar2) * iVar6 + uVar3 & 0xff;
}


#undef DAT_81c2b250
#undef DAT_81c2b194
#undef DAT_81c2b249
#undef DAT_81c2b237
#undef DAT_81c2b24b
#undef DAT_81c2b230
#undef DAT_81c2b244
#undef DAT_81c201d4

#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c05f7c; body bytes 332 */

void FUN_81c05f7c(ushort param_1,ushort param_2,uint param_3)

{
  unsigned char sg_stack[36] __attribute__((aligned(8)));
#define local_40 (*(char (*)[16])(sg_stack + 0))
#define local_30 (*(uint *)(sg_stack + 16))

  byte bVar1;
  byte bVar2;
  char cVar3;
  byte *pbVar4;
  ushort uVar5;
  ushort uVar6;
  uint uVar7;

  FUN_81c0a7e4(param_3 & 0xffff,local_40,10);
  local_30 = bbk_strlen(local_40);
  local_30 = local_30 & 0xff;
  pbVar4 = (byte *)FUN_81c152f0(0xf,'\x01',g_sango_package_data);
  bVar1 = *pbVar4;
  bVar2 = pbVar4[2];
  uVar7 = 0;
  if (local_30 != 0) {
    do {
      cVar3 = local_40[uVar7];
      FUN_81c14164(4,'\0');
      uVar5 = 0;
      if (bVar2 != 0) {
        uVar6 = 1;
        do {
          FUN_81c14fb8(param_1 & 0xff,(param_2 & 0xff) - uVar5,(ushort)bVar1,uVar6,cVar3 - 0x30,
                       pbVar4);
          FUN_81c14164(1,'\0');
          uVar5 = uVar6 & 0xff;
          uVar6 = uVar5 + 1;
        } while (uVar5 < bVar2);
      }
      uVar7 = uVar7 + 1 & 0xff;
      param_1 = (param_1 & 0xff) + (ushort)bVar1;
    } while (uVar7 < local_30);
  }
  return;
}


#undef g_sango_package_data
#undef local_40
#undef local_30


/* VA 0x81c060c8; body bytes 160 */

void FUN_81c060c8(char *param_1,uint param_2)

{
  unsigned char sg_stack[32] __attribute__((aligned(8)));
#define acStack_20 (*(char (*)[16])(sg_stack + 0))

  uint uVar1;
  uint uVar2;
  char *dst;

  uVar1 = FUN_81c1b9d4(param_1);
  uVar2 = 0;
  if ((uVar1 & 0xffff) != 0) {
    do {
      dst = param_1 + uVar2;
      uVar2 = uVar2 + 1 & 0xffff;
      if (*dst == '%') break;
      dst = (char *)0x0;
    } while (uVar2 < (uVar1 & 0xffff));
    if (dst != (char *)0x0) {
      FUN_81c0a7e4(param_2 & 0xffff,acStack_20,10);
      uVar1 = FUN_81c1b9d4(acStack_20);
      bbk_memcpy(dst,acStack_20,uVar1 & 0xffff);
    }
  }
  return;
}


#undef acStack_20

#define DAT_81c2b230 (*(byte * *)(0x81c2b230u))
#define DAT_81c2b244 (*(byte * *)(0x81c2b244u))
/* VA 0x81c06168; body bytes 164 */

uint FUN_81c06168(ushort param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;

  uVar3 = (uint)*DAT_81c2b230 - (uint)*DAT_81c2b244 & 0xff;
  uVar1 = FUN_81c07cac(param_1);
  uVar1 = uVar1 >> 2 & 0xff;
  if ((0x80 < uVar3) || (uVar2 = 0, uVar3 < uVar1)) {
    uVar2 = uVar1 - uVar3 & 0xff;
  }
  return (uVar2 + 2 & 0xff) % 100;
}


#undef DAT_81c2b230
#undef DAT_81c2b244

#define DAT_81c2b262 (*(ushort *)(0x81c2b262u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c0620c; body bytes 196 */

undefined4 FUN_81c0620c(uint param_1,uint param_2)

{
  byte bVar1;
  byte *pbVar2;
  undefined4 uVar3;

  pbVar2 = (byte *)FUN_81c152f0((uint)DAT_81c2b262,'\x01',g_sango_package_data);
  uVar3 = 6;
  bVar1 = pbVar2[((uint)*pbVar2 * (param_2 & 0xff) + (param_1 & 0xff) & 0xffff) + 0x10];
  if (bVar1 != 0x29) {
    uVar3 = 7;
  }
  if (bVar1 < 0x10) {
    uVar3 = 2;
    if (bVar1 < 6) {
      uVar3 = 3;
      if (bVar1 < 5) {
        uVar3 = 4;
        if (bVar1 < 4) {
          uVar3 = 5;
          if ((bVar1 < 3) && (uVar3 = 0, bVar1 < 2)) {
            uVar3 = 1;
          }
        }
      }
    }
  }
  return uVar3;
}


#undef DAT_81c2b262
#undef g_sango_package_data

#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c062d0; body bytes 72 */

int FUN_81c062d0(uint param_1)

{
  int iVar1;

  iVar1 = FUN_81c152f0(10,'\x01',g_sango_package_data);
  return iVar1 + (((param_1 & 0xff) - 1) * 0x22 & 0xffff);
}


#undef g_sango_package_data

#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c06318; body bytes 108 */

uint FUN_81c06318(ushort param_1,ushort param_2)

{
  int iVar1;
  uint uVar2;

  uVar2 = 0;
  while( true ) {
    iVar1 = uVar2 * 7;
    if ((((&DAT_81c2b286)[iVar1] != '\b') && ((byte)(&DAT_81c2b280)[iVar1] == param_1)) &&
       ((byte)(&DAT_81c2b281)[iVar1] == param_2)) break;
    uVar2 = uVar2 + 1 & 0xff;
    if (0x13 < uVar2) {
      return 0xff;
    }
  }
  return uVar2;
}


#undef DAT_81c2b280
#undef DAT_81c2b281
#undef DAT_81c2b286

#define DAT_81c2b17d (*(byte *)(0x81c2b17du))
/* VA 0x81c06384; body bytes 188 */

void FUN_81c06384(void)

{
  uint uVar1;

  uVar1 = bbk_rand();
  uVar1 = (int)uVar1 % 5 + 1;
  DAT_81c2b17d = (byte)uVar1;
  FUN_81c077bc((uVar1 & 0xff) + 0x1b,1,0x14,0x31,'\x01');
  FUN_81c077bc(9,(uint)DAT_81c2b17d,0x4b,0xf3,'\x01');
  FUN_81c077bc(9,(uint)DAT_81c2b17d,0x4b,0xf3,'\0');
  FUN_81c14164(0x32,'\0');
  return;
}


#undef DAT_81c2b17d

#define DAT_81c2b128 (*(uint *)(0x81c2b128u))
#define DAT_81c2b18c (*(undefined1 *)(0x81c2b18cu))
#define DAT_81c2b114 (*(undefined1 *)(0x81c2b114u))
#define DAT_81c2b171 (*(undefined1 *)(0x81c2b171u))
#define DAT_81c2b194 (*(undefined1 *)(0x81c2b194u))
/* VA 0x81c06440; body bytes 388 */

undefined4 FUN_81c06440(void)

{
  unsigned char sg_stack[80] __attribute__((aligned(8)));
#define local_30 (*(ushort (*)[8])(sg_stack + 48))
#define acStack_60 (*(char (*)[48])(sg_stack + 0))

  uint uVar1;
  uint uVar2;
  byte *unaff_s2;

  local_30[2] = 0x38;
  local_30[4] = 0x6b;
  local_30[6] = 0x83;
  local_30[3] = 0x44;
  local_30[1] = 8;
  local_30[5] = 0x93;
  local_30[7] = 0xab;
  local_30[0] = 8;
  uVar2 = 0x9f;
  uVar1 = 0;
  do {
    FUN_81c0666c(9,acStack_60);
    uVar1 = FUN_81c07068(local_30,uVar1,acStack_60);
    if (uVar1 == 2) {
      unaff_s2 = &DAT_81c2b194;
      uVar2 = 10;
    }
    else if ((int)uVar1 < 3) {
      if (uVar1 == 0) {
LAB_81c06534:
        FUN_81c14f98(DAT_81c2b128);
        return 0xff;
      }
      if (uVar1 == 1) {
        DAT_81c2b18c = 2;
        goto LAB_81c06534;
      }
    }
    else if (uVar1 == 4) {
      unaff_s2 = &DAT_81c2b114;
      uVar2 = 10;
    }
    else if ((int)uVar1 < 4) {
      unaff_s2 = &DAT_81c2b171;
      uVar2 = 0xb;
    }
    else if (uVar1 == 0xff) {
      FUN_81c14f98(DAT_81c2b128);
      return 1;
    }
    FUN_81c0666c(uVar2,acStack_60);
    uVar2 = FUN_81c07068(local_30 + 4,(uint)*unaff_s2,acStack_60);
    if (uVar2 != 0xff) {
      *unaff_s2 = (byte)uVar2;
    }
    FUN_81c14f98(DAT_81c2b128);
  } while( true );
}


#undef DAT_81c2b128
#undef DAT_81c2b18c
#undef DAT_81c2b114
#undef DAT_81c2b171
#undef DAT_81c2b194
#undef local_30
#undef acStack_60

#define DAT_81c2b150 (*(byte *)(0x81c2b150u))
#define DAT_81c2b160 (*(byte *)(0x81c2b160u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
/* VA 0x81c065c4; body bytes 140 */

void FUN_81c065c4(char param_1,uint param_2,uint param_3)

{
  unsigned char sg_stack[32] __attribute__((aligned(8)));
#define local_18 (*(char *)(sg_stack + 0))
#define auStack_17 (*(undefined1 (*)[15])(sg_stack + 1))

  int iVar1;

  local_18 = param_1;
  FUN_81c0a7e4(param_3 & 0xffff,auStack_17,10);
  iVar1 = (param_2 & 0xff) * 7;
  FUN_81c149dc(((ushort)(byte)(&DAT_81c2b280)[iVar1] - (ushort)DAT_81c2b150) * 0x10 & 0xff,
               ((ushort)(byte)(&DAT_81c2b281)[iVar1] - (ushort)DAT_81c2b160) * 0x10 & 0xff,&local_18
              );
  return;
}


#undef DAT_81c2b150
#undef DAT_81c2b160
#undef DAT_81c2b280
#undef DAT_81c2b281
#undef local_18
#undef auStack_17

#define DAT_81c2b268 (*(undefined1 *)(0x81c2b268u))
/* VA 0x81c06650; body bytes 28 */

uint FUN_81c06650(uint param_1)

{
  return (byte)(&DAT_81c2b268)[param_1 & 0xff] - 1 & 0xff;
}


#undef DAT_81c2b268


/* VA 0x81c0666c; body bytes 40 */

void FUN_81c0666c(uint param_1,void *param_2)

{
  FUN_81c154d8(1,param_1 & 0xff,param_2);
  return;
}




#define DAT_81c2b172 (*(undefined1 *)(0x81c2b172u))
#define DAT_81c2b148 (*(undefined1 *)(0x81c2b148u))
#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
#define DAT_81c2b283 (*(undefined1 *)(0x81c2b283u))
#define DAT_81c2b285 (*(undefined1 *)(0x81c2b285u))
/* VA 0x81c06694; body bytes 420 */

uint FUN_81c06694(uchar *record)

{
  byte bVar1;
  byte bVar2;
  undefined1 uVar3;
  uint uVar4;
  uint unaff_s2;
  int iVar5;
  uint uVar6;

  uVar6 = (uint)record[2];
  iVar5 = uVar6 * 7;
  (&DAT_81c2b285)[iVar5] = 1;
  FUN_81c01278(0,uVar6);
  FUN_81c01278(1,(uint)record[3]);
  bVar1 = *record;
  if (bVar1 == 1) {
    unaff_s2 = FUN_81c058b8((int)record);
  }
  else if (bVar1 < 2) {
    if (bVar1 == 0) {
      unaff_s2 = FUN_81c05e0c((uint)record[3]);
    }
  }
  else {
    if (bVar1 != 3) {
      if (bVar1 != 0xff) {
        return unaff_s2;
      }
      (&DAT_81c2b280)[iVar5] = DAT_81c2b172;
      uVar3 = DAT_81c2b148;
      (&DAT_81c2b285)[iVar5] = 0;
      (&DAT_81c2b281)[iVar5] = uVar3;
      FUN_81c04468(uVar6);
    }
    uVar4 = FUN_81c06650(uVar6);
    iVar5 = DAT_81c2b164 + uVar4 * 0x10;
    bVar1 = *(byte *)(iVar5 + 4);
    uVar4 = FUN_81c07cac((ushort)*(byte *)(iVar5 + 3));
    bVar2 = (&DAT_81c2b283)[uVar6 * 7];
    if ((uint)bVar2 <
        (((((uint)bVar1 * 0x50) / 100 + (uVar4 >> 1 & 0xff) + (uint)*(byte *)(iVar5 + 2)) *
         (uint)*(byte *)(iVar5 + 8)) / 100 & 0xff)) {
      (&DAT_81c2b283)[uVar6 * 7] = bVar2 + 1;
    }
    unaff_s2 = 0;
  }
  return unaff_s2;
}


#undef DAT_81c2b172
#undef DAT_81c2b148
#undef DAT_81c2b164
#undef DAT_81c2b280
#undef DAT_81c2b281
#undef DAT_81c2b283
#undef DAT_81c2b285

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c06838; body bytes 184 */

uint FUN_81c06838(uint param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;

  uVar4 = param_1 & 0xff;
  iVar2 = uVar4 * 7;
  uVar1 = FUN_81c06650(uVar4);
  if (((&DAT_81c2b286)[iVar2] == '\x06') || ((&DAT_81c2b286)[iVar2] == '\x01')) {
    uVar3 = 0xe;
  }
  else {
    iVar2 = FUN_81c0620c((uint)(byte)(&DAT_81c2b280)[iVar2],(uint)(byte)(&DAT_81c2b281)[iVar2]);
    uVar3 = 0xc;
    if (iVar2 != 7) {
      uVar3 = (*(byte *)(uVar1 * 0x10 + DAT_81c2b164 + 9) & 0x7f) << 1;
    }
  }
  if (9 < uVar4) {
    uVar3 = uVar3 + 0x10 & 0xff;
  }
  return uVar3;
}


#undef DAT_81c2b164
#undef DAT_81c2b280
#undef DAT_81c2b281
#undef DAT_81c2b286

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b283 (*(undefined1 *)(0x81c2b283u))
/* VA 0x81c068f0; body bytes 228 */

void FUN_81c068f0(uint param_1)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;

  uVar3 = FUN_81c06650(param_1 & 0xff);
  iVar4 = DAT_81c2b164 + uVar3 * 0x10;
  bVar1 = *(byte *)(iVar4 + 4);
  uVar3 = FUN_81c07cac((ushort)*(byte *)(iVar4 + 3));
  bVar2 = (&DAT_81c2b283)[(param_1 & 0xff) * 7];
  if ((uint)bVar2 <
      (((((uint)bVar1 * 0x50) / 100 + (uVar3 >> 1 & 0xff) + (uint)*(byte *)(iVar4 + 2)) *
       (uint)*(byte *)(iVar4 + 8)) / 100 & 0xff)) {
    (&DAT_81c2b283)[(param_1 & 0xff) * 7] = bVar2 + 1;
  }
  return;
}


#undef DAT_81c2b164
#undef DAT_81c2b283

#define DAT_81c2b125 (*(char *)(0x81c2b125u))
#define DAT_81c2b116 (*(char *)(0x81c2b116u))
#define DAT_81c2b280 (*(undefined1 *)(0x81c2b280u))
#define DAT_81c2b281 (*(undefined1 *)(0x81c2b281u))
#define DAT_81c2b285 (*(undefined1 *)(0x81c2b285u))
#define DAT_81c2b286 (*(undefined1 *)(0x81c2b286u))
/* VA 0x81c069d4; body bytes 148 */

uint FUN_81c069d4(void)

{
  char cVar1;
  int iVar2;
  uint uVar3;

  uVar3 = 0;
  while( true ) {
    iVar2 = uVar3 * 7;
    cVar1 = (&DAT_81c2b286)[iVar2];
    if (((cVar1 != '\b') && ((&DAT_81c2b280)[iVar2] == DAT_81c2b125)) &&
       ((&DAT_81c2b281)[iVar2] == DAT_81c2b116)) break;
    uVar3 = uVar3 + 1 & 0xff;
    if (9 < uVar3) {
      return 0xff;
    }
  }
  if ((&DAT_81c2b285)[iVar2] != '\0') {
    return 0xff;
  }
  if (cVar1 == '\x01') {
    return 0xff;
  }
  if (cVar1 != '\x06') {
    return uVar3;
  }
  return 0xff;
}


#undef DAT_81c2b125
#undef DAT_81c2b116
#undef DAT_81c2b280
#undef DAT_81c2b281
#undef DAT_81c2b285
#undef DAT_81c2b286

#define DAT_81c2b128 (*(uint *)(0x81c2b128u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c06a70; body bytes 1528 */

uint FUN_81c06a70(uint param_1,uint param_2,uint param_3,uint param_4,ushort param_5,short param_6)

{
  unsigned char sg_stack[86] __attribute__((aligned(8)));
  (*(ushort *)(sg_stack + 64)) = param_5;
  (*(short *)(sg_stack + 68)) = param_6;
#define local_30 (*(uint *)(sg_stack + 0))
#define param_5 (*(ushort *)(sg_stack + 64))
#define param_6 (*(short *)(sg_stack + 68))

  byte bVar1;
  byte bVar2;
  byte bVar3;
  bool bVar4;
  bool bVar5;
  int iVar6;
  byte bVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  byte *pbVar11;
  uint uVar12;
  byte *pbVar13;
  uint uVar14;
  byte *pbVar15;
  uint uVar16;
  uint uVar17;
  byte *pbVar18;
  uint uVar19;
  int iVar20;
  int iVar21;

  uVar10 = param_3 & 0xff;
  uVar19 = param_2 & 0xff;
  iVar8 = FUN_81c152f0(param_1 & 0xffff,'\x01',g_sango_package_data);
  iVar6 = g_scratch_buffer_4096;
  bVar4 = true;
  bVar5 = true;
  if (iVar8 == 0) {
    FUN_81c15834(param_1 & 0xffff);
  }
  else {
    iVar20 = iVar8 + 6;
    bVar7 = *(byte *)(iVar8 + 3);
    iVar21 = g_scratch_buffer_4096 + 400;
    pbVar15 = (byte *)(iVar20 + (uint)*(byte *)(iVar8 + 2) * 5);
    pbVar18 = (byte *)(g_scratch_buffer_4096 + 500);
    uVar17 = 0;
    if (-1 < (int)(uVar10 - uVar19)) {
      do {
        iVar8 = (uVar17 + uVar19) * 5 + iVar20;
        *(undefined1 *)(iVar21 + uVar17) = *(undefined1 *)(iVar8 + 3);
        pbVar11 = pbVar18 + uVar17;
        uVar17 = uVar17 + 1 & 0xff;
        *pbVar11 = *(byte *)(iVar8 + 2);
      } while ((int)uVar17 <= (int)(uVar10 - uVar19));
    }
    uVar17 = 0;
    if (bVar7 != 0) {
      do {
        bVar1 = pbVar15[3];
        bVar2 = pbVar15[2];
        uVar9 = (uint)pbVar15[1] * 0x100 + (uint)*pbVar15;
        bVar3 = pbVar15[5];
        iVar8 = uVar17 * 4;
        uVar17 = uVar17 + 1 & 0xff;
        uVar12 = (uVar9 & 0xffff) >> 2;
        if ((uVar9 & 3) != 0) {
          uVar12 = uVar12 + 1;
        }
        *(byte **)(iVar8 + iVar6) = pbVar15;
        uVar12 = uVar12 * ((uint)bVar1 * 0x100 + (uint)bVar2 & 0xffff) & 0xffff;
        pbVar15 = pbVar15 + ((bVar3 & 1) * uVar12 + uVar12 + 6 & 0xffff);
      } while (uVar17 < bVar7);
    }
    uVar17 = 0;
    local_30 = 0;
    do {
      do {
        uVar12 = 0;
        pbVar15 = pbVar18;
        if (((param_4 & 1) != 0) && (uVar9 = FUN_81c14268(), uVar9 != 0xff)) {
          return uVar9;
        }
        do {
          if (*pbVar15 == 1) {
            pbVar11 = (byte *)((uVar12 + uVar19) * 5 + iVar20);
            bVar4 = true;
            if ((param_4 & 2) != 0) goto LAB_81c06c20;
            pbVar13 = *(byte **)((uint)pbVar11[4] * 4 + iVar6);
            FUN_81c15210(param_5 + *pbVar11,param_6 + (ushort)pbVar11[1],
                         param_5 + *pbVar11 + (ushort)pbVar13[1] * 0x100 + (ushort)*pbVar13 + -1,
                         param_6 + (ushort)pbVar11[1] +
                         (ushort)pbVar13[3] * 0x100 + (ushort)pbVar13[2] + -1,DAT_81c2b128);
            bVar7 = *pbVar15;
          }
          else {
LAB_81c06c20:
            bVar7 = *pbVar15;
          }
          uVar12 = uVar12 + 1 & 0xff;
          if (bVar7 != 0) {
            *pbVar15 = bVar7 - 1;
          }
          pbVar15 = pbVar18 + uVar12;
        } while (uVar12 <= uVar17);
        if (bVar4) {
          uVar12 = 0;
          do {
            pbVar15 = (byte *)((uVar12 + uVar19) * 5 + iVar20);
            if (pbVar18[uVar12] != 0) {
              pbVar11 = *(byte **)((uint)pbVar15[4] * 4 + iVar6);
              uVar16 = (uint)param_5 + (uint)*pbVar15 & 0xffff;
              uVar9 = (uint)pbVar11[1] * 0x100 + (uint)*pbVar11 & 0xffff;
              uVar14 = (uint)pbVar11[3] * 0x100 + (uint)pbVar11[2] & 0xffff;
              if ((pbVar11[5] & 1) == 1) {
                FUN_81c14690(uVar16,param_6 + (ushort)pbVar15[1],uVar9,uVar14,(int)(pbVar11 + 6),
                             DAT_81c2b128);
              }
              else {
                FUN_81c14504(uVar16,param_6 + (ushort)pbVar15[1],uVar9,uVar14,(int)(pbVar11 + 6),
                             DAT_81c2b128);
              }
            }
            uVar12 = uVar12 + 1 & 0xff;
          } while (uVar12 <= local_30);
        }
        uVar12 = local_30;
        if (bVar5) {
          while (uVar12 = uVar12 + 1 & 0xff, local_30 = uVar17, uVar12 <= uVar17) {
            pbVar15 = (byte *)((uVar12 + uVar19) * 5 + iVar20);
            if (pbVar18[uVar12] != 0) {
              pbVar11 = *(byte **)((uint)pbVar15[4] * 4 + iVar6);
              uVar16 = (uint)param_5 + (uint)*pbVar15 & 0xffff;
              uVar9 = (uint)pbVar11[1] * 0x100 + (uint)*pbVar11 & 0xffff;
              uVar14 = (uint)pbVar11[3] * 0x100 + (uint)pbVar11[2] & 0xffff;
              if ((pbVar11[5] & 1) == 1) {
                FUN_81c14690(uVar16,param_6 + (ushort)pbVar15[1],uVar9,uVar14,(int)(pbVar11 + 6),
                             DAT_81c2b128);
              }
              else {
                FUN_81c14504(uVar16,param_6 + (ushort)pbVar15[1],uVar9,uVar14,(int)(pbVar11 + 6),
                             DAT_81c2b128);
              }
            }
          }
        }
        if ((bVar5) || (bVar4)) {
          bVar5 = false;
          bVar4 = false;
          FUN_81c14f98(DAT_81c2b128);
        }
        else {
          uVar12 = FUN_81c14164(1,'\x01');
          if (uVar12 != 0) {
            return uVar12;
          }
        }
        bVar7 = *(byte *)(iVar21 + uVar17);
        if (bVar7 != 0) {
          bVar7 = bVar7 - 1;
          *(byte *)(iVar21 + uVar17) = bVar7;
        }
        uVar12 = uVar17 + uVar19;
        if ((bVar7 < 2) && (uVar12 < uVar10)) {
          bVar5 = true;
          do {
            uVar17 = uVar17 + 1 & 0xff;
            uVar12 = uVar17 + uVar19;
            if (1 < *(byte *)(iVar21 + uVar17)) break;
          } while (uVar12 < uVar10);
        }
      } while (uVar12 < uVar10);
      uVar12 = 0;
      pbVar15 = pbVar18;
      while (*pbVar15 < 2) {
        uVar12 = uVar12 + 1 & 0xff;
        pbVar15 = pbVar18 + uVar12;
        if (uVar17 < uVar12) {
          return 0xff;
        }
      }
    } while (uVar12 <= uVar17);
  }
  return 0xff;
}


#undef DAT_81c2b128
#undef g_scratch_buffer_4096
#undef g_sango_package_data
#undef local_30
#undef param_5
#undef param_6

#define DAT_81c2b13d (*(undefined1 *)(0x81c2b13du))
#define DAT_81c2b120 (*(ushort *)(0x81c2b120u))
#define DAT_81c2b18a (*(ushort *)(0x81c2b18au))
#define DAT_81c2b186 (*(ushort *)(0x81c2b186u))
#define DAT_81c2b174 (*(ushort *)(0x81c2b174u))
#define DAT_81c20c4c (*(uint *)(0x81c20c4cu))
/* VA 0x81c07068; body bytes 1876 */

uint FUN_81c07068(ushort *param_1,uint param_2,char *param_3)

{
  unsigned char sg_stack[68] __attribute__((aligned(8)));
#define local_60 (*(int *)(sg_stack + 0))
#define local_5c (*(int *)(sg_stack + 4))
#define local_40 (*(uint *)(sg_stack + 32))
#define local_3c (*(uint *)(sg_stack + 36))
#define local_38 (*(uint *)(sg_stack + 40))
#define local_34 (*(uint *)(sg_stack + 44))
#define local_30 (*(uint *)(sg_stack + 48))

  bool bVar1;
  bool bVar2;
  short sVar3;
  uint uVar4;
  uint uVar5;
  short sVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;

  DAT_81c2b13d = 0;
  DAT_81c2b174 = param_1[3];
  DAT_81c2b186 = param_1[1];
  DAT_81c2b120 = *param_1;
  DAT_81c2b18a = param_1[2];
  uVar11 = param_2 & 0xff;
  local_34 = (int)((uint)DAT_81c2b174 - (uint)DAT_81c2b186) / 0xc & 0xff;
  local_40 = (int)((uint)DAT_81c2b18a - (uint)DAT_81c2b120) / 6 & 0xff;
  uVar4 = bbk_strlen(param_3);
  if (local_40 == 0) {
    trap(7);
  }
  local_3c = uVar4 / local_40 & 0xff;
  FUN_81c0ac48(DAT_81c2b120 - 3,DAT_81c2b186 - 3,DAT_81c2b18a + 2,DAT_81c2b174 + 2,0,0);
  bVar1 = local_34 < local_3c;
  local_38 = uVar11;
  if (!bVar1) {
    local_38 = 0;
  }
  FUN_81c08e7c(DAT_81c2b120 - 3,DAT_81c2b186 - 3,DAT_81c2b18a + 2,DAT_81c2b174 + 2,3,0,0);
  if (bVar1) {
    FUN_81c0ac48(DAT_81c2b18a + 2,DAT_81c2b186 - 3,DAT_81c2b18a + 6,DAT_81c2b174 + 2,0,0);
    FUN_81c08e7c(DAT_81c2b18a + 2,DAT_81c2b186 - 3,DAT_81c2b18a + 6,DAT_81c2b174 + 2,3,0,0);
    FUN_81c08e7c(DAT_81c2b18a + 2,DAT_81c2b186 - 1,DAT_81c2b18a + 6,DAT_81c2b174,3,0,0);
    if ((int)local_3c < (int)(local_38 + local_34)) {
      local_38 = local_3c - local_34 & 0xff;
    }
  }
  local_30 = local_38 * local_40;
  bVar2 = true;
  iVar10 = uVar11 - local_38;
  FUN_81c149dc(DAT_81c2b120,DAT_81c2b186,param_3 + local_30);
  uVar8 = (uint)(byte)DAT_81c2b186 + iVar10 * 0xc & 0xff;
  iVar9 = uVar8 + 0xc;
  FUN_81c0aae4(DAT_81c2b120,(short)uVar8,DAT_81c2b18a,(short)iVar9,0);
  uVar4 = (uint)(byte)DAT_81c2b186;
  do {
    do {
      if (bVar1) {
        sVar3 = (short)uVar4;
        sVar6 = sVar3 + 2;
        if (bVar2) {
          FUN_81c08e7c(DAT_81c2b18a + 3,sVar3,DAT_81c2b18a + 5,sVar6,0,0,0);
          FUN_81c0886c(DAT_81c2b18a + 4,sVar3 + 1,0,0);
          FUN_81c0886c(DAT_81c2b18a + 4,sVar3 + 1,0,0);
          uVar4 = FUN_81c1e6b0((int)(char)uVar11);
          if ((char)uVar11 < 0) {
            uVar4 = soft_float_add(uVar4,DAT_81c20c4c);
          }
          bVar2 = false;
          uVar5 = FUN_81c1e6b0(local_3c - 1);
          uVar4 = soft_float_div(uVar4,uVar5);
          uVar7 = (uint)DAT_81c2b186;
          uVar5 = FUN_81c1e6b0((DAT_81c2b174 - uVar7) - 3);
          uVar4 = soft_float_mul(uVar4,uVar5);
          uVar5 = FUN_81c1e6b0(uVar7);
          uVar4 = soft_float_add(uVar4,uVar5);
          uVar4 = FUN_81c1df40(uVar4);
          uVar4 = uVar4 & 0xff;
          sVar6 = (short)uVar4 + 2;
          FUN_81c08e7c(DAT_81c2b18a + 3,(short)uVar4,DAT_81c2b18a + 5,sVar6,3,0,0);
        }
        FUN_81c0aae4(DAT_81c2b18a + 3,(short)uVar4,DAT_81c2b18a + 5,sVar6,0);
      }
      FUN_81c1408c(&local_60);
    } while (local_60 != 5);
    FUN_81c0aae4(DAT_81c2b120,(short)uVar8,DAT_81c2b18a,(short)iVar9,0);
    if (local_5c == 0x1c) {
      DAT_81c2b120 = 0;
      DAT_81c2b13d = 1;
      DAT_81c2b174 = 0x140;
      DAT_81c2b186 = 0;
      DAT_81c2b18a = 0xef;
      return uVar11;
    }
    if (local_5c < 0x1d) {
      if (local_5c == 1) {
        DAT_81c2b13d = 1;
        DAT_81c2b174 = 0x140;
        DAT_81c2b18a = 0xef;
        DAT_81c2b120 = 0;
        DAT_81c2b186 = 0;
        return 0xff;
      }
    }
    else {
      if (local_5c == 0x67) {
        if (uVar11 == 0) {
          bVar2 = true;
          local_38 = local_3c - local_34 & 0xff;
          local_30 = local_38 * local_40;
          uVar11 = local_3c - 1 & 0xff;
          iVar10 = uVar11 - local_38;
        }
        else {
          uVar11 = uVar11 - 1 & 0xff;
          bVar2 = true;
          iVar10 = uVar11 - local_38;
          if (local_38 <= uVar11) goto LAB_81c07348;
          local_38 = local_38 - 1 & 0xff;
          local_30 = local_30 - local_40 & 0xffff;
          iVar10 = uVar11 - local_38;
        }
      }
      else {
        if (local_5c != 0x6c) goto LAB_81c07348;
        if (uVar11 == local_3c - 1) {
          uVar11 = 0;
          bVar2 = true;
          iVar10 = 0;
          local_38 = 0;
          local_30 = 0;
        }
        else {
          if ((int)uVar11 < (int)(local_3c - 1)) {
            uVar11 = uVar11 + 1 & 0xff;
            bVar2 = true;
            iVar10 = uVar11 - local_38;
          }
          if (iVar10 < (int)local_34) goto LAB_81c07348;
          local_38 = local_38 + 1 & 0xff;
          local_30 = local_30 + local_40 & 0xffff;
          iVar10 = uVar11 - local_38;
        }
      }
      FUN_81c149dc(DAT_81c2b120,DAT_81c2b186,param_3 + local_30);
    }
LAB_81c07348:
    uVar8 = (uint)(byte)DAT_81c2b186 + iVar10 * 0xc & 0xff;
    iVar9 = uVar8 + 0xc;
    FUN_81c0aae4(DAT_81c2b120,(short)uVar8,DAT_81c2b18a,(short)iVar9,0);
  } while( true );
}


#undef DAT_81c2b13d
#undef DAT_81c2b120
#undef DAT_81c2b18a
#undef DAT_81c2b186
#undef DAT_81c2b174
#undef DAT_81c20c4c
#undef local_60
#undef local_5c
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30

#define DAT_81c2b128 (*(uint *)(0x81c2b128u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c077bc; body bytes 352 */

void FUN_81c077bc(uint param_1,uint param_2,uint param_3,short param_4,char param_5)

{
  unsigned char sg_stack[17] __attribute__((aligned(8)));
  (*(char *)(sg_stack + 0)) = param_5;
#define param_5 (*(char *)(sg_stack + 0))

  byte bVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;

  uVar6 = param_3 & 0xffff;
  pbVar2 = (byte *)FUN_81c152f0(param_1 & 0xffff,'\x01',g_sango_package_data);
  if ((pbVar2 != (byte *)0x0) && ((param_2 & 0xff) <= (uint)pbVar2[4])) {
    uVar3 = (uint)*pbVar2 + (uint)pbVar2[1] * 0x100;
    uVar5 = uVar3 & 0xffff;
    uVar4 = uVar5 >> 2;
    if ((uVar3 & 3) != 0) {
      uVar4 = (uVar5 >> 2) + 1;
    }
    uVar3 = (uint)pbVar2[2] + (uint)pbVar2[3] * 0x100 & 0xffff;
    bVar1 = pbVar2[5];
    pbVar2 = pbVar2 + (((uVar4 * uVar3 & 0xffff) << (bVar1 & 1)) * ((param_2 & 0xff) - 1) & 0xffff)
                      + 6;
    if (param_5 == '\0') {
      if ((bVar1 & 1) == 0) {
        FUN_81c14504(uVar6,param_4,uVar5,uVar3,(int)pbVar2,DAT_81c2b128);
      }
      else {
        FUN_81c14690(uVar6,param_4,uVar5,uVar3,(int)pbVar2,DAT_81c2b128);
      }
    }
    else if ((bVar1 & 1) == 0) {
      FUN_81c14350(uVar6,param_4,uVar5,uVar3,(int)pbVar2);
    }
    else {
      FUN_81c14838(uVar6,param_4,uVar5,uVar3,(int)pbVar2);
    }
  }
  return;
}


#undef DAT_81c2b128
#undef g_sango_package_data
#undef param_5


/* VA 0x81c0791c; body bytes 224 */

void FUN_81c0791c(ushort *param_1,undefined2 *param_2,char *param_3)

{
  unsigned char sg_stack[48] __attribute__((aligned(8)));
#define local_20 (*(ushort (*)[4])(sg_stack + 16))
#define local_18 (*(ushort (*)[4])(sg_stack + 24))
#define local_30 (*(ushort (*)[4])(sg_stack + 0))
#define local_28 (*(ushort (*)[4])(sg_stack + 8))

  int iVar1;
  uint uVar2;

  local_30[0] = *param_1;
  local_28[1] = param_2[1];
  local_28[3] = param_2[3];
  local_20[0] = param_1[2];
  local_18[3] = param_1[3];
  local_28[0] = param_1[1];
  local_20[1] = *param_2;
  local_30[2] = param_2[2];
  uVar2 = 0;
  local_30[1] = local_30[0];
  local_30[3] = local_30[0];
  local_28[2] = local_28[1];
  local_20[2] = local_20[0];
  local_20[3] = local_20[0];
  local_18[0] = local_28[1];
  local_18[1] = local_28[3];
  local_18[2] = local_28[3];
  FUN_81c1b9d4(param_3);
  iVar1 = 0;
  do {
    param_3 = FUN_81c079fc(*(ushort *)((int)local_30 + iVar1),*(ushort *)((int)local_28 + iVar1),
                           *(ushort *)((int)local_20 + iVar1),*(ushort *)((int)local_18 + iVar1),
                           param_3);
    uVar2 = uVar2 + 1 & 0xff;
    if (param_3 == (char *)0x0) {
      return;
    }
    iVar1 = uVar2 << 1;
  } while (uVar2 < 4);
  return;
}


#undef local_20
#undef local_18
#undef local_30
#undef local_28

#define DAT_81c2b18a (*(ushort *)(0x81c2b18au))
#define DAT_81c2b174 (*(ushort *)(0x81c2b174u))
#define DAT_81c2b120 (*(ushort *)(0x81c2b120u))
#define DAT_81c2b186 (*(ushort *)(0x81c2b186u))
/* VA 0x81c079fc; body bytes 292 */

char * FUN_81c079fc(ushort param_1,ushort param_2,ushort param_3,ushort param_4,char *param_5)

{
  unsigned char sg_stack[20] __attribute__((aligned(8)));
  (*(char * *)(sg_stack + 0)) = param_5;
#define param_5 (*(char * *)(sg_stack + 0))

  uint uVar1;
  uint uVar2;
  char *pcVar3;

  pcVar3 = (char *)0x0;
  uVar2 = ((int)((uint)param_3 - (uint)param_1) / 6) * ((int)((uint)param_4 - (uint)param_2) / 0xc)
          & 0xff;
  uVar1 = FUN_81c1b9d4(param_5);
  if (uVar2 <= uVar1) {
    pcVar3 = FUN_81c07b20((int)param_5,uVar2,'|');
    if (pcVar3 == (char *)0x0) {
      pcVar3 = param_5 + uVar2;
      if (uVar2 == 0) {
        return param_5;
      }
    }
    else {
      *pcVar3 = '\0';
      pcVar3 = pcVar3 + 1;
    }
  }
  DAT_81c2b120 = param_1;
  DAT_81c2b174 = param_4;
  DAT_81c2b186 = param_2;
  DAT_81c2b18a = param_3;
  FUN_81c149dc(param_1,param_2,param_5);
  return pcVar3;
}


#undef DAT_81c2b18a
#undef DAT_81c2b174
#undef DAT_81c2b120
#undef DAT_81c2b186
#undef param_5


/* VA 0x81c07b20; body bytes 56 */

char * FUN_81c07b20(int param_1,uint param_2,char param_3)

{
  char *pcVar1;
  uint uVar2;

  uVar2 = param_2 & 0xff;
  do {
    if (uVar2 == 0) {
      return (char *)0x0;
    }
    pcVar1 = (char *)(param_1 + uVar2);
    uVar2 = uVar2 - 1 & 0xff;
  } while (*pcVar1 != param_3);
  return pcVar1;
}





/* VA 0x81c07b58; body bytes 104 */

void FUN_81c07b58(short param_1,ushort param_2,char *param_3)

{
  uint uVar1;

  uVar1 = bbk_strlen(param_3);
  FUN_81c149dc(param_1 - ((short)uVar1 * 3 & 0x7fU),param_2,param_3);
  return;
}




#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c07bc0; body bytes 236 */

void FUN_81c07bc0(char *param_1,ushort param_2,ushort param_3)

{
  ushort uVar1;
  byte *pbVar2;
  uint uVar3;

  pbVar2 = (byte *)FUN_81c152f0(0x1a,'\x01',g_sango_package_data);
  uVar1 = (param_3 & 0xff) * 0xc;
  uVar3 = (int)(0xef - (uint)*pbVar2) >> 1 & 0xff;
  if ((param_3 & 0xff) == 0xff) {
    uVar1 = (ushort)((int)(0x13f - (uint)pbVar2[2]) >> 1);
  }
  FUN_81c14350(uVar3,uVar1 & 0xff,(uint)*pbVar2,(uint)pbVar2[2],(int)(pbVar2 + 6));
  FUN_81c149dc((short)uVar3 + 10,(uVar1 & 0xff) + 6,param_1);
  FUN_81c14164((param_2 & 0xff) * 100,'\x01');
  return;
}


#undef g_sango_package_data


/* VA 0x81c07cac; body bytes 68 */

uint FUN_81c07cac(ushort param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;

  uVar2 = 10;
  uVar1 = 0;
  while( true ) {
    uVar3 = uVar1;
    uVar1 = uVar3 + uVar2 & 0xff;
    if (uVar2 == 0) break;
    if ((uint)param_1 <= uVar1 * uVar1) {
      uVar2 = uVar2 - 1 & 0xff;
      uVar1 = uVar3;
    }
  }
  return uVar3;
}




#define DAT_81c201e0 (*(undefined *)(0x81c201e0u))
/* VA 0x81c07cf0; body bytes 288 */

void FUN_81c07cf0(ushort param_1,ushort param_2,uint param_3,uint param_4,int param_5)

{
  unsigned char sg_stack[108] __attribute__((aligned(8)));
  (*(int *)(sg_stack + 88)) = param_5;
#define param_5 (*(int *)(sg_stack + 88))
#define acStack_48 (*(char (*)[16])(sg_stack + 0))
#define acStack_38 (*(char (*)[16])(sg_stack + 16))

  uint uVar1;
  uint uVar2;
  uint uVar3;
  char *dst;

  dst = acStack_48;
  uVar3 = param_4 & 0xff;
  FUN_81c0a7c8(dst,0x30,0xc);
  uVar2 = *(uint *)(&DAT_81c201e0 + uVar3 * 4);
  if (uVar2 == 0) {
    trap(7);
  }
  FUN_81c0a7e4(param_3 % uVar2,acStack_38,10);
  uVar1 = FUN_81c1b9d4(acStack_38);
  uVar1 = uVar1 & 0xff;
  if ((uVar1 <= uVar3) && (uVar2 <= param_3)) {
    dst = dst + (uVar3 - uVar1);
  }
  bbk_memcpy(dst,acStack_38,uVar1 + 1);
  if (param_5 == 0) {
    FUN_81c149dc(param_1,param_2,acStack_48);
  }
  else {
    FUN_81c15134(param_1,param_2,acStack_48,param_5);
  }
  return;
}


#undef DAT_81c201e0
#undef param_5
#undef acStack_48
#undef acStack_38

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
/* VA 0x81c07e10; body bytes 84 */

int FUN_81c07e10(uint param_1)

{
  int iVar1;

  iVar1 = DAT_81c2b164 + (param_1 & 0xff) * 0x10;
  return ((uint)*(byte *)(iVar1 + 3) + (uint)*(byte *)(iVar1 + 4)) * 10 +
         (uint)*(byte *)(iVar1 + 2) * 100;
}


#undef DAT_81c2b164

#define DAT_81c2b218 (*(int *)(0x81c2b218u))
#define DAT_81c2b21c (*(uint *)(0x81c2b21cu))
#define DAT_81c2b220 (*(uint *)(0x81c2b220u))
#define g_app_frame (*(undefined4 *)(0x81c2b0f4u))
#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
/* VA 0x81c07e70; body bytes 356 */

uint sango_window_proc(uint handle,int message,uint wparam,uint lparam)

{
  uint uVar1;

  DAT_81c2b218 = message;
  if (message < 0x13) {
    if (0xf < message) {
      DAT_81c2b21c = wparam & 0xffff;
      DAT_81c2b220 = lparam;
      return 0;
    }
    if ((message == 1) || (message == 2)) {
      DAT_81c2b21c = wparam & 0xffff;
      DAT_81c2b220 = lparam;
    }
  }
  else {
    if (message == 0x66) {
      bda_sango_gui_end_draw(g_draw_context);
      bda_sango_gui_frame_stop(g_app_frame);
      bda_sango_gui_frame_release(g_app_frame);
      return 0;
    }
    if ((message < 0x67) && (message == 0x60)) {
      g_app_frame = handle;
      g_draw_context = bda_sango_gui_current_draw(handle);
    }
  }
  uVar1 = bda_sango_gui_default_proc(handle,message,wparam,lparam);
  return uVar1;
}


#undef DAT_81c2b218
#undef DAT_81c2b21c
#undef DAT_81c2b220
#undef g_app_frame
#undef g_draw_context

#define g_app_frame (*(undefined4 *)(0x81c2b0f4u))
#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
/* VA 0x81c07fd4; body bytes 300 */

void FUN_81c07fd4(short param_1,short param_2,uint param_3,uint param_4)

{
  int iVar1;
  int iVar2;

  iVar1 = (int)param_1;
  iVar2 = (int)param_2;
  if (((iVar1 + 0xefU & 0xffff) < 0x1df) && ((iVar2 + 0x13fU & 0xffff) < 0x27f)) {
    if (param_3 == 0) {
      if (param_4 != 0) {
        bda_sango_gui_context_copy(0,0,0,0xf0,0x140,g_draw_context,iVar1,iVar2,0);
        bda_sango_gui_request_redraw(g_app_frame,0,0);
      }
    }
    else {
      if (param_4 == 0) {
        param_4 = 0;
        param_3 = g_draw_context;
      }
      bda_sango_gui_context_copy(param_3,0,0,0xf0,0x140,param_4,iVar1,iVar2,0);
    }
  }
  return;
}


#undef g_app_frame
#undef g_draw_context

#define g_app_frame (*(undefined4 *)(0x81c2b0f4u))
#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
/* VA 0x81c08100; body bytes 508 */

void FUN_81c08100(short left,short top,short right,short bottom,uint color,uint target)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
  (*(uint *)(sg_stack + 0)) = color;
  (*(uint *)(sg_stack + 4)) = target;
#define color (*(uint *)(sg_stack + 0))
#define target (*(uint *)(sg_stack + 4))

  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;

  iVar4 = (unsigned short)top;
  iVar3 = (unsigned short)left;
  iVar2 = (unsigned short)(bottom - top + 1);
  iVar1 = (unsigned short)(right - left + 1);
  if (color == 1) {
    uVar5 = 8;
  }
  else if (color == 0) {
    uVar5 = 0xf;
  }
  else if (color == 2) {
    uVar5 = 7;
  }
  else {
    uVar5 = 0x10;
    if (color != 3) goto LAB_81c08188;
  }
  color = (uint)bda_sango_gui_draw_object(uVar5);
LAB_81c08188:
  if (target == 0) {
    bda_sango_gui_draw_guard(1);
    bda_sango_gui_bind_image_resource(g_draw_context,color);
    bda_sango_gui_fill_region(g_draw_context,iVar3,iVar4,iVar1,iVar2);
    bda_sango_gui_request_redraw(g_app_frame,0,0);
    bda_sango_gui_draw_guard(0);
  }
  else {
    bda_sango_gui_bind_image_resource(g_draw_context,color);
    bda_sango_gui_fill_region(g_draw_context,iVar3,iVar4,iVar1,iVar2);
    bda_sango_gui_bind_image_resource(target,color);
    bda_sango_gui_fill_region(target,iVar3,iVar4,iVar1,iVar2);
  }
  return;
}


#undef g_app_frame
#undef g_draw_context
#undef color
#undef target

#define g_app_frame (*(undefined4 *)(0x81c2b0f4u))
/* VA 0x81c082fc; body bytes 832 */

void FUN_81c082fc(short param_1,short param_2,short param_3,short param_4,short param_5,
                 short param_6,int param_7,undefined4 param_8,undefined4 param_9,uint param_10,
                 int param_11)

{
  unsigned char sg_stack[132] __attribute__((aligned(8)));
  (*(short *)(sg_stack + 88)) = param_5;
  (*(short *)(sg_stack + 92)) = param_6;
  (*(int *)(sg_stack + 96)) = param_7;
  (*(undefined4 *)(sg_stack + 100)) = param_8;
  (*(undefined4 *)(sg_stack + 104)) = param_9;
  (*(uint *)(sg_stack + 108)) = param_10;
  (*(int *)(sg_stack + 112)) = param_11;
#define param_5 (*(short *)(sg_stack + 88))
#define local_48 (*(undefined4 *)(sg_stack + 0))
#define param_6 (*(short *)(sg_stack + 92))
#define local_44 (*(int *)(sg_stack + 4))
#define param_7 (*(int *)(sg_stack + 96))
#define local_40 (*(int *)(sg_stack + 8))
#define param_8 (*(undefined4 *)(sg_stack + 100))
#define local_3c (*(undefined4 *)(sg_stack + 12))
#define param_9 (*(undefined4 *)(sg_stack + 104))
#define local_38 (*(undefined1 *)(sg_stack + 16))
#define param_10 (*(uint *)(sg_stack + 108))
#define local_37 (*(undefined1 *)(sg_stack + 17))
#define param_11 (*(int *)(sg_stack + 112))
#define local_34 (*(int *)(sg_stack + 20))
#define local_30 (*(int *)(sg_stack + 24))
#define local_28 (*(byte *)(sg_stack + 32))
#define local_27 (*(byte *)(sg_stack + 33))
#define local_26 (*(byte *)(sg_stack + 34))
#define local_25 (*(byte *)(sg_stack + 35))

  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;

  local_48 = 0;
  iVar5 = (int)param_1;
  iVar6 = (int)param_2;
  local_44 = (((uint)*(byte *)(param_7 + 7) * 0x100 + (uint)*(byte *)(param_7 + 6)) * 0x100 +
             (uint)*(byte *)(param_7 + 5)) * 0x100 + (uint)*(byte *)(param_7 + 4);
  local_28 = *(byte *)(param_7 + 8);
  iVar7 = (int)param_3;
  iVar2 = (int)param_4;
  local_27 = *(byte *)(param_7 + 9);
  local_26 = *(byte *)(param_7 + 10);
  local_25 = *(byte *)(param_7 + 0xb);
  local_3c = 0;
  local_40 = (((uint)local_25 * 0x100 + (uint)local_26) * 0x100 + (uint)local_27) * 0x100 +
             (uint)local_28;
  local_38 = *(undefined1 *)(param_7 + 0x10);
  local_34 = param_7 + 0x16;
  local_37 = 0x10;
  local_30 = -1;
  iVar3 = (int)param_5;
  iVar4 = (int)param_6;
  if (param_11 == 0) {
    if (param_10 != 0) {
      bda_sango_gui_render_region
                (param_10,iVar5,iVar6,iVar7,iVar2,local_44,local_40,&local_48,iVar3,iVar4);
      return;
    }
    bda_sango_gui_draw_guard(1);
    uVar1 = bda_sango_gui_object_draw_begin(g_app_frame);
    bda_sango_gui_render_region
              (uVar1,iVar5,iVar6,iVar7,iVar2,local_44,local_40,&local_48,iVar3,iVar4);
  }
  else {
    if (param_11 != 1) {
      return;
    }
    if (param_10 != 0) {
      local_30 = bda_sango_gui_rgb(param_10,0xff,0,0xff);
      bda_sango_gui_render_region
                (param_10,iVar5,iVar6,iVar7,iVar2,local_44,local_40,&local_48,iVar3,iVar4);
      return;
    }
    bda_sango_gui_draw_guard(1);
    uVar1 = bda_sango_gui_object_draw_begin(g_app_frame);
    local_30 = bda_sango_gui_rgb(uVar1,0xff,0,0xff);
    bda_sango_gui_render_region
              (uVar1,iVar5,iVar6,iVar7,iVar2,local_44,local_40,&local_48,iVar3,iVar4);
  }
  bda_sango_gui_object_draw_end(g_app_frame,uVar1);
  bda_sango_gui_draw_guard(0);
  return;
}


#undef g_app_frame
#undef param_5
#undef local_48
#undef param_6
#undef local_44
#undef param_7
#undef local_40
#undef param_8
#undef local_3c
#undef param_9
#undef local_38
#undef param_10
#undef local_37
#undef param_11
#undef local_34
#undef local_30
#undef local_28
#undef local_27
#undef local_26
#undef local_25

#define g_app_frame (*(undefined4 *)(0x81c2b0f4u))
#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
#define g_frame_buffer (*(undefined4 *)(0x81c2b1d0u))
/* VA 0x81c0863c; body bytes 560 */

void FUN_81c0863c(short param_1,short param_2,short param_3,short param_4,short param_5,
                 short param_6,ushort *param_7,int param_8,undefined4 param_9,int param_10,
                 int param_11)

{
  unsigned char sg_stack[44] __attribute__((aligned(8)));
  (*(short *)(sg_stack + 0)) = param_5;
  (*(short *)(sg_stack + 4)) = param_6;
  (*(ushort * *)(sg_stack + 8)) = param_7;
  (*(int *)(sg_stack + 12)) = param_8;
  (*(undefined4 *)(sg_stack + 16)) = param_9;
  (*(int *)(sg_stack + 20)) = param_10;
  (*(int *)(sg_stack + 24)) = param_11;
#define param_5 (*(short *)(sg_stack + 0))
#define param_6 (*(short *)(sg_stack + 4))
#define param_7 (*(ushort * *)(sg_stack + 8))
#define param_8 (*(int *)(sg_stack + 12))
#define param_9 (*(undefined4 *)(sg_stack + 16))
#define param_10 (*(int *)(sg_stack + 20))
#define param_11 (*(int *)(sg_stack + 24))

  ushort uVar1;
  ushort uVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint unaff_s5;
  void *pvVar9;

  uVar7 = (uint)param_3;
  uVar8 = (uint)param_4;
  iVar5 = (int)param_5;
  iVar6 = (int)param_6;
  if (param_11 == 1) {
    unaff_s5 = 1;
  }
  else if (param_11 == 2) {
    unaff_s5 = 2;
  }
  if (1 < (unaff_s5 - 1 & 0xff)) {
    return;
  }
  if (param_7 == (ushort *)0x0) {
    return;
  }
  uVar1 = param_7[1];
  uVar2 = *param_7;
  pvVar9 = (void *)(param_8 + 0xc);
  if ((((iVar5 != 0) || (iVar6 != 0)) || (uVar2 != uVar7)) || (uVar1 != uVar8)) {
    iVar4 = uVar7 + 3;
    if ((int)(uVar7 + 3) < 0) {
      iVar4 = uVar7 + 6;
    }
    pvVar3 = bda_sango_mem_alloc((iVar4 >> 2) * uVar8 + 0x20);
    if (pvVar3 == 0) {
      return;
    }
    iVar5 = bda_sango_gui_bitmap_crop
                      ((uint)uVar2,(uint)uVar1,iVar5,iVar6,iVar5 + uVar7 + -1,iVar6 + uVar8 + -1,
                       pvVar9,pvVar3);
    pvVar9 = pvVar3;
    if (iVar5 == 0) goto LAB_81c08778;
  }
  if (param_10 == 0) {
    bda_sango_gui_bitmap_context
              (g_draw_context,(int)param_1,(int)param_2,uVar7,uVar8,pvVar9,unaff_s5);
    bda_sango_gui_bitmap_buffer
              ((int)param_1,(int)param_2,uVar7,uVar8,pvVar9,g_frame_buffer,unaff_s5);
    bda_sango_gui_request_redraw(g_app_frame,0,0);
  }
LAB_81c08778:
  if (pvVar9 != 0) {
    bda_sango_mem_free(pvVar9);
  }
  return;
}


#undef g_app_frame
#undef g_draw_context
#undef g_frame_buffer
#undef param_5
#undef param_6
#undef param_7
#undef param_8
#undef param_9
#undef param_10
#undef param_11

#define g_app_frame (*(undefined4 *)(0x81c2b0f4u))
#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
/* VA 0x81c0886c; body bytes 344 */

void FUN_81c0886c(short param_1,short param_2,uint param_3,uint param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  void *unaff_s3;

  iVar2 = (int)param_1;
  iVar3 = (int)param_2;
  if (iVar2 < 0) {
    return;
  }
  if (iVar3 < 0) {
    return;
  }
  if (0xef < iVar2) {
    return;
  }
  if (0x13f < iVar3) {
    return;
  }
  if (3 < param_3) {
    return;
  }
  if (param_3 == 1) {
    uVar1 = 8;
  }
  else if (param_3 == 0) {
    uVar1 = 0xf;
  }
  else if (param_3 == 2) {
    uVar1 = 7;
  }
  else {
    uVar1 = 0x10;
    if (param_3 != 3) goto LAB_81c088dc;
  }
  unaff_s3 = bda_sango_gui_draw_object(uVar1);
LAB_81c088dc:
  if (param_4 == 0) {
    bda_sango_gui_draw_guard(1);
    bda_sango_gui_put_pixel(g_draw_context,iVar2,iVar3,(uint)unaff_s3);
    bda_sango_gui_request_redraw(g_app_frame,0,0);
    bda_sango_gui_draw_guard(0);
  }
  else {
    bda_sango_gui_put_pixel(param_4,iVar2,iVar3,(uint)unaff_s3);
  }
  return;
}


#undef g_app_frame
#undef g_draw_context

#define g_app_frame (*(undefined4 *)(0x81c2b0f4u))
#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
/* VA 0x81c089c4; body bytes 1208 */

void FUN_81c089c4(short param_1,short param_2,short param_3,short param_4,uint param_5,
                 undefined4 param_6,uint param_7)

{
  unsigned char sg_stack[28] __attribute__((aligned(8)));
  (*(uint *)(sg_stack + 0)) = param_5;
  (*(undefined4 *)(sg_stack + 4)) = param_6;
  (*(uint *)(sg_stack + 8)) = param_7;
#define param_5 (*(uint *)(sg_stack + 0))
#define param_6 (*(undefined4 *)(sg_stack + 4))
#define param_7 (*(uint *)(sg_stack + 8))

  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  int iVar6;
  uint uVar7;
  void *unaff_s0;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;

  iVar8 = (int)param_1;
  iVar10 = (int)param_2;
  iVar12 = (int)param_3;
  iVar13 = (int)param_4;
  if ((iVar8 < 0) && (iVar12 < 0)) {
    return;
  }
  if ((iVar10 < 0) && (iVar13 < 0)) {
    return;
  }
  if ((0xef < iVar8) && (0xef < iVar12)) {
    return;
  }
  if ((0x13f < iVar10) && (0x13f < iVar13)) {
    return;
  }
  iVar9 = iVar8;
  if (iVar8 < 0) {
    iVar9 = 0;
  }
  if (iVar12 < 0) {
    iVar12 = 0;
  }
  iVar11 = iVar10;
  if (iVar10 < 0) {
    iVar11 = 0;
  }
  if (iVar13 < 0) {
    iVar13 = 0;
  }
  if (0xef < iVar12) {
    iVar12 = 0xef;
  }
  if (0x13f < iVar13) {
    iVar13 = 0x13f;
  }
  if (0xef < iVar8) {
    iVar9 = 0xef;
  }
  if (0x13f < iVar10) {
    iVar11 = 0x13f;
  }
  if (3 < param_5) {
    return;
  }
  if (param_5 == 1) {
    uVar7 = 8;
  }
  else if (param_5 == 0) {
    uVar7 = 0xf;
  }
  else if (param_5 == 2) {
    uVar7 = 7;
  }
  else {
    uVar7 = 0x10;
    if (param_5 != 3) goto LAB_81c08ab8;
  }
  unaff_s0 = bda_sango_gui_draw_object(uVar7);
LAB_81c08ab8:
  if (param_7 == 0) {
    pvVar5 = bda_sango_gui_select_draw_object(g_draw_context,unaff_s0);
    bda_sango_gui_draw_guard(1);
    bda_sango_gui_move_to(g_draw_context,iVar9,iVar11);
    bda_sango_gui_line_to(g_draw_context,iVar12,iVar13);
    bda_sango_gui_request_redraw(g_app_frame,0,0);
    bda_sango_gui_select_draw_object(g_draw_context,pvVar5);
    bda_sango_gui_draw_guard(0);
  }
  else if ((iVar9 == iVar12) || (iVar11 == iVar13)) {
    iVar8 = iVar9;
    if (iVar12 < iVar9) {
      iVar8 = iVar12;
      iVar12 = iVar9;
    }
    iVar10 = iVar11;
    if (iVar13 < iVar11) {
      iVar10 = iVar13;
      iVar13 = iVar11;
    }
    FUN_81c08100((short)iVar8,(short)iVar10,(short)iVar12,(short)iVar13,param_5,param_7);
  }
  else {
    iVar8 = (iVar12 - iVar9) * 0x10000;
    iVar10 = (iVar13 - iVar11) * 0x10000;
    iVar15 = iVar8 >> 0x10;
    iVar14 = iVar10 >> 0x10;
    iVar6 = 1;
    if (iVar15 * iVar14 < 0) {
      iVar6 = -1;
    }
    iVar3 = FUN_81c1de00(iVar15);
    iVar4 = FUN_81c1de00(iVar14);
    sVar1 = (short)((uint)iVar8 >> 0x10);
    sVar2 = (short)((uint)iVar10 >> 0x10);
    if (iVar4 < iVar3) {
      iVar8 = iVar9;
      if (iVar15 < 0) {
        iVar15 = (int)-sVar1;
        iVar14 = (int)-sVar2;
        iVar8 = iVar12;
        iVar11 = iVar13;
        iVar12 = iVar9;
      }
      iVar13 = iVar14 * 2 - iVar15;
      FUN_81c0886c((short)iVar8,(short)iVar11,param_5,param_7);
      while (iVar8 < iVar12) {
        iVar13 = iVar13 * 0x10000 >> 0x10;
        iVar9 = (iVar8 + 1) * 0x10000;
        iVar8 = iVar9 >> 0x10;
        iVar10 = iVar14 << 0x11;
        if (-1 < iVar13) {
          iVar11 = (iVar11 + iVar6) * 0x10000 >> 0x10;
          iVar10 = (iVar14 - iVar15) * 0x20000;
        }
        iVar13 = iVar13 + (iVar10 >> 0x10);
        FUN_81c0886c((short)((uint)iVar9 >> 0x10),(short)iVar11,param_5,param_7);
      }
    }
    else {
      iVar8 = iVar11;
      if (iVar14 < 0) {
        iVar15 = (int)-sVar1;
        iVar14 = (int)-sVar2;
        iVar9 = iVar12;
        iVar8 = iVar13;
        iVar13 = iVar11;
      }
      iVar12 = iVar15 * 2 - iVar14;
      FUN_81c0886c((short)iVar9,(short)iVar8,param_5,param_7);
      while (iVar8 < iVar13) {
        iVar12 = iVar12 * 0x10000 >> 0x10;
        iVar11 = (iVar8 + 1) * 0x10000;
        iVar8 = iVar11 >> 0x10;
        iVar10 = iVar15 << 0x11;
        if (-1 < iVar12) {
          iVar9 = (iVar9 + iVar6) * 0x10000 >> 0x10;
          iVar10 = (iVar15 - iVar14) * 0x20000;
        }
        iVar12 = iVar12 + (iVar10 >> 0x10);
        FUN_81c0886c((short)iVar9,(short)((uint)iVar11 >> 0x10),param_5,param_7);
      }
    }
  }
  return;
}


#undef g_app_frame
#undef g_draw_context
#undef param_5
#undef param_6
#undef param_7

#define g_app_frame (*(undefined4 *)(0x81c2b0f4u))
#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
/* VA 0x81c08e7c; body bytes 584 */

void FUN_81c08e7c(short param_1,short param_2,short param_3,short param_4,uint param_5,
                 undefined4 param_6,int param_7)

{
  unsigned char sg_stack[28] __attribute__((aligned(8)));
  (*(uint *)(sg_stack + 0)) = param_5;
  (*(undefined4 *)(sg_stack + 4)) = param_6;
  (*(int *)(sg_stack + 8)) = param_7;
#define param_5 (*(uint *)(sg_stack + 0))
#define param_6 (*(undefined4 *)(sg_stack + 4))
#define param_7 (*(int *)(sg_stack + 8))

  void *pvVar1;
  short sVar2;
  uint uVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  void *unaff_s7;

  iVar11 = (int)param_1;
  iVar10 = (int)param_2;
  iVar7 = (int)param_3;
  iVar9 = (int)param_4;
  if (3 < param_5) {
    return;
  }
  iVar8 = iVar7;
  if (iVar7 < iVar11) {
    iVar8 = iVar11;
    iVar11 = iVar7;
  }
  iVar7 = iVar9;
  if (iVar9 < iVar10) {
    iVar7 = iVar10;
    iVar10 = iVar9;
  }
  uVar3 = 8;
  if (param_5 != 1) {
    if (param_5 == 0) {
      uVar3 = 0xf;
    }
    else if (param_5 == 2) {
      uVar3 = 7;
    }
    else {
      uVar3 = 0x10;
      if (param_5 != 3) goto LAB_81c08f2c;
    }
  }
  unaff_s7 = bda_sango_gui_draw_object(uVar3);
LAB_81c08f2c:
  if (param_7 == 0) {
    pvVar1 = bda_sango_gui_select_draw_object(g_draw_context,unaff_s7);
    bda_sango_gui_draw_guard(1);
    bda_sango_gui_rectangle(g_draw_context,iVar11,iVar10,iVar8 + 1,iVar7 + 1);
    bda_sango_gui_draw_guard(0);
    bda_sango_gui_request_redraw(g_app_frame,0,0);
    bda_sango_gui_select_draw_object(g_draw_context,pvVar1);
  }
  sVar2 = (short)iVar11;
  sVar4 = (short)iVar10;
  sVar5 = (short)iVar8;
  FUN_81c089c4(sVar2,sVar4,sVar5,sVar4,param_5,param_6,param_7);
  sVar6 = (short)iVar7;
  FUN_81c089c4(sVar5,sVar4,sVar5,sVar6,param_5,param_6,param_7);
  FUN_81c089c4(sVar2,sVar6,sVar5,sVar6,param_5,param_6,param_7);
  FUN_81c089c4(sVar2,sVar4,sVar2,sVar6,param_5,param_6,param_7);
  return;
}


#undef g_app_frame
#undef g_draw_context
#undef param_5
#undef param_6
#undef param_7

#define g_app_frame (*(undefined4 *)(0x81c2b0f4u))
#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
/* VA 0x81c090c4; body bytes 764 */

void FUN_81c090c4(short param_1,short param_2,int param_3,uint param_4,undefined4 param_5,
                 int param_6)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
  (*(undefined4 *)(sg_stack + 0)) = param_5;
  (*(int *)(sg_stack + 4)) = param_6;
#define param_5 (*(undefined4 *)(sg_stack + 0))
#define param_6 (*(int *)(sg_stack + 4))

  int iVar1;
  void *pvVar2;
  int iVar3;
  short sVar4;
  short sVar5;
  int iVar6;
  uint uVar7;
  short sVar8;
  void *unaff_s1;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;

  iVar6 = (int)param_1;
  iVar12 = (int)param_2;
  if (param_3 == 0) {
    return;
  }
  if (3 < param_4) {
    return;
  }
  if (param_4 == 1) {
    uVar7 = 8;
  }
  else if (param_4 == 0) {
    uVar7 = 0xf;
  }
  else if (param_4 == 2) {
    uVar7 = 7;
  }
  else {
    uVar7 = 0x10;
    if (param_4 != 3) goto LAB_81c09140;
  }
  unaff_s1 = bda_sango_gui_draw_object(uVar7);
LAB_81c09140:
  if (param_6 == 0) {
    pvVar2 = bda_sango_gui_select_draw_object(g_draw_context,unaff_s1);
    bda_sango_gui_circle(g_draw_context,iVar6,iVar12,param_3);
    bda_sango_gui_request_redraw(g_app_frame,0,0);
    bda_sango_gui_select_draw_object(g_draw_context,pvVar2);
  }
  iVar3 = param_3 * -2 + 3;
  iVar9 = (int)(short)param_3;
  iVar10 = 0;
  if (-1 < iVar9) {
    do {
      iVar11 = iVar3 * 0x10000 >> 0x10;
      sVar4 = (short)((uint)((iVar6 + iVar10) * 0x10000) >> 0x10);
      sVar8 = (short)((uint)((iVar12 + iVar9) * 0x10000) >> 0x10);
      FUN_81c0886c(sVar4,sVar8,param_4,param_6);
      sVar5 = (short)((uint)((iVar6 - iVar10) * 0x10000) >> 0x10);
      FUN_81c0886c(sVar5,sVar8,param_4,param_6);
      sVar8 = (short)((uint)((iVar12 - iVar9) * 0x10000) >> 0x10);
      FUN_81c0886c(sVar4,sVar8,param_4,param_6);
      FUN_81c0886c(sVar5,sVar8,param_4,param_6);
      sVar4 = (short)((uint)((iVar6 + iVar9) * 0x10000) >> 0x10);
      sVar8 = (short)((uint)((iVar12 + iVar10) * 0x10000) >> 0x10);
      FUN_81c0886c(sVar4,sVar8,param_4,param_6);
      sVar5 = (short)((uint)((iVar6 - iVar9) * 0x10000) >> 0x10);
      FUN_81c0886c(sVar5,sVar8,param_4,param_6);
      sVar8 = (short)((uint)((iVar12 - iVar10) * 0x10000) >> 0x10);
      FUN_81c0886c(sVar4,sVar8,param_4,param_6);
      FUN_81c0886c(sVar5,sVar8,param_4,param_6);
      iVar1 = iVar10 - iVar9;
      iVar3 = iVar11 + iVar10 * 4 + 6;
      if (-1 < iVar11) {
        iVar9 = (iVar9 + -1) * 0x10000 >> 0x10;
        iVar3 = iVar11 + iVar1 * 4 + 10;
      }
      iVar10 = (iVar10 + 1) * 0x10000 >> 0x10;
    } while (iVar10 <= iVar9);
  }
  return;
}


#undef g_app_frame
#undef g_draw_context
#undef param_5
#undef param_6


/* VA 0x81c093c0; body bytes 500 */

void FUN_81c093c0(short param_1,short param_2,int param_3,uint param_4,int param_5)

{
  unsigned char sg_stack[20] __attribute__((aligned(8)));
  (*(int *)(sg_stack + 0)) = param_5;
#define param_5 (*(int *)(sg_stack + 0))

  int iVar1;
  int iVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;

  iVar11 = (int)param_1;
  iVar10 = (int)param_2;
  if (((param_3 != 0) && (param_4 < 4)) && (param_5 != 0)) {
    iVar2 = param_3 * -2 + 3;
    iVar8 = (int)(short)param_3;
    iVar9 = 0;
    if (-1 < iVar8) {
      do {
        iVar12 = iVar2 * 0x10000 >> 0x10;
        sVar3 = (short)((uint)((iVar11 + iVar9) * 0x10000) >> 0x10);
        sVar4 = (short)((uint)((iVar10 + iVar8) * 0x10000) >> 0x10);
        sVar6 = (short)((uint)((iVar11 - iVar9) * 0x10000) >> 0x10);
        FUN_81c089c4(sVar3,sVar4,sVar6,sVar4,param_4,0,param_5);
        sVar4 = (short)((uint)((iVar11 + iVar8) * 0x10000) >> 0x10);
        sVar5 = (short)((uint)((iVar10 + iVar9) * 0x10000) >> 0x10);
        sVar7 = (short)((uint)((iVar11 - iVar8) * 0x10000) >> 0x10);
        FUN_81c089c4(sVar4,sVar5,sVar7,sVar5,param_4,0,param_5);
        sVar5 = (short)((uint)((iVar10 - iVar9) * 0x10000) >> 0x10);
        FUN_81c089c4(sVar4,sVar5,sVar7,sVar5,param_4,0,param_5);
        sVar4 = (short)((uint)((iVar10 - iVar8) * 0x10000) >> 0x10);
        FUN_81c089c4(sVar3,sVar4,sVar6,sVar4,param_4,0,param_5);
        iVar1 = iVar9 - iVar8;
        iVar2 = iVar12 + iVar9 * 4 + 6;
        if (-1 < iVar12) {
          iVar8 = (iVar8 + -1) * 0x10000 >> 0x10;
          iVar2 = iVar12 + iVar1 * 4 + 10;
        }
        iVar9 = (iVar9 + 1) * 0x10000 >> 0x10;
      } while (iVar9 <= iVar8);
    }
  }
  return;
}


#undef param_5

#define DAT_81c2b204 (*(void * *)(0x81c2b204u))
#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
/* VA 0x81c095b4; body bytes 204 */

void FUN_81c095b4(int param_1,uint param_2)

{
  void *pvVar1;
  uint uVar2;

  if (param_1 == 1) {
    uVar2 = 8;
  }
  else if (param_1 == 0) {
    uVar2 = 0xf;
  }
  else if (param_1 == 2) {
    uVar2 = 7;
  }
  else {
    if (param_1 != 3) {
      return;
    }
    uVar2 = 0x10;
  }
  pvVar1 = bda_sango_gui_draw_object(uVar2);
  if (param_2 == 0) {
    bda_sango_gui_set_fill_object(g_draw_context,(uint)pvVar1);
    DAT_81c2b204 = pvVar1;
  }
  else {
    bda_sango_gui_set_fill_object(param_2,(uint)pvVar1);
  }
  return;
}


#undef DAT_81c2b204
#undef g_draw_context

#define DAT_81c2b208 (*(void * *)(0x81c2b208u))
#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
/* VA 0x81c09680; body bytes 204 */

void FUN_81c09680(int param_1,uint param_2)

{
  void *pvVar1;
  uint uVar2;

  if (param_1 == 1) {
    uVar2 = 8;
  }
  else if (param_1 == 0) {
    uVar2 = 0xf;
  }
  else if (param_1 == 2) {
    uVar2 = 7;
  }
  else {
    if (param_1 != 3) {
      return;
    }
    uVar2 = 0x10;
  }
  pvVar1 = bda_sango_gui_draw_object(uVar2);
  if (param_2 == 0) {
    bda_sango_gui_set_text_color(g_draw_context,(uint)pvVar1);
    DAT_81c2b208 = pvVar1;
  }
  else {
    bda_sango_gui_set_text_color(param_2,(uint)pvVar1);
  }
  return;
}


#undef DAT_81c2b208
#undef g_draw_context

#define DAT_81c2b210 (*(undefined1 *)(0x81c2b210u))
#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
/* VA 0x81c0974c; body bytes 168 */

undefined4 FUN_81c0974c(undefined1 param_1,uint param_2)

{
  undefined4 uVar1;
  undefined1 uVar2;

  uVar1 = 0;
  switch(param_1) {
  case 0:
  case 1:
  case 2:
    uVar2 = 0;
    break;
  case 3:
  case 4:
  case 5:
    uVar2 = 4;
    break;
  case 6:
  case 7:
  case 8:
    uVar2 = 8;
    break;
  default:
    goto switchD_81c09778_default;
  }
  if (param_2 == 0) {
    bda_sango_gui_select_font(g_draw_context,(uint)uVar2);
    uVar1 = 1;
    DAT_81c2b210 = uVar2;
  }
  else {
    bda_sango_gui_select_font(param_2,(uint)uVar2);
    uVar1 = 1;
  }
switchD_81c09778_default:
  return uVar1;
}


#undef DAT_81c2b210
#undef g_draw_context


/* VA 0x81c097f4; body bytes 192 */

ushort * FUN_81c097f4(undefined4 *param_1,uint param_2,int param_3,int param_4)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
#define local_18 (*(int (*)[2])(sg_stack + 0))

  ushort uVar1;
  ushort uVar2;
  ushort *puVar3;

  if (2 < param_2) {
    return (ushort *)0x0;
  }
  crt_memcpy(local_18,(void *)(param_4 + param_3 * 4),4);
  puVar3 = (ushort *)(param_4 + local_18[0]);
  if (param_2 == 1) {
    *param_1 = puVar3;
  }
  else {
    if (param_2 != 0) {
      if (param_2 == 2) {
        uVar1 = *puVar3;
        uVar2 = puVar3[1];
        param_1[1] = puVar3;
        *param_1 = (ushort *)(((int)(uVar1 + 3) >> 2) * (uint)uVar2 + (int)puVar3);
      }
      goto LAB_81c09858;
    }
    *param_1 = 0;
  }
  param_1[1] = 0;
LAB_81c09858:
  param_1[2] = param_2;
  return puVar3;
}


#undef local_18


/* VA 0x81c098b4; body bytes 220 */

uint FUN_81c098b4(uint param_1)

{
  unsigned char sg_stack[22] __attribute__((aligned(8)));
#define local_18 (*(char *)(sg_stack + 0))
#define local_17 (*(char *)(sg_stack + 1))
#define local_16 (*(char *)(sg_stack + 2))
#define local_15 (*(char *)(sg_stack + 3))
#define local_14 (*(char *)(sg_stack + 4))
#define local_13 (*(char *)(sg_stack + 5))


  crt_memset(&local_18,0,6);
  bda_sango_gui_input_packet(&local_18);
  if (param_1 != 0x67) {
    if (param_1 < 0x68) {
      local_15 = '\x01';
      if (param_1 != 1) {
        if (param_1 != 0x1c) {
          return 0;
        }
        return (uint)(local_13 == '\x01');
      }
      goto LAB_81c09944;
    }
    local_15 = local_18;
    if (param_1 != 0x6a) {
      if (param_1 < 0x6b) {
        local_15 = local_17;
        if (param_1 != 0x69) {
          return 0;
        }
      }
      else {
        local_15 = local_16;
        if (param_1 != 0x6c) {
          return 0;
        }
      }
    }
  }
  local_14 = '\x01';
LAB_81c09944:
  return (uint)(local_14 == local_15);
}


#undef local_18
#undef local_17
#undef local_16
#undef local_15
#undef local_14
#undef local_13

#define DAT_81c20244 (*(undefined4 *)(0x81c20244u))
#define DAT_81c20248 (*(undefined4 *)(0x81c20248u))
/* VA 0x81c09990; body bytes 476 */

void FUN_81c09990(short param_1,short param_2,short param_3,short param_4,int param_5)

{
  unsigned char sg_stack[52] __attribute__((aligned(8)));
  (*(int *)(sg_stack + 32)) = param_5;
#define param_5 (*(int *)(sg_stack + 32))
#define local_10 (*(undefined4 (*)[2])(sg_stack + 0))
#define local_8 (*(undefined4 (*)[2])(sg_stack + 8))

  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;

  iVar6 = (int)param_1;
  local_10[0] = DAT_81c20244;
  local_8[0] = DAT_81c20248;
  iVar4 = (int)param_3;
  iVar8 = (int)param_2;
  iVar10 = (int)param_4;
  if (iVar6 < 0xf0) {
    if (iVar6 < 0) {
      iVar6 = 0;
    }
    if (iVar8 < 0x140) {
      if (iVar8 < 0) {
        iVar8 = 0;
      }
      if (-1 < iVar4) {
        if (0xef < iVar4) {
          iVar4 = 0xef;
        }
        if (-1 < iVar10) {
          iVar11 = iVar4 + 3;
          if (-1 < iVar4) {
            iVar11 = iVar4;
          }
          iVar7 = iVar6 + 3;
          if (-1 < iVar6) {
            iVar7 = iVar6;
          }
          iVar13 = (iVar6 + (iVar7 >> 2) * -4) * 0x10000 >> 0x10;
          iVar11 = (iVar4 + (iVar11 >> 2) * -4) * 0x10000 >> 0x10;
          iVar6 = (iVar4 - iVar11) + (iVar13 - iVar6);
          iVar4 = iVar6 + 4;
          if (0x13f < iVar10) {
            iVar10 = 0x13f;
          }
          if (iVar4 < 0) {
            iVar4 = iVar6 + 7;
          }
          iVar4 = iVar4 >> 2;
          iVar6 = 0;
          if (-1 < iVar10 - iVar8) {
            iVar9 = param_5 + (int)(short)(iVar7 >> 2) + iVar8 * 0x3c;
            iVar12 = 0;
            iVar7 = 0;
            do {
              bVar1 = *(byte *)(iVar7 + iVar9);
              bVar2 = *(byte *)((int)local_10 + iVar13);
              iVar5 = iVar7 + iVar9 + iVar4;
              *(byte *)(iVar7 + iVar9) = ~bVar1 & bVar2 | bVar1 & ~bVar2;
              bVar1 = *(byte *)(iVar5 + -1);
              bVar2 = *(byte *)((int)local_8 + iVar11);
              *(byte *)(iVar5 + -1) = ~bVar1 & bVar2 | bVar1 & ~bVar2;
              if ((2 < iVar4) && (0 < iVar4 + -2)) {
                pbVar3 = (byte *)(iVar12 * 4 + iVar9);
                iVar5 = iVar4 + -2;
                do {
                  pbVar3 = pbVar3 + 1;
                  iVar5 = iVar5 + -1;
                  *pbVar3 = ~*pbVar3;
                } while (iVar5 != 0);
              }
              iVar6 = iVar6 + 1;
              iVar7 = iVar7 + 0x3c;
              iVar12 = iVar12 + 0xf;
            } while (iVar6 <= iVar10 - iVar8);
          }
        }
      }
    }
  }
  return;
}


#undef DAT_81c20244
#undef DAT_81c20248
#undef param_5
#undef local_10
#undef local_8

#define DAT_81c2b108 (*(undefined4 *)(0x81c2b108u))
#define DAT_81c2b0f8 (*(uint *)(0x81c2b0f8u))
#define DAT_81c2b10c (*(uint *)(0x81c2b10cu))
#define DAT_81c2b104 (*(uint *)(0x81c2b104u))
/* VA 0x81c09b6c; body bytes 548 */

uint sango_text_input_proc(uint handle,int message,uint wparam,uint lparam)

{
  uint uVar1;

  if (message == 0x66) {
    bda_sango_gui_edit_finish();
    bda_sango_gui_control_destroy(DAT_81c2b104);
    bda_sango_gui_frame_stop(handle);
    bda_sango_gui_frame_release(handle);
    uVar1 = 0;
  }
  else {
    if (message < 0x67) {
      if (message == 0x12) {
        if ((wparam & 0xffff) == 0x1c) {
          bda_sango_gui_send_message(DAT_81c2b104,0x133,DAT_81c2b0f8,DAT_81c2b10c);
          bda_sango_gui_post_message(handle,0x66,0,0);
          DAT_81c2b108 = 0;
        }
        else if ((wparam & 0xffff) == 1) {
          bda_sango_gui_post_message(handle,0x66,0,0);
        }
      }
      else if (message == 0x60) {
        DAT_81c2b108 = 1;
        DAT_81c2b104 = bda_sango_gui_control_create
                                 ((char *)0x81c2024c,(char *)0x0,0x48410000,0,0,6,8,0x78,0x18,handle
                                  ,0);
        bda_sango_gui_send_message(DAT_81c2b104,0xf0c5,DAT_81c2b0f8,DAT_81c2b10c);
        bda_sango_gui_set_active(DAT_81c2b104);
      }
    }
    uVar1 = bda_sango_gui_default_proc(handle,message,wparam,lparam);
  }
  return uVar1;
}


#undef DAT_81c2b108
#undef DAT_81c2b0f8
#undef DAT_81c2b10c
#undef DAT_81c2b104

#define DAT_81c2b0f8 (*(undefined4 *)(0x81c2b0f8u))
#define DAT_81c2b10c (*(undefined1 * *)(0x81c2b10cu))
#define DAT_81c2b100 (*(void * *)(0x81c2b100u))
#define DAT_81c2b108 (*(undefined4 *)(0x81c2b108u))
/* VA 0x81c09d90; body bytes 544 */

undefined4 FUN_81c09d90(undefined4 param_1,undefined1 *param_2,undefined4 param_3)

{
  unsigned char sg_stack[104] __attribute__((aligned(8)));
#define local_50 (*(code * *)(sg_stack + 24))
#define local_4c (*(undefined4 *)(sg_stack + 28))
#define local_48 (*(undefined4 *)(sg_stack + 32))
#define local_44 (*(undefined4 *)(sg_stack + 36))
#define local_40 (*(undefined4 *)(sg_stack + 40))
#define local_3c (*(void * *)(sg_stack + 44))
#define local_38 (*(undefined4 *)(sg_stack + 48))
#define auStack_30 (*(undefined1 (*)[32])(sg_stack + 56))
#define local_68 (*(undefined4 *)(sg_stack + 0))
#define local_64 (*(undefined4 *)(sg_stack + 4))
#define local_60 (*(undefined4 *)(sg_stack + 8))
#define local_5c (*(undefined4 *)(sg_stack + 12))
#define local_58 (*(undefined4 *)(sg_stack + 16))
#define local_54 (*(undefined4 *)(sg_stack + 20))

  int iVar1;
  uint uVar2;
  undefined4 uVar3;

  *param_2 = 0;
  local_68 = 0x28400000;
  local_50 = sango_text_input_proc;
  local_4c = 0x5a;
  local_44 = 0xe6;
  local_48 = 0x50;
  local_40 = 0x8c;
  local_64 = 0;
  local_5c = 0;
  local_58 = 0;
  DAT_81c2b0f8 = param_3;
  DAT_81c2b10c = param_2;
  local_60 = param_1;
  local_3c = bda_sango_gui_draw_object(8);
  local_38 = 0;
  local_54 = 0;
  iVar1 = bda_sango_gui_display_metric(0,6);
  DAT_81c2b100 = bda_sango_mem_alloc(iVar1 * 0x3200 + 10);
  if (DAT_81c2b100 != 0) {
    bda_sango_gui_capture_region(0,200,0x140,0x28,DAT_81c2b100);
  }
  uVar2 = bda_sango_gui_register_frame(&local_68);
  if (uVar2 == 0xffffffff) {
    bda_sango_mem_free(DAT_81c2b100);
    uVar3 = 1;
  }
  else {
    while (iVar1 = bda_sango_gui_event_poll(auStack_30,0), iVar1 != 0) {
      bda_sango_gui_event_step(auStack_30);
      bda_sango_gui_event_dispatch(auStack_30);
    }
    bda_sango_gui_close_frame(uVar2);
    uVar3 = DAT_81c2b108;
    if (DAT_81c2b100 != 0) {
      bda_sango_gui_restore_region(0,200,0xf0,0x28,DAT_81c2b100);
      bda_sango_mem_free(DAT_81c2b100);
      uVar3 = DAT_81c2b108;
    }
  }
  return uVar3;
}


#undef DAT_81c2b0f8
#undef DAT_81c2b10c
#undef DAT_81c2b100
#undef DAT_81c2b108
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef auStack_30
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_58
#undef local_54

#define g_app_frame (*(undefined4 *)(0x81c2b0f4u))
/* VA 0x81c09fb0; body bytes 784 */

void FUN_81c09fb0(short param_1,short param_2,int param_3,uint param_4,int param_5,int param_6)

{
  unsigned char sg_stack[120] __attribute__((aligned(8)));
  (*(int *)(sg_stack + 96)) = param_5;
  (*(int *)(sg_stack + 100)) = param_6;
#define param_5 (*(int *)(sg_stack + 96))
#define param_6 (*(int *)(sg_stack + 100))
#define local_50 (*(int (*)[4])(sg_stack + 0))
#define local_40 (*(undefined4 *)(sg_stack + 16))
#define local_3c (*(int *)(sg_stack + 20))
#define local_38 (*(int *)(sg_stack + 24))
#define local_34 (*(undefined4 *)(sg_stack + 28))
#define local_30 (*(undefined1 *)(sg_stack + 32))
#define local_2f (*(undefined1 *)(sg_stack + 33))
#define local_2c (*(int *)(sg_stack + 36))
#define local_28 (*(int *)(sg_stack + 40))
#define local_20 (*(byte *)(sg_stack + 48))
#define local_1f (*(byte *)(sg_stack + 49))
#define local_1e (*(byte *)(sg_stack + 50))
#define local_1d (*(byte *)(sg_stack + 51))

  uint uVar1;
  int iVar2;
  int iVar3;

  iVar3 = (int)param_2;
  iVar2 = (int)param_1;
  FUN_81c097f4(local_50,1,param_3,param_6);
  local_40 = 0;
  local_3c = (((uint)*(byte *)(local_50[0] + 7) * 0x100 + (uint)*(byte *)(local_50[0] + 6)) * 0x100
             + (uint)*(byte *)(local_50[0] + 5)) * 0x100 + (uint)*(byte *)(local_50[0] + 4);
  local_20 = *(byte *)(local_50[0] + 8);
  local_1f = *(byte *)(local_50[0] + 9);
  local_1e = *(byte *)(local_50[0] + 10);
  local_1d = *(byte *)(local_50[0] + 0xb);
  local_34 = 0;
  local_38 = (((uint)local_1d * 0x100 + (uint)local_1e) * 0x100 + (uint)local_1f) * 0x100 +
             (uint)local_20;
  local_30 = *(undefined1 *)(local_50[0] + 0x10);
  local_2c = local_50[0] + 0x16;
  local_2f = 0x10;
  local_28 = -1;
  if (param_5 == 0) {
    if (param_4 != 0) {
      bda_sango_gui_render_region
                (param_4,iVar2,iVar3,local_3c,local_38,local_3c,local_38,&local_40,0,0);
      return;
    }
    bda_sango_gui_draw_guard(1);
    uVar1 = bda_sango_gui_object_draw_begin(g_app_frame);
    bda_sango_gui_render_region(uVar1,iVar2,iVar3,local_3c,local_38,local_3c,local_38,&local_40,0,0)
    ;
  }
  else {
    if (param_5 != 1) {
      return;
    }
    if (param_4 != 0) {
      local_28 = bda_sango_gui_rgb(param_4,0xff,0,0xff);
      bda_sango_gui_render_region
                (param_4,iVar2,iVar3,local_3c,local_38,local_3c,local_38,&local_40,0,0);
      return;
    }
    bda_sango_gui_draw_guard(1);
    uVar1 = bda_sango_gui_object_draw_begin(g_app_frame);
    local_28 = bda_sango_gui_rgb(uVar1,0xff,0,0xff);
    bda_sango_gui_render_region(uVar1,iVar2,iVar3,local_3c,local_38,local_3c,local_38,&local_40,0,0)
    ;
  }
  bda_sango_gui_object_draw_end(g_app_frame,uVar1);
  bda_sango_gui_draw_guard(0);
  return;
}


#undef g_app_frame
#undef param_5
#undef param_6
#undef local_50
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2f
#undef local_2c
#undef local_28
#undef local_20
#undef local_1f
#undef local_1e
#undef local_1d

#define g_app_frame (*(undefined4 *)(0x81c2b0f4u))
/* VA 0x81c0a2c0; body bytes 56 */

void FUN_81c0a2c0(uint param_1,uint param_2)

{
  bda_sango_gui_window_aux_a(g_app_frame,param_1,param_2);
  return;
}


#undef g_app_frame

#define DAT_81c2b20c (*(undefined4 *)(0x81c2b20cu))
#define s_v300_COM_APP_81c20210 (*(char (*)[1])(0x81c20210u))
#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
#define g_frame_buffer (*(undefined4 *)(0x81c2b1d0u))
/* VA 0x81c0a330; body bytes 284 */

int sango_create_app_frame(void)

{
  unsigned char sg_stack[68] __attribute__((aligned(8)));
#define local_3c (*(undefined4 *)(sg_stack + 4))
#define local_38 (*(char * *)(sg_stack + 8))
#define local_34 (*(undefined4 *)(sg_stack + 12))
#define local_30 (*(undefined4 *)(sg_stack + 16))
#define local_2c (*(undefined4 *)(sg_stack + 20))
#define local_28 (*(code * *)(sg_stack + 24))
#define local_24 (*(undefined4 *)(sg_stack + 28))
#define local_20 (*(undefined4 *)(sg_stack + 32))
#define local_1c (*(undefined4 *)(sg_stack + 36))
#define local_18 (*(undefined4 *)(sg_stack + 40))
#define local_14 (*(void * *)(sg_stack + 44))
#define local_10 (*(undefined4 *)(sg_stack + 48))
#define local_40 (*(undefined4 *)(sg_stack + 0))

  int iVar1;
  int iVar2;

  g_frame_buffer = bda_sango_mem_alloc(0x4b20);
  iVar2 = -1;
  if (g_frame_buffer != 0) {
    crt_memset(g_frame_buffer,0xff,0x4b00);
    local_40 = 0x8000000;
    local_38 = s_v300_COM_APP_81c20210;
    local_28 = sango_window_proc;
    local_1c = 0xf0;
    local_18 = 0x140;
    local_3c = 0;
    local_34 = 0;
    local_30 = 0;
    local_24 = 0;
    local_20 = 0;
    local_14 = bda_sango_gui_draw_object(0xf);
    local_10 = 0;
    local_2c = 0;
    iVar1 = bda_sango_gui_register_frame(&local_40);
    iVar2 = -1;
    if (iVar1 != -1) {
      FUN_81c095b4(0,0);
      FUN_81c09680(3,0);
      bda_sango_gui_set_text_mode(g_draw_context,0);
      DAT_81c2b20c = 0;
      iVar2 = 0;
    }
  }
  return iVar2;
}


#undef DAT_81c2b20c
#undef s_v300_COM_APP_81c20210
#undef g_draw_context
#undef g_frame_buffer
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
#undef local_40

#define g_frame_buffer (*(undefined4 *)(0x81c2b1d0u))
/* VA 0x81c0a44c; body bytes 88 */

uint FUN_81c0a44c(void)

{
  bool bVar1;

  g_frame_buffer = bda_sango_mem_alloc(0x4b20);
  bVar1 = g_frame_buffer != 0;
  if (bVar1) {
    crt_memset(g_frame_buffer,0xff,0x4b00);
  }
  return (uint)bVar1;
}


#undef g_frame_buffer

#define g_app_frame (*(undefined4 *)(0x81c2b0f4u))
#define g_frame_buffer (*(undefined4 *)(0x81c2b1d0u))
/* VA 0x81c0a4a4; body bytes 212 */

int sango_run_event_loop_and_close(void)

{
  unsigned char sg_stack[48] __attribute__((aligned(8)));
#define auStack_28 (*(undefined1 (*)[32])(sg_stack + 0))

  int iVar1;

  bda_sango_gui_post_message(g_app_frame,0x66,0,0);
  while( true ) {
    iVar1 = bda_sango_gui_event_poll(auStack_28,0);
    if (iVar1 == 0) break;
    bda_sango_gui_event_step(auStack_28);
    bda_sango_gui_event_dispatch(auStack_28);
  }
  bda_sango_gui_close_frame(g_app_frame);
  if (g_frame_buffer != 0) {
    bda_sango_mem_free((void *)g_frame_buffer);
  }
  return 1;
}


#undef g_app_frame
#undef g_frame_buffer
#undef auStack_28

#define s_v300_COM_APP_81c20210 (*(char (*)[1])(0x81c20210u))
/* VA 0x81c0a578; body bytes 132 */

void FUN_81c0a578(undefined4 *param_1)

{
  void *pvVar3;

  *param_1 = 0x8000000;
  param_1[2] = s_v300_COM_APP_81c20210;
  param_1[6] = sango_window_proc;
  param_1[9] = 0xf0;
  param_1[10] = 0x140;
  param_1[1] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  pvVar3 = bda_sango_gui_draw_object(0xf);
  param_1[0xb] = pvVar3;
  param_1[5] = 0;
  param_1[0xc] = 0;
  return;
}


#undef s_v300_COM_APP_81c20210

#define DAT_81c2b218 (*(undefined4 *)(0x81c2b218u))
#define DAT_81c2b21c (*(undefined4 *)(0x81c2b21cu))
#define DAT_81c2b220 (*(undefined4 *)(0x81c2b220u))
/* VA 0x81c0a5fc; body bytes 164 */

uint FUN_81c0a5fc(undefined4 *param_1)

{
  unsigned char sg_stack[48] __attribute__((aligned(8)));
#define auStack_28 (*(undefined1 (*)[32])(sg_stack + 0))

  int iVar1;

  iVar1 = bda_sango_gui_event_poll(auStack_28,0);
  if (iVar1 != 0) {
    bda_sango_gui_event_step(auStack_28);
    bda_sango_gui_event_dispatch(auStack_28);
    *param_1 = DAT_81c2b218;
    param_1[1] = DAT_81c2b21c;
    param_1[2] = DAT_81c2b220;
    DAT_81c2b218 = 0;
  }
  return (uint)(iVar1 != 0);
}


#undef DAT_81c2b218
#undef DAT_81c2b21c
#undef DAT_81c2b220
#undef auStack_28

#define g_app_frame (*(undefined4 *)(0x81c2b0f4u))
/* VA 0x81c0a6a0; body bytes 100 */

int bbk_post_message(uint message,uint wparam,uint lparam)

{
  unsigned char sg_stack[32] __attribute__((aligned(8)));
#define local_24 (*(uint *)(sg_stack + 4))
#define local_20 (*(uint *)(sg_stack + 8))
#define local_1c (*(uint *)(sg_stack + 12))
#define auStack_28 (*(undefined1 (*)[4])(sg_stack + 0))


  crt_memset(auStack_28,0,0x1c);
  local_24 = message;
  local_20 = wparam;
  local_1c = lparam;
  bda_sango_gui_post_message(g_app_frame,message,wparam,lparam);
  return 1;
}


#undef g_app_frame
#undef local_24
#undef local_20
#undef local_1c
#undef auStack_28


/* VA 0x81c0a704; body bytes 40 */

void * bbk_alloc(uint size)

{
  void *pvVar1;

  pvVar1 = bda_sango_mem_alloc(size);
  return pvVar1;
}





/* VA 0x81c0a72c; body bytes 44 */

void bbk_free_if_nonnull(void *ptr)

{
  if (ptr != 0) {
    bda_sango_mem_free(ptr);
  }
  return;
}





/* VA 0x81c0a774; body bytes 28 */

char * bbk_strcat(char *destination,char *source)

{
  char *pcVar1;

  pcVar1 = FUN_81c1de70(destination,source);
  return pcVar1;
}





/* VA 0x81c0a790; body bytes 28 */

uint bbk_strlen(char *text)

{
  uint uVar1;

  uVar1 = FUN_81c1b9d4(text);
  return uVar1;
}





/* VA 0x81c0a7ac; body bytes 28 */

void * bbk_memcpy(void *dst,void *src,uint size)

{
  void *pvVar1;

  pvVar1 = crt_memcpy(dst,src,size);
  return pvVar1;
}





/* VA 0x81c0a7c8; body bytes 28 */

void FUN_81c0a7c8(void *param_1,int param_2,uint param_3)

{
  crt_memset(param_1,param_2,param_3);
  return;
}




#define DAT_81c20254 (*(undefined *)(0x81c20254u))
#define DAT_81c20258 (*(undefined *)(0x81c20258u))
/* VA 0x81c0a7e4; body bytes 136 */

undefined1 * FUN_81c0a7e4(int param_1,undefined1 *param_2,int param_3)

{
  int iVar1;
  byte *pbVar2;

  pbVar2 = &DAT_81c20254;
  if (param_3 != 10) {
    if (param_3 < 0xb) {
      pbVar2 = &DAT_81c20258;
      iVar1 = 8;
    }
    else {
      pbVar2 = (byte *)0x81c2025c;
      iVar1 = 0x10;
    }
    if (param_3 != iVar1) {
      return pbVar2;
    }
  }
  FUN_81c1c670(param_2,pbVar2,param_1,param_3);
  return pbVar2;
}


#undef DAT_81c20254
#undef DAT_81c20258


/* VA 0x81c0a86c; body bytes 36 */

void bbk_zero_time_stub(ushort *time_fields)

{
  time_fields[7] = 0;
  *time_fields = 0;
  time_fields[1] = 0;
  time_fields[2] = 0;
  time_fields[5] = 0;
  time_fields[3] = 0;
  time_fields[6] = 0;
  time_fields[4] = 0;
  return;
}





/* VA 0x81c0a890; body bytes 28 */

void bbk_srand(uint seed)

{
  crt_srand(seed);
  return;
}





/* VA 0x81c0a8ac; body bytes 28 */

uint bbk_rand(void)

{
  uint uVar1;

  uVar1 = crt_rand();
  return uVar1;
}




#define g_app_frame (*(undefined4 *)(0x81c2b0f4u))
/* VA 0x81c0a8c8; body bytes 60 */

undefined4 FUN_81c0a8c8(uint param_1,uint param_2)

{
  bda_sango_gui_timer_start(g_app_frame,param_1,param_2);
  return 1;
}


#undef g_app_frame

#define g_app_frame (*(undefined4 *)(0x81c2b0f4u))
/* VA 0x81c0a904; body bytes 52 */

undefined4 FUN_81c0a904(uint param_1)

{
  bda_sango_gui_timer_stop(g_app_frame,param_1);
  return 1;
}


#undef g_app_frame

#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
/* VA 0x81c0a938; body bytes 44 */

void * bbk_compatible_context_create(void)

{
  void *pvVar1;

  pvVar1 = bda_sango_gui_compatible_create(g_draw_context);
  return pvVar1;
}


#undef g_draw_context


/* VA 0x81c0a964; body bytes 44 */

int bbk_compatible_context_free(void *context)

{
  bda_sango_gui_compatible_free(context);
  return 1;
}




#define g_app_frame (*(undefined4 *)(0x81c2b0f4u))
#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
/* VA 0x81c0a990; body bytes 332 */

void FUN_81c0a990(uint param_1,uint param_2)

{

  if (param_1 == 0) {
    if (param_2 != 0) {
      bda_sango_gui_draw_guard(1);
      bda_sango_gui_context_copy(param_2,0,0,0xf0,0x140,g_draw_context,0,0,0xf81f);
      bda_sango_gui_request_redraw(g_app_frame,0,0);
      bda_sango_gui_draw_guard(0);
    }
  }
  else {
    if (param_2 == 0) {
      param_2 = g_draw_context;
    }
    else {
    }
    bda_sango_gui_context_copy(param_2,0,0,0xf0,0x140,param_1,0,0,0xf81f);
  }
  return;
}


#undef g_app_frame
#undef g_draw_context


/* VA 0x81c0aadc; body bytes 8 */

void FUN_81c0aadc(void)

{
  return;
}




#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
/* VA 0x81c0aae4; body bytes 232 */

void FUN_81c0aae4(short param_1,short param_2,short param_3,short param_4,uint param_5)

{
  unsigned char sg_stack[20] __attribute__((aligned(8)));
  (*(uint *)(sg_stack + 0)) = param_5;
#define param_5 (*(uint *)(sg_stack + 0))

  int iVar1;
  int iVar2;

  iVar2 = (int)param_1;
  iVar1 = (int)param_2;
  if (param_5 == 0) {
    bda_sango_gui_draw_guard(1);
    bda_sango_gui_draw_aux_rectangle(g_draw_context,iVar2,iVar1,param_3 - iVar2,param_4 - iVar1);
    bda_sango_gui_draw_guard(0);
  }
  else {
    bda_sango_gui_draw_aux_rectangle(param_5,iVar2,iVar1,param_3 - iVar2,param_4 - iVar1);
  }
  return;
}


#undef g_draw_context
#undef param_5


/* VA 0x81c0abcc; body bytes 52 */

int FUN_81c0abcc(byte *param_1)

{
  return (((uint)param_1[3] * 0x100 + (uint)param_1[2]) * 0x100 + (uint)param_1[1]) * 0x100 +
         (uint)*param_1;
}





/* VA 0x81c0ac00; body bytes 72 */

undefined4
FUN_81c0ac00(ushort *param_1,undefined4 param_2,undefined4 param_3,uint *param_4,uint *param_5)

{
  unsigned char sg_stack[20] __attribute__((aligned(8)));
  (*(uint * *)(sg_stack + 0)) = param_5;
#define param_5 (*(uint * *)(sg_stack + 0))

  undefined4 uVar1;

  uVar1 = 0;
  if (((param_1 != (ushort *)0x0) && (param_4 != (uint *)0x0)) && (param_5 != (uint *)0x0)) {
    uVar1 = 1;
    *param_4 = (uint)*param_1;
    *param_5 = (uint)param_1[1];
  }
  return uVar1;
}


#undef param_5


/* VA 0x81c0ac48; body bytes 72 */

void FUN_81c0ac48(short param_1,short param_2,short param_3,short param_4,uint param_5,uint param_6)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
  (*(uint *)(sg_stack + 0)) = param_5;
  (*(uint *)(sg_stack + 4)) = param_6;
#define param_5 (*(uint *)(sg_stack + 0))
#define param_6 (*(uint *)(sg_stack + 4))

  FUN_81c08100(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}


#undef param_5
#undef param_6

#define DAT_81c2b210 (*(undefined1 *)(0x81c2b210u))
#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
/* VA 0x81c0ad1c; body bytes 192 */

void FUN_81c0ad1c(undefined2 *param_1,uint param_2)

{
  int iVar2;

  bda_sango_gui_current_font(param_2);
  bda_sango_gui_select_font(g_draw_context,param_2 & 0xff);
  iVar2 = bda_sango_gui_font_cell_width(g_draw_context);
  param_1[1] = (short)iVar2;
  iVar2 = bda_sango_gui_font_cell_height(g_draw_context);
  *param_1 = (short)iVar2;
  bda_sango_gui_select_font(g_draw_context,(uint)DAT_81c2b210);
  return;
}


#undef DAT_81c2b210
#undef g_draw_context

#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
/* VA 0x81c0addc; body bytes 212 */

void FUN_81c0addc(short param_1,short param_2,char *param_3,uint param_4)

{
  if (param_4 == 0) {
    bda_sango_gui_draw_guard(1);
    bda_sango_gui_draw_text(g_draw_context,(int)param_1,(int)param_2,param_3,-1);
    bda_sango_gui_draw_guard(0);
  }
  else {
    bda_sango_gui_draw_text(param_4,(int)param_1,(int)param_2,param_3,-1);
  }
  return;
}


#undef g_draw_context


/* VA 0x81c0aeb0; body bytes 40 */

void bbk_clearerr(void *file)

{
  bda_sango_fs_clearerr(file);
  return;
}





/* VA 0x81c0aed8; body bytes 40 */

int bbk_ferror(void *file)

{
  int iVar1;

  iVar1 = bda_sango_fs_ferror(file);
  return iVar1;
}





/* VA 0x81c0af00; body bytes 40 */

int bbk_fclose(void *file)

{
  int iVar1;

  iVar1 = bda_sango_fs_fclose(file);
  return iVar1;
}





/* VA 0x81c0af28; body bytes 40 */

int bbk_feof(void *file)

{
  int iVar1;

  iVar1 = bda_sango_fs_feof(file);
  return iVar1;
}





/* VA 0x81c0af50; body bytes 8 */

undefined4 FUN_81c0af50(void)

{
  return 0;
}





/* VA 0x81c0af58; body bytes 8 */

undefined4 FUN_81c0af58(void)

{
  return 0;
}





/* VA 0x81c0af60; body bytes 40 */

void * bbk_fopen(char *path,char *mode)

{
  void *pvVar1;

  pvVar1 = bda_sango_fs_fopen(path,mode);
  return pvVar1;
}





/* VA 0x81c0af88; body bytes 8 */

undefined4 FUN_81c0af88(void)

{
  return 0;
}





/* VA 0x81c0af90; body bytes 8 */

undefined4 FUN_81c0af90(void)

{
  return 0;
}





/* VA 0x81c0af98; body bytes 68 */

uint bbk_fread(void *buffer,uint size,uint count,void *file)

{
  if ((size != 0) && (count != 0)) {
    count = bda_sango_fs_fread(buffer,size,count,file);
  }
  return count;
}





/* VA 0x81c0afdc; body bytes 40 */

int bbk_fseek(void *file,int offset,int whence)

{
  int iVar1;

  iVar1 = bda_sango_fs_fseek(file,offset,whence);
  return iVar1;
}





/* VA 0x81c0b004; body bytes 40 */

int bbk_ftell(void *file)

{
  int iVar1;

  iVar1 = bda_sango_fs_ftell(file);
  return iVar1;
}





/* VA 0x81c0b02c; body bytes 68 */

uint FUN_81c0b02c(void *param_1,uint param_2,uint param_3,void *param_4)

{
  if ((param_2 != 0) && (param_3 != 0)) {
    param_3 = bda_sango_fs_fwrite(param_1,param_2,param_3,param_4);
  }
  return param_3;
}





/* VA 0x81c0b070; body bytes 8 */

undefined4 FUN_81c0b070(void)

{
  return 0;
}





/* VA 0x81c0b078; body bytes 8 */

undefined4 FUN_81c0b078(void)

{
  return 0;
}





/* VA 0x81c0b080; body bytes 8 */

undefined4 FUN_81c0b080(void)

{
  return 0;
}





/* VA 0x81c0b088; body bytes 8 */

undefined4 FUN_81c0b088(void)

{
  return 0;
}





/* VA 0x81c0b090; body bytes 8 */

undefined4 FUN_81c0b090(void)

{
  return 0;
}





/* VA 0x81c0b098; body bytes 40 */

int bbk_rename(char *old_path,char *new_path)

{
  int iVar1;

  iVar1 = bda_sango_fs_rename(old_path,new_path);
  return iVar1;
}





/* VA 0x81c0b0c0; body bytes 8 */

void FUN_81c0b0c0(void)

{
  return;
}




#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
/* VA 0x81c0b0c8; body bytes 464 */

void * bbk_load_file_with_progress(char *path)

{
  short sVar1;
  uint uVar2;
  void *pvVar3;
  int iVar4;
  void *pvVar5;
  void *pvVar6;
  uint uVar7;
  uint uVar8;

  pvVar3 = bda_sango_fs_fopen(path,(char *)0x81c20260);
  pvVar6 = (void *)0x0;
  if (pvVar3 != 0) {
    bda_sango_fs_fseek(pvVar3,0,2);
    iVar4 = bda_sango_fs_ftell(pvVar3);
    uVar2 = iVar4 / 100;
    pvVar5 = bda_sango_mem_alloc(iVar4 + 1);
    pvVar6 = (void *)0x0;
    if (pvVar5 != 0) {
      uVar8 = 0;
      bda_sango_fs_fseek(pvVar3,0,0);
      FUN_81c08100(0x12,0x118,0xde,0x124,0,0);
      uVar7 = 0;
      do {
        bda_sango_fs_read_at((void *)((int)pvVar5 + uVar7),uVar7,uVar2,pvVar3);
        uVar7 = bda_sango_gui_rgb(g_draw_context,0x1f,0x78,0xa5);
        sVar1 = (short)uVar8 * 2;
        FUN_81c08100(sVar1 + 0x14,0x11a,sVar1 + 0x16,0x122,uVar7,0);
        uVar8 = uVar8 + 1 & 0xff;
        uVar7 = uVar8 * uVar2;
      } while (uVar8 < 100);
      bda_sango_fs_fread((void *)((int)pvVar5 + uVar2 * 100),iVar4 % 100,1,pvVar3);
      bda_sango_fs_fclose(pvVar3);
      pvVar6 = pvVar5;
    }
  }
  return pvVar6;
}


#undef g_draw_context


/* VA 0x81c0b2c4; body bytes 8 */

undefined4 FUN_81c0b2c4(void)

{
  return 1;
}





/* VA 0x81c0b2cc; body bytes 8 */

undefined4 FUN_81c0b2cc(void)

{
  return 1;
}





/* VA 0x81c0b2d4; body bytes 8 */

undefined4 FUN_81c0b2d4(void)

{
  return 1;
}




#define DAT_81c2b218 (*(int *)(0x81c2b218u))
/* VA 0x81c0b404; body bytes 252 */

void FUN_81c0b404(uint param_1)

{
  unsigned char sg_stack[48] __attribute__((aligned(8)));
#define auStack_38 (*(undefined1 (*)[32])(sg_stack + 0))

  bool bVar1;
  int iVar2;
  uint uVar3;

  uVar3 = 0;
  bVar1 = true;
  do {
    iVar2 = bda_sango_gui_event_poll(auStack_38,0);
    if (iVar2 != 0) {
      bda_sango_gui_event_step(auStack_38);
      bda_sango_gui_event_dispatch(auStack_38);
      iVar2 = DAT_81c2b218;
      DAT_81c2b218 = 0;
      if (iVar2 == 0x144) {
        uVar3 = uVar3 + 1;
      }
      if (iVar2 == 0x10) {
        bVar1 = false;
      }
      if (param_1 / 0x2a <= uVar3) {
        bVar1 = false;
      }
    }
  } while (bVar1);
  return;
}


#undef DAT_81c2b218
#undef auStack_38


/* VA 0x81c0b500; body bytes 8 */

int graphics_init_stub(void)

{
  return 1;
}





/* VA 0x81c0b508; body bytes 8 */

undefined4 FUN_81c0b508(void)

{
  return 1;
}




#define g_app_frame (*(undefined4 *)(0x81c2b0f4u))
#define g_draw_context (*(undefined4 *)(0x81c2b0fcu))
/* VA 0x81c0b510; body bytes 372 */

int bbk_message_box(char *message,char *title,uint flags)

{
  void *pvVar1;
  int iVar2;

  pvVar1 = bda_sango_gui_compatible_create(g_draw_context);
  iVar2 = -1;
  if (pvVar1 != 0) {
    bda_sango_gui_context_copy(g_draw_context,0,0,0xf0,0x140,(uint)pvVar1,0,0,0xf81f);
    iVar2 = bda_sango_gui_message_box(0,message,title,flags);
    bda_sango_gui_draw_guard(1);
    bda_sango_gui_context_copy((uint)pvVar1,0,0,0xf0,0x140,g_draw_context,0,0,0xf81f);
    bda_sango_gui_request_redraw(g_app_frame,0,0);
    bda_sango_gui_draw_guard(0);
    bda_sango_gui_compatible_free(pvVar1);
  }
  return iVar2;
}


#undef g_app_frame
#undef g_draw_context

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c2b161 (*(char *)(0x81c2b161u))
#define DAT_81c2b468 (*(undefined2 *)(0x81c2b468u))
#define DAT_81c2b46a (*(undefined2 *)(0x81c2b46au))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c0b6f0; body bytes 1408 */

undefined4 FUN_81c0b6f0(int param_1)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  char *destination;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  byte index;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint unaff_s5;
  uint uVar10;
  char *source;

  FUN_81c13494();
  destination = g_scratch_buffer_4096;
  uVar4 = bbk_rand();
  uVar8 = uVar4 + 3;
  if (-1 < (int)uVar4) {
    uVar8 = uVar4;
  }
  bVar2 = *(byte *)(param_1 + 1);
  uVar9 = (uint)bVar2;
  uVar8 = uVar4 + ((int)uVar8 >> 2) * -4 & 0xff;
  iVar7 = uVar9 * 0x10 + DAT_81c2b164;
  uVar4 = (uint)*(byte *)(iVar7 + 4);
  source = destination + 0x28;
  bVar3 = *(byte *)(iVar7 + 1);
  uVar10 = (uint)bVar3;
  if (uVar8 == 1) {
    uVar8 = 0;
    uVar5 = bbk_rand();
    unaff_s5 = (int)uVar5 % 0x96 & 0xff;
    uVar5 = (int)uVar5 % 0x96 & 1;
    if (unaff_s5 < uVar4) {
      if (uVar5 == 0) {
        uVar5 = FUN_81c13918((uint)*(byte *)(param_1 + 2),(int)destination);
        if (uVar5 != 0) {
          uVar6 = bbk_rand();
          if (uVar5 == 0) {
            trap(7);
          }
          unaff_s5 = 0;
          index = destination[(int)uVar6 % (int)uVar5 & 0xff];
          iVar7 = FUN_81c152f0(0x3f,DAT_81c2b161,g_sango_package_data);
          uVar5 = (uint)*(byte *)(iVar7 + (uint)index * 3 + 1);
          if (uVar5 - 1 == uVar9) {
LAB_81c0bc08:
            unaff_s5 = 1;
            iVar7 = (uint)index * 0x10;
            *(byte *)(iVar7 + DAT_81c2b164 + 1) = bVar3;
            iVar7 = iVar7 + DAT_81c2b164;
            uVar4 = bbk_rand();
            *(char *)(iVar7 + 5) = (char)uVar4 + (char)((int)uVar4 / 0x1e) * -0x1e + 'F';
          }
          else if (uVar5 == 0) {
            uVar9 = bbk_rand();
            unaff_s5 = 2;
            if (((int)uVar9 % 0x6e & 0xffU) < uVar4) goto LAB_81c0bc08;
          }
          uVar9 = (uint)DAT_81c2b115;
          if (uVar10 != uVar9 + 1) goto LAB_81c0b79c;
          uVar8 = 1;
          if (unaff_s5 == 0) {
            FUN_81c154d8(0x40,100,destination);
            index = bVar2;
          }
          else {
            FUN_81c154d8(0x40,99,destination);
            sango_load_named_text(index,source);
            bbk_strcat(destination,source);
            FUN_81c18024(bVar2,destination);
            if (unaff_s5 == 1) {
              uVar9 = bbk_rand();
              uVar4 = uVar9 + 3;
              if (-1 < (int)uVar9) {
                uVar4 = uVar9;
              }
              uVar4 = (uVar9 + ((int)uVar4 >> 2) * -4) - 0x7a;
LAB_81c0bb8c:
              unaff_s5 = uVar4 & 0xff;
            }
            else if (unaff_s5 == 2) {
              uVar9 = bbk_rand();
              uVar4 = uVar9 + 3;
              if (-1 < (int)uVar9) {
                uVar4 = uVar9;
              }
              uVar4 = (uVar9 + ((int)uVar4 >> 2) * -4) - 0x76;
              goto LAB_81c0bb8c;
            }
            FUN_81c154d8(0x40,unaff_s5,destination);
          }
          FUN_81c18024(index,destination);
        }
      }
      else if ((uVar5 == 1) &&
              (uVar4 = FUN_81c18248((uint)*(byte *)(param_1 + 2),(int)destination), uVar4 != 0)) {
        uVar5 = bbk_rand();
        if (uVar4 == 0) {
          trap(7);
        }
        bVar3 = destination[(int)uVar5 % (int)uVar4 & 0xff];
        iVar7 = FUN_81c152f0(0x43,DAT_81c2b161,g_sango_package_data);
        uVar4 = (uint)*(byte *)(iVar7 + (uint)bVar3 * 3 + 1);
        if ((uVar4 == 0) || (uVar4 - 1 == uVar9)) {
          bVar1 = uVar10 == DAT_81c2b115 + 1;
          if (bVar1) {
            FUN_81c154d8(0x40,99,destination);
            FUN_81c18c80(bVar3,source);
            bbk_strcat(destination,source);
            FUN_81c18024(bVar2,destination);
          }
          uVar8 = (uint)bVar1;
          FUN_81c18150(bVar3);
        }
      }
    }
  }
  else if (1 < uVar8) {
    if (uVar8 == 2) {
      uVar5 = bbk_rand();
      if (uVar4 == 0) {
        trap(7);
      }
      uVar9 = (uint)DAT_81c2b115;
      unaff_s5 = (int)uVar5 % (int)(uVar4 << 1) + 10U & 0xff;
      (&DAT_81c2b468)[(uint)*(byte *)(param_1 + 2) * 0x12] =
           (&DAT_81c2b468)[(uint)*(byte *)(param_1 + 2) * 0x12] + (short)unaff_s5;
      goto LAB_81c0b79c;
    }
    if (uVar8 == 3) {
      uVar5 = bbk_rand();
      if (uVar4 == 0) {
        trap(7);
      }
      uVar9 = (uint)DAT_81c2b115;
      unaff_s5 = (int)uVar5 % (int)(uVar4 << 1) + 10U & 0xff;
      (&DAT_81c2b46a)[(uint)*(byte *)(param_1 + 2) * 0x12] =
           (&DAT_81c2b46a)[(uint)*(byte *)(param_1 + 2) * 0x12] + (short)unaff_s5;
      goto LAB_81c0b79c;
    }
  }
  uVar9 = (uint)DAT_81c2b115;
LAB_81c0b79c:
  if ((uVar10 == uVar9 + 1) && (uVar8 != 1)) {
    if (uVar8 == 0) {
      FUN_81c154d8(0x40,0x65,destination);
    }
    else {
      FUN_81c154d8(0x40,uVar8 + 100 & 0xff,destination);
      FUN_81c0a7e4(unaff_s5,source,10);
      bbk_strcat(destination,source);
    }
    FUN_81c18024(bVar2,destination);
    bVar3 = *(byte *)(param_1 + 2);
  }
  else {
    bVar3 = *(byte *)(param_1 + 2);
  }
  FUN_81c134b8((uint)bVar3,bVar2);
  return 1;
}


#undef DAT_81c2b164
#undef DAT_81c2b115
#undef DAT_81c2b161
#undef DAT_81c2b468
#undef DAT_81c2b46a
#undef g_scratch_buffer_4096
#undef g_sango_package_data

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0bc70; body bytes 692 */

undefined4 FUN_81c0bc70(int param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  bool bVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  int iVar8;
  int iVar9;

  bVar1 = *(byte *)(param_1 + 1);
  bVar2 = *(byte *)(param_1 + 3);
  iVar9 = (uint)bVar1 * 0x10;
  iVar8 = DAT_81c2b164 + (uint)bVar2 * 0x10;
  bVar4 = false;
  if (*(char *)(iVar8 + 1) != *(char *)(iVar9 + DAT_81c2b164 + 1)) {
    uVar6 = ((uint)*(byte *)(iVar9 + DAT_81c2b164 + 4) - (uint)*(byte *)(iVar8 + 4)) + 0x32 & 0xff;
    uVar5 = bbk_rand();
    if (((int)uVar5 % 100 & 0xffU) <= uVar6) {
      switch(*(undefined1 *)(iVar8 + 6)) {
      case 0:
        uVar6 = 2;
        break;
      case 1:
        uVar6 = 5;
        break;
      case 2:
        uVar6 = 4;
        break;
      case 3:
        uVar6 = 3;
        break;
      case 4:
        uVar6 = 1;
      }
      bVar3 = *(byte *)(iVar8 + 5);
      *(byte *)(iVar8 + 5) = bVar3 - bVar3 / 10;
      if (bVar3 < 0x3d) {
        if (uVar6 == 0) {
          trap(7);
        }
        uVar5 = bbk_rand();
        if (bVar3 / uVar6 <= ((int)uVar5 % 100 & 0xffU)) {
          bVar4 = true;
          *(undefined1 *)(iVar8 + 1) = *(undefined1 *)(iVar9 + DAT_81c2b164 + 1);
          uVar5 = bbk_rand();
          *(char *)(iVar8 + 5) = (char)uVar5 + (char)((int)uVar5 / 0x28) * -0x28 + '(';
        }
      }
    }
    if ((uint)*(byte *)(iVar9 + DAT_81c2b164 + 1) == DAT_81c2b115 + 1) {
      if (bVar4) {
        FUN_81c116a0(bVar2);
        uVar5 = (uint)*(byte *)(param_1 + 2);
      }
      else {
        pcVar7 = (char *)(g_scratch_buffer_4096 + 300);
        uVar5 = bbk_rand();
        FUN_81c154d8(0x40,(int)uVar5 % 3 + 0x7aU & 0xff,pcVar7);
        FUN_81c13494();
        FUN_81c18024(bVar2,pcVar7);
        uVar5 = (uint)*(byte *)(param_1 + 2);
      }
      goto LAB_81c0bd9c;
    }
  }
  uVar5 = (uint)*(byte *)(param_1 + 2);
LAB_81c0bd9c:
  FUN_81c134b8(uVar5,bVar1);
  return 1;
}


#undef DAT_81c2b164
#undef DAT_81c2b115
#undef g_scratch_buffer_4096

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c20284 (*(undefined *)(0x81c20284u))
/* VA 0x81c0bf24; body bytes 580 */

undefined4 FUN_81c0bf24(int param_1)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;

  iVar4 = (uint)*(byte *)(param_1 + 3) * 0x10;
  uVar3 = ((uint)*(byte *)((uint)*(byte *)(param_1 + 1) * 0x10 + DAT_81c2b164 + 4) -
          (uint)*(byte *)(iVar4 + DAT_81c2b164 + 4)) + 0x32 & 0xff;
  uVar1 = bbk_rand();
  if (uVar3 < ((int)uVar1 % 100 & 0xffU)) {
LAB_81c0bfbc:
    bVar2 = *(byte *)(param_1 + 1);
    if ((uint)*(byte *)((uint)bVar2 * 0x10 + DAT_81c2b164 + 1) != DAT_81c2b115 + 1)
    goto LAB_81c0bfec;
LAB_81c0c018:
    FUN_81c18024(bVar2,&DAT_81c20284);
  }
  else {
    uVar1 = bbk_rand();
    if (((int)uVar1 % 100 & 0xffU) < (uint)*(byte *)(iVar4 + DAT_81c2b164 + 5)) {
      bVar2 = *(byte *)(param_1 + 1);
      if ((uint)*(byte *)((uint)bVar2 * 0x10 + DAT_81c2b164 + 1) != DAT_81c2b115 + 1)
      goto LAB_81c0bfec;
      goto LAB_81c0c018;
    }
    switch(*(undefined1 *)(iVar4 + DAT_81c2b164 + 6)) {
    case 0:
      uVar3 = 0x32;
      break;
    case 1:
    case 3:
      uVar3 = 0x1e;
      break;
    case 2:
      uVar3 = 0x28;
      break;
    case 4:
      uVar3 = 5;
    }
    uVar1 = bbk_rand();
    if (uVar3 < ((int)uVar1 % 100 & 0xffU)) goto LAB_81c0bfbc;
    iVar4 = iVar4 + DAT_81c2b164;
    if (*(byte *)(iVar4 + 5) < 5) {
      *(undefined1 *)(iVar4 + 5) = 0;
    }
    else {
      *(byte *)(iVar4 + 5) = *(byte *)(iVar4 + 5) - 4;
    }
  }
  bVar2 = *(byte *)(param_1 + 1);
LAB_81c0bfec:
  FUN_81c134b8((uint)*(byte *)(param_1 + 2),bVar2);
  return 1;
}


#undef DAT_81c2b164
#undef DAT_81c2b115
#undef DAT_81c20284

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c202a8 (*(undefined *)(0x81c202a8u))
#define DAT_81c202b8 (*(undefined *)(0x81c202b8u))
/* VA 0x81c0c168; body bytes 808 */

undefined4 FUN_81c0c168(int param_1)

{
  byte bVar1;
  uint uVar2;
  byte bVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  int iVar7;

  bVar3 = *(byte *)(param_1 + 3);
  bVar1 = *(byte *)(param_1 + 1);
  iVar6 = (uint)bVar3 * 0x10;
  iVar7 = (uint)bVar1 * 0x10;
  uVar5 = ((uint)*(byte *)(iVar7 + DAT_81c2b164 + 4) - (uint)*(byte *)(iVar6 + DAT_81c2b164 + 4)) +
          0x32 & 0xff;
  uVar2 = bbk_rand();
  if (uVar5 < ((int)uVar2 % 100 & 0xffU)) {
LAB_81c0c20c:
    bVar3 = *(byte *)(param_1 + 1);
    if ((uint)*(byte *)((uint)bVar3 * 0x10 + DAT_81c2b164 + 1) == DAT_81c2b115 + 1) {
LAB_81c0c270:
      pcVar4 = &DAT_81c202a8;
LAB_81c0c278:
      FUN_81c18024(bVar3,pcVar4);
      uVar2 = (uint)*(byte *)(param_1 + 2);
      goto LAB_81c0c23c;
    }
  }
  else {
    uVar2 = bbk_rand();
    if (((int)uVar2 % 100 & 0xffU) < (uint)*(byte *)(iVar6 + DAT_81c2b164 + 5)) {
      bVar3 = *(byte *)(param_1 + 1);
      if ((uint)*(byte *)((uint)bVar3 * 0x10 + DAT_81c2b164 + 1) == DAT_81c2b115 + 1)
      goto LAB_81c0c270;
    }
    else {
      switch(*(undefined1 *)(iVar6 + DAT_81c2b164 + 6)) {
      case 0:
        uVar5 = 0xf;
        break;
      case 1:
        uVar5 = 0x28;
        break;
      case 2:
        uVar5 = 0x1e;
        break;
      case 3:
        uVar5 = 0x14;
        break;
      case 4:
        uVar5 = 5;
      }
      uVar2 = bbk_rand();
      if (uVar5 < ((int)uVar2 % 100 & 0xffU)) {
        bVar3 = *(byte *)(param_1 + 1);
        if ((uint)*(byte *)((uint)bVar3 * 0x10 + DAT_81c2b164 + 1) == DAT_81c2b115 + 1) {
          pcVar4 = &DAT_81c202b8;
          goto LAB_81c0c278;
        }
      }
      else {
        uVar2 = FUN_81c137f0(bVar3);
        if (uVar2 == 0xff) goto LAB_81c0c20c;
        FUN_81c123f0(uVar2,bVar3);
        FUN_81c134b8((uint)*(byte *)(param_1 + 2),bVar3);
        *(undefined1 *)(iVar6 + DAT_81c2b164 + 1) = *(undefined1 *)(iVar7 + DAT_81c2b164 + 1);
        iVar6 = iVar6 + DAT_81c2b164;
        uVar2 = bbk_rand();
        *(char *)(iVar6 + 5) = (char)uVar2 + (char)((int)uVar2 / 0x28) * -0x28 + '(';
        if ((uint)*(byte *)(iVar7 + DAT_81c2b164 + 1) == DAT_81c2b115 + 1) {
          FUN_81c116a0(bVar3);
          uVar2 = (uint)*(byte *)(param_1 + 2);
          goto LAB_81c0c23c;
        }
      }
    }
  }
  uVar2 = (uint)*(byte *)(param_1 + 2);
LAB_81c0c23c:
  FUN_81c134b8(uVar2,bVar1);
  return 1;
}


#undef DAT_81c2b164
#undef DAT_81c2b115
#undef DAT_81c202a8
#undef DAT_81c202b8

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c202e0 (*(undefined *)(0x81c202e0u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0c490; body bytes 708 */

undefined4 FUN_81c0c490(int param_1)

{
  uint uVar1;
  byte *pbVar2;
  byte bVar3;
  char cVar4;
  uint uVar5;
  int iVar6;

  bVar3 = *(byte *)(param_1 + 3);
  iVar6 = (uint)bVar3 * 0x10;
  uVar5 = ((uint)*(byte *)((uint)*(byte *)(param_1 + 1) * 0x10 + DAT_81c2b164 + 4) -
          (uint)*(byte *)(iVar6 + DAT_81c2b164 + 4)) + 0x32 & 0xff;
  uVar1 = bbk_rand();
  if (uVar5 < ((int)uVar1 % 100 & 0xffU)) {
LAB_81c0c52c:
    bVar3 = *(byte *)(param_1 + 1);
    if ((uint)*(byte *)((uint)bVar3 * 0x10 + DAT_81c2b164 + 1) != DAT_81c2b115 + 1)
    goto LAB_81c0c55c;
  }
  else {
    uVar1 = bbk_rand();
    if ((uint)*(byte *)(iVar6 + DAT_81c2b164 + 5) <= ((int)uVar1 % 100 & 0xffU)) {
      switch(*(undefined1 *)(iVar6 + DAT_81c2b164 + 6)) {
      case 0:
        uVar5 = 0x1e;
        break;
      case 1:
        uVar5 = 10;
        break;
      case 2:
        uVar5 = 0x14;
        break;
      case 3:
        uVar5 = 0x3c;
        break;
      case 4:
        uVar5 = 5;
      }
      uVar1 = bbk_rand();
      if (((int)uVar1 % 100 & 0xffU) <= uVar5) {
        uVar1 = FUN_81c137f0(bVar3);
        cVar4 = bVar3 + 1;
        if (uVar1 != 0xff) {
          *(char *)(iVar6 + DAT_81c2b164 + 1) = cVar4;
          iVar6 = g_scratch_buffer_4096;
          uVar5 = FUN_81c13870(uVar1,g_scratch_buffer_4096);
          (&DAT_81c2b451)[uVar1 * 0x24] = cVar4;
          uVar1 = 0;
          if (uVar5 != 0) {
            do {
              pbVar2 = (byte *)(iVar6 + uVar1);
              uVar1 = uVar1 + 1 & 0xff;
              *(char *)((uint)*pbVar2 * 0x10 + DAT_81c2b164 + 1) = cVar4;
            } while (uVar1 < uVar5);
          }
          FUN_81c11638(bVar3);
          bVar3 = *(byte *)(param_1 + 1);
          goto LAB_81c0c55c;
        }
      }
      goto LAB_81c0c52c;
    }
    bVar3 = *(byte *)(param_1 + 1);
    if ((uint)*(byte *)((uint)bVar3 * 0x10 + DAT_81c2b164 + 1) != DAT_81c2b115 + 1)
    goto LAB_81c0c55c;
  }
  FUN_81c18024(bVar3,&DAT_81c202e0);
  bVar3 = *(byte *)(param_1 + 1);
LAB_81c0c55c:
  FUN_81c134b8((uint)*(byte *)(param_1 + 2),bVar3);
  return 1;
}


#undef DAT_81c2b164
#undef DAT_81c2b115
#undef DAT_81c202e0
#undef DAT_81c2b451
#undef g_scratch_buffer_4096

#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c20304 (*(undefined *)(0x81c20304u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0c754; body bytes 1040 */

undefined4 FUN_81c0c754(int param_1)

{
  byte index;
  byte bVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  byte bVar5;
  uint uVar6;
  uint uVar7;
  char *source;
  char *destination;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint unaff_s5;

  iVar4 = g_scratch_buffer_4096;
  uVar7 = (uint)DAT_81c2b115;
  index = *(byte *)(param_1 + 3);
  uVar10 = (uint)index;
  bVar1 = *(byte *)(param_1 + 1);
  bVar2 = false;
  if (uVar7 == uVar10) {
    bVar5 = bVar1;
    if ((uint)*(byte *)((uint)bVar1 * 0x10 + DAT_81c2b164 + 1) != uVar10 + 1) goto LAB_81c0c844;
  }
  else {
    iVar9 = (uint)bVar1 * 0x10;
    bVar5 = *(byte *)(iVar9 + DAT_81c2b164 + 1);
    unaff_s5 = (uint)bVar5;
    iVar8 = uVar10 * 0x10;
    uVar7 = FUN_81c13794(unaff_s5 - 1 & 0xff,g_scratch_buffer_4096);
    uVar3 = FUN_81c13794(*(byte *)(iVar8 + DAT_81c2b164 + 1) - 1 & 0xff,iVar4);
    if ((int)(uVar3 << 1) <= (int)uVar7) {
      uVar3 = ((uint)*(byte *)(iVar9 + DAT_81c2b164 + 4) - (uint)*(byte *)(iVar8 + DAT_81c2b164 + 4)
              ) + 0x32 & 0xff;
      uVar7 = bbk_rand();
      if (((int)uVar7 % 100 & 0xffU) <= uVar3) {
        switch(*(undefined1 *)(iVar8 + DAT_81c2b164 + 6)) {
        case 0:
          uVar3 = 10;
          break;
        case 1:
          uVar3 = 1;
          break;
        case 2:
          uVar3 = 0x14;
          break;
        case 3:
          uVar3 = 5;
          break;
        case 4:
          uVar3 = 0xf;
        }
        uVar7 = bbk_rand();
        if (((int)uVar7 % 100 & 0xffU) <= uVar3) {
          iVar8 = g_scratch_buffer_4096 + 0x26;
          uVar7 = FUN_81c13794(uVar10,iVar4);
          uVar10 = 0;
          if (uVar7 != 0) {
            do {
              uVar3 = FUN_81c13870((uint)*(byte *)(iVar4 + uVar10),iVar8);
              (&DAT_81c2b451)[(uint)*(byte *)(iVar4 + uVar10) * 0x24] = bVar5;
              uVar6 = 0;
              if (uVar3 != 0) {
                do {
                  uVar6 = uVar6 + 1 & 0xff;
                  *(byte *)((uint)*(byte *)(iVar8 + uVar10) * 0x10 + DAT_81c2b164 + 1) = bVar5;
                } while (uVar6 < uVar3);
              }
              uVar10 = uVar10 + 1 & 0xff;
            } while (uVar10 < uVar7);
          }
          uVar7 = (uint)DAT_81c2b115;
          bVar2 = true;
          goto LAB_81c0c844;
        }
      }
    }
    uVar7 = (uint)DAT_81c2b115;
    bVar5 = *(byte *)(param_1 + 1);
    if ((uint)*(byte *)((uint)*(byte *)(param_1 + 1) * 0x10 + DAT_81c2b164 + 1) != uVar7 + 1)
    goto LAB_81c0c844;
  }
  FUN_81c18024(bVar5,&DAT_81c20304);
  uVar7 = (uint)DAT_81c2b115;
LAB_81c0c844:
  source = (char *)(g_scratch_buffer_4096 + 0x154);
  destination = (char *)(g_scratch_buffer_4096 + 300);
  if (unaff_s5 == uVar7 + 1) {
    iVar4 = 0x9d;
    if (!bVar2) {
      iVar4 = 0x99;
    }
    uVar10 = bbk_rand();
    uVar7 = uVar10 + 3;
    if (-1 < (int)uVar10) {
      uVar7 = uVar10;
    }
    FUN_81c154d8(0x40,iVar4 + uVar10 + ((int)uVar7 >> 2) * -4 & 0xff,destination);
    FUN_81c13494();
    FUN_81c18024(index,destination);
    uVar7 = (uint)*(byte *)(param_1 + 2);
  }
  else if (bVar2) {
    sango_load_named_text(index,destination);
    FUN_81c154d8(0x40,0x6e,source);
    bbk_strcat(destination,source);
    sango_load_named_text((char)unaff_s5 + 0xff,source);
    bbk_strcat(destination,source);
    FUN_81c14dd8(destination,2);
    uVar7 = (uint)*(byte *)(param_1 + 2);
  }
  else {
    uVar7 = (uint)*(byte *)(param_1 + 2);
  }
  FUN_81c134b8(uVar7,bVar1);
  return 1;
}


#undef DAT_81c2b115
#undef DAT_81c2b164
#undef DAT_81c20304
#undef DAT_81c2b451
#undef g_scratch_buffer_4096

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c2b456 (*(undefined2 *)(0x81c2b456u))
#define DAT_81c2b45a (*(undefined2 *)(0x81c2b45au))
#define DAT_81c2b45c (*(undefined1 *)(0x81c2b45cu))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
#define DAT_81c2b468 (*(undefined2 *)(0x81c2b468u))
#define DAT_81c2b46a (*(undefined2 *)(0x81c2b46au))
/* VA 0x81c0cb64; body bytes 420 */

undefined4 FUN_81c0cb64(int param_1)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  char *destination;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  char *source;

  iVar4 = DAT_81c2b164;
  uVar5 = (uint)*(byte *)(param_1 + 2);
  uVar2 = (&DAT_81c2b456)[uVar5 * 0x12];
  uVar3 = (&DAT_81c2b45a)[uVar5 * 0x12];
  (&DAT_81c2b45c)[uVar5 * 0x24] = (byte)(&DAT_81c2b45c)[uVar5 * 0x24] >> 1;
  (&DAT_81c2b456)[uVar5 * 0x12] = uVar2 >> 1;
  (&DAT_81c2b45a)[uVar5 * 0x12] = uVar3 >> 1;
  iVar6 = (uint)*(byte *)(param_1 + 1) * 0x10 + iVar4;
  uVar8 = (uint)DAT_81c2b115;
  iVar6 = (uint)*(byte *)(iVar6 + 4) + (uint)*(byte *)(iVar6 + 3);
  iVar7 = iVar6 * 2;
  iVar6 = iVar6 * 5;
  (&DAT_81c2b468)[uVar5 * 0x12] = (short)iVar7 + (&DAT_81c2b468)[uVar5 * 0x12];
  (&DAT_81c2b46a)[uVar5 * 0x12] = (short)iVar6 + (&DAT_81c2b46a)[uVar5 * 0x12];
  destination = g_scratch_buffer_4096;
  bVar1 = *(byte *)(param_1 + 1);
  if ((uint)*(byte *)((uint)bVar1 * 0x10 + iVar4 + 1) == uVar8 + 1) {
    source = g_scratch_buffer_4096 + 100;
    FUN_81c154d8(0x40,0x95,g_scratch_buffer_4096);
    FUN_81c0a7e4(iVar7,source,10);
    bbk_strcat(destination,source);
    FUN_81c154d8(0x40,0x96,source);
    bbk_strcat(destination,source);
    FUN_81c0a7e4(iVar6,source,10);
    bbk_strcat(destination,source);
    FUN_81c154d8(0x40,0x97,source);
    bbk_strcat(destination,source);
    FUN_81c18024(*(uchar *)(param_1 + 1),destination);
    bVar1 = *(byte *)(param_1 + 1);
  }
  FUN_81c134b8((uint)*(byte *)(param_1 + 2),bVar1);
  return 1;
}


#undef DAT_81c2b164
#undef DAT_81c2b115
#undef DAT_81c2b456
#undef DAT_81c2b45a
#undef DAT_81c2b45c
#undef g_scratch_buffer_4096
#undef DAT_81c2b468
#undef DAT_81c2b46a

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define DAT_81c2b468 (*(undefined2 *)(0x81c2b468u))
#define DAT_81c2b46a (*(undefined2 *)(0x81c2b46au))
#define DAT_81c2b46c (*(undefined2 *)(0x81c2b46cu))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0cd08; body bytes 820 */

undefined4 FUN_81c0cd08(undefined1 *param_1)

{
  char cVar1;
  char cVar2;
  char *pcVar3;
  uint uVar4;
  byte bVar5;
  uint uVar6;

  FUN_81c0d03c();
  switch(*param_1) {
  case 0:
  case 0x14:
  case 0x15:
  case 0x16:
    goto switchD_81c0cd48_caseD_0;
  case 1:
    FUN_81c134b8((uint)(byte)param_1[2],param_1[1]);
    break;
  case 2:
    FUN_81c134b8((uint)(byte)param_1[2],param_1[1]);
  case 0xc:
    break;
  case 3:
    FUN_81c0b6f0((int)param_1);
    break;
  case 4:
    FUN_81c134b8((uint)(byte)param_1[2],param_1[1]);
    break;
  case 5:
    FUN_81c134b8((uint)(byte)param_1[2],param_1[1]);
    break;
  case 6:
    FUN_81c0bc70((int)param_1);
    break;
  case 7:
    break;
  case 8:
    break;
  case 9:
    break;
  case 10:
    break;
  case 0xb:
    FUN_81c134b8((uint)(byte)param_1[2],param_1[1]);
    break;
  case 0xd:
    uVar4 = bbk_rand();
    uVar6 = 0x78;
    if (0x14 < (int)uVar4 % 100) {
      uVar4 = (uint)(byte)param_1[3];
      uVar6 = 0x77;
      (&DAT_81c2b46a)[uVar4 * 0x12] = (&DAT_81c2b46a)[uVar4 * 0x12] + *(short *)(param_1 + 6);
      (&DAT_81c2b468)[uVar4 * 0x12] = (&DAT_81c2b468)[uVar4 * 0x12] + *(short *)(param_1 + 8);
      (&DAT_81c2b46c)[uVar4 * 0x12] = (&DAT_81c2b46c)[uVar4 * 0x12] + *(short *)(param_1 + 4);
    }
    pcVar3 = g_scratch_buffer_4096;
    FUN_81c154d8(0x40,uVar6,g_scratch_buffer_4096);
    FUN_81c18024(param_1[1],pcVar3);
    FUN_81c134b8((uint)(byte)param_1[2],param_1[1]);
    break;
  case 0xe:
    uVar4 = (uint)(byte)param_1[3];
    bVar5 = param_1[1];
    cVar1 = (&DAT_81c2b451)[uVar4 * 0x24];
    cVar2 = *(char *)((uint)bVar5 * 0x10 + DAT_81c2b164 + 1);
    if (cVar1 == '\0') {
      (&DAT_81c2b451)[uVar4 * 0x24] = cVar2;
      bVar5 = param_1[1];
    }
    else if (cVar1 != cVar2) {
      uVar4 = (uint)(byte)param_1[2];
    }
    FUN_81c134b8(uVar4,bVar5);
    break;
  case 0xf:
    FUN_81c0bf24((int)param_1);
    break;
  case 0x10:
    FUN_81c0c168((int)param_1);
    break;
  case 0x11:
    FUN_81c0c490((int)param_1);
    break;
  case 0x12:
    break;
  case 0x13:
    FUN_81c0c754((int)param_1);
    break;
  case 0x17:
    FUN_81c134b8((uint)(byte)param_1[2],param_1[1]);
    break;
  case 0x18:
    FUN_81c134b8((uint)(byte)param_1[2],param_1[1]);
    break;
  case 0x19:
    break;
  case 0x1a:
    FUN_81c0cb64((int)param_1);
    break;
  case 0x1b:
    FUN_81c10394((int)param_1);
    break;
  default:
    return 1;
  }
  FUN_81c0d03c();
switchD_81c0cd48_caseD_0:
  return 1;
}


#undef DAT_81c2b164
#undef DAT_81c2b451
#undef DAT_81c2b468
#undef DAT_81c2b46a
#undef DAT_81c2b46c
#undef g_scratch_buffer_4096

#define DAT_81c2b310 (*(undefined1 *)(0x81c2b310u))
#define DAT_81c2b311 (*(undefined1 *)(0x81c2b311u))
#define DAT_81c2b46f (*(undefined1 *)(0x81c2b46fu))
/* VA 0x81c0d03c; body bytes 168 */

void FUN_81c0d03c(void)

{
  unsigned char sg_stack[120] __attribute__((aligned(8)));
#define auStack_70 (*(undefined1 (*)[104])(sg_stack + 0))

  byte bVar1;
  uchar uVar2;
  int iVar3;
  uchar *puVar4;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  int iVar8;

  iVar7 = 0;
  pbVar5 = &DAT_81c2b46f;
  iVar3 = 0x25;
  do {
    bVar1 = *pbVar5;
    iVar3 = iVar3 + -1;
    pbVar5 = pbVar5 + 0x24;
    iVar7 = iVar7 + (uint)bVar1;
  } while (-1 < iVar3);
  iVar3 = 0;
  if (0 < iVar7 + -1) {
    do {
      iVar8 = iVar3 + 1;
      if (iVar8 < iVar7) {
        puVar4 = &DAT_81c2b311 + iVar3;
        iVar6 = iVar8;
        do {
          uVar2 = *puVar4;
          iVar6 = iVar6 + 1;
          puVar4 = puVar4 + 1;
          if ((&DAT_81c2b310)[iVar3] == uVar2) {
            sango_load_named_text((&DAT_81c2b310)[iVar3],auStack_70);
            return;
          }
        } while (iVar6 < iVar7);
      }
      iVar3 = iVar8;
    } while (iVar8 < iVar7 + -1);
  }
  return;
}


#undef DAT_81c2b310
#undef DAT_81c2b311
#undef DAT_81c2b46f
#undef auStack_70


/* VA 0x81c0d0e4; body bytes 36 */

undefined4 FUN_81c0d0e4(int param_1)

{
  FUN_81c134b8((uint)*(byte *)(param_1 + 2),*(byte *)(param_1 + 1));
  return 1;
}





/* VA 0x81c0d304; body bytes 8 */

undefined4 FUN_81c0d304(void)

{
  return 1;
}




#define g_state_buffer_1200 (*(undefined4 *)(0x81c2b0e4u))
/* VA 0x81c0d354; body bytes 136 */

void FUN_81c0d354(void)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;

  iVar1 = g_state_buffer_1200;
  uVar3 = 0;
  do {
    pcVar2 = (char *)(uVar3 * 0xc + iVar1);
    if (*pcVar2 != -1) {
      FUN_81c0cd08(pcVar2);
      FUN_81c117c0(pcVar2);
    }
    uVar3 = uVar3 + 1 & 0xff;
  } while (uVar3 < 100);
  return;
}


#undef g_state_buffer_1200


/* VA 0x81c0d3e0; body bytes 184 */

uint FUN_81c0d3e0(void)

{
  uint uVar1;

  while( true ) {
    while( true ) {
      while( true ) {
        FUN_81c13494();
        uVar1 = FUN_81c0d498();
        if (uVar1 != 2) break;
        uVar1 = FUN_81c0d5b8();
        if (uVar1 != 0xff) {
          return uVar1 + 0x17 & 0xff;
        }
      }
      if (2 < (int)uVar1) break;
      if (uVar1 == 0) {
        uVar1 = FUN_81c0d4f8();
        if (uVar1 != 0xff) {
          return uVar1 + 1 & 0xff;
        }
      }
      else if (uVar1 == 1) {
        uVar1 = FUN_81c0d558();
        if (uVar1 != 0xff) {
          return uVar1 + 0xf & 0xff;
        }
      }
    }
    if (uVar1 == 3) break;
    if (uVar1 == 0xff) {
      return 0xff;
    }
  }
  return 0xfe;
}





/* VA 0x81c0d498; body bytes 96 */

uint FUN_81c0d498(void)

{
  unsigned char sg_stack[56] __attribute__((aligned(8)));
#define local_30 (*(ushort (*)[4])(sg_stack + 0))
#define acStack_28 (*(char (*)[32])(sg_stack + 8))

  uint uVar1;

  FUN_81c154d8(0x40,0x25,acStack_28);
  local_30[0] = 0x4f;
  local_30[2] = 0x67;
  local_30[1] = 10;
  local_30[3] = 0x3a;
  uVar1 = FUN_81c07068(local_30,0,acStack_28);
  return uVar1;
}


#undef local_30
#undef acStack_28


/* VA 0x81c0d4f8; body bytes 96 */

uint FUN_81c0d4f8(void)

{
  unsigned char sg_stack[104] __attribute__((aligned(8)));
#define local_60 (*(ushort (*)[4])(sg_stack + 0))
#define acStack_58 (*(char (*)[80])(sg_stack + 8))

  uint uVar1;

  FUN_81c154d8(0x40,0x26,acStack_58);
  local_60[0] = 0x77;
  local_60[2] = 0x8f;
  local_60[1] = 0xe;
  local_60[3] = 0xb2;
  uVar1 = FUN_81c07068(local_60,0,acStack_58);
  return uVar1;
}


#undef local_60
#undef acStack_58


/* VA 0x81c0d558; body bytes 96 */

uint FUN_81c0d558(void)

{
  unsigned char sg_stack[56] __attribute__((aligned(8)));
#define acStack_28 (*(char (*)[32])(sg_stack + 8))
#define local_30 (*(ushort (*)[4])(sg_stack + 0))

  uint uVar1;

  FUN_81c154d8(0x40,0x27,acStack_28);
  local_30[0] = 0x77;
  local_30[2] = 0x8f;
  local_30[1] = 0xe;
  local_30[3] = 0x4a;
  uVar1 = FUN_81c07068(local_30,0,acStack_28);
  return uVar1;
}


#undef acStack_28
#undef local_30


/* VA 0x81c0d5b8; body bytes 96 */

uint FUN_81c0d5b8(void)

{
  unsigned char sg_stack[56] __attribute__((aligned(8)));
#define acStack_28 (*(char (*)[32])(sg_stack + 8))
#define local_30 (*(ushort (*)[4])(sg_stack + 0))

  uint uVar1;

  FUN_81c154d8(0x40,0x28,acStack_28);
  local_30[0] = 0x77;
  local_30[2] = 0x8f;
  local_30[1] = 0xe;
  local_30[3] = 0x4a;
  uVar1 = FUN_81c07068(local_30,0,acStack_28);
  return uVar1;
}


#undef acStack_28
#undef local_30


/* VA 0x81c0d618; body bytes 460 */

undefined4 FUN_81c0d618(byte param_1,undefined1 param_2)

{
  uint uVar1;
  undefined4 uVar2;

  uVar1 = (uint)param_1;
  uVar2 = 0;
  if (uVar1 < 0x26) {
    uVar2 = 1;
    switch(param_2) {
    case 1:
      FUN_81c0d7e4(param_1);
    case 0:
    case 0x14:
    case 0x15:
    case 0x16:
      uVar2 = 1;
      break;
    case 2:
      FUN_81c0da0c(param_1);
      uVar2 = 1;
      break;
    case 3:
      FUN_81c0ddf0(param_1);
      uVar2 = 1;
      break;
    case 4:
      FUN_81c0df94(param_1);
      uVar2 = 1;
      break;
    case 5:
      FUN_81c0e184(param_1);
      uVar2 = 1;
      break;
    case 6:
      FUN_81c0e38c(param_1);
      uVar2 = 1;
      break;
    case 7:
      FUN_81c0e53c(uVar1);
      uVar2 = 1;
      break;
    case 8:
      FUN_81c0e6c4(uVar1);
      uVar2 = 1;
      break;
    case 9:
      FUN_81c0e87c(uVar1);
      uVar2 = 1;
      break;
    case 10:
      FUN_81c117d0(uVar1);
      uVar2 = 1;
      break;
    case 0xb:
      FUN_81c0eb10(param_1);
      uVar2 = 1;
      break;
    case 0xc:
      FUN_81c0ed78(uVar1);
      uVar2 = 1;
      break;
    case 0xd:
      FUN_81c0ef00(uVar1);
      uVar2 = 1;
      break;
    case 0xe:
      FUN_81c0f244(param_1);
      uVar2 = 1;
      break;
    case 0xf:
      FUN_81c0f49c(param_1);
      uVar2 = 1;
      break;
    case 0x10:
      FUN_81c0f61c(param_1);
      uVar2 = 1;
      break;
    case 0x11:
      FUN_81c0f7a0(param_1);
      uVar2 = 1;
      break;
    case 0x12:
      FUN_81c10020();
      uVar2 = 1;
      break;
    case 0x13:
      FUN_81c0f934(param_1);
      uVar2 = 1;
      break;
    case 0x17:
      FUN_81c0fab8(param_1);
      uVar2 = 1;
      break;
    case 0x18:
      FUN_81c0fca4(param_1);
      uVar2 = 1;
      break;
    case 0x19:
      FUN_81c0fe88(uVar1);
      uVar2 = 1;
      break;
    case 0x1a:
      FUN_81c11a2c(param_1);
      uVar2 = 1;
      break;
    case 0x1b:
      FUN_81c10050(param_1);
      uVar2 = 1;
    }
  }
  return uVar2;
}




#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b454 (*(undefined2 *)(0x81c2b454u))
#define DAT_81c2b456 (*(undefined2 *)(0x81c2b456u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0d7e4; body bytes 552 */

undefined4 FUN_81c0d7e4(byte param_1)

{
  unsigned char sg_stack[28] __attribute__((aligned(8)));
#define local_37 (*(byte *)(sg_stack + 1))
#define local_36 (*(byte *)(sg_stack + 2))
#define local_2d (*(undefined1 *)(sg_stack + 11))
#define local_38 (*(undefined1 *)(sg_stack + 0))

  byte bVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  byte bVar7;
  uint uVar8;
  ushort *puVar9;

  iVar4 = g_scratch_buffer_4096;
  uVar3 = (uint)param_1;
  uVar5 = FUN_81c13870(uVar3,g_scratch_buffer_4096);
  bVar7 = 0x54;
  if (uVar5 != 0) {
    puVar9 = &DAT_81c2b456 + uVar3 * 0x12;
    uVar2 = (&DAT_81c2b454)[uVar3 * 0x12];
    while( true ) {
      bVar7 = 0x34;
      if ((uint)uVar2 <= (uint)*puVar9) break;
      uVar5 = FUN_81c12308(uVar3,1);
      if (uVar5 == 0) {
        bVar7 = 0x3b;
        break;
      }
      uVar5 = FUN_81c13870(uVar3,iVar4);
      if (uVar5 == 0) {
        return 1;
      }
      while( true ) {
        FUN_81c13494();
        uVar6 = FUN_81c19270(iVar4,uVar5,4,2,0xeb,0x3d);
        if (uVar6 == 0xff) {
          return 1;
        }
        bVar7 = *(byte *)(iVar4 + uVar6);
        uVar8 = (uint)bVar7;
        uVar6 = FUN_81c11b50(uVar8,1);
        if (uVar6 != 0) break;
        FUN_81c17f44(0x3c);
      }
      bVar1 = *(byte *)(uVar8 * 0x10 + DAT_81c2b164 + 4);
      uVar6 = bbk_rand();
      uVar5 = uVar6 + 3;
      if (-1 < (int)uVar6) {
        uVar5 = uVar6;
      }
      uVar6 = (bVar1 / 10) * (uVar6 + ((int)uVar5 >> 2) * -4 + 2) +
              (uint)(*(byte *)(uVar8 * 0x10 + DAT_81c2b164 + 4) >> 1);
      uVar5 = (uVar6 & 0xffff) + (uint)*puVar9;
      *puVar9 = (ushort)uVar5;
      if ((uint)uVar2 < (uVar5 & 0xffff)) {
        *puVar9 = uVar2;
      }
      FUN_81c0dc30(uVar3,bVar7,(byte)uVar6,0);
      FUN_81c11bbc(uVar8,1);
      FUN_81c12374(uVar3,1);
      local_38 = 1;
      local_2d = 0;
      local_37 = bVar7;
      local_36 = param_1;
      FUN_81c116f0(&local_38);
      FUN_81c123f0(uVar3,bVar7);
      uVar2 = (&DAT_81c2b454)[uVar3 * 0x12];
    }
  }
  FUN_81c17f44(bVar7);
  return 1;
}


#undef DAT_81c2b164
#undef DAT_81c2b454
#undef DAT_81c2b456
#undef g_scratch_buffer_4096
#undef local_37
#undef local_36
#undef local_2d
#undef local_38

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b458 (*(undefined2 *)(0x81c2b458u))
#define DAT_81c2b45a (*(undefined2 *)(0x81c2b45au))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0da0c; body bytes 548 */

undefined4 FUN_81c0da0c(byte param_1)

{
  unsigned char sg_stack[28] __attribute__((aligned(8)));
#define local_2d (*(undefined1 *)(sg_stack + 11))
#define local_38 (*(undefined1 *)(sg_stack + 0))
#define local_37 (*(byte *)(sg_stack + 1))
#define local_36 (*(byte *)(sg_stack + 2))

  byte bVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  byte bVar7;
  uint uVar8;
  ushort *puVar9;

  iVar4 = g_scratch_buffer_4096;
  uVar3 = (uint)param_1;
  uVar5 = FUN_81c13870(uVar3,g_scratch_buffer_4096);
  bVar7 = 0x54;
  if (uVar5 != 0) {
    puVar9 = &DAT_81c2b45a + uVar3 * 0x12;
    while( true ) {
      uVar2 = (&DAT_81c2b458)[uVar3 * 0x12];
      bVar7 = 0x35;
      if ((uint)uVar2 <= (uint)*puVar9) break;
      uVar5 = FUN_81c12308(uVar3,2);
      if (uVar5 == 0) {
        bVar7 = 0x3b;
        break;
      }
      uVar5 = FUN_81c13870(uVar3,iVar4);
      if (uVar5 == 0) {
        return 1;
      }
      while( true ) {
        FUN_81c13494();
        uVar6 = FUN_81c19270(iVar4,uVar5,4,2,0xeb,0x3d);
        if (uVar6 == 0xff) {
          return 1;
        }
        bVar7 = *(byte *)(iVar4 + uVar6);
        uVar8 = (uint)bVar7;
        uVar6 = FUN_81c11b50(uVar8,2);
        if (uVar6 != 0) break;
        FUN_81c17f44(0x3c);
      }
      bVar1 = *(byte *)(uVar8 * 0x10 + DAT_81c2b164 + 4);
      uVar6 = bbk_rand();
      uVar5 = uVar6 + 3;
      if (-1 < (int)uVar6) {
        uVar5 = uVar6;
      }
      uVar6 = (int)((bVar1 / 10) * (uVar6 + ((int)uVar5 >> 2) * -4 + 2) +
                   (uint)*(byte *)(uVar8 * 0x10 + DAT_81c2b164 + 4)) >> 1;
      uVar5 = (uVar6 & 0xffff) + (uint)*puVar9;
      *puVar9 = (ushort)uVar5;
      if ((uint)uVar2 < (uVar5 & 0xffff)) {
        *puVar9 = uVar2;
      }
      FUN_81c0dc30(uVar3,bVar7,(byte)uVar6,1);
      FUN_81c11bbc(uVar8,2);
      FUN_81c12374(uVar3,2);
      local_38 = 2;
      local_2d = 0;
      local_37 = bVar7;
      local_36 = param_1;
      FUN_81c116f0(&local_38);
      FUN_81c123f0(uVar3,bVar7);
    }
  }
  FUN_81c17f44(bVar7);
  return 1;
}


#undef DAT_81c2b164
#undef DAT_81c2b458
#undef DAT_81c2b45a
#undef g_scratch_buffer_4096
#undef local_2d
#undef local_38
#undef local_37
#undef local_36

#define DAT_81c2b456 (*(undefined2 *)(0x81c2b456u))
#define DAT_81c2b45a (*(undefined2 *)(0x81c2b45au))
#define DAT_81c2b45c (*(undefined1 *)(0x81c2b45cu))
#define DAT_81c2b45d (*(undefined1 *)(0x81c2b45du))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0dc30; body bytes 448 */

void FUN_81c0dc30(uint param_1,uchar param_2,byte param_3,byte param_4)

{
  char *source;
  char *destination;
  uint uVar1;

  uVar1 = param_1 & 0xff;
  source = (char *)(g_scratch_buffer_4096 + 0x15e);
  destination = (char *)(g_scratch_buffer_4096 + 300);
  if (param_4 == 1) {
    FUN_81c154d8(0x40,0x74,destination);
    uVar1 = (uint)(ushort)(&DAT_81c2b45a)[uVar1 * 0x12];
  }
  else if (param_4 < 2) {
    if (param_4 != 0) goto LAB_81c0dc94;
    FUN_81c154d8(0x40,0x71,destination);
    uVar1 = (uint)(ushort)(&DAT_81c2b456)[uVar1 * 0x12];
  }
  else if (param_4 == 2) {
    FUN_81c154d8(0x40,0x75,destination);
    uVar1 = (uint)(byte)(&DAT_81c2b45c)[uVar1 * 0x24];
  }
  else {
    if (param_4 != 3) goto LAB_81c0dc94;
    FUN_81c154d8(0x40,0x76,destination);
    uVar1 = (uint)(byte)(&DAT_81c2b45d)[uVar1 * 0x24];
  }
  FUN_81c0a7e4(uVar1,source,10);
LAB_81c0dc94:
  bbk_strcat(destination,source);
  FUN_81c154d8(0x40,0x72,source);
  bbk_strcat(destination,source);
  FUN_81c0a7e4((uint)param_3,source,10);
  bbk_strcat(destination,source);
  FUN_81c154d8(0x40,0x73,source);
  bbk_strcat(destination,source);
  FUN_81c13494();
  FUN_81c18024(param_2,destination);
  return;
}


#undef DAT_81c2b456
#undef DAT_81c2b45a
#undef DAT_81c2b45c
#undef DAT_81c2b45d
#undef g_scratch_buffer_4096

#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0ddf0; body bytes 420 */

undefined4 FUN_81c0ddf0(byte param_1)

{
  unsigned char sg_stack[28] __attribute__((aligned(8)));
#define local_28 (*(undefined1 *)(sg_stack + 0))
#define local_27 (*(byte *)(sg_stack + 1))
#define local_26 (*(byte *)(sg_stack + 2))
#define local_1d (*(undefined1 *)(sg_stack + 11))

  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  char *pcVar6;
  uint uVar7;

  iVar2 = g_scratch_buffer_4096;
  uVar1 = (uint)param_1;
  uVar3 = FUN_81c13870(uVar1,g_scratch_buffer_4096);
  bVar5 = 0x54;
  if (uVar3 != 0) {
    while (uVar3 = FUN_81c12308(uVar1,3), uVar3 != 0) {
      uVar3 = FUN_81c13870(uVar1,iVar2);
      if (uVar3 == 0) {
        return 1;
      }
      while( true ) {
        FUN_81c13494();
        uVar4 = FUN_81c19270(iVar2,uVar3,4,2,0xeb,0x3d);
        if (uVar4 == 0xff) {
          return 1;
        }
        bVar5 = *(byte *)(iVar2 + uVar4);
        uVar7 = (uint)bVar5;
        uVar4 = FUN_81c11b50(uVar7,3);
        if (uVar4 != 0) break;
        FUN_81c17f44(0x3c);
      }
      FUN_81c11bbc(uVar7,3);
      FUN_81c12374(uVar1,3);
      uVar3 = bbk_rand();
      uVar4 = (int)uVar3 % 3 & 0xff;
      uVar3 = uVar4 - 0x6f;
      if (DAT_81c2b115 != uVar7) {
        uVar3 = uVar4 - 0x72;
      }
      pcVar6 = (char *)(g_scratch_buffer_4096 + 300);
      FUN_81c154d8(0x40,uVar3 & 0xff,pcVar6);
      FUN_81c18024(bVar5,pcVar6);
      local_28 = 3;
      local_1d = 0;
      local_27 = bVar5;
      local_26 = param_1;
      FUN_81c116f0(&local_28);
      FUN_81c123f0(uVar1,bVar5);
    }
    bVar5 = 0x3b;
  }
  FUN_81c17f44(bVar5);
  return 1;
}


#undef DAT_81c2b115
#undef g_scratch_buffer_4096
#undef local_28
#undef local_27
#undef local_26
#undef local_1d

#define DAT_81c2b450 (*(undefined1 *)(0x81c2b450u))
#define DAT_81c2b45d (*(undefined1 *)(0x81c2b45du))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0df94; body bytes 496 */

undefined4 FUN_81c0df94(byte param_1)

{
  unsigned char sg_stack[28] __attribute__((aligned(8)));
#define local_28 (*(undefined1 *)(sg_stack + 0))
#define local_27 (*(byte *)(sg_stack + 1))
#define local_26 (*(byte *)(sg_stack + 2))
#define local_1d (*(undefined1 *)(sg_stack + 11))

  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  int iVar6;

  iVar2 = g_scratch_buffer_4096;
  uVar1 = (uint)param_1;
  uVar3 = FUN_81c13870(uVar1,g_scratch_buffer_4096);
  bVar5 = 0x54;
  if (uVar3 != 0) {
    while (uVar3 = FUN_81c12308(uVar1,4), uVar3 != 0) {
      iVar6 = uVar1 * 0x24;
      if (((&DAT_81c2b450)[iVar6] == '\0') && (99 < (byte)(&DAT_81c2b45d)[iVar6])) {
        bVar5 = 0x3d;
        goto LAB_81c0e16c;
      }
      uVar3 = FUN_81c13870(uVar1,iVar2);
      if (uVar3 == 0) {
        return 1;
      }
      while( true ) {
        FUN_81c13494();
        uVar4 = FUN_81c19270(iVar2,uVar3,4,2,0xeb,0x3d);
        if (uVar4 == 0xff) {
          return 1;
        }
        bVar5 = *(byte *)(iVar2 + uVar4);
        uVar4 = FUN_81c11b50((uint)bVar5,4);
        if (uVar4 != 0) break;
        FUN_81c17f44(0x3c);
      }
      FUN_81c11bbc((uint)bVar5,4);
      FUN_81c12374(uVar1,4);
      uVar4 = bbk_rand();
      uVar3 = uVar4 + 3;
      if (-1 < (int)uVar4) {
        uVar3 = uVar4;
      }
      uVar3 = uVar4 + ((int)uVar3 >> 2) * -4 + 1;
      uVar4 = (uVar3 & 0xff) + (uint)(byte)(&DAT_81c2b45d)[iVar6];
      (&DAT_81c2b450)[iVar6] = 0;
      (&DAT_81c2b45d)[iVar6] = (char)uVar4;
      if (100 < (uVar4 & 0xff)) {
        (&DAT_81c2b45d)[iVar6] = 100;
      }
      FUN_81c0dc30(uVar1,bVar5,(byte)uVar3,3);
      local_28 = 4;
      local_1d = 0;
      local_27 = bVar5;
      local_26 = param_1;
      FUN_81c116f0(&local_28);
      FUN_81c123f0(uVar1,bVar5);
    }
    bVar5 = 0x3b;
  }
LAB_81c0e16c:
  FUN_81c17f44(bVar5);
  return 1;
}


#undef DAT_81c2b450
#undef DAT_81c2b45d
#undef g_scratch_buffer_4096
#undef local_28
#undef local_27
#undef local_26
#undef local_1d

#define DAT_81c2b45c (*(undefined1 *)(0x81c2b45cu))
#define DAT_81c2b460 (*(undefined4 *)(0x81c2b460u))
#define DAT_81c2b464 (*(undefined4 *)(0x81c2b464u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0e184; body bytes 520 */

undefined4 FUN_81c0e184(byte param_1)

{
  unsigned char sg_stack[28] __attribute__((aligned(8)));
#define local_30 (*(undefined1 *)(sg_stack + 0))
#define local_2f (*(byte *)(sg_stack + 1))
#define local_2e (*(byte *)(sg_stack + 2))
#define local_25 (*(undefined1 *)(sg_stack + 11))

  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  byte bVar6;
  uint uVar7;
  byte *pbVar8;

  iVar2 = g_scratch_buffer_4096;
  uVar1 = (uint)param_1;
  uVar3 = FUN_81c13870(uVar1,g_scratch_buffer_4096);
  bVar6 = 0x54;
  if (uVar3 != 0) {
    while (uVar3 = FUN_81c12308(uVar1,5), uVar3 != 0) {
      uVar3 = FUN_81c13870(uVar1,iVar2);
      if (uVar3 == 0) {
        return 1;
      }
      while( true ) {
        FUN_81c13494();
        uVar4 = FUN_81c19270(iVar2,uVar3,4,2,0xeb,0x3d);
        if (uVar4 == 0xff) {
          return 1;
        }
        bVar6 = *(byte *)(iVar2 + uVar4);
        uVar4 = FUN_81c11b50((uint)bVar6,5);
        if (uVar4 != 0) break;
        FUN_81c17f44(0x3c);
      }
      FUN_81c11bbc((uint)bVar6,5);
      FUN_81c12374(uVar1,5);
      uVar4 = bbk_rand();
      uVar3 = uVar4 + 3;
      if (-1 < (int)uVar4) {
        uVar3 = uVar4;
      }
      pbVar8 = &DAT_81c2b45c + uVar1 * 0x24;
      uVar7 = (uint)*pbVar8;
      uVar3 = uVar4 + ((int)uVar3 >> 2) * -4 + 1 & 0xff;
      if (100 < uVar7 + uVar3) {
        uVar3 = 100 - uVar7 & 0xff;
      }
      *pbVar8 = (byte)(uVar3 + uVar7);
      if (100 < (uVar3 + uVar7 & 0xff)) {
        *pbVar8 = 100;
      }
      puVar5 = &DAT_81c2b464 + uVar1 * 9;
      uVar4 = *puVar5;
      *puVar5 = uVar4 + 100;
      if ((uint)(&DAT_81c2b460)[uVar1 * 9] < uVar4 + 100) {
        *puVar5 = (&DAT_81c2b460)[uVar1 * 9];
      }
      FUN_81c0dc30(uVar1,bVar6,(byte)uVar3,2);
      local_30 = 5;
      local_25 = 0;
      local_2f = bVar6;
      local_2e = param_1;
      FUN_81c116f0(&local_30);
      FUN_81c123f0(uVar1,bVar6);
    }
    bVar6 = 0x3b;
  }
  FUN_81c17f44(bVar6);
  return 1;
}


#undef DAT_81c2b45c
#undef DAT_81c2b460
#undef DAT_81c2b464
#undef g_scratch_buffer_4096
#undef local_30
#undef local_2f
#undef local_2e
#undef local_25

#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0e38c; body bytes 432 */

undefined4 FUN_81c0e38c(byte param_1)

{
  unsigned char sg_stack[28] __attribute__((aligned(8)));
#define local_38 (*(undefined1 *)(sg_stack + 0))
#define local_37 (*(byte *)(sg_stack + 1))
#define local_36 (*(byte *)(sg_stack + 2))
#define local_35 (*(char *)(sg_stack + 3))
#define local_2d (*(undefined1 *)(sg_stack + 11))

  char cVar1;
  uint uVar2;
  char *pcVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  byte bVar7;

  pcVar3 = g_scratch_buffer_4096;
  uVar2 = (uint)param_1;
  uVar5 = FUN_81c13870(uVar2,(int)g_scratch_buffer_4096);
  bVar7 = 0x54;
  if (uVar5 != 0) {
LAB_81c0e3e4:
    uVar5 = FUN_81c139a8(uVar2,(int)pcVar3);
    if (uVar5 != 0) {
      FUN_81c13494();
      uVar5 = FUN_81c19270((int)pcVar3,uVar5,4,2,0xeb,0x3d);
      if (uVar5 == 0xff) {
        return 1;
      }
      cVar1 = pcVar3[uVar5];
      uVar5 = FUN_81c13870(uVar2,(int)pcVar3);
      if (uVar5 == 0) {
        return 1;
      }
      while( true ) {
        FUN_81c13494();
        uVar6 = FUN_81c19270((int)pcVar3,uVar5,4,2,0xeb,0x3d);
        if (uVar6 == 0xff) break;
        bVar7 = pcVar3[uVar6];
        uVar6 = FUN_81c11b50((uint)bVar7,6);
        if (uVar6 != 0) {
          FUN_81c11bbc((uint)bVar7,6);
          local_38 = 6;
          local_2d = 0;
          local_37 = bVar7;
          local_36 = param_1;
          local_35 = cVar1;
          FUN_81c116f0(&local_38);
          FUN_81c123f0(uVar2,bVar7);
          pcVar4 = g_scratch_buffer_4096;
          FUN_81c154d8(0x40,0xa2,g_scratch_buffer_4096);
          FUN_81c13494();
          FUN_81c18024(bVar7,pcVar4);
          break;
        }
        FUN_81c17f44(0x3c);
      }
      goto LAB_81c0e3e4;
    }
    bVar7 = 0x58;
  }
  FUN_81c17f44(bVar7);
  return 1;
}


#undef g_scratch_buffer_4096
#undef local_38
#undef local_37
#undef local_36
#undef local_35
#undef local_2d

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0e53c; body bytes 392 */

undefined4 FUN_81c0e53c(uint param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  byte *pbVar5;
  uint uVar6;

  iVar3 = g_scratch_buffer_4096;
  uVar6 = param_1 & 0xff;
  uVar2 = FUN_81c139a8(uVar6,g_scratch_buffer_4096);
  if (uVar2 == 0) {
    FUN_81c17f44(0x58);
  }
  uVar2 = FUN_81c19270(iVar3,uVar2,4,2,0xeb,0x3d);
  pbVar5 = (byte *)(iVar3 + uVar2);
  if (uVar2 != 0xff) {
    iVar3 = DAT_81c2b164 + (uint)*pbVar5 * 0x10;
    if (*(char *)(iVar3 + 0xc) == '\0') {
      cVar1 = *(char *)(iVar3 + 0xd);
    }
    else {
      FUN_81c135a8(uVar6,*(char *)(iVar3 + 0xc) - 1);
      FUN_81c18150(*(char *)(iVar3 + 0xc) - 1);
      cVar1 = *(char *)(iVar3 + 0xd);
    }
    if (cVar1 != '\0') {
      FUN_81c135a8(uVar6,cVar1 - 1);
      FUN_81c18150(*(char *)(iVar3 + 0xd) - 1);
    }
    pcVar4 = (char *)(g_scratch_buffer_4096 + 300);
    uVar2 = bbk_rand();
    FUN_81c154d8(0x40,(int)uVar2 % 3 + 0x7dU & 0xff,pcVar4);
    FUN_81c13494();
    FUN_81c18024(*pbVar5,pcVar4);
    FUN_81c123f0(uVar6,*pbVar5);
  }
  return 1;
}


#undef DAT_81c2b164
#undef g_scratch_buffer_4096

#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c204d0 (*(undefined *)(0x81c204d0u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0e6c4; body bytes 440 */

undefined4 FUN_81c0e6c4(uint param_1)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;

  iVar3 = g_scratch_buffer_4096;
  uVar6 = param_1 & 0xff;
  uVar4 = FUN_81c13870(uVar6,g_scratch_buffer_4096);
  uVar5 = FUN_81c139a8(uVar6,iVar3 + uVar4);
  uVar4 = uVar4 + uVar5 & 0xff;
  if (uVar4 == 0) {
    FUN_81c17f44(0x54);
  }
  else {
    uVar4 = FUN_81c19270(iVar3,uVar4,4,2,0xeb,0x3d);
    if (uVar4 != 0xff) {
      bVar1 = *(byte *)(iVar3 + uVar4);
      iVar7 = (uint)bVar1 * 0x10;
      if ((uint)DAT_81c2b115 != (uint)bVar1) {
        *(undefined1 *)(iVar7 + DAT_81c2b164 + 1) = 0;
        uVar4 = bbk_rand();
        uVar4 = (int)uVar4 % 0x26 & 0xff;
        if (((((char *)(iVar7 + DAT_81c2b164))[1] == -1) &&
            (cVar2 = *(char *)(iVar7 + DAT_81c2b164), cVar2 != '\0')) &&
           (uVar5 = FUN_81c13794((uint)(byte)(cVar2 - 1),iVar3), uVar5 != 0)) {
          ((undefined1 *)(iVar7 + DAT_81c2b164))[1] = *(undefined1 *)(iVar7 + DAT_81c2b164);
          uVar4 = bbk_rand();
          if (uVar5 == 0) {
            trap(7);
          }
          uVar4 = (int)uVar4 % (int)uVar5 & 0xff;
        }
        FUN_81c123f0(uVar6,bVar1);
        FUN_81c134b8(uVar4,bVar1);
        return 1;
      }
      FUN_81c14dd8(&DAT_81c204d0,2);
      return 0;
    }
  }
  return 1;
}


#undef DAT_81c2b115
#undef DAT_81c2b164
#undef DAT_81c204d0
#undef g_scratch_buffer_4096

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c204e0 (*(undefined *)(0x81c204e0u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0e87c; body bytes 652 */

undefined4 FUN_81c0e87c(uint param_1)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  byte bVar6;
  byte bVar7;
  char *pcVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;

  uVar10 = param_1 & 0xff;
  iVar9 = g_scratch_buffer_4096 + 200;
  uVar2 = FUN_81c181b8(uVar10,iVar9);
  bVar6 = 0x56;
  if (uVar2 != 0) {
    uVar2 = FUN_81c18874(iVar9,uVar2,4,2,0xeb,0x3d);
    if (uVar2 == 0xff) {
      return 1;
    }
    while( true ) {
      iVar4 = g_scratch_buffer_4096;
      iVar12 = 0;
      uVar3 = FUN_81c13870(uVar10,g_scratch_buffer_4096);
      if (uVar3 == 0) break;
      uVar3 = FUN_81c19270(iVar4,uVar3,4,2,0xeb,0x3d);
      if (uVar3 == 0xff) {
        return 1;
      }
      bVar6 = *(byte *)(iVar4 + uVar3);
      uVar3 = (uint)bVar6;
      bVar1 = *(byte *)(iVar9 + uVar2);
      iVar11 = uVar3 * 0x10;
      iVar4 = DAT_81c2b164 + iVar11;
      if ((*(char *)(iVar4 + 0xc) == '\0') || (iVar12 = 1, *(char *)(iVar4 + 0xd) == '\0')) {
        uVar5 = FUN_81c17a08((uint)bVar1,uVar3);
        bVar7 = 0x6d;
        if (uVar5 == 1) {
LAB_81c0e9b4:
          FUN_81c12504(uVar10,bVar1);
          if (DAT_81c2b115 == uVar3) {
            FUN_81c13494();
            FUN_81c18024(bVar6,&DAT_81c204e0);
            return 1;
          }
          pcVar8 = (char *)(g_scratch_buffer_4096 + 300);
          uVar2 = bbk_rand();
          FUN_81c154d8(0x40,(int)uVar2 % 3 - 0x7dU & 0xff,pcVar8);
          FUN_81c13494();
          FUN_81c18024(bVar6,pcVar8);
          *(char *)(iVar11 + DAT_81c2b164 + 5) = *(char *)(iVar11 + DAT_81c2b164 + 5) + '\b';
          if (*(byte *)(iVar11 + DAT_81c2b164 + 5) < 0x65) {
            return 1;
          }
          *(undefined1 *)(iVar11 + DAT_81c2b164 + 5) = 100;
          return 1;
        }
        if ((int)uVar5 < 2) {
          if (uVar5 == 0) {
            *(byte *)(iVar4 + 0xc + iVar12) = bVar1 + 1;
          }
          goto LAB_81c0e9b4;
        }
        if (uVar5 != 0xff) goto LAB_81c0e9b4;
      }
      else {
        bVar7 = 0x57;
      }
      FUN_81c17f44(bVar7);
      FUN_81c13494();
    }
    bVar6 = 0x54;
  }
  FUN_81c17f44(bVar6);
  return 1;
}


#undef DAT_81c2b164
#undef DAT_81c2b115
#undef DAT_81c204e0
#undef g_scratch_buffer_4096

#define DAT_81c20510 (*(undefined *)(0x81c20510u))
#define DAT_81c2b468 (*(undefined2 *)(0x81c2b468u))
#define DAT_81c2b46a (*(undefined2 *)(0x81c2b46au))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0eb10; body bytes 616 */

undefined4 FUN_81c0eb10(byte param_1)

{
  unsigned char sg_stack[56] __attribute__((aligned(8)));
#define local_3e (*(byte *)(sg_stack + 18))
#define local_35 (*(undefined1 *)(sg_stack + 27))
#define acStack_50 (*(char (*)[16])(sg_stack + 0))
#define local_30 (*(ushort (*)[4])(sg_stack + 32))
#define local_40 (*(undefined1 *)(sg_stack + 16))
#define local_3f (*(byte *)(sg_stack + 17))

  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;

  iVar2 = g_scratch_buffer_4096;
  uVar1 = (uint)param_1;
  do {
    while( true ) {
      uVar3 = FUN_81c13870(uVar1,iVar2);
      bVar5 = 0x54;
      if (uVar3 == 0) goto LAB_81c0ed68;
      FUN_81c13494();
      uVar3 = FUN_81c19270(iVar2,uVar3,4,2,0xeb,0x3d);
      if (uVar3 == 0xff) {
        return 1;
      }
      bVar5 = *(byte *)(iVar2 + uVar3);
      uVar3 = FUN_81c11b50((uint)bVar5,0xb);
      if (uVar3 != 0) break;
      FUN_81c17f44(0x3c);
    }
    FUN_81c154d8(0x40,0x2e,acStack_50);
    local_30[0] = 0x77;
    local_30[2] = 0x8f;
    local_30[1] = 0xe;
    local_30[3] = 0x26;
    uVar3 = FUN_81c07068(local_30,0,acStack_50);
  } while (uVar3 == 0xff);
  if (uVar3 == 0) {
    uVar3 = FUN_81c12308(uVar1,0xc);
    if (uVar3 == 0) {
      bVar5 = 0x3b;
LAB_81c0ed68:
      FUN_81c17f44(bVar5);
      return 1;
    }
    if (((ushort)(&DAT_81c2b468)[uVar1 * 0x12] / 5 != 0) &&
       (uVar3 = FUN_81c13b9c(1,(ushort)(&DAT_81c2b468)[uVar1 * 0x12] / 5), uVar3 != 0xffff)) {
      (&DAT_81c2b468)[uVar1 * 0x12] = (&DAT_81c2b468)[uVar1 * 0x12] + (short)uVar3 * -5;
      (&DAT_81c2b46a)[uVar1 * 0x12] = (short)uVar3 + (&DAT_81c2b46a)[uVar1 * 0x12];
    }
  }
  else if (uVar3 == 1) {
    if ((ushort)(&DAT_81c2b46a)[uVar1 * 0x12] == 0) {
      FUN_81c14dd8(&DAT_81c20510,2);
      return 1;
    }
    uVar3 = FUN_81c13b9c(1,(uint)(ushort)(&DAT_81c2b46a)[uVar1 * 0x12]);
    if (uVar3 != 0xffff) {
      uVar4 = (uVar3 & 0x7fff) * 2 + (uint)(ushort)(&DAT_81c2b468)[uVar1 * 0x12];
      (&DAT_81c2b46a)[uVar1 * 0x12] = (&DAT_81c2b46a)[uVar1 * 0x12] - (short)uVar3;
      (&DAT_81c2b468)[uVar1 * 0x12] = (short)uVar4;
      if (30000 < (uVar4 & 0xffff)) {
        (&DAT_81c2b468)[uVar1 * 0x12] = 30000;
      }
    }
  }
  FUN_81c11bbc((uint)bVar5,0xb);
  local_40 = 0xb;
  local_35 = 0;
  local_3f = bVar5;
  local_3e = param_1;
  FUN_81c116f0(&local_40);
  FUN_81c123f0(uVar1,bVar5);
  return 1;
}


#undef DAT_81c20510
#undef DAT_81c2b468
#undef DAT_81c2b46a
#undef g_scratch_buffer_4096
#undef local_3e
#undef local_35
#undef acStack_50
#undef local_30
#undef local_40
#undef local_3f

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c2051c (*(undefined *)(0x81c2051cu))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0ed78; body bytes 392 */

undefined4 FUN_81c0ed78(uint param_1)

{
  char *pcVar1;
  char *pcVar2;
  uint uVar3;
  byte bVar4;
  byte bVar5;
  int iVar6;
  uint uVar7;

  pcVar1 = g_scratch_buffer_4096;
  uVar7 = param_1 & 0xff;
  uVar3 = FUN_81c13870(uVar7,(int)g_scratch_buffer_4096);
  bVar5 = 0x54;
  if (uVar3 != 0) {
    while (uVar3 = FUN_81c12308(uVar7,0xc), uVar3 != 0) {
      FUN_81c13494();
      uVar3 = FUN_81c13870(uVar7,(int)pcVar1);
      if (uVar3 == 0) {
        return 1;
      }
      uVar3 = FUN_81c19270((int)pcVar1,uVar3,4,2,0xeb,0x3d);
      if (uVar3 == 0xff) {
        return 1;
      }
      bVar5 = pcVar1[uVar3];
      iVar6 = DAT_81c2b164 + (uint)bVar5 * 0x10;
      FUN_81c12374(uVar7,0xc);
      bVar4 = *(char *)(iVar6 + 8) + 0x32;
      *(byte *)(iVar6 + 8) = bVar4;
      if (100 < bVar4) {
        *(undefined1 *)(iVar6 + 8) = 100;
      }
      pcVar2 = g_scratch_buffer_4096;
      if ((uint)DAT_81c2b115 == (uint)bVar5) {
        FUN_81c13494();
        FUN_81c18024(bVar5,&DAT_81c2051c);
      }
      else {
        FUN_81c154d8(0x40,0xa1,g_scratch_buffer_4096);
        FUN_81c13494();
        FUN_81c18024(bVar5,pcVar2);
        if (*(byte *)(iVar6 + 5) < 100) {
          *(byte *)(iVar6 + 5) = *(byte *)(iVar6 + 5) + 1;
        }
      }
    }
    bVar5 = 0x3b;
  }
  FUN_81c17f44(bVar5);
  return 1;
}


#undef DAT_81c2b164
#undef DAT_81c2b115
#undef DAT_81c2051c
#undef g_scratch_buffer_4096

#define DAT_81c2b192 (*(byte *)(0x81c2b192u))
#define DAT_81c2b193 (*(byte *)(0x81c2b193u))
#define DAT_81c2b190 (*(undefined1 *)(0x81c2b190u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define DAT_81c2b468 (*(undefined2 *)(0x81c2b468u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
#define DAT_81c2b46a (*(undefined2 *)(0x81c2b46au))
#define DAT_81c2b46c (*(undefined2 *)(0x81c2b46cu))
/* VA 0x81c0ef00; body bytes 836 */

undefined4 FUN_81c0ef00(uint param_1)

{
  unsigned char sg_stack[52] __attribute__((aligned(8)));
#define local_40 (*(uint *)(sg_stack + 16))
#define local_3c (*(int *)(sg_stack + 20))
#define local_38 (*(int *)(sg_stack + 24))
#define local_34 (*(int *)(sg_stack + 28))
#define local_30 (*(int *)(sg_stack + 32))
#define local_50 (*(undefined1 *)(sg_stack + 0))
#define local_4f (*(byte *)(sg_stack + 1))
#define local_4e (*(undefined1 *)(sg_stack + 2))
#define local_4d (*(char *)(sg_stack + 3))
#define local_4c (*(short *)(sg_stack + 4))
#define local_4a (*(short *)(sg_stack + 6))
#define local_48 (*(short *)(sg_stack + 8))
#define local_45 (*(undefined1 *)(sg_stack + 11))

  byte bVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  byte bVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  uint unaff_s6;

  uVar7 = param_1 & 0xff;
  local_38 = uVar7 * 9;
  local_34 = uVar7 * 0x24;
  local_3c = g_scratch_buffer_4096;
  iVar8 = 0;
  local_40 = uVar7;
LAB_81c0ef6c:
  do {
    if (iVar8 == 0) goto LAB_81c0f1b8;
    while( true ) {
      while( true ) {
        while( true ) {
          while (bVar2 = DAT_81c2b193, bVar1 = DAT_81c2b192, iVar8 == 1) {
            iVar8 = 2;
            uVar3 = FUN_81c13b9c(0,(uint)(ushort)(&DAT_81c2b46a)[uVar7 * 0x12]);
            local_4a = (short)uVar3;
            if (uVar3 == 0xffff) {
LAB_81c0f1b8:
              while( true ) {
                uVar3 = FUN_81c13870(local_40,local_3c);
                if (uVar3 == 0) {
                  FUN_81c17f44(0x54);
                  return 1;
                }
                FUN_81c13494();
                uVar3 = FUN_81c19270(local_3c,uVar3,4,2,0xeb,0x3d);
                if (uVar3 == 0xff) {
                  return 1;
                }
                iVar8 = 1;
                unaff_s6 = (uint)*(byte *)(local_3c + uVar3);
                uVar3 = FUN_81c11b50(unaff_s6,0xd);
                if (uVar3 != 0) break;
                FUN_81c17f44(0x3c);
              }
            }
          }
          if (iVar8 != 2) break;
          iVar8 = 1;
          uVar3 = FUN_81c13c3c(0,(uint)*(ushort *)((int)&DAT_81c2b468 + local_34));
          if (uVar3 != 0xffff) {
            iVar8 = 3;
          }
          local_48 = (short)uVar3;
        }
        if (iVar8 != 3) break;
        iVar8 = 2;
        uVar3 = FUN_81c13cdc(0,(uint)(ushort)(&DAT_81c2b46c)[uVar7 * 0x12]);
        if (uVar3 != 0xffff) {
          iVar8 = 4;
        }
        local_4c = (short)uVar3;
      }
      if (iVar8 != 4) goto LAB_81c0ef6c;
      pcVar9 = (char *)(g_scratch_buffer_4096 + 300);
      FUN_81c154d8(0x40,0x5d,pcVar9);
      FUN_81c13494();
      bVar5 = (byte)unaff_s6;
      FUN_81c18024(bVar5,pcVar9);
      uVar3 = FUN_81c12b18(&DAT_81c2b190);
      if (uVar3 != 0xff) break;
      iVar8 = 3;
    }
    if (uVar3 != local_40) {
      bVar6 = 0x38;
      if ((&DAT_81c2b451)[uVar3 * 0x24] != '\0') {
        local_30 = local_38 * 4;
        bVar6 = 0x36;
        if ((&DAT_81c2b451)[uVar3 * 0x24] == (&DAT_81c2b451)[local_30]) {
          uVar4 = FUN_81c1261c(local_40,bVar1,bVar2,(char)uVar3,DAT_81c2b192,DAT_81c2b193);
          bVar6 = 0x37;
          if (uVar4 != 0xff) {
            FUN_81c11bbc(unaff_s6,0xd);
            *(short *)((int)&DAT_81c2b46a + local_30) =
                 *(short *)((int)&DAT_81c2b46a + local_30) - local_4a;
            *(short *)((int)&DAT_81c2b46c + local_30) =
                 *(short *)((int)&DAT_81c2b46c + local_30) - local_4c;
            *(short *)((int)&DAT_81c2b468 + local_30) =
                 *(short *)((int)&DAT_81c2b468 + local_30) - local_48;
            FUN_81c154d8(0x40,0x98,pcVar9);
            FUN_81c18024(bVar5,pcVar9);
            local_50 = 0xd;
            local_45 = (undefined1)uVar4;
            local_4e = (undefined1)local_40;
            local_4f = bVar5;
            local_4d = (char)uVar3;
            FUN_81c116f0(&local_50);
            FUN_81c123f0(local_40,bVar5);
            return 1;
          }
        }
      }
      FUN_81c17f44(bVar6);
    }
  } while( true );
}


#undef DAT_81c2b192
#undef DAT_81c2b193
#undef DAT_81c2b190
#undef DAT_81c2b451
#undef DAT_81c2b468
#undef g_scratch_buffer_4096
#undef DAT_81c2b46a
#undef DAT_81c2b46c
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_50
#undef local_4f
#undef local_4e
#undef local_4d
#undef local_4c
#undef local_4a
#undef local_48
#undef local_45

#define DAT_81c2b192 (*(byte *)(0x81c2b192u))
#define DAT_81c2b193 (*(byte *)(0x81c2b193u))
#define DAT_81c2b190 (*(undefined1 *)(0x81c2b190u))
#define DAT_81c2b450 (*(undefined1 *)(0x81c2b450u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0f244; body bytes 600 */

undefined4 FUN_81c0f244(byte param_1)

{
  unsigned char sg_stack[36] __attribute__((aligned(8)));
#define local_40 (*(undefined1 *)(sg_stack + 0))
#define local_3f (*(byte *)(sg_stack + 1))
#define local_3e (*(byte *)(sg_stack + 2))
#define local_3d (*(char *)(sg_stack + 3))
#define local_35 (*(undefined1 *)(sg_stack + 11))
#define local_30 (*(undefined1 * *)(sg_stack + 16))

  uint uVar1;
  bool bVar2;
  int iVar3;
  byte bVar4;
  byte bVar5;
  uint uVar6;
  uint uVar7;
  byte bVar8;
  byte bVar9;
  uint unaff_s4;
  char *pcVar10;

  iVar3 = g_scratch_buffer_4096;
  uVar1 = (uint)param_1;
  local_30 = &DAT_81c2b450 + uVar1 * 0x24;
  bVar2 = false;
  do {
    if (!bVar2) goto LAB_81c0f41c;
    while (bVar5 = DAT_81c2b193, bVar4 = DAT_81c2b192, bVar2) {
      pcVar10 = (char *)(g_scratch_buffer_4096 + 300);
      FUN_81c154d8(0x40,0x5d,pcVar10);
      FUN_81c13494();
      bVar8 = (byte)unaff_s4;
      FUN_81c18024(bVar8,pcVar10);
      uVar6 = FUN_81c12b18(&DAT_81c2b190);
      if (uVar6 != 0xff) {
        if (uVar6 != uVar1) {
          if ((&DAT_81c2b451)[uVar6 * 0x24] == '\0') {
            FUN_81c17f44(0x38);
LAB_81c0f348:
            uVar7 = FUN_81c1261c(uVar1,bVar4,bVar5,(char)uVar6,DAT_81c2b192,DAT_81c2b193);
            bVar9 = 0x37;
            if (uVar7 != 0xff) {
              FUN_81c11bbc(unaff_s4,0xd);
              FUN_81c154d8(0x40,0x98,pcVar10);
              FUN_81c18024(bVar8,pcVar10);
              local_40 = 0xe;
              local_35 = (undefined1)uVar7;
              local_3f = bVar8;
              local_3e = param_1;
              local_3d = (char)uVar6;
              FUN_81c116f0(&local_40);
              FUN_81c123f0(uVar1,bVar8);
              return 1;
            }
          }
          else {
            bVar9 = 0x36;
            if ((&DAT_81c2b451)[uVar6 * 0x24] == local_30[1]) goto LAB_81c0f348;
          }
          FUN_81c17f44(bVar9);
        }
        break;
      }
LAB_81c0f41c:
      while( true ) {
        uVar6 = FUN_81c13870(uVar1,iVar3);
        if (uVar6 == 0) {
          FUN_81c17f44(0x54);
          return 1;
        }
        FUN_81c13494();
        uVar6 = FUN_81c19270(iVar3,uVar6,4,2,0xeb,0x3d);
        if (uVar6 == 0xff) {
          return 1;
        }
        unaff_s4 = (uint)*(byte *)(iVar3 + uVar6);
        bVar2 = true;
        uVar6 = FUN_81c11b50(unaff_s4,0xe);
        if (uVar6 != 0) break;
        FUN_81c17f44(0x3c);
      }
    }
  } while( true );
}


#undef DAT_81c2b192
#undef DAT_81c2b193
#undef DAT_81c2b190
#undef DAT_81c2b450
#undef DAT_81c2b451
#undef g_scratch_buffer_4096
#undef local_40
#undef local_3f
#undef local_3e
#undef local_3d
#undef local_35
#undef local_30

#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0f49c; body bytes 384 */

undefined4 FUN_81c0f49c(byte param_1)

{
  unsigned char sg_stack[28] __attribute__((aligned(8)));
#define local_25 (*(undefined1 *)(sg_stack + 11))
#define local_30 (*(undefined1 *)(sg_stack + 0))
#define local_2f (*(byte *)(sg_stack + 1))
#define local_2e (*(byte *)(sg_stack + 2))
#define local_2d (*(byte *)(sg_stack + 3))

  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;

  uVar1 = (uint)param_1;
  uVar3 = FUN_81c12308(uVar1,0xf);
  iVar2 = g_scratch_buffer_4096;
  bVar5 = 0x3b;
  if (uVar3 == 0) {
LAB_81c0f60c:
    FUN_81c17f44(bVar5);
  }
  else {
    do {
      while( true ) {
        uVar3 = FUN_81c13870(uVar1,iVar2);
        if (uVar3 == 0) {
          bVar5 = 0x54;
          goto LAB_81c0f60c;
        }
        FUN_81c13494();
        uVar3 = FUN_81c19270(iVar2,uVar3,4,2,0xeb,0x3d);
        if (uVar3 == 0xff) {
          return 1;
        }
        uVar4 = FUN_81c11b50((uint)*(byte *)(iVar2 + uVar3),0xf);
        if (uVar4 != 0) break;
        FUN_81c17f44(0x3c);
      }
      bVar5 = *(byte *)(iVar2 + uVar3);
      uVar3 = FUN_81c1297c((uint)DAT_81c2b115,iVar2);
      FUN_81c13494();
      uVar3 = FUN_81c19270(iVar2,uVar3,4,2,0xeb,0x3d);
    } while (uVar3 == 0xff);
    FUN_81c11bbc((uint)*(byte *)(iVar2 + uVar3),0xf);
    FUN_81c12374(uVar1,0xf);
    local_30 = 0xf;
    local_2d = *(byte *)(iVar2 + uVar3);
    local_25 = 10;
    local_2f = bVar5;
    local_2e = param_1;
    FUN_81c116f0(&local_30);
    FUN_81c123f0(uVar1,bVar5);
  }
  return 1;
}


#undef DAT_81c2b115
#undef g_scratch_buffer_4096
#undef local_25
#undef local_30
#undef local_2f
#undef local_2e
#undef local_2d

#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0f61c; body bytes 388 */

undefined4 FUN_81c0f61c(byte param_1)

{
  unsigned char sg_stack[28] __attribute__((aligned(8)));
#define local_30 (*(undefined1 *)(sg_stack + 0))
#define local_2f (*(byte *)(sg_stack + 1))
#define local_2e (*(byte *)(sg_stack + 2))
#define local_2d (*(undefined1 *)(sg_stack + 3))
#define local_25 (*(undefined1 *)(sg_stack + 11))

  uint uVar1;
  int iVar2;
  uint uVar3;
  byte bVar4;

  uVar1 = (uint)param_1;
  uVar3 = FUN_81c12308(uVar1,0x10);
  iVar2 = g_scratch_buffer_4096;
  bVar4 = 0x3b;
  if (uVar3 == 0) {
LAB_81c0f790:
    FUN_81c17f44(bVar4);
  }
  else {
    do {
      while( true ) {
        uVar3 = FUN_81c13870(uVar1,iVar2);
        if (uVar3 == 0) {
          bVar4 = 0x54;
          goto LAB_81c0f790;
        }
        FUN_81c13494();
        uVar3 = FUN_81c19270(iVar2,uVar3,4,2,0xeb,0x3d);
        if (uVar3 == 0xff) {
          return 1;
        }
        bVar4 = *(byte *)(iVar2 + uVar3);
        uVar3 = FUN_81c11b50((uint)bVar4,0x10);
        if (uVar3 != 0) break;
        FUN_81c17f44(0x3c);
      }
      uVar3 = FUN_81c1297c((uint)DAT_81c2b115,iVar2);
      FUN_81c13494();
      uVar3 = FUN_81c19270(iVar2,uVar3,4,2,0xeb,0x3d);
    } while (uVar3 == 0xff);
    FUN_81c11bbc((uint)bVar4,0x10);
    FUN_81c12374(uVar1,0x10);
    local_30 = 0x10;
    local_2d = *(undefined1 *)(iVar2 + uVar3);
    local_25 = 10;
    local_2f = bVar4;
    local_2e = param_1;
    FUN_81c116f0(&local_30);
    FUN_81c123f0(uVar1,bVar4);
  }
  return 1;
}


#undef DAT_81c2b115
#undef g_scratch_buffer_4096
#undef local_30
#undef local_2f
#undef local_2e
#undef local_2d
#undef local_25

#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0f7a0; body bytes 404 */

undefined4 FUN_81c0f7a0(byte param_1)

{
  unsigned char sg_stack[28] __attribute__((aligned(8)));
#define local_30 (*(undefined1 *)(sg_stack + 0))
#define local_2f (*(byte *)(sg_stack + 1))
#define local_2e (*(byte *)(sg_stack + 2))
#define local_2d (*(undefined1 *)(sg_stack + 3))
#define local_25 (*(undefined1 *)(sg_stack + 11))

  uint uVar1;
  int iVar2;
  uint uVar3;
  byte bVar4;

  uVar1 = (uint)param_1;
  uVar3 = FUN_81c12308(uVar1,0x11);
  iVar2 = g_scratch_buffer_4096;
  bVar4 = 0x3b;
  if (uVar3 == 0) {
LAB_81c0f924:
    FUN_81c17f44(bVar4);
  }
  else {
    do {
      while( true ) {
        uVar3 = FUN_81c13870(uVar1,iVar2);
        if (uVar3 == 0) {
          bVar4 = 0x54;
          goto LAB_81c0f924;
        }
        FUN_81c13494();
        uVar3 = FUN_81c19270(iVar2,uVar3,4,2,0xeb,0x3d);
        if (uVar3 == 0xff) {
          return 1;
        }
        bVar4 = *(byte *)(iVar2 + uVar3);
        uVar3 = FUN_81c11b50((uint)bVar4,0x11);
        if (uVar3 != 0) break;
        FUN_81c17f44(0x3c);
      }
      uVar3 = FUN_81c13a40((uint)DAT_81c2b115,iVar2);
      FUN_81c13494();
      if (uVar3 == 0) {
        return 1;
      }
      FUN_81c13494();
      uVar3 = FUN_81c19270(iVar2,uVar3,4,2,0xeb,0x3d);
    } while (uVar3 == 0xff);
    FUN_81c11bbc((uint)bVar4,0x11);
    FUN_81c12374(uVar1,0x11);
    local_30 = 0x11;
    local_2d = *(undefined1 *)(iVar2 + uVar3);
    local_25 = 10;
    local_2f = bVar4;
    local_2e = param_1;
    FUN_81c116f0(&local_30);
    FUN_81c123f0(uVar1,bVar4);
  }
  return 1;
}


#undef DAT_81c2b115
#undef g_scratch_buffer_4096
#undef local_30
#undef local_2f
#undef local_2e
#undef local_2d
#undef local_25

#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0f934; body bytes 388 */

undefined4 FUN_81c0f934(byte param_1)

{
  unsigned char sg_stack[28] __attribute__((aligned(8)));
#define local_30 (*(undefined1 *)(sg_stack + 0))
#define local_2f (*(byte *)(sg_stack + 1))
#define local_2e (*(byte *)(sg_stack + 2))
#define local_2d (*(byte *)(sg_stack + 3))
#define local_25 (*(undefined1 *)(sg_stack + 11))

  uint uVar1;
  byte *pbVar2;
  uint uVar3;
  byte bVar4;

  uVar1 = (uint)param_1;
  uVar3 = FUN_81c12308(uVar1,0x13);
  pbVar2 = g_scratch_buffer_4096;
  bVar4 = 0x3b;
  if (uVar3 == 0) {
LAB_81c0faa8:
    FUN_81c17f44(bVar4);
  }
  else {
    do {
      while( true ) {
        uVar3 = FUN_81c13870(uVar1,(int)pbVar2);
        if (uVar3 == 0) {
          bVar4 = 0x54;
          goto LAB_81c0faa8;
        }
        FUN_81c13494();
        uVar3 = FUN_81c19270((int)pbVar2,uVar3,4,2,0xeb,0x3d);
        if (uVar3 == 0xff) {
          return 1;
        }
        bVar4 = pbVar2[uVar3];
        uVar3 = FUN_81c11b50((uint)bVar4,0x13);
        if (uVar3 != 0) break;
        FUN_81c17f44(0x3c);
      }
      uVar3 = FUN_81c12a68((uint)DAT_81c2b115,pbVar2);
      FUN_81c13494();
      uVar3 = FUN_81c19270((int)pbVar2,uVar3,4,2,0xeb,0x3d);
    } while (uVar3 == 0xff);
    FUN_81c11bbc((uint)bVar4,0x13);
    FUN_81c12374(uVar1,0x13);
    local_30 = 0x13;
    local_2d = pbVar2[uVar3];
    local_25 = 10;
    local_2f = bVar4;
    local_2e = param_1;
    FUN_81c116f0(&local_30);
    FUN_81c123f0(uVar1,bVar4);
  }
  return 1;
}


#undef DAT_81c2b115
#undef g_scratch_buffer_4096
#undef local_30
#undef local_2f
#undef local_2e
#undef local_2d
#undef local_25

#define DAT_81c2b190 (*(undefined1 *)(0x81c2b190u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0fab8; body bytes 492 */

undefined4 FUN_81c0fab8(byte param_1)

{
  unsigned char sg_stack[28] __attribute__((aligned(8)));
#define local_30 (*(undefined1 *)(sg_stack + 0))
#define local_2f (*(byte *)(sg_stack + 1))
#define local_2e (*(byte *)(sg_stack + 2))
#define local_2d (*(byte *)(sg_stack + 3))
#define local_25 (*(undefined1 *)(sg_stack + 11))

  uint uVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  byte bVar5;
  char *pcVar6;
  uint unaff_s4;

  uVar1 = (uint)param_1;
  uVar4 = FUN_81c12308(uVar1,0x17);
  iVar3 = g_scratch_buffer_4096;
  bVar5 = 0x3b;
  if (uVar4 == 0) {
LAB_81c0fc94:
    FUN_81c17f44(bVar5);
    return 1;
  }
  bVar2 = false;
  do {
    if (!bVar2) goto LAB_81c0fc20;
    while (bVar2) {
      pcVar6 = (char *)(g_scratch_buffer_4096 + 300);
      FUN_81c154d8(0x40,0x5d,pcVar6);
      FUN_81c13494();
      bVar5 = (byte)unaff_s4;
      FUN_81c18024(bVar5,pcVar6);
      uVar4 = FUN_81c12b18(&DAT_81c2b190);
      if (uVar4 != 0xff) {
        if (uVar4 != uVar1) {
          if ((&DAT_81c2b451)[uVar4 * 0x24] != (&DAT_81c2b451)[uVar1 * 0x24]) {
            FUN_81c19b1c((byte)uVar4);
            FUN_81c11bbc(unaff_s4,0x17);
            FUN_81c12374(uVar1,0x17);
            local_30 = 0x17;
            local_2f = bVar5;
            local_2e = param_1;
            local_2d = (byte)uVar4;
            local_25 = bVar2;
            FUN_81c116f0(&local_30);
            FUN_81c123f0(uVar1,bVar5);
            return 1;
          }
          FUN_81c17f44(0x3a);
        }
        break;
      }
LAB_81c0fc20:
      while( true ) {
        uVar4 = FUN_81c13870(uVar1,iVar3);
        if (uVar4 == 0) {
          bVar5 = 0x54;
          goto LAB_81c0fc94;
        }
        FUN_81c13494();
        uVar4 = FUN_81c19270(iVar3,uVar4,4,2,0xeb,0x3d);
        if (uVar4 == 0xff) {
          return 1;
        }
        unaff_s4 = (uint)*(byte *)(iVar3 + uVar4);
        bVar2 = true;
        uVar4 = FUN_81c11b50(unaff_s4,0x17);
        if (uVar4 != 0) break;
        FUN_81c17f44(0x3c);
      }
    }
  } while( true );
}


#undef DAT_81c2b190
#undef DAT_81c2b451
#undef g_scratch_buffer_4096
#undef local_30
#undef local_2f
#undef local_2e
#undef local_2d
#undef local_25

#define DAT_81c2b45c (*(undefined1 *)(0x81c2b45cu))
#define DAT_81c2b468 (*(undefined2 *)(0x81c2b468u))
#define DAT_81c2b46c (*(undefined2 *)(0x81c2b46cu))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0fca4; body bytes 484 */

undefined4 FUN_81c0fca4(byte param_1)

{
  unsigned char sg_stack[28] __attribute__((aligned(8)));
#define local_38 (*(undefined1 *)(sg_stack + 0))
#define local_37 (*(byte *)(sg_stack + 1))
#define local_36 (*(byte *)(sg_stack + 2))
#define local_2d (*(undefined1 *)(sg_stack + 11))

  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  uint mode;
  ushort *puVar6;

  iVar2 = g_scratch_buffer_4096;
  uVar1 = (uint)param_1;
  uVar3 = FUN_81c13870(uVar1,g_scratch_buffer_4096);
  bVar5 = 0x54;
  if (uVar3 != 0) {
    while (uVar3 = FUN_81c12308(uVar1,0x18), uVar3 != 0) {
      uVar3 = FUN_81c13870(uVar1,iVar2);
      if (uVar3 == 0) {
        return 1;
      }
      do {
        while( true ) {
          FUN_81c13494();
          uVar4 = FUN_81c19270(iVar2,uVar3,4,2,0xeb,0x3d);
          puVar6 = &DAT_81c2b468 + uVar1 * 0x12;
          if (uVar4 == 0xff) {
            return 1;
          }
          bVar5 = *(byte *)(iVar2 + uVar4);
          uVar4 = FUN_81c11b50((uint)bVar5,0x18);
          if (uVar4 != 0) break;
          FUN_81c17f44(0x3c);
        }
        uVar4 = (uint)*puVar6;
        if (uVar4 < 0x1900) {
          uVar4 = uVar4 * 10 & 0xffff;
        }
        mode = (uint)(byte)(&DAT_81c2b45c)[uVar1 * 0x24] * 0x14;
        if (uVar4 < (uint)(byte)(&DAT_81c2b45c)[uVar1 * 0x24] * 0x14) {
          mode = uVar4;
        }
        uVar4 = FUN_81c13cdc(0,mode);
      } while (uVar4 == 0xffff);
      (&DAT_81c2b46c)[uVar1 * 0x12] = (short)uVar4 + (&DAT_81c2b46c)[uVar1 * 0x12];
      FUN_81c11bbc((uint)bVar5,0x18);
      local_38 = 0x18;
      local_2d = 0;
      *puVar6 = *puVar6 - (short)(uVar4 / 10);
      local_37 = bVar5;
      local_36 = param_1;
      FUN_81c116f0(&local_38);
      FUN_81c123f0(uVar1,bVar5);
    }
    bVar5 = 0x3b;
  }
  FUN_81c17f44(bVar5);
  return 1;
}


#undef DAT_81c2b45c
#undef DAT_81c2b468
#undef DAT_81c2b46c
#undef g_scratch_buffer_4096
#undef local_38
#undef local_37
#undef local_36
#undef local_2d

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b46c (*(undefined2 *)(0x81c2b46cu))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c0fe88; body bytes 408 */

undefined4 FUN_81c0fe88(uint param_1)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint unaff_s1;
  int iVar6;
  uint uVar7;

  iVar2 = g_scratch_buffer_4096;
  uVar7 = param_1 & 0xff;
  uVar3 = FUN_81c13870(uVar7,g_scratch_buffer_4096);
  if (uVar3 == 0) {
    FUN_81c17f44(0x54);
    return 1;
  }
  bVar1 = false;
  do {
    if (bVar1) goto LAB_81c0ff2c;
    while( true ) {
      uVar3 = FUN_81c13870(uVar7,iVar2);
      if (uVar3 == 0) {
        return 1;
      }
      FUN_81c13494();
      unaff_s1 = FUN_81c19270(iVar2,uVar3,4,2,0xeb,0x3d);
      bVar1 = true;
      if (unaff_s1 == 0xff) {
        return 1;
      }
LAB_81c0ff2c:
      if (!bVar1) break;
      iVar6 = (uint)*(byte *)(iVar2 + unaff_s1) * 0x10;
      iVar4 = iVar6 + DAT_81c2b164;
      uVar5 = (uint)(ushort)(&DAT_81c2b46c)[uVar7 * 0x12] + (uint)*(ushort *)(iVar4 + 10);
      uVar3 = ((uint)*(byte *)(iVar4 + 2) * 10 +
              (uint)*(byte *)(iVar4 + 3) + (uint)*(byte *)(iVar4 + 4)) * 10;
      if (uVar5 < uVar3) {
        uVar3 = uVar5;
      }
      if (uVar3 == 0) {
        FUN_81c17f44(0x39);
      }
      else {
        uVar3 = FUN_81c13cdc(0,uVar3 & 0xffff);
        if (uVar3 != 0xffff) {
          iVar6 = iVar6 + DAT_81c2b164;
          (&DAT_81c2b46c)[uVar7 * 0x12] =
               ((&DAT_81c2b46c)[uVar7 * 0x12] + *(short *)(iVar6 + 10)) - (short)uVar3;
          *(short *)(iVar6 + 10) = (short)uVar3;
        }
      }
    }
  } while( true );
}


#undef DAT_81c2b164
#undef DAT_81c2b46c
#undef g_scratch_buffer_4096

#define DAT_81c20538 (*(undefined *)(0x81c20538u))
/* VA 0x81c10020; body bytes 40 */

undefined4 FUN_81c10020(void)

{
  FUN_81c14dd8(&DAT_81c20538,2);
  return 1;
}


#undef DAT_81c20538

#define DAT_81c2b192 (*(byte *)(0x81c2b192u))
#define DAT_81c2b193 (*(byte *)(0x81c2b193u))
#define DAT_81c2b190 (*(undefined1 *)(0x81c2b190u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define DAT_81c2b46a (*(undefined2 *)(0x81c2b46au))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c10050; body bytes 836 */

undefined4 FUN_81c10050(byte param_1)

{
  unsigned char sg_stack[44] __attribute__((aligned(8)));
#define local_48 (*(char (*)[16])(sg_stack + 0))
#define local_38 (*(undefined1 (*)[2])(sg_stack + 16))
#define local_36 (*(byte *)(sg_stack + 18))
#define local_35 (*(undefined1 *)(sg_stack + 19))
#define local_32 (*(short *)(sg_stack + 22))
#define local_2d (*(undefined1 *)(sg_stack + 27))

  bool bVar1;
  uint uVar2;
  char *pcVar3;
  byte bVar4;
  byte bVar5;
  uint uVar6;
  uint uVar7;
  byte bVar8;
  uint uVar9;

  uVar2 = (uint)param_1;
  uVar6 = FUN_81c12308(uVar2,0x1b);
  bVar5 = DAT_81c2b193;
  bVar4 = DAT_81c2b192;
  pcVar3 = g_scratch_buffer_4096;
  bVar8 = 0x3b;
  if (uVar6 != 0) {
    uVar6 = FUN_81c13870(uVar2,(int)g_scratch_buffer_4096);
    if (uVar6 != 0) {
      FUN_81c0a7c8(local_48,0,10);
      uVar9 = 0;
      do {
        FUN_81c13494();
        uVar6 = FUN_81c19270((int)pcVar3,uVar6,4,2,0xeb,0x3d);
        if (uVar6 == 0xff) break;
        local_48[uVar9] = pcVar3[uVar6] + 1;
        FUN_81c123f0(uVar2,pcVar3[uVar6]);
        uVar6 = FUN_81c13870(uVar2,(int)pcVar3);
        uVar9 = uVar9 + 1 & 0xff;
      } while (uVar9 < 10);
      if (uVar9 == 0) {
        return 1;
      }
      FUN_81c13494();
      uVar6 = (uint)(ushort)(&DAT_81c2b46a)[uVar2 * 0x12];
      bVar1 = uVar6 != 0;
      if (!bVar1) {
        uVar6 = 0;
      }
      uVar6 = FUN_81c13b9c((uint)bVar1,uVar6);
      local_32 = (short)uVar6;
      if ((short)uVar6 != -1) {
        do {
          do {
            pcVar3 = g_scratch_buffer_4096;
            FUN_81c154d8(0x40,0x5d,g_scratch_buffer_4096);
            FUN_81c13494();
            FUN_81c18024(local_48[0] + 0xff,pcVar3);
            uVar6 = FUN_81c12b18(&DAT_81c2b190);
            if (uVar6 == 0xff) {
              while (uVar9 = uVar9 - 1 & 0xff, (uVar9 + 1 & 0xff) != 0) {
                FUN_81c134b8(uVar2,local_48[uVar9] - 1);
              }
              return 1;
            }
          } while (uVar6 == uVar2);
          bVar8 = 0x3a;
          if ((&DAT_81c2b451)[uVar6 * 0x24] != (&DAT_81c2b451)[uVar2 * 0x24]) {
            uVar7 = FUN_81c136a0(uVar2,bVar4,bVar5,uVar6,DAT_81c2b192,DAT_81c2b193);
            bVar8 = 0x37;
            if (uVar7 != 0xff) {
              FUN_81c17f44(0x5e);
              (&DAT_81c2b46a)[uVar2 * 0x12] = (&DAT_81c2b46a)[uVar2 * 0x12] - local_32;
              FUN_81c12374(uVar2,0x1b);
              local_38[0] = 0x1b;
              local_35 = (undefined1)uVar6;
              local_2d = (undefined1)uVar7;
              local_36 = param_1;
              FUN_81c11564(local_38,local_48);
              return 1;
            }
          }
          FUN_81c17f44(bVar8);
        } while( true );
      }
      while (uVar9 = uVar9 - 1 & 0xff, (uVar9 + 1 & 0xff) != 0) {
        FUN_81c134b8(uVar2,local_48[uVar9] - 1);
      }
      return 1;
    }
    bVar8 = 0x60;
  }
  FUN_81c17f44(bVar8);
  return 1;
}


#undef DAT_81c2b192
#undef DAT_81c2b193
#undef DAT_81c2b190
#undef DAT_81c2b451
#undef DAT_81c2b46a
#undef g_scratch_buffer_4096
#undef local_48
#undef local_38
#undef local_36
#undef local_35
#undef local_32
#undef local_2d

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b262 (*(short *)(0x81c2b262u))
#define DAT_81c2b261 (*(undefined1 *)(0x81c2b261u))
#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c2b260 (*(undefined1 *)(0x81c2b260u))
#define DAT_81c2b266 (*(undefined2 *)(0x81c2b266u))
#define DAT_81c2b264 (*(undefined2 *)(0x81c2b264u))
#define DAT_81c2b18c (*(char *)(0x81c2b18cu))
#define DAT_81c2b272 (*(undefined1 *)(0x81c2b272u))
#define DAT_81c2b268 (*(undefined1 *)(0x81c2b268u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define DAT_81c2b46a (*(undefined2 *)(0x81c2b46au))
#define g_state_buffer_300 (*(undefined4 *)(0x81c2b0e8u))
#define g_state_buffer_30 (*(undefined4 *)(0x81c2b0ecu))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c10394; body bytes 1720 */

undefined4 FUN_81c10394(int param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  uint uVar5;
  byte *pbVar6;
  byte *pbVar7;
  int iVar8;
  uint uVar9;
  byte *pbVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;

  pbVar7 = g_scratch_buffer_4096;
  *(undefined1 *)(g_state_buffer_30 + (uint)*(byte *)(param_1 + 1)) = 0;
  pbVar10 = (byte *)((uint)*(byte *)(param_1 + 1) * 10 + g_state_buffer_300);
  FUN_81c0a7c8(&DAT_81c2b268,0,0x14);
  bVar1 = *(byte *)(param_1 + 3);
  uVar13 = (uint)bVar1;
  bVar2 = (&DAT_81c2b451)[uVar13 * 0x24];
  uVar14 = (uint)bVar2;
  bVar3 = *(byte *)((uint)*pbVar10 * 0x10 + DAT_81c2b164 + -0xf);
  uVar12 = (uint)bVar3;
  FUN_81c154d8(2,0xf,pbVar7);
  DAT_81c2b262 = pbVar7[uVar13] + 0x6e;
  uVar5 = FUN_81c182d0(uVar13,(uint)*(byte *)(param_1 + 2));
  DAT_81c2b261 = (undefined1)uVar5;
  FUN_81c11d98(bVar3 - 1,bVar1);
  if (uVar14 == DAT_81c2b115 + 1) {
    if (uVar12 != uVar14) {
      DAT_81c2b264 = (&DAT_81c2b46a)[uVar13 * 0x12];
      DAT_81c2b260 = 0;
      uVar5 = 0;
      DAT_81c2b266 = *(undefined2 *)(param_1 + 6);
      do {
        uVar12 = FUN_81c13870(uVar13,(int)pbVar7);
        FUN_81c13494();
        uVar12 = FUN_81c19270((int)pbVar7,uVar12,4,2,0xeb,0x3d);
        if (uVar12 == 0xff) break;
        (&DAT_81c2b268)[uVar5] = pbVar7[uVar12] + 1;
        FUN_81c123f0(uVar13,pbVar7[uVar12]);
        uVar5 = uVar5 + 1 & 0xff;
      } while (uVar5 < 10);
      bbk_memcpy(&DAT_81c2b272,pbVar10,10);
      goto LAB_81c10678;
    }
    uVar5 = 0;
    pbVar7 = pbVar10;
    do {
      if (*pbVar7 != 0) {
        FUN_81c134b8(uVar13,*pbVar7 - 1);
      }
      uVar5 = uVar5 + 1 & 0xff;
      pbVar7 = pbVar10 + uVar5;
    } while (uVar5 < 10);
  }
  else {
    if (uVar12 == DAT_81c2b115 + 1) {
      if (uVar14 != 0) {
        if (uVar14 == uVar12) {
          uVar5 = 0;
          pbVar7 = pbVar10;
          do {
            if (*pbVar7 != 0) {
              FUN_81c134b8(uVar13,*pbVar7 - 1);
            }
            FUN_81c12058(bVar3);
            uVar5 = uVar5 + 1 & 0xff;
            pbVar7 = pbVar10 + uVar5;
          } while (uVar5 < 10);
          return 1;
        }
        DAT_81c2b260 = 1;
        DAT_81c2b264 = *(undefined2 *)(param_1 + 6);
        DAT_81c2b266 = (&DAT_81c2b46a)[uVar13 * 0x12];
        bbk_memcpy(&DAT_81c2b268,pbVar10,10);
        uVar5 = FUN_81c13870(uVar13,(int)pbVar7);
        if (uVar5 != 0) {
          uVar14 = uVar5 - 1;
          uVar12 = 0;
          if (0 < (int)uVar14) {
            uVar9 = 1;
            do {
              uVar11 = uVar9 & 0xff;
              if (uVar11 < uVar5) {
                iVar8 = DAT_81c2b164;
                do {
                  pbVar10 = pbVar7 + uVar11;
                  bVar1 = pbVar7[uVar12];
                  bVar2 = *pbVar10;
                  uVar11 = uVar11 + 1 & 0xff;
                  if (*(ushort *)((uint)bVar1 * 0x10 + iVar8 + 10) <
                      *(ushort *)((uint)bVar2 * 0x10 + iVar8 + 10)) {
                    *pbVar10 = bVar1;
                    pbVar7[uVar12] = bVar2;
                    iVar8 = DAT_81c2b164;
                  }
                  if (*(short *)((uint)pbVar7[uVar5 - 1] * 0x10 + iVar8 + 10) == 0) {
                    uVar5 = uVar14 & 0xff;
                    uVar14 = uVar5 - 1;
                  }
                } while (uVar11 < uVar5);
              }
              uVar12 = uVar9 & 0xff;
              uVar9 = uVar12 + 1;
            } while ((int)uVar12 < (int)uVar14);
          }
          if (uVar5 == 0) {
            DAT_81c2b272 = *pbVar7 + 1;
            FUN_81c123f0(uVar13,*pbVar7);
          }
          else {
            if (10 < uVar5) {
              uVar5 = 10;
            }
            uVar12 = 0;
            pbVar10 = pbVar7;
            if (uVar5 != 0) {
              do {
                FUN_81c123f0(uVar13,*pbVar10);
                (&DAT_81c2b272)[uVar12] = *pbVar10 + 1;
                uVar12 = uVar12 + 1 & 0xff;
                pbVar10 = pbVar7 + uVar12;
              } while (uVar12 < uVar5);
            }
          }
        }
        goto LAB_81c10678;
      }
      uVar5 = 0;
      do {
        if (pbVar10[uVar5] != 0) {
          FUN_81c134b8(uVar13,pbVar10[uVar5] - 1);
        }
        uVar5 = uVar5 + 1 & 0xff;
      } while (uVar5 < 10);
    }
    else {
      uVar5 = 0;
      pbVar6 = pbVar10;
      if (uVar14 != 0) {
        if (uVar14 == uVar12) {
          uVar5 = 0;
          pbVar7 = pbVar10;
          do {
            if (*pbVar7 != 0) {
              FUN_81c134b8(uVar13,*pbVar7 - 1);
            }
            uVar5 = uVar5 + 1 & 0xff;
            pbVar7 = pbVar10 + uVar5;
          } while (uVar5 < 10);
          goto LAB_81c104f4;
        }
        bbk_memcpy(&DAT_81c2b268,pbVar10,10);
        uVar5 = FUN_81c13870(uVar13,(int)pbVar7);
        if (uVar5 != 0) {
          uVar14 = uVar5 - 1;
          uVar12 = 0;
          if (0 < (int)uVar14) {
            uVar9 = 1;
            do {
              uVar11 = uVar9 & 0xff;
              if (uVar11 < uVar5) {
                iVar8 = DAT_81c2b164;
                do {
                  pbVar10 = pbVar7 + uVar11;
                  bVar1 = pbVar7[uVar12];
                  bVar4 = *pbVar10;
                  uVar11 = uVar11 + 1 & 0xff;
                  if (*(ushort *)((uint)bVar1 * 0x10 + iVar8 + 10) <
                      *(ushort *)((uint)bVar4 * 0x10 + iVar8 + 10)) {
                    *pbVar10 = bVar1;
                    pbVar7[uVar12] = bVar4;
                    iVar8 = DAT_81c2b164;
                  }
                  if (*(short *)((uint)pbVar7[uVar5 - 1] * 0x10 + iVar8 + 10) == 0) {
                    uVar5 = uVar14 & 0xff;
                    uVar14 = uVar5 - 1;
                  }
                } while (uVar11 < uVar5);
              }
              uVar12 = uVar9 & 0xff;
              uVar9 = uVar12 + 1;
            } while ((int)uVar12 < (int)uVar14);
          }
          if (uVar5 == 0) {
            DAT_81c2b272 = *pbVar7;
            FUN_81c123f0(uVar13,*pbVar7);
          }
          else {
            if (10 < uVar5) {
              uVar5 = 10;
            }
            uVar12 = 0;
            pbVar10 = pbVar7;
            if (uVar5 != 0) {
              do {
                FUN_81c123f0(uVar13,*pbVar10);
                (&DAT_81c2b272)[uVar12] = *pbVar10 + 1;
                uVar12 = uVar12 + 1 & 0xff;
                pbVar10 = pbVar7 + uVar12;
              } while (uVar12 < uVar5);
            }
          }
        }
        DAT_81c2b260 = 2;
        DAT_81c2b264 = *(undefined2 *)(param_1 + 6);
        DAT_81c2b266 = (&DAT_81c2b46a)[uVar13 * 0x12];
        FUN_81c11f18(bVar3 - 1,bVar2 - 1);
LAB_81c10678:
        FUN_81c04fe0();
        FUN_81c10a4c(uVar13,DAT_81c2b18c);
        return 1;
      }
      do {
        if (*pbVar6 != 0) {
          FUN_81c134b8(uVar13,*pbVar6 - 1);
        }
        uVar5 = uVar5 + 1 & 0xff;
        pbVar6 = pbVar10 + uVar5;
      } while (uVar5 < 10);
    }
    (&DAT_81c2b451)[uVar13 * 0x24] = bVar3;
  }
LAB_81c104f4:
  FUN_81c12058(bVar3);
  return 1;
}


#undef DAT_81c2b164
#undef DAT_81c2b262
#undef DAT_81c2b261
#undef DAT_81c2b115
#undef DAT_81c2b260
#undef DAT_81c2b266
#undef DAT_81c2b264
#undef DAT_81c2b18c
#undef DAT_81c2b272
#undef DAT_81c2b268
#undef DAT_81c2b451
#undef DAT_81c2b46a
#undef g_state_buffer_300
#undef g_state_buffer_30
#undef g_scratch_buffer_4096

#define DAT_81c2b17e (*(byte *)(0x81c2b17eu))
#define DAT_81c2b264 (*(short *)(0x81c2b264u))
#define DAT_81c2b266 (*(short *)(0x81c2b266u))
#define DAT_81c2b260 (*(char *)(0x81c2b260u))
#define DAT_81c2b13c (*(uchar *)(0x81c2b13cu))
#define DAT_81c2b272 (*(undefined1 *)(0x81c2b272u))
#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b268 (*(undefined1 *)(0x81c2b268u))
#define DAT_81c2b456 (*(undefined2 *)(0x81c2b456u))
#define DAT_81c2b45a (*(undefined2 *)(0x81c2b45au))
#define DAT_81c2b45c (*(undefined1 *)(0x81c2b45cu))
#define DAT_81c2b468 (*(undefined2 *)(0x81c2b468u))
#define DAT_81c2b46a (*(undefined2 *)(0x81c2b46au))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c10a4c; body bytes 800 */

undefined4 FUN_81c10a4c(uint param_1,char param_2)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  char *destination;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  char *source;

  uVar5 = param_1 & 0xff;
  DAT_81c2b17e = 0;
  uVar6 = 0xff;
  if (param_2 == '\x01') {
    uVar4 = 0;
    do {
      if ((&DAT_81c2b268)[uVar4] != '\0') {
        FUN_81c134b8(uVar5,(&DAT_81c2b268)[uVar4] - 1);
      }
      uVar4 = uVar4 + 1 & 0xff;
    } while (uVar4 < 10);
    FUN_81c12058(*(byte *)((uint)DAT_81c2b268 * 0x10 + DAT_81c2b164 + -0xf));
    if ((byte)(DAT_81c2b260 - 1U) < 2) {
      uVar6 = FUN_81c1107c(DAT_81c2b268 - 1,uVar5);
    }
    uVar4 = FUN_81c10d6c(uVar5,(char *)&DAT_81c2b272);
    if (uVar4 != 0xff) {
      uVar6 = uVar4;
    }
  }
  else {
    uVar4 = 10;
    if (param_2 == '\x02') {
      do {
        if ((&DAT_81c2b268)[uVar4] != '\0') {
          FUN_81c134b8(uVar5,(&DAT_81c2b268)[uVar4] - 1);
        }
        uVar4 = uVar4 + 1 & 0xff;
      } while (uVar4 < 0x14);
      if (DAT_81c2b260 == '\0') {
        uVar6 = FUN_81c1107c(DAT_81c2b272 - 1,uVar5);
      }
      uVar4 = FUN_81c10d6c(uVar5,(char *)&DAT_81c2b268);
      if (uVar4 != 0xff) {
        uVar6 = uVar4;
      }
      if (DAT_81c2b260 == '\x02') {
        FUN_81c12058(*(byte *)((uint)DAT_81c2b272 * 0x10 + DAT_81c2b164 + -0xf));
      }
      else {
        FUN_81c12188();
        destination = g_scratch_buffer_4096;
        if (DAT_81c2b17e != 0) {
          source = g_scratch_buffer_4096 + 0x28;
          if (1 < DAT_81c2b17e) {
            DAT_81c2b17e = 2;
          }
          sango_load_named_text(DAT_81c2b13c,g_scratch_buffer_4096);
          FUN_81c154d8(0x40,DAT_81c2b17e + 0x69 & 0xff,source);
          bbk_strcat(destination,source);
          FUN_81c14dd8(destination,2);
        }
      }
    }
  }
  uVar1 = (&DAT_81c2b456)[uVar5 * 0x12];
  uVar2 = (&DAT_81c2b45a)[uVar5 * 0x12];
  uVar3 = (&DAT_81c2b468)[uVar5 * 0x12];
  (&DAT_81c2b45c)[uVar5 * 0x24] =
       (&DAT_81c2b45c)[uVar5 * 0x24] - (byte)(&DAT_81c2b45c)[uVar5 * 0x24] / 10;
  (&DAT_81c2b456)[uVar5 * 0x12] = uVar1 - uVar1 / 0x14;
  (&DAT_81c2b45a)[uVar5 * 0x12] = uVar2 - uVar2 / 0x14;
  (&DAT_81c2b468)[uVar5 * 0x12] = uVar3 - uVar3 / 0x14;
  if (uVar6 != 0xff) {
    FUN_81c11188((byte)uVar6);
  }
  (&DAT_81c2b46a)[uVar5 * 0x12] = DAT_81c2b264 + DAT_81c2b266;
  return 0;
}


#undef DAT_81c2b17e
#undef DAT_81c2b264
#undef DAT_81c2b266
#undef DAT_81c2b260
#undef DAT_81c2b13c
#undef DAT_81c2b272
#undef DAT_81c2b164
#undef DAT_81c2b268
#undef DAT_81c2b456
#undef DAT_81c2b45a
#undef DAT_81c2b45c
#undef DAT_81c2b468
#undef DAT_81c2b46a
#undef g_scratch_buffer_4096

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b260 (*(char *)(0x81c2b260u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c10d6c; body bytes 524 */

uint FUN_81c10d6c(uint param_1,char *param_2)

{
  char cVar1;
  byte index;
  uint uVar2;
  int iVar3;
  char *source;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  char *destination;

  source = (char *)(g_scratch_buffer_4096 + 0x154);
  uVar8 = param_1 & 0xff;
  uVar9 = 0xff;
  destination = (char *)(g_scratch_buffer_4096 + 300);
  uVar7 = 0;
  pcVar4 = param_2;
  do {
    index = *pcVar4 - 1;
    if (*pcVar4 != '\0') {
      uVar5 = (uint)index;
      iVar6 = DAT_81c2b164 + uVar5 * 0x10;
      uVar2 = bbk_rand();
      uVar2 = (int)uVar2 % 100 & 0xff;
      if (*(byte *)(iVar6 + 4) < uVar2) {
        if (*(char *)(iVar6 + 1) == *pcVar4) {
          uVar9 = uVar5;
        }
LAB_81c10e88:
        FUN_81c10f78(index,uVar8);
      }
      else {
        iVar3 = FUN_81c10fdc(index);
        if (iVar3 == 0) {
          if (*(char *)(iVar6 + 1) == *pcVar4) {
            uVar9 = uVar5;
          }
          if (uVar2 != 0) goto LAB_81c10e88;
          if (*(char *)(iVar6 + 0xc) == '\0') {
            cVar1 = *(char *)(iVar6 + 0xd);
          }
          else {
            FUN_81c135a8(uVar8,*(char *)(iVar6 + 0xc) - 1);
            FUN_81c18150(*(char *)(iVar6 + 0xc) - 1);
            cVar1 = *(char *)(iVar6 + 0xd);
          }
          if (cVar1 != '\0') {
            FUN_81c135a8(uVar8,cVar1 - 1);
            FUN_81c18150(*(char *)(iVar6 + 0xd) - 1);
          }
          if (DAT_81c2b260 != '\x02') {
            sango_load_named_text(index,destination);
            FUN_81c154d8(0x40,0x6c,source);
            bbk_strcat(destination,source);
            FUN_81c14dd8(destination,2);
          }
        }
      }
    }
    uVar7 = uVar7 + 1 & 0xff;
    pcVar4 = param_2 + uVar7;
    if (9 < uVar7) {
      return uVar9;
    }
  } while( true );
}


#undef DAT_81c2b164
#undef DAT_81c2b260
#undef g_scratch_buffer_4096

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b17e (*(char *)(0x81c2b17eu))
#define DAT_81c2b13c (*(byte *)(0x81c2b13cu))
/* VA 0x81c10f78; body bytes 100 */

void FUN_81c10f78(byte param_1,uint param_2)

{
  undefined1 uVar1;
  undefined1 *puVar2;

  puVar2 = (undefined1 *)(DAT_81c2b164 + (uint)param_1 * 0x10);
  uVar1 = puVar2[1];
  puVar2[1] = 0xff;
  *puVar2 = uVar1;
  *(undefined2 *)(puVar2 + 10) = 0;
  DAT_81c2b17e = DAT_81c2b17e + '\x01';
  DAT_81c2b13c = param_1;
  FUN_81c134b8(param_2 & 0xff,param_1);
  return;
}


#undef DAT_81c2b164
#undef DAT_81c2b17e
#undef DAT_81c2b13c

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c10fdc; body bytes 160 */

undefined4 FUN_81c10fdc(byte param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;

  iVar1 = g_scratch_buffer_4096;
  uVar2 = FUN_81c13794(*(byte *)((uint)param_1 * 0x10 + DAT_81c2b164 + 1) - 1 & 0xff,
                       g_scratch_buffer_4096);
  uVar3 = 0;
  if (uVar2 != 0) {
    uVar4 = bbk_rand();
    if (uVar2 == 0) {
      trap(7);
    }
    FUN_81c134b8((uint)*(byte *)(iVar1 + ((int)uVar4 % (int)uVar2 & 0xffU)),param_1);
    uVar3 = 1;
  }
  return uVar3;
}


#undef DAT_81c2b164
#undef g_scratch_buffer_4096

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b17e (*(char *)(0x81c2b17eu))
#define DAT_81c2b13c (*(byte *)(0x81c2b13cu))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define DAT_81c2b452 (*(undefined1 *)(0x81c2b452u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c1107c; body bytes 268 */

uint FUN_81c1107c(byte param_1,uint param_2)

{
  undefined1 uVar1;
  byte *pbVar2;
  uint uVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;

  pbVar2 = g_scratch_buffer_4096;
  uVar3 = FUN_81c13870(param_2 & 0xff,(int)g_scratch_buffer_4096);
  iVar6 = DAT_81c2b164;
  uVar1 = *(undefined1 *)((uint)param_1 * 0x10 + DAT_81c2b164 + 1);
  iVar4 = (param_2 & 0xff) * 0x24;
  (&DAT_81c2b452)[iVar4] = param_1 + 1;
  (&DAT_81c2b451)[iVar4] = uVar1;
  uVar8 = 0xff;
  uVar7 = 0;
  pbVar5 = pbVar2;
  uVar9 = uVar8;
  if (uVar3 != 0) {
    while( true ) {
      uVar8 = (uint)*pbVar5;
      iVar6 = iVar6 + uVar8 * 0x10;
      if ((uint)*(byte *)(iVar6 + 1) == uVar8 + 1) {
        DAT_81c2b17e = DAT_81c2b17e + '\x01';
        DAT_81c2b13c = *pbVar5;
        *(undefined1 *)(iVar6 + 1) = 0xff;
      }
      else {
        *(undefined1 *)(iVar6 + 1) = 0;
        uVar8 = uVar9;
      }
      uVar7 = uVar7 + 1 & 0xff;
      *(undefined2 *)(iVar6 + 10) = 0;
      if (uVar3 <= uVar7) break;
      pbVar5 = pbVar2 + uVar7;
      iVar6 = DAT_81c2b164;
      uVar9 = uVar8;
    }
  }
  return uVar8;
}


#undef DAT_81c2b164
#undef DAT_81c2b17e
#undef DAT_81c2b13c
#undef DAT_81c2b451
#undef DAT_81c2b452
#undef g_scratch_buffer_4096

#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c11188; body bytes 636 */

void FUN_81c11188(byte param_1)

{
  unsigned char sg_stack[224] __attribute__((aligned(8)));
#define auStack_f0 (*(undefined1 (*)[104])(sg_stack + 0))
#define auStack_88 (*(undefined1 (*)[104])(sg_stack + 104))

  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte *pbVar4;
  byte *pbVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  byte *pbVar9;

  uVar7 = (uint)param_1;
  FUN_81c11404(param_1);
  pbVar5 = g_scratch_buffer_4096;
  uVar1 = FUN_81c13794(uVar7,(int)g_scratch_buffer_4096);
  pbVar9 = pbVar5 + 0x26;
  if (uVar1 == 0) {
    FUN_81c114fc(param_1);
  }
  else {
    uVar2 = FUN_81c13ab8(uVar7,(int)pbVar9);
    if (uVar2 == 0) {
      FUN_81c114fc(param_1);
      uVar7 = 0;
      pbVar9 = pbVar5;
      if (uVar1 != 0) {
        do {
          uVar7 = uVar7 + 1 & 0xff;
          (&DAT_81c2b451)[(uint)*pbVar9 * 0x24] = 0;
          pbVar9 = pbVar5 + uVar7;
        } while (uVar7 < uVar1);
      }
    }
    else {
      uVar6 = 1;
      if (DAT_81c2b115 == uVar7) {
        FUN_81c17f44(0x50);
        do {
          uVar7 = FUN_81c19270((int)pbVar9,uVar2,4,2,0xeb,0x3d);
        } while (uVar7 == 0xff);
        pbVar8 = pbVar9 + uVar7;
        DAT_81c2b115 = *pbVar8;
        bVar3 = *pbVar8;
      }
      else {
        pbVar8 = pbVar9;
        if (1 < uVar2) {
          do {
            pbVar4 = pbVar9 + uVar6;
            uVar6 = uVar6 + 1 & 0xff;
            if (*(byte *)((uint)*pbVar8 * 0x10 + DAT_81c2b164 + 4) <
                *(byte *)((uint)*pbVar4 * 0x10 + DAT_81c2b164 + 4)) {
              pbVar8 = pbVar4;
            }
          } while (uVar6 < uVar2);
        }
        bVar3 = *pbVar8;
      }
      uVar7 = 0;
      FUN_81c11494(bVar3);
      *(undefined1 *)((uint)*pbVar8 * 0x10 + DAT_81c2b164 + 5) = 100;
      pbVar4 = pbVar5;
      if (uVar1 != 0) {
        do {
          uVar7 = uVar7 + 1 & 0xff;
          (&DAT_81c2b451)[(uint)*pbVar4 * 0x24] = *pbVar8 + 1;
          pbVar4 = pbVar5 + uVar7;
        } while (uVar7 < uVar1);
      }
      uVar7 = 0;
      if (uVar2 != 0) {
        pbVar5 = pbVar9;
        do {
          *(byte *)((uint)*pbVar5 * 0x10 + DAT_81c2b164 + 1) = *pbVar8 + 1;
          sango_load_named_text
                    (*(char *)((uint)*pbVar5 * 0x10 + DAT_81c2b164 + 1) + 0xff,auStack_f0);
          sango_load_named_text(*pbVar5,auStack_88);
          uVar7 = uVar7 + 1 & 0xff;
          pbVar5 = pbVar9 + uVar7;
        } while (uVar7 < uVar2);
      }
    }
  }
  return;
}


#undef DAT_81c2b115
#undef DAT_81c2b164
#undef DAT_81c2b451
#undef g_scratch_buffer_4096
#undef auStack_f0
#undef auStack_88

#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c11404; body bytes 144 */

void FUN_81c11404(uchar param_1)

{
  char *source;
  char *destination;

  destination = (char *)(g_scratch_buffer_4096 + 300);
  source = (char *)(g_scratch_buffer_4096 + 0x154);
  FUN_81c154d8(0x40,0x4e,destination);
  sango_load_named_text(param_1,source);
  bbk_strcat(destination,source);
  FUN_81c154d8(0x40,0x4f,source);
  bbk_strcat(destination,source);
  FUN_81c14dd8(destination,2);
  return;
}


#undef g_scratch_buffer_4096

#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c11494; body bytes 104 */

void FUN_81c11494(uchar param_1)

{
  char *source;
  char *destination;

  destination = (char *)(g_scratch_buffer_4096 + 300);
  source = (char *)(g_scratch_buffer_4096 + 0x154);
  sango_load_named_text(param_1,destination);
  FUN_81c154d8(0x40,0x51,source);
  bbk_strcat(destination,source);
  FUN_81c14dd8(destination,2);
  return;
}


#undef g_scratch_buffer_4096

#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c114fc; body bytes 104 */

void FUN_81c114fc(uchar param_1)

{
  char *source;
  char *destination;

  destination = (char *)(g_scratch_buffer_4096 + 300);
  source = (char *)(g_scratch_buffer_4096 + 0x154);
  sango_load_named_text(param_1,destination);
  FUN_81c154d8(0x40,0x53,source);
  bbk_strcat(destination,source);
  FUN_81c14dd8(destination,2);
  return;
}


#undef g_scratch_buffer_4096

#define g_state_buffer_1200 (*(undefined4 *)(0x81c2b0e4u))
#define g_state_buffer_300 (*(undefined4 *)(0x81c2b0e8u))
#define g_state_buffer_30 (*(undefined4 *)(0x81c2b0ecu))
/* VA 0x81c11564; body bytes 212 */

undefined4 FUN_81c11564(void *param_1,void *param_2)

{
  char *dst;
  uint uVar1;

  uVar1 = 0;
  do {
    if (*(char *)(g_state_buffer_30 + uVar1) == '\0') {
      *(char *)(g_state_buffer_30 + uVar1) = '\x01';
      bbk_memcpy((void *)(uVar1 * 10 + g_state_buffer_300),param_2,10);
      *(char *)((int)param_1 + 1) = (char)uVar1;
      uVar1 = 0x46;
      do {
        dst = (char *)(uVar1 * 0xc + g_state_buffer_1200);
        uVar1 = uVar1 + 1 & 0xff;
        if (*dst == -1) {
          bbk_memcpy(dst,param_1,0xc);
          return 1;
        }
      } while (uVar1 < 100);
      return 1;
    }
    uVar1 = uVar1 + 1 & 0xff;
  } while (uVar1 < 100);
  return 0;
}


#undef g_state_buffer_1200
#undef g_state_buffer_300
#undef g_state_buffer_30

#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c11638; body bytes 104 */

void FUN_81c11638(uchar param_1)

{
  char *source;
  char *destination;

  destination = (char *)(g_scratch_buffer_4096 + 300);
  source = (char *)(g_scratch_buffer_4096 + 0x154);
  sango_load_named_text(param_1,destination);
  FUN_81c154d8(0x40,0x52,source);
  bbk_strcat(destination,source);
  FUN_81c14dd8(destination,2);
  return;
}


#undef g_scratch_buffer_4096

#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c116a0; body bytes 80 */

void FUN_81c116a0(uchar param_1)

{
  char *pcVar1;

  pcVar1 = (char *)(g_scratch_buffer_4096 + 300);
  FUN_81c154d8(0x40,0x5f,pcVar1);
  FUN_81c18024(param_1,pcVar1);
  return;
}


#undef g_scratch_buffer_4096

#define g_state_buffer_1200 (*(undefined4 *)(0x81c2b0e4u))
/* VA 0x81c116f0; body bytes 104 */

undefined4 FUN_81c116f0(void *param_1)

{
  int iVar1;
  uint uVar2;
  char *dst;

  uVar2 = 0;
  iVar1 = 0;
  do {
    dst = (char *)((iVar1 + uVar2) * 4 + g_state_buffer_1200);
    uVar2 = uVar2 + 1 & 0xff;
    if (*dst == -1) {
      bbk_memcpy(dst,param_1,0xc);
      return 0;
    }
    iVar1 = uVar2 << 1;
  } while (uVar2 < 100);
  return 1;
}


#undef g_state_buffer_1200

#define g_state_buffer_1200 (*(undefined4 *)(0x81c2b0e4u))
/* VA 0x81c11758; body bytes 104 */

undefined4 FUN_81c11758(void *param_1)

{
  int iVar1;
  uint uVar2;
  char *dst;

  uVar2 = 0x46;
  iVar1 = 0x8c;
  do {
    dst = (char *)((iVar1 + uVar2) * 4 + g_state_buffer_1200);
    uVar2 = uVar2 + 1 & 0xff;
    if (*dst == -1) {
      bbk_memcpy(dst,param_1,0xc);
      return 0;
    }
    iVar1 = uVar2 << 1;
  } while (uVar2 < 100);
  return 1;
}


#undef g_state_buffer_1200


/* VA 0x81c117c0; body bytes 16 */

undefined4 FUN_81c117c0(undefined1 *param_1)

{
  *param_1 = 0xff;
  return 1;
}




#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c20540 (*(undefined *)(0x81c20540u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c117d0; body bytes 604 */

undefined4 FUN_81c117d0(uint param_1)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
#define local_30 (*(byte (*)[8])(sg_stack + 0))

  bool bVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  byte *pbVar9;
  char *pcVar10;

  iVar3 = g_scratch_buffer_4096;
  while( true ) {
    uVar4 = FUN_81c13870(param_1 & 0xff,iVar3);
    if (uVar4 == 0) {
      FUN_81c17f44(0x54);
      return 1;
    }
    FUN_81c13494();
    uVar4 = FUN_81c19270(iVar3,uVar4,4,2,0xeb,0x3d);
    if (uVar4 == 0xff) break;
    bVar2 = *(byte *)(iVar3 + uVar4);
    uVar4 = (uint)bVar2;
    iVar7 = DAT_81c2b164 + uVar4 * 0x10;
    bVar1 = *(char *)(iVar7 + 0xc) != '\0';
    pcVar10 = (char *)(iVar7 + 0xc);
    if (!bVar1) {
      *(undefined1 *)(iVar7 + 0xc) = *(undefined1 *)(iVar7 + 0xd);
      *(undefined1 *)(iVar7 + 0xd) = 0;
    }
    uVar5 = (uint)bVar1;
    if (pcVar10[uVar5] != '\0') {
      uVar5 = uVar5 + 1;
    }
    local_30[0] = *pcVar10 - 1;
    local_30[1] = *(char *)(iVar7 + 0xd) + -1;
    if (uVar5 == 0) {
      FUN_81c17f44(0x55);
    }
    else {
      FUN_81c13494();
      uVar5 = FUN_81c18874((int)local_30,uVar5,4,2,0xeb,0x3d);
      if (uVar5 != 0xff) {
        if (DAT_81c2b115 == uVar4) {
          FUN_81c13494();
          FUN_81c18024(bVar2,&DAT_81c20540);
        }
        else {
          pcVar8 = (char *)(g_scratch_buffer_4096 + 300);
          uVar6 = bbk_rand();
          FUN_81c154d8(0x40,(int)uVar6 % 3 - 0x80U & 0xff,pcVar8);
          FUN_81c13494();
          FUN_81c18024(bVar2,pcVar8);
          iVar7 = uVar4 * 0x10 + DAT_81c2b164;
          if (*(byte *)(iVar7 + 5) < 0x14) {
            *(undefined1 *)(iVar7 + 5) = 0;
          }
          else {
            *(byte *)(iVar7 + 5) = *(byte *)(iVar7 + 5) - 0x14;
          }
        }
        pbVar9 = local_30 + uVar5;
        FUN_81c135a8(param_1 & 0xff,*pbVar9);
        FUN_81c18150(*pbVar9);
        FUN_81c17eb4((uint)*pbVar9,uVar4);
        pcVar10[uVar5] = '\0';
      }
    }
  }
  return 1;
}


#undef DAT_81c2b164
#undef DAT_81c2b115
#undef DAT_81c20540
#undef g_scratch_buffer_4096
#undef local_30

#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c11a2c; body bytes 292 */

undefined4 FUN_81c11a2c(byte param_1)

{
  unsigned char sg_stack[28] __attribute__((aligned(8)));
#define local_28 (*(undefined1 *)(sg_stack + 0))
#define local_27 (*(byte *)(sg_stack + 1))
#define local_26 (*(byte *)(sg_stack + 2))
#define local_1d (*(undefined1 *)(sg_stack + 11))

  byte bVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;

  iVar2 = g_scratch_buffer_4096;
  while( true ) {
    uVar3 = FUN_81c13870((uint)param_1,iVar2);
    if (uVar3 == 0) {
      FUN_81c17f44(0x54);
      return 1;
    }
    FUN_81c13494();
    uVar3 = FUN_81c19270(iVar2,uVar3,4,2,0xeb,0x3d);
    if (uVar3 == 0xff) break;
    bVar1 = *(byte *)(iVar2 + uVar3);
    uVar3 = FUN_81c11b50((uint)bVar1,0x18);
    if (uVar3 != 0) {
      FUN_81c11bbc((uint)bVar1,0x18);
      pcVar4 = (char *)(g_scratch_buffer_4096 + 300);
      FUN_81c154d8(0x40,0x94,pcVar4);
      FUN_81c18024(bVar1,pcVar4);
      local_28 = 0x1a;
      local_1d = 0;
      local_27 = bVar1;
      local_26 = param_1;
      FUN_81c116f0(&local_28);
      FUN_81c123f0((uint)param_1,bVar1);
      return 1;
    }
    FUN_81c17f44(0x3c);
  }
  return 1;
}


#undef g_scratch_buffer_4096
#undef local_28
#undef local_27
#undef local_26
#undef local_1d

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c11b50; body bytes 108 */

uint FUN_81c11b50(uint param_1,uint param_2)

{
  int iVar1;

  iVar1 = FUN_81c152f0(2,'\n',g_sango_package_data);
  return (uint)(*(byte *)(iVar1 + (param_2 & 0xff)) <=
               *(byte *)((param_1 & 0xff) * 0x10 + DAT_81c2b164 + 8));
}


#undef DAT_81c2b164
#undef g_sango_package_data

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c11bbc; body bytes 108 */

void FUN_81c11bbc(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;

  iVar1 = FUN_81c152f0(2,'\n',g_sango_package_data);
  iVar2 = (param_1 & 0xff) * 0x10 + DAT_81c2b164;
  *(char *)(iVar2 + 8) = *(char *)(iVar2 + 8) - *(char *)(iVar1 + (param_2 & 0xff));
  return;
}


#undef DAT_81c2b164
#undef g_sango_package_data

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b310 (*(undefined1 *)(0x81c2b310u))
#define g_state_buffer_1200 (*(undefined4 *)(0x81c2b0e4u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define DAT_81c2b46e (*(undefined1 *)(0x81c2b46eu))
#define DAT_81c2b46f (*(undefined1 *)(0x81c2b46fu))
/* VA 0x81c11c28; body bytes 368 */

uint FUN_81c11c28(uint param_1,int param_2)

{
  char cVar1;
  int iVar2;
  byte *pbVar3;
  ushort uVar4;
  int iVar5;
  uint uVar6;
  ushort uVar7;
  char *pcVar8;
  uint uVar9;
  uint unaff_s1;

  uVar7 = 0xffff;
  uVar9 = 0;
  if ((param_1 & 0xff) != 0) {
    do {
      uVar4 = 0;
      iVar2 = (uint)*(byte *)(param_2 + uVar9) * 0x24;
      uVar6 = 0;
      if ((byte)(&DAT_81c2b46f)[iVar2] != 0) {
        pbVar3 = &DAT_81c2b310 + (byte)(&DAT_81c2b46e)[iVar2];
        do {
          uVar6 = uVar6 + 1 & 0xff;
          iVar5 = (uint)*pbVar3 * 0x10 + DAT_81c2b164;
          if (*(char *)(iVar5 + 1) == (&DAT_81c2b451)[iVar2]) {
            uVar4 = uVar4 + *(short *)(iVar5 + 10);
          }
          pbVar3 = &DAT_81c2b310 + (byte)(&DAT_81c2b46e)[iVar2] + uVar6;
        } while (uVar6 < (byte)(&DAT_81c2b46f)[iVar2]);
      }
      uVar6 = 0;
      iVar2 = 0;
      do {
        pcVar8 = (char *)((iVar2 + uVar6) * 4 + g_state_buffer_1200);
        cVar1 = *pcVar8;
        uVar6 = uVar6 + 1 & 0xff;
        if ((((cVar1 != -1) && (cVar1 != '\x0e')) && (cVar1 != '\x1b')) &&
           (pcVar8[2] == *(byte *)(param_2 + uVar9))) {
          uVar4 = uVar4 + *(short *)((uint)(byte)pcVar8[1] * 0x10 + DAT_81c2b164 + 10);
        }
        iVar2 = uVar6 << 1;
      } while (uVar6 < 100);
      if (uVar4 < uVar7) {
        unaff_s1 = uVar9;
        uVar7 = uVar4;
      }
      uVar9 = uVar9 + 1 & 0xff;
    } while (uVar9 < (param_1 & 0xff));
  }
  return (uint)*(byte *)(param_2 + unaff_s1);
}


#undef DAT_81c2b164
#undef DAT_81c2b310
#undef g_state_buffer_1200
#undef DAT_81c2b451
#undef DAT_81c2b46e
#undef DAT_81c2b46f

#define DAT_81c2b115 (*(uchar *)(0x81c2b115u))
#define DAT_81c2b128 (*(uint *)(0x81c2b128u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c11d98; body bytes 384 */

void FUN_81c11d98(uchar param_1,char param_2)

{
  byte *pbVar1;
  char *destination;
  char *source;

  FUN_81c0ac48(0x3b,0x75,0xb3,0xc9,0,0);
  FUN_81c08e7c(0x3b,0x75,0xb3,0xc9,3,0,0);
  pbVar1 = (byte *)FUN_81c152f0(0x4c,'\x01',g_sango_package_data);
  FUN_81c14fb8(0x4d,0x77,0x54,0x40,0,pbVar1);
  destination = (char *)(g_scratch_buffer_4096 + 300);
  source = (char *)(g_scratch_buffer_4096 + 0x154);
  if (DAT_81c2b115 == param_1) {
    FUN_81c154d8(0x40,0x62,destination);
  }
  else {
    sango_load_named_text(param_1,destination);
  }
  FUN_81c154d8(0x40,0x61,source);
  bbk_strcat(destination,source);
  FUN_81c1971c(param_2,source);
  bbk_strcat(destination,source);
  FUN_81c07b58(0x77,0xb9,destination);
  FUN_81c14164(0x1e,'\0');
  FUN_81c15210(0x78,0xd4,0x9f,0xef,DAT_81c2b128);
  FUN_81c15134(0x78,0xd4,source,DAT_81c2b128);
  return;
}


#undef DAT_81c2b115
#undef DAT_81c2b128
#undef g_scratch_buffer_4096
#undef g_sango_package_data

#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c11f18; body bytes 320 */

void FUN_81c11f18(uchar param_1,uchar param_2)

{
  byte *pbVar1;
  char *source;
  char *destination;

  FUN_81c0ac48(0x3b,0x75,0xb3,0xc9,0,0);
  FUN_81c08e7c(0x3b,0x75,0xb3,0xc9,3,0,0);
  pbVar1 = (byte *)FUN_81c152f0(0x4c,'\x01',g_sango_package_data);
  FUN_81c14fb8(0x4d,0x77,0x54,0x40,1,pbVar1);
  destination = (char *)(g_scratch_buffer_4096 + 300);
  source = (char *)(g_scratch_buffer_4096 + 0x154);
  sango_load_named_text(param_1,destination);
  FUN_81c154d8(0x40,0x68,source);
  bbk_strcat(destination,source);
  sango_load_named_text(param_2,source);
  bbk_strcat(destination,source);
  FUN_81c154d8(0x40,0x69,source);
  bbk_strcat(destination,source);
  FUN_81c07b58(0x77,0xb9,destination);
  FUN_81c14164(0x32,'\0');
  return;
}


#undef g_scratch_buffer_4096
#undef g_sango_package_data

#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c12058; body bytes 304 */

void FUN_81c12058(byte param_1)

{
  byte *pbVar1;
  char *destination;
  char *source;

  FUN_81c0ac48(0x3b,0x75,0xb3,0xc9,0,0);
  FUN_81c08e7c(0x3b,0x75,0xb3,0xc9,3,0,0);
  pbVar1 = (byte *)FUN_81c152f0(0x4c,'\x01',g_sango_package_data);
  FUN_81c14fb8(0x4d,0x77,0x54,0x40,2,pbVar1);
  destination = (char *)(g_scratch_buffer_4096 + 300);
  source = (char *)(g_scratch_buffer_4096 + 0x154);
  if ((uint)param_1 == DAT_81c2b115 + 1) {
    FUN_81c154d8(0x40,0x62,destination);
  }
  else {
    sango_load_named_text(param_1 - 1,destination);
  }
  FUN_81c154d8(0x40,0x5b,source);
  bbk_strcat(destination,source);
  FUN_81c07b58(0x77,0xb9,destination);
  FUN_81c14164(0x32,'\0');
  return;
}


#undef DAT_81c2b115
#undef g_scratch_buffer_4096
#undef g_sango_package_data

#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c12188; body bytes 236 */

void FUN_81c12188(void)

{
  byte *pbVar1;
  char *source;
  char *destination;

  FUN_81c0ac48(0x3b,0x75,0xb3,0xc9,0,0);
  FUN_81c08e7c(0x3b,0x75,0xb3,0xc9,3,0,0);
  pbVar1 = (byte *)FUN_81c152f0(0x4c,'\x01',g_sango_package_data);
  FUN_81c14fb8(0x4d,0x77,0x54,0x40,3,pbVar1);
  destination = (char *)(g_scratch_buffer_4096 + 300);
  source = (char *)(g_scratch_buffer_4096 + 0x154);
  FUN_81c154d8(0x40,0x62,destination);
  FUN_81c154d8(0x40,0x5c,source);
  bbk_strcat(destination,source);
  FUN_81c07b58(0x77,0xb9,destination);
  FUN_81c14164(0x32,'\0');
  return;
}


#undef g_scratch_buffer_4096
#undef g_sango_package_data

#define DAT_81c2b468 (*(undefined2 *)(0x81c2b468u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c12308; body bytes 108 */

uint FUN_81c12308(uint param_1,uint param_2)

{
  int iVar1;

  iVar1 = FUN_81c152f0(2,'\v',g_sango_package_data);
  return (uint)((ushort)*(byte *)(iVar1 + (param_2 & 0xff)) <=
               (ushort)(&DAT_81c2b468)[(param_1 & 0xff) * 0x12]);
}


#undef DAT_81c2b468
#undef g_sango_package_data

#define DAT_81c2b468 (*(undefined2 *)(0x81c2b468u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c12374; body bytes 112 */

void FUN_81c12374(uint param_1,uint param_2)

{
  int iVar1;

  iVar1 = FUN_81c152f0(2,'\v',g_sango_package_data);
  (&DAT_81c2b468)[(param_1 & 0xff) * 0x12] =
       (&DAT_81c2b468)[(param_1 & 0xff) * 0x12] - (ushort)*(byte *)(iVar1 + (param_2 & 0xff));
  return;
}


#undef DAT_81c2b468
#undef g_sango_package_data

#define DAT_81c2b310 (*(undefined1 *)(0x81c2b310u))
#define DAT_81c2b311 (*(undefined1 *)(0x81c2b311u))
#define DAT_81c2b46e (*(undefined1 *)(0x81c2b46eu))
#define DAT_81c2b46f (*(undefined1 *)(0x81c2b46fu))
/* VA 0x81c123f0; body bytes 276 */

undefined4 FUN_81c123f0(uint param_1,byte param_2)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;

  uVar6 = param_1 & 0xff;
  if ((uVar6 < 0x26) && (param_2 < 200)) {
    iVar3 = uVar6 * 0x24;
    uVar4 = (uint)(byte)(&DAT_81c2b46e)[iVar3];
    bVar1 = (&DAT_81c2b46f)[iVar3];
    uVar5 = uVar4 + bVar1;
    for (; bVar2 = uVar4 < (uVar5 & 0xff), bVar2; uVar4 = uVar4 + 1 & 0xff) {
      if ((&DAT_81c2b310)[uVar4] == param_2) {
        if (bVar2) {
          for (; uVar4 < 199; uVar4 = uVar4 + 1 & 0xff) {
            (&DAT_81c2b310)[uVar4] = (&DAT_81c2b311)[uVar4];
          }
          (&DAT_81c2b46f)[iVar3] = bVar1 - 1;
          while (uVar6 = uVar6 + 1 & 0xff, uVar6 < 0x26) {
            (&DAT_81c2b46e)[uVar6 * 0x24] = (&DAT_81c2b46e)[uVar6 * 0x24] + -1;
          }
          return 1;
        }
        return 0;
      }
    }
  }
  return 0;
}


#undef DAT_81c2b310
#undef DAT_81c2b311
#undef DAT_81c2b46e
#undef DAT_81c2b46f

#define DAT_81c2b3e0 (*(undefined1 *)(0x81c2b3e0u))
#define DAT_81c2b3e1 (*(undefined1 *)(0x81c2b3e1u))
#define DAT_81c2b470 (*(undefined1 *)(0x81c2b470u))
#define DAT_81c2b471 (*(undefined1 *)(0x81c2b471u))
/* VA 0x81c12504; body bytes 280 */

undefined4 FUN_81c12504(uint param_1,byte param_2)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;

  uVar6 = param_1 & 0xff;
  if ((uVar6 < 0x26) && (param_2 < 0x21)) {
    iVar3 = uVar6 * 0x24;
    uVar4 = (uint)(byte)(&DAT_81c2b470)[iVar3];
    bVar1 = (&DAT_81c2b471)[iVar3];
    uVar5 = uVar4 + bVar1;
    for (; bVar2 = uVar4 < (uVar5 & 0xff), bVar2; uVar4 = uVar4 + 1 & 0xff) {
      if (((&DAT_81c2b3e0)[uVar4] & 0x7f) == param_2) {
        if (bVar2) {
          for (; uVar4 < 0x20; uVar4 = uVar4 + 1 & 0xff) {
            (&DAT_81c2b3e0)[uVar4] = (&DAT_81c2b3e1)[uVar4];
          }
          (&DAT_81c2b471)[iVar3] = bVar1 - 1;
          while (uVar6 = uVar6 + 1 & 0xff, uVar6 < 0x26) {
            (&DAT_81c2b470)[uVar6 * 0x24] = (&DAT_81c2b470)[uVar6 * 0x24] + -1;
          }
          return 1;
        }
        return 0;
      }
    }
  }
  return 0;
}


#undef DAT_81c2b3e0
#undef DAT_81c2b3e1
#undef DAT_81c2b470
#undef DAT_81c2b471

#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c1261c; body bytes 464 */

uint FUN_81c1261c(uint param_1,byte param_2,byte param_3,char param_4,byte param_5,byte param_6)

{
  unsigned char sg_stack[21] __attribute__((aligned(8)));
  (*(byte *)(sg_stack + 0)) = param_5;
  (*(byte *)(sg_stack + 4)) = param_6;
#define param_5 (*(byte *)(sg_stack + 0))
#define param_6 (*(byte *)(sg_stack + 4))

  char cVar1;
  byte bVar2;
  uint uVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  uint uVar9;

  pcVar8 = (char *)(g_scratch_buffer_4096 + 200);
  uVar3 = FUN_81c127ec(param_1 & 0xff,(int)pcVar8);
  if (uVar3 != 0) {
    do {
      uVar7 = uVar3;
      uVar9 = 0;
      uVar3 = uVar7;
      if (uVar7 != 0) {
        do {
          uVar6 = FUN_81c127ec((uint)(byte)pcVar8[uVar9],(int)(pcVar8 + uVar3));
          uVar9 = uVar9 + 1 & 0xff;
          uVar3 = uVar3 + uVar6 & 0xff;
        } while (uVar9 < uVar7);
      }
      uVar9 = 0;
      if (uVar3 != 0) {
        uVar6 = 1;
        do {
          uVar5 = uVar6 & 0xff;
          if (uVar5 < uVar3) {
            do {
              if (pcVar8[uVar9] == pcVar8[uVar5]) {
                uVar3 = uVar3 - 1 & 0xff;
                pcVar8[uVar5] = pcVar8[uVar3];
              }
              else {
                uVar5 = uVar5 + 1 & 0xff;
              }
            } while (uVar5 < uVar3);
          }
          uVar9 = uVar6 & 0xff;
          uVar6 = uVar9 + 1;
        } while (uVar9 < uVar3);
      }
    } while (uVar3 != uVar7);
    uVar3 = 0;
    if (uVar7 != 0) {
      pcVar4 = pcVar8;
      do {
        uVar3 = uVar3 + 1 & 0xff;
        if (*pcVar4 == param_4) {
          cVar1 = param_6 - param_3;
          if (param_6 <= param_3) {
            cVar1 = param_3 - param_6;
          }
          if (param_2 < param_5) {
            bVar2 = (cVar1 + param_5) - param_2;
          }
          else {
            bVar2 = (cVar1 + param_2) - param_5;
          }
          return (uint)bVar2;
        }
        pcVar4 = pcVar8 + uVar3;
      } while (uVar3 < uVar7);
    }
  }
  return 0xff;
}


#undef g_scratch_buffer_4096
#undef param_5
#undef param_6

#define DAT_81c2b42d (*(undefined *)(0x81c2b42du))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c127ec; body bytes 200 */

uint FUN_81c127ec(uint param_1,int param_2)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  char *pcVar6;
  byte *pbVar7;
  uint uVar8;

  iVar3 = FUN_81c152f0(0x3b,'\x01',g_sango_package_data);
  cVar1 = (&DAT_81c2b451)[(param_1 & 0xff) * 0x24];
  pbVar7 = (byte *)(iVar3 + (param_1 & 0xff) * 0x10);
  uVar8 = 0;
  uVar5 = 0;
  pbVar4 = pbVar7;
  do {
    bVar2 = *pbVar4;
    uVar5 = uVar5 + 1 & 0xff;
    if (bVar2 != 0) {
      pcVar6 = (char *)(param_2 + uVar8);
      if ((&DAT_81c2b42d)[(uint)bVar2 * 0x24] == cVar1) {
        uVar8 = uVar8 + 1 & 0xff;
        *pcVar6 = bVar2 - 1;
      }
    }
    pbVar4 = pbVar7 + uVar5;
  } while (uVar5 < 8);
  return uVar8;
}


#undef DAT_81c2b42d
#undef DAT_81c2b451
#undef g_sango_package_data

#define DAT_81c2b42d (*(undefined *)(0x81c2b42du))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c128b4; body bytes 200 */

uint FUN_81c128b4(uint param_1,int param_2)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  char *pcVar6;
  byte *pbVar7;
  uint uVar8;

  iVar3 = FUN_81c152f0(0x3b,'\x01',g_sango_package_data);
  cVar1 = (&DAT_81c2b451)[(param_1 & 0xff) * 0x24];
  pbVar7 = (byte *)(iVar3 + (param_1 & 0xff) * 0x10);
  uVar8 = 0;
  uVar5 = 0;
  pbVar4 = pbVar7;
  do {
    bVar2 = *pbVar4;
    uVar5 = uVar5 + 1 & 0xff;
    if (bVar2 != 0) {
      if ((&DAT_81c2b42d)[(uint)bVar2 * 0x24] != '\0') {
        pcVar6 = (char *)(param_2 + uVar8);
        if ((&DAT_81c2b42d)[(uint)bVar2 * 0x24] != cVar1) {
          uVar8 = uVar8 + 1 & 0xff;
          *pcVar6 = bVar2 - 1;
        }
      }
    }
    pbVar4 = pbVar7 + uVar5;
  } while (uVar5 < 8);
  return uVar8;
}


#undef DAT_81c2b42d
#undef DAT_81c2b451
#undef g_sango_package_data

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b310 (*(undefined1 *)(0x81c2b310u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define DAT_81c2b46e (*(undefined1 *)(0x81c2b46eu))
#define DAT_81c2b46f (*(undefined1 *)(0x81c2b46fu))
/* VA 0x81c1297c; body bytes 236 */

uint FUN_81c1297c(uint param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;

  uVar7 = 0;
  uVar6 = 0;
  do {
    iVar2 = uVar6 * 0x24;
    uVar4 = (uint)(byte)(&DAT_81c2b451)[iVar2];
    if (((uVar4 != (param_1 & 0xff) + 1) && (uVar4 != 0)) &&
       (uVar5 = 0, (&DAT_81c2b46f)[iVar2] != '\0')) {
      do {
        bVar1 = (&DAT_81c2b310)[uVar5 + (byte)(&DAT_81c2b46e)[uVar6 * 0x24]];
        uVar5 = uVar5 + 1 & 0xff;
        if (*(byte *)((uint)bVar1 * 0x10 + DAT_81c2b164 + 1) == uVar4) {
          pbVar3 = (byte *)(param_2 + uVar7);
          if (bVar1 + 1 != uVar4) {
            uVar7 = uVar7 + 1 & 0xff;
            *pbVar3 = bVar1;
          }
        }
      } while (uVar5 < (byte)(&DAT_81c2b46f)[iVar2]);
    }
    uVar6 = uVar6 + 1 & 0xff;
  } while (uVar6 < 0x26);
  return uVar7;
}


#undef DAT_81c2b164
#undef DAT_81c2b310
#undef DAT_81c2b451
#undef DAT_81c2b46e
#undef DAT_81c2b46f

#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
/* VA 0x81c12a68; body bytes 176 */

uint FUN_81c12a68(uint param_1,byte *param_2)

{
  bool bVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;

  uVar6 = 0;
  uVar5 = 0;
  do {
    uVar4 = (uint)(byte)(&DAT_81c2b451)[uVar5 * 0x24];
    if ((uVar4 != 0) && (uVar4 != (param_1 & 0xff) + 1)) {
      uVar3 = 0;
      if (uVar6 == 0) {
        bVar1 = false;
LAB_81c12b00:
        if (bVar1) goto LAB_81c12ae4;
      }
      else {
        pbVar2 = param_2;
        do {
          if ((uint)*pbVar2 == uVar4 - 1) {
            bVar1 = uVar3 < uVar6;
            goto LAB_81c12b00;
          }
          uVar3 = uVar3 + 1 & 0xff;
          pbVar2 = param_2 + uVar3;
        } while (uVar3 < uVar6);
      }
      param_2[uVar6] = (&DAT_81c2b451)[uVar5 * 0x24] - 1;
      uVar6 = uVar6 + 1 & 0xff;
    }
LAB_81c12ae4:
    uVar5 = uVar5 + 1 & 0xff;
    if (0x25 < uVar5) {
      return uVar6;
    }
  } while( true );
}


#undef DAT_81c2b451

#define DAT_81c2b128 (*(uint *)(0x81c2b128u))
#define DAT_81c2b118 (*(char *)(0x81c2b118u))
#define DAT_81c2b17c (*(byte *)(0x81c2b17cu))
#define DAT_81c20570 (*(undefined *)(0x81c20570u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c12b18; body bytes 768 */

uint FUN_81c12b18(byte *param_1)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
#define local_28 (*(int *)(sg_stack + 0))
#define local_24 (*(int *)(sg_stack + 4))

  bool bVar1;
  bool bVar2;
  byte bVar3;
  byte *pbVar4;
  uint uVar5;
  short sVar6;
  byte bVar7;
  uint unaff_s4;

  bVar1 = true;
  bVar7 = 0;
  bVar2 = false;
  FUN_81c15210(0,0,0xef,0x13f,DAT_81c2b128);
LAB_81c12b64:
  if (!bVar1) goto LAB_81c12b8c;
LAB_81c12b6c:
  if (bVar2) goto LAB_81c12b8c;
  do {
    unaff_s4 = FUN_81c12e18(param_1,bVar7);
    bVar1 = false;
    bVar7 = 0;
LAB_81c12b8c:
    FUN_81c1408c(&local_28);
    if (local_28 == 5) {
      if (!bVar2) break;
    }
    else {
      if (local_28 != 0xb) goto LAB_81c12b64;
      if (!bVar2) {
        /* The input message retains full 16-bit x/y at bytes 8/10.
           Legacy coordinate globals truncate y to a byte above row 255. */
        enum SangoStatusbarAction action = sango_statusbar_hit(
            *(ushort *)(sg_stack + 8), *(ushort *)(sg_stack + 10));
        if (action == SANGO_STATUSBAR_INFO) {
          FUN_81c14dd8(&DAT_81c20570,2);
          FUN_81c13494();
        }
        if (action != SANGO_STATUSBAR_FIND) goto LAB_81c12b64;
        sVar6 = 0x13f;
        goto LAB_81c12c2c;
      }
    }
    bVar2 = false;
  } while( true );
  if (local_24 == 0x67) {
    bVar3 = param_1[3];
    if (bVar3 == 0) goto LAB_81c12b64;
    param_1[3] = bVar3 - 1;
    bVar7 = 1;
    if (param_1[1] <= (byte)(bVar3 - 1)) goto LAB_81c12d6c;
    param_1[1] = bVar3 - 1;
  }
  else {
    if (local_24 < 0x68) {
      if (local_24 == 0x1c) {
        if (unaff_s4 == 0) goto LAB_81c12b64;
        uVar5 = unaff_s4 - 1 & 0xff;
      }
      else {
        if (0x1c < local_24) {
          sVar6 = 0x13f;
          if (local_24 == 0x1f) {
LAB_81c12c2c:
            FUN_81c0ac48(0,0,0xef,sVar6,0,0);
            pbVar4 = (byte *)FUN_81c152f0(0x4b,'\x01',g_sango_package_data);
            bVar2 = true;
            /* The 9588 resource is 84x64, unlike the 9288S 160x160 map.
               Respect its descriptor rather than reading past the bitmap. */
            ushort map_width = (ushort)(pbVar4[0] | (pbVar4[1] << 8));
            ushort map_height = (ushort)(pbVar4[2] | (pbVar4[3] << 8));
            FUN_81c14fb8((240 - map_width) / 2,(320 - map_height) / 2,
                         map_width,map_height,0,pbVar4);
          }
          goto LAB_81c12b64;
        }
        uVar5 = 0xff;
        if (local_24 != 1) goto LAB_81c12b64;
      }
      return uVar5;
    }
    if (local_24 == 0x6a) {
      bVar3 = param_1[2];
      if (10 < bVar3) goto LAB_81c12b64;
      param_1[2] = bVar3 + 1;
      bVar7 = 4;
      if ((uint)(byte)(bVar3 + 1) < *param_1 + 7) goto LAB_81c12d6c;
      *param_1 = bVar3 - 5;
    }
    else if (local_24 < 0x6b) {
      if (local_24 != 0x69) goto LAB_81c12b64;
      bVar3 = param_1[2];
      if (bVar3 == 0) goto LAB_81c12b64;
      param_1[2] = bVar3 - 1;
      bVar7 = 2;
      if (*param_1 <= (byte)(bVar3 - 1)) goto LAB_81c12d6c;
      *param_1 = bVar3 - 1;
    }
    else {
      if (local_24 != 0x6c) goto LAB_81c12b64;
      bVar3 = param_1[3];
      if (7 < bVar3) goto LAB_81c12b64;
      param_1[3] = bVar3 + 1;
      bVar7 = 3;
      if ((uint)(byte)(bVar3 + 1) < param_1[1] + 7) goto LAB_81c12d6c;
      param_1[1] = bVar3 - 5;
    }
  }
  bVar7 = 0;
LAB_81c12d6c:
  bVar1 = true;
  goto LAB_81c12b6c;
}


#undef DAT_81c2b128
#undef DAT_81c2b118
#undef DAT_81c2b17c
#undef DAT_81c20570
#undef g_sango_package_data
#undef local_28
#undef local_24

#define DAT_81c2b128 (*(uint *)(0x81c2b128u))
#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c2b161 (*(byte *)(0x81c2b161u))
#define DAT_81c2b140 (*(ushort *)(0x81c2b140u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
#define DAT_81c2b170 (*(byte *)(0x81c2b170u))
#define DAT_81c2b410 (*(undefined1 *)(0x81c2b410u))
#define DAT_81c2b42d (*(undefined *)(0x81c2b42du))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c12e18; body bytes 1660 */

uint FUN_81c12e18(byte *param_1,byte param_2)

{
  int iVar1;
  byte *pbVar2;
  char *pcVar3;
  uint uVar4;
  short sVar5;
  uint uVar6;
  char *destination;
  byte bVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  char *source;

  iVar1 = FUN_81c152f0(2,'\x0e',g_sango_package_data);
  uVar9 = 0;
  uVar8 = (uint)param_1[1] * 0xc + (uint)*param_1;
  do {
    bbk_memcpy(&DAT_81c2b410 + uVar9 * 7,(void *)(iVar1 + uVar8),7);
    uVar9 = uVar9 + 1 & 0xff;
    uVar8 = uVar8 + 0xc & 0xffff;
  } while (uVar9 < 7);
  uVar8 = (uint)param_1[3] - (uint)param_1[1] & 0xff;
  uVar9 = (uint)param_1[2] - (uint)*param_1 & 0xff;
  iVar1 = FUN_81c152f0(0x36,'\x01',g_sango_package_data);
  if (param_2 == 0) {
    uVar10 = 0;
    do {
      uVar6 = 0;
      uVar4 = ((uVar10 + param_1[1]) * 0xc + (uint)*param_1) * 0x100;
      do {
        FUN_81c14504(uVar6 << 5,(short)(uVar10 << 5),0x20,0x20,iVar1 + 6 + (uVar4 & 0xffff),
                     DAT_81c2b128);
        uVar6 = uVar6 + 1 & 0xff;
        uVar4 = (uVar4 & 0xffff) + 0x100;
      } while (uVar6 < 7);
      uVar10 = uVar10 + 1 & 0xff;
    } while (uVar10 < 7);
    uVar10 = 0;
    do {
      uVar4 = 0;
      pbVar2 = &DAT_81c2b410 + uVar10 * 7;
      do {
        bVar7 = 8;
        if (*pbVar2 != 0) {
          if (((uint)(byte)(&DAT_81c2b42d)[(uint)*pbVar2 * 0x24] != DAT_81c2b115 + 1) &&
             (bVar7 = 7, (byte)(&DAT_81c2b42d)[(uint)*pbVar2 * 0x24] == 0)) {
            bVar7 = 0;
          }
          pbVar2 = (byte *)FUN_81c152f0(0x37,'\x01',g_sango_package_data);
          FUN_81c15070((short)uVar4 * 0x20 + 8,(short)uVar10 * 0x20 + 8,0x10,0x10,bVar7,pbVar2,
                       DAT_81c2b128);
        }
        uVar4 = uVar4 + 1 & 0xff;
        pbVar2 = &DAT_81c2b410 + uVar10 * 7 + uVar4;
      } while (uVar4 < 7);
      uVar10 = uVar10 + 1 & 0xff;
    } while (uVar10 < 7);
    goto LAB_81c1304c;
  }
  uVar10 = uVar8;
  if (param_2 == 2) {
    uVar4 = uVar9 + 1;
LAB_81c13484:
    uVar6 = uVar4 & 0xff;
  }
  else {
    uVar6 = uVar9;
    if (param_2 < 3) {
      uVar4 = uVar8 + 1;
      if (param_2 == 1) {
LAB_81c13468:
        uVar10 = uVar4 & 0xff;
      }
    }
    else {
      uVar4 = uVar8 - 1;
      if (param_2 == 3) goto LAB_81c13468;
      uVar4 = uVar9 - 1;
      if (param_2 == 4) goto LAB_81c13484;
    }
  }
  sVar5 = (short)uVar10 * 0x20;
  FUN_81c14504(uVar6 * 0x20,sVar5,0x20,0x20,
               iVar1 + 6 + (((uVar10 + param_1[1]) * 0xc + (uint)*param_1 + uVar6) * 0x100 & 0xffff)
               ,DAT_81c2b128);
  if ((byte)(&DAT_81c2b410)[uVar6 + uVar10 * 7] != 0) {
    bVar7 = 8;
    if (((uint)(byte)(&DAT_81c2b42d)[(uint)(byte)(&DAT_81c2b410)[uVar6 + uVar10 * 7] * 0x24] !=
         DAT_81c2b115 + 1) &&
       (bVar7 = 7,
       (byte)(&DAT_81c2b42d)[(uint)(byte)(&DAT_81c2b410)[uVar6 + uVar10 * 7] * 0x24] == 0)) {
      bVar7 = 0;
    }
    pbVar2 = (byte *)FUN_81c152f0(0x37,'\x01',g_sango_package_data);
    FUN_81c15070((short)(uVar6 * 0x20) + 8,sVar5 + 8,0x10,0x10,bVar7,pbVar2,DAT_81c2b128);
  }
LAB_81c1304c:
  iVar1 = FUN_81c152f0(0x38,'\x01',g_sango_package_data);
  FUN_81c14690(uVar9 * 0x20 + 8,(short)uVar8 * 0x20 + 0x10,0x10,0x10,iVar1 + 6,DAT_81c2b128);
  source = (char *)(g_scratch_buffer_4096 + 0x154);
  destination = (char *)(g_scratch_buffer_4096 + 300);
  FUN_81c15210(0,0xe0,0xef,0x13f,DAT_81c2b128);
  sango_statusbar_draw(DAT_81c2b128);
  pbVar2 = (byte *)FUN_81c152f0(DAT_81c2b161 + 0x2f,'\x01',g_sango_package_data);
  FUN_81c15070(0x15,0x10f,0x18,0x18,DAT_81c2b115,pbVar2,DAT_81c2b128);
  pbVar2 = (byte *)FUN_81c152f0(0x45,'\x01',g_sango_package_data);
  FUN_81c15070(0x35,0x10f,7,9,1,pbVar2,DAT_81c2b128);
  uVar10 = (uint)DAT_81c2b115;
  uVar4 = 0;
  uVar6 = 0;
  iVar1 = 0;
  do {
    pcVar3 = destination + uVar4;
    if ((uint)(byte)(&DAT_81c2b451)[(iVar1 + uVar6) * 4] == uVar10 + 1) {
      uVar4 = uVar4 + 1 & 0xff;
      *pcVar3 = (char)uVar6;
    }
    uVar6 = uVar6 + 1 & 0xff;
    iVar1 = uVar6 << 3;
  } while (uVar6 < 0x26);
  FUN_81c0a7e4(uVar4,destination,10);
  FUN_81c15134(0x3f,0x10e,destination,DAT_81c2b128);
  FUN_81c15070(0x35,0x11e,7,9,0,pbVar2,DAT_81c2b128);
  uVar10 = FUN_81c17b3c((uint)DAT_81c2b115);
  FUN_81c0a7e4(uVar10,destination,10);
  FUN_81c15134(0x3f,0x11c,destination,DAT_81c2b128);
  FUN_81c0a7e4((uint)DAT_81c2b140,destination,10);
  FUN_81c154d8(0x40,0x3f,source);
  bbk_strcat(destination,source);
  FUN_81c15134(0x52,0x10e,destination,DAT_81c2b128);
  FUN_81c0a7e4((uint)DAT_81c2b170,destination,10);
  FUN_81c154d8(0x40,0x40,source);
  bbk_strcat(destination,source);
  FUN_81c15134(0x52,0x11c,destination,DAT_81c2b128);
  bVar7 = (&DAT_81c2b410)[uVar9 + uVar8 * 7];
  if (bVar7 != 0) {
    FUN_81c1971c(bVar7 - 1,source);
    FUN_81c15134(0x78,0x115,source,DAT_81c2b128);
  }
  FUN_81c13494();
  return (uint)(byte)(&DAT_81c2b410)[uVar9 + uVar8 * 7];
}


#undef DAT_81c2b128
#undef DAT_81c2b115
#undef DAT_81c2b161
#undef DAT_81c2b140
#undef g_scratch_buffer_4096
#undef DAT_81c2b170
#undef DAT_81c2b410
#undef DAT_81c2b42d
#undef DAT_81c2b451
#undef g_sango_package_data

#define DAT_81c2b128 (*(uint *)(0x81c2b128u))
/* VA 0x81c13494; body bytes 36 */

void FUN_81c13494(void)

{
  FUN_81c14f98(DAT_81c2b128);
  return;
}


#undef DAT_81c2b128

#define DAT_81c2b310 (*(undefined1 *)(0x81c2b310u))
#define DAT_81c2b46e (*(undefined1 *)(0x81c2b46eu))
#define DAT_81c2b46f (*(undefined1 *)(0x81c2b46fu))
/* VA 0x81c134b8; body bytes 240 */

undefined4 FUN_81c134b8(uint param_1,byte param_2)

{
  undefined1 *puVar1;
  char cVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;

  uVar7 = param_1 & 0xff;
  uVar3 = 0;
  if ((uVar7 < 0x26) && (param_2 < 200)) {
    uVar6 = (uint)(byte)(&DAT_81c2b46e)[uVar7 * 0x24] + (uint)(byte)(&DAT_81c2b46f)[uVar7 * 0x24] &
            0xff;
    uVar5 = 199;
    if (uVar6 < 199) {
      do {
        puVar4 = &DAT_81c2b310 + uVar5;
        puVar1 = (undefined1 *)(uVar5 + 0x81c2b30f);
        uVar5 = uVar5 - 1 & 0xff;
        *puVar4 = *puVar1;
      } while (uVar6 < uVar5);
    }
    cVar2 = (&DAT_81c2b46f)[uVar7 * 0x24];
    (&DAT_81c2b310)[uVar6] = param_2;
    (&DAT_81c2b46f)[uVar7 * 0x24] = cVar2 + '\x01';
    while (uVar7 = uVar7 + 1 & 0xff, uVar7 < 0x26) {
      (&DAT_81c2b46e)[uVar7 * 0x24] = (&DAT_81c2b46e)[uVar7 * 0x24] + '\x01';
    }
    uVar3 = 1;
  }
  return uVar3;
}


#undef DAT_81c2b310
#undef DAT_81c2b46e
#undef DAT_81c2b46f

#define DAT_81c2b3e0 (*(undefined1 *)(0x81c2b3e0u))
#define DAT_81c2b470 (*(undefined1 *)(0x81c2b470u))
#define DAT_81c2b471 (*(undefined1 *)(0x81c2b471u))
/* VA 0x81c135a8; body bytes 240 */

undefined4 FUN_81c135a8(uint param_1,byte param_2)

{
  undefined1 *puVar1;
  char cVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;

  uVar7 = param_1 & 0xff;
  uVar3 = 0;
  if ((uVar7 < 0x26) && (param_2 < 0x21)) {
    uVar6 = (uint)(byte)(&DAT_81c2b470)[uVar7 * 0x24] + (uint)(byte)(&DAT_81c2b471)[uVar7 * 0x24] &
            0xff;
    uVar5 = 0x20;
    if (uVar6 < 0x20) {
      do {
        puVar4 = &DAT_81c2b3e0 + uVar5;
        puVar1 = (undefined1 *)(uVar5 + 0x81c2b3df);
        uVar5 = uVar5 - 1 & 0xff;
        *puVar4 = *puVar1;
      } while (uVar6 < uVar5);
    }
    cVar2 = (&DAT_81c2b471)[uVar7 * 0x24];
    (&DAT_81c2b3e0)[uVar6] = param_2;
    (&DAT_81c2b471)[uVar7 * 0x24] = cVar2 + '\x01';
    while (uVar7 = uVar7 + 1 & 0xff, uVar7 < 0x26) {
      (&DAT_81c2b470)[uVar7 * 0x24] = (&DAT_81c2b470)[uVar7 * 0x24] + '\x01';
    }
    uVar3 = 1;
  }
  return uVar3;
}


#undef DAT_81c2b3e0
#undef DAT_81c2b470
#undef DAT_81c2b471


/* VA 0x81c13698; body bytes 8 */

void FUN_81c13698(void)

{
  return;
}




#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c136a0; body bytes 244 */

uint FUN_81c136a0(uint param_1,byte param_2,byte param_3,uint param_4,byte param_5,byte param_6)

{
  unsigned char sg_stack[21] __attribute__((aligned(8)));
  (*(byte *)(sg_stack + 0)) = param_5;
  (*(byte *)(sg_stack + 4)) = param_6;
#define param_5 (*(byte *)(sg_stack + 0))
#define param_6 (*(byte *)(sg_stack + 4))

  char cVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  byte *pbVar6;

  iVar3 = FUN_81c152f0(0x3b,'\x01',g_sango_package_data);
  pbVar6 = (byte *)(iVar3 + (param_1 & 0xff) * 0x10);
  uVar5 = 0;
  pbVar4 = pbVar6;
  do {
    if ((uint)*pbVar4 == (param_4 & 0xff) + 1) {
      if (7 < uVar5) {
        return 0xff;
      }
      cVar1 = param_3 - param_6;
      if (param_3 < param_6) {
        cVar1 = param_6 - param_3;
      }
      if (param_2 < param_5) {
        bVar2 = (cVar1 + param_5) - param_2;
      }
      else {
        bVar2 = (cVar1 + param_2) - param_5;
      }
      return (uint)bVar2;
    }
    uVar5 = uVar5 + 1 & 0xff;
    pbVar4 = pbVar6 + uVar5;
  } while (uVar5 < 8);
  return 0xff;
}


#undef g_sango_package_data
#undef param_5
#undef param_6

#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
/* VA 0x81c13794; body bytes 92 */

uint FUN_81c13794(uint param_1,int param_2)

{
  undefined1 *puVar1;
  uint uVar2;
  uint uVar3;

  uVar3 = 0;
  uVar2 = 0;
  do {
    puVar1 = (undefined1 *)(param_2 + uVar3);
    if ((uint)(byte)(&DAT_81c2b451)[uVar2 * 0x24] == (param_1 & 0xff) + 1) {
      uVar3 = uVar3 + 1 & 0xff;
      *puVar1 = (char)uVar2;
    }
    uVar2 = uVar2 + 1 & 0xff;
  } while (uVar2 < 0x26);
  return uVar3;
}


#undef DAT_81c2b451

#define DAT_81c2b310 (*(undefined1 *)(0x81c2b310u))
#define DAT_81c2b46e (*(undefined1 *)(0x81c2b46eu))
#define DAT_81c2b46f (*(undefined1 *)(0x81c2b46fu))
/* VA 0x81c137f0; body bytes 128 */

uint FUN_81c137f0(char param_1)

{
  char *pcVar1;
  uint uVar2;
  byte bVar3;
  uint uVar4;

  uVar4 = 0;
  do {
    uVar2 = (uint)(byte)(&DAT_81c2b46e)[uVar4 * 0x24];
    bVar3 = 0;
    if ((&DAT_81c2b46f)[uVar4 * 0x24] != 0) {
      do {
        pcVar1 = &DAT_81c2b310 + uVar2;
        bVar3 = bVar3 + 1;
        uVar2 = uVar2 + 1 & 0xff;
        if (*pcVar1 == param_1) {
          return uVar4;
        }
      } while (bVar3 < (byte)(&DAT_81c2b46f)[uVar4 * 0x24]);
    }
    uVar4 = uVar4 + 1 & 0xff;
  } while (uVar4 < 0x26);
  return 0xff;
}


#undef DAT_81c2b310
#undef DAT_81c2b46e
#undef DAT_81c2b46f

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b310 (*(undefined1 *)(0x81c2b310u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define DAT_81c2b46e (*(undefined1 *)(0x81c2b46eu))
#define DAT_81c2b46f (*(undefined1 *)(0x81c2b46fu))
/* VA 0x81c13870; body bytes 168 */

uint FUN_81c13870(uint param_1,int param_2)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;

  iVar3 = (param_1 & 0xff) * 0x24;
  uVar5 = 0;
  uVar4 = 0;
  if ((&DAT_81c2b46f)[iVar3] != '\0') {
    do {
      iVar1 = uVar4 + (byte)(&DAT_81c2b46e)[iVar3];
      uVar4 = uVar4 + 1 & 0xff;
      pbVar2 = (byte *)(param_2 + uVar5);
      if (*(char *)((uint)(byte)(&DAT_81c2b310)[iVar1] * 0x10 + DAT_81c2b164 + 1) ==
          (&DAT_81c2b451)[iVar3]) {
        uVar5 = uVar5 + 1 & 0xff;
        *pbVar2 = (&DAT_81c2b310)[iVar1];
      }
    } while (uVar4 < (byte)(&DAT_81c2b46f)[iVar3]);
  }
  return uVar5;
}


#undef DAT_81c2b164
#undef DAT_81c2b310
#undef DAT_81c2b451
#undef DAT_81c2b46e
#undef DAT_81c2b46f

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b310 (*(undefined1 *)(0x81c2b310u))
#define DAT_81c2b46e (*(undefined1 *)(0x81c2b46eu))
#define DAT_81c2b46f (*(undefined1 *)(0x81c2b46fu))
/* VA 0x81c13918; body bytes 144 */

uint FUN_81c13918(uint param_1,int param_2)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;

  iVar2 = (param_1 & 0xff) * 0x24;
  uVar5 = 0;
  uVar4 = 0;
  if ((&DAT_81c2b46f)[iVar2] != '\0') {
    do {
      iVar1 = uVar4 + (byte)(&DAT_81c2b46e)[iVar2];
      uVar4 = uVar4 + 1 & 0xff;
      pbVar3 = (byte *)(param_2 + uVar5);
      if (*(char *)((uint)(byte)(&DAT_81c2b310)[iVar1] * 0x10 + DAT_81c2b164 + 1) == '\0') {
        uVar5 = uVar5 + 1 & 0xff;
        *pbVar3 = (&DAT_81c2b310)[iVar1];
      }
    } while (uVar4 < (byte)(&DAT_81c2b46f)[iVar2]);
  }
  return uVar5;
}


#undef DAT_81c2b164
#undef DAT_81c2b310
#undef DAT_81c2b46e
#undef DAT_81c2b46f

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b310 (*(undefined1 *)(0x81c2b310u))
#define DAT_81c2b46e (*(undefined1 *)(0x81c2b46eu))
#define DAT_81c2b46f (*(undefined1 *)(0x81c2b46fu))
/* VA 0x81c139a8; body bytes 152 */

uint FUN_81c139a8(uint param_1,int param_2)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;

  iVar2 = (param_1 & 0xff) * 0x24;
  uVar5 = 0;
  uVar4 = 0;
  if ((&DAT_81c2b46f)[iVar2] != '\0') {
    do {
      iVar1 = uVar4 + (byte)(&DAT_81c2b46e)[iVar2];
      uVar4 = uVar4 + 1 & 0xff;
      pbVar3 = (byte *)(param_2 + uVar5);
      if (*(char *)((uint)(byte)(&DAT_81c2b310)[iVar1] * 0x10 + DAT_81c2b164 + 1) == -1) {
        uVar5 = uVar5 + 1 & 0xff;
        *pbVar3 = (&DAT_81c2b310)[iVar1];
      }
    } while (uVar4 < (byte)(&DAT_81c2b46f)[iVar2]);
  }
  return uVar5;
}


#undef DAT_81c2b164
#undef DAT_81c2b310
#undef DAT_81c2b46e
#undef DAT_81c2b46f

#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define DAT_81c2b452 (*(undefined1 *)(0x81c2b452u))
/* VA 0x81c13a40; body bytes 120 */

uint FUN_81c13a40(uint param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  uint uVar6;

  uVar6 = 0;
  uVar3 = 0;
  do {
    iVar2 = uVar3 * 0x24;
    uVar4 = (uint)(byte)(&DAT_81c2b451)[iVar2];
    uVar3 = uVar3 + 1 & 0xff;
    if (uVar4 != 0) {
      bVar1 = (&DAT_81c2b452)[iVar2];
      if ((bVar1 != 0) && (uVar4 != (param_1 & 0xff) + 1)) {
        pcVar5 = (char *)(param_2 + uVar6);
        if (bVar1 != uVar4) {
          uVar6 = uVar6 + 1 & 0xff;
          *pcVar5 = bVar1 - 1;
        }
      }
    }
  } while (uVar3 < 0x26);
  return uVar6;
}


#undef DAT_81c2b451
#undef DAT_81c2b452

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b310 (*(undefined1 *)(0x81c2b310u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define DAT_81c2b46e (*(undefined1 *)(0x81c2b46eu))
#define DAT_81c2b46f (*(undefined1 *)(0x81c2b46fu))
/* VA 0x81c13ab8; body bytes 228 */

uint FUN_81c13ab8(uint param_1,int param_2)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;

  uVar7 = 0;
  uVar6 = 0;
  do {
    iVar3 = uVar6 * 0x24;
    if ((uint)(byte)(&DAT_81c2b451)[iVar3] == (param_1 & 0xff) + 1) {
      uVar5 = 0;
      uVar4 = 0;
      if ((&DAT_81c2b46f)[iVar3] != '\0') {
        do {
          iVar1 = uVar4 + (byte)(&DAT_81c2b46e)[iVar3];
          uVar4 = uVar4 + 1 & 0xff;
          pbVar2 = (byte *)(param_2 + uVar7 + uVar5);
          if (*(char *)((uint)(byte)(&DAT_81c2b310)[iVar1] * 0x10 + DAT_81c2b164 + 1) ==
              (&DAT_81c2b451)[iVar3]) {
            uVar5 = uVar5 + 1 & 0xff;
            *pbVar2 = (&DAT_81c2b310)[iVar1];
          }
        } while (uVar4 < (byte)(&DAT_81c2b46f)[iVar3]);
      }
      uVar7 = uVar7 + uVar5 & 0xff;
    }
    uVar6 = uVar6 + 1 & 0xff;
  } while (uVar6 < 0x26);
  return uVar7;
}


#undef DAT_81c2b164
#undef DAT_81c2b310
#undef DAT_81c2b451
#undef DAT_81c2b46e
#undef DAT_81c2b46f


/* VA 0x81c13b9c; body bytes 160 */

uint FUN_81c13b9c(uint value,uint mode)

{
  unsigned char sg_stack[40] __attribute__((aligned(8)));
#define acStack_28 (*(char (*)[24])(sg_stack + 0))

  uint uVar1;

  FUN_81c0ac48(0x53,0x8d,0x9b,0xb1,0,0);
  FUN_81c08e7c(0x52,0x8c,0x9c,0xb2,3,0,0);
  FUN_81c154d8(0x40,0x29,acStack_28);
  FUN_81c149dc(0x53,0x8d,acStack_28);
  uVar1 = FUN_81c1b364(value & 0xffff,mode & 0xffff);
  return uVar1;
}


#undef acStack_28


/* VA 0x81c13c3c; body bytes 160 */

uint FUN_81c13c3c(uint value,uint mode)

{
  unsigned char sg_stack[40] __attribute__((aligned(8)));
#define acStack_28 (*(char (*)[24])(sg_stack + 0))

  uint uVar1;

  FUN_81c0ac48(0x53,0x8d,0x9b,0xb1,0,0);
  FUN_81c08e7c(0x52,0x8c,0x9c,0xb2,3,0,0);
  FUN_81c154d8(0x40,0x2a,acStack_28);
  FUN_81c149dc(0x53,0x8d,acStack_28);
  uVar1 = FUN_81c1b364(value & 0xffff,mode & 0xffff);
  return uVar1;
}


#undef acStack_28


/* VA 0x81c13cdc; body bytes 160 */

uint FUN_81c13cdc(uint value,uint mode)

{
  unsigned char sg_stack[40] __attribute__((aligned(8)));
#define acStack_28 (*(char (*)[24])(sg_stack + 0))

  uint uVar1;

  FUN_81c0ac48(0x53,0x8d,0x9b,0xb1,0,0);
  FUN_81c08e7c(0x52,0x8c,0x9c,0xb2,3,0,0);
  FUN_81c154d8(0x40,0x2b,acStack_28);
  FUN_81c149dc(0x53,0x8d,acStack_28);
  uVar1 = FUN_81c1b364(value & 0xffff,mode & 0xffff);
  return uVar1;
}


#undef acStack_28

#define DAT_81c2b110 (*(undefined *)(0x81c2b110u))
#define _DAT_81c2b110 (*(u32 *)(0x81c2b110u))
#define DAT_81c2b174 (*(undefined2 *)(0x81c2b174u))
#define DAT_81c2b13d (*(undefined1 *)(0x81c2b13du))
#define DAT_81c2b18a (*(undefined2 *)(0x81c2b18au))
#define DAT_81c2b120 (*(undefined2 *)(0x81c2b120u))
#define DAT_81c2b186 (*(undefined2 *)(0x81c2b186u))
#define DAT_81c2b138 (*(void * *)(0x81c2b138u))
#define DAT_81c2b128 (*(void * *)(0x81c2b128u))
#define DAT_81c2b11c (*(void * *)(0x81c2b11cu))
#define s_font_bin_81c20590 (*(char (*)[1])(0x81c20590u))
#define DAT_81c2059c (*(undefined *)(0x81c2059cu))
#define DAT_81c205b8 (*(undefined *)(0x81c205b8u))
#define g_state_buffer_1200 (*(undefined4 *)(0x81c2b0e4u))
#define g_state_buffer_300 (*(undefined4 *)(0x81c2b0e8u))
#define g_state_buffer_30 (*(undefined4 *)(0x81c2b0ecu))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
#define g_sango_package_file (*(undefined4 *)(0x81c2b130u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c13d80; body bytes 484 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sango_load_package_and_buffers(void)

{
  unsigned char sg_stack[288] __attribute__((aligned(8)));
#define local_20 (*(ushort (*)[8])(sg_stack + 256))
#define acStack_120 (*(char (*)[256])(sg_stack + 0))

  uint size;
  uint uVar1;

  _DAT_81c2b110 = 1;
  FUN_81c0a8c8(1,500);
  crt_memset(acStack_120,0,0xfa);
  bbk_memcpy(acStack_120,s_font_bin_81c20590,10);
  crt_memset(acStack_120,0,0xfa);
  bbk_memcpy(acStack_120,&DAT_81c2059c,0xfa);
  g_sango_package_file = bbk_fopen(acStack_120,&DAT_81c205b8);
  uVar1 = 1;
  if (g_sango_package_file != 0) {
    bbk_fseek(g_sango_package_file,0,2);
    size = bbk_ftell(g_sango_package_file);
    g_sango_package_data = bbk_alloc(size);
    uVar1 = 1;
    if (g_sango_package_data != 0) {
      bbk_fseek(g_sango_package_file,0,0);
      bbk_fread(g_sango_package_data,size,1,g_sango_package_file);
      g_state_buffer_30 = bbk_alloc(0x1e);
      uVar1 = 1;
      if (g_state_buffer_30 != 0) {
        g_state_buffer_300 = bbk_alloc(300);
        uVar1 = 1;
        if (g_state_buffer_300 != 0) {
          g_state_buffer_1200 = bbk_alloc(0x4b0);
          uVar1 = 1;
          if (g_state_buffer_1200 != 0) {
            bbk_zero_time_stub(local_20);
            bbk_srand((uint)local_20[0]);
            DAT_81c2b174 = 0x140;
            DAT_81c2b13d = 1;
            DAT_81c2b18a = 0xef;
            DAT_81c2b120 = 0;
            DAT_81c2b186 = 0;
            DAT_81c2b138 = bbk_compatible_context_create();
            DAT_81c2b128 = bbk_compatible_context_create();
            DAT_81c2b11c = bbk_compatible_context_create();
            g_scratch_buffer_4096 = bbk_alloc(0x1000);
            uVar1 = (uint)(g_scratch_buffer_4096 == 0);
          }
        }
      }
    }
  }
  return uVar1;
}


#undef DAT_81c2b110
#undef _DAT_81c2b110
#undef DAT_81c2b174
#undef DAT_81c2b13d
#undef DAT_81c2b18a
#undef DAT_81c2b120
#undef DAT_81c2b186
#undef DAT_81c2b138
#undef DAT_81c2b128
#undef DAT_81c2b11c
#undef s_font_bin_81c20590
#undef DAT_81c2059c
#undef DAT_81c205b8
#undef g_state_buffer_1200
#undef g_state_buffer_300
#undef g_state_buffer_30
#undef g_scratch_buffer_4096
#undef g_sango_package_file
#undef g_sango_package_data
#undef local_20
#undef acStack_120

#define DAT_81c2b128 (*(void * *)(0x81c2b128u))
#define g_state_buffer_1200 (*(undefined4 *)(0x81c2b0e4u))
#define DAT_81c2b11c (*(void * *)(0x81c2b11cu))
#define g_state_buffer_300 (*(undefined4 *)(0x81c2b0e8u))
#define DAT_81c2b138 (*(void * *)(0x81c2b138u))
#define g_state_buffer_30 (*(undefined4 *)(0x81c2b0ecu))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
#define g_sango_package_file (*(undefined4 *)(0x81c2b130u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c13f64; body bytes 296 */

int sango_release_package_and_buffers(void)

{
  if (g_sango_package_data != 0) {
    bbk_free_if_nonnull(g_sango_package_data);
  }
  if (DAT_81c2b128 != 0) {
    bbk_compatible_context_free(DAT_81c2b128);
  }
  if (DAT_81c2b11c != 0) {
    bbk_compatible_context_free(DAT_81c2b11c);
  }
  if (DAT_81c2b138 != 0) {
    bbk_compatible_context_free(DAT_81c2b138);
  }
  if (g_scratch_buffer_4096 != 0) {
    bbk_free_if_nonnull(g_scratch_buffer_4096);
  }
  if (g_state_buffer_30 != 0) {
    bbk_free_if_nonnull(g_state_buffer_30);
  }
  if (g_state_buffer_300 != 0) {
    bbk_free_if_nonnull(g_state_buffer_300);
  }
  if (g_state_buffer_1200 != 0) {
    bbk_free_if_nonnull(g_state_buffer_1200);
  }
  FUN_81c0a904(1);
  bbk_fclose(g_sango_package_file);
  return 0;
}


#undef DAT_81c2b128
#undef g_state_buffer_1200
#undef DAT_81c2b11c
#undef g_state_buffer_300
#undef DAT_81c2b138
#undef g_state_buffer_30
#undef g_scratch_buffer_4096
#undef g_sango_package_file
#undef g_sango_package_data

#define DAT_81c2b9a8 (*(int *)(0x81c2b9a8u))
#define DAT_81c2b9ac (*(int *)(0x81c2b9acu))
#define DAT_81c2b9b0 (*(int *)(0x81c2b9b0u))
#define DAT_81c2b118 (*(undefined1 *)(0x81c2b118u))
#define DAT_81c2b17c (*(undefined1 *)(0x81c2b17cu))
/* VA 0x81c1408c; body bytes 216 */

undefined4 FUN_81c1408c(int *param_1)

{
  int iVar1;
  int iVar2;

  if (DAT_81c2b9a8 == 0) {
    do {
      while( true ) {
        FUN_81c0a5fc(param_1);
        iVar1 = *param_1;
        if (iVar1 == 0x10) {
          iVar2 = 5;
          goto LAB_81c14154;
        }
        if (0x10 < iVar1) break;
        if (iVar1 == 1) {
          *param_1 = 0xb;
          DAT_81c2b118 = (char)param_1[2];
          DAT_81c2b17c = (char)*(undefined2 *)((int)param_1 + 10);
          return 0;
        }
      }
      iVar2 = 6;
    } while (iVar1 != 0x144);
LAB_81c14154:
    *param_1 = iVar2;
  }
  else {
    *param_1 = DAT_81c2b9a8;
    param_1[1] = DAT_81c2b9ac;
    param_1[2] = DAT_81c2b9b0;
    DAT_81c2b9a8 = 0;
  }
  return 0;
}


#undef DAT_81c2b9a8
#undef DAT_81c2b9ac
#undef DAT_81c2b9b0
#undef DAT_81c2b118
#undef DAT_81c2b17c

#define DAT_81c2b110 (*(char *)(0x81c2b110u))
/* VA 0x81c14164; body bytes 260 */

uint FUN_81c14164(short param_1,char param_2)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
#define local_28 (*(uint *)(sg_stack + 0))
#define local_24 (*(uint *)(sg_stack + 4))

  char cVar1;
  short sVar2;

  cVar1 = DAT_81c2b110;
  FUN_81c0a904(1);
  if (param_1 == 0) {
    FUN_81c1408c((int *)&local_28);
  }
  else {
    FUN_81c0a8c8(1,1);
    while (param_1 != 0) {
      FUN_81c1408c((int *)&local_28);
      if (local_28 == 0xb) {
        if (cVar1 != '\0') {
          FUN_81c0a904(1);
          FUN_81c0a8c8(1,1);
          return local_28 & 0xff;
        }
        return 0xb;
      }
      sVar2 = param_1 + -1;
      if ((local_28 != 6) && (sVar2 = param_1, param_2 != '\0')) break;
      param_1 = sVar2;
      local_24 = 0;
    }
  }
  if (cVar1 != '\0') {
    FUN_81c0a904(1);
    FUN_81c0a8c8(1,1);
  }
  return local_24 & 0xff;
}


#undef DAT_81c2b110
#undef local_28
#undef local_24


/* VA 0x81c14268; body bytes 48 */

uint FUN_81c14268(void)

{
  unsigned char sg_stack[21] __attribute__((aligned(8)));
#define local_14 (*(byte *)(sg_stack + 4))
#define local_18 (*(int *)(sg_stack + 0))

  uint uVar1;

  FUN_81c1408c(&local_18);
  uVar1 = 0xff;
  if (local_18 == 5) {
    uVar1 = (uint)local_14;
  }
  return uVar1;
}


#undef local_14
#undef local_18


/* VA 0x81c14298; body bytes 8 */

void FUN_81c14298(void)

{
  return;
}





/* VA 0x81c142a0; body bytes 8 */

void FUN_81c142a0(void)

{
  return;
}




#define DAT_81c2b9a8 (*(undefined4 *)(0x81c2b9a8u))
#define DAT_81c2b9ac (*(undefined4 *)(0x81c2b9acu))
#define DAT_81c2b9b0 (*(undefined4 *)(0x81c2b9b0u))
/* VA 0x81c142a8; body bytes 40 */

undefined4 FUN_81c142a8(undefined4 *param_1)

{
  DAT_81c2b9a8 = *param_1;
  DAT_81c2b9ac = param_1[1];
  DAT_81c2b9b0 = param_1[2];
  return 0;
}


#undef DAT_81c2b9a8
#undef DAT_81c2b9ac
#undef DAT_81c2b9b0

#define DAT_81c2b138 (*(uint *)(0x81c2b138u))
/* VA 0x81c14350; body bytes 436 */

void FUN_81c14350(uint param_1,short param_2,uint param_3,uint param_4,int param_5)

{
  unsigned char sg_stack[20] __attribute__((aligned(8)));
  (*(int *)(sg_stack + 0)) = param_5;
#define param_5 (*(int *)(sg_stack + 0))

  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;

  uVar7 = param_1 & 0xffff;
  FUN_81c0a990(DAT_81c2b138,0);
  uVar2 = param_3 & 0xffff;
  /* Two-bit pixels occupy four pixels per byte, as in the image header's
     frame stride. Rounding to eight pixels overreads 84-pixel-wide maps. */
  if ((param_3 & 3) != 0) {
    uVar2 = (param_3 & 0xfffc) + 4;
  }
  iVar1 = uVar2 * (param_4 & 0xffff);
  if (iVar1 < 0) {
    iVar1 = iVar1 + 3;
  }
  uVar2 = iVar1 >> 2 & 0xffff;
  iVar1 = 0;
  if (uVar2 != 0) {
    uVar5 = uVar7;
    do {
      uVar6 = 6;
      do {
        uVar3 = (int)(uint)*(byte *)(param_5 + iVar1) >> (uVar6 & 0x1f) & 3;
        uVar4 = 3;
        if ((((uVar3 == 3) || (uVar4 = 2, uVar3 == 2)) || (uVar4 = 1, uVar3 == 1)) ||
           (uVar4 = 0, uVar3 == 0)) {
          FUN_81c0886c((short)uVar5,param_2,uVar4,DAT_81c2b138);
        }
        uVar5 = uVar5 + 1 & 0xffff;
        uVar6 = uVar6 - 2;
        if ((int)(uVar7 + (param_3 & 0xffff) + -1) < (int)uVar5) {
          param_2 = param_2 + 1;
          uVar5 = uVar7;
          break;
        }
      } while (-1 < (int)uVar6);
      iVar1 = iVar1 + 1;
    } while (iVar1 < (int)uVar2);
  }
  FUN_81c0a990(0,DAT_81c2b138);
  FUN_81c0aadc();
  return;
}


#undef DAT_81c2b138
#undef param_5


/* VA 0x81c14504; body bytes 396 */

void FUN_81c14504(uint param_1,short param_2,uint param_3,uint param_4,int param_5,uint param_6)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
  (*(int *)(sg_stack + 0)) = param_5;
  (*(uint *)(sg_stack + 4)) = param_6;
#define param_5 (*(int *)(sg_stack + 0))
#define param_6 (*(uint *)(sg_stack + 4))

  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;

  uVar7 = param_1 & 0xffff;
  uVar6 = param_3 & 0xffff;
  if ((param_3 & 3) != 0) {
    uVar6 = (param_3 & 0xfffc) + 4;
  }
  iVar1 = uVar6 * (param_4 & 0xffff);
  if (iVar1 < 0) {
    iVar1 = iVar1 + 3;
  }
  uVar6 = iVar1 >> 2 & 0xffff;
  iVar1 = 0;
  if (uVar6 != 0) {
    uVar4 = uVar7;
    do {
      uVar5 = 6;
      do {
        uVar2 = (int)(uint)*(byte *)(param_5 + iVar1) >> (uVar5 & 0x1f) & 3;
        uVar3 = 3;
        if ((((uVar2 == 3) || (uVar3 = 2, uVar2 == 2)) || (uVar3 = 1, uVar2 == 1)) ||
           (uVar3 = 0, uVar2 == 0)) {
          FUN_81c0886c((short)uVar4,param_2,uVar3,param_6);
        }
        uVar4 = uVar4 + 1 & 0xffff;
        uVar5 = uVar5 - 2;
        if ((int)(uVar7 + (param_3 & 0xffff) + -1) < (int)uVar4) {
          param_2 = param_2 + 1;
          uVar4 = uVar7;
          break;
        }
      } while (-1 < (int)uVar5);
      iVar1 = iVar1 + 1;
    } while (iVar1 < (int)uVar6);
  }
  return;
}


#undef param_5
#undef param_6


/* VA 0x81c14690; body bytes 424 */

void FUN_81c14690(uint param_1,short param_2,uint param_3,uint param_4,int param_5,uint param_6)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
  (*(int *)(sg_stack + 0)) = param_5;
  (*(uint *)(sg_stack + 4)) = param_6;
#define param_5 (*(int *)(sg_stack + 0))
#define param_6 (*(uint *)(sg_stack + 4))

  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;

  uVar6 = param_1 & 0xffff;
  uVar5 = param_3 & 0xffff;
  if ((param_3 & 3) != 0) {
    uVar5 = (param_3 & 0xfffc) + 4;
  }
  iVar1 = uVar5 * (param_4 & 0xffff);
  if (iVar1 < 0) {
    iVar1 = iVar1 + 3;
  }
  uVar5 = iVar1 >> 2 & 0xffff;
  iVar1 = 0;
  if (uVar5 != 0) {
    uVar3 = uVar6;
    do {
      uVar4 = 6;
      do {
        if (((int)(uint)*(byte *)(param_5 + iVar1) >> (uVar4 & 0x1f) & 1U) == 0) {
          uVar2 = (int)(uint)((byte *)(param_5 + iVar1))[uVar5] >> (uVar4 & 0x1f) & 3;
          if (uVar2 == 3) {
            uVar2 = 3;
          }
          else if (uVar2 == 2) {
            uVar2 = 2;
          }
          else if (uVar2 == 1) {
            uVar2 = 1;
          }
          else {
            if (uVar2 != 0) goto LAB_81c14764;
            uVar2 = 0;
          }
          FUN_81c0886c((short)uVar3,param_2,uVar2,param_6);
        }
LAB_81c14764:
        uVar3 = uVar3 + 1 & 0xffff;
        uVar4 = uVar4 - 2;
        if ((int)(uVar6 + (param_3 & 0xffff) + -1) < (int)uVar3) {
          param_2 = param_2 + 1;
          uVar3 = uVar6;
          break;
        }
      } while (-1 < (int)uVar4);
      iVar1 = iVar1 + 1;
    } while (iVar1 < (int)uVar5);
  }
  return;
}


#undef param_5
#undef param_6


/* VA 0x81c14838; body bytes 420 */

void FUN_81c14838(uint param_1,short param_2,uint param_3,uint param_4,int param_5)

{
  unsigned char sg_stack[20] __attribute__((aligned(8)));
  (*(int *)(sg_stack + 0)) = param_5;
#define param_5 (*(int *)(sg_stack + 0))

  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;

  uVar6 = param_1 & 0xffff;
  uVar5 = param_3 & 0xffff;
  if ((param_3 & 3) != 0) {
    uVar5 = (param_3 & 0xfffc) + 4;
  }
  iVar1 = uVar5 * (param_4 & 0xffff);
  if (iVar1 < 0) {
    iVar1 = iVar1 + 3;
  }
  uVar5 = iVar1 >> 2 & 0xffff;
  iVar1 = 0;
  if (uVar5 != 0) {
    uVar3 = uVar6;
    do {
      uVar4 = 6;
      do {
        if (((int)(uint)*(byte *)(param_5 + iVar1) >> (uVar4 & 0x1f) & 1U) == 0) {
          uVar2 = (int)(uint)((byte *)(param_5 + iVar1))[uVar5] >> (uVar4 & 0x1f) & 3;
          if (uVar2 == 3) {
            uVar2 = 3;
          }
          else if (uVar2 == 2) {
            uVar2 = 2;
          }
          else if (uVar2 == 1) {
            uVar2 = 1;
          }
          else {
            if (uVar2 != 0) goto LAB_81c14908;
            uVar2 = 0;
          }
          FUN_81c0886c((short)uVar3,param_2,uVar2,0);
        }
LAB_81c14908:
        uVar3 = uVar3 + 1 & 0xffff;
        uVar4 = uVar4 - 2;
        if ((int)(uVar6 + (param_3 & 0xffff) + -1) < (int)uVar3) {
          param_2 = param_2 + 1;
          uVar3 = uVar6;
          break;
        }
      } while (-1 < (int)uVar4);
      iVar1 = iVar1 + 1;
    } while (iVar1 < (int)uVar5);
  }
  return;
}


#undef param_5

#define DAT_81c2b120 (*(ushort *)(0x81c2b120u))
#define DAT_81c2b186 (*(ushort *)(0x81c2b186u))
#define DAT_81c2b18a (*(ushort *)(0x81c2b18au))
#define DAT_81c2b174 (*(ushort *)(0x81c2b174u))
#define DAT_81c2b13d (*(char *)(0x81c2b13du))
/* VA 0x81c149dc; body bytes 720 */

void FUN_81c149dc(ushort param_1,ushort param_2,char *param_3)

{
  unsigned char sg_stack[28] __attribute__((aligned(8)));
#define local_34 (*(int *)(sg_stack + 4))
#define local_30 (*(int *)(sg_stack + 8))

  uint uVar1;
  ushort uVar2;
  int iVar3;
  void *ptr;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  undefined1 *puVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  bool bVar11;
  int iVar12;
  int iVar13;

  uVar2 = DAT_81c2b174;
  uVar1 = (uint)param_2;
  uVar5 = (uint)param_1;
  if ((uint)param_1 < (uint)DAT_81c2b120) {
    uVar5 = (uint)DAT_81c2b120;
  }
  if (uVar1 < DAT_81c2b186) {
    param_2 = DAT_81c2b186;
  }
  uVar5 = (int)(DAT_81c2b18a - uVar5) / 6;
  local_30 = 0;
  local_34 = 0;
  iVar3 = FUN_81c1b9d4(param_3);
  if (uVar5 == 0) {
    trap(7);
  }
  uVar9 = iVar3 + iVar3 / (int)uVar5;
  if ((int)uVar9 < (int)uVar5) {
    uVar5 = uVar9;
  }
  ptr = bbk_alloc(uVar9 + 0x230);
  iVar3 = uVar5 + 1;
  FUN_81c0a7c8(ptr,0,uVar9 + 0x230);
  if (iVar3 == 0) {
    trap(7);
  }
  if (-1 < (int)uVar9 / iVar3) {
    iVar13 = 0;
    iVar12 = 0;
    do {
      bVar11 = false;
      iVar10 = iVar12 + uVar5;
      bbk_memcpy((void *)((int)ptr + iVar12),param_3 + local_30,uVar5);
      puVar7 = (undefined1 *)((int)ptr + iVar10);
      local_30 = local_30 + uVar5;
      if ((0x80 < (byte)puVar7[-1]) && (iVar8 = iVar10 + -1, iVar6 = iVar8, iVar12 <= iVar8)) {
        do {
          pcVar4 = (char *)((int)ptr + iVar6);
          iVar6 = iVar6 + -1;
          if (-1 < *pcVar4) break;
          bVar11 = (bool)(bVar11 ^ 1);
        } while (iVar12 <= iVar6);
        if (bVar11) {
          puVar7 = (undefined1 *)((int)ptr + iVar8);
          local_30 = local_30 + -1;
          iVar10 = iVar8;
        }
      }
      *puVar7 = 0;
      if (((int)(uVar9 - iVar12) < (int)uVar5) || ((int)((uint)uVar2 - (uint)param_2) <= iVar13))
      break;
      FUN_81c0974c(0,0);
      FUN_81c0addc(param_1,(short)((uVar1 + iVar13) * 0x10000 >> 0x10),(char *)((int)ptr + iVar12),0
                  );
      local_34 = local_34 + 1;
      iVar13 = iVar13 + 0xc;
      if (iVar3 == 0) {
        trap(7);
      }
      iVar12 = iVar10 + 1;
    } while (local_34 <= (int)uVar9 / iVar3);
  }
  if (DAT_81c2b13d != '\0') {
    DAT_81c2b18a = 0xef;
    DAT_81c2b174 = 0x140;
    DAT_81c2b120 = 0;
    DAT_81c2b186 = 0;
  }
  bbk_free_if_nonnull(ptr);
  return;
}


#undef DAT_81c2b120
#undef DAT_81c2b186
#undef DAT_81c2b18a
#undef DAT_81c2b174
#undef DAT_81c2b13d
#undef local_34
#undef local_30

#define DAT_81c2b178 (*(void * *)(0x81c2b178u))
/* VA 0x81c14cac; body bytes 236 */

void FUN_81c14cac(uint param_1,int param_2)

{
  unsigned char sg_stack[40] __attribute__((aligned(8)));
#define local_20 (*(byte (*)[24])(sg_stack + 0))

  byte bVar1;
  byte bVar2;
  byte bVar3;
  int offset;
  uint uVar4;
  byte *pbVar5;
  uint uVar6;

  if ((param_1 & 0xffff) >> 8 < 0xa1) {
    FUN_81c0a7c8((void *)param_2,0,0x18);
  }
  else {
    offset = FUN_81c14d98(param_1 & 0xffff);
    bbk_fseek(DAT_81c2b178,offset,0);
    bbk_fread(local_20,1,0x12,DAT_81c2b178);
    uVar6 = 0;
    do {
      uVar4 = uVar6 * 3 & 0xff;
      bVar1 = local_20[uVar4 + 2];
      bVar2 = local_20[uVar4 + 1];
      bVar3 = local_20[uVar4];
      uVar4 = uVar6 & 0x3f;
      uVar6 = uVar6 + 1 & 0xff;
      pbVar5 = (byte *)(param_2 + uVar4 * 4);
      pbVar5[3] = bVar1 << 4;
      *pbVar5 = bVar3;
      pbVar5[1] = bVar2 & 0xf0;
      pbVar5[2] = bVar2 * '\x10' + (char)((int)(bVar1 & 0xf0) >> 4);
    } while (uVar6 < 6);
  }
  return;
}


#undef DAT_81c2b178
#undef local_20


/* VA 0x81c14d98; body bytes 64 */

int FUN_81c14d98(uint param_1)

{
  return ((((param_1 & 0xffff) >> 8) - 0xa1) * 0x5e + (param_1 & 0xff) + -0xa1) * 0x12;
}




#define DAT_81c2b18a (*(short *)(0x81c2b18au))
#define DAT_81c2b120 (*(ushort *)(0x81c2b120u))
#define DAT_81c2b174 (*(short *)(0x81c2b174u))
#define DAT_81c2b186 (*(ushort *)(0x81c2b186u))
/* VA 0x81c14dd8; body bytes 448 */

/* WARNING: Removing unreachable block (ram,0x81c14e24) */

void FUN_81c14dd8(char *param_1,uint param_2)

{
  uint uVar1;

  DAT_81c2b18a = 0xeb;
  DAT_81c2b120 = 5;
  uVar1 = bbk_strlen(param_1);
  uVar1 = (uVar1 & 0xff) / 0x25 + 1;
  DAT_81c2b186 = (ushort)((int)(uVar1 * -0xc + 0x13f) >> 1);
  DAT_81c2b174 = DAT_81c2b186 + (short)uVar1 * 0xc;
  if (0x19 < uVar1) {
    DAT_81c2b174 = 0x13a;
    DAT_81c2b186 = 5;
  }
  FUN_81c0ac48(DAT_81c2b120 - 3,DAT_81c2b186 - 3,DAT_81c2b18a + 3,DAT_81c2b174 + 2,0,0);
  FUN_81c08e7c(DAT_81c2b120 - 3,DAT_81c2b186 - 3,DAT_81c2b18a + 3,DAT_81c2b174 + 2,3,0,0);
  FUN_81c149dc(DAT_81c2b120,DAT_81c2b186,param_1);
  if ((param_2 & 0xff) != 0) {
    FUN_81c14164((short)(param_2 & 0xff) * 0x28,'\x01');
  }
  return;
}


#undef DAT_81c2b18a
#undef DAT_81c2b120
#undef DAT_81c2b174
#undef DAT_81c2b186


/* VA 0x81c14f98; body bytes 32 */

void FUN_81c14f98(uint param_1)

{
  FUN_81c0a990(0,param_1);
  return;
}





/* VA 0x81c14fb8; body bytes 184 */

void FUN_81c14fb8(ushort param_1,short param_2,ushort param_3,ushort param_4,byte param_5,
                 byte *param_6)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
  (*(byte *)(sg_stack + 0)) = param_5;
  (*(byte * *)(sg_stack + 4)) = param_6;
#define param_5 (*(byte *)(sg_stack + 0))
#define param_6 (*(byte * *)(sg_stack + 4))

  if ((param_6[5] & 1) == 1) {
    FUN_81c14838((uint)param_1,param_2,(uint)param_3,(uint)param_4,
                 (int)(param_6 +
                      (((int)(((uint)param_6[1] * 0x100 + (uint)*param_6 & 0xffff) + 3) >> 2) *
                       ((uint)param_6[3] * 0x100 + (uint)param_6[2] & 0xffff) << (param_6[5] & 1)) *
                      (uint)param_5 + 6));
  }
  else {
    FUN_81c14350((uint)param_1,param_2,(uint)param_3,(uint)param_4,
                 (int)(param_6 +
                      (((int)(((uint)param_6[1] * 0x100 + (uint)*param_6 & 0xffff) + 3) >> 2) *
                       ((uint)param_6[3] * 0x100 + (uint)param_6[2] & 0xffff) << (param_6[5] & 1)) *
                      (uint)param_5 + 6));
  }
  return;
}


#undef param_5
#undef param_6


/* VA 0x81c15070; body bytes 196 */

void FUN_81c15070(ushort param_1,short param_2,ushort param_3,ushort param_4,byte param_5,
                 byte *param_6,uint param_7)

{
  unsigned char sg_stack[28] __attribute__((aligned(8)));
  (*(byte * *)(sg_stack + 4)) = param_6;
  (*(uint *)(sg_stack + 8)) = param_7;
  (*(byte *)(sg_stack + 0)) = param_5;
#define param_6 (*(byte * *)(sg_stack + 4))
#define param_7 (*(uint *)(sg_stack + 8))
#define param_5 (*(byte *)(sg_stack + 0))

  if ((param_6[5] & 1) == 1) {
    FUN_81c14690((uint)param_1,param_2,(uint)param_3,(uint)param_4,
                 (int)(param_6 +
                      (((int)(((uint)param_6[1] * 0x100 + (uint)*param_6 & 0xffff) + 3) >> 2) *
                       ((uint)param_6[3] * 0x100 + (uint)param_6[2] & 0xffff) << (param_6[5] & 1)) *
                      (uint)param_5 + 6),param_7);
  }
  else {
    FUN_81c14504((uint)param_1,param_2,(uint)param_3,(uint)param_4,
                 (int)(param_6 +
                      (((int)(((uint)param_6[1] * 0x100 + (uint)*param_6 & 0xffff) + 3) >> 2) *
                       ((uint)param_6[3] * 0x100 + (uint)param_6[2] & 0xffff) << (param_6[5] & 1)) *
                      (uint)param_5 + 6),param_7);
  }
  return;
}


#undef param_6
#undef param_7
#undef param_5


/* VA 0x81c15134; body bytes 116 */

void FUN_81c15134(short param_1,short param_2,char *param_3,uint param_4)

{
  FUN_81c0974c(0,param_4);
  FUN_81c0addc(param_1,param_2,param_3,param_4);
  return;
}




#define DAT_81c2b13d (*(char *)(0x81c2b13du))
#define DAT_81c2b18a (*(undefined2 *)(0x81c2b18au))
#define DAT_81c2b174 (*(undefined2 *)(0x81c2b174u))
#define DAT_81c2b120 (*(undefined2 *)(0x81c2b120u))
#define DAT_81c2b186 (*(undefined2 *)(0x81c2b186u))
/* VA 0x81c151a8; body bytes 60 */

void FUN_81c151a8(void)

{
  if (DAT_81c2b13d != '\0') {
    DAT_81c2b18a = 0xef;
    DAT_81c2b174 = 0x140;
    DAT_81c2b120 = 0;
    DAT_81c2b186 = 0;
  }
  return;
}


#undef DAT_81c2b13d
#undef DAT_81c2b18a
#undef DAT_81c2b174
#undef DAT_81c2b120
#undef DAT_81c2b186

#define DAT_81c2b158 (*(undefined4 *)(0x81c2b158u))
/* VA 0x81c151e4; body bytes 44 */

void FUN_81c151e4(byte param_1,byte param_2,byte param_3)

{
  DAT_81c2b158 = 0;
  FUN_81c149dc((ushort)param_1,(ushort)param_2,(char *)(uint)param_3);
  return;
}


#undef DAT_81c2b158


/* VA 0x81c15210; body bytes 68 */

void FUN_81c15210(short param_1,short param_2,short param_3,short param_4,uint param_5)

{
  unsigned char sg_stack[20] __attribute__((aligned(8)));
  (*(uint *)(sg_stack + 0)) = param_5;
#define param_5 (*(uint *)(sg_stack + 0))

  FUN_81c08100(param_1,param_2,param_3,param_4,0,param_5);
  return;
}


#undef param_5


/* VA 0x81c152a4; body bytes 64 */

int FUN_81c152a4(int param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;

  uVar2 = (param_3 - param_1) + 1;
  uVar1 = (param_3 - param_1) + 4;
  if (-1 < (int)uVar2) {
    uVar1 = uVar2;
  }
  iVar3 = (int)uVar1 >> 2;
  if ((uVar2 & 3) != 0) {
    iVar3 = iVar3 + 1;
  }
  return (param_4 - param_2) * iVar3 + iVar3;
}





/* VA 0x81c152f0; body bytes 232 */

int FUN_81c152f0(uint param_1,char param_2,int param_3)

{
  unsigned char sg_stack[27] __attribute__((aligned(8)));
#define local_1a (*(ushort *)(sg_stack + 6))
#define local_18 (*(ushort *)(sg_stack + 8))
#define local_16 (*(char *)(sg_stack + 10))
#define auStack_20 (*(undefined1 (*)[6])(sg_stack + 0))

  int iVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  void *src;

  iVar3 = 0;
  if (param_2 != '\0') {
    uVar4 = (byte)param_2 - 1 & 0xff;
    iVar1 = FUN_81c153d8(param_1 & 0xffff);
    iVar3 = 0;
    if (iVar1 != 0) {
      src = (void *)(param_3 + iVar1);
      FUN_81c16de8(src,iVar1);
      bbk_memcpy(auStack_20,src,0xc);
      if ((local_1a < uVar4) || (local_16 != '\0')) {
        iVar3 = 0;
      }
      else if (local_18 == 0) {
        if (local_1a == 1) {
          iVar3 = (int)src + 0xc;
        }
        else {
          pbVar2 = (byte *)((int)src + uVar4 * 4 + 0xc);
          iVar3 = (int)src + ((uint)pbVar2[1] * 0x100 + (uint)*pbVar2 & 0xffff);
        }
      }
      else {
        iVar3 = (int)src + uVar4 * local_18 + 0xc;
      }
    }
  }
  return iVar3;
}


#undef local_1a
#undef local_18
#undef local_16
#undef auStack_20

#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c153d8; body bytes 80 */

int FUN_81c153d8(uint param_1)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
#define local_10 (*(int (*)[2])(sg_stack + 0))

  int iVar1;

  iVar1 = ((param_1 & 0xffff) - 1) * 4;
  local_10[0] = 0;
  if ((param_1 & 0xffff) != 0) {
    local_10[0] = iVar1;
    bbk_memcpy(local_10,(void *)(g_sango_package_data + iVar1),4);
  }
  return local_10[0];
}


#undef g_sango_package_data
#undef local_10

#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c15428; body bytes 176 */

uint FUN_81c15428(ushort param_1,uint param_2)

{
  unsigned char sg_stack[34] __attribute__((aligned(8)));
#define auStack_20 (*(undefined1 (*)[8])(sg_stack + 8))
#define local_28 (*(undefined1 (*)[2])(sg_stack + 0))
#define local_26 (*(ushort *)(sg_stack + 2))
#define local_18 (*(ushort *)(sg_stack + 16))

  int iVar1;
  uint uVar2;

  iVar1 = FUN_81c153d8((uint)param_1);
  uVar2 = 0;
  if (iVar1 != 0) {
    bbk_memcpy(auStack_20,(void *)(g_sango_package_data + iVar1),0xc);
    if (local_18 == 0) {
      bbk_memcpy(local_28,(void *)(g_sango_package_data + iVar1 + ((param_2 & 0xff) - 1) * 4 + 0xc),
                 4);
      uVar2 = (uint)local_26;
    }
    else {
      uVar2 = (uint)local_18;
    }
  }
  return uVar2;
}


#undef g_sango_package_data
#undef auStack_20
#undef local_28
#undef local_26
#undef local_18

#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c154d8; body bytes 268 */

undefined4 FUN_81c154d8(ushort param_1,uint param_2,void *param_3)

{
  unsigned char sg_stack[35] __attribute__((aligned(8)));
#define auStack_20 (*(undefined1 (*)[8])(sg_stack + 8))
#define local_28 (*(ushort *)(sg_stack + 0))
#define local_26 (*(ushort *)(sg_stack + 2))
#define local_18 (*(ushort *)(sg_stack + 16))
#define local_16 (*(char *)(sg_stack + 18))

  int iVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  uint size;

  iVar1 = FUN_81c153d8((uint)param_1);
  uVar2 = 1;
  if (iVar1 != 0) {
    bbk_memcpy(auStack_20,(void *)(g_sango_package_data + iVar1),0xc);
    iVar3 = (param_2 & 0xff) - 1;
    if (local_18 == 0) {
      bbk_memcpy(&local_28,(void *)(g_sango_package_data + iVar1 + iVar3 * 4 + 0xc),4);
    }
    else {
      local_26 = local_18;
      local_28 = (short)iVar3 * local_18 + 0xc;
    }
    size = (uint)local_26;
    bbk_memcpy(param_3,(void *)(g_sango_package_data + iVar1 + (uint)local_28),size);
    *(undefined1 *)((int)param_3 + size) = 0;
    if ((local_16 != '\0') && (uVar5 = 0, size != 0)) {
      do {
        pcVar4 = (char *)((int)param_3 + uVar5);
        uVar5 = uVar5 + 1 & 0xffff;
        *pcVar4 = *pcVar4 - local_16;
      } while (uVar5 < size);
    }
    uVar2 = 0;
  }
  return uVar2;
}


#undef g_sango_package_data
#undef auStack_20
#undef local_28
#undef local_26
#undef local_18
#undef local_16


/* VA 0x81c155e4; body bytes 60 */

void FUN_81c155e4(int param_1,char param_2,uint param_3)

{
  char *pcVar1;
  uint uVar2;

  uVar2 = 0;
  if ((param_3 & 0xffff) != 0) {
    do {
      pcVar1 = (char *)(param_1 + uVar2);
      uVar2 = uVar2 + 1 & 0xffff;
      *pcVar1 = *pcVar1 - param_2;
    } while (uVar2 < (param_3 & 0xffff));
  }
  return;
}




#define s_0123456789ABCDEF_81c205c0 (*(char (*)[1])(0x81c205c0u))
/* VA 0x81c156e0; body bytes 340 */

void FUN_81c156e0(ushort param_1,ushort param_2,int param_3,byte param_4,char param_5)

{
  unsigned char sg_stack[137] __attribute__((aligned(8)));
  (*(char *)(sg_stack + 120)) = param_5;
#define acStack_48 (*(char (*)[40])(sg_stack + 32))
#define abStack_61 (*(byte (*)[25])(sg_stack + 7))
#define param_5 (*(char *)(sg_stack + 120))

  byte bVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;

  if ((param_5 == '\x01') && (param_3 < 0)) {
    FUN_81c151e4((byte)param_1,(byte)param_2,0x2d);
    param_1 = param_1 + 8;
    param_3 = -param_3;
  }
  if (param_4 == 0) {
    trap(7);
  }
  uVar4 = 0;
  while( true ) {
    iVar2 = param_3 / (int)(uint)param_4;
    if (iVar2 == 0) break;
    abStack_61[uVar4 + 1] = (byte)param_3 - (char)iVar2 * param_4;
    uVar4 = uVar4 + 1 & 0xffff;
    param_3 = iVar2;
    if (param_4 == 0) {
      trap(7);
    }
  }
  uVar5 = uVar4 + 1 & 0xffff;
  abStack_61[uVar4 + 1] = (byte)param_3;
  uVar4 = 0;
  if (uVar5 != 0) {
    pbVar3 = abStack_61 + uVar5;
    do {
      bVar1 = *pbVar3;
      uVar4 = uVar4 + 1;
      pbVar3 = pbVar3 + -1;
      FUN_81c0a7e4((uint)(byte)s_0123456789ABCDEF_81c205c0[bVar1],acStack_48,10);
      FUN_81c0addc(param_1,param_2,acStack_48,0);
      param_1 = param_1 + 8;
    } while (uVar4 < uVar5);
  }
  return;
}


#undef s_0123456789ABCDEF_81c205c0
#undef acStack_48
#undef abStack_61
#undef param_5


/* VA 0x81c15834; body bytes 156 */

void FUN_81c15834(int param_1)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
#define local_20 (*(int *)(sg_stack + 0))
#define local_1c (*(int *)(sg_stack + 4))

  byte bVar1;

  bVar1 = 0;
  do {
    FUN_81c151e4(bVar1 << 3,0,0x20);
    bVar1 = bVar1 + 1;
  } while (bVar1 < 8);
  FUN_81c156e0(0,0,param_1,0x10,'\0');
  do {
    do {
      FUN_81c1408c(&local_20);
    } while (local_20 != 5);
  } while ((local_1c != 0x1c) && (local_1c != 1));
  return;
}


#undef local_20
#undef local_1c

#define DAT_81c2b12c (*(undefined1 *)(0x81c2b12cu))
#define DAT_81c2b16c (*(void * *)(0x81c2b16cu))
#define DAT_81c2b14c (*(void * *)(0x81c2b14cu))
#define DAT_81c2b15c (*(void * *)(0x81c2b15cu))
#define DAT_81c2b164 (*(void * *)(0x81c2b164u))
#define DAT_81c2b193 (*(undefined1 *)(0x81c2b193u))
#define DAT_81c2b171 (*(undefined1 *)(0x81c2b171u))
#define DAT_81c2b144 (*(undefined4 *)(0x81c2b144u))
#define DAT_81c2b180 (*(undefined4 *)(0x81c2b180u))
#define DAT_81c2b118 (*(undefined1 *)(0x81c2b118u))
#define DAT_81c2b17c (*(undefined1 *)(0x81c2b17cu))
#define DAT_81c2b115 (*(undefined1 *)(0x81c2b115u))
#define DAT_81c2b190 (*(undefined1 *)(0x81c2b190u))
#define DAT_81c2b191 (*(undefined1 *)(0x81c2b191u))
#define DAT_81c2b192 (*(undefined1 *)(0x81c2b192u))
#define DAT_81c2b140 (*(undefined2 *)(0x81c2b140u))
#define DAT_81c2b170 (*(undefined1 *)(0x81c2b170u))
#define g_state_buffer_1200 (*(undefined4 *)(0x81c2b0e4u))
#define DAT_81c2b114 (*(undefined1 *)(0x81c2b114u))
#define DAT_81c2b194 (*(undefined1 *)(0x81c2b194u))
#define g_state_buffer_30 (*(undefined4 *)(0x81c2b0ecu))
/* VA 0x81c159a0; body bytes 300 */

int sango_allocate_session_state(void)

{
  int iVar1;

  DAT_81c2b12c = 0;
  FUN_81c0a7c8(g_state_buffer_30,0,0x1e);
  FUN_81c0a7c8(g_state_buffer_1200,0x4b0,0xff);
  DAT_81c2b16c = bbk_alloc(0xe1);
  iVar1 = 1;
  if (DAT_81c2b16c != 0) {
    DAT_81c2b14c = bbk_alloc(0xfa);
    iVar1 = 1;
    if (DAT_81c2b14c != 0) {
      DAT_81c2b15c = bbk_alloc(0x56);
      iVar1 = 1;
      if (DAT_81c2b15c != 0) {
        DAT_81c2b164 = bbk_alloc(0xc84);
        iVar1 = 1;
        if (DAT_81c2b164 != 0) {
          DAT_81c2b193 = 0;
          DAT_81c2b171 = 1;
          DAT_81c2b144 = 0;
          DAT_81c2b180 = 0;
          DAT_81c2b118 = 0;
          DAT_81c2b17c = 0;
          DAT_81c2b115 = 0;
          DAT_81c2b190 = 0;
          DAT_81c2b191 = 0;
          DAT_81c2b192 = 0;
          DAT_81c2b140 = 0;
          DAT_81c2b170 = 1;
          DAT_81c2b114 = 1;
          DAT_81c2b194 = 1;
          iVar1 = 0;
        }
      }
    }
  }
  return iVar1;
}


#undef DAT_81c2b12c
#undef DAT_81c2b16c
#undef DAT_81c2b14c
#undef DAT_81c2b15c
#undef DAT_81c2b164
#undef DAT_81c2b193
#undef DAT_81c2b171
#undef DAT_81c2b144
#undef DAT_81c2b180
#undef DAT_81c2b118
#undef DAT_81c2b17c
#undef DAT_81c2b115
#undef DAT_81c2b190
#undef DAT_81c2b191
#undef DAT_81c2b192
#undef DAT_81c2b140
#undef DAT_81c2b170
#undef g_state_buffer_1200
#undef DAT_81c2b114
#undef DAT_81c2b194
#undef g_state_buffer_30

#define DAT_81c2b15c (*(uchar * *)(0x81c2b15cu))
#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c2b192 (*(byte *)(0x81c2b192u))
#define DAT_81c2b193 (*(byte *)(0x81c2b193u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
#define DAT_81c2b190 (*(char *)(0x81c2b190u))
#define DAT_81c2b191 (*(char *)(0x81c2b191u))
#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define DAT_81c2b46a (*(undefined2 *)(0x81c2b46au))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c15acc; body bytes 588 */

int sango_select_session(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;

  do {
    while( true ) {
      while( true ) {
        while( true ) {
          uVar2 = FUN_81c15d18(0x2c,100);
          if (uVar2 != 2) break;
          FUN_81c15e44();
        }
        if ((int)uVar2 < 3) break;
        if ((uVar2 == 3) || (uVar2 == 0xff)) {
          return 0;
        }
      }
      if (uVar2 != 0) break;
      uVar2 = FUN_81c15d18(0x2d,0x68);
      if (uVar2 != 0xff) {
        uVar2 = FUN_81c1b91c((char)uVar2 + '\x01',DAT_81c2b15c);
        uVar2 = FUN_81c15e6c(uVar2);
        if (uVar2 != 0xff) {
          DAT_81c2b115 = (byte)uVar2;
          uVar2 = FUN_81c137f0(DAT_81c2b115);
          iVar3 = FUN_81c152f0(2,'\x06',g_sango_package_data);
          iVar1 = g_scratch_buffer_4096;
          pbVar4 = (byte *)(iVar3 + uVar2 * 2);
          DAT_81c2b192 = *pbVar4;
          DAT_81c2b193 = pbVar4[1];
          if (DAT_81c2b192 + 3 < 0xc) {
            DAT_81c2b190 = DAT_81c2b192 - 3;
            if (DAT_81c2b192 < 3) {
              DAT_81c2b190 = '\0';
            }
          }
          else {
            DAT_81c2b190 = '\x05';
          }
          if (DAT_81c2b193 + 3 < 9) {
            DAT_81c2b191 = DAT_81c2b193 - 3;
            if (DAT_81c2b193 < 3) {
              DAT_81c2b191 = '\0';
            }
          }
          else {
            DAT_81c2b191 = '\x02';
          }
          uVar2 = 0;
          do {
            if ((uint)(byte)(&DAT_81c2b451)[uVar2 * 0x24] != DAT_81c2b115 + 1) {
              uVar5 = FUN_81c13870(uVar2,iVar1);
              iVar3 = DAT_81c2b164;
              uVar6 = 0;
              if (uVar5 != 0) {
                do {
                  pbVar4 = (byte *)(iVar1 + uVar6);
                  uVar6 = uVar6 + 1 & 0xff;
                  *(undefined2 *)((uint)*pbVar4 * 0x10 + iVar3 + 10) = 800;
                } while (uVar6 < uVar5);
              }
              (&DAT_81c2b46a)[uVar2 * 0x12] = (&DAT_81c2b46a)[uVar2 * 0x12] + 1000;
            }
            uVar2 = uVar2 + 1 & 0xff;
          } while (uVar2 < 0x26);
          return 1;
        }
      }
    }
  } while ((uVar2 != 1) || (uVar2 = FUN_81c16330('\x01'), uVar2 == 0xff));
  return 1;
}


#undef DAT_81c2b15c
#undef DAT_81c2b115
#undef DAT_81c2b192
#undef DAT_81c2b193
#undef g_scratch_buffer_4096
#undef DAT_81c2b190
#undef DAT_81c2b191
#undef DAT_81c2b164
#undef DAT_81c2b451
#undef DAT_81c2b46a
#undef g_sango_package_data


/* VA 0x81c15d18; body bytes 300 */

uint FUN_81c15d18(ushort param_1,short param_2)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
#define local_28 (*(int *)(sg_stack + 0))
#define local_24 (*(uint *)(sg_stack + 4))

  uint uVar1;
  uint uVar2;

  uVar2 = 0;
  FUN_81c077bc((uint)param_1,1,0,0,'\0');
LAB_81c15d5c:
  FUN_81c0a5fc(&local_28);
  do {
    if (local_28 == 5) {
      if (local_24 == 0x67) {
LAB_81c15e28:
        uVar1 = uVar2 - 1;
LAB_81c15e2c:
        uVar2 = uVar1 & 0xff;
      }
      else if ((int)local_24 < 0x68) {
        uVar1 = 0xff;
        if ((local_24 == 1) || (uVar1 = uVar2, local_24 == 0x1c)) {
          return uVar1;
        }
      }
      else {
        uVar1 = uVar2 + 1;
        if (local_24 == 0x6a) goto LAB_81c15e2c;
        if ((int)local_24 < 0x6b) {
          if (local_24 == 0x69) goto LAB_81c15e28;
        }
        else if (local_24 == 0x6c) {
          uVar2 = uVar2 + 1;
        }
      }
      uVar2 = uVar2 & 3;
      FUN_81c077bc((uint)param_1,1,0,0,'\0');
    }
    uVar1 = FUN_81c162e0(param_2 + (short)uVar2);
    if (uVar1 == 0xff) goto LAB_81c15d5c;
    local_28 = 5;
    local_24 = uVar1;
  } while( true );
}


#undef local_28
#undef local_24


/* VA 0x81c15e44; body bytes 40 */
#define credits_draw_target (*(uint *)(0x81c2b128u))

void FUN_81c15e44(void)

{
  sango_credits_draw(credits_draw_target);
  FUN_81c14164(5000,'\x01');
  return;
}

#undef credits_draw_target



#define DAT_81c2b15c (*(byte * *)(0x81c2b15cu))
#define DAT_81c2b14c (*(char * *)(0x81c2b14cu))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c15e6c; body bytes 856 */

uint FUN_81c15e6c(uint param_1)

{
  unsigned char sg_stack[64] __attribute__((aligned(8)));
#define abStack_60 (*(byte (*)[40])(sg_stack + 0))
#define local_38 (*(int *)(sg_stack + 40))
#define local_34 (*(int *)(sg_stack + 44))

  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;

  uVar8 = param_1 & 0xff;
  uVar6 = 0;
  FUN_81c0ac48(0,0,0xef,0x13f,0,0);
  if (uVar8 != 0) {
    do {
      uVar4 = uVar6 * 6 & 0xff;
      sango_load_named_text(DAT_81c2b15c[uVar6],DAT_81c2b14c + uVar4);
      uVar3 = FUN_81c1b9d4(DAT_81c2b14c);
      uVar3 = uVar3 & 0xff;
      if (uVar3 < uVar4 + 6) {
        FUN_81c0a7c8(DAT_81c2b14c + uVar3,0x20,(uVar4 - uVar3) + 6);
      }
      uVar6 = uVar6 + 1 & 0xff;
    } while (uVar6 < uVar8);
  }
  FUN_81c08e7c(0,0,0xef,0x13f,3,0,0);
  FUN_81c154d8(1,0x2d,abStack_60);
  FUN_81c149dc(0x48,4,(char *)abStack_60);
  FUN_81c077bc(0x2f,1,0x3c,0x14,'\x01');
  FUN_81c08e7c(0xd,10,0x36,0x13b,3,0,0);
  iVar2 = FUN_81c152f0(2,'\x06',g_sango_package_data);
  FUN_81c16274(0);
  FUN_81c0aae4(0x10,0xd,0x34,0x19,0);
  uVar3 = 0;
  uVar7 = 0;
  bVar1 = false;
  uVar6 = FUN_81c13794((uint)*DAT_81c2b15c,(int)abStack_60);
  uVar4 = 0xd;
  iVar5 = 0x19;
  do {
    while (FUN_81c1408c(&local_38), local_38 != 5) {
      bVar1 = (bool)(bVar1 ^ 1);
      FUN_81c161c4(uVar6,abStack_60,iVar2);
    }
    FUN_81c0aae4(0x10,(short)uVar4,0x34,(short)iVar5,0);
    if (bVar1) {
      FUN_81c161c4(uVar6,abStack_60,iVar2);
      bVar1 = false;
    }
    if (local_34 == 0x1c) {
      return (uint)DAT_81c2b15c[uVar7];
    }
    if (local_34 < 0x1d) {
      iVar5 = uVar7 - uVar3;
      if (local_34 == 1) {
        return 0xff;
      }
    }
    else if (local_34 == 0x67) {
      iVar5 = -uVar3;
      if (uVar7 != 0) {
        if (uVar7 == uVar3) {
          uVar3 = uVar7 - 1 & 0xff;
        }
        uVar7 = uVar7 - 1 & 0xff;
LAB_81c160e8:
        iVar5 = uVar7 - uVar3;
      }
    }
    else {
      iVar5 = uVar7 - uVar3;
      if ((local_34 == 0x6c) && ((int)uVar7 < (int)(uVar8 - 1))) {
        uVar7 = uVar7 + 1 & 0xff;
        iVar5 = uVar7 - uVar3;
        if (0x18 < iVar5) {
          uVar3 = uVar3 + 1 & 0xff;
          goto LAB_81c160e8;
        }
      }
    }
    FUN_81c16274(uVar3);
    uVar4 = iVar5 * 0xc + 0xdU & 0xff;
    iVar5 = uVar4 + 0xc;
    FUN_81c0aae4(0x10,(short)uVar4,0x34,(short)iVar5,0);
    uVar6 = FUN_81c13794((uint)DAT_81c2b15c[uVar7],(int)abStack_60);
  } while( true );
}


#undef DAT_81c2b15c
#undef DAT_81c2b14c
#undef g_sango_package_data
#undef abStack_60
#undef local_38
#undef local_34


/* VA 0x81c161c4; body bytes 176 */

void FUN_81c161c4(uint param_1,byte *param_2,int param_3)

{
  ushort uVar1;
  ushort uVar2;
  byte *pbVar3;
  uint uVar4;

  uVar4 = 0;
  pbVar3 = param_2;
  if ((param_1 & 0xff) != 0) {
    do {
      pbVar3 = (byte *)(param_3 + (*pbVar3 & 0x7f) * 2);
      uVar1 = (ushort)*pbVar3 * 7 + 0x3f & 0xff;
      uVar2 = (ushort)pbVar3[1] * 7 + 0x17 & 0xff;
      FUN_81c0aae4(uVar1,uVar2,uVar1 + 1,uVar2 + 1,0);
      uVar4 = uVar4 + 1 & 0xff;
      pbVar3 = param_2 + uVar4;
    } while (uVar4 < (param_1 & 0xff));
  }
  return;
}




#define DAT_81c2b14c (*(int *)(0x81c2b14cu))
#define DAT_81c2b120 (*(undefined2 *)(0x81c2b120u))
#define DAT_81c2b18a (*(undefined2 *)(0x81c2b18au))
#define DAT_81c2b186 (*(undefined2 *)(0x81c2b186u))
#define DAT_81c2b174 (*(undefined2 *)(0x81c2b174u))
/* VA 0x81c16274; body bytes 108 */

void FUN_81c16274(uint param_1)

{
  DAT_81c2b120 = 0x10;
  DAT_81c2b18a = 0x34;
  DAT_81c2b186 = 0xd;
  DAT_81c2b174 = 0x139;
  FUN_81c149dc(0x10,0xd,(char *)(DAT_81c2b14c + (param_1 & 0xff) * 6));
  return;
}


#undef DAT_81c2b14c
#undef DAT_81c2b120
#undef DAT_81c2b18a
#undef DAT_81c2b186
#undef DAT_81c2b174

#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c162e0; body bytes 80 */

uint FUN_81c162e0(ushort kind)

{
  int iVar1;
  uint uVar2;

  iVar1 = FUN_81c152f0((uint)kind,'\x01',g_sango_package_data);
  uVar2 = FUN_81c06a70((uint)kind,0,(uint)*(byte *)(iVar1 + 5),1,0,0);
  return uVar2;
}


#undef g_sango_package_data


/* VA 0x81c16330; body bytes 408 */

uint FUN_81c16330(char param_1)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
#define local_28 (*(int *)(sg_stack + 0))
#define local_24 (*(int *)(sg_stack + 4))

  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;

  FUN_81c164c8();
  uVar2 = 0;
  FUN_81c0aae4(0x18,0x74,0x86,0x80,0);
  iVar4 = 0x74;
  iVar3 = 0x80;
  do {
    do {
      FUN_81c1408c(&local_28);
    } while (local_28 != 5);
    FUN_81c0aae4(0x18,(short)iVar4,0x86,(short)iVar3,0);
    if (local_24 == 0x1c) {
      if (param_1 == '\0') {
        iVar4 = FUN_81c16940((char)uVar2);
      }
      else {
        iVar4 = FUN_81c16704((char)uVar2);
      }
      if (iVar4 != 0) {
        return uVar2 & 0xff;
      }
      FUN_81c164c8();
    }
    else if (local_24 < 0x1d) {
      if (local_24 == 1) {
        return 0xff;
      }
    }
    else if (local_24 == 0x67) {
      uVar2 = uVar2 - 1;
      if (uVar2 == 0xffffffff) {
        uVar2 = 2;
      }
    }
    else if ((local_24 == 0x6c) && (uVar2 = uVar2 + 1, uVar2 == 3)) {
      uVar2 = 0;
    }
    uVar2 = (int)uVar2 % 3;
    uVar1 = uVar2 * 0x1b + 0x22 & 0xff;
    iVar3 = uVar1 + 0x5e;
    iVar4 = uVar1 + 0x52;
    FUN_81c0aae4(0x18,(short)iVar4,0x86,(short)iVar3,0);
  } while( true );
}


#undef local_28
#undef local_24

#define DAT_81c2b161 (*(undefined1 *)(0x81c2b161u))
#define DAT_81c205e0 (*(undefined *)(0x81c205e0u))
/* VA 0x81c164c8; body bytes 572 */

void FUN_81c164c8(void)

{
  unsigned char sg_stack[128] __attribute__((aligned(8)));
#define local_90 (*(uchar (*)[8])(sg_stack + 0))
#define local_71 (*(char *)(sg_stack + 31))
#define local_49 (*(char *)(sg_stack + 71))
#define local_28 (*(ushort (*)[4])(sg_stack + 104))
#define acStack_88 (*(char (*)[10])(sg_stack + 8))
#define auStack_7e (*(undefined1 (*)[13])(sg_stack + 18))
#define acStack_60 (*(char (*)[23])(sg_stack + 48))
#define acStack_38 (*(char (*)[16])(sg_stack + 88))

  char cVar1;
  bool bVar2;
  undefined1 uVar3;
  void *file;
  void *file_00;
  uint uVar4;
  ushort uVar5;

  FUN_81c077bc(0x2e,1,0,0,'\x01');
  uVar3 = DAT_81c2b161;
  uVar5 = 0;
  do {
    cVar1 = (char)uVar5 * '\x02';
    FUN_81c154d8(1,0x40,acStack_88);
    local_71 = cVar1 + '0';
    file = bbk_fopen(acStack_88,&DAT_81c205e0);
    FUN_81c154d8(1,0x40,acStack_60);
    local_49 = cVar1 + '1';
    file_00 = bbk_fopen(acStack_60,&DAT_81c205e0);
    bVar2 = false;
    if (file_00 == 0) {
      if (file != 0) {
        bbk_fclose(file);
      }
      FUN_81c154d8(1,0x42,acStack_88);
      bVar2 = true;
    }
    if (file == 0) {
      if (file_00 != 0) {
        bbk_fclose(file_00);
      }
      FUN_81c154d8(1,0x42,acStack_88);
      bVar2 = true;
    }
    if (!bVar2) {
      bbk_fread(&DAT_81c2b161,1,1,file);
      bbk_fread(local_90,1,1,file);
      bbk_fread(local_28,1,2,file);
      bbk_fclose(file);
      bbk_fclose(file_00);
      FUN_81c154d8(1,0x41,acStack_88);
      sango_load_named_text(local_90[0],acStack_38);
      uVar4 = bbk_strlen(acStack_38);
      local_90[0] = (uchar)uVar4;
      bbk_memcpy(acStack_88,acStack_38,uVar4 & 0xff);
      FUN_81c0a7e4((uint)local_28[0],acStack_38,10);
      uVar4 = bbk_strlen(acStack_38);
      bbk_memcpy(auStack_7e,acStack_38,uVar4 + 1 & 0xff);
    }
    FUN_81c149dc(0x28,uVar5 * 0x1b + 0x74,acStack_88);
    uVar5 = uVar5 + 1 & 0xff;
  } while (uVar5 < 3);
  DAT_81c2b161 = uVar3;
  return;
}


#undef DAT_81c2b161
#undef DAT_81c205e0
#undef local_90
#undef local_71
#undef local_49
#undef local_28
#undef acStack_88
#undef auStack_7e
#undef acStack_60
#undef acStack_38

#define DAT_81c2b164 (*(void * *)(0x81c2b164u))
#define DAT_81c205e0 (*(undefined *)(0x81c205e0u))
#define DAT_81c2b114 (*(undefined1 *)(0x81c2b114u))
#define DAT_81c2b115 (*(undefined1 *)(0x81c2b115u))
#define DAT_81c2b140 (*(undefined2 *)(0x81c2b140u))
#define DAT_81c2b161 (*(undefined1 *)(0x81c2b161u))
#define DAT_81c2b170 (*(undefined1 *)(0x81c2b170u))
#define DAT_81c2b171 (*(undefined1 *)(0x81c2b171u))
#define DAT_81c2b190 (*(undefined1 *)(0x81c2b190u))
#define DAT_81c2b194 (*(undefined1 *)(0x81c2b194u))
#define DAT_81c2b310 (*(undefined1 *)(0x81c2b310u))
#define DAT_81c2b3e0 (*(undefined1 *)(0x81c2b3e0u))
#define DAT_81c2b450 (*(undefined1 *)(0x81c2b450u))
#define g_state_buffer_1200 (*(undefined4 *)(0x81c2b0e4u))
#define g_state_buffer_300 (*(undefined4 *)(0x81c2b0e8u))
#define g_state_buffer_30 (*(undefined4 *)(0x81c2b0ecu))
/* VA 0x81c16704; body bytes 572 */

undefined4 FUN_81c16704(char param_1)

{
  unsigned char sg_stack[40] __attribute__((aligned(8)));
#define acStack_38 (*(char (*)[23])(sg_stack + 0))
#define local_21 (*(char *)(sg_stack + 23))

  void *pvVar1;

  FUN_81c154d8(1,0x44,acStack_38);
  FUN_81c14dd8(acStack_38,1);
  FUN_81c154d8(1,0x40,acStack_38);
  local_21 = param_1 * '\x02' + '0';
  pvVar1 = bbk_fopen(acStack_38,&DAT_81c205e0);
  if (pvVar1 != 0) {
    bbk_fread(&DAT_81c2b161,1,1,pvVar1);
    bbk_fread(&DAT_81c2b115,1,1,pvVar1);
    bbk_fread(&DAT_81c2b140,2,1,pvVar1);
    bbk_fread(&DAT_81c2b114,1,1,pvVar1);
    bbk_fread(&DAT_81c2b194,1,1,pvVar1);
    bbk_fread(&DAT_81c2b171,1,1,pvVar1);
    bbk_fread(&DAT_81c2b170,1,1,pvVar1);
    bbk_fread(&DAT_81c2b190,4,1,pvVar1);
    bbk_fread(DAT_81c2b164,0x10,200,pvVar1);
    bbk_fread(&DAT_81c2b310,1,200,pvVar1);
    bbk_fread(&DAT_81c2b3e0,1,0x21,pvVar1);
    bbk_fclose(pvVar1);
    local_21 = param_1 * '\x02' + '1';
    pvVar1 = bbk_fopen(acStack_38,&DAT_81c205e0);
    if (pvVar1 != 0) {
      bbk_fread(g_state_buffer_30,1,0x1e,pvVar1);
      bbk_fread(g_state_buffer_300,10,0x1e,pvVar1);
      bbk_fread(g_state_buffer_1200,0xc,100,pvVar1);
      bbk_fread(&DAT_81c2b450,0x24,0x26,pvVar1);
      bbk_fclose(pvVar1);
      return 1;
    }
  }
  FUN_81c154d8(1,0x46,acStack_38);
  FUN_81c14dd8(acStack_38,2);
  return 0;
}


#undef DAT_81c2b164
#undef DAT_81c205e0
#undef DAT_81c2b114
#undef DAT_81c2b115
#undef DAT_81c2b140
#undef DAT_81c2b161
#undef DAT_81c2b170
#undef DAT_81c2b171
#undef DAT_81c2b190
#undef DAT_81c2b194
#undef DAT_81c2b310
#undef DAT_81c2b3e0
#undef DAT_81c2b450
#undef g_state_buffer_1200
#undef g_state_buffer_300
#undef g_state_buffer_30
#undef acStack_38
#undef local_21

#define DAT_81c2b164 (*(void * *)(0x81c2b164u))
#define DAT_81c20608 (*(undefined *)(0x81c20608u))
#define DAT_81c2b114 (*(undefined1 *)(0x81c2b114u))
#define DAT_81c2b115 (*(undefined1 *)(0x81c2b115u))
#define DAT_81c2b140 (*(undefined2 *)(0x81c2b140u))
#define DAT_81c2b161 (*(undefined1 *)(0x81c2b161u))
#define DAT_81c2b170 (*(undefined1 *)(0x81c2b170u))
#define DAT_81c2b171 (*(undefined1 *)(0x81c2b171u))
#define DAT_81c2b190 (*(undefined1 *)(0x81c2b190u))
#define DAT_81c2b194 (*(undefined1 *)(0x81c2b194u))
#define DAT_81c2b310 (*(undefined1 *)(0x81c2b310u))
#define DAT_81c2b3e0 (*(undefined1 *)(0x81c2b3e0u))
#define DAT_81c2b450 (*(undefined1 *)(0x81c2b450u))
#define g_state_buffer_1200 (*(undefined4 *)(0x81c2b0e4u))
#define g_state_buffer_300 (*(undefined4 *)(0x81c2b0e8u))
#define g_state_buffer_30 (*(undefined4 *)(0x81c2b0ecu))
/* VA 0x81c16940; body bytes 740 */

undefined4 FUN_81c16940(char param_1)

{
  unsigned char sg_stack[84] __attribute__((aligned(8)));
#define local_49 (*(char *)(sg_stack + 23))
#define local_1d (*(char *)(sg_stack + 67))
#define acStack_60 (*(char (*)[23])(sg_stack + 0))
#define auStack_38 (*(undefined1 (*)[27])(sg_stack + 40))

  int iVar1;
  void *pvVar2;
  char cVar3;

  FUN_81c154d8(1,0x43,acStack_60);
  FUN_81c14dd8(acStack_60,0);
  FUN_81c154d8(1,0x40,acStack_60);
  FUN_81c154d8(1,0x47,auStack_38);
  iVar1 = bda_sango_fs_access((char *)0x81c205e4,0);
  if (iVar1 == -1) {
    bda_sango_fs_mkdir((char *)0x81c205e4);
  }
  iVar1 = bda_sango_fs_access((char *)0x81c205f4,0);
  if (iVar1 == -1) {
    cVar3 = param_1 << 1;
    bda_sango_fs_mkdir((char *)0x81c205f4);
  }
  else {
    cVar3 = param_1 * '\x02';
  }
  local_49 = cVar3 + '0';
  local_1d = local_49;
  pvVar2 = bbk_fopen(acStack_60,&DAT_81c20608);
  if (pvVar2 != 0) {
    FUN_81c0b02c(&DAT_81c2b161,1,1,pvVar2);
    FUN_81c0b02c(&DAT_81c2b115,1,1,pvVar2);
    FUN_81c0b02c(&DAT_81c2b140,2,1,pvVar2);
    FUN_81c0b02c(&DAT_81c2b114,1,1,pvVar2);
    FUN_81c0b02c(&DAT_81c2b194,1,1,pvVar2);
    FUN_81c0b02c(&DAT_81c2b171,1,1,pvVar2);
    FUN_81c0b02c(&DAT_81c2b170,1,1,pvVar2);
    FUN_81c0b02c(&DAT_81c2b190,4,1,pvVar2);
    FUN_81c0b02c(DAT_81c2b164,0x10,200,pvVar2);
    FUN_81c0b02c(&DAT_81c2b310,1,200,pvVar2);
    FUN_81c0b02c(&DAT_81c2b3e0,1,0x21,pvVar2);
    bbk_fclose(pvVar2);
    local_49 = cVar3 + '1';
    pvVar2 = bbk_fopen(acStack_60,&DAT_81c20608);
    if (pvVar2 != 0) {
      FUN_81c0b02c(g_state_buffer_30,1,0x1e,pvVar2);
      FUN_81c0b02c(g_state_buffer_300,10,0x1e,pvVar2);
      FUN_81c0b02c(g_state_buffer_1200,0xc,100,pvVar2);
      FUN_81c0b02c(&DAT_81c2b450,0x24,0x26,pvVar2);
      bbk_fclose(pvVar2);
      return 1;
    }
  }
  FUN_81c154d8(1,0x45,acStack_60);
  FUN_81c14dd8(acStack_60,2);
  return 0;
}


#undef DAT_81c2b164
#undef DAT_81c20608
#undef DAT_81c2b114
#undef DAT_81c2b115
#undef DAT_81c2b140
#undef DAT_81c2b161
#undef DAT_81c2b170
#undef DAT_81c2b171
#undef DAT_81c2b190
#undef DAT_81c2b194
#undef DAT_81c2b310
#undef DAT_81c2b3e0
#undef DAT_81c2b450
#undef g_state_buffer_1200
#undef g_state_buffer_300
#undef g_state_buffer_30
#undef local_49
#undef local_1d
#undef acStack_60
#undef auStack_38


/* VA 0x81c16c24; body bytes 92 */

void sango_main(void)

{
  int iVar1;

  iVar1 = bda_sango_gui_shell_open(1);
  if ((iVar1 != 0) && (iVar1 = sango_create_app_frame(), iVar1 != -1)) {
    sango_game_lifecycle();
    sango_run_event_loop_and_close();
  }
  return;
}




#define DAT_81c2b16c (*(void * *)(0x81c2b16cu))
#define DAT_81c2b14c (*(void * *)(0x81c2b14cu))
#define DAT_81c2b15c (*(void * *)(0x81c2b15cu))
#define DAT_81c2b164 (*(void * *)(0x81c2b164u))
/* VA 0x81c16c80; body bytes 232 */

void sango_game_lifecycle(void)

{
  unsigned char sg_stack[128] __attribute__((aligned(8)));
#define acStack_78 (*(char (*)[56])(sg_stack + 0))
#define acStack_40 (*(char (*)[56])(sg_stack + 56))

  int iVar1;

  graphics_init_stub();
  iVar1 = sango_load_package_and_buffers();
  if (iVar1 == 0) {
    FUN_81c162e0(3);
    iVar1 = sango_allocate_session_state();
    if (iVar1 == 0) {
      while (iVar1 = sango_select_session(), iVar1 != 0) {
        FUN_81c1aab4();
      }
    }
    else {
      FUN_81c154d8(1,0x2f,acStack_40);
      FUN_81c14dd8(acStack_40,2);
    }
    bbk_free_if_nonnull(DAT_81c2b16c);
    bbk_free_if_nonnull(DAT_81c2b14c);
    bbk_free_if_nonnull(DAT_81c2b15c);
    bbk_free_if_nonnull(DAT_81c2b164);
    sango_release_package_and_buffers();
  }
  else {
    FUN_81c154d8(1,0x2e,acStack_78);
    FUN_81c14dd8(acStack_78,2);
  }
  return;
}


#undef DAT_81c2b16c
#undef DAT_81c2b14c
#undef DAT_81c2b15c
#undef DAT_81c2b164
#undef acStack_78
#undef acStack_40

#define DAT_81c2b16c (*(void * *)(0x81c2b16cu))
#define DAT_81c2b14c (*(void * *)(0x81c2b14cu))
#define DAT_81c2b15c (*(void * *)(0x81c2b15cu))
#define DAT_81c2b164 (*(void * *)(0x81c2b164u))
/* VA 0x81c16d68; body bytes 72 */

void FUN_81c16d68(void)

{
  bbk_free_if_nonnull(DAT_81c2b16c);
  bbk_free_if_nonnull(DAT_81c2b14c);
  bbk_free_if_nonnull(DAT_81c2b15c);
  bbk_free_if_nonnull(DAT_81c2b164);
  return;
}


#undef DAT_81c2b16c
#undef DAT_81c2b14c
#undef DAT_81c2b15c
#undef DAT_81c2b164


/* VA 0x81c16db0; body bytes 56 */

void FUN_81c16db0(char param_1)

{
  unsigned char sg_stack[72] __attribute__((aligned(8)));
#define acStack_40 (*(char (*)[56])(sg_stack + 0))


  FUN_81c154d8(1,(byte)param_1 + 0x2e & 0xff,acStack_40);
  FUN_81c14dd8(acStack_40,2);
  return;
}


#undef acStack_40

#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c16de8; body bytes 16 */

int FUN_81c16de8(undefined4 param_1,int param_2)

{
  return g_sango_package_data + param_2;
}


#undef g_sango_package_data

#define DAT_81c2b170 (*(byte *)(0x81c2b170u))
#define DAT_81c2b9a2 (*(byte *)(0x81c2b9a2u))
#define DAT_81c2b9a3 (*(byte *)(0x81c2b9a3u))
#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c2b450 (*(undefined1 *)(0x81c2b450u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define DAT_81c2b45d (*(undefined1 *)(0x81c2b45du))
#define DAT_81c2b460 (*(undefined4 *)(0x81c2b460u))
#define DAT_81c2b464 (*(undefined4 *)(0x81c2b464u))
#define DAT_81c2b468 (*(undefined2 *)(0x81c2b468u))
#define DAT_81c2b46a (*(undefined2 *)(0x81c2b46au))
#define DAT_81c2b46c (*(undefined2 *)(0x81c2b46cu))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c16e00; body bytes 972 */

undefined4 FUN_81c16e00(void)

{
  char cVar1;
  ushort uVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  byte *pbVar12;
  uint uVar13;
  uint uVar14;

  if ((DAT_81c2b170 == 6) || (DAT_81c2b170 == 10)) {
    FUN_81c176d8();
  }
  if (DAT_81c2b170 % 3 == 0) {
    FUN_81c1767c();
  }
  uVar10 = (uint)DAT_81c2b9a2 + (uint)DAT_81c2b9a3 & 0xff;
  uVar14 = 0;
  if (uVar10 != 0) {
    do {
      iVar6 = uVar14 * 0x10 + DAT_81c2b164;
      *(char *)(iVar6 + 8) = *(char *)(iVar6 + 8) + '\x04';
      iVar6 = uVar14 * 0x10 + DAT_81c2b164;
      if (100 < *(byte *)(iVar6 + 8)) {
        *(undefined1 *)(iVar6 + 8) = 100;
      }
      uVar14 = uVar14 + 1 & 0xff;
    } while (uVar14 < uVar10);
  }
  pbVar3 = g_scratch_buffer_4096;
  uVar10 = 0;
  iVar6 = 0;
  do {
    iVar6 = iVar6 + uVar10;
    iVar4 = iVar6 * 4;
    if ((&DAT_81c2b451)[iVar4] != '\0') {
      if ((uint)DAT_81c2b170 % 3 == 0) {
        uVar11 = bbk_rand();
        uVar14 = uVar11 + 3;
        if (-1 < (int)uVar11) {
          uVar14 = uVar11;
        }
        uVar14 = uVar11 + ((int)uVar14 >> 2) * -4 + 1;
        if ((uVar14 & 0xff) < (uint)(byte)(&DAT_81c2b45d)[iVar4]) {
          (&DAT_81c2b45d)[iVar4] = (&DAT_81c2b45d)[iVar4] - (char)uVar14;
        }
      }
      if (30000 < (ushort)(&DAT_81c2b468)[iVar6 * 2]) {
        (&DAT_81c2b468)[iVar6 * 2] = 30000;
      }
      iVar5 = (&DAT_81c2b464)[iVar6];
      (&DAT_81c2b464)[iVar6] = iVar5 + 0x32U;
      if ((uint)(&DAT_81c2b460)[iVar6] < iVar5 + 0x32U) {
        (&DAT_81c2b464)[iVar6] = (&DAT_81c2b460)[iVar6];
      }
      uVar13 = (uint)(ushort)(&DAT_81c2b46c)[iVar6 * 2];
      uVar14 = FUN_81c13870(uVar10,(int)pbVar3);
      iVar5 = DAT_81c2b164;
      uVar11 = 0;
      if (uVar14 != 0) {
        do {
          pbVar12 = pbVar3 + uVar11;
          uVar2 = *(ushort *)((uint)*pbVar12 * 0x10 + iVar5 + 10);
          uVar9 = (uint)uVar2;
          switch((&DAT_81c2b450)[uVar14 * 0x24]) {
          case 2:
          case 3:
            uVar9 = uVar9 - (uVar2 >> 2) & 0xffff;
            break;
          case 4:
            uVar9 = (uint)(uVar2 >> 1);
          }
          uVar11 = uVar11 + 1 & 0xff;
          *(short *)((uint)*pbVar12 * 0x10 + iVar5 + 10) = (short)uVar9;
          uVar13 = uVar13 + uVar9 & 0xffff;
        } while (uVar11 < uVar14);
      }
      iVar5 = DAT_81c2b164;
      if (uVar13 / 0x32 < (uint)(ushort)(&DAT_81c2b46a)[iVar6 * 2]) {
        (&DAT_81c2b46a)[iVar6 * 2] = (&DAT_81c2b46a)[iVar6 * 2] - (short)(uVar13 / 0x32);
      }
      else {
        uVar11 = 0;
        if (uVar14 != 0) {
          do {
            pbVar12 = pbVar3 + uVar11;
            uVar11 = uVar11 + 1 & 0xff;
            iVar8 = (uint)*pbVar12 * 0x10 + iVar5;
            *(ushort *)(iVar8 + 10) = *(ushort *)(iVar8 + 10) >> 1;
          } while (uVar11 < uVar14);
        }
        (&DAT_81c2b46a)[iVar6 * 2] = 0;
        cVar1 = (&DAT_81c2b450)[iVar4];
        (&DAT_81c2b450)[iVar4] = '\x01';
        if ((cVar1 != '\x01') && ((uint)(byte)(&DAT_81c2b451)[iVar4] == DAT_81c2b115 + 1)) {
          FUN_81c17c48((byte)uVar10,&DAT_81c2b46a + iVar6 * 2,uVar11,uVar14);
        }
      }
      uVar14 = FUN_81c139a8(uVar10,(int)pbVar3);
      uVar11 = 0;
      pbVar12 = pbVar3;
      if (uVar14 != 0) {
        do {
          pcVar7 = (char *)((uint)*pbVar12 * 0x10 + DAT_81c2b164);
          if (*pcVar7 == (&DAT_81c2b451)[iVar4]) {
            pcVar7[1] = (&DAT_81c2b451)[iVar4];
          }
          uVar11 = uVar11 + 1 & 0xff;
          pbVar12 = pbVar3 + uVar11;
        } while (uVar11 < uVar14);
      }
    }
    uVar10 = uVar10 + 1 & 0xff;
    iVar6 = uVar10 << 3;
  } while (uVar10 < 0x26);
  return 1;
}


#undef DAT_81c2b170
#undef DAT_81c2b9a2
#undef DAT_81c2b9a3
#undef DAT_81c2b164
#undef DAT_81c2b115
#undef DAT_81c2b450
#undef DAT_81c2b451
#undef DAT_81c2b45d
#undef DAT_81c2b460
#undef DAT_81c2b464
#undef DAT_81c2b468
#undef DAT_81c2b46a
#undef DAT_81c2b46c
#undef g_scratch_buffer_4096

#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c2b450 (*(undefined1 *)(0x81c2b450u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define DAT_81c2b45c (*(undefined1 *)(0x81c2b45cu))
#define DAT_81c2b45d (*(undefined1 *)(0x81c2b45du))
#define DAT_81c2b46a (*(undefined2 *)(0x81c2b46au))
#define switchdataD_81c20624 (*(u32 *)(0x81c20624u))
/* VA 0x81c171cc; body bytes 576 */

undefined4 FUN_81c171cc(void)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  ushort uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  byte *pbVar9;
  uint uVar10;

  uVar10 = 0;
  iVar8 = 0;
  do {
    iVar3 = (iVar8 + uVar10) * 4;
    pbVar9 = &DAT_81c2b450 + iVar3;
    bVar1 = (&DAT_81c2b451)[iVar3];
    if (bVar1 != 0) {
      uVar4 = bbk_rand();
      uVar7 = (uint)*pbVar9;
      uVar6 = (uint)(uVar7 < 5);
      uVar4 = (int)uVar4 % 100 & 0xff;
      if (uVar6 != 0) {
        switch((uint)(&switchdataD_81c20624)[uVar7] & 0xfffffffe) {
        case 0x81c172a4:
          iVar8 = (iVar8 + uVar10) * 4;
          if ((byte)(&DAT_81c2b45d)[iVar8] < uVar4) {
            uVar4 = bbk_rand();
            iVar3 = (int)uVar4 >> 0x1f;
            uVar4 = (int)uVar4 % 5 & 0xff;
            bVar2 = 3;
            if (uVar4 == 1) {
LAB_81c1736c:
              *pbVar9 = bVar2;
LAB_81c17370:
              if ((*pbVar9 != 0) && ((uint)bVar1 == DAT_81c2b115 + 1)) {
                FUN_81c17c48((byte)uVar10,iVar3,uVar6,uVar7);
              }
            }
            else if (uVar4 < 2) {
              bVar2 = 2;
              if (uVar4 == 0) goto LAB_81c1736c;
            }
            else if (uVar4 == 2) {
              uVar4 = bbk_rand();
              iVar3 = (int)uVar4 >> 0x1f;
              uVar6 = (uint)((uint)(byte)(&DAT_81c2b45c)[iVar8] < ((int)uVar4 % 100 & 0xffU));
              bVar2 = 4;
              if (uVar6 != 0) goto LAB_81c1736c;
              goto LAB_81c17370;
            }
          }
          goto switchD_81c1729c_default;
        case 0x81c173b0:
          uVar5 = (&DAT_81c2b46a)[(iVar8 + uVar10) * 2];
          break;
        case 0x81c173d4:
          uVar5 = (ushort)(uVar4 < (byte)(&DAT_81c2b45d)[(iVar8 + uVar10) * 4]);
          break;
        case 0x81c173f0:
          uVar5 = (ushort)(uVar4 < (byte)(&DAT_81c2b45c)[(iVar8 + uVar10) * 4]);
        }
        if (uVar5 != 0) {
          *pbVar9 = 0;
        }
      }
    }
switchD_81c1729c_default:
    uVar10 = uVar10 + 1 & 0xff;
    iVar8 = uVar10 << 3;
    if (0x25 < uVar10) {
      return 1;
    }
  } while( true );
}


#undef DAT_81c2b115
#undef DAT_81c2b450
#undef DAT_81c2b451
#undef DAT_81c2b45c
#undef DAT_81c2b45d
#undef DAT_81c2b46a
#undef switchdataD_81c20624

#define DAT_81c2b450 (*(undefined1 *)(0x81c2b450u))
#define DAT_81c2b456 (*(undefined2 *)(0x81c2b456u))
#define DAT_81c2b45a (*(undefined2 *)(0x81c2b45au))
#define DAT_81c2b45c (*(undefined1 *)(0x81c2b45cu))
#define DAT_81c2b464 (*(undefined4 *)(0x81c2b464u))
#define DAT_81c2b468 (*(undefined2 *)(0x81c2b468u))
#define DAT_81c2b46a (*(undefined2 *)(0x81c2b46au))
#define DAT_81c2b46c (*(undefined2 *)(0x81c2b46cu))
/* VA 0x81c1740c; body bytes 624 */

undefined4 FUN_81c1740c(void)

{
  ushort uVar1;
  uint uVar2;
  byte *pbVar3;
  ushort *puVar4;
  uint *puVar5;
  ushort *puVar6;
  ushort *puVar7;
  ushort *puVar8;
  uint uVar9;

  uVar9 = 0;
  do {
    pbVar3 = &DAT_81c2b45c + uVar9 * 0x24;
    puVar6 = &DAT_81c2b45a + uVar9 * 0x12;
    puVar7 = &DAT_81c2b46c + uVar9 * 0x12;
    puVar4 = &DAT_81c2b46a + uVar9 * 0x12;
    puVar8 = &DAT_81c2b468 + uVar9 * 0x12;
    puVar5 = &DAT_81c2b464 + uVar9 * 9;
    switch((&DAT_81c2b450)[uVar9 * 0x24]) {
    case 0:
      goto switchD_81c17494_caseD_0;
    case 1:
      *puVar6 = *puVar6 - *puVar6 / 0x14;
      *pbVar3 = *pbVar3 - *pbVar3 / 0x14;
      uVar2 = *puVar5;
      *puVar7 = *puVar7 >> 1;
      *puVar5 = uVar2 - (uVar2 >> 2);
      break;
    case 2:
      uVar1 = *puVar4;
      *puVar5 = *puVar5 - (*puVar5 >> 2);
      *puVar4 = uVar1 - uVar1 / 0x14;
      goto LAB_81c1756c;
    case 3:
      uVar1 = *puVar4;
      *puVar5 = *puVar5 - (*puVar5 >> 2);
      *puVar4 = uVar1 - uVar1 / 0x14;
      *puVar6 = *puVar6 - *puVar6 / 10;
      *puVar8 = *puVar8 - *puVar8 / 10;
LAB_81c1756c:
      *puVar7 = *puVar7 - (*puVar7 >> 2);
      break;
    case 4:
      *puVar4 = *puVar4 - *puVar4 / 0x14;
      *puVar6 = *puVar6 - *puVar6 / 0x14;
      *puVar8 = *puVar8 - *puVar8 / 0x14;
      *pbVar3 = *pbVar3 - *pbVar3 / 10;
      *puVar7 = *puVar7 >> 1;
    }
    uVar1 = (&DAT_81c2b456)[uVar9 * 0x12];
    (&DAT_81c2b456)[uVar9 * 0x12] = uVar1 - uVar1 / 0x14;
switchD_81c17494_caseD_0:
    uVar9 = uVar9 + 1 & 0xff;
    if (0x25 < uVar9) {
      return 1;
    }
  } while( true );
}


#undef DAT_81c2b450
#undef DAT_81c2b456
#undef DAT_81c2b45a
#undef DAT_81c2b45c
#undef DAT_81c2b464
#undef DAT_81c2b468
#undef DAT_81c2b46a
#undef DAT_81c2b46c

#define DAT_81c2b45a (*(undefined2 *)(0x81c2b45au))
#define DAT_81c2b468 (*(undefined2 *)(0x81c2b468u))
/* VA 0x81c1767c; body bytes 92 */

void FUN_81c1767c(void)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;

  uVar3 = 0;
  iVar2 = 0;
  do {
    iVar2 = iVar2 + uVar3;
    uVar1 = (&DAT_81c2b468)[iVar2 * 2];
    uVar3 = uVar3 + 1 & 0xff;
    if (uVar1 < 30000) {
      (&DAT_81c2b468)[iVar2 * 2] = uVar1 + ((ushort)(&DAT_81c2b45a)[iVar2 * 2] >> 1);
    }
    iVar2 = uVar3 << 3;
  } while (uVar3 < 0x26);
  return;
}


#undef DAT_81c2b45a
#undef DAT_81c2b468

#define DAT_81c2b456 (*(undefined2 *)(0x81c2b456u))
#define DAT_81c2b46a (*(undefined2 *)(0x81c2b46au))
/* VA 0x81c176d8; body bytes 92 */

void FUN_81c176d8(void)

{
  int iVar1;
  uint uVar2;

  uVar2 = 0;
  iVar1 = 0;
  do {
    iVar1 = iVar1 + uVar2;
    uVar2 = uVar2 + 1 & 0xff;
    if ((ushort)(&DAT_81c2b46a)[iVar1 * 2] < 30000) {
      (&DAT_81c2b46a)[iVar1 * 2] =
           (&DAT_81c2b46a)[iVar1 * 2] + ((ushort)(&DAT_81c2b456)[iVar1 * 2] >> 2);
    }
    iVar1 = uVar2 << 3;
  } while (uVar2 < 0x26);
  return;
}


#undef DAT_81c2b456
#undef DAT_81c2b46a

#define DAT_81c2b170 (*(char *)(0x81c2b170u))
#define DAT_81c2b161 (*(char *)(0x81c2b161u))
#define DAT_81c2b140 (*(short *)(0x81c2b140u))
#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b310 (*(undefined1 *)(0x81c2b310u))
#define DAT_81c2b46e (*(undefined1 *)(0x81c2b46eu))
#define DAT_81c2b46f (*(undefined1 *)(0x81c2b46fu))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c17734; body bytes 724 */

undefined4 FUN_81c17734(void)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;

  if (DAT_81c2b170 == '\x01') {
    uVar7 = 0;
    do {
      iVar2 = uVar7 * 0x10 + DAT_81c2b164;
      uVar7 = uVar7 + 1 & 0xff;
      *(char *)(iVar2 + 0xe) = *(char *)(iVar2 + 0xe) + '\x01';
    } while (uVar7 < 200);
  }
  uVar7 = 0;
  iVar2 = FUN_81c152f0(0x3f,DAT_81c2b161,g_sango_package_data);
  uVar8 = 0;
  do {
    if ((ushort)(*(byte *)(iVar2 + uVar8) + 0x10) == DAT_81c2b140) {
      uVar5 = (uint)((byte *)(iVar2 + uVar8))[2];
      if (uVar5 == 0) {
        uVar5 = bbk_rand();
        uVar5 = (int)uVar5 % 0x26 & 0xff;
      }
      uVar6 = 0;
      uVar3 = 0;
      do {
        iVar4 = uVar3 * 0x24;
        uVar3 = uVar3 + 1 & 0xff;
        uVar6 = uVar6 + (byte)(&DAT_81c2b46f)[iVar4] & 0xff;
      } while (uVar3 < 0x26);
      uVar3 = 0;
      if (uVar6 == 0) {
        bVar1 = false;
LAB_81c17974:
        if (bVar1) goto LAB_81c177a0;
      }
      else {
        do {
          if ((byte)(&DAT_81c2b310)[uVar3] == uVar7) {
            bVar1 = uVar3 < uVar6;
            goto LAB_81c17974;
          }
          uVar3 = uVar3 + 1 & 0xff;
        } while (uVar3 < uVar6);
      }
      iVar4 = FUN_81c134b8(uVar5,(byte)uVar7);
      if (iVar4 == 0) {
        return 0;
      }
      *(undefined1 *)(uVar7 * 0x10 + DAT_81c2b164 + 0xe) = 0x10;
    }
LAB_81c177a0:
    uVar7 = uVar7 + 1 & 0xff;
    uVar8 = uVar8 + 3 & 0xffff;
    if (199 < uVar7) {
      uVar7 = 0;
      iVar2 = 0;
      do {
        iVar2 = (iVar2 + uVar7) * 4;
        uVar8 = (uint)(byte)(&DAT_81c2b46e)[iVar2];
        uVar5 = uVar8 + (byte)(&DAT_81c2b46f)[iVar2];
        for (; uVar8 < (uVar5 & 0xff); uVar8 = uVar8 + 1 & 0xff) {
          iVar2 = uVar8 * 0x10 + DAT_81c2b164;
          *(char *)(iVar2 + 0xe) = *(char *)(iVar2 + 0xe) + '\x01';
          if (((0x59 < *(byte *)(uVar8 * 0x10 + DAT_81c2b164 + 0xe)) &&
              (uVar3 = bbk_rand(), (int)uVar3 % 100 < 0x32)) &&
             (iVar2 = FUN_81c123f0(uVar7,(byte)uVar8), iVar2 == 0)) {
            return 0;
          }
        }
        uVar7 = uVar7 + 1 & 0xff;
        iVar2 = uVar7 << 3;
        if (0x25 < uVar7) {
          return 1;
        }
      } while( true );
    }
  } while( true );
}


#undef DAT_81c2b170
#undef DAT_81c2b161
#undef DAT_81c2b140
#undef DAT_81c2b164
#undef DAT_81c2b310
#undef DAT_81c2b46e
#undef DAT_81c2b46f
#undef g_sango_package_data

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c17a08; body bytes 308 */

uint FUN_81c17a08(uint param_1,uint param_2)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;

  iVar3 = FUN_81c152f0(0x42,'\x01',g_sango_package_data);
  iVar5 = (param_2 & 0xff) * 0x10;
  iVar4 = (param_1 & 0xff) * 0x42 + iVar3;
  *(char *)(iVar5 + DAT_81c2b164 + 3) =
       *(char *)(iVar5 + DAT_81c2b164 + 3) + *(char *)(iVar4 + 0x3e);
  *(char *)(iVar5 + DAT_81c2b164 + 4) =
       *(char *)(iVar5 + DAT_81c2b164 + 4) + *(char *)(iVar4 + 0x3f);
  bVar1 = *(byte *)(iVar4 + 0x41);
  if (bVar1 == 2) {
    if (*(byte *)(iVar5 + DAT_81c2b164 + 4) < 0x6a) {
      return 0xff;
    }
    uVar2 = 5;
  }
  else {
    if (bVar1 < 3) {
      if (bVar1 == 1) {
        *(undefined1 *)(iVar5 + DAT_81c2b164 + 9) = 3;
      }
      goto LAB_81c17ab0;
    }
    if (bVar1 != 3) goto LAB_81c17ab0;
    if (*(byte *)(iVar5 + DAT_81c2b164 + 3) < 0x6a) {
      return 0xff;
    }
    uVar2 = 4;
  }
  *(undefined1 *)(iVar5 + DAT_81c2b164 + 9) = uVar2;
LAB_81c17ab0:
  return (uint)*(byte *)((param_1 & 0xff) * 0x42 + iVar3 + 1);
}


#undef DAT_81c2b164
#undef g_sango_package_data

#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define g_state_buffer_1200 (*(undefined4 *)(0x81c2b0e4u))
#define g_state_buffer_300 (*(undefined4 *)(0x81c2b0e8u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c17b3c; body bytes 268 */

uint FUN_81c17b3c(uint param_1)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;

  uVar6 = 0;
  uVar5 = 0;
  iVar1 = 0;
  do {
    pcVar2 = (char *)((iVar1 + uVar5) * 4 + g_state_buffer_1200);
    if ((*pcVar2 != -1) &&
       ((uint)(byte)(&DAT_81c2b451)[(uint)(byte)pcVar2[2] * 0x24] == (param_1 & 0xff) + 1)) {
      uVar4 = 0;
      if (*pcVar2 == '\x1b') {
        pcVar3 = (char *)(g_state_buffer_300 + (uint)(byte)pcVar2[1] * 10);
        pcVar2 = pcVar3;
        do {
          uVar4 = uVar4 + 1 & 0xff;
          if (*pcVar2 != '\0') {
            uVar6 = uVar6 + 1 & 0xff;
          }
          pcVar2 = pcVar3 + uVar4;
        } while (uVar4 < 10);
      }
      else {
        uVar6 = uVar6 + 1 & 0xff;
      }
    }
    uVar5 = uVar5 + 1 & 0xff;
    iVar1 = uVar5 << 1;
  } while (uVar5 < 100);
  uVar5 = FUN_81c13ab8(param_1 & 0xff,g_scratch_buffer_4096);
  return uVar6 + uVar5 & 0xff;
}


#undef DAT_81c2b451
#undef g_state_buffer_1200
#undef g_state_buffer_300
#undef g_scratch_buffer_4096

#define DAT_81c2b161 (*(byte *)(0x81c2b161u))
#define DAT_81c2b452 (*(undefined1 *)(0x81c2b452u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c17c48; body bytes 464 */

void FUN_81c17c48(byte param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  unsigned char sg_stack[48] __attribute__((aligned(8)));
#define acStack_28 (*(char (*)[16])(sg_stack + 16))
#define local_38 (*(ushort (*)[8])(sg_stack + 0))

  char cVar1;
  byte *pbVar2;
  char *pcVar3;
  byte index;
  char *source;
  char *destination;

  cVar1 = (&DAT_81c2b452)[(uint)param_1 * 0x24];
  if (cVar1 != '\0') {
    destination = (char *)(g_scratch_buffer_4096 + 300);
    source = (char *)(g_scratch_buffer_4096 + 0x154);
    FUN_81c1971c(param_1,destination);
    pcVar3 = source;
    FUN_81c154d8(0x40,0x6f,source);
    bbk_strcat(destination,source);
    FUN_81c19a98((uint)param_1,source,pcVar3,param_4);
    bbk_strcat(destination,source);
    FUN_81c154d8(0x40,0x70,source);
    bbk_strcat(destination,source);
    index = cVar1 - 1;
    FUN_81c13494();
    FUN_81c0ac48(4,0x10b,0xea,0x13b,0,0);
    FUN_81c08e7c(4,0x10b,0xea,0x13a,3,0,0);
    local_38[0] = 8;
    local_38[1] = 0x10b;
    local_38[2] = 0xe8;
    local_38[3] = 0x138;
    local_38[4] = 10;
    local_38[5] = 0x111;
    local_38[7] = 0x13b;
    local_38[6] = 0x3e;
    pbVar2 = (byte *)FUN_81c152f0(DAT_81c2b161 + 0x2f,'\x01',g_sango_package_data);
    FUN_81c14fb8(0x15,0x111,0x18,0x18,index,pbVar2);
    sango_load_named_text(index,acStack_28);
    FUN_81c07b58(0x22,299,acStack_28);
    FUN_81c0791c(local_38,local_38 + 4,destination);
    FUN_81c14164(100,'\x01');
  }
  return;
}


#undef DAT_81c2b161
#undef DAT_81c2b452
#undef g_scratch_buffer_4096
#undef g_sango_package_data
#undef acStack_28
#undef local_38

#define DAT_81c2b161 (*(char *)(0x81c2b161u))
#define DAT_81c2b140 (*(ushort *)(0x81c2b140u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c17e18; body bytes 156 */

uint FUN_81c17e18(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;

  iVar2 = FUN_81c152f0(0x43,DAT_81c2b161,g_sango_package_data);
  bVar1 = 0;
  uVar4 = 0;
  while ((*(byte *)(iVar2 + uVar4) != DAT_81c2b140 ||
         (iVar3 = FUN_81c135a8((uint)((byte *)(iVar2 + uVar4))[2],bVar1), iVar3 != 0))) {
    bVar1 = bVar1 + 1;
    uVar4 = uVar4 + 3 & 0xffff;
    if (199 < bVar1) {
      return 0;
    }
  }
  return 0;
}


#undef DAT_81c2b161
#undef DAT_81c2b140
#undef g_sango_package_data

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c17eb4; body bytes 144 */

void FUN_81c17eb4(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;

  iVar1 = FUN_81c152f0(0x42,'\x01',g_sango_package_data);
  iVar3 = (param_2 & 0xff) * 0x10;
  iVar1 = (param_1 & 0xff) * 0x42 + iVar1;
  iVar2 = iVar3 + DAT_81c2b164;
  *(char *)(iVar2 + 3) = *(char *)(iVar2 + 3) - *(char *)(iVar1 + 0x3e);
  iVar3 = iVar3 + DAT_81c2b164;
  *(char *)(iVar3 + 4) = *(char *)(iVar3 + 4) - *(char *)(iVar1 + 0x3f);
  return;
}


#undef DAT_81c2b164
#undef g_sango_package_data


/* VA 0x81c17f44; body bytes 52 */

void FUN_81c17f44(byte param_1)

{
  unsigned char sg_stack[40] __attribute__((aligned(8)));
#define acStack_20 (*(char (*)[24])(sg_stack + 0))


  FUN_81c154d8(0x40,(uint)param_1,acStack_20);
  FUN_81c14dd8(acStack_20,2);
  return;
}


#undef acStack_20

#define DAT_81c2b161 (*(byte *)(0x81c2b161u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c17f78; body bytes 172 */

void FUN_81c17f78(short param_1,short param_2,uchar param_3)

{
  unsigned char sg_stack[32] __attribute__((aligned(8)));
#define acStack_20 (*(char (*)[16])(sg_stack + 0))

  byte *pbVar1;

  pbVar1 = (byte *)FUN_81c152f0(DAT_81c2b161 + 0x2f,'\x01',g_sango_package_data);
  FUN_81c14fb8(param_1 + 0xd,param_2 + 2,0x18,0x18,param_3,pbVar1);
  sango_load_named_text(param_3,acStack_20);
  FUN_81c07b58(param_1 + 0x1a,param_2 + 0x1c,acStack_20);
  return;
}


#undef DAT_81c2b161
#undef g_sango_package_data
#undef acStack_20

#define DAT_81c2b161 (*(byte *)(0x81c2b161u))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c18024; body bytes 300 */

void FUN_81c18024(uchar param_1,char *param_2)

{
  unsigned char sg_stack[48] __attribute__((aligned(8)));
#define acStack_20 (*(char (*)[16])(sg_stack + 16))
#define local_30 (*(ushort (*)[8])(sg_stack + 0))

  byte *pbVar1;

  FUN_81c0ac48(4,0x10b,0xea,0x13b,0,0);
  FUN_81c08e7c(4,0x10b,0xea,0x13a,3,0,0);
  local_30[0] = 8;
  local_30[1] = 0x10b;
  local_30[2] = 0xe8;
  local_30[3] = 0x138;
  local_30[4] = 10;
  local_30[5] = 0x111;
  local_30[7] = 0x13b;
  local_30[6] = 0x3e;
  pbVar1 = (byte *)FUN_81c152f0(DAT_81c2b161 + 0x2f,'\x01',g_sango_package_data);
  FUN_81c14fb8(0x15,0x111,0x18,0x18,param_1,pbVar1);
  sango_load_named_text(param_1,acStack_20);
  FUN_81c07b58(0x22,299,acStack_20);
  FUN_81c0791c(local_30,local_30 + 4,param_2);
  FUN_81c14164(100,'\x01');
  return;
}


#undef DAT_81c2b161
#undef g_sango_package_data
#undef acStack_20
#undef local_30

#define DAT_81c2b9a4 (*(byte *)(0x81c2b9a4u))
#define DAT_81c2b9a5 (*(byte *)(0x81c2b9a5u))
#define DAT_81c2b3e0 (*(undefined1 *)(0x81c2b3e0u))
/* VA 0x81c18150; body bytes 104 */

void FUN_81c18150(byte param_1)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  uint uVar4;

  uVar4 = (uint)DAT_81c2b9a4 + (uint)DAT_81c2b9a5 & 0xff;
  uVar2 = 0;
  if (uVar4 != 0) {
    do {
      pbVar3 = &DAT_81c2b3e0 + uVar2;
      bVar1 = *pbVar3;
      uVar2 = uVar2 + 1 & 0xff;
      if ((bVar1 & 0x7f) == param_1) {
        *pbVar3 = bVar1 | 0x80;
        return;
      }
    } while (uVar2 < uVar4);
  }
  return;
}


#undef DAT_81c2b9a4
#undef DAT_81c2b9a5
#undef DAT_81c2b3e0

#define DAT_81c2b3e0 (*(undefined1 *)(0x81c2b3e0u))
#define DAT_81c2b470 (*(undefined1 *)(0x81c2b470u))
#define DAT_81c2b471 (*(undefined1 *)(0x81c2b471u))
/* VA 0x81c181b8; body bytes 144 */

uint FUN_81c181b8(uint param_1,int param_2)

{
  char *pcVar1;
  byte *pbVar2;
  byte bVar3;
  int iVar4;
  uint uVar5;
  byte *pbVar6;
  uint uVar7;

  iVar4 = (param_1 & 0xff) * 0x24;
  uVar7 = 0;
  uVar5 = (uint)(byte)(&DAT_81c2b470)[iVar4];
  bVar3 = 0;
  if ((&DAT_81c2b471)[iVar4] != '\0') {
    do {
      pcVar1 = &DAT_81c2b3e0 + uVar5;
      bVar3 = bVar3 + 1;
      pbVar2 = &DAT_81c2b3e0 + uVar5;
      pbVar6 = (byte *)(param_2 + uVar7);
      uVar5 = uVar5 + 1 & 0xff;
      if (*pcVar1 < '\0') {
        uVar7 = uVar7 + 1 & 0xff;
        *pbVar6 = *pbVar2 & 0x7f;
      }
    } while (bVar3 < (byte)(&DAT_81c2b471)[iVar4]);
  }
  return uVar7;
}


#undef DAT_81c2b3e0
#undef DAT_81c2b470
#undef DAT_81c2b471

#define DAT_81c2b3e0 (*(undefined1 *)(0x81c2b3e0u))
#define DAT_81c2b470 (*(undefined1 *)(0x81c2b470u))
#define DAT_81c2b471 (*(undefined1 *)(0x81c2b471u))
/* VA 0x81c18248; body bytes 136 */

uint FUN_81c18248(uint param_1,int param_2)

{
  char *pcVar1;
  undefined1 *puVar2;
  byte bVar3;
  int iVar4;
  uint uVar5;
  undefined1 *puVar6;
  uint uVar7;

  iVar4 = (param_1 & 0xff) * 0x24;
  uVar7 = 0;
  uVar5 = (uint)(byte)(&DAT_81c2b470)[iVar4];
  bVar3 = 0;
  if ((&DAT_81c2b471)[iVar4] != '\0') {
    do {
      pcVar1 = &DAT_81c2b3e0 + uVar5;
      bVar3 = bVar3 + 1;
      puVar2 = &DAT_81c2b3e0 + uVar5;
      puVar6 = (undefined1 *)(param_2 + uVar7);
      uVar5 = uVar5 + 1 & 0xff;
      if (-1 < *pcVar1) {
        uVar7 = uVar7 + 1 & 0xff;
        *puVar6 = *puVar2;
      }
    } while (bVar3 < (byte)(&DAT_81c2b471)[iVar4]);
  }
  return uVar7;
}


#undef DAT_81c2b3e0
#undef DAT_81c2b470
#undef DAT_81c2b471

#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c182d0; body bytes 120 */

uint FUN_81c182d0(uint param_1,uint param_2)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  byte *pbVar4;

  iVar1 = FUN_81c152f0(0x3b,'\x01',g_sango_package_data);
  pbVar4 = (byte *)(iVar1 + (param_1 & 0xff) * 0x10);
  uVar3 = 0;
  pbVar2 = pbVar4;
  do {
    if ((uint)*pbVar2 == (param_2 & 0xff) + 1) {
      return uVar3;
    }
    uVar3 = uVar3 + 1 & 0xff;
    pbVar2 = pbVar4 + uVar3;
  } while (uVar3 < 8);
  return uVar3;
}


#undef g_sango_package_data


/* VA 0x81c18350; body bytes 48 */

void FUN_81c18350(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                 undefined1 *param_5)

{
  unsigned char sg_stack[20] __attribute__((aligned(8)));
  (*(undefined1 * *)(sg_stack + 0)) = param_5;
#define param_5 (*(undefined1 * *)(sg_stack + 0))

  param_5[7] = param_2;
  param_5[2] = param_3;
  param_5[3] = param_4;
  param_5[6] = param_1;
  *param_5 = param_1;
  param_5[1] = param_2;
  param_5[4] = param_1;
  param_5[5] = param_2;
  return;
}


#undef param_5


/* VA 0x81c18380; body bytes 144 */

undefined4
FUN_81c18380(byte param_1,byte param_2,int param_3,undefined1 *param_4,undefined1 *param_5)

{
  unsigned char sg_stack[20] __attribute__((aligned(8)));
  (*(undefined1 * *)(sg_stack + 0)) = param_5;
#define param_5 (*(undefined1 * *)(sg_stack + 0))

  char cVar1;
  int iVar2;
  undefined4 uVar3;

  iVar2 = (uint)*(byte *)(param_3 + 5) + (uint)param_2 + -1;
  uVar3 = 0;
  if (iVar2 <= (int)(uint)*(byte *)(param_3 + 3)) {
    cVar1 = *(byte *)(param_3 + 6) + 1;
    if ((int)((uint)*(byte *)(param_3 + 6) + (uint)param_1 + -1) <=
        (int)(uint)*(byte *)(param_3 + 2)) {
      *(byte *)(param_3 + 6) = param_1 + cVar1 + -1;
      *(char *)(param_3 + 4) = cVar1;
      uVar3 = 1;
      if ((int)(uint)*(byte *)(param_3 + 7) < iVar2) {
        *(byte *)(param_3 + 7) = param_2 + *(byte *)(param_3 + 5) + -1;
      }
      *param_4 = *(undefined1 *)(param_3 + 4);
      *param_5 = *(undefined1 *)(param_3 + 5);
    }
  }
  return uVar3;
}


#undef param_5


/* VA 0x81c18410; body bytes 56 */

uint FUN_81c18410(undefined1 *param_1)

{
  char cVar1;

  cVar1 = param_1[7];
  if (cVar1 != param_1[3]) {
    param_1[7] = cVar1 + '\x01';
    param_1[5] = cVar1 + '\x01';
    param_1[6] = *param_1;
    param_1[4] = *param_1;
  }
  return (uint)(cVar1 != param_1[3]);
}





/* VA 0x81c18450; body bytes 380 */

void FUN_81c18450(byte param_1,uint param_2,char param_3,char param_4,char param_5)

{
  unsigned char sg_stack[113] __attribute__((aligned(8)));
  (*(char *)(sg_stack + 96)) = param_5;
#define abStack_30 (*(byte (*)[8])(sg_stack + 32))
#define acStack_48 (*(char (*)[24])(sg_stack + 8))
#define auStack_28 (*(undefined1 (*)[8])(sg_stack + 40))
#define local_50 (*(byte *)(sg_stack + 0))
#define local_4f (*(byte (*)[7])(sg_stack + 1))
#define param_5 (*(char *)(sg_stack + 96))

  int iVar1;
  uint uVar2;
  byte *pbVar3;

  uVar2 = param_2 & 0xff;
  FUN_81c18350(param_3,param_4,param_3 + param_5 + -1,param_4 + '\f',auStack_28);
  iVar1 = FUN_81c18380(0x3d,0xc,(int)auStack_28,&local_50,local_4f);
  if (iVar1 != 0) {
    FUN_81c18c80(param_1,acStack_48);
    FUN_81c07b58(local_50 + 0x1e,(ushort)local_4f[0],acStack_48);
    FUN_81c154d8(2,7,abStack_30);
    for (; uVar2 < 5; uVar2 = uVar2 + 1 & 0xff) {
      pbVar3 = abStack_30 + uVar2;
      iVar1 = FUN_81c18380(*pbVar3 * '\x06' + 1,0xc,(int)auStack_28,&local_50,local_4f);
      if (iVar1 == 0) {
        return;
      }
      FUN_81c185cc((uint)param_1,(char)uVar2,acStack_48);
      FUN_81c07b58((ushort)*pbVar3 * 3 + (ushort)local_50,(ushort)local_4f[0],acStack_48);
    }
  }
  return;
}


#undef abStack_30
#undef acStack_48
#undef auStack_28
#undef local_50
#undef local_4f
#undef param_5

#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c185cc; body bytes 312 */

void FUN_81c185cc(uint param_1,undefined1 param_2,undefined1 *param_3)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint unaff_s3;

  iVar2 = FUN_81c152f0(0x42,'\x01',g_sango_package_data);
  iVar2 = iVar2 + (param_1 & 0xff) * 0x42;
  switch(param_2) {
  case 0:
    if (*(char *)(iVar2 + 1) == '\0') {
      unaff_s3 = 0x47;
    }
    else if (*(char *)(iVar2 + 1) == '\x01') {
      unaff_s3 = 0x48;
    }
    goto LAB_81c18654;
  case 1:
    uVar3 = (uint)*(byte *)(iVar2 + 0x3e);
    break;
  case 2:
    uVar3 = (uint)*(byte *)(iVar2 + 0x3f);
    break;
  case 3:
    uVar3 = (uint)*(byte *)(iVar2 + 0x40);
    break;
  case 4:
    bVar1 = *(byte *)(iVar2 + 0x41);
    if (bVar1 == 1) {
      unaff_s3 = 0x49;
    }
    else if (bVar1 < 2) {
      if (bVar1 == 0) {
        unaff_s3 = 0x32;
      }
    }
    else if (bVar1 == 2) {
      unaff_s3 = 0x4a;
    }
    else if (bVar1 == 3) {
      unaff_s3 = 0x4b;
    }
LAB_81c18654:
    FUN_81c154d8(0x40,unaff_s3,param_3);
  default:
    goto switchD_81c18634_default;
  }
  FUN_81c0a7e4(uVar3,param_3,10);
switchD_81c18634_default:
  return;
}


#undef g_sango_package_data


/* VA 0x81c18704; body bytes 368 */

uint FUN_81c18704(uint param_1,char param_2,char param_3,char param_4)

{
  unsigned char sg_stack[56] __attribute__((aligned(8)));
#define auStack_28 (*(undefined1 (*)[8])(sg_stack + 32))
#define local_48 (*(byte *)(sg_stack + 0))
#define local_47 (*(byte (*)[7])(sg_stack + 1))
#define abStack_30 (*(byte (*)[8])(sg_stack + 24))
#define acStack_40 (*(char (*)[16])(sg_stack + 8))

  int iVar1;
  uint uVar2;
  byte *pbVar3;

  FUN_81c18350(param_2,param_3,param_2 + param_4 + -1,param_3 + '\f',auStack_28);
  iVar1 = FUN_81c18380(0x3d,0xc,(int)auStack_28,&local_48,local_47);
  uVar2 = 0;
  if (iVar1 != 0) {
    FUN_81c154d8(0x40,0x41,acStack_40);
    FUN_81c07b58(local_48 + 0x1e,(ushort)local_47[0],acStack_40);
    FUN_81c154d8(2,7,abStack_30);
    uVar2 = param_1 & 0xff;
    while( true ) {
      pbVar3 = abStack_30 + uVar2;
      if (4 < uVar2) break;
      iVar1 = FUN_81c18380(*pbVar3 * '\x06' + 1,0xc,(int)auStack_28,&local_48,local_47);
      if (iVar1 == 0) {
        return uVar2;
      }
      FUN_81c154d8(0x40,uVar2 + 0x42 & 0xff,acStack_40);
      FUN_81c07b58((ushort)*pbVar3 * 3 + (ushort)local_48,(ushort)local_47[0],acStack_40);
      uVar2 = uVar2 + 1 & 0xff;
    }
  }
  return uVar2;
}


#undef auStack_28
#undef local_48
#undef local_47
#undef abStack_30
#undef acStack_40


/* VA 0x81c18874; body bytes 1036 */

uint FUN_81c18874(int param_1,uint param_2,uint param_3,uint param_4,byte param_5,byte param_6)

{
  unsigned char sg_stack[117] __attribute__((aligned(8)));
  (*(byte *)(sg_stack + 96)) = param_5;
  (*(byte *)(sg_stack + 100)) = param_6;
#define param_5 (*(byte *)(sg_stack + 96))
#define param_6 (*(byte *)(sg_stack + 100))
#define local_50 (*(byte (*)[8])(sg_stack + 0))
#define local_48 (*(int *)(sg_stack + 8))
#define local_44 (*(int *)(sg_stack + 12))
#define local_38 (*(uint *)(sg_stack + 24))
#define local_34 (*(uint *)(sg_stack + 28))
#define local_30 (*(int *)(sg_stack + 32))
#define local_2c (*(int *)(sg_stack + 36))

  bool bVar1;
  uint uVar2;
  uint uVar3;
  short sVar4;
  char cVar5;
  char cVar6;
  char cVar7;
  int iVar8;
  short sVar9;
  byte *pbVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;

  local_38 = (uint)param_5;
  uVar15 = param_2 & 0xff;
  uVar11 = param_4 & 0xff;
  if (uVar15 == 0) {
    return 0xff;
  }
  cVar7 = (param_5 - (char)param_3) + '\x01';
  local_34 = 0;
  uVar16 = 0;
  bVar1 = true;
  uVar14 = (int)((param_6 - uVar11) + 1) / 0xc - 1U & 0xff;
  if (uVar15 < uVar14) {
    uVar14 = uVar15;
  }
  local_30 = uVar14 * 2;
  FUN_81c08e7c((short)(param_3 & 0xff),(short)uVar11,(ushort)param_5,
               ((short)uVar11 + (short)uVar14 * 0xc + 0xcU & 0xff) + 1,3,0,0);
  uVar2 = (param_3 & 0xff) + 1;
  uVar13 = uVar2 & 0xff;
  local_38 = local_38 - 1 & 0xff;
  local_2c = (uVar13 + 0x3b) * 0x10000;
  uVar12 = uVar11 + 1 & 0xff;
  local_50[0] = 0;
  uVar18 = 0;
  do {
    sVar4 = (short)uVar13;
    uVar17 = uVar16;
    if (bVar1) goto LAB_81c18a44;
    while (FUN_81c1408c(&local_48), local_48 == 5) {
      sVar9 = (short)((uint)local_2c >> 0x10);
      if (local_44 == 0x67) {
        if (uVar18 == 0) break;
        iVar8 = uVar12 + (uVar18 - uVar16) * 0xc;
        FUN_81c0aae4(sVar4,(short)((uint)((iVar8 + 0xc) * 0x10000) >> 0x10),sVar9,
                     (short)((uint)((iVar8 + 0x17) * 0x10000) >> 0x10),0);
        uVar17 = uVar18 - 1 & 0xff;
        iVar8 = uVar17 - uVar16;
        uVar18 = uVar17;
        if (uVar16 <= uVar17) {
LAB_81c18bbc:
          iVar8 = uVar12 + iVar8 * 0xc;
          FUN_81c0aae4(sVar4,(short)((uint)((iVar8 + 0xc) * 0x10000) >> 0x10),sVar9,
                       (short)((uint)((iVar8 + 0x17) * 0x10000) >> 0x10),0);
          uVar18 = uVar17;
          break;
        }
      }
      else {
        if (local_44 < 0x68) {
          if (local_44 == 1) {
            return 0xff;
          }
          if (local_44 == 0x1c) {
            return uVar18;
          }
          break;
        }
        if (local_44 == 0x6a) {
          if (4 < local_50[local_34 + 1]) break;
          local_34 = local_34 + 1;
        }
        else {
          if (0x6a < local_44) {
            if ((local_44 == 0x6c) && ((int)uVar18 < (int)(uVar15 - 1))) {
              iVar8 = uVar12 + (uVar18 - uVar16) * 0xc;
              FUN_81c0aae4(sVar4,(short)((uint)((iVar8 + 0xc) * 0x10000) >> 0x10),sVar9,
                           (short)((uint)((iVar8 + 0x17) * 0x10000) >> 0x10),0);
              uVar18 = uVar18 + 1 & 0xff;
              if (uVar18 < uVar16 + uVar14) {
                iVar8 = uVar18 - uVar16;
                uVar17 = uVar18;
                goto LAB_81c18bbc;
              }
              uVar17 = (uVar18 - uVar14) + 1 & 0xff;
              goto LAB_81c18a44;
            }
            break;
          }
          if ((local_44 != 0x69) || (local_50[local_34] == 0)) break;
          local_34 = local_34 - 1;
        }
        local_34 = local_34 & 0xff;
        uVar17 = uVar16;
      }
LAB_81c18a44:
      FUN_81c0ac48(sVar4,(short)uVar12,(short)local_38,
                   (short)((uVar12 + (local_30 + uVar14) * 4 + 0xb) * 0x10000 >> 0x10),0,0);
      uVar16 = local_34;
      pbVar10 = local_50 + local_34;
      cVar5 = (char)uVar2;
      cVar6 = (char)(uVar11 + 1);
      uVar3 = FUN_81c18704((uint)*pbVar10,cVar5,cVar6,cVar7);
      local_50[uVar16 + 1] = (byte)uVar3;
      uVar16 = 0;
      if (uVar14 != 0) {
        iVar8 = 0;
        do {
          if (uVar15 <= uVar16) break;
          FUN_81c18450(*(byte *)(param_1 + uVar17 + uVar16),(uint)*pbVar10,cVar5,
                       cVar6 + ((char)iVar8 + (char)uVar16) * '\x04' + '\f',cVar7);
          uVar16 = uVar16 + 1 & 0xff;
          iVar8 = uVar16 << 1;
        } while (uVar16 < uVar14);
      }
      iVar8 = uVar12 + (uVar18 - uVar17) * 0xc;
      bVar1 = false;
      FUN_81c0aae4(sVar4,(short)((uint)((iVar8 + 0xc) * 0x10000) >> 0x10),
                   (short)((uint)local_2c >> 0x10),(short)((uint)((iVar8 + 0x17) * 0x10000) >> 0x10)
                   ,0);
      uVar16 = uVar17;
    }
  } while( true );
}


#undef param_5
#undef param_6
#undef local_50
#undef local_48
#undef local_44
#undef local_38
#undef local_34
#undef local_30
#undef local_2c


/* VA 0x81c18c80; body bytes 44 */

void FUN_81c18c80(char param_1,void *param_2)

{
  FUN_81c154d8(0x49,(byte)param_1 + 1 & 0xff,param_2);
  return;
}




#define DAT_81c2b161 (*(byte *)(0x81c2b161u))
/* VA 0x81c18cac; body bytes 476 */

void FUN_81c18cac(uint param_1,uint param_2,char param_3,char param_4,char param_5)

{
  unsigned char sg_stack[121] __attribute__((aligned(8)));
  (*(char *)(sg_stack + 104)) = param_5;
#define local_58 (*(byte *)(sg_stack + 0))
#define local_57 (*(byte (*)[7])(sg_stack + 1))
#define param_5 (*(char *)(sg_stack + 104))
#define abStack_38 (*(byte (*)[16])(sg_stack + 32))
#define acStack_50 (*(char (*)[24])(sg_stack + 8))
#define auStack_28 (*(undefined1 (*)[8])(sg_stack + 48))

  int iVar1;
  uint uVar2;
  ushort unaff_s1;
  byte *pbVar3;

  uVar2 = param_2 & 0xff;
  FUN_81c18350(param_3,param_4,param_3 + param_5 + -1,param_4 + '\f',auStack_28);
  iVar1 = FUN_81c18380(0x31,0xc,(int)auStack_28,&local_58,local_57);
  if (iVar1 != 0) {
    if (DAT_81c2b161 == 2) {
      unaff_s1 = 0x46;
    }
    else if (DAT_81c2b161 < 3) {
      if (DAT_81c2b161 == 1) {
        unaff_s1 = 0x3e;
      }
    }
    else if (DAT_81c2b161 == 3) {
      unaff_s1 = 0x47;
    }
    else if (DAT_81c2b161 == 4) {
      unaff_s1 = 0x48;
    }
    FUN_81c154d8(unaff_s1,(param_1 & 0xff) + 1 & 0xff,acStack_50);
    FUN_81c07b58(local_58 + 0x18,(ushort)local_57[0],acStack_50);
    FUN_81c154d8(2,8,abStack_38);
    for (; uVar2 < 0xd; uVar2 = uVar2 + 1 & 0xff) {
      pbVar3 = abStack_38 + uVar2;
      iVar1 = FUN_81c18380(*pbVar3 * '\x06' + 1,0xc,(int)auStack_28,&local_58,local_57);
      if (iVar1 == 0) {
        return;
      }
      FUN_81c18e88(param_1 & 0xff,(char)uVar2,acStack_50);
      FUN_81c07b58((ushort)*pbVar3 * 3 + (ushort)local_58,(ushort)local_57[0],acStack_50);
    }
  }
  return;
}


#undef DAT_81c2b161
#undef local_58
#undef local_57
#undef param_5
#undef abStack_38
#undef acStack_50
#undef auStack_28

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b161 (*(byte *)(0x81c2b161u))
/* VA 0x81c18e88; body bytes 632 */

void FUN_81c18e88(uint param_1,undefined1 param_2,undefined1 *param_3)

{
  char cVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint in_t1;

  uVar3 = param_1 & 0xff;
  iVar5 = uVar3 * 0x10;
  uVar4 = (uint)*(byte *)(iVar5 + DAT_81c2b164 + 1);
  switch(param_2) {
  case 0:
    if (uVar4 == 0xff) {
      uVar2 = 0x40;
      in_t1 = 0x31;
    }
    else {
      uVar2 = 0x40;
      if (uVar4 == uVar3 + 1) {
        in_t1 = 0x30;
      }
      else if (uVar4 == 0) {
        uVar2 = 0x40;
        in_t1 = 0x2f;
      }
      else {
        if (DAT_81c2b161 == 2) {
          uVar3 = 0x46;
        }
        else {
          uVar3 = in_t1;
          if (DAT_81c2b161 < 3) {
            if (DAT_81c2b161 == 1) {
              uVar3 = 0x3e;
            }
          }
          else if (DAT_81c2b161 == 3) {
            uVar3 = 0x47;
          }
          else if (DAT_81c2b161 == 4) {
            uVar3 = 0x48;
          }
        }
        in_t1 = (uVar4 - 1 & 0xff) + 1 & 0xff;
        uVar2 = (ushort)uVar3;
      }
    }
    goto LAB_81c18f2c;
  case 1:
    uVar3 = FUN_81c137f0((char)param_1);
    FUN_81c1971c((char)uVar3,param_3);
    return;
  case 2:
    uVar3 = (uint)*(byte *)(iVar5 + DAT_81c2b164 + 2);
    break;
  case 3:
    uVar3 = (uint)*(byte *)(iVar5 + DAT_81c2b164 + 3);
    break;
  case 4:
    uVar3 = (uint)*(byte *)(iVar5 + DAT_81c2b164 + 4);
    break;
  case 5:
    if ((uVar4 == uVar3 + 1) || (uVar4 == 0)) {
      uVar2 = 0x40;
      in_t1 = 0x33;
      goto LAB_81c18f2c;
    }
    uVar3 = (uint)*(byte *)(iVar5 + DAT_81c2b164 + 5);
    break;
  case 6:
    uVar3 = (uint)*(byte *)(iVar5 + DAT_81c2b164 + 7);
    break;
  case 7:
    uVar3 = (uint)*(byte *)(iVar5 + DAT_81c2b164 + 8);
    break;
  case 8:
    switch(*(undefined1 *)(iVar5 + DAT_81c2b164 + 9)) {
    case 0:
      in_t1 = 0x11;
      break;
    case 1:
      in_t1 = 0x12;
      break;
    case 2:
      in_t1 = 0x13;
      break;
    case 3:
      in_t1 = 0x14;
      break;
    case 4:
      in_t1 = 0x15;
      break;
    case 5:
      in_t1 = 0x16;
    }
    uVar2 = 0x40;
LAB_81c18f2c:
    FUN_81c154d8(uVar2,in_t1,param_3);
    return;
  case 9:
    uVar3 = (uint)*(ushort *)(iVar5 + DAT_81c2b164 + 10);
    break;
  case 10:
    uVar3 = (uint)*(byte *)(iVar5 + DAT_81c2b164 + 0xe);
    break;
  case 0xb:
    *param_3 = 0;
    cVar1 = *(char *)(iVar5 + DAT_81c2b164 + 0xc);
    goto LAB_81c190cc;
  case 0xc:
    *param_3 = 0;
    cVar1 = *(char *)(iVar5 + DAT_81c2b164 + 0xd);
LAB_81c190cc:
    if (cVar1 != '\0') {
      FUN_81c18c80(cVar1 + -1,param_3);
    }
  default:
    goto switchD_81c18ecc_default;
  }
  FUN_81c0a7e4(uVar3,param_3,10);
switchD_81c18ecc_default:
  return;
}


#undef DAT_81c2b164
#undef DAT_81c2b161


/* VA 0x81c19100; body bytes 368 */

uint FUN_81c19100(uint param_1,char param_2,char param_3,char param_4)

{
  unsigned char sg_stack[64] __attribute__((aligned(8)));
#define local_4f (*(byte (*)[7])(sg_stack + 1))
#define auStack_28 (*(undefined1 (*)[8])(sg_stack + 40))
#define abStack_38 (*(byte (*)[16])(sg_stack + 24))
#define acStack_48 (*(char (*)[16])(sg_stack + 8))
#define local_50 (*(byte *)(sg_stack + 0))

  int iVar1;
  uint uVar2;
  byte *pbVar3;

  FUN_81c18350(param_2,param_3,param_2 + param_4 + -1,param_3 + '\f',auStack_28);
  iVar1 = FUN_81c18380(0x31,0xc,(int)auStack_28,&local_50,local_4f);
  uVar2 = 0;
  if (iVar1 != 0) {
    FUN_81c154d8(0x40,0x17,acStack_48);
    FUN_81c07b58(local_50 + 0x18,(ushort)local_4f[0],acStack_48);
    FUN_81c154d8(2,8,abStack_38);
    uVar2 = param_1 & 0xff;
    while( true ) {
      pbVar3 = abStack_38 + uVar2;
      if (0xc < uVar2) break;
      iVar1 = FUN_81c18380(*pbVar3 * '\x06' + 1,0xc,(int)auStack_28,&local_50,local_4f);
      if (iVar1 == 0) {
        return uVar2;
      }
      FUN_81c154d8(0x40,uVar2 + 0x18 & 0xff,acStack_48);
      FUN_81c07b58((ushort)*pbVar3 * 3 + (ushort)local_50,(ushort)local_4f[0],acStack_48);
      uVar2 = uVar2 + 1 & 0xff;
    }
  }
  return uVar2;
}


#undef local_4f
#undef auStack_28
#undef abStack_38
#undef acStack_48
#undef local_50


/* VA 0x81c19270; body bytes 1196 */

uint FUN_81c19270(int param_1,uint param_2,uint param_3,uint param_4,byte param_5,byte param_6)

{
  unsigned char sg_stack[117] __attribute__((aligned(8)));
  (*(byte *)(sg_stack + 96)) = param_5;
  (*(byte *)(sg_stack + 100)) = param_6;
#define local_50 (*(byte (*)[8])(sg_stack + 0))
#define local_48 (*(int *)(sg_stack + 8))
#define local_44 (*(int *)(sg_stack + 12))
#define local_38 (*(uint *)(sg_stack + 24))
#define local_34 (*(uint *)(sg_stack + 28))
#define local_30 (*(uint *)(sg_stack + 32))
#define param_5 (*(byte *)(sg_stack + 96))
#define local_2c (*(int *)(sg_stack + 36))
#define param_6 (*(byte *)(sg_stack + 100))

  bool bVar1;
  uint uVar2;
  uint uVar3;
  short sVar4;
  char cVar5;
  short sVar6;
  int iVar7;
  char cVar8;
  short sVar9;
  char cVar10;
  short sVar11;
  int iVar12;
  uint uVar13;
  byte *pbVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;

  local_38 = (uint)param_5;
  uVar19 = param_2 & 0xff;
  uVar15 = param_4 & 0xff;
  if (uVar19 == 0) {
    return 0xff;
  }
  cVar10 = (param_5 - (char)param_3) + -1;
  local_30 = 0;
  uVar20 = 0;
  bVar1 = true;
  uVar18 = (int)((param_6 - uVar15) + -1) / 0xc - 1U & 0xff;
  if (uVar19 < uVar18) {
    uVar18 = uVar19;
  }
  local_34 = uVar15 + uVar18 * 0xc + 0xc & 0xff;
  FUN_81c08e7c((short)(param_3 & 0xff),(short)uVar15,(ushort)param_5,(short)local_34 + 1,3,0,0);
  uVar2 = (param_3 & 0xff) + 1;
  uVar17 = uVar2 & 0xff;
  local_38 = local_38 - 1 & 0xff;
  local_2c = (uVar17 + 0x2f) * 0x10000;
  uVar16 = uVar15 + 1 & 0xff;
  local_50[0] = 0;
  uVar21 = 0;
  do {
    sVar9 = (short)local_38;
    sVar4 = (short)uVar17;
    uVar13 = uVar21;
    if (bVar1) goto LAB_81c1947c;
    while (FUN_81c1408c(&local_48), uVar21 = uVar13, local_48 == 5) {
      sVar9 = (short)((uint)local_2c >> 0x10);
      if (local_44 == 0x68) {
        if (uVar20 == 0) break;
        if (uVar20 < uVar18) {
          uVar20 = 1;
        }
        else {
          uVar20 = (uVar20 - uVar18) + 1 & 0xff;
        }
        bVar1 = true;
LAB_81c19418:
        if (uVar20 == 0) break;
        iVar7 = uVar16 + (uVar20 - uVar13) * 0xc;
        FUN_81c0aae4(sVar4,(short)((uint)((iVar7 + 0xc) * 0x10000) >> 0x10),sVar9,
                     (short)((uint)((iVar7 + 0x17) * 0x10000) >> 0x10),0);
        uVar21 = uVar20 - 1 & 0xff;
        uVar20 = uVar21;
        if (uVar13 <= uVar21) {
          iVar7 = uVar16 + (uVar21 - uVar13) * 0xc;
          sVar6 = (short)((uint)((iVar7 + 0xc) * 0x10000) >> 0x10);
          sVar11 = (short)((uint)((iVar7 + 0x17) * 0x10000) >> 0x10);
LAB_81c1959c:
          FUN_81c0aae4(sVar4,sVar6,sVar9,sVar11,0);
          uVar21 = uVar13;
          break;
        }
      }
      else {
        if (local_44 < 0x69) {
          if (local_44 == 0x1c) {
            return uVar20;
          }
          if (local_44 < 0x1d) {
            if (local_44 == 1) {
              return 0xff;
            }
          }
          else if (local_44 == 0x67) goto LAB_81c19418;
          break;
        }
        if (local_44 != 0x6a) {
          if (local_44 < 0x6a) {
            uVar13 = local_30 - 1;
            if (local_50[local_30] != 0) goto LAB_81c196c8;
            break;
          }
          if (local_44 != 0x6c) {
            if (local_44 != 0x6d) break;
            if ((int)uVar20 < (int)(uVar19 - 2)) {
              uVar20 = (uVar20 + uVar18) - 1 & 0xff;
              if ((int)(uVar19 - 1) <= (int)uVar20) {
                uVar20 = uVar19 - 2 & 0xff;
              }
              bVar1 = true;
            }
          }
          if ((int)uVar20 < (int)(uVar19 - 1)) {
            iVar12 = uVar16 + (uVar20 - uVar13) * 0xc;
            iVar7 = iVar12 + 0xc;
            if (iVar7 < 0x8c) {
              FUN_81c0aae4(sVar4,(short)((uint)(iVar7 * 0x10000) >> 0x10),sVar9,
                           (short)((uint)((iVar12 + 0x17) * 0x10000) >> 0x10),0);
            }
            uVar20 = uVar20 + 1 & 0xff;
            if (uVar13 + uVar18 <= uVar20) {
              uVar21 = (uVar20 - uVar18) + 1 & 0xff;
              goto LAB_81c19478;
            }
            iVar7 = uVar16 + (uVar20 - uVar13) * 0xc;
            sVar6 = (short)((uint)((iVar7 + 0xc) * 0x10000) >> 0x10);
            sVar11 = (short)((uint)((iVar7 + 0x17) * 0x10000) >> 0x10);
            sVar9 = (short)((uint)local_2c >> 0x10);
            goto LAB_81c1959c;
          }
          break;
        }
        if (0xc < local_50[local_30 + 1]) break;
        uVar13 = local_30 + 1;
LAB_81c196c8:
        local_30 = uVar13 & 0xff;
      }
LAB_81c19478:
      sVar9 = (short)local_38;
LAB_81c1947c:
      FUN_81c0ac48(sVar4,(short)uVar16,sVar9,(short)local_34,0,0);
      uVar13 = local_30;
      pbVar14 = local_50 + local_30;
      cVar5 = (char)uVar2;
      cVar8 = (char)(uVar15 + 1);
      uVar3 = FUN_81c19100((uint)*pbVar14,cVar5,cVar8,cVar10);
      local_50[uVar13 + 1] = (byte)uVar3;
      uVar13 = 0;
      if (uVar18 != 0) {
        iVar7 = 0;
        do {
          if (uVar19 <= uVar13) break;
          FUN_81c18cac((uint)*(byte *)(param_1 + uVar21 + uVar13),(uint)*pbVar14,cVar5,
                       cVar8 + ((char)iVar7 + (char)uVar13) * '\x04' + '\f',cVar10);
          uVar13 = uVar13 + 1 & 0xff;
          iVar7 = uVar13 << 1;
        } while (uVar13 < uVar18);
      }
      iVar12 = uVar16 + (uVar20 - uVar21) * 0xc;
      iVar7 = iVar12 + 0xc;
      uVar13 = uVar21;
      if (iVar7 < 0x8c) {
        FUN_81c0aae4(sVar4,(short)((uint)(iVar7 * 0x10000) >> 0x10),(short)((uint)local_2c >> 0x10),
                     (short)((uint)((iVar12 + 0x17) * 0x10000) >> 0x10),0);
        bVar1 = false;
      }
      else {
        bVar1 = false;
      }
    }
  } while( true );
}


#undef local_50
#undef local_48
#undef local_44
#undef local_38
#undef local_34
#undef local_30
#undef param_5
#undef local_2c
#undef param_6


/* VA 0x81c1971c; body bytes 44 */

void FUN_81c1971c(char param_1,void *param_2)

{
  FUN_81c154d8(0x3a,(byte)param_1 + 1 & 0xff,param_2);
  return;
}




#define DAT_81c2b161 (*(byte *)(0x81c2b161u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define DAT_81c2b452 (*(undefined1 *)(0x81c2b452u))
#define DAT_81c2b454 (*(undefined2 *)(0x81c2b454u))
#define DAT_81c2b456 (*(undefined2 *)(0x81c2b456u))
#define DAT_81c2b458 (*(undefined2 *)(0x81c2b458u))
#define DAT_81c2b45a (*(undefined2 *)(0x81c2b45au))
#define DAT_81c2b45c (*(undefined1 *)(0x81c2b45cu))
#define DAT_81c2b45d (*(undefined1 *)(0x81c2b45du))
#define DAT_81c2b464 (*(undefined4 *)(0x81c2b464u))
#define DAT_81c2b468 (*(undefined2 *)(0x81c2b468u))
#define DAT_81c2b46a (*(undefined2 *)(0x81c2b46au))
#define DAT_81c2b46c (*(undefined2 *)(0x81c2b46cu))
/* VA 0x81c19748; body bytes 848 */

void FUN_81c19748(uint param_1,undefined1 param_2,char *param_3,uint param_4)

{
  unsigned char sg_stack[40] __attribute__((aligned(8)));
#define acStack_28 (*(char (*)[24])(sg_stack + 0))

  byte bVar1;
  ushort uVar2;
  uint uVar3;
  char *pcVar4;
  ushort unaff_s0;
  uint uVar5;

  uVar5 = param_1 & 0xff;
  *param_3 = '\0';
  switch(param_2) {
  case 0:
    FUN_81c154d8(0x40,2,param_3);
    bVar1 = (&DAT_81c2b451)[uVar5 * 0x24];
    goto LAB_81c197b0;
  case 1:
    FUN_81c154d8(0x40,3,param_3);
    bVar1 = (&DAT_81c2b452)[uVar5 * 0x24];
LAB_81c197b0:
    if (bVar1 == 0) {
      unaff_s0 = 0x40;
      uVar5 = 0x32;
    }
    else {
      if (DAT_81c2b161 == 2) {
        unaff_s0 = 0x46;
      }
      else if (DAT_81c2b161 < 3) {
        if (DAT_81c2b161 == 1) {
          unaff_s0 = 0x3e;
        }
      }
      else if (DAT_81c2b161 == 3) {
        unaff_s0 = 0x47;
      }
      else if (DAT_81c2b161 == 4) {
        unaff_s0 = 0x48;
      }
      uVar5 = (uint)bVar1;
    }
    FUN_81c154d8(unaff_s0,uVar5,param_3 + 5);
    return;
  case 2:
    FUN_81c154d8(0x40,4,param_3);
    FUN_81c0a7e4((uint)(ushort)(&DAT_81c2b456)[uVar5 * 0x12],acStack_28,10);
    bbk_strcat(param_3,acStack_28);
    uVar3 = bbk_strlen(param_3);
    param_3[uVar3 + 1] = '\0';
    uVar3 = bbk_strlen(param_3);
    param_3[uVar3] = '/';
    uVar2 = (&DAT_81c2b454)[uVar5 * 0x12];
    goto LAB_81c198e4;
  case 3:
    FUN_81c154d8(0x40,5,param_3);
    FUN_81c0a7e4((uint)(ushort)(&DAT_81c2b45a)[uVar5 * 0x12],acStack_28,10);
    bbk_strcat(param_3,acStack_28);
    uVar3 = bbk_strlen(param_3);
    param_3[uVar3 + 1] = '\0';
    uVar3 = bbk_strlen(param_3);
    param_3[uVar3] = '/';
    uVar2 = (&DAT_81c2b458)[uVar5 * 0x12];
LAB_81c198e4:
    uVar5 = (uint)uVar2;
    break;
  case 4:
    FUN_81c154d8(0x40,6,param_3);
    uVar5 = (uint)(byte)(&DAT_81c2b45c)[uVar5 * 0x24];
    break;
  case 5:
    FUN_81c154d8(0x40,7,param_3);
    uVar5 = (uint)(byte)(&DAT_81c2b45d)[uVar5 * 0x24];
    break;
  case 6:
    FUN_81c154d8(0x40,8,param_3);
    uVar5 = (&DAT_81c2b464)[uVar5 * 9];
    break;
  case 7:
    FUN_81c154d8(0x40,9,param_3);
    uVar5 = (uint)(ushort)(&DAT_81c2b468)[uVar5 * 0x12];
    break;
  case 8:
    FUN_81c154d8(0x40,10,param_3);
    uVar5 = (uint)(ushort)(&DAT_81c2b46a)[uVar5 * 0x12];
    break;
  case 9:
    FUN_81c154d8(0x40,0xb,param_3);
    uVar5 = (uint)(ushort)(&DAT_81c2b46c)[uVar5 * 0x12];
    break;
  case 10:
    pcVar4 = param_3;
    FUN_81c154d8(0x40,1,param_3);
    FUN_81c19a98(uVar5,acStack_28,pcVar4,param_4);
    goto LAB_81c198f4;
  default:
    goto switchD_81c19784_default;
  }
  FUN_81c0a7e4(uVar5,acStack_28,10);
LAB_81c198f4:
  bbk_strcat(param_3,acStack_28);
switchD_81c19784_default:
  return;
}


#undef DAT_81c2b161
#undef DAT_81c2b451
#undef DAT_81c2b452
#undef DAT_81c2b454
#undef DAT_81c2b456
#undef DAT_81c2b458
#undef DAT_81c2b45a
#undef DAT_81c2b45c
#undef DAT_81c2b45d
#undef DAT_81c2b464
#undef DAT_81c2b468
#undef DAT_81c2b46a
#undef DAT_81c2b46c
#undef acStack_28

#define DAT_81c2b450 (*(undefined1 *)(0x81c2b450u))
/* VA 0x81c19a98; body bytes 132 */

void FUN_81c19a98(uint param_1,void *param_2,undefined4 param_3,uint param_4)

{
  switch((&DAT_81c2b450)[(param_1 & 0xff) * 0x24]) {
  case 0:
    param_4 = 0xc;
    break;
  case 1:
    param_4 = 0xd;
    break;
  case 2:
    param_4 = 0xe;
    break;
  case 3:
    param_4 = 0xf;
    break;
  case 4:
    param_4 = 0x10;
  }
  FUN_81c154d8(0x40,param_4,param_2);
  return;
}


#undef DAT_81c2b450


/* VA 0x81c19b1c; body bytes 400 */

undefined4 FUN_81c19b1c(byte param_1)

{
  unsigned char sg_stack[56] __attribute__((aligned(8)));
#define acStack_48 (*(char (*)[32])(sg_stack + 0))
#define local_28 (*(int *)(sg_stack + 32))
#define local_24 (*(int *)(sg_stack + 36))

  bool bVar1;
  undefined4 uVar2;
  ushort uVar3;
  uint uVar4;
  ushort uVar5;
  ushort uVar6;

  uVar6 = 0;
  bVar1 = true;
  do {
    if (bVar1) goto LAB_81c19bdc;
    while (FUN_81c1408c(&local_28), local_28 == 5) {
      if (local_24 == 0x67) {
LAB_81c19bcc:
        uVar3 = uVar6 - 0x17;
        if (uVar6 == 0) break;
      }
      else {
        if (local_24 < 0x68) {
          uVar2 = 0;
          if ((local_24 == 1) || (uVar2 = 1, local_24 == 0x1c)) {
            return uVar2;
          }
          break;
        }
        if (local_24 != 0x6a) {
          if (local_24 < 0x6b) {
            if (local_24 == 0x69) goto LAB_81c19bcc;
            break;
          }
          if (local_24 != 0x6c) break;
        }
        uVar3 = uVar6 + 0x17;
        if (10 < uVar3) break;
      }
      uVar6 = uVar3 & 0xff;
LAB_81c19bdc:
      FUN_81c0ac48(0x45,2,0xa9,0x13a,0,0);
      uVar4 = 0x13b;
      FUN_81c08e7c(0x44,1,0xaa,0x13b,3,0,0);
      FUN_81c1971c(param_1,acStack_48);
      FUN_81c149dc(0x4a,2,acStack_48);
      uVar5 = 0;
      uVar3 = uVar6;
      do {
        FUN_81c19748((uint)param_1,(char)uVar3,acStack_48,uVar4);
        FUN_81c149dc(0x4a,uVar5 * 0xd + 0xe,acStack_48);
        uVar5 = uVar5 + 1 & 0xff;
        uVar3 = uVar6 + uVar5;
      } while (uVar5 < 0x17);
      bVar1 = false;
    }
  } while( true );
}


#undef acStack_48
#undef local_28
#undef local_24

#define DAT_81c2b161 (*(byte *)(0x81c2b161u))
/* VA 0x81c19cac; body bytes 132 */

void sango_load_named_text(uchar index,void *output)

{
  ushort in_a3;

  if (DAT_81c2b161 == 2) {
    in_a3 = 0x46;
  }
  else if (DAT_81c2b161 < 3) {
    if (DAT_81c2b161 == 1) {
      in_a3 = 0x3e;
    }
  }
  else if (DAT_81c2b161 == 3) {
    in_a3 = 0x47;
  }
  else if (DAT_81c2b161 == 4) {
    in_a3 = 0x48;
  }
  FUN_81c154d8(in_a3,index + 1 & 0xff,output);
  return;
}


#undef DAT_81c2b161

#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c2b190 (*(undefined1 *)(0x81c2b190u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
/* VA 0x81c19d30; body bytes 200 */

undefined4 FUN_81c19d30(void)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;

  while( true ) {
    uVar1 = FUN_81c12b18(&DAT_81c2b190);
    if (uVar1 == 0xff) break;
    if ((uint)(byte)(&DAT_81c2b451)[uVar1 * 0x24] == DAT_81c2b115 + 1) {
      uVar2 = FUN_81c0d3e0();
      if (uVar2 == 0xfe) {
        FUN_81c19b1c((byte)uVar1);
      }
      else if (uVar2 != 0xff) {
        FUN_81c0d618((byte)uVar1,(char)uVar2);
      }
    }
    else {
      bVar3 = 0x36;
      if ((byte)(&DAT_81c2b451)[uVar1 * 0x24] == 0) {
        bVar3 = 0x38;
      }
      FUN_81c17f44(bVar3);
    }
  }
  return 1;
}


#undef DAT_81c2b115
#undef DAT_81c2b190
#undef DAT_81c2b451

#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b450 (*(undefined1 *)(0x81c2b450u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define DAT_81c2b45d (*(undefined1 *)(0x81c2b45du))
#define DAT_81c2b468 (*(undefined2 *)(0x81c2b468u))
#define DAT_81c2b46a (*(undefined2 *)(0x81c2b46au))
/* VA 0x81c19df8; body bytes 404 */

void FUN_81c19df8(void)

{
  unsigned char sg_stack[32] __attribute__((aligned(8)));
#define abStack_20 (*(byte (*)[8])(sg_stack + 0))
#define abStack_18 (*(byte (*)[8])(sg_stack + 8))

  char cVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  byte bVar5;
  uint uVar6;
  uint uVar7;

  FUN_81c154d8(2,0xc,abStack_20);
  FUN_81c154d8(2,0xd,abStack_18);
  uVar7 = 0;
  do {
    iVar3 = uVar7 * 0x24;
    uVar6 = (uint)(byte)(&DAT_81c2b451)[iVar3];
    (&DAT_81c2b450)[iVar3] = 0;
    if ((uVar6 != 0) && (uVar6 != DAT_81c2b115 + 1)) {
      cVar1 = (&DAT_81c2b45d)[iVar3];
      (&DAT_81c2b45d)[iVar3] = cVar1 + 1U;
      if (100 < (byte)(cVar1 + 1U)) {
        (&DAT_81c2b45d)[iVar3] = 100;
      }
      if ((ushort)(&DAT_81c2b46a)[uVar7 * 0x12] < 100) {
        (&DAT_81c2b46a)[uVar7 * 0x12] = 500;
      }
      if (10000 < (ushort)(&DAT_81c2b468)[uVar7 * 0x12]) {
        (&DAT_81c2b468)[uVar7 * 0x12] = (ushort)(&DAT_81c2b468)[uVar7 * 0x12] >> 1;
      }
      uVar4 = bbk_rand();
      bVar2 = *(byte *)(uVar6 * 0x10 + DAT_81c2b164 + -10);
      uVar6 = (int)uVar4 % 100 & 0xff;
      bVar5 = (byte)uVar7;
      if (uVar6 < abStack_20[bVar2]) {
        FUN_81c19f8c(bVar5);
        FUN_81c1a480(bVar5);
      }
      else if (uVar6 < abStack_18[bVar2]) {
        FUN_81c1a188(bVar5);
      }
      else {
        FUN_81c1a6a4(bVar5);
      }
    }
    uVar7 = uVar7 + 1 & 0xff;
  } while (uVar7 < 0x26);
  return;
}


#undef DAT_81c2b115
#undef DAT_81c2b164
#undef DAT_81c2b450
#undef DAT_81c2b451
#undef DAT_81c2b45d
#undef DAT_81c2b468
#undef DAT_81c2b46a
#undef abStack_20
#undef abStack_18

#define DAT_81c2b454 (*(undefined2 *)(0x81c2b454u))
#define DAT_81c2b456 (*(undefined2 *)(0x81c2b456u))
#define DAT_81c2b458 (*(undefined2 *)(0x81c2b458u))
#define DAT_81c2b45a (*(undefined2 *)(0x81c2b45au))
#define DAT_81c2b45c (*(undefined1 *)(0x81c2b45cu))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
#define DAT_81c2b460 (*(undefined4 *)(0x81c2b460u))
#define DAT_81c2b464 (*(undefined4 *)(0x81c2b464u))
/* VA 0x81c19f8c; body bytes 508 */

void FUN_81c19f8c(byte param_1)

{
  unsigned char sg_stack[44] __attribute__((aligned(8)));
#define local_38 (*(int *)(sg_stack + 16))
#define local_34 (*(uint *)(sg_stack + 20))
#define local_30 (*(uint *)(sg_stack + 24))
#define local_48 (*(undefined1 *)(sg_stack + 0))
#define local_47 (*(byte *)(sg_stack + 1))
#define local_46 (*(byte *)(sg_stack + 2))
#define local_45 (*(byte *)(sg_stack + 3))
#define local_3d (*(undefined1 *)(sg_stack + 11))

  byte bVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  uint uVar7;
  uint *puVar8;
  byte *pbVar9;
  ushort *puVar10;
  ushort *puVar11;

  uVar3 = (uint)param_1;
  local_38 = g_scratch_buffer_4096;
  local_30 = (uint)(ushort)(&DAT_81c2b454)[uVar3 * 0x12];
  local_34 = (uint)(ushort)(&DAT_81c2b458)[uVar3 * 0x12];
  uVar4 = FUN_81c13870(uVar3,g_scratch_buffer_4096);
  puVar11 = &DAT_81c2b456 + uVar3 * 0x12;
  puVar10 = &DAT_81c2b45a + uVar3 * 0x12;
  pbVar9 = &DAT_81c2b45c + uVar3 * 0x24;
  puVar8 = &DAT_81c2b464 + uVar3 * 9;
  uVar7 = 0;
  if (uVar4 != 0) {
    do {
      uVar5 = bbk_rand();
      switch((int)uVar5 % 5 & 0xff) {
      case 0:
        uVar2 = *puVar11;
        *puVar11 = uVar2 + 200;
        if (local_30 < (ushort)(uVar2 + 200)) {
          *puVar11 = (ushort)local_30;
        }
        local_48 = 1;
        break;
      case 1:
        uVar2 = *puVar10;
        *puVar10 = uVar2 + 200;
        if (local_34 < (ushort)(uVar2 + 200)) {
          *puVar10 = (ushort)local_34;
        }
        local_48 = 2;
        break;
      case 2:
        local_48 = 3;
        break;
      case 3:
        bVar1 = *pbVar9;
        *pbVar9 = bVar1 + 4;
        if (100 < (byte)(bVar1 + 4)) {
          *pbVar9 = 100;
        }
        uVar5 = *puVar8;
        *puVar8 = uVar5 + 100;
        if ((uint)(&DAT_81c2b460)[uVar3 * 9] < uVar5 + 100) {
          *puVar8 = (&DAT_81c2b460)[uVar3 * 9];
        }
        local_48 = 5;
        break;
      case 4:
        goto switchD_81c1a094_caseD_4;
      }
      pbVar6 = (byte *)(local_38 + uVar7);
      local_47 = *pbVar6;
      local_3d = 0;
      local_46 = param_1;
      local_45 = param_1;
      FUN_81c116f0(&local_48);
      FUN_81c123f0(uVar3,*pbVar6);
switchD_81c1a094_caseD_4:
      uVar7 = uVar7 + 1 & 0xff;
    } while (uVar7 < uVar4);
  }
  return;
}


#undef DAT_81c2b454
#undef DAT_81c2b456
#undef DAT_81c2b458
#undef DAT_81c2b45a
#undef DAT_81c2b45c
#undef g_scratch_buffer_4096
#undef DAT_81c2b460
#undef DAT_81c2b464
#undef local_38
#undef local_34
#undef local_30
#undef local_48
#undef local_47
#undef local_46
#undef local_45
#undef local_3d

#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c1a188; body bytes 760 */

void FUN_81c1a188(byte param_1)

{
  unsigned char sg_stack[28] __attribute__((aligned(8)));
#define local_30 (*(undefined1 *)(sg_stack + 0))
#define local_2f (*(byte *)(sg_stack + 1))
#define local_2e (*(byte *)(sg_stack + 2))
#define local_2d (*(byte *)(sg_stack + 3))
#define local_25 (*(undefined1 *)(sg_stack + 11))

  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  byte bVar6;
  byte *pbVar7;
  byte *pbVar8;
  uint uVar9;

  iVar2 = g_scratch_buffer_4096;
  uVar1 = (uint)param_1;
  uVar3 = FUN_81c13870(uVar1,g_scratch_buffer_4096);
  pbVar8 = (byte *)(iVar2 + 200);
  uVar9 = 0;
  if (uVar3 != 0) {
    do {
      uVar4 = bbk_rand();
      uVar5 = uVar4 + 7;
      if (-1 < (int)uVar4) {
        uVar5 = uVar4;
      }
      uVar4 = uVar4 + ((int)uVar5 >> 3) * -8 & 0xff;
      uVar5 = FUN_81c139a8(uVar1,(int)pbVar8);
      if (uVar5 != 0) {
        uVar4 = 0;
      }
      switch(uVar4) {
      case 0:
        if (uVar5 != 0) {
          uVar4 = bbk_rand();
          if (uVar5 == 0) {
            trap(7);
          }
          pbVar7 = (byte *)((uint)pbVar8[(int)uVar4 % (int)uVar5 & 0xff] * 0x10 + DAT_81c2b164);
          if ((uint)*pbVar7 == DAT_81c2b115 + 1) {
            FUN_81c123f0(uVar1,pbVar8[(int)uVar4 % (int)uVar5 & 0xff]);
            local_30 = 6;
            goto switchD_81c1a250_default;
          }
          pbVar7[1] = (&DAT_81c2b451)[uVar1 * 0x24];
        }
        break;
      case 1:
        if (uVar5 != 0) {
          uVar4 = bbk_rand();
          if (uVar5 == 0) {
            trap(7);
          }
          bVar6 = pbVar8[(int)uVar4 % (int)uVar5 & 0xff];
          goto LAB_81c1a320;
        }
        break;
      case 2:
      case 7:
        break;
      case 3:
        uVar5 = FUN_81c1297c(uVar1,(int)pbVar8);
        if (uVar5 != 0) {
          uVar4 = bbk_rand();
          if (uVar5 == 0) {
            trap(7);
          }
          local_2d = pbVar8[(int)uVar4 % (int)uVar5 & 0xff];
          local_30 = 0xf;
          goto switchD_81c1a250_default;
        }
        break;
      case 4:
        uVar5 = FUN_81c1297c(uVar1,(int)pbVar8);
        if (uVar5 != 0) {
          uVar4 = bbk_rand();
          if (uVar5 == 0) {
            trap(7);
          }
          local_2d = pbVar8[(int)uVar4 % (int)uVar5 & 0xff];
          local_30 = 0x10;
          goto switchD_81c1a250_default;
        }
        break;
      case 5:
        uVar5 = FUN_81c13a40(uVar1,(int)pbVar8);
        if (uVar5 != 0) {
          uVar4 = bbk_rand();
          if (uVar5 == 0) {
            trap(7);
          }
          local_2d = pbVar8[(int)uVar4 % (int)uVar5 & 0xff];
          local_30 = 0x11;
          goto switchD_81c1a250_default;
        }
        break;
      case 6:
        uVar5 = FUN_81c12a68(uVar1,pbVar8);
        if (uVar5 != 0) {
          uVar4 = bbk_rand();
          if (uVar5 == 0) {
            trap(7);
          }
          local_2d = pbVar8[(int)uVar4 % (int)uVar5 & 0xff];
          local_30 = 0x13;
          goto switchD_81c1a250_default;
        }
        break;
      default:
switchD_81c1a250_default:
        pbVar7 = (byte *)(iVar2 + uVar9);
        local_2f = *pbVar7;
        local_25 = 0;
        local_2e = param_1;
        FUN_81c116f0(&local_30);
        bVar6 = *pbVar7;
LAB_81c1a320:
        FUN_81c123f0(uVar1,bVar6);
        goto LAB_81c1a264;
      }
LAB_81c1a264:
      uVar9 = uVar9 + 1 & 0xff;
    } while (uVar9 < uVar3);
  }
  return;
}


#undef DAT_81c2b115
#undef DAT_81c2b164
#undef DAT_81c2b451
#undef g_scratch_buffer_4096
#undef local_30
#undef local_2f
#undef local_2e
#undef local_2d
#undef local_25

#define DAT_81c2b450 (*(undefined1 *)(0x81c2b450u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define DAT_81c2b45d (*(undefined1 *)(0x81c2b45du))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c1a480; body bytes 548 */

void FUN_81c1a480(byte param_1)

{
  unsigned char sg_stack[36] __attribute__((aligned(8)));
#define local_40 (*(undefined1 *)(sg_stack + 0))
#define local_3f (*(byte *)(sg_stack + 1))
#define local_3e (*(byte *)(sg_stack + 2))
#define local_3d (*(byte *)(sg_stack + 3))
#define local_35 (*(undefined1 *)(sg_stack + 11))
#define local_30 (*(uint *)(sg_stack + 16))

  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  byte *pbVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  byte *pbVar11;

  iVar3 = g_scratch_buffer_4096;
  uVar2 = (uint)param_1;
  iVar4 = uVar2 * 0x24;
  uVar5 = FUN_81c13870(uVar2,g_scratch_buffer_4096);
  pbVar11 = (byte *)(iVar3 + 200);
  uVar10 = 0;
  if (uVar5 != 0) {
    do {
      uVar6 = bbk_rand();
      switch((int)uVar6 % 7 & 0xff) {
      case 0:
        cVar1 = (&DAT_81c2b45d)[iVar4];
        (&DAT_81c2b450)[iVar4] = 0;
        (&DAT_81c2b45d)[iVar4] = cVar1 + 4U;
        if (100 < (byte)(cVar1 + 4U)) {
          (&DAT_81c2b45d)[iVar4] = 100;
        }
        local_40 = 4;
      default:
switchD_81c1a570_default:
        local_3f = *(byte *)(iVar3 + uVar10);
        local_35 = 0;
        local_3e = param_1;
        FUN_81c116f0(&local_40);
        FUN_81c123f0(uVar2,*(byte *)(iVar3 + uVar10));
      case 1:
      case 2:
      case 3:
      case 4:
      case 6:
        break;
      case 5:
        if ((2 < uVar10) &&
           (uVar6 = FUN_81c13794((byte)(&DAT_81c2b451)[iVar4] - 1 & 0xff,(int)pbVar11), 1 < uVar6))
        {
          local_30 = 0;
          uVar9 = 0;
          pbVar7 = pbVar11;
          if (uVar6 != 0) {
            do {
              uVar8 = FUN_81c128b4((uint)*pbVar7,iVar3 + 0xee);
              if ((uVar8 != 0) &&
                 (uVar8 = bbk_rand(), local_30 = uVar9, ((int)uVar8 % 2 & 0xffU) != 0)) break;
              uVar9 = uVar9 + 1 & 0xff;
              pbVar7 = pbVar11 + uVar9;
            } while (uVar9 < uVar6);
          }
          local_3d = pbVar11[local_30];
          local_40 = 0xe;
          goto switchD_81c1a570_default;
        }
      }
      uVar10 = uVar10 + 1 & 0xff;
    } while (uVar10 < uVar5);
  }
  return;
}


#undef DAT_81c2b450
#undef DAT_81c2b451
#undef DAT_81c2b45d
#undef g_scratch_buffer_4096
#undef local_40
#undef local_3f
#undef local_3e
#undef local_3d
#undef local_35
#undef local_30

#define DAT_81c2b170 (*(byte *)(0x81c2b170u))
#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b46a (*(undefined2 *)(0x81c2b46au))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c1a6a4; body bytes 1040 */

void FUN_81c1a6a4(byte param_1)

{
  unsigned char sg_stack[44] __attribute__((aligned(8)));
#define local_38 (*(undefined1 *)(sg_stack + 16))
#define local_37 (*(byte *)(sg_stack + 17))
#define local_36 (*(byte *)(sg_stack + 18))
#define local_35 (*(undefined1 *)(sg_stack + 19))
#define local_34 (*(undefined2 *)(sg_stack + 20))
#define local_32 (*(undefined2 *)(sg_stack + 22))
#define local_2d (*(undefined1 *)(sg_stack + 27))
#define local_48 (*(char (*)[16])(sg_stack + 0))

  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  byte bVar8;
  char *pcVar9;
  int iVar10;
  uint uVar11;
  byte *pbVar12;
  byte *pbVar13;
  uint uVar14;

  iVar3 = g_scratch_buffer_4096;
  uVar2 = (uint)param_1;
  uVar4 = FUN_81c13870(uVar2,g_scratch_buffer_4096);
  pbVar13 = (byte *)(iVar3 + 200);
  if (uVar4 != 0) {
    uVar5 = bbk_rand();
    if (uVar4 == 0) {
      trap(7);
    }
    iVar10 = DAT_81c2b164 + (uint)*(byte *)(iVar3 + (int)uVar5 % (int)uVar4) * 0x10;
    if (((uint)DAT_81c2b170 % 3 == 0) &&
       (bVar8 = *(char *)(iVar10 + 2) + 1, *(byte *)(iVar10 + 2) = bVar8, 0x14 < bVar8)) {
      *(undefined1 *)(iVar10 + 2) = 0x14;
    }
    uVar5 = 0;
    if (uVar4 != 0) {
      do {
        uVar6 = bbk_rand();
        switch((int)uVar6 % 9 & 0xff) {
        case 0:
          local_38 = 0x17;
          break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
          iVar10 = DAT_81c2b164 + (uint)*(byte *)(iVar3 + uVar5) * 0x10;
          *(ushort *)(iVar10 + 10) =
               ((ushort)*(byte *)(iVar10 + 2) * 10 +
               (ushort)*(byte *)(iVar10 + 3) + (ushort)*(byte *)(iVar10 + 4)) * 10;
          local_38 = 0x18;
          local_34 = 0;
          break;
        case 6:
          local_38 = 0x1a;
          break;
        case 7:
          if (uVar5 == 0) {
            uVar6 = FUN_81c128b4(uVar2,(int)pbVar13);
            if (uVar6 == 0) break;
            uVar7 = bbk_rand();
            if (uVar6 << 1 == 0) {
              trap(7);
            }
            if (((int)uVar7 % (int)(uVar6 << 1) & 0xffU) < uVar6) {
              uVar6 = FUN_81c11c28(uVar6,(int)pbVar13);
              local_35 = (undefined1)uVar6;
              uVar6 = FUN_81c13870(uVar2,(int)pbVar13);
              if (uVar6 == 0) break;
              uVar7 = uVar6 - 1;
              iVar10 = DAT_81c2b164;
              if ((int)uVar7 < 1) {
                bVar8 = *pbVar13;
              }
              else {
                uVar11 = 0;
                do {
                  uVar14 = uVar11 + 1 & 0xff;
                  if (uVar14 < uVar6) {
                    do {
                      bVar8 = pbVar13[uVar11];
                      bVar1 = pbVar13[uVar14];
                      if (*(ushort *)((uint)bVar8 * 0x10 + iVar10 + 10) <
                          *(ushort *)((uint)bVar1 * 0x10 + iVar10 + 10)) {
                        pbVar13[uVar14] = bVar8;
                        pbVar13[uVar11] = bVar1;
                        iVar10 = DAT_81c2b164;
                      }
                      if (*(short *)((uint)pbVar13[uVar4 - 1] * 0x10 + iVar10 + 10) == 0) {
                        uVar6 = uVar7 & 0xff;
                        uVar7 = uVar6 - 1;
                      }
                      uVar14 = uVar14 + 1 & 0xff;
                    } while (uVar14 < uVar6);
                  }
                  uVar11 = uVar11 + 1 & 0xff;
                } while ((int)uVar11 < (int)uVar7);
                bVar8 = *pbVar13;
              }
              if ((999 < *(ushort *)((uint)bVar8 * 0x10 + iVar10 + 10)) && (3 < uVar6)) {
                uVar7 = uVar7 & 0xff;
                local_38 = 0x1b;
                FUN_81c0a7c8(local_48,0,10);
                if (10 < uVar7) {
                  uVar7 = 10;
                }
                uVar4 = 0;
                if (uVar7 != 0) {
                  do {
                    pbVar12 = pbVar13 + uVar4;
                    FUN_81c123f0(uVar2,*pbVar12);
                    pcVar9 = local_48 + uVar4;
                    uVar4 = uVar4 + 1 & 0xff;
                    *pcVar9 = *pbVar12 + 1;
                  } while (uVar4 < uVar7);
                }
                local_32 = (&DAT_81c2b46a)[uVar2 * 0x12];
                local_2d = 0;
                local_36 = param_1;
                FUN_81c11564(&local_38,local_48);
                return;
              }
            }
          }
          goto LAB_81c1a810;
        case 8:
          break;
        default:
          local_37 = *(byte *)(iVar3 + uVar5);
          local_2d = 0;
          local_36 = param_1;
          FUN_81c116f0(&local_38);
          FUN_81c123f0(uVar2,*(byte *)(iVar3 + uVar5));
          goto LAB_81c1a810;
        }
LAB_81c1a810:
        uVar5 = uVar5 + 1 & 0xff;
      } while (uVar5 < uVar4);
    }
  }
  return;
}


#undef DAT_81c2b170
#undef DAT_81c2b164
#undef DAT_81c2b46a
#undef g_scratch_buffer_4096
#undef local_38
#undef local_37
#undef local_36
#undef local_35
#undef local_34
#undef local_32
#undef local_2d
#undef local_48

#define DAT_81c2b170 (*(byte *)(0x81c2b170u))
#define DAT_81c2b140 (*(short *)(0x81c2b140u))
/* VA 0x81c1aab4; body bytes 288 */

undefined4 FUN_81c1aab4(void)

{
  uint uVar1;
  int iVar2;

  while( true ) {
    uVar1 = FUN_81c1ac04();
    if (uVar1 != 0) {
      FUN_81c17f44(0x59);
      return 1;
    }
    uVar1 = FUN_81c1abd4();
    if (uVar1 != 0) break;
    FUN_81c1ac34();
    while( true ) {
      do {
        FUN_81c19d30();
        iVar2 = FUN_81c1b2b4();
      } while (iVar2 == 0);
      if (iVar2 == 1) break;
      if (iVar2 == 2) {
        return 2;
      }
    }
    FUN_81c1b784();
    FUN_81c19df8();
    FUN_81c0d354();
    DAT_81c2b170 = DAT_81c2b170 + 1;
    if (0xc < DAT_81c2b170) {
      DAT_81c2b170 = 1;
      DAT_81c2b140 = DAT_81c2b140 + 1;
      FUN_81c17e18();
      FUN_81c17734();
    }
    FUN_81c16e00();
    FUN_81c1740c();
    FUN_81c171cc();
  }
  FUN_81c17f44(0x5a);
  return 0;
}


#undef DAT_81c2b170
#undef DAT_81c2b140

#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c1abd4; body bytes 48 */

uint FUN_81c1abd4(void)

{
  uint uVar1;

  uVar1 = FUN_81c12a68((uint)DAT_81c2b115,g_scratch_buffer_4096);
  return (uint)(uVar1 == 0);
}


#undef DAT_81c2b115
#undef g_scratch_buffer_4096

#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c1ac04; body bytes 48 */

uint FUN_81c1ac04(void)

{
  uint uVar1;

  uVar1 = FUN_81c13794((uint)DAT_81c2b115,g_scratch_buffer_4096);
  return (uint)(uVar1 == 0);
}


#undef DAT_81c2b115
#undef g_scratch_buffer_4096

#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b310 (*(undefined1 *)(0x81c2b310u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define DAT_81c2b452 (*(undefined1 *)(0x81c2b452u))
#define DAT_81c2b46e (*(undefined1 *)(0x81c2b46eu))
#define DAT_81c2b46f (*(undefined1 *)(0x81c2b46fu))
/* VA 0x81c1ac34; body bytes 252 */

void FUN_81c1ac34(void)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;

  uVar7 = 0;
  iVar10 = 0;
  do {
    iVar1 = (iVar10 + uVar7) * 4;
    uVar6 = (uint)(byte)(&DAT_81c2b451)[iVar1];
    uVar8 = 0;
    if (uVar6 == 0) {
      (&DAT_81c2b452)[iVar1] = 0;
    }
    else {
      uVar5 = 0;
      uVar9 = uVar8;
      if ((byte)(&DAT_81c2b46f)[iVar1] != 0) {
        pbVar2 = &DAT_81c2b310 + (byte)(&DAT_81c2b46e)[iVar1];
        do {
          iVar3 = (uint)*pbVar2 * 0x10 + DAT_81c2b164;
          uVar4 = *pbVar2 + 1;
          if (*(byte *)(iVar3 + 1) == uVar6) {
            uVar9 = uVar6;
            if (uVar6 == uVar4) break;
            if ((uVar8 == 0) ||
               (*(byte *)(uVar8 * 0x10 + DAT_81c2b164 + -0xc) < *(byte *)(iVar3 + 4))) {
              uVar8 = uVar4 & 0xff;
            }
          }
          uVar5 = uVar5 + 1 & 0xff;
          pbVar2 = &DAT_81c2b310 + (byte)(&DAT_81c2b46e)[iVar1] + uVar5;
          uVar9 = uVar8;
        } while (uVar5 < (byte)(&DAT_81c2b46f)[iVar1]);
      }
      (&DAT_81c2b452)[(iVar10 + uVar7) * 4] = (char)uVar9;
    }
    uVar7 = uVar7 + 1 & 0xff;
    iVar10 = uVar7 << 3;
    if (0x25 < uVar7) {
      return;
    }
  } while( true );
}


#undef DAT_81c2b164
#undef DAT_81c2b310
#undef DAT_81c2b451
#undef DAT_81c2b452
#undef DAT_81c2b46e
#undef DAT_81c2b46f

#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
/* VA 0x81c1ad30; body bytes 164 */

uint FUN_81c1ad30(byte *param_1)

{
  byte bVar1;
  bool bVar2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;

  uVar5 = 0;
  uVar6 = 0;
  do {
    bVar1 = (&DAT_81c2b451)[uVar6 * 0x24];
    if (bVar1 != 0) {
      uVar4 = 0;
      if (uVar5 == 0) {
        bVar2 = false;
LAB_81c1adbc:
        if (bVar2) goto LAB_81c1ada0;
      }
      else {
        pbVar3 = param_1;
        do {
          if ((uint)*pbVar3 == bVar1 - 1) {
            bVar2 = uVar4 < uVar5;
            goto LAB_81c1adbc;
          }
          uVar4 = uVar4 + 1 & 0xff;
          pbVar3 = param_1 + uVar4;
        } while (uVar4 < uVar5);
      }
      param_1[uVar5] = bVar1 - 1;
      uVar5 = uVar5 + 1 & 0xff;
    }
LAB_81c1ada0:
    uVar6 = uVar6 + 1 & 0xff;
    if (0x25 < uVar6) {
      return uVar5;
    }
  } while( true );
}


#undef DAT_81c2b451

#define DAT_81c2b140 (*(short *)(0x81c2b140u))
#define DAT_81c2b164 (*(int *)(0x81c2b164u))
#define DAT_81c2b161 (*(char *)(0x81c2b161u))
#define DAT_81c2b170 (*(undefined1 *)(0x81c2b170u))
#define DAT_81c2b310 (*(undefined1 *)(0x81c2b310u))
#define DAT_81c2b3e0 (*(undefined1 *)(0x81c2b3e0u))
#define DAT_81c2b450 (*(undefined1 *)(0x81c2b450u))
#define DAT_81c2b451 (*(undefined1 *)(0x81c2b451u))
#define DAT_81c2b452 (*(undefined1 *)(0x81c2b452u))
#define DAT_81c2b454 (*(undefined2 *)(0x81c2b454u))
#define DAT_81c2b456 (*(undefined2 *)(0x81c2b456u))
#define DAT_81c2b458 (*(undefined2 *)(0x81c2b458u))
#define DAT_81c2b45a (*(undefined2 *)(0x81c2b45au))
#define DAT_81c2b45c (*(undefined1 *)(0x81c2b45cu))
#define DAT_81c2b45d (*(undefined1 *)(0x81c2b45du))
#define DAT_81c2b460 (*(undefined4 *)(0x81c2b460u))
#define DAT_81c2b464 (*(undefined4 *)(0x81c2b464u))
#define DAT_81c2b468 (*(undefined2 *)(0x81c2b468u))
#define DAT_81c2b46a (*(undefined2 *)(0x81c2b46au))
#define DAT_81c2b46c (*(undefined2 *)(0x81c2b46cu))
#define DAT_81c2b46e (*(undefined1 *)(0x81c2b46eu))
#define DAT_81c2b46f (*(undefined1 *)(0x81c2b46fu))
#define DAT_81c2b470 (*(undefined1 *)(0x81c2b470u))
#define DAT_81c2b471 (*(undefined1 *)(0x81c2b471u))
#define g_state_buffer_1200 (*(undefined4 *)(0x81c2b0e4u))
#define g_state_buffer_30 (*(undefined4 *)(0x81c2b0ecu))
#define g_sango_package_data (*(undefined4 *)(0x81c2b154u))
/* VA 0x81c1add4; body bytes 1248 */

void FUN_81c1add4(char param_1)

{
  byte bVar1;
  undefined1 *puVar2;
  int iVar3;
  void *pvVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  undefined1 *puVar9;
  undefined1 *puVar10;

  puVar2 = (undefined1 *)FUN_81c152f0(0x39,param_1,g_sango_package_data);
  uVar8 = 0;
  puVar10 = puVar2;
  do {
    iVar7 = uVar8 * 0x24;
    (&DAT_81c2b450)[iVar7] = *puVar10;
    (&DAT_81c2b451)[iVar7] = puVar10[1];
    (&DAT_81c2b452)[iVar7] = puVar10[2];
    bVar1 = puVar10[4];
    (&DAT_81c2b454)[uVar8 * 0x12] = (ushort)bVar1 * 0x100;
    (&DAT_81c2b454)[uVar8 * 0x12] = (ushort)bVar1 * 0x100 + (ushort)(byte)puVar10[3];
    bVar1 = puVar10[6];
    uVar6 = uVar8 + 1 & 0xff;
    (&DAT_81c2b456)[uVar8 * 0x12] = (ushort)bVar1 * 0x100;
    (&DAT_81c2b456)[uVar8 * 0x12] = (ushort)bVar1 * 0x100 + (ushort)(byte)puVar10[5];
    bVar1 = puVar10[8];
    (&DAT_81c2b458)[uVar8 * 0x12] = (ushort)bVar1 * 0x100;
    (&DAT_81c2b458)[uVar8 * 0x12] = (ushort)bVar1 * 0x100 + (ushort)(byte)puVar10[7];
    bVar1 = puVar10[10];
    (&DAT_81c2b45a)[uVar8 * 0x12] = (ushort)bVar1 * 0x100;
    (&DAT_81c2b45a)[uVar8 * 0x12] = (ushort)bVar1 * 0x100 + (ushort)(byte)puVar10[9];
    (&DAT_81c2b45c)[iVar7] = puVar10[0xb];
    (&DAT_81c2b45d)[iVar7] = puVar10[0xc];
    bVar1 = puVar10[0x10];
    (&DAT_81c2b460)[uVar8 * 9] = (uint)bVar1 * 0x100;
    iVar3 = ((uint)bVar1 * 0x100 + (uint)(byte)puVar10[0xf]) * 0x100;
    (&DAT_81c2b460)[uVar8 * 9] = iVar3;
    iVar3 = (iVar3 + (uint)(byte)puVar10[0xe]) * 0x100;
    (&DAT_81c2b460)[uVar8 * 9] = iVar3;
    (&DAT_81c2b460)[uVar8 * 9] = iVar3 + (uint)(byte)puVar10[0xd];
    bVar1 = puVar10[0x14];
    (&DAT_81c2b464)[uVar8 * 9] = (uint)bVar1 * 0x100;
    iVar3 = ((uint)bVar1 * 0x100 + (uint)(byte)puVar10[0x13]) * 0x100;
    (&DAT_81c2b464)[uVar8 * 9] = iVar3;
    iVar3 = (iVar3 + (uint)(byte)puVar10[0x12]) * 0x100;
    (&DAT_81c2b464)[uVar8 * 9] = iVar3;
    (&DAT_81c2b464)[uVar8 * 9] = iVar3 + (uint)(byte)puVar10[0x11];
    bVar1 = puVar10[0x16];
    (&DAT_81c2b468)[uVar8 * 0x12] = (ushort)bVar1 * 0x100;
    (&DAT_81c2b468)[uVar8 * 0x12] = (ushort)bVar1 * 0x100 + (ushort)(byte)puVar10[0x15];
    bVar1 = puVar10[0x18];
    (&DAT_81c2b46a)[uVar8 * 0x12] = (ushort)bVar1 * 0x100;
    (&DAT_81c2b46a)[uVar8 * 0x12] = (ushort)bVar1 * 0x100 + (ushort)(byte)puVar10[0x17];
    bVar1 = puVar10[0x1a];
    (&DAT_81c2b46c)[uVar8 * 0x12] = (ushort)bVar1 * 0x100;
    (&DAT_81c2b46c)[uVar8 * 0x12] = (ushort)bVar1 * 0x100 + (ushort)(byte)puVar10[0x19];
    (&DAT_81c2b46e)[iVar7] = puVar10[0x1b];
    (&DAT_81c2b46f)[iVar7] = puVar10[0x1c];
    puVar9 = puVar10 + 0x1e;
    (&DAT_81c2b470)[iVar7] = puVar10[0x1d];
    puVar10 = puVar10 + 0x1f;
    (&DAT_81c2b471)[iVar7] = *puVar9;
    uVar8 = uVar6;
  } while (uVar6 < 0x26);
  DAT_81c2b140 = (ushort)(byte)puVar2[0x49b] * 0x100 + (ushort)(byte)puVar2[0x49a];
  puVar10 = (undefined1 *)FUN_81c152f0(0x3d,param_1,g_sango_package_data);
  uVar8 = 0;
  do {
    iVar7 = uVar8 * 0x10;
    *(undefined1 *)(iVar7 + DAT_81c2b164) = *puVar10;
    *(undefined1 *)(iVar7 + DAT_81c2b164 + 1) = puVar10[1];
    *(undefined1 *)(iVar7 + DAT_81c2b164 + 2) = puVar10[2];
    *(undefined1 *)(iVar7 + DAT_81c2b164 + 3) = puVar10[3];
    *(undefined1 *)(iVar7 + DAT_81c2b164 + 4) = puVar10[4];
    *(undefined1 *)(iVar7 + DAT_81c2b164 + 5) = puVar10[5];
    *(undefined1 *)(iVar7 + DAT_81c2b164 + 6) = puVar10[6];
    *(undefined1 *)(iVar7 + DAT_81c2b164 + 7) = puVar10[7];
    *(undefined1 *)(iVar7 + DAT_81c2b164 + 8) = puVar10[8];
    *(undefined1 *)(iVar7 + DAT_81c2b164 + 9) = puVar10[9];
    bVar1 = puVar10[0xb];
    iVar3 = iVar7 + DAT_81c2b164;
    *(ushort *)(iVar3 + 10) = (ushort)bVar1 * 0x100;
    uVar8 = uVar8 + 1 & 0xff;
    *(ushort *)(iVar3 + 10) = (ushort)bVar1 * 0x100 + (ushort)(byte)puVar10[10];
    *(undefined1 *)(iVar3 + 0xc) = puVar10[0xc];
    puVar2 = puVar10 + 0xe;
    *(undefined1 *)(iVar7 + DAT_81c2b164 + 0xd) = puVar10[0xd];
    puVar10 = puVar10 + 0xf;
    *(undefined1 *)(iVar7 + DAT_81c2b164 + 0xe) = *puVar2;
  } while (uVar8 < 200);
  pvVar4 = (void *)FUN_81c152f0(0x41,param_1,g_sango_package_data);
  bbk_memcpy(&DAT_81c2b310,pvVar4,200);
  pvVar4 = (void *)FUN_81c152f0(0x44,param_1,g_sango_package_data);
  bbk_memcpy(&DAT_81c2b3e0,pvVar4,0x21);
  FUN_81c0a7c8(g_state_buffer_30,0,0x1e);
  FUN_81c0a7c8(g_state_buffer_1200,0xff,0x4b0);
  uVar6 = 1;
  uVar8 = 0;
  DAT_81c2b161 = param_1;
  do {
    uVar5 = uVar6 & 0xff;
    (&DAT_81c2b450)[uVar8 * 0x24] = 0;
    uVar6 = uVar5 + 1;
    uVar8 = uVar5;
  } while (uVar5 < 0x26);
  uVar8 = 0;
  do {
    iVar3 = uVar8 * 0x10;
    *(undefined1 *)(iVar3 + DAT_81c2b164 + 8) = 100;
    uVar8 = uVar8 + 1 & 0xff;
    puVar10 = (undefined1 *)(iVar3 + DAT_81c2b164);
    *puVar10 = 0;
    *(undefined2 *)(puVar10 + 10) = 100;
  } while (uVar8 < 200);
  DAT_81c2b170 = 1;
  return;
}


#undef DAT_81c2b140
#undef DAT_81c2b164
#undef DAT_81c2b161
#undef DAT_81c2b170
#undef DAT_81c2b310
#undef DAT_81c2b3e0
#undef DAT_81c2b450
#undef DAT_81c2b451
#undef DAT_81c2b452
#undef DAT_81c2b454
#undef DAT_81c2b456
#undef DAT_81c2b458
#undef DAT_81c2b45a
#undef DAT_81c2b45c
#undef DAT_81c2b45d
#undef DAT_81c2b460
#undef DAT_81c2b464
#undef DAT_81c2b468
#undef DAT_81c2b46a
#undef DAT_81c2b46c
#undef DAT_81c2b46e
#undef DAT_81c2b46f
#undef DAT_81c2b470
#undef DAT_81c2b471
#undef g_state_buffer_1200
#undef g_state_buffer_30
#undef g_sango_package_data


/* VA 0x81c1b2b4; body bytes 176 */

undefined4 FUN_81c1b2b4(void)

{
  unsigned char sg_stack[56] __attribute__((aligned(8)));
#define local_30 (*(ushort (*)[4])(sg_stack + 0))
#define acStack_28 (*(char (*)[32])(sg_stack + 8))

  uint uVar1;
  undefined4 uVar2;

  FUN_81c154d8(0x40,0x79,acStack_28);
  local_30[0] = 0x4f;
  local_30[2] = 0x7f;
  local_30[3] = 0x2e;
  local_30[1] = 10;
  uVar1 = FUN_81c07068(local_30,0,acStack_28);
  if (uVar1 == 1) {
    FUN_81c16330('\0');
    uVar2 = 0;
  }
  else if ((int)uVar1 < 2) {
    uVar2 = 1;
  }
  else {
    uVar2 = 2;
    if (uVar1 != 2) {
      uVar2 = 0;
    }
  }
  return uVar2;
}


#undef local_30
#undef acStack_28


/* VA 0x81c1b364; body bytes 1056 */

uint FUN_81c1b364(uint param_1,uint param_2)

{
  unsigned char sg_stack[61] __attribute__((aligned(8)));
#define local_40 (*(int *)(sg_stack + 24))
#define local_3c (*(int *)(sg_stack + 28))
#define acStack_58 (*(char (*)[7])(sg_stack + 0))
#define local_30 (*(char *)(sg_stack + 40))
#define local_2f (*(char *)(sg_stack + 41))
#define local_2e (*(char *)(sg_stack + 42))
#define acStack_51 (*(char (*)[17])(sg_stack + 7))
#define local_2d (*(char *)(sg_stack + 43))
#define local_2c (*(undefined1 *)(sg_stack + 44))

  bool bVar1;
  short sVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;

  uVar8 = param_2 & 0xffff;
  if (9999 < uVar8) {
    uVar8 = 9999;
  }
  uVar6 = param_1 & 0xffff;
  FUN_81c154d8(0x40,0x2c,acStack_58);
  FUN_81c149dc(0x53,0x99,acStack_58);
  FUN_81c154d8(0x40,0x2d,acStack_58);
  FUN_81c0a7e4(uVar8,acStack_51,10);
  FUN_81c149dc(0x53,0xa5,acStack_58);
  uVar4 = bbk_strlen(acStack_51);
  uVar7 = uVar4 - 1 & 0xff;
  uVar9 = 1;
  bVar1 = true;
  uVar4 = uVar7;
LAB_81c1b42c:
  do {
    if (!bVar1) goto LAB_81c1b4bc;
LAB_81c1b434:
    while( true ) {
      cVar3 = (char)uVar6;
      if (uVar7 == 3) {
        local_2c = 0;
        local_30 = (char)(uVar6 / 1000) + '0';
        local_2d = cVar3 + (char)(uVar6 / 10) * -10 + '0';
        local_2f = (char)((uVar6 % 1000) / 100) + '0';
        local_2e = (char)((uVar6 % 100) / 10) + '0';
      }
      if (uVar7 == 2) {
        local_2d = '\0';
        local_2e = cVar3 + (char)(uVar6 / 10) * -10 + '0';
        local_30 = (char)((uVar6 % 1000) / 100) + '0';
        local_2f = (char)((uVar6 % 100) / 10) + '0';
      }
      if (uVar7 == 1) {
        local_2e = '\0';
        local_2f = cVar3 + (char)(uVar6 / 10) * -10 + '0';
        local_30 = (char)((uVar6 % 100) / 10) + '0';
      }
      if (uVar7 == 0) {
        local_2f = '\0';
        local_30 = cVar3 + (char)(uVar6 / 10) * -10 + '0';
      }
      FUN_81c149dc(0x7d,0x99,&local_30);
      sVar2 = (short)uVar4 * 6;
      bVar1 = false;
      FUN_81c0aae4(sVar2 + 0x7d,0x99,sVar2 + 0x82,0xa4,0);
LAB_81c1b4bc:
      FUN_81c1408c(&local_40);
      if (local_40 != 5) goto LAB_81c1b42c;
      if (local_3c != 0x67) break;
      if (uVar8 < uVar6 + uVar9) goto LAB_81c1b42c;
      uVar6 = uVar6 + uVar9 & 0xffff;
    }
    if (0x67 < local_3c) {
      if (local_3c == 0x6a) {
        if (uVar7 <= uVar4) goto LAB_81c1b42c;
        uVar4 = uVar4 + 1;
        uVar9 = uVar9 / 10;
      }
      else {
        if (0x6a < local_3c) {
          if (((local_3c != 0x6c) || (uVar6 < uVar9)) || ((int)(uVar6 - uVar9) < 0))
          goto LAB_81c1b42c;
          uVar6 = uVar6 - uVar9 & 0xffff;
          goto LAB_81c1b434;
        }
        if ((local_3c != 0x69) || (uVar4 == 0)) goto LAB_81c1b42c;
        uVar4 = uVar4 - 1;
        uVar9 = uVar9 * 10;
      }
      uVar4 = uVar4 & 0xff;
      uVar9 = uVar9 & 0xffff;
      goto LAB_81c1b434;
    }
    uVar5 = 0xffff;
    if ((local_3c == 1) || (uVar5 = uVar6, local_3c == 0x1c)) {
      return uVar5;
    }
  } while( true );
}


#undef local_40
#undef local_3c
#undef acStack_58
#undef local_30
#undef local_2f
#undef local_2e
#undef acStack_51
#undef local_2d
#undef local_2c

#define DAT_81c2b115 (*(byte *)(0x81c2b115u))
#define g_scratch_buffer_4096 (*(undefined4 *)(0x81c2b0f0u))
/* VA 0x81c1b784; body bytes 280 */

void FUN_81c1b784(void)

{
  byte *pbVar1;
  uint uVar2;
  byte *pbVar3;
  byte *destination;
  uint uVar4;

  FUN_81c13494();
  pbVar1 = g_scratch_buffer_4096;
  uVar4 = 0;
  uVar2 = FUN_81c12a68((uint)DAT_81c2b115,g_scratch_buffer_4096);
  destination = pbVar1 + 200;
  pbVar3 = pbVar1;
  if (uVar2 != 0) {
    do {
      sango_load_named_text(*pbVar3,destination);
      FUN_81c154d8(0x40,0xa3,pbVar1 + 0xfa);
      bbk_strcat((char *)destination,(char *)(pbVar1 + 0xfa));
      FUN_81c0ac48(0x3c,0x12f,0xb2,0x13d,0,0);
      FUN_81c08e7c(0x3c,0x12f,0xb2,0x13d,3,0,0);
      FUN_81c149dc(0x3e,0x131,(char *)destination);
      FUN_81c14164(0x14,'\0');
      uVar4 = uVar4 + 1 & 0xff;
      pbVar3 = pbVar1 + uVar4;
    } while (uVar4 < uVar2);
  }
  FUN_81c13494();
  return;
}


#undef DAT_81c2b115
#undef g_scratch_buffer_4096

#define DAT_81c2b170 (*(byte *)(0x81c2b170u))
#define DAT_81c2b140 (*(short *)(0x81c2b140u))
/* VA 0x81c1b89c; body bytes 128 */

void FUN_81c1b89c(void)

{
  DAT_81c2b170 = DAT_81c2b170 + 1;
  if (0xc < DAT_81c2b170) {
    DAT_81c2b170 = 1;
    DAT_81c2b140 = DAT_81c2b140 + 1;
    FUN_81c17e18();
    FUN_81c17734();
  }
  FUN_81c16e00();
  FUN_81c1740c();
  FUN_81c171cc();
  return;
}


#undef DAT_81c2b170
#undef DAT_81c2b140


/* VA 0x81c1b91c; body bytes 48 */

uint FUN_81c1b91c(char scenario,uchar *state)

{
  uint uVar1;

  FUN_81c1add4(scenario);
  uVar1 = FUN_81c1ad30(state);
  return uVar1;
}





/* VA 0x81c1b950; body bytes 48 */

char * FUN_81c1b950(char *param_1,int param_2,int param_3)

{
  char *pcVar1;
  int iVar2;

  iVar2 = param_3 + -1;
  do {
    pcVar1 = param_1;
    if (iVar2 < 0) {
      return (char *)0x0;
    }
    iVar2 = iVar2 + -1;
    param_1 = pcVar1 + 1;
  } while (*pcVar1 != param_2);
  return pcVar1;
}





/* VA 0x81c1b980; body bytes 84 */

void FUN_81c1b980(undefined1 *param_1,byte *param_2,uint param_3,undefined4 param_4)

{
  unsigned char sg_stack[32] __attribute__((aligned(8)));
#define local_res4 (*(byte * *)(sg_stack + 4))
#define local_res8 (*(uint *)(sg_stack + 8))
#define local_resc (*(undefined4 *)(sg_stack + 12))
#define local_res0 (*(undefined1 * *)(sg_stack + 0))


  local_res0 = param_1;
  local_res4 = param_2;
  local_res8 = param_3;
  local_resc = param_4;
  FUN_81c1bd50(param_2,&local_res8,FUN_81c1c48c,&local_res0);
  *local_res0 = 0;
  return;
}


#undef local_res4
#undef local_res8
#undef local_resc
#undef local_res0


/* VA 0x81c1b9d4; body bytes 48 */

int FUN_81c1b9d4(char *param_1)

{
  char cVar1;
  char *pcVar2;
  int iVar3;

  iVar3 = 0;
  cVar1 = *param_1;
  pcVar2 = param_1 + 1;
  while (cVar1 != '\0') {
    iVar3 = iVar3 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  }
  return iVar3;
}




#define DAT_81c2b198 (*(undefined4 *)(0x81c2b198u))
/* VA 0x81c1ba04; body bytes 596 */

int FUN_81c1ba04(char *param_1,undefined4 *param_2,int param_3)

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
  while (iVar2 = FUN_81c1c620(*param_1), iVar2 != 0) {
    param_1 = param_1 + 1;
  }
  cVar3 = *param_1;
  if (*param_1 == '+') {
    param_1 = param_1 + 1;
    cVar3 = *param_1;
  }
  else if (*param_1 == '-') {
    param_1 = param_1 + 1;
    cVar3 = *param_1;
    iVar7 = -1;
  }
  pcVar4 = param_1;
  if (cVar3 == '0') {
    pcVar4 = param_1 + 1;
    iVar2 = FUN_81c1c650(*pcVar4);
    if (iVar2 != 0x58) {
      if (param_3 == 0) {
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
    while (cVar3 != 0) {
      iVar2 = FUN_81c1c600(cVar3);
      iVar5 = cVar3 + -0x30;
      if (iVar2 == 0) {
        iVar2 = FUN_81c1c650(cVar3);
        if ((iVar2 < 0x41) || (iVar5 = iVar2 + -0x37, param_3 + 0x37 <= iVar2)) break;
      }
      pcVar4 = pcVar4 + 1;
      if (param_3 == 0) {
        trap(7);
      }
      bVar1 = 0x7fffffff / param_3 + -1 <= iVar6;
      iVar6 = iVar6 * param_3 + iVar5;
      if (bVar1) {
        iVar6 = 0x7fffffff;
        DAT_81c2b198 = 0x22;
      }
      cVar3 = *pcVar4;
    }
  }
  else {
LAB_81c1ba80:
    bVar1 = param_3 < 0xb;
    if (param_3 == 0) {
      param_3 = 10;
    }
    else {
LAB_81c1bb3c:
      if (!bVar1) goto joined_r0x81c1bb4c;
    }
    while (iVar2 = FUN_81c1c600(cVar3), iVar2 != 0) {
      if (param_3 == 0) {
        trap(7);
      }
      if (iVar6 < 0x7fffffff / param_3 + -1) {
        iVar6 = iVar6 * param_3 + (int)*pcVar4 + -0x30;
      }
      else {
        DAT_81c2b198 = 0x22;
        iVar6 = 0x7fffffff;
      }
      pcVar4 = pcVar4 + 1;
      cVar3 = *pcVar4;
    }
  }
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = pcVar4;
  }
  if (iVar7 == -1) {
    iVar6 = -iVar6;
  }
  return iVar6;
}


#undef DAT_81c2b198


/* VA 0x81c1bc58; body bytes 32 */

void FUN_81c1bc58(char *param_1)

{
  FUN_81c1ba04(param_1,(undefined4 *)0x0,10);
  return;
}





/* VA 0x81c1bcbc; body bytes 36 */

char * FUN_81c1bcbc(char *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;

  pcVar2 = param_1;
  do {
    cVar1 = *param_2;
    param_2 = param_2 + 1;
    *pcVar2 = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  return param_1;
}





/* VA 0x81c1bce0; body bytes 40 */

void * crt_memset(void *dst,int value,uint size)

{
  undefined1 *puVar1;
  int iVar2;

  puVar1 = (undefined1 *)dst;
  for (iVar2 = size - 1; iVar2 != -1; iVar2 = iVar2 + -1) {
    *puVar1 = (char)value;
    puVar1 = puVar1 + 1;
  }
  return dst;
}





/* VA 0x81c1bd08; body bytes 52 */

void * crt_memcpy(void *dst,void *src,uint size)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  int iVar3;

  puVar2 = (undefined1 *)dst;
  for (iVar3 = size - 1; iVar3 != -1; iVar3 = iVar3 + -1) {
                    /* WARNING: Load size is inaccurate */
    uVar1 = *(byte *)src;
    src = (void *)((int)src + 1);
    *puVar2 = uVar1;
    puVar2 = puVar2 + 1;
  }
  return dst;
}




#define DAT_81c2b1e0 (*(undefined *)(0x81c2b1e0u))
/* VA 0x81c1bd3c; body bytes 12 */

undefined * FUN_81c1bd3c(void)

{
  return &DAT_81c2b1e0;
}


#undef DAT_81c2b1e0


/* VA 0x81c1bd48; body bytes 8 */

void FUN_81c1bd48(void)

{
  return;
}




#define s_0123456789abcdef_81c20770 (*(char (*)[1])(0x81c20770u))
#define s_0123456789ABCDEF_81c20784 (*(char (*)[1])(0x81c20784u))
#define s__null__81c20798 (*(char (*)[1])(0x81c20798u))
/* VA 0x81c1bd50; body bytes 1852 */

/* WARNING: Type propagation algorithm not settling */

int FUN_81c1bd50(byte *param_1,uint *param_2,undefined *param_3,undefined4 param_4)

{
  unsigned char sg_stack[104] __attribute__((aligned(8)));
#define local_38 (*(uint *)(sg_stack + 72))
#define local_34 (*(uint *)(sg_stack + 76))
#define local_30 (*(uint *)(sg_stack + 80))
#define local_2c (*(uint *)(sg_stack + 84))
#define auStack_80 (*(undefined1 (*)[16])(sg_stack + 0))
#define local_70 (*(undefined1 (*)[30])(sg_stack + 16))
#define local_52 (*(undefined1 (*)[2])(sg_stack + 46))
#define local_50 (*(char * *)(sg_stack + 48))
#define local_4c (*(uint *)(sg_stack + 52))
#define local_48 (*(char * *)(sg_stack + 56))
#define local_44 (*(char * *)(sg_stack + 60))
#define local_40 (*(int *)(sg_stack + 64))
#define local_3c (*(char * *)(sg_stack + 68))

  byte bVar1;
  char cVar2;
  undefined1 *puVar3;
  char *pcVar4;
  uint uVar5;
  byte bVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  char **ppcVar10;
  char **ppcVar11;
  byte *pbVar12;
  char *pcVar13;
  undefined4 *puVar14;
  uint *puVar15;
  int *piVar16;
  int iVar17;
  uint uVar18;

  bVar6 = *param_1;
  local_3c = s_0123456789abcdef_81c20770;
  iVar17 = 0;
LAB_81c1bda0:
  uVar5 = (uint)bVar6;
  if (uVar5 == 0) {
LAB_81c1be54:
    return iVar17;
  }
  if (uVar5 == 0x25) {
    local_4c = 0;
    local_50 = (char *)0x0;
    local_44 = (char *)0x0;
    pcVar13 = (char *)0xffffffff;
    local_40 = 0;
    pbVar12 = param_1;
LAB_81c1be0c:
    param_1 = pbVar12 + 1;
    uVar5 = (uint)*param_1;
    switch(uVar5) {
    case 0:
      goto LAB_81c1be54;
    default:
      goto switchD_81c1be34_caseD_1;
    case 0x20:
      iVar8 = 0x20;
      pbVar12 = param_1;
      if (local_40 == 0) goto LAB_81c1be48;
      goto LAB_81c1be0c;
    case 0x23:
      local_4c = local_4c | 8;
      break;
    case 0x2a:
      puVar14 = (undefined4 *)((uint)((int)param_2 + 3) & 0xfffffffc);
      local_44 = (char *)*puVar14;
      param_2 = puVar14 + 1;
      pbVar12 = param_1;
      if ((int)local_44 < 0) {
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
      if (bVar6 == 0x2a) {
        puVar14 = (undefined4 *)((uint)((int)param_2 + 3) & 0xfffffffc);
        pcVar13 = (char *)*puVar14;
        param_2 = puVar14 + 1;
      }
      else {
        while ((-1 < (char)bVar6 && (iVar8 = FUN_81c1c600(bVar6), iVar8 != 0))) {
          bVar1 = *pbVar12;
          pbVar12 = pbVar12 + 1;
          bVar6 = *pbVar12;
          pcVar13 = (char *)((int)pcVar13 * 10 + (uint)bVar1 + -0x30);
        }
        pbVar12 = pbVar12 + -1;
      }
      if ((int)pcVar13 < -1) {
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
      while( true ) {
        pbVar12 = param_1 + 1;
        pcVar4 = (char *)((int)pcVar4 * 10 + uVar5 + -0x30);
        if (((char)*pbVar12 < '\0') || (iVar8 = FUN_81c1c600(*pbVar12), iVar8 == 0)) break;
        uVar5 = (uint)*pbVar12;
        param_1 = pbVar12;
      }
      local_44 = pcVar4;
      pbVar12 = param_1;
      goto LAB_81c1be0c;
    case 0x44:
      local_4c = local_4c | 1;
    case 100:
    case 0x69:
      puVar3 = (undefined1 *)((int)param_2 + 3);
      if ((local_4c & 4) == 0) {
        uVar5 = *(uint *)((uint)puVar3 & 0xfffffffc);
      }
      else {
        uVar5 = (uint)*(short *)((uint)puVar3 & 0xfffffffc);
      }
      param_2 = (uint *)(((uint)puVar3 & 0xfffffffc) + 4);
      if ((int)uVar5 < 0) {
        uVar5 = -uVar5;
        local_40 = 0x2d;
      }
      uVar7 = 10;
LAB_81c1bfe4:
      local_50 = pcVar13;
      if (-1 < (int)pcVar13) {
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
      puVar3 = (undefined1 *)((int)param_2 + 3);
      if ((local_4c & 4) == 0) {
        uVar5 = *(uint *)((uint)puVar3 & 0xfffffffc);
      }
      else {
        uVar5 = (uint)*(short *)((uint)puVar3 & 0xfffffffc);
      }
      param_2 = (uint *)(((uint)puVar3 & 0xfffffffc) + 4);
      uVar7 = 8;
LAB_81c1c2a8:
      local_40 = 0;
      goto LAB_81c1bfe4;
    case 0x55:
      local_4c = local_4c | 1;
    case 0x75:
      puVar3 = (undefined1 *)((int)param_2 + 3);
      if ((local_4c & 4) == 0) {
        uVar5 = *(uint *)((uint)puVar3 & 0xfffffffc);
      }
      else {
        uVar5 = (uint)*(short *)((uint)puVar3 & 0xfffffffc);
      }
      param_2 = (uint *)(((uint)puVar3 & 0xfffffffc) + 4);
      uVar7 = 10;
      goto LAB_81c1c2a8;
    case 0x58:
      local_3c = s_0123456789ABCDEF_81c20784;
    case 0x78:
      puVar3 = (undefined1 *)((int)param_2 + 3);
      if ((local_4c & 4) == 0) {
        uVar5 = *(uint *)((uint)puVar3 & 0xfffffffc);
      }
      else {
        uVar5 = (uint)*(short *)((uint)puVar3 & 0xfffffffc);
      }
      param_2 = (uint *)(((uint)puVar3 & 0xfffffffc) + 4);
      uVar7 = 0x10;
      if ((local_4c & 8) != 0) {
        if (uVar5 != 0) {
          local_4c = local_4c | 0x40;
        }
      }
      goto LAB_81c1c2a8;
    case 99:
      puVar3 = (undefined1 *)((uint)((int)param_2 + 3) & 0xfffffffc);
      local_70[0] = *puVar3;
      ppcVar11 = (char **)local_70;
      param_2 = (uint *)(puVar3 + 4);
      local_48 = (char *)0x1;
      local_40 = 0;
      goto LAB_81c1c074;
    case 0x68:
      goto switchD_81c1be34_caseD_68;
    case 0x6c:
      local_4c = local_4c | 1;
      break;
    case 0x6e:
      if (((local_4c & 1) == 0) && ((local_4c & 4) != 0)) {
        puVar14 = (undefined4 *)((uint)((int)param_2 + 3) & 0xfffffffc);
        param_2 = puVar14 + 1;
        *(short *)*puVar14 = (short)iVar17;
      }
      else {
        puVar14 = (undefined4 *)((uint)((int)param_2 + 3) & 0xfffffffc);
        param_2 = puVar14 + 1;
        *(int *)*puVar14 = iVar17;
      }
      goto LAB_81c1bdc4;
    case 0x70:
      puVar15 = (uint *)((uint)((int)param_2 + 3) & 0xfffffffc);
      uVar5 = *puVar15;
      uVar7 = 0x10;
      param_2 = puVar15 + 1;
      goto LAB_81c1c2a8;
    case 0x73:
      piVar16 = (int *)((uint)((int)param_2 + 3) & 0xfffffffc);
      ppcVar11 = (char **)*piVar16;
      param_2 = (uint *)(piVar16 + 1);
      if (ppcVar11 == (char **)0x0) {
        ppcVar11 = (char **)s__null__81c20798;
      }
      if ((int)pcVar13 < 0) {
        local_48 = (char *)FUN_81c1b9d4((char *)ppcVar11);
      }
      else {
        pcVar4 = FUN_81c1b950((char *)ppcVar11,0,(int)pcVar13);
        local_48 = pcVar13;
        if ((pcVar4 != (char *)0x0) &&
           (local_48 = pcVar4 + -(int)ppcVar11, (int)pcVar13 < (int)(pcVar4 + -(int)ppcVar11))) {
          local_48 = pcVar13;
        }
      }
      local_40 = 0;
      goto LAB_81c1c074;
    }
    pbVar12 = param_1;
    goto LAB_81c1be0c;
  }
  if (uVar5 != 10) goto LAB_81c1bdb8;
  (*(code *)param_3)(0xd,param_4);
  (*(code *)param_3)(10,param_4);
  iVar17 = iVar17 + 1;
  goto LAB_81c1bdc0;
switchD_81c1be34_caseD_68:
  local_4c = local_4c | 4;
  pbVar12 = param_1;
  goto LAB_81c1be0c;
LAB_81c1c010:
  do {
    ppcVar10 = ppcVar11;
    uVar18 = uVar5 / uVar7;
    if (uVar7 == 0) {
      trap(7);
    }
    ppcVar11 = (char **)((int)ppcVar10 + -1);
    cVar2 = local_3c[uVar5 % uVar7];
    *(char *)ppcVar11 = cVar2;
    uVar5 = uVar18;
  } while (uVar18 != 0);
  local_3c = s_0123456789abcdef_81c20770;
  if (((local_4c & 8) == 0) || (uVar7 != 8)) {
LAB_81c1c068:
    puVar3 = auStack_80 + -(int)ppcVar11;
  }
  else {
    puVar3 = auStack_80 + -(int)ppcVar11;
    if (cVar2 != '0') {
      ppcVar11 = (char **)((int)ppcVar10 + -2);
      *(char *)ppcVar11 = '0';
      goto LAB_81c1c068;
    }
  }
LAB_81c1c06c:
  local_48 = puVar3 + 0x30;
LAB_81c1c074:
  pcVar13 = local_48;
  if (local_40 != 0) {
    pcVar13 = local_48 + 1;
  }
  if ((local_4c & 0x40) != 0) {
    pcVar13 = pcVar13 + 2;
  }
  local_38 = local_4c & 0x40;
  local_34 = (uint)((int)pcVar13 < (int)local_50);
  pcVar4 = pcVar13;
  if ((int)pcVar13 < (int)local_50 != 0) {
    pcVar4 = local_50;
  }
  local_30 = local_4c & 0x30;
  uVar5 = (uint)((int)pcVar4 < (int)local_44);
  local_2c = uVar5;
  if ((((local_4c & 0x30) == 0) && (local_2c = (uint)((int)pcVar4 < 0), local_44 != (char *)0x0)) &&
     (local_2c = uVar5, pcVar9 = pcVar4, uVar5 != 0)) {
    do {
      (*(code *)param_3)(0x20,param_4);
      pcVar9 = pcVar9 + 1;
    } while ((int)pcVar9 < (int)local_44);
  }
  if (local_40 != 0) {
    (*(code *)param_3)(local_40,param_4);
  }
  if (local_38 != 0) {
    (*(code *)param_3)(0x30,param_4);
    (*(code *)param_3)((int)(char)*param_1,param_4);
  }
  if ((local_30 == 0x20) && (local_2c != 0)) {
    iVar8 = (int)local_44 - (int)pcVar4;
    do {
      iVar8 = iVar8 + -1;
      (*(code *)param_3)(0x30,param_4);
    } while (iVar8 != 0);
  }
  pcVar9 = local_48;
  if (local_34 != 0) {
    iVar8 = (int)local_50 - (int)pcVar13;
    do {
      iVar8 = iVar8 + -1;
      (*(code *)param_3)(0x30,param_4);
      pcVar9 = local_48;
    } while (iVar8 != 0);
  }
  while (-1 < (int)(pcVar9 + -1)) {
    (*(code *)param_3)((int)*(char *)ppcVar11,param_4);
    ppcVar11 = (char **)((int)ppcVar11 + 1);
    pcVar9 = pcVar9 + -1;
  }
  if (((local_4c & 0x10) != 0) && (local_2c != 0)) {
    iVar8 = (int)local_44 - (int)pcVar4;
    do {
      iVar8 = iVar8 + -1;
      (*(code *)param_3)(0x20,param_4);
    } while (iVar8 != 0);
  }
  pcVar13 = local_44;
  if (local_2c == 0) {
    pcVar13 = pcVar4;
  }
  iVar17 = iVar17 + (int)pcVar13;
LAB_81c1bdc4:
  param_1 = param_1 + 1;
  bVar6 = *param_1;
  goto LAB_81c1bda0;
switchD_81c1be34_caseD_1:
  uVar5 = (uint)(char)*param_1;
LAB_81c1bdb8:
  (*(code *)param_3)(uVar5,param_4);
LAB_81c1bdc0:
  iVar17 = iVar17 + 1;
  goto LAB_81c1bdc4;
}


#undef s_0123456789abcdef_81c20770
#undef s_0123456789ABCDEF_81c20784
#undef s__null__81c20798
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


/* VA 0x81c1c48c; body bytes 20 */

void FUN_81c1c48c(undefined1 param_1,int *param_2)

{
  undefined1 *puVar1;

  puVar1 = (undefined1 *)*param_2;
  *puVar1 = param_1;
  *param_2 = (int)(puVar1 + 1);
  return;
}




#define DAT_81c2b9cc (*(undefined4 *)(0x81c2b9ccu))
#define DAT_81c2b9d0 (*(undefined2 *)(0x81c2b9d0u))
#define DAT_81c2b9d4 (*(undefined4 *)(0x81c2b9d4u))
#define DAT_81c2b1a0 (*(undefined2 * *)(0x81c2b1a0u))
#define DAT_81c2b19c (*(undefined2 * *)(0x81c2b19cu))
#define DAT_81c2b1ac (*(undefined2 * *)(0x81c2b1acu))
#define DAT_81c2b9c0 (*(undefined2 *)(0x81c2b9c0u))
#define DAT_81c2b9c2 (*(undefined1 *)(0x81c2b9c2u))
#define DAT_81c2b9c4 (*(undefined4 *)(0x81c2b9c4u))
#define DAT_81c2b9c8 (*(undefined2 *)(0x81c2b9c8u))
#define DAT_81c2b9ca (*(undefined1 *)(0x81c2b9cau))
#define DAT_81c2b9d2 (*(undefined1 *)(0x81c2b9d2u))
#define DAT_81c2b198 (*(undefined4 *)(0x81c2b198u))
#define DAT_81c2b1a4 (*(undefined4 *)(0x81c2b1a4u))
#define g_rand_state (*(undefined4 *)(0x81c2b1a8u))
/* VA 0x81c1c4a0; body bytes 160 */

void FUN_81c1c4a0(void)

{
  DAT_81c2b9cc = 1;
  DAT_81c2b9d0 = 0x45;
  DAT_81c2b9d4 = 2;
  DAT_81c2b1a0 = &DAT_81c2b9c0;
  DAT_81c2b19c = &DAT_81c2b9c8;
  DAT_81c2b1ac = &DAT_81c2b9d0;
  DAT_81c2b9c0 = 0x45;
  DAT_81c2b9c2 = 0;
  DAT_81c2b9c4 = 0;
  DAT_81c2b9c8 = 0x45;
  DAT_81c2b9ca = 0;
  DAT_81c2b9d2 = 0;
  DAT_81c2b198 = 0;
  FUN_81c1dd88(-0x7f5ce000,-0x7e400000);
  g_rand_state = 1;
  DAT_81c2b1a4 = 0xffffffff;
  return;
}


#undef DAT_81c2b9cc
#undef DAT_81c2b9d0
#undef DAT_81c2b9d4
#undef DAT_81c2b1a0
#undef DAT_81c2b19c
#undef DAT_81c2b1ac
#undef DAT_81c2b9c0
#undef DAT_81c2b9c2
#undef DAT_81c2b9c4
#undef DAT_81c2b9c8
#undef DAT_81c2b9ca
#undef DAT_81c2b9d2
#undef DAT_81c2b198
#undef DAT_81c2b1a4
#undef g_rand_state

#define DAT_81c2b1f4 (*(char *)(0x81c2b1f4u))
#define DAT_81c2b9e0 (*(undefined1 *)(0x81c2b9e0u))
#define DAT_81c2b1f0 (*(int *)(0x81c2b1f0u))
/* VA 0x81c1c540; body bytes 152 */

int FUN_81c1c540(undefined4 param_1,undefined1 *param_2,int param_3)

{
  int iVar1;

  iVar1 = 0;
  while ((param_3 != 0 && (DAT_81c2b1f4 != '\x01'))) {
    if (DAT_81c2b9e0 == '\0') {
      DAT_81c2b1f4 = '\x01';
      DAT_81c2b1f0 = 1;
    }
    else {
      DAT_81c2b9e0 = DAT_81c2b9e0 + -1;
      param_3 = param_3 + -1;
      iVar1 = iVar1 + 1;
      *param_2 = (&DAT_81c2b9e0)[DAT_81c2b1f0];
      DAT_81c2b1f0 = DAT_81c2b1f0 + 1;
      param_2 = param_2 + 1;
    }
  }
  return iVar1;
}


#undef DAT_81c2b1f4
#undef DAT_81c2b9e0
#undef DAT_81c2b1f0


/* VA 0x81c1c5d8; body bytes 8 */

void FUN_81c1c5d8(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}




#define DAT_81c2b1f4 (*(undefined1 *)(0x81c2b1f4u))
#define DAT_81c2b9e0 (*(undefined1 *)(0x81c2b9e0u))
/* VA 0x81c1c5e0; body bytes 20 */

void FUN_81c1c5e0(void)

{
  DAT_81c2b1f4 = 0;
  DAT_81c2b9e0 = 0;
  return;
}


#undef DAT_81c2b1f4
#undef DAT_81c2b9e0


/* VA 0x81c1c5f4; body bytes 8 */

void crt_diagnostic_noop(uint ignored,...)

{
  return;
}





/* VA 0x81c1c600; body bytes 24 */

int FUN_81c1c600(char param_1)

{
  int iVar1;

  iVar1 = (int)param_1;
  if (9 < iVar1 - 0x30U) {
    iVar1 = 0;
  }
  return iVar1;
}





/* VA 0x81c1c620; body bytes 48 */

int FUN_81c1c620(char param_1)

{
  int iVar1;
  int iVar2;

  iVar2 = (int)param_1;
  iVar1 = iVar2;
  if ((4 < iVar2 - 9U) && (iVar1 = 0, iVar2 == 0x20)) {
    iVar1 = iVar2;
  }
  return iVar1;
}





/* VA 0x81c1c650; body bytes 28 */

int FUN_81c1c650(char param_1)

{
  int iVar1;
  int iVar2;

  iVar2 = (int)param_1;
  iVar1 = iVar2 + -0x20;
  if (0x19 < iVar2 - 0x61U) {
    iVar1 = iVar2;
  }
  return iVar1;
}





/* VA 0x81c1c670; body bytes 88 */

int FUN_81c1c670(undefined1 *param_1,byte *param_2,int param_3,undefined4 param_4)

{
  unsigned char sg_stack[24] __attribute__((aligned(8)));
#define local_resc (*(undefined4 *)(sg_stack + 4))
#define local_res8 (*(int *)(sg_stack + 0))

  int iVar1;

  local_res8 = param_3;
  local_resc = param_4;
  iVar1 = FUN_81c1c6d0(0x4d,param_1,param_2,&local_res8);
  if (iVar1 < 0) {
    *param_1 = 0;
  }
  else {
    param_1[iVar1] = 0;
  }
  return iVar1;
}


#undef local_resc
#undef local_res8

#define s__81c20990 (*(char (*)[1])(0x81c20990u))
#define s_00000000000000000000_81c209a8 (*(char (*)[1])(0x81c209a8u))
/* VA 0x81c1c6d0; body bytes 1892 */

int FUN_81c1c6d0(int param_1,void *param_2,byte *param_3,int *param_4)

{
  unsigned char sg_stack[120] __attribute__((aligned(8)));
#define local_90 (*(int * *)(sg_stack + 0))
#define local_8c (*(undefined4 *)(sg_stack + 4))
#define local_88 (*(int *)(sg_stack + 8))
#define local_84 (*(undefined4 *)(sg_stack + 12))
#define local_80 (*(undefined4 *)(sg_stack + 16))
#define local_7c (*(uint *)(sg_stack + 20))
#define local_78 (*(int *)(sg_stack + 24))
#define local_74 (*(int *)(sg_stack + 28))
#define local_70 (*(void * *)(sg_stack + 32))
#define local_6c (*(uint *)(sg_stack + 36))
#define local_68 (*(uint *)(sg_stack + 40))
#define local_64 (*(uint *)(sg_stack + 44))
#define local_60 (*(uint *)(sg_stack + 48))
#define local_5c (*(uint *)(sg_stack + 52))
#define local_58 (*(uint *)(sg_stack + 56))
#define local_54 (*(uint *)(sg_stack + 60))
#define local_50 (*(uint *)(sg_stack + 64))
#define acStack_48 (*(char (*)[32])(sg_stack + 72))

  byte bVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  void *dst;
  uint uVar7;
  int iVar8;

  iVar8 = 0;
  dst = param_2;
  local_90 = param_4;
  if (param_3 != (byte *)0x0) {
    do {
      uVar7 = 0;
      bVar1 = *param_3;
      pbVar5 = param_3;
      while ((bVar1 != 0x25 && (bVar1 != 0))) {
        pbVar5 = pbVar5 + 1;
        uVar7 = uVar7 + 1;
        bVar1 = *pbVar5;
      }
      uVar2 = 0x53;
      if (param_1 == 0x53) {
        crt_diagnostic_noop(*(uint *)((int)param_2 + 4),param_3,uVar7);
        if (uVar2 != uVar7) {
          return -1;
        }
      }
      else {
        crt_memcpy(dst,param_3,uVar7);
        dst = (void *)((int)dst + uVar7);
      }
      iVar8 = iVar8 + uVar7;
      if (*pbVar5 != 0x25) {
        return iVar8;
      }
      local_8c = 0x4c;
      local_88 = 0x4c;
      local_84 = 0x4c;
      local_80 = 0x4c;
      iVar4 = 0x4c;
      do {
        pbVar6 = pbVar5;
        pbVar5 = pbVar6 + 1;
        switch(*pbVar5) {
        case 0x20:
          if (local_88 == 0x4c) {
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
      if (*pbVar5 == 0x2a) {
        piVar3 = (int *)((int)local_90 + 3U & 0xfffffffc);
        local_90 = piVar3 + 1;
        local_78 = *piVar3;
        if (local_78 < 0) {
          local_8c = 0x48;
          local_78 = -local_78;
        }
        pbVar5 = pbVar6 + 2;
        bVar1 = *pbVar5;
      }
      else {
        local_78 = 0;
        while (iVar4 = FUN_81c1c600(*pbVar5), iVar4 != 0) {
          local_78 = local_78 * 10 + (uint)*pbVar5 + -0x30;
          pbVar5 = pbVar5 + 1;
        }
        bVar1 = *pbVar5;
      }
      if (bVar1 == 0x2e) {
        pbVar6 = pbVar5 + 1;
        if (*pbVar6 == 0x2a) {
          piVar3 = (int *)((int)local_90 + 3U & 0xfffffffc);
          local_90 = piVar3 + 1;
          local_74 = *piVar3;
          pbVar6 = pbVar5 + 2;
          goto LAB_81c1c938;
        }
        local_74 = 0;
        while (iVar4 = FUN_81c1c600(*pbVar6), iVar4 != 0) {
          local_74 = local_74 * 10 + (uint)*pbVar6 + -0x30;
          pbVar6 = pbVar6 + 1;
        }
        bVar1 = *pbVar6;
      }
      else {
        local_74 = -1;
        pbVar6 = pbVar5;
LAB_81c1c938:
        bVar1 = *pbVar6;
      }
      local_7c = (uint)bVar1;
      if ((local_7c == 0x68) || (local_7c = (uint)*pbVar6, local_7c == 0x6c)) {
        pbVar6 = pbVar6 + 1;
      }
      else {
        local_7c = 0x4c;
      }
      param_3 = (byte *)FUN_81c1ce34((int *)&local_90,(char *)pbVar6,acStack_48);
      for (uVar7 = local_6c; 0x14 < (int)uVar7; uVar7 = uVar7 - 0x14) {
        iVar4 = 0x53;
        if (param_1 == 0x53) {
          crt_diagnostic_noop(*(uint *)((int)param_2 + 4),s__81c20990,0x14);
          if (iVar4 != 0x14) {
            return -1;
          }
        }
        else {
          crt_memcpy(dst,s__81c20990,0x14);
          dst = (void *)((int)dst + 0x14);
        }
        iVar8 = iVar8 + 0x14;
      }
      uVar2 = 0x53;
      if (param_1 == 0x53) {
        crt_diagnostic_noop(*(uint *)((int)param_2 + 4),s__81c20990,uVar7);
        if (uVar2 != uVar7) {
          return -1;
        }
      }
      else {
        crt_memcpy(dst,s__81c20990,uVar7);
        dst = (void *)((int)dst + uVar7);
      }
      uVar2 = 0x53;
      if (param_1 == 0x53) {
        crt_diagnostic_noop(*(uint *)((int)param_2 + 4),acStack_48,local_58);
        if (uVar2 != local_58) {
          return -1;
        }
      }
      else {
        crt_memcpy(dst,acStack_48,local_58);
        dst = (void *)((int)dst + local_58);
      }
      iVar8 = iVar8 + uVar7 + local_58;
      for (uVar7 = local_68; 0x14 < (int)uVar7; uVar7 = uVar7 - 0x14) {
        iVar4 = 0x53;
        if (param_1 == 0x53) {
          crt_diagnostic_noop(*(uint *)((int)param_2 + 4),s_00000000000000000000_81c209a8,0x14);
          if (iVar4 != 0x14) {
            return -1;
          }
        }
        else {
          crt_memcpy(dst,s_00000000000000000000_81c209a8,0x14);
          dst = (void *)((int)dst + 0x14);
        }
        iVar8 = iVar8 + 0x14;
      }
      uVar2 = 0x53;
      if (param_1 == 0x53) {
        crt_diagnostic_noop(*(uint *)((int)param_2 + 4),s_00000000000000000000_81c209a8,uVar7);
        if (uVar2 != uVar7) {
          return -1;
        }
      }
      else {
        crt_memcpy(dst,s_00000000000000000000_81c209a8,uVar7);
        dst = (void *)((int)dst + uVar7);
      }
      uVar2 = 0x53;
      if (param_1 == 0x53) {
        crt_diagnostic_noop(*(uint *)((int)param_2 + 4),local_70,local_54);
        if (uVar2 != local_54) {
          return -1;
        }
      }
      else {
        crt_memcpy(dst,local_70,local_54);
        dst = (void *)((int)dst + local_54);
      }
      iVar8 = iVar8 + uVar7 + local_54;
      for (uVar7 = local_64; 0x14 < (int)uVar7; uVar7 = uVar7 - 0x14) {
        iVar4 = 0x53;
        if (param_1 == 0x53) {
          crt_diagnostic_noop(*(uint *)((int)param_2 + 4),s_00000000000000000000_81c209a8,0x14);
          if (iVar4 != 0x14) {
            return -1;
          }
        }
        else {
          crt_memcpy(dst,s_00000000000000000000_81c209a8,0x14);
          dst = (void *)((int)dst + 0x14);
        }
        iVar8 = iVar8 + 0x14;
      }
      uVar2 = 0x53;
      if (param_1 == 0x53) {
        crt_diagnostic_noop(*(uint *)((int)param_2 + 4),s_00000000000000000000_81c209a8,uVar7);
        if (uVar2 != uVar7) {
          return -1;
        }
      }
      else {
        crt_memcpy(dst,s_00000000000000000000_81c209a8,uVar7);
        dst = (void *)((int)dst + uVar7);
      }
      if (param_1 == 0x53) {
        uVar2 = local_54;
        crt_diagnostic_noop(*(uint *)((int)param_2 + 4),(int)local_70 + local_54,local_50);
        if (uVar2 != local_50) {
          return -1;
        }
      }
      else {
        crt_memcpy(dst,(void *)((int)local_70 + local_54),local_50);
        dst = (void *)((int)dst + local_50);
      }
      iVar8 = iVar8 + uVar7 + local_50;
      for (uVar7 = local_60; 0x14 < (int)uVar7; uVar7 = uVar7 - 0x14) {
        iVar4 = 0x53;
        if (param_1 == 0x53) {
          crt_diagnostic_noop(*(uint *)((int)param_2 + 4),s_00000000000000000000_81c209a8,0x14);
          if (iVar4 != 0x14) {
            return -1;
          }
        }
        else {
          crt_memcpy(dst,s_00000000000000000000_81c209a8,0x14);
          dst = (void *)((int)dst + 0x14);
        }
        iVar8 = iVar8 + 0x14;
      }
      uVar2 = 0x53;
      if (param_1 == 0x53) {
        crt_diagnostic_noop(*(uint *)((int)param_2 + 4),s_00000000000000000000_81c209a8,uVar7);
        if (uVar2 != uVar7) {
          return -1;
        }
      }
      else {
        crt_memcpy(dst,s_00000000000000000000_81c209a8,uVar7);
        dst = (void *)((int)dst + uVar7);
      }
      iVar8 = iVar8 + uVar7;
      for (uVar7 = local_5c; 0x14 < (int)uVar7; uVar7 = uVar7 - 0x14) {
        iVar4 = 0x53;
        if (param_1 == 0x53) {
          crt_diagnostic_noop(*(uint *)((int)param_2 + 4),s__81c20990,0x14);
          if (iVar4 != 0x14) {
            return -1;
          }
        }
        else {
          crt_memcpy(dst,s__81c20990,0x14);
          dst = (void *)((int)dst + 0x14);
        }
        iVar8 = iVar8 + 0x14;
      }
      uVar2 = 0x53;
      if (param_1 == 0x53) {
        crt_diagnostic_noop(*(uint *)((int)param_2 + 4),s__81c20990,uVar7);
        if (uVar2 != uVar7) {
          return -1;
        }
      }
      else {
        crt_memcpy(dst,s__81c20990,uVar7);
        dst = (void *)((int)dst + uVar7);
      }
      iVar8 = iVar8 + uVar7;
    } while (param_3 != (byte *)0x0);
  }
  return iVar8;
}


#undef s__81c20990
#undef s_00000000000000000000_81c209a8
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


/* VA 0x81c1ce34; body bytes 868 */

char * FUN_81c1ce34(int *param_1,char *param_2,char *param_3)

{
  code *pcVar1;
  undefined4 *puVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  uint uVar7;
  uint uVar8;

  param_1[9] = 0;
  param_1[0xe] = 0;
  param_1[10] = 0;
  param_1[0xf] = 0;
  param_1[0xb] = 0;
  param_1[0x10] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  switch(*param_2) {
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
    puVar3 = (uint *)(*param_1 + 7U & 0xfffffff8);
    *param_1 = (int)(puVar3 + 2);
    uVar7 = *puVar3;
    uVar8 = puVar3[1];
    if ((int)uVar8 < 0) {
      *param_3 = '-';
      param_1[0xe] = 1;
      uVar8 = uVar8 & 0x7fffffff;
    }
    else {
      if (param_1[2] == 0x20) {
        *param_3 = ' ';
      }
      else {
        if (param_1[2] != 0x2b) goto LAB_81c1d098;
        *param_3 = '+';
      }
      param_1[0xe] = 1;
    }
LAB_81c1d098:
    param_1[8] = (int)(param_3 + param_1[0xe]);
    if (*param_2 == 'G') {
      *param_2 = 'E';
    }
    else if (*param_2 == 'g') {
      *param_2 = 'e';
    }
    if (param_1[7] < 0) {
      param_1[7] = 6;
    }
    FUN_81c1d2d4((int)param_1,param_2,uVar7,uVar8,param_2);
    iVar4 = param_1[6];
    goto LAB_81c1d128;
  case 'X':
  case 'o':
  case 'u':
  case 'x':
    if (param_1[5] == 0x68) {
      trap();
    }
    puVar3 = (uint *)(*param_1 + 3U & 0xfffffffc);
    *param_1 = (int)(puVar3 + 1);
    uVar7 = *puVar3;
    if ((param_1[4] == 0x48) && (*param_2 != 'u')) {
      param_3[param_1[0xe]] = '0';
      iVar4 = param_1[0xe];
      param_1[0xe] = iVar4 + 1;
      if (*param_2 != 'o') {
        param_3[iVar4 + 1] = *param_2;
        param_1[0xe] = param_1[0xe] + 1;
      }
    }
    param_1[8] = (int)(param_3 + param_1[0xe]);
    uVar8 = 8;
    if ((*param_2 != 'o') && (uVar8 = 10, *param_2 != 'u')) {
      uVar8 = 0x10;
    }
    goto LAB_81c1d014;
  case 'c':
                    /* WARNING: Does not return */
    pcVar1 = (code *)trap(0);
    (*pcVar1)();
  case 'd':
  case 'i':
    if (param_1[5] == 0x68) {
      trap();
    }
    puVar3 = (uint *)(*param_1 + 3U & 0xfffffffc);
    *param_1 = (int)(puVar3 + 1);
    uVar7 = *puVar3;
    if ((int)uVar7 < 0) {
      *param_3 = '-';
      param_1[0xe] = 1;
      uVar7 = -uVar7;
    }
    else {
      if (param_1[2] == 0x20) {
        *param_3 = ' ';
      }
      else {
        if (param_1[2] != 0x2b) goto LAB_81c1cf50;
        *param_3 = '+';
      }
      param_1[0xe] = 1;
    }
LAB_81c1cf50:
    param_1[8] = (int)(param_3 + param_1[0xe]);
    uVar8 = 10;
LAB_81c1d014:
    FUN_81c1d198((int)param_1,uVar7,uVar8,param_2);
    iVar4 = param_1[6];
    goto LAB_81c1d128;
  case 's':
    puVar2 = (undefined4 *)(*param_1 + 3U & 0xfffffffc);
    *param_1 = (int)(puVar2 + 1);
    pcVar6 = (char *)*puVar2;
    param_1[8] = (int)pcVar6;
    iVar4 = FUN_81c1b9d4(pcVar6);
    param_1[0xf] = iVar4;
    iVar5 = param_1[7];
    if ((-1 < iVar5) && (iVar5 < iVar4)) {
      param_1[0xf] = iVar5;
    }
  }
  iVar4 = param_1[6];
LAB_81c1d128:
  iVar4 = (((((iVar4 - param_1[0xe]) - param_1[10]) - param_1[0xf]) - param_1[0xb]) - param_1[0x10])
          - param_1[0xc];
  param_1[6] = iVar4;
  if (0 < iVar4) {
    if (param_1[1] == 0x4c) {
      param_1[9] = iVar4;
    }
    else {
      param_1[0xd] = param_1[6];
    }
  }
  return param_2 + 1;
}




#define s_0123456789abcdef_81c20b54 (*(char (*)[1])(0x81c20b54u))
#define s_0123456789ABCDEF_81c20b68 (*(char (*)[1])(0x81c20b68u))
/* VA 0x81c1d198; body bytes 316 */

void FUN_81c1d198(int param_1,uint param_2,uint param_3,char *param_4)

{
  unsigned char sg_stack[48] __attribute__((aligned(8)));
#define acStack_21 (*(char (*)[25])(sg_stack + 7))

  char *pcVar1;
  int iVar2;
  int iVar3;

  pcVar1 = s_0123456789ABCDEF_81c20b68;
  if (*param_4 != 'X') {
    pcVar1 = s_0123456789abcdef_81c20b54;
  }
  iVar2 = 0x18;
  do {
    iVar3 = iVar2;
    iVar2 = iVar3 + -1;
    if (param_3 == 0) {
      trap(7);
    }
    acStack_21[iVar3] = pcVar1[param_2 % param_3];
    if (param_3 == 0) {
      trap(7);
    }
  } while ((param_2 / param_3 != 0) && (param_2 = param_2 / param_3, 0 < iVar2));
  *(uint *)(param_1 + 0x3c) = 0x18U - iVar2;
  crt_memcpy(*(void **)(param_1 + 0x20),acStack_21 + iVar3,0x18U - iVar2);
  iVar2 = *(int *)(param_1 + 0x1c);
  if (iVar2 < 1) {
    if (*(int *)(param_1 + 0x1c) == 0) {
      if (**(char **)(param_1 + 0x20) != '0') {
        return;
      }
      *(undefined4 *)(param_1 + 0x3c) = 0;
      return;
    }
    if (*(int *)(param_1 + 0xc) != 0x48) {
      return;
    }
    if (*(int *)(param_1 + 4) != 0x4c) {
      return;
    }
    if (*(int *)(param_1 + 0x18) <= *(int *)(param_1 + 0x3c) + *(int *)(param_1 + 0x38)) {
      return;
    }
    iVar2 = (*(int *)(param_1 + 0x18) - *(int *)(param_1 + 0x3c)) - *(int *)(param_1 + 0x38);
  }
  else {
    if (iVar2 <= *(int *)(param_1 + 0x3c)) {
      return;
    }
    iVar2 = iVar2 - *(int *)(param_1 + 0x3c);
  }
  *(int *)(param_1 + 0x28) = iVar2;
  return;
}


#undef s_0123456789abcdef_81c20b54
#undef s_0123456789ABCDEF_81c20b68
#undef acStack_21

#define DAT_81c20c70 (*(uint *)(0x81c20c70u))
#define DAT_81c20c74 (*(undefined4 *)(0x81c20c74u))
#define DAT_81c20bd0 (*(undefined4 *)(0x81c20bd0u))
#define DAT_81c20c78 (*(uint *)(0x81c20c78u))
#define DAT_81c20c7c (*(undefined4 *)(0x81c20c7cu))
#define DAT_81c20b80 (*(undefined4 *)(0x81c20b80u))
#define DAT_81c20b84 (*(undefined4 *)(0x81c20b84u))
#define DAT_81c20bf8 (*(undefined *)(0x81c20bf8u))
#define DAT_81c20bfc (*(undefined *)(0x81c20bfcu))
/* VA 0x81c1d2d4; body bytes 1876 */

void FUN_81c1d2d4(int param_1,undefined4 param_2,uint param_3,int param_4,char *param_5)

{
  unsigned char sg_stack[108] __attribute__((aligned(8)));
  (*(char * *)(sg_stack + 88)) = param_5;
#define local_48 (*(char (*)[24])(sg_stack + 0))
#define local_30 (*(uint (*)[2])(sg_stack + 24))
#define param_5 (*(char * *)(sg_stack + 88))

  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;

  uVar8 = CONCAT44(param_4,param_3);
  if ((param_4 == 0x7ff00000) && (param_3 == 0)) {
    crt_memcpy(*(void **)(param_1 + 0x20),&DAT_81c20bf8,3);
    *(undefined4 *)(param_1 + 0x3c) = 3;
LAB_81c1d378:
    *(undefined4 *)(param_1 + 0xc) = 0x4c;
    return;
  }
  if (0x7fefffff < param_4) {
    crt_memcpy(*(void **)(param_1 + 0x20),&DAT_81c20bfc,3);
    *(undefined4 *)(param_1 + 0x3c) = 3;
    *(undefined4 *)(param_1 + 0x38) = 0;
    goto LAB_81c1d378;
  }
  local_30[0] = 0;
  iVar2 = FUN_81c1f330(param_3,param_4,DAT_81c20c70,DAT_81c20c74);
  if (iVar2 < 0) {
    iVar2 = FUN_81c1f2a0(param_3,param_4,0,0);
    uVar9 = CONCAT44(param_4,param_3);
    uVar6 = local_30[0];
    if (((0 < iVar2) &&
        (iVar2 = FUN_81c1f3c0(param_3,param_4,DAT_81c20c78,DAT_81c20c7c),
        uVar9 = CONCAT44(param_4,param_3), uVar6 = local_30[0], iVar2 < 0)) &&
       (iVar2 = 0, uVar9 = CONCAT44(param_4,param_3), 0 < DAT_81c20bd0)) {
      cVar1 = *param_5;
      do {
        uVar7 = (undefined4)((ulonglong)uVar8 >> 0x20);
        if ((cVar1 == 'e') || (cVar1 == 'E')) {
          uVar9 = FUN_81c1ec50((uint)uVar8,uVar7,(&DAT_81c20b80)[iVar2 * 2],
                               (&DAT_81c20b84)[iVar2 * 2]);
          uVar5 = DAT_81c20c70;
          uVar7 = DAT_81c20c74;
        }
        else {
          uVar9 = FUN_81c1ec50((uint)uVar8,uVar7,(&DAT_81c20b80)[iVar2 * 2],
                               (&DAT_81c20b84)[iVar2 * 2]);
          uVar5 = DAT_81c20c78;
          uVar7 = DAT_81c20c7c;
        }
        iVar3 = FUN_81c1f3c0((uint)uVar9,(int)((ulonglong)uVar9 >> 0x20),uVar5,uVar7);
        if (iVar3 < 0) {
          uVar6 = uVar6 - (&DAT_81c20bd0)[iVar2];
          uVar8 = uVar9;
        }
        iVar2 = iVar2 + 1;
        uVar9 = uVar8;
      } while (0 < (&DAT_81c20bd0)[iVar2]);
    }
  }
  else {
    iVar2 = 0;
    uVar9 = uVar8;
    uVar6 = local_30[0];
    if (0 < DAT_81c20bd0) {
      iVar3 = 0;
      do {
        uVar7 = (undefined4)((ulonglong)uVar8 >> 0x20);
        iVar4 = FUN_81c1f330((uint)uVar8,uVar7,*(uint *)((int)&DAT_81c20b80 + iVar3),
                             *(undefined4 *)((int)&DAT_81c20b84 + iVar3));
        if (-1 < iVar4) {
          uVar8 = FUN_81c1efe0((uint)uVar8,uVar7,*(uint *)((int)&DAT_81c20b80 + iVar3),
                               *(undefined4 *)((int)&DAT_81c20b84 + iVar3));
          uVar6 = uVar6 + (&DAT_81c20bd0)[iVar2];
        }
        iVar2 = iVar2 + 1;
        iVar3 = iVar2 * 8;
        uVar9 = uVar8;
      } while (0 < (&DAT_81c20bd0)[iVar2]);
    }
  }
  local_30[0] = uVar6;
  uVar7 = (undefined4)((ulonglong)uVar9 >> 0x20);
  uVar6 = (uint)uVar9;
  if ((*param_5 == 'e') || (*param_5 == 'E')) {
    iVar2 = 0x11;
    if (*(int *)(param_1 + 0x1c) < 0x11) {
      iVar2 = *(int *)(param_1 + 0x1c) + 1;
    }
    iVar2 = FUN_81c1da28(uVar6,uVar7,(int *)local_30,iVar2,local_48);
    **(char **)(param_1 + 0x20) = local_48[0];
    iVar3 = 1;
    if (((1 < iVar2) || (*(int *)(param_1 + 0x10) == 0x48)) || (0 < *(int *)(param_1 + 0x1c))) {
      *(undefined1 *)(*(int *)(param_1 + 0x20) + 1) = 0x2e;
      crt_memcpy((void *)(*(int *)(param_1 + 0x20) + 2),local_48 + 1,iVar2 - 1);
      iVar3 = iVar2 + 1;
    }
    *(int *)(param_1 + 0x3c) = iVar3;
    if (iVar2 + -1 < *(int *)(param_1 + 0x1c)) {
      *(int *)(param_1 + 0x2c) = (*(int *)(param_1 + 0x1c) - iVar2) + 1;
    }
    *(char *)(*(int *)(param_1 + 0x20) + iVar3) = *param_5;
    if ((int)local_30[0] < 0) {
      *(undefined1 *)(*(int *)(param_1 + 0x20) + iVar3 + 1) = 0x2d;
      local_30[0] = -local_30[0];
    }
    else {
      *(undefined1 *)(*(int *)(param_1 + 0x20) + iVar3 + 1) = 0x2b;
    }
    iVar3 = iVar3 + 2;
    if ((int)local_30[0] < 10) {
      *(undefined1 *)(*(int *)(param_1 + 0x20) + iVar3) = 0x30;
      *(char *)(iVar3 + *(int *)(param_1 + 0x20) + 1) = (char)local_30[0] + '0';
      iVar2 = 4;
    }
    else {
      iVar2 = 10;
      for (; 0 < (int)local_30[0]; local_30[0] = (int)local_30[0] / 10) {
        local_48[iVar2] = (char)local_30[0] + (char)((int)local_30[0] / 10) * -10 + '0';
        iVar2 = iVar2 + -1;
      }
      crt_memcpy((void *)(iVar3 + *(int *)(param_1 + 0x20)),local_48 + iVar2 + 1,10 - iVar2);
      iVar2 = 0xc - iVar2;
    }
    *(int *)(param_1 + 0x40) = iVar2;
    goto LAB_81c1d99c;
  }
  if ((int)local_30[0] < 0) {
    iVar2 = 0;
    if ((int)~local_30[0] < *(int *)(param_1 + 0x1c)) {
      iVar3 = *(int *)(param_1 + 0x1c) + local_30[0] + 1;
      iVar2 = 0x11;
      if (iVar3 < 0x12) {
        iVar2 = iVar3;
      }
    }
    uVar6 = FUN_81c1da28(uVar6,uVar7,(int *)local_30,iVar2,local_48);
    **(undefined1 **)(param_1 + 0x20) = 0x30;
    uVar7 = 1;
    if (((0 < (int)uVar6) || (*(int *)(param_1 + 0x10) == 0x48)) || (0 < *(int *)(param_1 + 0x1c)))
    {
      *(undefined1 *)(*(int *)(param_1 + 0x20) + 1) = 0x2e;
      uVar7 = 2;
      crt_memcpy((void *)(*(int *)(param_1 + 0x20) + 2),local_48,uVar6);
    }
    *(undefined4 *)(param_1 + 0x3c) = uVar7;
    *(uint *)(param_1 + 0x40) = uVar6;
    if (*(int *)(param_1 + 0x1c) < (int)~local_30[0]) {
      *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_1 + 0x1c);
    }
    else {
      *(uint *)(param_1 + 0x2c) = ~local_30[0];
    }
    if (*(int *)(param_1 + 0x1c) <= *(int *)(param_1 + 0x40) + *(int *)(param_1 + 0x2c))
    goto LAB_81c1d99c;
    iVar2 = (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 0x40)) - *(int *)(param_1 + 0x2c);
  }
  else {
    iVar2 = 0x11;
    if (*(int *)(param_1 + 0x1c) < (int)(0x10 - local_30[0])) {
      iVar2 = *(int *)(param_1 + 0x1c) + local_30[0] + 1;
    }
    uVar6 = FUN_81c1da28(uVar6,uVar7,(int *)local_30,iVar2,local_48);
    if ((int)uVar6 <= (int)(local_30[0] + 1)) {
      crt_memcpy(*(void **)(param_1 + 0x20),local_48,uVar6);
      *(uint *)(param_1 + 0x3c) = uVar6;
      if ((*(int *)(param_1 + 0x10) == 0x48) || (0 < *(int *)(param_1 + 0x1c))) {
        *(undefined1 *)(*(int *)(param_1 + 0x20) + uVar6) = 0x2e;
        *(undefined4 *)(param_1 + 0x40) = 1;
        *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x1c);
      }
      if ((int)uVar6 < (int)(local_30[0] + 1)) {
        *(uint *)(param_1 + 0x2c) = (local_30[0] - uVar6) + 1;
      }
      goto LAB_81c1d99c;
    }
    crt_memcpy(*(void **)(param_1 + 0x20),local_48,local_30[0] + 1);
    *(undefined1 *)(*(int *)(param_1 + 0x20) + local_30[0] + 1) = 0x2e;
    crt_memcpy((void *)(*(int *)(param_1 + 0x20) + local_30[0] + 2),local_48 + local_30[0] + 1,
               (uVar6 - local_30[0]) - 1);
    *(uint *)(param_1 + 0x3c) = local_30[0] + 1;
    *(uint *)(param_1 + 0x40) = uVar6 - local_30[0];
    if (*(int *)(param_1 + 0x1c) <= (int)((uVar6 - local_30[0]) + -1)) goto LAB_81c1d99c;
    iVar2 = (*(int *)(param_1 + 0x1c) - uVar6) + local_30[0] + 1;
  }
  *(int *)(param_1 + 0x30) = iVar2;
LAB_81c1d99c:
  if (*(int *)(param_1 + 0xc) != 0x48) {
    return;
  }
  if (*(int *)(param_1 + 4) != 0x4c) {
    return;
  }
  iVar2 = *(int *)(param_1 + 0x38) + *(int *)(param_1 + 0x3c) + *(int *)(param_1 + 0x2c) +
          *(int *)(param_1 + 0x40) + *(int *)(param_1 + 0x30);
  if (*(int *)(param_1 + 0x18) <= iVar2) {
    return;
  }
  *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x18) - iVar2;
  return;
}


#undef DAT_81c20c70
#undef DAT_81c20c74
#undef DAT_81c20bd0
#undef DAT_81c20c78
#undef DAT_81c20c7c
#undef DAT_81c20b80
#undef DAT_81c20b84
#undef DAT_81c20bf8
#undef DAT_81c20bfc
#undef local_48
#undef local_30
#undef param_5

#define DAT_81c20c70 (*(uint *)(0x81c20c70u))
#define DAT_81c20c74 (*(undefined4 *)(0x81c20c74u))
/* VA 0x81c1da28; body bytes 476 */

int FUN_81c1da28(uint param_1,undefined4 param_2,int *param_3,int param_4,undefined1 *param_5)

{
  unsigned char sg_stack[20] __attribute__((aligned(8)));
  (*(undefined1 * *)(sg_stack + 0)) = param_5;
#define param_5 (*(undefined1 * *)(sg_stack + 0))

  uint uVar1;
  undefined4 uVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  int iVar7;
  undefined4 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;

  uVar10 = CONCAT44(param_2,param_1);
  iVar4 = FUN_81c1f210(param_1,param_2,0,0);
  uVar2 = DAT_81c20c74;
  uVar1 = DAT_81c20c70;
  if (iVar4 == 0) {
    *param_5 = 0x30;
    return 1;
  }
  if (param_4 == 0) {
    return 0;
  }
  iVar4 = 0;
  if (0 < param_4 + 1) {
    do {
      uVar8 = (undefined4)((ulonglong)uVar10 >> 0x20);
      uVar5 = FUN_81c1f540((uint)uVar10,uVar8);
      param_5[iVar4] = (char)uVar5 + '0';
      uVar9 = FUN_81c1f450(uVar5);
      uVar10 = FUN_81c1ebd8((uint)uVar10,uVar8,(uint)uVar9,(int)((ulonglong)uVar9 >> 0x20));
      uVar10 = FUN_81c1ec50((uint)uVar10,(int)((ulonglong)uVar10 >> 0x20),uVar1,uVar2);
      iVar4 = iVar4 + 1;
    } while (iVar4 < param_4 + 1);
  }
  iVar4 = iVar4 + -1;
  if ((param_4 - *param_3) + -1 < 0x10) {
    pcVar6 = param_5 + iVar4;
    if ((0xf < *param_3 + 1) || (pcVar6 = param_5 + iVar4, iVar4 < 0x10)) goto LAB_81c1db48;
    iVar4 = 0xf;
  }
  pcVar6 = param_5 + iVar4;
LAB_81c1db48:
  if (*pcVar6 < '5') {
    param_5[iVar4] = 0x30;
    do {
      iVar7 = iVar4;
      iVar4 = iVar7 + -1;
    } while (param_5[iVar7 + -1] == '0');
  }
  else {
    do {
      iVar7 = iVar4;
      if (iVar7 == 0) {
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


#undef DAT_81c20c70
#undef DAT_81c20c74
#undef param_5

#define DAT_81c2b198 (*(undefined4 *)(0x81c2b198u))
/* VA 0x81c1dc10; body bytes 376 */

int FUN_81c1dc10(int param_1)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  int unaff_gp;

  if (param_1 != 0) {
    piVar3 = (int *)(*(int *)(unaff_gp + 0xe0) + -8);
    if (7 < *(int *)(unaff_gp + 0xe8) - *(int *)(unaff_gp + 0xf0)) {
      uVar2 = 0;
      if (*(int *)(unaff_gp + 0xec) != 0) {
        do {
          uVar1 = piVar3[1];
          if (((uVar1 & 1) == 0) && (uVar4 = param_1 + 3U & 0xfffffffc, uVar4 <= uVar1)) {
            piVar3[1] = uVar4 | 1;
            iVar5 = *piVar3;
            if (uVar1 - uVar4 == 0) {
              return iVar5;
            }
            FUN_81c1deb0(*(undefined4 **)(unaff_gp + 0xe8),(*(int *)(unaff_gp + 0xec) - uVar2) + -1)
            ;
            piVar3[-1] = uVar1 - uVar4;
            piVar3[-2] = iVar5 + uVar4;
            *(int *)(unaff_gp + 0xe8) = *(int *)(unaff_gp + 0xe8) + -8;
            *(int *)(unaff_gp + 0xec) = *(int *)(unaff_gp + 0xec) + 1;
            return iVar5;
          }
          uVar2 = uVar2 + 1;
          piVar3 = piVar3 + -2;
        } while (uVar2 < *(uint *)(unaff_gp + 0xec));
      }
      if ((param_1 + 3U & 0xfffffffc) + 8 <=
          (uint)(*(int *)(unaff_gp + 0xe8) - *(int *)(unaff_gp + 0xf0))) {
        iVar5 = *(int *)(unaff_gp + 0xf0);
        *piVar3 = iVar5;
        uVar2 = param_1 + 3U & 0xfffffffc;
        piVar3[1] = uVar2 | 1;
        *(uint *)(unaff_gp + 0xf0) = uVar2 + *(int *)(unaff_gp + 0xf0);
        *(int *)(unaff_gp + 0xec) = *(int *)(unaff_gp + 0xec) + 1;
        *(int *)(unaff_gp + 0xe8) = *(int *)(unaff_gp + 0xe8) + -8;
        return iVar5;
      }
    }
    DAT_81c2b198 = 0xc;
  }
  return 0;
}


#undef DAT_81c2b198


/* VA 0x81c1dd88; body bytes 80 */

uint FUN_81c1dd88(int param_1,int param_2)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  int unaff_gp;

  uVar2 = param_1 + 3U & 0xfffffffc;
  *(uint *)(unaff_gp + 0xe4) = uVar2;
  uVar3 = param_2 + 3U & 0xfffffffc;
  *(uint *)(unaff_gp + 0xe0) = uVar3;
  bVar1 = uVar3 < uVar2 + 0x10;
  if (!bVar1) {
    *(undefined4 *)(unaff_gp + 0xf0) = *(undefined4 *)(unaff_gp + 0xe4);
    *(int *)(unaff_gp + 0xe8) = *(int *)(unaff_gp + 0xe0) + -8;
    *(undefined4 *)(unaff_gp + 0xec) = 0;
  }
  return (uint)bVar1;
}





/* VA 0x81c1de00; body bytes 20 */

int FUN_81c1de00(int param_1)

{
  if (param_1 < 0) {
    param_1 = -param_1;
  }
  return param_1;
}




#define g_rand_state (*(undefined4 *)(0x81c2b1a8u))
/* VA 0x81c1de20; body bytes 60 */

uint crt_rand(void)

{
  g_rand_state = g_rand_state * 0x41c64e6d + 0x3039;
  return g_rand_state / 0xffff & 0x7fff;
}


#undef g_rand_state

#define g_rand_state (*(undefined4 *)(0x81c2b1a8u))
/* VA 0x81c1de60; body bytes 16 */

void crt_srand(uint seed)

{
  g_rand_state = seed;
  return;
}


#undef g_rand_state


/* VA 0x81c1de70; body bytes 52 */

char * FUN_81c1de70(char *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;

  pcVar2 = param_1;
  do {
    pcVar3 = pcVar2;
    pcVar2 = pcVar3 + 1;
  } while (*pcVar3 != '\0');
  pcVar3 = pcVar3 + -1;
  do {
    cVar1 = *param_2;
    param_2 = param_2 + 1;
    pcVar3 = pcVar3 + 1;
    *pcVar3 = cVar1;
  } while (cVar1 != '\0');
  return param_1;
}





/* VA 0x81c1deb0; body bytes 48 */

void FUN_81c1deb0(undefined4 *param_1,int param_2)

{
  int iVar1;

  iVar1 = 0;
  if (0 < param_2) {
    do {
      param_1[-2] = *param_1;
      param_1[-1] = param_1[1];
      iVar1 = iVar1 + 1;
      param_1 = param_1 + 2;
    } while (iVar1 < param_2);
  }
  return;
}





/* VA 0x81c1dee0; body bytes 40 */

void FUN_81c1dee0(undefined1 *param_1,int param_2)

{
  undefined1 *puVar1;
  int iVar2;

  iVar2 = 0;
  puVar1 = param_1;
  if (0 < param_2) {
    do {
      *puVar1 = 0;
      iVar2 = iVar2 + 1;
      puVar1 = param_1 + iVar2;
    } while (iVar2 < param_2);
  }
  return;
}





/* VA 0x81c1df08; body bytes 48 */

void FUN_81c1df08(undefined4 *param_1,int param_2)

{
  int iVar1;

  iVar1 = 0;
  if (0 < param_2) {
    do {
      *param_1 = param_1[-2];
      param_1[1] = param_1[-1];
      iVar1 = iVar1 + 1;
      param_1 = param_1 + -2;
    } while (iVar1 < param_2);
  }
  return;
}




#define DAT_81c20c60 (*(uint *)(0x81c20c60u))
#define DAT_81c20c64 (*(uint *)(0x81c20c64u))
/* VA 0x81c1df40; body bytes 100 */

uint FUN_81c1df40(uint param_1)

{
  int iVar1;
  uint uVar2;

  iVar1 = FUN_81c1e620(param_1,DAT_81c20c60);
  if (iVar1 < 0) {
    uVar2 = FUN_81c1e770(param_1);
  }
  else {
    uVar2 = soft_float_add(param_1,DAT_81c20c64);
    uVar2 = FUN_81c1e770(uVar2);
    uVar2 = uVar2 + 0x80000000;
  }
  return uVar2;
}


#undef DAT_81c20c60
#undef DAT_81c20c64

#define DAT_81c20c00 (*(undefined *)(0x81c20c00u))
/* VA 0x81c1dfb0; body bytes 572 */

uint * FUN_81c1dfb0(uint *param_1,uint *param_2,uint *param_3)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;

  uVar6 = *param_1;
  puVar5 = param_1;
  if ((1 < uVar6) && (uVar3 = *param_2, puVar5 = param_2, 1 < uVar3)) {
    if (uVar6 == 4) {
      puVar5 = param_1;
      if (((uVar3 ^ 4) == 0) && (puVar5 = (uint *)&DAT_81c20c00, param_1[1] == param_2[1])) {
        puVar5 = param_1;
      }
    }
    else {
      puVar5 = param_2;
      if ((uVar3 ^ 4) != 0) {
        if (uVar3 == 2) {
          puVar5 = param_1;
          if ((uVar6 ^ 2) == 0) {
            *param_3 = uVar6;
            param_3[1] = param_1[1];
            param_3[2] = param_1[2];
            param_3[3] = param_1[3];
            param_3[1] = param_1[1] & param_2[1];
            puVar5 = param_3;
          }
        }
        else {
          puVar5 = param_2;
          if ((uVar6 ^ 2) != 0) {
            uVar7 = param_1[2];
            uVar6 = param_2[2];
            uVar3 = param_1[3];
            iVar2 = uVar7 - uVar6;
            if (iVar2 < 0) {
              iVar2 = -iVar2;
            }
            uVar8 = param_2[3];
            if (iVar2 < 0x20) {
              bVar1 = (int)uVar7 < (int)uVar6;
              uVar4 = uVar6;
              if ((int)uVar7 > (int)uVar6) {
                iVar2 = uVar7 - uVar6;
                do {
                  iVar2 = iVar2 + -1;
                  uVar8 = uVar8 & 1 | uVar8 >> 1;
                } while (iVar2 != 0);
                bVar1 = false;
                uVar4 = uVar7;
              }
              uVar6 = uVar7;
              if (bVar1) {
                iVar2 = uVar4 - uVar7;
                do {
                  iVar2 = iVar2 + -1;
                  uVar3 = uVar3 & 1 | uVar3 >> 1;
                  uVar6 = uVar4;
                } while (iVar2 != 0);
              }
            }
            else if ((int)uVar7 <= (int)uVar6) {
              uVar3 = 0;
            }
            else {
              uVar8 = 0;
              uVar6 = uVar7;
            }
            uVar7 = param_1[1];
            if (uVar7 == param_2[1]) {
              uVar3 = uVar3 + uVar8;
              param_3[1] = uVar7;
              param_3[2] = uVar6;
              param_3[3] = uVar3;
            }
            else {
              uVar4 = uVar8 - uVar3;
              if (uVar7 == 0) {
                uVar4 = uVar3 - uVar8;
              }
              if ((int)uVar4 < 0) {
                param_3[1] = 1;
                param_3[2] = uVar6;
                param_3[3] = -uVar4;
              }
              else {
                param_3[2] = uVar6;
                param_3[3] = uVar4;
                param_3[1] = 0;
              }
              uVar3 = param_3[3];
              if (uVar3 - 1 < 0x3fffffff) {
                uVar6 = param_3[2];
                do {
                  uVar3 = uVar3 * 2;
                  uVar6 = uVar6 - 1;
                } while (uVar3 - 1 < 0x3fffffff);
                param_3[2] = uVar6;
                param_3[3] = uVar3;
              }
            }
            *param_3 = 3;
            puVar5 = param_3;
            if ((int)uVar3 < 0) {
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


#undef DAT_81c20c00


/* VA 0x81c1e1ec; body bytes 96 */

uint soft_float_add(uint left,uint right)

{
  unsigned char sg_stack[72] __attribute__((aligned(8)));
#define local_10 (*(uint *)(sg_stack + 48))
#define local_c (*(uint *)(sg_stack + 52))
#define auStack_30 (*(uint (*)[4])(sg_stack + 16))
#define auStack_40 (*(uint (*)[4])(sg_stack + 0))
#define auStack_20 (*(uint (*)[4])(sg_stack + 32))

  uint *puVar1;
  uint uVar2;

  local_10 = left;
  local_c = right;
  FUN_81c1f790(&local_10,auStack_40);
  FUN_81c1f790(&local_c,auStack_30);
  puVar1 = FUN_81c1dfb0(auStack_40,auStack_30,auStack_20);
  uVar2 = FUN_81c1f620(puVar1);
  return uVar2;
}


#undef local_10
#undef local_c
#undef auStack_30
#undef auStack_40
#undef auStack_20


/* VA 0x81c1e24c; body bytes 108 */

uint soft_float_sub(uint left,uint right)

{
  unsigned char sg_stack[72] __attribute__((aligned(8)));
#define auStack_40 (*(uint (*)[4])(sg_stack + 0))
#define local_2c (*(uint *)(sg_stack + 20))
#define local_10 (*(uint *)(sg_stack + 48))
#define local_c (*(uint *)(sg_stack + 52))
#define uStack_30 (*(uint *)(sg_stack + 16))
#define auStack_20 (*(uint (*)[4])(sg_stack + 32))

  uint *puVar1;
  uint uVar2;

  local_10 = left;
  local_c = right;
  FUN_81c1f790(&local_10,auStack_40);
  FUN_81c1f790(&local_c,&uStack_30);
  local_2c = local_2c ^ 1;
  puVar1 = FUN_81c1dfb0(auStack_40,&uStack_30,auStack_20);
  uVar2 = FUN_81c1f620(puVar1);
  return uVar2;
}


#undef auStack_40
#undef local_2c
#undef local_10
#undef local_c
#undef uStack_30
#undef auStack_20

#define DAT_81c20c00 (*(undefined *)(0x81c20c00u))
/* VA 0x81c1e2c0; body bytes 488 */

uint soft_float_mul(uint left,uint right)

{
  unsigned char sg_stack[72] __attribute__((aligned(8)));
#define local_40 (*(uint *)(sg_stack + 0))
#define local_3c (*(uint *)(sg_stack + 4))
#define local_38 (*(int *)(sg_stack + 8))
#define local_34 (*(uint *)(sg_stack + 12))
#define local_30 (*(uint *)(sg_stack + 16))
#define local_2c (*(uint *)(sg_stack + 20))
#define local_28 (*(int *)(sg_stack + 24))
#define local_24 (*(uint *)(sg_stack + 28))
#define local_20 (*(uint *)(sg_stack + 32))
#define local_1c (*(uint *)(sg_stack + 36))
#define local_18 (*(int *)(sg_stack + 40))
#define local_14 (*(uint *)(sg_stack + 44))
#define local_10 (*(uint *)(sg_stack + 48))
#define local_c (*(uint *)(sg_stack + 52))

  ulonglong uVar1;
  uint uVar2;
  uint *puVar3;

  local_10 = left;
  local_c = right;
  FUN_81c1f790(&local_10,&local_40);
  FUN_81c1f790(&local_c,&local_30);
  puVar3 = &local_20;
  if (local_40 < 2) {
LAB_81c1e33c:
    local_3c = (uint)(local_3c != local_2c);
    puVar3 = &local_40;
  }
  else {
    if (1 < local_30) {
      if (local_40 == 4) {
        puVar3 = (uint *)&DAT_81c20c00;
        if (local_30 == 2) goto LAB_81c1e354;
        goto LAB_81c1e33c;
      }
      if (local_30 == 4) {
        puVar3 = (uint *)&DAT_81c20c00;
        if ((local_40 ^ 2) == 0) goto LAB_81c1e354;
      }
      else {
        if ((local_40 ^ 2) == 0) goto LAB_81c1e33c;
        if (local_30 != 2) {
          uVar1 = (ulonglong)local_34 * (ulonglong)local_24;
          local_18 = local_38 + local_28 + 2;
          local_1c = (uint)(local_3c != local_2c);
          if ((longlong)uVar1 < 0) {
            uVar2 = (uint)uVar1;
            local_18 = local_38 + local_28 + 3;
            if ((uVar1 & 0x100000000) != 0) {
              uVar2 = uVar2 >> 1 | 0x80000000;
            }
            uVar1 = CONCAT44((uint)(uVar1 >> 0x21),uVar2);
          }
          if (uVar1 < 0x4000000000000000) {
            do {
              uVar2 = (int)(uVar1 >> 0x20) << 1;
              local_18 = local_18 + -1;
              if ((int)uVar1 < 0) {
                uVar2 = uVar2 | 1;
              }
              uVar1 = CONCAT44(uVar2,(int)uVar1 << 1);
            } while (uVar2 < 0x40000000);
          }
          local_14 = (uint)(uVar1 >> 0x20);
          if (((local_14 & 0x7f) == 0x40) && (((uVar1 & 0x8000000000) != 0 || ((int)uVar1 != 0)))) {
            local_14 = local_14 + 0x40;
          }
          local_20 = 3;
          goto LAB_81c1e354;
        }
      }
    }
    local_2c = (uint)(local_3c != local_2c);
    puVar3 = &local_30;
  }
LAB_81c1e354:
  uVar2 = FUN_81c1f620(puVar3);
  return uVar2;
}


#undef DAT_81c20c00
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

#define DAT_81c20c00 (*(undefined *)(0x81c20c00u))
/* VA 0x81c1e4b0; body bytes 356 */

uint soft_float_div(uint left,uint right)

{
  unsigned char sg_stack[56] __attribute__((aligned(8)));
#define local_30 (*(uint *)(sg_stack + 0))
#define local_2c (*(uint *)(sg_stack + 4))
#define local_28 (*(int *)(sg_stack + 8))
#define local_24 (*(uint *)(sg_stack + 12))
#define local_20 (*(uint *)(sg_stack + 16))
#define local_1c (*(uint *)(sg_stack + 20))
#define local_18 (*(int *)(sg_stack + 24))
#define local_14 (*(uint *)(sg_stack + 28))
#define local_10 (*(uint *)(sg_stack + 32))
#define local_c (*(uint *)(sg_stack + 36))

  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;

  local_10 = left;
  local_c = right;
  FUN_81c1f790(&local_10,&local_30);
  FUN_81c1f790(&local_c,&local_20);
  puVar4 = &local_30;
  if ((local_30 < 2) || (puVar4 = &local_20, local_20 < 2)) goto LAB_81c1e548;
  local_2c = local_2c ^ local_1c;
  if ((local_30 == 4) || (local_30 == 2)) {
    puVar4 = (uint *)&DAT_81c20c00;
    uVar2 = local_24;
    if (local_30 == local_20) goto LAB_81c1e548;
  }
  else {
    if (local_20 == 4) {
      local_24 = 0;
      local_28 = 0;
      puVar4 = &local_30;
      goto LAB_81c1e548;
    }
    if (local_20 == 2) {
      local_30 = 4;
      puVar4 = &local_30;
      goto LAB_81c1e548;
    }
    bVar1 = local_24 < local_14;
    local_28 = local_28 - local_18;
    if (bVar1) {
      local_28 = local_28 + -1;
      local_24 = local_24 << 1;
      bVar1 = local_24 < local_14;
    }
    uVar3 = 0x40000000;
    uVar2 = 0;
    do {
      if (!bVar1) {
        uVar2 = uVar2 | uVar3;
        local_24 = local_24 - local_14;
      }
      local_24 = local_24 << 1;
      uVar3 = uVar3 >> 1;
      bVar1 = local_24 < local_14;
    } while (uVar3 != 0);
    if (((uVar2 & 0x7f) == 0x40) && (((uVar2 & 0x80) != 0 || (local_24 != 0)))) {
      uVar2 = uVar2 + 0x40;
    }
  }
  local_24 = uVar2;
  puVar4 = &local_30;
LAB_81c1e548:
  uVar2 = FUN_81c1f620(puVar4);
  return uVar2;
}


#undef DAT_81c20c00
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


/* VA 0x81c1e620; body bytes 132 */

int FUN_81c1e620(uint param_1,uint param_2)

{
  unsigned char sg_stack[56] __attribute__((aligned(8)));
#define local_30 (*(uint (*)[4])(sg_stack + 0))
#define local_20 (*(uint (*)[4])(sg_stack + 16))
#define local_10 (*(uint *)(sg_stack + 32))
#define local_c (*(uint *)(sg_stack + 36))

  int iVar1;

  local_10 = param_1;
  local_c = param_2;
  FUN_81c1f790(&local_10,local_30);
  FUN_81c1f790(&local_c,local_20);
  iVar1 = -1;
  if ((1 < local_30[0]) && (1 < local_20[0])) {
    iVar1 = FUN_81c1f860(local_30,local_20);
  }
  return iVar1;
}


#undef local_30
#undef local_20
#undef local_10
#undef local_c

#define DAT_81c20c64 (*(uint *)(0x81c20c64u))
/* VA 0x81c1e6b0; body bytes 180 */

uint FUN_81c1e6b0(uint param_1)

{
  unsigned char sg_stack[32] __attribute__((aligned(8)));
#define local_10 (*(int *)(sg_stack + 8))
#define local_c (*(uint *)(sg_stack + 12))
#define local_18 (*(uint *)(sg_stack + 0))
#define local_14 (*(int *)(sg_stack + 4))

  uint uVar1;

  local_14 = -((int)param_1 >> 0x1f);
  local_18 = 3;
  if (param_1 == 0) {
    local_18 = 2;
  }
  else {
    local_10 = 0x1e;
    local_c = param_1;
    if (local_14 != 0) {
      if (param_1 == 0x80000000) {
        return DAT_81c20c64;
      }
      local_c = -param_1;
    }
    if (local_c < 0x40000000) {
      local_10 = 0x1e;
      do {
        local_c = local_c << 1;
        local_10 = local_10 + -1;
      } while (local_c < 0x40000000);
    }
  }
  uVar1 = FUN_81c1f620(&local_18);
  return uVar1;
}


#undef DAT_81c20c64
#undef local_10
#undef local_c
#undef local_18
#undef local_14


/* VA 0x81c1e770; body bytes 160 */

uint FUN_81c1e770(uint param_1)

{
  unsigned char sg_stack[40] __attribute__((aligned(8)));
#define local_20 (*(uint *)(sg_stack + 0))
#define local_1c (*(int *)(sg_stack + 4))
#define local_18 (*(int *)(sg_stack + 8))
#define local_14 (*(uint *)(sg_stack + 12))
#define local_10 (*(uint (*)[2])(sg_stack + 16))


  local_10[0] = param_1;
  FUN_81c1f790(local_10,&local_20);
  if (local_20 == 2) {
    return 0;
  }
  if (local_20 < 2) {
    return 0;
  }
  if (local_20 != 4) {
    if (local_18 < 0) {
      return 0;
    }
    if (local_18 < 0x1f) {
      local_14 = local_14 >> (0x1eU - local_18 & 0x1f);
      if (local_1c == 0) {
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

#define DAT_81c20c10 (*(undefined *)(0x81c20c10u))
/* VA 0x81c1e810; body bytes 864 */

uint * FUN_81c1e810(uint *param_1,uint *param_2,uint *param_3)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;

  uVar4 = *param_1;
  puVar7 = param_1;
  if ((1 < uVar4) && (uVar3 = *param_2, puVar7 = param_2, 1 < uVar3)) {
    if (uVar4 == 4) {
      puVar7 = param_1;
      if (((uVar3 ^ 4) == 0) && (puVar7 = (uint *)&DAT_81c20c10, param_1[1] == param_2[1])) {
        puVar7 = param_1;
      }
    }
    else {
      puVar7 = param_2;
      if ((uVar3 ^ 4) != 0) {
        if (uVar3 == 2) {
          puVar7 = param_1;
          if ((uVar4 ^ 2) == 0) {
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
        else {
          puVar7 = param_2;
          if ((uVar4 ^ 2) != 0) {
            uVar11 = param_1[2];
            uVar4 = param_2[2];
            uVar10 = param_1[4];
            uVar3 = param_1[5];
            iVar2 = uVar11 - uVar4;
            if (iVar2 < 0) {
              iVar2 = -iVar2;
            }
            uVar8 = param_2[4];
            uVar9 = param_2[5];
            if (iVar2 < 0x40) {
              bVar1 = (int)uVar11 < (int)uVar4;
              uVar5 = uVar4;
              if ((int)uVar11 > (int)uVar4) {
                iVar2 = uVar11 - uVar4;
                do {
                  uVar4 = uVar9 << 0x1f;
                  uVar9 = uVar9 >> 1;
                  iVar2 = iVar2 + -1;
                  uVar8 = uVar8 & 1 | uVar8 >> 1 | uVar4;
                } while (iVar2 != 0);
                bVar1 = false;
                uVar5 = uVar11;
              }
              uVar4 = uVar11;
              if (bVar1) {
                iVar2 = uVar5 - uVar11;
                do {
                  uVar4 = uVar3 << 0x1f;
                  uVar3 = uVar3 >> 1;
                  iVar2 = iVar2 + -1;
                  uVar10 = uVar10 & 1 | uVar10 >> 1 | uVar4;
                  uVar4 = uVar5;
                } while (iVar2 != 0);
              }
            }
            else if ((int)uVar11 <= (int)uVar4) {
              uVar10 = 0;
              uVar3 = 0;
            }
            else {
              uVar8 = 0;
              uVar9 = 0;
              uVar4 = uVar11;
            }
            uVar11 = param_1[1];
            if (uVar11 == param_2[1]) {
              param_3[1] = uVar11;
              param_3[2] = uVar4;
              param_3[4] = uVar10 + uVar8;
              param_3[5] = uVar3 + uVar9 + (uint)(uVar10 + uVar8 < uVar8);
            }
            else {
              uVar5 = uVar8 - uVar10;
              uVar6 = (uVar9 - uVar3) - (uint)(uVar8 < uVar10);
              if (uVar11 == 0) {
                uVar5 = uVar10 - uVar8;
                uVar6 = (uVar3 - uVar9) - (uint)(uVar10 < uVar8);
              }
              if ((int)uVar6 < 0) {
                param_3[1] = 1;
                param_3[2] = uVar4;
                param_3[4] = -uVar5;
                param_3[5] = -(uint)(-uVar5 != 0) - uVar6;
              }
              else {
                param_3[2] = uVar4;
                param_3[4] = uVar5;
                param_3[5] = uVar6;
                param_3[1] = 0;
              }
              uVar4 = param_3[4];
              uVar3 = param_3[5];
              uVar10 = (uVar3 - 1) + (uint)(uVar4 != 0);
              while ((uVar10 < 0x10000000 && ((uVar10 != 0xfffffff || (uVar4 != 0))))) {
                uVar3 = uVar3 << 1 | uVar4 >> 0x1f;
                uVar4 = uVar4 * 2;
                uVar10 = (uVar3 - 1) + (uint)(uVar4 != 0);
                param_3[2] = param_3[2] - 1;
                param_3[4] = uVar4;
                param_3[5] = uVar3;
              }
            }
            *param_3 = 3;
            puVar7 = param_3;
            if (0x1fffffff < param_3[5]) {
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


#undef DAT_81c20c10


/* VA 0x81c1eb70; body bytes 104 */

undefined8 FUN_81c1eb70(uint param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  unsigned char sg_stack[104] __attribute__((aligned(8)));
#define local_10 (*(uint *)(sg_stack + 80))
#define local_c (*(undefined4 *)(sg_stack + 84))
#define auStack_48 (*(uint (*)[6])(sg_stack + 24))
#define auStack_60 (*(uint (*)[6])(sg_stack + 0))
#define auStack_30 (*(uint (*)[6])(sg_stack + 48))
#define local_18 (*(uint *)(sg_stack + 72))
#define local_14 (*(undefined4 *)(sg_stack + 76))

  uint *puVar1;
  undefined8 uVar2;

  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  FUN_81c1fc40(&local_18,auStack_60);
  FUN_81c1fc40(&local_10,auStack_48);
  puVar1 = FUN_81c1e810(auStack_60,auStack_48,auStack_30);
  uVar2 = FUN_81c1f9a0(puVar1);
  return uVar2;
}


#undef local_10
#undef local_c
#undef auStack_48
#undef auStack_60
#undef auStack_30
#undef local_18
#undef local_14


/* VA 0x81c1ebd8; body bytes 116 */

undefined8 FUN_81c1ebd8(uint param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  unsigned char sg_stack[104] __attribute__((aligned(8)));
#define local_44 (*(uint *)(sg_stack + 28))
#define local_18 (*(uint *)(sg_stack + 72))
#define local_14 (*(undefined4 *)(sg_stack + 76))
#define auStack_60 (*(uint (*)[6])(sg_stack + 0))
#define local_10 (*(uint *)(sg_stack + 80))
#define local_c (*(undefined4 *)(sg_stack + 84))
#define uStack_48 (*(uint *)(sg_stack + 24))
#define auStack_30 (*(uint (*)[6])(sg_stack + 48))

  uint *puVar1;
  undefined8 uVar2;

  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  FUN_81c1fc40(&local_18,auStack_60);
  FUN_81c1fc40(&local_10,&uStack_48);
  local_44 = local_44 ^ 1;
  puVar1 = FUN_81c1e810(auStack_60,&uStack_48,auStack_30);
  uVar2 = FUN_81c1f9a0(puVar1);
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

#define DAT_81c20c10 (*(undefined *)(0x81c20c10u))
/* VA 0x81c1ec50; body bytes 904 */

undefined8 FUN_81c1ec50(uint param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  unsigned char sg_stack[104] __attribute__((aligned(8)));
#define local_70 (*(uint *)(sg_stack + 0))
#define local_6c (*(uint *)(sg_stack + 4))
#define local_68 (*(int *)(sg_stack + 8))
#define local_60 (*(uint *)(sg_stack + 16))
#define local_5c (*(uint *)(sg_stack + 20))
#define local_58 (*(uint *)(sg_stack + 24))
#define local_54 (*(uint *)(sg_stack + 28))
#define local_50 (*(int *)(sg_stack + 32))
#define local_48 (*(uint *)(sg_stack + 40))
#define local_44 (*(uint *)(sg_stack + 44))
#define local_40 (*(uint *)(sg_stack + 48))
#define local_3c (*(uint *)(sg_stack + 52))
#define local_38 (*(int *)(sg_stack + 56))
#define local_30 (*(ulonglong *)(sg_stack + 64))
#define local_28 (*(uint *)(sg_stack + 72))
#define local_24 (*(undefined4 *)(sg_stack + 76))
#define local_20 (*(uint *)(sg_stack + 80))
#define local_1c (*(undefined4 *)(sg_stack + 84))

  longlong lVar1;
  longlong lVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  undefined8 uVar12;

  local_28 = param_1;
  local_24 = param_2;
  local_20 = param_3;
  local_1c = param_4;
  FUN_81c1fc40(&local_28,&local_70);
  FUN_81c1fc40(&local_20,&local_58);
  puVar5 = &local_40;
  if (local_70 < 2) {
LAB_81c1ece4:
    local_6c = (uint)(local_6c != local_54);
    puVar5 = &local_70;
  }
  else {
    if (1 < local_58) {
      if (local_70 == 4) {
        puVar5 = (uint *)&DAT_81c20c10;
        if (local_58 == 2) goto LAB_81c1ecfc;
        goto LAB_81c1ece4;
      }
      if (local_58 == 4) {
        puVar5 = (uint *)&DAT_81c20c10;
        if ((local_70 ^ 2) == 0) goto LAB_81c1ecfc;
      }
      else {
        if ((local_70 ^ 2) == 0) goto LAB_81c1ece4;
        if (local_58 != 2) {
          uVar8 = 0;
          lVar1 = (ulonglong)local_44 * (ulonglong)local_60;
          uVar10 = (uint)((ulonglong)lVar1 >> 0x20);
          lVar2 = (ulonglong)local_48 * (ulonglong)local_5c + lVar1;
          uVar6 = (uint)lVar2;
          uVar7 = (uint)((ulonglong)lVar2 >> 0x20);
          uVar9 = (uint)((ulonglong)local_48 * (ulonglong)local_60);
          uVar11 = (uint)((ulonglong)local_48 * (ulonglong)local_60 >> 0x20);
          if ((uVar7 < uVar10) || ((uVar10 == uVar7 && (uVar6 < (uint)lVar1)))) {
            uVar8 = 1;
          }
          uVar6 = uVar11 + uVar6;
          local_30 = (ulonglong)local_44 * (ulonglong)local_5c + CONCAT44(uVar8,uVar7) +
                     (ulonglong)(uVar6 < uVar11);
          local_3c = (uint)(local_6c != local_54);
          local_38 = local_68 + local_50 + 4;
          uVar3 = local_30;
          if (0x1fffffffffffffff < local_30) {
            do {
              uVar3 = local_30 & 1;
              uVar4 = local_30 >> 0x21;
              local_38 = local_38 + 1;
              local_30 = local_30 >> 1;
              if (uVar3 != 0) {
                uVar9 = uVar9 >> 1 | uVar6 << 0x1f;
                uVar6 = uVar6 >> 1 | 0x80000000;
              }
              uVar3 = local_30;
            } while (0x1fffffff < (uint)uVar4);
          }
          while (uVar3 < 0x1000000000000000) {
            local_38 = local_38 + -1;
            uVar3 = local_30 << 1;
            uVar7 = (uint)uVar3;
            if ((int)uVar6 < 0) {
              uVar7 = uVar7 | 1;
            }
            local_30 = CONCAT44((int)(uVar3 >> 0x20),uVar7);
            uVar6 = uVar6 << 1 | uVar9 >> 0x1f;
            uVar9 = uVar9 << 1;
          }
          if ((((uint)local_30 & 0xff) == 0x80) &&
             (((local_30 & 0x100) != 0 || (uVar9 != 0 || uVar6 != 0)))) {
            local_30 = local_30 + 0x80;
          }
          local_40 = 3;
          goto LAB_81c1ecfc;
        }
      }
    }
    local_54 = (uint)(local_6c != local_54);
    puVar5 = &local_58;
  }
LAB_81c1ecfc:
  uVar12 = FUN_81c1f9a0(puVar5);
  return uVar12;
}


#undef DAT_81c20c10
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

#define DAT_81c20c10 (*(undefined *)(0x81c20c10u))
/* VA 0x81c1efe0; body bytes 552 */

undefined8 FUN_81c1efe0(uint param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  unsigned char sg_stack[80] __attribute__((aligned(8)));
#define local_48 (*(uint *)(sg_stack + 0))
#define local_44 (*(uint *)(sg_stack + 4))
#define local_40 (*(int *)(sg_stack + 8))
#define local_38 (*(uint *)(sg_stack + 16))
#define local_34 (*(uint *)(sg_stack + 20))
#define local_30 (*(uint *)(sg_stack + 24))
#define local_2c (*(uint *)(sg_stack + 28))
#define local_28 (*(int *)(sg_stack + 32))
#define local_20 (*(uint *)(sg_stack + 40))
#define local_1c (*(uint *)(sg_stack + 44))
#define local_18 (*(uint *)(sg_stack + 48))
#define local_14 (*(undefined4 *)(sg_stack + 52))
#define local_10 (*(uint *)(sg_stack + 56))
#define local_c (*(undefined4 *)(sg_stack + 60))

  bool bVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined8 uVar7;

  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  FUN_81c1fc40(&local_18,&local_48);
  FUN_81c1fc40(&local_10,&local_30);
  puVar2 = &local_48;
  uVar3 = local_38;
  uVar6 = local_34;
  if ((1 < local_48) && (puVar2 = &local_30, 1 < local_30)) {
    local_44 = local_44 ^ local_2c;
    if ((local_48 == 4) || (local_48 == 2)) {
      puVar2 = (uint *)&DAT_81c20c10;
      if (local_48 != local_30) {
        puVar2 = &local_48;
      }
    }
    else if (local_30 == 4) {
      local_38 = 0;
      local_34 = 0;
      local_40 = 0;
      puVar2 = &local_48;
      uVar3 = local_38;
      uVar6 = local_34;
    }
    else if (local_30 == 2) {
      local_48 = 4;
      puVar2 = &local_48;
    }
    else {
      bVar1 = local_34 < local_1c;
      local_40 = local_40 - local_28;
      if ((bVar1) || ((local_1c == local_34 && (local_38 < local_20)))) {
        local_40 = local_40 + -1;
        local_34 = local_34 << 1 | local_38 >> 0x1f;
        local_38 = local_38 << 1;
        bVar1 = local_34 < local_1c;
      }
      uVar4 = 0x10000000;
      uVar3 = 0;
      uVar5 = 0;
      uVar6 = 0;
      do {
        if ((!bVar1) && ((local_1c != local_34 || (local_20 <= local_38)))) {
          bVar1 = local_38 < local_20;
          local_38 = local_38 - local_20;
          local_34 = (local_34 - local_1c) - (uint)bVar1;
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
      if (((uVar5 & 0xff) == 0x80) && (((uVar5 & 0x100) != 0 || (local_38 != 0 || local_34 != 0))))
      {
        uVar3 = uVar5 + 0x80;
        uVar6 = uVar6 + (uVar5 + 0x80 < 0x80);
      }
    }
  }
  local_34 = uVar6;
  local_38 = uVar3;
  uVar7 = FUN_81c1f9a0(puVar2);
  return uVar7;
}


#undef DAT_81c20c10
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


/* VA 0x81c1f210; body bytes 140 */

int FUN_81c1f210(uint param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  unsigned char sg_stack[80] __attribute__((aligned(8)));
#define local_48 (*(uint (*)[6])(sg_stack + 0))
#define local_30 (*(uint (*)[6])(sg_stack + 24))
#define local_18 (*(uint *)(sg_stack + 48))
#define local_14 (*(undefined4 *)(sg_stack + 52))
#define local_10 (*(uint *)(sg_stack + 56))
#define local_c (*(undefined4 *)(sg_stack + 60))

  int iVar1;

  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  FUN_81c1fc40(&local_18,local_48);
  FUN_81c1fc40(&local_10,local_30);
  iVar1 = 1;
  if ((1 < local_48[0]) && (1 < local_30[0])) {
    iVar1 = FUN_81c1fd60(local_48,local_30);
  }
  return iVar1;
}


#undef local_48
#undef local_30
#undef local_18
#undef local_14
#undef local_10
#undef local_c


/* VA 0x81c1f2a0; body bytes 140 */

int FUN_81c1f2a0(uint param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  unsigned char sg_stack[80] __attribute__((aligned(8)));
#define local_14 (*(undefined4 *)(sg_stack + 52))
#define local_10 (*(uint *)(sg_stack + 56))
#define local_c (*(undefined4 *)(sg_stack + 60))
#define local_48 (*(uint (*)[6])(sg_stack + 0))
#define local_30 (*(uint (*)[6])(sg_stack + 24))
#define local_18 (*(uint *)(sg_stack + 48))

  int iVar1;

  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  FUN_81c1fc40(&local_18,local_48);
  FUN_81c1fc40(&local_10,local_30);
  iVar1 = -1;
  if ((1 < local_48[0]) && (1 < local_30[0])) {
    iVar1 = FUN_81c1fd60(local_48,local_30);
  }
  return iVar1;
}


#undef local_14
#undef local_10
#undef local_c
#undef local_48
#undef local_30
#undef local_18


/* VA 0x81c1f330; body bytes 140 */

int FUN_81c1f330(uint param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  unsigned char sg_stack[80] __attribute__((aligned(8)));
#define local_30 (*(uint (*)[6])(sg_stack + 24))
#define local_18 (*(uint *)(sg_stack + 48))
#define local_14 (*(undefined4 *)(sg_stack + 52))
#define local_10 (*(uint *)(sg_stack + 56))
#define local_c (*(undefined4 *)(sg_stack + 60))
#define local_48 (*(uint (*)[6])(sg_stack + 0))

  int iVar1;

  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  FUN_81c1fc40(&local_18,local_48);
  FUN_81c1fc40(&local_10,local_30);
  iVar1 = -1;
  if ((1 < local_48[0]) && (1 < local_30[0])) {
    iVar1 = FUN_81c1fd60(local_48,local_30);
  }
  return iVar1;
}


#undef local_30
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_48


/* VA 0x81c1f3c0; body bytes 140 */

int FUN_81c1f3c0(uint param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  unsigned char sg_stack[80] __attribute__((aligned(8)));
#define local_48 (*(uint (*)[6])(sg_stack + 0))
#define local_30 (*(uint (*)[6])(sg_stack + 24))
#define local_18 (*(uint *)(sg_stack + 48))
#define local_14 (*(undefined4 *)(sg_stack + 52))
#define local_10 (*(uint *)(sg_stack + 56))
#define local_c (*(undefined4 *)(sg_stack + 60))

  int iVar1;

  local_18 = param_1;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  FUN_81c1fc40(&local_18,local_48);
  FUN_81c1fc40(&local_10,local_30);
  iVar1 = 1;
  if ((1 < local_48[0]) && (1 < local_30[0])) {
    iVar1 = FUN_81c1fd60(local_48,local_30);
  }
  return iVar1;
}


#undef local_48
#undef local_30
#undef local_18
#undef local_14
#undef local_10
#undef local_c

#define DAT_81c20c80 (*(undefined4 *)(0x81c20c80u))
#define DAT_81c20c84 (*(undefined4 *)(0x81c20c84u))
/* VA 0x81c1f450; body bytes 228 */

undefined8 FUN_81c1f450(uint param_1)

{
  unsigned char sg_stack[40] __attribute__((aligned(8)));
#define local_20 (*(uint *)(sg_stack + 0))
#define local_1c (*(int *)(sg_stack + 4))
#define local_18 (*(int *)(sg_stack + 8))
#define local_10 (*(uint *)(sg_stack + 16))
#define local_c (*(uint *)(sg_stack + 20))

  uint uVar1;
  undefined8 uVar2;

  uVar1 = (int)param_1 >> 0x1f;
  local_1c = -uVar1;
  local_20 = 3;
  if (param_1 == 0) {
    local_20 = 2;
  }
  else {
    local_18 = 0x3c;
    if (local_1c != 0) {
      if (param_1 == 0x80000000) {
        return CONCAT44(DAT_81c20c84,DAT_81c20c80);
      }
      param_1 = -param_1;
      uVar1 = (int)param_1 >> 0x1f;
    }
    local_10 = param_1;
    local_c = uVar1;
    if (uVar1 < 0x10000000) {
      local_18 = 0x3c;
      do {
        local_c = local_c << 1 | local_10 >> 0x1f;
        local_10 = local_10 << 1;
        local_18 = local_18 + -1;
      } while (local_c < 0x10000000);
    }
  }
  uVar2 = FUN_81c1f9a0(&local_20);
  return uVar2;
}


#undef DAT_81c20c80
#undef DAT_81c20c84
#undef local_20
#undef local_1c
#undef local_18
#undef local_10
#undef local_c


/* VA 0x81c1f540; body bytes 220 */

uint FUN_81c1f540(uint param_1,undefined4 param_2)

{
  unsigned char sg_stack[48] __attribute__((aligned(8)));
#define local_28 (*(uint *)(sg_stack + 0))
#define local_24 (*(int *)(sg_stack + 4))
#define local_20 (*(int *)(sg_stack + 8))
#define local_18 (*(uint *)(sg_stack + 16))
#define local_14 (*(uint *)(sg_stack + 20))
#define local_10 (*(uint *)(sg_stack + 24))
#define local_c (*(undefined4 *)(sg_stack + 28))

  uint uVar1;

  local_10 = param_1;
  local_c = param_2;
  FUN_81c1fc40(&local_10,&local_28);
  if (local_28 == 2) {
    return 0;
  }
  if (local_28 < 2) {
    return 0;
  }
  if (local_28 != 4) {
    if (local_20 < 0) {
      return 0;
    }
    if (local_20 < 0x1f) {
      uVar1 = 0x3c - local_20;
      if ((int)(uVar1 * 0x4000000) < 0) {
        local_18 = local_14 >> (uVar1 & 0x1f);
      }
      else {
        local_18 = local_18 >> (uVar1 & 0x1f);
        if (uVar1 * 0x4000000 != 0) {
          local_18 = local_18 | local_14 << (-uVar1 & 0x1f);
        }
      }
      if (local_24 == 0) {
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


/* VA 0x81c1f620; body bytes 360 */

uint FUN_81c1f620(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;

  uVar1 = *param_1;
  uVar2 = param_1[3];
  uVar3 = 0;
  if (uVar1 < 2) {
    uVar2 = uVar2 | 0x100000;
    uVar3 = 0xff;
    goto LAB_81c1f648;
  }
  if (uVar1 == 4) {
LAB_81c1f740:
    uVar3 = 0xff;
  }
  else if (uVar1 != 2) {
    if (uVar2 == 0) goto LAB_81c1f648;
    uVar1 = param_1[2];
    if ((int)uVar1 < -0x7e) {
      uVar1 = -uVar1 - 0x7e;
      if ((int)uVar1 < 0x1a) {
        uVar2 = uVar2 >> (uVar1 & 0x1f) | (uint)((uVar2 & (1 << (uVar1 & 0x1f)) - 1U) != 0);
      }
      else {
        uVar2 = 0;
      }
      if ((uVar2 & 0x7f) == 0x40) {
        if ((uVar2 & 0x80) != 0) {
          uVar2 = uVar2 + 0x40;
        }
      }
      else {
        uVar2 = uVar2 + 0x3f;
      }
      if (0x3fffffff < uVar2) {
        uVar3 = 1;
      }
    }
    else {
      if (0x7f < (int)uVar1) goto LAB_81c1f740;
      uVar3 = uVar1 + 0x7f;
      if ((uVar2 & 0x7f) == 0x40) {
        if ((uVar2 & 0x80) != 0) {
          uVar2 = uVar2 + 0x40;
        }
      }
      else {
        uVar2 = uVar2 + 0x3f;
      }
      if ((int)uVar2 < 0) {
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





/* VA 0x81c1f790; body bytes 204 */

void FUN_81c1f790(uint *param_1,undefined4 *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;

  uVar1 = *param_1;
  uVar4 = uVar1 >> 0x17 & 0xff;
  param_2[1] = uVar1 >> 0x1f;
  uVar5 = uVar1 & 0x7fffff;
  if (uVar4 == 0) {
    uVar2 = 2;
    if (uVar5 != 0) {
      uVar5 = uVar5 << 7;
      iVar3 = -0x7e;
      param_2[2] = 0xffffff82;
      *param_2 = 3;
      if (uVar5 < 0x40000000) {
        do {
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
  else if (uVar4 == 0xff) {
    uVar2 = 4;
    if (uVar5 != 0) {
      if ((uVar1 & 0x100000) == 0) {
        *param_2 = 0;
      }
      else {
        *param_2 = 1;
      }
      goto LAB_81c1f7fc;
    }
  }
  else {
    param_2[3] = uVar5 << 7 | 0x40000000;
    uVar2 = 3;
    param_2[2] = uVar4 - 0x7f;
  }
  *param_2 = uVar2;
  return;
}





/* VA 0x81c1f860; body bytes 320 */

int FUN_81c1f860(uint *param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;

  uVar2 = *param_1;
  if (uVar2 < 2) {
    return 1;
  }
  uVar3 = *param_2;
  if (uVar3 < 2) {
    return 1;
  }
  if ((uVar2 == 4) && (uVar3 == 4)) {
    return param_2[1] - param_1[1];
  }
  if (uVar2 == 4) {
LAB_81c1f908:
    if (param_1[1] != 0) {
      return -1;
    }
    return 1;
  }
  if (uVar3 != 4) {
    if (uVar2 != 2) {
      if (uVar3 == 2) goto LAB_81c1f908;
      uVar2 = param_1[1];
      if (uVar2 == param_2[1]) {
        if ((int)param_1[2] <= (int)param_2[2]) {
          if ((int)param_2[2] <= (int)param_1[2]) {
            if (param_2[3] < param_1[3]) goto LAB_81c1f934;
            if (param_2[3] <= param_1[3]) {
              return 0;
            }
          }
          if (uVar2 != 0) {
            return 1;
          }
          return -1;
        }
      }
LAB_81c1f934:
      if (uVar2 != 0) {
        return -1;
      }
      return 1;
    }
    if (uVar3 == 2) {
      return 0;
    }
  }
  iVar1 = 1;
  if (param_2[1] == 0) {
    iVar1 = -1;
  }
  return iVar1;
}





/* VA 0x81c1f9a0; body bytes 668 */

undefined8 FUN_81c1f9a0(uint *param_1)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;

  uVar4 = *param_1;
  uVar6 = param_1[4];
  uVar7 = param_1[5];
  uVar8 = 0;
  if (uVar4 < 2) {
    uVar7 = uVar7 | 0x80000;
    uVar8 = 0x7ff;
    goto LAB_81c1f9d4;
  }
  if (uVar4 == 4) {
LAB_81c1fba8:
    uVar8 = 0x7ff;
  }
  else if (uVar4 != 2) {
    if (uVar6 == 0 && uVar7 == 0) goto LAB_81c1f9d4;
    uVar4 = param_1[2];
    if ((int)uVar4 < -0x3fe) {
      uVar4 = -uVar4 - 0x3fe;
      if ((int)uVar4 < 0x39) {
        if ((int)(uVar4 * 0x4000000) < 0) {
          uVar2 = 1 << (uVar4 & 0x1f);
          iVar3 = 0;
        }
        else {
          uVar2 = 0 << (uVar4 & 0x1f);
          if (uVar4 * 0x4000000 != 0) {
            uVar2 = uVar2 | 1U >> (-uVar4 & 0x1f);
          }
          iVar3 = 1 << (uVar4 & 0x1f);
        }
        uVar2 = uVar7 & (uVar2 - 1) + (uint)(iVar3 - 1U != 0xffffffff);
        if ((int)(uVar4 * 0x4000000) < 0) {
          uVar5 = uVar7 >> (uVar4 & 0x1f);
          uVar7 = 0;
        }
        else {
          uVar5 = uVar6 >> (uVar4 & 0x1f);
          if (uVar4 * 0x4000000 != 0) {
            uVar5 = uVar5 | uVar7 << (-uVar4 & 0x1f);
          }
          uVar7 = uVar7 >> (uVar4 & 0x1f);
        }
        uVar6 = uVar5 | ((uVar6 & iVar3 - 1U) != 0 || uVar2 != 0);
      }
      else {
        uVar6 = 0;
        uVar7 = 0;
      }
      if ((uVar6 & 0xff) == 0x80) {
        if ((uVar6 & 0x100) != 0) {
          uVar6 = uVar6 + 0x80;
          bVar1 = uVar6 < 0x80;
          goto LAB_81c1faa0;
        }
      }
      else {
        uVar6 = uVar6 + 0x7f;
        bVar1 = uVar6 < 0x7f;
LAB_81c1faa0:
        uVar7 = uVar7 + bVar1;
      }
      uVar2 = uVar7 << 0x18;
      if (0xfffffff < uVar7) {
        uVar8 = 1;
LAB_81c1fabc:
        uVar2 = uVar7 << 0x18;
      }
    }
    else {
      if (0x3ff < (int)uVar4) goto LAB_81c1fba8;
      uVar8 = uVar4 + 0x3ff;
      if ((uVar6 & 0xff) == 0x80) {
        if ((uVar6 & 0x100) != 0) {
          uVar6 = uVar6 + 0x80;
          bVar1 = uVar6 < 0x80;
          goto LAB_81c1fbdc;
        }
      }
      else {
        uVar6 = uVar6 + 0x7f;
        bVar1 = uVar6 < 0x7f;
LAB_81c1fbdc:
        uVar7 = uVar7 + bVar1;
      }
      uVar2 = uVar7 << 0x18;
      if (0x1fffffff < uVar7) {
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
  return CONCAT44(uVar7 & 0xfffff | (uVar8 & 0x7ff) << 0x14 | param_1[1] << 0x1f,uVar6);
}





/* VA 0x81c1fc40; body bytes 288 */

void FUN_81c1fc40(uint *param_1,undefined4 *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;

  uVar1 = param_1[1];
  uVar4 = uVar1 >> 0x14 & 0x7ff;
  uVar5 = *param_1;
  uVar6 = uVar1 & 0xfffff;
  param_2[1] = uVar1 >> 0x1f;
  if (uVar4 == 0) {
    if (uVar5 != 0 || uVar6 != 0) {
      uVar6 = uVar6 << 8 | uVar5 >> 0x18;
      uVar5 = uVar5 << 8;
      param_2[2] = 0xfffffc02;
      *param_2 = 3;
      if (uVar6 < 0x10000000) {
        iVar3 = -0x3fe;
        do {
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
  else if (uVar4 == 0x7ff) {
    uVar2 = 4;
    if (uVar5 != 0 || uVar6 != 0) {
      if ((uVar1 & 0x80000) == 0) {
        *param_2 = 0;
      }
      else {
        *param_2 = 1;
      }
      goto LAB_81c1fcdc;
    }
  }
  else {
    param_2[4] = uVar5 << 8;
    param_2[5] = uVar6 << 8 | uVar5 >> 0x18 | 0x10000000;
    uVar2 = 3;
    param_2[2] = uVar4 - 0x3ff;
  }
  *param_2 = uVar2;
  return;
}





/* VA 0x81c1fd60; body bytes 392 */

int FUN_81c1fd60(uint *param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;

  uVar2 = *param_1;
  if (uVar2 < 2) {
    return 1;
  }
  uVar3 = *param_2;
  if (uVar3 < 2) {
    return 1;
  }
  if ((uVar2 == 4) && (uVar3 == 4)) {
    return param_2[1] - param_1[1];
  }
  if (uVar2 == 4) {
LAB_81c1fe08:
    if (param_1[1] != 0) {
      return -1;
    }
    return 1;
  }
  if (uVar3 != 4) {
    if (uVar2 != 2) {
      if (uVar3 == 2) goto LAB_81c1fe08;
      uVar2 = param_1[1];
      if (uVar2 == param_2[1]) {
        if ((int)param_1[2] <= (int)param_2[2]) {
          if ((int)param_2[2] <= (int)param_1[2]) {
            uVar4 = param_1[5];
            uVar3 = param_2[5];
            if ((uVar3 < uVar4) || ((uVar4 == uVar3 && (param_2[4] < param_1[4]))))
            goto LAB_81c1fe34;
            if (uVar3 <= uVar4) {
              if (uVar3 != uVar4) {
                return 0;
              }
              if (param_2[4] <= param_1[4]) {
                return 0;
              }
            }
          }
          if (uVar2 != 0) {
            return 1;
          }
          return -1;
        }
      }
LAB_81c1fe34:
      if (uVar2 != 0) {
        return -1;
      }
      return 1;
    }
    if (uVar3 == 2) {
      return 0;
    }
  }
  iVar1 = 1;
  if (param_2[1] == 0) {
    iVar1 = -1;
  }
  return iVar1;
}

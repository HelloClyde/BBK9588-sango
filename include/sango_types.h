#ifndef SANGO_TYPES_H
#define SANGO_TYPES_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <bda_sango_compat.h>

/* The reconstructed ABI is MIPS O32. Preserve widths and signedness when
 * replacing decompiler spellings; this toolchain uses unsigned long for u32. */
_Static_assert(__builtin_types_compatible_p(uint8_t, unsigned char), "u8 ABI");
_Static_assert(__builtin_types_compatible_p(uint16_t, unsigned short), "u16 ABI");
_Static_assert(sizeof(uint32_t) == sizeof(unsigned int), "u32 ABI width");
_Static_assert(__builtin_types_compatible_p(uint64_t, unsigned long long), "u64 ABI");
_Static_assert(__builtin_types_compatible_p(int64_t, signed long long), "s64 ABI");

/* Recovered runtime callbacks use the original unprototyped O32 call form. */
typedef int SangoLegacyCode();
#define CONCAT44(a, b) (((uint64_t)(uint32_t)(a) << 32) | (uint32_t)(b))
#define CONCAT22(a, b) (((uint32_t)(uint16_t)(a) << 16) | (uint16_t)(b))
#define CONCAT31(a, b) (((uint32_t)(a) << 8) | (uint8_t)(b))
#define CONCAT13(a, b) (((uint32_t)(uint8_t)(a) << 24) | ((uint32_t)(b)&0xffffffu))
static inline SangoLegacyCode *sango_legacy_trap()
{
    __builtin_trap();
    return (SangoLegacyCode *)0;
}

#endif

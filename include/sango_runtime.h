#ifndef SANGO_RUNTIME_H
#define SANGO_RUNTIME_H
#include "sango_types.h"

/* 软件浮点内部表示，非IEEE754打包值。指数以32位补码保存；
 * 分类依次为sNaN、qNaN、零、有限数、无穷。尾数含舍入保护位。 */
typedef struct
{
    uint32_t kind;
    uint32_t sign;
    uint32_t exponent_bits;
    uint32_t significand;
} SangoSoftF32Parts;

typedef struct
{
    uint32_t kind;
    uint32_t sign;
    uint32_t exponent_bits;
    uint32_t reserved;
    uint32_t significand_low;
    uint32_t significand_high;
} SangoSoftF64Parts;

_Static_assert(sizeof(SangoSoftF32Parts) == 16, "soft f32 parts layout");
_Static_assert(sizeof(SangoSoftF64Parts) == 24, "soft f64 parts layout");
_Static_assert(offsetof(SangoSoftF64Parts, significand_low) == 16, "soft f64 mantissa");

char *sango_crt_memchr(char *buffer, int character, int byte_count);
void sango_crt_sprintf_words(uint8_t *output, uint8_t *format, uint32_t argument0,
                             uint32_t argument1);
int sango_crt_strlen(char *text);
int sango_crt_strtol(char *cursor, uint32_t *end_pointer, int base);
void sango_crt_atoi_compat(char *text);
char *sango_crt_strcpy(char *destination, char *source);
void *crt_memset(void *dst, int value, uint32_t size);
void *crt_memcpy(void *dst, void *src, uint32_t size);
uint8_t *sango_crt_stub_1bd3c(void);
void sango_crt_stub_1bd48(void);
int sango_crt_vformat(uint8_t *format, uint32_t *arguments, uint8_t *emit_callback_address,
                      uint32_t emit_context);
void sango_crt_append_character(uint8_t character, int *output_cursor_address);
void sango_crt_initialize(void);
int sango_crt_read_buffer(uint32_t stream_handle, uint8_t *output, int requested_bytes);
void sango_crt_abort_loop(void);
void sango_crt_reset_input_buffer(void);
void crt_diagnostic_noop(uint32_t ignored, ...);
int sango_crt_isdigit(char character);
int sango_crt_isspace(char character);
int sango_crt_toupper(char character);
int sango_crt_format_entry(uint8_t *output, uint8_t *format, int argument0, uint32_t argument1);
int sango_crt_format_words(int output_mode, void *output_target, uint8_t *format, int *arguments);
char *sango_crt_format_field(int *field, char *conversion, char *prefix_buffer);
void sango_crt_format_unsigned_digits(int field_address, uint32_t value, uint32_t radix,
                                      char *conversion);
void sango_crt_format_double_digits(int field_address, uint32_t abi_alignment_word,
                                    uint32_t value_low, int value_high, char *conversion);
int sango_crt_scale_double_decimal(uint32_t value_low, uint32_t value_high, int *decimal_exponent,
                                   int requested_digits, uint8_t *output_digits);
int sango_crt_heap_allocate(int requested_bytes);
uint32_t sango_crt_heap_initialize(int heap_begin, int heap_end);
int sango_crt_abs(int value);
uint32_t crt_rand(void);
void crt_srand(uint32_t seed);
char *sango_crt_strcat(char *destination, char *source);
void sango_crt_heap_shift_forward(uint32_t *descriptor_words, int descriptor_count);
void sango_crt_zero_bytes(uint8_t *buffer, int byte_count);
void sango_crt_heap_shift_backward(uint32_t *destination, int block_count);
uint32_t sango_soft_f32_to_int(uint32_t float_bits);
uint32_t *sango_soft_add_f32_parts(uint32_t *left, uint32_t *right, uint32_t *output);
uint32_t soft_float_add(uint32_t left, uint32_t right);
uint32_t soft_float_sub(uint32_t left, uint32_t right);
uint32_t soft_float_mul(uint32_t left, uint32_t right);
uint32_t soft_float_div(uint32_t left, uint32_t right);
int sango_soft_compare_f32(uint32_t left, uint32_t right);
uint32_t sango_soft_int_to_f32(uint32_t integer_value);
uint32_t sango_soft_unpack_f32_integer(uint32_t float_bits);
uint32_t *sango_soft_add_f64_parts(uint32_t *left, uint32_t *right, uint32_t *output);
uint64_t sango_soft_add_f64(uint32_t left_low, uint32_t left_high, uint32_t right_low,
                            uint32_t right_high);
uint64_t sango_soft_sub_f64(uint32_t left_low, uint32_t left_high, uint32_t right_low,
                            uint32_t right_high);
uint64_t sango_soft_mul_f64(uint32_t left_low, uint32_t left_high, uint32_t right_low,
                            uint32_t right_high);
uint64_t sango_soft_div_f64(uint32_t left_low, uint32_t left_high, uint32_t right_low,
                            uint32_t right_high);
int sango_soft_compare_f64_nan_high(uint32_t left_low, uint32_t left_high, uint32_t right_low,
                                    uint32_t right_high);
int sango_soft_compare_f64_nan_low(uint32_t left_low, uint32_t left_high, uint32_t right_low,
                                   uint32_t right_high);
int sango_soft_compare_f64_nan_low_compat(uint32_t left_low, uint32_t left_high, uint32_t right_low,
                                          uint32_t right_high);
int sango_soft_compare_f64_nan_high_compat(uint32_t left_low, uint32_t left_high,
                                           uint32_t right_low, uint32_t right_high);
uint64_t sango_soft_int_to_f64(uint32_t integer_value);
uint32_t sango_soft_f64_to_int(uint32_t float_low, uint32_t float_high);
uint32_t sango_soft_pack_f32(uint32_t *parts);
void sango_soft_unpack_f32(uint32_t *source_bits, uint32_t *parts);
int sango_soft_compare_f32_parts(uint32_t *left_parts, uint32_t *right_parts);
uint64_t sango_soft_pack_f64(uint32_t *parts);
void sango_soft_unpack_f64(uint32_t *source_bits, uint32_t *parts);
int sango_soft_compare_f64_parts(uint32_t *left_parts, uint32_t *right_parts);

#endif

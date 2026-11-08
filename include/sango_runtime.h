#ifndef SANGO_RUNTIME_H
#define SANGO_RUNTIME_H
#include "sango_types.h"

char *sango_crt_memchr(char *param_1, int param_2, int param_3);
void sango_crt_sprintf_words(uint8_t *param_1, uint8_t *param_2, uint32_t param_3,
                             uint32_t param_4);
int sango_crt_strlen(char *text);
int sango_crt_strtol(char *param_1, uint32_t *param_2, int param_3);
void sango_crt_atoi_compat(char *param_1);
char *sango_crt_strcpy(char *param_1, char *param_2);
void *crt_memset(void *dst, int value, uint32_t size);
void *crt_memcpy(void *dst, void *src, uint32_t size);
uint8_t *sango_crt_stub_1bd3c(void);
void sango_crt_stub_1bd48(void);
int sango_crt_vformat(uint8_t *param_1, uint32_t *param_2, uint8_t *param_3, uint32_t param_4);
void sango_crt_append_character(uint8_t param_1, int *param_2);
void sango_crt_initialize(void);
int sango_crt_read_buffer(uint32_t param_1, uint8_t *param_2, int param_3);
void sango_crt_abort_loop(void);
void sango_crt_reset_input_buffer(void);
void crt_diagnostic_noop(uint32_t ignored, ...);
int sango_crt_isdigit(char param_1);
int sango_crt_isspace(char param_1);
int sango_crt_toupper(char param_1);
int sango_crt_format_integer_entry(uint8_t *param_1, uint8_t *param_2, int param_3,
                                   uint32_t param_4);
int sango_crt_format_integer_words(int param_1, void *param_2, uint8_t *param_3, int *param_4);
char *sango_crt_format_float_field(int *param_1, char *param_2, char *param_3);
void sango_crt_format_unsigned_digits(int param_1, uint32_t param_2, uint32_t param_3,
                                      char *param_4);
void sango_crt_format_double_digits(int param_1, uint32_t param_2, uint32_t param_3, int param_4,
                                    char *param_5);
int sango_crt_scale_double_decimal(uint32_t param_1, uint32_t param_2, int *param_3, int param_4,
                                   uint8_t *param_5);
int sango_crt_heap_allocate(int param_1);
uint32_t sango_crt_heap_initialize(int param_1, int param_2);
int sango_crt_abs(int param_1);
uint32_t crt_rand(void);
void crt_srand(uint32_t seed);
char *sango_crt_strcat(char *param_1, char *param_2);
void sango_crt_heap_shift_forward(uint32_t *param_1, int param_2);
void sango_crt_zero_bytes(uint8_t *param_1, int param_2);
void sango_crt_heap_shift_backward(uint32_t *param_1, int param_2);
uint32_t sango_soft_f32_to_int(uint32_t param_1);
uint32_t *sango_soft_add_f32_parts(uint32_t *param_1, uint32_t *param_2, uint32_t *param_3);
uint32_t soft_float_add(uint32_t left, uint32_t right);
uint32_t soft_float_sub(uint32_t left, uint32_t right);
uint32_t soft_float_mul(uint32_t left, uint32_t right);
uint32_t soft_float_div(uint32_t left, uint32_t right);
int sango_soft_compare_f32(uint32_t param_1, uint32_t param_2);
uint32_t sango_soft_int_to_f32(uint32_t param_1);
uint32_t sango_soft_unpack_f32_integer(uint32_t param_1);
uint32_t *sango_soft_add_f64_parts(uint32_t *param_1, uint32_t *param_2, uint32_t *param_3);
uint64_t sango_soft_add_f64(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4);
uint64_t sango_soft_sub_f64(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4);
uint64_t sango_soft_mul_f64(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4);
uint64_t sango_soft_div_f64(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4);
int sango_soft_compare_f64_nan_high(uint32_t param_1, uint32_t param_2, uint32_t param_3,
                                    uint32_t param_4);
int sango_soft_compare_f64_nan_low(uint32_t param_1, uint32_t param_2, uint32_t param_3,
                                   uint32_t param_4);
int sango_soft_compare_f64_nan_low_compat(uint32_t param_1, uint32_t param_2, uint32_t param_3,
                                          uint32_t param_4);
int sango_soft_compare_f64_nan_high_compat(uint32_t param_1, uint32_t param_2, uint32_t param_3,
                                           uint32_t param_4);
uint64_t sango_soft_int_to_f64(uint32_t param_1);
uint32_t sango_soft_f64_to_int(uint32_t param_1, uint32_t param_2);
uint32_t sango_soft_pack_f32(uint32_t *param_1);
void sango_soft_unpack_f32(uint32_t *param_1, uint32_t *param_2);
int sango_soft_compare_f32_parts(uint32_t *param_1, uint32_t *param_2);
uint64_t sango_soft_pack_f64(uint32_t *param_1);
void sango_soft_unpack_f64(uint32_t *param_1, uint32_t *param_2);
int sango_soft_compare_f64_parts(uint32_t *param_1, uint32_t *param_2);

#endif

#ifndef SANGO_RESOURCES_H
#define SANGO_RESOURCES_H
#include "sango_types.h"

int sango_resource_item(uint32_t resource_id, char item_number, int package_base);
int sango_resource_offset(uint32_t resource_id);
uint32_t sango_resource_item_size(uint16_t resource_id, uint32_t item_number);
uint32_t sango_resource_read_text(uint16_t resource_id, uint32_t item_number, void *output);
void sango_resource_decode_bytes(int buffer_address, char encoding, uint32_t byte_count);
void sango_debug_draw_integer(uint16_t param_1, uint16_t param_2, int param_3, uint8_t param_4, char param_5);
void sango_debug_show_resource_id(int param_1);

#endif

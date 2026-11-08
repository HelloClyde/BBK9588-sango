#ifndef SANGO_APP_H
#define SANGO_APP_H
#include "sango_types.h"

void bda_entry(void);
void bda_runtime_init(void);
int sango_load_package_and_buffers(void);
int sango_release_package_and_buffers(void);
void sango_main(void);
void sango_game_lifecycle(void);
void sango_app_free_resource_buffer(void);
void sango_app_show_initialization_error(char error_kind);
int sango_resource_prepare_hook(uint32_t unused_callback_argument, int resource_offset);

#endif

#ifndef SANGO_SETTINGS_H
#define SANGO_SETTINGS_H
#include "sango_types.h"

enum { SANGO_SETTINGS_RESOURCE = 78 };
void sango_settings_load(const char *library_path);
void sango_settings_save(void);
void sango_settings_show(void);
void sango_settings_draw(unsigned int selected);
int sango_settings_touch(const int *event);
int sango_settings_sdk_read(void *bytes, unsigned int size);
int sango_settings_sdk_write(const void *bytes, unsigned int size);
#endif

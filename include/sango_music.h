#ifndef SANGO_MUSIC_H
#define SANGO_MUSIC_H
#include "sango_types.h"
enum
{
    SANGO_MUSIC_NONE,
    SANGO_MUSIC_MENU,
    SANGO_MUSIC_STRATEGY,
    SANGO_MUSIC_BATTLE
};
enum
{
    SANGO_MUSIC_TIMER_ID = 3,
    SANGO_MUSIC_POLL_MS = 10,
    SANGO_MUSIC_BLOCK_BYTES = 256,
    SANGO_MUSIC_BLOCK_SAMPLES = 505
};
void sango_music_set_library_path(const char *library_path);
void sango_music_set_scene(unsigned int scene);
void sango_music_poll(void);
void sango_music_shutdown(void);
int sango_music_decode_ima_block(const uint8_t *block, int16_t *output);
int sango_music_sdk_file_open(const char *path);
void sango_music_sdk_file_close(int file);
int sango_music_sdk_file_read(int file, void *buffer, unsigned int bytes);
int sango_music_sdk_file_seek(int file, int offset, int whence);
uint32_t sango_music_sdk_clock(void);
void sango_music_sdk_timer(int active);
void sango_music_sdk_audio_open(void);
int sango_music_sdk_audio_ready(void);
int sango_music_sdk_audio_write(const void *pcm, unsigned int bytes);
void sango_music_sdk_audio_stop(void);
#ifdef SANGO_MUSIC_DIAGNOSTICS
void sango_music_sdk_diagnostic_start(const char *library_path);
#endif
#endif

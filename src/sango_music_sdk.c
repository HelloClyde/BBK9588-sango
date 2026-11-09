#include "bda_sdk.h"
#include "sango_internal.h"

__attribute__((noinline)) int sango_music_sdk_file_open(const char *path)
{
    int file = bda_fs_fopen_raw(path, "rb");
    return bda_fs_file_is_valid(file) ? file : 0;
}
__attribute__((noinline)) void sango_music_sdk_file_close(int file)
{
    (void)bda_fs_close_raw(file);
}
__attribute__((noinline)) int sango_music_sdk_file_read(int file, void *buffer,
                                                        unsigned int bytes)
{
    return bda_fs_read_raw(file, buffer, bytes);
}
__attribute__((noinline)) int sango_music_sdk_file_seek(int file, int offset, int whence)
{
    return bda_fs_seek_raw(file, offset, whence);
}
__attribute__((noinline)) uint32_t sango_music_sdk_clock(void)
{
    return bda_gui_window_timer_clock_ms();
}
__attribute__((noinline)) void sango_music_sdk_timer(int active)
{
    if (active)
        (void)bda_gui_window_timer_start((bda_handle_t)g_app_frame, SANGO_MUSIC_TIMER_ID, 20);
    else
        (void)bda_gui_window_timer_stop((bda_handle_t)g_app_frame, SANGO_MUSIC_TIMER_ID);
}
__attribute__((noinline)) void sango_music_sdk_audio_open(void)
{
    bda_audio_open_pcm(BDA_AUDIO_SAMPLE_RATE_22050, BDA_AUDIO_BITS_16, BDA_AUDIO_CHANNELS_MONO);
}
__attribute__((noinline)) int sango_music_sdk_audio_ready(void) { return bda_audio_ready(); }
__attribute__((noinline)) int sango_music_sdk_audio_write(const void *pcm, unsigned int bytes)
{
    return bda_audio_write(pcm, bytes);
}
__attribute__((noinline)) void sango_music_sdk_audio_stop(void) { bda_audio_stop(); }

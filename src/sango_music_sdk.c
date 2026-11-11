#include "bda_sdk.h"
#include "sango_internal.h"

/* Initialize the playback level explicitly, as in the hardware-verified SDK
 * demo. Own this setting only during our stream and restore it on stop. */
static int previous_attenuation, owns_attenuation;
static int16_t restore_silence[512];

#ifdef SANGO_MUSIC_DIAGNOSTICS
/* D2 profiles in RAM. No filesystem writes occur while audio is playing. */
static struct
{
    unsigned int reads, read_bytes, read_ticks, longest_read;
    unsigned int writes, write_bytes, write_ticks, longest_write;
    unsigned int ready_calls, ready_samples, ready_ticks, longest_ready;
    unsigned int first_tick, attenuation;
} profile;
static const char *profile_path;
static char *profile_output;
static unsigned int profile_output_used;
static void profile_line(const char *label, unsigned int value)
{
    char line[100], digits[10];
    unsigned int used = 0, count = 0;
    int file;
    while (*label && used < 80)
        line[used++] = *label++;
    line[used++] = '=';
    do
    {
        digits[count++] = '0' + value % 10;
        value /= 10;
    } while (value && count < sizeof(digits));
    while (count)
        line[used++] = digits[--count];
    line[used++] = '\r';
    line[used++] = '\n';
    if (profile_output)
    {
        unsigned int i;
        for (i = 0; i < used && profile_output_used < 1024; ++i)
            profile_output[profile_output_used++] = line[i];
        return;
    }
    if (!profile_path)
        return;
    file = bda_fs_fopen_raw(profile_path, "ab");
    if (bda_fs_file_is_valid(file))
    {
        (void)bda_fs_write_raw(file, line, used);
        (void)bda_fs_close_raw(file);
    }
}
void sango_music_sdk_diagnostic_start(const char *library_path)
{
    int file;
    (void)library_path;
    profile_path = "A:\\SANGOMUS.TXT";
    file = bda_fs_fopen_raw(profile_path, "wb");
    if (!bda_fs_file_is_valid(file))
    {
        profile_path = "\\SANGOMUS.TXT";
        file = bda_fs_fopen_raw(profile_path, "wb");
    }
    if (bda_fs_file_is_valid(file))
        (void)bda_fs_close_raw(file);
    else
        profile_path = 0;
    profile_line("SANGO_AUDIO_RAM_PROFILE_D2", 1);
}
#endif

__attribute__((noinline)) int sango_music_sdk_file_open(const char *path)
{
#ifdef SANGO_MUSIC_DIAGNOSTICS
    unsigned int i;
    unsigned int *words = (unsigned int *)&profile;
    for (i = 0; i < sizeof(profile) / sizeof(*words); ++i)
        words[i] = 0;
    profile.first_tick = bda_gui_tick_count_25ms();
#endif
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
#ifdef SANGO_MUSIC_DIAGNOSTICS
    unsigned int start = bda_gui_tick_count_25ms();
#endif
    int result = bda_fs_read_raw(file, buffer, bytes);
#ifdef SANGO_MUSIC_DIAGNOSTICS
    unsigned int elapsed = bda_gui_tick_count_25ms() - start;
    ++profile.reads;
    if (result > 0)
        profile.read_bytes += result;
    profile.read_ticks += elapsed;
    if (elapsed > profile.longest_read)
        profile.longest_read = elapsed;
#endif
    return result;
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
        (void)bda_gui_window_timer_start((bda_handle_t)g_app_frame, SANGO_MUSIC_TIMER_ID,
                                         SANGO_MUSIC_POLL_MS);
    else
        (void)bda_gui_window_timer_stop((bda_handle_t)g_app_frame, SANGO_MUSIC_TIMER_ID);
}
__attribute__((noinline)) void sango_music_sdk_audio_open(void)
{
    previous_attenuation = bda_audio_get_attenuation();
    bda_audio_open_pcm(BDA_AUDIO_SAMPLE_RATE_22050, BDA_AUDIO_BITS_16, BDA_AUDIO_CHANNELS_MONO);
    owns_attenuation = 1;
    sango_music_sdk_audio_volume(sango_music_get_volume());
}
__attribute__((noinline)) void sango_music_sdk_audio_volume(unsigned int level)
{
    if (owns_attenuation)
    {
        if (level > 10)
            level = 10;
        /* SDK attenuation uses multiples of3; level8 retains alpha.7's24. */
        bda_audio_set_attenuation(level <= 8 ? 96 - level * 9 : (10 - level) * 12);
    }
}
__attribute__((noinline)) int sango_music_sdk_audio_ready(void)
{
#ifdef SANGO_MUSIC_DIAGNOSTICS
    unsigned int sampled = (++profile.ready_calls & 15) == 1;
    unsigned int start = sampled ? bda_gui_tick_count_25ms() : 0;
#endif
    int result = bda_audio_ready();
#ifdef SANGO_MUSIC_DIAGNOSTICS
    if (sampled)
    {
        unsigned int elapsed = bda_gui_tick_count_25ms() - start;
        ++profile.ready_samples;
        profile.ready_ticks += elapsed;
        if (elapsed > profile.longest_ready)
            profile.longest_ready = elapsed;
    }
#endif
    return result;
}
__attribute__((noinline)) int sango_music_sdk_audio_write(const void *pcm, unsigned int bytes)
{
#ifdef SANGO_MUSIC_DIAGNOSTICS
    unsigned int start = bda_gui_tick_count_25ms();
#endif
    int result = bda_audio_write(pcm, bytes);
#ifdef SANGO_MUSIC_DIAGNOSTICS
    unsigned int elapsed = bda_gui_tick_count_25ms() - start;
    ++profile.writes;
    if (result > 0)
        profile.write_bytes += result;
    profile.write_ticks += elapsed;
    if (elapsed > profile.longest_write)
        profile.longest_write = elapsed;
    if (profile.writes == 1)
        profile.attenuation = bda_audio_get_attenuation();
#endif
    return result;
}
__attribute__((noinline)) void sango_music_sdk_audio_stop(void)
{
    if (owns_attenuation)
    {
        unsigned int started = bda_gui_tick_count_25ms(), attempts = 0;
        while (!bda_audio_ready() && attempts++ < 100000 &&
               bda_gui_tick_elapsed_25ms(started, bda_gui_tick_count_25ms()) < 10)
            bda_sys_delay(1);
        bda_audio_set_attenuation(previous_attenuation);
        if (bda_audio_ready())
            (void)bda_audio_write(restore_silence, sizeof(restore_silence));
        owns_attenuation = 0;
    }
    bda_audio_stop();
#ifdef SANGO_MUSIC_DIAGNOSTICS
    char summary[1024];
    int file;
    profile_output = summary;
    profile_output_used = 0;
    profile_line("D2_STREAM_END", 1);
    profile_line("ELAPSED_RAW_TICKS", bda_gui_tick_count_25ms() - profile.first_tick);
    profile_line("READ_CALLS", profile.reads);
    profile_line("READ_BYTES", profile.read_bytes);
    profile_line("READ_TOTAL_RAW_TICKS", profile.read_ticks);
    profile_line("READ_MAX_RAW_TICKS", profile.longest_read);
    profile_line("WRITE_CALLS", profile.writes);
    profile_line("WRITE_BYTES", profile.write_bytes);
    profile_line("WRITE_TOTAL_RAW_TICKS", profile.write_ticks);
    profile_line("WRITE_MAX_RAW_TICKS", profile.longest_write);
    profile_line("READY_CALLS", profile.ready_calls);
    profile_line("READY_SAMPLED_CALLS", profile.ready_samples);
    profile_line("READY_SAMPLED_RAW_TICKS", profile.ready_ticks);
    profile_line("READY_MAX_RAW_TICKS", profile.longest_ready);
    profile_line("APPLIED_ATTENUATION", profile.attenuation);
    profile_line("RESTORED_ATTENUATION", bda_audio_get_attenuation());
    profile_output = 0;
    file = profile_path ? bda_fs_fopen_raw(profile_path, "ab") : 0;
    if (bda_fs_file_is_valid(file))
    {
        (void)bda_fs_write_raw(file, summary, profile_output_used);
        (void)bda_fs_close_raw(file);
    }
    bda_fs_flush_all();
#endif
}

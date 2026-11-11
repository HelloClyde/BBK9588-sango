#include "bda_filesystem.h"
#include "sango_internal.h"

/* One file and fixed streaming buffers outside the original save region.
 * Read sixteen ADPCM blocks together; submit at most one PCM buffer per poll. */
static struct
{
    unsigned int wanted, scene, busy, streaming, timer;
    int file;
    uint32_t data_offset, data_bytes, data_left, total_samples, samples_left;
    unsigned int decoded_position, pending_bytes, written_bytes;
    char directory[224];
    unsigned int encoded_position, encoded_bytes;
    uint8_t encoded[16 * SANGO_MUSIC_BLOCK_BYTES];
    int16_t decoded[SANGO_MUSIC_BLOCK_SAMPLES];
    int16_t pending[512];
} music;

static unsigned int read16(const uint8_t *p) { return p[0] | (unsigned int)p[1] << 8; }
static uint32_t read32(const uint8_t *p) { return read16(p) | (uint32_t)read16(p + 2) << 16; }

int sango_music_decode_ima_block(const uint8_t *block, int16_t *output)
{
    static const int16_t steps[89] = {
        7,     8,     9,     10,    11,    12,    13,    14,    16,    17,    19,    21,
        23,    25,    28,    31,    34,    37,    41,    45,    50,    55,    60,    66,
        73,    80,    88,    97,    107,   118,   130,   143,   157,   173,   190,   209,
        230,   253,   279,   307,   337,   371,   408,   449,   494,   544,   598,   658,
        724,   796,   876,   963,   1060,  1166,  1282,  1411,  1552,  1707,  1878,  2066,
        2272,  2499,  2749,  3024,  3327,  3660,  4026,  4428,  4871,  5358,  5894,  6484,
        7132,  7845,  8630,  9493,  10442, 11487, 12635, 13899, 15289, 16818, 18500, 20350,
        22385, 24623, 27086, 29794, 32767};
    static const int8_t changes[8] = {-1, -1, -1, -1, 2, 4, 6, 8};
    int predictor = (int16_t)read16(block), index = block[2];
    unsigned int nibble;
    if (index > 88 || block[3])
        return 0;
    output[0] = (int16_t)predictor;
    for (nibble = 0; nibble < 504; ++nibble)
    {
        unsigned int code = (block[4 + nibble / 2] >> ((nibble & 1) * 4)) & 15;
        /* Keep IMA-WAV multiplication rounding, including low step values. */
        int difference = ((2 * (code & 7) + 1) * steps[index]) >> 3;
        predictor += (code & 8) ? -difference : difference;
        if (predictor > 32767)
            predictor = 32767;
        if (predictor < -32768)
            predictor = -32768;
        index += changes[code & 7];
        if (index < 0)
            index = 0;
        if (index > 88)
            index = 88;
        output[nibble + 1] = (int16_t)predictor;
    }
    return SANGO_MUSIC_BLOCK_SAMPLES;
}

static int read_exact(void *buffer, unsigned int bytes)
{
    unsigned int done = 0;
    while (done < bytes)
    {
        int got = sango_music_sdk_file_read(music.file, (uint8_t *)buffer + done, bytes - done);
        if (got <= 0 || (unsigned int)got > bytes - done)
            return 0;
        done += (unsigned int)got;
    }
    return 1;
}

static void close_stream(void)
{
    if (music.timer)
    {
        sango_music_sdk_timer(0);
        music.timer = 0;
    }
    if (music.streaming)
    {
        sango_music_sdk_audio_stop();
        music.streaming = 0;
    }
    if (music.file)
    {
        sango_music_sdk_file_close(music.file);
        music.file = 0;
    }
    music.pending_bytes = music.written_bytes = 0;
}

static int rewind_stream(void)
{
    if (sango_music_sdk_file_seek(music.file, (int)music.data_offset, BDA_SEEK_SET) !=
        (int)music.data_offset)
        return 0;
    music.data_left = music.data_bytes;
    music.samples_left = music.total_samples;
    music.decoded_position = SANGO_MUSIC_BLOCK_SAMPLES;
    music.encoded_position = music.encoded_bytes = 0;
    return 1;
}

static int read_header(void)
{
    uint8_t header[20];
    int file_size = sango_music_sdk_file_seek(music.file, 0, BDA_SEEK_END);
    uint32_t position = 12, chunk, size;
    unsigned int found = 0, attempts = 0;
    if (file_size < 60 || file_size > 32 * 1024 * 1024 ||
        sango_music_sdk_file_seek(music.file, 0, BDA_SEEK_SET) != 0 || !read_exact(header, 12))
        return 0;
    if (read32(header) != 0x46464952u || read32(header + 8) != 0x45564157u ||
        read32(header + 4) != (uint32_t)file_size - 8)
        return 0;
    while (position + 8 <= (uint32_t)file_size && ++attempts <= 64)
    {
        if (sango_music_sdk_file_seek(music.file, (int)position, BDA_SEEK_SET) !=
                (int)position ||
            !read_exact(header, 8))
            return 0;
        chunk = read32(header);
        size = read32(header + 4);
        position += 8;
        if (size > (uint32_t)file_size - position)
            return 0;
        if (chunk == 0x20746d66u)
        {
            if (found & 1 || size < 20 || !read_exact(header, 20))
                return 0;
            if (read16(header) != 17 || read16(header + 2) != 1 ||
                read32(header + 4) != 22050 || read16(header + 12) != 256 ||
                read16(header + 14) != 4 || read16(header + 16) != 2 ||
                read16(header + 18) != 505)
                return 0;
            found |= 1;
        }
        else if (chunk == 0x74636166u)
        {
            if (found & 2 || size < 4 || !read_exact(header, 4))
                return 0;
            music.total_samples = read32(header);
            found |= 2;
        }
        else if (chunk == 0x61746164u)
        {
            if (found & 4 || !size || size % 256)
                return 0;
            music.data_offset = position;
            music.data_bytes = size;
            found |= 4;
        }
        position += size + (size & 1);
    }
    if (found != 7 || position != (uint32_t)file_size ||
        music.total_samples > music.data_bytes / 256 * 505 ||
        music.total_samples <= (music.data_bytes / 256 - 1) * 505)
        return 0;
    return rewind_stream();
}

static int open_scene(unsigned int scene)
{
    static const char *names[] = {"", "menu.wav", "strategy.wav", "battle.wav"};
    char path[256];
    unsigned int used = 0, i = 0;
    while (music.directory[used])
    {
        path[used] = music.directory[used];
        ++used;
    }
    do
    {
        path[used++] = names[scene][i];
    } while (names[scene][i++]);
    music.file = sango_music_sdk_file_open(path);
    if (!music.file || !read_header())
    {
        close_stream();
        return 0;
    }
    sango_music_sdk_audio_open();
    music.streaming = 1;
    sango_music_sdk_timer(1);
    music.timer = 1;
    return 1;
}

static int prepare_pcm(void)
{
    unsigned int used = 0;
    while (used < 512)
    {
        unsigned int count, i;
        if (!music.samples_left && !rewind_stream())
            return 0;
        if (music.decoded_position == SANGO_MUSIC_BLOCK_SAMPLES)
        {
            if (music.encoded_position == music.encoded_bytes)
            {
                unsigned int bytes = music.data_left;
                if (bytes > sizeof(music.encoded))
                    bytes = sizeof(music.encoded);
                if (bytes < SANGO_MUSIC_BLOCK_BYTES || !read_exact(music.encoded, bytes))
                    return 0;
                music.data_left -= bytes;
                music.encoded_position = 0;
                music.encoded_bytes = bytes;
            }
            if (!sango_music_decode_ima_block(music.encoded + music.encoded_position,
                                              music.decoded))
                return 0;
            music.encoded_position += SANGO_MUSIC_BLOCK_BYTES;
            music.decoded_position = 0;
        }
        count = 505 - music.decoded_position;
        if (count > 512 - used)
            count = 512 - used;
        if (count > music.samples_left)
            count = music.samples_left;
        for (i = 0; i < count; ++i)
            music.pending[used + i] = music.decoded[music.decoded_position + i];
        music.samples_left -= count;
        music.decoded_position += count;
        used += count;
    }
    music.pending_bytes = 1024;
    music.written_bytes = 0;
    return 1;
}

void sango_music_poll(void)
{
    unsigned int writes;
    if (music.busy || !music.wanted || !music.directory[0] || !g_app_frame)
        return;
    /* The GUI timer clock can lag while the device is drawing. The firmware
     * audio queue supplies pacing even when that GUI clock does not advance. */
    music.busy = 1;
    if (music.wanted != music.scene)
    {
        close_stream();
        music.scene = music.wanted;
        (void)open_scene(music.scene);
    }
    /* Firmware writes may yield to DMA. One1024-byte write per poll avoids
     * monopolizing the game thread; short writes retain pending samples. */
    for (writes = 0; music.streaming && music.wanted == music.scene && writes < 1; ++writes)
    {
        unsigned int remaining;
        int written;
        if (!sango_music_sdk_audio_ready())
            break;
        if (music.written_bytes == music.pending_bytes && !prepare_pcm())
        {
            close_stream();
            break;
        }
        remaining = music.pending_bytes - music.written_bytes;
        written = sango_music_sdk_audio_write((uint8_t *)music.pending + music.written_bytes,
                                              remaining);
        if (written < 0 || (unsigned int)written > remaining || (written & 1))
        {
            close_stream();
            break;
        }
        if (!written)
            break;
        music.written_bytes += (unsigned int)written;
    }
    if (!music.wanted)
    {
        close_stream();
        music.scene = 0;
    }
    music.busy = 0;
}

void sango_music_shutdown(void)
{
    music.wanted = 0;
    if (!music.busy)
    {
        close_stream();
        music.scene = 0;
    }
}

void sango_music_set_scene(unsigned int scene)
{
    if (scene > SANGO_MUSIC_BATTLE)
        return;
    if (!scene)
    {
        sango_music_shutdown();
        return;
    }
    music.wanted = scene;
    sango_music_poll();
}

void sango_music_set_library_path(const char *library_path)
{
    unsigned int i = 0, last = 0;
    sango_music_shutdown();
    music.directory[0] = 0;
#ifdef SANGO_MUSIC_DIAGNOSTICS
    sango_music_sdk_diagnostic_start(library_path);
#endif
    while (library_path[i])
    {
        if (i >= 200)
            return;
        if (library_path[i] == '\\' || library_path[i] == '/')
            last = i + 1;
        ++i;
    }
    for (i = 0; i < last; ++i)
        music.directory[i] = library_path[i];
    {
        const char *folder = "sango-music\\";
        unsigned int j = 0;
        do
        {
            music.directory[last + j] = folder[j];
        } while (folder[j++]);
    }
}

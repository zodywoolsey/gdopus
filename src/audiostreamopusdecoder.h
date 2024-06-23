#ifndef GDOPUSDECODER_H
#define GDOPUSDECODER_H

#include <godot_cpp/classes/audio_stream_generator.hpp>
#include <godot_cpp/classes/audio_stream_generator_playback.hpp>
#include <opus/include/opus.h>

namespace godot {

class AudioStreamOpusDecoder : public AudioStreamGenerator {
    GDCLASS(AudioStreamOpusDecoder, AudioStreamGenerator)

private:
    double time_passed;

protected:
    static void _bind_methods();

public:
    AudioStreamOpusDecoder();
    ~AudioStreamOpusDecoder();
    OpusDecoder* decoder;
    PackedVector2Array gdopus_decode(PackedByteArray in_buffer, int in_encoded_bytes);
    void fast_push_buffer(PackedVector2Array in_buffer, AudioStreamGeneratorPlayback* playback);
    float* output;
    void _process(double delta);
    void _ready();
};

}

#endif
#ifndef GDOPUSENCODER_H
#define GDOPUSENCODER_H

#include <godot_cpp/classes/audio_effect_capture.hpp>
#include <opus/include/opus.h>
#include "opus/include/opus_defines.h"

namespace godot {

class GDOpusEncoder : public AudioEffectCapture {
    GDCLASS(GDOpusEncoder, AudioEffectCapture)

private:
    double time_passed;

protected:
    static void _bind_methods();

public:
    GDOpusEncoder();
    ~GDOpusEncoder();
    void gdopus_set_bitrate(int bitrate);
    void gdopus_set_forward_error_correction(bool enabled);
    Dictionary gdopus_encode();
	OpusEncoder* encoder;
    unsigned char* output;
    void _process(double delta);
    void _ready();
};

}

#endif
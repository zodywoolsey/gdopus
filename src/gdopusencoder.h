#ifndef GDOPUSENCODER_H
#define GDOPUSENCODER_H
#define SUNVOX_MAIN

#include <godot_cpp/classes/audio_effect_capture.hpp>
#include "opus-1.4/include/opus.h"

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
    Dictionary gdopus_encode();
    unsigned char* output;
    void _process(double delta);
    void _ready();
};

}

#endif
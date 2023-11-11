#include "gdopusencoder.h"
#include <godot_cpp/core/class_db.hpp>
#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include "opus-1.4/include/opus.h"

using namespace godot;

#define MAX_PACKET 2000
#define FRAME_SIZE 960

void GDOpusEncoder::_bind_methods() {
	// register static method "test"
	ClassDB::bind_method(D_METHOD("gdopus_encode"), &GDOpusEncoder::gdopus_encode);
}

GDOpusEncoder::GDOpusEncoder() {
    // Initialize any variables here.
	output = new unsigned char[MAX_PACKET];
}

GDOpusEncoder::~GDOpusEncoder() {
    // Add your cleanup here.
	delete output;
}

void GDOpusEncoder::_ready() {
	
}

Dictionary GDOpusEncoder::gdopus_encode(){
	PackedVector2Array tmp = get_buffer(FRAME_SIZE);
	float* interleaved = new float[tmp.size() * 2];
	// flatten PackedVector2Array tmp to interleaved float*
	for (int i = 0; i < tmp.size(); i++) {
		interleaved[i * 2] = tmp[i].x;
		interleaved[i * 2 + 1] = tmp[i].y;
	}
	// instantiate encoder
	int err;
	OpusEncoder* encoder = opus_encoder_create(48000, 2, OPUS_APPLICATION_VOIP, &err);
	// encode
	opus_int32 encoded_bytes = opus_encode_float(encoder, interleaved, FRAME_SIZE, output, MAX_PACKET);
	delete interleaved;
	// create a new PackedByteArray and resize it to the size of the output buffer
	PackedByteArray packed_output;
	packed_output.resize(encoded_bytes);

	// copy the contents of output_copy to the PackedByteArray
	for (int i = 0; i < encoded_bytes; i++) {
		packed_output.set(i, output[i]);
	}
	Dictionary dict;
	dict["encoded_bytes"] = encoded_bytes;
	dict["output"] = packed_output;
	// print size of output
	// printf("size of encoded: %d\n", packed_output.size());
	return dict;
}

void GDOpusEncoder::_process(double delta) {
}
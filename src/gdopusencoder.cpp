#include "gdopusencoder.h"
#include <godot_cpp/core/class_db.hpp>
// #include <opus/include/opus.h>

using namespace godot;

#define MAX_PACKET 2000
#define FRAME_SIZE 960

void GDOpusEncoder::_bind_methods() {
	// register static method "test"
	ClassDB::bind_method(D_METHOD("gdopus_encode"), &GDOpusEncoder::gdopus_encode);
	ClassDB::bind_method(D_METHOD("gdopus_set_bitrate"), &GDOpusEncoder::gdopus_set_bitrate);
	ClassDB::bind_method(D_METHOD("gdopus_set_forward_error_correction"), &GDOpusEncoder::gdopus_set_forward_error_correction);
	ClassDB::bind_method(D_METHOD("encode_buffer"), &GDOpusEncoder::encode_buffer);
}

GDOpusEncoder::GDOpusEncoder() {
    // Initialize any variables here.
	output = new unsigned char[MAX_PACKET];
	int err;
	encoder = opus_encoder_create(48000, 2, OPUS_APPLICATION_VOIP, &err);
	// opus_encoder_ctl(encoder, OPUS_SET_INBAND_FEC(1));
	// opus_encoder_ctl(encoder, OPUS_SET_PACKET_LOSS_PERC(100));
}

GDOpusEncoder::~GDOpusEncoder() {
    // Add your cleanup here.
	opus_encoder_destroy(encoder);
	delete output;
}

void GDOpusEncoder::_ready() {
	
}

void GDOpusEncoder::gdopus_set_forward_error_correction(bool enabled){
	if(enabled == true){
		opus_encoder_ctl(encoder, OPUS_SET_INBAND_FEC(1));
	}else{
		opus_encoder_ctl(encoder, OPUS_SET_INBAND_FEC(0));
	}
}

void GDOpusEncoder::gdopus_set_bitrate(int bitrate){
	opus_encoder_ctl(encoder, OPUS_SET_BITRATE(bitrate));
}

Dictionary GDOpusEncoder::encode_buffer(PackedFloat32Array in_buffer, int max_packet_size_b){
  float* casted_in_buffer = new float[in_buffer.size()];
  for (int i = 0; i < in_buffer.size(); i++){
    casted_in_buffer[i] = in_buffer[i];
  }
  int err;
  unsigned char* tmp_out = new unsigned char[max_packet_size_b];
  opus_int32 encoded_bytes = opus_encode_float(encoder, casted_in_buffer, in_buffer.size()/2, tmp_out, max_packet_size_b);
  PackedByteArray packed_output;
  packed_output.resize(encoded_bytes);
  
  for (int i = 0; i < encoded_bytes; i++){
    packed_output[i] = tmp_out[i];
  }
  Dictionary dict;
  dict["encoded_bytes"] = encoded_bytes;
  dict["output"] = packed_output;
  return dict;
}

Dictionary GDOpusEncoder::gdopus_encode(){
	// if(get_buffer_length_frames)
	PackedVector2Array tmp = get_buffer(FRAME_SIZE);
	float* interleaved = new float[tmp.size() * 2];
	// flatten PackedVector2Array tmp to interleaved float*
	for (int i = 0; i < tmp.size(); i++) {
		interleaved[i * 2] = tmp[i].x;
		interleaved[i * 2 + 1] = tmp[i].y;
	}
	// instantiate encoder
	int err;
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

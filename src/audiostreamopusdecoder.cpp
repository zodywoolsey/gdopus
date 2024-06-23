#include "audiostreamopusdecoder.h"
#include <godot_cpp/core/class_db.hpp>
// #include <opus/include/opus.h>

using namespace godot;

#define MAX_PACKET 2000
#define FRAME_SIZE 960

// audio stream

/**
 * @brief Binds the methods of the AudioStreamOpusDecoder class to Godot's scripting language.
 */
void AudioStreamOpusDecoder::_bind_methods() {
	// register static method "test"
	ClassDB::bind_method(D_METHOD("gdopus_decode"), &AudioStreamOpusDecoder::gdopus_decode);
	ClassDB::bind_method(D_METHOD("fast_push_buffer"), &AudioStreamOpusDecoder::fast_push_buffer);
}

/**
 * Constructor for AudioStreamOpusDecoder class.
 * Initializes the output buffer with a maximum packet size.
 */
AudioStreamOpusDecoder::AudioStreamOpusDecoder() {
    // Initialize any variables here.
	output = new float[MAX_PACKET];
	int err;
	decoder = opus_decoder_create(48000, 2, &err);
}

/**
 * @brief Destructor for AudioStreamOpusDecoder class.
 * 
 * This function is responsible for cleaning up the memory allocated for the output buffer.
 * 
 */
AudioStreamOpusDecoder::~AudioStreamOpusDecoder() {
    // Add your cleanup here.
	delete output;
	opus_decoder_destroy(decoder);
}

void AudioStreamOpusDecoder::_ready() {
	
}

/**
 * Decodes an Opus-encoded audio stream from the given input buffer and returns the decoded audio as a PackedVector2Array.
 * 
 * @param in_buffer The input buffer containing the Opus-encoded audio data.
 * @param in_encoded_bytes The number of bytes in the input buffer.
 * @return The decoded audio as a PackedVector2Array.
 */
PackedVector2Array AudioStreamOpusDecoder::gdopus_decode(PackedByteArray in_buffer, int in_encoded_bytes){
	// make sure the input buffer is exactly double the FRAME_SIZE
	// if (in_buffer.size() != FRAME_SIZE) {
	// 	return PackedVector2Array();
	// }
	//convert in_buffer to an unsigned char*
	unsigned char* in_buffer_copy = new unsigned char[in_buffer.size()];
	for (int i = 0; i < in_buffer.size(); i++) {
		in_buffer_copy[i] = in_buffer[i];
	}
	
	
	// encode
	opus_int32 decoded_samples = opus_decode_float(decoder, in_buffer_copy, in_encoded_bytes, output, FRAME_SIZE, 0);
	delete in_buffer_copy;
	// create a new PackedVector2Array and resize it to the size of the output buffer
	PackedVector2Array packed_output = PackedVector2Array();
	
	// printf("output size: %d\n", sizeof(output));
	
	packed_output.resize(decoded_samples);
	// print packed_output size
	// unflatten the output buffer into the PackedVector2Array
	for (int i = 0; i < decoded_samples; i++) {
		packed_output[i] = Vector2(output[i*2],output[(i*2)+1]);
	}
	// print size of packed_output
	// printf("size of decoded: %d\n", packed_output.size());
	return packed_output;
}

/**
 * This function pushes an audio buffer to the playback stream. If the available frames in the playback stream are less than the size of the input buffer, the buffer is resized to match the available frames. If the playback stream can push the buffer, it is pushed to the stream. If the playback stream is not playing, it is started. If the playback stream cannot push the buffer, the buffer is not pushed to the stream.
 * @param in_buffer The input buffer to be pushed to the playback stream.
 * @param playback The AudioStreamGeneratorPlayback object representing the playback stream.
 */
void AudioStreamOpusDecoder::fast_push_buffer(PackedVector2Array in_buffer, AudioStreamGeneratorPlayback* playback){
	// print available frames
	if(playback->get_frames_available() < in_buffer.size()){
		in_buffer.resize(playback->get_frames_available());
		if(playback->can_push_buffer(in_buffer.size())){
			playback->push_buffer(in_buffer);
		}
		// printf("available frames: %d\n", playback->get_frames_available());
		// printf("buffer size: %d\n", in_buffer.size());
		if(!playback->_is_playing()){
			playback->_start(0);
		}
		return;
	}
	// push the buffer
	if(playback->can_push_buffer(FRAME_SIZE)){
		playback->push_buffer(in_buffer);
		if(!playback->_is_playing()){
			playback->_start(0);
		}
		return;
	}
}

void AudioStreamOpusDecoder::_process(double delta) {
}

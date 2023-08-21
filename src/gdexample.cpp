#include "gdexample.h"
#include <godot_cpp/core/class_db.hpp>
#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include "sunvox_lib-2.1c/sunvox_lib/headers/sunvox.h"

using namespace godot;

int getOutput(int16_t* buf, int size){
	int output = sv_audio_callback(buf, size, 0, sv_get_ticks());
	return output;
}

void printBuffer(int16_t* buf, int size){
	for(int i = 0; i < size; i++){
		std::cout << buf[i];
		std::cout << "\n";
	}
		std::cout << "\n";
}
void GDExample::_bind_methods() {
}

GDExample::GDExample() {
    // Initialize any variables here.
    time_passed = 0.0;
}

GDExample::~GDExample() {
    // Add your cleanup here.
}

void GDExample::_ready() {
	using namespace std::this_thread;
	using namespace std::chrono;
	if(sv_load_dll()) return;
	std::cout<<"Load sunvox dll\n";
	int flags = SV_INIT_FLAG_AUDIO_INT16 | SV_INIT_FLAG_USER_AUDIO_CALLBACK;
	int ver = sv_init("",44100,2,0);
	if(ver>=0)
	{
		sv_open_slot(0);
		std::cout << "Opened a slot, ready to load a file/n";
		sv_load(0, "C:/Users/zodie/Documents/github/gdextensiontest/gdextensiontest/bin/worst.sunvox");
		sv_volume(0, 30);
		sv_play(0);
		int16_t* buf = new int16_t [512];
		// for(int i = 0; i < 10000; i++){
		// 	buf = new int16_t [512];
		// 	getOutput(buf, 512);
		// }
		// printBuffer(buf, 512);
		sleep_for(seconds(2));
		sv_close_slot(0);
		sv_deinit();
		// std::cout << "Closed slot and deinitialized\n";
	}
	sv_unload_dll();
}

void GDExample::_process(double delta) {
}
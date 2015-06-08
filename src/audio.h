//audio.h
//reads in and stores audio files in memory

#ifndef AUDIO_H
#define AUDIO_H

#include <fstream>
#include <stdint.h>
#include <map>
#include <AL/al.h>
#include <AL/alc.h>

#define FREQUENCY 44100
#define FORMAT AL_FORMAT_STEREO16

#include <iostream>

class Audio {
	private:
		void initListener();

		std::map<std::string, char*> audio;
		std::map<std::string, ALuint> sources;
		ALCdevice* device;
		ALCcontext* context;
	public:
		Audio();
		~Audio();
		void addAudio(std::string name, std::string sourceName, const char* path);
		void addSource(float x, float y, std::string name);
		void playSource(std::string name);
};

#endif

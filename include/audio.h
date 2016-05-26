//audio.h
//reads in and stores audio files in memory

#ifndef AUDIO_H
#define AUDIO_H

#define FREQUENCY 44100
#define FORMAT AL_FORMAT_STEREO16

#include <fstream>
#include <stdint.h>
#include <map>
#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>

class Audio {
	private:
		static void initListener();

		static std::map<std::string, char*> audio;
		static std::map<std::string, ALuint> sources;
		static ALCdevice* device;
		static ALCcontext* context;

		static class InitAudio {
			public:
				InitAudio();
				~InitAudio();
		} init;
	public:
		static void addAudio(std::string name, std::string sourceName, const char* path);
		static void addSource(float x, float y, std::string name);
		static void playSource(std::string name);
};

#endif

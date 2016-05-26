#include "audio.h"

std::map<std::string, char*> Audio::audio;
std::map<std::string, ALuint> Audio::sources;
ALCdevice* Audio::device;
ALCcontext* Audio::context;
Audio::InitAudio Audio::init;

Audio::InitAudio::InitAudio() {
	device = alcOpenDevice(NULL);

	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);

	initListener();
}

Audio::InitAudio::~InitAudio() {
	//deallocate all of the char pointers
	for (std::map<std::string, char*>::iterator it = audio.begin(); it != audio.end(); it++)
		free(it->second);

	//deallocate all of the sources
	for (std::map<std::string, ALuint>::iterator it = sources.begin(); it != sources.end(); it++)
		alDeleteSources(1, &it->second);

	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

void Audio::initListener() {
	alListener3f(AL_POSITION, 0, 0, 0);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListener3f(AL_ORIENTATION, 0, 0, -1);
}

void Audio::addAudio(std::string name, std::string sourceName, const char* path) {
	std::ifstream fin (path+name, std::ifstream::in|std::ifstream::binary);

	char in[4];

	//find the data section
	//need to check by 2s, but should be alright because we're reading header
	do {
		fin.seekg(0, std::ifstream::cur);
		fin.read(in, 2);
	} while (in[0] != 'd' || in[1] != 'a');
	//skip the "ta"
	fin.seekg(2, std::ifstream::cur);
	fin.read(in, 4);

	uint32_t size = 0;

	for (int i = 0; i < 4; i++)
		size += in[i] << i*8;

	audio[name] = (char*) malloc(size);
	fin.read(audio[name], size);

	fin.close();

	ALuint buffer;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, FORMAT, audio[name], size, FREQUENCY);

	alSourcei(sources[sourceName], AL_BUFFER, buffer);
}

void Audio::addSource(float x, float y, std::string name) {
	ALuint buffer;
	alGenSources(1, &buffer);

	sources[name] = buffer;

	alSourcef(sources[name], AL_PITCH, 1);
	alSourcef(sources[name], AL_GAIN, 1);
	alSource3f(sources[name], AL_POSITION, x, y, 0);
	alSource3f(sources[name], AL_VELOCITY, 0, 0, 0);
	alSourcei(sources[name], AL_LOOPING, AL_FALSE);
}

void Audio::playSource(std::string name) {
	alSourcePlay(sources[name]);
}

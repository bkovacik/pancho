#include "../include/keytranslate.h"
#include <fstream>

KeyTranslate::KeyTranslate(std::string name) {
	std::ifstream fin (name.c_str(), std::ifstream::in);
	if (!fin) {
		fprintf(stderr, "Keytranslate file not found.\n");
		exit(-1);
	}
	while (fin.good()) {
		std::string mkey, mvalue;

		getline(fin, mkey, ',');
		if (!mkey.length() || mkey[0] < '0' || mkey[0] > '9')
			break;
		getline(fin, mvalue);

		tmap[std::stoi(mkey)] = key(std::stoi(mvalue));
	}
/*
	tmap[GLFW_KEY_RIGHT] = KEY_RIGHT;
	tmap[GLFW_KEY_LEFT] = KEY_LEFT;
	tmap[GLFW_KEY_DOWN] = KEY_DOWN;
	tmap[GLFW_KEY_UP] = KEY_UP;
	tmap[GLFW_KEY_C] = KEY_C;
	tmap[GLFW_KEY_Z] = KEY_Z;
	tmap[GLFW_KEY_X] = KEY_X;*/
}

key KeyTranslate::getKey(int key_p) {
	return tmap[key_p];
}

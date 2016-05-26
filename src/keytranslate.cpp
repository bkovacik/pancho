#include "../include/keytranslate.h"

KeyTranslate::KeyTranslate() {
	tmap[GLFW_KEY_RIGHT] = KEY_RIGHT;
	tmap[GLFW_KEY_LEFT] = KEY_LEFT;
	tmap[GLFW_KEY_DOWN] = KEY_DOWN;
	tmap[GLFW_KEY_UP] = KEY_UP;
	tmap[GLFW_KEY_C] = KEY_C;
	tmap[GLFW_KEY_Z] = KEY_Z;
	tmap[GLFW_KEY_X] = KEY_X;
}

key KeyTranslate::getKey(int key_p) {
	return tmap[key_p];
}

//keytranslate.h
//translates GLFW keybindings into messages

#ifndef KEYTRANSLATE_H
#define KEYTRANSLATE_H

#include <GLFW/glfw3.h>
#include <map>

enum key {KEY_OTHER, KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP, KEY_C, KEY_Z, KEY_X};

class KeyTranslate {
	std::map<int, key> tmap;
	public:
		KeyTranslate(std::string name);
		key getKey(int key_p);
};

#endif

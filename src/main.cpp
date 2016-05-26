#include <iostream>
#include <fstream>
#include "../include/render.h"
#include "../include/window.h"
#include "../include/image.h"
#include "../include/atlas.h"
#include "../include/level.h"
#include "../include/audio.h"
#include "../include/keytranslate.h"

Render* render; //needs to be global because GLFW is pure C
Level* level;
KeyTranslate * keytranslate;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(int argv, char** argc) {
	Image image = Image("resources/atlas.png");
	Audio::addSource(0, 0, "name");
	Audio::addAudio("power_down_chime.wav", "name", "resources/sounds/");
	Audio::playSource("name");
	keytranslate = new KeyTranslate();

	if (!Window::getWindow())
		return -1;
	else {
		glfwMakeContextCurrent(Window::getWindow());
		glfwSetKeyCallback(Window::getWindow(), key_callback);

		//bottom left = (0, 0)
		render = new Render(194, 130, image.getImage_data());

		Window::setWidth(640);
		Window::setHeight(480);

		if (argv < 2) {
			fprintf(stderr, "Needs at least 1 arg to run.");
			return -1;
		}
		
		std::string lname = "resources/";
		lname += argc[1];

		level = new Level(lname);

		render->render(60, *level);
	}	

	delete(render);
	delete(level);
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	level->onKey(keytranslate->getKey(key), action);
}

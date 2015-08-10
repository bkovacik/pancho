#include <iostream>
#include "render.h"
#include "window.h"
#include "image.h"
#include "atlas.h"
#include "level.h"
#include "audio.h"

Render * render; //needs to be global because GLFW is pure C
Audio * audio;
Level * level;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(int argv, char** argc) {
	Image image = Image("resources/atlas.png");
	audio = new Audio();
	audio->addSource(0, 0, "name");
	audio->addAudio("power_down_chime.wav", "name", "resources/sounds/");

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
			printf("Needs at least 1 arg to run.");
			return -1;
		}
		std::string lname = "resources/";
		lname += argc[1];
		level = new Level(lname.c_str());

		render->render(60, *level);
	}	

	delete(render);
	delete(audio);
	delete(level);
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	level->onKey(key, action);
}

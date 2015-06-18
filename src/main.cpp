#include <iostream>
#include "render.h"
#include "window.h"
#include "image.h"
#include "atlas.h"
#include "level.h"
#include "audio.h"

Render * render; //needs to be global because GLFW is pure C
Audio * audio;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
	Image image = Image("resources/atlas.png");
	Atlas atlas = Atlas("resources/atlasMap.csv");
	Level level = Level("resources/test_level.csv");
	audio = new Audio();
	audio->addSource(0, 0, "name");
	audio->addAudio("power_down_chime.wav", "name", "resources/sounds/");

	GLFWwindow* window = createWindow(640, 480, WINDOWED);
	if (!window)
		return -1;
	else {
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);

		render = new Render(194, 130, image.getImage_data(), window);

		level.load(render, atlas);
		
		for (int i = -128; i < 640; i+=128) {
			for (int j = -128; j < 480; j+=128)
				render->addImage(i, j, atlas.getCoords("background"));
		}

		//bottom left = (0, 0)

	delete(render);
	delete(audio);
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	int x = 0, y = 0, move = 180.0;

	if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
		audio->playSource("name");
		x += move;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT))
		x -= move;
	if (glfwGetKey(window, GLFW_KEY_UP))
		y += move;
	if (glfwGetKey(window, GLFW_KEY_DOWN))
		y -= move;

	for (int i = 0; i < 30; i++)
		render->setMovement(-x, -y, i*2);
}

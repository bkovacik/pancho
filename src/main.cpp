#include <iostream>
#include "render.h"
#include "window.h"
#include "image.h"
#include "atlas.h"

Render * render; //needs to be global because GLFW is pure C
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
	Image image = Image("resources/atlas.png");
	Atlas atlas = Atlas("resources/atlasMap.csv");

	GLFWwindow* window = createWindow(640, 480, WINDOWED);
	if (!window)
		return -1;
	else {
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);

		render = new Render(64, 32, image.getImage_data(), window);

		//bottom left = (0, 0)
		render->addImage(40, 2, atlas.getCoords("test"));
		render->addImage(300, 93, atlas.getCoords("test3"));
		render->render(60);
		
	}

	delete(render);
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	int x = 0, y = 0, move = 180.0;

	if (glfwGetKey(window, GLFW_KEY_RIGHT))
		x += move;
	if (glfwGetKey(window, GLFW_KEY_LEFT))
		x -= move;
	if (glfwGetKey(window, GLFW_KEY_UP))
		y += move;
	if (glfwGetKey(window, GLFW_KEY_DOWN))
		y -= move;

	render->setMovement(x, y, 2);
}

#include "window.h"

GLFWwindow* createWindow(int width, int height, wType type) {
	GLFWwindow* window;

	if (!glfwInit())
		return NULL;

	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	switch(type) {
		case WINDOWED:
			window = glfwCreateWindow(width, height, "Pancho and the Cloak of a Million Colors", NULL, NULL); break;
		case BORDERLESS:
			glfwWindowHint(GLFW_DECORATED, false);
			glfwWindowHint(GLFW_FLOATING, true);

			window = glfwCreateWindow(width, height, "", NULL, NULL);

			//center the window
			glfwSetWindowPos(window, (mode->width-width)/2, (mode->height-height)/2); 

			break;
		case FULLSCREEN:
			window = glfwCreateWindow(width, height, "", glfwGetPrimaryMonitor(), NULL); break;
		default:
			return NULL;
	}

	if (!window)
    	{
		glfwTerminate();
		return NULL;
	}

	return window;	
}

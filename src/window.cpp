#include "../include/window.h"

GLFWwindow* Window::window_;
int Window::width_, Window::height_;
Window::InitWindow Window::init;

Window::InitWindow::InitWindow() {
	width_=0, height_=0;
	if (!glfwInit())
		return;

	window_ = glfwCreateWindow(1, 1, "Pancho and the Cloak of a Million Colors", NULL, NULL);

	if (!window_)
		glfwTerminate();
}
/*
GLFWwindow* createWindow() {
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
}*/

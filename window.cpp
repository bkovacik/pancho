#include "window.h"

//basically copied from glfw documentation
bool createWindow() {
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(640, 480, "Hello World!", NULL, NULL);
	if (!window)
    	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
	
}

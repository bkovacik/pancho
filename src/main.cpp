#include <iostream>
#include <GL/glew.h>
#include "window.h"

int main() {
	GLFWwindow * window = createWindow(640, 480, WINDOWED);
	if (!window)
		return -1;
	else {
		glfwMakeContextCurrent(window);

		while (!glfwWindowShouldClose(window))
		{
			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	
		glfwTerminate();
	}
		
	return 0;
}

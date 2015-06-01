#include <iostream>
#include "render.h"
#include "window.h"
#include "image.h"
#include "atlas.h"

int main() {
	Image image = Image("resources/atlas.png");
	Atlas atlas = Atlas("resources/atlasMap");

	GLFWwindow* window = createWindow(640, 480, WINDOWED);
	if (!window)
		return -1;
	else {
		glfwMakeContextCurrent(window);
		Render render = Render(64, 32, image.getImage_data(), window);
		//bottom left = (0, 0)
		render.addImage(40, 2, atlas.getCoords("test"));
		render.addImage(300, 93, atlas.getCoords("test3"));
		render.render();
		
	}
		
	return 0;
}

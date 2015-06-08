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
	audio->addAudio("Untitled.wav", "name", "resources/sounds/");

	GLFWwindow* window = createWindow(640, 480, WINDOWED);
	if (!window)
		return -1;
	else {
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);

		render = new Render(64, 32, image.getImage_data(), window);

		if (level.getWidth() < 640 || level.getHeight() < 480 ||
		 level.getHeight() < 0 || level.getWidth() < 0) {
			std::cerr << "ERROR: Level size is less than window size." << std::endl;
		}

		// Not sure how to implement full level size, 
		// data is stored as X = level.getWidth(), Y = level.getHeight()

		//bottom left = (0, 0)

		// Load Pancho
		if (level.start("X") > level.getWidth() || level.start("Y") > level.getHeight() ||
		 level.start("X") < 0 || level.start("Y") < 0) {
			std::cerr << "ERROR: Pancho is out of this world." << std::endl;
		}
		render->addImage(level.start("X"), level.start("Y"), atlas.getCoords("test3"));

		// Load goal
		if (level.goal("X") > level.getWidth() || level.goal("Y") > level.getHeight() ||
		 level.goal("X") < 0 || level.goal("Y") < 0) {
			std::cerr << "ERROR: Goal is out of this world." << std::endl;
		}
		render->addImage(level.goal("X"), level.goal("Y"), atlas.getCoords("test"));

		// Load enemies
		for (std::map<Point, std::string>::const_iterator enemies = level.getEnemies().begin(); enemies != level.getEnemies().end(); ++enemies) {
			if (enemies->first.pt_X > level.getWidth() || enemies->first.pt_Y > level.getHeight() ||
		 		enemies->first.pt_X < 0 || enemies->first.pt_Y < 0) {
				std::cerr << "ERROR: Enemy is not within level bounds." << std::endl;
			}
		render->addImage(enemies->first.pt_X, enemies->first.pt_Y, atlas.getCoords("test"));
		}

		// Load Power-Ups
		for (std::map<Point, std::string>::const_iterator items = level.getPower_Ups().begin(); items != level.getPower_Ups().end(); ++items) {
			if (items->first.pt_X > level.getWidth() || items->first.pt_Y > level.getHeight() ||
		 		items->first.pt_X < 0 || items->first.pt_Y < 0) {
				std::cerr << "ERROR: Item is not within level bounds." << std::endl;
			}
		render->addImage(items->first.pt_X, items->first.pt_Y, atlas.getCoords("test3"));
		}
		render->render(60);
	}

	delete(render);
	delete(audio);
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	int x = 0, y = 0, move = 180.0;

	if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
		x += move;
		audio->playSource("name");
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT))
		x -= move;
	if (glfwGetKey(window, GLFW_KEY_UP))
		y += move;
	if (glfwGetKey(window, GLFW_KEY_DOWN))
		y -= move;

	render->setMovement(x, y, 2);
}

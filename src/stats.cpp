#include "stats.h"

Stats::Stats(Render* render, Atlas* atlas) {
	this->render = render;
	this->atlas = atlas;

	drawHealth(5, 3);
	drawCloak("violet", 80);
}

//health is represented as a factor of 6
//there probably won't be health power-ups so this basic implementation is ok
Stats::drawHealth(int health, int slots) {
	for (int i = 0; i < slots; i++) {
		if (health <= 0)
			render->addImage(i*32, 448, atlas->getCoords("lifeempty"));
		else if (health == 1)
			render->addImage(i*32, 448, atlas->getCoords("lifehalf"));
		else
			render->addImage(i*32, 448, atlas->getCoords("lifefull"));

		health -= 2;
	}
}

Stats::drawCloak(const char* type, int cloak) {
	render->addImage(0, 418, atlas->getCoords("white"), 128, 20);
	render->addImage(1, 419, atlas->getCoords("black"), 126, 18);
	render->addImage(2, 420, atlas->getCoords(type), 124*cloak/100, 16);
}

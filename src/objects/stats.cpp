#include "stats.h"
#include "cloak.h"

Stats::Stats() : hearts(3, Heart(0, 0, 0, 0, FULL)) {
	Coords coords = Atlas::getCoords("lifefull");
	int wHeight = Window::getHeight(), wWidth = Window::getWidth();
	int cWidth = coords.endX - coords.beginX, cHeight = coords.endY - coords.beginY;

	for (int i = 0; i < hearts.size(); i++)
		hearts[i].setPosition(i*cWidth-wWidth/2, wHeight/2-cHeight, (i+1)*cWidth-wWidth/2, wHeight/2);

	cloak = new Cloak(-wWidth/2+CLOAKOFFX, wHeight/2-CLOAKHEIGHT-cHeight-CLOAKOFFY, -wWidth/2+CLOAKWIDTH+CLOAKOFFX, wHeight/2-cHeight-CLOAKOFFY);
}

//health is represented as a factor of 6
Stats::drawHealth(int health, int hearts, std::vector<float>& v, int& offset) {
	Coords coords = Atlas::getCoords("lifefull");
	int wHeight = Window::getHeight(), wWidth = Window::getWidth();
	int cWidth = coords.endX - coords.beginX, cHeight = coords.endY - coords.beginY;

	for (int i = this->hearts.size(); hearts > this->hearts.size(); i++)
		this->hearts.push_back(Heart(i*cWidth-wWidth/2, wHeight/2-cHeight, (i+1)*cWidth-wWidth/2, wHeight/2, FULL));

	for (int i = 0; i < hearts; i++) {
		health -= 2;

		if (health <= -2)
			this->hearts[i].changeState("lifeempty");
		else if (health == -1)
			this->hearts[i].changeState("lifehalf");
		else
			this->hearts[i].changeState("lifefull");

		this->hearts[i].genPosition(Window::getWidth(), Window::getHeight(), 0, 0);
		this->hearts[i].genCoords(Atlas::getWidth(), Atlas::getHeight());
		this->hearts[i].addCoords(v, offset);
	}
}

Stats::drawCloak(const char* type, int cloak, std::vector<float>& v, int& offset) {
	this->cloak->draw(type, cloak, v, offset);
}

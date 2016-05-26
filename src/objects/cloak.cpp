#include "../../include/objects/cloak.h"

Cloak::Cloak(int beginX, int beginY, int endX, int endY) :
	cloak(100),
	draws({Global(beginX, beginY, endX, endY, Atlas::getCoords("white")),
		Global(beginX+1, beginY+1, endX-1, endY-1, Atlas::getCoords("black")),
		Global(beginX+2, beginY+2, endX-2, endY-2, Atlas::getCoords("red"))
	}) {
	position = Coords(beginX, beginY, endX, endY);
}

void Cloak::draw(const char* type, int cloak, std::vector<float>& v, int& offset) {
	int width = position.endX - position.beginX;

	if (this->cloak != cloak) {
		this->cloak = cloak;
		draws[CLOAK] = Global(position.beginX+2, position.beginY+2, position.beginX+((int) width*(cloak/100.0))-2, position.endY-2, Atlas::getCoords(type));
	}

	for (int i = 0; i < 3; i++) {
		this->draws[i].genPosition(Window::getWidth(), Window::getHeight(), 0, 0);
		this->draws[i].genCoords(Atlas::getWidth(), Atlas::getHeight());
		this->draws[i].addCoords(v, offset);
	}
};

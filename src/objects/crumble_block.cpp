#include "../../include/objects/crumble_block.h"
#include "../../include/level.h"

Crumble::Crumble(int beginX, int beginY, int endX, int endY) : Block(beginX, beginY, endX, endY) {
	std::vector<Coords> v_crumbling = std::vector<Coords>(20, Atlas::getCoords("green"));
	statemap["crumbling"] = v_crumbling;

	std::vector<Coords> v_crumbled = std::vector<Coords>(40, Atlas::getCoords("none"));
	statemap["crumbled"] = v_crumbled;
}

void Crumble::step(Level* level) {
	if (frame >= statemap[state].size()-1) {
		if (state == "crumbling")
			changeState("crumbled");
		else if (state == "crumbled")
			changeState("default");
		frame = 0;
	} 
	else
		frame++;
}

void Crumble::onCollide(Drawing* object, Level* level, sides side) {
	if (side == UP && state != "crumbled" && dynamic_cast<Pancho*>(object))
		changeState("crumbling");
}

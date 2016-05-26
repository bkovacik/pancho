#include "../../include/objects/jumpthrough_block.h"
#include "../../include/level.h"

JumpThrough::JumpThrough(int beginX, int beginY, int endX, int endY) : Block(beginX, beginY, endX, endY) {
	std::vector<Coords> v_default = std::vector<Coords>(1, Atlas::getCoords("violet"));
	statemap["default"] = v_default;
	statemap["through"] = v_default;
}

void JumpThrough::onKey(Level* level, key key, int action) {
	if (key == KEY_DOWN)
		state = "through";
	else if (key == KEY_UP)
		state = "default";
}

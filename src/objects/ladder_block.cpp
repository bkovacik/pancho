#include "../../include/objects/ladder_block.h"

Ladder::Ladder(int beginX, int beginY, int endX, int endY) : Block(beginX, beginY, endX, endY) {
	std::vector<Coords> v_default = std::vector<Coords>(1, Atlas::getCoords("yellow"));
	statemap["default"] = v_default;
}

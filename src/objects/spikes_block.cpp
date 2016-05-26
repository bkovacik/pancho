#include "../../include/objects/spikes_block.h"
#include "../../include/level.h"

Spikes::Spikes(int beginX, int beginY, int endX, int endY) : Block(beginX, beginY, endX, endY) {
	std::vector<Coords> v_default = std::vector<Coords>(1, Atlas::getCoords("red"));
	statemap["default"] = v_default;
}

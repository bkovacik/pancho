#include "../../include/objects/trigger_block.h"

Trigger::Trigger(int beginX, int beginY, int endX, int endY) : Block(beginX, beginY, endX, endY) {
	std::vector<Coords> v_default = std::vector<Coords>(1, Atlas::getCoords("indigo"));
	statemap["default"] = v_default;
}

void Trigger::onTrigger() {
#if DEBUG
	printf("#TRIGGERED");
#endif
}

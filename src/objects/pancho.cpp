#include "pancho.h"

Pancho::Pancho(int beginX, int beginY, int endX, int endY) : health(6), numHearts(3), cloak(RED),
	Drawing(beginX, beginY, endX, endY, Atlas::getCoords(COORDNAME)) {
}

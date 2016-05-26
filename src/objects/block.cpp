#include "../../include/objects/block.h"

Block::Block(int beginX, int beginY, int endX, int endY) :
	Drawing(beginX, beginY, endX, endY, Atlas::getCoords("blue")) {
}

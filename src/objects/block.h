//block.h

#ifndef BLOCK_H
#define BLOCK_H

#include "drawing.h"
#include "../atlas.h"

class Block : public Drawing {
	public:
		Block(int beginX, int beginY, int endX, int endY);
};

#endif

//ladder.h

#ifndef LADDER_BLOCK_H
#define LADDER_BLOCK_H

#include "block.h"

class Ladder : public Block {
	public:
		Ladder(int beginX, int beginY, int endX, int endY);
};

#endif

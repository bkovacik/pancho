//crumble_block.h

#ifndef CRUMBLE_BLOCK_H
#define CRUMBLE_BLOCK_H

#include "block.h"

class Crumble : public Block {
	public:
		Crumble(int beginX, int beginY, int endX, int endY);
		void step(Level* level);
		void onCollide(Drawing* object, Level* level, sides side);
};

#endif

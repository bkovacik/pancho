//jumpthrough_block.h

#ifndef JUMPTHROUGH_BLOCK_H
#define JUMPTHROUGH_BLOCK_H

#include "block.h"

class JumpThrough : public Block {
	public:
		JumpThrough(int beginX, int beginY, int endX, int endY);
		void onKey(Level* level, int key, int action);
};

#endif

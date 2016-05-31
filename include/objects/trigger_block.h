//trigger_block.h

#ifndef TRIGGER_BLOCK_H
#define TRIGGER_BLOCK_H

#include "block.h"

class Trigger : public Block {
	public:
		Trigger(int beginX, int beginY, int endX, int endY);
		void onTrigger();
};

#endif

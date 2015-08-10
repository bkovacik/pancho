//heart.h

#ifndef HEART_H
#define HEART_H

#include <vector>
#include "drawing.h"
#include "../atlas.h"

enum full {FULL, HALF, EMPTY};

class Heart : public Global {
	public:
		Heart(int beginX, int beginY, int endX, int endY, full full);
};

#endif

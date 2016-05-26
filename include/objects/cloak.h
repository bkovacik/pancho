//cloak.h

#ifndef CLOAK_H
#define CLOAK_H

#include <vector>
#include "../atlas.h"
#include "drawing.h"

class Cloak {
	enum rects { WHITEO, BLACKO, CLOAK };

	Coords position;
	int cloak;

	Global draws[3];

	public:
		Cloak(int beginX, int beginY, int endX, int endY);
		void draw(const char* type, int cloak, std::vector<float>& v, int& offset);
};

#endif

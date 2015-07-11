//pancho.h

#ifndef PANCHO_H
#define PANCHO_H

#define COORDNAME "red"

#include <vector>
#include "../supertypes.h"
#include "../atlas.h"

enum cloaks {RED,ORANGE,YELLOW,GREEN,BLUE,INDIGO,VIOLET};

class Pancho : public Drawing {
	protected:
		int health, numHearts, cloak;
	public:
		Pancho(int beginX, int beginY, int endX, int endY);
		void setHealth(int health) {this->health = health;}
		void setNumHearts(int numHearts) {this->numHearts = numHearts;}
		void setCloak(int cloak) {this->cloak = cloak;}
};

#endif

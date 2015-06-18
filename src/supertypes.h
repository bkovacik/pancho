#ifndef SUPERTYPES_H
#define SUPERTYPES_H

#include "atlas.h"

//For polymorphism purposes
class GameObject {};

class Collision {

};

class Velocity {

};

class Gravity {

};

class Autonomous {

};

class Dynamic {

}

class Position : GameObject {
	private:
		Coords position;
	public:
		Position(int beginX, int beginY, int endX, int endY) {
			position = Coords(int beginX, int beginY, int endX, int endY);
		}
}

class Drawing : Position {
	private:
		Coords texCoords;
	public:
		virtual void getCoords();

		Drawing(int pbeginX, int pbeginY, int pendX, int pendY,
			int tbeginX, int tbeginY, int tendX, int tendY) {
			Position(int pbeginX, int pbeginY, int pendX, int pendY);
			texCoords = Coords(int tbeginX, int tbeginY, int tendX, int tendY);
		}
		
};

#endif

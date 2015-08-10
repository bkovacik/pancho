//position.h

#ifndef POSITION_H
#define POSITION_H

#include <vector>
#include "../atlas.h"

//for polymorphism
class GameObject {public: virtual ~GameObject(){}};

class Position : public GameObject {
	protected:
		Coords position;
		std::vector<float> vertices;
	public:
		Position(int beginX, int beginY, int endX, int endY) :
			position(beginX, beginY, endX, endY) {
			vertices.assign(24, 0);
		}
		void setPosition(int beginX, int beginY, int endX, int endY) {
			position = Coords(beginX, beginY, endX, endY);	
		}
		virtual Coords getPosition(int originX, int originY) {return position;}
		virtual void genPosition(int width, int height, int originX, int originY);
};

#endif

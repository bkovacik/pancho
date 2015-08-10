#include "drawing.h"
#include "../level.h"

//width and height of IMAGE
void Drawing::genCoords(int width, int height) {
	Coords texCoords = statemap[state][frame];
	float	cbx = (float)texCoords.beginX/width,
		cby = (float)texCoords.beginY/height,
		cex = (float)texCoords.endX/width,
		cey = (float)texCoords.endY/height;

	float c[] = {
		cbx, cby,
		cex, cby,
		cbx, cey,
		cex, cey
	};

	for (int i = 0; i < 4; i++) {
		vertices[i*6+2] = c[i*2];
		vertices[i*6+3] = c[i*2+1];
		vertices[i*6+4] = orientation ? 1.0 : 0.0;
		vertices[i*6+5] = c[((i+1)%2)*2];
	}
}

sides Drawing::isCollide(Drawing* object, float offsetX, float offsetY) {
	Coords pos1 = this->getPosition(offsetX, offsetY);
	Coords pos2 = object->getPosition(offsetX, offsetY);

	int tbeginX = position.beginX, tendX = position.endX,
		tbeginY = position.beginY, tendY = position.endY;

	if (!(pos1.beginX > pos2.endX ||
		pos1.endX < pos2.beginX ||
		pos1.beginY > pos2.endY ||
		pos1.endY < pos2.beginY)) {

		float totalX = (pos1.endX - pos1.beginX + pos2.endX - pos2.endX)/2.0;
		float totalY = (pos1.endY - pos1.beginY + pos2.endY - pos2.endY)/2.0;
		float diffX, diffY;
		if (pos1.beginX > pos2.beginX)
			diffX = pos1.beginX - pos2.beginX;
		else
			diffX = pos2.beginX - pos1.beginX;
		if (pos1.beginY > pos2.beginY)
			diffY = pos1.beginY - pos2.beginY;
		else
			diffY = pos2.beginY - pos1.beginY;

		if (diffY/totalY > diffX/totalX) {
			if (pos1.beginY < pos2.beginY)
				return UP;
			else if (pos1.endY > pos2.endY)
				return DOWN;
		}
		else {
			if (pos1.beginX < pos2.beginX)
				return RIGHT;
			else if (pos1.endX > pos2.endX)
				return LEFT;
		}
		return IN;
	}

	return NONE;
}

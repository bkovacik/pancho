#include "../../include/objects/position.h"

void Position::genPosition(int width, int height, int originX, int originY)
{
	float	bx = (position.beginX-originX)*2.0/width,
		by = (position.beginY-originY)*2.0/height,
		ex = (position.endX-originX)*2.0/width,
		ey = (position.endY-originY)*2.0/height;

	float v[] = {
		bx, ey,
		ex, ey,
		bx, by,
		ex, by
	};

	for (int i = 0; i < 4; i++) {
		vertices[i*6] = v[i*2];
		vertices[i*6+1] = v[i*2+1];
	}
}

#ifndef SUPERTYPES_H
#define SUPERTYPES_H

#include "atlas.h"

class Collision {

};

class Velocity {

};

class Gravity {

};

class Autonomous {

};

class Position {
	protected:
		Coords position;
		std::vector<float> vertices;
	public:
		Position(int beginX, int beginY, int endX, int endY) :
			position(beginX, beginY, endX, endY) {
			vertices.assign(16, 0);
		}
		//width and height of WINDOW
		void genPosition(int width, int height, int originX, int originY) {
			float	bx = (position.beginX-originX)*2.0/width - 1.0,
				by = (position.beginY-originY)*2.0/height - 1.0,
				ex = (position.endX-originX)*2.0/width - 1.0,
				ey = (position.endY-originY)*2.0/height - 1.0;

			float v[] = {
				bx, ey,
				ex, ey,
				bx, by,
				ex, by
			};

			for (int i = 0; i < 8; i+=2) {
				vertices[i*2] = v[i];
				vertices[i*2+1] = v[i+1];
			}
		}
};

class Drawing : public Position {
	protected:
		Coords texCoords;
	public:
		Drawing(int beginX, int beginY, int endX, int endY, Coords coords) :
			Position(beginX, beginY, endX, endY) {
			texCoords = coords;

			vertices.assign(16, 0);
		}
		//width and height of IMAGE
		void genCoords(int width, int height) {
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

			for (int i = 0; i < 8; i+=2) {
				vertices[i*2+2] = c[i];
				vertices[i*2+3] = c[i+1];
			}
		}
		void addCoords(std::vector<float>& v, int offset) {
			if (offset >= v.size())
				v.insert(v.end(), vertices.begin(), vertices.end());

			else {
				for (int i = 0; i < 16; i++)
					v[i+offset] = vertices[i];
			}
		}
		
};

#endif

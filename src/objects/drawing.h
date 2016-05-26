#ifndef DRAWING_H
#define DRAWING_H

#include <vector>
#include "position.h"
#include "../atlas.h"
#include "../window.h"
#include "../keytranslate.h"

class Level;

enum sides {NONE, LEFT, UP, RIGHT, DOWN, IN};

class Drawing : public Position {
	protected:
		int frame;
		float moveX, moveY;
		std::string state;
		std::map<std::string, std::vector<Coords> > statemap;
		bool orientation; // true is facing right, false is facing left
		bool alwaysDraw;
	public:
		Drawing(int beginX, int beginY, int endX, int endY, Coords coords) :
			Position(beginX, beginY, endX, endY) {
			this->frame = 0;
			this->orientation = false;
			this->state = "default";
			std::vector<Coords> v = std::vector<Coords>(1, coords);
			this->statemap[this->state] = v;
		}
		void changeState(std::string state) { if (statemap.count(state)) this->state = state; }
		std::string getState() { return this->state; }
		bool getAlwaysDraw() { return this->alwaysDraw; }
		void genCoords(int width, int height);
		sides isCollide(Drawing* object, float offsetX, float offsetY);

		virtual void onCollide(Drawing* object, Level* level, sides side) {}
		virtual void onKey(Level* level, key key, int action) {}

		virtual void step(Level* level) { if (frame >= statemap[state].size()-1) frame = 0; else frame++; }
		virtual void addCoords(std::vector<float>& v, int& offset) {
			if (offset >= v.size())
				v.insert(v.end(), vertices.begin(), vertices.end());
			else {
				for (int i = 0; i < vertices.size(); i++)
					v[i+offset] = vertices[i];
			}

			offset += vertices.size();
		}
};

//always draw if an object is Global
class Global : public Drawing {
	public:
		Global(int beginX, int beginY, int endX, int endY, Coords coords) :
			Drawing(beginX, beginY, endX, endY, coords) {
			this->alwaysDraw = true;
		}
		void genPosition(int width, int height, int originX, int originY) {
			Drawing::genPosition(width,height,0,0);
		}
		Coords getPosition(int originX, int originY) {return Coords(position.beginX+originX, position.beginY+originY, position.endX+originX, position.endY+originY);}
};

#endif

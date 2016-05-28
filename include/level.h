//level.h
//loads basic level characteristics

#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include <map>
#include <vector>
#include "objects/factory.h"
#include "atlas.h"
#include "window.h"
#include "keytranslate.h"

struct Point {
	int pt_X = 0;
	int pt_Y = 0;
	Point() : pt_X(0), pt_Y(0) {}
	Point(int x, int y) : pt_X(x), pt_Y(y) {}
};

// I made this static because it was being redeclared in level.cpp after main.cpp, not sure if this 
// is good coding practice.
static bool operator<(const Point& pt1, const Point& pt2) {
	if (pt1.pt_X < pt2.pt_X) { return true; }
	else { return pt1.pt_Y < pt2.pt_Y; }
}

class Level {
	private:
		int toGrid(int position, int dimension) { return (int) ((float) dimension/position) + 0.5;}
		void checkCollObj(Drawing* object);
		void populate();
		void checkCollisions();
		void trigger(std::string name);

		std::map<std::string, Point> positions;
		std::map<std::string, Drawing*> objects;
		std::map<Point, std::string> enemies;
		std::map<Point, std::string> pwr_ups;

		std::vector<std::vector<std::vector<Drawing*> > > draw;
		std::vector<Drawing*> drawGlobal;
		std::vector<float> vertices;

		int numDraw, width, height, fps;
		float originX, originY, moveX, moveY, gravity;
		bool orientation;
	public:
		Level(std::string name);
		~Level();
		int getWidth() { return positions["Size"].pt_X; }
		int getHeight() { return positions["Size"].pt_Y; }

		int start(const std::string& cord);
		int goal(const std::string& cord);

		void createAt(std::string name, std::string key, int x, int y);
		void deleteFrom(Drawing* object);
		void onKey(key key, int action);
		void step(int fps);

		void setMove(float x, float y) { moveX=x; moveY=y; }
		void getMove(float& x, float& y) { x=moveX; y=moveY; }
		void shift(float x, float y) { originX += x; originY += y; }
		void getOrigin(float& x, float& y) { x=originX; y=originY; }
		float getGravity() { return this->gravity/fps; }
		//void load(Render* render);

		std::vector<float> getDrawVert() { return vertices; }

		const std::map<Point, std::string>& getEnemies() { return enemies; }
		const std::map<Point, std::string>& getPower_Ups() { return pwr_ups; }
};



#endif

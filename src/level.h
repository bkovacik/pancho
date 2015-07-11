//level.h
//loads basic level characteristics

#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include <map>
#include <vector>
#include "supertypes.h"
#include "objects/pancho.h"
#include "atlas.h"
#include "window.h"
#include <iostream>

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

		std::map<std::string, Point> positions;
		std::map<Point, std::string> enemies;
		std::map<Point, std::string> pwr_ups;

		std::vector<std::vector<std::vector<Drawing*> > > draw;
		std::vector<float> vertices;

		int numDraw, width, height;
		float originX, originY;
	public:
		Level(const char* name);
		~Level();
		int getWidth() { return positions["Size"].pt_X; }
		int getHeight() { return positions["Size"].pt_Y; }
		int getNumDraw() { return numDraw; }
		int start(const std::string& cord);
		int goal(const std::string& cord);
		void populate();
		void shiftOrigin(float x, float y) { originX += x; originY += y; }
		//void load(Render* render);

		std::vector<float> getDrawVert() { return vertices; }

		const std::map<Point, std::string>& getEnemies() { return enemies; }
		const std::map<Point, std::string>& getPower_Ups() { return pwr_ups; }
};



#endif

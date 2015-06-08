//levels.h
//loads basic level characteristics

#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include <map>

class Point {
	public:
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
public:
	Level(const char* name);
	int getWidth() { return positions["Size"].pt_X; }
	int getHeight() { return positions["Size"].pt_Y; }
	int start(const std::string& cord);
	int goal(const std::string& cord);

	const std::map<Point, std::string>& getEnemies() { return enemies; }
	const std::map<Point, std::string>& getPower_Ups() { return pwr_ups; }

private:
	std::map<std::string, Point> positions;
	std::map<Point, std::string> enemies;
	std::map<Point, std::string> pwr_ups;
};



#endif

#include "level.h"
#include "render.h"
#include "atlas.h"

Level::Level(const char* name) {
	std::ifstream fin (name, std::ifstream::in);
	std::string str;
	int line = 1;

	//Discard the first line
	getline(fin, str);

	while (fin.good() && line != 4) {
		int index = 0;
		line++;

		getline(fin, str);
		if (str == "" || str == "Enemies")
			break;

		std::string key;
		index = str.find(",");
		key = str.substr(0, index);
		positions[key] = Point();

		index++;
		positions[key].pt_X = std::stoi(str.substr(index, str.find(",", index)-index));
		index = str.find(",", index)+1;
		positions[key].pt_Y = std::stoi(str.substr(index));
	}

	// Ignore fifth line of the file
	getline(fin, str);

	//Parse all enemies + locations
	while (fin.good()) {
		getline(fin, str);

		if (str == "" || str == "Power-ups")
			break;

		int index = str.find(",")+1;
		std::string type = str.substr(0,index);

		int x = std::stoi(str.substr(index, str.find(",", index)-index));
		index = str.find(",", index)+1;
		int y = std::stoi(str.substr(index));

		enemies[Point(x,y)] = type;
	}

	//Parse all power-ups
	while (fin.good()) {
		getline(fin, str);

		//check for ending \n
		if (str == "")
			break;
		
		int index = str.find(",");
		std::string type = str.substr(0,index);
		index++;
		int x = std::stoi(str.substr(index, str.find(",", index)-index));
		index = str.find(",", index)+1;
		int y = std::stoi(str.substr(index));

		pwr_ups[Point(x,y)] = type;
	}

	fin.close();
}

int Level::start(const std::string& cord) {
	if (cord == "X") return positions["Start"].pt_X;
	if (cord == "Y") return positions["Start"].pt_Y;
}

int Level::goal(const std::string& cord) {
	if (cord == "X") return positions["Goal"].pt_X;
	if (cord == "Y") return positions["Goal"].pt_Y;
}

void Level::load(Render* render, Atlas& atlas) {
	if (getWidth() < 640 || getHeight() < 480 ||
	 getHeight() < 0 || getWidth() < 0) {
		std::cerr << "ERROR: Level size is less than window size." << std::endl;
	}

	// Not sure how to implement full level size, 
	// data is stored as X = level.getWidth(), Y = level.getHeight()

	// Load Pancho
	if (start("X") > getWidth() || start("Y") > getHeight() ||
	 start("X") < 0 || start("Y") < 0) {
		std::cerr << "ERROR: Pancho is out of this world." << std::endl;
	}
	render->addImage(start("X"), start("Y"), atlas.getCoords("test3"));
	
	// Load goal
	if (goal("X") > getWidth() || goal("Y") > getHeight() ||
	 goal("X") < 0 || goal("Y") < 0) {
		std::cerr << "ERROR: Goal is out of this world." << std::endl;
	}
	render->addImage(goal("X"), goal("Y"), atlas.getCoords("test"));

	// Load enemies
	for (std::map<Point, std::string>::iterator ens = enemies.begin(); ens != enemies.end(); ++ens) {
		if (ens->first.pt_X > getWidth() || ens->first.pt_Y > getHeight() ||
	 		ens->first.pt_X < 0 || ens->first.pt_Y < 0) {
			std::cerr << "ERROR: Enemy is not within level bounds." << std::endl;
		}
	render->addImage(ens->first.pt_X, ens->first.pt_Y, atlas.getCoords("test"));
	}

	// Load Power-Ups
	for (std::map<Point, std::string>::iterator items = pwr_ups.begin(); items != pwr_ups.end(); ++items) {
		if (items->first.pt_X > getWidth() || items->first.pt_Y > getHeight() ||
	 		items->first.pt_X < 0 || items->first.pt_Y < 0) {
			std::cerr << "ERROR: Item is not within level bounds." << std::endl;
		}
	render->addImage(items->first.pt_X, items->first.pt_Y, atlas.getCoords("test3"));
	}
}

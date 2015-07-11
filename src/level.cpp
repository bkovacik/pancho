#include "level.h"

Level::Level(const char* name) {
	numDraw = 0;
	std::ifstream fin (name, std::ifstream::in);
	std::string str;
	int line = 1;

	//Discard the first line
	getline(fin, str);

	//width and height
	getline(fin, str);
	int index = str.find(",");
	this->width = std::stoi(str.substr(0, index));
	this->height = std::stoi(str.substr(index+1));
	this->draw = std::vector<std::vector<std::vector<Drawing*> > >(toGrid(640/2, width), std::vector<std::vector<Drawing*> >(toGrid(480/2, height), std::vector<Drawing*>()));

	//origin
	getline(fin, str);
	index = str.find(",");
	this->originX = std::stoi(str.substr(0, index));
	this->originY = std::stoi(str.substr(index+1));

	while (fin.good()) {
		index = 0;
		line++;
		numDraw++;

		getline(fin, str);

		std::string key;
		index = str.find(",");
		key = str.substr(0, index);
		positions[key] = Point();

		index++;
		int x = std::stoi(str.substr(index, str.find(",", index)-index));
		index = str.find(",", index)+1;
		int y = std::stoi(str.substr(index));
		draw[toGrid(640/2, x)][toGrid(480/2, y)].push_back(new Pancho(x, y, x+32, y+32));
	}

	fin.close();
}

Level::~Level() {
	for (int i = 0; i < draw.size(); i++) {
		for (int j = 0; j < draw[i].size(); j++) {
			for (int k = 0; k < draw[i][j].size(); k++)
				delete(draw[i][j][k]);
		}
	}
}

int Level::start(const std::string& cord) {
	if (cord == "X") return positions["Start"].pt_X;
	if (cord == "Y") return positions["Start"].pt_Y;
}

int Level::goal(const std::string& cord) {
	if (cord == "X") return positions["Goal"].pt_X;
	if (cord == "Y") return positions["Goal"].pt_Y;
}

void Level::populate() {
	vertices.resize(numDraw*16);
	int offset = 0;

	for (int i = 0; i < draw.size(); i++) {
		for (int j = 0; j < draw[i].size(); j++) {
			for (int k = 0; k < draw[i][j].size(); k++) {
				draw[i][j][k]->genPosition(640, 480, originX, originY);
				draw[i][j][k]->genCoords(194, 130);
				draw[i][j][k]->addCoords(vertices, offset++*16);
			}
		}
	}
}

/*
void Level::load(Render* render) {
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
	render->addImage(start("X"), start("Y"), Atlas::getCoords("test3"));
	
	// Load goal
	if (goal("X") > getWidth() || goal("Y") > getHeight() ||
	 goal("X") < 0 || goal("Y") < 0) {
		std::cerr << "ERROR: Goal is out of this world." << std::endl;
	}
	render->addImage(goal("X"), goal("Y"), Atlas::getCoords("test"));

	// Load enemies
	for (std::map<Point, std::string>::iterator ens = enemies.begin(); ens != enemies.end(); ++ens) {
		if (ens->first.pt_X > getWidth() || ens->first.pt_Y > getHeight() ||
	 		ens->first.pt_X < 0 || ens->first.pt_Y < 0) {
			std::cerr << "ERROR: Enemy is not within level bounds." << std::endl;
		}
	render->addImage(ens->first.pt_X, ens->first.pt_Y, Atlas::getCoords("test"));
	}

	// Load Power-Ups
	for (std::map<Point, std::string>::iterator items = pwr_ups.begin(); items != pwr_ups.end(); ++items) {
		if (items->first.pt_X > getWidth() || items->first.pt_Y > getHeight() ||
	 		items->first.pt_X < 0 || items->first.pt_Y < 0) {
			std::cerr << "ERROR: Item is not within level bounds." << std::endl;
		}
	render->addImage(items->first.pt_X, items->first.pt_Y, Atlas::getCoords("test3"));
	}
}*/

#include "level.h"

Level::Level(std:: string name) {
	std::ifstream fin (name.c_str(), std::ifstream::in);
	if (!fin) {
		fprintf(stderr, "File not found.\n");
		exit(-1);
	}
	std::string str;
	int line = 1;

	//Discard the first line
	getline(fin, str);

	//width and height
	getline(fin, str);
	int index = str.find(",");
	this->width = std::stoi(str.substr(0, index));
	this->height = std::stoi(str.substr(index+1));
	this->draw = std::vector<std::vector<std::vector<Drawing*> > >(toGrid(Window::getWidth()/2, width), std::vector<std::vector<Drawing*> >(toGrid(Window::getHeight()/2, height), std::vector<Drawing*>()));

	//origin
	getline(fin, str);
	index = str.find(",");
	this->originX = std::stoi(str.substr(0, index));
	this->originY = std::stoi(str.substr(index+1));
	this->moveX = 0; this->moveY = 0;

	//gravity
	getline(fin, str);
	this->gravity = std::stof(str);

	while (fin.good()) {
		index = 0;
		line++;

		getline(fin, str);

		std::string key;
		index = str.find(",");
		key = str.substr(0, index);
		positions[key] = Point();

		if (!key.length() || key[0] < 'A' || key[0] > 'z')
			break;

		index++;
		int x = std::stoi(str.substr(index, str.find(",", index)-index));
		index = str.find(",", index)+1;
		int y = std::stoi(str.substr(index));

		createAt(key, x, y);
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

void Level::checkCollObj(Drawing* object) {
	for (int i = 0; i < draw.size(); i++) {
		for (int j = 0; j < draw[i].size(); j++) {
			for (int k = 0; k < draw[i][j].size(); k++) {
				Drawing* collide = draw[i][j][k];
				sides side = NONE;
				if (collide != object)
					side = collide->isCollide(object, originX, originY);
				if (side > NONE)
					collide->onCollide(object, this, side);
			}
		}
	}

	for (int i = 0; i < drawGlobal.size(); i++) {
		Drawing* collide = drawGlobal[i];
		sides side = NONE;
		if (collide != object)
			side = collide->isCollide(object, originX, originY);
		if (side > NONE)
			collide->onCollide(object, this, side);
	}
}

void Level::populate() {
	int offset = 0;

	for (int i = 0; i < draw.size(); i++) {
		for (int j = 0; j < draw[i].size(); j++) {
			for (int k = 0; k < draw[i][j].size(); k++) {
				draw[i][j][k]->genPosition(640, 480, originX, originY);
				draw[i][j][k]->genCoords(194, 130);
				draw[i][j][k]->addCoords(vertices, offset);
			}
		}
	}

	for (int i = 0; i < drawGlobal.size(); i++) {
		drawGlobal[i]->genPosition(640, 480, originX, originY);
		drawGlobal[i]->genCoords(194, 130);
		drawGlobal[i]->addCoords(vertices, offset);
	}
}

void Level::checkCollisions() {
	for (int i = 0; i < draw.size(); i++) {
		for (int j = 0; j < draw[i].size(); j++) {
			for (int k = 0; k < draw[i][j].size(); k++)
				checkCollObj(draw[i][j][k]);
		}
	}

	for (int i = 0; i < drawGlobal.size(); i++)
		checkCollObj(drawGlobal[i]);
}

int Level::start(const std::string& cord) {
	if (cord == "X") return positions["Start"].pt_X;
	if (cord == "Y") return positions["Start"].pt_Y;
}

int Level::goal(const std::string& cord) {
	if (cord == "X") return positions["Goal"].pt_X;
	if (cord == "Y") return positions["Goal"].pt_Y;
}

void Level::createAt(std::string key, int x, int y) {
	GameObject* newObject = Factory::getNewObject(key, x, y, x+32, y+32);
	if (Drawing* newDraw = dynamic_cast<Drawing*>(newObject)) {
		if (newDraw->getAlwaysDraw())
			drawGlobal.push_back(newDraw);
		else
			draw[toGrid(640/2, x)][toGrid(480/2, y)].push_back(newDraw);
	}		
}

void Level::deleteFrom(Drawing* object) {
	for (int i = 0; i < draw.size(); i++) {
		for (int j = 0; j < draw[i].size(); j++) {
			for (int k = 0; k < draw[i][j].size(); k++)
				if (draw[i][j][k] == object)
					draw[i][j].erase(draw[i][j].begin()+k);
		}
	}

	for (int i = 0; i < drawGlobal.size(); i++) {
		if (drawGlobal[i] == object)
			drawGlobal.erase(drawGlobal.begin()+i);
	}

	delete(object);
}

void Level::onKey(key key, int action) {
	for (int i = 0; i < draw.size(); i++) {
		for (int j = 0; j < draw[i].size(); j++) {
			for (int k = 0; k < draw[i][j].size(); k++)
				draw[i][j][k]->onKey(this, key, action);
		}
	}

	for (int i = 0; i < drawGlobal.size(); i++)
		drawGlobal[i]->onKey(this, key, action);
}

void Level::step(int fps) {
	this->fps = fps;
	moveY -= gravity/fps;

	for (int i = 0; i < draw.size(); i++) {
		for (int j = 0; j < draw[i].size(); j++) {
			for (int k = 0; k < draw[i][j].size(); k++)
				draw[i][j][k]->step(this);
		}
	}

	for (int i = 0; i < drawGlobal.size(); i++)
		drawGlobal[i]->step(this);

	populate();
	checkCollisions();

	originX += moveX/fps; originY += moveY/fps;
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

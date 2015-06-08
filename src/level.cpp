#include "level.h"

Level::Level(const char* name) {
	std::ifstream fin (name, std::ifstream::in);
	std::string str;
	int line = 1;

	//Discard the first line
	getline(fin, str);

	while (fin >> str) {
		++line;
		int index = 0;

		//check for ending \n or enemies portion of the file
		if (str == "" || str == "Enemies")
			break;

		std::string key;
		index = str.find(",");
		key = str.substr(0, index);
		positions[key] = Point();

		index++;
		positions[key].pt_X = std::atoi(str.substr(index, str.find(",", index)).c_str());
		index = str.find(",", index)+1;
		positions[key].pt_Y = std::atoi(str.substr(index).c_str());
		if (line == 4) break;
	}

	// Ignore fifth line of the file
	getline(fin, str);
	getline(fin, str);

	//Parse all enemies + locations
	while (fin >> str) {
		//check for ending \n or power-ups portion of the file
		if (str == "" || str == "Power-ups")
			break;

		int index = str.find(",");
		std::string type = str.substr(0,index);
		++index;
		int x = std::atoi(str.substr(index, str.find(",", index)).c_str());
		index = str.find(",", index)+1;
		int y = std::atoi(str.substr(index).c_str());

		enemies[Point(x,y)] = type;
	}

	//Parse all power-ups
	while (fin >> str) {
		//check for ending \n
		if (str == "")
			break;
		
		int index = str.find(",");
		std::string type = str.substr(0,index);
		++index;
		int x = std::atoi(str.substr(index, str.find(",", index)).c_str());
		index = str.find(",", index)+1;
		int y = std::atoi(str.substr(index).c_str());

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

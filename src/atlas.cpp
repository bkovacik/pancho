#include "atlas.h"

std::map<std::string, Coords> Atlas::textures_;
int Atlas::width_, Atlas::height_;
Atlas::InitAtlas Atlas::init;

Atlas::InitAtlas::InitAtlas() {
	std::ifstream fin (ATLASNAME, std::ifstream::in);

	std::string str;

	//Discard the first line
	getline(fin, str);

	getline(fin, str);

	int index = str.find(",", index);
	width_ = std::stoi(str.substr(0, index));
	height_ = std::stoi(str.substr(index+1));

	while (fin.good()) {
		index = 0;

		getline(fin, str);

		//check for ending \n
		if (str == "")	
			break;

		std::string key;
		index = str.find(",");
		key = str.substr(0, index);

		textures_[key] = Coords();

		index++;
		textures_[key].beginX = std::stoi(str.substr(index, str.find(",", index)));
		index = str.find(",", index)+1;

		textures_[key].beginY = std::stoi(str.substr(index, str.find(",", index)));
		index = str.find(",", index)+1;

		textures_[key].endX = std::stoi(str.substr(index, str.find(",", index)));
		index = str.find(",", index)+1;

		textures_[key].endY = std::stoi(str.substr(index));
	}

	fin.close();
}

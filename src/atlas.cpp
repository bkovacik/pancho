#include "atlas.h"

Atlas::Atlas(const char* name) {
	std::ifstream fin (name, std::ifstream::in);

	std::string str;

	//Discard the first line
	getline(fin, str);
	std::string remain;

	while (fin.good()) {
		int index = 0;

		getline(fin, str);

		//check for ending \n
		if (str == "")	
			break;

		std::string key;
		index = str.find(",");
		key = str.substr(0, index);

		textures[key] = Coords();

		index++;
		textures[key].beginX = std::stoi(str.substr(index, str.find(" ", index)-index));
		index = str.find(",", index)+1;

		textures[key].beginY = std::stoi(str.substr(index, str.find(" ", index)-index));
		index = str.find(",", index)+1;

		textures[key].endX = std::stoi(str.substr(index, str.find(" ", index)-index));
		index = str.find(",", index)+1;

		textures[key].endY = std::stoi(str.substr(index));
	}

	fin.close();
}

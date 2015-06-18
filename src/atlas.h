//atlas.h
//provides an interface for the texture atlas mapping

#ifndef ATLAS_H
#define ATLAS_H

#include <fstream>
#include <map>

class Coords {
	public:
		int beginX, beginY, endX, endY;
		Coords(int beginX=0, int beginY=0, int endX=0, int endY=0) {
			this->beginX = beginX;
			this->beginY = beginY;
			this->endX = endX;
			this->endY = endY;
		}
};

class Atlas {
	private:
		std::map<std::string, Coords> textures;
	public:
		Atlas(const char* name);
		Coords getCoords(const char* key) { return textures[key]; }
};

#endif

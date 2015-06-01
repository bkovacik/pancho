//atlas.h
//provides an interface for the texture atlas mapping

#ifndef ATLAS_H
#define ATLAS_H

#include <fstream>
#include <map>

class Coords {
	public:
		int beginX, beginY, endX, endY;
};

class Atlas {
	private:
		std::map<std::string, Coords> textures;
	public:
		Atlas(const char* name);
		Coords getCoords(const char* key) { return textures[key]; }
};

#endif

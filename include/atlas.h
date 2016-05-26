//atlas.h
//provides an interface for the texture atlas mapping

#ifndef ATLAS_H
#define ATLAS_H

#define ATLASNAME "resources/atlasMap.csv"

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
	static std::map<std::string, Coords> textures_;
	static int width_, height_;

	static class InitAtlas {
		public:
			InitAtlas();
	} init;

	public:
		static Coords getCoords(const char* key) {return textures_[key];}
		static int getWidth() {return width_;}
		static int getHeight() {return height_;}
};

#endif

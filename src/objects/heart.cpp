#include "../../include/objects/heart.h"

Heart::Heart(int beginX, int beginY, int endX, int endY, full full) :
	Global(beginX, beginY, endX, endY, Atlas::getCoords("red")) {

	statemap["lifefull"] = std::vector<Coords>();
	statemap["lifefull"].push_back(Atlas::getCoords("lifefull"));

	statemap["lifeehalf"] = std::vector<Coords>();
	statemap["lifehalf"].push_back(Atlas::getCoords("lifehalf"));

	statemap["lifeempty"] = std::vector<Coords>();
	statemap["lifeempty"].push_back(Atlas::getCoords("lifeempty"));
}

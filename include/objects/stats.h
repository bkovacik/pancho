//stats.h

#ifndef STATS_H
#define STATS_H

#include <vector>
#include "heart.h"
#include "../window.h"
#include "../atlas.h"

#define CLOAKWIDTH 80
#define CLOAKHEIGHT 20
#define CLOAKOFFX 10
#define CLOAKOFFY 5

class Cloak;

class Stats {
	protected:
		std::vector<Heart> hearts;
		Cloak* cloak;
	public:
		Stats();
		drawHealth(int health, int hearts, std::vector<float>& v, int& offset);
		drawCloak(const char* type, int cloak, std::vector<float>& v, int& offset);
};

#endif

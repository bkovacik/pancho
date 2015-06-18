//stats.h

#ifndef STATS_H
#define STATS_H

#include "render.h"
#include "atlas.h"

class Stats{
	private:
		Render* render;
		Atlas* atlas;
	public:
		Stats(Render* render, Atlas* atlas);
		drawHealth(int health, int slots);
		drawCloak(const char* type, int cloak);
};

#endif

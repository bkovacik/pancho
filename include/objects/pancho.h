//pancho.h

#ifndef PANCHO_H
#define PANCHO_H

#include <vector>
#include "../atlas.h"
#include "drawing.h"
#include "stats.h"

#define INVULN_FRAMES 60
#define COORDNAME "red"
#define NUMCLOAKS 7

class Level;
class Block;
class Crumble;
class Spikes;
class Blob;
class JumpThrough;
class Ladder;
class Trigger;

enum cloake {RED,ORANGE,YELLOW,GREEN,BLUE,INDIGO,VIOLET};

class Pancho : public Global {
	protected:
		int health, numHearts, cloak, invuln, numJumps, maxJumps;
		cloake cloakColor;
		const char* cloaks[NUMCLOAKS];
		Stats stats;

		void setHealth(int health) {this->health = health;}
		void setNumHearts(int numHearts) {this->numHearts = numHearts;}
		void setCloakColor(cloake cloakColor) {this->cloakColor = cloakColor;}
		void decCloak();
		void incCloak();
		void damage(int health);
	public:
		Pancho(int beginX, int beginY, int endX, int endY);
		void addCoords(std::vector<float>& v, int& offset);

		void onKey(Level* level, key key, int action);
		void step(Level* level);

		void onCollide(Drawing* object, Level* level, sides side);
		void onCollide(Block* object, Level* level, sides side);
		void onCollide(Crumble* object, Level* level, sides side);
		void onCollide(Spikes* object, Level* level, sides side);
		void onCollide(Blob* object, Level* level, sides side);
		void onCollide(JumpThrough* object, Level* level, sides side);
		void onCollide(Ladder* object, Level* level, sides side);
};

#endif

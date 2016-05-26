//enemy.h

#ifndef ENEMY_H
#define ENEMY_H

#include "drawing.h"

#define X_MOVE 2
#define DAMAGE 1

class Block;

class Enemy : public Drawing {
	int damage;
	public:
		Enemy(int beginX, int beginY, int endX, int endY, Coords coords);
		int getDamage() {return damage;}
		virtual void step(Level* level);

		void onCollide(Drawing* object, Level* level, sides side);
		void onCollide(Block* object, Level* level, sides side);
};

#endif

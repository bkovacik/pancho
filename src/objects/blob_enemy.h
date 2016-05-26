//blob.h

#ifndef BLOB_ENEMY_H
#define BLOB_ENEMY_H

#include "enemy.h"

class Block;
class Pancho;

class Blob : public Enemy {
	public:
		Blob(int beginX, int beginY, int endX, int endY);

		void onCollide(Drawing* object, Level* level, sides side);
		void onCollide(Block* object, Level* level, sides side);
		void onCollide(Pancho* object, Level* level, sides side);
};

#endif

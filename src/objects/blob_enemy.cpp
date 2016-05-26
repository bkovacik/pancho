#include "blob_enemy.h"
#include "block.h"
#include "pancho.h"
#include "../level.h"
#include "../atlas.h"

Blob::Blob(int beginX, int beginY, int endX, int endY) :
	Enemy(beginX, beginY, endX, endY, Atlas::getCoords("red")) {
}

void Blob::onCollide(Drawing* object, Level* level, sides side) {
	if (Block* collide = dynamic_cast<Block*>(object))
		this->onCollide(collide, level, side);
	else if (Pancho* collide = dynamic_cast<Pancho*>(object))
		this->onCollide(collide, level, side);
}

void Blob::onCollide(Block* object, Level* level, sides side) {
	Enemy::onCollide(object, level, side);
	if (side == LEFT || side == RIGHT)
		this->moveX *= -1;
}

void Blob::onCollide(Pancho* object, Level* level, sides side) {
	if (side == UP)
		level->deleteFrom(this);
}

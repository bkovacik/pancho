#include "../../include/objects/enemy.h"
#include "../../include/objects/block.h"
#include "../../include/level.h"

Enemy::Enemy(int beginX, int beginY, int endX, int endY, Coords coords) :
	Drawing(beginX, beginY, endX, endY, coords) {
	this->moveX = X_MOVE;
	this->moveY = 0;
	this->damage = DAMAGE;
}

void Enemy::step(Level* level) {
	this->position.beginX += this->moveX;
	this->position.endX += this->moveX;
	this->position.beginY += this->moveY;
	this->position.endY += this->moveY;

	this->moveY = level->getGravity()*-1;
}

void Enemy::onCollide(Drawing* object, Level* level, sides side) {
	if (Block* collide = dynamic_cast<Block*>(object))
		this->onCollide(collide, level, side);
}

void Enemy::onCollide(Block* object, Level* level, sides side) {
	float ox, oy;
	level->getOrigin(ox, oy);
	Coords obj = this->getPosition(ox, oy), thisobj = object->getPosition(ox, oy);

	if (side == LEFT) {
		this->position.beginX += obj.beginX - thisobj.endX;
		this->position.endX += obj.beginX - thisobj.endX;
	}
 	else if	(side == RIGHT) {
		this->position.beginX += obj.endX - thisobj.beginX;
		this->position.endX += obj.endX - thisobj.beginX;
	}
	else if (side == DOWN) {
		this->position.beginY += obj.beginY - thisobj.endY;
		this->position.endY += obj.beginY - thisobj.endY;
		this->moveY = 0;
	}
	else if (side == UP) {
		this->position.beginY += obj.endY - thisobj.beginY;
		this->position.endY += obj.endY - thisobj.beginY;
	}
}

#include "pancho.h"
#include "block.h"
#include "crumble_block.h"
#include "spikes_block.h"
#include "jumpthrough_block.h"
#include "../level.h"

Pancho::Pancho(int beginX, int beginY, int endX, int endY) : health(6), numHearts(3), cloak(100), cloakColor(RED), cloaks {"red", "orange", "yellow", "green", "blue", "indigo", "violet"},
	Global(beginX, beginY, endX, endY, Atlas::getCoords(COORDNAME)) {
}

void Pancho::damage(int health) {
	if (!invuln && this->health > 0) {
		setHealth(this->health-health);
		invuln++;
	}
}

void Pancho::addCoords(std::vector<float>& v, int& offset) {
	Drawing::addCoords(v, offset);

	stats.drawHealth(health, numHearts, v, offset);
	stats.drawCloak(cloaks[cloakColor], cloak, v, offset);
}

void Pancho::step(Level* level) {
	float x, y;
	level->getMove(x, y);
	level->setMove(moveX, y);

	if (invuln == INVULN_FRAMES)
		invuln = 0;
	else if (invuln > 0)
		invuln++;

	Drawing::step(level);
}

void Pancho::onKey(Level* level, int key, int action) {
	float x, y, move = 180;
	level->getMove(x, y);

	//on release
	if ((key == GLFW_KEY_RIGHT || key == GLFW_KEY_LEFT) && action == GLFW_RELEASE)
		moveX = 0.0;
	if (key == GLFW_KEY_UP && action == GLFW_RELEASE && y > 0.0)
		y = 0.0;

	//on press
	if (key == GLFW_KEY_LEFT && action > GLFW_RELEASE) {
		moveX = -move;
		level->setOrient(true);
	}
	if (key == GLFW_KEY_RIGHT && action > GLFW_RELEASE) {
		moveX = move;
		level->setOrient(false);
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		y = move*2;

	level->setMove(x, y);
}

void Pancho::onCollide(Drawing* object, Level* level, sides side) {
	if (Crumble* collide = dynamic_cast<Crumble*>(object))
		this->onCollide(collide, level, side);
	else if (Spikes* collide = dynamic_cast<Spikes*>(object))
		this->onCollide(collide, level, side);
	else if (JumpThrough* collide = dynamic_cast<JumpThrough*>(object))
		this->onCollide(collide, level, side);
	else if (Block* collide = dynamic_cast<Block*>(object))
		this->onCollide(collide, level, side);
}

void Pancho::onCollide(Block* object, Level* level, sides side) {
	float x, y, ox, oy;
	level->getMove(x, y);
	level->getOrigin(ox, oy);

	Coords obj = object->getPosition(ox, oy);
	Coords thisobj = this->getPosition(ox, oy);

	if (side == LEFT && x < 0) {
		level->setMove(0, y);
		level->shift(obj.endX - thisobj.beginX, 0);
	}
 	else if	(side == RIGHT && x > 0) {
		level->setMove(0, y);
		level->shift(obj.beginX - thisobj.endX, 0);
	}
	else if (side == DOWN && y < 0) {
		level->setMove(x, 0);
		level->shift(0, obj.endY - thisobj.beginY);
	}
	else if (side == UP && y > 0) {
		level->setMove(x, 0);
		level->shift(0, obj.beginY - thisobj.endY);
	}
}

void Pancho::onCollide(Crumble* object, Level* level, sides side) {
	float x, y, ox, oy;
	level->getMove(x, y);
	level->getOrigin(ox, oy);

	Coords obj = object->getPosition(ox, oy);
	Coords thisobj = this->getPosition(ox, oy);

	if (object->getState() != "crumbled") {
		if (side == LEFT)
			level->shift(obj.endX - thisobj.beginX, 0);
	 	else if	(side == RIGHT)
			level->shift(obj.beginX - thisobj.endX, 0);
		else if (side == DOWN && y < 0) {
			level->setMove(x, 0);
			level->shift(0, obj.endY - thisobj.beginY);
		}
		else if (side == UP)
			level->shift(0, obj.beginY - thisobj.endY);
	}
}

void Pancho::onCollide(Spikes* object, Level* level, sides side) {
	damage(1);

	onCollide((Block*) object, level, side);
}

void Pancho::onCollide(JumpThrough* object, Level* level, sides side) {
	if (side == DOWN && object->getState() != "through")
		this->onCollide((Block*) object, level, side);
}

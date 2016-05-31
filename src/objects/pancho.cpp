#include "../../include/objects/pancho.h"
#include "../../include/objects/block.h"
#include "../../include/objects/crumble_block.h"
#include "../../include/objects/spikes_block.h"
#include "../../include/objects/blob_enemy.h"
#include "../../include/objects/jumpthrough_block.h"
#include "../../include/objects/trigger_block.h"
#include "../../include/level.h"

Pancho::Pancho(int beginX, int beginY, int endX, int endY) : health(6), numHearts(3), cloak(100), cloakColor(RED), invuln(0), numJumps(1), maxJumps(1), cloaks {"red", "orange", "yellow", "green", "blue", "indigo", "violet"},
	Global(beginX, beginY, endX, endY, Atlas::getCoords(COORDNAME)) {
	this->moveX = 0;
	this->moveY = 0;

	for (int i = 0; i < NUMCLOAKS; i++) {
		std::vector<Coords> v = std::vector<Coords>(1, Atlas::getCoords(cloaks[i]));
		this->statemap[cloaks[i]] = v;
	}
}

void Pancho::decCloak() {
	if (this->cloakColor > 0)
		this->cloakColor = cloake(int(this->cloakColor)-1);
	else
		setCloakColor(cloake(NUMCLOAKS-1));

	this->state = cloaks[this->cloakColor];
}

void Pancho::incCloak() {
	if (this->cloakColor < NUMCLOAKS-1)
		this->cloakColor = cloake(int(this->cloakColor)+1);
	else
		setCloakColor(RED);

	this->state = cloaks[this->cloakColor];
}

void Pancho::damage(int health) {
	if (!invuln && this->health > 0) {
		setHealth(this->health-health);
		invuln++;
	}
}

void Pancho::addCoords(std::vector<float>& v, int& offset) {
	if (!invuln || (invuln)%10 > 5)
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

void Pancho::onKey(Level* level, key key, int action) {
	float x, y, move = 180;
	level->getMove(x, y);

	//on release
	if (key == KEY_RIGHT && action == GLFW_RELEASE && x >= 0)
		moveX = 0.0;
	if (key == KEY_LEFT && action == GLFW_RELEASE && x <= 0)
		moveX = 0.0;
	if (key == KEY_UP && action == GLFW_RELEASE) {
		moveY = 0.0;
		if (y > 0)
			y = 0.0;
	}
	if (key == KEY_DOWN && action == GLFW_RELEASE)
		moveY = 0.0;

	//on press
	if (key == KEY_LEFT && action > GLFW_RELEASE) {
		moveX = -move;
		orientation = false;
	}
	if (key == KEY_RIGHT && action > GLFW_RELEASE) {
		moveX = move;
		orientation = true;
	}
	if (key == KEY_UP && action == GLFW_PRESS) {
		if (numJumps > 0) {
			moveY = move;
			y = move*2;
			numJumps--;
		}
	}
	if (key == KEY_DOWN && action == GLFW_PRESS)
		moveY = -move;

	if (key == KEY_X && action == GLFW_PRESS)
		incCloak();
	if (key == KEY_Z && action == GLFW_PRESS)
		decCloak();
		

	level->setMove(x, y);
}

void Pancho::onCollide(Drawing* object, Level* level, sides side) {
	if (Crumble* collide = dynamic_cast<Crumble*>(object))
		this->onCollide(collide, level, side);
	else if (Spikes* collide = dynamic_cast<Spikes*>(object))
		this->onCollide(collide, level, side);
	else if (Blob* collide = dynamic_cast<Blob*>(object))
		this->onCollide(collide, level, side);
	else if (JumpThrough* collide = dynamic_cast<JumpThrough*>(object))
		this->onCollide(collide, level, side);
	else if (Ladder* collide = dynamic_cast<Ladder*>(object))
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
		numJumps = maxJumps;
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
		this->onCollide((Block*) object, level, side);

		if (side == LEFT)
			level->shift(obj.endX - thisobj.beginX, 0);
	 	else if	(side == RIGHT)
			level->shift(obj.beginX - thisobj.endX, 0);
		else if (side == DOWN && y < 0 
			&& object->getState() == "crumbling") {
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

void Pancho::onCollide(Blob* object, Level* level, sides side) {
	if (side != DOWN)
		damage(1);
	else
		onCollide((Block*) object, level, side);
}

void Pancho::onCollide(JumpThrough* object, Level* level, sides side) {
	if (side == DOWN && object->getState() != "through")
		this->onCollide((Block*) object, level, side);
}

void Pancho::onCollide(Ladder* object, Level* level, sides side) {
	float x, y;
	numJumps = maxJumps;
	level->getMove(x, y);

	level->setMove(x, moveY);
}

#include "main.hpp"
#include <math.h>

Actor::Actor(int x, int y, int ch, const char *name) : x(x), y(y), ch(ch), name(name), blocks(true), fovOnly(true), attacker(NULL), destructible(NULL),
ai(NULL), pickable(NULL), container(NULL) {}

Actor::~Actor() 
{
	if (attacker) delete attacker;
	if (destructible) delete destructible;
	if (ai) delete ai;
	if (pickable) delete pickable;
	if (container) delete container;
}

void putPic(int x, int y, int c)
{
	TCODConsole::root->putChar(x, y, c);
	TCODConsole::root->putChar(x + 1, y, c + 1);
	TCODConsole::root->putChar(x, y + 1, c + 16);
	TCODConsole::root->putChar(x + 1, y + 1, c + 17);
}

void Actor::render(int cx, int cy)
{
	putPic(x + cx, y + cy, ch);
}

void Actor::update() 
{
	if (ai) ai->update(this);
}

void Actor::save(TCODZip &zip) {
	zip.putInt(x);
	zip.putInt(y);
	zip.putInt(ch);
	zip.putString(name);
	zip.putInt(blocks);

	zip.putInt(attacker != NULL);
	zip.putInt(destructible != NULL);
	zip.putInt(ai != NULL);
	zip.putInt(pickable != NULL);
	zip.putInt(container != NULL);

	if (attacker) attacker->save(zip);
	if (destructible) destructible->save(zip);
	if (ai) ai->save(zip);
	if (pickable) pickable->save(zip);
	if (container) container->save(zip);
}

void Actor::load(TCODZip &zip) {
	x = zip.getInt();
	y = zip.getInt();
	ch = zip.getInt();
	name = _strdup(zip.getString());
	blocks = zip.getInt();

	bool hasAttacker = zip.getInt();
	bool hasDestructible = zip.getInt();
	bool hasAi = zip.getInt();
	bool hasPickable = zip.getInt();
	bool hasContainer = zip.getInt();

	if (hasAttacker) {
		attacker = new Attacker(0.0f);
		attacker->load(zip);
	}

	if (hasDestructible) {
		destructible = Destructible::create(zip);
	}

	if (hasAi) {
		ai = Ai::create(zip);
	}
	if (hasPickable) {
		pickable = Pickable::create(zip);
	}

	if (hasContainer) {
		container = new Container(0);
		container->load(zip);
	}
}

float Actor::getDistance(int cx, int cy) const
{
	int dx = x - cx;
	int dy = y - cy;
	return sqrtf(dx*dx + dy*dy);
}
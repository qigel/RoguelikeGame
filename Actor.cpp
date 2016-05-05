#include "main.hpp"

Actor::Actor(int x, int y, int ch, const char *name) : x(x), y(y), ch(ch), name(name), blocks(true), attacker(NULL), destructible(NULL), ai(NULL) {}

void putPic(int x, int y, int c)
{
	TCODConsole::root->putChar(x, y, c);
	TCODConsole::root->putChar(x + 1, y, c + 1);
	TCODConsole::root->putChar(x, y + 1, c + 16);
	TCODConsole::root->putChar(x + 1, y + 1, c + 17);
}

void Actor::render() const
{
	putPic(x, y, ch);
}

void Actor::update() 
{
	if (ai) ai->update(this);
}
#include <stdio.h>
#include "main.hpp"

Destructible::Destructible(float maxHp, float defense, const char *corpseName, int xp) : maxHp(maxHp), hp(maxHp), defense(defense),
corpseName(corpseName), xp(xp)
{
	//this->corpseName = _strdup(corpseName);
}

/*Destructible::~Destructible()
{
	free(corpseName);
}*/

float Destructible::takeDamage(Actor *owner, float damage)
{
	damage -= defense;
	if (damage > 0)
	{
		hp -= damage;
		if (hp <= 0) 
		{
			die(owner);
		}
	}
	else
	{
		damage = 0;
	}
	return damage;
}

float Destructible::heal(float amount)
{
	hp += amount;
	if (hp > maxHp)
	{
		amount -= hp - maxHp;
		hp = maxHp;
	}
	return amount;
}

void Destructible::die(Actor *owner) 
{
	// transform the actor into a corpse!
	owner->ch = 3868;
	owner->name = corpseName;
	owner->blocks = false;
	// make sure corpses are drawn before living actors
	engine.sendToBack(owner);
}

MonsterDestructible::MonsterDestructible(float maxHp, float defense, const char *corpseName, int xp) :	Destructible(maxHp, defense, corpseName, xp) {}

PlayerDestructible::PlayerDestructible(float maxHp, float defense, const char *corpseName) : Destructible(maxHp, defense, corpseName, xp) {}

void MonsterDestructible::die(Actor *owner)
{
	// transform it into a nasty corpse! it doesn't block, can't be
	// attacked and doesn't move
	engine.gui->message(TCODColor::lightGrey, "%s �����. �� ��������� %d �����", owner->name, xp);
	engine.player->destructible->xp += xp;
	Destructible::die(owner);
}

void PlayerDestructible::die(Actor *owner)
{
	engine.gui->message(TCODColor::red, "�� �������, ��� � �� ��������� ����� ����...");
	Destructible::die(owner);
	engine.gameStatus = Engine::DEFEAT;
}

Destructible *Destructible::create(TCODZip &zip)
{
	DestructibleType type = (DestructibleType)zip.getInt();
	Destructible *destructible = NULL;
	switch (type) 
	{
		case MONSTER: destructible = new MonsterDestructible(0, 0, NULL, 0); break;
		case PLAYER: destructible = new PlayerDestructible(0, 0, NULL); break;
	}
	destructible->load(zip);
	return destructible;
}
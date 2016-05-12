#include <stdio.h>
#include "main.hpp"

Attacker::Attacker(float power, float intell) : power(power), intell(intell){}

void Attacker::attack(Actor *owner, Actor *target) 
{
	if (target->destructible && !target->destructible->isDead())
	{
		if (power - target->destructible->defense > 0) 
		{
			engine.gui->message(owner == engine.player ? TCODColor::red : TCODColor::lightGrey,
				"%s ���� %s � ������� %g �����.", owner->name, target->name,
				power - target->destructible->defense);
		}
		else
		{
			engine.gui->message(TCODColor::lightGrey, "%s ���� %s, �� ��������������!", owner->name, target->name);
		}
		target->destructible->takeDamage(target, power);
	}
	else 
	{
		engine.gui->message(TCODColor::lightGrey, "%s ���� %s ��� ������.", owner->name, target->name);
	}
}
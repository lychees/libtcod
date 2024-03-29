#include <stdio.h>
#include "main.hpp"

Destructible::Destructible(float maxHp, float defense, const char *corpseName) :
	maxHp(maxHp),hp(maxHp),defense(defense),corpseName(corpseName) {
}

float Destructible::takeDamage(Actor *owner, float damage) {
	damage -= defense;
	if ( damage > 0 ) {
		hp -= damage;
		if ( hp <= 0 ) {
			die(owner);
		}
	} else {
		damage=0;
	}
	return damage;
}

void Destructible::die(Actor *owner) {
	// transform the actor into a corpse!
	owner->ch='%';
	owner->col=TCODColor::darkRed;	
	owner->name=corpseName;
	owner->blocks=false;
	// make sure corpses are drawn before living actors
	engine.sendToBack(owner);
}

MonsterDestructible::MonsterDestructible(float maxHp, float defense, const char *corpseName) :
	Destructible(maxHp,defense,corpseName) {
}

void MonsterDestructible::die(Actor *owner) {
	// transform it into a nasty corpse! it doesn't block, can't be
	// attacked and doesn't move
	printf ("%s is dead\n",owner->name);
	Destructible::die(owner);
}

PlayerDestructible::PlayerDestructible(float maxHp, float defense, const char *corpseName) :
	Destructible(maxHp,defense,corpseName) {
}

void PlayerDestructible::die(Actor *owner) {
	printf ("You died!\n");
	Destructible::die(owner);
	engine.gameStatus=Engine::DEFEAT;
}

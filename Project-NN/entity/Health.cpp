#include "Health.h"
#include "GameObject.h"

Health::Health(int hp) {
	this->hp = hp;
}

void Health::Damage(int hp) {
	this->hp -= hp;
	this->hp = this->hp < 0 ? 0 : this->hp;
}

void Health::setHealth(int hp)
{
	this->hp = hp;
}

void Health::Heal(int hp) {
	this->hp += hp;
}

bool Health::IsAlive() {
	return this->hp > 0;
}

void Health::HandleCollision(GameObject* other) 
{
	hp -= other->damage;
}
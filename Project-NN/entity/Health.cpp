#include "Health.h"

Health::Health(int hp) {
	this->hp = hp;
}

void Health::Damage(int hp) {
	this->hp -= hp;
	this->hp = this->hp < 0 ? 0 : this->hp;
}

void Health::Heal(int hp) {
	this->hp += hp;
}

bool Health::IsAlive() {
	return this->hp > 0;
}
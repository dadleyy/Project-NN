#include "Pause.h"

#include "entity/GameObject.h"
#include "StateManager.h"

Pause Pause::instance;

void Pause::Init(StateManager* manager) {
	GameState::Init(manager);
}

void Pause::Cleanup() {
}

void Pause::Update(float dt) {
	//TODO: Pause updating
}

void Pause::Draw() {
	//TODO: Pause updating
}
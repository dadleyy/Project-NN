#include "Instructions.h"

#include "entity/GameObject.h"
#include "StateManager.h"

Instructions Instructions::instance;

void Instructions::Init(StateManager* manager) {
	GameState::Init(manager);
}

void Instructions::Cleanup() {
}

void Instructions::Update(float dt) {
	//TODO: Pause updating
}

void Instructions::Draw() {
	//TODO: Pause updating
}
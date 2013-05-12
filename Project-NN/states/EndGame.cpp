#include "EndGame.h"

#include "entity/GameObject.h"
#include "StateManager.h"

EndGame EndGame::instance;

void EndGame::Init(StateManager* manager) {
	GameState::Init(manager);
}

void EndGame::Cleanup() {
}

void EndGame::Update(float dt) {
	//TODO: Pause updating
}

void EndGame::Draw() {
	//TODO: Pause updating
}
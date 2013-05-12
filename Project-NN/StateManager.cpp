#include "StateManager.h"

#include "GameState.h"


StateManager::StateManager(void) : states() {
}


StateManager::~StateManager(void) {
}


void StateManager::Init() {
}

void StateManager::Update(float dt) {
	states[states.size() - 1]->Update(dt);
}

void StateManager::Draw() {
	//TODO: Add ability to have transparent states.
	states[states.size() - 1]->Draw();
}

void StateManager::ChangeState(GameState* state) {
	//TODO: Error out
	if(state->IsSubState())
		return;
	for(auto it = states.rbegin(); it != states.rend(); ++it)
		(*it)->Cleanup();
	states.clear();
	states.push_back(state);
	state->Init(this);
}

void StateManager::PushState(GameState* state) {
	if(!state->IsSubState())
		return;
	states.push_back(state);
	state->Init(this);
}

void StateManager::PopState() {
	states[states.size() - 1]->Cleanup();
	states.pop_back();
}
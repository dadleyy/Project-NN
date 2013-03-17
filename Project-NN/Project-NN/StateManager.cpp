#include "StateManager.h"
#include "GameState.h"


StateManager::StateManager(void) : states()
{
}


StateManager::~StateManager(void)
{
}


void StateManager::Update(float dt)
{
	states[states.size() - 1]->Update(dt);
}

void StateManager::Draw()
{
	//TODO: Add ability to have transparent states.
	states[states.size() - 1]->Draw();
}

void StateManager::PushState(GameState* state)
{
	state->Init();
	states.push_back(state);
}

void StateManager::PopState()
{
	states[states.size() - 1]->Cleanup();
	states.pop_back();
}
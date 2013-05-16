#include "StateManager.h"
#include "GameState.h"
#include "states/Credits.h"
#include "states/Gameplay.h"
#include "states/Instructions.h"
#include "states/MainMenu.h"
#include <iostream>
#include <assert.h>


int StateManager::ToCredits( StateManager* manager )
{
	manager->ChangeState( Credits::Instance( ) );
	return 1;
}

int StateManager::ToGamePlay( StateManager* manager )
{
	manager->ChangeState( Gameplay::Instance( ) );
	return 1;
}

int StateManager::ToMainMenu( StateManager* manager )
{
	manager->ChangeState( MainMenu::Instance( ) );
	return 1;
}

int StateManager::ToInstructions( StateManager* manager )
{
	manager->ChangeState( Instructions::Instance( ) );
	return 1;
}

int StateManager::Blank( StateManager* manager ){ return 1; }


StateManager::StateManager(void) : states(), wait_time(0.0f) {
}


StateManager::~StateManager(void) {
}


void StateManager::Init(GameState* state) {
	states.push_back(state);
	state->Init(this);
	preparedStateOperation = nullptr;
}

void StateManager::Update(float dt) {
	wait_time = wait_time - dt;
	if( wait_time < 0.0f )
		wait_time = 0.0f;

	assert(states.size() > 0);
	states[states.size() - 1]->Update(dt);
	if(preparedStateOperation != nullptr) {
		preparedStateOperation();
		preparedStateOperation = nullptr;
	}
}

void StateManager::Draw() {
	for(auto it = states.begin(); it != states.end(); ++it)
		(*it)->Draw();
}

void StateManager::ChangeState(GameState* state) {
	if( wait_time > 0.0f )
		return;

	wait_time = 1.0f;
	if(state->IsSubState())
		return;
	assert(preparedStateOperation == nullptr);
	preparedStateOperation = [this, state]() {
		for(auto it = states.rbegin(); it != states.rend(); ++it)
			(*it)->Cleanup();
		states.clear();
		states.push_back(state);
		state->Init(this);
	};
}

void StateManager::PushState(GameState* state) {
	if(!state->IsSubState())
		return;
	assert(preparedStateOperation == nullptr);
	preparedStateOperation = [this, state]() {
		states.push_back(state);
		state->Init(this);
	};
}

void StateManager::PopState() {
	assert(preparedStateOperation == nullptr);
	preparedStateOperation = [this]() {
		assert(states.size() > 0);
		states[states.size() - 1]->Cleanup();
		states.pop_back();
	};
}
#include "StateManager.h"
#include "GameState.h"
#include "states/Gameplay.h"
#include "states/Credits.h"
#include "states/MainMenu.h"
#include <iostream>

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

int StateManager::Blank( StateManager* manager ){ return 1; }


StateManager::StateManager(void) : states(), wait_time(0.0f) {
}


StateManager::~StateManager(void) {
}


void StateManager::Init() {
}

void StateManager::Update(float dt) {
	wait_time = wait_time - dt;
	if( wait_time < 0.0f )
		wait_time = 0.0f;

	states[states.size() - 1]->Update(dt);
}

void StateManager::Draw() {
	//TODO: Add ability to have transparent states.
	states[states.size() - 1]->Draw();
}

void StateManager::ChangeState(GameState* state) {
	if( wait_time > 0.0f )
		return;

	wait_time = 1.0f;
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
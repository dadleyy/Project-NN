#include "StateManager.h"
#include "GameState.h"


StateManager::StateManager(void) : states()
{
}


StateManager::~StateManager(void)
{

}


void StateManager::Init(ID3D11Device* device, ID3D11DeviceContext* context)
{
	this->device = device;
	this->context = context;

    for( int i = 0; i < 256; i++ ){
        keystates[i] = false;
    }
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
	state->Init(this);
	states.push_back(state);
}

void StateManager::PopState()
{
	states[states.size() - 1]->Cleanup();
	states.pop_back();
}

ID3D11Device* StateManager::GetDevice()
{
	return device;
}

ID3D11DeviceContext* StateManager::GetContext()
{
	return context;
}
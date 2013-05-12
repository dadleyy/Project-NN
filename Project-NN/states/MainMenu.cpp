#include "MainMenu.h"

#include "entity/GameObject.h"
#include "Gameplay.h"
#include "SceneManager.h"
#include "StateManager.h"

MainMenu MainMenu::instance;

void MainMenu::Init(StateManager* manager) {
	GameState::Init(manager);
	//For now, we pass through to Gameplay
	manager->ChangeState(Gameplay::Instance());
}

void MainMenu::Cleanup() {
}

void MainMenu::Update(float dt) {
	for(auto it = sceneMgr->Begin(); it != sceneMgr->End(); ++it) {
		if(!(*it)->active)
			continue;
		(*it)->Update(dt);
	}
}

void MainMenu::Draw() {
}
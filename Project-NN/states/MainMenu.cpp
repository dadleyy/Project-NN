#include "MainMenu.h"

#include "entity/GameObject.h"
#include "SceneManager.h"

MainMenu MainMenu::instance;

void MainMenu::Init(StateManager* manager) {
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
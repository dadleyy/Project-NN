#include "MainMenu.h"

#include "entity/GameObject.h"
#include "entity/MenuItem.h"
#include "Gameplay.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "StateManager.h"

MainMenu MainMenu::instance;

void MainMenu::Init(StateManager* manager) {
	GameState::Init(manager);
	
	playbutton = new MenuItem( manager );
}

void MainMenu::Cleanup() {
}

void MainMenu::Update(float dt) {
	playbutton->Update( dt );
}

void MainMenu::Draw() 
{
	playbutton->Draw( );
}
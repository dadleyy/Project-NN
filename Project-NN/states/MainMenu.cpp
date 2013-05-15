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

	MenuItemDescription playbtn;
	playbtn.width = 0.5f;
	playbtn.height = 0.5f;
	playbtn.position = XMFLOAT2( 0.0f, 0.0f );
	
	playbutton = new MenuItem( manager, &playbtn );
}

void MainMenu::Cleanup() {
}

void MainMenu::Update(float dt) {
	resourceMgr->camera.UpdateViewMatrix( );

	playbutton->Update( dt );

	resourceMgr->updateCameraBuffer( );
}

void MainMenu::Draw() 
{
	playbutton->Draw( );
}
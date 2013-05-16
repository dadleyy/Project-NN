#include "Instructions.h"

#include "entity/GameObject.h"
#include "entity/MenuItem.h"
#include "StateManager.h"

Instructions Instructions::instance;

void Instructions::Init(StateManager* manager) {
	GameState::Init(manager);

	MenuItemDescription background;
	background.width = 800.0f;
	background.height = 600.0f;
	background.function = StateManager::Blank;
	background.texture = "menuBG";
	background.position = XMFLOAT2( 400.0f, 300.0f );

	MenuItemDescription backBtn;
	backBtn.width = 800.0f;
	backBtn.height = 600.0f;
	backBtn.function = StateManager::ToMainMenu;
	backBtn.texture = "backBtn";
	backBtn.position = XMFLOAT2( 400.0f, 300.0f );

	buttons.push_back(new MenuItem(manager, background));
	buttons.push_back(new MenuItem(manager, backBtn));
}

void Instructions::Cleanup() {
	//TODO: Clean up buttons.
}

void Instructions::Update(float dt) {
	//TODO: Instructions updating
}

void Instructions::Draw() {
	//TODO: Instructions updating
}
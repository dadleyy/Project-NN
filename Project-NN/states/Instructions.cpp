#include "Instructions.h"

#include "entity/GameObject.h"
#include "entity/MenuItem.h"
#include "ResourceManager.h"
#include "StateManager.h"

Instructions Instructions::instance;

void Instructions::Init(StateManager* manager) {
	GameState::Init(manager);

	MenuItemDescription bgDesc;
	bgDesc.width = 800.0f;
	bgDesc.height = 600.0f;
	bgDesc.function = StateManager::Blank;
	bgDesc.texture = "menuBG";
	bgDesc.style = MENU_STATIC;
	bgDesc.position = XMFLOAT2( 400.0f, 300.0f );

	MenuItemDescription backBtn;
	backBtn.width = 170.0f;
	backBtn.height = 50.0f;
	backBtn.function = StateManager::ToMainMenu;
	backBtn.texture = "backBtn";
	backBtn.style = MENU_BUTTON;
	backBtn.position = XMFLOAT2( 125.0f, 320.0f );

	buttons.push_back(new MenuItem(manager, background));
	buttons.push_back(new MenuItem(manager, backBtn));
}

void Instructions::Cleanup() {
	for(auto it = buttons.begin(); it != buttons.end(); ++it) {
		delete *it;
	}
	buttons.clear();
}

void Instructions::Update(float dt) {
	for( auto it = buttons.begin(); it != buttons.end(); ++it ){
		(*it)->Update( dt );
	}
}

void Instructions::Draw() {
	ID3DX11EffectVectorVariable* dims = resourceMgr->effects.at("menuEffect")->effect->GetVariableByName("screenDimensions")->AsVector( );
	float screen_dimensions[2] = { screenWidth, screenHeight };
	dims->SetFloatVector( screen_dimensions );

	for( auto it = buttons.begin(); it != buttons.end(); ++it ){
		(*it)->Draw( );
	}
}
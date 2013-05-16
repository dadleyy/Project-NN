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
	bgDesc.texture = "instructionsBG";
	bgDesc.style = MENU_STATIC;
	bgDesc.position = XMFLOAT2( 400.0f, 300.0f );

	MenuItemDescription backBtnDesc;
	backBtnDesc.width = 170.0f;
	backBtnDesc.height = 50.0f;
	backBtnDesc.function = StateManager::ToMainMenu;
	backBtnDesc.texture = "backBtn";
	backBtnDesc.style = MENU_BUTTON;
	backBtnDesc.position = XMFLOAT2( 125.0f, 320.0f );

	background = new MenuItem(manager, bgDesc);
	backBtn = new MenuItem(manager, backBtnDesc);
}

void Instructions::Cleanup() {
	delete background;
	delete backBtn;
}

void Instructions::Update(float dt) {
	backBtn->Update(dt);
}

void Instructions::Draw() {
	ID3DX11EffectVectorVariable* dims = resourceMgr->effects.at("menuEffect")->effect->GetVariableByName("screenDimensions")->AsVector( );
	float screen_dimensions[2] = { screenWidth, screenHeight };
	dims->SetFloatVector( screen_dimensions );

	background->Draw();
	backBtn->Draw();
}
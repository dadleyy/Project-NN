#include "Credits.h"

#include "entity/GameObject.h"
#include "entity/MenuItem.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "StateManager.h"

Credits Credits::credits_instace;

void Credits::Init(StateManager* manager)
{
	GameState::Init(manager);

	MenuItemDescription backbtn;
	backbtn.width = 170.0f;
	backbtn.height = 50.0f;
	backbtn.function = StateManager::ToMainMenu;
	backbtn.texture = "backBtn";
	backbtn.style = MENU_BUTTON;
	backbtn.position = XMFLOAT2( 125.0f, 320.0f );

	MenuItemDescription creditbg;
	creditbg.width = 800.0f;
	creditbg.height = 600.0f;
	creditbg.function = StateManager::Blank;
	creditbg.style = MENU_STATIC;
	creditbg.texture = "creditsBG";
	creditbg.position = XMFLOAT2( 400.0f, 300.0f );

	statics.push_back( new MenuItem( manager, creditbg ) );
	buttons.push_back( new MenuItem( manager, backbtn ) );

}

void Credits::Cleanup() 
{

}

void Credits::Update(float dt) 
{
	for( auto it = buttons.begin(); it != buttons.end(); ++it ){
		(*it)->Update( dt );
	}
}

void Credits::Draw() 
{
	ID3DX11EffectVectorVariable* dims = resourceMgr->effects.at("menuEffect")->effect->GetVariableByName("screenDimensions")->AsVector( );
	float screen_dimensions[2] = { screenWidth, screenHeight };
	dims->SetFloatVector( screen_dimensions );

	for( auto it = statics.begin(); it != statics.end(); ++it ){
		(*it)->Draw( );
	}

	for( auto it = buttons.begin(); it != buttons.end(); ++it ){
		(*it)->Draw( );
	}

}
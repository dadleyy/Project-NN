#include "MainMenu.h"

#include "entity/GameObject.h"
#include "entity/MenuItem.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "StateManager.h"

MainMenu MainMenu::mainmenu_instance;

void MainMenu::Init(StateManager* manager)
{
	GameState::Init(manager);

	MenuItemDescription playbtn;
	playbtn.width = 170.0f;
	playbtn.height = 50.0f;
	playbtn.function = StateManager::ToGamePlay;
	playbtn.texture = "playBtn";
	playbtn.position = XMFLOAT2( 125.0f, 320.0f );

	MenuItemDescription creditbtn;
	creditbtn.width = 170.0f;
	creditbtn.height = 50.0f;
	creditbtn.function = StateManager::ToCredits;
	creditbtn.texture = "creditBtn";
	creditbtn.position = XMFLOAT2( 125.0f, 390.0f );

	MenuItemDescription instructionsBtn;
	instructionsBtn.width = 170.0f;
	instructionsBtn.height = 50.0f;
	instructionsBtn.function = StateManager::Blank;
	instructionsBtn.texture = "creditBtn";
	instructionsBtn.position = XMFLOAT2( 125.0f, 460.0f );

	MenuItemDescription menubg;
	menubg.width = 800.0f;
	menubg.height = 600.0f;
	menubg.function = StateManager::Blank;
	menubg.texture = "menuBG";
	menubg.position = XMFLOAT2( 400.0f, 300.0f );

	menuBG = new MenuItem( manager, menubg );
	buttons.push_back( new MenuItem( manager, playbtn ) );
	buttons.push_back( new MenuItem( manager, creditbtn ) );
	buttons.push_back( new MenuItem( manager, instructionsBtn ) );
}

void MainMenu::Cleanup() 
{
	for(auto it = buttons.begin(); it != buttons.end(); ++it) {
		delete *it;
	}
	buttons.clear();
}

void MainMenu::Update(float dt) 
{
	for( auto it = buttons.begin(); it != buttons.end(); ++it ){
		(*it)->Update( dt );
	}
}

void MainMenu::Draw() 
{
	ID3DX11EffectVectorVariable* dims = resourceMgr->effects.at("menuEffect")->effect->GetVariableByName("screenDimensions")->AsVector( );
	float screen_dimensions[2] = { screenWidth, screenHeight };
	dims->SetFloatVector( screen_dimensions );

	menuBG->Draw( );
	for( auto it = buttons.begin(); it != buttons.end(); ++it ){
		(*it)->Draw( );
	}
}
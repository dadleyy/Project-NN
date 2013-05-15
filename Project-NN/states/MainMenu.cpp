#include "MainMenu.h"

#include "entity/GameObject.h"
#include "entity/MenuItem.h"
#include "Gameplay.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "StateManager.h"

MainMenu MainMenu::instance;

namespace MenuFunctions {
	HRESULT ToGamePlay( StateManager* manager ){
		manager->ChangeState( Gameplay::Instance( ) );
		return S_OK;
	};
}

void MainMenu::Init(StateManager* manager)
{
	GameState::Init(manager);

	MenuItemDescription playbtn;
	playbtn.width = 500.0f;
	playbtn.height = 200.0f;
	playbtn.function = MenuFunctions::ToGamePlay;
	playbtn.texture = "playbtn";
	playbtn.position = XMFLOAT2( 400.0f, 300.0f );

	playbutton = new MenuItem( manager, playbtn );
}

void MainMenu::Cleanup() 
{

}

void MainMenu::Update(float dt) 
{
	playbutton->Update( dt );
}

void MainMenu::Draw() 
{
	ID3DX11EffectVectorVariable* dims = resourceMgr->effects.at("menuEffect")->effect->GetVariableByName("screenDimensions")->AsVector( );
	float screen_dimensions[2] = { screenWidth, screenHeight };
	dims->SetFloatVector( screen_dimensions );

	playbutton->Draw( );
}
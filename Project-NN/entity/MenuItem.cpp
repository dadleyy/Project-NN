#include "MenuItem.h"

#include "MenuDrawable.h"
#include "Transform.h"
#include "MenuControlComponent.h"
#include "input.h"

MenuItem::MenuItem( StateManager* _manager, MenuItemDescription* description ) : triggered(false)
{
	manager = _manager;

	transform = new Transform( );
	drawable = new MenuDrawable( );
	control = new MenuComponent( this );

	transform->position = XMFLOAT3( description->position.x, description->position.y, 0.0f );
	transform->scale = XMFLOAT3( 1.0f, 1.0f, 1.0f );

	drawable->getEffectVariables("menuEffect","Render");
	drawable->setShader("menuEffect","Render");
	drawable->createBuffer( description );
	drawable->addTexture("playbtn", "buttonTexture");

	components.push_back( transform );
	components.push_back( drawable );
	components.push_back( control );

	GameObject::InitComponents( );
}

void MenuItem::Trigger()
{
	if( !triggered )
		manager->ChangeState( Gameplay::Instance() );

	triggered = true;
}

void MenuItem::Draw( )
{
	drawable->setShader("menuEffect","Render");
	drawable->setEffectTextures();
	drawable->draw( );
}

MenuItem::~MenuItem( ){ }
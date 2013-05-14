#include "MenuItem.h"

#include "MenuDrawable.h"
#include "Transform.h"
#include "MenuControlComponent.h"

MenuItem::MenuItem( StateManager* _manager ) : triggered(false)
{
	manager = _manager;

	transform = new Transform( );
	drawable = new MenuDrawable( );
	control = new MenuComponent( this );

	transform->position = XMFLOAT3( 0.0f, 0.0f, 0.0f );

	drawable->getEffectVariables("menueffect","Render");
	drawable->setShader("menueffect","Render");
	drawable->createBuffer("whoa");

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
	drawable->setShader("menueffect","Render");
	drawable->draw();
}

MenuItem::~MenuItem( ){ }
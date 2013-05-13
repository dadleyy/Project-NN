#include "MenuItem.h"

#include "Drawable.h"
#include "Transform.h"
#include "MenuControlComponent.h"

MenuItem::MenuItem( StateManager* _manager ) : triggered(false)
{
	transform = new Transform( );
	drawable = new Drawable( );
	control = new MenuComponent( this );

	manager = _manager;

	triggered = false;
	components.push_back( transform );
	components.push_back( drawable );
	components.push_back( control );
}

void MenuItem::Trigger()
{
	if( !triggered )
		manager->ChangeState( Gameplay::Instance() );

	triggered = true;
}

void MenuItem::Draw( )
{

}

MenuItem::~MenuItem( ){ }
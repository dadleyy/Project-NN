#include "MenuItem.h"

#include "UIDrawable.h"
#include "Transform.h"
#include "MenuControlComponent.h"
#include "input.h"

MenuItem::MenuItem( StateManager* _manager, UIElementDescription description ) : triggered(false)
{
	manager = _manager;
	this->description = description;

	transform = new Transform( );
	drawable = new UIDrawable( );
	control = new MenuComponent( );

	transform->position = XMFLOAT3( 0.0f, 0.0f, 1.0f );
	transform->scale = XMFLOAT3( 1.0f, 1.0f, 1.0f );

	drawable->getEffectVariables("menuEffect","Render");
	drawable->setShader("menuEffect","Render");
	drawable->createBuffer( description );
	drawable->addTexture( description.texture, "itemTexture");

	components.push_back( transform );
	components.push_back( drawable );
	components.push_back( control );

	GameObject::InitComponents( );
}

void MenuItem::Trigger()
{
	description.function(manager);
}

void MenuItem::Draw( )
{
	drawable->setShader("menuEffect","Render");
	drawable->setEffectTextures( );
	drawable->draw( );
}

MenuItem::~MenuItem( )
{

}
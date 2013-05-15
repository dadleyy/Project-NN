#include "MenuControlComponent.h"
#include "GameObject.h"
#include "MenuItem.h"
#include "Transform.h"
#include "input.h"

MenuComponent::MenuComponent( ) : item(0), is_hovered(false), hover_time(0.0f) { }

bool MenuComponent::Init(GameObject* go){
	item = static_cast<MenuItem*>( go );
	transform = go->GetComponent<Transform>( );
	return true;
}

void MenuComponent::Update( float dt ){
	if( input->getLMouseButton() && hover_time != 0.0f )
		item->Trigger( );
	
	float mx = input->getMouseX(),
		  my = input->getMouseY(),
		  hw = item->GetWidth( ) * 0.5,
		  hh = item->GetHeight( ) * 0.5,
		  min_x = item->GetPosition().x - hw,
		  max_x = item->GetPosition().x + hw,
		  min_y = item->GetPosition().y - hh,
		  max_y = item->GetPosition().y + hh;

	if( mx < max_x && mx > min_x && my < max_y && my > min_y )
		hover_time = ( hover_time + dt > 100.0f ) ? 0.01f : hover_time + dt;
	else
		hover_time = 0.0f;

}


MenuComponent::~MenuComponent( ){ }
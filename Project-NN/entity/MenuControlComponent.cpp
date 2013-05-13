#include "MenuControlComponent.h"
#include "GameObject.h"
#include "MenuItem.h"
#include "input.h"

MenuComponent::MenuComponent( MenuItem* _item ) : item(0) {
	item = _item;
}

bool MenuComponent::Init(GameObject* go){
	return true;
}

void MenuComponent::Update( float dt ){
	if( input->getLMouseButton() ){
		if( item != 0 )
			item->Trigger( );
	}
}


MenuComponent::~MenuComponent( ){ }
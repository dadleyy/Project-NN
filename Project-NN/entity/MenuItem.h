#pragma once

#include <iostream>
#include "../states/Gameplay.h"
#include "GameObject.h"
#include "StateManager.h"

class Transform;
class MenuDrawable;
class MenuComponent;

struct MenuItemBuffer {
	float width;
	float height;
	XMFLOAT2 position;
};

// this describes menu items
struct MenuItemDescription
{
	float width;
	float height;
	XMFLOAT2 position;
	char* texture;
	HRESULT (*function)( StateManager* manager );
};


class MenuItem : public GameObject {

public:
	MenuItem( StateManager* _manager, MenuItemDescription description );
	~MenuItem( 	);
	void Draw( );
	void Trigger( );

	float GetWidth( ) { return this->description.width; };
	float GetHeight( ) { return this->description.height; };
	XMFLOAT2 GetPosition( ) { return this->description.position; }
	
private:
	Transform* transform;
	MenuComponent* control;
	MenuDrawable* drawable;
	StateManager* manager;
	MenuItemDescription description;

	bool triggered;

};
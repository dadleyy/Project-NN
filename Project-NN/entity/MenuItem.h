#pragma once

#include <iostream>
#include "../states/Gameplay.h"
#include "GameObject.h"
#include "StateManager.h"

class Transform;
class MenuDrawable;
class MenuComponent;

// this describes menu items
struct MenuItemDescription
{
	float width;
	float height;
	XMFLOAT2 position;
};


class MenuItem : public GameObject {

public:
	MenuItem( StateManager* _manager, MenuItemDescription* description );
	~MenuItem( 	);
	void Draw( );
	void Trigger( );

private:
	Transform* transform;
	MenuComponent* control;
	MenuDrawable* drawable;
	StateManager* manager;

	bool triggered;

};
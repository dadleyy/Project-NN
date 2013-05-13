#pragma once

#include <iostream>
#include "../states/Gameplay.h"
#include "GameObject.h"
#include "StateManager.h"

class Transform;
class MenuDrawable;
class MenuComponent;

class MenuItem : public GameObject {

public:
	MenuItem( StateManager* _manager );
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
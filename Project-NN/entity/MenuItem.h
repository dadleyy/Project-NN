#pragma once

#include <iostream>
#include "../states/Gameplay.h"
#include "GameObject.h"
#include "StateManager.h"

class Transform;
class Drawable;
class MenuComponent;

class MenuItem : public GameObject {

public:
	MenuItem( StateManager* _manager );
	~MenuItem( 	);
	void Draw( );
	void Trigger( );

private:
	Drawable* drawable;
	Transform* transform;
	MenuComponent* control;
	StateManager* manager;

	bool triggered;

};
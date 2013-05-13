#pragma once

#include <iostream>
#include "entity/Component.h"

class GameObject;
class MenuItem;

class MenuComponent : public Component {

public:

	MenuComponent( MenuItem* _item );
	~MenuComponent(  );
	bool Init(GameObject* go);
	void Update( float dt );

private:
	
	MenuItem* item;

};

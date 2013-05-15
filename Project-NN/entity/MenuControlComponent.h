#pragma once

#include <iostream>
#include "ResourceManager.h"
#include "entity/Component.h"

class GameObject;
class MenuItem;
class Transform;
struct MenuItemDescription;

class MenuComponent : public Component {

public:

	MenuComponent( );
	~MenuComponent(  );
	bool Init(GameObject* go);
	void Update( float dt );

private:

	MenuItem* item;
	Transform* transform;
	bool is_hovered;
	float hover_time;

};

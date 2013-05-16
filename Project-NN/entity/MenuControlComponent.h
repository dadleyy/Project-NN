#pragma once

#define HOVER_SPEED 2.0f
#define HOVER_AGE_CAP 3.14f
#define HOVER_AGE_MIN 0.01f

#include <iostream>
#include "ResourceManager.h"
#include "entity/Component.h"

class GameObject;
class MenuItem;
class Transform;
struct UIElementDescription;

class MenuComponent : public Component {

public:

	MenuComponent( );
	~MenuComponent(  );
	bool Init(GameObject* go);
	void Update( float dt );
	float getHoverAge( ) {
		return hover_time;
	};

private:

	MenuItem* item;
	Transform* transform;
	bool is_hovered;
	float hover_time;

};

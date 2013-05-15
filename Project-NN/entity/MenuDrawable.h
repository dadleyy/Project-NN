#pragma once

#include <iostream>
#include "Drawable.h"

class Transform;
struct MenuItemDescription;

class MenuDrawable : public Drawable {

public:

	MenuDrawable( );
	void createBuffer( MenuItemDescription* desc );
	void draw( );
	bool Init( GameObject* go );

private:		
	MenuItemDescription* description;
	Transform* transform;
};
#pragma once

#include <iostream>
#include "Drawable.h"

struct MenuItemDescription;

class MenuDrawable : public Drawable {

public:

	MenuDrawable( );
	void createBuffer( MenuItemDescription* desc );
	void draw( );

private:		
	MenuItemDescription* description;
};
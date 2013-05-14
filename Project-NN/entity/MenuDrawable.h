#pragma once

#include <iostream>
#include "Drawable.h"

struct MenuItemDescription;

class MenuDrawable : public Drawable {

public:

	MenuDrawable( );
	void createBuffer( MenuItemDescription* desc );
	void draw( );
	void getEffectVariables(char* effectID, char* techniqueName);
	void setShader(char* effectName, char* techniqueName );

private:		
	MenuItemDescription* description;
};
#pragma once

#include <iostream>
#include "Drawable.h"

struct MenuStruct {
	float width, height;
	XMFLOAT2 position;
};

class MenuDrawable : public Drawable {

public:

	MenuDrawable( );

	void createBuffer(char* param);

};
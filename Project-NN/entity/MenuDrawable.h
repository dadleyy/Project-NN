#pragma once

#include <iostream>
#include "Drawable.h"

struct MenuStruct
{
	float width;
	float height;
	XMFLOAT2 pos;
};

class MenuDrawable : public Drawable {

public:

	MenuDrawable( );
	void createBuffer(char* param);
	void draw( );

private:	

	std::vector<MenuStruct> menudata;
};
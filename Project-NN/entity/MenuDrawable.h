#pragma once

#include <iostream>
#include "Drawable.h"

class Transform;
class MenuComponent;
struct MenuItemDescription;

class MenuDrawable : public Drawable {

public:

	MenuDrawable( );
	void createBuffer( MenuItemDescription desc );
	void draw( );
	bool Init( GameObject* go );

private:

	Transform* transform;
	MenuComponent* control;
	ID3DX11EffectScalarVariable* ageVar;
	int debug_count;

};
#pragma once

#include <iostream>
#include "Drawable.h"

class Transform;
class MenuComponent;
struct UIElementDescription;

class UIDrawable : public Drawable {

public:

	UIDrawable( );
	void createBuffer( UIElementDescription desc );
	void draw( );
	bool Init( GameObject* go );

private:

	Transform* transform;
	MenuComponent* control;
	ID3DX11EffectScalarVariable* ageVar;
	int debug_count;

};
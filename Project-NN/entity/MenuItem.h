#pragma once

#include <iostream>
#include "GameObject.h"
#include "StateManager.h"

class Transform;
class UIDrawable;
class MenuComponent;

enum MENU_ITEM_STYLE {
	MENU_STATIC = 0,
	MENU_BUTTON = 1
};

struct UIElementBuffer {
	float width;
	float height;
	XMFLOAT2 position;
};

// this describes menu items
struct UIElementDescription
{
	float width;
	float height;
	XMFLOAT2 position;
	char* texture;
	MENU_ITEM_STYLE style;
	int (*function)( StateManager* manager );
};


class MenuItem : public GameObject {

public:
	MenuItem( StateManager* _manager, UIElementDescription description );
	~MenuItem( );
	void Draw( );
	void Trigger( );

	float GetWidth( ) { return this->description.width; };
	float GetHeight( ) { return this->description.height; };
	XMFLOAT2 GetPosition( ) { return this->description.position; }
	
private:
	Transform* transform;
	MenuComponent* control;
	UIDrawable* drawable;
	StateManager* manager;
	UIElementDescription description;

	bool triggered;

};
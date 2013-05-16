//
//input.cpp
//

#include "input.h"
#include <iostream>


//constructor
Input::Input() {
	// clear key down array
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		keysDown[i] = false;
	// clear key pressed array
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		keysPressed[i] = false;

	// mouse data
	mouseX = 0;                         // screen X
	mouseY = 0;                         // screen Y
	mouseLButton = false;               // true if left mouse button is down
	mouseMButton = false;               // true if middle mouse button is down
	mouseRButton = false;               // true if right mouse button is down
	mouseCaptured = false;
}

//destructor
Input::~Input() {
	if(mouseCaptured)
		ReleaseCapture();               // release mouse
}


void Input::OnMouseDown(WPARAM btnState, UINT btn, int x, int y) {
	//manager->OnMouseDown(x, y);
	if(btn == inputNS::L_BTN) {
		mouseLButton = true;
	} else if(btn == inputNS::M_BTN) {
		mouseMButton = true;
	} else {
		mouseRButton = true;
	}
}
void Input::OnMouseUp(WPARAM btnState, UINT btn, int x, int y) {
	//manager->OnMouseUp(x, y);
	if(btn == inputNS::L_BTN) {
		mouseLButton = false;
	} else if(btn == inputNS::M_BTN) {
		mouseMButton = false;
	} else {
		mouseRButton = false;
	}
}

void Input::OnMouseMove(WPARAM btnState, int x, int y) {
	//manager->OnMouseMove(x, y);
	mouseX = x;
	mouseY = y;
}

void Input::OnKeyDown(WPARAM keyCode) {
	//manager->OnKeyDown( (int)keyCode );
	keysDown[(int)keyCode] = true;
}
void Input::OnKeyUp(WPARAM keyCode) {
	//manager->OnKeyUp( (int)keyCode );
	keysDown[(int)keyCode] = false;
}


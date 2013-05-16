//
//input.h
//
#ifndef _INPUT_H                // prevent multiple definitions if this 
#define _INPUT_H                // ..file is included in more than one place

#pragma once

#include "framework/d3dUtil.h"
#include "framework/GameTimer.h"
#include <string>
#include <windows.h>
#include <WindowsX.h>
#include <XInput.h>
#include "StateManager.h"

namespace inputNS {
const int KEYS_ARRAY_LEN = 256;     // size of key arrays
////
// what values for clear(), bit flag
const UCHAR KEYS_DOWN = 1;
const UCHAR KEYS_PRESSED = 2;
const UCHAR MOUSE = 4;
const UINT L_BTN = 1;
const UINT M_BTN = 2;
const UINT R_BTN = 3;
const UCHAR TEXT_IN = 8;
const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
};

class Input {
private:
	//Key input
	bool keysDown[inputNS::KEYS_ARRAY_LEN];     // true if specified key is down
	bool keysPressed[inputNS::KEYS_ARRAY_LEN];  // true if specified key was pressed
	//Mouse input
	int  mouseX, mouseY;                        // mouse screen coordinates
	bool mouseCaptured;                         // true if mouse captured
	bool mouseLButton;                          // true if left mouse button down
	bool mouseMButton;                          // true if middle mouse button down
	bool mouseRButton;                          // true if right mouse button down
	//other
	//StateManager* manager;
public:
	// Constructor
	Input();

	// Destructor
	virtual ~Input();

	//initialize
	//void initialize(HWND hwnd, bool capture, StateManager gManager);
	//void initialize(StateManager* gManager);

	void OnMouseDown(WPARAM btnState, UINT btn,int x, int y);
	void OnMouseUp(WPARAM btnState, UINT btn, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);
	void OnKeyUp(WPARAM keyCode);
	void OnKeyDown(WPARAM keyCode);

	bool getLMouseButton() {
		return mouseLButton;
	}

	bool getRMouseButton() {
		return mouseRButton;
	}

	bool getKeyDown(int i) {
		return keysDown[i];
	}

	int getMouseX() {
		return mouseX;
	}

	int getMouseY() {
		return mouseY;
	}
};

extern Input* input;

#endif //Input_H
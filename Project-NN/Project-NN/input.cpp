//
//input.cpp
//

#include "input.h"


//constructor
Input::Input()
{
    // clear key down array
    for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
        keysDown[i] = false;
    // clear key pressed array
    for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
        keysPressed[i] = false;
    newLine = true;                     // start new line
    textIn = "";                        // clear textIn
    charIn = 0;                         // clear charIn

    // mouse data
    mouseX = 0;                         // screen X
	mouseY = 0;                         // screen Y
	mouseLButton = false;               // true if left mouse button is down
    mouseMButton = false;               // true if middle mouse button is down
    mouseRButton = false;               // true if right mouse button is down
}

//destructor
Input::~Input()
{
    if(mouseCaptured)
        ReleaseCapture();               // release mouse
}

//initialize
void Input::initialize(HWND hwnd, bool capture)
{
    try{
        mouseCaptured = capture;
        if(mouseCaptured)
            SetCapture(hwnd);           // capture mouse
	}
    catch(...)
    {
	//    throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing input system"));
    }
}

//sets the equivalent value to true in the key down array
void Input::keyDown(WPARAM wParam)
{
    // make sure key code is within buffer range
    if (wParam < inputNS::KEYS_ARRAY_LEN)
    {
        keysDown[wParam] = true;    // update keysDown array
        // key has been "pressed, erased by clear()
        keysPressed[wParam] = true; // update keysPressed array
    }
}

//sets the equivalent value to false in the key down array
void Input::keyUp(WPARAM wParam)
{
    // make sure key code is within buffer range
    if (wParam < inputNS::KEYS_ARRAY_LEN)
        // update state table
        keysDown[wParam] = false;
}

//returns true if the specified key has been pressed in the most recent frame
bool Input::wasKeyPressed(UCHAR vkey) const
{
    if (vkey < inputNS::KEYS_ARRAY_LEN)
        return keysPressed[vkey];
    else
        return false;
}

//returns true if a key is pressed
bool Input::anyKeyPressed() const
{
    for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
        if(keysPressed[i] == true)
            return true;
    return false;
}

//clear the specified key press
void Input::clearKeyPress(UCHAR vkey)
{
    if (vkey < inputNS::KEYS_ARRAY_LEN)
        keysPressed[vkey] = false;
}

//clear the specified buffers
void Input::clear(UCHAR what)
{
    if(what & inputNS::KEYS_DOWN)       // if clear keys down
    {
        for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
            keysDown[i] = false;
    }
    if(what & inputNS::KEYS_PRESSED)    // if clear keys pressed
    {
        for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
            keysPressed[i] = false;
    }
    if(what & inputNS::MOUSE)           // if clear mouse
    {
        mouseX = 0;
        mouseY = 0;
    }
    if(what & inputNS::TEXT_IN)
        clearTextIn();
}


//mouse input
void Input::mouseIn(LPARAM lParam)
{
    mouseX = GET_X_LPARAM(lParam); 
    mouseY = GET_Y_LPARAM(lParam);
}
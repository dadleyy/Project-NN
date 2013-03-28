//
//input.h
//
#ifndef _INPUT_H                // prevent multiple definitions if this 
#define _INPUT_H                // ..file is included in more than one place

#include "d3dUtil.h"
#include "GameTimer.h"
#include <string>
#include <windows.h>
#include <WindowsX.h>
#include <XInput.h>

namespace inputNS
{
	const int KEYS_ARRAY_LEN = 256;     // size of key arrays
	////
	// what values for clear(), bit flag
    const UCHAR KEYS_DOWN = 1;
    const UCHAR KEYS_PRESSED = 2;
    const UCHAR MOUSE = 4;
    const UCHAR TEXT_IN = 8;
    const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
}

class Input
{
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
	std::string textIn;                         // user entered text
    char charIn;                                // last character entered
    bool newLine;                               // true on start of new line
	
public:
    // Constructor
    Input();

    // Destructor
    virtual ~Input();

	//initialize
	void initialize(HWND hwnd, bool capture);

	//Keyboard
		// Save key down state
		void keyDown(WPARAM);

	    // Save key up state
		void keyUp(WPARAM);

		// Save the char just entered in textIn string
		void keyIn(WPARAM);

		// Returns true if the specified VIRTUAL KEY is down, otherwise false.
		bool isKeyDown(UCHAR vkey) const;

		// Return true if the specified VIRTUAL KEY has been pressed in the most recent frame.
		// Key presses are erased at the end of each frame.
		bool wasKeyPressed(UCHAR vkey) const;

		// Return true if any key was pressed in the most recent frame.
		// Key presses are erased at the end of each frame.
		bool anyKeyPressed() const;
	//end Keyboard

	//Mouse
		// Reads mouse screen position into mouseX, mouseY
		void mouseIn(LPARAM);

		// Save state of mouse button
		void setMouseLButton(bool b) { mouseLButton = b; }

		// Save state of mouse button
		void setMouseMButton(bool b) { mouseMButton = b; }

		// Save state of mouse button
		void setMouseRButton(bool b) { mouseRButton = b; }

		// Return mouse X position
		int  getMouseX()        const { return mouseX; }

		// Return mouse Y position
		int  getMouseY()        const { return mouseY; }

		// Return state of left mouse button.
		bool getMouseLButton()  const { return mouseLButton; }

		// Return state of middle mouse button.
		bool getMouseMButton()  const { return mouseMButton; }

		// Return state of right mouse button.
		bool getMouseRButton()  const { return mouseRButton; }
	//end Mouse

	//text
		// Return text input as a string
		std::string getTextIn() {return textIn;}

		// Return last character entered
		char getCharIn()        {return charIn;}
	//end text

	//cleanup
		// Clear specified input buffers where what is any combination of
		// KEYS_DOWN, KEYS_PRESSED, MOUSE, TEXT_IN or KEYS_MOUSE_TEXT.
		// Use OR '|' operator to combine parmeters.
		void clear(UCHAR what);

		// Clears key, mouse and text input data
		void clearAll() {clear(inputNS::KEYS_MOUSE_TEXT);}
		
		// Clear the specified key press
		void clearKeyPress(UCHAR vkey);

		// Clear text input buffer
		void clearTextIn() {textIn.clear();}
	//end cleanup
}

#endif //Input_H
#pragma once
#pragma once
#include "SDL.h"
#include <string>
#include <map>

typedef std::map<std::string, bool> Input; //Use input as an alias for our map
typedef std::pair<int, int> Mouse; //Use mouse as an alias for a pai rof ints

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	void update();

	void checkKey(std::string key, SDL_Keycode code);

	//Checks if a button has been pressed
	bool isButtonPressed(std::string button);
	//Checks if a button is being held down
	bool isButtonDown(std::string button);
	int getMouseX() { return m_mousePos.first; }
	int getMouseY() { return m_mousePos.second; }
private:
	Mouse m_mousePos;
	Input m_current;
	Input m_previous;
	const Uint8* m_keyStates;
	Uint32 m_mouseState;
};


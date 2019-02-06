#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "InputSystem.h"
#include <utility>
#include <string>
#include "SDL.h"
#include <map>
typedef std::map<std::string, bool> Input;


class InputComponent  : public Component {

public: 
	InputComponent()
	{
		//Keep a pointer to the keyboard state
		m_keyStates = SDL_GetKeyboardState(NULL);

		//Add buttons to our input handler
		m_current["W"] = false;
		m_current["A"] = false;
		m_current["S"] = false;
		m_current["D"] = false;
		m_current["Space"] = false;

		//Copy the values of current to previous
		m_previous = m_current;
	}
		
	const Uint8* m_keyStates;
	Input m_current;
	Input m_previous;
};



#endif
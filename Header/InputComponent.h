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

		//Check joycon buttons
		m_current["ABTN"] = false;
		m_current["XBTN"] = false;
		m_current["BBTN"] = false;
		m_current["YBTN"] = false;
		m_current["LBBTN"] = false;
		m_current["RBBTN"] = false;
		m_current["RBBTN"] = false;
		m_current["MINUS"] = false;
		m_current["PLUS"] = false;

		//Determinging the status of the sticks
		m_current["STICKUP"] = false;
		m_current["STICKDOWN"] = false;
		m_current["STICKLEFT"] = false;
		m_current["STICKRIGHT"] = false;

		//Copy the values of current to previous
		m_previous = m_current;
	}
	void initialiseJoycon(int index)
	{
		SDL_JoystickEventState(SDL_ENABLE);
		m_joycon = SDL_JoystickOpen(index);

		std::cout << "Joycon has rumble? " << (SDL_JoystickIsHaptic(m_joycon) == SDL_TRUE ? "Yes" : "NO") << "\n";
		m_rumble = SDL_GameControllerOpen(index);
		//SDL_HapticRumbleInit(m_rumble);
		int x = 0;
	}
		
	const Uint8* m_keyStates;
	SDL_Joystick* m_joycon;
	SDL_GameController* m_rumble;
	Input m_current;
	Input m_previous;
};



#endif
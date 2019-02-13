#include "..\Header\InputSystem.h"

void InputSystem::addComponent(Component * component)
{
	m_input = static_cast<InputComponent*>(component);
}

void InputSystem::update(double dt)
{	
	SDL_PumpEvents(); //Update the keystate

	m_input->m_previous = m_input->m_current; //Set our previous

	//Check if the keys are currently down
	m_input->m_current["W"] = m_input->m_keyStates[SDL_SCANCODE_W];
	m_input->m_current["A"] = m_input->m_keyStates[SDL_SCANCODE_A];
	m_input->m_current["S"] = m_input->m_keyStates[SDL_SCANCODE_S];
	m_input->m_current["D"] = m_input->m_keyStates[SDL_SCANCODE_D];
	m_input->m_current["Space"] = m_input->m_keyStates[SDL_SCANCODE_C];

	//Check joycon buttons
	m_input->m_current["ABTN"] = SDL_JoystickGetButton(m_input->m_joycon, 0);
	m_input->m_current["XBTN"] = SDL_JoystickGetButton(m_input->m_joycon, 1);
	m_input->m_current["BBTN"] = SDL_JoystickGetButton(m_input->m_joycon, 2);
	m_input->m_current["YBTN"] = SDL_JoystickGetButton(m_input->m_joycon, 3);
	m_input->m_current["LBBTN"] = SDL_JoystickGetButton(m_input->m_joycon, 4);
	m_input->m_current["RBBTN"] = SDL_JoystickGetButton(m_input->m_joycon, 5);
	m_input->m_current["RBBTN"] = SDL_JoystickGetButton(m_input->m_joycon, 5);
	m_input->m_current["MINUS"] = SDL_JoystickGetButton(m_input->m_joycon, 8);
	m_input->m_current["PLUS"] = SDL_JoystickGetButton(m_input->m_joycon, 9);

	//Determinging the status of the sticks
	m_input->m_current["STICKUP"] = SDL_JoystickGetHat(m_input->m_joycon, 0) == 1 ? true : false;
	m_input->m_current["STICKDOWN"] = SDL_JoystickGetHat(m_input->m_joycon, 0) == 4 ? true : false;
	m_input->m_current["STICKLEFT"] = SDL_JoystickGetHat(m_input->m_joycon, 0) == 8 ? true : false;
	m_input->m_current["STICKRIGHT"] = SDL_JoystickGetHat(m_input->m_joycon, 0) == 2 ? true : false;
	m_input->m_current["STICKDOWNLEFT"] = SDL_JoystickGetHat(m_input->m_joycon, 0) == 12 ? true : false;
	m_input->m_current["STICKDOWNRIGHT"] = SDL_JoystickGetHat(m_input->m_joycon, 0) == 6 ? true : false;
	m_input->m_current["STICKUPLEFT"] = SDL_JoystickGetHat(m_input->m_joycon, 0) == 9 ? true : false;
	m_input->m_current["STICKUPRIGHT"] = SDL_JoystickGetHat(m_input->m_joycon, 0) == 3 ? true : false;
}

bool InputSystem::isButtonPressed(std::string m_button)
{
	return m_input->m_current[m_button] && !m_input->m_previous[m_button];
}

bool InputSystem::isButtonHeld(std::string button)
{
	return m_input->m_current[button];
}

void InputSystem::applyRumble(float strength, int durMs)
{
	if (SDL_JoystickRumble(m_input->m_joycon, .5, .75, 10000) == -1)
	{
		std::cout << "Rumble not supported\n";
	}

}

void InputSystem::checkKey(std::string m_button, SDL_Keycode code)
{
	m_input->m_current[m_button] = m_input->m_keyStates[code];
}
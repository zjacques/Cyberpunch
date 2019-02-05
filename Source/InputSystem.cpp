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
}

void InputSystem::isButtonPressed(std::string m_button)
{
	if (m_input->m_current[m_button] == m_input->m_current["W"])
	{

	}

	if (m_input->m_current[m_button] == m_input->m_current["A"])
	{

	}

	if (m_input->m_current[m_button] == m_input->m_current["S"])
	{

	}
	if (m_input->m_current[m_button] == m_input->m_current["D"])
	{

	}
	if (m_input->m_current[m_button] == m_input->m_current["D"])
	{

	}
	
}

void InputSystem::checkKey(std::string m_button, SDL_Keycode code)
{
	m_input->m_current[m_button] = m_input->m_keyStates[code];
}
#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "System.h"
#include "InputComponent.h"


class InputSystem : public System
{
public: 
	InputSystem() {}
	~InputSystem() {}
	void addComponent(Component * component);
	void update(double dt);
	void isButtonPressed(std::string m_button);
	void checkKey(std::string m_button, SDL_Keycode code);
private:
	InputComponent * m_input;
};




#endif

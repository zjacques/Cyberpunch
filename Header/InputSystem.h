#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "System.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"

class InputSystem : public System
{
public: 
	InputSystem() {}
	~InputSystem() {}
	void addComponent(Component * component);
	void update(double dt);
	void checkKey(std::string m_button, SDL_Keycode code);
	bool isButtonPressed(std::string m_button);
	bool isButtonHeld(std::string button);
	void applyRumble(float strength, int durMs);
	
private:
	InputComponent * m_input;
};

#endif

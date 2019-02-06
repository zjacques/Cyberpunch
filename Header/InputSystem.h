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
<<<<<<< HEAD
	void checkKey(std::string m_button, SDL_Keycode code);
	void isButtonPressed(std::string m_button);

=======
	void isButtonPressed(std::string m_button);
	void checkKey(std::string m_button, SDL_Keycode code);
>>>>>>> dc2d41139dd0693dfc942e68f62d8803e45a9744
private:
	InputComponent * m_input;
};

#endif

#include "MovementSystem.h"


MovementSystem::MovementSystem(InputSystem * input) :
	m_inputPtr(input)
{
}

void MovementSystem::update(double dt)
{
	if (m_inputPtr->isButtonPressed("A"))
	{
		
	}
}

void MovementSystem::Jump() {
}

void MovementSystem::Left() {

}

void MovementSystem::Right() {


}

void MovementSystem::Kick() {


}

void MovementSystem::crouch() {


}
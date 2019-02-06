#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "InputSystem.h"
class MovementSystem : public System {
public:
	MovementSystem(InputSystem* input);

	void update(double dt);
	void Jump();
	void Left();
	void Right();
	void crouch();
	void Kick();



private: 
	InputSystem * m_inputPtr;
	PhysicsComponent* m_playerPhys; //Players physics
};



#endif

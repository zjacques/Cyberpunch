#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "InputSystem.h"
extern class Player;
class MovementSystem : public System {
public:
	MovementSystem(InputSystem* input);

	void update(double dt);
	void addComponent(Component* comp);
	void addPlayer(Player* player);
	void Jump();
	void Left();
	void Right();
	void crouch();
	void Kick();



private: 
	Player * m_player;
	InputSystem * m_inputPtr;
	PhysicsComponent* m_playerPhys; //Players physics
};



#endif

#pragma once
#ifndef PLAYERPHYSICSSYSTEM_H
#define PLAYERPHYSICSSYSTEM_H
#include "System.h"
#include "PlayerPhysicsComponent.h"

class PlayerPhysicsSystem : public System
{
public:
	PlayerPhysicsSystem() : m_gravFlipped(false) {}
	void setWorld(Box2DBridge& world);
	void addComponent(Component* comp);
	void update(double dt);
	void flipGravity();
private:
	Box2DBridge * m_worldPtr;
	bool m_gravFlipped;
};
#endif
#pragma once
#include "System.h"
#include "PhysicsComponent.h"

class PhysicsSystem : public System
{
public:
	PhysicsSystem() {}
	void addComponent(Component* comp);
	void update(double dt);
};
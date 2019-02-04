#pragma once
#include "Entity.h"
class System
{
public:
	System() {};
	virtual ~System() {}
	virtual void addEntity(Entity& e) = 0;
	virtual void update(double dt) = 0;
};
#ifndef SYSTEM_H
#define SYSTEM_H

#include "Component.h"

class System
{
public:
	System() {};
	virtual ~System() {}
	virtual void addComponent(Component *) = 0;
	virtual void update(double dt) = 0;

	std::vector<Component *> m_components;
};

#endif
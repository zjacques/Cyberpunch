#ifndef  DJBOOTHSYSTEM_H
#define DJBOOTHSYSTEM_H

#include "System.h"
#include "PickUpComponent.h"

class DJBoothSystem : public System
{
public:
	DJBoothSystem() {}
	void setWorld(Box2DBridge& world);
	void addComponent(Component* comp);
	void update(double dt);
	float getScalar();
private:
	Box2DBridge * m_worldPtr;

};

#endif // !  DJBOOTHSYSTEM_H


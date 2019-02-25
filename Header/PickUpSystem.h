#ifndef PICKUPSYSTEM_H
#define PICKUPSYSTEM_H
#include "System.h"
#include "PickUpComponent.h"

class PickUpSystem : public System
{
public:
	PickUpSystem(System* renderSys) :
		m_renderSysPtr(renderSys)
	{}
	void setWorld(Box2DBridge& world);
	void addComponent(Component* comp);
	void update(double dt);
private:
	Box2DBridge * m_worldPtr;
	System* m_renderSysPtr;
};

#endif
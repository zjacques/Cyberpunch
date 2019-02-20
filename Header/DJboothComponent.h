#pragma once
#include "Box2DBridge.h"
#include "PhysicsComponent.h"

class DJBoothComponent : public Component
{
public: 
	DJBoothComponent();

	void spawn(Box2DBridge& world);
	
private:
	
	PhysicsComponent * m_body;

};
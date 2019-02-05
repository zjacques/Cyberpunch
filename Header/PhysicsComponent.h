#pragma once
#include "Box2DBridge.h"
#include "PositionComponent.h"

class PhysicsComponent
{
public:
	PhysicsComponent(PositionComponent* pos) {}

	//The body of the physics component
	Box2DBody m_body;

	//Hold a ptr to the position component that the physics modifies
	PositionComponent * posPtr; 
};
#pragma once
#include "Box2D/Box2D.h"

//Class listens for collisions, this is an observer class
//From here we can check if specific sensor have collided
class CollisionListener : public b2ContactListener
{
public:
	CollisionListener() {}

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};
#pragma once
#include "Box2DBridge.h"
#include "PhysicsComponent.h"

class PickUpComponent : public Component
{
public: 
	PickUpComponent();

	void spawn(Box2DBridge& world);
	void despawn(Box2DBridge& world);
	
	bool& spawned() { return m_spawned; }
	float& getTimeLive() { return m_timeLive; }
	float& getTimeTillSpawn() { return m_timeTillSpawn; }
	Vector2f& getTeleportLocation() { return m_teleportLocation; }
private:
	float m_timeLive;
	bool m_spawned;
	float m_timeTillSpawn;
	Vector2f m_teleportLocation;

	PhysicsComponent* m_body;

};

#pragma once
#include "Box2DBridge.h"
#include "Entity.h"
#include "PhysicsComponent.h"

class PickUpComponent : public Component
{
public: 
	PickUpComponent(Entity* pickupEntity);

	void spawn(Box2DBridge& world);
	void despawn(Box2DBridge& world);
	void teleport(Entity* e) { m_playerToTele = e; m_teleport = true; };

	//Getters
	bool& toTeleport() { return m_teleport; }
	bool& spawned() { return m_spawned; }
	float& getTimeLive() { return m_timeLive; }
	float& getTimeTillSpawn() { return m_timeTillSpawn; }
	float& getTimeInBooth() { return m_timeInBooth; }
	Vector2f& getTeleportLocation() { return m_teleportLocation; }
	Entity* getPlayer() { return m_playerToTele; }
	Entity* getPickupEntity() { return m_pickupEntity; }
	PhysicsComponent* getBody() { return m_body; };
private:
	float m_timeLive;
	float m_timeInBooth = 10;
	bool m_spawned;
	float m_timeTillSpawn;
	Vector2f m_teleportLocation;
	PhysicsComponent* m_body;
	Entity* m_playerToTele, *m_pickupEntity;
	bool m_teleport;
	bool m_back;

};

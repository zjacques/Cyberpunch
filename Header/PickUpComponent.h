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
	bool& toTeleportB() { return m_back; }
	bool& spawned() { return m_spawned; }
	float& getTimeLive() { return m_timeLive; }
	float& getTimeTillSpawn() { return m_timeTillSpawn; }
	float& getTimeInBooth() { return m_timeInBooth; }
	Vector2f& getTeleportLocation() { return m_teleportLocation; }
	Vector2f& getTeleportLocationB() { return m_teleportLocationB; }
	Entity* getPlayer() { return m_playerToTele; }
	Entity* getPickupEntity() { return m_pickupEntity; }
	PhysicsComponent* getBody() { return m_body; };
private:
	float m_timeLive;
	float m_timeInBooth = 10;
	bool m_spawned;
	float m_timeTillSpawn;
	Vector2f m_teleportLocation = Vector2f(960, 80);
	Vector2f m_teleportLocationB;
	PhysicsComponent* m_body;
	Entity* m_playerToTele, *m_pickupEntity;
	bool m_teleport;
	bool m_back;

};

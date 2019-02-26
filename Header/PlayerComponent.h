#pragma once
#include "Vector2f.h"
#include "Entity.h"
#include "PlayerPhysicsComponent.h"
class PlayerComponent : public Component
{
public:
	PlayerComponent(std::vector<Vector2f> locations, Entity* player) :
		m_dead(false),
		m_lives(3),
		m_newSpawn(nullptr),
		m_playerPtr(player),
		m_spawnLocations(locations),
		m_respawn(false)
	{
	}

	void respawn()
	{
		//Set the player to respawn
		m_lives--;

		if (m_lives < 1)
		{
			m_dead = true;
		}

		//If the player is not dead, pick a spawn location
		if (m_dead == false)
		{
			m_respawn = true;
			m_spawnTimer = 2.5f; //Respawn after 2.5 seconds
			m_newSpawn = &m_spawnLocations.at(rand() % m_spawnLocations.size()); //Number between 0 and the size of the amount of spawn points
			
		}
	}

	void spawnPlayer()
	{
		m_respawn = false;
		m_spawnTimer = 0;
		//Set the players position to the new position
		static_cast<PlayerPhysicsComponent*>(&m_playerPtr->getComponent("Player Physics"))->m_body->setPosition(m_newSpawn->x, m_newSpawn->y);
	}

	Vector2f getSpawnLocation() { return *m_newSpawn; }
	Entity* getPlayer() { return m_playerPtr; }
	float& getTimer() { return m_spawnTimer; }
	bool& isDead() { return m_dead; }
	bool& toRespawn() { return m_respawn; }
private:
	float m_spawnTimer;
	Entity * m_playerPtr;
	Vector2f* m_newSpawn;
	std::vector<Vector2f> m_spawnLocations;
	bool m_dead, m_respawn;
	int m_lives;
};
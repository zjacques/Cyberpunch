#pragma once
#include "Component.h"
#include "Vector2f.h"

class PlayerComponent : public Component
{
public:
	PlayerComponent() :
		m_dead(false),
		m_lives(3),
		m_newSpawn(nullptr)
	{}

	void setSpawnLocations(std::vector<Vector2f> locations)
	{
		//Get the vector of spawn locations
		m_spawnLocations = locations;
	}

	void respawn()
	{
		m_lives--;

		if (m_lives < 1)
		{
			m_dead = true;
		}

		//If the player is not dead, pick a spawn location
		if (m_dead == false)
		{
			m_newSpawn = &m_spawnLocations.at(rand() % 5); //Number bewteen 0 and 4
		}
	}

	Vector2f getSpawnLocation() { return *m_newSpawn; }
	bool isDead() { return m_dead; }
private:
	Vector2f* m_newSpawn;
	std::vector<Vector2f> m_spawnLocations;
	bool m_dead;
	int m_lives;
};
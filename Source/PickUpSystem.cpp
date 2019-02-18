#include "PickUpSystem.h"

void PickUpSystem::setWorld(Box2DBridge & world)
{
	m_worldPtr = &world;
}

void PickUpSystem::addComponent(Component * comp)
{
	m_components.push_back(comp);
}

void PickUpSystem::update(double dt)
{
	for (auto& comp : m_components)
	{
		auto pickup = static_cast<PickUpComponent*>(comp);
		

		//pickup->getTimeTillSpawn();

		if (pickup->getTimeTillSpawn() > 0)
		{
			pickup->getTimeTillSpawn() -= dt;

			if(pickup->getTimeTillSpawn() <= 0)
				pickup->spawn(*m_worldPtr);
		}

		if (pickup->spawned())
		{
			if (pickup->getTimeLive() > 0)
			{
				pickup->getTimeLive() -= dt;

				if (pickup->getTimeLive() <= 0)
				{
					pickup->despawn(*m_worldPtr);
				}
			}
		}
	}
}


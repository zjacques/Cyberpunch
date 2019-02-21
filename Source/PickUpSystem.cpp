#include "PickUpSystem.h"
#include "PlayerPhysicsComponent.h"

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

		if (pickup->toTeleportB())
		{
			
			pickup->getTimeInBooth() -= dt;
		}

		if (pickup->spawned())
		{
			
			//If ye have to teleport  aplayer
			if (pickup->toTeleport())
			{
				auto p = static_cast<PlayerPhysicsComponent*>(&pickup->getPlayer()->getComponent("Player Physics"));
				p->m_body->setPosition(pickup->getTeleportLocation().x, pickup->getTeleportLocation().y);

				pickup->toTeleportB() = true;


				if (pickup->getTimeInBooth() <= 0)
				{
					pickup->toTeleport() = false;
					pickup->toTeleportB() = false;
					p->m_body->setPosition(400, 400);
					pickup->getTimeInBooth() = 10;
				}
			}

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


#include "PickUpSystem.h"
#include "PlayerPhysicsComponent.h"
#include "RenderSystem.h"

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

			if (pickup->getTimeTillSpawn() <= 0)
			{
				pickup->spawn(*m_worldPtr);
				m_renderSysPtr->addComponent(&pickup->getPickupEntity()->getComponent("Sprite"));
			}

		}

		//countdown for time in booths
		if (pickup->toTeleportB())
		{
			
			pickup->getTimeInBooth() -= dt;
		}

		if (pickup->spawned())
		{
			
			//If ye have to teleport  aplayer
			if (pickup->toTeleport())
			{
				// sends player to booth, despawns the pickup and sets the timer to countdown
				auto p = static_cast<PlayerPhysicsComponent*>(&pickup->getPlayer()->getComponent("Player Physics"));
				p->m_body->setPosition(pickup->getTeleportLocation().x, pickup->getTeleportLocation().y);
				pickup->despawn(*m_worldPtr);
				m_renderSysPtr->deleteComponent(&pickup->getPickupEntity()->getComponent("Sprite"));
				pickup->toTeleportB() = true;


				//checks to see if time is up for player in booth, sets teleport to false
				//sets timer back to 10 seconds and moves player back into the game
				if (pickup->getTimeInBooth() <= 0)
				{
					pickup->toTeleport() = false;
					pickup->toTeleportB() = false;
					p->m_body->setPosition(400, 400);
					pickup->getTimeInBooth() = 10;
				}
			}

			//despawns the pickup after ten seconds if not collected
			if (pickup->getTimeLive() > 0)
			{
				pickup->getTimeLive() -= dt;

				if (pickup->getTimeLive() <= 0)
				{
					pickup->despawn(*m_worldPtr);
					m_renderSysPtr->deleteComponent(&pickup->getPickupEntity()->getComponent("Sprite"));
				}
			}

		}


		
	}

}



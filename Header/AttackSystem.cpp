#include "AttackSystem.h"

void AttackSystem::addComponent(Component * comp)
{
	m_components.push_back(comp);
}

void AttackSystem::update(double dt)
{
	for (auto& comp : m_components)
	{
		auto hit = static_cast<AttackComponent*>(comp);

		//If there is a delay on the hit
		if (hit->delay())
		{
			//Take away from the delay
			hit->delayLeft() -= dt;

			if (hit->delayLeft() <= 0)
			{
				//Set spawn attack to true
				hit->spawnAttack() = true;
			}
		}

		//If the hit is to spawn an attack then spawn one
		if (hit->spawnAttack())
		{
			hit->spawn(*m_worldPtr);
		}

		//If a hit is active,  minus from its time to live
		if (hit->attackActive())
		{
			//minus dt from the time to live
			hit->timeToLive() -= dt;

			if (hit->timeToLive() <= 0)
			{
				hit->setDestoryAttack(true);
			}
			else
			{
				hit->updatePosition();
			}
		}

		//If the bool to destroy an attack is true, then delete the attack body
		if (hit->destroyAttack())
		{
			hit->deleteAttack(*m_worldPtr);
		}
	}
}

#include "DJBoothSystem.h"
#include "DJboothComponent.h"
#include "SlowBoothComponent.h"

void DJBoothSystem::setWorld(Box2DBridge & world)
{
	m_worldPtr = &world;
}

void DJBoothSystem::addComponent(Component * comp)
{
	m_components.push_back(comp);
}

void DJBoothSystem::update(double dt)
{
	for (auto& comp : m_components)
	{
		static_cast<DJBoothComponent*>(comp)->update(dt);
	}
	
}

float DJBoothSystem::getScalar()
{
	for (auto& comp : m_components)
	{
		auto c = dynamic_cast<SlowBoothComponent*>(comp);

		if (nullptr != c)
		{
			return c->getScaler();
		}

	}

	return 1.0f;
}

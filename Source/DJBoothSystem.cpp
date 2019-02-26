#include "DJBoothSystem.h"
#include "DJboothComponent.h"
#include "SlowBoothComponent.h"
#include "SpriteComponent.h"


void DJBoothSystem::addComponent(Component * comp)
{
	m_components.push_back(comp);
}

void DJBoothSystem::update(double dt)
{
	for (auto& comp : m_components)
	{
		auto booth = static_cast<DJBoothComponent*>(comp);

		booth->update(dt);

		if (booth->bgSwitch)
		{
			m_currentBg++;
			m_currentPc++;

			if (m_currentBg > 3)
				m_currentBg = 0;
			
			if (m_currentPc > 3)
				m_currentPc = 0;


			auto bgSprite = static_cast<SpriteComponent*>(&m_bgPtr->getComponent("Sprite"));
			bgSprite->setTexture(m_resourcePtr->getTexture("Game BG" + std::to_string(m_currentBg)));
			booth->bgSwitch = false;

			
		}
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

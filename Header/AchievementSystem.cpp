#include "AchievementSystem.h"

AchievementSystem::AchievementSystem() :
	m_showingAchievement(false),
	m_comptToUpdate(false)
{
}

void AchievementSystem::addComponent(Component * comp)
{
	m_components.push_back(comp);
}

void AchievementSystem::update(double dt)
{
	if (m_showingAchievement == false)
	{
		if (!m_components.empty())
		{
			m_showingAchievement = true;
			m_comptToUpdate = m_components.at(0);
		}
	}
}

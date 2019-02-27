#pragma once
#include "AchievementPopup.h"
#include "System.h"
#include "Entity.h"

class AchievementSystem : public System
{
public:
	AchievementSystem();
	void addComponent(Component* comp);
	void update(double dt);

private:
	bool m_showingAchievement;
	Component* m_comptToUpdate;
};
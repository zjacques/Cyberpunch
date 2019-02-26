#pragma once
#include "Component.h"
#include <iostream>

class AchievementComponent : public Component
{
public:
	AchievementComponent(){ }

	void unlockAchievement(std::string name)
	{
		bool hasAchiev = false;
		for (auto& pair : m_achievements)
		{
			if (pair.first == name)
			{
				pair.second = true;
				hasAchiev = true;
				break;
			}
		}

		if (!hasAchiev)
			std::cout << "Tried unlocking an achievement that doesnt exist\n";
	}

private:
	std::map<std::string, bool> m_achievements;

};
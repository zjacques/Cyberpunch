#pragma once
#include "System.h"
#include "AnimationComponent.h"

class AnimationSystem : public System
{
public:
	AnimationSystem() {};
	void addComponents(Component * comp);
	void update(double dt);
private:
};
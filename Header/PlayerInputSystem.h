#pragma once
#ifndef PLAYERINPUTSYSTEM_H
#define PLAYERINPUTSYSTEM_H

#include "System.h"
#include "PlayerInputComponent.h"

class PlayerInputSystem : public System
{
public:
	PlayerInputSystem() {}
	~PlayerInputSystem() {}
	void addComponent(Component * component);
	void update(double dt);
};

#endif
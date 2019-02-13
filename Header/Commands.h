#pragma once
#include "Entity.h"
#include "PlayerPhysicsComponent.h"

class Command
{
public:
	virtual ~Command() {}
	virtual void execute(Entity& e) = 0;
};

class JumpCommand : public Command
{
public:
	JumpCommand() {}
	void execute(Entity& e)
	{
		auto phys = static_cast<PlayerPhysicsComponent*>(&e.getComponent("Player Physics"));
		//If the physics component can jump, then jump
		if (phys->canJump())
		{
			phys->jump();
		}
	}
};

class MoveLeftCommand : public Command
{
public:
	MoveLeftCommand() {}
	void execute(Entity& e)
	{
		auto phys = static_cast<PlayerPhysicsComponent*>(&e.getComponent("Player Physics"));
		phys->moveLeft();
	}
};

class MoveRightCommand : public Command
{
public:
	MoveRightCommand() {}
	void execute(Entity& e)
	{
		auto phys = static_cast<PlayerPhysicsComponent*>(&e.getComponent("Player Physics"));
		phys->moveRight();
	}
};
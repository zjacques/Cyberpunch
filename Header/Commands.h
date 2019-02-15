#pragma once
#include "Entity.h"
#include "PlayerPhysicsComponent.h"
#include "OnlineSendComponent.h"
#include "AttackComponent.h"

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
		auto hit = static_cast<AttackComponent*>(&e.getComponent("Attack"));
		if (hit->attackActive() == false)
		{
			auto phys = static_cast<PlayerPhysicsComponent*>(&e.getComponent("Player Physics"));
			//If the physics component can jump, then jump
			if (phys->canJump())
			{
				phys->jump();
			}
			auto net = static_cast<OnlineSendComponent*>(&e.getComponent("Send"));
			if (net != NULL) 
			{
				net->addCommand("JUMP");
			}
		}
	}
};

class MoveLeftCommand : public Command
{
public:
	MoveLeftCommand() {}
	void execute(Entity& e)
	{
		auto hit = static_cast<AttackComponent*>(&e.getComponent("Attack"));
		auto phys = static_cast<PlayerPhysicsComponent*>(&e.getComponent("Player Physics"));
		if (hit->attackActive() == false || !phys->canJump())
		{
			phys->moveLeft();
		}
		auto net = static_cast<OnlineSendComponent*>(&e.getComponent("Send"));
		if (net != NULL)
		{
			net->addCommand("MOVE LEFT");
		}
	}
};

class MoveRightCommand : public Command
{
public:
	MoveRightCommand() {}
	void execute(Entity& e)
	{
		//get the attack component from the entity
		auto hit = static_cast<AttackComponent*>(&e.getComponent("Attack"));
		auto phys = static_cast<PlayerPhysicsComponent*>(&e.getComponent("Player Physics"));
		if (hit->attackActive() == false || !phys->canJump())
		{
			phys->moveRight();
		}
		auto net = static_cast<OnlineSendComponent*>(&e.getComponent("Send"));
		if (net != NULL)
		{
			net->addCommand("MOVE RIGHT");
		}
	}
};

class PunchCommand : public Command
{
public:
	PunchCommand() {}
	void execute(Entity& e)
	{
		//get the attack component from the entity
		auto hit = static_cast<AttackComponent*>(&e.getComponent("Attack"));

		if (hit->attackActive() == false)
		{
			auto phys = static_cast<PlayerPhysicsComponent*>(&e.getComponent("Player Physics"));

			auto tag = "Attack";
			auto offset = Vector2f(phys->isMovingLeft() ? -40 : 40, phys->isGravityFlipped() ? -12.5f : 12.5f);

			hit->attack(offset, Vector2f(30, 25), e, tag, .175f, 0);
			hit->setAttackProperties(2, phys->isMovingLeft() ? -250 : 250, phys->isGravityFlipped() ? -30 : 30);
		}
		auto net = static_cast<OnlineSendComponent*>(&e.getComponent("Send"));
		if (net != NULL)
		{
			net->addCommand("PUNCH");
		}
	}
};

class KickCommand : public Command
{
public:
	KickCommand() {}
	void execute(Entity& e)
	{
		//get the attack component from the entity
		auto hit = static_cast<AttackComponent*>(&e.getComponent("Attack"));

		if (hit->attackActive() == false)
		{
			auto phys = static_cast<PlayerPhysicsComponent*>(&e.getComponent("Player Physics"));

			auto tag = "Attack";
			auto offset = Vector2f(phys->isMovingLeft() ? -50 : 50, phys->isGravityFlipped() ? 12.5f : -12.5f);

			hit->attack(offset, Vector2f(50, 25), e, tag, .4f, 0);
			hit->setAttackProperties(5, phys->isMovingLeft() ? -300 : 300, phys->isGravityFlipped() ? -45 : 45);
		}
		auto net = static_cast<OnlineSendComponent*>(&e.getComponent("Send"));
		if (net != NULL)
		{
			net->addCommand("KICK");
		}
	}
};

class UppercutCommand : public Command
{
public:
	UppercutCommand() {}
	void execute(Entity& e)
	{
		//get the attack component from the entity
		auto hit = static_cast<AttackComponent*>(&e.getComponent("Attack"));

		if (hit->attackActive() == false)
		{
			auto phys = static_cast<PlayerPhysicsComponent*>(&e.getComponent("Player Physics"));

			auto tag = "Attack";
			auto offset = Vector2f(phys->isMovingLeft() ? -37.5f : 37.5f, phys->isGravityFlipped() ? 12.5f : -12.5f);

			hit->attack(offset, Vector2f(25, 45), e, tag, .4f, 0);
			hit->setAttackProperties(5, phys->isMovingLeft() ? -10 : 10, phys->isGravityFlipped() ? -75 : 75);
		}
		auto net = static_cast<OnlineSendComponent*>(&e.getComponent("Send"));
		if (net != NULL)
		{
			net->addCommand("UPPERCUT");
		}
	}
};
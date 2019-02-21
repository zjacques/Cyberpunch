#pragma once
#include "Entity.h"
#include "SpriteComponent.h"
#include "PlayerPhysicsComponent.h"
#include "OnlineSendComponent.h"
#include "AttackComponent.h"
#include "AnimationComponent.h"

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
		auto phys = static_cast<PlayerPhysicsComponent*>(&e.getComponent("Player Physics"));

		if (hit->attackActive() == false && phys->stunned() == false)
		{
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

		//Only perform the command if the playe ris not stunned
		if (phys->stunned() == false)
		{
			if (hit->attackActive() == false || !phys->canJump())
			{
				phys->moveLeft();
				//Play run animation
				auto a = static_cast<AnimationComponent*>(&e.getComponent("Animation"));
				a->playAnimation("Run", true);
				auto s = static_cast<SpriteComponent*>(&e.getComponent("Sprite"));
				s->setScale(1, s->getScale().y);
				s->setTexture(a->getCurrentAnimation()->getTexture());
			}
			else if(hit->attackActive() == false)
				static_cast<AnimationComponent*>(&e.getComponent("Animation"))->playAnimation("Idle", true);
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

		//Only perform the command if the playe ris not stunned
		if (phys->stunned() == false)
		{
			if (hit->attackActive() == false || !phys->canJump())
			{
				phys->moveRight();
				auto a = static_cast<AnimationComponent*>(&e.getComponent("Animation"));
				a->playAnimation("Run", true);
				auto s = static_cast<SpriteComponent*>(&e.getComponent("Sprite"));
				s->setScale(-1, s->getScale().y);
				s->setTexture(a->getCurrentAnimation()->getTexture());
			}
			else if(hit->attackActive() == false)
				static_cast<AnimationComponent*>(&e.getComponent("Animation"))->playAnimation("Idle", true);
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
		auto phys = static_cast<PlayerPhysicsComponent*>(&e.getComponent("Player Physics"));

		if (hit->attackActive() == false && phys->stunned() == false)
		{

			auto tag = "Attack";
			auto offset = Vector2f(phys->isMovingLeft() ? -40 : 40, phys->isGravityFlipped() ? 12.5f : -12.5f);

			hit->attack(offset, Vector2f(30, 25), e, tag, .175f, 0);
			hit->setAttackProperties(2, phys->isMovingLeft() ? -100 : 100, phys->isGravityFlipped() ? -30 : 30);
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
		auto phys = static_cast<PlayerPhysicsComponent*>(&e.getComponent("Player Physics"));

		if (hit->attackActive() == false && phys->stunned() == false)
		{
			auto tag = "Attack";
			auto offset = Vector2f(phys->isMovingLeft() ? -50 : 50, phys->isGravityFlipped() ? -12.5f : 12.5f);

			hit->attack(offset, Vector2f(50, 25), e, tag, .4f, 0);
			hit->setAttackProperties(5, phys->isMovingLeft() ? -175 : 175, phys->isGravityFlipped() ? -45 : 45);

			auto a = static_cast<AnimationComponent*>(&e.getComponent("Animation"));
			a->playAnimation("Ground Kick", false);
			static_cast<SpriteComponent*>(&e.getComponent("Sprite"))->setTexture(a->getCurrentAnimation()->getTexture());
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
		auto phys = static_cast<PlayerPhysicsComponent*>(&e.getComponent("Player Physics"));

		if (hit->attackActive() == false && phys->stunned() == false)
		{

			auto tag = "Attack";
			auto offset = Vector2f(phys->isMovingLeft() ? -37.5f : 37.5f, 0);

			hit->attack(offset, Vector2f(25, 45), e, tag, .4f, 0);
			hit->setAttackProperties(50, phys->isMovingLeft() ? -10 : 10, phys->isGravityFlipped() ? -85 : 85);
		}
		auto net = static_cast<OnlineSendComponent*>(&e.getComponent("Send"));
		if (net != NULL)
		{
			net->addCommand("UPPERCUT");
		}
	}
};

class PhaseDownCommand : public Command
{
public:
	PhaseDownCommand() {}
	void execute(Entity& e)
	{
		//get the attack component from the entity
		auto hit = static_cast<AttackComponent*>(&e.getComponent("Attack"));
		auto phys = static_cast<PlayerPhysicsComponent*>(&e.getComponent("Player Physics"));

		if (hit->attackActive() == false && phys->stunned() == false)
		{
			if (phys->canJump())
			{
				phys->jumpDown();
			}
		}
	}
};

class SuperCommand : public Command
{
public:
	SuperCommand() {}
	void execute(Entity& e)
	{
		//get the attack component from the entity
		auto hit = static_cast<AttackComponent*>(&e.getComponent("Attack"));
		auto phys = static_cast<PlayerPhysicsComponent*>(&e.getComponent("Player Physics"));

		//Only execute if we arent in the middle of attacking and we are not stunned
		if (hit->attackActive() == false && phys->stunned() == false && phys->canSuperUp() && phys->isSupered() == false)
		{
			phys->beginSuper();
			std::cout << "Player has used super up, they can now stun someone for 5 seconds if they hit within 5 seconds\n";
		}
	}
};

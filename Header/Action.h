#ifndef ACTION_H
#define ACTION_H

#include "BehaviourTree.h"
#include "Entity.h"
#include "Component.h"
#include "PositionComponent.h"
#include "AIComponent.h"

class Action : public BehaviourTree::Node
{
public:
	std::string m_name;
	int successRate;
	Action(const std::string newName, int p) : m_name(newName), successRate(p) {}

	virtual bool run() = 0;
};

#endif

#ifndef WALKLEFTACTION_H
#define WALKLEFTACTION_H

class WalkLeftAction : public Action
{
public:
	WalkLeftAction(std::string newName, int p)
		: Action(newName, p)
	{
	}

	bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Walking left" << std::endl;
			return true;
		}
		return false;
	}
};

#endif

#ifndef WALKRIGHTACTION_H
#define WALKRIGHTACTION_H

class WalkRightAction : public Action
{
public:
	WalkRightAction(std::string newName, int p)
		: Action(newName, p)
	{
	}
	bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Walking right" << std::endl;
			return true;
		}
		return false;
	}
};

#endif

#ifndef JUMPACTION_H
#define JUMPACTION_H

class JumpAction : public Action
{
public:
	JumpAction(std::string newName, int p)
		: Action(newName, p)
	{
	}
	bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Jump" << std::endl;
			return true;
		}
		return false;
	}
};

#endif

#ifndef PUNCHACTION_H
#define PUNCHACTION_H

class PunchAction : public Action
{
public:
	PunchAction(std::string newName, int p)
		: Action(newName, p)
	{
	}
	bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Punch" << std::endl;
			return true;
		}
		return false;
	}
};

#endif

#ifndef CHECKNEAREST_H
#define CHECKNEAREST_H

class CheckNearest : public Action
{
public:
	CheckNearest(std::string newName, int p, std::vector<Entity *> e, Entity * s) :
		Action(newName, p),
		m_entities(e),
		self(s)
	{
	}

	bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Getting nearest player" << std::endl;

			Entity* nearest;
			float nearest_dist;

			for (auto i : m_entities)
			{
				nearest = i;

				auto p = dynamic_cast<PositionComponent *>(&nearest->getComponent("Pos"));
				auto self_pos = dynamic_cast<PositionComponent *>(&self->getComponent("Pos"));
				nearest_dist = dist(p->position, self_pos->position);
				if (dist(p->position, self_pos->position) < nearest_dist)
				{
					nearest_dist = dist(p->position, self_pos->position);
					nearest = i;
				}
			}
			//auto me = dynamic_cast<AIComponent *>(&self->getComponent("AI"));
			//me->nearestPlayer = nearest;
			return true;
		}
		return false;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="p1"></param>
	/// <param name="p2"></param>
	/// <returns></returns>
	float dist(Vector2f p1, Vector2f p2)
	{
		return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
	}
	std::vector<Entity *> m_entities;
	Entity * self;
};
#endif

#ifndef CLOSEENOUGH_H
#define CLOSEENOUGH_H

class CloseEnough : public Action
{
public:
	CloseEnough(std::string newName, int p) :
		Action(newName, p)
	{
	}

	bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Close enough" << std::endl;
			return true;
		}
		return false;
	}
};

#endif

#ifndef CHECKPLAYERDIRECTION_H
#define CHECKPLAYERDIRECTION_H

class CheckPlayerDirection : public Action
{
public:
	CheckPlayerDirection(std::string newName, int p) :
		Action(newName, p)
	{
	}

	bool run() override
	{
		if (std::rand() % 100 < successRate)
		{
			std::cout << "Check direction" << std::endl;
			return true;
		}
		return false;
	}
};

#endif


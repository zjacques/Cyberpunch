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
	Action(Entity * e) :
	m_entity(e)
	{}

	virtual bool run() = 0;
	Entity * m_entity;
};

#endif

#ifndef WALKLEFTACTION_H
#define WALKLEFTACTION_H

class WalkLeftAction : public Action
{
public:
	WalkLeftAction(Entity * e) :
		Action(e)
	{
	}

	bool run() override
	{
		std::cout << "Walking left" << std::endl;
		return true;
	}
};

#endif

#ifndef WALKRIGHTACTION_H
#define WALKRIGHTACTION_H

class WalkRightAction : public Action
{
public:
	WalkRightAction(Entity * e)
		: Action(e)
	{
	}

	bool run() override
	{
		std::cout << "Waling right" << std::endl;
		return true;
	}
};

#endif

#ifndef JUMPACTION_H
#define JUMPACTION_H

class JumpAction : public Action
{
public:
	JumpAction(Entity * e)
		: Action(e)
	{
	}
	bool run() override
	{
		std::cout << "Jump" << std::endl;

		
		return true;
	}
};

#endif

#ifndef PUNCHACTION_H
#define PUNCHACTION_H

class PunchAction : public Action
{
public:
	PunchAction(Entity * e)
		: Action(e)
	{
	}

	bool run() override
	{
		std::cout << "Punch" << std::endl;
		return true;
	}
};

#endif

#ifndef CHECKNEAREST_H
#define CHECKNEAREST_H

class CheckNearest : public Action
{
public:
	CheckNearest(std::vector<Entity *> e, Entity * s) :
		m_entities(e), Action(s)
	{
	}

	bool run() override
	{
		std::cout << "Getting nearest player" << std::endl;

		Entity* nearest;
		float nearest_dist;
		//nearest = i;
		for (auto i : m_entities)
		{
			/*auto p = dynamic_cast<PositionComponent *>(&nearest->getComponent("Pos"));
			auto self_pos = dynamic_cast<PositionComponent *>(&m_entity->getComponent("Pos"));
			nearest_dist = dist(p->position, self_pos->position);
			if (dist(p->position, self_pos->position) < nearest_dist)
			{
				nearest_dist = dist(p->position, self_pos->position);
				nearest = i;
			}*/
		}
		return true;
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
};
#endif

#ifndef CLOSEENOUGH_H
#define CLOSEENOUGH_H

class CloseEnough : public Action
{
public:
	CloseEnough(Entity * e)
		: Action(e)
	{
	}

	bool run() override
	{
		std::cout << "Close enough" << std::endl;
		return true;
	}
};

#endif

#ifndef CHECKPLAYERDIRECTION_H
#define CHECKPLAYERDIRECTION_H

class CheckPlayerDirection : public Action
{
public:
	CheckPlayerDirection(Entity * e)
		: Action(e)
	{
	}

	bool run() override
	{
		std::cout << "Check direction" << std::endl;
		return true;
	}
};

#endif

#ifndef CHECKHEALTH_H
#define CHECKHEALTH_H

class CheckHealth : public Action
{
public:
	CheckHealth(Entity * e)
		: Action(e)
	{
	}

	bool run() override
	{
		std::cout << "Check health" << std::endl;
		return true;
	}
};

#endif

#ifndef FLEEACTION_H
#define FLEEACTION_H

class FleeAction : public Action
{
public:
	FleeAction(Entity * e)
		: Action(e)
	{

	}

	bool run() override
	{
		std::cout << "Fleeing" << std::endl;
		return true;
	}
};

#endif

#ifndef CHECKABOVE_H
#define CHECKABOVE_H

class CheckAbove : public Action
{
public:
	CheckAbove(Entity * e)
		: Action(e)
	{}

	bool run() override
	{
		std::cout << "Check if player above" << std::endl;
		return true;
	}
};

#endif

#ifndef CHECKPLAYERHEALTH_H
#define CHECKPLAYERHEALTH_H

class CheckPlayerHealth : public Action
{
public:
	CheckPlayerHealth(Entity * e)
		: Action(e)
	{}

	bool run() override
	{
		std::cout << "Check player health" << std::endl;
		return true;
	}
};

#endif

#ifndef DROPACTION_H
#define DROPACTION_H

class DropAction : public Action
{
public:
	DropAction(Entity * e) 
		: Action(e)
	{}

	bool run() override
	{
		std::cout << "Drop down" << std::endl;
		return true;
	}
};

#endif


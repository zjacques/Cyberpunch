#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "Component.h"
#include "BehaviourTree.h"
#include "Action.h"
#include "Entity.h"
#include <vector>

class AIComponent : public Component
{
public:
	AIComponent(std::vector<Entity *> e) :
		m_entities(e)
	{
		Entity* me = nullptr;
		for (auto& entity : m_entities)
		{
			auto aiComp = dynamic_cast<AIComponent*>(&entity->getComponent("AI"));

			if (nullptr != aiComp)
			{
				if (aiComp == this)
				{
					me = entity;
					m_self = entity;
				}
			}
		}
		if (nullptr != me)
		{
			m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), me), m_entities.end());
		}
	}
	~AIComponent() {}

	//Declare Tree, selector nodes and sequence nodes
	BehaviourTree BT;
	BehaviourTree::Selector m_selectors[7];
	BehaviourTree::Sequence m_sequences[3];
	BehaviourTree::Succeeder m_succeeders[3];
	std::vector<Entity *> m_entities;
	Entity * m_self;
	Entity * nearestPlayer;
	//Declare actions for AI
	Action * walkLeft,
		*walkRight,
		*attackOne,
		*attackTwo,
		*jump,
		*getNearest,
		*closeEnough,
		*checkPlayerDirection,
		*isHealthHigh,
		*Flee,
		*isPlayerAbove,
		*isPlayerHealthLow,
		*canKick,
		*kick,
		*punch,
		*moveToClosestPlayer,
		*drop;
};

#endif
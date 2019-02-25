#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "Component.h"
#include "BehaviourTree.h"
#include "Entity.h"
#include <vector>
#include "AiInputComponent.h"
#include "PlayerComponent.h"

class AIComponent : public Component
{
public:
	AIComponent(std::vector<Entity *> e, AiInputComponent * i, Entity * self, PlayerComponent * p) :
		m_entities(e),
		m_input(i),
		m_self(self),
		m_player(p)
	{

	}
	~AIComponent() {}

	//Declare Tree, selector nodes and sequence nodes
	BehaviourTree BT;
	BehaviourTree::Selector m_selectors[7];
	BehaviourTree::Sequence m_sequences[3];
	BehaviourTree::Sequence punchSequence;
	BehaviourTree::Succeeder m_succeeders[3];
	std::vector<Entity *> m_entities;
	Entity * m_self;
	Entity * nearestPlayer;
	AiInputComponent * m_input;
	PlayerComponent * m_player;
	//Declare actions for AI
};

#endif
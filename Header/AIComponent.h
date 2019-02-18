#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "Component.h"
#include "BehaviourTree.h"
#include "Action.h"

class AIComponent : public Component 
{
public:
	AIComponent() {}
	~AIComponent() {}

	//Declare Tree, selector nodes and sequence nodes
	BehaviourTree BT;
	BehaviourTree::Selector m_selectors[7];
	BehaviourTree::Sequence m_sequences[3];
	BehaviourTree::Succeeder m_succeeders[3];
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
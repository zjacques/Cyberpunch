#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "Component.h"
#include "BehaviourTree.h"
#include "Action.h"

class AIComponent : public Component 
{
public:
	AIComponent() { createTree(); }
	~AIComponent() {}

	void initialiseActions()
	{

	};

	/// <summary>
	/// Set the actions for the selector and sequence nodes
	/// </summary>
	void createTree()
	{
		//Root
		BT.setRootChild(&m_selectors[0]);

		//Left Sub Tree
		m_selectors[0].addChildren({ &m_sequences[0], &m_selectors[5]});
		m_sequences[0].addChildren({getNearest, closeEnough, &m_succeeders[0], &m_selectors[1], &m_selectors[3]});
		m_succeeders[0].setChild(checkPlayerDirection);
		m_selectors[1].addChildren({ isHealthHigh, &m_selectors[2]});
		m_selectors[2].addChildren({&m_succeeders[1], Flee});
		m_selectors[3].addChildren({isPlayerAbove, &m_selectors[4]});
		m_selectors[4].addChildren({isPlayerHealthLow, punch});

		//Right Sub Tree
		m_selectors[5].addChildren({ &m_sequences[1], &m_sequences[2] });
		m_sequences[1].addChildren({ getNearest, closeEnough });
		m_sequences[2].addChildren({&m_succeeders[1], &m_selectors[6]});
		m_selectors[6].addChildren({isPlayerAbove, drop});
	}

	/// <summary>
	/// Calls run function for the behaviour tree
	/// </summary>
	void runTree()
	{
		if (BT.run())
		{
			std::cout << "Success" << std::endl;
		}
		else
		{
			std::cout << "Failed" << std::endl;
		}
	}

	/*BehaviourTree BT;
	BehaviourTree::Selector m_selectors[7];
	BehaviourTree::Sequence m_sequences[3];
	BehaviourTree::Succeeder m_succeeders[3];*/
public:
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
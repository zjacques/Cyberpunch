#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "Component.h"
#include "BehaviourTree.h"
#include "Action.h"

class AIComponent : public Component 
{
public:
	AIComponent() { createTree(); }
	~AIComponent();
	void initialiseActions()
	{
		walkLeft = new Action("Walk left", 50);
		walkRight = new Action("Walk right", 50);
		attackOne = new Action("Attack 1", 75);
		attackTwo = new Action("Attack 2", 60);
		jump = new Action("Jump", 80);
	};

	/// <summary>
	/// Set the actions for the selector and sequence nodes
	/// </summary>
	void createTree()
	{
		BT.setRootChild(&m_selectors[0]);
		m_selectors[0].addChildren({ &m_sequences[0], &m_sequences[2] });
		m_sequences[0].addChildren({ walkLeft, &m_selectors[1], jump, attackOne});
		
		m_selectors[1].addChildren({ walkRight, &m_sequences[1], attackTwo });
		m_sequences[1].addChildren({ attackOne, attackTwo, jump });

		m_sequences[2].addChildren({ jump, &m_selectors[2], attackTwo, walkRight });
		m_selectors[2].addChildren({jump, walkLeft, attackTwo});
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
private:
	//Declare Tree, selector nodes and sequence nodes
	BehaviourTree BT;
	BehaviourTree::Selector m_selectors[3];
	BehaviourTree::Sequence m_sequences[3];

	//Declare actions for AI
	Action * walkLeft, * walkRight,
		* attackOne, * attackTwo, * jump;
};

#endif
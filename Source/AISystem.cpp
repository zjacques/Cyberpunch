#include "AISystem.h"

/// <summary>
/// Pushback new component into vector
/// </summary>
/// <param name="c"></param>
void AISystem::addComponent(Component * c)
{
	m_components.push_back(c);
	initialiseActions();
	createTree();
}

/// <summary>
/// Initialise the values of 
/// action nodes on behaviour tree
/// </summary>
void AISystem::initialiseActions()
{
	for (auto c : m_components)
	{
		//Cast all components as AIComponents
		auto cast_comp = dynamic_cast<AIComponent *>(c);

		cast_comp->walkLeft = new WalkLeftAction("Walk left", 100);
		cast_comp->walkRight = new WalkRightAction("Walk right", 100);
		cast_comp->attackOne = new PunchAction("Attack 1", 100);
		cast_comp->attackTwo = new PunchAction("Attack 2", 100);
		cast_comp->jump = new JumpAction("Jump", 100);
		cast_comp->getNearest = new CheckNearest("Nearest", 100);
		cast_comp->closeEnough = new CloseEnough("close", 100);
		cast_comp->checkPlayerDirection = new CheckPlayerDirection("PlayerDir", 100);
		cast_comp->isHealthHigh = new JumpAction("Health", 100);
		cast_comp->Flee = new JumpAction("Flee", 100);
		cast_comp->isPlayerAbove = new JumpAction("PlayerAbove", 100);
		cast_comp->isPlayerHealthLow = new JumpAction("Health low", 100);
		cast_comp->canKick = new JumpAction("Can kick", 100);
		cast_comp->punch = new JumpAction("Punch", 100);
		cast_comp->moveToClosestPlayer = new JumpAction("MoveTo", 100);
		cast_comp->drop = new JumpAction("Drop", 100);
	}
}

/// <summary>
/// Create structure of behaviour
/// tree using root, decorator,
/// and leaf nodes
/// </summary>
void AISystem::createTree()
{
	for (auto c : m_components)
	{
		auto cast_comp = dynamic_cast<AIComponent *>(c);

		//Set Behaviour Tree Root node
		cast_comp->BT.setRootChild(&cast_comp->m_sequences[0]);

		cast_comp->m_sequences[0].addChildren({ cast_comp->getNearest, cast_comp->closeEnough });

		/*

		//Left sub tree
		cast_comp->m_selectors[0].addChildren({&cast_comp->m_sequences[0], &cast_comp->m_selectors[5]});
		cast_comp->m_sequences[0].addChildren({ cast_comp->getNearest, cast_comp->closeEnough, 
			&cast_comp->m_succeeders[0], &cast_comp->m_selectors[1], &cast_comp->m_selectors[3] });
		cast_comp->m_succeeders[0].setChild(cast_comp->checkPlayerDirection);
		cast_comp->m_selectors[1].addChildren({ cast_comp->isHealthHigh, &cast_comp->m_selectors[2] });
		cast_comp->m_selectors[2].addChildren({ &cast_comp->m_succeeders[1], cast_comp->Flee });
		cast_comp->m_selectors[3].addChildren({ cast_comp->isPlayerAbove, &cast_comp->m_selectors[4] });
		cast_comp->m_selectors[4].addChildren({ cast_comp->isPlayerHealthLow, cast_comp->punch });

		//Right sub tree
		cast_comp->m_selectors[5].addChildren({ &cast_comp->m_sequences[1], &cast_comp->m_sequences[2] });
		cast_comp->m_sequences[1].addChildren({ cast_comp->getNearest, cast_comp->closeEnough });
		cast_comp->m_sequences[2].addChildren({ &cast_comp->m_succeeders[1], &cast_comp->m_selectors[6] });
		cast_comp->m_selectors[6].addChildren({ cast_comp->isPlayerAbove, cast_comp->drop });

		*/
	}
}

/// <summary>
/// Execute behaviour 
/// </summary>
void AISystem::runTree()
{
	for (auto c : m_components)
	{
		auto cast_comp = dynamic_cast<AIComponent *>(c);
		if (cast_comp->BT.run())
		{
			std::cout << "Behaviour tree exited with SUCCESS" << std::endl;
		}
		else
		{
			std::cout << "Behaviour tree exited with FAILURE" << std::endl;
		}
	}
}

/// <summary>
/// Update AIComponent
/// values here
/// </summary>
/// <param name="dt"></param>
void AISystem::update(double dt)
{
	runTree();
}
#include "AISystem.h"
#include "Action.h"

/// <summary>
/// Pushback new component into vector
/// </summary>
/// <param name="c"></param>
void AISystem::addComponent(Component * c)
{
	m_components.push_back(c);
	createTree();
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

		auto e = cast_comp->m_self;

		auto input = dynamic_cast<AiInputComponent *>(cast_comp->m_input);
		
		//Set Behaviour Tree Root node
		//cast_comp->BT.setRootChild(&cast_comp->m_sequences[0]);
		cast_comp->BT.setRootChild(&cast_comp->m_selectors[0]);

		//Left sub tree
		cast_comp->m_selectors[0].addChildren({&cast_comp->m_sequences[0], &cast_comp->m_selectors[5]});
		//cast_comp->m_selectors[0].addChildren({ &cast_comp->m_sequences[0], &cast_comp->m_selectors[0] });
		cast_comp->m_sequences[0].addChildren({ new CheckNearest(cast_comp->m_entities, e, input), new CloseEnough(e, input),
			&cast_comp->m_succeeders[0], &cast_comp->m_selectors[1], &cast_comp->punchSequence});
		cast_comp->m_succeeders[0].setChild(new CheckPlayerDirection(e, input));
		cast_comp->m_selectors[1].addChildren({ new CheckHealth(e, input), &cast_comp->m_selectors[2] });
		cast_comp->m_selectors[2].addChildren({ new PunchAction(e, input), new FleeAction(e, input) });
		cast_comp->punchSequence.addChildren({ new CheckAbove(e, input), &cast_comp->m_selectors[4] });
		cast_comp->m_selectors[4].addChildren({ new PunchAction(e, input), new PunchAction(e, input) });

		//Right sub tree
		cast_comp->m_selectors[5].addChildren({ &cast_comp->m_sequences[1], &cast_comp->m_sequences[2] });
		cast_comp->m_sequences[1].addChildren({ new CheckNearest(cast_comp->m_entities, cast_comp->m_self, input), new CloseEnough(e, input) });
		cast_comp->m_sequences[2].addChildren({ &cast_comp->m_succeeders[1], &cast_comp->m_selectors[6] });
		cast_comp->m_succeeders[1].setChild({ new MoveToPlayer(e, input) });
		cast_comp->m_selectors[6].addChildren({ new CheckAbove(e, input), new JumpAction(e, input) });
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
			//std::cout << "Behaviour tree exited with SUCCESS" << std::endl;
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
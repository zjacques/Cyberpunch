#ifndef ACTION_H
#define ACTION_H

#include "BehaviourTree.h"
#include "Entity.h"
#include "Component.h"
#include "PositionComponent.h"
#include "AIComponent.h"
#include "AiInputComponent.h"
#include "PlayerPhysicsComponent.h"

class Action : public BehaviourTree::Node
{
public:
	Action(Entity * e, AiInputComponent * a) :
	m_entity(e),
	m_input(a)
	{}

	virtual bool run() = 0;
	Entity * m_entity;
	AiInputComponent * m_input;
};

#endif

#ifndef WALKLEFTACTION_H
#define WALKLEFTACTION_H

class WalkLeftAction : public Action
{
public:
	WalkLeftAction(Entity * e, AiInputComponent * a) :
		Action(e, a)
	{
	}

	bool run() override
	{
		//std::cout << "Walking left" << std::endl;
		m_input->handleInput("STICKLEFT", m_entity);
		return true;
	}
};

#endif

#ifndef WALKRIGHTACTION_H
#define WALKRIGHTACTION_H

class WalkRightAction : public Action
{
public:
	WalkRightAction(Entity * e, AiInputComponent * a)
		: Action(e, a)
	{
	}

	bool run() override
	{
		//std::cout << "Walking right" << std::endl;
		m_input->handleInput("STICKRIGHT", m_entity);
		return true;
	}
};

#endif

#ifndef JUMPACTION_H
#define JUMPACTION_H

class JumpAction : public Action
{
public:
	JumpAction(Entity * e, AiInputComponent * a)
		: Action(e, a)
	{
	}
	bool run() override
	{
		//std::cout << "Jump" << std::endl;
		m_input->handleInput("YBTN", m_entity);
		return true;
	}
};

#endif

#ifndef PUNCHACTION_H
#define PUNCHACTION_H

class PunchAction : public Action
{
public:
	PunchAction(Entity * e, AiInputComponent * a)
		: Action(e, a)
	{
	}

	bool run() override
	{
		std::cout << "Punch" << std::endl;
		m_input->handleInput("XBTN", m_entity);
		return true;
	}
};

#endif

#ifndef CHECKNEAREST_H
#define CHECKNEAREST_H

class CheckNearest : public Action
{
public:
	CheckNearest(std::vector<Entity *> e, Entity * s, AiInputComponent * a) :
		m_entities(e), Action(s, a)
	{
	}

	/// <summary>
	/// Behaviour tree run function overidden from Action base class.
	/// Loops through vector of all players in the current game and 
	/// finds the one nearest to the current AI entity.
	/// </summary>
	/// <returns></returns>
	bool run() override
	{
		//std::cout << "Getting nearest player" << std::endl;
		//Container to store nearest entity
		auto nearest = new Entity("temp");

		//If entities vector is not empty, set nearest to first element
		if (!m_entities.empty())
		{
			nearest = m_entities.at(0);
		}

		//Get position component of current AI entity
		auto self_pos = dynamic_cast<PositionComponent *>(&m_entity->getComponent("Pos"));
		//Get position component from entity
		auto otherPos = dynamic_cast<PositionComponent *>(&nearest->getComponent("Pos"));

		//Loop through all entities
		for (auto entity : m_entities)
		{
			//Get position component of the current entity in the loop
			auto newPos = dynamic_cast<PositionComponent *>(&entity->getComponent("Pos"));
			//Check distance between self and previous position, and self and new position
			if (dist(newPos->position, self_pos->position) < dist(otherPos->position, self_pos->position))
			{
				//If new position is closer, the entity it belongs to is assigned to nearest
				nearest = entity;
			}
		}
		//Cast AI component
		auto e = dynamic_cast<AIComponent *>(&m_entity->getComponent("AI"));
		//Assign nearest player to variable in the AI 
		e->nearestPlayer = nearest;
		return true;
	}

	//Euclidean distance function
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
	CloseEnough(Entity * e, AiInputComponent * a)
		: Action(e, a)
	{
	}

	bool run() override
	{
		//std::cout << "Close enough" << std::endl;
		//Get AI component
		auto comp = dynamic_cast<AIComponent *>(&m_entity->getComponent("AI"));
		//Cast self component to PositionComponent
		auto pos = dynamic_cast<PositionComponent *>(&m_entity->getComponent("Pos"));
		//Cast nearest player entity from Ai component to Position component
		auto nearest = dynamic_cast<PositionComponent *>(&comp->nearestPlayer->getComponent("Pos"));
		//Return true if dist between two entities is less than 100
		return dist(pos->position, nearest->position) < 1000 ? true : false;
	}

	//Euclidean distance function
	float dist(Vector2f p1, Vector2f p2)
	{
		return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
	}
};

#endif

#ifndef CHECKPLAYERDIRECTION_H
#define CHECKPLAYERDIRECTION_H

class CheckPlayerDirection : public Action
{
public:
	CheckPlayerDirection(Entity * e, AiInputComponent * a)
		: Action(e, a)
	{
	}

	/// <summary>
	/// Run function overidden from the Action base class
	/// casts a vector from the AI entity to the nearest
	/// player as one of 4 directions
	/// </summary>
	/// <returns></returns>
	bool run() override
	{
		//Get AI component
		auto comp = dynamic_cast<AIComponent *>(&m_entity->getComponent("AI"));

		//std::cout << "Check direction" << std::endl;
		//Cast self component to PositionComponent
		auto pos = dynamic_cast<PositionComponent *>(&m_entity->getComponent("Pos"));

		//Cast nearest player entity from Ai component to Position component
		auto nearest = dynamic_cast<PositionComponent *>(&comp->nearestPlayer->getComponent("Pos"));

		//Check if the nearest player is to the left of AI
		if (nearest->position.x < pos->position.x)
		{
			//move left
			m_input->handleInput("STICKLEFT", m_entity);
		} //Check if the nearest player is to the right of AI
		else if (nearest->position.x > pos->position.x)
		{
			//move right
			m_input->handleInput("STICKRIGHT", m_entity);
		}
		else //If player and AI are on the same X coord, jump
		{
			//jump
			m_input->handleInput("YBTN", m_entity);
		}
		//Return function as true to continue tree iteration
		return true;
	}

	//Euclidean distance function
	float dist(Vector2f p1, Vector2f p2)
	{
		return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
	}
};

#endif

#ifndef CHECKHEALTH_H
#define CHECKHEALTH_H

class CheckHealth : public Action
{
public:
	CheckHealth(Entity * e, AiInputComponent * a)
		: Action(e, a)
	{
	}

	/// <summary>
	/// Run function overidden from the Action base class function.
	/// Down casts the self entity component to a play physics component.
	/// Returns true if the current damage percentage is greater than 50
	/// </summary>
	/// <returns></returns>
	bool run() override
	{
		//std::cout << "Check health" << std::endl;
		auto p = dynamic_cast<PlayerPhysicsComponent *>(&m_entity->getComponent("Player Physics"));
		return p->damagePercentage() > 50 ? true : false;
	}
};

#endif

#ifndef FLEEACTION_H
#define FLEEACTION_H

class FleeAction : public Action
{
public:
	FleeAction(Entity * e, AiInputComponent * a)
		: Action(e, a)
	{
	}

	bool run() override
	{
		//std::cout << "Fleeing" << std::endl;

		//Get AI component
		auto comp = dynamic_cast<AIComponent *>(&m_entity->getComponent("AI"));

		std::cout << "Check direction" << std::endl;
		//Cast self component to PositionComponent
		auto pos = dynamic_cast<PositionComponent *>(&m_entity->getComponent("Position"));

		//Cast nearest player entity from Ai component to Position component
		auto nearest = dynamic_cast<PositionComponent *>(&comp->nearestPlayer->getComponent("Pos"));

		while (dist(pos->position, nearest->position) < 200)
		{
			if (nearest->position.x < pos->position.x)
			{
				m_input->handleInput("STICKRIGHT", m_entity);
			}
			else
			{
				m_input->handleInput("STICKLEFT", m_entity);
			}
		}
		return true;
	}

	//Euclidean distance function
	float dist(Vector2f p1, Vector2f p2)
	{
		return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
	}
};

#endif

#ifndef CHECKABOVE_H
#define CHECKABOVE_H

class CheckAbove : public Action
{
public:
	CheckAbove(Entity * e, AiInputComponent * a)
		: Action(e, a)
	{}

	bool run() override
	{
		//std::cout << "Check if player above" << std::endl;

		//Get AI component
		auto comp = dynamic_cast<AIComponent *>(&m_entity->getComponent("AI"));

		std::cout << "Check direction" << std::endl;
		//Cast self component to PositionComponent
		auto pos = dynamic_cast<PositionComponent *>(&m_entity->getComponent("Pos"));

		//Cast nearest player entity from Ai component to Position component
		auto nearest = dynamic_cast<PositionComponent *>(&comp->nearestPlayer->getComponent("Pos"));

		//Return function true if player position is below(screen axis) the AI 
		return nearest->position.y > pos->position.y ? true : false;
	}
};

#endif

#ifndef CHECKPLAYERHEALTH_H
#define CHECKPLAYERHEALTH_H

class CheckPlayerHealth : public Action
{
public:
	CheckPlayerHealth(Entity * e, AiInputComponent * a)
		: Action(e, a)
	{}

	/// <summary>
	/// Run function overidden from Action base class.
	/// Checks if the nearest players damage percentage
	/// is high enough to attack them
	/// </summary>
	/// <returns></returns>
	bool run() override
	{
		//std::cout << "Check player health" << std::endl;

		//Get AI component
		auto comp = dynamic_cast<AIComponent *>(&m_entity->getComponent("AI"));

		//Cast nearest player entity from Ai component to Position component
		auto nearest = dynamic_cast<PlayerPhysicsComponent *>(&comp->nearestPlayer->getComponent("Player Physics"));

		//Return true if nearest players damage % is greater than 50
		return nearest->damagePercentage() > 50 ? true : false;
	}
};

#endif

#ifndef DROPACTION_H
#define DROPACTION_H

class DropAction : public Action
{
public:
	DropAction(Entity * e, AiInputComponent * a)
		: Action(e, a)
	{}

	bool run() override
	{
		//std::cout << "Drop down" << std::endl;
		m_input->handleInput("STICKDOWN", m_entity);
		return true;
	}
};

#endif
#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "Component.h"
#include "BehaviourTree.h"
#include "Entity.h"
#include <vector>
#include "AiInputComponent.h"
#include "PlayerComponent.h"
#include "Box2DBridge.h"

class AIComponent : public Component
{
public:
	AIComponent(std::vector<Entity *>* e, AiInputComponent * i, Entity * self, PlayerComponent * p, Box2DBridge & world) :
		m_entities(e),
		m_input(i),
		m_self(self),
		m_player(p),
		m_world(world)
	{
		m_phys = new PhysicsComponent(static_cast<PositionComponent *>(&self->getComponent("Pos")));
		auto pos = static_cast<PositionComponent *>(&self->getComponent("Pos"))->position;
		m_phys->m_body = m_world.createBox(pos.x, pos.y, 75, 25, false, true, b2_staticBody);
		m_world.addProperties(*m_phys->m_body, 0, 0, 0, true, new PhysicsComponent::ColData("Edge Sensor", m_self));
	}
	~AIComponent() {}

	//Declare Tree, selector nodes and sequence nodes
	BehaviourTree BT;
	BehaviourTree::Selector m_selectors[7];
	BehaviourTree::Sequence m_sequences[3];
	BehaviourTree::Sequence punchSequence;
	BehaviourTree::Succeeder m_succeeders[3];
	std::vector<Entity *>* m_entities;
	Entity * m_self;
	Entity * nearestPlayer;
	AiInputComponent * m_input;
	PlayerComponent * m_player;
	PhysicsComponent * m_phys;
	Box2DBridge m_world;

	bool onEdge = false;
	
	//Declare actions for AI
};

#endif
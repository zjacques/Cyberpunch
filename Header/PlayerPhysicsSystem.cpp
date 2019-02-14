#include "PlayerPhysicsSystem.h"

void PlayerPhysicsSystem::setWorld(Box2DBridge & world)
{
	m_worldPtr = &world;
}

void PlayerPhysicsSystem::addComponent(Component * comp)
{
	m_components.push_back(comp);
}

void PlayerPhysicsSystem::update(double dt)
{
	for (auto& comp : m_components)
	{
		//Convert the component down to a player physics component
		auto p = static_cast<PlayerPhysicsComponent*>(comp);

		//Get the velocity of the player
		p->m_currentVel = p->m_body->getBody()->GetLinearVelocity();

		//if we are to move, call move and the direction to move (-1, 1)
		if (p->m_desiredVel.x != 0)
			p->move(p->m_desiredVel.x);
		if (p->m_desiredVel.y != 0)
			p->moveUp(p->m_desiredVel.y);

		if (p->m_desiredVel.x == 0)
			p->m_currentVel.x *= .98f;

		//Set the velocity of the player
		p->m_body->getBody()->SetLinearVelocity(p->m_currentVel);

		//Reset desired velocity
		p->m_desiredVel = b2Vec2(0,0);

		//check if to unstun the player
		if (p->stunned())
		{
			p->stunLeft() -= dt;

			if (p->stunLeft() <= 0)
			{
				p->stunned() = false;
			}
		}
	}
}

void PlayerPhysicsSystem::flipGravity()
{
	m_gravFlipped = !m_gravFlipped;
}

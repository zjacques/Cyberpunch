#include "PhysicsSystem.h"

void PhysicsSystem::addComponent(Component * comp)
{
	//Add component to the system
	m_components.push_back(comp);
}

void PhysicsSystem::update(double dt)
{
	//Loop through all of the physics components and set the position components based on their physics position
	for (auto& comp : m_components)
	{
		//Convert the component to a physics component
		auto p = dynamic_cast<PhysicsComponent*>(comp);

		//Assign the bodies position the position component
		p->posPtr->position = p->m_body->getPosition();
	}
}

#include "DJboothComponent.h"

DJBoothComponent::DJBoothComponent() 
{
	
}

void DJBoothComponent::spawn(Box2DBridge & world)
{
	//creates the Djbooths box2d bodies and defines their proporties
	m_body = new PhysicsComponent(new PositionComponent(0, 0));
	m_body->m_body = world.createBox(1920 / 2, 1080 / 2, 50, 50, false, false, b2BodyType::b2_staticBody);
	world.addProperties(*m_body->m_body, 0, 0, 0, true, new PhysicsComponent::ColData("Booth", this));
} 
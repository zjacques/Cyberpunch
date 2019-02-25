#include "..\Header\PickUpComponent.h"

PickUpComponent::PickUpComponent(Entity* pickupEntity) :
	m_pickupEntity(pickupEntity),
	m_timeLive(10),
	m_timeTillSpawn(10),
	m_spawned(false)
{
}

void PickUpComponent::spawn(Box2DBridge & world)
{
	m_spawned = true;
	m_timeLive = 10; //10 seconds
	m_body = new PhysicsComponent(new PositionComponent(0,0));

	//creates a box2d body for the pickup and defines it proporties
	m_body->m_body = world.createBox(1920 / 2, 800, 50, 50, false, false, b2BodyType::b2_staticBody);
	world.addProperties(*m_body->m_body, 0, 0, 0, true, new PhysicsComponent::ColData("Pickup", m_pickupEntity));
	
	static_cast<PositionComponent*>(&m_pickupEntity->getComponent("Pos"))->position = Vector2f(1920/ 2, 800);
}

void PickUpComponent::despawn(Box2DBridge & world)
{
	//despawns the record after its been spawned for 10 seconds
	m_timeTillSpawn = 10; //10 seconds
	m_spawned = false;

	world.deleteBody(m_body->m_body);

	m_body = nullptr;
}
#pragma once
#include "DJboothComponent.h"
#include "CollisionListener.h"
#include "Entity.h"

class PlatformBoothComponent : public DJBoothComponent
{
public:
	PlatformBoothComponent(std::vector<Entity*>* allPlatforms):
		m_entities(allPlatforms),
		m_timer(0),
		m_active(false),
		m_speed(100),
		m_halfPoint(false)
	{

	}
	void run()
	{
		std::cout << "Platform moving booth\n";
		m_active = true;
		m_timer = 15;
		m_halfPoint = false;
	}

	void update(double dt)
	{
		if (m_active)
		{
			m_timer -= dt;

			if (m_halfPoint == false)
			{
				m_speed -= .175f * dt;

				for (auto& comp : *m_entities)
				{
					auto platform = static_cast<PhysicsComponent*>(&comp->getComponent("Physics"));

					if (comp->m_ID == "Platform")
					{
						float temp = platform->m_body->getPosition().x - (m_speed * dt);
						platform->m_body->setPosition(temp, platform->m_body->getPosition().y);
					}
				}

				if (m_speed <= 0.65f)
				{
					m_speed += .175f * dt;
					m_halfPoint = true;
				}
			}
			else if (m_timer <= 2)
			{
				m_speed -= .175 * dt;
			}

			if (m_timer <= 0)
			{
				m_active = false;
				m_speed = 0;
			}	
		}
	}

	void movePlatforms()
	{

	}
	float& getTimeLeft() { return m_timer; }
	float& getSpeed() { return m_speed; }
private:
	float m_timer;
	bool m_active;
	float m_halfPoint;
	float m_speed;
	std::vector<Entity*>* m_entities;

};
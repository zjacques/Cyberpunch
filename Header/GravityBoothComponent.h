#pragma once
#include "Box2DBridge.h"
#include "CollisionListener.h"
#include "DJboothComponent.h"
#include "Entity.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerPhysicsSystem.h"

class GravityBoothComponent : public DJBoothComponent
{
public: 
	GravityBoothComponent(std::vector<Entity*> allPlayers, Box2DBridge* world,
		PlayerPhysicsSystem* physSys, CollisionListener* cL, Entity* pickUp) :
		m_systemPtr(physSys),
		m_entities(allPlayers),
		m_collistenerPtr(cL),
		m_worldPtr(world), 
		m_timer(0),
		DJBoothComponent(pickUp)
	{
		

	}


	void run()
	{
		std::cout << "Flipping Grvaity booth\n";
		bgSwitch = true;
		flipGrav();

	}
	void update(double dt)
	{
		if (m_timer > 0)
		{
			m_timer -= dt;

			if (m_timer <= 0)
			{
				unflipGrav();
			}
		}
	}
  
	void flipGrav()
	{

		m_timer = 10; //10 seconds flipped
		for (auto& comp : m_entities)
		{
			auto s = static_cast<SpriteComponent*>(&comp->getComponent("Sprite"));
			s->setScale(s->getScale().x, -1);
		}

		m_worldPtr->flipGravity();
		m_collistenerPtr->flipGravity();
		m_systemPtr->flipGravity();
	}

	void unflipGrav()
	{
		m_timer = 0;
		for (auto& comp : m_entities)
		{
			auto s = static_cast<SpriteComponent*>(&comp->getComponent("Sprite"));
			s->setScale(s->getScale().x, 1);
		}
		m_worldPtr->flipGravity();
		m_collistenerPtr->flipGravity();
		m_systemPtr->flipGravity();
	}

	float& getTimeLeft() { return m_timer; }
private:
	float m_timer;
	std::vector<Entity*> m_entities;
	Box2DBridge* m_worldPtr;
	PlayerPhysicsSystem* m_systemPtr;
	CollisionListener* m_collistenerPtr;
};
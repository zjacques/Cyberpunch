#pragma once
#include "Box2DBridge.h"
#include "CollisionListener.h"
#include "DJboothComponent.h"
#include "Entity.h"
#include "PlayerPhysicsComponent.h"

class GravityBoothComponent : public DJBoothComponent
{
public: 
	GravityBoothComponent(std::vector<Entity*> allPlayers, Box2DBridge* world,
		PhysicsSystem* physSys, CollisionListener* cL) :
		m_systemPtr(physSys),
		m_entities(allPlayers),
		m_collistenerPtr(cL),
		m_worldPtr(world), 
		m_timer(0)
	{
		

	}


	void run()
	{
		std::cout << "Flipping Grvaity booth\n";
		
		flipGrav();

	}
	void update(double dt)
	{
	}
  
	void flipGrav()
	{

		m_timer = 10; //10 seconds flipped
		for (auto& comp : m_entities)
		{
			static_cast<PlayerPhysicsComponent*>(&comp->getComponent("Player Physics"))->flipGravity();
			auto s = static_cast<SpriteComponent*>(&comp->getComponent("Sprite"));
			s->setScale(s->getScale().x, -1);
			m_worldPtr->flipGravity();
			m_collistenerPtr->flipGravity();
			m_systemPtr->flipGravity();
		}
	}

	void unflipGrav()
	{
		m_timer = 0;
		for (auto& comp : m_entities)
		{
			static_cast<PlayerPhysicsComponent*>(&comp->getComponent("Player Physics"))->flipGravity();
			auto s = static_cast<SpriteComponent*>(&comp->getComponent("Sprite"));
			s->setScale(s->getScale().x, 1);
			m_worldPtr->flipGravity();
			m_collistenerPtr->flipGravity();
			m_systemPtr->flipGravity();
		}
	}

	float& getTimeLeft() { return m_timer; }
private:
	float m_timer;
	std::vector<Entity*> m_entities;
	Box2DBridge* m_worldPtr;
	PhysicsSystem* m_systemPtr;
	CollisionListener* m_collistenerPtr;
};
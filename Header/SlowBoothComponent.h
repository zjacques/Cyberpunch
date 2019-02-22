#pragma once
#pragma once
#include "DJboothComponent.h"
#include "CollisionListener.h"
#include "DJboothComponent.h"
#include "Entity.h"
#include "PlayerPhysicsComponent.h"

class SlowBoothComponent : public DJBoothComponent
{
public:
	SlowBoothComponent(std::vector<Entity*> allPlayers, Box2DBridge* world,
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
		m_timer = 10;
		for (auto& comp : m_entities)
		{
			std::cout << "Slowing down booth\n";
			//static_cast<PlayerPhysicsComponent*>(&comp->getComponent("Player Physics"))->flipGravity();
			//auto s = static_cast<SpriteComponent*>(&comp->getComponent("Sprite"));
			//s->setScale(s->getScale().x, -1);
			
		
		}
	}
	

private: 
	float m_timer;
	std::vector<Entity*> m_entities;
	Box2DBridge* m_worldPtr;
	PhysicsSystem* m_systemPtr;
	CollisionListener* m_collistenerPtr;
};
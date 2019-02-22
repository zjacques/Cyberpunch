#pragma once
#include "DJboothComponent.h"
#include "CollisionListener.h"
#include "Entity.h"

class PlatformBoothComponent : public DJBoothComponent
{
public:
	PlatformBoothComponent(std::vector<Entity*> allPlatforms, Box2DBridge* world):
		m_entities(allPlatforms), m_timer(0)
	{

	}
	void run()
	{
	//	std::cout << "Platform moving booth\n";
	}

	void movePlatforms()
	{
		for (auto& comp : m_entities)
		{
			static_cast<PhysicsComponent*>(&comp->getComponent("Platforms"));
			auto s = static_cast<SpriteComponent*>(&comp->getComponent("Sprite"));
			
			//m_worldPtr->flipGravity();
			//m_collistenerPtr->flipGravity();
			//m_systemPtr->flipGravity();
		}
	}

private:
	float m_timer;
	std::vector<Entity*> m_entities;
	Box2DBridge* m_worldPtr;
};
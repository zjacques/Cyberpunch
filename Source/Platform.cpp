#include "Platform.h"

Platform::Platform()
{
}

void Platform::createPlatforms(Box2DBridge& world, PhysicsSystem& system)
{
	m_physicsComponents.push_back(PhysicsComponent(new PositionComponent(1280 / 2, 720 - 25)));
	m_physicsComponents.at(0).m_body = world.createBox(1280 / 2, 720 - 25, 1280, 50, false, b2BodyType::b2_staticBody);
	world.addProperties(*m_physicsComponents.at(0).m_body, 0, 1, false, this);
}

void Platform::deletePlatforms()
{
	m_physicsComponents.clear();
}

void Platform::draw(SDL_Renderer & renderer)
{
	//Draw each platform, this is just for debugging for now
	for (auto& body : m_physicsComponents)
	{
		m_rect.x = body.m_body->getPosition().x;
		m_rect.y = body.m_body->getPosition().y;
		m_rect.w = body.m_body->getSize().x;
		m_rect.h = body.m_body->getSize().y;

		SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(&renderer, &m_rect);
	}
}

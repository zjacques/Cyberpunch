#pragma once
#include "SDL.h"
#include "Box2DBridge.h"
#include "PhysicsSystem.h"

class Platform
{
public:
	Platform();

	void createPlatforms(Box2DBridge& world, PhysicsSystem& system);
	void deletePlatforms();

	void draw(SDL_Renderer& renderer);
	std::vector<PhysicsComponent> m_physicsComponents;
private:
	SDL_Rect m_rect;

	//std::vector<PhysicsComponent> m_physicsComponents;
};
#pragma once
#include "SDL.h"
#include "Box2DBridge.h"
#include "PhysicsSystem.h"
#include "ResourceManager.h"


class Platform
{
public:
	Platform();

	void createPlatforms(ResourceHandler& resources, Box2DBridge& world, PhysicsSystem& system);
	void deletePlatforms();

	void draw(SDL_Renderer& renderer);
private:
	SDL_Rect m_rect;

	std::vector<PhysicsComponent> m_physicsComponents;
};
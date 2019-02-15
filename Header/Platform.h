#pragma once
#include "SDL.h"
#include "Box2DBridge.h"
#include "PhysicsSystem.h"
#include "ResourceManager.h"


class Platform
{
public:
	Platform(std::string tag);

	void draw(SDL_Renderer& renderer);
	PhysicsComponent& getPhysComp() { return m_physicsComponents; }
	std::string& getTag() { return m_tag; }

	void setTexture(ResourceHandler& resources, std::string colour);
	void setAmountOfTiles();
private:
	Vector2f m_startpos, m_offset;
	Vector2f m_size;
	int m_numberofTiles; //The number of tiles for the platform
	std::string m_tag;
	SDL_Rect m_rect, m_srcRect;
	SDL_Texture* m_startCap, *m_middle, *m_endCap;

	PhysicsComponent m_physicsComponents;
};
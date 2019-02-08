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
	void addContact() { m_numberOfContacts++; }
	void removeContact() { m_numberOfContacts--; }
	PhysicsComponent& getPhysComp() { return m_physicsComponents; }
	std::string& getTag() { return m_tag; }
private:
	int m_numberOfContacts;
	std::string m_tag;
	SDL_Rect m_rect;

	PhysicsComponent m_physicsComponents;
};
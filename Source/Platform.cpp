#include "Platform.h"

Platform::Platform(std::string tag) :
	m_numberOfContacts(0),
	m_tag(tag),
	m_physicsComponents(new PositionComponent(0,0))
{
}

void Platform::draw(SDL_Renderer & renderer)
{
	m_rect.w = m_physicsComponents.m_body->getSize().x;
	m_rect.h = m_physicsComponents.m_body->getSize().y;
	m_rect.x = m_physicsComponents.m_body->getPosition().x - (m_rect.w / 2.0f);
	m_rect.y = m_physicsComponents.m_body->getPosition().y - (m_rect.h / 2.0f);

	SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(&renderer, &m_rect);
}

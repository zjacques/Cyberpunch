#include "Platform.h"

Platform::Platform(std::string tag) :
	m_numberofTiles(0),
	m_tag(tag),
	m_physicsComponents(new PositionComponent(0,0))
{
	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = 50;
	m_srcRect.h = 50;

	m_size = Vector2f(50 * (m_tag == "Floor" ? 1 : .5f), 50 * (m_tag == "Floor" ? 1 : .5f));
	auto w = m_tag == "Floor" ? 50 : 25;
	m_offset = Vector2f(m_size.x - w, m_size.y - w);

}

void Platform::draw(SDL_Renderer & renderer)
{
	m_rect.w = m_physicsComponents.m_body->getSize().x;
	m_rect.h = m_physicsComponents.m_body->getSize().y;
	m_rect.x = m_physicsComponents.m_body->getPosition().x - (m_rect.w / 2.0f);
	m_rect.y = m_physicsComponents.m_body->getPosition().y - (m_rect.h / 2.0f);

	SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 75);
	//SDL_RenderFillRect(&renderer, &m_rect);

	//Draw all of the tiles
	for (int i = 0; i < m_numberofTiles; i++)
	{
		m_rect.w = m_size.x;
		m_rect.h = m_size.y;
		m_rect.x = (m_startpos.x + m_size.x * i) - (m_offset.x / 2);
		m_rect.y = m_startpos.y - (m_offset.y / 2);

		if (i == 0)
		{
			SDL_RenderCopy(&renderer, m_startCap, &m_srcRect, &m_rect);
		}
		else if (i == (m_numberofTiles - 1))
		{
			SDL_RenderCopy(&renderer, m_endCap, &m_srcRect, &m_rect);
		}
		else
		{
			SDL_RenderCopy(&renderer, m_middle, &m_srcRect, &m_rect);
		}
	}
}

void Platform::setTexture(ResourceHandler & resources, std::string colour)
{
	//Get the three textures
	m_startCap = resources.getTexture("Platform " + colour + " 0");
	m_middle = resources.getTexture("Platform " + colour + " 1");
	m_endCap = resources.getTexture("Platform " + colour + " 2");

	//Get the start position
	auto bodyPos = m_physicsComponents.m_body->getPosition();
	auto bodySize = m_physicsComponents.m_body->getSize();
	m_startpos = Vector2f((int)bodyPos.x - ((int)bodySize.x / 2), (int)bodyPos.y - ((int)bodySize.y / 2));
}

void Platform::setAmountOfTiles()
{
	auto bodySize = m_physicsComponents.m_body->getSize();

	m_numberofTiles = (int)bodySize.x / (m_tag == "Floor" ? 50 : 25);
}

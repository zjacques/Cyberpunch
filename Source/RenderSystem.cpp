#include "../Header/RenderSystem.h"

/// <summary>
/// 
/// </summary>
void RenderSystem::initWindow(SDL_Window * window, SDL_Surface * surface, SDL_Renderer * renderer)
{
	m_window = window;
	m_drawSurface = surface;
	m_renderer = renderer;

	SCREEN_WIDTH = 1920.f;
	SCREEN_HEIGHT = 1080.f;
}

/// <summary>
/// Add a new component to the vector
/// in the renderSystem
/// </summary>
/// <param name="c"></param>
void RenderSystem::addComponent(Component * c)
{
	m_components.push_back(c);
}

/// <summary>
/// Uses SDL_RenderCopy to draw
/// object using parametres from 
/// the component class
/// </summary>
void RenderSystem::render(SDL_Rect * src, SDL_Rect * dst, SDL_Texture * t)
{
	SDL_RenderCopy(m_renderer, t, src, dst);
}

/// <summary>
/// Loops through render components
/// creates SDL_Rects using their values
/// and calls render function.
/// </summary>
void RenderSystem::update(double dt)
{
	for (auto c : m_components)
	{
		if (c->m_ID == "RENDER")
		{
			RenderComponent * temp = dynamic_cast<RenderComponent *>(c);
			SDL_Rect * src;
			src->x = temp->getPosition().x;
			src->y = temp->getPosition().y;
			src->w = temp->getBounds().x;
			src->h = temp->getBounds().y;
		}
	}
}


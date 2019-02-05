#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "Component.h"
#include "Vector2f.h"
#include <SDL.h>

class RenderComponent : public Component
{
public:
	Vector2f getPosition(){ return m_position; }
	Vector2f getBounds() { return m_bounds; }
	SDL_Surface * getSurface() { return m_surface; }
	SDL_Texture * getTexture() { return m_texture; }

private:
	Vector2f m_position;
	Vector2f m_bounds;
	SDL_Surface * m_surface;
	SDL_Texture * m_texture;
};

#endif

#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Component.h"
#include <SDL.h>
#include "Vector2f.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(Vector2f p, Vector2f b, SDL_Texture * t):
		m_position(p),
		m_bounds(b),
		m_texture(t) 
	{
		m_src = { m_position.x, m_position.y, m_bounds.x, m_bounds.y };
		m_dst = { 0, 0, m_bounds.x, m_bounds.y };
	}
	Vector2f getPosition() { return m_position; }
	Vector2f getBounds() { return m_bounds; }
	SDL_Texture * getTexture() { return m_texture; }
	SDL_Rect getSourceRect() { return m_src; }
	SDL_Rect getDestRect() { return m_dst; }
private:
	Vector2f m_position;
	Vector2f m_bounds;
	SDL_Rect m_src;
	SDL_Rect m_dst;
	SDL_Texture * m_texture;
};

#endif
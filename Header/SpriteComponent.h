#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL.h>
#include "PositionComponent.h"
#include "Vector2f.h"

class SpriteComponent : public Component
{
public:
	//Sprite component take sin the position component (where its placed), the overallSize of the sprite
	//the size of a single frame (this can be the same as overall size if its a 1 frame sprite)
	//the texture itself and the layer of the sprite
	SpriteComponent(Component* pos, Vector2f overallSize, Vector2f singleFramebounds, SDL_Texture * texture, int layer = 0):
		m_bounds(overallSize),
		m_singleFrameBounds(singleFramebounds),
		m_texture(texture),
		m_layer(layer),
		m_posPtr(pos)
	{
		m_src = { 0, 0, (int)overallSize.x, (int)overallSize.y };
		m_dst = { 0, 0, (int)singleFramebounds.x, (int)singleFramebounds.y };
	}

	//Setters
	void setTexture(SDL_Texture* texture) { m_texture = texture; }
	void setCurrentFrame(SDL_Rect& frame) { m_src = frame; }

	//Getters

	Vector2f& getPosition() { return static_cast<PositionComponent*>(m_posPtr)->position; }
	Vector2f getBounds() { return m_bounds; }
	Vector2f getFrameSize() { return m_singleFrameBounds; }
	SDL_Texture* getTexture() { return m_texture; }
	SDL_Rect getSourceRect() { return m_src; }
	SDL_Rect getDestRect() { return m_dst; }
	int getLayer() { return m_layer; }
private:
	Component* m_posPtr;
	Vector2f m_bounds, m_singleFrameBounds;
	SDL_Rect m_src;
	SDL_Rect m_dst;
	SDL_Texture * m_texture;
	int m_layer;
};

#endif
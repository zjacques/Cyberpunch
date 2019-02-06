#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "Component.h"
#include "Vector2f.h"
#include <SDL.h>

class RenderComponent : public Component
{
public:
	SDL_Rect * getSourceRect() { return m_src; }
	SDL_Rect * getDestRect() { return m_dst; }
	SDL_Surface * getSurface() { return m_surface; }
	SDL_Texture * getTexture() { return m_texture; }
	std::string getTexturePath() { return filepath; }
private:
	SDL_Rect * m_src;
	SDL_Rect * m_dst;
	SDL_Surface * m_surface;
	SDL_Texture * m_texture;
	std::string filepath;
};

#endif
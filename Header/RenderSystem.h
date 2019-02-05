#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "System.h"
#include <SDL.h>
#include "../Header/RenderComponent.h"

class RenderSystem : public System
{
public:
	void initWindow(SDL_Window *, SDL_Surface *, SDL_Renderer *);
	void update(double dt);
	void addComponent(Component *);
	void render(SDL_Rect *, SDL_Rect *, SDL_Texture *);
	void loadTexture();

private:
	SDL_Window * m_window;
	SDL_Surface * m_drawSurface;
	SDL_Renderer * m_renderer;

	float SCREEN_WIDTH;
	float SCREEN_HEIGHT;
};

#endif
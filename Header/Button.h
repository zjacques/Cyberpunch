#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include "../Libraries/SDL_TTF/include/SDL_ttf.h"
#include "../Libraries/SDL_image/include/SDL_image.h"
#include <string>
#include <iostream>

class Button
{
public:
	Button();
	~Button();

private:
	SDL_Rect * m_rect;
	SDL_Surface * m_surface;
	SDL_Texture * m_texture;
	std::string m_text;
};

#endif

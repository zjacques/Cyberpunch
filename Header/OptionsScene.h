#ifndef OPTIONSSCENE_H
#define OPTIONSSCENE_H

#include "Scene.h"
#include "../Libraries/SDL_TTF/include/SDL_ttf.h"

class OptionsScene : public Scene
{
public:
	OptionsScene();
	~OptionsScene();
	void start();
	void stop();
	void update(double dt);
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);
private:
	SDL_Rect * button_tst;
	SDL_Surface * txtSurface;
	SDL_Texture * txt_texture;
	TTF_Font* m_font;
	SDL_Rect txtPos = { 100, 100, 100, 50 };
	SDL_Color fgColour = { 255, 0, 0 , 255 };
};

#endif

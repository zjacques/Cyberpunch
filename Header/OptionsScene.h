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

};

#endif

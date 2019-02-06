#pragma once
#include "Scene.h"

class OptionsScene : public Scene
{
public:
	OptionsScene();
	void start();
	void stop();
	void update(double dt);
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);
private:
};
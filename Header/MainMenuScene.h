#pragma once
#include "Scene.h"

//The main menu scene, from here we navigate to the other scenes of the game
class MainMenuScene : public Scene
{
public:
	MainMenuScene();
	void start();
	void stop();
	void update(double dt);
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);
private:
};
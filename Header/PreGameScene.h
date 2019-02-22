#pragma once
#include "Scene.h"


class PreGameScene : public Scene {
public:
	PreGameScene();
	void start();
	void stop();
	void update(double dt);
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);
private:
	InputComponent m_input;

};
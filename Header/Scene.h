#pragma once
#include "SDL.h"
#include <iostream>
#include "InputSystem.h"

//Base scene class, this iwll be inherite dby every other scene
class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void update(double dt) = 0;
	virtual void handleInput(InputSystem& input) = 0;
	virtual void draw(SDL_Renderer& renderer) = 0;
};
#pragma once
#include "Box2DBridge.h"
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <bitset>

#include "../Header/Component.h"
#include "../Header/RenderComponent.h"
#include "../Header/RenderSystem.h"

class Game
{
public:
	Game(int fps);

	//Update the game passing in delta time
	void update(double dt);

	//Draw game components
	void draw();

	void processEvents(SDL_Event& e);

	void setupPhysics();

	void run();
	//Starts up SDL and creates window
	bool init();
	//Loads media
	bool loadMedia();
	//Frees media and shuts down SDL
	void close();

private:
	//Screen dimension constants
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;

	//The window we'll be rendering to
	SDL_Window* m_window;
	//The surface contained by the window
	SDL_Surface* m_screenSurface;
	//The renderer, we will use this to draw images
	SDL_Renderer* m_renderer;

	Box2DBridge m_world;

	float m_msPerFrame;
	bool m_quit;

	//Components
	RenderComponent * testComponent;

	//Systems
	RenderSystem * testSystem;

	//Entities
};
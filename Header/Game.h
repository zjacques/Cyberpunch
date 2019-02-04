#pragma once
#include "Box2D/Box2D.h"
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <chrono>

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
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	//The window we'll be rendering to
	SDL_Window* m_window;
	//The surface contained by the window
	SDL_Surface* m_screenSurface;

	//Physics variables
	b2World* m_physWorld;
	const int32 VELOCITY_ITERS = 8;   //how strongly to correct velocity
	const int32 POSITION_ITERS = 3;   //how strongly to correct position

	float m_msPerFrame;
	bool m_quit;
};
#include "Game.h"

Game::Game(int fps) :
	m_msPerFrame(fps / 60.0f), //Get the target fps
	m_window(NULL),
	m_screenSurface(NULL),
	m_quit(false),
	m_resources("./Resources/")
{
	if (TTF_Init() < 0)
	{
		printf("TTF_Init: %s\n", TTF_GetError());
	}

	testComponent = new RenderComponent();
	testSystem = new RenderSystem();

	testSystem->addComponent(testComponent);

	m_input.addComponent(&m_inputComp);
}

void Game::update(double dt)
{
	testSystem->update(dt);

	//Updat ethe input handler
	m_input.update(dt);

	//Update the menu manager
	m_mManager.update(dt);
}

void Game::draw()
{
	//Clear the screen with a colour of black
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	//Draw the current scene
	m_mManager.draw(*m_renderer);

	//Render everything drawn to the renderer
	SDL_RenderPresent(m_renderer);
}

void Game::processEvents(SDL_Event& e)
{
	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			//Set our bool to true
			m_quit = true;
		}
	}
}


void Game::run()
{
	m_inputComp.initialiseJoycon(0);

	//Create our SDL event variable
	SDL_Event e;
	double dt = 0;
	auto now = std::chrono::system_clock::now();
	auto before = std::chrono::system_clock::now();

	//While our bool is false, loop indefinitely
	while (!m_quit)
	{
		now = std::chrono::system_clock::now();
		dt = std::chrono::duration<double>(now - before).count();

		//Process any events that have occured
		processEvents(e);

		//handle input in the scenes
		m_mManager.handleInput(m_input);

		//Update the game
		update(dt);

		//Draw the Game
		draw();

		//Make before time equal to the current time
		before = now;
	}

	//Call close if our game loop is over
	close();
}

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		m_window = SDL_CreateWindow("Cyber Punch", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
			//Get window surface
			m_screenSurface = SDL_GetWindowSurface(m_window);
		}

	}
	return success;
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load any media here, we call our resource manager here
	m_resources.loadTextures(*m_renderer);
	m_mManager.setResourceHandler(m_resources);

	m_mManager.setScene("Game");

	return success;
}

void Game::close()
{
	//Destroy window
	SDL_DestroyWindow(m_window);
	m_window = NULL;

	TTF_Quit();

	//Quit SDL subsystems
	SDL_Quit();
}
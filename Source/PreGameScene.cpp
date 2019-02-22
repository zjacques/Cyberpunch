#include "..\Header\PreGameScene.h"

PreGameScene::PreGameScene()
{
}

void PreGameScene::start()
{
	//Setup the input using the first joycon connected
	m_input.initialiseJoycon(0);
}

void PreGameScene::stop()
{
}

void PreGameScene::update(double dt)
{
}

void PreGameScene::draw(SDL_Renderer & renderer)
{
}

void PreGameScene::handleInput(InputSystem & input)
{
}

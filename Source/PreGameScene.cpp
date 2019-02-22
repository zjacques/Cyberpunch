#include "..\Header\PreGameScene.h"

PreGameScene::PreGameScene()
{
}

void PreGameScene::start()
{
	m_numOfPossibleLocalPlayers = SDL_NumJoysticks();

	m_network = static_cast<OnlineSystem*>(Scene::systems()["Network"]);

	m_input.push_back(InputComponent());
	m_input[0].initialiseJoycon(0);

	if (m_network->isConnected)
	{


		if (m_network->m_isHost)
		{
			//m_input[0] gets to be player 1
		}
		else {
			//m_input[0] becomes the first available player
		}
	}
	//Setup the input using the first joycon connected
	//m_input.initialiseJoycon(0);
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

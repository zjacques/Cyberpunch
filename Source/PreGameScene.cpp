#include "..\Header\PreGameScene.h"


PreGameScene::PlayersInfo PreGameScene::playerIndexes;
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
			playerIndexes.localPlyrs.push_back(1);
		}
		else {
			//m_input[0] becomes the first available player
			playerIndexes.localPlyrs.push_back(m_network->m_playerNumber);//move from member var to getter
		}
		vector<int> players = m_network->getPlayers();

		for (auto num : players)
		{
			playerIndexes.onlinePlyrs.push_back(num);
		}

	}

	for (int i = 1; i < m_numOfPossibleLocalPlayers; i++)
	{
		m_input.push_back(InputComponent());
		m_input[i].initialiseJoycon(i);
	}
}

void PreGameScene::stop()
{
}

void PreGameScene::update(double dt)
{
	lastUpdate += dt;
	if (m_network->isConnected && lastUpdate > 0.5)
	{
		checkForUpdates();
		lastUpdate = 0;
	}
}

void PreGameScene::draw(SDL_Renderer & renderer)
{
}

void PreGameScene::handleInput(InputSystem & input)
{
	//Update the input system
	Scene::systems()["Input"]->update(0);

	//If the main menu input component is not added to the system, add it
	if (!m_addedInput)
	{
		input.addComponent(&m_input[0]);
		m_addedInput = true;
	}
	else
	{
		if (m_input[0].isButtonPressed("XBTN"))
		{
			Scene::goToScene("Game");
		}
		else if (m_input[0].isButtonPressed("ABTN"))
		{
			Scene::goToScene("Main Menu");
		}
		else if (m_input[0].isButtonPressed("BBTN"))
		{
			//add AI
		}
	}
}

void PreGameScene::checkForUpdates()
{
	vector<int> players = m_network->getPlayers();
	playerIndexes.onlinePlyrs.clear();
	for (auto num : players)
	{
		playerIndexes.onlinePlyrs.push_back(num);
	}
}

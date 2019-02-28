#include "..\Header\PreGameScene.h"


PreGameScene::PlayersInfo PreGameScene::playerIndexes;
PreGameScene::PreGameScene()
{
	m_availablePlyrs.push_back(true);
	m_availablePlyrs.push_back(true);
	m_availablePlyrs.push_back(true);
	m_availablePlyrs.push_back(true);
}

void PreGameScene::start()
{
	m_numOfPossibleLocalPlayers = SDL_NumJoysticks();

	m_network = static_cast<OnlineSystem*>(Scene::systems()["Network"]);

	m_input.push_back(pair<InputComponent*,int>(static_cast<InputComponent*>(Scene::systems()["Input"]->m_components.at(0)), -1));
	//m_input[0].first.initialiseJoycon(0);
	//m_hasJoined.push_back(true);

	if (m_network->isConnected)
	{
		if (m_network->m_isHost)
		{
			//m_input[0] gets to be player 1
			playerIndexes.localPlyrs.push_back(0);
			m_availablePlyrs[0] = false;
			m_input[0].second = 0;
		}
		else {
			//m_input[0] becomes the first available player
			playerIndexes.localPlyrs.push_back(m_network->m_playerNumber);//move from member var to getter
			m_availablePlyrs[m_network->m_playerNumber] = false;
			m_input[0].second = m_network->m_playerNumber;
		}
		vector<int> players = m_network->getPlayers();

		for (auto num : players)
		{
			if (num != playerIndexes.localPlyrs.back())
			{
				playerIndexes.onlinePlyrs.push_back(num);
				m_availablePlyrs[num] = false;

				//playerIndexes.botPlyrs.push_back(num);
			}
		}

	}
	else {
		playerIndexes.localPlyrs.push_back(0);
		m_availablePlyrs[0] = false;
		m_input[0].second = 0;
	}

	for (int i = 1; i < m_numOfPossibleLocalPlayers; i++)
	{
		m_input.push_back(pair<InputComponent*,int>(new InputComponent(), -1));
		m_input[i].first->initialiseJoycon(i);
		Scene::systems()["Input"]->addComponent(m_input[i].first);
		//m_hasJoined.push_back(false);
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
	if (m_network->gameStarted)
	{
		Scene::goToScene("Game");
	}
}

void PreGameScene::draw(SDL_Renderer & renderer)
{
}

void PreGameScene::handleInput(InputSystem & input)
{
	//Update the input system
	Scene::systems()["Input"]->update(0);
	bool playersChanged = false;

	//If the main menu input component is not added to the system, add it
	if (!m_addedInput)
	{
		//input.addComponent(&m_input[0].first);
		m_addedInput = true;
	}
	else
	{
		if (m_input[0].first->isButtonPressed("XBTN"))
		{
			if (!m_network->isConnected)
			{
				Scene::goToScene("Game");
			}
			else if (m_network->m_isHost)
			{
				m_network->startGame();
				Scene::goToScene("Game");
			}
		}
		else if (m_input[0].first->isButtonPressed("ABTN"))
		{
			//tell network you are leaving. It's only polite
			//you'll have to tell it to shut down the lobby too probs....
			if (m_network->isConnected) {
				m_network->disconnect();
			}
			playerIndexes.localPlyrs.clear();
			playerIndexes.onlinePlyrs.clear();
			playerIndexes.botPlyrs.clear();
			Scene::goToScene("Main Menu");
		}
		else if (m_input[0].first->isButtonPressed("BBTN"))
		{
			//tell the network a slot is being taken up
			//add AI
			for (int j = 0; j < m_availablePlyrs.size(); j++)
			{
				if (m_availablePlyrs[j])
				{
					m_availablePlyrs[j] = false;
					playerIndexes.botPlyrs.push_back(j); 
					playersChanged = true;
					break;
				}
			}
		}
		else if (m_input[0].first->isButtonPressed("YBTN"))
		{
			//remove AI
			for (int j = m_availablePlyrs.size(); j > 0; j--)
			{
				if (std::find(playerIndexes.botPlyrs.begin(), playerIndexes.botPlyrs.end(), j) != playerIndexes.botPlyrs.end() && !m_availablePlyrs[j])
				{
					m_availablePlyrs[j] = true;
					playerIndexes.botPlyrs.push_back(j);
					playerIndexes.botPlyrs.erase(std::remove(playerIndexes.botPlyrs.begin(), playerIndexes.botPlyrs.end(), j), playerIndexes.botPlyrs.end());
					playersChanged = true;
					break;
				}
			}
		}
		for (int i = 1; i < m_numOfPossibleLocalPlayers; i++)
		{
			if (m_input[i].first->isButtonPressed("XBTN"))//try to join the game;
			{
				if (m_input[i].second < 0)//controllers not joined are set to -1
				{
					if (m_network->isConnected)
						checkForUpdates();
					//join the game
					for (int j = 0; j < m_availablePlyrs.size(); j++)
					{
						if (m_availablePlyrs[j])
						{
							m_availablePlyrs[j] = false;
							playerIndexes.localPlyrs.push_back(j);
							m_input[i].second = j;
							//tell the network you've joined
							playersChanged = true;
							break;
						}
					}
				}
			}
			else if (m_input[i].first->isButtonPressed("ABTN"))
			{
				//remove this player from the game if they are in
				if (m_input[i].second > 0)//controllers not joined are set to -1
				{
					m_availablePlyrs[m_input[i].second] = false;
					playerIndexes.localPlyrs.erase(std::remove(playerIndexes.localPlyrs.begin(), playerIndexes.localPlyrs.end(), m_input[i].second), playerIndexes.localPlyrs.end());
					m_input[i].second = -1;
					//tell the network you've left
					playersChanged = true;
				}
			}
		}
	}

	if (m_network->isConnected && playersChanged)//actually send the message to say which slots are taken
	{
		m_network->assignPlayerSlots(m_availablePlyrs);
	}
}

void PreGameScene::checkForUpdates()
{
	vector<int> players = m_network->getPlayers();
	playerIndexes.onlinePlyrs.clear();
	//playerIndexes.botPlyrs.clear();
	for (auto num : players)
	{
		//if (num != playerIndexes.localPlyrs.back())
		if(!(std::find(playerIndexes.localPlyrs.begin(), playerIndexes.localPlyrs.end(), num) != playerIndexes.localPlyrs.end()) && !(std::find(playerIndexes.botPlyrs.begin(), playerIndexes.botPlyrs.end(), num) == playerIndexes.botPlyrs.end()))
		{
			playerIndexes.onlinePlyrs.push_back(num);
			m_availablePlyrs[num] = false;
		}
	}
}

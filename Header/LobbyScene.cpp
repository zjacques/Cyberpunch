#include "LobbyScene.h"

LobbyScene::LobbyScene() :
	m_currentIndex(0),
	m_addedInput(false),
	m_camera(false) //Dont use camera
{
}

void LobbyScene::start()
{
	//Setup the input using the first joycon connected
	m_input.initialiseJoycon(0);
	m_currentIndex = 0; //Start main menu at hovering over local play button

	m_network = static_cast<OnlineSystem*>(Scene::systems()["Network"]);
	// Initialise SDL_net (Note: We don't initialise or use normal SDL at all - only the SDL_net library!)
	if (SDLNet_Init() == -1)
	{
		std::cerr << "Failed to intialise SDL_net: " << SDLNet_GetError() << std::endl;
		exit(-1);
	}
	if (!m_network->isConnected)
	{
		if (m_network->ConnectToServer())
		{
			//if it can connect to the server, make the UI and fetch lobbies
			m_lobbies = m_network->getLobbies();

		}
		else {
			//else just tell the player to return to main menu
			Scene::goToScene("Main Menu");
		}
	}
	else {
		m_lobbies = m_network->getLobbies();
	}
}

void LobbyScene::stop()
{
	//Remove components from systems
	for (auto& btn : m_buttons)
	{
		Scene::systems()["Render"]->deleteComponent(&btn->getComponent("Sprite"));
	}

	//Clear the buttons vector
	m_buttons.clear();
}

void LobbyScene::update(double dt)
{
}

void LobbyScene::draw(SDL_Renderer & renderer)
{
}

void LobbyScene::handleInput(InputSystem & input)
{
	//Update the input system
	Scene::systems()["Input"]->update(0);

	//If the main menu input component is not added to the system, add it
	if (!m_addedInput)
	{
		input.addComponent(&m_input);
		m_addedInput = true;
	}
	else
	{
		int newIndex = m_currentIndex;
		if (m_input.isButtonPressed("STICKUP"))
		{
			newIndex--;
		}
		if (m_input.isButtonPressed("STICKDOWN"))
		{
			newIndex++;
		}
		if (m_input.isButtonPressed("XBTN"))
		{
			handleButtonPressed();//Join the selected server. If it fails, show a message and refresh
		}
		if (m_input.isButtonPressed("BBTN"))
		{
			requestHost();//try to start a game with no players and wait for them to join
		}
		if (m_input.isButtonPressed("YBTN"))
		{
			m_lobbies = m_network->getLobbies();//Refresh the page from the server
			//createLobbyButtons();
		}
		if (m_input.isButtonPressed("ABTN"))
		{
			Scene::goToScene("Main Menu");//Just go back to the main menu
		}


		/*if (newIndex < 0)
			newIndex = m_buttons.size() - 1;
		else if (newIndex >= m_buttons.size())
			newIndex = 0;

		//If the button we are highlighting has changed, deslect the current button and select the new one
		if (newIndex != m_currentIndex)
		{
			//Deslect current button
			auto btnComp = static_cast<ButtonComponent*>(&m_buttons.at(m_currentIndex)->getComponent("Btn"));
			auto sprite = static_cast<SpriteComponent*>(&m_buttons.at(m_currentIndex)->getComponent("Sprite"));
			btnComp->deselect();
			sprite->setTexture(btnComp->getTexture());

			//Set new button index
			m_currentIndex = newIndex;

			//Select new button
			btnComp = static_cast<ButtonComponent*>(&m_buttons.at(m_currentIndex)->getComponent("Btn"));
			sprite = static_cast<SpriteComponent*>(&m_buttons.at(m_currentIndex)->getComponent("Sprite"));
			btnComp->select();
			sprite->setTexture(btnComp->getTexture());
		}*/
	}
}

void LobbyScene::handleButtonPressed()
{
	//placeholder

	if (m_network->joinLobby(1))//plz to always be nonzero
	{
		Scene::goToScene("PreGame");
	}
	else {
		//Give failure message, refresh
		m_lobbies = m_network->getLobbies();
		//createLobbyButtons();
	}

	/*auto tag = static_cast<ButtonComponent*>(&m_buttons.at(m_currentIndex)->getComponent("Btn"))->getTag();

	if (tag == "Local")
	{
		Scene::goToScene("Game");
	}
	else if (tag == "Multiplayer")
	{
		Scene::goToScene("Main Menu"); // Temp, dont have a pre game lobby screen
	}
	else if (tag == "Options")
	{
		Scene::goToScene("Options");
	}
	else if (tag == "Exit")
	{
		// Need a way to exit the game
	}*/
}

void LobbyScene::createLobbyButtons()
{
	for (auto but : m_buttons)
	{
		delete(but);
	}
	m_buttons.clear();
	for (auto lob : m_lobbies) {
		m_buttons.push_back(createButton(Vector2f(960, 455), Scene::resources().getTexture(lob.name), lob.name, true)); 
		//make it say how many players there are somehow
	}
}


Entity* LobbyScene::createButton(Vector2f position, SDL_Texture* selectedTexture, std::string btnTag, bool selected)
{
	auto btn = new Entity("Button");
	auto pos = new PositionComponent(position.x, position.y);
	auto btnComp = new ButtonComponent(selectedTexture, Scene::resources().getTexture("Button Off"), btnTag, selected);
	btn->addComponent("Btn", btnComp);
	btn->addComponent("Pos", pos);
	btn->addComponent("Sprite", new SpriteComponent(pos, Vector2f(365, 205), Vector2f(365, 205), btnComp->getTexture(), 1));

	//Add sprite component to the render system
	Scene::systems()["Render"]->addComponent(&btn->getComponent("Sprite"));

	//Return the created btn
	return btn;
}

void LobbyScene::requestHost()
{
	m_network->makeHost();
	cout << "hosting" << endl;
	Scene::goToScene("PreGame");
	//go to pregame lobby to wait for more players to join
}

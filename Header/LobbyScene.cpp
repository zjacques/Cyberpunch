#include "LobbyScene.h"

LobbyScene::LobbyScene() :
	m_currentIndex(0),
	m_addedInput(false),
	m_camera(false) //Dont use camera
{
}

void LobbyScene::start()
{
	m_network = static_cast<OnlineSystem*>(Scene::systems()["Network"]);

	// Initialise SDL_net (Note: We don't initialise or use normal SDL at all - only the SDL_net library!)
	if (SDLNet_Init() == -1)
	{
		std::cerr << "Failed to intialise SDL_net: " << SDLNet_GetError() << std::endl;
		exit(-1);
	}

	m_network->ConnectToServer();
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
			handleButtonPressed();
		}


		if (newIndex < 0)
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
		}
	}
}

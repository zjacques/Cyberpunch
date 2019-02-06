#include "MenuManager.h"

MenuManager::MenuManager() :
	m_current(nullptr)
{
	m_scenes["Main Menu"] = new MainMenuScene();
	m_scenes["Options"] = new OptionsScene();
	m_scenes["Game"] = new GameScene();

	//Set the current scene as the main menu
	m_current = m_scenes["Game"];
}

void MenuManager::update(double dt)
{
	//If the current scene is a scene
	if (nullptr != m_current)
	{
		m_current->update(dt);
	}
}

void MenuManager::draw(SDL_Renderer & renderer)
{
	//If the current scene is a scene
	if (nullptr != m_current)
	{
		m_current->draw(renderer);
	}
}

void MenuManager::handleInput(InputSystem& input)
{
	//If the current scene is a scene
	if (nullptr != m_current)
	{
		m_current->handleInput(input);
	}
}

void MenuManager::setScene(std::string scene)
{
	//Set the current scene
	m_current = m_scenes[scene];
}
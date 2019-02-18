#include "MainMenuScene.h"
#include "RenderSystem.h"

MainMenuScene::MainMenuScene() :
	m_currentIndex(0),
	m_addedInput(false),
	m_camera(false) //Dont use camera
{
}

void MainMenuScene::start()
{
	//Setup the input using the first joycon connected
	m_input.initialiseJoycon(0);
	m_currentIndex = 0; //Start main menu at hovering over local play button

	//Create the buttons for the game
	m_buttons.push_back(createButton(Vector2f(960, 270 - 135), Scene::resources().getTexture("Local Play Button"), "Local", true));
	m_buttons.push_back(createButton(Vector2f(960, 270 * 2 - 135), Scene::resources().getTexture("Multiplayer Button"), "Multiplayer", false));
	m_buttons.push_back(createButton(Vector2f(960, 270 * 3 - 135), Scene::resources().getTexture("Options Button"), "Options", false));
	m_buttons.push_back(createButton(Vector2f(960, 270 * 4 - 135), Scene::resources().getTexture("Exit Button"), "Exit", false));
}

void MainMenuScene::stop()
{
	//Remove components from systems
	for (auto& btn : m_buttons)
	{
		Scene::systems()["Render"]->deleteComponent(&btn->getComponent("Sprite"));
	}

	//Clear the buttons vector
	m_buttons.clear();
}

Entity* MainMenuScene::createButton(Vector2f position, SDL_Texture* selectedTexture, std::string btnTag, bool selected)
{
	auto btn = new Entity("Button");
	auto pos = new PositionComponent(position.x, position.y);
	auto btnComp = new ButtonComponent(selectedTexture, Scene::resources().getTexture("Button Off"),btnTag, selected);
	btn->addComponent("Btn", btnComp);
	btn->addComponent("Pos", pos);
	btn->addComponent("Sprite", new SpriteComponent(pos, Vector2f(365, 205), Vector2f(365, 205), btnComp->getTexture(), 1));

	//Add sprite component to the render system
	Scene::systems()["Render"]->addComponent(&btn->getComponent("Sprite"));

	//Return the created btn
	return btn;
}

void MainMenuScene::update(double dt)
{

}

void MainMenuScene::draw(SDL_Renderer & renderer)
{
	//Draw everything in the render system
	static_cast<RenderSystem*>(Scene::systems()["Render"])->render(renderer, m_camera);
}

void MainMenuScene::handleInput(InputSystem& input)
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

void MainMenuScene::handleButtonPressed()
{
	auto tag = static_cast<ButtonComponent*>(&m_buttons.at(m_currentIndex)->getComponent("Btn"))->getTag();
	
	if (tag == "Local")
	{
		Scene::goToScene("Game");
	}
	else if (tag == "Multiplayer")
	{

	}
	else if (tag == "Options")
	{

	}
	else if (tag == "Exit")
	{
		// Need a way to exit the game
	}
}

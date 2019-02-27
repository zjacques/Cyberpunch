#include "MainMenuScene.h"
#include "RenderSystem.h"
#include "AnimationComponent.h"

MainMenuScene::MainMenuScene() :
	m_currentIndex(0),
	m_addedInput(false),
	m_camera(false), //Dont use camera
	m_audioCreated(false)
{
}

void MainMenuScene::start()
{
	if (m_audioCreated == false)
	{
		m_audio.addSound("MenuMusic", Scene::resources().getMusic("Good Song"));
		m_audio.addSound("Neon", Scene::resources().getSFX("Neon"));
	}
	Mix_Volume(-1, 10);
	m_audio.playSound("MenuMusic", true);
	//Setup the input using the first joycon connected
	m_input.initialiseJoycon(0);

	//Create the buttons for the game
	m_buttons.push_back(createButton(Vector2f(960, 445), Scene::resources().getTexture("Local Play Button"), "Local", m_currentIndex == 0 ? true : false));
	m_buttons.push_back(createButton(Vector2f(960, 445 + 135), Scene::resources().getTexture("Multiplayer Button"), "Multiplayer", m_currentIndex == 1 ? true : false));
	m_buttons.push_back(createButton(Vector2f(960, 445 + 135 * 2), Scene::resources().getTexture("Achievements Button"), "Achievements", m_currentIndex == 2 ? true : false));
	m_buttons.push_back(createButton(Vector2f(960, 445 + 135 * 3), Scene::resources().getTexture("Options Button"), "Options", m_currentIndex == 3 ? true : false));
	m_buttons.push_back(createButton(Vector2f(960, 445 + 135 * 4), Scene::resources().getTexture("Exit Button"), "Exit", m_currentIndex == 4 ? true : false));

	m_audioCreated = true;
}

void MainMenuScene::stop()
{
	//Remove components from systems
	for (auto& btn : m_buttons)
	{
		Scene::systems()["Render"]->deleteComponent(&btn->getComponent("Sprite"));
		Scene::systems()["Render"]->deleteComponent(&btn->getComponent("Text Sprite"));
		Scene::systems()["Animation"]->deleteComponent(&btn->getComponent("Animation"));
		Scene::systems()["Animation"]->deleteComponent(&btn->getComponent("Text Animation"));
	}
	m_audio.stop();
	
	//Clear the buttons vector
	m_buttons.clear();
}

Entity* MainMenuScene::createButton(Vector2f position, SDL_Texture* selectedTexture, std::string btnTag, bool selected)
{
	auto btn = new Entity("Button");
	auto pos = new PositionComponent(position.x, position.y);
	auto btnComp = new ButtonComponent(selectedTexture, Scene::resources().getTexture("Button BG"), btnTag, false);
	btn->addComponent("Btn", btnComp);
	btn->addComponent("Pos", pos);
	btn->addComponent("Sprite", new SpriteComponent(pos, Vector2f(350, 125), Vector2f(350, 125), btnComp->getTexture(), 1));
	btn->addComponent("Text Sprite", new SpriteComponent(pos, Vector2f(350, 125), Vector2f(350, 125), selectedTexture, 1));
	auto anim = new AnimationComponent(&btn->getComponent("Sprite"));
	std::vector<SDL_Rect> m_animFrames;
	for (int i = 0; i < 10; i++)
		m_animFrames.push_back({ i * 350, 0, 350, 125 });
	anim->addAnimation("Selected", Scene::resources().getTexture("Button BG"), m_animFrames, .25f);
	//Reverse animation
	std::reverse(m_animFrames.begin(), m_animFrames.end());
	anim->addAnimation("De-Selected", Scene::resources().getTexture("Button BG"), m_animFrames, .25f);
	btn->addComponent("Animation", anim);

	std::reverse(m_animFrames.begin(), m_animFrames.end());
	auto textAnim = new AnimationComponent(&btn->getComponent("Text Sprite"));
	textAnim->addAnimation("Selected", selectedTexture, m_animFrames, .25f);
	std::reverse(m_animFrames.begin(), m_animFrames.end());
	textAnim->addAnimation("De-Selected", selectedTexture, m_animFrames, .25f);
	btn->addComponent("Text Animation", textAnim);

	if (selected)
	{
		anim->playAnimation("Selected", false);
		textAnim->playAnimation("Selected", false);
		Mix_Volume(-1, 40);
	//	m_audio.playSound("Neon", false);
	}


	//Add sprite component to the render system
	Scene::systems()["Render"]->addComponent(&btn->getComponent("Sprite"));
	Scene::systems()["Render"]->addComponent(&btn->getComponent("Text Sprite"));
	Scene::systems()["Animation"]->addComponent(anim);
	Scene::systems()["Animation"]->addComponent(textAnim);

	//Return the created btn
	return btn;
}

void MainMenuScene::update(double dt)
{
	Scene::systems()["Animation"]->update(dt);
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
		{
			newIndex = m_buttons.size() - 1;
		}
		else if (newIndex >= m_buttons.size()) {
			newIndex = 0;
			
		}

		//If the button we are highlighting has changed, deslect the current button and select the new one
		if (newIndex != m_currentIndex)
		{
			//Deslect current button
			auto anim = static_cast<AnimationComponent*>(&m_buttons.at(m_currentIndex)->getComponent("Animation"));
			auto textAnim = static_cast<AnimationComponent*>(&m_buttons.at(m_currentIndex)->getComponent("Text Animation"));
			anim->playAnimation("De-Selected", false);
			textAnim->playAnimation("De-Selected", false);

			//Set new button index
			m_currentIndex = newIndex;

			anim = static_cast<AnimationComponent*>(&m_buttons.at(m_currentIndex)->getComponent("Animation"));
			textAnim = static_cast<AnimationComponent*>(&m_buttons.at(m_currentIndex)->getComponent("Text Animation"));
			anim->playAnimation("Selected", false);
			textAnim->playAnimation("Selected", false);
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
		//Scene::goToScene("Main Menu"); // Temp, dont have a pre game lobby screen
		Scene::goToScene("Multiplayer");
	}
	else if (tag == "Options")
	{
		Scene::goToScene("Options");
	}
	else if (tag == "Exit")
	{
		// Need a way to exit the game
	}
}

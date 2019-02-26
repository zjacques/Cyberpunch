#include "AchievementsScene.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "RenderSystem.h"

AchievementsScene::AchievementsScene() :
	m_bgE("BG"),
	m_initialSetup(false),
	m_camera(false)
{
}

void AchievementsScene::start()
{
	if (!m_initialSetup)
	{
		auto pos = new PositionComponent(960, 540);
		m_bgE.addComponent("Pos", pos);
		auto sprite = new SpriteComponent(pos, Vector2f(1920, 1080), Vector2f(1920, 1080), Scene::resources().getTexture("Achievements BG"), 0);
		m_bgE.addComponent("Sprite", sprite);

		int index = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_icons.push_back(Entity("Icon"));
				auto pos = new PositionComponent(672 + j * 192, 216 + i * 216);
				m_icons.at(index).addComponent("Pos", pos);
				auto s = new SpriteComponent(pos, Vector2f(50, 50), Vector2f(50, 50), Scene::resources().getTexture("Achievement Locked"), 1);
				m_icons.at(index).addComponent("Sprite", s);
				index++;
			}
		}
	}

	for (auto& icon : m_icons)
		Scene::systems()["Render"]->addComponent(&icon.getComponent("Sprite"));

	//Add the bg to the render system
	Scene::systems()["Render"]->addComponent(&m_bgE.getComponent("Sprite"));
}

void AchievementsScene::stop()
{
	for (auto& icon : m_icons)
		Scene::systems()["Render"]->deleteComponent(&icon.getComponent("Sprite"));

	//Remove components from the systems
	Scene::systems()["Render"]->deleteComponent(&m_bgE.getComponent("Sprite"));
}

void AchievementsScene::update(double dt)
{
}

void AchievementsScene::handleInput(InputSystem & input)
{
	//Update the input system
	Scene::systems()["Input"]->update(0);

	if (!m_initialSetup)
	{
		m_input = static_cast<InputComponent*>(input.m_components.at(0));
		m_initialSetup = true;
	}

	if (m_input->isButtonPressed("ABTN"))
		Scene::goToScene("Main Menu");

}

void AchievementsScene::draw(SDL_Renderer & renderer)
{
	static_cast<RenderSystem*>(Scene::systems()["Render"])->render(renderer, m_camera);;
}

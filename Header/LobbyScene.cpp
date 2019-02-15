#include "LobbyScene.h"

LobbyScene::LobbyScene()
{
}

void LobbyScene::start()
{
	m_network = static_cast<OnlineSystem*>(Scene::systems()["Network"]);
}

void LobbyScene::stop()
{
}

void LobbyScene::update(double dt)
{
}

void LobbyScene::draw(SDL_Renderer & renderer)
{
}

void LobbyScene::handleInput(InputSystem & input)
{
}

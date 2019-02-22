#pragma once
#include <map>
#include "MainMenuScene.h"
#include "OptionsScene.h"
#include "GameScene.h"
#include "LobbyScene.h"

class MenuManager
{
public:
	MenuManager();
	void update(double dt);
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);
	void setResourceHandler(ResourceHandler& resources);
	void setSystemPtr(std::map<std::string, System*>& systems);
	void setScene(std::string scene);
private:
	std::map<std::string, Scene*> m_scenes;
	Scene* m_current; //Ptr to the curretn scene
};
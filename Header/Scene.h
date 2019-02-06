#pragma once
#include "SDL.h"
#include <iostream>
#include "InputSystem.h"

//Base scene class, this will be inherited by every other scene
class Scene
{
public:
	Scene() { m_stgt = ""; m_cs = false; }
	virtual ~Scene() {}
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void update(double dt) = 0;
	virtual void handleInput(InputSystem& input) = 0;
	virtual void draw(SDL_Renderer& renderer) = 0;
	void goToScene(std::string sceneName)
	{
		m_stgt = sceneName;
		m_cs = true;
	}
	bool changeScene() { return m_cs; }
	std::string getNewScene() { return m_stgt; }
	void resetSceneChange() { m_cs = false; }

private:
	std::string m_stgt;
	bool m_cs;
};
#pragma once
#include "Scene.h"
#include "Entity.h"
#include "Camera.h"
#include "InputComponent.h"

class AchievementsScene : public Scene
{
public:
	AchievementsScene();
	void start();
	void stop();
	void update(double dt);
	void handleInput(InputSystem& input);
	void draw(SDL_Renderer& renderer);

private:
	Camera m_camera;
	Entity m_bgE;
	std::vector<Entity> m_icons;
	InputComponent* m_input;
	bool m_initialSetup;
};
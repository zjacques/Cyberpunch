#pragma once
#include "Camera.h"
#include "Scene.h"
#include "Entity.h"
#include "ButtonComponent.h"

//The main menu scene, from here we navigate to the other scenes of the game
class MainMenuScene : public Scene
{
public:
	MainMenuScene();
	void start();
	void stop();
	Entity* createButton(Vector2f pos, SDL_Texture* selectedTexture, std::string btnTag, bool selected);
	void update(double dt);
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);
	void handleButtonPressed();
private:
	int m_currentIndex;
	Camera m_camera;
	InputComponent m_input;
	bool m_addedInput;

	std::vector<Entity*> m_buttons;
};
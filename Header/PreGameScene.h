#pragma once
#include "Scene.h"
#include "OnlineSystem.h"


class PreGameScene : public Scene {
public:
	PreGameScene();
	void start();
	void stop();
	void update(double dt);
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);
private:
	vector<InputComponent> m_input;
	int m_numOfPossibleLocalPlayers;
	bool isGameOnline = false;
	OnlineSystem* m_network;

	int m_maxPlayers = 4;

};
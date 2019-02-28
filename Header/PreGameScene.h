#pragma once
#include "Scene.h"
#include "OnlineSystem.h"
#include "AiInputComponent.h"
#include "PlayerInputComponent.h"

using std::map;
using std::pair;

class PreGameScene : public Scene {
public:
	static struct PlayersInfo {
		vector<int> localPlyrs;
		vector<int> onlinePlyrs;
		vector<int> botPlyrs;
	} playerIndexes;

	PreGameScene();
	void start();
	void stop();
	void update(double dt);
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);

	//static PlayersInfo playerIndexes;

private:
	void checkForUpdates();
	vector<bool> m_availablePlyrs;
	vector<pair<InputComponent*, int>> m_input;
	//vector<bool> m_hasJoined;
	int m_numOfPossibleLocalPlayers;
	bool isGameOnline = false;
	OnlineSystem* m_network;

	bool m_addedInput;

	double lastUpdate = 0;

	int m_maxPlayers = 4;

	bool m_netGame = false;

};
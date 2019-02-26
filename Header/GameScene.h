#pragma once
#include "Player.h"
#include "Scene.h"
#include "Entity.h"
#include "AttackSystem.h"
#include "PreGameScene.h"

#include "PhysicsComponent.h"
#include "PlayerInputComponent.h"
#include "AIComponent.h"
#include "DustTriggerComponent.h"
#include "DustComponent.h"
#include "PlayerComponent.h"

#include "PickUpComponent.h"
#include "PickUpSystem.h"
#include "PlayerInputComponent.h"
#include "DJBoothSystem.h"
#include "GravityBoothComponent.h"
#include "PlatformBoothComponent.h"
#include "SlowBoothComponent.h"

#include "AudioComponent.h"
#include "OnlineSystem.h"
#include "PlayerPhysicsComponent.h"
#include "OnlineSendComponent.h"
#include "OnlineInputComponent.h"
#include "Camera.h"
#include <SDL_net.h>

class GameScene : public Scene
{
public:
	GameScene();
	void start();
	void setupTimer();
	void stop();
	void update(double dt);
	void updateStartTimer(double dt);
	void updateEndGameTimer(double dt);

	Entity* createAI(int index, int posX, int posY, std::vector<Vector2f> spawnPositions);

	void updateCamera(double dt);
	Entity* createDJB(int index, int posX, int posY);

	void createPlatforms(SDL_Renderer& renderer);

	Entity* createPlayer(int playerNumber, int controllerNumber, int posX, int posY, bool local, std::vector<Vector2f> spawnPositions);
	Entity* createKillBox(int posX, int posY, int width, int height);
	
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);
private:
	bool m_audioCreated;
	bool m_platformsCreated;
	bool m_boothCreated;
	bool m_gameStarted, m_startTimerEnded, m_gameOver;
	Entity m_bgEntity;
	Entity m_gameStart, m_gameEndE;
	float m_gameStartTimer, m_endGameTimer;
	std::vector<Entity*> m_killboxes;
	std::vector<Entity*> m_localPlayers;
	std::vector<Entity*> m_AIPlayers;
	std::vector<Entity*> m_allPlayers; //All local, online and Ai players
	std::vector<Entity*> m_playersToDel;
	std::vector<InputSystem*> m_localInputs;
	int m_numOfLocalPlayers;
	Entity* m_pickUp;
	std::vector<Entity*> m_djBooths;
	//online
	std::vector<Entity*> m_onlinePlayers;
	//std::vector<OnlineInputSystem*> m_onlineInputs;
	int m_numOfOnlinePlayers;
	int m_numOfAIPlayers;

	//Physics variables
	PhysicsSystem m_physicsSystem; //Add all physics components to the system
	Box2DBridge m_physicsWorld;
	CollisionListener m_collisionListener;
	//Platforms of the game
	std::vector<Entity*> m_platforms;

	Camera m_camera;
	SDL_Renderer* m_rendererPtr; //Used for resetting the render scale when exiting a game
	AudioComponent m_audio;
};
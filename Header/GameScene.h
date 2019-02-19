#pragma once
#include "Player.h"
#include "Scene.h"
#include "Entity.h"
#include "AttackSystem.h"

#include "PhysicsComponent.h"
#include "PlayerInputComponent.h"
#include "AIComponent.h"
#include "DustTriggerComponent.h"
#include "DustComponent.h"

#include "PickUpComponent.h"
#include "PickUpSystem.h"
#include "PlayerInputComponent.h"
#include "DJBoothSystem.h"
#include "DJboothComponent.h"

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
	void stop();
	void update(double dt);
	void checkDust(double dt);

	Entity* createAI(int index, int posX, int posY);

	void updateCamera(double dt);
	Entity* createDJB(int index, int posX, int posY);

	void createPlatforms(SDL_Renderer& renderer);
	SDL_Rect createRect(int x, int y, int w, int h);

	Entity* createPlayer(int index, int posX, int posY, bool local);
	
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);
private:
	bool m_platformsCreated;
	bool m_boothCreated;
	Entity m_bgEntity;
	std::vector<Entity*> m_localPlayers;
	std::vector<Entity*> m_AIPlayers;
	std::vector<Entity*> m_dustParticles, m_dustToDelete;
	std::vector<InputSystem*> m_localInputs;
	int m_numOfLocalPlayers;
	Entity* m_pickUp;
	std::vector<Entity*> m_djBooths;
	//online
	std::vector<Entity*> m_onlinePlayers;
	//std::vector<OnlineInputSystem*> m_onlineInputs;
	int m_numOfOnlinePlayers;

	//Physics variables
	PhysicsSystem m_physicsSystem; //Add all physics components to the system
	Box2DBridge m_physicsWorld;
	CollisionListener m_collisionListener;
	//Platforms of the game
	std::vector<Entity*> m_platforms;

	//Dust particles rectangles
	std::vector<SDL_Rect> m_dustFrames;

	Camera m_camera;
};
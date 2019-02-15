#pragma once
#include "Player.h"
#include "Scene.h"
#include "PickUp.h"
#include "Entity.h"
#include "AttackSystem.h"
#include "OnlineSystem.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerInputComponent.h"
#include "OnlineSendComponent.h"
#include "OnlineInputComponent.h"
#include <SDL_net.h>

class GameScene : public Scene
{
public:
	GameScene();
	void start();
	void stop();
	void update(double dt);
	void createPlatforms(SDL_Renderer& renderer);
	SDL_Rect createRect(int x, int y, int w, int h);
	Entity* createPlayer(int index, int posX, int posY, bool local);
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);
private:
	bool m_platformsCreated;
	Entity m_bgEntity;
	std::vector<Entity*> m_localPlayers;
	int m_numOfLocalPlayers;
	//online
	std::vector<Entity*> m_onlinePlayers;
	//std::vector<OnlineInputSystem*> m_onlineInputs;
	int m_numOfOnlinePlayers;

	PickUp m_pickUp;
	//Physics variables
	PhysicsSystem m_physicsSystem; //Add all physics components to the system
	Box2DBridge m_physicsWorld;
	CollisionListener m_collisionListener;
	//Platforms of the game
	std::vector<Entity*> m_platforms;
};
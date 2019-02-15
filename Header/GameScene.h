#pragma once
#include "Platform.h"
#include "Player.h"
#include "Scene.h"
#include "PickUp.h"
#include "Entity.h"
#include "AttackSystem.h"
#include "PhysicsComponent.h"
#include "PlayerInputComponent.h"
#include "AIComponent.h"
#include "OnlineSystem.h"
#include "PlayerPhysicsComponent.h"
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
	Entity* createAI(int index, int posX, int posY);
	Entity* createPlayer(int index, int posX, int posY, bool local);
	
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);
private:
	std::vector<Entity*> m_localPlayers;
	std::vector<Entity*> m_AIPlayers;
	std::vector<InputSystem*> m_localInputs;
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
	SDL_Texture* m_bG;
	//Platforms of the game
	std::vector<Platform> m_platforms;
};
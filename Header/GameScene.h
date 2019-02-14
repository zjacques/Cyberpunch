#pragma once
#include "Platform.h"
#include "Player.h"
#include "Scene.h"
#include "PickUp.h"
#include "Entity.h"
#include "AttackSystem.h"
#include "PhysicsComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerInputComponent.h"
#include "AIComponent.h"

class GameScene : public Scene
{
public:
	GameScene();
	void start();
	void stop();
	void update(double dt);
	Entity* createPlayer(int index, int posX, int posY);
	Entity* createAI(int index, int posX, int posY);
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);
private:
	std::vector<Entity*> m_localPlayers;
	std::vector<Entity*> m_AIPlayers;
	std::vector<InputSystem*> m_localInputs;
	int m_numOfLocalPlayers;
	PickUp m_pickUp;
	//Physics variables
	PhysicsSystem m_physicsSystem; //Add all physics components to the system
	Box2DBridge m_physicsWorld;
	CollisionListener m_collisionListener;
	SDL_Texture* m_bG;
	//Platforms of the game
	std::vector<Platform> m_platforms;
};
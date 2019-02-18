#pragma once
#include "Platform.h"
#include "Player.h"
#include "Scene.h"
#include "Entity.h"
#include "AttackSystem.h"
#include "PickUpComponent.h"
#include "PickUpSystem.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerInputComponent.h"
#include "DJBoothSystem.h"
#include "DJboothComponent.h"

class GameScene : public Scene
{
public:
	GameScene();
	void start();
	void stop();
	void update(double dt);
	Entity* createPlayer(int index, int posX, int posY);
	Entity* createDJB(int index, int posX, int posY);
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);
private:
	std::vector<Entity*> m_localPlayers;
	int m_numOfLocalPlayers;
	Entity* m_pickUp;
	std::vector<Entity*> m_djBooths;
//	PickUpComponent m_pickUpComponent;
	//Physics variables
	PhysicsSystem m_physicsSystem; //Add all physics components to the system
	Box2DBridge m_physicsWorld;
	CollisionListener m_collisionListener;
	SDL_Texture* m_bG;

	SDL_Texture* m_recordt;
	
	//Platforms of the game
	std::vector<Platform> m_platforms;
};
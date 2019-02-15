#pragma once
#include "Player.h"
#include "Scene.h"
#include "PickUp.h"
#include "Entity.h"
#include "AttackSystem.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerInputComponent.h"

class GameScene : public Scene
{
public:
	GameScene();
	void start();
	void stop();
	void update(double dt);
	Entity* createPlayer(int index, int posX, int posY);
	void createPlatforms(SDL_Renderer& renderer);
	SDL_Rect createRect(int x, int y, int w, int h);
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);
private:
	bool m_platformsCreated;
	Entity m_bgEntity;
	std::vector<Entity*> m_localPlayers;
	int m_numOfLocalPlayers;
	PickUp m_pickUp;
	//Physics variables
	PhysicsSystem m_physicsSystem; //Add all physics components to the system
	Box2DBridge m_physicsWorld;
	CollisionListener m_collisionListener;
	//Platforms of the game
	std::vector<Entity*> m_platforms;
};
#pragma once
#include "Platform.h"
#include "Player.h"
#include "Scene.h"
#include "PickUp.h"

class GameScene : public Scene
{
public:
	GameScene();
	void start();
	void stop();
	void update(double dt);
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);
private:
	std::vector<Player> m_localPlayers;
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
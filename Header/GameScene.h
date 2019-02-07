#pragma once
#include "Platform.h"
#include "Player.h"
#include "Scene.h"

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
	//Test player
	Player m_player;

	//Physics variables
	Platform m_platformFactory;
	PhysicsSystem m_physicsSystem; //Add all physics components to the system
	Box2DBridge m_physicsWorld;
	CollisionListener m_collisionListener;
};
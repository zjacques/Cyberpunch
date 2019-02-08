#include "GameScene.h"

GameScene::GameScene()
{
}

void GameScene::start()
{
	m_physicsSystem = PhysicsSystem(); // Recreate the physics system
	m_physicsWorld.initWorld(); //Create the physics world
	m_physicsWorld.addContactListener(m_collisionListener); //Add collision listener to the world

	m_player.createPlayer(m_physicsWorld, m_physicsSystem);

	//Create all of the platforms for the game
	for (auto& platform : Scene::resources().getLevelData()["Platforms"])
	{
		//Get the X,Y,Width and Height of the platform
		int x = platform["X"], y = platform["Y"], w = platform["W"], h = platform["H"];
		std::string tag = platform["Tag"];
		auto newPlat = Platform(tag);

		//Add a physics body to the platform
		newPlat.getPhysComp().m_body = m_physicsWorld.createBox(x, y, w, h, false, true, b2BodyType::b2_staticBody);
		//Add the properties of the physics body
		m_physicsWorld.addProperties(*newPlat.getPhysComp().m_body, 0, 1, 0, false, new PhysicsComponent::ColData(newPlat.getTag(), &newPlat));

		m_platforms.push_back(newPlat); //Create a new platform
	}
}

void GameScene::stop()
{
	m_player.deletePlayer();
	m_physicsWorld.deleteWorld(); //Delete the physics world
	m_platforms.clear(); //Delete the platforms
}

void GameScene::update(double dt)
{
	//Update the physics world, do this before ANYTHING else
	m_physicsWorld.update(dt);

	m_player.update(dt);
}

void GameScene::draw(SDL_Renderer & renderer)
{
	//Draw the platforms
	for (auto& platform : m_platforms)
	{
		platform.draw(renderer);
	}

	m_player.draw(renderer);
}

void GameScene::handleInput(InputSystem & input)
{
	m_player.handleInput(input);

	//If the pause button has been pressed on either joycon
	if (input.isButtonPressed("A"))
	{
		Scene::goToScene("Main Menu");
	}
	if (input.isButtonPressed("Space"))
	{
		//Flip the gravioty of the physics system and the physics world
		m_physicsSystem.flipGravity();
		m_physicsWorld.flipGravity();
		m_collisionListener.flipGravity();
		m_player.flipGravity();
	}
}

#include "GameScene.h"

GameScene::GameScene()
{
}

void GameScene::start()
{
	std::cout << "Starting Game Scene\n";
	m_physicsSystem = PhysicsSystem(); // Recreate the physics system
	m_physicsWorld.initWorld(); //Create the physics world
	m_physicsWorld.addContactListener(m_collisionListener); //Add collision listener to the world

	//Create the platforms for the game
	m_platformFactory.createPlatforms(m_physicsWorld, m_physicsSystem);
}

void GameScene::stop()
{
	std::cout << "Stopping Game Scene\n";
	m_physicsWorld.deleteWorld(); //Delete the physics world
	m_platformFactory.deletePlatforms(); //Delete the platforms of the game
}

void GameScene::update(double dt)
{
	//Update the physics world, do this before ANYTHING else
	m_physicsWorld.update(dt);
}

void GameScene::draw(SDL_Renderer & renderer)
{
	//Draw the platforms
	m_platformFactory.draw(renderer);
}

void GameScene::handleInput(InputSystem & input)
{
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
	}
}

#include "GameScene.h"

GameScene::GameScene()
{
	for (int i = 0; i < 4; i++)
	{
		m_localPlayers.push_back(Player());
	}
}

void GameScene::start()
{
	std::cout << "Starting Game Scene\n";
	m_physicsSystem = PhysicsSystem(); // Recreate the physics system
	m_physicsWorld.initWorld(); //Create the physics world
	m_physicsWorld.addContactListener(m_collisionListener); //Add collision listener to the world

	//m_player.createPlayer(m_physicsWorld, m_physicsSystem);

	m_numOfLocalPlayers = SDL_NumJoysticks();

	//Create players for extra inputs
	for (int i = 0; i < m_numOfLocalPlayers; i++)
	{
		auto inputComp = new InputComponent();
		inputComp->initialiseJoycon(i);
		auto input = new InputSystem();
		input->addComponent(inputComp);
		m_localInputs.push_back(input);
		m_localPlayers.at(i).createPlayer(m_physicsWorld, m_physicsSystem);
	}


	//Create the platforms for the game
	m_platformFactory.createPlatforms(m_physicsWorld, m_physicsSystem);

}

void GameScene::stop()
{
	std::cout << "Stopping Game Scene\n";

	for (auto& player : m_localPlayers)
		player.deletePlayer();

	m_localInputs.clear();
	m_physicsWorld.deleteWorld(); //Delete the physics world
	m_platformFactory.deletePlatforms(); //Delete the platforms of the game
	m_numOfLocalPlayers = 0;
}

void GameScene::update(double dt)
{
	//Update the physics world, do this before ANYTHING else
	m_physicsWorld.update(dt);

	for (auto& inputSys : m_localInputs)
	{
		inputSys->update(dt);
	}

	for (int i = 0; i < m_numOfLocalPlayers; i++)
	{
		m_localPlayers.at(i).update(dt);
	}
}

void GameScene::draw(SDL_Renderer & renderer)
{
	//Draw the platforms
	m_platformFactory.draw(renderer);

	for (int i = 0; i < m_numOfLocalPlayers; i++)
	{
		m_localPlayers.at(i).draw(renderer);
	}
	
}

void GameScene::handleInput(InputSystem & input)
{
	//Handle input for all players
	for (int i = 0; i < m_numOfLocalPlayers; i++)
	{
		m_localPlayers.at(i).handleInput(*m_localInputs.at(i));
	}

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
		//Flip grav in all players
		for (auto& player : m_localPlayers)
		{
			player.flipGravity();
		}
	}
}

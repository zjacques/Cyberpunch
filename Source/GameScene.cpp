#include "GameScene.h"

GameScene::GameScene()
{
	for (int i = 0; i < 4; i++)
	{
		m_localPlayers.push_back(Player()); 
		m_onlinePlayers.push_back(Player());
	}
}

void GameScene::start()
{
	m_physicsSystem = PhysicsSystem(); // Recreate the physics system
	m_physicsWorld.initWorld(); //Create the physics world
	m_physicsWorld.addContactListener(m_collisionListener); //Add collision listener to the world

	//m_player.createPlayer(m_physicsWorld, m_physicsSystem);
	m_pickUp.createPickUp(m_physicsWorld, m_physicsSystem);

	m_bG = Scene::resources().getTexture("Game BG");

	m_numOfLocalPlayers = SDL_NumJoysticks();
	m_numOfOnlinePlayers = 1;

	// Initialise SDL_net (Note: We don't initialise or use normal SDL at all - only the SDL_net library!)
	if (SDLNet_Init() == -1)
	{
		std::cerr << "Failed to intialise SDL_net: " << SDLNet_GetError() << std::endl;
		exit(-1);
	}

	//Create players for extra inputs
	for (int i = 0; i < m_numOfLocalPlayers; i++)
	{
		auto inputComp = new InputComponent();
		inputComp->initialiseJoycon(i);
		auto input = new InputSystem();
		input->addComponent(inputComp);
		m_localInputs.push_back(input);
		m_localPlayers.at(i).createPlayer(m_physicsWorld, m_physicsSystem);
		m_localPlayers.at(i).addClient();
	}
	for (int i = 0; i < m_numOfOnlinePlayers; i++)
	{
		auto inputComp = new InputComponent();
		auto input = new OnlineInputSystem();
		input->addComponent(inputComp);
		input->ConnectToServer();
		m_onlineInputs.push_back(input);
		m_onlinePlayers.at(i).createPlayer(m_physicsWorld, m_physicsSystem);
	}


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
		m_physicsWorld.addProperties(*newPlat.getPhysComp().m_body, 0, .1f, 0, false, new PhysicsComponent::ColData(newPlat.getTag(), &newPlat));

		m_platforms.push_back(newPlat); //Create a new platform
	}
}

void GameScene::stop()
{
	for (auto& player : m_localPlayers)
		player.deletePlayer();
	for (auto& player : m_onlinePlayers)
		player.deletePlayer();

	m_localInputs.clear();
	m_onlineInputs.clear();
	m_physicsWorld.deleteWorld(); //Delete the physics world
	m_platforms.clear(); //Delete the platforms of the game
	m_numOfLocalPlayers = 0;
	m_pickUp.deletePickUp();
}

void GameScene::update(double dt)
{
	//Update the physics world, do this before ANYTHING else
	m_physicsWorld.update(dt);

	for (auto& inputSys : m_localInputs)
	{
		inputSys->update(dt);
	}
	for (auto& inputSys : m_onlineInputs)
	{
		inputSys->update(dt);
	}

	for (int i = 0; i < m_numOfLocalPlayers; i++)
	{
		m_localPlayers.at(i).update(dt);
	}
	for (int i = 0; i < m_numOfOnlinePlayers; i++)
	{
		m_onlinePlayers.at(i).update(dt);
	}
}

void GameScene::draw(SDL_Renderer & renderer)
{
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 1920;
	rect.h = 1080;

	SDL_RenderCopy(&renderer, m_bG, &rect, &rect);
	//Draw the platforms
	for (auto& platform : m_platforms)
	{
		platform.draw(renderer);
	}

	for (int i = 0; i < m_numOfLocalPlayers; i++)
	{
		m_localPlayers.at(i).draw(renderer);
	}
	for (int i = 0; i < m_numOfOnlinePlayers; i++)
	{
		m_onlinePlayers.at(i).draw(renderer);
	}

	m_pickUp.draw(renderer);
}

void GameScene::handleInput(InputSystem & input)
{
	//Handle input for all players
	for (int i = 0; i < m_numOfLocalPlayers; i++)
	{
		m_localPlayers.at(i).handleInput(*m_localInputs.at(i));
	}
	for (int i = 0; i < m_numOfOnlinePlayers; i++)
	{
		m_onlinePlayers.at(i).handleInput(*m_onlineInputs.at(i));
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
		for (int i = 0; i < m_numOfLocalPlayers; i++)
		{
			m_localPlayers.at(i).flipGravity();
		}
		for (int i = 0; i < m_numOfOnlinePlayers; i++)
		{
			m_onlinePlayers.at(i).flipGravity();
		}
		m_collisionListener.flipGravity();
	}
}

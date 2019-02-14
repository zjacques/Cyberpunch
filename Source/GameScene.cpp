#include "GameScene.h"

GameScene::GameScene()
{
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
		m_localPlayers.push_back(createPlayer(i,600 + 150 * i, 360));
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
	//for (auto& player : m_localPlayers)
	//	player.deletePlayer();

	//m_localInputs.clear();
	m_physicsWorld.deleteWorld(); //Delete the physics world
	m_platforms.clear(); //Delete the platforms of the game
	m_numOfLocalPlayers = 0;
	m_pickUp.deletePickUp();
}

void GameScene::update(double dt)
{
	//Update the physics world, do this before ANYTHING else
	m_physicsWorld.update(dt);
	//Update the player physics system
	Scene::systems()["Player Physics"]->update(dt);
}

Entity * GameScene::createPlayer(int index,int posX, int posY)
{
	auto p = new Entity("Player");
	p->addComponent("Pos", new PositionComponent(0, 0));

	//Create and initiliase the input component
	auto input = new PlayerInputComponent();
	Scene::systems()["Input"]->addComponent(input);
	input->initialiseJoycon(index);

	//Create the physics component and set up the bodies
	auto phys = new PlayerPhysicsComponent(&p->getComponent("Pos"));
	phys->m_body = m_physicsWorld.createBox(posX, posY, 50, 50, false, false, b2BodyType::b2_dynamicBody);
	phys->m_jumpSensor = m_physicsWorld.createBox(posX, posY + 25, 50, 50, false, false, b2BodyType::b2_dynamicBody);

	m_physicsWorld.addProperties(*phys->m_body, 1, 0.05f, 0.0f, false, new PhysicsComponent::ColData("Player Body", p));
	m_physicsWorld.addProperties(*phys->m_jumpSensor, 1, 0.05f, 0.0f, true, new PhysicsComponent::ColData("Jump Sensor", p));

	//Set the gravity scale to 2, this makes the player less floaty
	phys->m_body->getBody()->SetGravityScale(2.0f);

	//Create the joint between the player and the jump sensor
	phys->createJoint(m_physicsWorld);

	//Add the components to the entity
	p->addComponent("Input", input);
	p->addComponent("Player Physics", phys);

	//Add the physics component to the playe rphysics system
	Scene::systems()["Player Physics"]->addComponent(phys);

	return p; //Return the created entity
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
		SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
		auto phys = static_cast<PlayerPhysicsComponent*>(&m_localPlayers.at(i)->getComponent("Player Physics"));
		SDL_Rect rect;
		rect.w = phys->m_body->getSize().x;
		rect.h = phys->m_body->getSize().y;
		rect.x = phys->m_body->getPosition().x - (rect.w / 2);
		rect.y = phys->m_body->getPosition().y - (rect.h / 2);
		SDL_RenderFillRect(&renderer, &rect);
	}
	for (int i = 0; i < m_numOfOnlinePlayers; i++)
	{
		m_onlinePlayers.at(i).draw(renderer);
	}

	//m_pickUp.draw(renderer);
}

void GameScene::handleInput(InputSystem & input)
{
	//Update the input system
	Scene::systems()["Input"]->update(0);

	for (int i = 0; i < m_numOfLocalPlayers; i++)
	{
		auto input = static_cast<InputComponent*>(&m_localPlayers.at(i)->getComponent("Input"));
		input->handleInput(m_localPlayers.at(i));
	}
	for (int i = 0; i < m_numOfOnlinePlayers; i++)
	{
		m_onlinePlayers.at(i).handleInput(*m_onlineInputs.at(i));
	}



	//Handle input for all players
	//for (int i = 0; i < m_numOfLocalPlayers; i++)
	//{
	//	m_localPlayers.at(i).handleInput(*m_localInputs.at(i));
	//}

	////If the pause button has been pressed on either joycon
	//if (input.isButtonPressed("A"))
	//{
	//	Scene::goToScene("Main Menu");
	//}
	//if (input.isButtonPressed("Space"))
	//{
	//	//Flip the gravioty of the physics system and the physics world
	//	m_physicsSystem.flipGravity();
	//	m_physicsWorld.flipGravity();
	//	for (int i = 0; i < m_numOfLocalPlayers; i++)
	//	{
	//		m_localPlayers.at(i).flipGravity();
	//	}
	//	m_collisionListener.flipGravity();
	//}
}

#include "GameScene.h"

GameScene::GameScene()
{

}

void GameScene::start()
{
	m_physicsSystem = PhysicsSystem(); // Recreate the physics system
	m_physicsWorld.initWorld(); //Create the physics world
	m_physicsWorld.addContactListener(m_collisionListener); //Add collision listener to the world

	//Recreate the attack system
	Scene::systems()["Attack"] = new AttackSystem(m_physicsWorld);

	//m_player.createPlayer(m_physicsWorld, m_physicsSystem);
	// m_pickUp.createPickUp(m_physicsWorld, m_physicsSystem);
	auto pickupSys = new PickUpSystem();
	pickupSys->setWorld(m_physicsWorld);
	Scene::systems()["PickUp"] = pickupSys;
//	Scene::systems()["Booth"] = new DJBoothSystem();

	m_bG = Scene::resources().getTexture("Game BG");
//	m_recordt = Scene::resources().getTexture("Record.png");

	m_numOfLocalPlayers = SDL_NumJoysticks();

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

	/*for(auto& m_djBooths : Scene::resources().getLevelData()["Booth"])
	{
		int x = m_djBooths["X"], y = m_djBooths["Y"], w = m_djBooths["W"], h = m_djBooths["H"];
		std::string tag = m_djBooths["Tag"];
		auto newPlat = Platform(tag);
	
	}
*/
	m_pickUp = new Entity("pickup_entity");
	auto pos = new PositionComponent(0,0);
	m_pickUp->addComponent("Pos", pos);
    m_pickUp->addComponent("PickUp",new PickUpComponent());



	auto phys = new PhysicsComponent(pos);
	phys->m_body = m_physicsWorld.createBox(1920 / 2, 1080 / 2, 50, 50, false, false, b2BodyType::b2_staticBody);
	m_physicsWorld.addProperties(*phys->m_body, 0, 0, 0, true, new PhysicsComponent::ColData("PickUp", m_pickUp));
	m_pickUp->addComponent("Physics", phys);

	Scene::systems()["PickUp"]->addComponent(&m_pickUp->getComponent("PickUp"));
	
}

void GameScene::stop()
{
	m_physicsWorld.deleteWorld(); //Delete the physics world
	m_platforms.clear(); //Delete the platforms of the game
	m_numOfLocalPlayers = 0;
	//m_pickUp.deletePickUp();
}

void GameScene::update(double dt)
{
	//Update the physics world, do this before ANYTHING else
	m_physicsWorld.update(dt);
	//Update the player physics system
	Scene::systems()["Player Physics"]->update(dt);
	Scene::systems()["Attack"]->update(dt);
	Scene::systems()["PickUp"]->update(dt);
	//Scene::systems()["Booth"]->update(dt);


	

}

Entity * GameScene::createPlayer(int index,int posX, int posY)
{
	auto p = new Entity("Player");
	p->addComponent("Pos", new PositionComponent(0, 0));
	p->addComponent("Attack", new AttackComponent());

	//Add the players attack component to the attack system
	Scene::systems()["Attack"]->addComponent(&p->getComponent("Attack"));

	//Create and initiliase the input component
	auto input = new PlayerInputComponent();
	Scene::systems()["Input"]->addComponent(input);
	input->initialiseJoycon(index);

	//Create the physics component and set up the bodies
	auto phys = new PlayerPhysicsComponent(&p->getComponent("Pos"));
	phys->m_body = m_physicsWorld.createBox(posX, posY, 50, 50, false, false, b2BodyType::b2_dynamicBody);
	phys->m_jumpSensor = m_physicsWorld.createBox(posX, posY + 22.5f, 45, 5, false, false, b2BodyType::b2_dynamicBody);

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
//
//Entity*  GameScene::createDJB(int index, int posX, int posY)
//{
//	auto booth = new Entity("Booth");
//	auto pos = new PositionComponent(0, 0);
//	booth->addComponent("Pos", pos);
//
//	auto phys = new PhysicsComponent(pos);
//	phys->m_body = m_physicsWorld.createBox(posX, posY, 50, 50, false, false, b2BodyType::b2_dynamicBody);
//
//	m_physicsWorld.addProperties(*phys->m_body, 1, 0.05f, 0.0f, false, new PhysicsComponent::ColData("Booth", booth));
//	booth->addComponent("Booth", phys);
//
////	Scene::systems()["Booth"]->addComponent(phys);
//
//	return booth; //Return the created entity
//}

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


	/*for (int i = 0; i < m_numOfLocalPlayers; i++)
	{
		SDL_SetRenderDrawColor(&renderer, 0, 255, 0, 255);
		auto phys = static_cast<PhysicsComponent*>(&m_djBooths.at(i)->getComponent("Booth"));
		SDL_Rect rect;
		rect.w = phys->m_body->getSize().x;
		rect.h = phys->m_body->getSize().y;
		rect.x = phys->m_body->getPosition().x - (rect.w / 2);
		rect.y = phys->m_body->getPosition().y - (rect.h / 2);
		SDL_RenderFillRect(&renderer, &rect);
	}*/
	
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


	auto pC = static_cast<PickUpComponent*>(&m_pickUp->getComponent("PickUp"));
	if (pC->spawned())
	{
		auto phys = static_cast<PhysicsComponent*>(&m_pickUp->getComponent("Physics"));
		rect.w = phys->m_body->getSize().x;
		rect.h = phys->m_body->getSize().y;
		rect.x = phys->m_body->getPosition().x - (rect.w / 2);
		rect.y = phys->m_body->getPosition().y - (rect.h / 2);
		SDL_SetRenderDrawColor(&renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(&renderer, &rect);
	}
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

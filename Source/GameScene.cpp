#include "GameScene.h"
#include "RenderSystem.h"

GameScene::GameScene() :
	m_bgEntity("Game BG"),
	m_platformsCreated(false)
{

}

void GameScene::start()
{
	m_physicsSystem = PhysicsSystem(); // Recreate the physics system
	m_physicsWorld.initWorld(); //Create the physics world
	m_physicsWorld.addContactListener(m_collisionListener); //Add collision listener to the world

	//Recreate the attack system
	Scene::systems()["Attack"] = new AttackSystem(m_physicsWorld);

	auto pickupSys = new PickUpSystem();
	pickupSys->setWorld(m_physicsWorld);
	Scene::systems()["PickUp"] = pickupSys;
	//Scene::systems()["Booth"] = new DJBoothSystem();

	//Create background entity
	auto bgPos = new PositionComponent(1920 /2 , 1080 / 2);
	m_bgEntity.addComponent("Pos", bgPos);
	m_bgEntity.addComponent("Sprite", new SpriteComponent(bgPos, Vector2f(1920, 1080 ), Vector2f(1920 * 1.25f, 1080 * 1.25f), Scene::resources().getTexture("Game BG"), 0));
	//Add bg sprite component to the render system
	Scene::systems()["Render"]->addComponent(&m_bgEntity.getComponent("Sprite"));

	m_numOfLocalPlayers = SDL_NumJoysticks();
	m_numOfOnlinePlayers = 0;

	// Initialise SDL_net (Note: We don't initialise or use normal SDL at all - only the SDL_net library!)
	if (SDLNet_Init() == -1)
	{
		std::cerr << "Failed to intialise SDL_net: " << SDLNet_GetError() << std::endl;
		exit(-1);
	}

	/*for(auto& m_djBooths : Scene::resources().getLevelData()["Booth"])
	{
		int x = m_djBooths["X"], y = m_djBooths["Y"], w = m_djBooths["W"], h = m_djBooths["H"];
		std::string tag = m_djBooths["Tag"];
		auto newPlat = Platform(tag);*/
	
	//try to create the online system and connect
	//refactor to another spot once we get the full lobby system going I guess.
	static_cast<OnlineSystem*>(Scene::systems()["Network"])->ConnectToServer();
	/*auto net = new OnlineSystem();
	if (net->ConnectToServer())
		Scene::systems()["Network"] = net;
	else
		delete net;*/

	//Create players for extra inputs
	for (int i = 0; i < m_numOfLocalPlayers; i++)
	{
		m_localPlayers.push_back(createPlayer(i,600 + 150 * i, 360, true));
	}
	for (int i = 0; i < m_numOfOnlinePlayers; i++)
	{
		m_onlinePlayers.push_back(createPlayer(i+ m_numOfLocalPlayers, 600 + 150 * i+ m_numOfLocalPlayers, 360, false));
	}
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
	m_platformsCreated = false;
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
	Scene::systems()["Animation"]->update(dt); //Update the animation components

	//Update camera
	updateCamera(dt);
}

void GameScene::updateCamera(double dt)
{
	//The average position of the players
	auto avgPos = Vector2f(1920 / 2 , 1080 / 2);
	float maxDist = 0.0f;
	auto center = Vector2f();

	Vector2f lastP;
	int divisors = 0;

	for (auto& player : m_localPlayers)
	{
		auto pos = static_cast<PositionComponent*>(&player->getComponent("Pos"))->position;
		divisors++;
		avgPos += pos;

		if (lastP.x != 0 && lastP.y != 0)
		{
			//Get distance
			float dist = lastP.distance(pos);

			if (dist > maxDist)
			{
				maxDist = dist;
			}
		}

		lastP = pos;
	}

	if (divisors > 0)
	{
		maxDist += 50;

		auto minZoom = Vector2f(1920 / 2, 1080 / 2);
		auto maxZoom = Vector2f(1920 * m_camera.MAX_ZOOM / 2, 1080 * m_camera.MAX_ZOOM / 2);

		auto diff = minZoom.distance(maxZoom);
		maxDist = maxDist > diff ? diff : maxDist;

		float percentage = maxDist / diff;

		m_camera.zoom(m_camera.MAX_ZOOM - percentage * .55f);
	}

	m_camera.centerCamera(avgPos / (divisors + 1));
	//Update the camera
	m_camera.update(dt);
}

Entity * GameScene::createPlayer(int index,int posX, int posY, bool local)
{
	auto p = new Entity("Player");
	p->addComponent("Pos", new PositionComponent(0,0));
	p->addComponent("Attack", new AttackComponent());
	p->addComponent("Sprite", new SpriteComponent(&p->getComponent("Pos"), Vector2f(50,50), Vector2f(50, 50), Scene::resources().getTexture("Player"), 2));

	Scene::systems()["Render"]->addComponent(&p->getComponent("Sprite"));

	//Add the players attack component to the attack system
	Scene::systems()["Attack"]->addComponent(&p->getComponent("Attack"));

	//Create and initiliase the input component
	if (local) {
		auto input = new PlayerInputComponent();
		Scene::systems()["Input"]->addComponent(input);
		input->initialiseJoycon(index);
		p->addComponent("Input", input);
	}
	else {
		auto input = new OnlineInputComponent();
		static_cast<OnlineSystem*>(Scene::systems()["Network"])->addReceivingPlayer(input);
		p->addComponent("Input", input);
	}


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

	//Try to add a sender to the server
	auto netSys = static_cast<OnlineSystem*>(Scene::systems()["Network"]);
	if (netSys->isConnected && local)
	{
		auto net = new OnlineSendComponent();
		p->addComponent("Send", net);
		netSys->addSendingPlayer(net);
	} //if it can't connect to the server, it didn't need to be online anyway

	//Add the components to the entity
	p->addComponent("Player Physics", phys);

	//Add the physics component to the player physics system
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

void GameScene::createPlatforms(SDL_Renderer& renderer)
{	
	//Create all of the platforms for the game
	for (auto& platform : Scene::resources().getLevelData()["Platforms"])
	{
		//Get the X,Y,Width and Height of the platform
		int x = platform["X"], y = platform["Y"], w = platform["W"], h = platform["H"];
		std::string tag = platform["Tag"];

		//Creta ethe platform entity
		auto newPlat = new Entity("Platform");
		auto platPos = new PositionComponent(x, y);
		newPlat->addComponent("Pos", platPos);
		auto phys = new PhysicsComponent(platPos);
		phys->m_body = m_physicsWorld.createBox(x, y, w, h, false, true, b2BodyType::b2_staticBody);
		m_physicsWorld.addProperties(*phys->m_body, 0, .1f, 0, false, new PhysicsComponent::ColData(tag, newPlat));
		newPlat->addComponent("Physics", phys);
		Scene::systems()["Physics"]->addComponent(phys);

		//Create the texture for the platform
		auto texture = SDL_CreateTexture(&renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, w, h);
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		//Set it to draw to the texture we just created
		SDL_SetRenderTarget(&renderer, texture);


		SDL_Rect rect, srcRect;

		auto size = Vector2f(50 * (tag == "Floor" ? 1 : .5f), 50 * (tag == "Floor" ? 1 : .5f));
		auto smallW = tag == "Floor" ? 50 : 25;
		auto offset = Vector2f(size.x - w, size.y - w);
		auto start = Vector2f((int)x - ((int)w / 2), (int)y - ((int)h / 2));
		int numOfTiles = w / (tag == "Floor" ? 50 : 25);

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = 50;
		srcRect.h = 50;

		//Loop through the tiles and draw to the texture we just created the shape of the platform
		for (int i = 0; i < numOfTiles; i++)
		{
			rect.w = size.x;
			rect.h = size.y;
			rect.x = 0 + i * smallW;
			rect.y = 0;

			if (i == 0)
			{
				SDL_RenderCopy(&renderer, Scene::resources().getTexture("Platform Green 0"), &srcRect, &rect);
				SDL_RenderCopy(&renderer, Scene::resources().getTexture("Platform Green 0"), &srcRect, &rect);
			}
			else if (i == (numOfTiles - 1))
			{
				SDL_RenderCopy(&renderer, Scene::resources().getTexture("Platform Green 2"), &srcRect, &rect);
				SDL_RenderCopy(&renderer, Scene::resources().getTexture("Platform Green 2"), &srcRect, &rect);
			}
			else
			{
				SDL_RenderCopy(&renderer, Scene::resources().getTexture("Platform Green 1"), &srcRect, &rect);
				SDL_RenderCopy(&renderer, Scene::resources().getTexture("Platform Green 1"), &srcRect, &rect);
			}
		}
		SDL_SetRenderTarget(&renderer, NULL);
		SDL_RenderCopy(&renderer, texture, NULL, &rect);
		

		newPlat->addComponent("Sprite", new SpriteComponent(platPos, Vector2f(w, h), Vector2f(w, h), texture, 1));

		Scene::systems()["Render"]->addComponent(&newPlat->getComponent("Sprite"));
	}

	//Set platforms created as true
	m_platformsCreated = true;
}

SDL_Rect GameScene::createRect(int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return rect;
}

void GameScene::draw(SDL_Renderer & renderer)
{
	if (m_platformsCreated == false)
		createPlatforms(renderer);

	SDL_Rect rect;

	//Draw sprites in the render system
	auto renderSystem = static_cast<RenderSystem*>(Scene::systems()["Render"]);
	renderSystem->render(renderer, m_camera);

	//Drawing the jump sensors and attack boxes for the player (For debug only, this will be deleted)
	for (int i = 0; i < m_numOfLocalPlayers; i++)
	{
		auto phys = static_cast<PlayerPhysicsComponent*>(&m_localPlayers.at(i)->getComponent("Player Physics"));
		auto hit = static_cast<AttackComponent*>(&m_localPlayers.at(i)->getComponent("Attack"));

		//If the player is stunned, draw a yellow rectangle
		if (phys->stunned())
		{
			rect.w = phys->m_body->getSize().x;
			rect.h = phys->m_body->getSize().y;
			rect.x = phys->m_body->getPosition().x - (rect.w / 2);
			rect.y = phys->m_body->getPosition().y - (rect.h / 2);
			SDL_SetRenderDrawColor(&renderer, 255, 255, 0, 255);
			SDL_RenderFillRect(&renderer, &rect);
		}


		rect.w = phys->m_jumpSensor->getSize().x;
		rect.h = phys->m_jumpSensor->getSize().y;
		rect.x = phys->m_jumpSensor->getPosition().x - (rect.w / 2);
		rect.y = phys->m_jumpSensor->getPosition().y - (rect.h / 2);
		SDL_SetRenderDrawColor(&renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(&renderer, &rect);

		if (nullptr != hit->m_currentAttack)
		{
			rect.w = hit->m_currentAttack->m_body->getSize().x;
			rect.h = hit->m_currentAttack->m_body->getSize().y;
			rect.x = hit->m_currentAttack->m_body->getPosition().x - (rect.w / 2);
			rect.y = hit->m_currentAttack->m_body->getPosition().y - (rect.h / 2);
			SDL_SetRenderDrawColor(&renderer, 0, 255, 0, 255);
			SDL_RenderDrawRect(&renderer, &rect);
		}
	}
	for (int i = 0; i < m_numOfOnlinePlayers; i++)
	{
		SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
		auto phys = static_cast<PlayerPhysicsComponent*>(&m_onlinePlayers.at(i)->getComponent("Player Physics"));
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
	for (int i = 0; i < m_numOfOnlinePlayers; i++)
	{
		auto input = static_cast<OnlineInputComponent*>(&m_onlinePlayers.at(i)->getComponent("Input"));
		input->handleInput(m_onlinePlayers.at(i));
		//m_onlinePlayers.at(i).handleInput(*m_onlineInputs.at(i));
	}
}

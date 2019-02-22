#include "GameScene.h"
#include "RenderSystem.h"
#include "PlayerRespawnSystem.h"
#include "AnimationComponent.h"
#include "DustSystem.h"
#include "PickUpSystem.h"

GameScene::GameScene() :
	m_bgEntity("Game BG"),
	m_platformsCreated(false),
	m_camera(false)
{

}

void GameScene::start()
{
	m_physicsSystem = PhysicsSystem(); // Recreate the physics system
	m_physicsWorld.initWorld(); //Create the physics world
	m_physicsWorld.addContactListener(m_collisionListener); //Add collision listener to the world

	//Recreate the attack system
	Scene::systems()["Attack"] = new AttackSystem(m_physicsWorld);
	//Recreate the dust system
	Scene::systems()["Dust"] = new DustSystem(&Scene::systems(), &m_localPlayers, &Scene::resources());
	Scene::systems()["Respawn"] = new PlayerRespawnSystem();
	static_cast<PickUpSystem*>(Scene::systems()["Pickup"])->setWorld(m_physicsWorld);
	Scene::systems()["Booth"] = new DJBoothSystem();

	//m_AIPlayers.push_back(createAI(1, 600 + 150 * 1, 360));

	//Create background entity
	auto bgPos = new PositionComponent(1920 /2 , 1080 / 2);
	m_bgEntity.addComponent("Pos", bgPos);
	m_bgEntity.addComponent("Sprite", new SpriteComponent(bgPos, Vector2f(1920, 1080 ), Vector2f(1920, 1080), Scene::resources().getTexture("Game BG"), 0));
	//Add bg sprite component to the render system
	Scene::systems()["Render"]->addComponent(&m_bgEntity.getComponent("Sprite"));

	m_numOfLocalPlayers = SDL_NumJoysticks();
	m_numOfOnlinePlayers = 0;//get the number of players from the network system

	// Initialise SDL_net (Note: We don't initialise or use normal SDL at all - only the SDL_net library!)
	/*if (SDLNet_Init() == -1)
	{
		std::cerr << "Failed to intialise SDL_net: " << SDLNet_GetError() << std::endl;
		exit(-1);
	}*/
	
	//try to create the online system and connect
	//refactor to another spot once we get the full lobby system going I guess.
	//static_cast<OnlineSystem*>(Scene::systems()["Network"])->ConnectToServer();
	/*auto net = new OnlineSystem();
	if (net->ConnectToServer())
		Scene::systems()["Network"] = net;
	else
		delete net;*/
	

	//Create players, pass in the spawn locations to respawn players
	std::vector<Vector2f> spawnPos;

	for (int i = 0; i < Scene::resources().getLevelData()["Spawn Points"].size(); i++)
	{
		auto point = Scene::resources().getLevelData()["Spawn Points"].at(i);
		spawnPos.push_back(Vector2f(point["X"], point["Y"]));
	}
	for (int i = 0; i < m_numOfLocalPlayers; i++)
	{
		m_localPlayers.push_back(createPlayer(i,600 + 150 * i, 360, true, spawnPos));
	}
	for (int i = 0; i < m_numOfOnlinePlayers; i++)
	{
		m_onlinePlayers.push_back(createPlayer(i+ m_numOfLocalPlayers, 600 + 150 * i+ m_numOfLocalPlayers, 360, false, spawnPos));
	}
	
	//pickup Entity
	m_pickUp = new Entity("PickUp");
	auto pos = new PositionComponent(0,0);
	m_pickUp->addComponent("Pos", pos);
	m_pickUp->addComponent("PickUp",new PickUpComponent(m_pickUp));
	m_pickUp->addComponent("Sprite", new SpriteComponent(&m_pickUp->getComponent("Pos"), Vector2f(1500, 50), Vector2f(50, 50), Scene::resources().getTexture("Record"), 1));
	auto anim = new AnimationComponent(&m_pickUp->getComponent("Sprite"));		
	std::vector<SDL_Rect> m_spinAnimation;
	for (int i = 0; i < 30; i++)
		m_spinAnimation.push_back({i*50, 0, 50, 50});
	anim->addAnimation("Spin", Scene::resources().getTexture("Record"), m_spinAnimation, 1.75f);
	anim->playAnimation("Spin", true);
	Scene::systems()["Animation"]->addComponent(anim);
	m_pickUp->addComponent("Animation", anim);
	Scene::systems()["Pickup"]->addComponent(&m_pickUp->getComponent("PickUp"));

	//DJBooths created here 
	auto& booths = Scene::resources().getLevelData()["Booth"];

	for (int i = 0; i < booths.size(); i++)
	{
		m_djBooths.push_back(createDJB(i, booths.at(i)["X"], booths.at(i)["Y"]));
	}

	auto& kb = Scene::resources().getLevelData()["Kill Boxes"];
	for (int i = 0; i < kb.size(); i++)
	{
		m_killboxes.push_back(createKillBox(kb.at(i)["X"], kb.at(i)["Y"], kb.at(i)["W"], kb.at(i)["H"]));
	}
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
	float scalar = static_cast<DJBoothSystem*>(Scene::systems()["Booth"])->getScalar();
	//Update the physics world, do this before ANYTHING else
	m_physicsWorld.update(dt * scalar);
	//Update the player physics system

	Scene::systems()["Player Physics"]->update(dt * scalar);
	Scene::systems()["Physics"]->update(dt * scalar);
	Scene::systems()["Attack"]->update(dt * scalar);
	Scene::systems()["Pickup"]->update(dt * scalar);
	Scene::systems()["Booth"]->update(dt);
	Scene::systems()["Animation"]->update(dt * scalar); //Update the animation components
	Scene::systems()["AI"]->update(dt * scalar);
	Scene::systems()["Dust"]->update(dt * scalar);
	Scene::systems()["Respawn"]->update(dt * scalar);


	//Update camera
	updateCamera(dt * scalar);
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
		if (static_cast<PlayerComponent*>(&player->getComponent("Player"))->isDead() == false)
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

Entity * GameScene::createPlayer(int index,int posX, int posY, bool local, std::vector<Vector2f> spawnPositions)
{
	auto p = new Entity("Player");
	p->addComponent("Pos", new PositionComponent(0,0));
	p->addComponent("Dust Trigger", new DustTriggerComponent());
	p->addComponent("Attack", new AttackComponent());
	p->addComponent("Player", new PlayerComponent(spawnPositions, p));
	p->addComponent("Sprite", new SpriteComponent(&p->getComponent("Pos"), Vector2f(1220,85), Vector2f(61, 85), Scene::resources().getTexture("Player Idle"), 2));
	auto animation = new AnimationComponent(&p->getComponent("Sprite"));
	p->addComponent("Animation", animation);

	std::vector<SDL_Rect> m_animRects; //The rectangles for the animations

	for (int i = 0; i < 20; i++)
	{
		m_animRects.push_back({61 * i, 0, 61, 85});
	}

	animation->addAnimation("Run", Scene::resources().getTexture("Player Run"), m_animRects, .75f);
	animation->addAnimation("Idle", Scene::resources().getTexture("Player Idle"), m_animRects, .5f);
	m_animRects.clear();
	for (int i = 0; i < 20; i++)
	{
		m_animRects.push_back({71 * i, 0, 71, 83 });
	}
	animation->addAnimation("Ground Kick", Scene::resources().getTexture("Player Ground Kick"), m_animRects, .4f);
	animation->playAnimation("Idle", true); //Play the idle animation from the start


	//Add components to the system
	Scene::systems()["Animation"]->addComponent(&p->getComponent("Animation"));
	Scene::systems()["Render"]->addComponent(&p->getComponent("Sprite"));
	//Add the players attack component to the attack system
	Scene::systems()["Attack"]->addComponent(&p->getComponent("Attack"));
	Scene::systems()["Respawn"]->addComponent(&p->getComponent("Player"));

	//Create and initiliase the input component
	if (local) {
		auto input = new PlayerInputComponent();
		Scene::systems()["Input"]->addComponent(input);
		input->initialiseJoycon(index);
		input->m_playerNumber = index;
		p->addComponent("Input", input);
	}
	else {
		auto input = new OnlineInputComponent();
		static_cast<OnlineSystem*>(Scene::systems()["Network"])->addReceivingPlayer(input);
		input->m_playerNumber = index;
		p->addComponent("Input", input);
	}


	//Create the physics component and set up the bodies
	auto phys = new PlayerPhysicsComponent(&p->getComponent("Pos"));
	phys->m_body = m_physicsWorld.createBox(posX, posY, 30, 78, false, false, b2BodyType::b2_dynamicBody);
	phys->m_jumpSensor = m_physicsWorld.createBox(posX, posY, 27, 5, false, false, b2BodyType::b2_dynamicBody);

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
		net->m_playerNumber = index;
		p->addComponent("Send", net);
		netSys->addSendingPlayer(net);
	} //if it can't connect to the server, it didn't need to be online anyway

	//Add the components to the entity
	p->addComponent("Player Physics", phys);

	//Add the physics component to the player physics system
	Scene::systems()["Player Physics"]->addComponent(phys);

	return p; //Return the created entity
}

Entity * GameScene::createKillBox(int posX, int posY, int width, int height)
{
	auto kb = new Entity("KillBox");
	auto pos = new PositionComponent(0,0);
	kb->addComponent("Pos", pos);
	auto phys = new PhysicsComponent(pos);
	phys->m_body = m_physicsWorld.createBox(posX, posY, width, height, false, false, b2_staticBody);
	m_physicsWorld.addProperties(*phys->m_body, 0, 0, 0, true, new PhysicsComponent::ColData("Kill Box", kb));
	kb->addComponent("Physics", phys);
	Scene::systems()["Physics"]->addComponent(phys);
	return kb;
}

Entity* GameScene::createDJB(int index, int posX, int posY)
{
	auto booth = new Entity("Booth");
	auto pos = new PositionComponent(0, 0);
	booth->addComponent("Pos", pos);

	//creates a Box2d body for the djbooth defines its propoerties and applies a sprite
	auto phys = new PhysicsComponent(pos);
	phys->m_body = m_physicsWorld.createBox(posX, posY, 150, 50, false, false, b2BodyType::b2_staticBody);
	m_physicsWorld.addProperties(*phys->m_body, 1, 0.05f, 0.0f, true, new PhysicsComponent::ColData("Booth", booth));
	booth->addComponent("Physics", phys);
	Scene::systems()["Physics"]->addComponent(phys);
	booth->addComponent("Sprite", new SpriteComponent(pos, Vector2f(152, 93), Vector2f(152, 93), Scene::resources().getTexture("Booth" + std::to_string(index)), 1));
	Scene::systems()["Render"]->addComponent(&booth->getComponent("Sprite"));

	if (index == 0)
	{
		//this will call the gravity Component when the player punches it



		booth->addComponent("DJ Booth", new GravityBoothComponent(m_localPlayers, &m_physicsWorld, &m_physicsSystem, &m_collisionListener));
	}
	else if (index == 1)
	{
		//this will call the slow down Component when the player punches it
		booth->addComponent("DJ Booth", new SlowBoothComponent());
	}
	else if (index == 2)
	{
		////this will call the platforming moving Component when the player punches it
		booth->addComponent("DJ Booth", new PlatformBoothComponent(&m_platforms));
	}

	Scene::systems()["Booth"]->addComponent(&booth->getComponent("DJ Booth"));
	return booth;
}

/// <summary>
/// 
/// </summary>
/// <param name="index"></param>
/// <param name="posX"></param>
/// <param name="posY"></param>
/// <returns></returns>
Entity * GameScene::createAI(int index, int posX, int posY)
{
	auto ai = new Entity("AI");
	auto pos = new PositionComponent(0, 0);
	ai->addComponent("Pos", pos);
	ai->addComponent("Dust Trigger", new DustTriggerComponent());
	ai->addComponent("Attack", new AttackComponent());
	ai->addComponent("Sprite", new SpriteComponent(&ai->getComponent("Pos"), Vector2f(50, 50), Vector2f(50, 50), Scene::resources().getTexture("Player Run"), 2));
	auto behaviour = new AIComponent();
	Scene::systems()["AI"]->addComponent(behaviour);

	//Add the players attack component to the attack system
	Scene::systems()["Attack"]->addComponent(&ai->getComponent("Attack"));

	Scene::systems()["Render"]->addComponent(&ai->getComponent("Sprite"));

	//Create the physics component and set up the bodies
	auto phys = new PlayerPhysicsComponent(&ai->getComponent("Pos"));
	phys->m_body = m_physicsWorld.createBox(posX, posY, 50, 50, false, false, b2BodyType::b2_dynamicBody);
	phys->m_jumpSensor = m_physicsWorld.createBox(posX, posY + 22.5f, 45, 5, false, false, b2BodyType::b2_dynamicBody);

	m_physicsWorld.addProperties(*phys->m_body, 1, 0.05f, 0.0f, false, new PhysicsComponent::ColData("Player Body", ai));
	m_physicsWorld.addProperties(*phys->m_jumpSensor, 1, 0.05f, 0.0f, true, new PhysicsComponent::ColData("Jump Sensor", ai));

	//Set the gravity scale to 2, this makes the player less floaty
	phys->m_body->getBody()->SetGravityScale(2.0f);

	//Create the joint between the player and the jump sensor
	phys->createJoint(m_physicsWorld);

	//Add the components to the entity
	ai->addComponent("Player Physics", phys);

	//Add the physics component to the playe rphysics system
	Scene::systems()["Player Physics"]->addComponent(phys);

	return ai;
}

/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void GameScene::createPlatforms(SDL_Renderer& renderer)
{	
	//Create all of the platforms for the game
	for (auto& platform : Scene::resources().getLevelData()["Platforms"])
	{
		//Get the X,Y,Width and Height of the platform
		int x = platform["X"], y = platform["Y"], w = platform["W"], h = platform["H"];
		std::string tag = platform["Tag"];

		//Creta ethe platform entity
		auto newPlat = new Entity(tag);
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

		m_platforms.push_back(newPlat);
	}

	//Set platforms created as true
	m_platformsCreated = true;
}

/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
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

		//Draw the players outline for the hitbox
		rect.w = phys->m_body->getSize().x;
		rect.h = phys->m_body->getSize().y;
		rect.x = phys->m_body->getPosition().x - (rect.w / 2) - m_camera.x();
		rect.y = phys->m_body->getPosition().y - (rect.h / 2) - m_camera.y();

		if (phys->isSupered())
		{
			SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(&renderer, &rect);
		}
		//Draw orange if stunned by a super punch
		else if (phys->superStunned())
		{
			SDL_SetRenderDrawColor(&renderer, 255, 110, 0, 55);
			SDL_RenderFillRect(&renderer, &rect);
		}
		//If the player is stunned, draw a yellow rectangle
		else if (phys->stunned())
		{
			SDL_SetRenderDrawColor(&renderer, 255, 255, 0, 20);
			SDL_RenderFillRect(&renderer, &rect);
		}


		rect.w = phys->m_jumpSensor->getSize().x;
		rect.h = phys->m_jumpSensor->getSize().y;
		rect.x = phys->m_jumpSensor->getPosition().x - (rect.w / 2) - m_camera.x();
		rect.y = phys->m_jumpSensor->getPosition().y - (rect.h / 2) - m_camera.y();
		SDL_SetRenderDrawColor(&renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(&renderer, &rect);

		if (nullptr != hit->m_currentAttack)
		{
			rect.w = hit->m_currentAttack->m_body->getSize().x;
			rect.h = hit->m_currentAttack->m_body->getSize().y;
			rect.x = hit->m_currentAttack->m_body->getPosition().x - (rect.w / 2) - m_camera.x();
			rect.y = hit->m_currentAttack->m_body->getPosition().y - (rect.h / 2) - m_camera.y();
			SDL_SetRenderDrawColor(&renderer, 0, 255, 0, 255);
			SDL_RenderDrawRect(&renderer, &rect);
		}
	}

	for (auto i : m_AIPlayers)
	{
		SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
		auto phys = static_cast<PlayerPhysicsComponent*>(&i->getComponent("Player Physics"));

		for (int i = 0; i < m_numOfOnlinePlayers; i++)
		{
			SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
			auto phys = static_cast<PlayerPhysicsComponent*>(&m_onlinePlayers.at(i)->getComponent("Player Physics"));

			SDL_Rect rect;
			rect.w = phys->m_body->getSize().x;
			rect.h = phys->m_body->getSize().y;
			rect.x = phys->m_body->getPosition().x - (rect.w / 2) -m_camera.x();
			rect.y = phys->m_body->getPosition().y - (rect.h / 2) - m_camera.y();
			SDL_RenderFillRect(&renderer, &rect);

			rect.w = phys->m_jumpSensor->getSize().x;
			rect.h = phys->m_jumpSensor->getSize().y;
			rect.x = phys->m_jumpSensor->getPosition().x - (rect.w / 2) - m_camera.x();
			rect.y = phys->m_jumpSensor->getPosition().y - (rect.h / 2) - m_camera.y();
			SDL_SetRenderDrawColor(&renderer, 0, 255, 0, 255);
			SDL_RenderDrawRect(&renderer, &rect);
		}

		/*for (int i = 0; i < m_numOfOnlinePlayers; i++)
		{
			m_onlinePlayers.at(i).draw(renderer);
		}*/
		//m_pickUp.draw(renderer);
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
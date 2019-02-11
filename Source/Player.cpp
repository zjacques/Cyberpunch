#include "Player.h"


Player::Player() :
	m_canJump(false),
	m_gravFlipped(false),
	m_moveSystem(nullptr),
	m_canFall(false),
	m_falling(false),
	m_movingL(false),
	m_movingR(true),
	m_canPunch(true),
	m_punched(false),
	m_punchRecharge(.15f), //Temp
	m_rpttl(0),
	m_lpttl(0),
	m_timeTillPunch(m_punchRecharge),
	m_moveSpeed(10),
	m_jumpSpeed(20.0f),
	m_jumpDownSpeed(-10.0f),
	m_posComponent(0,0),
	m_floorSensor(&m_posComponent),
	m_physComponent(&m_posComponent),
	m_leftAttackSensor(&m_posComponent),
	m_rightAttackSensor(&m_posComponent)
{

}

void Player::createPlayer(Box2DBridge& world, PhysicsSystem& system)
{
	m_dmgPercent = 0; //Reset damage percentage
	m_worldPtr = &world; //Ste the world pointer
	m_physPtr = &system;

	m_floorSensor = PhysicsComponent(&m_posComponent);
	m_physComponent = PhysicsComponent(&m_posComponent);

	//Create the attack physics components
	m_leftAttackSensor = PhysicsComponent(&m_posComponent);
	m_rightAttackSensor = PhysicsComponent(&m_posComponent);

	//Create the bodies
	m_physComponent.m_body = world.createBox(960, 540, 50, 50, false, false, b2BodyType::b2_dynamicBody);
	m_floorSensor.m_body = world.createBox(960, 565, 45, 5, false, false, b2BodyType::b2_dynamicBody);

	//Add properties to the players bodies
	world.addProperties(*m_physComponent.m_body, 1, 0.05f, 0.0f, false, new PhysicsComponent::ColData("Player Body", this));
	world.addProperties(*m_floorSensor.m_body, 1, 0.05f, 0.0f, true, new PhysicsComponent::ColData("Jump Sensor", this));

	//Set gravity scale of the player
	m_physComponent.m_body->getBody()->SetGravityScale(2.0f);

	m_sensorJointDef.bodyA = m_physComponent.m_body->getBody();
	m_sensorJointDef.bodyB = m_floorSensor.m_body->getBody();
	m_sensorJointDef.collideConnected = false;
	m_sensorJointDef.localAnchorA.Set(0, .9f);
	
	//Create the joints
	m_sensorJoint = (b2RevoluteJoint*)world.getWorld().CreateJoint(&m_sensorJointDef);
}


void Player::deletePlayer()
{
	delete m_moveSystem;
	m_moveSystem = nullptr;
	m_canJump = false;
	m_canFall = false;
	m_gravFlipped = false;
	//Reset facing booleans
	m_movingL = false;
	m_movingR = true;
	m_canPunch = true;
	m_punched = false;
	m_timeTillPunch = m_punchRecharge; //Reset our punch timer
}

void Player::update(double dt)
{
	if (nullptr != m_moveSystem)
	{
		m_moveSystem->update(dt);
	}

	//Check if we can punch
	checkForPunch(dt);
	//Check if we must delete any punch sensors
	checkToDeletePunch(dt);
}

void Player::checkForPunch(double dt)
{
	if (m_timeTillPunch < m_punchRecharge)
	{
		m_timeTillPunch += dt;
	}
}

void Player::checkToDeletePunch(double dt)
{
	if (m_lpttl > 0)
	{
		m_lpttl -= dt;

		//If the punch time to live has reached 0 then delete the left attack sensor
		if (m_lpttl <= 0)
		{
			deletePunch("Left");
		}
	}
	if (m_rpttl > 0)
	{
		m_rpttl -= dt;

		//If the punch time to live has reached 0 then delete the right attack sensor
		if (m_rpttl <= 0)
		{
			deletePunch("Right");
		}
	}
}

void Player::draw(SDL_Renderer & renderer)
{
	m_rect.w = m_physComponent.m_body->getSize().x;
	m_rect.h = m_physComponent.m_body->getSize().y;
	m_rect.x = m_physComponent.m_body->getPosition().x - (m_rect.w / 2.0f);
	m_rect.y = m_physComponent.m_body->getPosition().y - (m_rect.h / 2.0f);

	SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(&renderer, &m_rect);

	m_rect.w = m_floorSensor.m_body->getSize().x;
	m_rect.h = m_floorSensor.m_body->getSize().y;
	m_rect.x = m_floorSensor.m_body->getPosition().x - (m_rect.w / 2.0f);
	m_rect.y = m_floorSensor.m_body->getPosition().y - (m_rect.h / 2.0f);

	SDL_SetRenderDrawColor(&renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(&renderer, &m_rect);

	//Attack sensors
	if (m_leftAttackSensor.m_body && m_leftAttackSensor.m_body->getBody())
	{
		m_rect.w = m_leftAttackSensor.m_body->getSize().x;
		m_rect.h = m_leftAttackSensor.m_body->getSize().y;
		m_rect.x = m_leftAttackSensor.m_body->getPosition().x - (m_rect.w / 2.0f);
		m_rect.y = m_leftAttackSensor.m_body->getPosition().y - (m_rect.h / 2.0f);

		SDL_SetRenderDrawColor(&renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(&renderer, &m_rect);
	}

	if (nullptr != m_rightAttackSensor.m_body&& m_rightAttackSensor.m_body->getBody())
	{
		m_rect.w = m_rightAttackSensor.m_body->getSize().x;
		m_rect.h = m_rightAttackSensor.m_body->getSize().y;
		m_rect.x = m_rightAttackSensor.m_body->getPosition().x - (m_rect.w / 2.0f);
		m_rect.y = m_rightAttackSensor.m_body->getPosition().y - (m_rect.h / 2.0f);

		SDL_SetRenderDrawColor(&renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(&renderer, &m_rect);
	}
}

void Player::handleInput(InputSystem& input)
{
	if (nullptr == m_moveSystem)
	{
		m_moveSystem = new MovementSystem(&input);
		m_moveSystem->addPlayer(this);
	}

	//Get the current velocity of the body
	m_currentVel = m_physComponent.m_body->getBody()->GetLinearVelocity();
	//m_currentVel.x = 0; //Reset the velocity on the X

	if(input.isButtonPressed("YBTN") || input.isButtonPressed("STICKUP"))
	{ 

		if (m_canJump)
		{
			m_jumpCMD.execute(*m_moveSystem);
		}
			
	}
	if (input.isButtonHeld("STICKRIGHT") || input.isButtonHeld("STICKDOWNRIGHT") || input.isButtonHeld("STICKUPRIGHT"))
	{
		m_moveRightCMD.execute(*m_moveSystem);
	}
	if (input.isButtonHeld("STICKLEFT") || input.isButtonHeld("STICKDOWNLEFT") || input.isButtonHeld("STICKUPLEFT"))
	{
		m_moveLeftCMD.execute(*m_moveSystem);
	}

	if (input.isButtonPressed("XBTN"))
	{
		punch();
	}

	if (input.isButtonPressed("STICKDOWN"))
	{
		//If we can fall, call our jump down command
		if (m_canFall)
		{
			m_jumpDwnCMD.execute(*m_moveSystem);
		}
	}

	//Set the velocity of the players body
	m_physComponent.m_body->getBody()->SetLinearVelocity(m_currentVel);
	m_floorSensor.m_body->getBody()->SetLinearVelocity(m_currentVel);
}

void Player::flipGravity()
{
	m_gravFlipped = !m_gravFlipped;
	m_sensorJointDef.localAnchorA.Set(m_sensorJoint->GetLocalAnchorA().x, -m_sensorJoint->GetLocalAnchorA().y);
	m_worldPtr->getWorld().DestroyJoint(m_sensorJoint);
	m_worldPtr->getWorld().CreateJoint(&m_sensorJointDef);
}

void Player::jump()
{
	m_currentVel.y -= m_gravFlipped ? -m_jumpSpeed : m_jumpSpeed;
}

void Player::jumpDown()
{
	//Set the player as falling
	m_falling = true;
	m_currentVel.y -= m_gravFlipped ? -m_jumpDownSpeed : m_jumpDownSpeed;
}

void Player::moveLeft()
{
	//Only move left if we arent punching
	if (m_lpttl <= 0 && m_rpttl <= 0 || !m_canJump)
	{
		m_currentVel.x =  -m_moveSpeed;
		m_movingL = true;
		m_movingR = false;
	}
}

void Player::moveRight()
{
	//Only move right if we arent punching or we are punching and falling
	if (m_lpttl <= 0 && m_rpttl <= 0 || !m_canJump)
	{
		m_currentVel.x = 0;
		m_currentVel.x = +m_moveSpeed;
		m_movingR = true;
		m_movingL = false;
	}
}

void Player::punch()
{
	if (m_timeTillPunch >= m_punchRecharge)
	{
		m_timeTillPunch = 0; //Reset the time till punch

		m_punched = true;

		//960, 540, X, Y
		if (m_movingL)
		{
			//If we already had a punch sensor active, delete it
			if(m_leftAttackSensor.m_body)
				m_worldPtr->deleteBody(m_leftAttackSensor.m_body);
			m_lpttl = m_punchRecharge;
			m_leftAttackSensor.m_body = m_worldPtr->createBox(m_physComponent.m_body->getPosition().x - 37.5f, m_physComponent.m_body->getPosition().y, 25, 50, false, false, b2BodyType::b2_dynamicBody);
			m_worldPtr->addProperties(*m_leftAttackSensor.m_body, 0, 0.1f, 0.0f, true, new PhysicsComponent::ColData("Attack Left", this));
			m_leftAttackSensor.m_body->getBody()->SetGravityScale(0);
		}
		else if (m_movingR)
		{
			//If we already had a punch sensor active, delete it
			if (m_rightAttackSensor.m_body)
				m_worldPtr->deleteBody(m_rightAttackSensor.m_body);
			m_rpttl = m_punchRecharge;
			m_rightAttackSensor.m_body = m_worldPtr->createBox(m_physComponent.m_body->getPosition().x + 37.5f, m_physComponent.m_body->getPosition().y, 25, 50, false, false, b2BodyType::b2_dynamicBody);
			m_worldPtr->addProperties(*m_rightAttackSensor.m_body, 0, 0.1f, 0.0f, true, new PhysicsComponent::ColData("Attack Right", this));
			m_rightAttackSensor.m_body->getBody()->SetGravityScale(0);
		}
	}
}

void Player::kick()
{
}

void Player::super()
{
}

void Player::damage(int percent)
{
	m_dmgPercent += percent;
	std::cout << m_dmgPercent << " Current damage percent\n";
}

void Player::applyDmgImpulse(float x)
{
	//Get the damage multiplier
	float dmgMultiplier = m_dmgPercent / 100.0f;
	auto impulse = Vector2f(x < 0 ? -1 : 1, m_gravFlipped ? 1 : -1);
	impulse = impulse.normalise() * ((impulse.x * x) * dmgMultiplier);

	m_physComponent.m_body->getBody()->ApplyLinearImpulse(b2Vec2(impulse.x, (impulse.y / 250)), m_physComponent.m_body->getBody()->GetWorldCenter(), true);
}

void Player::deletePunch(std::string whichArm)
{
	if (whichArm == "Left")
	{
		if(m_leftAttackSensor.m_body)
			m_worldPtr->deleteBody(m_leftAttackSensor.m_body);
		m_leftAttackSensor.m_body = nullptr;
	}
	else if(whichArm == "Right")
	{
		if (m_rightAttackSensor.m_body)
			m_worldPtr->deleteBody(m_rightAttackSensor.m_body);
		m_rightAttackSensor.m_body = nullptr;
	}
}

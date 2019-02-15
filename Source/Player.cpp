#include "Player.h"


Player::Player() :
	m_canJump(false),
	m_gravFlipped(false),
	m_canFall(false),
	m_falling(false),
	m_movingL(false),
	m_movingR(true),
	m_canPunch(true),
	m_punched(false),
	m_punchedDown(false),
	m_punchedUp(false),
	m_upperCut(false),
	m_canAttack(true),
	m_kicked(false),
	m_currentAttackSensor(nullptr),
	m_punchRecharge(.175f), //.175 seconds for a punch recharge
	m_kickRecharge(.4f), //.4 seconds for a kick recharge
	m_rpttl(0), //Right attack ttl
	m_lpttl(0), //Left attack ttl
	m_puttl(0), //Punch up ttl
	m_timeTillPunch(m_punchRecharge),
	m_timeTillKick(m_kickRecharge),
	m_moveSpeed(10),
	m_jumpSpeed(40.0f),
	m_jumpDownSpeed(-20.0f),
	m_posComponent(0,0),
	m_floorSensor(&m_posComponent),
	m_physComponent(&m_posComponent),
	m_leftAttackSensor(&m_posComponent),
	m_rightAttackSensor(&m_posComponent),
	m_upAttackSensor(&m_posComponent),
	m_upperCutSensor(&m_posComponent),
	m_downAttackSensor(&m_posComponent)
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
	m_upAttackSensor = PhysicsComponent(&m_posComponent);
	m_downAttackSensor = PhysicsComponent(&m_posComponent);
	m_upperCutSensor = PhysicsComponent(&m_posComponent);
	m_currentAttackSensor = nullptr;

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
	m_canJump = false;
	m_canFall = false;
	m_gravFlipped = false;
	//Reset facing booleans
	m_movingL = false;
	m_movingR = true;
	m_canPunch = true;
	m_punched = false;
	m_stunned = false;
	m_kicked = false;
	m_upperCut = false;
	m_punchedDown = false;
	m_punchedUp = false;
	m_timeTillKick = m_kickRecharge; //Reset our kick timer
	m_timeTillPunch = m_punchRecharge; //Reset our punch timer
}

void Player::update(double dt)
{

	//Check if we can punch
	checkForPunch(dt);
	//Check if we can kick
	checkForKick(dt);
	//Check if we must delete any punch sensors
	checkToDeleteAttack(dt);
	//Set the position fo the attacking body
	offsetAttackSensor();

	if (m_stunned)
	{
		m_stunLeft -= dt;

		if (m_stunLeft <= 0)
		{
			m_stunned = false;
		}
	}
}

void Player::offsetAttackSensor()
{
	//If attacked, set our attacking bodies position so it follows the player
	if (m_kicked || m_punched)
	{
		if (m_currentAttackSensor->m_body)
		{
			auto pPos = m_physComponent.m_body->getPosition();
			m_currentAttackSensor->m_body->setPosition(pPos.x + m_attackBoxOffset.x, pPos.y + m_attackBoxOffset.y);
		}
	}
}

void Player::checkForPunch(double dt)
{
	if (m_timeTillPunch < m_punchRecharge)
	{
		m_timeTillPunch += dt;
	}
}

void Player::checkForKick(double dt)
{
	if (m_timeTillKick < m_kickRecharge)
	{
		m_timeTillKick += dt;
	}
}

void Player::checkToDeleteAttack(double dt)
{
	if (m_lpttl > 0)
	{
		m_lpttl -= dt;

		//If the punch time to live has reached 0 then delete the left attack sensor
		if (m_lpttl <= 0)
		{
			deleteAttackBody();
		}
	}
	if (m_puttl > 0)
	{
		m_puttl -= dt;

		//If the punch time to live has reached 0 then delete the left attack sensor
		if (m_puttl <= 0)
		{
			deleteAttackBody();
		}
	}
	if (m_rpttl > 0)
	{
		m_rpttl -= dt;

		//If the punch time to live has reached 0 then delete the right attack sensor
		if (m_rpttl <= 0)
		{
			deleteAttackBody();
		}
	}
}

void Player::draw(SDL_Renderer & renderer)
{
	m_rect.w = m_physComponent.m_body->getSize().x;
	m_rect.h = m_physComponent.m_body->getSize().y;
	m_rect.x = m_physComponent.m_body->getPosition().x - (m_rect.w / 2.0f);
	m_rect.y = m_physComponent.m_body->getPosition().y - (m_rect.h / 2.0f);

	//Draw the player as yellow if they are stunned
	if(m_stunned)
		SDL_SetRenderDrawColor(&renderer, 255, 255, 0, 255);
	else
		SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);

	SDL_RenderFillRect(&renderer, &m_rect);

	m_rect.w = m_floorSensor.m_body->getSize().x;
	m_rect.h = m_floorSensor.m_body->getSize().y;
	m_rect.x = m_floorSensor.m_body->getPosition().x - (m_rect.w / 2.0f);
	m_rect.y = m_floorSensor.m_body->getPosition().y - (m_rect.h / 2.0f);

	SDL_SetRenderDrawColor(&renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(&renderer, &m_rect);

	//Attack sensor, draw the current attack sensor
	if (nullptr != m_currentAttackSensor && m_currentAttackSensor->m_body && m_currentAttackSensor->m_body->getBody())
	{
		m_rect.w = m_currentAttackSensor->m_body->getSize().x;
		m_rect.h = m_currentAttackSensor->m_body->getSize().y;
		m_rect.x = m_currentAttackSensor->m_body->getPosition().x - (m_rect.w / 2.0f);
		m_rect.y = m_currentAttackSensor->m_body->getPosition().y - (m_rect.h / 2.0f);

		SDL_SetRenderDrawColor(&renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(&renderer, &m_rect);
	}
}

void Player::handleInput(InputSystem& input)
{
	//Get the current velocity of the body
	m_currentVel = m_physComponent.m_body->getBody()->GetLinearVelocity();

	m_desiredVel.x = 0;

	//Only handle input if the playe ris not stunned
	if (m_stunned == false)
	{

		//if (input.isButtonPressed("YBTN"))
		//{
		//	if (m_canJump)
		//	{
		//		m_jumpCMD.execute(*m_moveSystem);
		//	}
		//}
		//if (input.isButtonHeld("STICKRIGHT") || input.isButtonHeld("STICKDOWNRIGHT") || input.isButtonHeld("STICKUPRIGHT"))
		//{
		//	m_moveRightCMD.execute(*m_moveSystem);
		//}
		//if (input.isButtonHeld("STICKLEFT") || input.isButtonHeld("STICKDOWNLEFT") || input.isButtonHeld("STICKUPLEFT"))
		//{
		//	m_moveLeftCMD.execute(*m_moveSystem);
		//}
		////Upercut
		//if (input.isButtonHeld("STICKUP") && input.isButtonPressed("XBTN"))
		//{
		//	//if on the ground upercut an enemy
		//	if (m_canJump)
		//		upperCut();
		//	else //If in air punch above you
		//		punchUp();
		//}

		//else if (input.isButtonPressed("XBTN"))
		//{
		//	punch();
		//}
		//if (input.isButtonPressed("ABTN"))
		//{
		//	kick();
		//}

		//if (input.isButtonPressed("STICKDOWN"))
		//{
		//	//If we can fall, call our jump down command
		//	if (m_canFall)
		//	{
		//		m_jumpDwnCMD.execute(*m_moveSystem);
		//	}
		//}
	}

	if (m_desiredVel.x == 0)
		m_currentVel.x *= .98f;

	//Set the velocity of the players body
	m_physComponent.m_body->getBody()->SetLinearVelocity(m_currentVel);

	//Online
	/*if (is_online && buttonPressed)
	{
		//m_client->SerializeInputs(input);
		//m_client->Send();
	}*/
}

void Player::addClient()
{
	/*m_client = new OnlineSendComponent();
	m_client->ConnectToServer();
	is_online = true;*/

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
	m_currentVel.y = 0;
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
	//Only move left if we arent punching or kicking
	if (m_lpttl <= 0 && m_rpttl <= 0 || !m_canJump)
	{
		m_desiredVel.x = -1;
		m_currentVel.x -= 0.4f;

		m_currentVel.x = m_currentVel.x < -m_moveSpeed ? -m_moveSpeed : m_currentVel.x;
		m_movingL = true;
		m_movingR = false;
	}
}

void Player::moveRight()
{
	//Only move right if we arent punching or we are punching and falling
	if (m_lpttl <= 0 && m_rpttl <= 0 || !m_canJump)
	{
		m_desiredVel.x = 1;
		m_currentVel.x += 0.4f;

		m_currentVel.x = m_currentVel.x > m_moveSpeed ? m_moveSpeed : m_currentVel.x;
		m_movingR = true;
		m_movingL = false;
	}
}

void Player::punch()
{
	if (m_timeTillPunch >= m_punchRecharge && m_canAttack)
	{
		m_punched = true;
		m_timeTillPunch = 0;

		//assign our time till punch
		m_lpttl = m_movingL ? m_punchRecharge : m_lpttl;
		m_rpttl = m_movingR ? m_punchRecharge : m_rpttl;

		auto tag = m_movingL ? "Attack Left" : "Attack Right";
		//Set the offset for the attack box so we can position it correctly
		m_attackBoxOffset = Vector2f(m_movingL ? -40 : 40, !m_gravFlipped ? -12.5f : 12.5f);

		//Cretae an attack sensor using the values passed over
		attack(tag, m_movingL ? m_leftAttackSensor : m_rightAttackSensor, 30, 25);
	}
}

void Player::kick()
{
	if (m_timeTillKick >= m_kickRecharge && m_canAttack)
	{
		m_kicked = true;
		m_timeTillKick = 0;

		m_lpttl = m_movingL ? m_punchRecharge : m_lpttl;
		m_rpttl = m_movingR ? m_punchRecharge : m_rpttl;

		auto tag = m_movingL ? "Attack Left" : "Attack Right";
		//Set the offset for the attack box so we can position it correctly
		m_attackBoxOffset = Vector2f(m_movingL ? -50 : 50, !m_gravFlipped ? 12.5f : -12.5f);

		//Cretae an attack sensor using the values passed over
		attack(tag, m_movingL ? m_leftAttackSensor : m_rightAttackSensor, 50, 25);
	}
}

void Player::punchUp()
{
	if (m_timeTillPunch >= m_punchRecharge && m_canAttack)
	{
		m_punchedUp = true;
		m_punched = true;
		m_puttl = m_punchRecharge;

		m_attackBoxOffset = Vector2f(0, !m_gravFlipped ? -35.0f : 35.0f);

		attack("Punch Up", m_upAttackSensor, 35, 20);
	}
}

void Player::punchDown()
{
}

void Player::upperCut()
{
	if (m_timeTillPunch >= m_punchRecharge && m_canAttack)
	{
		m_punched = true;
		m_upperCut = true;
		m_puttl = m_punchRecharge;

		m_attackBoxOffset = Vector2f(m_movingL ? -37.5f : 37.5f, 0);

		attack(m_movingL ? "UpperCut Left" : "UpperCut Right", m_movingL ? m_leftAttackSensor : m_rightAttackSensor, 25, 45);
	}
}

void Player::stun()
{
	//Set stunned to true
	m_stunned = true;

	//get the multiplier for a stun
	float stunMultiplier = m_dmgPercent / 100.0f;

	//Multiply our stun left by our stun multiplier
	m_stunLeft = .2f * stunMultiplier;	
}

void Player::super()
{
}

void Player::damage(int percent)
{
	m_dmgPercent += percent;
	std::cout << m_dmgPercent << " Current damage percent\n";
}

void Player::applyDmgImpulse(float x, float y)
{
	auto imp = Vector2f(x, y);
	//Get the damage multiplier
	float dmgMultiplier = m_dmgPercent / 100.0f;
	auto impulse = Vector2f(x < 0 ? -1 : 1, m_gravFlipped ? .75f : -.75f);
	impulse = impulse.normalise() * ((impulse * imp) * dmgMultiplier);

	//Apply knockback
	m_physComponent.m_body->getBody()->ApplyLinearImpulse(b2Vec2(impulse.x, -impulse.y), m_physComponent.m_body->getBody()->GetWorldCenter(), true);
}

void Player::deleteAttackBody()
{
	m_kicked = false;
	m_punched = false;
	m_punchedDown = false;
	m_punchedUp = false;
	m_canAttack = true;

	//Delete sthe current attack sensor thats active
	if (nullptr != m_currentAttackSensor && m_currentAttackSensor->m_body)
	{
		m_worldPtr->deleteBody(m_currentAttackSensor->m_body);
		m_currentAttackSensor->m_body = nullptr; //Set the attack sensor body to nullptr
	}
}

void Player::attack(std::string tag, PhysicsComponent& sensor, int sizeX, int sizeY)
{
	m_canAttack = false;

	//If the sensor is already active, delete it
	if (sensor.m_body)
		m_worldPtr->deleteBody(sensor.m_body);

	//Set the position of the attacking body
	sensor.m_body = m_worldPtr->createBox(m_physComponent.m_body->getPosition().x + m_attackBoxOffset.x, m_physComponent.m_body->getPosition().y + m_attackBoxOffset.y, sizeX, sizeY, false, false, b2BodyType::b2_dynamicBody);
	//Add properties to the body and set the user data with the passed over tag
	m_worldPtr->addProperties(*sensor.m_body, 0, 0.1f, 0.0f, true, new PhysicsComponent::ColData(tag, this));
	//Set gravity scale to 0 as we want to set the position of the attack sensor manually
	sensor.m_body->getBody()->SetGravityScale(0);
	//Assign the pointer for the new attack sensor that is active
	m_currentAttackSensor = &sensor;
}

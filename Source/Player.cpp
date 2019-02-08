#include "Player.h"


Player::Player() :
	m_canJump(false),
	m_gravFlipped(false),
	m_moveSystem(nullptr),
	m_moveSpeed(10),
	m_jumpSpeed(25),
	m_posComponent(0,0),
	m_floorSensor(&m_posComponent),
	m_physComponent(&m_posComponent)
{


}

void Player::createPlayer(Box2DBridge& world, PhysicsSystem& system)
{
	m_worldPtr = &world; //Ste the world pointer
	physPtr = &system;

	m_floorSensor = PhysicsComponent(&m_posComponent);
	m_physComponent = PhysicsComponent(&m_posComponent);

	m_physComponent.m_body = world.createBox(960, 540, 50, 50, false, false, b2BodyType::b2_dynamicBody);
	m_floorSensor.m_body = world.createBox(960, 565, 50, 5, false, false, b2BodyType::b2_dynamicBody);

	world.addProperties(*m_physComponent.m_body, 1, 0.1f, 0.0f, false, this);
	world.addProperties(*m_floorSensor.m_body, 1, 0.1f, 0.0f, true, this);

	m_physComponent.m_body->getBody().SetGravityScale(2.0f);

	m_sensorJointDef.bodyA = &m_physComponent.m_body->getBody();
	m_sensorJointDef.bodyB = &m_floorSensor.m_body->getBody();
	m_sensorJointDef.collideConnected = false;
	m_sensorJointDef.localAnchorA.Set(0, .9f);
	

	m_sensorJoint = (b2RevoluteJoint*)world.getWorld().CreateJoint(&m_sensorJointDef);
}


void Player::deletePlayer()
{
	delete m_moveSystem;
	m_moveSystem = nullptr;
}

void Player::update(double dt)
{
	if (nullptr != m_moveSystem)
	{
		m_moveSystem->update(dt);
	}
}

void Player::draw(SDL_Renderer & renderer)
{
	m_player.w = m_physComponent.m_body->getSize().x;
	m_player.h = m_physComponent.m_body->getSize().y;
	m_player.x = m_physComponent.m_body->getPosition().x - (m_player.w / 2.0f);
	m_player.y = m_physComponent.m_body->getPosition().y - (m_player.h / 2.0f);

	SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(&renderer, &m_player);

	m_player.w = m_floorSensor.m_body->getSize().x;
	m_player.h = m_floorSensor.m_body->getSize().y;
	m_player.x = m_floorSensor.m_body->getPosition().x - (m_player.w / 2.0f);
	m_player.y = m_floorSensor.m_body->getPosition().y - (m_player.h / 2.0f);

	SDL_SetRenderDrawColor(&renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(&renderer, &m_player);
}

void Player::handleInput(InputSystem& input)
{
	if (nullptr == m_moveSystem)
	{
		m_moveSystem = new MovementSystem(&input);
		m_moveSystem->addPlayer(this);
	}

	//Get the current velocity of the body
	m_currentVel = m_physComponent.m_body->getBody().GetLinearVelocity();
	m_currentVel.x = 0; //Reset the velocity on the X

	if(input.isButtonPressed("YBTN") || input.isButtonPressed("STICKUP"))
	{ 

		if (m_canJump)
		{
			m_jumpCMD.execute(*m_moveSystem);
			input.applyRumble(0.75, 1000);
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

	//Set the velocity of the players body
	m_physComponent.m_body->getBody().SetLinearVelocity(m_currentVel);
	m_floorSensor.m_body->getBody().SetLinearVelocity(m_currentVel);
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

void Player::moveLeft()
{
	m_currentVel.x = -m_moveSpeed;
}

void Player::moveRight()
{
	m_currentVel.x = +m_moveSpeed;
}

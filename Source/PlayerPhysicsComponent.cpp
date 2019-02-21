#include "PlayerPhysicsComponent.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(Component * pos) :
	m_body(nullptr),
	m_jumpSensor(nullptr),
	m_stunned(false),
	m_canFall(false),
	m_canJump(false),
	m_movingL(true),
	m_movingR(false),
	m_gravFlipped(false),
	m_falling(false),
	m_stunLeft(0),
	m_jumpSpeed(40.0f),
	m_jumpDownSpeed(20.0f),
	m_moveSpeed(10),
	m_dmgPercentage(0)
{
	posPtr = static_cast<PositionComponent*>(pos);
}

void PlayerPhysicsComponent::stun()
{
	//Set stunned to true
	m_stunned = true;

	//get the multiplier for a stun
	float stunMultiplier = m_dmgPercentage / 100.0f;

	//Multiply our stun left by our stun multiplier
	m_stunLeft = .3f * stunMultiplier;
}

void PlayerPhysicsComponent::jump()
{
	m_desiredVel.y = -1;
}

void PlayerPhysicsComponent::jumpDown()
{
	m_desiredVel.y = 1;
	//Set the body as falling
	m_falling = true;
}

void PlayerPhysicsComponent::moveLeft()
{
	m_desiredVel.x = -1;
	m_movingL = true;
	m_movingR = false;
}

void PlayerPhysicsComponent::moveRight()
{
	m_desiredVel.x = 1;
	m_movingR = true;
	m_movingL = false;
}

void PlayerPhysicsComponent::applyDamageImpulse(float x, float y)
{
	auto imp = Vector2f(x, y);
	//Get the damage multiplier
	float dmgMultiplier = m_dmgPercentage / 100.0f;
	auto impulse = Vector2f(x < 0 ? -1 : 1, .75f);
	impulse = impulse.normalise() * ((impulse * imp) * dmgMultiplier);

	//Apply knockback
	m_body->getBody()->ApplyLinearImpulse(b2Vec2(impulse.x, -impulse.y), m_body->getBody()->GetWorldCenter(), true);
}

void PlayerPhysicsComponent::flipGravity()
{
	m_gravFlipped = !m_gravFlipped;
}

void PlayerPhysicsComponent::createJoint(Box2DBridge & world)
{
	//Define the sensor
	m_sensorJointDef.bodyA = m_body->getBody();
	m_sensorJointDef.bodyB = m_jumpSensor->getBody();
	m_sensorJointDef.collideConnected = false;
	m_sensorJointDef.localAnchorA.Set(0, 1.35f);

	//Create the joints
	m_sensorJoint = (b2RevoluteJoint*)world.getWorld().CreateJoint(&m_sensorJointDef);
}

float PlayerPhysicsComponent::clamp(float min, float & val, float max)
{
	val < min ? val = min : val;
	val > max ? val = max : val;

	return val;
}

void PlayerPhysicsComponent::move(int direction)
{
	m_currentVel.x += 0.4f * direction;

	m_currentVel.x = clamp(-m_moveSpeed, m_currentVel.x, m_moveSpeed);
}

void PlayerPhysicsComponent::moveUp()
{
	m_currentVel.y = 0;
	m_currentVel.y -= m_gravFlipped ? -m_jumpSpeed : m_jumpSpeed;
}

void PlayerPhysicsComponent::moveDown()
{
	m_currentVel.y = 0;
	m_currentVel.y -= m_gravFlipped ? m_jumpDownSpeed : -m_jumpDownSpeed;
	m_falling = true;
}

#pragma once
#include "Box2DBridge.h"
#include "PositionComponent.h"

class PlayerPhysicsComponent : public Component
{
public:
	PlayerPhysicsComponent(Component* pos);

	//methods for modifying the player
	void stun();
	void jump();
	void jumpDown();
	void moveLeft();
	void moveRight();
	void move(int direction);
	void moveUp(int direction);
	void damage(int dmg) { m_dmgPercentage += dmg; };
	void applyDamageImpulse(float x, float y);
	void flipGravity();
	void createJoint(Box2DBridge& world);

	//Getter methods
	bool& stunned() { return m_stunned; };
	bool& canJump() { return m_canJump; }
	bool& canFall() { return m_canFall; }
	bool& falling() { return m_falling; }
	bool& isGravityFlipped() { return m_gravFlipped; }
	bool& isMovingLeft() { return m_movingL; }
	bool& isMovingRight() { return m_movingR; }
	float& stunLeft() { return m_stunLeft; }

	//Setters
	void setCanFall(bool b) { m_canFall = b; }
	void setCanJump(bool b) { m_canJump = b; }

	//---Member variables---//
	//The body of the physics component
	Box2DBody* m_body;
	Box2DBody* m_jumpSensor;
	//Hold a ptr to the position component that the physics modifies
	PositionComponent * posPtr;
	b2Vec2 m_currentVel, m_desiredVel;
private:
	float clamp(float min, float& val, float max);
	b2RevoluteJointDef m_sensorJointDef;
	b2RevoluteJoint * m_sensorJoint;
	bool m_falling, m_stunned, m_canJump, m_canFall, m_movingL, m_movingR, m_gravFlipped;
	float m_stunLeft, m_moveSpeed, m_jumpDownSpeed, m_jumpSpeed;
	int m_dmgPercentage;
};
#ifndef PLAYER_H
#define PLAYER_H

#include "Box2DBridge.h"
#include "PhysicsSystem.h"
#include "MovementSystem.h"
#include "CommandPattern.h"
#include "SDL.h"

class Player {

public:
	Player();

	void createPlayer(Box2DBridge& world, PhysicsSystem& system);
	void deletePlayer();
	void update(double dt);
	void checkForPunch(double dt);
	void checkToDeletePunch(double dt);
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);

	void flipGravity();
	void jump();
	void jumpDown();
	void moveLeft();
	void moveRight();
	void punch();
	void kick();
	void super();
	void damage(int percent);
	void applyDmgImpulse(float x);
	void deletePunch(std::string whichArm);

	void setCanJump(bool b) { m_canJump = b; }
	void setCanFall(bool b) { m_canFall = b; }
	bool& falling() { return m_falling; }
	bool& punched() { return m_punched; } //Return wheter punched or not
private:
	int m_dmgPercent;
	b2Vec2 m_currentVel;
	float m_moveSpeed;
	float m_jumpSpeed, m_jumpDownSpeed;
	bool m_canJump, m_gravFlipped, m_movingL, m_movingR;
	SDL_Rect m_rect;

	PhysicsSystem* m_physPtr;
	PhysicsComponent m_physComponent, m_floorSensor;
	PositionComponent m_posComponent;
	MovementSystem* m_moveSystem;

	//Attacking variables
	PhysicsComponent m_leftAttackSensor, m_rightAttackSensor;

	MoveLeftCommand m_moveLeftCMD;
	MoveRightCommand m_moveRightCMD;
	JumpCommand m_jumpCMD;
	JumpDownCommand m_jumpDwnCMD;

	Box2DBridge* m_worldPtr;

	b2RevoluteJoint * m_sensorJoint, *m_attackLeftJoint, *m_attackRightJoint;
	b2RevoluteJointDef m_sensorJointDef, m_attackLeftJointDef, m_attackRightJointDef;

	//Attack variables
	float m_punchRecharge, m_timeTillPunch, m_lpttl, m_rpttl;
	bool m_canPunch, m_punched;

	//Bools to determine if the player can flick down on the joycon stick
	bool m_canFall, m_falling;
};

#endif

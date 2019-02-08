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
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);

	void flipGravity();
	void jump();
	void moveLeft();
	void moveRight();

	void setCanJump(bool b) { m_canJump = b; };
private:
	b2Vec2 m_currentVel;
	float m_moveSpeed;
	float m_jumpSpeed;
	bool m_canJump, m_gravFlipped;
	SDL_Rect m_player;

	PhysicsSystem* physPtr;
	PhysicsComponent m_physComponent, m_floorSensor;
	PositionComponent m_posComponent;
	MovementSystem* m_moveSystem;

	MoveLeftCommand m_moveLeftCMD;
	MoveRightCommand m_moveRightCMD;
	JumpCommand m_jumpCMD;

	Box2DBridge* m_worldPtr;

	b2RevoluteJoint * m_sensorJoint;
	b2RevoluteJointDef m_sensorJointDef;
};

#endif

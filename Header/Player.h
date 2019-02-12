#ifndef PLAYER_H
#define PLAYER_H

#include "Box2DBridge.h"
#include "PhysicsSystem.h"
#include "MovementSystem.h"
#include "CommandPattern.h"
#include "OnlineSendComponent.h"
#include "SDL.h"

class Player {

public:
	Player();

	void createPlayer(Box2DBridge& world, PhysicsSystem& system);
	void deletePlayer();
	void update(double dt);
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);

	void addClient();

	void flipGravity();
	void jump();
	void jumpDown();
	void moveLeft();
	void moveRight();

	void setCanJump(bool b) { m_canJump = b; }
	void setCanFall(bool b) { m_canFall = b; }
	bool& falling() { return m_falling; }
private:
	b2Vec2 m_currentVel;
	float m_moveSpeed;
	float m_jumpSpeed, m_jumpDownSpeed;
	bool m_canJump, m_gravFlipped;
	SDL_Rect m_player;

	OnlineSendComponent* m_client;
	bool is_online = false;

	PhysicsSystem* physPtr;
	PhysicsComponent m_physComponent, m_floorSensor;
	PositionComponent m_posComponent;
	MovementSystem* m_moveSystem;

	MoveLeftCommand m_moveLeftCMD;
	MoveRightCommand m_moveRightCMD;
	JumpCommand m_jumpCMD;
	JumpDownCommand m_jumpDwnCMD;

	Box2DBridge* m_worldPtr;

	b2RevoluteJoint * m_sensorJoint;
	b2RevoluteJointDef m_sensorJointDef;

	//Bools to determine if the player can flick down on the joycon stick
	bool m_canFall, m_falling;
};

#endif

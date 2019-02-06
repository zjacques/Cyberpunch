#pragma once
#include <Box2D/Box2D.h> //Include Box2D
#include "Vector2f.h"

//Class for box 2d body, makes it easier to manage the bodies and avoids the conversions
class Box2DBody
{
public:
	void setBody(b2Body* body) { m_body = body; };
	
	b2Body& getBody() { return *m_body; }

	Vector2f getPosition();
	float getAngle();
private:
	b2Body * m_body;
	Vector2f m_position;

	const float CONVERSION = 30.0f; //Pixels to world and backwords, we multiply or divide by 30
};

//Bridge class to allow for easy manipulation of the Box2d API
class Box2DBridge
{
public:
	Box2DBridge();

	void update(double dt);

	//Creates and returns a box2d body, we can create circles and squares
	Box2DBody* createBox(int posX, int posY, int width, int height, bool canRotate, b2BodyType type);
	Box2DBody* createCircle(int posX, int posY, float radius, bool canRotate, b2BodyType type);

	//Allows to modify the mass, friction and sensor boolean on a body
	void addProperties(Box2DBody& body, float mass, float friction, bool isSensor, void* data);

private:
	b2World* m_world; //Create this to handle physics simulation
	const int32 VELOCITY_ITERS = 8; //how strongly to correct velocity
	const int32 POSITION_ITERS = 3; //how strongly to correct position
	const float CONVERSION = 30.0f; //Pixels to world and backwords, we multiply or divide by 30
	const b2Vec2 GRAVITY = b2Vec2(0, 10 * CONVERSION); //Const gravity
};
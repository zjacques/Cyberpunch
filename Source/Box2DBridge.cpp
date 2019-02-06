#include "Box2DBridge.h"

Box2DBridge::Box2DBridge()
{
}

void Box2DBridge::initWorld()
{
	m_world = new b2World(GRAVITY); //Create the world
	m_world->SetGravity(GRAVITY); //Set the gravity of the world
}

void Box2DBridge::update(double dt)
{
	//If there are bodies to delete, delete them
	if (!m_bodiesToDelete.empty())
	{
		for (auto& body : m_bodiesToDelete)
		{
			m_world->DestroyBody(&body->getBody());
		}
		m_bodiesToDelete.clear();
	}

	//Simulate the physics bodies
	m_world->Step(dt, VELOCITY_ITERS, POSITION_ITERS);
}

void Box2DBridge::deleteBody(Box2DBody * body)
{
	m_bodiesToDelete.push_back(body);
}

void Box2DBridge::deleteWorld()
{
	delete m_world;
}

Box2DBody* Box2DBridge::createBox(int posX, int posY, int width, int height, bool canRotate, b2BodyType type)
{
	Box2DBody* body =  new Box2DBody();
	b2BodyDef bDef;
	b2FixtureDef fDef;
	b2PolygonShape box;

	//Set the body type and its position
	bDef.type = type;
	bDef.fixedRotation = canRotate;
	box.SetAsBox(width, height);
	bDef.position.Set(posX, posY);

	fDef.shape = &box;

	//Create the body and set it for our box2D body wrapper
	body->setBody(m_world->CreateBody(&bDef));

	body->getBody().CreateFixture(&fDef);
	return body; //Return the body
}

Box2DBody* Box2DBridge::createCircle(int posX, int posY, float radius, bool canRotate, b2BodyType type)
{
	Box2DBody* body = new Box2DBody();
	b2BodyDef bDef;
	b2CircleShape circle;

	//Set the body type and its position
	bDef.type = type;
	bDef.fixedRotation = canRotate;
	circle.m_p.Set(posX, posY);
	circle.m_radius = radius;
	bDef.position.Set(posX, posY);

	body->setBody(m_world->CreateBody(&bDef));
	return body; //Return the body
}

void Box2DBridge::addProperties(Box2DBody & body, float mass, float friction, bool isSensor, void* data)
{
	//Get a pointer to the fixture fo the body
	b2Fixture* fDef = body.getBody().GetFixtureList();
	fDef->SetSensor(isSensor); //Set wheter the body is a sensor (doesnt tak epart of regular physics)
	fDef->SetDensity(mass); //Set the density/mass of the body
	fDef->SetFriction(friction); //Set friction of the body
	fDef->SetUserData(data); //Set the user data
}

//Box2DBody methods
Vector2f Box2DBody::getPosition()
{
	//Get the shape of the body
	auto shape = m_body->GetFixtureList()->GetAABB(0);
	m_position.x = m_body->GetPosition().x - (shape.GetExtents().x / 2.0f);
	m_position.y = m_body->GetPosition().y - (shape.GetExtents().y / 2.0f);

	//Return our position
	return m_position;
}

Vector2f Box2DBody::getSize()
{
	auto shape = m_body->GetFixtureList()->GetAABB(0);
	return Vector2f(shape.GetExtents().x, shape.GetExtents().y);
}


float Box2DBody::getAngle()
{
	return 0.0f;
}

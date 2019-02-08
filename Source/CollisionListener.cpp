#include "CollisionListener.h"
#include "Player.h"

void CollisionListener::BeginContact(b2Contact * contact)
{
	auto pPtr = static_cast<Player*>(contact->GetFixtureA()->GetUserData());

	if (nullptr != pPtr)
	{
		pPtr->setCanJump(true);
	}
}

void CollisionListener::EndContact(b2Contact * contact)
{
	auto pPtr = static_cast<Player*>(contact->GetFixtureA()->GetUserData());

	if (nullptr != pPtr)
	{
		pPtr->setCanJump(false);
	}
}

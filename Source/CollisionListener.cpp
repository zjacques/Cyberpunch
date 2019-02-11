#include "CollisionListener.h"
#include "Player.h"
#include "Platform.h"

void CollisionListener::BeginContact(b2Contact * contact)
{
	//Convert both contact points to a ColData struct, from here we can check what tthe bodies are tagged with
	auto dataA = static_cast<PhysicsComponent::ColData *>(contact->GetFixtureA()->GetUserData());
	auto dataB = static_cast<PhysicsComponent::ColData *>(contact->GetFixtureB()->GetUserData());

	//If the players jump sensor has hit a platform, set the player to be able to jump
	if ((dataA->Tag() == "Jump Sensor" && dataB->Tag() == "Platform")
	|| (dataB->Tag() == "Jump Sensor" && dataA->Tag() == "Platform")
	|| (dataA->Tag() == "Jump Sensor" && dataB->Tag() == "Floor")
	|| (dataB->Tag() == "Jump Sensor" && dataA->Tag() == "Floor"))
	{
		//Convert the collision data to a player pointer and call the allow jump method
		auto player = static_cast<Player*>(dataA->Tag() == "Jump Sensor" ? dataA->Data() : dataB->Data());

		//If the player has hit a platform, set his can fall boolean
		if (dataA->Tag() == "Platform" || dataB->Tag() == "Platform")
		{
			player->setCanFall(true);
		}
		player->setCanJump(true);
	}

	//Check if a player has attacked another player
	checkPlayerAttack(contact);
}

void CollisionListener::EndContact(b2Contact * contact)
{
	//Convert both contact points to a ColData struct, from here we can check what tthe bodies are tagged with
	auto dataA = static_cast<PhysicsComponent::ColData *>(contact->GetFixtureA()->GetUserData());
	auto dataB = static_cast<PhysicsComponent::ColData *>(contact->GetFixtureB()->GetUserData());

	//If the players jump sensor has stopped hitting a platform, set the player to be able to jump
	if ((dataA->Tag() == "Jump Sensor" && dataB->Tag() == "Platform")
		|| (dataB->Tag() == "Jump Sensor" && dataA->Tag() == "Platform")
		|| (dataA->Tag() == "Jump Sensor" && dataB->Tag() == "Floor")
		|| (dataB->Tag() == "Jump Sensor" && dataA->Tag() == "Floor"))
	{
		//Convert the collision data to a player pointer and call the allow jump method
		auto player = static_cast<Player*>(dataA->Tag() == "Jump Sensor" ? dataA->Data() : dataB->Data());
		player->setCanJump(false);
		player->setCanFall(false);
	}

	//if a players body has hit a platform
	if ((dataA->Tag() == "Player Body" && dataB->Tag() == "Platform")
		|| (dataB->Tag() == "Player Body" && dataA->Tag() == "Platform"))
	{
		//Convert the collision data to a player pointer and call the allow jump method
		auto player = dataA->Tag() == "Player Body" ? contact->GetFixtureA() : contact->GetFixtureB();
		auto platform = dataA->Tag() == "Platform" ? contact->GetFixtureA() : contact->GetFixtureB();

		auto pHeight = player->GetBody()->GetFixtureList()->GetAABB(0).GetExtents().y; //get height of the player

		//Convert the collision data to a player pointer and call the allow jump method
		auto pPtr = static_cast<Player*>(dataA->Tag() == "Player Body" ? dataA->Data() : dataB->Data());

		//If the player is jumping up from below a platform, set it sensor to true
		if ((!m_gravFlipped && player->GetBody()->GetPosition().y + pHeight < platform->GetBody()->GetPosition().y)
			|| (m_gravFlipped && player->GetBody()->GetPosition().y - pHeight > platform->GetBody()->GetPosition().y))
		{
			//Set contact as disabled so the player can move through floors
			pPtr->falling() = false;;
		}
	}
}

void CollisionListener::checkPlayerAttack(b2Contact * contact)
{
	auto dataA = static_cast<PhysicsComponent::ColData *>(contact->GetFixtureA()->GetUserData());
	auto dataB = static_cast<PhysicsComponent::ColData *>(contact->GetFixtureB()->GetUserData());

	//If a player has attacked left and hit a player
	if ((dataA->Tag() == "Attack Left" && dataB->Tag() == "Player Body")
	|| (dataB->Tag() == "Attack Left" && dataA->Tag() == "Player Body"))
	{
		//get our player pointers
		auto attackingP = static_cast<Player*>(dataA->Tag() == "Attack Left" ? dataA->Data() : dataB->Data());
		auto otherP = static_cast<Player*>(dataA->Tag() == "Player Body" ? dataA->Data() : dataB->Data());

		if (attackingP == otherP)
			return;

		//If the attacking player punched
		if (attackingP->punched() || attackingP->kicked())
		{
			auto dmgP = attackingP->punched() ? 2 : 5;
			auto impulse = dmgP == 2 ? -250 : -300;

			otherP->damage(dmgP); //Add damage of the punch to the other players damage percentage
			otherP->applyDmgImpulse(impulse); //Knock back the other player
			otherP->stun();

			attackingP->punched() = false; //Set punched as false
			attackingP->deletePunch("Left");
		}
	}
	//If a player has attacked right and hit a player
	else if ((dataA->Tag() == "Attack Right" && dataB->Tag() == "Player Body")
	|| (dataB->Tag() == "Attack Right" && dataA->Tag() == "Player Body"))
	{
		//get our player pointers
		auto attackingP = static_cast<Player*>(dataA->Tag() == "Attack Right" ? dataA->Data() : dataB->Data());
		auto otherP = static_cast<Player*>(dataA->Tag() == "Player Body" ? dataA->Data() : dataB->Data());

		if (attackingP == otherP)
			return;

		//If the attacking player punched
		if (attackingP->punched() || attackingP->kicked())
		{
			auto dmgP = attackingP->punched() ? 2 : 5;
			auto impulse = dmgP == 2 ? 250 : 300;

			otherP->damage(dmgP); //Add damage of the punch to the other players damage percentage
			otherP->applyDmgImpulse(impulse); //Knock back the other player back
			otherP->stun();

			attackingP->punched() = false; //Set punched as false
			attackingP->deletePunch("Right");
		}
	}
}

void CollisionListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
	//Convert both contact points to a ColData struct, from here we can check what tthe bodies are tagged with
	auto dataA = static_cast<PhysicsComponent::ColData *>(contact->GetFixtureA()->GetUserData());
	auto dataB = static_cast<PhysicsComponent::ColData *>(contact->GetFixtureB()->GetUserData());
	
	//if a players body has hit a platform
	if ((dataA->Tag() == "Player Body" && dataB->Tag() == "Platform")
		|| (dataB->Tag() == "Player Body" && dataA->Tag() == "Platform"))
	{
		//Convert the collision data to a player pointer and call the allow jump method
		auto player = dataA->Tag() == "Player Body" ? contact->GetFixtureA() : contact->GetFixtureB();
		auto platform = dataA->Tag() == "Platform" ? contact->GetFixtureA() : contact->GetFixtureB();

		auto pHeight = player->GetBody()->GetFixtureList()->GetAABB(0).GetExtents().y; //get height of the player

		//Convert the collision data to a player pointer and call the allow jump method
		auto pPtr = static_cast<Player*>(dataA->Tag() == "Player Body" ? dataA->Data() : dataB->Data());

		//If the player is jumping up from below a platform, set it sensor to true
		if ((!m_gravFlipped && player->GetBody()->GetPosition().y + pHeight > platform->GetBody()->GetPosition().y)
			|| (m_gravFlipped && player->GetBody()->GetPosition().y - pHeight < platform->GetBody()->GetPosition().y)
			|| (pPtr->falling()))
		{
			//Set contact as disabled so the player can move through floors
			contact->SetEnabled(false);
		}
	}
}

void CollisionListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{

}

void CollisionListener::flipGravity()
{
	m_gravFlipped = !m_gravFlipped;
}


#include "Observer.h"
#include "AchievementComponent.h"
#include "PlayerComponent.h"

void AchievementsListener::onNotify(Entity * ent, Event event)
{
	//Switch case on the event
	switch (event)
	{
	case DAMAGE_TAKEN:
		//If the player has taken 1000 damage, unlock the achievement for it
		if (static_cast<PlayerComponent*>(&ent->getComponent("Player"))->m_dmgTaken >= 1000)
		{
			static_cast<AchievementComponent*>(achi::Listener::m_AchisPtr)->unlockAchievement("Punching Bag");
		}
		break;
	case DAMAGE_DEALT:
		//If the player has dealt 1000 damage, unlock the achievement for it
		if (static_cast<PlayerComponent*>(&ent->getComponent("Player"))->m_dmgDealt >= 1000)
		{
			static_cast<AchievementComponent*>(achi::Listener::m_AchisPtr)->unlockAchievement("Damage Dealer");
		}
		break;
	case SUPER_STUN:
		//If the player has used 5 super stuns, unlock the achievement for it
		if (static_cast<PlayerComponent*>(&ent->getComponent("Player"))->m_supersUsed >= 5)
		{
			static_cast<AchievementComponent*>(achi::Listener::m_AchisPtr)->unlockAchievement("Stunner");
		}
		break;
	}
}
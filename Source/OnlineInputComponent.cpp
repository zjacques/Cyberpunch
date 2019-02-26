#include "OnlineInputComponent.h"

OnlineInputComponent::OnlineInputComponent()
{
	m_commandsToSend = queue<string>();
}


void OnlineInputComponent::handleInput(void* e)
{
	auto entity = static_cast<Entity*>(e);
	if ((m_previousCMD == (Command*)&m_moveLeftCMD || m_previousCMD == (Command*)&m_moveRightCMD) && m_commandsToSend.size() == 0)
	{
		m_previousCMD->execute(*entity);
	}
	if (m_commandsToSend.size() > 0)
	{
		string topCMD = m_commandsToSend.front();
		m_currentCMD = nullptr;
		if (topCMD == "JUMP")
		{
			m_currentCMD = &m_jumpCMD;
		}
		else if (topCMD == "UPPERCUT")
		{
			m_currentCMD = &m_uppercutCMD;
		}
		else if (topCMD == "PUNCH")
		{
			m_currentCMD = &m_punchCMD;
		}
		else if (topCMD == "KICK")
		{
			m_currentCMD = &m_kickCMD;
		}
		else if (topCMD == "MOVE LEFT")
		{
			m_currentCMD = &m_moveLeftCMD;
		}
		else if (topCMD == "MOVE RIGHT")
		{
			m_currentCMD = &m_moveRightCMD;
		}
		else if (topCMD == "FALL")
		{
			m_currentCMD = &m_fallCMD;
		}
		else if (topCMD == "SUPER")
		{
			m_currentCMD = &m_superCMD;
		}
		m_commandsToSend.pop();
		//If the current command was set, execute the command
		if (nullptr != m_currentCMD)
		{
			m_currentCMD->execute(*entity);
		}
	}
	else if (static_cast<AttackComponent*>(&entity->getComponent("Attack"))->attackActive() == false
		&& !(static_cast<AnimationComponent*>(&entity->getComponent("Animation"))->getCurrentID() == "Jump"
			&& static_cast<AnimationComponent*>(&entity->getComponent("Animation"))->getCurrentAnimation()->getCompleted() == false)
		&& static_cast<PlayerPhysicsComponent*>(&entity->getComponent("Player Physics"))->stunned() == false)
	{
		//static_cast<AnimationComponent*>(&entity->getComponent("Animation"))->playAnimation("Idle", true);
		m_idleCMD.execute(*entity);
	}
	if (m_positionsToSyncTo.size() > 0)
	{
		OnlineSendComponent::syncStruct loc = m_positionsToSyncTo.front();
		syncPosition(entity, loc.pos.x, loc.pos.y, loc.vel.x, loc.vel.y, loc.dvel.x, loc.dvel.y);
		m_positionsToSyncTo.pop();
	}

	m_previousCMD = m_currentCMD;
}

int OnlineInputComponent::addCommand(string cmd)
{
	m_commandsToSend.push(cmd);

	return m_commandsToSend.size();
}

void OnlineInputComponent::addPositions(float px, float py, float vx, float vy, float dvx, float dvy)
{
	OnlineSendComponent::syncStruct loc;
	loc.pos.x = px;
	loc.pos.y = py;
	loc.vel.x = vx;
	loc.vel.y = vy;
	loc.dvel.x = dvx;
	loc.dvel.y = dvy;
	m_positionsToSyncTo.push(loc);
}

void OnlineInputComponent::syncPosition(Entity* entity, float px, float py, float vx, float vy, float dvx, float dvy)
{
	//auto entity = static_cast<Entity*>(e);

	static_cast<PlayerPhysicsComponent*>(&entity->getComponent("Player Physics"))->posPtr->position = Vector2f(px, py);
	static_cast<PlayerPhysicsComponent*>(&entity->getComponent("Player Physics"))->m_currentVel = b2Vec2(vx, vy);
	static_cast<PlayerPhysicsComponent*>(&entity->getComponent("Player Physics"))->m_desiredVel = b2Vec2(dvx, dvy);
	static_cast<PlayerPhysicsComponent*>(&entity->getComponent("Player Physics"))->m_jumpSensor->setPosition(px, py);
}



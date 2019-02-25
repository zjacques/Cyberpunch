#include "OnlineInputComponent.h"

OnlineInputComponent::OnlineInputComponent()
{
	m_commandsToSend = queue<string>();
}


void OnlineInputComponent::handleInput(void* e)
{
	auto entity = static_cast<Entity*>(e);
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
		m_commandsToSend.pop();
		//If the current command was set, execute the command
		if (nullptr != m_currentCMD)
		{
			m_currentCMD->execute(*entity);
		}
	}
	else if (static_cast<AttackComponent*>(&entity->getComponent("Attack"))->attackActive() == false)
		static_cast<AnimationComponent*>(&entity->getComponent("Animation"))->playAnimation("Idle", true);
	
	

}

int OnlineInputComponent::addCommand(string cmd)
{
	m_commandsToSend.push(cmd);

	return m_commandsToSend.size();
}



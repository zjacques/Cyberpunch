#include "OnlineInputComponent.h"

OnlineInputComponent::OnlineInputComponent()
{

}


void OnlineInputComponent::handleInput(void* e)
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
	else if(topCMD == "PUNCH")
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

	//If the current command was set, execute the command
	if (nullptr != m_currentCMD)
	{
		auto entity = static_cast<Entity*>(e);
		m_currentCMD->execute(*entity);
	}

}


void OnlineInputComponent::deserialize(string jsonInput)
{
	json currentPacket = json::parse(jsonInput);

	if (currentPacket["type"] == "COMMANDS")
	{
		vector<string> commands = currentPacket["list"];
		for (auto iter = commands.begin(); iter != commands.end(); iter++)
		{
			m_commandsToSend.push(*iter);
			//m_input->m_current[*iter] = true;
		}
	}
}

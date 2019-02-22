#ifndef AIINPUTCOMPONENT_H
#define AIINPUTCOMPONENT_H

#include "InputComponent.h"
#include "Commands.h"
#include "Entity.h"

class AiInputComponent : public InputComponent
{
public:
	AiInputComponent() :
		InputComponent()
	{
	}

	void handleInput(std::string s, Entity * e)
	{
		m_currentCMD = nullptr;

		if (s == "YBTN")
		{
			m_currentCMD = &m_jumpCMD;
		}
		else if (s == "XBTN")
		{
			m_currentCMD = &m_punchCMD;
		}
		else if (s == "ABTN")
		{
			m_currentCMD = &m_kickCMD;
		}
		else if (s == "STICKDOWN")
		{
			m_currentCMD = &m_phaseDownCMD;
		}
		else if (s == "STICKLEFT")
		{
			m_currentCMD = &m_moveLeftCMD;
		}
		else if (s == "STICKRIGHT")
		{
			m_currentCMD = &m_moveRightCMD;
		}

		if (!s.empty())
		{
			//auto entity = static_cast<Entity*>(e);
			m_currentCMD->execute(*e);
		}

	}

private:
	JumpCommand m_jumpCMD;
	MoveLeftCommand m_moveLeftCMD;
	MoveRightCommand m_moveRightCMD;
	PunchCommand m_punchCMD;
	KickCommand m_kickCMD;
	UppercutCommand m_uppercutCMD;
	PhaseDownCommand m_phaseDownCMD;
	Command * m_currentCMD;
};

#endif

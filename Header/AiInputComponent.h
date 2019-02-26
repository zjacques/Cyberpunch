#ifndef AIINPUTCOMPONENT_H
#define AIINPUTCOMPONENT_H

#include "InputComponent.h"
#include "Commands.h"
#include "Entity.h"

class AiInputComponent : public InputComponent
{
public:
	AiInputComponent() :
		m_left(false),
		m_right(false),
		InputComponent()
	{
	}

	void handleInput(std::string s, Entity * e)
	{
		m_currentCMD = nullptr;

		if (aiIsButtonPressed("YBTN")) //Y
		{
			m_currentCMD = &m_jumpCMD;
		}
		else if (aiIsButtonPressed("XBTN")) //X
		{
			m_currentCMD = &m_punchCMD;
		}
		else if (aiIsButtonPressed("ABTN")) //A
		{
			m_currentCMD = &m_kickCMD;
		}
		else if (aiIsButtonPressed("STICKDOWN")) //Down
		{
			m_currentCMD = &m_phaseDownCMD;
		}
		else if (aiIsButtonHeld("STICKLEFT")) //Left
		{
			m_currentCMD = &m_moveLeftCMD;
		}
		else if (aiIsButtonHeld("STICKRIGHT")) //Right
		{
			m_currentCMD = &m_moveRightCMD;
		}

		if (nullptr != m_currentCMD)
		{
			m_currentCMD->execute(*e);
		}
	}

private:
	bool aiIsButtonHeld(std::string btn)
	{
		return m_previous[btn];
	}
	bool aiIsButtonPressed(std::string btn)
	{
		return m_previous[btn] && !m_current[btn];
	}

	JumpCommand m_jumpCMD;
	MoveLeftCommand m_moveLeftCMD;
	MoveRightCommand m_moveRightCMD;
	PunchCommand m_punchCMD;
	KickCommand m_kickCMD;
	UppercutCommand m_uppercutCMD;
	PhaseDownCommand m_phaseDownCMD;
	Command * m_currentCMD;
	bool m_left, m_right;
};

#endif
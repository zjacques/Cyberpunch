#ifndef AIINPUTCOMPONENT_H
#define AIINPUTCOMPONENT_H

#include "InputComponent.h"
#include "Commands.h"

class AiInputComponent : public InputComponent
{
public:
	AiInputComponent() :
		InputComponent()
	{
	}

	void handleInput(std::string e)
	{
		m_currentCMD = nullptr;

		if (e == "YBTN")
		{
			m_currentCMD = &m_jumpCMD;
		}
		else if (e == "XBTN")
		{
			m_currentCMD = &m_punchCMD;
		}
		else if (e == "")

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

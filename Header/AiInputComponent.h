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

		if (/*s == "YBTN"*/ isButtonPressed("YBTN"))
		{
			m_left = false;
			m_right = false;
			m_currentCMD = &m_jumpCMD;
		}
		else if (s == "XBTN")
		{
			m_left = false;
			m_right = false;
			m_currentCMD = &m_punchCMD;
		}
		else if (s == "ABTN")
		{
			m_left = false;
			m_right = false;
			m_currentCMD = &m_kickCMD;
		}
		else if (s == "STICKDOWN")
		{
			m_left = false;
			m_right = false;
			m_currentCMD = &m_phaseDownCMD;
		}
		if (s == "STICKLEFT")
		{
			m_left = true;
			m_right = false;
			m_currentCMD = &m_moveLeftCMD;
		}
		else if (s == "STICKRIGHT" || m_right)
		{
			m_right = true;
			m_left = false;
			m_currentCMD = &m_moveRightCMD;
		}

		if (!s.empty())
		{
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
	bool m_left, m_right;
};

#endif

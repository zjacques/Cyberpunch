#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H
#include "InputComponent.h"
#include "Commands.h"


class PlayerInputComponent : public InputComponent {

public:
	PlayerInputComponent() :
		InputComponent()
	{

	}
	void handleInput(void* e) override
	{
		m_currentCMD = nullptr;

		if (isButtonPressed("YBTN"))
		{
			m_currentCMD = &m_jumpCMD;
		}
		else if(isButtonPressed("XBTN"))
		{
			if (isButtonHeld("STICKUP"))
				m_currentCMD = &m_uppercutCMD;
			else
				m_currentCMD = &m_punchCMD;
		}
		else if (isButtonPressed("ABTN"))
		{
			m_currentCMD = &m_kickCMD;
		}
		else if (isButtonPressed("STICKDOWN"))
		{
			m_currentCMD = &m_phaseDownCMD;
		}
		else if (isButtonHeld("STICKLEFT") || isButtonHeld("STICKDOWNLEFT") || isButtonHeld("STICKUPLEFT"))
		{
			m_currentCMD = &m_moveLeftCMD;
		}
		else if (isButtonHeld("STICKRIGHT") || isButtonHeld("STICKDOWNRIGHT") || isButtonHeld("STICKUPRIGHT"))
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

private:
	//Commands
	JumpCommand m_jumpCMD;
	MoveLeftCommand m_moveLeftCMD;
	MoveRightCommand m_moveRightCMD;
	PunchCommand m_punchCMD;
	KickCommand m_kickCMD;
	UppercutCommand m_uppercutCMD;
	PhaseDownCommand m_phaseDownCMD;
	Command* m_currentCMD;
};



#endif
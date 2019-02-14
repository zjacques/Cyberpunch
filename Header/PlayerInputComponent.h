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



		//if (input.isButtonHeld("STICKRIGHT") || input.isButtonHeld("STICKDOWNRIGHT") || input.isButtonHeld("STICKUPRIGHT"))
		//{
		//	m_moveRightCMD.execute(*m_moveSystem);
		//}
		//if (input.isButtonHeld("STICKLEFT") || input.isButtonHeld("STICKDOWNLEFT") || input.isButtonHeld("STICKUPLEFT"))
		//{
		//	m_moveLeftCMD.execute(*m_moveSystem);
		//}
		////Upercut
		//if (input.isButtonHeld("STICKUP") && input.isButtonPressed("XBTN"))
		//{
		//	//if on the ground upercut an enemy
		//	//if (m_canJump)
		//	//	upperCut();
		//	//else //If in air punch above you
		//	//	punchUp();
		//}

		////else if (input.isButtonPressed("XBTN"))
		////{
		////	punch();
		////}
		////if (input.isButtonPressed("ABTN"))
		////{
		////	kick();
		////}

		//if (input.isButtonPressed("STICKDOWN"))
		//{
		//	//If we can fall, call our jump down command
		//	if (m_canFall)
		//	{
		//		m_jumpDwnCMD.execute(*m_moveSystem);
		//	}
		//}
	}

private:
	//Commands
	JumpCommand m_jumpCMD;
	MoveLeftCommand m_moveLeftCMD;
	MoveRightCommand m_moveRightCMD;
	PunchCommand m_punchCMD;
	KickCommand m_kickCMD;
	UppercutCommand m_uppercutCMD;
	Command* m_currentCMD;
};



#endif
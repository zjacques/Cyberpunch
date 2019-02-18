#pragma once
#include "Component.h"
#include "Commands.h"
#include "nlohmann/json.hpp"
#include <queue>

using std::string;
using nlohmann::json;
using std::queue;
using std::vector;

class OnlineInputComponent : public Component {
public:
	OnlineInputComponent();

	void handleInput(void* e);
	int addCommand(string);

	int m_playerNumber;
private:

	Command * m_currentCMD;

	JumpCommand m_jumpCMD;
	MoveLeftCommand m_moveLeftCMD;
	MoveRightCommand m_moveRightCMD;
	PunchCommand m_punchCMD;
	KickCommand m_kickCMD;
	UppercutCommand m_uppercutCMD;

	queue<string> m_commandsToSend;

};
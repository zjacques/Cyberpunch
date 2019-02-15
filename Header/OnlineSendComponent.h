#pragma once
#include "Component.h"
#include "InputSystem.h"
#include <queue>

using std::queue;
using std::string;

class OnlineSendComponent : public Component{
public:
	OnlineSendComponent();

	queue<string>* Send();
	void addCommand(string cmd) { m_commandsToSend.push(cmd); }

	int m_playerNumber;
private:

	queue<string> m_commandsToSend;
};
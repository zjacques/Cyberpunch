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
	void addCommand(string cmd) { 
		if (m_prevCommand != cmd) {
			m_commandsToSend.push(cmd);
			m_prevCommand = cmd;
		}
	}

	int m_playerNumber;
private:
	string m_prevCommand = "";
	queue<string> m_commandsToSend;
};
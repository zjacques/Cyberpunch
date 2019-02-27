#pragma once
#include "Component.h"
#include "InputSystem.h"
#include <queue>
#include "Vector2f.h"

using std::queue;
using std::string;

class OnlineSendComponent : public Component{
public:
	struct syncStruct {
		Vector2f pos;
		Vector2f vel;
		Vector2f dvel;
	} syncVars;
	OnlineSendComponent(bool local) { m_local = local; };

	queue<string>* Send();
	void addCommand(string cmd) { 
		if (m_prevCommand != cmd && m_local) {
			m_commandsToSend.push(cmd);
			m_prevCommand = cmd;
		}
	}

	void setSync(Vector2f pos, Vector2f vel, Vector2f dvel) {
		syncVars.pos = pos;
		syncVars.vel = vel;
		syncVars.dvel = dvel;
	}

	syncStruct getSync()
	{
		return syncVars;
	}

	int m_playerNumber;
private:
	bool m_local;
	string m_prevCommand = "";
	queue<string> m_commandsToSend;
};
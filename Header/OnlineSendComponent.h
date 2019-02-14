#pragma once
#include "Component.h"
#include "InputSystem.h"
#include <SDL_net.h>
#include "ClientSocket.h"
#include "SocketException.h"
#include <queue>

using std::queue;
using std::pair;

class OnlineSendComponent : public Component{
public:
	OnlineSendComponent();

	void ConnectToServer();
	void SerializeInputs(InputSystem& input);
	void Send();

private:


	ClientSocket* m_outputSocket;
	queue<string> m_commandsToSend;
};
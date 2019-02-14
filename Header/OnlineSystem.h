#pragma once
#include "System.h"
#include "ClientSocket.h"
#include "OnlineSendComponent.h"

using std::vector;
using std::string;

class OnlineSystem : public System {
public:
	OnlineSystem() {};
	virtual ~OnlineSystem() {}
	void addComponent(Component *);
	void addSendingPlayer(OnlineSendComponent*);

	void update(double dt);

	void SendCommands();

	bool ConnectToServer();

	bool isConnected = false;

private:
	ClientSocket* m_Socket;
	vector<OnlineSendComponent*> m_sendingPlayers;
};
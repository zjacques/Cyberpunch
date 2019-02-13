#pragma once
#include "InputSystem.h"
#include "ClientSocket.h"
#include "nlohmann/json.hpp"
#include <queue>

using std::string;
using nlohmann::json;
using std::queue;
using std::vector;

class OnlineInputSystem : public InputSystem {
public:
	OnlineInputSystem();
	void ConnectToServer();

	void update(double dt) override;
	void addComponent(Component * component) override;
private:
	void deserialize(string jsonInput);


	ClientSocket* m_inputSocket;
	queue<string> m_commandsToSend;
	//InputComponent * m_input;

};
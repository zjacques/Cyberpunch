#include "OnlineSendComponent.h"

OnlineSendComponent::OnlineSendComponent()
{
	
}

void OnlineSendComponent::ConnectToServer()
{
	try
	{
		// Now try to instantiate the client socket
		// Parameters: server address, port number, buffer size (i.e. max message size)
		// Note: You can provide the serverURL as a dot-quad ("1.2.3.4") or a hostname ("server.foo.com")
		m_outputSocket = new ClientSocket("127.0.0.1", 1234, 512);

		m_outputSocket->connectToServer();
	}
	catch (SocketException e)
	{
		std::cerr << "Something went wrong creating a ClientSocket object." << std::endl;
		std::cerr << "Error is: " << e.what() << std::endl;
		std::cerr << "Terminating application." << std::endl;
		exit(-1);
	}
}

void OnlineSendComponent::SerializeInputs(InputSystem& input)
{
	string jsonString = "{ \"type\" : \" COMMANDS\", \"list\":{";
	bool isFirst = true;

	if (input.isButtonPressed("YBTN") || input.isButtonPressed("STICKUP"))
	{
		if (!isFirst) {
			jsonString += ",";
		}
		else isFirst = false;
		jsonString += " \"command\" : \"JUMP\" ";
		//m_commandsToSend.push_back(pair<string, string>("command", "JUMP"));
	}
	if (input.isButtonHeld("STICKRIGHT") || input.isButtonHeld("STICKDOWNRIGHT") || input.isButtonHeld("STICKUPRIGHT"))
	{
		if (!isFirst) {
			jsonString += ",";
		}
		else isFirst = false;
		jsonString += " \"command\" : \"RIGHT\" ";
		//m_commandsToSend.push_back(pair<string, string>("command", "RIGHT"));
	}
	if (input.isButtonHeld("STICKLEFT") || input.isButtonHeld("STICKDOWNLEFT") || input.isButtonHeld("STICKUPLEFT"))
	{
		if (!isFirst) {
			jsonString += ",";
		}
		else isFirst = false;
		jsonString += " \"command\" : \"LEFT\" ";
		//m_commandsToSend.push_back(pair<string, string>("command", "LEFT"));
	}
	if (input.isButtonPressed("STICKDOWN"))
	{
		if (!isFirst) {
			jsonString += ",";
		}
		else isFirst = false;
		jsonString += " \"command\" : \"FALL\" ";
		//m_commandsToSend.push_back(pair<string, string>("command", "FALL"));
	}

	jsonString += " }}";

	m_commandsToSend.push(jsonString);

}

void OnlineSendComponent::Send()
{
	while (m_commandsToSend.size() > 0)
	{
		m_outputSocket->sendString(m_commandsToSend.front());
		m_commandsToSend.pop();
	}
	

}

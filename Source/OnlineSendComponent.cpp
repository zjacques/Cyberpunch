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
	string jsonString = "{ \"type\" : \"COMMANDS\", \"list\":[";
	bool isFirst = true;
	std::vector<string> buttons = {"YBTN","STICKUP","STICKRIGHT","STICKDOWNRIGHT","STICKUPRIGHT","STICKLEFT", "STICKDOWNLEFT","STICKUPLEFT","STICKDOWN","XBTN","ABTN" };
	//std::vector<string> heldButtons = {"YBTN","STICKUP","STICKRIGHT","STICKDOWNRIGHT","STICKUPRIGHT","STICKLEFT" "STICKDOWNLEFT","STICKUPLEFT","STICKDOWN","XBTN","ABTN" };
	/*for (auto const& x : buttons)
	{
		if (input.isButtonHeld(x) || input.isButtonPressed(x))
		{
			if (!isFirst) {jsonString += ",";}
			else { isFirst = false; }
			jsonString += "\""+x+"\"";
		}
	}*/

	/*if (input.isButtonPressed("YBTN") || input.isButtonPressed("STICKUP"))
	{
		if (!isFirst) {
			jsonString += ",";
		}
		else isFirst = false;
		jsonString += "\"YBTN\" ";
	}
	if (input.isButtonHeld("STICKRIGHT") || input.isButtonHeld("STICKDOWNRIGHT") || input.isButtonHeld("STICKUPRIGHT"))
	{
		if (!isFirst) {
			jsonString += ",";
		}
		else isFirst = false;
		jsonString += "\"STICKRIGHT\" ";
	}
	if (input.isButtonHeld("STICKLEFT") || input.isButtonHeld("STICKDOWNLEFT") || input.isButtonHeld("STICKUPLEFT"))
	{
		if (!isFirst) {
			jsonString += ",";
		}
		else isFirst = false;
		jsonString += "\"STICKLEFT\" ";
	}
	if (input.isButtonPressed("STICKDOWN"))
	{
		if (!isFirst) {
			jsonString += ",";
		}
		else isFirst = false;
		jsonString += "\"STICKDOWN\" ";
	}
	if (input.isButtonPressed("XBTN"))
	{
		if (!isFirst) {
			jsonString += ",";
		}
		else isFirst = false;
		jsonString += "\"XBTN\" ";
	}
	if (input.isButtonPressed("ABTN"))
	{
		if (!isFirst) {
			jsonString += ",";
		}
		else isFirst = false;
		jsonString += "\"ABTN\" ";
	}*/

	jsonString += " ]}";

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

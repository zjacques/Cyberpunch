#include "OnlineInputSystem.h"

OnlineInputSystem::OnlineInputSystem()
{

}

void OnlineInputSystem::ConnectToServer()
{
	try
	{
		// Now try to instantiate the client socket
		// Parameters: server address, port number, buffer size (i.e. max message size)
		// Note: You can provide the serverURL as a dot-quad ("1.2.3.4") or a hostname ("server.foo.com")
		m_inputSocket = new ClientSocket("127.0.0.1", 1234, 512);

		m_inputSocket->connectToServer();
	}
	catch (SocketException e)
	{
		std::cerr << "Something went wrong creating a ClientSocket object." << std::endl;
		std::cerr << "Error is: " << e.what() << std::endl;
		std::cerr << "Terminating application." << std::endl;
		exit(-1);
	}
}

void OnlineInputSystem::update(double dt)
{

	// Check if we've received a message
	//string receivedMessage = m_inputSocket->checkForIncomingMessages();

	m_input->m_previous = m_input->m_current; //Set our previous

	for (auto const& x : m_input->m_current)
	{
		m_input->m_current[x.first] = false;
	}

	// If so then...
	//if (receivedMessage != "")
	//{
		//deserialize(receivedMessage);
	//}
}

void OnlineInputSystem::addComponent(Component * component)
{
	m_input = static_cast<InputComponent*>(component);
}

void OnlineInputSystem::deserialize(string jsonInput)
{
	json currentPacket = json::parse(jsonInput);

	if (currentPacket["type"] == "COMMANDS")
	{
		vector<string> commands = currentPacket["list"];
		for (auto iter = commands.begin(); iter != commands.end(); iter++)
		{
			m_input->m_current[*iter] = true;
		}
	}
}

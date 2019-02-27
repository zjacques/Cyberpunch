#include "OnlineSendComponent.h"

queue<string>* OnlineSendComponent::Send()
{
	return &m_commandsToSend;

}

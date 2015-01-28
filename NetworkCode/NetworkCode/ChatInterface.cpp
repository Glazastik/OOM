#include "ChatInterface.h"

ChatModel ChatInterface::chatModel;

ChatInterface::ChatInterface()
{
}

ChatInterface::~ChatInterface()
{
}

void ChatInterface::TestConnect(int serviceType, char* buffer, int bufferCapacity)
{
	std::string responseStr = chatModel.TestConnect(serviceType);
	strcpy_s(buffer, bufferCapacity, responseStr.c_str());
}

void ChatInterface::GetMessage(char* messageBuffer, int bufferCapacity)
{
	std::string messageStr = chatModel.GetMessage();
	strcpy_s(messageBuffer, bufferCapacity, messageStr.c_str());
}
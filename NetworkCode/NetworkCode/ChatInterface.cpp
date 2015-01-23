#include "ChatInterface.h"

ChatModel ChatInterface::chatModel;

ChatInterface::ChatInterface()
{
}

ChatInterface::~ChatInterface()
{
}

void ChatInterface::GetMessage(char* messageBuffer, int bufferCapacity)
{
	std::string messageStr = chatModel.GetMessage();
	strcpy_s(messageBuffer, bufferCapacity, messageStr.c_str());
}
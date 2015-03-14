#include "ChatInterface.h"
#include "DebugBuffer.h"

ChatModel ChatInterface::chatModel;

// Public
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

void ChatInterface::ReadDebugBufferLine(char* lineBuffer, int bufferCapacity)
{
	std::string line = DebugBuffer::ReadLine();
	strcpy_s(lineBuffer, bufferCapacity, line.c_str());
}

int ChatInterface::GetDebugBufferSize()
{
	return DebugBuffer::GetNumLines();
}

// Private
ChatInterface::ChatInterface()
{
}

ChatInterface::~ChatInterface()
{
}
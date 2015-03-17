#include "ChatInterface.h"
#include "DebugBuffer.h"

ChatModel ChatInterface::chatModel;

// Public
void ChatInterface::ReadDebugBufferLine(char* lineBuffer, int bufferCapacity)
{
	std::string line = DebugBuffer::ReadLine();
	strcpy_s(lineBuffer, bufferCapacity, line.c_str());
}

int ChatInterface::GetDebugBufferSize()
{
	return DebugBuffer::GetNumLines();
}

void ChatInterface::ConnectService(int serviceType)
{
	chatModel.ConnectService(serviceType);
}

void ChatInterface::CloseService(int serviceType)
{
	chatModel.CloseService(serviceType);
}

// Private
ChatInterface::ChatInterface()
{
}

ChatInterface::~ChatInterface()
{
}
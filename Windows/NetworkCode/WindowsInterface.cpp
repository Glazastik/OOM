#include "WindowsInterface.h"
#include "ChatInterface.h"
#include "TokenHandler.h"
#include <string>
#include "boost/log/trivial.hpp"

__declspec(dllexport) void init()
{
	ChatInterface::Init();
}

__declspec(dllexport) int readMessage(size_t messageNum, char* messageBuffer, int bufferCapacity)
{
	return ChatInterface::ReadMessage(messageNum, messageBuffer, bufferCapacity);
}

__declspec(dllexport) int getNumMessages()
{
	return ChatInterface::GetNumMessages();
}

__declspec(dllexport) void connectService(int serviceType)
{
	ChatInterface::ConnectService(serviceType);
}

__declspec(dllexport) void closeService(int serviceType)
{
	ChatInterface::CloseService(serviceType);
}

__declspec(dllexport) void parseUrl(char* uri)
{
	// TokenHandler::parseUrl(uri);
}

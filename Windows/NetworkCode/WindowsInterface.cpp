#include "WindowsInterface.h"
#include "ChatInterface.h"
#include "TokenHandler.h"
#include <string>
#include "boost/log/trivial.hpp"

__declspec(dllexport) void init()
{
	ChatInterface::Init();
}

__declspec(dllexport) void readDebugBufferLine(int lineNum, char* lineBuffer, int bufferCapacity)
{
	ChatInterface::ReadDebugBufferLine(lineNum, lineBuffer, bufferCapacity);
}

__declspec(dllexport) int getDebugBufferSize()
{
	return ChatInterface::GetDebugBufferSize();
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

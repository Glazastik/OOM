#include "WindowsInterface.h"
#include "ChatInterface.h"
#include "TokenHandler.h"
#include <string>

__declspec(dllexport) void readDebugBufferLine(char* lineBuffer, int bufferCapacity)
{
	//ChatInterface::ReadDebugBufferLine(lineBuffer, bufferCapacity);
}

__declspec(dllexport) int getDebugBufferSize()
{
	//return ChatInterface::GetDebugBufferSize();
	return 1;
}

__declspec(dllexport) void connectService(int serviceType)
{
	//ChatInterface::ConnectService(serviceType);
}

__declspec(dllexport) void closeService(int serviceType)
{
	//ChatInterface::CloseService(serviceType);
}

__declspec(dllexport) void parseUrl(char* uri)
{
	// TokenHandler::parseUrl(uri);
}

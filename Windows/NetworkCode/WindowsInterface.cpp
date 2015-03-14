#include "WindowsInterface.h"
#include "ChatInterface.h"
#include "TokenHandler.h"
#include <string>

__declspec(dllexport) void testConnect(int serviceType, char* buffer, int bufferCapacity)
{
	ChatInterface::TestConnect(serviceType, buffer, bufferCapacity);
}

__declspec(dllexport) void getMessage(char* messageBuffer, int bufferCapacity)
{
	ChatInterface::GetMessage(messageBuffer, bufferCapacity);
}

__declspec(dllexport) void readDebugBufferLine(char* lineBuffer, int bufferCapacity)
{
	ChatInterface::ReadDebugBufferLine(lineBuffer, bufferCapacity);
}

__declspec(dllexport) int getDebugBufferSize()
{
	return ChatInterface::GetDebugBufferSize();
}

__declspec(dllexport) void parseUrl(char* uri)
{
	// TokenHandler::parseUrl(uri);
}
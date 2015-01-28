#include "WindowsInterface.h"
#include "ChatInterface.h"
#include <string>

__declspec(dllexport) void testConnect(int serviceType, char* buffer, int bufferCapacity)
{
	ChatInterface::TestConnect(serviceType, buffer, bufferCapacity);
}

__declspec(dllexport) void getMessage(char* messageBuffer, int bufferCapacity)
{
	ChatInterface::GetMessage(messageBuffer, bufferCapacity);
}
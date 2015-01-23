#include "WindowsInterface.h"
#include "ChatInterface.h"
#include <string>

__declspec(dllexport) void getMessage(char* messageBuffer, int bufferCapacity)
{
	ChatInterface::GetMessage(messageBuffer, bufferCapacity);
}
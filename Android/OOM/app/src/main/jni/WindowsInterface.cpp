#include "WindowsInterface.h"
#include "ChatInterface.h"
#include "TokenHandler.h"
#include <string>

__declspec(dllexport) void init()
{
	ChatInterface::Init();
}

__declspec(dllexport) void stop()
{
	ChatInterface::Stop();
}

__declspec(dllexport) void connectService(int serviceType)
{
	ChatInterface::ConnectService(serviceType);
}

__declspec(dllexport) int readMessage(size_t messageNum, char* messageBuffer, int bufferCapacity)
{
	return ChatInterface::ReadMessage(messageNum, messageBuffer, bufferCapacity);
}

__declspec(dllexport) int getNumMessages()
{
	return ChatInterface::GetNumMessages();
}

__declspec(dllexport) void addPerson(int id, const char* name)
{
	ChatInterface::AddPerson(id, name);
}

__declspec(dllexport) void addAccountToPerson(int personId, int accountId, int serviceType, const char* address)
{
	ChatInterface::AddAccountToPerson(personId, accountId, serviceType, address);
}

__declspec(dllexport) void sendChatMessage(int accountId, const char* message)
{
	ChatInterface::SendChatMessage(accountId, message);
}

__declspec(dllexport) int getServiceType(int accountId)
{
	return ChatInterface::GetServiceType(accountId);
}
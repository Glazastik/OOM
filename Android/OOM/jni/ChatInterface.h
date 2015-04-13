#pragma once
#include "ChatModel.h"
#include <memory>

class ChatInterface
{
public:
	static void Init();
	static void Stop();
	static void ConnectService(int serviceType);
	static int ReadMessage(size_t messageNum, char* messageBuffer, int bufferCapacity);
	static int GetNumMessages();
	static void AddPerson(int id, const char* name);
	static void AddAccountToPerson(int personId, int accountId, int serviceType, const char* address);
	static void SendChatMessage(int accountId, const char* message);
private:
	static std::shared_ptr<ChatModel> chatModel;

	ChatInterface();
	~ChatInterface();
};
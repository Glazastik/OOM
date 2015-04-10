#pragma once
#include "ChatModel.h"
#include <memory>

class ChatInterface
{
public:
	static void Init();
	static int ReadMessage(size_t messageNum, char* messageBuffer, int bufferCapacity);
	static int GetNumMessages();
	static void ConnectService(int serviceType);
	static void CloseService(int serviceType);
private:
	static std::shared_ptr<ChatModel> chatModel;

	ChatInterface();
	~ChatInterface();
};
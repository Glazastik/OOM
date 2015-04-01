#pragma once
#include "ChatModel.h"
#include <memory>

class ChatInterface
{
public:
	static void Init();
	static void ReadDebugBufferLine(int lineNum, char* lineBuffer, int bufferCapacity);
	static int GetDebugBufferSize();
	static void ConnectService(int serviceType);
	static void CloseService(int serviceType);
private:
	static std::shared_ptr<ChatModel> chatModel;

	ChatInterface();
	~ChatInterface();
};
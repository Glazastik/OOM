#pragma once
#include "ChatModel.h"
#include <memory>

class ChatInterface
{
public:
	static void ReadDebugBufferLine(char* lineBuffer, int bufferCapacity);
	static int GetDebugBufferSize();
	static void ConnectService(int serviceType);
	static void CloseService(int serviceType);
private:
	static ChatModel chatModel;

	ChatInterface();
	~ChatInterface();
};
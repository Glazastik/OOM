#pragma once
#include "ChatModel.h"
#include <memory>

class ChatInterface
{
public:
	static void TestConnect(int serviceType, char* responseBuffer, int bufferCapacity);
	static void GetMessage(char* messageBuffer, int bufferCapacity);
	static void ReadDebugBufferLine(char* lineBuffer, int bufferCapacity);
	static int GetDebugBufferSize();
private:
	static ChatModel chatModel;

	ChatInterface();
	~ChatInterface();
};
#pragma once
#include "ChatModel.h"
#include <memory>

class ChatInterface
{
private:
	static ChatModel chatModel;

	ChatInterface();
	~ChatInterface();
public:
	static void Init();
	static void GetMessage(char* messageBuffer, int bufferCapacity);
};
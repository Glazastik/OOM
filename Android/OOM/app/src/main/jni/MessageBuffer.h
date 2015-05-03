#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Message.h"

class MessageBuffer
{
public:
	static void AddMessage(std::shared_ptr<Message> message);
	static std::shared_ptr<Message> ReadMessage(size_t messageNum);
	static int GetNumMessages();
private:
	static std::vector<std::shared_ptr<Message>> messages;

	MessageBuffer();
	~MessageBuffer();
};


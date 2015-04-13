#include "MessageBuffer.h"

std::vector<std::shared_ptr<Message>> MessageBuffer::messages;

// Public
void MessageBuffer::AddMessage(std::shared_ptr<Message> message)
{
	messages.push_back(message);
}

std::shared_ptr<Message> MessageBuffer::ReadMessage(size_t messageNum)
{
	std::shared_ptr<Message> message = std::make_shared<Message>(-1, "Message number does not exist.");
	if (!messages.empty() && messageNum < messages.size())
	{
		message = messages.at(messageNum);
	}
	return message;
}

int MessageBuffer::GetNumMessages()
{
	return messages.size();
}

// Private
MessageBuffer::MessageBuffer()
{
}

MessageBuffer::~MessageBuffer()
{
}

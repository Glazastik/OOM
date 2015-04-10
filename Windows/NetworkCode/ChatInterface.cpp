#include "ChatInterface.h"
#include "MessageBuffer.h"

std::shared_ptr<ChatModel> ChatInterface::chatModel;

// Public
void ChatInterface::Init()
{
	chatModel = std::make_shared<ChatModel>();
}

// Return value is the account id of the message sender
int ChatInterface::ReadMessage(size_t messageNum, char* messageBuffer, int bufferCapacity)
{
	std::shared_ptr<Message> message = MessageBuffer::ReadMessage(messageNum);
	std::string payload = message->GetPayload();
	int senderId = message->GetSenderId();
	strcpy_s(messageBuffer, bufferCapacity, payload.c_str());
	return senderId;
}

int ChatInterface::GetNumMessages()
{
	return MessageBuffer::GetNumMessages();
}

void ChatInterface::ConnectService(int serviceType)
{
	chatModel->ConnectService(serviceType);
}

void ChatInterface::CloseService(int serviceType)
{
	chatModel->CloseService(serviceType);
}

// Private
ChatInterface::ChatInterface()
{
}

ChatInterface::~ChatInterface()
{
}
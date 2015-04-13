#include "ChatInterface.h"
#include "MessageBuffer.h"
#include "boost/log/trivial.hpp"

std::shared_ptr<ChatModel> ChatInterface::chatModel;

// Public
void ChatInterface::Init()
{
	chatModel = std::make_shared<ChatModel>();
}

void ChatInterface::Stop()
{
	chatModel->Cleanup();
}

void ChatInterface::ConnectService(int serviceType)
{
	chatModel->ConnectService(serviceType);
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

void ChatInterface::AddPerson(int id, const char* name)
{
	std::shared_ptr<Person> person = std::make_shared<Person>(id, name);
	chatModel->AddPerson(person);
}

void ChatInterface::AddAccountToPerson(int personId, int accountId, int serviceType, const char* address)
{
	std::shared_ptr<Person> person = chatModel->GetPerson(personId);
	std::shared_ptr<Account> account = std::make_shared<Account>(accountId, ServiceType::TypeOfIndex(serviceType), address);
	person->AddAccount(account);
}

void ChatInterface::SendChatMessage(int accountId, const char* message)
{
	chatModel->SendChatMessage(accountId, message);
}

// Private
ChatInterface::ChatInterface()
{
}

ChatInterface::~ChatInterface()
{
}
#include "ChatInterface.h"
#include "MessageBuffer.h"
#include <string>
#include <string.h>
#include <cstring>
#include <iostream>
#include <fstream>
//#include "boost/log/trivial.hpp"
#include <android/log.h>

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
	strncpy(messageBuffer, payload.c_str(), bufferCapacity); //omgjord
	
	for(int i = 0; i < bufferCapacity; i++)
	{
		messageBuffer[i] = 'h';
	}
	
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

int ChatInterface::GetServiceType(int accountId)
{
	return chatModel->GetServiceType(accountId);
}

// Private
ChatInterface::ChatInterface()
{
}

ChatInterface::~ChatInterface()
{
}
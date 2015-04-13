#include "Message.h"

Message::Message(int senderId, const std::string& payload)
{
	this->senderId = senderId;
	this->payload = payload;
}

Message::~Message()
{
}

int Message::GetSenderId()
{
	return senderId;
}

std::string Message::GetPayload()
{
	return payload;
}
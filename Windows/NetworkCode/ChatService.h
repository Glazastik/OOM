#pragma once
#include "ServiceType.h"
#include <string>

class ChatService
{
public:
	ChatService();
	~ChatService();
	virtual ServiceType::Type GetServiceType() = 0;
	virtual void Connect() = 0;
	virtual void CloseConnection() = 0;
	virtual void SendChatMessage(std::string address, std::string message) = 0;
};


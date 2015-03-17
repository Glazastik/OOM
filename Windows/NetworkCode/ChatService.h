#pragma once
#include "ServiceType.h"
#include <string>
#include <boost\asio.hpp>

using boost::asio::ip::tcp;

class ChatService
{
public:
	ChatService();
	~ChatService();
	virtual ServiceType::Type GetServiceType() = 0;
	virtual void Connect() = 0;
	virtual void CloseConnection() = 0;
};


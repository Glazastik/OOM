#pragma once
#include "ChatService.h"
#include "boost/asio.hpp"
#include "Person.h"
#include "IRCConnection.h"

class IRC : public ChatService
{
public:
	IRC(std::shared_ptr<boost::asio::io_service> io_service, std::shared_ptr<std::vector<std::shared_ptr<Person>>> persons,
		std::string host, std::string port, std::string channel, std::string username, std::string nickname, std::string password);
	~IRC();
	ServiceType::Type GetServiceType();
	void Connect();
	void CloseConnection();
	void SendChatMessage(std::string address, std::string message);
private:
	IRCConnection ircConnection;
};


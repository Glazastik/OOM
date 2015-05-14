#include "IRC.h"

// Public
IRC::IRC(std::shared_ptr<boost::asio::io_service> io_service,
	std::shared_ptr<std::vector<std::shared_ptr<Person>>> persons, std::string host, std::string port,
	std::string channel, std::string username, std::string nickname, std::string password) :
	ircConnection(io_service, persons, host, port, channel, username, nickname, password)
{
}

IRC::~IRC()
{
}

ServiceType::Type IRC::GetServiceType()
{
	return ServiceType::IRC;
}

void IRC::Connect()
{
	ircConnection.Connect();
}

void IRC::CloseConnection()
{
	ircConnection.CloseConnection();
}

void IRC::SendChatMessage(std::string address, std::string message)
{
	ircConnection.SendChatMessage(address, message);
}

#include "GoogleHangout.h"
#include <boost\array.hpp>

GoogleHangout::GoogleHangout(std::shared_ptr<boost::asio::io_service> io_service, std::string authid, std::string password, 
	std::shared_ptr<std::vector<std::shared_ptr<Person>>> persons) :
	ChatService(), googleHangoutConnection(io_service, authid, password, persons)
{
}

GoogleHangout::~GoogleHangout()
{
}

ServiceType::Type GoogleHangout::GetServiceType()
{
	return ServiceType::GOOGLE_HANGOUT;
}

void GoogleHangout::Connect()
{
	googleHangoutConnection.Connect();
}

void GoogleHangout::CloseConnection()
{
	googleHangoutConnection.CloseConnection();
}

void GoogleHangout::SendChatMessage(std::string address, std::string message)
{
	googleHangoutConnection.SendChatMessage(address, message);
}
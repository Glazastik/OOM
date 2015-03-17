#include "GoogleHangout.h"
#include <boost\array.hpp>
#include "DebugBuffer.h"

GoogleHangout::GoogleHangout(std::shared_ptr<boost::asio::io_service> io_service) : ChatService(), googleHangoutConnection(io_service)
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

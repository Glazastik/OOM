#include "GoogleHangout.h"
#include <boost\array.hpp>

GoogleHangout::GoogleHangout() : ChatService("talk.l.google.com", "5222")
{
	
}

GoogleHangout::~GoogleHangout()
{
}

ServiceType::Type GoogleHangout::GetServiceType()
{
	return ServiceType::GOOGLE_HANGOUT;
}

std::string GoogleHangout::TestConnect()
{
	ConnectSocket();

	std::string message;
	boost::array<char, 1024> responseBuffer;
	boost::system::error_code errorCode;
	size_t responseLength;

	// Initiate xml stream to server
	message = "<stream:stream  to = ' http://www.google.com/hangouts/' xmlns = 'jabber:client' xmlns : stream = 'http://etherx.jabber.org/streams' version = '1.0'>\r\n";
	socket->write_some(boost::asio::buffer(message));

	// Read server response
	responseLength = socket->read_some(boost::asio::buffer(responseBuffer), errorCode);

	std::string responseStr(responseBuffer.begin(), responseBuffer.end());
	return responseStr;
}
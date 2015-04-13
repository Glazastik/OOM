#include "GoogleHangoutConnection.h"

GoogleHangoutConnection::GoogleHangoutConnection(std::shared_ptr<boost::asio::io_service> io_service, std::string authid, std::string password,
	std::shared_ptr<std::vector<std::shared_ptr<Person>>> persons) :
XmppConnection(io_service, "xmpp.l.google.com", 5222, authid, password, persons)
{
	
}

GoogleHangoutConnection::~GoogleHangoutConnection()
{
}

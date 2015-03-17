#include "GoogleHangoutConnection.h"

GoogleHangoutConnection::GoogleHangoutConnection(std::shared_ptr<boost::asio::io_service> io_service) : XmppConnection(io_service, "xmpp.l.google.com", 5222)
{
	
}

GoogleHangoutConnection::~GoogleHangoutConnection()
{
}

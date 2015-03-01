#include <iostream>
#include <boost/asio.hpp>
#include "XmppConnection.h"

int main(int argc, char* args[])
{
	std::shared_ptr<boost::asio::io_service> io_service = std::make_shared<boost::asio::io_service>();
	XmppConnection xmppConnection(io_service, "xmpp.l.google.com", 5222);
	xmppConnection.Connect();
	xmppConnection.CloseConnection();

	std::cout << "Press RETURN to exit...";
	std::cin.get();
	return 0;
}
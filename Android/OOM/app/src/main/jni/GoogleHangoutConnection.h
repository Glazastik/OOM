#pragma once
#include <iostream>
#include <memory>
#include "boost\asio.hpp"
#include "XmppConnection.h"

class GoogleHangoutConnection : public XmppConnection
{
public:
	GoogleHangoutConnection(std::shared_ptr<boost::asio::io_service> io_service, std::string authid, std::string password,
		std::shared_ptr<std::vector<std::shared_ptr<Person>>> persons);
	~GoogleHangoutConnection();
};

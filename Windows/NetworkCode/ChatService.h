#pragma once
#include "ServiceType.h"
#include <string>
#include <boost\asio.hpp>

using boost::asio::ip::tcp;

class ChatService
{
protected:
	std::string hostAddress;
	std::string portNumber;

	std::shared_ptr<boost::asio::io_service> ioService;
	std::shared_ptr<tcp::resolver> resolver;
	std::shared_ptr<tcp::resolver::query> query;
	std::shared_ptr<tcp::resolver::iterator> endpointIterator;
	std::shared_ptr<tcp::socket> socket;

	void ConnectSocket();
public:
	ChatService(std::string hostAddress, std::string portNumber);
	~ChatService();
	virtual ServiceType::Type GetServiceType() = 0;
	virtual std::string TestConnect() = 0;
};


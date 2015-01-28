#include "ChatService.h"

ChatService::ChatService(std::string hostAddress, std::string portNumber)
{
	this->hostAddress = hostAddress;
	this->portNumber = portNumber;
}

ChatService::~ChatService()
{

}

void ChatService::ConnectSocket()
{
	// Resolve address and port
	ioService = std::make_shared<boost::asio::io_service>();
	resolver = std::make_shared<tcp::resolver>(*ioService);
	query = std::make_shared<tcp::resolver::query>(hostAddress, portNumber);
	endpointIterator = std::make_shared<tcp::resolver::iterator>(resolver->resolve(*query));
	socket = std::make_shared<tcp::socket>(*ioService);

	// Connect socket
	boost::asio::connect(*socket, *endpointIterator);
}
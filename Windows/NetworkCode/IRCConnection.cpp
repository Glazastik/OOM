#include "IRCConnection.h"
#include "DebugUtility.h"

IRCConnection::IRCConnection(std::shared_ptr<boost::asio::io_service> io_service,
	std::shared_ptr<std::vector<std::shared_ptr<Person>>> persons, std::string host, std::string port,
	std::string channel, std::string username, std::string nickname, std::string password)
{
	this->io_service = io_service;
	this->persons = persons;
	this->host = host;
	this->port = port;
	this->channel = channel;
	this->username = username;
	this->nickname = nickname;
	this->password = password;
}

IRCConnection::~IRCConnection()
{
}

void IRCConnection::Connect()
{
	std::cout << "TODO: Connect()" << std::endl;

	// Resolve address and port
	boost::asio::ip::tcp::resolver resolver(*io_service);
	boost::asio::ip::tcp::resolver::query query(host, boost::lexical_cast<std::string>(port));
	boost::asio::ip::tcp::resolver::iterator endpointIterator = resolver.resolve(query);

	// Connect socket
	boost::system::error_code error_code;
	boost::asio::connect(*tcp_socket, endpointIterator, error_code);
	if (error_code)
	{
		DebugUtility::DebugPrintError(error_code);
	}
}

void IRCConnection::CloseConnection()
{
	std::cout << "TODO: CloseConnection()" << std::endl;
}

void IRCConnection::SendChatMessage(std::string address, std::string message)
{
	std::cout << "TODO: SendChatMessage()" << std::endl;
}

// Private
void IRCConnection::StartAsyncReading()
{

}

void IRCConnection::ReadHandler(boost::system::error_code const& error, std::size_t bytes_transferred)
{

}

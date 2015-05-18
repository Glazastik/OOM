#pragma once
#include "boost/asio.hpp"
#include "Person.h"

class IRCConnection
{
public:
	IRCConnection(std::shared_ptr<boost::asio::io_service> io_service,
		std::shared_ptr<std::vector<std::shared_ptr<Person>>> persons, std::string host, std::string port,
		std::string channel, std::string username, std::string nickname, std::string password);
	~IRCConnection();
	void Connect();
	void CloseConnection();
	void SendChatMessage(std::string address, std::string message);
private:
	std::shared_ptr<boost::asio::io_service> io_service;
	std::shared_ptr<boost::asio::ip::tcp::socket> tcp_socket;
	std::shared_ptr<std::vector<std::shared_ptr<Person>>> persons;
	std::string host;
	std::string port;
	std::string channel;
	std::string username;
	std::string nickname;
	std::string password;

	static const int bufferSize;
	std::vector<char> readBuffer;
	size_t readBufferIndex;

	boost::asio::streambuf read_buffer;

	void Send(std::string const& msg);
	void StartAsyncReading();
	void ReadHandler(boost::system::error_code const& error, std::size_t bytes_transferred);
	std::string Parse(std::string input, std::string start, std::string ending);
	std::string pingResponse(std::string lineread);
};


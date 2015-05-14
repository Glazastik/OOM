#include "IRCConnection.h"
#include "DebugUtility.h"
#include "boost/bind.hpp"
#include "boost/regex.hpp"
#include "IRCMessage.h"

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

	Send(IRCMessage::authenticate(username, nickname, password));
	Send(IRCMessage::joinChannel(channel));
	StartAsyncReading();
}

void IRCConnection::CloseConnection()
{
	//boost::system::error_code error_code;
	//tcp_socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, error_code);
	//tcp_socket->close(error_code);
	DebugUtility::DebugPrint("TODO: IRCConnection::CloseConnection()");
}

void IRCConnection::SendChatMessage(std::string address, std::string message)
{
	std::string msg = IRCMessage::sendPrivateMessage(msg, channel, receiverNick);
}

// Private
void IRCConnection::Send(std::string const& msg)
{
	boost::system::error_code error_code;
	tcp_socket->write_some(boost::asio::buffer(msg), error_code);
	if (error_code)
	{
		DebugUtility::DebugPrintError(error_code);
	}
}

void IRCConnection::StartAsyncReading()
{
	/*
	boost::asio::async_read_until(socket, read_buffer, "\r\n",
		boost::bind(&IRCConnection::ReadHandler, this, _1, _2));
	*/
	DebugUtility::DebugPrint("TODO: IRCConnection::StartAsyncReading()");
}

void IRCConnection::ReadHandler(boost::system::error_code const& error_code, std::size_t bytes_transferred)
{
	if (error_code)
	{
		DebugUtility::DebugPrintError(error_code);
	}
	else
	{
		std::istream is(&read_buffer);
		std::string line;

		while (std::getline(is, line))
		{
			if (line.substr(0, 4) == "PING")
			{
				Send(IRCMessage::sendServerMsg(pingResponse(line)));
			}

			if (Parse(line, ":", "!") == IRCConnection::receiverNick)
			{
				std::cout << Parse(line, ":", "!") + ": " + Parse(line.substr(1, line.length()), ":", "") << std::endl;
				//recievedMessages.push_back(line); //parsa medelande innan?
			}
		}

		StartAsyncReading();
	}
}

std::string IRCConnection::Parse(std::string input, std::string start, std::string ending)
{
	std::string data(input), begin(start), end(ending);
	boost::regex r(begin + "(.*)" + end);
	boost::smatch result;

	if (boost::regex_search(data, result, r))
	{
		return result[1];
	}
	else
	{
		return "NotFound";
	}
}

std::string IRCConnection::pingResponse(std::string lineread)
{
	std::string server = Parse(lineread, ":", "");
	return "PONG " + server;
}
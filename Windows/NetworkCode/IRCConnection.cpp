#include "IRCConnection.h"
#include "DebugUtility.h"
#include "boost/bind.hpp"
#include "boost/regex.hpp"
#include "IRCMessageUtility.h"
#include "MessageBuffer.h"

const int IRCConnection::bufferSize = 4096;

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
	tcp_socket = std::make_shared<boost::asio::ip::tcp::socket>(*io_service);
	readBuffer.resize(bufferSize + 1);
	readBufferIndex = 0;
}

IRCConnection::~IRCConnection()
{
}

void IRCConnection::Connect()
{
	try
	{
		// Resolve address and port
		boost::asio::ip::tcp::resolver resolver(*io_service);
		boost::asio::ip::tcp::resolver::query query(host, boost::lexical_cast<std::string>(port));
		boost::asio::ip::tcp::resolver::iterator endpointIterator = resolver.resolve(query);

		// Connect socket
		boost::system::error_code error_code;
		boost::asio::connect(*tcp_socket, endpointIterator, error_code);
		Send(IRCMessageUtility::Authenticate(username, nickname, password));
		Send(IRCMessageUtility::JoinChannel(channel));
		StartAsyncReading();
	}
	catch (std::exception& exception)
	{
		DebugUtility::DebugPrintException(exception);
	}
}

void IRCConnection::CloseConnection()
{
	boost::system::error_code error_code;
	tcp_socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, error_code);
	tcp_socket->close(error_code);
}

void IRCConnection::SendChatMessage(std::string address, std::string message)
{
	std::string msg = IRCMessageUtility::SendPrivateMessage(message, address);
	DebugUtility::DebugPrint("IRC SENT MESSAGE: " + msg + "");
	Send(msg);
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
	tcp_socket->async_read_some(boost::asio::buffer(&readBuffer[readBufferIndex], bufferSize - readBufferIndex),
		boost::bind(&IRCConnection::ReadHandler, this, _1, _2));
}

void IRCConnection::ReadHandler(boost::system::error_code const& error_code, std::size_t bytes_transferred)
{
	if (error_code)
	{
		DebugUtility::DebugPrintError(error_code);
	}
	else
	{
		readBufferIndex += bytes_transferred;

		std::string readStr;
		readStr += readBuffer.data();
		if (readStr.find(":") != std::string::npos && readStr.find("!") != std::string::npos)
		{
			readBuffer[bytes_transferred] = '\0';

			if (readStr.substr(0, 4) == "PING")
			{
				Send(IRCMessageUtility::SendServerMsg(pingResponse(readStr)));
			}

			std::string address = Parse(readStr, ":", "!");
			bool hasAddress = false;
			std::shared_ptr<Account> account = NULL;
			for (std::vector<std::shared_ptr<Person>>::iterator it = persons->begin(); it != persons->end(); ++it)
			{
				std::shared_ptr<Person> person = *it;
				std::vector<int> accountIds = person->GetAccountIds();
				for (std::vector<int>::iterator idIt = accountIds.begin(); idIt != accountIds.end(); ++idIt)
				{
					int id = *idIt;
					std::shared_ptr<Account> acc = person->GetAccount(id);
					if (acc->GetAddress().compare(address) == 0)
					{
						hasAddress = true;
						account = acc;
					}
				}
			}
			if (hasAddress)
			{
				std::stringstream stream;
				stream << Parse(readStr, ":", "!") << ": " << Parse(readStr.substr(1, readStr.length()), ":", "") << std::endl;
				DebugUtility::DebugPrint(stream.str());

				std::string payload = Parse(readStr.substr(1, readStr.length()), ":", "");
				std::shared_ptr<Message> message = std::make_shared<Message>(account->GetId(), payload);
				MessageBuffer::AddMessage(message);
			}

			// Buffer cleanup
			std::fill_n(readBuffer.begin(), readBuffer.size() - 1, '\0');
			readBufferIndex = 0;
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
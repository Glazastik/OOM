#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "Person.h"
#include <vector>

class XmppConnection
{
public:
	XmppConnection(std::shared_ptr<boost::asio::io_service> io_service, std::string hostName, int portNumber, std::string authid, std::string password, 
		std::shared_ptr<std::vector<std::shared_ptr<Person>>> persons);
	~XmppConnection();
	void Connect();
	void CloseConnection();
	void SendChatMessage(std::string address, std::string message);
protected:
	std::string hostName;
	int portNumber;
	std::string authid;
	std::string password;
	std::string jid;
	std::shared_ptr<std::vector<std::shared_ptr<Person>>> persons;
	int nextId;
	std::shared_ptr<boost::asio::io_service> io_service;
	std::shared_ptr<boost::asio::ip::tcp::socket> tcp_socket;
	std::shared_ptr<boost::asio::ssl::context> ssl_context;
	std::shared_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket&>> ssl_socket;

	void TCPConnect();
	void SSLHandshake();
	std::string TCPReadUntil(std::string compareStr);
	std::string SSLReadUntil(std::string compareStr);
	void TCPWriteSome(std::string streamStr);
	void SSLWriteSome(std::string streamStr);
	void StartAsyncReading();
	void ReadHandler(const boost::system::error_code& error_code, size_t bytes_transfered);

	std::string ParseElement(std::string xml, std::string elementType);
private:
	static const int bufferSize;
	std::vector<char> readBuffer;
	size_t readBufferIndex;
};


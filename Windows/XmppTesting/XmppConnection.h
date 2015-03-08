#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

class XmppConnection
{
public:
	XmppConnection(std::shared_ptr<boost::asio::io_service> io_service, std::string hostName, int portNumber);
	~XmppConnection();
	void Connect();
	void CloseConnection();
protected:
	std::string hostName;
	int portNumber;
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

	void DebugPrint(std::string debugStr);
	void DebugPrintRead(std::string readStr);
	void DebugPrintWrite(std::string writeStr);
	void DebugPrintError(boost::system::error_code error_code);
	void DebugPrintException(std::exception& exception);
private:
	static const int bufferSize;
};


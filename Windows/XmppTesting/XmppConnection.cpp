#include "XmppConnection.h"
#include <boost/lexical_cast.hpp>

const int XmppConnection::bufferSize = 1024;

// Public
XmppConnection::XmppConnection(std::shared_ptr<boost::asio::io_service> io_service, std::string hostName, int portNumber)
{
	this->io_service = io_service;
	this->hostName = hostName;
	this->portNumber = portNumber;
	tcp_socket = std::make_shared<boost::asio::ip::tcp::socket>(*io_service);
	ssl_context = std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::sslv23);
	ssl_context->set_default_verify_paths();
	ssl_socket = std::make_shared<boost::asio::ssl::stream<boost::asio::ip::tcp::socket&>>(*tcp_socket, *ssl_context);
	ssl_socket->set_verify_mode(boost::asio::ssl::verify_peer);
	ssl_socket->set_verify_callback(boost::asio::ssl::rfc2818_verification(hostName));
}

XmppConnection::~XmppConnection()
{
}

void XmppConnection::Connect()
{
	try {
		// Connect TCP socket
		TCPConnect();

		std::stringstream stream;
		std::string readStr;

		// Initiate xml stream to server
		stream << "<?xmlversion='1.0'?>" << std::endl;
		stream << "<stream:stream" << std::endl;
		stream << "to='msp.se'" << std::endl;
		stream << "xmlns='jabber:client'" << std::endl;
		stream << "xmlns:stream='http://etherx.jabber.org/streams'" << std::endl;
		stream << "version='1.0'>" << std::endl;

		tcp_socket->write_some(boost::asio::buffer(stream.str()));
		DebugPrintWrite(stream.str());

		// Read server response
		readStr = TCPReadUntil("</stream:features>");
		DebugPrintRead(readStr);

		// Send STARTTLS
		stream.str("");
		stream.clear();
		stream << "<starttls" << std::endl;
		stream << "xmlns='urn:ietf:params:xml:ns:xmpp-tls'/>" << std::endl;

		tcp_socket->write_some(boost::asio::buffer(stream.str()));
		DebugPrintWrite(stream.str());

		// Read server response
		readStr = TCPReadUntil("<proceed xmlns=\"urn:ietf:params:xml:ns:xmpp-tls\"/>");
		DebugPrintRead(readStr);

		// Perform SSL Handshake
		SSLHandshake();
	}
	catch (std::exception& exception)
	{
		DebugPrintException(exception);
	}
}

void XmppConnection::CloseConnection()
{
	boost::system::error_code error_code;
	tcp_socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, error_code);
	if (error_code)
	{
		DebugPrintError(error_code);
	}
	tcp_socket->close();
}

// Protected
void XmppConnection::TCPConnect()
{
	// Resolve address and port
	boost::asio::ip::tcp::resolver resolver(*io_service);
	boost::asio::ip::tcp::resolver::query query(hostName, boost::lexical_cast<std::string>(portNumber));
	boost::asio::ip::tcp::resolver::iterator endpointIterator = resolver.resolve(query);

	// Connect socket
	DebugPrint("CONNECTING TO: " + hostName + ":" + boost::lexical_cast<std::string>(portNumber)+"\n");
	boost::system::error_code error_code;
	boost::asio::connect(*tcp_socket, endpointIterator, error_code);
	if (error_code)
	{
		DebugPrintError(error_code);
	}
}

void XmppConnection::SSLHandshake()
{
	DebugPrint("PERFORMING SSL HANDSHAKE");
	boost::system::error_code error_code;
	ssl_socket->handshake(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::client, error_code);
	if (error_code)
	{
		DebugPrintError(error_code);
	}
}

std::string XmppConnection::TCPReadUntil(std::string compareStr)
{
	boost::array<char, bufferSize + 1> readBuffer;
	boost::system::error_code error_code;
	std::string readStr;
	std::string subStr;

	while (subStr.compare(compareStr) != 0)
	{
		size_t responseLength = tcp_socket->read_some(boost::asio::buffer(readBuffer, bufferSize), error_code);
		if (error_code)
		{
			DebugPrintError(error_code);
			break;
		}

		readBuffer[responseLength] = '\0';
		readStr += readBuffer.data();
		subStr = readStr.substr(readStr.length() - compareStr.length());
	}

	return readStr;
}

std::string XmppConnection::SSLReadUntil(std::string compareStr)
{
	boost::array<char, bufferSize + 1> readBuffer;
	boost::system::error_code error_code;
	std::string readStr;
	std::string subStr;

	while (subStr.compare(compareStr) != 0)
	{
		size_t responseLength = ssl_socket->read_some(boost::asio::buffer(readBuffer, bufferSize), error_code);
		if (error_code)
		{
			DebugPrintError(error_code);
			break;
		}

		readBuffer[responseLength] = '\0';
		readStr += readBuffer.data();
		subStr = readStr.substr(readStr.length() - compareStr.length());
	}

	return readStr;
}

void XmppConnection::DebugPrint(std::string debugStr)
{
	std::cout << debugStr << std::endl;
}

void XmppConnection::DebugPrintRead(std::string readStr)
{
	std::stringstream stream;
	stream << "---SERVER---\n" << readStr << "\n" << "------------" << "\n";
	DebugPrint(stream.str());
}

void XmppConnection::DebugPrintWrite(std::string writeStr)
{
	std::stringstream stream;
	stream << "---CLIENT---\n" << writeStr << "------------" << "\n";
	DebugPrint(stream.str());
}

void XmppConnection::DebugPrintError(boost::system::error_code error_code)
{
	std::stringstream stream;
	stream << "ERROR CODE: " << error_code << " - \"" << error_code.message() << "\"\n";
	DebugPrint(stream.str());
}

void XmppConnection::DebugPrintException(std::exception& exception)
{
	std::stringstream stream;
	stream << "Exception: " << exception.what();
	DebugPrint(stream.str());
}
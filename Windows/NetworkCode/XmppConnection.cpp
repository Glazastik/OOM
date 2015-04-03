#include "XmppConnection.h"
#include <boost/lexical_cast.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>
#include "Base64.h"
#include "DebugBuffer.h"
#include "boost/log/trivial.hpp"

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

	/*
	* Using verify_none for the time being since I don't want to mess with certificate verification right now.
	*/
	ssl_socket->set_verify_mode(boost::asio::ssl::verify_none);
	//ssl_socket->set_verify_mode(boost::asio::ssl::verify_peer);

	ssl_socket->set_verify_callback(boost::asio::ssl::rfc2818_verification(hostName));
}

XmppConnection::~XmppConnection()
{
}

void XmppConnection::Connect()
{
	try {
		// Connect TCP socket
		DebugPrint("CONNECTING TO: " + hostName + ":" + boost::lexical_cast<std::string>(portNumber)+"\n");
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

		TCPWriteSome(stream.str());
		DebugPrintWrite(stream.str());
		
		// Read server response
		readStr = TCPReadUntil("</stream:features>");
		DebugPrintRead(readStr);

		// Send STARTTLS
		stream.str("");
		stream.clear();
		stream << "<starttls" << std::endl;
		stream << "xmlns='urn:ietf:params:xml:ns:xmpp-tls'/>" << std::endl;

		TCPWriteSome(stream.str());
		DebugPrintWrite(stream.str());

		// Read server response
		readStr = TCPReadUntil("<proceed xmlns=\"urn:ietf:params:xml:ns:xmpp-tls\"/>");
		DebugPrintRead(readStr);
		
		// Perform SSL Handshake
		DebugPrint("PERFORMING SSL HANDSHAKE\n");
		SSLHandshake();

		// Initiate xml stream to server
		stream.str("");
		stream.clear();
		stream << "<?xmlversion='1.0'?>" << std::endl;
		stream << "<stream:stream" << std::endl;
		stream << "to='msp.se'" << std::endl;
		stream << "xmlns='jabber:client'" << std::endl;
		stream << "xmlns:stream='http://etherx.jabber.org/streams'" << std::endl;
		stream << "version='1.0'>" << std::endl;

		SSLWriteSome(stream.str());
		DebugPrintWrite(stream.str());

		// Read server response
		readStr = SSLReadUntil("</stream:features>");
		DebugPrintRead(readStr);
		
		// SASL authentication
		std::string authzid = "";
		std::string authid = "kandidattest2015@gmail.com";
		std::string password = "test2015";

		char buffer[1024];
		int offset = 0;
		memcpy(buffer + offset, authzid.c_str(), authzid.length());
		offset += authzid.length();
		buffer[offset++] = 0;

		memcpy(buffer + offset, authid.c_str(), authid.length());
		offset += authid.length();
		buffer[offset++] = 0;

		memcpy(buffer + offset, password.c_str(), password.length());
		offset += password.length();

		std::string encodedStr = Base64::Encode(buffer, offset);

		stream.str("");
		stream.clear();
		stream << "<auth xmlns='urn:ietf:params:xml:ns:xmpp-sasl' mechanism='PLAIN'>";
		stream << encodedStr;
		stream << "</auth>";

		SSLWriteSome(stream.str());
		DebugPrintWrite(stream.str() + "\n");

		// Read server response
		readStr = SSLReadUntil(">");
		DebugPrintRead(readStr);
		
		// Initiate xml stream to server
		stream.str("");
		stream.clear();
		stream << "<?xmlversion='1.0'?>" << std::endl;
		stream << "<stream:stream" << std::endl;
		stream << "to='msp.se'" << std::endl;
		stream << "xmlns='jabber:client'" << std::endl;
		stream << "xmlns:stream='http://etherx.jabber.org/streams'" << std::endl;
		stream << "version='1.0'>" << std::endl;

		SSLWriteSome(stream.str());
		DebugPrintWrite(stream.str());

		// Read server response
		readStr = SSLReadUntil("</stream:features>");
		DebugPrintRead(readStr);
		
		// Ask server to generate resource identifier
		stream.str("");
		stream.clear();
		stream << "<iq id='1' type='set'>" << std::endl;
		stream << "<bind xmlns='urn:ietf:params:xml:ns:xmpp-bind'/>" << std::endl;
		stream << "</iq>" << std::endl;

		SSLWriteSome(stream.str());
		DebugPrintWrite(stream.str());

		// Read server response
		readStr = SSLReadUntil("</iq>");
		DebugPrintRead(readStr);

		// Parse resource identifier
		std::string jid = ParseElement(readStr, "<jid>");
		DebugPrint("JID: " + jid + "\n");
		
		// Session
		stream.str("");
		stream.clear();
		stream << "<iq type='set' id='2'>" << std::endl;
		stream << "<session xmlns='urn:ietf:params:xml:ns:xmpp-session'/>" << std::endl;
		stream << "</iq>" << std::endl;

		SSLWriteSome(stream.str());
		DebugPrintWrite(stream.str());

		// Read server response
		readStr = SSLReadUntil(">");
		DebugPrintRead(readStr);
		
		// Disco items
		stream.str("");
		stream.clear();
		stream << "<iq type='get' id='3' to='gmail.com'>" << std::endl;
		stream << "<query xmlns='http://jabber.org/protocol/disco#items'/>" << std::endl;
		stream << "</iq>" << std::endl;

		SSLWriteSome(stream.str());
		DebugPrintWrite(stream.str());

		// Read server response
		readStr = SSLReadUntil("</iq>");
		DebugPrintRead(readStr);
		
		// Disco info
		stream.str("");
		stream.clear();
		stream << "<iq type='get' id='4' to='gmail.com'>" << std::endl;
		stream << "<query xmlns='http://jabber.org/protocol/disco#info'/>" << std::endl;
		stream << "</iq>" << std::endl;

		SSLWriteSome(stream.str());
		DebugPrintWrite(stream.str());

		// Read server response
		readStr = SSLReadUntil("</iq>");
		DebugPrintRead(readStr);
		
		// Get roster
		stream.str("");
		stream.clear();
		stream << "<iq type='get' id='5'>" << std::endl;
		stream << "<query xmlns='jabber:iq:roster' ext='2'/>" << std::endl;
		stream << "</iq>" << std::endl;

		SSLWriteSome(stream.str());
		DebugPrintWrite(stream.str());

		// Read server response
		readStr = SSLReadUntil("</iq>");
		DebugPrintRead(readStr);
		
		// Send a message
		stream.str("");
		stream.clear();
		stream << "<message from='" << jid << "'" << std::endl;
		stream << "id='2'" << std::endl;
		stream << "to='1qb37r9krc35d08l0pdn0m4c8m@public.talk.google.com'" << std::endl;
		stream << "type='chat'" << std::endl;
		stream << "xml:lang='en'>" << std::endl;
		stream << "<body>TEST HEJ</body>" << std::endl;
		stream << "</message>" << std::endl;

		SSLWriteSome(stream.str());
		DebugPrintWrite(stream.str());

		// Read server response
		//readStr = SSLReadUntil(">");
		//DebugPrintRead(readStr);
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
	boost::system::error_code error_code;
	boost::asio::connect(*tcp_socket, endpointIterator, error_code);
	if (error_code)
	{
		DebugPrintError(error_code);
	}
}

void XmppConnection::SSLHandshake()
{
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

void XmppConnection::TCPWriteSome(std::string streamStr)
{
	boost::system::error_code error_code;
	tcp_socket->write_some(boost::asio::buffer(streamStr), error_code);
	if (error_code)
	{
		DebugPrintError(error_code);
	}
}

void XmppConnection::SSLWriteSome(std::string streamStr)
{
	boost::system::error_code error_code;
	ssl_socket->write_some(boost::asio::buffer(streamStr), error_code);
	if (error_code)
	{
		DebugPrintError(error_code);
	}
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

std::string XmppConnection::ParseElement(std::string xml, std::string elementType)
{
	std::string element;
	size_t typeStartPos = xml.find(elementType);
	elementType.insert(1, "/");
	size_t typeEndPos = xml.find(elementType);
	if ((typeStartPos != std::string::npos) && (typeEndPos != std::string::npos))
	{
		size_t elementStartPos = xml.find(">", typeStartPos);
		element = xml.substr(elementStartPos + 1, typeEndPos - elementStartPos - 1);
	}
	return element;
}

void XmppConnection::DebugPrint(std::string debugStr)
{
	BOOST_LOG_TRIVIAL(debug) << "\n" << debugStr;
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
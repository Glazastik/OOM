#include "XmppConnection.h"
#include <boost/lexical_cast.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>
#include "Base64.h"
#include "MessageBuffer.h"
#include "Message.h"
#include "boost/bind.hpp"
#include <algorithm>
#include "DebugUtility.h"

const int XmppConnection::bufferSize = 4096;

// Public
XmppConnection::XmppConnection(std::shared_ptr<boost::asio::io_service> io_service, std::string hostName, int portNumber, std::string authid, std::string password,
	std::shared_ptr<std::vector<std::shared_ptr<Person>>> persons)
{
	this->io_service = io_service;
	this->hostName = hostName;
	this->portNumber = portNumber;
	this->authid = authid;
	this->password = password;
	this->persons = persons;
	readBuffer.resize(bufferSize + 1);
	readBufferIndex = 0;
	nextId = 1;
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
	try 
	{
		// Connect TCP socket
		DebugUtility::DebugPrint("CONNECTING TO: " + hostName + ":" + boost::lexical_cast<std::string>(portNumber)+"\n");
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
		DebugUtility::DebugPrintWrite(stream.str());
		
		// Read server response
		readStr = TCPReadUntil("</stream:features>");
		DebugUtility::DebugPrintRead(readStr);

		// Send STARTTLS
		stream.str("");
		stream.clear();
		stream << "<starttls" << std::endl;
		stream << "xmlns='urn:ietf:params:xml:ns:xmpp-tls'/>" << std::endl;

		TCPWriteSome(stream.str());
		DebugUtility::DebugPrintWrite(stream.str());

		// Read server response
		readStr = TCPReadUntil("<proceed xmlns=\"urn:ietf:params:xml:ns:xmpp-tls\"/>");
		DebugUtility::DebugPrintRead(readStr);
		
		// Perform SSL Handshake
		DebugUtility::DebugPrint("PERFORMING SSL HANDSHAKE\n");
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
		DebugUtility::DebugPrintWrite(stream.str());

		// Read server response
		readStr = SSLReadUntil("</stream:features>");
		DebugUtility::DebugPrintRead(readStr);
		
		// SASL authentication
		std::string authzid = "";

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
		DebugUtility::DebugPrintWrite(stream.str() + "\n");

		// Read server response
		readStr = SSLReadUntil(">");
		DebugUtility::DebugPrintRead(readStr);
		
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
		DebugUtility::DebugPrintWrite(stream.str());

		// Read server response
		readStr = SSLReadUntil("</stream:features>");
		DebugUtility::DebugPrintRead(readStr);
		
		// Ask server to generate resource identifier
		stream.str("");
		stream.clear();
		stream << "<iq id='" << nextId << "' type='set'>" << std::endl;
		stream << "<bind xmlns='urn:ietf:params:xml:ns:xmpp-bind'/>" << std::endl;
		stream << "</iq>" << std::endl;
		nextId++;

		SSLWriteSome(stream.str());
		DebugUtility::DebugPrintWrite(stream.str());

		// Read server response
		readStr = SSLReadUntil("</iq>");
		DebugUtility::DebugPrintRead(readStr);

		// Parse resource identifier
		jid = ParseElement(readStr, "<jid>");
		DebugUtility::DebugPrint("JID: " + jid + "\n");
		
		// Session
		stream.str("");
		stream.clear();
		stream << "<iq type='set' id='" << nextId << "'>" << std::endl;
		stream << "<session xmlns='urn:ietf:params:xml:ns:xmpp-session'/>" << std::endl;
		stream << "</iq>" << std::endl;
		nextId++;

		SSLWriteSome(stream.str());
		DebugUtility::DebugPrintWrite(stream.str());

		// Read server response
		readStr = SSLReadUntil(">");
		DebugUtility::DebugPrintRead(readStr);
		
		// Disco items
		stream.str("");
		stream.clear();
		stream << "<iq type='get' id='" << nextId << "' to='gmail.com'>" << std::endl;
		stream << "<query xmlns='http://jabber.org/protocol/disco#items'/>" << std::endl;
		stream << "</iq>" << std::endl;
		nextId++;

		SSLWriteSome(stream.str());
		DebugUtility::DebugPrintWrite(stream.str());

		// Read server response
		readStr = SSLReadUntil("</iq>");
		DebugUtility::DebugPrintRead(readStr);
		
		// Disco info
		stream.str("");
		stream.clear();
		stream << "<iq type='get' id='" << nextId << "' to='gmail.com'>" << std::endl;
		stream << "<query xmlns='http://jabber.org/protocol/disco#info'/>" << std::endl;
		stream << "</iq>" << std::endl;
		nextId++;

		SSLWriteSome(stream.str());
		DebugUtility::DebugPrintWrite(stream.str());

		// Read server response
		readStr = SSLReadUntil("</iq>");
		DebugUtility::DebugPrintRead(readStr);
		
		// Get roster
		stream.str("");
		stream.clear();
		stream << "<iq type='get' id='" << nextId << "'>" << std::endl;
		stream << "<query xmlns='jabber:iq:roster' ext='2'/>" << std::endl;
		stream << "</iq>" << std::endl;
		nextId++;

		SSLWriteSome(stream.str());
		DebugUtility::DebugPrintWrite(stream.str());

		// Read server response
		readStr = SSLReadUntil("</iq>");
		DebugUtility::DebugPrintRead(readStr);

		// Presence
		stream.str("");
		stream.clear();
		stream << "<presence>" << std::endl;
		stream << "<priority>'1'</priority>" << std::endl;
		stream << "</presence>" << std::endl;

		SSLWriteSome(stream.str());
		DebugUtility::DebugPrintWrite(stream.str());
		
		// Send a message
		//SendChatMessage("1qb37r9krc35d08l0pdn0m4c8m@public.talk.google.com", "TEST");

		// Read server response
		/*readStr = SSLReadUntil(">");
		DebugPrintRead(readStr);
		std::string payload = ParseElement(readStr, "<body>");
		int accountId = 0;
		std::shared_ptr<Message> message = std::make_shared<Message>(accountId, payload);
		MessageBuffer::AddMessage(message);*/

		StartAsyncReading();
	}
	catch (std::exception& exception)
	{
		DebugUtility::DebugPrintException(exception);
	}
}

void XmppConnection::CloseConnection()
{
	boost::system::error_code error_code;
	tcp_socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, error_code);
	tcp_socket->close(error_code);
}

void XmppConnection::SendChatMessage(std::string address, std::string message)
{
	std::stringstream stream;
	stream << "<message from='" << jid << "'" << std::endl;
	stream << "id='" << nextId << "'" << std::endl;
	stream << "to='" << address << "'" << std::endl;
	stream << "type='chat'" << std::endl;
	stream << "xml:lang='en'>" << std::endl;
	stream << "<body>" << message << "</body>" << std::endl;
	stream << "</message>" << std::endl;
	nextId++;

	SSLWriteSome(stream.str());
	DebugUtility::DebugPrintWrite(stream.str());
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
		DebugUtility::DebugPrintError(error_code);
	}
}

void XmppConnection::SSLHandshake()
{
	boost::system::error_code error_code;
	ssl_socket->handshake(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::client, error_code);
	if (error_code)
	{
		DebugUtility::DebugPrintError(error_code);
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
			DebugUtility::DebugPrintError(error_code);
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
		DebugUtility::DebugPrintError(error_code);
	}
}

void XmppConnection::SSLWriteSome(std::string streamStr)
{
	boost::system::error_code error_code;
	ssl_socket->write_some(boost::asio::buffer(streamStr), error_code);
	if (error_code)
	{
		DebugUtility::DebugPrintError(error_code);
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
			DebugUtility::DebugPrintError(error_code);
			break;
		}

		readBuffer[responseLength] = '\0';
		readStr += readBuffer.data();
		subStr = readStr.substr(readStr.length() - compareStr.length());
	}

	return readStr;
}

void XmppConnection::StartAsyncReading()
{
	ssl_socket->async_read_some(boost::asio::buffer(&readBuffer[readBufferIndex], bufferSize - readBufferIndex),
		boost::bind(&XmppConnection::ReadHandler, this, _1, _2));
}

void XmppConnection::ReadHandler(const boost::system::error_code& error_code, size_t bytes_transfered)
{
	if (error_code)
	{
		DebugUtility::DebugPrintError(error_code);
	}
	else
	{
		readBufferIndex += bytes_transfered;

		std::string readStr;
		readStr += readBuffer.data();
		if (readStr.find("</message>") != std::string::npos)
		{
			readBuffer[bytes_transfered] = '\0';

			// Parse address
			int startPos = readStr.find("\"") + 1;
			int length = readStr.find("\/") - startPos;
			std::string address = readStr.substr(startPos, length);

			std::string payload = ParseElement(readStr, "<body>");
			
			// Find account with correct address
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
						account = acc;
					}
				}
			}
			if (account == NULL)
			{
				DebugUtility::DebugPrint("Received message from unknown account address.");
			}
			else
			{
				std::shared_ptr<Message> message = std::make_shared<Message>(account->GetId(), payload);
				MessageBuffer::AddMessage(message);
			}

			// Buffer cleanup
			std::fill_n(readBuffer.begin(), readBuffer.size() - 1, '\0');
			readBufferIndex = 0;
		}

		DebugUtility::DebugPrint(readStr);

		StartAsyncReading();
	}
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

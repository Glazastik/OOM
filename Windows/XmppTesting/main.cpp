#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <sstream>

using boost::asio::ip::tcp;

const int bufferSize = 1024;

std::string Read_Until(std::shared_ptr<tcp::socket> socket, std::string compareStr)
{
	boost::array<char, bufferSize + 1> responseBuffer;
	boost::system::error_code errorCode;
	std::string responseStr;
	std::string subStr;

	while (subStr.compare(compareStr) != 0)
	{
		size_t responseLength = socket->read_some(boost::asio::buffer(responseBuffer, 1024), errorCode);
		if (errorCode)
		{
			std::cout << "ERROR CODE: " << errorCode << " - \"" << errorCode.message() << "\"\n" << std::endl;
			break;
		}

		responseBuffer[responseLength] = '\0';
		responseStr += responseBuffer.data();
		subStr = responseStr.substr(responseStr.length() - compareStr.length());
	}

	return responseStr;
}

void End_Connection(std::shared_ptr<tcp::socket> socket)
{
	boost::system::error_code error_code;
	socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, error_code);
	socket->close();
}

int main(int argc, char* args[])
{
	try {
		//std::string hostAddress = "64.233.165.125";
		std::string hostAddress = "xmpp.l.google.com";
		std::string portNumber = "5222";

		// Resolve address and port
		boost::asio::io_service ioService;
		tcp::resolver resolver(ioService);
		tcp::resolver::query query(hostAddress, portNumber);
		tcp::resolver::iterator endpointIterator = resolver.resolve(query);
		std::shared_ptr<tcp::socket> socket = std::make_shared<tcp::socket>(ioService);

		// Connect socket
		std::cout << "Connecting to: " << hostAddress << " " << portNumber << "\n" << std::endl;
		boost::asio::connect(*socket, endpointIterator);

		std::stringstream stream;
		std::string responseStr;

		// Initiate xml stream to server
		stream << "<?xmlversion='1.0'?>" << std::endl;
		stream << "<stream:stream" << std::endl;
		stream << "to='msp.se'" << std::endl;
		stream << "xmlns='jabber:client'" << std::endl;
		stream << "xmlns:stream='http://etherx.jabber.org/streams'" << std::endl;
		stream << "version='1.0'>" << std::endl;

		socket->write_some(boost::asio::buffer(stream.str()));
		std::cout << "---CLIENT---\n" << stream.str() << std::endl;

		// Read server response
		responseStr = Read_Until(socket, "</stream:features>");
		std::cout << "---SERVER---\n" << responseStr << "\n" << std::endl;

		// Send STARTTLS
		stream.str("");
		stream.clear();
		stream << "<starttls" << std::endl;
		stream << "xmlns='urn:ietf:params:xml:ns:xmpp-tls'/>" << std::endl;

		socket->write_some(boost::asio::buffer(stream.str()));
		std::cout << "---CLIENT---\n" << stream.str() << std::endl;

		// Read server response
		responseStr = Read_Until(socket, "<proceed xmlns=\"urn:ietf:params:xml:ns:xmpp-tls\"/>");
		std::cout << "---SERVER---\n" << responseStr << "\n" << std::endl;

		End_Connection(socket);
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "Press any button to exit...";
	std::cin.get();
	return 0;
}
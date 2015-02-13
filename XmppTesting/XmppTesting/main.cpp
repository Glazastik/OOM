#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

static const int bufferSize = 1024;
static const std::string exit_command = "exit";

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
		tcp::socket socket(ioService);

		// Connect socket
		std::cout << "Connecting to: " << hostAddress << " " << portNumber << std::endl;
		boost::asio::connect(socket, endpointIterator);

		std::string message;
		boost::array<char, 1024> responseBuffer;
		boost::system::error_code errorCode;
		size_t responseLength;

		// Initiate xml stream to server
		message = "<stream:stream"
			" to='msp.se'"
			" xmlns='jabber:client'"
			" xmlns:stream='http://etherx.jabber.org/streams'"
			" version='1.0'"
			">";
		socket.write_some(boost::asio::buffer(message));

		// Read server response
		responseLength = socket.read_some(boost::asio::buffer(responseBuffer), errorCode);
		std::string responseStr(responseBuffer.begin(), responseBuffer.end());
		std::cout << responseStr << std::endl;

		socket.close();
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "Press any button to exit...";
	std::cin.get();
	return 0;
}
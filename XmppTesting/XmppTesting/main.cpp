#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <sstream>

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
		std::cout << "Connecting to: " << hostAddress << " " << portNumber << "\n" << std::endl;
		boost::asio::connect(socket, endpointIterator);

		std::string message;
		boost::array<char, 1024> responseBuffer;
		boost::system::error_code errorCode;
		size_t responseLength;

		// Initiate xml stream to server
		std::stringstream stream;
		stream << "<?xmlversion='1.0'?>" << std::endl;
		stream << "<stream:stream" << std::endl;
		stream << "to='msp.se'" << std::endl;
		stream << "xmlns='jabber:client'" << std::endl;
		stream << "xmlns:stream='http://etherx.jabber.org/streams'" << std::endl;
		stream << "version='1.0'>" << std::endl;

		std::cout << "---CLIENT---\n" << stream.str() << std::endl;
		socket.write_some(boost::asio::buffer(stream.str()));

		// Read server response
		responseLength = socket.read_some(boost::asio::buffer(responseBuffer), errorCode);
		std::string responseStr1(responseBuffer.begin(), responseBuffer.end());
		std::cout << "---SERVER---\n" << responseStr1 << std::endl;

		// Read server response
		responseLength = socket.read_some(boost::asio::buffer(responseBuffer), errorCode);
		std::string responseStr2(responseBuffer.begin(), responseBuffer.end());
		std::cout << "---SERVER---\n" << responseStr2 << std::endl;

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
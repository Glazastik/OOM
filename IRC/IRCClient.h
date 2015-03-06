#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <string>

class IRCConnection
{
public:
	IRCConnection(std::string const& host, std::string const&port);
	
	~IRCConnection();
	
	void connect(std::string password, std::string user, std::string nickname, std::string channel);
	void send(std::string const& message);



private:
	void do_connect();
	void do_send(std::string const& message);

	void start_read();
	void do_read();
	
	void handle_read(const boost::system::error_code& error, std::size_t bytes_transferred);

	void on_connect();

	std::string hostname;
	std::string port;

	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket socket;

	boost::thread read_thread;

	boost::asio::streambuf read_buffer;
	
};


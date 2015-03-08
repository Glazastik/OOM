#include "IRCClient.h"




static const std::string servername = "irc.rizon.net";
static const std::string port = "6667";

IRCConnection::IRCConnection(std::string const& host, std::string const&port):hostname(host), port(port), socket(io_service){
	boost::bind(&IRCConnection::on_connect, this);
}

IRCConnection::~IRCConnection(){
	socket.close();
	read_thread.join();
}

void IRCConnection::handle_read(boost::system::error_code const& error,
	std::size_t bytes_transferred){
	std::istream is(&read_buffer);
	std::string line;

	
	while (std::getline(is, line))
	{
		if (line == "PING")
			send("PONG");
		std::cout << line << std::endl;
	}

	do_read();
}
void IRCConnection::do_read(){
	boost::system::error_code error_code;
	try
	{
		boost::asio::async_read_until(socket, read_buffer, "\r\n",
			boost::bind(&IRCConnection::handle_read, this, _1, _2));
	}
	catch (boost::system::system_error& error)
	{
		std::cout << error.code() << std::endl;
	}
}


void IRCConnection::start_read(){
	do_read();
	read_thread = boost::thread(boost::bind(&boost::asio::io_service::run, &io_service));
}

void IRCConnection::on_connect(){
	start_read();
}

void IRCConnection::send(std::string const& msg)
{
	try
	{
		boost::asio::write(socket,
			boost::asio::buffer(msg.data(), msg.size()),
			boost::asio::transfer_all());
	}
	catch (boost::system::system_error& error)
	{
		std::cout << error.code() << std::endl;
		return;
	}
}

void IRCConnection::connect(std::string password, std::string username, std::string nickname, std::string channel){
	using namespace boost::asio::ip;

	boost::system::error_code error_code;
	try
	{
		boost::asio::ip::tcp::resolver           resolver(io_service);
		boost::asio::ip::tcp::resolver::query    query(hostname, port);
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		boost::asio::connect(socket, endpoint_iterator);
	}
	catch (boost::system::system_error& error)
	{
		std::cerr << error.code();
		return;
	}

	std::string pass = "PASS "+password+"\r\n";
	std::string nick = "NICK "+nickname+"\r\n";
	std::string user = "USER "+username+" testhost 127.0.0.1 :"+username+"\r\n";
	std::string join = "JOIN #"+channel+"\r\n";
	send(pass);
	send(nick);
	send(user);
	send(join);
	on_connect();
}


void on_error(boost::system::error_code error){
	std::cerr << "ERROR: " << error << std::endl;
}

int main()
{
	// Setup connection
	IRCConnection irc(servername, port);
	


	// Connect
	irc.connect("testpw","test123","test123","chat");

	std::string msg;
	
	while (getline(std::cin, msg))
	{
		msg = "PRIVMSG #chat "+ msg + "\r\n";
		irc.send(msg);
	}
}
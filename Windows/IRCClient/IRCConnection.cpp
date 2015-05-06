#include "IRCConnection.h"
#include <boost/regex.hpp>



IRCConnection::IRCConnection(std::string const& host, std::string const&port) :hostname(host), port(port), socket(io_service){
	boost::bind(&IRCConnection::on_connect, this);
}

IRCConnection::~IRCConnection(){
	socket.close();
	read_thread.join();
}

std::string parse(std::string input, std::string start, std::string ending){
	std::string data(input), begin(start), end(ending);
	boost::regex r(begin + "(.*)" + end);
	boost::smatch result;

	if (boost::regex_search(data, result, r)){
		return result[1];
	}

	else{
		return "NotFound";
	}
}

std::string pingResponse(std::string lineread){
	std::string server = parse(lineread, ":", "");
	return "PONG " + server;
}

void IRCConnection::handle_read(boost::system::error_code const& error,
	std::size_t bytes_transferred){

	std::istream is(&read_buffer);
	std::string line;

	while (std::getline(is, line))
	{
		if (line.substr(0, 4) == "PING"){
			send(message::sendServerMsg(pingResponse(line)));
		}

		if (parse(line, ":", "!") == IRCConnection::recieverNick){ //kollar om avsändaren är rätt person och lägger meddelandet i lista av mottagna meddelanden.
			std::cout << parse(line, ":", "!") + ": " + parse(line.substr(1, line.length()), ":", "") << std::endl;
			recievedMessages.push_back(line); //parsa medelande innan?
		}
	}

	do_read();
}
void IRCConnection::do_read(){
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

	try
	{
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query(hostname, port);
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		boost::asio::connect(socket, endpoint_iterator);
	}
	catch (boost::system::system_error& error)
	{
		std::cerr << error.code();
		return;
	}


	send(message::authenticate(username, nickname, password));
	send(message::joinChannel(channel));
	on_connect();
}

void IRCConnection::setReciever(std::string const& name){
	IRCConnection::recieverNick = name;
}

std::string IRCConnection::getReciever(){
	return IRCConnection::recieverNick;
}

void IRCConnection::setChannel(std::string chname){
	IRCConnection::channel = chname;
}

std::string IRCConnection::getChannel(){
	return IRCConnection::channel;
}

//inte helt färdig...
std::string IRCConnection::getMessage(){
	std::string strlist[40];
	return IRCConnection::recievedMessages.pop_back;

}

int main()
{
	static const std::string servername = "irc.rizon.net";
	static const std::string port = "6667";


	//Setup connection
	IRCConnection irc(servername, port);


	// Connect
	irc.setChannel("chat");

	irc.connect("testpw", "test123", "test123", irc.getChannel());
	irc.setReciever("nikey");
	std::string msg;

	while (getline(std::cin, msg))
	{
		if (msg[0] == '/'){
			msg = message::sendServerMsg(msg.substr(1, msg.length()));
		}
		else if (msg[0] == '+'){
			msg = message::sendPrivateMessage(msg.substr(1, msg.length()), irc.getChannel(), irc.getReciever());
		}
		else{
			msg = message::sendChannelMsg(msg, irc.getChannel());
		}
		irc.send(msg);
	}
}
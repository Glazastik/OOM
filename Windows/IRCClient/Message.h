#include<string>
namespace message{

	std::string authenticate(std::string username, std::string nickname, std::string password){
		std::string s = "NICK " + nickname + "\r\n" + "USER " + nickname + " testhost 127.0.0.1 :" + username + "\r\n";
		if (!password.empty()){
			s = s + "PASS " + password + "\r\n";
		}
		return s;
	}

	std::string joinChannel(std::string channelname){
		return "JOIN #" + channelname + "\r\n";
	}

	std::string sendChannelMsg(std::string message, std::string channel){
		return "PRIVMSG #" + channel + " " + message + "\r\n";
	}

	std::string sendServerMsg(std::string message){
		return message + "\r\n";
	}

	std::string sendPrivateMessage(std::string message, std::string channel, std::string usernick){
		return "PRIVMSG " + usernick + " " + message + "\r\n";
	}
}
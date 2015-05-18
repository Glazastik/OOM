#pragma once
#include <string>

class IRCMessageUtility
{
public:
	static std::string Authenticate(std::string username, std::string nickname, std::string password);
	static std::string JoinChannel(std::string channelname);
	static std::string SendChannelMsg(std::string message, std::string channel);
	static std::string SendServerMsg(std::string message);
	static std::string SendPrivateMessage(std::string message, std::string usernick);
private:
	IRCMessageUtility();
	~IRCMessageUtility();
};


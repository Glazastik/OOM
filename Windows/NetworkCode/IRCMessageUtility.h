#pragma once
#include <string>

class IRCMessageUtility
{
public:
	static std::string authenticate(std::string username, std::string nickname, std::string password);
	static std::string joinChannel(std::string channelname);
	static std::string sendChannelMsg(std::string message, std::string channel);
	static std::string sendServerMsg(std::string message);
	static std::string sendPrivateMessage(std::string message, std::string channel, std::string usernick);
private:
	IRCMessageUtility();
	~IRCMessageUtility();
};


#include "IRCMessageUtility.h"

// Public
std::string IRCMessageUtility::authenticate(std::string username, std::string nickname, std::string password)
{
	std::string s = "NICK " + nickname + "\r\n" + "USER " + nickname + " testhost 127.0.0.1 :" + username + "\r\n";
	if (!password.empty())
	{
		s = s + "PASS " + password + "\r\n";
	}
	return s;
}

std::string IRCMessageUtility::joinChannel(std::string channelname)
{
	return "JOIN #" + channelname + "\r\n";
}

std::string IRCMessageUtility::sendChannelMsg(std::string message, std::string channel)
{

	return "PRIVMSG #" + channel + " " + message + "\r\n";
}

std::string IRCMessageUtility::sendServerMsg(std::string message)
{
	return message + "\r\n";
}

std::string IRCMessageUtility::sendPrivateMessage(std::string message, std::string channel, std::string usernick)
{
	return "PRIVMSG " + usernick + " :" + message + "\r\n";
}

// Private
IRCMessageUtility::IRCMessageUtility()
{
}

IRCMessageUtility::~IRCMessageUtility()
{
}

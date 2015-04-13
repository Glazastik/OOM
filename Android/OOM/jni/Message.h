#pragma once
#include <iostream>

class Message
{
public:
	Message(int senderId, const std::string& payload);
	~Message();
	int GetSenderId();
	std::string GetPayload();
private:
	int senderId;
	std::string payload;
};

#pragma once
#include <string>
#include <vector>
#include <memory>
#include "ChatService.h"

class ChatModel
{
private:
	std::vector<std::shared_ptr<ChatService>> chatServices;
public:
	ChatModel();
	~ChatModel();
	std::string TestConnect(int serviceType);
	std::string GetMessage();
};

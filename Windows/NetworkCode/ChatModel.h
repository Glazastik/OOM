#pragma once
#include <string>
#include <vector>
#include <memory>
#include "ChatService.h"
#include "boost\asio.hpp"

class ChatModel
{
private:
	std::shared_ptr<boost::asio::io_service> io_service;
	std::vector<std::shared_ptr<ChatService>> chatServices;
public:
	ChatModel();
	~ChatModel();
	void ConnectService(int serviceType);
	void CloseService(int serviceType);
};

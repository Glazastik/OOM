#pragma once
#include <string>
#include <vector>
#include <memory>
#include "ChatService.h"
#include "boost\asio.hpp"
#include "Person.h"

class ChatModel
{
public:
	ChatModel();
	~ChatModel();
	void ConnectService(int serviceType);
	void CloseService(int serviceType);
	void AddPerson(std::shared_ptr<Person> person);
	std::shared_ptr<Person> GetPerson(int id);
	std::shared_ptr<Account> GetAccount(int id);
	void SendChatMessage(int accountId, std::string message);
private:
	std::shared_ptr<boost::asio::io_service> io_service;
	std::vector<std::shared_ptr<ChatService>> chatServices;
	std::vector<std::shared_ptr<Person>> persons;
};

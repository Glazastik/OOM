#pragma once
#include <string>
#include <vector>
#include <memory>
#include "ChatService.h"
#include "boost\asio.hpp"
#include "Person.h"
#include "boost\thread.hpp"

class ChatModel
{
public:
	ChatModel();
	~ChatModel();
	void ConnectService(int serviceType);
	void AddPerson(std::shared_ptr<Person> person);
	std::shared_ptr<Person> GetPerson(int id);
	std::shared_ptr<Account> GetAccount(int id);
	void SendChatMessage(int accountId, std::string message);
	void Cleanup();
private:
	std::shared_ptr<boost::asio::io_service> io_service;
	std::shared_ptr<boost::asio::io_service::work> work;
	std::vector<std::shared_ptr<ChatService>> chatServices;
	std::shared_ptr<std::vector<std::shared_ptr<Person>>> persons;
	boost::thread_group worker_threads;

	void InitThreads(int numThreads);
	void WorkerThread();
};

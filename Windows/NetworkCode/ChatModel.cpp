#include "ChatModel.h"
#include "GoogleHangout.h"
#include "boost/lexical_cast.hpp"
#include "boost/log/trivial.hpp"
#include "boost/bind.hpp"

// Public
ChatModel::ChatModel()
{
	io_service = std::make_shared<boost::asio::io_service>();
	work = std::make_shared<boost::asio::io_service::work>(*io_service);
	persons = std::make_shared<std::vector<std::shared_ptr<Person>>>();
	chatServices.push_back(std::make_shared<GoogleHangout>(io_service, "kandidattest2015@gmail.com", "test2015", persons));
	InitThreads(1);
}

ChatModel::~ChatModel()
{
}

void ChatModel::ConnectService(int serviceType)
{
	std::shared_ptr<ChatService> chatService = NULL;
	for (std::vector<std::shared_ptr<ChatService>>::iterator it = chatServices.begin(); it != chatServices.end(); ++it)
	{
		std::shared_ptr<ChatService> service = *it;
		if (service->GetServiceType() == serviceType)
		{
			chatService = service;
			chatService->Connect();
		}
	}
	if (chatService == NULL)
	{
		BOOST_LOG_TRIVIAL(error) << "ChatModel::ConnectService - Couldn't find service: " << boost::lexical_cast<std::string>(serviceType);
	}
}

void ChatModel::AddPerson(std::shared_ptr<Person> person)
{
	persons->push_back(person);
}

std::shared_ptr<Person> ChatModel::GetPerson(int id)
{
	std::shared_ptr<Person> person = NULL;
	for (std::vector<std::shared_ptr<Person>>::iterator it = persons->begin(); it != persons->end(); ++it)
	{
		std::shared_ptr<Person> p = *it;
		if (p->GetId() == id)
		{
			person = p;
		}
	}
	if (person == NULL)
	{
		BOOST_LOG_TRIVIAL(error) << "ChatModel::GetPerson - Person with specified id does not exist.";
	}
	return person;
}

std::shared_ptr<Account> ChatModel::GetAccount(int id)
{
	std::shared_ptr<Account> account = NULL;
	for (std::vector<std::shared_ptr<Person>>::iterator it = persons->begin(); it != persons->end(); ++it)
	{
		std::shared_ptr<Person> p = *it;
		std::vector<int> accountIds = p->GetAccountIds();
		if (std::find(accountIds.begin(), accountIds.end(), id) != accountIds.end())
		{
			account = p->GetAccount(id);
		}
	}
	if (account == NULL)
	{
		BOOST_LOG_TRIVIAL(error) << "ChatModel::GetAccount - Account with specified id does not exist.";
	}
	return account;
}

void ChatModel::SendChatMessage(int accountId, std::string message)
{
	std::shared_ptr<Account> account = GetAccount(accountId);
	if (account == NULL)
	{
		BOOST_LOG_TRIVIAL(error) << "ChatModel::SendChatMessage - Account with specified id does not exist.";
	}
	else
	{
		ServiceType::Type serviceType = account->GetServiceType();
		std::string address = account->GetAddress();

		std::shared_ptr<ChatService> chatService = NULL;
		for (std::vector<std::shared_ptr<ChatService>>::iterator it = chatServices.begin(); it != chatServices.end(); ++it)
		{
			std::shared_ptr<ChatService> service = *it;
			if (service->GetServiceType() == serviceType)
			{
				chatService = service;
				chatService->SendChatMessage(address, message);
			}
		}
		if (chatService == NULL)
		{
			BOOST_LOG_TRIVIAL(error) << "ChatModel::SendChatMessage - Account has a ServiceType that does not exist: " << boost::lexical_cast<std::string>(serviceType);
		}
	}
}

void ChatModel::Cleanup()
{
	for (std::vector<std::shared_ptr<ChatService>>::iterator it = chatServices.begin(); it != chatServices.end(); ++it)
	{
		std::shared_ptr<ChatService> service = *it;
		service->CloseConnection();
	}
	io_service->stop();
	worker_threads.join_all();
}

int ChatModel::GetServiceType(int accountId)
{

	std::shared_ptr<Account> account = GetAccount(accountId);
	if (account == NULL)
	{
		BOOST_LOG_TRIVIAL(error) << "ChatModel::SendChatMessage - Account with specified id does not exist.";
	}
	else
	{
		ServiceType::Type serviceType = account->GetServiceType();
		return (int)serviceType;
	}
	return -1;
}

// Private
void ChatModel::InitThreads(int numThreads)
{
	for (int i = 0; i < numThreads; ++i)
	{
		worker_threads.create_thread(boost::bind(&ChatModel::WorkerThread, this));
	}
}

void ChatModel::WorkerThread()
{
	BOOST_LOG_TRIVIAL(debug) << "Thread" << "[" << boost::this_thread::get_id() << "]" << " Start";
	io_service->run();
	BOOST_LOG_TRIVIAL(debug) << "Thread" << "[" << boost::this_thread::get_id() << "]" << " Stop";
}
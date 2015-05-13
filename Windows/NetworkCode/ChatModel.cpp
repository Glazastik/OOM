#include "ChatModel.h"
#include "GoogleHangout.h"
#include "boost/lexical_cast.hpp"
#include "boost/bind.hpp"

#ifdef __ANDROID__
#define LOG(string)	__android_log_print(ANDROID_LOG_DEBUG, "debug", "%s", string.c_str());
#include "android/log.h"
#else
#define LOG(string)	BOOST_LOG_TRIVIAL(debug) << "\n" << string;
#include "boost/log/trivial.hpp"
#endif

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
		std::stringstream message;
		message << "ChatModel::ConnectService - Couldn't find service: " << boost::lexical_cast<std::string>(serviceType);
		LOG(message.str());
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
		std::string message = "ChatModel::GetPerson - Person with specified id does not exist.";
		LOG(message);
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
		std::string message = "ChatModel::GetAccount - Account with specified id does not exist.";
		LOG(message);
	}
	return account;
}

void ChatModel::SendChatMessage(int accountId, std::string message)
{
	std::shared_ptr<Account> account = GetAccount(accountId);
	if (account == NULL)
	{
		std::string message = "ChatModel::SendChatMessage - Account with specified id does not exist.";
		LOG(message);
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
			std::stringstream message;
			message << "ChatModel::SendChatMessage - Account has a ServiceType that does not exist: " << boost::lexical_cast<std::string>(serviceType);
			LOG(message.str());
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
		std::string message = "ChatModel::SendChatMessage - Account with specified id does not exist.";
		LOG(message);
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
	std::stringstream message;
	message << "Thread" << "[" << boost::this_thread::get_id() << "]" << " Start";
	LOG(message.str());
	io_service->run();
	message.str("");
	message.clear();
	message << "Thread" << "[" << boost::this_thread::get_id() << "]" << " Stop";
	LOG(message.str());
}
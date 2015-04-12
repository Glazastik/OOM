#include "ChatModel.h"
#include "GoogleHangout.h"
#include "boost/lexical_cast.hpp"
#include "boost/log/trivial.hpp"

ChatModel::ChatModel()
{
	io_service = std::make_shared<boost::asio::io_service>();
	chatServices.push_back(std::make_shared<GoogleHangout>(io_service, "kandidattest2015@gmail.com", "test2015"));
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

void ChatModel::CloseService(int serviceType)
{
	std::shared_ptr<ChatService> chatService = NULL;
	for (std::vector<std::shared_ptr<ChatService>>::iterator it = chatServices.begin(); it != chatServices.end(); ++it)
	{
		std::shared_ptr<ChatService> service = *it;
		if (service->GetServiceType() == serviceType)
		{
			chatService = service;
			chatService->CloseConnection();
		}
	}
	if (chatService == NULL)
	{
		BOOST_LOG_TRIVIAL(error) << "ChatModel::CloseService - Couldn't find service: " << boost::lexical_cast<std::string>(serviceType);
	}
}

void ChatModel::AddPerson(std::shared_ptr<Person> person)
{
	persons.push_back(person);
}

std::shared_ptr<Person> ChatModel::GetPerson(int id)
{
	std::shared_ptr<Person> person = NULL;
	for (std::vector<std::shared_ptr<Person>>::iterator it = persons.begin(); it < persons.end(); ++it)
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
	for (std::vector<std::shared_ptr<Person>>::iterator it = persons.begin(); it < persons.end(); ++it)
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
	if (account != NULL)
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
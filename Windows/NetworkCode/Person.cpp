#include "Person.h"

#ifdef ANDROID
#define LOG(string)	__android_log_print(ANDROID_LOG_DEBUG, "debug", "%s", string.c_str());
#include "android/log.h"
#else
#define LOG(string)	BOOST_LOG_TRIVIAL(debug) << "\n" << string;
#include "boost/log/trivial.hpp"
#endif

Person::Person(int id, std::string name)
{
	this->id = id;
	this->name = name;
}

Person::~Person()
{
}

int Person::GetId()
{
	return id;
}

std::string Person::GetName()
{
	return name;
}

void Person::AddAccount(std::shared_ptr<Account> account)
{
	accounts.push_back(account);
}

std::shared_ptr<Account> Person::GetAccount(int id)
{
	std::shared_ptr<Account> account = NULL;
	for (std::vector<std::shared_ptr<Account>>::iterator it = accounts.begin(); it < accounts.end(); ++it)
	{
		std::shared_ptr<Account> acc = *it;
		if (acc->GetId() == id)
		{
			account = acc;
		}
	}
	if (account == NULL)
	{
		std::string message = "Person::GetAccount - Account with specified id does not exist.";
		LOG(message);
	}
	return account;
}

std::vector<int> Person::GetAccountIds()
{
	std::vector<int> accountIds;
	for (std::vector<std::shared_ptr<Account>>::iterator it = accounts.begin(); it < accounts.end(); ++it)
	{
		std::shared_ptr<Account> acc = *it;
		accountIds.push_back(acc->GetId());
	}
	return accountIds;
}
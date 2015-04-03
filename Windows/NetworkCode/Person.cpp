#include "Person.h"
#include "boost/log/trivial.hpp"

Person::Person()
{
	
}

Person::~Person()
{
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
		BOOST_LOG_TRIVIAL(debug) << "Error> Person::GetAccount - Account with specified id does not exist.";
	}
	return account;
}
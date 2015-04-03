#pragma once
#include <vector>
#include "Account.h"
#include <memory>

class Person
{
public:
	Person();
	~Person();
	void AddAccount(std::shared_ptr<Account> account);
	std::shared_ptr<Account> GetAccount(int id);
private:
	std::vector<std::shared_ptr<Account>> accounts;
};

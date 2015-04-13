#pragma once
#include <vector>
#include "Account.h"
#include <memory>

class Person
{
public:
	Person(int id, std::string name);
	~Person();
	int GetId();
	std::string GetName();
	void AddAccount(std::shared_ptr<Account> account);
	std::shared_ptr<Account> GetAccount(int id);
	std::vector<int> GetAccountIds();
private:
	int id;
	std::string name;
	std::vector<std::shared_ptr<Account>> accounts;
};

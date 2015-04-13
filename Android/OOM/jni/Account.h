#pragma once
#include "ServiceType.h"
#include <iostream>

class Account
{
public:
	Account(int id, ServiceType::Type serviceType, std::string address);
	~Account();
	int GetId();
	ServiceType::Type GetServiceType();
	std::string GetAddress();
private:
	int id;
	ServiceType::Type serviceType;
	std::string address;
};


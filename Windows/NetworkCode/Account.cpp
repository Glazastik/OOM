#include "Account.h"

Account::Account(int id, ServiceType::Type serviceType, std::string address)
{
	this->id = id;
	this->serviceType = serviceType;
	this->address = address;
}

Account::~Account()
{
}

int Account::GetId()
{
	return id;
}

ServiceType::Type Account::GetServiceType()
{
	return serviceType;
}

std::string Account::GetAddress()
{
	return address;
}
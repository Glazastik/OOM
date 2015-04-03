#include "Account.h"

int Account::next_id = 0;

Account::Account(ServiceType serviceType)
{
	id = next_id;
	next_id++;
	this->serviceType = serviceType;
}

Account::~Account()
{
}

int Account::GetId()
{
	return id;
}

ServiceType Account::GetServiceType()
{
	return serviceType;
}
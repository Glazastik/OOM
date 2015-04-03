#pragma once
#include "ServiceType.h"

class Account
{
public:
	Account(ServiceType serviceType);
	~Account();
	int GetId();
	ServiceType GetServiceType();
private:
	static int next_id;
	int id;
	ServiceType serviceType;
};


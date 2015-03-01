#pragma once
#include "ChatService.h"

class GoogleHangout : public ChatService
{
public:
	GoogleHangout();
	~GoogleHangout();
	ServiceType::Type GetServiceType();
	std::string TestConnect();
};

